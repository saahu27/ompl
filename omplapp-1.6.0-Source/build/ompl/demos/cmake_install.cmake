# Install script for directory: /home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/KinematicChainPathPlot.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/OptimalPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/PlannerData.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/Point2DPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/RandomWalkPlanner.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/RigidBodyPlanning.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/RigidBodyPlanningWithControls.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/RigidBodyPlanningWithODESolverAndControls.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE PROGRAM FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/build/share/ompl/demos/StateSampling.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE FILE FILES
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/CForestCircleGridBenchmark.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/Diagonal.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/GeometricCarPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/HybridSystemPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/HypercubeBenchmark.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/KinematicChainBenchmark.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/LTLWithTriangulation.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/OpenDERigidBodyPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/OptimalPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/PlannerData.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/PlannerProgressProperties.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/Point2DPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/RigidBodyPlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/RigidBodyPlanningWithControls.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/RigidBodyPlanningWithIK.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/RigidBodyPlanningWithIntegrationAndControls.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/RigidBodyPlanningWithODESolverAndControls.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/SpaceTimePlanning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/StateSampling.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/ThunderLightning.cpp"
    "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/TriangulationDemo.cpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE DIRECTORY FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/Koules")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "ompl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ompl/demos" TYPE DIRECTORY FILES "/home/sahugf/omplpinnochio/omplapp-1.6.0-Source/ompl/demos/VFRRT")
endif()

