# Root source directory is ${WSH_SOURCE_DIRECTORY}
cmake_minimum_required (VERSION 2.8)
project (WSH)

#Version
set (WSH_VERSION_MAJOR_1)
set (WSH_VERSION_MINOR_0)

set (WSH_VERSION "${WSH_VERSION_MAJOR}.${WSH_ERSION_MINOR}")

# Compiler flags
set (CMAKE_CXX_FLAGS "-Wall")

# Source directories
set (UTIL_DIR "util")
set (PLATFORM_DIR "platform")
set (INCLUDE_DIR "include")
set (CORE_DIR "core")

# Include directories
include_directories (${UTIL_DIR})
include_directories (${PLATFORM_DIR})
include_directories (${INCLUDE_DIR})

# Add source files
set (UTIL_FILES 
    ${UTIL_DIR}/hashtable.c
    ${UTIL_DIR}/hashtable.h
)
SOURCE_GROUP(util FILES ${UTIL_FILES})

set (INCLUDE_FILES
    ${INCLUDE_DIR}/wsh_builtin.h
    ${INCLUDE_DIR}/wsh_command.h
    ${INCLUDE_DIR}/wsh_execute.h
    ${INCLUDE_DIR}/wsh_input.h
    ${INCLUDE_DIR}/wsh_parse.h
    ${INCLUDE_DIR}/wsh_read.h
    ${INCLUDE_DIR}/wsh_status.h
)
SOURCE_GROUP(include FILES ${INCLUDE_FILES})

set (CORE_FILES
    ${CORE_DIR}/wsh_builtin.c
    ${CORE_DIR}/wsh_command.c
    ${CORE_DIR}/wsh_execute.c
    ${CORE_DIR}/wsh_input.c
    ${CORE_DIR}/wsh_parse.c
    ${CORE_DIR}/wsh_read.c
    ${CORE_DIR}/main.c
)
SOURCE_GROUP(core FILES ${CORE_FILES})

set (PLATFORM_FILES ${PLATFORM_DIR}/platform.h)
if (UNIX)
    set (PLATFORM_FILES ${PLATFORM_FILES} ${PLATFORM_DIR}/wsh_posix.c)
else()
    set (PLATFORM_FILES ${PLATFORM_FILES} ${PLATFORM_DIR}/wsh_windows.c)
endif()
SOURCE_GROUP(platform FILES ${PLATFORM_FILES})

add_executable (wsh ${UTIL_FILES} ${INCLUDE_FILES} ${PLATFORM_FILES} ${CORE_FILES})
