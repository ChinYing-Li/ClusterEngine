add_subdirectory(glfoundation)
add_subdirectory(utilities)
add_subdirectory(renderpass)
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
    )

add_library(ClusterEngine ${SOURCES})
add_library(STB_IMAGE "ext/stb_image.h")

target_include_directories(ClusterEngine
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
)


target_link_libraries(oglapphelpers
    PRIVATE
    OpenGL::OpenGL
    OpenGL::GLU
    ${GLEW_LIBRARIES}
    GLFW3
    )

