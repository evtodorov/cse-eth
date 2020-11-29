cmake_minimum_required(VERSION 3.0)

project("Random benchmark")


add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 11)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(main 	timer
							random)

							#make sure compiler uses -std=c++11


#useless install: everything in one place for easy removal
install(TARGETS main 
		DESTINATION ./install/bin)