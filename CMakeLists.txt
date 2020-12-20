cmake_minimum_required(VERSION 3.13)


###############################################################################
# Project definition

project(ClusterEngine
        VERSION 0.0.1
        CMAKE_PROJECT_DESCRIPTION "Rendering Engine with Cluster Shading and OpenGL"
	LANGUAGES CXX C)

enable_testing()

###############################################################################
# CMAKE configuration

set(CMAKE_WARN_DEPRECATED ON)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/share/cmake/utils
    ${CMAKE_SOURCE_DIR}/share/cmake/macros
    ${CMAKE_SOURCE_DIR}/share/cmake/modules
)

###############################################################################
# C++ configuration

set(SUPPORTED_CXX_STANDARDS 11 14)
string(REPLACE ";" ", " SUPPORTED_CXX_STANDARDS_STR "${SUPPORTED_CXX_STANDARDS}")

###############################################################################
# GPU configuration

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if(NOT APPLE)
    find_package(GLEW REQUIRED)
endif()

find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)


###############################################################################
# Progress to other sources

add_subdirectory(src)
