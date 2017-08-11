#!/usr/bin/env ruby
#******************************************************************************
#
# common.rb - Common functionality for make and testsuite
#
#******************************************************************************

require 'pathname'
require 'open3'
require 'timeout'

require_relative './sjson'

# Force stdout to flush its content immediately
STDOUT.sync = true

# Constants
ERROR_STATUS = -1

# Define host system
if (/cygwin|mswin|mingw|bccwin|wince|emx/ =~ RUBY_PLATFORM) != nil
	$system_windows = true
	$system_name = "windows"
elsif (/darwin/ =~ RUBY_PLATFORM) != nil
	$system_mac = true
	$system_name = "mac"
else
	$system_linux = true
	$system_name = "linux"
end

$reports = Array.new

$platforms = ["win32", "win64", "ios", "osx", "android", "xb1", "ps4", "web", "uwp32", "uwp64", "linux"]

# Define valid options
$platforms_whitelist = {
	"windows" => ["win32", "win64", "android", "xb1", "ps4", "web", "uwp32", "uwp64"],
	"mac" => ["ios", "osx"],
	"linux" => ["linux"]
}

$platform_aliases = {
	"hololens" => "uwp32"
}
$platform_alias_options = {
	"hololens" => [:hololens]
}

$devenvs = ["msvc10", "msvc11", "msvc12", "msvc14", "msvc15", "xcode", "makefile"]
$default_devenv = {
	"win32" => "msvc14",
	"win64" => "msvc14",
	"ios" => "xcode",
	"osx" => "xcode",
	"android" => "msvc14",
	"xb1" => "msvc14",
	"ps4" => "msvc14",
	"web" => "makefile",
	"uwp32" => "msvc14",
	"uwp64" => "msvc14",
	"linux" => "makefile"
}

$devenvs_whitelist = {
	"win32" => ["msvc11", "msvc14", "msvc15"],
	"win64" => ["msvc11", "msvc14", "msvc15"],
	"ios" => ["xcode"],
	"osx" => ["xcode"],
	"android" => ["msvc14"],
	"xb1" => ["msvc14"],
	"ps4" => ["msvc14"],
	"web" => ["makefile"],
	"uwp64" => ["msvc14", "msvc15"],
	"uwp32" => ["msvc14", "msvc15"]
}

$configs = ["debug", "dev", "release"]

$remote_platforms = ["android", "ios", "ps4", "xb1"]

$build_settings = nil

# Define default platform
if $system_windows
	$default_platform = "win64"
elsif $system_mac
	$default_platform = "ios"
elsif $system_linux
	$default_platform = "linux"
end

$default_config = "dev"

$package_root_cache = nil

# Utility functions
class String
	def colorize(color_code); $stdout.isatty() ? "\e[#{color_code}m#{self}\e[0m" : self; end
	def black; colorize(30) end
	def red; colorize(31) end
	def green; colorize(32) end
	def yellow; colorize(33) end
	def blue; colorize(34) end
	def magenta; colorize(35) end
	def cyan; colorize(36) end
	def gray; colorize(37) end
	def default; colorize(39) end
	def bold; $stdout.isatty() ? "\e[1m#{self}\e[22m" : self; end
	def quotes; "\"#{self}\"" end
end

def set_title(title)
	puts "\e]0;#{title}\a" if $stdout.isatty()
end

def get_repository_root()
	current_working_dir = Dir.pwd

	Pathname.new(current_working_dir).ascend() do |path|
		make_rb = File.join(path, "make.rb")
		if File.exists?(make_rb)
			return path
		end
	end

	raise "Couldn't find make.rb location while searching ascending starting from \"#{current_working_dir}\""
end

def get_build_setting(*properties)
	if $build_settings == nil
		build_settings_path = File.join(get_repository_root(), "build-settings.sjson")
		$build_settings = Sjson.load(build_settings_path) if File.exist?(build_settings_path)
	end

	v = $build_settings
	return nil if !v
	properties.each {|name|
		return nil if !v[name]
		v = v[name]
	}
	return v
end

def get_package_root_cache(platform, devenv)
	if $package_root_cache == nil
		generate_package_root_cache(platform, devenv)
	end

	return $package_root_cache
