#include "mvl/mvl.h"
#include "test_suite.h"
#include "tests.h"
#include <iostream>

namespace test_matrix
{
	void intro() {}

	template<typename T, size_t M, size_t N>
	void checkEquals(const mvl::Matrix<T,M,N>& a, const mvl::Matrix<T,M,N>& b)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				testing::checkEquals(a(i,j), b(i,j));
	}

	mvl::Matrix<int, 3, 2> makeA()
	{
		mvl::Matrix<int,3,2> a;
		a(0,0) = 2;
		a(1,0) = -1;
		a(2,0) = 5;
		a(0,1) = -2;
		a(1,1) = 3;
		a(2,1) = 1;
		return a;
	}

	mvl::Matrix<int, 3, 2> makeB()
	{
		mvl::Matrix<int,3,2> b;
		b(0,0) = -1;
		b(1,0) = 0;
		b(2,0) = 2;
		b(0,1) = 1;
		b(1,1) = 3;
		b(2,1) = -2;
		return b;
	}

	void test_constructor()
	{
		mvl::Matrix<int, 3, 2> a;
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 2; j++)
				testing::checkEquals(a(i,j), 0);
	}

	void test_copy_constructor()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> b(a);
		checkEquals(makeA(), b);
		a(1,1) = 7;
		b(1,1) = -15;
		testing::checkEquals(a(1,1), 7);
		testing::checkEquals(b(1,1), -15);
	}

	void test_copy_assignment()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> b = a;
		checkEquals(makeA(), b);
		a(1,1) = 7;
		b(1,1) = -15;
		testing::checkEquals(a(1,1), 7);
		testing::checkEquals(b(1,1), -15);

	}

	void test_move_constructor()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> b(std::move(a));
		checkEquals(makeA(), b);
	}

	void test_move_assignment()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> b = std::move(a);
		checkEquals(makeA(), b);
	}

	void test_element_access()
	{
		mvl::Matrix<int,3,2> a = makeA();
		testing::checkEquals(a(0,0), 2);
		testing::checkEquals(a(1,0), -1);
		testing::checkEquals(a(2,0), 5);
		testing::checkEquals(a(0,1), -2);
		testing::checkEquals(a(1,1), 3);
		testing::checkEquals(a(2,1), 1);
	}

	void test_const_element_access()
	{
		const mvl::Matrix<int,3,2> a = makeA();
		testing::checkEquals(a(0,0), 2);
		testing::checkEquals(a(1,0), -1);
		testing::checkEquals(a(2,0), 5);
		testing::checkEquals(a(0,1), -2);
		testing::checkEquals(a(1,1), 3);
		testing::checkEquals(a(2,1), 1);
	}

	void test_single_element_access()
	{
		mvl::Matrix<int,3,2> a = makeA();
		testing::checkEquals(a[0], 2);
		testing::checkEquals(a[1], -1);
		testing::checkEquals(a[2], 5);
	}

	void test_const_single_element_access()
	{
		const mvl::Matrix<int,3,2> a = makeA();
		testing::checkEquals(a[0], 2);
		testing::checkEquals(a[1], -1);
		testing::checkEquals(a[2], 5);
	}

	void test_get_row()
	{
		mvl::Matrix<int,1,2> a = makeA().getRow(0);
		testing::checkEquals(a(0,0), 2);
		testing::checkEquals(a(0,1), -2);
		mvl::Matrix<int,1,2> b = makeA().getRow(1);
		testing::checkEquals(b(0,0), -1);
		testing::checkEquals(b(0,1), 3);
		mvl::Matrix<int,1,2> c = makeA().getRow(2);
		testing::checkEquals(c(0,0), 5);
		testing::checkEquals(c(0,1), 1);
	}

	void test_get_col()
	{
		mvl::Matrix<int,3,1> a = makeA().getCol(0);
		testing::checkEquals(a(0,0), 2);
		testing::checkEquals(a(1,0), -1);
		testing::checkEquals(a(2,0), 5);
		mvl::Matrix<int,3,1> b = makeA().getCol(1);
		testing::checkEquals(b(0,0), -2);
		testing::checkEquals(b(1,0), 3);
		testing::checkEquals(b(2,0), 1);
	}

	void test_set_row()
	{
		mvl::Matrix<int,3,2> b = makeA();

		mvl::Matrix<int,1,2> a;
		a(0,0) = -1;
		a(0,1) = 1;
		b.setRow(0, a);

		a(0,0) = 0;
		a(0,1) = 3;
		b.setRow(1, a);

		a(0,0) = 2;
		a(0,1) = -2;
		b.setRow(2, a);

		checkEquals(b, makeB());
	}

	void test_set_col()
	{
		mvl::Matrix<int,3,2> b = makeA();

		mvl::Matrix<int,3,1> a;
		a(0,0) = -1;
		a(1,0) = 0;
		a(2,0) = 2;
		b.setCol(0, a);

		a(0,0) = 1;
		a(1,0) = 3;
		a(2,0) = -2;
		b.setCol(1, a);

		checkEquals(b, makeB());
	}

	void test_add_equals()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> b = makeB();
		mvl::Matrix<int,3,2> c;
		c(0,0) = 1;
		c(1,0) = -1;
		c(2,0) = 7;
		c(0,1) = -1;
		c(1,1) = 6;
		c(2,1) = -1;
		a += b;
		checkEquals(c, a);
	}

	void test_minus_equals()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> b = makeB();
		mvl::Matrix<int,3,2> c;
		c(0,0) = 3;
		c(1,0) = -1;
		c(2,0) = 3;
		c(0,1) = -3;
		c(1,1) = 0;
		c(2,1) = 3;
		a -= b;
		checkEquals(c, a);
	}

	void test_times_equals()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> c;
		c(0,0) = 4;
		c(1,0) = -2;
		c(2,0) = 10;
		c(0,1) = -4;
		c(1,1) = 6;
		c(2,1) = 2;
		a *= 2;
		checkEquals(c, a);
	}

	void test_divide_equals()
	{
		mvl::Matrix<int,3,2> a = makeA();
		mvl::Matrix<int,3,2> c;
		c(0,0) = 4;
		c(1,0) = -2;
		c(2,0) = 10;
		c(0,1) = -4;
		c(1,1) = 6;
		c(2,1) = 2;
		a *= 12;
		a /= 6;
		checkEquals(c, a);	
	}

	void test_equals()
	{
		mvl::Matrix<int,3,2> a = makeA();
		testing::checkTrue(a == makeA());
		testing::checkFalse(a == makeB());
	}

	void test_not_equals()
	{
		mvl::Matrix<int,3,2> a = makeA();
		testing::checkTrue(a != makeB());
		testing::checkFalse(a != makeA());
	}

	void test_plus()
	{
		mvl::Matrix<int,3,2> c;
		c(0,0) = 1;
		c(1,0) = -1;
		c(2,0) = 7;
		c(0,1) = -1;
		c(1,1) = 6;
		c(2,1) = -1;
		mvl::Matrix<int,3,2> a = makeA() + makeB();
		checkEquals(c, a);
	}

	void test_minus()
	{
		mvl::Matrix<int,3,2> c;
		c(0,0) = 3;
		c(1,0) = -1;
		c(2,0) = 3;
		c(0,1) = -3;
		c(1,1) = 0;
		c(2,1) = 3;
		mvl::Matrix<int,3,2> a = makeA() - makeB();
		checkEquals(c, a);
	}

	void test_times()
	{
		mvl::Matrix<int,3,2> a = makeA() * 2;
		mvl::Matrix<int,3,2> b = 2 * makeA();
		mvl::Matrix<int,3,2> c;
		c(0,0) = 4;
		c(1,0) = -2;
		c(2,0) = 10;
		c(0,1) = -4;
		c(1,1) = 6;
		c(2,1) = 2;
		checkEquals(c, a);
		checkEquals(c, b);
	}

	void test_divides()
	{
		mvl::Matrix<int,3,2> a = makeA() * 12;
		mvl::Matrix<int,3,2> b = a / 6;
		mvl::Matrix<int,3,2> c;
		c(0,0) = 4;
		c(1,0) = -2;
		c(2,0) = 10;
		c(0,1) = -4;
		c(1,1) = 6;
		c(2,1) = 2;
		checkEquals(c, b);	
	}

	void test_matrix_mult()
	{
		mvl::Matrix<int,3,3> a;
		a(0,0) = -4;
		a(1,0) = 4;
		a(2,0) = -4;
		a(0,1) = -6;
		a(1,1) = 9;
		a(2,1) = 3;
		a(0,2) = 8;
		a(1,2) = -8;
		a(2,2) = 8;
		checkEquals(a, makeA() * transpose(makeB()));

		mvl::Matrix<int,2,2> b;
		b(0,0) = 8;
		b(0,1) = 4;
		b(1,0) = -11;
		b(1,1) = 5;
		checkEquals(b, transpose(makeB()) * makeA());
	}

	void test_transpose()
	{
		mvl::Matrix<int,2,3> a = transpose(makeA());
		mvl::Matrix<int,2,3> b;
		b(0,0) = 2;
		b(1,0) = -2;
		b(0,1) = -1;
		b(1,1) = 3;
		b(0,2) = 5;
		b(1,2) = 1;
		checkEquals(a,b);
	}
}

