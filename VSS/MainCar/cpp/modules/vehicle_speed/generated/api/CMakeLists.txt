set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(vehicle_speed-api INTERFACE)
add_library(vehicle_speed::vehicle_speed-api ALIAS vehicle_speed-api)
target_include_directories(vehicle_speed-api
    INTERFACE
    $<BUILD_INTERFACE:${MODULES_DIR}>
    $<INSTALL_INTERFACE:include>
)

# install binary files
install(TARGETS vehicle_speed-api
        EXPORT Vehicle_speedApiTargets)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/vehicle_speed/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT Vehicle_speedApiTargets
  NAMESPACE vehicle_speed::
)

install(EXPORT Vehicle_speedApiTargets
  FILE Vehicle_speedApiTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE vehicle_speed::
)
