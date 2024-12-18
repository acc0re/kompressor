cmake_minimum_required(VERSION 3.10)
project(kompressor C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

include_directories(include)

add_subdirectory(snappy)

add_executable(kompressor main.c
        include/kompressor.h
        src/kompressor.c)

target_link_libraries(kompressor PRIVATE snappy)
