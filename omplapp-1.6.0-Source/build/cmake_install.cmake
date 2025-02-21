# Install script for directory: /home/sahugf/omplpinnochio/omplapp-1.6.0-Source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl" TYPE DIRECTORY FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/resources" REGEX "/\\.DS\\_Store$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl" TYPE DIRECTORY FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/webapp" REGEX "/\\.DS\\_Store$" EXCLUDE REGEX "/\\_\\_pycache\\_\\_$" EXCLUDE REGEX "/omplweb\\.py$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/webapp" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/webapp/omplweb.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM RENAME "ompl_webapp" FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/webapp/ompl_webapp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/cmake" TYPE FILE FILES
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/omplConfig.cmake"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/omplConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/doc/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/src/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/py-bindings/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/tests/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/demos/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/scripts/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/gui/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/doc/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/src/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/demos/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/benchmark/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/py-bindings/cmake_install.cmake")
  include("/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl_gui/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
