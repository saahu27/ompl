# Install script for directory: /home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/src/ompl

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ompl-1.6/ompl" TYPE FILE FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/ompl/src/ompl/config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so.1.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so.17"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/usr/local/lib:/opt/ros/iron/lib/x86_64-linux-gnu:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/lib/libompl.so.1.6.0"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/lib/libompl.so.17"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so.1.6.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so.17"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/opt/ros/iron/lib/x86_64-linux-gnu:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so:/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/tinyxml2::tinyxml2:"
           NEW_RPATH "/usr/local/lib:/opt/ros/iron/lib/x86_64-linux-gnu:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so"
         RPATH "/usr/local/lib:/opt/ros/iron/lib/x86_64-linux-gnu:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/lib/libompl.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so"
         OLD_RPATH "/opt/ros/iron/lib/x86_64-linux-gnu:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so:/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/tinyxml2::tinyxml2:"
         NEW_RPATH "/usr/local/lib:/opt/ros/iron/lib/x86_64-linux-gnu:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so:/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libompl.so")
    endif()
  endif()
endif()

