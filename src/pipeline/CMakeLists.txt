set(SOURCES
        deferred.cpp
        deferedcluster.cpp
        forward.cpp
        pipelinebase.cpp
        )

add_library(pipeline STATIC ${SOURCES})

target_include_directories(pipeline
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
        )