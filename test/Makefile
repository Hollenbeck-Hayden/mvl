all:
	g++ -o test test_suite.cpp test_all.cpp test_Matrix.cpp test_Vector.cpp

ogl: clean
	g++ -o ogl_test ogl_test.cpp 

clean:
	rm -rf test
	rm -rf ogl_test

again: clean all
