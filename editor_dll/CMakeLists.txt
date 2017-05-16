cmake_minimum_required(VERSION 3.6)
project(editor_dll)

# Include common plugin CMake scripts and set the type of plugin to be to and EDITOR_PLUGIN
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${REPOSITORY_DIR}/cmake")
include(CMakePlugin)
include(GenerateExportHeader)

# Scan and add project source files
find_source_files(ALL_SOURCE_FILES)

# Setup DLL dynamic library
set(BUILD_SHARED_LIBS TRUE)
add_library(${PROJECT_NAME} SHARED ${ALL_SOURCE_FILES})
generate_export_header(${PROJECT_NAME})

# Set target properties
set(TARGET_BASE_NAME "${PROJECT_NAME}_${ENGINE_PLUGIN_SUFFIX}_$<LOWER_CASE:$<CONFIG>>")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${TARGET_BASE_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${EDITOR_PLUGINS_INSTALL_DIR}")
