#!/usr/bin/env ruby

=begin
spm(1) -- stingray package manager
==================================

## SYNOPSIS

`spm` *command* [*args*]...

## DESCRIPTION

spm(1) is a command for installing specific versions of external packages needed
to build the Stingray engine.

A "package" in spm terminology is a collection of files identified by a name.
You can install a package with the `install` command

    spm install cmake

"Installing" a package means downloading the latest version of the package and
extracting it to the *LIBRARY* directory.

Packages are specified in one or more `spm-packages.sjson` files that define for
each package, its name, its current version and how it can be downloaded. Only
the current version of the package is specified in the `spm-packages.sjson`
file.

The configuration files are typically checked into the source repository
together with the rest of the code, so that when you check out a version of the
source code you also have all the information about the libraries you need to
build it. The version control system thus provides the package history.

spm(1) uses a local cache directory *LIBRARY*`/spm` to store currently unused
package versions. This allows you to switch quickly between branches that use
different library versions without having to redownload all the data. You can
clear the cache with the `spm prune` command.

For convenience, packages can be assigned to groups and platforms. This allows
you to install groups of packages quickly. For example, this installs all
packages in the `engine` group that have `win64` listed as a platform:

	spm install-group --platforms win64 engine


## OPTIONS

* `--lib-dir`=*value*:
  Specifies the *LIBRARY* directory, where packages should be installed. If not
  specified `$SR_LIB_DIR` from the environment will be used.

* `--tmp-dir`=*value*:
  Specifies the temporary directory where files are stored during download. If
  not specified `$SR_TMP_DIR` from the environment will be used or the system's
  default temporary diretory.

* `--verbose`:
  Display verbose output.

* `--packages-root-dir=*value*`:
  Overrides default directory lookup root for sjson files to parse

## ENVIRONMENT

* `SR_LIB_DIR`:
  Default location of *LIBRARY* directory.

* `SR_TMP_DIR`:
  Default location of temporary directory.

## COMMANDS

`update`

Updates all installed packages to the current version.

`install` [`-a`|`--all`] [`-o`|`--populate`] *package*...

Installs the package with the specified name.

* `-a`, `--all`:
  Install all packages.

* `-o`, `--populate`:
  Populate the cache with the specified packages, but do not install them in the
  *LIBRARY* directory.

`uninstall` [--all] *package*...

Uninstalls the specified packages.

* `--all`:
  Uninstall all packages.

`install-group` [`-a`|`--all`] [`-p`|`--platforms`=*value*,...] [`-d`|`--devenvs`=*value*,...] [`-o`|`--populate`] *group*...

Install the specified package groups.

* `-a`, `--all`:
  Install all package groups.

* `-p`, `--platforms`=*value*,...:
  Specifies a comma separated list of platforms to match (i.e. `osx,android`).
  Only packages matching the specified platforms will be installed. If not
  specified, all platforms are installed.

* `-d`, `--devenvs`=*value*,...:
  Specifies a comma separated list of development environments to match
  (i.e. `vc11,vc12`). Only packages matching the specified development platforms
  will be installed. If not specified, all development environments are
  installed.

* `-o`, `--populate`:
  Populate the cache with the specified packages, but do not install them in the
  *LIBRARY* directory.

`uninstall-group` [`-a`|`--all`] [`-p`|`--platforms`=*value*,...] [`-d`|`--devenvs`=*value*,...] *group*...

Uninstalls the specified package groups.

* `-a`, `--all`:
  Uninstall all package groups.

* `-p`, `--platforms`=*value*:
  Specifies a comma separated list of platforms to match (i.e. `osx,android`).
  Only packages matching the specified platforms will be uninstalled. If not
  specified, all platforms are installed.

* `-d`, `--devenvs`=*value*:
  Specifies a comma separated list of development environments to match (i.e.
  `vc11,vc12`). Only packages matching the specified development platforms will
  be installed. If not specified, all development environments are uninstalled.

`list`

Lists all known packages.

`list-groups`

Lists all known package groups.

`cache`

Lists the content of the package cache.

`prune` [`-s`|`--size`=*value*] [`-a`|`--age`=*value*]

Prunes old items from the package cache.

* `-s`, `--size`=*value*:
  Specifies the size to trim the cache to (e.g. `10gb`).

* `-a`, `--age`=*value*:
  Specifies the age to trim the ache to (e.g. `30d`).

`verify`

Verify that the package specifications in the JSON files are correct.

## SPM-PACKAGES FILE FORMAT

When spm(1) is run it will look for any file named `spm-packages.sjson` or
*name*`-spm-packages.sjson` in the directory tree where it is run. All packages
found in those files will be added to the package list.

`spm-packages.sjson` files are written in the SJSON format which is a human
readable extension of the JSON format. Their basic format is

	source-templates = {
		default = {
			type = "s3"
			bucket = "stingray-public-platform-libs"
			access-key-id = "************"
			secret-access-key = "**************"
			region = "us-west-2"
		}
	}

	packages = {
		jpeg = {
			groups = ["engine", "jpeg"]
			platforms = ["win64", "win32"]
			lib = "jpeg-9a-windows-r1"
			version = "LvAgcuwMTu5itX1L8rH_bB.TqvQnaqQ8"
		}
	}

The `source-templates` section specifies data for one or more sources that
will be used to fetch packages. The `default` source will be used by all
packages that don't explicitly specify a source template to use.

The `packages` section specifies the available packages by name.

**Package**

* `lib` = *value*:
  Specifies the name of the package's root folder. Note that this may change for
  different versions of the package.

* `version` = *value*:
  Specifies the current version of the package. Note that the version depends on
  the source used. For S3, it is the S3 version of the uploaded file. For git,
  it is the SHA1 ID.

* `groups` = [*value*, ...]:
  Specifies the group(s) that this package belongs to.

* `platforms` = [*value*, ...]:
  Specifies the platform(s) this package is valid for. Possible values are
  `android`, `ios`, `win64`, `win32`, `xb1`, `ps4`, `osx`, `web`, `uwp32`, `uwp64`.
  If not specified, the package is assumed to be valid for all platforms.

* `devenvs` = [*value*, ...]:
  Specifies the development environment(s) this package is valid for. Possible
  values are `vc11`, `vc12`, `vc14`, `xcode`, `makefile`. If not specified,
  package is assumed to be valid for all development environments.

* `priority` = *value*:
  If there are multiple entries for the same package name, the one with the
  highest priority will be used. You can use this to override some of the global
  package settings for the project in a local file. If no priority is specified
  the priority is `0`.

* `source-template` = *value*:
  Specifies which source template should be used to fetch the package. If no
  source template is specified, the `default` template will be used.

* `source` = { *opts* }:
  Instead of using a `source-template` you can specify the source settings
  directly in the package definition.

In addition to these settings you can also override any of the source
settings in the package definition.

**Artifactory Source**

Used to download files from Artifactory.

* `type = "artifactory"`

* `server` = *value*

* `repository` = *value*

**S3 Source**

Used to download files from Amazon S3.

* `type = "s3"`

* `access-key-id` = *value*

* `secret-access-key` = *value*

* `region` = *value*

* `bucket` = *value*

### Git Source

Used to download files from Git.

* `type= "git"`

* `url` = *value*

