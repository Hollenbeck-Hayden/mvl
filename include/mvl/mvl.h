#pragma once

#include <cstddef>
#include <array>
#include <initializer_list>
#include <cmath>

namespace mvl
{
	template<size_t M, size_t N>
	inline size_t matrix_array_index(size_t i, size_t j)
	{
		return i + M * j;
	}

	template<typename T, size_t M, size_t N>
	class Matrix
	{
	public:
		// Constructors
		Matrix()
		{
			mat.fill(0);
		}

		template<typename... S>
		Matrix(S... data) : mat{data...} {};

		// Element Access
		T& operator()(size_t i, size_t j)
		{
			return mat[matrix_array_index<M,N>(i,j)];
		}

		const T& operator()(size_t i, size_t j) const
		{
			return mat[matrix_array_index<M,N>(i,j)];
		}

		T& operator[](size_t i)
		{
			return (*this)(i,0);
		}

		const T& operator[](size_t i) const
		{
			return (*this)(i,0);
		}

		// Column / Row Access
		Matrix<T,1,N> getRow(size_t i) const
		{
			Matrix<T,1,N> row;
			for (size_t j = 0; j < N; j++)
				row(0,j) = (*this)(i,j);
			return row;
		}

		Matrix<T,M,1> getCol(size_t j) const
		{
			Matrix<T,M,1> col;
			for (size_t i = 0; i < M; i++)
				col(i,0) = (*this)(i,j);
			return col;
		}

		void setRow(size_t i, const Matrix<T,1,N>& row)
		{
			for (size_t j = 0; j < N; j++)
				(*this)(i,j) = row(0,j);
		}

		void setCol(size_t j, const Matrix<T,M,1>& col)
		{
			for (size_t i = 0; i < N; i++)
				(*this)(i,j) = col(i,0);
		}

		// Arithmetic Operations
		Matrix<T,M,N>& operator+=(const Matrix<T,M,N>& m)
		{
			component_wise(m, [](T& a, const T& b) { a += b; });
			return *this;
		}

		Matrix<T,M,N>& operator-=(const Matrix<T,M,N>& m)
		{
			component_wise(m, [](T& a, const T& b) { a -= b; });
			return *this;
		}

		Matrix<T,M,N>& operator*=(const T& t)
		{
			component_wise([t] (T& a) { a *= t; });
			return *this;
		}

		Matrix<T,M,N>& operator/=(const T& t)
		{
			component_wise([t] (T& a) { a /= t; });
			return *this;
		}
		
		Matrix<T,M,N> operator-() const
		{
			Matrix<T,M,N> m;
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					m(i,j) = -(*this)(i,j);
			return m;
		}

		// Comparison Operators
		bool operator==(const Matrix<T,M,N>& m) const
		{
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					if ((*this)(i,j) != m(i,j))
						return false;
			return true;
		}

		bool operator!=(const Matrix<T,M,N>& m) const
		{
			return !((*this) == m);
		}

		// OpenGL methods
		const T* toArray() const
		{
			return mat.data();
		}

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
	template<typename T, size_t M, size_t N>
	Matrix<T,M,N> operator+(Matrix<T,M,N> m, const Matrix<T,M,N>& n)
	{
		return m += n;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N> operator-(Matrix<T,M,N> m, const Matrix<T,M,N>& n)
	{
		return m -= n;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N> operator*(Matrix<T,M,N> m, const T& t)
	{
		return m *= t;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N> operator*(const T& t, Matrix<T,M,N> m)
	{
		return m *= t;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N> operator/(Matrix<T,M,N> m, const T& t)
	{
		return m /= t;
	}

	template<typename T, size_t M, size_t N, size_t S>
	Matrix<T,M,S> operator*(const Matrix<T,M,N>& m, const Matrix<T,N,S>& n)
	{
		Matrix<T,M,S> s;
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < S; j++)
				for (size_t k = 0; k < N; k++)
					s(i,j) += m(i,k) * n(k,j);
		return s;
	}

	// Useful aliases
	template<typename T, size_t N> using Vector = Matrix<T,N,1>;
	template<typename T, size_t N> using SMatrix = Matrix<T,N,N>;

	// Inner Product Operations
	template<typename T, size_t N>
	T inner_product(const Vector<T,N>& a, const Vector<T,N>& b)
	{
		T t = 0;
		for (size_t i = 0; i < N; i++)
			t += a[i] * b[i];
		return t;
	}

	template<typename T, size_t N>
	T norm2(const Vector<T,N>& v)
	{
		return inner_product(v,v);
	}

	template<typename T, size_t N>
	T norm(const Vector<T,N>& v)
	{
		return sqrt(norm2(v));
	}

	template<typename T, size_t N>
	Vector<T,N> normalize(const Vector<T,N>& v)
	{
		Vector<T,N> u = v;
		return u / norm(u);
	}

	template<typename T, size_t N>
	Vector<T,N>& normalize(Vector<T,N>& v)
	{
		return v /= norm(v);
	}

	template<typename T, size_t N>
	bool is_orthogonal(const Vector<T,N>& a, const Vector<T,N>& b)
	{
		return inner_product(a,b) == 0;
	}
	
	// Dual Space Operations
	template<typename T, size_t M, size_t N>
	Matrix<T,N,M> transpose(const Matrix<T,M,N>& m)
	{
		Matrix<T,N,M> n;
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				n(j,i) = m(i,j);
		return n;
	}

	// Vector Operations
	template<typename T, size_t N> T dot(const Vector<T,N>& a, const Vector<T,N>& b)
	{
		return inner_product(a, b);
	}

	template<typename T> Vector<T,3> cross(const Vector<T,3>& a, const Vector<T,3>& b)
	{
		Vector<T,3> c;
		c[0] = (a[1] * b[2]) - (a[2] * b[1]);
		c[1] = (a[2] * b[0]) - (a[0] * b[2]);
		c[2] = (a[0] * b[1]) - (a[1] * b[0]);
		return c;
	}
}
