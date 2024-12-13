#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "olink_core::olink_core" for configuration "Release"
set_property(TARGET olink_core::olink_core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(olink_core::olink_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libolink_core.a"
  )

list(APPEND _cmake_import_check_targets olink_core::olink_core )
list(APPEND _cmake_import_check_files_for_olink_core::olink_core "${_IMPORT_PREFIX}/lib/libolink_core.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