### URL Source

Used to download package from an url end point.

* `type = "url"`

* `url` = *value*

### Manual Source

Used to download files from a manually downloaded zip file.

* `type = "manual"`

* `message` = *value*

* `zip` = *value*
=end

STDOUT.sync = true

require 'fileutils'
require 'tempfile'
require 'find'
require 'stringio'
require 'tmpdir'
require 'open3'
require 'timeout'
require 'open-uri'

begin
	require 'openssl'
	original_verbose = $VERBOSE
	$VERBOSE = nil
	OpenSSL::SSL::VERIFY_PEER = OpenSSL::SSL::VERIFY_NONE
	$VERBOSE = original_verbose
rescue LoadError => e
end

require File.expand_path('../sjson', __FILE__)

$s3_retry_limit = 10

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
	def bold; $stdout.isatty() ? "\033[1m#{self}\033[22m" : self; end
	def clear_line; $stdout.isatty() ? "\033[2K#{self}" : self; end
	def cursor_up; $stdout.isatty() ? "\033[A#{self}" : self; end
	def quotes; "\"#{self}\"" end
end

stderr = $stderr
Thread.abort_on_exception = true

passed_zip_min_version_check = false

# Auto install required gems
begin
	# Temporary redirect $stderr to get rid of "DL is deprecated, please use Fiddle" warning
	$stderr = StringIO.new
	require 'thor'
	$stderr = stderr

	gem 'zip', '>=2.0.2'
	passed_zip_min_version_check = true

	require 'aws-sdk-core'
	require 'artifactory'
	require 'zip/zip'
	require 'os'
	require 'slop'
	require 'childprocess'
	require 'websocket'

rescue LoadError => e
	$stderr = stderr
	puts e
	print "Error loading gems, should I try to install them for you [Y/n]: "
	answer = STDIN.gets.strip
	exit(-1) unless answer == '' || answer[/^[yY]/]

	sys = lambda do |s|
		puts(s)
		res = system(s)
		raise "execution error" unless res
	end
	sys.call("gem install thor --conservative")
	sys.call("gem install aws-sdk-core --conservative")
	if passed_zip_min_version_check
		sys.call("gem install zip --conservative")
	else
		sys.call("gem install zip -v 2.0.2")
	end
	sys.call("gem install os --conservative")
	sys.call("gem install artifactory --conservative")
	sys.call("gem install slop --conservative")
	# TODO might need to add '--platform=ruby' to avoid getting stuck in an infinite
	# 'cannot load such file -- ffi_c' on `require 'childprocess'`
	# on Windows the '--platform=ruby' option may require the RubyInstaller
	# https://github.com/oneclick/rubyinstaller/wiki/Development-Kit
	sys.call("gem install childprocess --conservative")
	sys.call("gem install websocket --conservative")
	Gem.clear_paths
	retry
end

def retry_rm_r(dir)
	return unless Dir.exist?(dir)
	retries = 10
	begin
		FileUtils.rm_r(dir)
	rescue Errno::ENOTEMPTY => e
		retries -= 1
		raise if retries <= 0
		puts "WARNING: Failed deleting directory #{dir}. Retrying (attempts left #{retries})".bold.yellow
		sleep(1)
		retry
	end
end

def retry_mv(a,b)
	retries = 10
	begin
		FileUtils.mv(a, b)
		if !Dir.exists?(b)
			raise Errno::EACCES
		end
	rescue Errno::EACCES => e
		retries -= 1
		raise if retries <= 0
		puts "WARNING: Failed moving #{a} --> #{b}. Retrying (attempts left #{retries})".bold.yellow
		sleep(1)
		retry
	end
end

# Global configuration
Configuration = Object.new
class << Configuration
	attr_accessor :verbose, :lib_dir, :tmp_dir, :packages_root_dir, :num_threads, :part_size
	def installed_file; File.join(lib_dir, 'spm-installed.sjson'); end
end

Configuration.lib_dir = ENV['SR_LIB_DIR']
Configuration.tmp_dir = ENV['SR_TMP_DIR']

Configuration.num_threads = 64
Configuration.part_size = 10

def log(s)
	puts(s) if Configuration.verbose
end

# Setup AWS
Aws.config[:ssl_verify_peer] = false

# Convert to/from human representation of time
class Time
	def self.to_human(t)
		scale = 2
		secs = t.to_i
		mins = secs / 60
		hours = mins / 60
		days = hours / 24
		months = days / 30
		years = days / 365
		return "#{secs} seconds" if secs < 60*scale
		return "#{mins} minutes" if mins < 60*scale
		return "#{hours} hours" if hours < 24*scale
		return "#{days} days" if days < 30*scale
		return "#{months} months" if months < 12*scale
		return "#{years} years"
	end

	def self.from_human(s)
		unless s =~ /^([\d.]+)([a-zA-Z]+)$/
			raise "bad time format"
		end
		units = $1.to_f
		unit = $2.downcase
		case unit
		when 's', 'sec', 'secs', 'second', 'seconds'
			return units
		when 'm', 'min', 'mins', 'minute', 'minutes'
			return 60*units
		when 'h', 'hour', 'hours'
			return 60*60*units
		when 'd', 'day', 'days'
			return 24*60*60*units
		when 'month', 'months'
			return 30*24*60*60*units
		when 'y', 'year', 'years'
			return 365*24*60*60*units
		else
			raise "unknown time unit `#{unit}`"
		end
	end
end

# Convert to/from human representation of memory size
class MemorySize
	def self.to_human(s)
		b = s
		kb = b / 1024.0
		mb = kb / 1024.0
		gb = mb / 1024.0
		tb = gb / 1024.0

		lim = 1

		return "#{b} B" if kb < lim
		return "#{sprintf('%.1f', kb)} KB" if mb < lim
		return "#{sprintf('%.1f', mb)} MB" if gb < lim
		return "#{sprintf('%.1f', gb)} GB" if tb < lim
		return "#{sprintf('%.1f', tb)} TB"
	end

	def self.from_human(s, default_unit: nil)
		unless s.downcase =~ /^([\d.]+)([kmgt]?b?)$/
			raise "bad memory format"
		end
		units = $1.to_f
		unit = $2.empty? ? default_unit : $2
		raise "no memory unit" unless unit
		case unit
		when 'b'
			return units
		when 'kb', 'k'
			return units*1024
		when 'mb', 'm'
			return units*1024*1024
		when 'gb', 'g'
			return units*1024*1024*1024
		when 'tb', 'g'
			return units*1024*1024*1024*1024
		else
			raise "unknown memory unit `#{unit}`"
		end
	end
end

Platform = Struct.new(:name)

Android = Platform.new('android')
IOS = Platform.new('ios')
Win64 = Platform.new('win64')
Win32 = Platform.new('win32')
XboxOne = Platform.new('xb1')
PS4 = Platform.new('ps4')
OSX = Platform.new('osx')
Web = Platform.new('web')
UWP32 = Platform.new('uwp32')
UWP64 = Platform.new('uwp64')
Linux = Platform.new('linux')