void testMatrix(testing::Tester& t)
{
	t.addTest("Matrix",			test_matrix::intro				);
	t.addTest("Copy Constructor",		test_matrix::test_copy_constructor		);
	t.addTest("Move Constructor",		test_matrix::test_move_constructor		);
	t.addTest("Copy Assignment",		test_matrix::test_copy_assignment		);
	t.addTest("Move Assignment",		test_matrix::test_move_assignment		);
	t.addTest("Element Access",		test_matrix::test_element_access		);
	t.addTest("Const Element Access",	test_matrix::test_const_element_access		);
	t.addTest("Single Element",		test_matrix::test_single_element_access		);
	t.addTest("Const Single Element",	test_matrix::test_const_single_element_access	);
	t.addTest("Get Row",			test_matrix::test_get_row			);
	t.addTest("Get Col",			test_matrix::test_get_col			);
	t.addTest("Set Row",			test_matrix::test_set_row			);
	t.addTest("Set Col",			test_matrix::test_set_col			);
	t.addTest("+=",				test_matrix::test_add_equals			);
	t.addTest("-=",				test_matrix::test_minus_equals			);
	t.addTest("*=",				test_matrix::test_times_equals			);
	t.addTest("/=",				test_matrix::test_divide_equals			);
	t.addTest("==",				test_matrix::test_equals			);
	t.addTest("!=",				test_matrix::test_not_equals			);
	t.addTest("+",				test_matrix::test_plus				);
	t.addTest("-",				test_matrix::test_minus				);
	t.addTest("*",				test_matrix::test_times				);
	t.addTest("/",				test_matrix::test_divides			);
	t.addTest("* Matrix",			test_matrix::test_matrix_mult			);
	t.addTest("Transpose",			test_matrix::test_transpose			);
}
