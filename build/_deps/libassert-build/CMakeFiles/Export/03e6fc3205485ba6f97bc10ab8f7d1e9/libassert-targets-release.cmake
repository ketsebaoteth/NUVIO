#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libassert::assert" for configuration "Release"
set_property(TARGET libassert::assert APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libassert::assert PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/assert.lib"
  )

list(APPEND _cmake_import_check_targets libassert::assert )
list(APPEND _cmake_import_check_files_for_libassert::assert "${_IMPORT_PREFIX}/lib/assert.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
