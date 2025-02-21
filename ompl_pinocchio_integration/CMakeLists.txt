cmake_minimum_required(VERSION 3.10)
project(ompl_pinocchio_integration)

# Tell CMake where to find custom modules.
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/home/sahugf/omplpinnochio/pinocchio/build")

# Manually specify the correct Pinocchio path if not found
set(PINOCCHIO_DIR "/home/sahugf/omplpinnochio/pinocchio/build")
set(PINOCCHIO_INCLUDE_DIRS "${PINOCCHIO_DIR}/include")

find_package(OMPL REQUIRED)
# We are manually setting Pinocchio variables here.
# find_package(Pinocchio CONFIG REQUIRED) is commented out or replaced by manual settings.
find_package(Eigen3 REQUIRED)

# Include directories
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${PINOCCHIO_INCLUDE_DIRS})
include_directories(${OMPL_INCLUDE_DIRS})
# *** Add the project include directory so that headers in "include/" are found ***
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/models)

# Manually set Pinocchio libraries
set(PINOCCHIO_LIBRARIES
    "/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_default.so;/home/sahugf/omplpinnochio/pinocchio/build/src/libpinocchio_parsers.so"
)

message(STATUS "Pinocchio Include Dirs: ${PINOCCHIO_INCLUDE_DIRS}")
message(STATUS "Pinocchio Libraries: ${PINOCCHIO_LIBRARIES}")
message(STATUS "OMPL Libraries: ${OMPL_LIBRARIES}")
message(STATUS "OMPL Include Dirs: ${OMPL_INCLUDE_DIRS}")
message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")

if(NOT PINOCCHIO_LIBRARIES)
    message(FATAL_ERROR "Pinocchio libraries not found. Please verify that PINOCCHIO_DIR is set correctly and that the Pinocchio library is built and installed.")
endif()

if(NOT OMPL_LIBRARIES)
    message(FATAL_ERROR "OMPL libraries not found. Please check your OMPL installation.")
endif()

# Add our executable
add_executable(robot_planner 
    src/main.cpp 
    src/Robot_Model.cpp 
    src/Motion_Planner.cpp)

# Link external libraries
target_link_libraries(robot_planner PRIVATE
    ${PINOCCHIO_LIBRARIES} 
    ${OMPL_LIBRARIES}
)

# Add our executable
add_executable(example_robot_planner 
    examples/pinocchio_ompl_planning.cpp )

# Link external libraries
target_link_libraries(example_robot_planner PRIVATE
    ${PINOCCHIO_LIBRARIES} 
    ${OMPL_LIBRARIES}
)