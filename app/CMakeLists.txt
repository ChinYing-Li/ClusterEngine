set(SOURCES
    app.cpp)

add_library(app STATIC ${SOURCES})

target_link_libraries(app
        PRIVATE
        ${GLEW_LIBRARIES}
        ${GLFW3_LIBRARY}
        ${Boost_LIBRARIES}
        stdc++fs
        ClusterEngine
        pipeline
        )

target_include_directories(app
        PUBLIC
        ${GLEW_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

add_executable(
        ClusterEngineDemo
        main.cpp
)

target_link_libraries(ClusterEngineDemo
        app)

target_include_directories(ClusterEngineDemo
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
