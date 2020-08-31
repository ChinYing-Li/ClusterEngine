
cmake_minimum_required(VERSION 3.12)

project(ClusterEngine
        VERSION 0.0.1
	LANGUAGES CXX C)

set(ClusterEngine_VERSION_RELEASE_TYPE "dev")

enable_testing()

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/share/cmake/macros
    ${CMAKE_SOURCE_DIR}/share/cmake/modules
)
set(CMAKE_WARN_DEPRECATED ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

###############################################################################
# C++ version configuration

set(SUPPORTED_CXX_STANDARDS 11 14)
string(REPLACE ";" ", " SUPPORTED_CXX_STANDARDS_STR "${SUPPORTED_CXX_STANDARDS}")

if(CMAKE_CXX_STANDARD AND NOT CMAKE_CXX_STANDARD IN_LIST SUPPORTED_CXX_STANDARDS)
    message(FATAL_ERROR " CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD} is unsupported. Supported standards are: ${SUPPORTED_CXX_STANDARDS_STR}.")
elseif(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif()

include(CheckCXXCompilerFlag)

if(MSVC)
	CHECK_CXX_COMPILER_FLAG("-std:c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std:c++14" COMPILER_SUPPORTS_CXX14)
else()
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
endif()

if(NOT COMPILER_SUPPORTS_CXX11 AND ${CMAKE_CXX_STANDARD} EQUAL 11)
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER_ID} has no C++11 only support. Use C++14.")
	set(CMAKE_CXX_STANDARD 14)
endif()

if(NOT COMPILER_SUPPORTS_CXX14 AND ${CMAKE_CXX_STANDARD} EQUAL 14)
	message(ERROR "The compiler ${CMAKE_CXX_COMPILER_ID} has no C++14 only support.")
endif()


# Disable fallback to other C++ version if standard is not supported.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable any compiler specific C++ extensions.
set(CMAKE_CXX_EXTENSIONS OFF)

set(_BUILD_TYPE_DEBUG OFF)
if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
    set(_BUILD_TYPE_DEBUG ON)
endif()
set(BUILD_TYPE_DEBUG ${_BUILD_TYPE_DEBUG} CACHE BOOL "Case-insensitive CMAKE_BUILD_TYPE Debug equality flag.")

###############################################################################
# GPU configuration

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

if(NOT APPLE)
    find_package(GLEW REQUIRED)
endif()

find_package(GLUT REQUIRED)

###############################################################################
# Progress to other sources

add_subdirectory(include)
add_subdirectory(src)
