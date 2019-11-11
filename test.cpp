#include <iostream>
#include "mvl.h"
#include <vector>

int main( void )
{
	mvl::Vector<int, 2> v;
	mvl::Vector<int, 2> w;
	mvl::Matrix<int, 2, 2> m;
	mvl::Matrix<int, 2, 2> n;

	v(0,0) = 3;
	v(1,0) = -2;

	w(0,0) = -1;
	w(1,0) = 7;

	m(0,0) = 1;
	m(1,0) = 3;
	m(0,1) = -1;
	m(1,1) = -2;

	n(0,0) = -4;
	n(1,0) = 1;
	n(0,1) = 2;
	n(1,1) = 0;

	mvl::Vector<int, 2> u = m * v;

	std::cout << "m: " << std::endl;
	m.print();

	std::cout << "n: " << std::endl;
	n.print();

	std::cout << "v: " << std::endl;
	v.print();

	std::cout << "u: " << std::endl;
	u.print();

	std::cout << "w: " << std::endl;
	w.print();

	std::cout << "w + v: " << std::endl;
	(w + v).print();

	return 0;
}
