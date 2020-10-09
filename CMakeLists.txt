cmake_minimum_required(VERSION 3.12)

project(ClusterEngine
        VERSION 0.0.1
	LANGUAGES CXX C)

enable_testing()

# C++ version configuration ##################################################

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