end

def find_package_root(package_name)
	devenv = $options[:devenv] != "msvc15" ? $options[:devenv] : "msvc14"
	package_root_cache = get_package_root_cache($options[:platform], devenv)
	package_root_cache.each do |k, v|
		if k.include?(package_name)
			return v
		end
	end
	return ""
end

def get_copy_command(source, destination, mirror, ignore_patterns)
	if $system_mac or $system_linux
		if mirror == true
			return "mkdir -p #{File.dirname(destination).quotes}; ln -sfn #{source.quotes} #{destination.quotes}"
		else
			return "rsync -av --exclude 'version-id.txt' #{File.join(source, "/").quotes} #{File.join(destination, "/").quotes}"
		end
	else
		copy_op = mirror ? "/mir" : "/s"
		return "robocopy #{source.quotes} #{destination.quotes} #{copy_op} /nfl /ndl /njh /njs /nc /ns /np /xa:sh /xjd /xf version-id.txt #{ignore_patterns}"
	end
end

def copy_dir(source, destination, verbose, mirror = false, ignore_patterns = "")
	copy_command = get_copy_command(source, destination, mirror, ignore_patterns)
	puts "Copying #{source} to #{destination}" if verbose
	command_output = `#{copy_command}`
	if command_output.strip.length > 0
		puts command_output.bold.yellow if verbose
	end
end

def mirror_dir(source, destination, verbose, ignore_patterns = "")
	return copy_dir(source, destination, verbose, true, ignore_patterns)
end

def generate_package_root_cache(platform, devenv)
	$package_root_cache = {}
	arguments = "--all"
	if platform != nil and not platform.empty?
		arguments = "#{arguments} --platforms #{platform}"
	end
	if devenv != nil and not devenv.empty?
		modified_devenv = devenv
		if modified_devenv.start_with?('msvc')
			modified_devenv = modified_devenv[2..-1]
		end
		arguments = "#{arguments} --devenvs #{modified_devenv}"
	end

	begin
		Dir.chdir($script_dir) {
 			lines = `ruby ./tools/spm.rb locate --lib-dir "#{$lib_dir}" #{arguments}`.lines
 			for line in lines
 				if line.include?(" = ")
 					split_line = line.split("=")
 					package_name = split_line[0].strip
 					package_location = split_line[1].strip
 					$package_root_cache[package_name] = package_location
 				end
 			end
 		}
 	rescue Exception => e
 		puts "Unable to generate package root cache for platform: #{platform} and devenv: #{devenv}\n#{e}"
	end
end

def kill_process(process)
	if $system_windows
		return if !system "taskkill /f /im #{process} /T 2>nul 1>nul"
	elsif $system_mac
		return if !system "killall -KILL #{process.quotes} > /dev/null 2>&1"
	else
		puts "\nERROR: Kill process not implemented for this platform.".bold.red
		exit 1
	end
	puts "Killed running process '#{process}'.".bold.cyan
end

def kill_process_pid(pid)
	if $system_windows
		return if !system "taskkill /f /pid #{pid} /T 2>nul 1>nul"
	elsif $system_mac
		return if !system "killall -KILL #{pid} > /dev/null 2>&1"
	else
		puts "\nERROR: Kill process not implemented for this platform.".bold.red
		exit 1
	end
	puts "Killed running process '#{pid}'.".bold.cyan
end

def xcodebuild_quiet(command)
	# To filter Xcode output, we use egrep. But to return the exit code from the command, we store it in a random file in /tmp folder.
	return system "(s=/tmp/.$$_$RANDOM;((" + command + ";echo $?>$s)|(egrep #{$stdout.isatty() ? "--color=always " : ""}-A 5 \"(error|warning):\")); exit $(cat $s;rm $s))"
end

