#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vehicle_speed::vehicle_speed-core" for configuration "Release"
set_property(TARGET vehicle_speed::vehicle_speed-core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vehicle_speed::vehicle_speed-core PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvehicle_speed-core.so"
  IMPORTED_SONAME_RELEASE "libvehicle_speed-core.so"
  )

list(APPEND _cmake_import_check_targets vehicle_speed::vehicle_speed-core )
list(APPEND _cmake_import_check_files_for_vehicle_speed::vehicle_speed-core "${_IMPORT_PREFIX}/lib/libvehicle_speed-core.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
