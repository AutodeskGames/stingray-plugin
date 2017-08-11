cmake_minimum_required(VERSION 3.8)

# This module is shared; use include blocker.
if( _SETTINGS_ )
	return()
endif()
set(_SETTINGS_ 1)

include(CMakePlatforms)
include(CMakeMacros)

# Define product build options
set(PRODUCT_NAME "Stingray")
set(PRODUCT_COMPANY "Autodesk")
set(PRODUCT_COPYRIGHT "Copyright (C) 2016 ${PRODUCT_COMPANY}, Inc. All rights reserved.")
set(PRODUCT_VERSION_MAJOR "1")
set(PRODUCT_VERSION_MINOR "9")
set(PRODUCT_VERSION_REVISION "0")

# Bump this revision if projects require any migration.
# Reset to 0 if you increase MAJOR or MINOR versions.
set(PRODUCT_DEV_VERSION_REVISION "0")
string(TIMESTAMP PRODUCT_DEFAULT_BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ" UTC)

# Build options controlled by TeamCity - do not change here!
set_default(PRODUCT_VERSION_LABEL "$ENV{SR_PRODUCT_VERSION_LABEL}" "Developer Build")
set_default(PRODUCT_VERSION_TCID "$ENV{SR_PRODUCT_VERSION_TCID}" "0")
set_default(PRODUCT_BUILD_TIMESTAMP "$ENV{SR_PRODUCT_BUILD_TIMESTAMP}" "${PRODUCT_DEFAULT_BUILD_TIMESTAMP}")
set_default(PRODUCT_LICENSING_KEY "$ENV{SR_PRODUCT_LICENSING_KEY}" "A72J1")
set_default(PRODUCT_LICENSING_VERSION "$ENV{SR_PRODUCT_LICENSING_VERSION}" "2018.0.0.F")

# Allow environment variables to override some build options
set(ENGINE_BUILD_IDENTIFIER $ENV{SR_BUILD_IDENTIFIER})

# Check if required variables are properly defined
if( NOT REPOSITORY_DIR OR REPOSITORY_DIR STREQUAL "" )
	message(FATAL_ERROR "REPOSITORY_DIR not set! Please set REPOSITORY_DIR to appropriate location when running this CMake script.")
endif()
string(REGEX REPLACE "\\\\" "/" REPOSITORY_DIR ${REPOSITORY_DIR})

if( NOT CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX STREQUAL "" )
	message(FATAL_ERROR "CMAKE_INSTALL_PREFIX not set! Please set CMAKE_INSTALL_PREFIX to appropriate location when running this CMake script.")
endif()
string(REGEX REPLACE "\\\\" "/" BINARIES_DIR ${CMAKE_INSTALL_PREFIX})

# PLUGIN REPO CUSTOM CHANGE
if( NOT ENGINE_LIB_DIR )
	set(ENGINE_LIB_DIR $ENV{SR_LIB_DIR})
	if( NOT ENGINE_LIB_DIR OR ENGINE_LIB_DIR STREQUAL "" )
		message(FATAL_ERROR "Environment variable SR_LIB_DIR not set! Please set environment variable SR_LIB_DIR to appropriate location before running this CMake script.")
	endif()
endif()
string(REGEX REPLACE "\\\\" "/" ENGINE_LIB_DIR ${ENGINE_LIB_DIR})

# Generate package location cache
set(PACKAGE_CACHE_FILE "${CMAKE_BINARY_DIR}/cmake_package_cache.cmake")
generate_package_location_cache()

# Set install directories
if( PLATFORM_WINDOWS )
	set(ENGINE_INSTALL_DIR "${BINARIES_DIR}/engine/win${ARCH_BITS}/$<LOWER_CASE:$<CONFIG>>")
	# PLUGIN REPO CUSTOM CHANGE
	set(EDITOR_INSTALL_DIR "${BINARIES_DIR}/editor/win${ARCH_BITS}/$<LOWER_CASE:$<CONFIG>>")
elseif( PLATFORM_UWP )
	set(ENGINE_INSTALL_DIR "${BINARIES_DIR}/engine/uwp${ARCH_BITS}/$<LOWER_CASE:$<CONFIG>>")
	# PLUGIN REPO CUSTOM CHANGE
	set(EDITOR_INSTALL_DIR "${BINARIES_DIR}/editor/uwp${ARCH_BITS}/$<LOWER_CASE:$<CONFIG>>")
else()
	set(ENGINE_INSTALL_DIR "${BINARIES_DIR}/engine/${PLATFORM_NAME}/$<LOWER_CASE:$<CONFIG>>")
	# PLUGIN REPO CUSTOM CHANGE
	set(EDITOR_INSTALL_DIR "${BINARIES_DIR}/editor/${PLATFORM_NAME}/$<LOWER_CASE:$<CONFIG>>")
endif()
# PLUGIN REPO CUSTOM CHANGE
set(ENGINE_PLUGINS_INSTALL_DIR "${ENGINE_INSTALL_DIR}")
set(EDITOR_PLUGINS_INSTALL_DIR "${EDITOR_INSTALL_DIR}")
set(TOOLS_INSTALL_DIR "${BINARIES_DIR}/tools")
set(PLUGIN_SDK_INSTALL_DIR "${BINARIES_DIR}/plugin_sdk")
set(TOOLS_EXTERNAL_INSTALL_DIR "${BINARIES_DIR}/tools_external")

if( PLATFORM_WINDOWS )
	set(ENGINE_PLUGIN_SUFFIX "w${ARCH_BITS}")
else()
	set(ENGINE_PLUGIN_SUFFIX "")
endif()

# Global options
if( PLATFORM_WINDOWS OR PLATFORM_ANDROID OR PLATFORM_IOS)
	set(BUILD_SHARED_LIBS ON CACHE BOOL "Build plug-ins as shared libraries.")
else()
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build plug-ins as static libraries.")
endif()

if( PLATFORM_IOS )
	# In order to find what value to set for SR_IOS_DEVELOPMENT_TEAM, follow these steps:
	#    - Open the generated XCode project
	#    - Set the development team manually to the desired team
	#    - Close XCode
	#    - Find and open the XCode project file in a text editor: stingray_engine_ios.xcodeproj/project.pbxproj
	#    - Find the team entry: DEVELOPMENT_TEAM
	#    - The value assigned is an ID that looks like this: 2C7C55VMJ0
	#    - This is the value you need to use and set for the environment variable

	set_default(ENGINE_IOS_CODE_SIGN_IDENTITY "$ENV{SR_IOS_CODE_SIGN_IDENTITY}" "iPhone Developer")
	if (NOT DEFINED ENV{SR_IOS_DEVELOPMENT_TEAM} OR "$ENV{SR_IOS_DEVELOPMENT_TEAM}" STREQUAL "")
		message(WARNING "
****************************************
ERROR: No iOS development team is set.
Please set SR_IOS_DEVELOPMENT_TEAM environment var.
****************************************
Try running:
$ source tools/ios_resign/set_ios_dev_team.sh
****************************************")
	endif()
	set_default(ENGINE_IOS_DEVELOPMENT_TEAM "$ENV{SR_IOS_DEVELOPMENT_TEAM}" "")
endif()

# Engine options
set(ENGINE_USE_DEBUG_INFO ON CACHE BOOL "Enable debug information in all configurations.")
set(ENGINE_USE_AVX OFF CACHE BOOL "Enable AVX instructions set support.")

set(ENGINE_USE_WEB_WASM ON CACHE BOOL "Enable WebAssembly support for Web platform.")
set(ENGINE_USE_WEB_THREADS OFF CACHE BOOL "Enable threading support for Web platform.")
set(ENGINE_USE_WEB_SIMD OFF CACHE BOOL "Enable SIMD support for Web platform.")

# Set folder names inside solution files
set(ENGINE_FOLDER_NAME "runtime")
set(ENGINE_PLUGINS_FOLDER_NAME "plugins")
set(ENGINE_USE_SOLUTION_FOLDERS ON)

# Define if platform can compile game data
if( PLATFORM_64BIT AND (PLATFORM_WINDOWS) )
	set(ENGINE_CAN_COMPILE 1)
endif()

# Editor options
set(EDITOR_SHIPPING OFF CACHE BOOL "Enable editor shipping mode.")
set(BUILD_FEATURES_INTERNAL_CLIC_ENABLED OFF CACHE BOOL "Enable CLIC support.")
set(EDITOR_USE_CER OFF CACHE BOOL "Enable CER support.")
set(EDITOR_USE_UPI OFF CACHE BOOL "Enable UPI support.")
set(EDITOR_USE_MC3 OFF CACHE BOOL "Enable MC3 support.")
set(EDITOR_USE_TEMPLATES OFF CACHE BOOL "Enable editor template install.")
set(EDITOR_USE_GEARVR OFF CACHE BOOL "Enable editor GearVR support.")

if( EDITOR_SHIPPING )
	if( NOT EDITOR_USE_CER )
		message(STATUS "CER support enabled, implied by editor's shipping mode.")
		set(EDITOR_USE_CER ON)
	endif()
	if( NOT EDITOR_USE_UPI )
		message(STATUS "UPI support enabled, implied by editor's shipping mode.")
		set(EDITOR_USE_UPI ON)
	endif()
	if( NOT EDITOR_USE_MC3 )
		message(STATUS "MC3 support enabled, implied by editor's shipping mode.")
		set(EDITOR_USE_MC3 ON)
	endif()
endif()

set(PRODUCT_VERSION_REGKEY "${PRODUCT_VERSION_MAJOR}.${PRODUCT_VERSION_MINOR}.${PRODUCT_VERSION_TCID}.${PRODUCT_VERSION_REVISION}")
