#include "tests.h"
#include "../src/mvl.h"
#include "test_suite.h"
#include <iostream>

namespace test_matrix
{
	mvl::Matrix<int,2,3> make2x3A()
	{
		mvl::AbstractVector<int,2,3> a;
		a(0,0) = 1;
		a(0,1) = 3;
		a(0,2) = 5;
		a(1,0) = -2;
		a(1,1) = -4;
		a(1,2) = -6;
		return a;
	}

	mvl::Matrix<int,2,3> make2x3B()
	{
		mvl::Matrix<int,2,3> b;
		b(0,0) = 3;
		b(0,1) = -1;
		b(0,2) = 1;
		b(1,0) = 0;
		b(1,1) = 2;
		b(1,2) = -2;
		return b;
	}

	template<typename T, size_t M, size_t N>
	void checkEquals(mvl::Matrix<T,M,N> a, mvl::Matrix<T,M,N> b)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				testing::checkEquals(a(i,j), b(i,j));
	}

	void testConstructor()
	{
		mvl::Matrix<int,2,3> a;
		for (size_t i = 0; i < 2; i++)
			for (size_t j = 0; j < 3; j++)
				testing::checkEquals(a(i,j), 0);
	}

	void testConstructorCopy()
	{
		mvl::Matrix<int,2,3> a = make2x3A();
		mvl::Matrix<int,2,3> b(a);
		checkEquals(a,b);

		a(0,0) = 70;
		b(0,0) = -15;

		testing::checkEquals(a(0,0), 70);
		testing::checkEquals(b(0,0), -15);

		mvl::AbstractVector<int,2,3> c = make2x3B();
		mvl::Matrix<int,2,3> d(c);
		checkEquals(mvl::Matrix<int,2,3>(c),d);

		a(0,0) = 40;
		c(0,0) = 10;
		
		testing::checkEquals(a(0,0), 40);
		testing::checkEquals(c(0,0), 10);
	}

	void testConstructorMove()
	{
		mvl::Matrix<int,2,3> a = make2x3A();
		mvl::Matrix<int,2,3> b(std::move(a));

		checkEquals(b, make2x3A());
	}

	void testAssignmentCopy()
	{
		mvl::Matrix<int,2,3> a = make2x3A();
		mvl::Matrix<int,2,3> b = a;
		checkEquals(a,b);

		a(0,0) = 70;
		b(0,0) = -15;

		testing::checkEquals(a(0,0), 70);
		testing::checkEquals(b(0,0), -15);
	}

	void testAssignmentMove()
	{
		testing::failUnimplemented();
	}

	void testOperatorAdd()
	{
		testing::failUnimplemented();
	}

	void testOperatorMinus()
	{
		testing::failUnimplemented();
	}

	void testOperatorScalarMultiply()
	{
		testing::failUnimplemented();
	}

	void testOperatorScalarDivide()
	{
		testing::failUnimplemented();
	}

	void testOperatorMultiply()
	{
		testing::failUnimplemented();
	}
};

void testMatrix(testing::Tester& t)
{
	t.addTest("Default constructor", test_matrix::testConstructor);
	t.addTest("Copy constructor", test_matrix::testConstructorCopy);
	t.addTest("Move constructor", test_matrix::testConstructorMove);
	t.addTest("Copy assignment", test_matrix::testAssignmentCopy);
	t.addTest("Move assignment", test_matrix::testAssignmentMove);
	t.addTest("Operator +", test_matrix::testOperatorAdd);
	t.addTest("Operator -", test_matrix::testOperatorMinus);
	t.addTest("Operator scalar *", test_matrix::testOperatorScalarMultiply);
	t.addTest("Operator scalar /", test_matrix::testOperatorScalarDivide);
	t.addTest("Operator *", test_matrix::testOperatorMultiply);
}
