cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MainCarServer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the submodule as a subdirectory
add_subdirectory(Controller)
add_subdirectory(Sensors)
add_subdirectory(Sensors/CANBus)

# Specify include directories for MainCar
include_directories(MainCar/includes)
include_directories(Devices/includes)
include_directories(Controller/includes)
include_directories(Sensors/includes)
include_directories(Sensors/CANBus/includes)

# Define the source files for MainCar
set(MAINCAR_SOURCES
    MainCar/sources/ACar.cpp
    MainCar/sources/JetSnailsCar.cpp
    Devices/sources/devices.cpp
    main.cpp
)

# Create the executable for the project
add_executable(${PROJECT_NAME} ${MAINCAR_SOURCES})

# Link the Controller library to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE Controller)
target_link_libraries(${PROJECT_NAME} PRIVATE SpeedSensorLib)
target_link_libraries(${PROJECT_NAME} PRIVATE CANBus)

