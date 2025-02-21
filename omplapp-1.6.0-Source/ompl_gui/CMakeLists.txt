cmake_minimum_required(VERSION 3.5)
project(ompl_gui LANGUAGES CXX)

# Let CMake run moc/uic automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# This is recommended for new CMake + Qt usage
find_package(Qt5 5.9 REQUIRED COMPONENTS Widgets OpenGL)

# Let’s prefer GLVND over legacy if available
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

find_package(ompl CONFIG REQUIRED)

# Only needed if you're actually calling GLU functions (like gluPerspective).
# If so, also link GLU. Some systems treat it as separate library, some do not.
# (On some Linux distros, -lGLU is separate from -lGL.)
# If you need GLU:
# find_package(GLU REQUIRED)

# 1) Gather all sources. 
#    - We have mainWindow, mainWidget, problemWidget, etc. 
#    - Also your "main.cpp" is here. 
#    - List them all so that AUTOMOC sees the Q_OBJECT classes.
set(GUI_SOURCES
    src/main.cpp

    # The main window
    src/MainWindow.cpp
    include/MainWindow.h

    # The main widget that has the GLViewer, ProblemWidget, etc.
    src/MainWidget.cpp
    include/MainWidget.h

    # GLViewer
    src/GLViewer.cpp
    include/GLViewer.h

    # ProblemWidget + Pose2DBox/Pose3DBox
    src/ProblemWidget.cpp
    include/ProblemWidget.h
    src/Pose2DBox.cpp
    include/Pose2DBox.h
    src/Pose3Dbox.cpp  # <— watch the name if it’s "Pose3Dbox.cpp" or "Pose3DBox.cpp"
    include/Pose3DBox.h

    # PlannerWidget + sub-widgets
    src/PlannerWidget.cpp
    include/PlannerWidget.h
    src/PlannerHelperWidget.cpp
    include/PlannerHelperWidget.h
    src/GeometricPlannerWidget.cpp
    include/GeometricPlannerWidget.h
    
    # If you have ControlPlannerWidget, 
    src/ControlPlannerWidget.cpp 
    include/ControlPlannerWidget.h

    # BoundsWidget + BoundsBox
    src/BoundsWidget.cpp
    include/BoundsWidget.h
    src/BoundsBox.cpp
    include/BoundsBox.h

    # SolveWidget
    src/SolveWidget.cpp
    include/SolveWidget.h

    src/LogOutputHandler.cpp
    include/LogOutputHandler.h

    src/PlannerRegistry.cpp
    include/PlannerRegistry.h

    include/PlannerLists.h

    include/PlannerParameterHelper.h
    src/PlannerParameterHelper.cpp
    )

# 2) Create the executable from these sources.
add_executable(ompl_gui
    ${GUI_SOURCES}
)

# 3) Include directories: your "include" folder
target_include_directories(ompl_gui
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>

    # Here we assume OMPL_INCLUDE_DIRS and OMPLAPP_INCLUDE_DIRS
    # are set by the top-level CMake or by included modules. For example:
    #    set(OMPL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ompl/src;${CMAKE_CURRENT_BINARY_DIR}/ompl/src")
    #    set(OMPLAPP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src;${CMAKE_CURRENT_BINARY_DIR}/src")
    # (You can adjust if your variable names differ.)
    ${OMPL_INCLUDE_DIRS}
    ${OMPLAPP_INCLUDE_DIRS}
    message(STATUS "OMPL_INCLUDE_DIRS: ${OMPL_INCLUDE_DIRS}")
)

# 4) Link Qt5 libs + OpenGL
target_link_libraries(ompl_gui
    Qt5::Widgets
    Qt5::OpenGL
    ${OPENGL_LIBRARIES}
    # If you need GLU:
    ${GLU_LIBRARY}
    # If you want to link ompl:
    # ompl
    ompl
    ompl_app_base
    ompl_app
)

# 5) Install the executable if desired
install(TARGETS ompl_gui
    RUNTIME DESTINATION bin
)
