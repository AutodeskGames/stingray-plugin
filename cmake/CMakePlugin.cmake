cmake_minimum_required(VERSION 3.8)

include(CMakeSettings)

set(CMAKE_C_FLAGS)
set(CMAKE_CXX_FLAGS)
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")

# Global cache entry filled with file paths to any plugins built as dynamic
# libraries for platforms that need to bundle them (eg: iOS)
set(PLUGIN_RESOURCE_FILES "" CACHE INTERNAL "" FORCE)

# Setup platforms
if( PLATFORM_WINDOWS )
	add_compile_options(-DWINDOWSPC)
elseif( PLATFORM_OSX )
	add_compile_options(-DMACOSX)
elseif( PLATFORM_IOS )
	add_compile_options(-DIOS)
	if ( ENGINE_USE_GL )
		add_compile_options(-DUSE_IOS_GLES3 -DUSE_GL_RENDER_BUFFER)
	else()
		add_compile_options(-DUSE_IOS_METAL)
	endif()
elseif( PLATFORM_ANDROID )
	add_compile_options(-DANDROID -DCORELIB=1 -DPXD_DISABLE_PPU=1 -DLINUX)
	if( ENGINE_ANDROID_GLES3 )
		add_compile_options(-DUSE_ANDROID_GLES3)
	endif()
	if( ENGINE_ANDROID_GLES3_GLSL100 )
		add_compile_options(-DUSE_ANDROID_GLES3_GLSL100)
	endif()
	if( ENGINE_ANDROID_GL4 )
		add_compile_options(-DUSE_ANDROID_GL4)
	endif()
elseif( PLATFORM_XBOXONE )
	if( NOT (EXISTS "${PROJECT_SOURCE_DIR}/platforms/xb1" AND IS_DIRECTORY "${PROJECT_SOURCE_DIR}/platforms/xb1") )
		message(FATAL_ERROR "Could not find XBoxOne engine source directory, cannot continue.")
	endif()
	add_compile_options(-DXBOXONE $<$<NOT:$<CONFIG:RELEASE>>:-DUSE_PIX>)
elseif( PLATFORM_PS4 )
	if( NOT (EXISTS "${PROJECT_SOURCE_DIR}/platforms/ps4" AND IS_DIRECTORY "${PROJECT_SOURCE_DIR}/platforms/ps4") )
		message(FATAL_ERROR "Could not find PlayStation4 engine source directory, cannot continue.")
	endif()
	add_definitions(-DPS4)	# Patch for PS4: Scaleform use a namespace named 'PS4', and it conflicts with the define 'PS4'. Using add_definitions allow us to remove it later.
	add_compile_options(-D__ORBIS__ -DX64 -D__SSE3__)
elseif( PLATFORM_WEB )
	add_compile_options(-DWEB -DSINGLE_THREAD)
	if( ENGINE_USE_WEB_SIMD )
		add_compile_options(-DUSE_WEB_SIMD)
	endif()
elseif( PLATFORM_UWP )
	add_compile_options(-DUWP -DWINAPI_PARTITION_APP=1)
	if( ENGINE_USE_HOLOLENS_PLUGIN )
		add_compile_options(-DHOLOLENS)
	endif()
elseif( PLATFORM_LINUX )
	add_compile_options(-DLINUXPC)
endif()

# Define standard configurations
if( CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_CONFIGURATION_TYPES MATCHES "Debug;Dev;Release" )
	list(APPEND Configs Debug Dev Release)
	set(CMAKE_CONFIGURATION_TYPES ${Configs} CACHE STRING "List of supported configurations." FORCE)
	set(CMAKE_INSTALL_PREFIX $ENV{SR_BIN_DIR} CACHE STRING "Default installation directory." FORCE)
	message(FATAL_ERROR "Default configuration was reset, please re-run CMake.")
endif()

