#pragma once

#include "mvl/mvl.h"
#include <cmath>

namespace aff
{
	template<typename T, size_t N> using HomMatrix = mvl::SMatrix<T,N+1>;

	// Elementary basis
	template<typename T, size_t N>
	mvl::Vector<T,N> basis_vector(size_t i)
	{
		mvl::Vector<T,N> v;
		v[i] = 1;
		return v;
	}

	template<typename T, size_t N> mvl::Vector<T,N> x_axis() { return basis_vector<T,N>(0); }
	template<typename T, size_t N> mvl::Vector<T,N> y_axis() { return basis_vector<T,N>(1); }
	template<typename T, size_t N> mvl::Vector<T,N> z_axis() { return basis_vector<T,N>(2); }
	template<typename T, size_t N> mvl::Vector<T,N> w_axis() { return basis_vector<T,N>(3); }

	//// Affine Transformations
	template<typename T, size_t N>
	HomMatrix<T,N> identity()
	{
		HomMatrix<T,N> m;
		for (size_t i = 0; i < N+1; i++)
			m(i,i) = 1;
		return m;
	}

	//template<typename T, size_t N> HomMatrix<T,N> translate(T t, size_t axis);
	//template<typename T, size_t N> HomMatrix<T,N> scale(T t, size_t axis);
	//template<typename T, size_t N> HomMatrix<T,N> shear(T t, size_t axis);
	//template<typename T, size_t N> HomMatrix<T,N> reflect(size_t axis);
	
	template<typename T, size_t N>
	HomMatrix<T,N> translate(const mvl::Vector<T,N>& v)
	{
		HomMatrix<T,N> mat = identity<T,N>();
		for (size_t i = 0; i < N; i++)
			mat(i,N) = v[i];
		return mat;
	}

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
	template<typename T>
	HomMatrix<T,3> lookTowards(const mvl::Vector<T,3>& camera, const mvl::Vector<T,3>& direction, const mvl::Vector<T,3>& up)
	{
		// Determine camera basis vectors
		auto camera_z = mvl::normalize(direction);
		auto camera_y = mvl::normalize(up);
		auto camera_x = mvl::cross(camera_z, camera_y);
		camera_y = mvl::cross(camera_x, camera_z);

		HomMatrix<T,3> mat;
		for (size_t i = 0; i < 3; i++)
		{
			// Change of basis from model to camera basis
			mat(0,i) = camera_x[i];
			mat(1,i) = camera_y[i];
			mat(2,i) = -camera_z[i];
		}

		// Homogeneous coordinate
		mat(3,3) = 1;
		
		return mat * translate<T,3>(-camera);
	}

	template<typename T>
	HomMatrix<T,3> lookAt(const mvl::Vector<T,3>& camera, const mvl::Vector<T,3>& center, const mvl::Vector<T,3>& up)
	{
		return lookTowards(camera, center - camera, up);
	}

	// Projection Matrix
	template<typename T>
	HomMatrix<T,3> orthographic(const mvl::Vector<T,3>& rtf, const mvl::Vector<T,3>& lbn)
	{
		HomMatrix<T,3> mat;

		for (size_t i = 0; i < 3; i++)
		{
			mat(i,i) = 2 / (rtf[i] - lbn[i]);
			mat(i,3) = (rtf[i] + lbn[i]) / (lbn[i] - rtf[i]);
		}

		mat(2,2) = -mat(2,2);
		mat(3,3) = 1;
		
		return mat;
	}

	template<typename T>
	HomMatrix<T,3> frustum(const mvl::Vector<T,2>& lr, const mvl::Vector<T,2>& bt, const mvl::Vector<T,2>& nf)
	{
		HomMatrix<T,3> mat;
		T rl_diff = lr[1] - lr[0];
		T tb_diff = bt[1] - bt[0];
		T fn_diff = nf[1] - nf[0];

		mat(0,0) = 2 * nf[0] / rl_diff;
		mat(0,1) = 0;
		mat(0,2) = 0;
		mat(0,3) = 0;

		mat(1,0) = 0;
		mat(1,1) = 2 * nf[0] / tb_diff;
		mat(1,2) = 0;
		mat(1,3) = 0;

		mat(2,0) = (lr[0] + lr[1]) / rl_diff;
		mat(2,1) = (bt[0] + bt[1]) / tb_diff;
		mat(2,2) = -(nf[0] + nf[1]) / fn_diff;
		mat(2,3) = -1;

		mat(3,0) = 0;
		mat(3,1) = 0;
		mat(3,2) = -2 * nf[0] * nf[1] / fn_diff;
		mat(3,3) = 0;

		return mvl::transpose(mat);
	}

	template<typename T>
	HomMatrix<T,3> perspective(T fovy, T aspect, T zNear, T zFar)
	{
		T top = tan(fovy / 2.0) * zNear;
		T bottom = -top;
		T right = top * aspect;
		T left = bottom * aspect;

		return frustum(mvl::Vector<T,2>{left, right}, mvl::Vector<T,2>{bottom, top}, mvl::Vector<T,2>{zNear, zFar});
	}
}
