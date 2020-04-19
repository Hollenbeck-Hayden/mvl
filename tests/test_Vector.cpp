#include "mvl/mvl.h"
#include "test_suite.h"
#include <cmath>

namespace test_vector
{
	void intro() {}

	mvl::Vector<int,3> makeA()
	{
		mvl::Vector<int,3> a;
		a[0] = 1;
		a[1] = 4;
		a[2] = -3;
		return a;
	}

	mvl::Vector<int,3> makeB()
	{
		mvl::Vector<int,3> b;
		b[0] = 2;
		b[1] = -1;
		b[2] = 2;
		return b;
	}

	mvl::Vector<double,3> makeC()
	{
		mvl::Vector<double,3> c;
		c[0] = 1;
		c[1] = 4;
		c[2] = -3;
		return c;

	}

	mvl::Vector<double,3> makeD()
	{
		mvl::Vector<double,3> d;
		d[0] = 2;
		d[1] = -1;
		d[2] = 2;
		return d;
	}

	template<typename T, size_t N>
	void checkVectors(const mvl::Vector<T,N>& a, const mvl::Vector<T,N>& b)
	{
		for (size_t i = 0; i < N; i++)
			testing::checkEquals(a[i], b[i]);
	}

	template<typename T, size_t N>
	void checkMatrices(const mvl::Matrix<T,N,1>& a, const mvl::Matrix<T,N,1>& b)
	{
		for (size_t i = 0; i < N; i++)
			testing::checkEquals(a(i,0), b(i,0));
	}

	void vector_to_matrix()
	{
		mvl::Vector<int,3> a = makeA();

		mvl::Matrix<int,3,1> b = a;
		testing::checkEquals(a[0], b(0,0));
		testing::checkEquals(a[1], b(1,0));
		testing::checkEquals(a[2], b(2,0));

		checkVectors(a, b);
		checkMatrices(a, b);
	}

	void dot_product()
	{
		mvl::Vector<int,3> a = makeA();
		mvl::Vector<int,3> b = makeB();

		auto c = dot(a,b);

		testing::checkEquals(-8, c);
	}

	void norm()
	{
		mvl::Vector<double,3> c = makeC();
		testing::checkEquals(sqrt(26), mvl::norm(c));
	}

	void norm2()
	{
		mvl::Vector<double,3> c = makeC();
		testing::checkEquals(26.0, mvl::norm2(c));
	}

	void normalize()
	{
		mvl::Vector<double,3> c = makeC();
		mvl::normalize(c);
		testing::checkEquals(1.0 / sqrt(26), c[0]);
		testing::checkEquals(4.0 / sqrt(26), c[1]);
		testing::checkEquals(-3.0 / sqrt(26), c[2]);
	}

	void normalized()
	{
		mvl::Vector<double,3> c = mvl::normalize(makeC());
		mvl::Vector<double,3> d = makeC();
		d = mvl::normalize(d);
		checkVectors(d, c);
	}

	void cross()
	{
		mvl::Vector<double,3> c = makeC();
		mvl::Vector<double,3> d = makeD();
		mvl::Vector<double,3> e = mvl::cross(c,d);

		testing::checkEquals( 5.0, e[0]);
		testing::checkEquals(-8.0, e[1]);
		testing::checkEquals(-9.0, e[2]);
	}

	void is_orthogonal()
	{
		mvl::Vector<double,3> c = makeC();
		mvl::Vector<double,3> d = makeD();
		mvl::Vector<double,3> e = mvl::cross(c,d);

		testing::checkTrue(mvl::is_orthogonal(c,e));
		testing::checkTrue(mvl::is_orthogonal(d,e));
		testing::checkFalse(mvl::is_orthogonal(c,d));
	}
}

int main(void)
{
	testing::Tester t;

	t.addTest("Vector", test_vector::intro);
	t.addTest("Vector To Matrix", test_vector::vector_to_matrix);
	t.addTest("Dot Product", test_vector::dot_product);
	t.addTest("Norm", test_vector::norm);
	t.addTest("Norm Squared", test_vector::norm2);
	t.addTest("Normalize", test_vector::normalize);
	t.addTest("Normalized", test_vector::normalized);
	t.addTest("Cross", test_vector::cross);
	t.addTest("Is Orthogonal", test_vector::is_orthogonal);

	t.test();

	return 0;
}
