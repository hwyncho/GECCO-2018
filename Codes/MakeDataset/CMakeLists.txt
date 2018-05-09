cmake_minimum_required(VERSION 3.10.0)
project(MakeDataset VERSION 0.0.0)

set(CMAKE_C_STANDARD 11)
set(SOURCES main.c OneMax.c OneMax.h NK.c NK.h)

add_executable(MakeDataset ${SOURCES})

add_subdirectory(libGA)
target_link_libraries(MakeDataset m GA)
