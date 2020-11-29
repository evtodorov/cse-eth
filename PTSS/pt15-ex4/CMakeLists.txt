cmake_minimum_required(VERSION 3.0)

project("Random benchmark")

add_subdirectory(timer		./timer)
add_subdirectory(random		./random)
link_directories(./timer ./random)
include_directories(./timer ./random)
add_subdirectory(benchmark)