# Initialize the development configuration using release configuration
set(CMAKE_C_FLAGS_DEV "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEV "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_STATIC_LINKER_FLAGS_DEV "${CMAKE_STATIC_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS_DEV "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
set(CMAKE_MODULE_LINKER_FLAGS_DEV "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}")
set(CMAKE_EXE_LINKER_FLAGS_DEV "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

# Get the current working branch and latest commit hash and generate build identifier header file
determine_build_revision("${PROJECT_SOURCE_DIR}" ENGINE_BUILD_IDENTIFIER)
if( ENGINE_BUILD_IDENTIFIER )
	execute_process(COMMAND git rev-parse --abbrev-ref HEAD WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} OUTPUT_VARIABLE ENGINE_BUILD_BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_VARIABLE GIT_ERROR)
	    if( "${GIT_ERROR}" STRGREATER "")
			    message(WARNING "The following git command: >> git rev-parse --abbrev-ref HEAD (get current git branch) << could not be executed, because no .git folder was found.")
	    endif()
endif()
#configure_file("${PROJECT_SOURCE_DIR}/build_identifier.h.in" "${PROJECT_BINARY_DIR}/build_identifier.h")

# Compute the resource version offset based on product version
math(EXPR BRANCH_RESOURCE_VERSION_OFFSET "(${PRODUCT_VERSION_MAJOR}*10000 + ${PRODUCT_VERSION_MINOR}*100 + ${PRODUCT_VERSION_REVISION}) * 1000")
#configure_file("${PROJECT_SOURCE_DIR}/resource_version.h.in" "${PROJECT_BINARY_DIR}/resource_version.h")

# Generate Emscripten config file if targeting platform Web
if( PLATFORM_WEB AND NOT "${EMSCRIPTEN_CONFIG}" STREQUAL "" )
	configure_file("${PROJECT_SOURCE_DIR}/main/web/emscripten.in" "${EMSCRIPTEN_CONFIG}" @ONLY)
	configure_file("${PROJECT_SOURCE_DIR}/main/web/emscripten_sanity.in" "${EMSCRIPTEN_CONFIG_SANITY}" @ONLY)
	# Prevent Emscripten from believing we changed the config: sanity timestamp must be greater than config timestamp
	execute_process(COMMAND ${CMAKE_COMMAND} -E touch "${EMSCRIPTEN_CONFIG_SANITY}")
endif()

# Allow subfolders in solution file
if ( ENGINE_USE_SOLUTION_FOLDERS )
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# Set global defines
add_compile_options(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
add_compile_options($<$<CONFIG:DEBUG>:-D_SECURE_SCL_THROWS=0> $<$<CONFIG:DEBUG>:-D_SILENCE_DEPRECATION_OF_SECURE_SCL_THROWS>)
add_compile_options(-D_HAS_ITERATOR_DEBUGGING=$<CONFIG:DEBUG> -D_SECURE_SCL=$<CONFIG:DEBUG>)
if( NOT PLATFORM_XBOXONE )
	add_compile_options(-D_HAS_EXCEPTIONS=0)
endif()

add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DDEVELOPMENT>)
add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DUNIT_TESTS>)
add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DUSE_CALLSTACK>)

add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DHAS_PROFILER>)
add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DHAS_LOADING_PROFILER>)
if( NOT PLATFORM_WEB)
	add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DHAS_CONSOLE_SERVER>)
endif()

# Define platform architecture
if( PLATFORM_WINDOWS OR PLATFORM_OSX OR PLATFORM_LINUX OR PLATFORM_XBOXONE OR PLATFORM_PS4 OR PLATFORM_WEB OR PLATFORM_UWP )
	add_compile_options(-DPLATFORM_ARCH_X86)
elseif( PLATFORM_IOS OR PLATFORM_ANDROID )
	add_compile_options(-DPLATFORM_ARCH_ARM)
else()
	message(FATAL_ERROR "Unknown platform architecture!")
endif()

# Define 32 versus 64 bit architecture
if( PLATFORM_64BIT )
	add_compile_options(-DPLATFORM_64BIT)
else()
	add_compile_options(-DPLATFORM_32BIT)
endif()

if(NOT BUILD_SHARED_LIBS)
	add_compile_options(-DSTATIC_PLUGIN_LINKING)
endif()

# Define if platform can compile game data
if( ENGINE_CAN_COMPILE )
	add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DCAN_COMPILE>)
	add_compile_options($<$<NOT:$<CONFIG:RELEASE>>:-DMOJOSHADER_NO_VERSION_INCLUDE>)
