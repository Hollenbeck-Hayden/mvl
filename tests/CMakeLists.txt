cmake_minimum_required(VERSION 3.5)

set(sources
	test_suite.cpp
	test_all.cpp
	test_Matrix.cpp
	test_Vector.cpp
)

add_executable(mvl-test ${sources})
target_link_libraries(mvl-test PUBLIC mvl)

add_test(NAME TestAll COMMAND mvl-test)
