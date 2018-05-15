cmake_minimum_required(VERSION 3.10.0)
project(FindOptimal VERSION 0.0.0)

set(CMAKE_C_STANDARD 11)
set(SOURCES main.c)

add_executable(FindOptimal ${SOURCES})

add_subdirectory(libGA)
target_link_libraries(FindOptimal m GA)
