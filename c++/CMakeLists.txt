cmake_minimum_required(VERSION 3.5.0)

project(GSGfile)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(GSGfile_SOURCES
  src/GSGfile.cpp
)

include_directories("${PROJECT_SOURCE_DIR}/src")

OPTION(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
SET(LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
  SET(LIB_TYPE SHARED)
endif()

add_library(GSGfile ${LIB_TYPE} ${GSGfile_SOURCES})

SET(GSGfile_Headers
${PROJECT_SOURCE_DIR}/src/GSGfile.h
)

# tests
enable_testing()

add_subdirectory("${CMAKE_SOURCE_DIR}/test")
add_subdirectory("${CMAKE_SOURCE_DIR}/examples")

target_compile_definitions(GSGfile PRIVATE GSGfile_LIBRARY)
