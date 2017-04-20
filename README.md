Welcome to Stingray Plugin
==========================

This is the main source code repository to build new Stingray plugins.

Stingray plugins can include the following components and this startup repo contains minimal examples for all of them.

- [x] A plugin descriptor (.plugin)
- [x] Various engine and editor components, such as:
	- [x] Engine runtime resources (i.e. `units`, `entity`, etc.)
	- [x] Engine native plugin extension (C/C++ dll)
		- [x] The editor loads and unloads these extensions at runtime using `runtime_libraries` extensions.
	- [x] Editor native plugin extension(s) (C/C++ dll)
	- [x] Editor scripts/modules
	- [x] Plugin extensions
- [x] Contain a sample project.
- [x] Build system included.
    - [x] `make.rb` is used to interface the Stingray plugin build system.
    - [x] `spm.rb` is used to fetch and install build packages, plugin sdk, and external libraries.
	- [x] `cmake` is used to generate and compile the native plugin extension.

## Quick start for new customers

The following steps are a shorthand guide to getting started, aimed at a relatively knowledgeable developer. It will help you create your first custom Stingray plugin, using a preset configuration.

For more detail on all the topics below, as well as instructions for building with support for other target platforms, please see the Stingray Developer Help (link [below](#more-help)).

### Step 1. Install prerequisites

-   Git client: <https://git-scm.com/>
-   Ruby 2.0 or later: <http://rubyinstaller.org>.
    -   Rubygems SSL fix (if needed): <http://guides.rubygems.org/ssl-certificate-update>
-   Visual Studio 2015 with Update 3 & Patch KB3165756: <https://www.visualstudio.com/downloads/#visual-studio-professional-2015-with-update-3>

### Step 2. Get a local copy of the source

You will need to clone a local copy of this repository using the Git command line (explanation as to why below).

Note that this repository only contains source code for platforms with public development libraries: e.g. Windows, iOS, and Android. If that is all you need access to then you can sinmply do:

```
git clone https://github.com/AutodeskGames/stingray-plugin.git <name of your plugin>
```

And you should have everything you need.

### Step 3. Set up your library directory

Every revision of the Stingray source code depends on several libraries that are not stored in Git. Instead, our build tools copy these libraries to your computer from a storage location on the Internet.

Before you run a build, you have to specify a location on your computer where you want the build to store and access these libraries.

-   Create an environment variable named `SR_LIB_DIR`. Set its value to an empty directory on your computer where you want the libraries to be copied. Make sure that you have at least 2 GB of space.

### Step 4. Build

Run the `make.rb` script in the root directory of this repository.

~~~
> ruby make.rb
~~~

This command:

-   automatically updates your library directory with the correct versions of all libraries needed for your build.
-   generates and builds Visual Studio solutions for the Stingray engine and editing tools.
-   offers several parameters that you can use to control what gets built and how. Call it with the `--help` command-line parameter to get a list of all available parameters.

>   **NOTE:** The first time you run this script, it will take some time to complete all the required downloads. Subsequent builds based on the same revision will not need to download anything. Subsequent builds based on future revisions will only need to download the libraries that have changed since the version you last downloaded.

#### Build results

By default, the script writes all compiled output to the `plugin/binaries` directory under the root directory in which you cloned the Stingray source code.

##### Directory structure

-   `build`: Various build outputs (i.e. CMake generated solutions)
-   `cmake`: CMake helper scripts downloaded by `spm`
-   `editor`: Proposed folder to put editor native extension source code. (i.e. C/C++ plugin sources)
-   `engine`: Proposed folder to put engine native extension source code. (i.e. C/C++ plugin sources)
-   `plugin`: Other plugin sources (plugin descriptor, editor extension, compiled editor and engine extenions, etc.)
-   `stingray_sdk`: Stingray editor and engine C/C++ header based plugin SDK downloaded by `spm`.
-   `tools`: Various build tools downloaded by `spm`.
-   `make.rb`: Build interface script. Execute `make.rb --help` to see all the options.

Once you've successfully built the Stingray plugin, you can zip the `plugin` folder and **distribute** your plugin. For help getting started with with the Stingray SDK, see the tutorial videos and topics in the [main Stingray SDK Help](http://help.autodesk.com/view/Stingray/ENU/?guid=__sdk_help_introduction_html).

##### Plugin structure

-   `stingray-example.plugin`: Initial plugin descriptor. It is strongly recommended to rename the file name of this file.
-   `sample_project/`: Example project that demonstrate how your plugin works.

## More help

Please see the [Stingray Developer Help](http://www.autodesk.com/stingray-help/?contextId=DEVELOPER_HOME) for more details on all these topics and more.

## Stay in touch!

Your feedback is essential in making this product a success. Please help us by sharing your opinions about all the things we're doing wrong in the [Stingray user forum](http://www.autodesk.com/stingray-forums) or in the user forums on the [Autodesk beta portal](http://beta.autodesk.com). Autodesk engineers and designers are actively engaged in the forum threads, so you can make your voice heard loud and clear and get help straight from the source.