endif()

# Setup global per-platform compiler/linker options
if( PLATFORM_WINDOWS OR PLATFORM_XBOXONE OR PLATFORM_UWP )
	# Debug information
	if( ENGINE_USE_DEBUG_INFO )
		add_compile_options(/Zi)
	else()
		add_compile_options($<$<CONFIG:DEBUG>:/Zi>)
	endif()

	# Enable full optimization in dev/release
	add_compile_options($<$<CONFIG:DEBUG>:/Od> $<$<NOT:$<CONFIG:DEBUG>>:/Ox>)

	# Inline function expansion
	add_compile_options($<$<CONFIG:DEBUG>:/Ob0> $<$<NOT:$<CONFIG:DEBUG>>:/Ob2>)

	# Enable intrinsic functions in dev/release
	add_compile_options($<$<NOT:$<CONFIG:DEBUG>>:/Oi>)

	# Favor fast code
	add_compile_options(/Ot)

	# Enable fiber-safe optimizations in dev/release
	add_compile_options($<$<NOT:$<CONFIG:DEBUG>>:/GT>)

	# Enable string pooling
	add_compile_options(/GF)

	# Disable C++ exceptions
	# PLUGIN CUSTOM CHANGES
	if (NOT EDITOR_PLUGIN)
		replace_compile_flags("/EHsc" "")
	endif()

	# Select static/dynamic runtime library
	if( PLATFORM_WINDOWS )
		add_compile_options($<$<CONFIG:DEBUG>:/MTd> $<$<NOT:$<CONFIG:DEBUG>>:/MT>)
	elseif( PLATFORM_XBOXONE OR PLATFORM_UWP )
		add_compile_options($<$<CONFIG:DEBUG>:/MDd> $<$<NOT:$<CONFIG:DEBUG>>:/MD>)
	endif()

	# Use security checks only in debug
	if( PLATFORM_UWP )
		add_compile_options($<$<CONFIG:DEBUG>:/sdl> $<$<NOT:$<CONFIG:DEBUG>>:/sdl->)
	else()
		add_compile_options($<$<CONFIG:DEBUG>:/GS> $<$<NOT:$<CONFIG:DEBUG>>:/GS->)
	endif()

	# Enable function-level linking
	add_compile_options(/Gy)

	# Enable SIMD
	if( PLATFORM_WINDOWS )
		if( PLATFORM_64BIT )
			if( ENGINE_USE_AVX )
				add_compile_options(/arch:AVX -DAVX)
			endif()
		else()
			add_compile_options(/arch:SSE2)
		endif()
	endif()

	# Use fast floating point model
	add_compile_options(/fp:fast)

	# Disable run-time type information (RTTI)
	replace_compile_flags("/GR" "/GR-")

	# Set warning level 3
	add_compile_options(/W3)

	# Disable specific warnings
	add_compile_options(/wd4351 /wd4005)

	# Disable specific warnings for MSVC14 and above
	if( (PLATFORM_WINDOWS OR PLATFORM_UWP) AND (NOT MSVC_VERSION LESS 1900) )
		add_compile_options(/wd4838 /wd4312 /wd4477 /wd4244 /wd4091 /wd4311 /wd4302 /wd4476 /wd4474)
		add_compile_options(/wd4309)	# truncation of constant value
	endif()

	if( PLATFORM_XBOXONE AND (NOT MSVC_VERSION LESS 1900) )
		add_compile_options(/wd4577 /wd4838 /wd4312)
	endif()

	# Force specific warnings as errors
	add_compile_options(/we4101)

	# Treat all other warnings as errors
	add_compile_options(/WX)

	# Disable specific link libraries
	if( PLATFORM_WINDOWS )
		add_linker_flags(/NODEFAULTLIB:"MSVCRT.lib")
	endif()

	# Disable specific linker warnings

	# This object file does not define any previously undefined public symbols,
	# so it will not be used by any link operation that consumes this library
	add_linker_flags("/ignore:4221")

	# Missing PDB files. We get this warning for freetype and zlib used by scaleform.
	#
	# Unfortunately, this linker warning cannot be ignored even though it is mostly
	# harmless and will occur frequently for third-party libraries. See
	#
	#     http://www.geoffchappell.com/studies/msvc/link/link/options/ignore.htm
	#
	# To be able to ignore this warning, you need to patch link.exe. We have a tool
	# for that:
	#
	#     tools/visual_studio_plugins/patch_linker.rb
	#
	add_linker_flags("/ignore:4099")

	# In debug builds we get this warning because we link with some non-debug libraries
	# (for performance reasons). It is harmless, so we ignore it.
	add_linker_flags("/ignore:4098")

	if( PLATFORM_UWP )
		add_linker_flags(/IGNORE:4264)
	endif()

	# Debug information linker flags
	if( ENGINE_USE_DEBUG_INFO )
		add_exe_linker_flags(/DEBUG)
		add_exe_linker_flags(/MAP)
	else()
		add_exe_linker_flags(/MAP debug)
	endif()

	# Disable incremental linking
	replace_linker_flags("/INCREMENTAL" "/INCREMENTAL:NO" debug)
	if( PLATFORM_UWP )
		add_exe_linker_flags(/INCREMENTAL:NO)
	endif()

	# Enable multi-processor compilation for Visual Studio 2012 and above
	if( MSVC_VERSION GREATER 1600 OR PLATFORM_XBOXONE )
		add_compile_options(/MP)
	endif()

	# Platform specific options
	if( PLATFORM_XBOXONE )
		add_compile_options(/ZW)			# Consume Windows Runtime
		add_compile_options(/wd4530)		# C++ exception handler used, but unwind semantics are not enabled
		add_linker_flags("/ignore:4264")	# archiving object file compiled with /ZW into a static library
	elseif( PLATFORM_UWP )
		add_compile_options(/ZW)			# Consume Windows Runtime
		add_compile_options(/EHsc)			# C++ exceptions
	endif()

	# Clean-up linker flags case since VS IDE doesn't recognize them properly
	replace_linker_flags("/debug" "/DEBUG" debug)
	replace_linker_flags("/machine:x64" "/MACHINE:X64")

