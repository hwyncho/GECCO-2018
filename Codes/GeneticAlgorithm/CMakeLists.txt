cmake_minimum_required(VERSION 3.10.0)
project(libGA VERSION 0.0.0)

set(CMAKE_C_STANDARD 11)
set(SOURCES Chromosome.c Chromosome.h GA.c GA.h operators/Selection.c operators/Selection.h operators/Crossover.c operators/Crossover.h operators/Mutation.c operators/Mutation.h operators/Replacement.c operators/Replacement.h)

add_library(GA ${SOURCES})
