set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    vehiclespeed.cpp
)
add_library(vehicle_speed-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(vehicle_speed::vehicle_speed-implementation ALIAS vehicle_speed-implementation)
target_include_directories(vehicle_speed-implementation
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(vehicle_speed-implementation PUBLIC vehicle_speed::vehicle_speed-api PRIVATE vehicle_speed::vehicle_speed-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(vehicle_speed-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(vehicle_speed-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)

find_package(Catch2 REQUIRED)

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/vehicle_speed.test.cpp
    vehiclespeed.test.cpp
)
add_executable(test_vehicle_speed
    ${SOURCES_TEST}
)
target_link_libraries(test_vehicle_speed vehicle_speed::vehicle_speed-implementation Catch2::Catch2)
target_include_directories(test_vehicle_speed PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_vehicle_speed PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_vehicle_speed PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_vehicle_speed COMMAND $<TARGET_FILE:test_vehicle_speed>)
endif(BUILD_TESTING)

install(TARGETS vehicle_speed-implementation
        EXPORT Vehicle_speedImplementationTargets)
# install includes
FILE(GLOB Vehicle_speed_INCLUDES *.h)
install(FILES ${Vehicle_speed_INCLUDES}
        DESTINATION include/vehicle_speed/implementation)

export(EXPORT Vehicle_speedImplementationTargets
  NAMESPACE vehicle_speed::
)

install(EXPORT Vehicle_speedImplementationTargets
  FILE Vehicle_speedImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE vehicle_speed::
)
