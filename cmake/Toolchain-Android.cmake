# This module is shared; use include blocker.
if( _ANDROID_TOOLCHAIN_ )
	return()
endif()
set(_ANDROID_TOOLCHAIN_ 1)

# Android Nsight Tegra version requirement
set(REQUIRED_NSIGHT_TEGRA_VERSION "3.4")

# Get Android Nsight Tegra environment
set(NSIGHT_TEGRA_VERSION ${CMAKE_VS_NsightTegra_VERSION})
if( "${NSIGHT_TEGRA_VERSION}" STREQUAL "" )
	get_filename_component(NSIGHT_TEGRA_VERSION "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\NVIDIA Corporation\\Nsight Tegra;Version]" NAME)
endif()

# Report and check version if it exist
if( NOT "${NSIGHT_TEGRA_VERSION}" STREQUAL "" )
	message(STATUS "Android Nsight Tegra version found: ${NSIGHT_TEGRA_VERSION}")
	if( NOT "${NSIGHT_TEGRA_VERSION}" MATCHES "${REQUIRED_NSIGHT_TEGRA_VERSION}+" )
		message(WARNING "Expected Android Nsight Tegra version: ${REQUIRED_NSIGHT_TEGRA_VERSION}")
	endif()
endif()

# We are building Android platform, fail if Android Nsight Tegra not found
if( NOT NSIGHT_TEGRA_VERSION )
	message(FATAL_ERROR "Engine requires Android Nsight Tegra to be installed in order to build Android platform.")
endif()

set(ANDROID_NDK_ROOT "$ENV{ANDROID_NDK_ROOT}")
string(STRIP "${ANDROID_NDK_ROOT}" ANDROID_NDK_ROOT)
string(REPLACE "\\" "/" ANDROID_NDK_ROOT "${ANDROID_NDK_ROOT}")
if(NOT ANDROID_NDK_ROOT)
	message(FATAL_ERROR "Engine requires ANDROID_NDK_ROOT environment variable to point to your Android NDK.")
endif()

file(GLOB ANDROID_TOOLCHAIN_DIR "${ANDROID_NDK_ROOT}/toolchains/arm-linux-androideabi-*")
message("Android NDK directory: ${ANDROID_TOOLCHAIN_DIR}")
file(GLOB_RECURSE ANDROID_STRIP_BIN "${ANDROID_TOOLCHAIN_DIR}/*/strip.exe")

# Tell CMake we are cross-compiling to Android
set(CMAKE_SYSTEM_NAME Android)

# Tell CMake we want to use default Clang NDK toolchain version
set(CMAKE_GENERATOR_TOOLSET DefaultClang)

# Tell CMake which version of the Android API we are targeting
set(CMAKE_ANDROID_API_MIN 21)
set(CMAKE_ANDROID_API 25)

# Tell CMake we want to use all CPUs when we build
set(CMAKE_ANDROID_PROCESS_MAX $ENV{NUMBER_OF_PROCESSORS})

# Tell CMake we don't want to skip Ant step
set(CMAKE_ANDROID_SKIP_ANT_STEP 0)

# Tell CMake we have our java source in the 'java' directory
set(CMAKE_ANDROID_JAVA_SOURCE_DIR java)

# Tell CMake we have use Gradle as our default build system
set(CMAKE_ANDROID_BUILD_SYSTEM GradleBuild)
