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
# Display and validate options
#
#******************************************************************************

require 'optparse'
require 'fileutils'
require 'stringio'
require 'tmpdir'
require 'open3'

# Force stdout to flush its content immediately
STDOUT.sync = true

# Initialize global variables
$script_dir = File.expand_path(File.dirname(__FILE__))
$build_dir = File.join($script_dir, "build")
$lib_dir = ENV["SR_LIB_DIR"] || File.join($build_dir, "libs")
$lib_dir = $lib_dir.gsub("\\", "/")

# Parse command-line arguments into options
$options = {}

if $system_windows
	$processes = ["stingray_editor_backend.exe", "stingray_editor.exe", "stingray_win32_dev.exe", "stingray_win32_debug.exe",
		"stingray_win32_release.exe", "stingray_win64_dev.exe", "stingray_win64_debug.exe", "stingray_win64_release.exe", "console.exe"]
else
	$processes = []
end

require_relative 'tools/common.rb'

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

	if options[:verbose] == nil
		options[:verbose] = true
	end

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

def is_verbose?
	return $options[:verbose]
end

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
# Generate and build targets
#
#******************************************************************************

start_time = Time.now

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

	# Test cmake binaries exist
	$cmake_bin = File.join(find_package_root($options[:platform], $options[:devenv], "cmake"), $system_windows ? "win/cmake.exe" : $system_mac ? "mac/cmake" : "linux/cmake")
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
		$jom_dir = find_package_root($options[:platform], $options[:devenv], "jom")
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
		$emsdk_dir = find_package_root($options[:platform], $options[:devenv], "emscripten")
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
	elsif !!which("npm")
		Dir.chdir(File.join($script_dir)) {
			run_process("npm install", is_verbose?, $options[:pause])
		}
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

# Pause if requested
if $options[:pause]
	if $system_windows
		system "pause"
	else
		system "read -p \"Press any key to continue...\""
	end
end