class Platform
	def self.all
		[Android, IOS, Win64, Win32, XboxOne, PS4, OSX, Web, UWP32, UWP64, Linux]
	end
	def self.from_s(name)
		all.each {|p| return p if name == p.name}
		raise "unknown platform `#{name}`"
	end
	def self.whitelist
		whitelist = Platform.all.map{|p| p.name}
		whitelist << "win"
		whitelist << "uwp"
		whitelist << "winuwp"
		whitelist << "winuwp32"
		whitelist << "winuwp64"
		whitelist.sort_by!{|p| p.downcase}
		return whitelist
	end
end

Devenv = Struct.new(:name)

VC11 = Devenv.new('vc11')
VC12 = Devenv.new('vc12')
VC14 = Devenv.new('vc14')
Xcode = Devenv.new('xcode')
Makefile = Devenv.new('makefile')

class Devenv
	def self.all
		[VC11, VC12, VC14, Xcode, Makefile]
	end
	def self.from_s(name)
		all.each {|e| return e if name == e.name}
		raise "unknown devenv `#{name}`"
	end
	def self.whitelist
		whitelist = Devenv.all.map{|e| e.name}.select{|e| e.include?("vc")}
		whitelist.sort_by!{|e| e.downcase}
		return whitelist
	end
end

# Global object representing the cache
Cache = Object.new
class << Cache
	include Enumerable

	def root
		File.join(Configuration.lib_dir, 'spm')
	end

	def has?(lib, version)
		return Dir.exist?(dir(lib,version))
	end

	def dir(lib,version)
		short_version = version[0,8]
		return File.join(root, "#{lib}-#{short_version}")
	end

	Entry = Struct.new(:name, :size, :age, :path)

	def each
		each_entry do |name, path|
			yield Entry.new(name, dirsize(name), Time.now - File.mtime(path), path)
		end
	end

	# Prune cache by age or size. If neither is set, prunes all files.
	def prune(age: nil, size: nil)
		if age
			select {|e| e.age > age}.each {|e| retry_rm_r(e.path)}
		elsif size
			while total_size > size
				retry_rm_r(max_by {|e| e.age}.path)
			end
		else
			each_entry do |name, path|
				retry_rm_r(path)
			end
		end
	end

	def total_size
		collect {|e| e.size}.reduce(0, :+)
	end

private
	def each_entry
		return unless Dir.exists?(root)
		Dir.entries(root).each do |name|
			next if name[/^\./]
			path = File.join(root, name)
			next unless Dir.exists?(path)
			yield name, path
		end
	end

	def dirsize(name)
		infopath = File.join(root, "info.sjson")
		info = File.exist?(infopath) ? Sjson.load(infopath) : {}
		info[name] = {} unless info[name]
		info[name]["size"] = compute_dirsize(File.join(root, name)) unless info[name]["size"]
		Sjson.save(info, infopath)
		return info[name]["size"]
	end

	def compute_dirsize(path)
		size = 0
		Find.find(path) do |f| size += File.stat(f).size end
		return size
	end
end

# Base class for sources for package installs
class Source
end

# Thread pool for running threaded jobs
class ThreadPool
	class Task
		attr_writer :thread
		def initialize(action)
			@action = action
			@done = false
			@thread = nil
		end

		def run
			@action.call()
			@done = true
		end

		def join
			if Configuration.num_threads > 0
				sleep(0.5) until @done
			end
		end

		def alive?
			!@done
		end
	end

	def initialize(size)
		@threads = []
		@max_threads = size
		@queue = []
	end

	def add(&action)
		task = Task.new(action)
		if Configuration.num_threads == 0
			task.run
			return task
		end

		if @threads.size < @max_threads
			t = Thread.new do
				task.thread = t
				task.run
				while x = @queue.shift
					x.run
				end
				@threads.delete(t)
			end
			@threads << t
		else
			@queue << task
		end
		return task
	end
end
$DefaultThreadPool = nil

Part = Struct.new(:temp_file, :offset, :len, :downloaded, :task)

class ArtifactorySource < Source
	def initialize(opts, lib: nil, version: nil)
		@lib = lib
		@version = version
		@server = opts['server']
		@repository = opts['repository']
	end

	def get(dest_dir)
		begin
			client = Artifactory::Client.new(
				endpoint: @server,
				username: ENV['ARTIFACTORY_USER'],
				password: ENV['ARTIFACTORY_PASSWORD'],
				ssl_verify: false
			)
		rescue
			raise "Could not create an Artifactory client for #{@server}"
		end

		FileUtils.mkdir_p(dest_dir) unless File.exists?(dest_dir)
		artifact = @lib + '-' + @version + '.zip'
		artifactory_path = [@repository,@lib,@version,artifact].join('/')
		puts "requested Artifactory path: #{artifactory_path}" if Configuration.verbose
		dest_dir_temp = Dir.mktmpdir(nil,Configuration.tmp_dir)
		zipfile = File.join(dest_dir_temp, 'tmp-' + artifact)
		zipdir = File.join(dest_dir_temp, @lib)
		FileUtils.mkdir_p(zipdir)

		@state = :download

		begin
			File.open(zipfile, 'wb') do |file|
				file.write(client.get(artifactory_path))
			end
		rescue
			puts "Could not download #{artifactory_path}"
			raise
		end

		@state = :unzip

		begin
			Zip::ZipFile.open(zipfile) do |file|
				file.each do |f|
					filename = f.name.force_encoding("UTF-8")
					path = File.join(zipdir, File.dirname(filename))
					FileUtils.mkdir_p(path)
					file.extract(f, File.join(path, filename))
				end
			end
			retry_mv(zipdir, dest_dir)
		rescue
			retry_rm_r(dest_dir)
			raise
		end

		@state = :done
	end

	def populate_progress_string
		if @state == :getting_size
			return "(starting)"
		elsif @state == :download
			return "(downloading)"
		elsif @state == :unzip
			return "(unzipping)"
		elsif @state == :done
			return "(done)"
		else
			return ""
		end
	end

	def verify; end
end

class PartDownloadError < RuntimeError; end
class CorruptZipError < RuntimeError; end