# command: Complete command and arguments string to run
# verbose: Whether process output is printed to console output
# pause: Whether script execution should pause on failed execution of command
# timeout_minutes: When specified, kills the spawned process by the command if not exited after specified minutes
# is_build: Used to control command execution for code building purposes
# print_time: If true, prints execution time of command
def run_process(command, verbose, pause, is_build = false, print_time = false, timeout_minutes: 0, exit_on_error: true)
	exit_code = 0
	command_start = Time.now
	# stdout, stderr pipes
	rout, wout = IO.pipe
	rerr, werr = IO.pipe
	if is_build and $system_mac and !verbose
		return exit_code if xcodebuild_quiet(command)
	else
		puts "Running command: #{command}" if verbose
		pid = nil
		if verbose
			$stdout.sync = true
			$stderr.sync = true
			pid = Process.spawn(command)
		else
			pid = Process.spawn(command, :out => wout, :err => [:child, :out])
		end
		begin
			Timeout.timeout(timeout_minutes * 60) do
				_, status = Process.wait2
				exit_code = status.exitstatus ||= $?.exitstatus ||= -1
				puts "Completed in %.2f seconds.".bold.default % (Time.now - command_start) if print_time
				return exit_code if exit_code == 0
			end
		rescue Timeout::Error
			exit_code = -1
			STDERR.puts "Process started by the following command didn't exit after #{timeout_minutes} minutes and was forcefully closed:"
			STDERR.puts "\"#{command}\""
			Process.kill('KILL', pid)
		end

		wout.close
		werr.close
	end
	if exit_on_error
		STDERR.puts "\nFailed to run command (#{exit_code}): #{command}".bold.red
		if !verbose
			STDERR.puts "NOTE: For more context on this error re-run make.rb command with -v option"
			@stdout = rout.readlines.join("\n")
			@stderr = rerr.readlines.join("\n")
			rout.close
			rerr.close
		end
		system "pause" if pause
		exit exit_code
	end

	return exit_code
end

def report_block_start(label, prefix = 'Running')
	$reports.push({label: label, time_start: Time.now})
	if label != ""
		puts "\n#{prefix} #{label}...".bold.cyan
	end
end

def report_block_end(print_time = false)
	report = $reports.pop
	if report == nil then return end
	if print_time
		puts "Completed in %.2f seconds.".bold.default % (Time.now - report[:time_start])
	end
end

# Report a block and scope it.
def report_block(*args) # ([condition], label, prefix, print_time)
	has_condition_arg = !args[0].is_a?(String)
	cond = !has_condition_arg || !!args[0]
	if cond
		label = has_condition_arg ? args[1] : args[0]
		prefix = has_condition_arg ? args[2] : args[1]
		print_time = has_condition_arg ? args[3] : args[2]
		report_block_start(label, prefix || "Running")
		yield
		report_block_end(print_time)
	end
end

def which(cmd)
	exts = ENV['PATHEXT'] ? ENV['PATHEXT'].split(';') : ['']
	ENV['PATH'].split(File::PATH_SEPARATOR).each do |path|
		exts.each { |ext|
			exe = File.join(path, "#{cmd}#{ext}")
			return exe if File.executable?(exe) && !File.directory?(exe)
		}
	end
	return nil
end

def find_specific_package_root(package_name, platform = nil, devenv = nil)
	arguments = "#{package_name}"
	if platform != nil and not platform.empty?
		arguments = "#{arguments} --platforms #{platform}"
	end
	if devenv != nil and not devenv.empty?
		modified_devenv = devenv
		if modified_devenv.start_with?('msvc')
			modified_devenv = modified_devenv[2..-1]
		end
		arguments = "#{arguments} --devenvs #{modified_devenv}"
	end
	result = `ruby ./spm.rb locate --lib-dir "#{$lib_dir}" #{arguments}`.lines.select{|line| line.include?(" = ")}.first
	return "" if result == nil or result.empty?
	return result.split("=")[1].strip
end

