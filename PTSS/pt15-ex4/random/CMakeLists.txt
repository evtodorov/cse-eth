cmake_minimum_required(VERSION 3.0)

project("Random benchmark")


add_library(random STATIC random.cpp)

#make sure compiler uses -std=c++11
set_property(TARGET random PROPERTY CXX_STANDARD 11)
set_property(TARGET random PROPERTY CXX_STANDARD_REQUIRED ON)

#useless install: everything in one place for easy removal
install(TARGETS 	random 
		DESTINATION ./install/lib)
install(FILES 		random.hpp 
		DESTINATION ./install/include)