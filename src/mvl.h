#pragma once

#include <iostream>
#include <cstddef>
#include <array>
#include <initializer_list>

namespace mvl
{
	template<size_t M, size_t N>
	inline size_t matrix_array_index(size_t i, size_t j)
	{
		if (i >= M or j >= N)
			std::cout << "Out of bounds: (" << i << ", " << j << ") in " << M << " x " << N << std::endl;

		return i + M * j;
	}

	template<typename T, size_t M, size_t N>
	class Matrix
	{
	public:
		// Constructors
		Matrix();

		template<typename... S>
		Matrix(S... data) : mat{data...} {};

		// Element Access
		T& operator()(size_t i, size_t j);
		const T& operator()(size_t i, size_t j) const;

		T& operator[](size_t i);
		const T& operator[](size_t i) const;

		// Column / Row Access
		Matrix<T,1,N> getRow(size_t i) const;
		Matrix<T,M,1> getCol(size_t i) const;

		void setRow(size_t i, const Matrix<T,1,N>& row);
		void setCol(size_t i, const Matrix<T,M,1>& col);

		// Arithmetic Operations
		Matrix<T,M,N>& operator+=(const Matrix<T,M,N>& m);
		Matrix<T,M,N>& operator-=(const Matrix<T,M,N>& m);
		Matrix<T,M,N>& operator*=(const T& t);
		Matrix<T,M,N>& operator/=(const T& t);
		
		Matrix<T,M,N> operator-() const;

		// Comparison Operators
		bool operator==(const Matrix<T,M,N>& m) const;
		bool operator!=(const Matrix<T,M,N>& m) const;

		// OpenGL methods
		const T* toArray() const;

	private:
		std::array<T, M*N> mat;

		template<typename F>
		void component_wise(F f)
		{
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					f(mat[matrix_array_index<M,N>(i,j)]);
		}

		template<typename F>
		void component_wise(const Matrix<T,M,N>& m, F f)
		{
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					f(mat[matrix_array_index<M,N>(i,j)], m(i,j));
		}
	};

	// Arithmetic operations
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator+(Matrix<T,M,N> m, const Matrix<T,M,N>& n);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator-(Matrix<T,M,N> m, const Matrix<T,M,N>& n);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator*(Matrix<T,M,N> m, const T& t);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator*(const T& t, Matrix<T,M,N> m);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator/(Matrix<T,M,N> m, const T& t);

	template<typename T, size_t M, size_t N, size_t S>
	Matrix<T,M,S> operator*(const Matrix<T,M,N>& m, const Matrix<T,N,S>& n);

	// Useful aliases
	template<typename T, size_t N> using Vector = Matrix<T,N,1>;
	template<typename T, size_t N> using SMatrix = Matrix<T,N,N>;

	// Vector Operations
	template<typename T, size_t N> T dot(const Vector<T,N>& a, const Vector<T,N>& b);
	template<typename T, size_t N> Vector<T,N> cross(const Vector<T,N>& a, const Vector<T,N>& b);

	// Inner Product Operations
	template<typename T, size_t N> T inner_product(const Vector<T,N>& a, const Vector<T,N>& b);
	template<typename T, size_t N> T norm(const Vector<T,N>& v);
	template<typename T, size_t N> T norm2(const Vector<T,N>& v);
	template<typename T, size_t N> Vector<T,N> normalize(const Vector<T,N>& v);
	template<typename T, size_t N> Vector<T,N>& normalize(Vector<T,N>& v);
	template<typename T, size_t N> bool is_orthogonal(const Vector<T,N>& a, const Vector<T,N>& b);
	
	// Dual Space Operations
	template<typename T, size_t M, size_t N>
	Matrix<T,N,M> transpose(const Matrix<T,M,N>& m);
}

#include "mvl.tpp"
