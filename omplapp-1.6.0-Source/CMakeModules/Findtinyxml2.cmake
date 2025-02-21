# Findtinyxml2.cmake
# Locate the TinyXML2 library.
# This module defines:
#   tinyxml2_FOUND
#   tinyxml2_INCLUDE_DIRS
#   tinyxml2_LIBRARIES
#
# Additionally, it creates an imported target tinyxml2::tinyxml2.

find_path(TINYXML2_INCLUDE_DIR
  NAMES tinyxml2.h
  PATHS
    /usr/include
    /usr/local/include
  DOC "TinyXML2 include directory"
)

find_library(TINYXML2_LIBRARY
  NAMES tinyxml2
  PATHS
    /usr/lib
    /usr/local/lib
    /usr/lib/x86_64-linux-gnu
  DOC "TinyXML2 library"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(tinyxml2 DEFAULT_MSG TINYXML2_LIBRARY TINYXML2_INCLUDE_DIR)

if(tinyxml2_FOUND)
  set(tinyxml2_LIBRARIES ${TINYXML2_LIBRARY})
  set(tinyxml2_INCLUDE_DIRS ${TINYXML2_INCLUDE_DIR})
  mark_as_advanced(TINYXML2_INCLUDE_DIR TINYXML2_LIBRARY)

  # Create an imported target alias.
  add_library(tinyxml2::tinyxml2 UNKNOWN IMPORTED)
  set_target_properties(tinyxml2::tinyxml2 PROPERTIES
      IMPORTED_LOCATION "${tinyxml2_LIBRARIES}"
      INTERFACE_INCLUDE_DIRECTORIES "${tinyxml2_INCLUDE_DIRS}"
  )
endif()
