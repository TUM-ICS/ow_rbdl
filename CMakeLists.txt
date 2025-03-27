cmake_minimum_required(VERSION 3.11)
project(ow_rbdl)

# Set the rpath (to build deb package)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    urdf
    )

# Set a default build type to 'Release' if none was specified
IF(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
MESSAGE(STATUS "Setting build type to 'Release' as none was specified.")
SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

# Set the possible values of build type for cmake-gui
SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
ENDIF()

find_package(Eigen3 REQUIRED)
add_definitions(${EIGEN_DEFINITIONS})

#find_package(Boost REQUIRED COMPONENTS date_time thread)

catkin_package(
    INCLUDE_DIRS    include
    LIBRARIES       ow_rbdl #tum_ics_urdfreader
    CATKIN_DEPENDS  roscpp urdf
    DEPENDS         ${DEPENDS_VAR}
    )

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    )

# needed for Qt generated files
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

################################################################################
# RBDL Library
################################################################################
set(HEADER_FILES
    Body.h
    compileassert.h
    Constraints.h
    Contacts.h
    Dynamics.h
    Joint.h
    Kinematics.h
    Logging.h
    Model.h
    Quaternion.h
    rbdl_config.h
    rbdl_eigenmath.h
    rbdl.h
    rbdl_math.h
    rbdl_mathutils.h
    rbdl_utils.h
    SpatialAlgebraOperators.h
    )

foreach(file ${HEADER_FILES})
    list(APPEND HEADERS include/${PROJECT_NAME}/${file})
endforeach()
#message(${HEADERS})

set(SOURCES
    src/rbdl_mathutils.cc
    src/Constraints.cc
    src/Model.cc
    src/Logging.cc
    src/Joint.cc
    src/Kinematics.cc
    src/rbdl_version.cc
    src/Dynamics.cc
    src/rbdl_utils.cc

    src/urdfreader/urdfreader.cc
    src/urdfreader/rbdl_urdfreader_util.cc
    )

add_library(ow_rbdl ${SOURCES})

add_dependencies(ow_rbdl
    ${${PROJECT_NAME}_EXPORTED_TARGETS}
    ${catkin_EXPORTED_TARGETS})

target_link_libraries(ow_rbdl
    ${catkin_LIBRARIES}
)


######################################################################################
# TUM_ICS_NOTE: We need to modify the installation variables to be compliant with the
#   debtools. This function is controlled with the global variable -DDEB_BUILD
#   (true/false)
#include(/usr/share/cmake/CMakeTools/ics_tools.cmake)
#ics_ros_debgen()

#install(DIRECTORY include/${PROJECT_NAME}/
#    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#    )

# don't install private headers
install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
    PATTERN "*_p.h" EXCLUDE
    PATTERN "*.h"
)

install(TARGETS ow_rbdl #tum_ics_urdfreader
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    )