# Source based on an AWS S3 bucket
class S3Source < Source

	def initialize(opts, lib: nil, version: nil)
		@access_key_id = opts["access-key-id"]
		@secret_access_key = opts["secret-access-key"]
		@region = opts["region"]
		@bucket = opts["bucket"]
		@lib = lib
		@version = version
		@key = lib + ".zip"
		@last_time = Time.now
		@last_downloaded = 0
		@num_downloading_task = 0

		# List server versions unless specified
		unless @version
			puts
			puts "CONFIGURATION ERROR: No version specified for `#{@lib}`. (Options below.)".bold.red
			list_versions
			puts
		end
	end

	def list_versions
		if versions and versions.last
			puts
			versions.each {|item| puts "* #{item.version_id} (#{item.last_modified})"}
			@version = versions.last.version_id
		else
			puts "* No version found on server!"
		end
	end

	def get(dest_dir)
		@state = :getting_size

		log "Getting size of #{id}"
		begin
			s3 = Aws::S3::Client.new(
				access_key_id: @access_key_id,
				secret_access_key: @secret_access_key,
				region: @region,
				retry_limit: $s3_retry_limit)

			head = s3.head_object(bucket: @bucket, version_id: @version, key: @key)
		rescue
			raise "could not download `#{@lib}` at version `#{@version}` from S3"
		end
		@total_download_size = head[:content_length]

		begin
			get_internal(s3, dest_dir)
		rescue CorruptZipError
			@state = :corrupt
			sleep(5)
			retry
		end
	end

	def get_internal(s3, dest_dir)
		@downloading_files = []

		zip = Tempfile.new("#{short_id}.", Configuration.tmp_dir)
		zip.close

		log("Downloading #{id}")

		if Configuration.num_threads == 0 # need some basic progress report if no multithread
			puts("Downloading #{@lib} (#{MemorySize.to_human(@total_download_size)})")
		end

		@state = :download

		num_parts = 1
		part_byte_size = Configuration.part_size*1024*1024
		if part_byte_size > 0
			num_parts = ((@total_download_size - 1) / part_byte_size) + 1
		end

		if num_parts == 1
			task = $DefaultThreadPool.add do
				@num_downloading_task += 1
				@downloading_files << zip.path
				begin
					response = s3.get_object(bucket: @bucket, version_id: @version, key: @key, response_target: zip.path)
				rescue Errno::EACCES
					# Windows file locking fun
					retry
				rescue Seahorse::Client::NetworkingError
					retry
				end
				raise PartDownloadError.new if File.size(zip.path) != @total_download_size
				@num_downloading_task -= 1
			end
			task.join
		else
			parts = []
			for i in 0..(num_parts-1) do
				offset = i * part_byte_size
				len = [offset + part_byte_size, @total_download_size].min - offset
				temp_file = Tempfile.new("#{short_id}.#{i}.", Configuration.tmp_dir)
				temp_file.close
				@downloading_files << temp_file.path
				parts[i] = Part.new(temp_file, offset, len, 0, nil)
			end

			parts.each do |part|
				part.task = $DefaultThreadPool.add do
					@num_downloading_task += 1
					range = "bytes=#{part.offset}-#{part.offset+part.len-1}"
					begin
						response = s3.get_object(bucket: @bucket, version_id: @version, key: @key, range: range,
							response_target: part.temp_file.path)
					rescue Errno::EACCES
						# Windows file locking fun
						retry
					rescue Seahorse::Client::NetworkingError
						retry
					end
					raise PartDownloadError.new if File.size(part.temp_file.path) != part.len
					@num_downloading_task -= 1
				end
			end

			# aggregate all part.temp_file into zip
			File.open(zip.path, 'wb') do |file|
				parts.each do |part|
					part.task.join
					data = nil
					File.open(part.temp_file.path, 'rb') {|part| data = part.read}
					file.write(data)
				end
			end
		end

		if Configuration.num_threads == 0 # need some basic progress report if no multithread
			puts("Downloading #{@lib} (#{MemorySize.to_human(@total_download_size)}) done")
		end

		@state = :unzip

		begin
			Zip::ZipFile.open(zip.path) {}
		rescue TypeError
			raise CorruptZipError.new
		end

		begin
			dest_dir_temp = Dir.mktmpdir("temp-#{File.basename(dest_dir)[0,10]}-", Cache.root)
			Zip::ZipFile.open(zip.path) { |zip_file|
				zip_file.each { |f|
					filename = f.name.force_encoding("UTF-8")
					FileUtils.mkdir_p(File.join(dest_dir_temp, File.dirname(filename)))
					zip_file.extract(f, File.join(dest_dir_temp, filename))
				}
			}

			# Add version id file
			version_file = File.join(dest_dir_temp, @lib, "version-id.txt")
			File.open(version_file, "w") do |f|
				f.write(@version)
			end

			retry_mv(dest_dir_temp, dest_dir)
		rescue
			retry_rm_r(dest_dir)
			retry_rm_r(dest_dir_temp) if dest_dir_temp
			raise $!, "Problem extracting zip file `#{zip.path}`: #{$!}", $!.backtrace
		end

		@state = :done
	end

	def populate_progress_string
		if @state == :getting_size
			return "(starting)"
		elsif @state == :download
			now = Time.now
			if @num_downloading_task == 0 || @downloading_files.empty? then
				progress = "(pending)"
			else
				downloaded = @downloading_files.map {|f| File.size?(f) || 0}.reduce(:+) || 0
				download_percent = sprintf('%.1f', downloaded.to_f / @total_download_size.to_f * 100.0)
				download_size = "#{MemorySize.to_human(downloaded)} of #{MemorySize.to_human(@total_download_size)}"
				download_speed = (downloaded - @last_downloaded).to_f / (now - @last_time)
				progress = "#{download_percent}% (#{download_size})#{download_speed > 0.0 ? " - #{MemorySize.to_human(download_speed)}/s" : ""}"
				@last_downloaded = downloaded
				@last_time = now
			end
			return progress
		elsif @state == :unzip
			return "(unzipping)"
		elsif @state == :done
			return "(done)"
		elsif @state == :corrupt
			return "(error: corrupt zip file -- will retry)"
		else
			return ""
		end
	end

	def verify
		if versions.empty?
			puts "`#{@lib}`: no versions found on S3"
		elsif !versions.any? {|v| v.version_id == @version}
			puts "`#{@lib}`: version `#{@version}` not found on S3, latest is `#{versions.last.version_id}`"
		elsif versions.last.version_id != @version
			puts "`#{@lib}`: version `#{@version}` is not latest version, latest is `#{versions.last.version_id}`"
		end
		matches = /^([a-z0-9\-]+)\-([a-z0-9]*[0-9]+)\.?([a-z0-9]*)\.?([a-z0-9]*)\.?([a-z0-9]*)\-?([a-z0-9]*)\-?([a-z0-9]*)$/.match(@lib)
		if matches == nil
			raise "`#{@lib}`: invalid package name, please follow package naming convention: name-major[.minor][.patch][.rev][-platform][-compiler]"
		else
			name, major, minor, patch, rev, platform, compiler = matches.captures
			if !platform.empty? and !Platform.whitelist.include?(platform)
				raise "`#{@lib}`: invalid platform name `#{platform}`, must be one of: #{Platform.whitelist.join(", ")}"
			end
			if !compiler.empty? and !Devenv.whitelist.include?(compiler)
				raise "`#{@lib}`: invalid compiler name `#{compiler}`, must be one of: #{Devenv.whitelist.join(", ")}"
			end
		end
	end

private
	def id
		return "#{@lib}-#{@version}"
	end

	def short_id
		return "#{@lib[/[[:alnum:]]+/]}-#{@version[0,8]}"
	end

	def versions
		return S3Source.versions_for(access_key_id: @access_key_id, secret_access_key: @secret_access_key,
			region: @region, bucket: @bucket, key: @key)
	end

	def self.versions_for(access_key_id: nil, secret_access_key: nil, region: nil, bucket: nil, key: nil)
		@versions ||= {}
		if @versions[bucket] == nil
			s3 = Aws::S3::Client.new(access_key_id: access_key_id, secret_access_key: secret_access_key, region: region)
			resp = s3.list_object_versions(bucket: bucket)
			@versions[bucket] = resp.versions
			while resp.is_truncated
				resp = s3.list_object_versions(bucket: bucket, key_marker: resp.next_key_marker)
				@versions[bucket] += resp.versions
			end
		end
		@versions[bucket].select {|item| item.key == key}.sort_by {|item| item.last_modified}
	end
