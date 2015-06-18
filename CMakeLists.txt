# Root source directory is ${WSH_SOURCE_DIRECTORY}
cmake_minimum_required (VERSION 2.6)
project (WSH)

#Version
set (WSH_VERSION_MAJOR_1)
set (WSH_VERSION_MINOR_0)

set (WSH_VERSION "${WSH_VERSION_MAJOR}.${WSH_ERSION_MINOR}")

# Include directories
include_directories("include")
include_directories("platform")
include_directories("util")

# Recurse into source directories
add_subdirectory (platform)
add_subdirectory (util)
add_subdirectory (core)
add_subdirectory (bin)
