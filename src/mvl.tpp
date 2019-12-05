#include <iostream>

namespace mvl
{
	// Data Matrix Definition
	template<typename T, size_t M, size_t N>
	DataMatrix<T,M,N>::DataMatrix()
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				(*this)(i,j) = 0;
	}

	template<typename T, size_t M, size_t N>
	DataMatrix<T,M,N>::DataMatrix(const DataMatrix<T,M,N>& m)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				(*this)(i,j) = m(i,j);
	}

	template<typename T, size_t M, size_t N>
	DataMatrix<T,M,N>& DataMatrix<T,M,N>::operator=(const DataMatrix<T,M,N>& m)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				(*this)(i,j) = m(i,j);
		return *this;
	}

	template<typename T, size_t M, size_t N>
	T& DataMatrix<T,M,N>::operator()(size_t i, size_t j)
	{
		return data[j][i];
	}

	template<typename T, size_t M, size_t N>
	const T& DataMatrix<T,M,N>::operator()(size_t i, size_t j) const
	{
		return data[j][i];
	}

	// Data Matrix Nx1
	template<typename T, size_t N>
	DataMatrix<T,N,1>::DataMatrix()
	{
		for (size_t i = 0; i < N; i++)
			(*this)(i,0) = 0;
	}

	template<typename T, size_t N>
	DataMatrix<T,N,1>::DataMatrix(const DataMatrix<T,N,1>& m)
	{
		for (size_t i = 0; i < N; i++)
			(*this)(i,0) = m(i,0);
	}

	template<typename T, size_t N>
	DataMatrix<T,N,1>& DataMatrix<T,N,1>::operator=(const DataMatrix<T,N,1>& m)
	{
		for (size_t i = 0; i < N; i++)
			(*this)(i,0) = m(i,0);
		return *this;
	}

	template<typename T, size_t N>
	T& DataMatrix<T,N,1>::operator()(size_t i, size_t j)
	{
		return data[i];
	}

	template<typename T, size_t N>
	const T& DataMatrix<T,N,1>::operator()(size_t i, size_t j) const
	{
		return data[i];
	}

	// Matrix
	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>::Matrix()
	{
		mat = std::make_unique<DataMatrix<T,M,N>>();
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>::Matrix(const Matrix<T,M,N>& m)
	{
		mat = std::make_unique<DataMatrix<T,M,N>>();
		component_wise(m, [](T& a, const T& b) { a = b; });
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>& Matrix<T,M,N>::operator=(const Matrix<T,M,N>& m)
	{
		mat = std::make_unique<DataMatrix<T,M,N>>();
		component_wise(m, [](T& a, const T& b) { a = b; });
		return *this;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>::Matrix(Matrix<T,M,N>&& m)
	{
		mat = std::move(m.mat);
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>& Matrix<T,M,N>::operator=(Matrix<T,M,N>&& m)
	{
		mat = std::move(m.mat);
		return *this;
	}

	template<typename T, size_t M, size_t N>
	Matrix<T,M,N>::~Matrix<T,M,N>()
	{
		mat.release();
	}

	template<typename T, size_t M, size_t N>
	T& Matrix<T,M,N>::operator()(size_t i, size_t j)
	{
		return mat->operator()(i,j);
	}

	template<typename T, size_t M, size_t N>
	const T& Matrix<T,M,N>::operator()(size_t i, size_t j) const
	{	
		return mat->operator()(i,j);
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
		T t = 0;
		for (size_t i = 0; i < N; i++)
			t += a[i] * b[i];
		return t;
	}
}
