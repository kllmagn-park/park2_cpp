#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LIBSHARED::libshared" for configuration "Release"
set_property(TARGET LIBSHARED::libshared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(LIBSHARED::libshared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/liblibshared.so"
  IMPORTED_SONAME_RELEASE "liblibshared.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS LIBSHARED::libshared )
list(APPEND _IMPORT_CHECK_FILES_FOR_LIBSHARED::libshared "${_IMPORT_PREFIX}/lib/liblibshared.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
