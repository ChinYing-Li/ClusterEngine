set(SOURCES collisionidetector.cpp)
add_library(Physics ${SOURCE})
target_include_directories(Physics
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        )