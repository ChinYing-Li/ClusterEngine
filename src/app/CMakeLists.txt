set(SOURCES
    app.cpp)

add_library(app STATIC ${SOURCES})

target_link_libraries(app
        PRIVATE
        ClusterEngine
        pipeline
        )

target_include_directories(pipeline
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}
        )