end

class GitSource < Source
	def initialize(opts, lib: nil, version: nil)
		@sshUrl = opts['ssh-url']
		@httpsUrl = opts['https-url']
		raise "No url" unless @sshUrl || @httpsUrl
		@lib = lib
		@version = version
		@progress = ""
	end

	def get(dest_dir)
		begin
			dest_dir_temp = Dir.mktmpdir("temp-#{File.basename(dest_dir)[0,10]}-", Cache.root)
			dir = File.join(dest_dir_temp, @lib)

			ssh_failed = false
			https_timeout = false

			if @sshUrl
				Open3.popen3("git clone --progress #{@sshUrl} #{dir}") do |i,o,e|
					i.close
					e.each do |line|
						puts line
						@progress = line.strip
						if line.include? "Permission denied (publickey)."
							ssh_failed = true
						end
					end
				end
			end

			if (ssh_failed)
				puts "Cannot connect using SSH. Trying HTTPS..."
			end

			if !@sshUrl || ssh_failed

				gitCredConfigValue = `git config --global --get credential.helper`
				areCredsCached = gitCredConfigValue.include? "wincred"
				if !areCredsCached
					puts "HTTPS credentials are not cached. Aborting.".bold.red
					puts "Git config value credential.helper='#{gitCredConfigValue}'"
					puts "Note that SSH was tried first, but it failed."
					exit(1)
				end

				Open3.popen3("git clone --progress #{@httpsUrl} #{dir}") do |i,o,e,w|
					begin
						Timeout.timeout(300) do
							i.close
							e.each do |line|
								@progress = line.strip
							end
						end
					rescue Timeout::Error
						https_timeout = true
						Process.kill("KILL", w.pid)
					end
				end

				if https_timeout
					puts "Cloning the repo timed out.\nMake sure that the git credentials saved with wincred are correct.".bold.red
					exit(1)
				end
			end

			Dir.chdir(dir) do
				Open3.popen3("git checkout #{@version}") do |i,o,e|
					i.close
					o.close
					e.close
				end
			end

			# Add version id file
			version_file = File.join(dest_dir_temp, @lib, "version-id.txt")
			File.open(version_file, "w") do |f|
				f.write(@version)
			end

			retry_mv(dest_dir_temp, dest_dir)
			@progress = "(done)"
		rescue
			retry_rm_r(dest_dir)
			retry_rm_r(dest_dir_temp) if dest_dir_temp
			raise
		end
	end

	def populate_progress_string
		return @progress
	end

	def verify; end
end

class ManualSource < Source
	def initialize(opts, lib: nil, version: nil)
		@lib = lib
		@message = opts['message']
		@version = version
		@prompt = "Location of #{lib}.zip: "
		@zip = opts['zip']
		@state = nil
	end

	def prepare_get(dest_dir)
		return if @zip

		raise "Cannot install manual packages without a TTY" unless $stdin.isatty

		puts @message
		puts
		while true
			print @prompt
			file = $stdin.gets.strip
			if File.exist?(file)
				@zip = file
				return
			end
			puts "ERROR: File not found `#{file}`".red
		end
	end

	def get(dest_dir)
		raise "No zip file specified" unless @zip

		@state = :unzip

		begin
			dest_dir_temp = Dir.mktmpdir("temp-#{File.basename(dest_dir)[0,10]}-", Cache.root)
			container = File.join(dest_dir_temp, @lib)

			Zip::ZipFile.open(@zip) { |zip_file|
				has_dir = true
				zip_file.each {|f| has_dir = has_dir && f.name.start_with?(@lib)}
				target = has_dir ? dest_dir_temp : container

				zip_file.each { |f|
					filename = f.name.force_encoding("UTF-8")
					FileUtils.mkdir_p(File.join(target, File.dirname(filename)))
					zip_file.extract(f, File.join(target, filename))
				}
			}

			# Add version id file
			version_file = File.join(container, "version-id.txt")
			File.open(version_file, "w") do |f|
				f.write(@version)
			end

			retry_mv(dest_dir_temp, dest_dir)
		rescue
			retry_rm_r(dest_dir)
			retry_rm_r(dest_dir_temp) if dest_dir_temp
			raise
		end

		@state = :done
	end

	def populate_progress_string
		if @state == :unzip
			return "(unzipping)"
		elsif @state == :done
			return "(done)"
		else
			return ""
		end
	end

	def verify; end
end

# Fetch a zip file from an given URL and unzip the file.
class URLSource < Source
	def initialize(opts, lib: nil, version: nil)
		@lib = lib
		@url = opts['url']
		@state = nil
		@progress = "0%"
		@version = version
	end

	def get(dest_dir)

		# Setup source
		@state = :setup

		# Download file at url
		bytes_total = nil
		zip_file_path = File.join(Cache.root, @lib + ".zip")
		@state = :download
		File.open(zip_file_path, "wb") do |downloaded_file|
			open(@url, "rb",
				:content_length_proc => lambda{|content_length|
					bytes_total = content_length
				},
				:progress_proc => lambda{|bytes_transferred|
					if bytes_total
						@progress = "#{sprintf('%.1f', bytes_transferred.to_f / bytes_total.to_f * 100.0)}%"
					else
						@progress = "#{bytes_transferred / 1024.0 / 1024.0} kb"
					end
				}) do |read_file|
				downloaded_file.write(read_file.read)
			end
		end

		begin
			# Unzip file
			@state = :unzip

			dest_dir_temp = Dir.mktmpdir("temp-#{File.basename(dest_dir)[0,10]}-", Cache.root)
			container = File.join(dest_dir_temp, @lib)

			Zip::ZipFile.open(zip_file_path) { |zip_file|
				has_dir = true
				zip_file.each {|f| has_dir = has_dir && f.name.start_with?(@lib)}
				target = has_dir ? dest_dir_temp : container

				zip_file.each { |f|
					filename = f.name.force_encoding("UTF-8")
					FileUtils.mkdir_p(File.join(target, File.dirname(filename)))
					zip_file.extract(f, File.join(target, filename))
				}
			}

			# Delete zip file
			FileUtils.rm(zip_file_path)

			@state = :install

			# Add version id file
			version_file = File.join(container, "version-id.txt")
			File.open(version_file, "w") do |f|
				f.write(@version)
			end

			retry_mv(dest_dir_temp, dest_dir)
		rescue
			retry_rm_r(dest_dir)
			retry_rm_r(dest_dir_temp) if dest_dir_temp
			raise
		end

		@state = :done
	end

	def populate_progress_string
		if @state == :setup
			return "(initializing)"
		elsif @state == :download
			return "(downloading #{@progress})".green
		elsif @state == :unzip
			return "(unzipping)"
		elsif @state == :install
			return "(installing)"
		elsif @state == :done
			return "(done)"
		else
			return ""
		end
	end

	def verify; end
end

class Source
	def self.from_json(source_template, package, lib: nil, version: nil)
		source_options = source_template.dup
		package.each {|k,v| source_options[k] = v unless source_options[k]}
		return S3Source.new(source_options, lib: lib, version: version) if source_options["type"] == "s3"
		return GitSource.new(source_options, lib: lib, version: version) if source_options["type"] == "git"
		return ArtifactorySource.new(source_options, lib: lib, version: version) if source_options["type"] == "artifactory"
		return URLSource.new(source_options, lib: lib, version: version) if source_options["type"] == "url"
		return ManualSource.new(source_options, lib: lib, version: version) if source_options["type"] == "manual"
		raise "unknown source type: `#{source_options["type"]}`"
	end