def run_or_die(command, is_build=false, print_time=false, override_verbose=false)
	command_start = Time.now
	if is_build and $system_mac and !$options[:verbose]
		return if xcodebuild_quiet(command)
	elsif is_verbose? or override_verbose
		puts "Running command: #{command}"
		result = system command
		puts "Completed in %.2f seconds.".bold.default % (Time.now - command_start) if print_time
		return if result
	else
		result = Open3.popen2e(command) { |stdin, stdout_and_stderr, wait_thr|
			stdin.puts "Y"
			stdin.close
			to_print = ''
			stdout_and_stderr.each {|line| to_print << line}
			print to_print if not wait_thr.value.success?
			wait_thr.value.success? # Return true or false based on command execution.
		}
		puts "Completed in %.2f seconds.".bold.default % (Time.now - command_start) if print_time
		return if result
	end
	puts "\nERROR: failed to run command: #{command}".bold.red
	system "pause" if $options[:pause]
	exit 1
end

def get_msvc_generator_name()
	generator = ""
	if $options[:devenv] == "msvc10"
		generator = "Visual Studio 10 2010"
	elsif $options[:devenv] == "msvc11"
		generator = "Visual Studio 11 2012"
	elsif $options[:devenv] == "msvc12"
		generator = "Visual Studio 12 2013"
	elsif $options[:devenv] == "msvc14"
		generator = "Visual Studio 14 2015"
	else
		puts "\nERROR: Development environment '#{$options[:devenv]}' not recognized.".bold.red
		exit 1
	end
	if $options[:platform] == "win64" or $options[:platform] == "uwp64"
		generator += " Win64"
	end
	return generator
end

def get_msvc_common_tools_path()
	vs_commmon_tools = ""
	if $options[:devenv] == "msvc11"
		vs_commmon_tools = ENV["VS110COMNTOOLS"]
	elsif $options[:devenv] == "msvc12"
		vs_commmon_tools = ENV["VS120COMNTOOLS"]
	elsif $options[:devenv] == "msvc14"
		vs_commmon_tools = ENV["VS140COMNTOOLS"]
	else
		puts "\nERROR: Development environment '#{$options[:devenv]}' not recognized.".bold.red
		exit 1
	end
	return vs_commmon_tools
end

def get_cmake_set_command(var, value)
	if value.is_a?(String)
		return "set(#{var} #{value.quotes} CACHE STRING \"\" FORCE)\n"
	else
		return "set(#{var} #{value ? "ON" : "OFF"} CACHE BOOL \"\" FORCE)\n"
	end
end

