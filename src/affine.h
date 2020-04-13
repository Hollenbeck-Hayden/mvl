#pragma once

#include "mvl.h"

namespace aff
{
	template<typename T, size_t N> using HomMatrix = mvl::SMatrix<T,N+1>;

	// Elementary basis
	template<typename T, size_t N> mvl::Vector<T,N> basis_vector(size_t i);
	template<typename T, size_t N> mvl::Vector<T,N> x_axis();
	template<typename T, size_t N> mvl::Vector<T,N> y_axis();
	template<typename T, size_t N> mvl::Vector<T,N> z_axis();
	template<typename T, size_t N> mvl::Vector<T,N> w_axis();

	//// Affine Transformations
	template<typename T, size_t N> HomMatrix<T,N> identity();
	//template<typename T, size_t N> HomMatrix<T,N> translate(T t, size_t axis);
	//template<typename T, size_t N> HomMatrix<T,N> scale(T t, size_t axis);
	//template<typename T, size_t N> HomMatrix<T,N> shear(T t, size_t axis);
	//template<typename T, size_t N> HomMatrix<T,N> reflect(size_t axis);
	//
	template<typename T, size_t N> HomMatrix<T,N> translate(const mvl::Vector<T,N>& v);
	//template<typename T, size_t N> HomMatrix<T,N> scale(const Vector<T,N>& v);
	//template<typename T, size_t N> HomMatrix<T,N> shear(const Vector<T,N>& v);

	//// 2D Transformations
	//template<typename T> HomMatrix<T,2> translate(T x, T y);
	//template<typename T> HomMatrix<T,2> scale(T x, T y);
	//template<typename T> HomMatrix<T,2> shear(T x, T y);
	//template<typename T> HomMatrix<T,2> reflectX();
	//template<typename T> HomMatrix<T,2> reflectY();
	//template<typename T> HomMatrix<T,2> rotate(T t);

	//// 3D Transformations
	//template<typename T> HomMatrix<T,3> translate(T x, T y, T z);
	//template<typename T> HomMatrix<T,3> scale(T x, T y, T z);
	//template<typename T> HomMatrix<T,3> shear(T x, T y, T z);
	//template<typename T> HomMatrix<T,3> reflectX();
	//template<typename T> HomMatrix<T,3> reflectY();
	//template<typename T> HomMatrix<T,3> reflectZ();
	//template<typename T> HomMatrix<T,3> rotate(const Vector<T,3>& axis, T t);
	
	// View Matrix
	template<typename T> HomMatrix<T,3> lookTowards(const mvl::Vector<T,3>& camera, const mvl::Vector<T,3>& direction, const mvl::Vector<T,3>& up);
	template<typename T> HomMatrix<T,3> lookAt(const mvl::Vector<T,3>& camera, const mvl::Vector<T,3>& center, const mvl::Vector<T,3>& up);

	// Projection Matrix
	template<typename T> HomMatrix<T,3> orthographic(const mvl::Vector<T,3>& rtf, const mvl::Vector<T,3>& lbn);
	template<typename T> HomMatrix<T,3> perspective(T fovy, T aspect, T zNear, T zFar);
}

#include "affine.tpp"
