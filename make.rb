#!/usr/bin/env ruby
#******************************************************************************
#
# make.rb - launch build with default options
#
# This file will call make_switch.rb with multiple default options. If you
# need fine control over what is built, please use make_switch.rb instead. The
# script make_switch.rb does not have any components or plug-ins enabled by
# default.
#
#******************************************************************************

#******************************************************************************
#
# make_options.rb - display and validate options
#
# This file is responsible to control which options are available, parse them,
# and verify their coherence. This script file is used by both make.rb and
# make_switch.rb files. It also defines as set of utilities.
#
#******************************************************************************

require 'optparse'

# Force stdout to flush its content immediately
STDOUT.sync = true

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
	result = `ruby ./tools/spm.rb locate --lib-dir "#{$lib_dir}" #{arguments}`.lines.select{|line| line.include?(" = ")}.first
	return "" if result == nil or result.empty?
	return result.split("=")[1].strip
end

# Initialize global variables
$script_dir = File.expand_path(File.dirname(__FILE__))
$build_dir = File.join($script_dir, "build")
$lib_dir = ENV["SR_LIB_DIR"] || $build_dir
$lib_dir = $lib_dir.gsub("\\", "/")

# Define valid options
$platforms = ["win32", "win64", "ios", "android", "xb1", "ps4", "webgl", "uwp32", "uwp64", "linux"]
$platforms_whitelist = {
	"windows" => ["win32", "win64", "android", "xb1", "ps4", "webgl", "uwp32", "uwp64"],
	"mac" => ["osx", "ios"],
	"linux" => ["linux"]
}
$configs = ["debug", "dev", "release"]
$devenvs = ["msvc10", "msvc11", "msvc12", "msvc14", "xcode", "makefile"]
$devenvs_whitelist = {
	"win32" => ["msvc11", "msvc14"],
	"win64" => ["msvc11", "msvc14"],
	"ios" => ["xcode"],
	"android" => ["msvc11", "msvc14"],
	"xb1" => ["msvc14"],
	"ps4" => ["msvc11", "msvc14"],
	"webgl" => ["makefile"],
	"uwp64" => ["msvc14"],
	"uwp32" => ["msvc14"]
}
$remote_platforms = ["android", "ios", "ps4", "xb1"]

$platform_aliases = {
	"hololens" => "uwp32"
}
$platform_alias_options = {
	"hololens" => [:hololens]
}

if $system_windows
	$processes = ["stingray_editor_backend.exe", "stingray_editor.exe", "stingray_win32_dev.exe", "stingray_win32_debug.exe",
		"stingray_win32_release.exe", "stingray_win64_dev.exe", "stingray_win64_debug.exe", "stingray_win64_release.exe", "console.exe"]
else
	$processes = []
end

# Define default options
if $system_windows
	$default_platform = "win64"
elsif $system_mac
	$default_platform = "ios"
elsif $system_linux
	$default_platform = "linux"
end
$default_devenv = {
	"win32" => "msvc14",
	"win64" => "msvc14",
	"ios" => "xcode",
	"android" => "msvc14",
	"xb1" => "msvc14",
	"ps4" => "msvc14",
	"webgl" => "makefile",
	"uwp32" => "msvc14",
	"uwp64" => "msvc14",
	"linux" => "makefile"
}
$default_config = "dev"

