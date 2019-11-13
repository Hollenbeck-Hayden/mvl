#include "tests.h"
#include "../src/mvl.h"
#include "test_suite.h"
#include <iostream>

namespace test_abstract_vector
{
	mvl::AbstractVector<int,2,3> make2x3A()
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

	mvl::AbstractVector<int,2,3> make2x3B()
	{
		mvl::AbstractVector<int,2,3> b;
		b(0,0) = 3;
		b(0,1) = -1;
		b(0,2) = 1;
		b(1,0) = 0;
		b(1,1) = 2;
		b(1,2) = -2;
		return b;
	}

	template<typename T, size_t M, size_t N>
	void checkEquals(mvl::AbstractVector<T,M,N> a, mvl::AbstractVector<T,M,N> b)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				testing::checkEquals(a(i,j), b(i,j));
	}

	void testConstructor()
	{
		mvl::AbstractVector<int,3,1> a;
		for(size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 1; j++)
				testing::checkEquals(a(i,j), 0);

		mvl::AbstractVector<int,2,5> b;
		for(size_t i = 0; i < 2; i++)
			for(size_t j = 0; j < 5; j++)
				testing::checkEquals(b(i,j), 0);
	}

	void testConstructorCopy()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,3> b(a);
		checkEquals(a,b);

		a(0,0) = 70;
		b(0,0) = -15;

		testing::checkEquals(a(0,0), 70);
		testing::checkEquals(b(0,0), -15);

		a = make2x3B();
		mvl::AbstractVector<int,2,3> c(a);
		checkEquals(a,c);

		a(0,0) = 40;
		c(0,0) = 10;
		
		testing::checkEquals(a(0,0), 40);
		testing::checkEquals(c(0,0), 10);
	}

	void testConstructorMove()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,3> b(std::move(a));

		checkEquals(b, make2x3A());
	}

	void testAssignmentCopy()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,3> b = a;
		checkEquals(a,b);

		a(0,0) = 70;
		b(0,0) = -15;

		testing::checkEquals(a(0,0), 70);
		testing::checkEquals(b(0,0), -15);

		a = make2x3B();
		mvl::AbstractVector<int,2,3> c = a;
		checkEquals(a,c);

		a(0,0) = 40;
		c(0,0) = 10;
		
		testing::checkEquals(a(0,0), 40);
		testing::checkEquals(c(0,0), 10);
	
	}

	void testAssignmentMove()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,3> b = std::move(a);

		checkEquals(b, make2x3A());
	}

	void testElementAccess()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		testing::checkEquals(a(0,0), 1);
		testing::checkEquals(a(0,1), 3);
		testing::checkEquals(a(0,2), 5);
		testing::checkEquals(a(1,0), -2);
		testing::checkEquals(a(1,1), -4);
		testing::checkEquals(a(1,2), -6);
	}

	void testElementAccessConst()
	{
		const mvl::AbstractVector<int,2,3> a = make2x3A();
		testing::checkEquals(a(0,0), 1);
		testing::checkEquals(a(0,1), 3);
		testing::checkEquals(a(0,2), 5);
		testing::checkEquals(a(1,0), -2);
		testing::checkEquals(a(1,1), -4);
		testing::checkEquals(a(1,2), -6);
	}

	void testGetRow()
	{
		const mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,1,3> b;

		mvl::AbstractVector<int,1,3> a_0 = a.getRow(0);
		b(0,0) = 1;
		b(0,1) = 3;
		b(0,2) = 5;
		checkEquals(a_0, b);

		mvl::AbstractVector<int,1,3> a_1 = a.getRow(1);
		b(0,0) = -2;
		b(0,1) = -4;
		b(0,2) = -6;
		checkEquals(a_1, b);
	}

	void testGetCol()
	{
		const mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,1> b;

		mvl::AbstractVector<int,2,1> a_0 = a.getCol(0);
		b(0,0) = 1;
		b(1,0) = -2;
		checkEquals(a_0, b);

		mvl::AbstractVector<int,2,1> a_1 = a.getCol(1);
		b(0,0) = 3;
		b(1,0) = -4;
		checkEquals(a_1, b);

		mvl::AbstractVector<int,2,1> a_2 = a.getCol(2);
		b(0,0) = 5;
		b(1,0) = -6;
		checkEquals(a_2, b);
	}

	void testSetRow()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,3> b;

		for (size_t i = 0; i < 2; i++)
			b.setRow(i, a.getRow(i));

		checkEquals(b,a);
	}

	void testSetCol()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		mvl::AbstractVector<int,2,3> b;

		for(size_t i = 0; i < 3; i++)
			b.setCol(i, a.getCol(i));

		checkEquals(b,a);
	}

	void testOperatorPE()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		const mvl::AbstractVector<int,2,3> b = make2x3B();
		mvl::AbstractVector<int,2,3> c;
		c(0,0) = 4;
		c(0,1) = 2;
		c(0,2) = 6;
		c(1,0) = -2;
		c(1,1) = -2;
		c(1,2) = -8;

		a += b;
		checkEquals(a, c);
	}

	void testOperatorME()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		const mvl::AbstractVector<int,2,3> b = make2x3B();
		mvl::AbstractVector<int,2,3> c;
		c(0,0) = -2;
		c(0,1) = 4;
		c(0,2) = 4;
		c(1,0) = -2;
		c(1,1) = -6;
		c(1,2) = -4;

		a -= b;
		checkEquals(a, c);
	}

	void testOperatorTE()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		int b = 3;
		mvl::AbstractVector<int,2,3> c;
		c(0,0) = 3;
		c(0,1) = 9;
		c(0,2) = 15;
		c(1,0) = -6;
		c(1,1) = -12;
		c(1,2) = -18;

		a *= b;
		checkEquals(a, c);
	}

	void testOperatorDE()
	{
		mvl::AbstractVector<int,2,3> a = make2x3A();
		a *= 12;

		int b = 3;
		mvl::AbstractVector<int,2,3> c;
		c(0,0) = 4;
		c(0,1) = 12;
		c(0,2) = 20;
		c(1,0) = -8;
		c(1,1) = -16;
		c(1,2) = -24;

		a /= b;
		checkEquals(a, c);	
	}

	void testOperatorEquals ()
	{
		const mvl::AbstractVector<int,2,3> a = make2x3A();
		const mvl::AbstractVector<int,2,3> b = make2x3A();
		const mvl::AbstractVector<int,2,3> c = make2x3B();

		testing::checkTrue(a == b);
		testing::checkTrue(b == a);
		testing::checkFalse(a == c);
		testing::checkFalse(c == b);
	}

	void testOperatorNotEquals ()
	{
		const mvl::AbstractVector<int,2,3> a = make2x3A();
		const mvl::AbstractVector<int,2,3> b = make2x3A();
		const mvl::AbstractVector<int,2,3> c = make2x3B();

		testing::checkFalse(a != b);
		testing::checkFalse(b != a);
		testing::checkTrue(a != c);
		testing::checkTrue(c != b);
	
	}

	void testOperatorAddition()
	{
		auto a = make2x3A();
		a += make2x3B();
		auto b = make2x3A() + make2x3B();

		checkEquals(b,a);
	}

	void testOperatorSubtraction()
	{
		auto a = make2x3A();
		a -= make2x3B();
		auto b = make2x3A() - make2x3B();

		checkEquals(b,a);
	}

	void testOperatorScalarMultiplication()
	{
		auto a = make2x3A();
		a *= 3;
		auto b = 3 * make2x3A();
		checkEquals(b,a);

		auto c = make2x3A() * 3;
		checkEquals(c,a);
	}

	void testOperatorScalarDivision()
	{
		auto a = make2x3A() * 4;
		auto temp = make2x3A() * 12;
		auto b = temp / 3;
		checkEquals(b,a);
	}

	void testOperatorMultiplication()
	{
		auto a = make2x3A();
		mvl::AbstractVector<int,3,2> b;
		b(0,0) = 3;
		b(0,1) = 1;
		b(1,0) = 0;
		b(1,1) = -1;
		b(2,0) = 2;
		b(2,1) = -3;
		mvl::AbstractVector<int,2,2> c = a * b;

		testing::checkEquals(c(0,0), 13);
		testing::checkEquals(c(0,1), -17);
		testing::checkEquals(c(1,0), -18);
		testing::checkEquals(c(1,1), 20);

		mvl::AbstractVector<int,3,3> d = b * a;
		testing::checkEquals(d(0,0), 1);
		testing::checkEquals(d(0,1), 5);
		testing::checkEquals(d(0,2), 9);
		testing::checkEquals(d(1,0), 2);
		testing::checkEquals(d(1,1), 4);
		testing::checkEquals(d(1,2), 6);
		testing::checkEquals(d(2,0), 8);
		testing::checkEquals(d(2,1), 18);
		testing::checkEquals(d(2,2), 28);
	}
};

