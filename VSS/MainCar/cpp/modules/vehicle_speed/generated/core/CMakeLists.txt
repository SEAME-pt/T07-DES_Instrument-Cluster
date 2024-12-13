set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
set (SOURCES_CORE_SUPPORT
    vehicle_speed.json.adapter.cpp
    vehiclespeed.publisher.cpp
    vehiclespeed.threadsafedecorator.cpp
)
add_library(vehicle_speed-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(vehicle_speed::vehicle_speed-core ALIAS vehicle_speed-core)
target_include_directories(vehicle_speed-core
    PUBLIC
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(vehicle_speed-core PUBLIC vehicle_speed::vehicle_speed-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(vehicle_speed-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(vehicle_speed-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS vehicle_speed-core
        EXPORT Vehicle_speedCoreTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/vehicle_speed/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Vehicle_speedCoreTargets
  NAMESPACE vehicle_speed::
)

install(EXPORT Vehicle_speedCoreTargets
  FILE Vehicle_speedCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE vehicle_speed::
)
