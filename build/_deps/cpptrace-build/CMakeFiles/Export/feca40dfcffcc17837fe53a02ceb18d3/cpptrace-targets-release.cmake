#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cpptrace::cpptrace" for configuration "Release"
set_property(TARGET cpptrace::cpptrace APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cpptrace::cpptrace PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/cpptrace.lib"
  )

list(APPEND _cmake_import_check_targets cpptrace::cpptrace )
list(APPEND _cmake_import_check_files_for_cpptrace::cpptrace "${_IMPORT_PREFIX}/lib/cpptrace.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
