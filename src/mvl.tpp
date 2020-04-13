#include <cmath>

namespace mvl
{
	// Matrix
	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>::Matrix()
	{
		mat.fill(0);
	}

	// Access Operators
	template<typename T, size_t M, size_t N>
	T& Matrix<T,M,N>::operator()(size_t i, size_t j)
	{
		return mat[matrix_array_index<M,N>(i,j)];
	}

	template<typename T, size_t M, size_t N>
	const T& Matrix<T,M,N>::operator()(size_t i, size_t j) const
	{	
		return mat[matrix_array_index<M,N>(i,j)];
	}

	template<typename T, size_t M, size_t N>
	T& Matrix<T,M,N>::operator[](size_t i)
	{
		return (*this)(i,0);
	}

	template<typename T, size_t M, size_t N>
	const T& Matrix<T,M,N>::operator[](size_t i) const
	{
		return (*this)(i,0);
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,1,N> Matrix<T,M,N>::getRow(size_t i) const
	{
		Matrix<T,1,N> row;
		for (size_t j = 0; j < N; j++)
			row(0,j) = (*this)(i,j);
		return row;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,1> Matrix<T,M,N>::getCol(size_t j) const
	{
		Matrix<T,M,1> col;
		for (size_t i = 0; i < M; i++)
			col(i,0) = (*this)(i,j);
		return col;
	}

	template<typename T, size_t M, size_t N>
	void Matrix<T,M,N>::setRow(size_t i, const Matrix<T,1,N>& row)
	{
		for (size_t j = 0; j < N; j++)
			(*this)(i,j) = row(0,j);
	}

	template<typename T, size_t M, size_t N>
	void Matrix<T,M,N>::setCol(size_t j, const Matrix<T,M,1>& col)
	{
		for (size_t i = 0; i < M; i++)
			(*this)(i,j) = col(i,0);
	}

	// Arithmetic Operators
	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>& Matrix<T,M,N>::operator+=(const Matrix<T,M,N>& m)
	{
		component_wise(m, [](T& a, const T& b) { a += b; });
		return *this;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>& Matrix<T,M,N>::operator-=(const Matrix<T,M,N>& m)
	{
		component_wise(m, [](T& a, const T& b) { a -= b; });
		return *this;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>& Matrix<T,M,N>::operator*=(const T& t)
	{
		component_wise([t] (T& a) { a *= t; });
		return *this;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>& Matrix<T,M,N>::operator/=(const T& t)
	{
		component_wise([t] (T& a) { a /= t; });
		return *this;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N> Matrix<T,M,N>::operator-() const
	{
		Matrix<T,M,N> m;
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				m(i,j) = -(*this)(i,j);
		return m;
	}

	// Comparison Operators
	template<typename T, size_t M, size_t N>
	bool Matrix<T,M,N>::operator==(const Matrix<T,M,N>& m) const
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				if ((*this)(i,j) != m(i,j))
					return false;
		return true;
	}

	template<typename T, size_t M, size_t N>
	bool Matrix<T,M,N>::operator!=(const Matrix<T,M,N>& m) const
	{
		return !((*this) == m);
	}

	// External Arithmetic Functions
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
	template<typename T, size_t N>
	T dot(const Vector<T,N>& a, const Vector<T,N>& b)
	{
		return inner_product(a, b);
	}

	template<typename T>
	Vector<T,3> cross(const Vector<T,3>& a, const Vector<T,3>& b)
	{
		Vector<T,3> c;
		c[0] = (a[1] * b[2]) - (a[2] * b[1]);
		c[1] = (a[2] * b[0]) - (a[0] * b[2]);
		c[2] = (a[0] * b[1]) - (a[1] * b[0]);
		return c;
	}

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
	T norm(const Vector<T,N>& v)
	{
		return sqrt(norm2(v));
	}

	template<typename T, size_t N>
	T norm2(const Vector<T,N>& v)
	{
		return inner_product(v,v);
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

	// OpenGL Methods
	template<typename T, size_t M, size_t N>
	const T* Matrix<T,M,N>::toArray() const
	{
		return mat.data();
	}
}
