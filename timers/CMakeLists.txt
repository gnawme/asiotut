cmake_minimum_required(VERSION 3.5)
project(asiotimers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -DASIO_STANDALONE")
find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(
    SOURCE_FILES
    AsioTimers.cpp
    AsioTimers.h
)

add_executable(asiotimers ${SOURCE_FILES})

target_link_libraries(asiotimers -lgtest pthread)
