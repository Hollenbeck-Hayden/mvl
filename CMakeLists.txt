cmake_minimum_required(VERSION 3.17)
project(mvl VERSION 0.1.0 
	DESCRIPTION "Mathematical Vector Library"
	LANGUAGES CXX)

add_library(mvl INTERFACE)
target_include_directories(mvl INTERFACE include)
target_compile_features(mvl INTERFACE cxx_std_17)
