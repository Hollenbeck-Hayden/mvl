#include <cmath>
#include <iostream>
#include <iomanip>

namespace aff
{
	// Basis functions
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

	// Affine transformations
	template<typename T, size_t N>
	HomMatrix<T,N> identity()
	{
		HomMatrix<T,N> m;
		for (size_t i = 0; i < N+1; i++)
			m(i,i) = 1;
		return m;
	}

	template<typename T, size_t N>
	HomMatrix<T,N> translate(const mvl::Vector<T,N>& v)
	{
		HomMatrix<T,N> mat = identity<T,N>();
		for (size_t i = 0; i < N; i++)
			mat(i, N) = v[i];
		return mat;
	}


	// View Matrix
	template<typename T>
	HomMatrix<T,3> lookAt(const mvl::Vector<T,3>& camera, const mvl::Vector<T,3>& center, const mvl::Vector<T,3>& up)
	{
		return lookTowards(camera, center - camera, up);
	}

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

	// Projection Matrix
	
	// RTF - right, top, front of the projection box
	// LBN - left, bottom, near of the projection box
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
	HomMatrix<T,3> perspective(T fovy, T aspect, T zNear, T zFar)
	{
		HomMatrix<T,3> mat;

		T fovy2 = fovy / 2.0;
		T f = cos(fovy2) / sin(fovy2);
		
		mat(0,0) = f / aspect;
		mat(1,1) = f;
		mat(2,2) = (zNear + zFar) / (zNear - zFar);
		mat(3,2) = 2 * zNear * zFar / (zNear - zFar);
		mat(2,3) = -1;
		
		return mat;
	}
}