end

# Represents a package that has been installed
class InstalledPackage
	attr_reader :name, :lib, :version

	def initialize(name: nil, version: nil, lib: nil)
		@name = name
		@version = version
		@lib = lib
	end

	def self.from_json(name, value)
		o = InstalledPackage.new
		o.send(:init_from_installed_json, name, value)
		return o
	end

	def to_json
		return {
			"version" => @version,
			"lib" => @lib
		}
	end

	def uninstall()
		unless @version == "bad"
			lib_dir = File.join(Configuration.lib_dir, @lib)
			cache_dir = Cache.dir(@lib, @version)
			if Dir.exist?(cache_dir)
				puts "WARNING: When uninstalling `#{@lib}-#{@version}` - cache_dir already exists".bold.yellow
				retry_rm_r(cache_dir)
			end
			FileUtils.mkdir_p(cache_dir)
			begin
				retry_mv(lib_dir, cache_dir)
			rescue
				if $stdout.isatty()
					print "ERROR: Directory locked `#{lib_dir}`. Retry (Y/n): "
					answer = STDIN.gets.strip
					retry if answer=='' || answer[/^[yY]/]
				end
				retry_rm_r(cache_dir)
				raise
			end
		end
	end

	def installed?
		lib_dir = File.join(Configuration.lib_dir, @lib)
		return false unless Dir.exist?(lib_dir)
		version_file = File.join(lib_dir, "version-id.txt")
		version = "null"
		version = File.read(version_file).strip if File.exist?(version_file)
		return @version == version
	end

	def mark_as_bad_install
		@version = "bad"
	end

private

	def init_from_installed_json(name, value)
		@name = name
		@version = value["version"]
		@lib = value["lib"]
	end
end

# Represents a package that can be installed
class Package
	attr_reader :name, :package, :platforms, :lib, :version, :groups, :devenvs, :priority

	def self.from_json(name, value, source_templates)
		o = Package.new
		o.send(:init_from_json, name, value, source_templates)
		return o
	end

	def enabled_in_configuration?(conf)
		return conf.packages.include?(@package) && !(conf.platforms & @platforms).empty?
	end

	def install()
		cache_dir = Cache.dir(@lib, @version)
		@source.get(cache_dir) unless Cache.has?(@lib, @version)
		if File.exist?(File.join(Configuration.lib_dir, @lib))
			puts "WARNING: Overwriting library file #{@lib}".bold.yellow
			retry_rm_r(File.join(Configuration.lib_dir, @lib))
		end
		retry_mv(File.join(cache_dir, @lib), Configuration.lib_dir)
		retry_rm_r(cache_dir)
		return InstalledPackage.new(name: @name, version: @version, lib: @lib)
	end

	def in_cache?()
		return Cache.has?(@lib, @version)
	end

	def prepare_populate
		if @source.respond_to?(:prepare_get)
			@source.prepare_get(Cache.dir(@lib, @version)) unless in_cache?
		end
	end

	def populate
		@source.get(Cache.dir(@lib, @version)) unless in_cache?
	end

	def populate_progress_string
		@source.populate_progress_string
	end

	def verify()
		@source.verify()
	end

	def location()
		return File.join(Configuration.lib_dir, @lib).gsub("\\", "/")
	end

	def list_versions()
		return @source.list_versions()
	end

private
	def init_from_json(name, value, source_templates)
		@name = name
		@package = value["package"]
		@platforms = value["platforms"] ? value["platforms"].collect {|s| Platform.from_s(s)} : Platform.all
		@groups = (value["groups"] || [])
		@devenvs = value["devenvs"] ? value["devenvs"].collect {|s| Devenv.from_s(s)} : Devenv.all
		@lib = value["lib"]
		raise "no lib set for `#{name}" unless @lib
		@version = value["version"]
		@priority = (value["priority"] || 0)
		if value["source"]
			@source = Source.from_json(value["source"], value, lib: lib, version: version)
		else
			source_template = (value["source-template"] || "default")
			raise "no source template for `#{name}`" unless source_templates[source_template]
			@source = Source.from_json(source_templates[source_template], value, lib: lib, version: version)
		end
	end
end

