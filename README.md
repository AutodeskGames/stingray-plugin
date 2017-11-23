Welcome to the Autodesk Interactive 3.0 plug-in startup repo
============================================================

This repository provides an easy way to get started creating new plug-ins for [Autodesk Interactive 3.0](http://www.autodesk.com/products/stingray/overview).

You'll find a sample plug-in that is already set up with some basic content, and a framework that you can build on:

- A sample *.stingray_plugin* descriptor file, which tells Autodesk Interactive what your plug-in is and what it does.
- Various components that extend the Autodesk Interactive environment:
	- Content resources that your plug-in makes available to all the Autodesk Interactive projects you open in the editor.
	- C/C++ code that extends the runtime engine with new functionality.
	- C/C++ code that extends the editor's JavaScript environment with hooks to functions implemented in native code.
	- JavaScript modules that extend the Autodesk Interactive editor with new panels, menus, and commands.
	- A Autodesk Interactive content project that your plug-in users will see in the Templates tab of the **Project Manager**.
- Everything you need to build C/C++ plug-in code into *.dll* files ready for the engine and editor to load:
	- `make.rb` launches the plug-in build system.
	- `spm.rb` fetches and installs build packages and external libraries. It's called internally by `make.rb`, but you can also use it on its own as well if your plug-in has other dependencies that you want to download automatically.
	- `cmake` generates and compiles Visual Studio solutions for the native plug-in extensions.

For more information about plug-ins, how they work, and what you can do with them, see the [Autodesk Interactive SDK Help](http://help.autodesk.com/view/Stingray/ENU/?contextId=SDK_HOME).

## Step 1. Install prerequisites

You'll need [a Git client](https://git-scm.com/) to clone the contents of this repo to your computer.

If you want your plug-in to include C/C++ libraries that extend the editor or the engine, you'll also need:

-   [Ruby 2.0 or later](http://rubyinstaller.org).

-   [Node 6.11.2 LTS or later](https://nodejs.org/en/).

-   [Visual Studio 2015 with Update 3 & Patch KB3165756](https://www.visualstudio.com/downloads/#visual-studio-professional-2015-with-update-3).

## Step 2. Get a local copy of the source

You will need to get the contents of this repo to your computer so that you can work with it.

**IMPORTANT: You need to get the version of this repo that corresponds to the version of Autodesk Interactive that you will use your plug-in with!** This is especially true if your plug-in will use a C/C++ *.dll* to extend the engine or editor, since you'll need compatible versions of the Autodesk Interactive SDK header files to compile your plug-in against.

-	The `master` branch is always in sync with the latest released version of Autodesk Interactive. This is the default branch you'll get if you clone this repo. Use it if you want your plug-in to work with the current version of Autodesk Interactive.

-	If you want to set up your plug-in to work with a previous version of Autodesk Interactive, you can get a version of this repo to match by checking out a release tag, or downloading the source from the **Releases** tab on GitHub.

If you have access to the source code for Autodesk Interactive:

-	If you're using the `develop` branch of the Autodesk Interactive engine repo to pick up the latest and greatest changes and bug fixes, use the `develop` branch of this repo to build your plug-in.

-	If you want your plug-in to support an upcoming release that isn't yet publicly available but that has its own `release` branch in the Autodesk Interactive engine repository, use the matching `release` branch of this repo to keep in sync.

## Step 3. Set up your library directory

Every revision of the plug-in source code depends on libraries and dependencies that are not stored in Git. Instead, our build tools copy these libraries to your computer from a storage location on the Internet.

Before you run a build, you have to specify a location on your computer where you want the build to store and access these libraries.

-   Create an environment variable named `SR_LIB_DIR`. Set its value to any empty directory on your computer where you want the libraries to be copied.

## Step 4. Build

If you're including a C/C++ plug-in for the engine or the editor, build it by running the `make.rb` script in the root directory of this repository.

~~~
> ruby make.rb
~~~

This command:

-   automatically updates your library directory with the correct versions of all libraries needed for your build.
-   generates and builds Visual Studio solutions for the Autodesk Interactive engine and editing tools.
-   offers several parameters that you can use to control what gets built and how. Call it with the `--help` command-line parameter to get a list of all available parameters.

>	**NOTE:** If you get an error about certificate verification, you may need to [install this SSL fix for RubyGems](http://guides.rubygems.org/ssl-certificate-update)

### Build results

By default, the script writes all compiled *.dll* files to the `plugin/binaries` directory under the root directory in which you cloned the Autodesk Interactive source code.

You can also use the Visual Studio solutions generated in the `build/engine` and `build/editor` folders to work with the source code and rebuild your libraries.

## Tutorial!

See [the wiki](https://github.com/AutodeskGames/stingray-plugin/wiki/How-to-create-a-cool-plugin) for a tutorial that walks you step-by-step through the process of making a plug-in that extends both the engine and the editor.

## Directory structure

-   `build`: Various build outputs (i.e. CMake generated solutions)
-   `cmake`: CMake helper scripts downloaded by `spm`
-   `editor`: A folder where you can put C/C++ code that extends the editor.
-   `engine`: A folder where you can put C/C++ code that extends the runtime engine.
-   `plugin`: Other plugin sources (plugin descriptor, editor extension, compiled editor and engine extenions, etc.)
-   `stingray_sdk`: Autodesk Interactive editor and engine C/C++ header based plugin SDK downloaded by `spm`.
-   `tools`: Various build tools downloaded by `spm`.
-   `make.rb`: Build interface script. Execute `make.rb --help` to see all the options.
-	`docs`:	Ruby script and template to automatically generate documentation for your plugin using Adoc.

Once you've successfully built the Autodesk Interactive plugin, you can zip the `plugin` folder and **distribute** your plugin. For help getting started with with the Autodesk Interactive SDK, see the tutorial videos and topics in the [main Autodesk Interactive SDK Help](http://help.autodesk.com/view/Stingray/ENU/?guid=__sdk_help_introduction_html).

## Plugin structure

-   `stingray-example.plugin`: Initial plugin descriptor. It is strongly recommended to rename the file name of this file.
-   `sample_project/`: Example project that demonstrate how your plugin works.

## Documentation

*Note: This currently requires Stingray source access due to the dependency on Adoc.*

In the [`./docs`](./docs) directory there's a ruby script that will generate documentation for your plugin using Adoc. Refer to the comments in the script and the other documentation example files in the `./docs` dir, as well as the Stingray repository docs readme to learn how to annotate your code comments for Adoc parsing.

You do not need to install the `ixg-doc-tools` to generate your plugin docs. Just define the `%SR_SOURCE_DIR%` environment variable (e.g. `c:\dev\stingray`) or modify the line in [`make_plugin_docs.rb`](./docs/make_plugin_docs.rb). Then run the script and refer to the output directory in the console to view the generated documentation.

Usage:
```
ruby docs/make_plugin_docs.rb
```

## More help

Please see the [Autodesk Interactive SDK Help](http://help.autodesk.com/view/Stingray/ENU/?contextId=SDK_HOME) for more details on working with plug-ins, API reference documentation, and more.

## Stay in touch!

Your feedback is essential in making this product a success. Please help us by sharing your opinions about all the things we're doing wrong in the [Autodesk Interactive user forum](http://www.autodesk.com/stingray-forums) or in the user forums on the [Autodesk beta portal](http://beta.autodesk.com). Autodesk engineers and designers are actively engaged in the forum threads, so you can make your voice heard loud and clear and get help straight from the source.
