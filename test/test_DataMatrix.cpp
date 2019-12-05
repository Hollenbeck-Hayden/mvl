#include "../src/mvl.h"
#include "test_suite.h"
#include <iostream>
#include "tests.h"

namespace test_data_matrix
{
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

	void intro()
	{
	}

	void testConstructor()
	{
		mvl::DataMatrix<int, 3, 3> a;
		int a_arr[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
		testMatch(a, a_arr);

		mvl::DataMatrix<int, 5, 1> b;
		int b_arr[5][1] = {{0},{0},{0},{0},{0}};
		testMatch(b, b_arr);

		mvl::DataMatrix<int, 1, 5> c;
		int c_arr[1][5] = {{0,0,0,0,0}};
		testMatch(c, c_arr);
	}

	void testConstructorCopy()
	{
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
		b(1,1) = 5;
		testing::checkEquals(b(1,1), 5);
		testing::checkEquals(a(1,1), 1);
	}

	void testAssignmentCopy()
	{
		mvl::DataMatrix<int, 3, 3> a; a(0,0) = 1; a(1,0) = 2;
		a(2,0) = -3;
		a(0,1) = 3;
		a(1,1) = 1;
		a(2,1) = 5;
		a(0,2) = -1;
		a(1,2) = 0;
		a(2,2) = -7;
		mvl::DataMatrix<int,3,3> b = a;
		testMatch(a, b);
		b(1,1) = 5;
		testing::checkEquals(b(1,1), 5);
		testing::checkEquals(a(1,1), 1);
	}

	void testOperatorAccess()
	{
		mvl::DataMatrix<int,2,5> a;
		for (size_t i = 0; i < 2 * 5; i++)
			a(i / 5, i % 5) = i;
		for (size_t i = 0; i < 2 * 5; i++)
			testing::checkEquals(a(i / 5, i % 5), (int) i);

		mvl::DataMatrix<int,4,3> b;
		for (size_t i = 0; i < 4 * 3; i++)
			b(i / 3, i % 3) = i;
		for (size_t i = 0; i < 4 * 3; i++)
			testing::checkEquals(b(i / 3, i % 3), (int) i);
	}

	void testOperatorAccessConst()
	{
		mvl::DataMatrix<int,2,5> a;
		for (size_t i = 0; i < 2 * 5; i++)
			a(i / 5, i % 5) = i;
		for (size_t i = 0; i < 2 * 5; i++)
			testing::checkEquals(a(i / 5, i % 5), (int) i);

		mvl::DataMatrix<int,4,3> b;
		for (size_t i = 0; i < 4 * 3; i++)
			b(i / 3, i % 3) = i;
		for (size_t i = 0; i < 4 * 3; i++)
			testing::checkEquals(b(i / 3, i % 3), (int) i);
	}
};

namespace test_data_vector
{
	template<typename T, size_t N>
	void testMatch(const mvl::DataMatrix<T,N,1>& m, T t[N])
	{
		for (size_t i = 0; i < N; i++)
			testing::checkEquals(m(i,0), t[i]);
	}

	template<typename T, size_t N>
	void testMatch(const mvl::DataMatrix<T,N,1>& m, const mvl::DataMatrix<T,N,1>& n)
	{
		for (size_t i = 0; i < N; i++)
			testing::checkEquals(m(i,0), n(i,0));
	}

	void intro()
	{
	}

	void testConstructor()
	{
		mvl::DataMatrix<int, 3, 1> a;
		int a_arr[3] = {0,0,0};
		testMatch(a, a_arr);
	}

	void testConstructorCopy()
	{
		mvl::DataMatrix<int, 3, 1> a;
		a(0,0) = 1;
		a(1,0) = 2;
		a(2,0) = -3;
		mvl::DataMatrix<int, 3, 1> b(a);
		testMatch(a, b);
		b(1,0) = 5;
		testing::checkEquals(b(1,0), 5);
		testing::checkEquals(a(1,0), 2);

		mvl::DataMatrix<int,3,1> c(a);
		testMatch(a, c);
		c(1,0) = 7;
		testing::checkEquals(c(1,0), 7);
		testing::checkEquals(a(1,0), 2);
	}

	void testAssignmentCopy()
	{
		mvl::DataMatrix<int, 3, 1> a;
		a(0,0) = 3;
		a(1,0) = 1;
		a(2,0) = 5;
		mvl::DataMatrix<int, 3, 1> b = a;
		testMatch(a, b);
		b(1,0) = 5;
		testing::checkEquals(b(1,0), 5);
		testing::checkEquals(a(1,0), 1);

		mvl::DataMatrix<int,3,1> c = a;
		testMatch(a, c);
		c(1,0) = 7;
		testing::checkEquals(c(1,0), 7);
		testing::checkEquals(a(1,0), 1);
	}

	void testOperatorAccess()
	{
		mvl::DataMatrix<int,5,1> a;
		for (size_t i = 0; i < 5; i++)
			a(i, 0) = i;
		for (size_t i = 0; i < 5; i++)
			testing::checkEquals(a(i, 0), (int) i);
	}

	void testOperatorAccessConst()
	{
		mvl::DataMatrix<int,5,1> a;
		for (size_t i = 0; i < 5; i++)
			a(i, 0) = i;

		const mvl::DataMatrix<int,5,1> b = a;
		for (size_t i = 0; i < 5; i++)
			testing::checkEquals(b(i, 0), (int) i);
	}
};

void testDataMatrix(testing::Tester& t)
{
	t.addTest("Data Matrix", 		test_data_matrix::intro);
	t.addTest("Empty constructor",		test_data_matrix::testConstructor);
	t.addTest("Copy constructor",		test_data_matrix::testConstructorCopy);
	t.addTest("Copy assignment",		test_data_matrix::testAssignmentCopy);
	t.addTest("Access operator",		test_data_matrix::testOperatorAccess);
	t.addTest("Constant access operator",	test_data_matrix::testOperatorAccessConst);

	t.addTest("Data Vector", 		test_data_vector::intro);
	t.addTest("Empty constructor",		test_data_vector::testConstructor);
	t.addTest("Copy constructor",		test_data_vector::testConstructorCopy);
	t.addTest("Copy assignment",		test_data_vector::testAssignmentCopy);
	t.addTest("Access operator",		test_data_vector::testOperatorAccess);
	t.addTest("Constant access operator",	test_data_vector::testOperatorAccessConst);
}
