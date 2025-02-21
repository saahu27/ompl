# Install script for directory: /home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/DynamicCarPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/KinematicCarPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/SE3MultiRigidBodyPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/SE3RigidBodyPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "omplapp" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE FILE FILES
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/OpenDEPlanning/displayOpenDE.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/OpenDEPlanning/planOpenDE.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE2RigidBodyPlanning/DynamicCarPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE2RigidBodyPlanning/KinematicCarPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE2RigidBodyPlanning/SE2MultiRigidBodyPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE2RigidBodyPlanning/SE2RigidBodyPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/BlimpPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/CollisionCheckers.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/QuadrotorPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/SE3MultiRigidBodyPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/SE3RigidBodyPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/SE3RigidBodyPlanningBenchmark.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/demos/SE3RigidBodyPlanning/SE3RigidBodyPlanningWithOptimization.cpp"
    )
endif()

