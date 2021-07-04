if(BUILD_PHYSICS)
    add_subdirectory(physics)
endif()

set(SOURCES
    glfoundation/camera.cpp
    glfoundation/cubemap.cpp
    glfoundation/framebuffer.cpp
    glfoundation/gbuffer.cpp
    glfoundation/light.cpp
    glfoundation/mesh.cpp
    glfoundation/renderable.cpp
    glfoundation/renderstate.cpp
    glfoundation/shader.cpp
    glfoundation/shaderregistry.cpp
    glfoundation/skybox.cpp
    glfoundation/texture.cpp
    glfoundation/texturegenerator.cpp
    glfoundation/transformation.cpp
    glfoundation/trivialobject.cpp
    utilities/color.cpp
    utilities/fpscounter.cpp
    utilities/material.cpp
    utilities/objobject.cpp
    utilities/debug/debug.cpp
    utilities/managers/windowmanager.cpp
    renderpass/bloompass.cpp
    renderpass/gammacorrectpass.cpp
    renderpass/gaussianblurpass.cpp
    renderpass/lightingpass.cpp
    renderpass/renderpass.cpp
    renderpass/skyboxpass.cpp
    renderpass/sumpass.cpp
    renderpass/tonemappass.cpp
    renderpass/lightmanage/clusterpass.cpp
    )

set(SHADER_ROOT "${CMAKE_CURRENT_DIR}/shader")

add_library(ClusterEngine STATIC ${SOURCES})

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
    ext)

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

add_subdirectory(pipeline)
