

# add_subdirectory(glfoundation)
# add_subdirectory(utilities)
# add_subdirectory(renderpass)
# The three subdirectory up there should be grouped into a library
add_subdirectory(pipeline)

if(BUILD_PHYSICS)
    add_subdirectory(physics)
endif()

set(SOURCES
    glfoundation/camera.cpp
    glfoundation/cubemap.cpp
    glfoundation/framebuffer.cpp
    glfoundation/gbuffer.cpp
    glfoundation/globject.cpp
    glfoundation/light.cpp
    glfoundation/mesh.cpp
    glfoundation/renderstate.cpp
    glfoundation/shader.cpp
    glfoundation/texture.cpp
    glfoundation/trivialobject.cpp
    utilities/color.cpp
    utilities/material.cpp
    utilities/objobject.cpp
    utilities/timer.cpp
    utilities/debug/debug.cpp
    utilities/managers/resourcemanager
    utilities/managers/windowmanager
    renderpass/bloompass.cpp
    renderpass/gammacorrectpass.cpp
    renderpass/lightingpass.cpp
    renderpass/skyboxpass.cpp
    renderpass/sumpass.cpp
    renderpass/tonemappass.cpp
    )

set(SHADER_ROOT "${CMAKE_CURRENT_DIR}/shader")

add_library(ClusterEngine STATIC ${SOURCES})
add_library(STB_IMAGE "ext/stb_image.h")
set_target_properties(ClusterEngine PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Currently have no flags specified...
# set_target_properties(ClusterEngine PROPERTIES COMPILE_FLAGS "{PLATFORM_COMPILE_FLAGS")

target_include_directories(ClusterEngine
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(ClusterEngine
    PRIVATE
    OpenGL::OpenGL
    OpenGL::GLU
    ${GLEW_LIBRARIES}
    ${GLFW3_INCLUDE_DIRS}
    ASSIMP
    )

if(${CLS_PROFILE_MODE})
    find_library(NVTX_LIBRARY nvToolsExt PATHS ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
    if(NOT NVTX_LIBRARY)
        message(STATUS "NVIDIA Extension Library not found; can't profile with it.")
        set(CLS_PROFILE_MODE OFF)
    else()
        target_link_libraries(ClusterEngine
            PRIVATE
            ${NVTX_LIBRARY})
    endif()
endif()
