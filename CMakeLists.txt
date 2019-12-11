CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(SpaceInvaders)
SET(CMAKE_CXX_STANDARD 14)
ADD_EXECUTABLE(SpaceInvaders main.cpp Stopwatch.cpp Stopwatch.h Game.cpp Game.h Transformation.cpp Transformation.h Level.cpp Level.h)

# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Look for SFML >= 2.4.2, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2.4.2 COMPONENTS system window graphics)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

# Link target to SFML libs
# (The SFML_LIBRARIES variable is defined by FindSFML.cmake, if SFML was found)
TARGET_LINK_LIBRARIES(SpaceInvaders ${SFML_LIBRARIES})

INSTALL(TARGETS SpaceInvaders DESTINATION ${PROJECT_SOURCE_DIR}/bin)