elseif( PLATFORM_ANDROID )
	# Debug information
	if( ENGINE_USE_DEBUG_INFO )
		add_compile_options(-g)
	else()
		add_compile_options($<$<CONFIG:DEBUG>:-g>)
	endif()

	# Optimizations
	add_compile_options($<$<CONFIG:DEBUG>:-O0> $<$<NOT:$<CONFIG:DEBUG>>:-O3>)

	# Set architecture deployment target
	add_compile_options(-march=armv7-a)

	# Use soft-float calling convention
	add_compile_options(-mfloat-abi=softfp)

	# Set the FPU mode to use NEON
	add_compile_options(-mfpu=neon)

	# Enable automatic vectorization
	add_compile_options(-ftree-vectorize)

	# Improve locality of reference in the instruction space optimization
	add_compile_options($<$<NOT:$<CONFIG:DEBUG>>:-ffunction-sections>)

	# Disable strict aliasing
	add_compile_options(-fno-strict-aliasing)

	# Disable short enums
	add_compile_options(-fno-short-enums)

	# Disable specific warnings
	add_compile_options(-Wno-logical-op-parentheses -Wno-unknown-attributes)

	# Treat all other warnings as errors
	add_compile_options(-Werror)

elseif( PLATFORM_IOS OR PLATFORM_OSX )
	# Debug information
	if( ENGINE_USE_DEBUG_INFO )
		add_compile_options(-g)
	else()
		add_compile_options($<$<CONFIG:DEBUG>:-g>)
	endif()

	# Enable full optimization in dev/release
	add_compile_options($<$<CONFIG:DEBUG>:-O0> $<$<NOT:$<CONFIG:DEBUG>>:-O3>)

	# Use pipes rather than temporary files for communication between the various stages of compilation
	add_compile_options(-pipe)

	# Adds support for multithreading with the pthreads library
	add_compile_options(-pthread)

	# Use fast floating point model
	add_compile_options(-ffast-math)

	# Disable run-time type information (RTTI)
	add_compile_options(-fno-rtti)

	# Disable specific warnings
	add_compile_options(-Wno-parentheses -Wno-reorder -Wno-missing-braces -Wno-unused-private-field)
	if( ${XCODE_VERSION} VERSION_GREATER_EQUAL 8.3 )
		add_compile_options(-Wno-nonportable-include-path -Wno-null-dereference)
	endif()

	# Treat all other warnings as errors
	add_compile_options(-Werror)

	# Enable C++11 language, but only for c++ files
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

