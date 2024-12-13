# Enable GoogleTest
find_package(GTest REQUIRED)

# Include the directory for the main library
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add unit test sources
set(TEST_SOURCES
    SpeedSensorTest.cpp
)

# Create the test executable
add_executable(SpeedSensorTest ${TEST_SOURCES})

# Link the test executable with SpeedSensor library and GoogleTest
target_link_libraries(SpeedSensorTest PRIVATE SpeedSensorLib GTest::GTest GTest::Main)

# Enable testing
add_test(NAME SpeedSensorTest COMMAND SpeedSensorTest)