set(SOURCES
        objloader.cpp)

add_library(ext STATIC ${SOURCES})

target_include_directories(ext PUBLIC .)