cmake_minimum_required(VERSION 3.10)

# Project name
project(Controller)

# Set C++ standard to C++11 or higher
set(CMAKE_CXX_STANDARD 11)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Include directories for the project
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

# List of source files
set(SOURCES
    sources/Controller.cpp
)

# Create a library (static or shared)
add_library(Controller ${SOURCES})

# Link the library with SDL2
target_link_libraries(Controller ${SDL2_LIBRARIES})

