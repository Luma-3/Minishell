#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Check::check" for configuration "Release"
set_property(TARGET Check::check APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Check::check PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcheck.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Check::check )
list(APPEND _IMPORT_CHECK_FILES_FOR_Check::check "${_IMPORT_PREFIX}/lib/libcheck.a" )

# Import target "Check::checkShared" for configuration "Release"
set_property(TARGET Check::checkShared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Check::checkShared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcheck.so.0.15.2"
  IMPORTED_SONAME_RELEASE "libcheck.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS Check::checkShared )
list(APPEND _IMPORT_CHECK_FILES_FOR_Check::checkShared "${_IMPORT_PREFIX}/lib/libcheck.so.0.15.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
