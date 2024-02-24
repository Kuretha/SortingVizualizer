cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
# compiler flags
set(CMAKE_CXX_FLAGS -fopenmp)

# SDL2 lib
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "C:/Users/tf_no/SDL2-devel-2.30.0-mingw/SDL2-2.30.0/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(untitled main.cpp
        utils/vizUtils.cpp
        utils/vizUtils.h
        algos/timSort.cpp
        algos/timSort.h
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

target_include_directories(${PROJECT_NAME} PRIVATE .)
