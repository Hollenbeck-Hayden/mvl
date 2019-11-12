#include "../src/mvl.h"
#include "test_suite.h"
#include <iostream>
#include "tests.h"


template<typename T, size_t M, size_t N>
void testMatch(const mvl::DataMatrix<T,M,N>& m, T t[M][N])
{
	for (size_t i = 0; i < M; i++)
		for (size_t j = 0; j < N; j++)
			testing::checkEquals(m(i,j), t[i][j]);
}

template<typename T, size_t M, size_t N>
void testMatch(const mvl::DataMatrix<T,M,N>& m, const mvl::DataMatrix<T,M,N>& n)
{
	for (size_t i = 0; i < M; i++)
		for (size_t j = 0; j < N; j++)
			testing::checkEquals(m(i,j), n(i,j));
}

void testConstructor()
{
	std::cout << "Empty 3x3 data matrix: ";
	mvl::DataMatrix<int, 3, 3> a;
	int a_arr[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
	testMatch(a, a_arr);
	std::cout << "Successful" << std::endl;

	std::cout << "Empty 5x1 data matrix: ";
	mvl::DataMatrix<int, 5, 1> b;
	int b_arr[5][1] = {{0},{0},{0},{0},{0}};
	testMatch(b, b_arr);
	std::cout << "Successful" << std::endl;

	std::cout << "Empty 1x5 data matrix: ";
	mvl::DataMatrix<int, 1, 5> c;
	int c_arr[1][5] = {{0,0,0,0,0}};
	testMatch(c, c_arr);
	std::cout << "Successful" << std::endl;
}

void testConstructorCopy()
{
	std::cout << "3x3 matrix: ";
	mvl::DataMatrix<int, 3, 3> a;
	a(0,0) = 1;
	a(1,0) = 2;
	a(2,0) = -3;
	a(0,1) = 3;
	a(1,1) = 1;
	a(2,1) = 5;
	a(0,2) = -1;
	a(1,2) = 0;
	a(2,2) = -7;
	mvl::DataMatrix<int,3,3> b(a);
	testMatch(a, b);
	std::cout << "Values match... ";
	b(1,1) = 5;
	testing::checkEquals(b(1,1), 5);
	testing::checkEquals(a(1,1), 1);
	std::cout << "Copy successful" << std::endl;
}

void testAssignmentCopy()
{
	std::cout << "3x3 matrix: ";
	mvl::DataMatrix<int, 3, 3> a;
	a(0,0) = 1;
	a(1,0) = 2;
	a(2,0) = -3;
	a(0,1) = 3;
	a(1,1) = 1;
	a(2,1) = 5;
	a(0,2) = -1;
	a(1,2) = 0;
	a(2,2) = -7;
	mvl::DataMatrix<int,3,3> b = a;
	testMatch(a, b);
	std::cout << "Values match... ";
	b(1,1) = 5;
	testing::checkEquals(b(1,1), 5);
	testing::checkEquals(a(1,1), 1);
	std::cout << "Copy successful" << std::endl;
}

void testOperatorAccess()
{
	std::cout << "2x5 matrix: ";
	mvl::DataMatrix<int,2,5> a;
	for (size_t i = 0; i < 2 * 5; i++)
		a(i / 5, i % 5) = i;
	for (size_t i = 0; i < 2 * 5; i++)
		testing::checkEquals(a(i / 5, i % 5), (int) i);
	std::cout << "Successful" << std::endl;

	std::cout << "4x3 matrix: ";
	mvl::DataMatrix<int,4,3> b;
	for (size_t i = 0; i < 4 * 3; i++)
		b(i / 3, i % 3) = i;
	for (size_t i = 0; i < 4 * 3; i++)
		testing::checkEquals(b(i / 3, i % 3), (int) i);
	std::cout << "Successful" << std::endl;
}

void testOperatorAccessConst()
{
	std::cout << "2x5 matrix: ";
	mvl::DataMatrix<int,2,5> a;
	for (size_t i = 0; i < 2 * 5; i++)
		a(i / 5, i % 5) = i;
	for (size_t i = 0; i < 2 * 5; i++)
		testing::checkEquals(a(i / 5, i % 5), (int) i);
	std::cout << "Successful" << std::endl;

	std::cout << "4x3 matrix: ";
	mvl::DataMatrix<int,4,3> b;
	for (size_t i = 0; i < 4 * 3; i++)
		b(i / 3, i % 3) = i;
	for (size_t i = 0; i < 4 * 3; i++)
		testing::checkEquals(b(i / 3, i % 3), (int) i);
	std::cout << "Successful" << std::endl;
}

void testDataMatrix(testing::Tester& t)
{
	t.addTest("Empty constructor", testConstructor);
	t.addTest("Copy constructor", testConstructorCopy);
	t.addTest("Copy assignment", testAssignmentCopy);
	t.addTest("Access operator", testOperatorAccess);
	t.addTest("Constant access operator", testOperatorAccessConst);
}