# Parse command-line arguments into options
def parse_options(argv, options)
	options[:extra_plugins] = []
	opt_parser = OptionParser.new do |opts|
		opts.banner = "Usage: make.rb [options]"
		opts.separator ""
		opts.separator "Common Options:"
		opts.on("-o", "--output DIRECTORY", "Binaries output directory (override SR_BIN_DIR)") { |v| options[:output] = v }
		opts.on("-p", "--platform PLATFORM", "Platform to target (#{$platforms.join(", ")}, #{$platform_aliases.keys.join(", ")})") { |v| options[:platform] = v }
		opts.on("-c", "--config CONFIGURATION", "Build configuration to use (#{$configs.join(", ")})") { |v| options[:config] = v }
		opts.on("-e", "--devenv ENVIRONMENT", "Development environment to use (#{$devenvs.join(", ")})") { |v| options[:devenv] = v }
		opts.on("-t", "--target TARGET", "Target project to build (default is all)") { |v| options[:target] = v }
		opts.on("-r", "--rebuild", "Clean all output targets before build") { |v| options[:rebuild] = v }
		opts.on("-x", "--clean", "Clean all output targets only") { |v| options[:clean] = v }
		opts.on("-g", "--[no-]generate", "Generate project files (default)") { |v| options[:generate] = v }
		opts.on("-b", "--[no-]build", "Launch a build of generated project files (default)") { |v| options[:build] = v }
		opts.on("-z", "--[no-]debug-info", "Enable debug information in all configurations (default)") { |v| options[:debug_info] = v }
		opts.on("--[no-]engine", "Enable Engine target") { |v| options[:engine] = v }
		opts.on("--[no-]editor", "Enable Editor target") { |v| options[:editor] = v }
		opts.separator ""
		opts.separator "Other Options:"
		opts.on("-k", "--kill", "Kill running processes") { |v| options[:kill] = v }
		opts.on("-u", "--[no-]update", "Update library directory with latest versions (default)") { |v| options[:update] = v }
		opts.on("-v", "--[no-]verbose", "Print detailed build informations") { |v| options[:verbose] = v }
		opts.on("--distrib", "Bundle your plugin for distribution") { |v| options[:distrib] = v }
		opts.on("--pause", "Pause system on completion or error") { |v| options[:pause] = v }
		opts.on("-h", "--help", "Prints this help") do
			puts opts
			exit 1
		end
	end

	# Parse options
	begin
		opt_parser.parse(argv)
	rescue OptionParser::ParseError => e
		puts e
		puts
		puts opt_parser
		exit 1
	end

	return opt_parser
end

# Validate options
def validate_options(options, opt_parser)
	# Check if build is running on TeamCity
	options[:team_city] = false

	# Test or set default platform
	if options[:platform] == nil
		options[:platform] = $default_platform
	else
		#Check if platform is an alias
		if $platform_aliases.has_key?(options[:platform])
			# Enable options for this alias
			$platform_alias_options[options[:platform]].each do |plugin|
				options[plugin] = true
			end

			# Switch the platform to what it's an alias for
			options[:platform_alias] = options[:platform]
			options[:platform] = $platform_aliases[options[:platform]]
		end

		if !$platforms.include?(options[:platform])
			puts "\nError: Invalid platform '#{options[:platform]}' specified.".bold.red
			puts
			puts "Valid choices are one of: #{$platforms.join(", ")}, #{$platform_aliases.keys.join(", ")}"
			exit 1
		end
	end

	# Make sure the host system can build this platform
	if !$platforms_whitelist[$system_name].include?(options[:platform])
		puts "\nError: Platform '#{options[:platform]}' is not supported on #{$system_name} host system.".bold.red
		exit 1
	end

	# Test or set default configuration
	if options[:config] == nil
		options[:config] = $default_config
	else
		if !$configs.include?(options[:config])
			puts "\nError: Invalid configuration '#{options[:config]}' specified.".bold.red
			puts
			puts "Valid choices are one of: #{$configs.join(", ")}"
			exit 1
		end
		if options[:distrib]
			puts "\nOption --config has no effect in distrib builds.".bold.yellow
		end
	end

	# Test or set default development environment
	if options[:devenv] == nil
		options[:devenv] = $default_devenv[options[:platform]]
	else
		if !$devenvs.include?(options[:devenv])
			puts "\nError: Invalid development environment '#{options[:devenv]}' specified.".bold.red
			puts
			puts "Valid choices are one of: #{$devenvs.join(", ")}"
			exit 1
		end

		if !$devenvs_whitelist[options[:platform]].include?(options[:devenv])
			puts "\nError: Platform '#{options[:platform]}' using development environment '#{options[:devenv]}' is not supported.".bold.red
			exit 1
		end
	end

	# Test or set default target
	if options[:target] == nil
		if $system_windows and options[:devenv].include?("msvc")
			options[:target] = "build"
		else
			options[:target] = "install"
		end
	end

	# Enable debug info in all configurations by default
	if options[:debug_info] == nil
		options[:debug_info] = true
	end

	# Rebuild or Clean implies Build and Kill
	if options[:rebuild] or options[:clean]
		options[:build] = true
		options[:kill] = true
	end

	# Set default build products if none specified
	if options[:engine] == nil and options[:editor] == nil
		options[:engine] = true
		options[:editor] = options[:devenv] == "msvc14"
	end

	# Disable some products not supported by platform
	if options[:platform] != "win64"
		options[:editor] = false
	end

	# Set default output dir
	if options[:output] == nil
		options[:output] = File.join($script_dir, "plugin/binaries")
	end
	options[:output] = options[:output].gsub("\\", "/")

	# Make sure output dir is not equal to build dir
	if options[:output] == $build_dir
		puts "\nError: Output directory cannot be the same as build directory!".bold.red
		puts "Output directory: #{options[:output]}"
		exit 1
	end
