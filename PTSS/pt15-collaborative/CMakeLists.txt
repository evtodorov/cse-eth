cmake_minimum_required(VERSION 2.8)

project(Simpsons integration)


# Create library
add_library(integrate STATIC simpson_integral.cpp)

# Create executable
add_executable(simpson_integral main.cpp)
target_link_libraries(simpson_integral integrate)

# Install library
install(TARGETS integrate
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(FILES simpson_integral.hpp DESTINATION include)

# Install executable
install(TARGETS simpson_integral DESTINATION bin)