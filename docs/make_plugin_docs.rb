#******************************************************************************
#
# make_plugin_docs.rb - Builds Adoc documentation for your plugin project.
#
# Note: This script requires Stingray source access to run, due to the 
# dependency on Adoc.
# 
# Refer to the comments in this script to configure for documentation generation. 
# See also the other documentation example files in the `./docs` dir, as well as 
# the Stingray repository docs readme to learn how to annotate your code comments 
# for Adoc parsing.
#
# Usage:
#   1) Modify the configuration variables below if needed.
#   2) ruby make_plugin_docs.rb
#******************************************************************************

require 'optparse'
require 'fileutils'

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
end

$script_dir = File.expand_path(File.dirname(__FILE__))
$docs_dir = $script_dir
$plugin_dir = "#{$script_dir}/.."

#**************************************************************************
# Change these depending upon your plugin's needs.
$explicit_engine_dir = nil					# Path to Stingray source directory e.g. "c:\dev\stingray", alternatively set the %SR_SOURCE_DIR% environment variable.
$input_dirs = [
    "#{$plugin_dir}/engine",				# For Lua API documentation.
    "#{$docs_dir}/source/samples",
    "#{$docs_dir}/source/lua_reference",
	"#{$plugin_dir}/plugin/sample_project"
	# Add any additional paths for adoc to process as needed.
]
$output_dir = "#{$docs_dir}/output"
$config_path = "#{$docs_dir}/config_adoc_lua_reference.json"
#**************************************************************************

$engine_dir = $explicit_engine_dir || ENV["SR_SOURCE_DIR"]
if $engine_dir == nil or $engine_dir.empty?
    STDERR.puts "\nPlease define the %SR_SOURCE_DIR% environment variable or modify this script's $explicit_engine_dir to point to your Stingray source directory.".bold.red
    exit 1
end

$make_docs = "#{$engine_dir}/docs/build/make_docs.rb"
puts "Calling #{$make_docs}..."
STDOUT.flush
# This only builds the Lua API documentation. You can modify this to build other documentation types as needed.
$command = ["ruby #{$make_docs} --lua-ref", "--input",  "\"#{$input_dirs.join("\",\"")}\"",
																	 "--output", "\"#{$output_dir}\"",
																	 "--config", "\"#{$config_path}\"",
																	 *ARGV].join(" ")	# Pass any command line args through.
system($command)