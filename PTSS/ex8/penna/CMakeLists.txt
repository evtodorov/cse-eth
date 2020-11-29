cmake_minimum_required(VERSION 2.8)

project("Penna")

set(CMAKE_CXX_FLAGS "-std=c++11")

add_library(Penna STATIC genome.cpp fish.cpp)

add_executable(genome-test genome-test.cpp)
target_link_libraries(genome-test Penna)

add_executable(fish-test fish-test.cpp)
target_link_libraries(fish-test Penna)