elseif( PLATFORM_PS4 )
	# Debug information
	if( ENGINE_USE_DEBUG_INFO )
		add_compile_options(-g)
		add_exe_linker_flags("-Wl,-Map=$(OutDir)$(TargetName).pdb")
	else()
		add_compile_options($<$<CONFIG:DEBUG>:-g>)
		add_exe_linker_flags("-Wl,-Map=$(OutDir)$(TargetName).pdb" debug)
	endif()

	# Enable full optimization in dev/release
	add_compile_options($<$<CONFIG:DEBUG>:-O0> $<$<NOT:$<CONFIG:DEBUG>>:-O3>)

	# Use fast floating point model
	add_compile_options(-ffast-math)

	# Disable specific warnings
	add_compile_options(-Wno-reorder -Wno-overloaded-virtual -Wno-missing-braces -Wno-logical-op-parentheses -Wno-unknown-pragmas)

	# Treat all other warnings as errors
	add_compile_options(-Werror -Wno-deprecated-declarations)

elseif( PLATFORM_WEB )
	# Debug information
	add_compile_flags("-g" debug)

	# Enable full optimization in dev/release, partial optimization in debug
	add_compile_flags("-O2" debug)
	add_compile_flags("-O3" dev release)

	# Enable pthread support (if available)
	if( ENGINE_USE_WEB_THREADS )
		add_compile_flags("-s USE_PTHREADS=2")
	endif()

	# Enable SIMD
	if( ENGINE_USE_WEB_SIMD )
		add_compile_options(-msse3)
	endif()

	# Use fast floating point model
	add_compile_options(-ffast-math)

	# Disable run-time type information (RTTI)
	add_compile_options(-fno-rtti)

	# Disable exceptions
	add_compile_options(-fno-exceptions)

	# Disable specific warnings
	add_compile_options(-Wno-uninitialized -Wno-invalid-offsetof -Wno-logical-op-parentheses -Wno-inconsistent-missing-override -Wno-undefined-bool-conversion -Wno-c++14-extensions -Wno-nonportable-include-path -Wno-null-dereference)

	# Treat all other warnings as errors
	add_compile_options(-Werror)

	# Enable C++11 language, but only for c++ files
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

elseif( PLATFORM_LINUX )
	# Debug information
	if( ENGINE_USE_DEBUG_INFO )
		add_compile_options(-g)
		add_exe_linker_flags("-rdynamic")
	else()
		add_compile_options($<$<CONFIG:DEBUG>:-g>)
		add_exe_linker_flags("-rdynamic" debug)
	endif()

	# Enable full optimization in dev/release
	add_compile_options($<$<CONFIG:DEBUG>:-O0> $<$<NOT:$<CONFIG:DEBUG>>:-O3>)

	# Use pipes rather than temporary files for communication between the various stages of compilation
	add_compile_options(-pipe)

	# Adds support for multithreading with the pthreads library
	add_compile_options(-pthread)

	# Use fast floating point model
	add_compile_options(-ffast-math)

	# Disable run-time type information (RTTI)
	add_compile_options(-fno-rtti)

	# Enable SIMD instructions (SSE3)
	add_compile_options(-msse3)

	# Disable specific warnings
	add_compile_options(-Wno-parentheses -Wno-reorder -Wno-missing-braces -Wno-unused-private-field -Wno-return-type-c-linkage)

	# Treat all other warnings as errors
	add_compile_options(-Werror)

	# Enable C++11 language, but only for c++ files
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

else()
	message(FATAL_ERROR "Unknown platform!")
endif()

# Add runtime dir as root for includes
include_directories(${PROJECT_SOURCE_DIR})

# Add the binary directory to include paths, needed for build_identifier.h
include_directories(${PROJECT_BINARY_DIR})

# Set main_<platform> project as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
