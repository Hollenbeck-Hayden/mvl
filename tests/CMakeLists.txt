cmake_minimum_required(VERSION 3.5)


# Unit test matrix
add_executable(mvl-test-matrix)
target_link_libraries(mvl-test-matrix PRIVATE mvl)
target_sources(mvl-test-matrix
	PRIVATE
		test_Matrix.cpp
		test_suite.cpp
)

# Unit test vector
add_executable(mvl-test-vector)
target_link_libraries(mvl-test-vector PRIVATE mvl)
target_sources(mvl-test-vector
	PRIVATE
		test_Vector.cpp
		test_suite.cpp
)


# Add unit tests
add_test(NAME MVLTestMatrix COMMAND mvl-test-matrix)
add_test(NAME MVLTestVector COMMAND mvl-test-vector)
