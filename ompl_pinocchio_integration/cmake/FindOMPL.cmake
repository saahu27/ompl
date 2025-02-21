# FindOMPL.cmake
#
# This module locates the OMPL installation and sets the following variables:
#   OMPL_FOUND         - Indicates if OMPL was found
#   OMPL_INCLUDE_DIRS  - The directory with OMPL headers
#   OMPL_LIBRARIES     - The OMPL library file
#

# Locate the header file. We know from your installation that the headers are in:
# /usr/local/include/ompl-1.6/ompl/base/SpaceInformation.h
find_path(OMPL_INCLUDE_DIR
  NAMES ompl/base/SpaceInformation.h
  HINTS /usr/local/include/ompl-1.6
)

if(NOT OMPL_INCLUDE_DIR)
  message(FATAL_ERROR "OMPL headers not found in /usr/local/include/ompl-1.6")
endif()

# Locate the library. Assume the OMPL library is named 'ompl'.
find_library(OMPL_LIBRARY
  NAMES ompl
  HINTS /usr/local/lib
)

if(NOT OMPL_LIBRARY)
  message(FATAL_ERROR "OMPL library not found in /usr/local/lib")
endif()

# Set the variables for use in your project.
set(OMPL_INCLUDE_DIRS ${OMPL_INCLUDE_DIR})
set(OMPL_LIBRARIES ${OMPL_LIBRARY})

# Mark these variables as advanced.
mark_as_advanced(OMPL_INCLUDE_DIR OMPL_LIBRARY)