class Manager < Thor
	class_option :lib_dir, :desc => "library directory"
	class_option :verbose, :desc => "enable verbose output", :type => :boolean, :aliases => %w(v)
	class_option :tmp_dir, :desc => "directory for temporary downloads"
	class_option :packages_root_dir, :desc => "overrides default parsing root directory which is current directory"

	# Uncomment to have more flexible options in spm.rb
	# class_option :num_threads, :type => :numeric, :default => 64, :desc => "use multiple threads to download from S3 servers"
	# class_option :part_size, :type => :numeric, :default => 10, :desc => "download big files using multiple small parts"

	def initialize(*args)
		super
		Configuration.verbose = options[:verbose]
		Configuration.lib_dir = options[:lib_dir] if options[:lib_dir]
		Configuration.tmp_dir = options[:tmp_dir] if options[:tmp_dir]
		Configuration.packages_root_dir = options[:packages_root_dir]

		if Configuration.lib_dir != nil and !Configuration.lib_dir.empty?
			Configuration.lib_dir = Configuration.lib_dir.gsub("\\", "/").gsub("\"", "")
		else
			puts "\nERROR: SR_LIB_DIR environment variable not set! Please set SR_LIB_DIR environment variable to library path.".bold.red
			exit 1
		end

		if Configuration.tmp_dir != nil and !Configuration.tmp_dir.empty?
			Configuration.tmp_dir = Configuration.tmp_dir.gsub("\\", "/").gsub("\"", "")
		end

		# Uncomment to have more flexible options in spm.rb
		# Configuration.num_threads = options[:num_threads]
		# Configuration.part_size = options[:part_size]
		# if Configuration.num_threads == 0
		# 	Configuration.part_size = 0 # no point using multiple parts if num_threads is zero
		# end

		if Configuration.tmp_dir.nil? || Configuration.tmp_dir.empty?
			Configuration.tmp_dir = Dir.tmpdir
		else
			unless Dir.exists?(Configuration.tmp_dir)
				FileUtils.mkdir_p(Configuration.tmp_dir)
			end
		end

		$DefaultThreadPool = ThreadPool.new(Configuration.num_threads)

		@packages = {}
		@installed = {}

		raise 'no $SR_LIB_DIR or --lib-dir parameter' unless Configuration.lib_dir
		raise 'no $SR_LIB_DIR or --lib-dir parameter' if Configuration.lib_dir.empty?

		FileUtils.mkdir_p(Configuration.lib_dir)
		FileUtils.mkdir_p(Cache.root)

		root_dir = (!Configuration.packages_root_dir.to_s.empty? && Dir.exists?(Configuration.packages_root_dir)) ? Configuration.packages_root_dir : Dir.pwd
 		Dir.chdir(root_dir) {
 			Dir.glob("**/spm-packages.sjson").each {|pf| parse_packages(pf)}
 			Dir.glob("**/*-spm-packages.sjson").each {|pf| parse_packages(pf)}
 		}

		parse_installed
	end

	desc "update", "updates all packages to latest version"
	def update()
		to_update = []
		internal_update(@installed.keys)
	end

	desc "install package(s)...", "installs the specified package(s)"
	option :all, :type => :boolean, :aliases => %w(a), :desc => "install everything"
	option :populate, :aliases => %w(o), :desc => "populate cache but do not install", :type => :boolean
	def install(*packages)
		packages = @packages.keys if options[:all]
		packages.each {|p| raise "unknown package `#{p}`" unless @packages[p]}
		m = options[:populate] ? method(:internal_populate) : method(:internal_update)
		m.call(packages)
	end

	desc "uninstall [options] package(s)...", "uninstalls the specified package(s)"
	option :all, :type => :boolean, :desc => "uninstall everything", :aliases => %w(a)
	def uninstall(*packages)
		packages += @installed.keys if options[:all]
		packages.each {|p| raise "not installed `#{p}`" unless @installed[p]}
		internal_uninstall(packages)
	end

	desc "install-group [options] group(s)...", "installs all the packages in the specified group(s)"
	option :all, :type => :boolean, :aliases => %w(a), :desc => "install everything"
	option :platforms, :aliases => %w(p), :desc => "list of platforms to install for (e.g. osx,android)"
	option :devenvs, :aliases => %w(d), :desc => "list of devenvs to install for (e.g. vc11,vc12)"
	option :populate, :aliases => %w(o), :desc => "populate cache but do not install", :type => :boolean
	def install_group(*groups)
		groups = @packages.collect {|k,v| v.groups}.flatten.uniq.sort if options[:all]
		platforms = options[:platforms] ? options[:platforms].split(',').collect {|p| Platform.from_s(p)} : Platform.all()
		devenvs = options[:devenvs] ? options[:devenvs].split(',').collect {|e| Devenv.from_s(e)} : Devenv.all()
		m = options[:populate] ? method(:internal_populate) : method(:internal_update)
		m.call(@packages.values.select {|p|
			(p.groups & groups).any? && (p.platforms & platforms).any? && (p.devenvs & devenvs).any?
		}.collect {|p| p.name})
	end

	desc "uninstall-group [options] group(s)...", "uninstalls all the packages in the specified group(s)"
	option :all, :type => :boolean, :aliases => %w(a), :desc => "uninstall everything"
	option :platforms, :aliases => %w(p), :desc => "list of platforms to uninstall for (e.g. osx,android)"
	option :devenvs, :aliases => %w(d), :desc => "list of devenvs to uninstall for (e.g. vc11,vc12)"
	def uninstall_group(*groups)
		groups = @packages.collect {|k,v| v.groups}.flatten.uniq.sort if options[:all]
		platforms = options[:platforms] ? options[:platforms].split(',').collect {|p| Platform.from_s(p)} : Platform.all()
		devenvs = options[:devenvs] ? options[:devenvs].split(',').collect {|e| Devenv.from_s(e)} : Devenv.all()
		internal_uninstall(@packages.values.select {|p|
			@installed[p.name] && (p.groups & groups).any? && (p.platforms & platforms).any? && (p.devenvs & devenvs).any?
		}.collect {|p| p.name })
	end

	desc "list", "list packages"
	def list()
		puts "*** INSTALLED PACKAGES ***"
		puts
		@installed.keys.sort.each {|k| puts k}
		puts
		puts "*** AVAILABLE UPDATES ***"
		puts
		@installed.select {|k,v| @packages[k] && (@packages[k].version != v.version || @packages[k].lib != v.lib)}.
			each{|k,v| puts "#{k} (#{v.version} -> #{@packages[k].version})"}
		puts
		puts "*** AVAILABLE PACKAGES ***"
		puts
		@packages.keys.sort.each {|k| puts "#{k}" unless @installed[k]}
	end

	desc "list-groups", "list groups"
	def list_groups()
		groups = @packages.collect {|k,v| v.groups}.flatten.uniq.sort
		full = groups.select do |g|
			@packages.values.all? {|p| @installed[p.name] || !p.groups.include?(g)}
		end
		partial = @installed.keys.collect {|k| @packages[k]}.collect {|p| p ? p.groups : []}.flatten.uniq.sort

		puts "*** FULLY INSTALLED GROUPS ***"
		puts
		full.each {|g| puts g}
		puts
		puts "*** PARTIALLY INSTALLED GROUPS ***"
		puts
		(partial - full).each {|g| puts g}
		puts
		puts "*** AVAILABLE GROUPS ***"
		puts
		(groups - full - partial).each {|g| puts g}
	end

	desc "list-versions package(s)...", "list versions available from remote source for specified package(s)"
	option :all, :type => :boolean, :aliases => %w(a), :desc => "list versions all packages"
	def list_versions(*packages)
		packages = @packages.keys if options[:all]
		packages.each do |p|
			raise "unknown package `#{p}`" unless @packages[p]
			puts "package `#{p}`"
			@packages[p].list_versions()
			puts
		end
	end

	desc "cache", "list cache content"
	def cache()
		total = 0
		Cache.entries.sort_by {|e| e.size}.each do |e|
			puts "#{MemorySize.to_human(e.size)} - #{e.name} - #{Time.to_human(e.age)} ago"
			total += e.size
		end
		puts
		puts "#{MemorySize.to_human(total)} TOTAL"
	end

	desc "prune", "prune old items from cache"
	option :size, :aliases => %w(s), :desc => "size to trim the cache to (e.g. 10gb)"
	option :age, :aliases => %w(a), :desc => "age to trim the cache to (e.g. 30d)"
	def prune()
		if options[:size]
			Cache.prune(size: MemorySize.from_human(options[:size]))
		elsif options[:age]
			Cache.prune(age: Time.from_human(options[:age]))
		else
			Cache.prune
		end
	end

	desc "verify", "verify that the package lists are correct"
	def verify()
		@installed.keys.each do |k|
			puts "`#{k}` is installed but is not mentioned in the package lists" unless @packages[k]
		end
		@packages.values.each do |p| p.verify end
	end

	desc "locate [options] package(s)...", "locate the specified package(s)"
	option :all, :type => :boolean, :aliases => %w(a), :desc => "locate all packages"
	option :groups, :aliases => %w(g), :desc => "list of groups to search for (e.g. engine,editor)"
	option :platforms, :aliases => %w(p), :desc => "list of platforms to search for (e.g. osx,android)"
	option :devenvs, :aliases => %w(d), :desc => "list of devenvs to search for (e.g. vc11,vc12)"
	def locate(*packages)
		packages = @packages.keys if options[:all]
		groups = options[:groups] ? options[:groups].split(',') : @packages.collect {|k,v| v.groups}.flatten.uniq.sort
		platforms = options[:platforms] ? options[:platforms].split(',').collect {|p| Platform.from_s(p)} : Platform.all()
		devenvs = options[:devenvs] ? options[:devenvs].split(',').collect {|e| Devenv.from_s(e)} : Devenv.all()
		packages.each{|p|
			matching_packages = @packages.select{|k,v| v.name.include?(p) && (v.groups & groups).any? && (v.platforms & platforms).any? && (v.devenvs & devenvs).any?}
			matching_packages.each{|k,v|
				puts "#{v.name} = #{v.location()}" if @installed[v.name]
			}
		}
	end

	desc "clean [options] untracked package(s)...", "remove untracked directories and package(s) from the library (and optionally cache)"
	option :cache, :type => :boolean, :aliases => %w(c), :desc => "also clean untracked cache entries"
	def clean()
		@installed.keys.each do |k|
			p = @installed[k]
			unless @packages[k]
				puts "Deleting untracked package `#{p.lib}`..."
				lib_dir = File.join(Configuration.lib_dir, p.lib)
				cache_dir = Cache.dir(p.lib, p.version)
				FileUtils.rm_rf(lib_dir) if Dir.exists?(lib_dir)
				FileUtils.rm_rf(cache_dir) if Dir.exists?(cache_dir)
				@installed.delete(p.name)
			end
			if p.version == "bad"
				puts "Removing bad package entry `#{p.lib}`..."
				@installed.delete(p.name)
			end
		end
		Dir.entries(Configuration.lib_dir).each do |lib|
			full_path = File.join(Configuration.lib_dir, lib)
			next if lib[0,1] == '.' # skip . and ..
			next if full_path == Cache.root # skip cache directory
			next if !File.directory?(full_path) # skip files
			next if !@packages.values.select{|p| p.lib == lib}.empty? # skip if found in package list
			puts "Deleting untracked directory `#{lib}`..."
			FileUtils.rm_rf(full_path) if Dir.exists?(full_path)
			@installed.delete(@installed[lib])
		end
		save_installed
		if options[:cache]
			Cache.each do |entry|
				lib = entry.name.rpartition("-")[0]
				if @packages.select{|k,v| v.lib == lib}.empty?
					puts "Deleting untracked package cache `#{lib}`..."
					FileUtils.rm_rf(entry.path) if Dir.exists?(entry.path)
				end
			end
		end
	end

