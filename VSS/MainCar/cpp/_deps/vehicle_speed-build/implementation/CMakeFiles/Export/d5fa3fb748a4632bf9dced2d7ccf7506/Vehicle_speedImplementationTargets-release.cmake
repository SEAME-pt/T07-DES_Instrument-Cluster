#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vehicle_speed::vehicle_speed-implementation" for configuration "Release"
set_property(TARGET vehicle_speed::vehicle_speed-implementation APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vehicle_speed::vehicle_speed-implementation PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "vehicle_speed::vehicle_speed-core"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvehicle_speed-implementation.so"
  IMPORTED_SONAME_RELEASE "libvehicle_speed-implementation.so"
  )

list(APPEND _cmake_import_check_targets vehicle_speed::vehicle_speed-implementation )
list(APPEND _cmake_import_check_files_for_vehicle_speed::vehicle_speed-implementation "${_IMPORT_PREFIX}/lib/libvehicle_speed-implementation.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