void testAbstractVector(testing::Tester& t)
{
	t.addTest("Default constructor",	test_abstract_vector::testConstructor);
	t.addTest("Copy constructor",		test_abstract_vector::testConstructorCopy);
	t.addTest("Move constructor",		test_abstract_vector::testConstructorMove);
	t.addTest("Copy assignment",		test_abstract_vector::testAssignmentCopy);
	t.addTest("Move assignment",		test_abstract_vector::testAssignmentMove);
	t.addTest("Element access",		test_abstract_vector::testElementAccess);
	t.addTest("Const element access",	test_abstract_vector::testElementAccessConst);
	t.addTest("Get row",			test_abstract_vector::testGetRow);
	t.addTest("Set row",			test_abstract_vector::testSetRow);
	t.addTest("Get col",			test_abstract_vector::testGetCol);
	t.addTest("Set col",			test_abstract_vector::testSetCol);
	t.addTest("Operator +=",		test_abstract_vector::testOperatorPE);
	t.addTest("Operator -=",		test_abstract_vector::testOperatorME);
	t.addTest("Operator *=",		test_abstract_vector::testOperatorTE);
	t.addTest("Operator /=",		test_abstract_vector::testOperatorDE);
	t.addTest("Operator ==",		test_abstract_vector::testOperatorEquals);
	t.addTest("Operator !=",		test_abstract_vector::testOperatorNotEquals);
	t.addTest("Vector addition",		test_abstract_vector::testOperatorAddition);
	t.addTest("Vector subtraction",		test_abstract_vector::testOperatorSubtraction);
	t.addTest("Scalar multiplication",	test_abstract_vector::testOperatorScalarMultiplication);
	t.addTest("Scalar division",		test_abstract_vector::testOperatorScalarDivision);
	t.addTest("Matrix multiplication",	test_abstract_vector::testOperatorMultiplication);
}