end

# Parse command-line arguments into options
$options = {}

# Check if the user has a custom file that indicates what to build.
if File.exist?('make_args.txt') || File.exist?('.makeargs')
	make_arg_file_name = File.exist?('make_args.txt') ? 'make_args.txt' : '.makeargs'
	make_file_args = File.open(make_arg_file_name).read.strip.gsub(/#[^{].*[\r\n]?/, "").gsub(/\s+/, " ")
	validate_options($options, parse_options(make_file_args.split(" ").concat(ARGV), $options))
else
	validate_options($options, parse_options(ARGV, $options))
end


# Update libraries by default
if $options[:update] == nil
	$options[:update] = true
end

# Generate projects by default
if $options[:generate] == nil
	$options[:generate] = true
end

# Launch build by default
if $options[:build] == nil and $options[:rebuild] == nil and $options[:clean] == nil
	$options[:build] = true
end

# Enable debug info in all configurations by default
if $options[:debug_info] == nil
	$options[:debug_info] = true
end


#******************************************************************************
#
# make_switch.rb - generate and build targets
#
# This file is responsible for generating and building targets. Using this file
# directly will build without components or plug-ins by default. If you need
# default options, please use make.rb instead.
#
#******************************************************************************

require 'fileutils'
require 'stringio'
require 'tmpdir'
require 'open3'

start_time = Time.now

$package_root_cache = nil

def generate_package_root_cache()
	$package_root_cache = {}
	platform = $options[:platform]
	devenv = $options[:devenv]
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

	lines = `ruby ./tools/spm.rb locate --lib-dir "#{$lib_dir}" #{arguments}`.lines
	for line in lines
		if line.include?(" = ")
			split_line = line.split("=")
			package_name = split_line[0].strip
			package_location = split_line[1].strip
			$package_root_cache[package_name] = package_location
		end
	end
end

def find_package_root(package_name)
	if $package_root_cache == nil
		generate_package_root_cache()
	end

	$package_root_cache.each do |k, v|
		if k.include?(package_name)
			return v
		end
	end

	return ""
end

# Utility functions
def xcodebuild_quiet(command)
	# To filter Xcode output, we use egrep. But to return the exit code from the command, we store it in a random file in /tmp folder.
	return system "(s=/tmp/.$$_$RANDOM;((" + command + ";echo $?>$s)|(egrep #{$stdout.isatty() ? "--color=always " : ""}-A 5 \"(error|warning):\")); exit $(cat $s;rm $s))"
end

def is_verbose?
	return $options[:verbose] || $options[:team_city]
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

# Cross-platform way of finding an executable in the $PATH.
# which('ruby') #=> /usr/bin/ruby
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
		content += get_cmake_set_command("CMAKE_SYSTEM_VERSION", "10.0")
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

def get_copy_command(source, destination, mirror)
	if $system_mac or $system_linux
		if mirror == true
			return "mkdir -p #{File.dirname(destination).quotes}; ln -sfn #{source.quotes} #{destination.quotes}"
		else
			return "rsync -av --exclude 'version-id.txt' #{File.join(source, "/").quotes} #{File.join(destination, "/").quotes}"
		end
	else
		copy_op = mirror ? "/mir" : "/s"
		return "robocopy #{source.quotes} #{destination.quotes} #{copy_op} /nfl /ndl /njh /njs /nc /ns /np /xa:sh /xjd /xf version-id.txt"
	end
end

def copy_dir(source, destination, mirror = false)
	copy_command = get_copy_command(source, destination, mirror)
	puts "Copying #{source} to #{destination}" if is_verbose?
	command_output = `#{copy_command}`
	if command_output.strip.length > 0
		puts command_output.bold.yellow if is_verbose?
	end
end

def mirror_dir(source, destination)
	return copy_dir(source, destination, true)
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

def run_process(timeout_minutes, *args)
	require 'childprocess'

	puts "Running command: `#{args.join(' ')}`" if is_verbose?

	name = args[0]
	process = ChildProcess.build(*args)
	process.io.inherit!
	process.start
	begin
		process.poll_for_exit(timeout_minutes * 60)
	rescue ChildProcess::TimeoutError
		process.stop # tries increasingly harsher methods to kill the process.
		puts "\nTIMEOUT ERROR: Process #{name} #{args.join(' ')} took more than #{timeout_minutes} minutes.".bold.red
	end
	if process.exit_code != 0 then
		puts "\nERROR: Process #{name} #{args.join(' ')} has failed. See info above.".bold.red
		if $options[:team_city]
			puts "##teamcity[publishArtifacts '**/*.log => logs.zip']"
		end
		system "pause" if $options[:pause]
		exit 1
	end
end

$reports = Array.new
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

#******************************************************************************
#******************************************************************************
#******************************************************************************

# Update libraries
report_block($options[:update], "packages", "Downloading") do
	command = ["ruby", "./tools/spm.rb", "install-group", "--lib-dir", "\"#{$lib_dir}\"", "common"]

	command << "engine" if $options[:engine]
	command << "editor" if $options[:editor]
	command << "distrib" if $options[:distrib]
	command << "--platforms"
	command << $options[:platform]
	command << "--devenvs"
	if $options[:devenv].include?("msvc")
		if $options[:devenv] == "msvc12"
			command << "vc12"
		elsif $options[:devenv] == "msvc11"
			command << "vc11"
		elsif $options[:devenv] == "msvc14"
			command << "vc14"
		else
			puts "\nERROR: Unknown development environment for spm.rb script!".bold.red
			exit 1
		end
	else
		command << $options[:devenv]
	end

	# Go and run spm
	run_or_die(command.join(" "), false, true, true)
end

# Setup build system
report_block("plugin", "Configuring", true) do

	# Install build system
	copy_dir(find_package_root("stingray-plugin-sdk"), File.join($script_dir))

	# Test cmake binaries exist
	$cmake_bin = File.join(find_package_root("cmake"), $system_windows ? "win/cmake.exe" : $system_mac ? "mac/cmake" : "linux/cmake")
	if $cmake_bin == nil or !File.exist?($cmake_bin)
		puts "\nERROR: CMake binaries not found in library path!".bold.red
		exit 1
	end

	# Make sure the cmake binary has executable bit set on Unix based systems
	if !$system_windows
		if !File.stat($cmake_bin).executable?
			File.chmod(0755, $cmake_bin)
		end
	end

	# Setup NMake JOM build environment on Windows if using makefile
	if $system_windows and $options[:devenv] == "makefile"
		# Locate NMake JOM in library directory
		$jom_dir = find_package_root("jom")
		$jom_bin = File.join($jom_dir, "jom.exe")
		if $jom_bin == nil or !File.exist?($jom_bin)
			puts "\nERROR: JOM binary not found in library path!".bold.red
			exit 1
		end

		# Make sure JOM binary is in PATH for CMake to find it
		jom_path = which("jom.exe")
		if jom_path == nil
			ENV["PATH"] = "#{$jom_dir};#{ENV["PATH"]}"
		else
			if !jom_path.include?($lib_dir)
				puts "\nWARNING: JOM binary location found in PATH, but expected to find it here:".bold.yellow
				puts $jom_bin
			end
		end
	end

	# Setup Emscripten build environment if targeting platform WebGL
	if $options[:platform] == "webgl"
		# Locate Emscripten in library directory
		$emsdk_dir = find_package_root("emscripten")
		if $emsdk_dir == nil or !Dir.exists?($emsdk_dir)
			puts "\nERROR: Emscripten not found in library path!".bold.red
			exit 1
		end

		# Find Emscripten directories
		$emcc_dir = File.dirname(Dir.glob("#{$emsdk_dir}/**/emcc.bat").first)
		$em_llvm_dir = File.dirname(Dir.glob("#{$emsdk_dir}/**/clang.exe").first)
		$em_binaryen_dir = File.expand_path(File.join(File.dirname(Dir.glob("#{$emsdk_dir}/**/asm2wasm.exe").first), "../"))
		$em_nodejs = Dir.glob("#{$emsdk_dir}/**/node.exe").first
		$em_python = Dir.glob("#{$emsdk_dir}/**/python.exe").first
		$em_java = Dir.glob("#{$emsdk_dir}/**/java.exe").first
		$em_optimizer = Dir.glob("#{$emsdk_dir}/**/optimizer.exe").first
		$em_config = File.join($emsdk_dir, ".emscripten")
		$em_config_sanity = $em_config + "_sanity"
		$em_cache_dir = File.join($emsdk_dir, ".emscripten_cache")
		$em_tmp_dir = (ENV["SR_TMP_DIR"] || Dir.tmpdir).gsub("\\", "/")

		# Find Emscripten and LLVM version
		$em_version = File.read(File.join($emcc_dir, "emscripten-version.txt")).lines[0].gsub(/[\n\r"]/, '')
		Open3.popen3("#{File.join($em_llvm_dir, "clang.exe")} -v") do |stdin, stdout, stderr, wait_thr|
			$em_llvm_version = stderr.read.lines[0][/[\d].[\d]/]
		end

		# Temporarily override Emscripten environment
		ENV["EM_CONFIG"] = $em_config
		ENV["EM_CACHE"] = $em_cache_dir
		ENV["JAVA_HOME"] = File.dirname($em_java)
		ENV["EMSCRIPTEN"] = $emcc_dir
		ENV["PATH"] = "#{$emsdk_dir};#{ENV["PATH"]}"
		ENV["PATH"] = "#{$em_llvm_dir};#{ENV["PATH"]}"
		ENV["PATH"] = "#{File.dirname($em_nodejs)};#{ENV["PATH"]}"
		ENV["PATH"] = "#{File.dirname($em_python)};#{ENV["PATH"]}"
		ENV["PATH"] = "#{File.dirname($em_java)};#{ENV["PATH"]}"
		ENV["PATH"] = "#{$emcc_dir};#{ENV["PATH"]}"

		# Make sure directories exist
		FileUtils.mkdir_p($em_cache_dir) unless Dir.exists?($em_cache_dir)
		FileUtils.mkdir_p($em_tmp_dir) unless Dir.exists?($em_tmp_dir)
	end

	# Kill running processes
	if $options[:kill]
		if ["win32", "win64", "osx"].include?($options[:platform])
			$processes.each { |process| kill_process(process) }
		end
	end

	# Run clean operations
	if $options[:clean] or $options[:rebuild]
		dirs = []
		if $options[:editor]
			dirs << "editor" << "tools"
		end
		if $options[:engine]
			dirs << "engine"
		end
		dirs.each{|entry| FileUtils.rm_rf(File.join($options[:output], entry))}
	end
end

# Build engine components
report_block(File.exist?(File.join($script_dir, "engine")) && $options[:engine], "", "", true) do

	if $options[:distrib]
		build_configs = ["dev", "release"]
	else
		build_configs = [$options[:config]]
	end

	cmake_report("engine plugin", build_configs)
	cmake_build(File.join($script_dir, "engine"), File.join($build_dir, "engine/#{$options[:platform]}"), build_configs)
end

# Build editor components
report_block(File.exist?(File.join($script_dir, "editor")) && $options[:editor], "", "", true) do
	build_configs = $options[:distrib] ? ["release"] : ["dev"]
	cmake_report("editor plugin", build_configs)
	cmake_build(File.join($script_dir, "editor"), File.join($build_dir, "editor/#{$options[:platform]}"), build_configs)
end

#******************************************************************************
#******************************************************************************
#******************************************************************************

# Print total time elapsed
puts "\nSUCCESSFULLY COMPLETED!".bold.green
puts "Total Time Elapsed: %.2f seconds." % (Time.now - start_time)

if $options[:team_city]
	puts "##teamcity[buildStatus status='SUCCESS' text='All good Jim!']"
end

# Pause if requested
if $options[:pause]
	if $system_windows
		system "pause"
	else
		system "read -p \"Press any key to continue...\""
	end
end
