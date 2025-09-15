cmake_minimum_required(VERSION 3.12)

# Project name
project(Engine VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively grab all .cpp files from src/ and its subdirectories
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.hpp
)

# Debug: print all sources to make sure we got them
message(STATUS "Engine sources: ${ENGINE_SRC}")

# Create shared library
add_library(Engine SHARED ${ENGINE_SRC})
target_compile_definitions(Engine PUBLIC BUILD_DLL)

# Include headers
target_include_directories(Engine PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

# Add preprocessor define for DLL export
