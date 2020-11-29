cmake_minimum_required(VERSION 3.0)

project("Random benchmark")


add_library(timer STATIC timer.cpp)

#make sure compiler uses -std=c++11
set_property(TARGET timer PROPERTY CXX_STANDARD 11)
set_property(TARGET timer PROPERTY CXX_STANDARD_REQUIRED ON)

#useless install: everything in one place for easy removal
install(TARGETS 	timer 
		DESTINATION ./install/lib)
install(FILES 	timer.hpp 
		DESTINATION ./install/include)