def cmake_cache_init(build_dir, config=nil)
	content = "# CMake Initial Cache File\n# Generated by make_switch.rb - DO NOT EDIT!!!\n"

	# Setup CMake global properties
	content += "\n# CMake Global Properties\n"
	content += get_cmake_set_command("CMAKE_INSTALL_PREFIX", $options[:output])
	content += get_cmake_set_command("CMAKE_CONFIGURATION_TYPES", "Debug;Dev;Release")
	if $options[:devenv] == "makefile"
		content += get_cmake_set_command("CMAKE_BUILD_TYPE", "#{config.capitalize}")
		content += get_cmake_set_command("CMAKE_RULE_MESSAGES", $options[:verbose])
	end
	if ($options[:platform] == "win64" or $options[:platform] == "win32") and ($options[:devenv] == "msvc14" or $options[:d3d12])
		# If building with VC14 or if DirectX 12 is enabled, requires targeting Windows 10 SDK
		content += get_cmake_set_command("CMAKE_SYSTEM_VERSION", "10.0")
	elsif $options[:platform] == "osx"
		content += get_cmake_set_command("CMAKE_OSX_ARCHITECTURES", "x86_64")
	elsif $options[:platform] == "ios"
		content += get_cmake_set_command("CMAKE_TOOLCHAIN_FILE", File.join($script_dir, "cmake/Toolchain-iOS.cmake"))
	elsif $options[:platform] == "android"
		content += get_cmake_set_command("CMAKE_TOOLCHAIN_FILE", File.join($script_dir, "cmake/Toolchain-Android.cmake"))
	elsif $options[:platform] == "xb1"
		content += get_cmake_set_command("CMAKE_TOOLCHAIN_FILE", File.join($script_dir, "cmake/Toolchain-XBoxOne.cmake"))
	elsif $options[:platform] == "ps4"
		content += get_cmake_set_command("CMAKE_TOOLCHAIN_FILE", File.join($script_dir, "cmake/Toolchain-PS4.cmake"))
	elsif $options[:platform] == "webgl"
		content += get_cmake_set_command("EMSCRIPTEN_GENERATE_BITCODE_STATIC_LIBRARIES", true)
		content += get_cmake_set_command("CMAKE_TOOLCHAIN_FILE", File.join($emcc_dir, "cmake/Modules/Platform/Emscripten.cmake"))
		if $options[:devenv].include?("msvc")
			content += get_cmake_set_command("CMAKE_GENERATOR_PLATFORM", "Emscripten")
		end
		content += get_cmake_set_command("EMSCRIPTEN_LLVM_ROOT", $em_llvm_dir)
		content += get_cmake_set_command("EMSCRIPTEN_BINARYEN_ROOT", $em_binaryen_dir)
		content += get_cmake_set_command("EMSCRIPTEN_NODEJS", $em_nodejs)
		content += get_cmake_set_command("EMSCRIPTEN_PYTHON", $em_python)
		content += get_cmake_set_command("EMSCRIPTEN_JAVA", $em_java)
		content += get_cmake_set_command("EMSCRIPTEN_NATIVE_OPTIMIZER", $em_optimizer)
		content += get_cmake_set_command("EMSCRIPTEN_CONFIG", $em_config)
		content += get_cmake_set_command("EMSCRIPTEN_CONFIG_SANITY", $em_config_sanity)
		content += get_cmake_set_command("EMSCRIPTEN_CACHE", $em_cache_dir)
		content += get_cmake_set_command("EMSCRIPTEN_TMP", $em_tmp_dir)
		content += get_cmake_set_command("EMSCRIPTEN_VERSION", $em_version)
		content += get_cmake_set_command("EMSCRIPTEN_LLVM_VERSION", $em_llvm_version)
	elsif $options[:platform] == "uwp32" or $options[:platform] == "uwp64"
		content += get_cmake_set_command("CMAKE_SYSTEM_NAME", "WindowsStore")
		content += get_cmake_set_command("CMAKE_SYSTEM_VERSION", "10.0.14393.0")
	end
	content += get_cmake_set_command("REPOSITORY_DIR", $script_dir)

	if $options[:platform_alias] != nil
		# Add platform define for platform aliases
		content += get_cmake_set_command("PLATFORM_#{$options[:platform_alias].upcase}", true)
	end

	# Setup engine properties
	content += "\n# Engine Properties\n"
	content += get_cmake_set_command("ENGINE_LIB_DIR", $lib_dir)
	content += get_cmake_set_command("ENGINE_USE_DEBUG_INFO", $options[:debug_info])

	# Setup engine plug-ins properties
	content += "\n# Engine Plug-ins Properties\n"
	content += get_cmake_set_command("ENGINE_USE__YOUR_PLUGIN_NAME__PLUGIN", true)

	# Setup editor properties
	content += "\n# Editor Properties\n"
	content += get_cmake_set_command("EDITOR_SHIPPING", false)

	# Write the CMake initial cache file
	cmake_cache_file = File.join(build_dir, "cmake_initial_cache.cmake")
	File.open(cmake_cache_file, 'w') { |file|
		file.write content
	}
	return cmake_cache_file
end

def get_cmake_build_command(config)
	cmake_build_command = $cmake_bin.quotes + " --build . --config #{config.capitalize}"
	if $options[:clean]
		cmake_build_command += " --target clean"
	else
		cmake_build_command += " --target #{$options[:target]}"
		if $options[:rebuild]
			cmake_build_command += " --clean-first"
		end
	end

	# Additional compiler specific options
	cmake_build_command += " --"
	if $system_windows
		cmake_build_command += " /nologo"
		if $options[:devenv].include?("msvc")
			cmake_build_command += " /p:WarningLevel=0"
			cmake_build_command += " /maxcpucount"
			cmake_build_command += " /nr:false"
			if $options[:platform] == "ps4"
				cmake_build_command += " /p:CL_MPCount=#{ENV["NUMBER_OF_PROCESSORS"]}"
			end
			if !$options[:verbose]
				cmake_build_command += " /verbosity:quiet"
			else
				cmake_build_command += " /verbosity:minimal"
			end
		elsif $options[:devenv] == "makefile"
			if !$options[:verbose]
				cmake_build_command += " /S"
			end
		end
	elsif $system_mac
		if $options[:platform] == "ios" and $options[:distrib]
			cmake_build_command += " CODE_SIGN_IDENTITY=\"\" CODE_SIGNING_REQUIRED=NO"
		end
	elsif $system_linux
		if $options[:devenv] == "makefile"
			cmake_build_command += " -j #{`nproc`.gsub("\n", "")}"
			if !$options[:verbose]
				cmake_build_command += " -s"
			end
		end
	end
	return cmake_build_command
