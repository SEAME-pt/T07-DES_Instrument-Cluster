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

# Add the directories for pigpio headers and libraries
include_directories(/usr/local/include)  # Diretório onde o pigpio.h está localizado
link_directories(/usr/local/lib)  # Diretório onde a biblioteca pigpio foi instalada

# Find and link the pigpio library
find_library(PIGPIO_LIB pigpio REQUIRED)

# List of source files
set(SOURCES
    sources/Controller.cpp
    sources/JetCar.cpp
    sources/main.cpp
    sources/devices.cpp
)

# Add executable
add_executable(ControllerExec ${SOURCES})

# Link the executable with SDL2, pigpio, and zmq libraries
target_link_libraries(ControllerExec ${SDL2_LIBRARIES} ${PIGPIO_LIB} /usr/lib/aarch64-linux-gnu/libzmq.so)