private
	def parse_packages(file)
		return unless File.exist?(file)
		sjson = Sjson.load(file)
		source_templates = {}
		sjson["source-templates"].each do |key, value|
			source_templates[key] = value
		end
		sjson["packages"].each do |key, value|
			p = Package.from_json(key, value, source_templates)
			next if @packages[key] && @packages[key].priority > p.priority
			@packages[key] = p
		end
	end

	def parse_installed
		file = Configuration.installed_file
		if File.exist?(file)
			sjson = Sjson.load(file)
			sjson.each do |key, value|
				p = InstalledPackage.from_json(key, value)
				unless p.installed?
					puts "WARNING: #{p.lib}-#{p.version} specified as installed, but not found".bold.yellow
					p.mark_as_bad_install()
				end
				@installed[key] = p
			end
		end

		# Auto-add files that have been installed through other means (i.e. through update-libraries)
		Dir.entries(Configuration.lib_dir).each do |lib|
			next if lib[0,1] == '.'
			next if @installed.values.any? {|p| p.lib == lib}

			ps = @packages.values.select {|p| p.lib == lib}
			next if ps.size != 1
			p = ps[0]

			lib_dir = File.join(Configuration.lib_dir, lib)
			version_file = File.join(lib_dir, "version-id.txt")
			version = "null"
			version = File.read(version_file).strip if File.exist?(version_file)
			installed = InstalledPackage.new(name: p.name, version: version, lib: lib)
			next if @installed[p.name]
			puts "WARNING: #{p.lib}-#{p.version} found, but not specified as installed".bold.yellow
			@installed[p.name] = installed
		end
	end

	def save_installed
		file = Configuration.installed_file
		sjson = {}
		@installed.each do |key, pv|
			sjson[key] = pv.to_json
		end
		FileUtils.mkdir_p(File.dirname(file))
		Sjson.save(sjson, file)
	end

	def internal_update(keys)
		internal_populate(keys)
		keys.each do |k|
			if !@packages[k]
				STDERR.puts("ERROR: Don't know how to update `#{k}` -- it may have been removed".bold.red)
				next
			elsif !@packages[k].version
				STDERR.puts("ERROR: Don't know how to update `#{k}` -- no version specified".bold.red)
				next
			end

			if !@installed[k] || @packages[k].version != @installed[k].version || @packages[k].lib != @installed[k].lib
				do_uninstall(@installed[k]) if @installed[k]
				do_install(@packages[k])
			end
		end
	end

	def internal_populate(keys)
		topop = keys.select do |k|
			if !@packages[k]
				STDERR.puts("ERROR: Don't know how to populate `#{k}` -- it may have been removed".bold.red)
				false
			elsif !@packages[k].version
				STDERR.puts("ERROR: Don't know how to populate `#{k}` -- no version specified".bold.red)
				false
			else
				(!@installed[k] || @installed[k].version != @packages[k].version || @packages[k].lib != @installed[k].lib) && !@packages[k].in_cache?
			end
		end
		topop.each do |k|
			@packages[k].prepare_populate()
		end
		threads = []
		topop.each_with_index do |k,i|
			t = $DefaultThreadPool.add {@packages[k].populate()}
			threads[i] = t
		end
		width = 70
		while true
			any_alive = false
			topop.each_with_index do |k,i|
				if $stdout.isatty()
					progress = @packages[k].populate_progress_string
					s = ""
					if progress["(done)"]
						s = "#{i+1}/#{topop.size}: #{k} #{progress}".bold.green
					elsif progress["(unzipping)"]
						s = "#{i+1}/#{topop.size}: #{k} #{progress}".bold.yellow
					elsif progress["(error"]
						s = "#{i+1}/#{topop.size}: #{k} #{progress}".bold.red
					else
						s = "#{i+1}/#{topop.size}: #{k.bold.gray} #{progress}"
					end
					width = [width, s.length].max
					printf("%-*s\n", width, s)
					any_alive ||= threads[i].alive?
				end
			end
			break unless any_alive
			sleep(0.5)
			if $stdout.isatty()
				topop.each_with_index do |k,i|
					print "\r".cursor_up
				end
			end
		end
	end

	def internal_uninstall(keys)
		keys.each {|k| do_uninstall(@installed[k])}
	end

	def do_install(p)
		@installed[p.name] = p.install
		save_installed
	end

	def do_uninstall(p)
		p.uninstall
		@installed.delete(p.name)
		save_installed
	end
end

def test()
	script = <<EOS
cache
list
list_groups
verify

uninstall-group luajit --platforms ios,android
prune --size=0gb
install-group luajit --platforms ios,android
install luajit-windows
uninstall luajit-windows
install luajit-windows
uninstall luajit-android
update

uninstall --all
prune --size=0gb
install --all
EOS
	script.each_line do |line|
		line = line.strip
		next if line.empty?
		puts("-"*60)
		puts("> spm #{line}")
		puts
		Manager.start(line.split)
	end
end

begin
	if ARGV[0] == '--test'
		test()
	else
		Manager.start(ARGV)
	end
rescue RuntimeError => e
	$stderr.puts "ERROR: #{e}".bold.red
	if Configuration.verbose then
		$stderr.puts
		$stderr.puts e.inspect
		$stderr.puts
		$stderr.puts e.backtrace
	end
	exit(-1)
end