end

def cmake_generate(cmake_file_dir, build_dir, config=nil)
	# Make sure build directory exist
	FileUtils.mkdir_p(build_dir) unless Dir.exists?(build_dir)

	# Get CMake generator name
	if $options[:devenv].include?("msvc")
		cmake_generator = get_msvc_generator_name()
	elsif $options[:devenv] == "xcode"
		cmake_generator = "Xcode"
	elsif $options[:devenv] == "makefile"
		if $system_windows
			cmake_generator = "NMake Makefiles JOM"
		else
			cmake_generator = "Unix Makefiles"
		end
	end

	# Run generate command from build directory
	Dir.chdir(build_dir) {
		run_or_die($cmake_bin.quotes + " -G #{cmake_generator.quotes} -C #{cmake_cache_init(build_dir, config).quotes} #{cmake_file_dir.quotes}")
	}
end

def cmake_build(cmake_file_dir, build_dir, build_configs)
	# For single configuration build systems, such as makefiles, we need to generate projects for each config. But for
	# multi-configuration build systems, such as Visual Studio or XCode, we can generate only once to get all configurations.
	if $options[:devenv] == "makefile"
		build_configs.each do |config|
			build_dir_config = File.join(build_dir, config)
			FileUtils.mkdir_p(build_dir_config) unless Dir.exists?(build_dir_config)
			if $options[:generate]
				cmake_generate(cmake_file_dir, build_dir_config, config)
			end
			if $options[:build]
				Dir.chdir(build_dir_config) {
					run_or_die(get_cmake_build_command(config), true)
				}
			end
		end
	else
		FileUtils.mkdir_p(build_dir) unless Dir.exists?(build_dir)
		if $options[:generate]
			cmake_generate(cmake_file_dir, build_dir)
		end
		if $options[:build]
			Dir.chdir(build_dir) {
				build_configs.each do |config|
					run_or_die(get_cmake_build_command(config), true)
				end
			}
		end
	end
end

def cmake_report(project_name, build_configs)
	return if not ($options[:generate] or $options[:build] or $options[:clean] or $options[:rebuild])
	build_type = !$options[:build] ? "Generating" : $options[:clean] ? "Cleaning" : $options[:rebuild] ? "Rebuilding" : "Building"
	print "\n#{build_type} [".bold.cyan
	print "#{$options[:platform].upcase}".bold.gray
	print "]".bold.cyan
	if $options[:build]
		print " [".bold.cyan
		print "#{build_configs.join(", ").upcase}".bold.gray
		print "]".bold.cyan
	end
	print " #{project_name}...\n".bold.cyan
end

def ms_build(solution_file, additional_options, build_config = "Release")
	build_command = "#{File.expand_path(File.join(get_msvc_common_tools_path(), "../../VC/vcvarsall.bat")).quotes} x86_amd64 && MSBuild.exe #{solution_file.quotes}"
	build_command += " /t:#{$options[:clean] ? "Clean" : $options[:rebuild] ? "Rebuild" : "Build"}"
	build_command += " /p:Configuration=#{build_config == "debug" ? "Debug" : "Release"}"
	build_command += " /p:Platform=\"Any CPU\" /maxcpucount"
	build_command += " /nr:false" # Don't keep msbuild.exe running when compilation is done.
	if additional_options
		build_command += " " + additional_options
	end
	if !$options[:verbose]
		build_command += " /nologo /verbosity:quiet"
	else
		build_command += " /verbosity:minimal"
	end

	run_or_die(build_command)
end
