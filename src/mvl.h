#include <iostream>
#include <cstddef>
#include <memory>

namespace mvl
{
	template<typename T, size_t M, size_t N>
	class DataMatrix
	{
	public:
		// Constructors
		DataMatrix();

		// Copy Constructor
		DataMatrix(const DataMatrix<T,M,N>& m);
		DataMatrix<T,M,N>& operator=(const DataMatrix<T,M,N>& m);

		// Access Operators
		T& operator()(size_t i, size_t j);
		const T& operator()(size_t i, size_t j) const;
	
	private:
		T data[N][M];
	};

	template<typename T, size_t M, size_t N>
	class Matrix
	{
	public:
		// Constructors
		Matrix();

		// Copy Constructors
		Matrix(const Matrix<T,M,N>& m);
		Matrix<T,M,N>& operator=(const Matrix<T,M,N>& m);

		// Move Constructors
		Matrix(Matrix<T,M,N>&& m);
		Matrix<T,M,N>& operator=(Matrix<T,M,N>&& m);

		// Destructor
		virtual ~Matrix();

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

		// Comparison Operators
		bool operator==(const Matrix<T,M,N>& m) const;
		bool operator!=(const Matrix<T,M,N>& m) const;

	private:
		std::unique_ptr<DataMatrix<T,M,N>> mat;

		template<typename F>
		void component_wise(F f)
		{
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					f(mat->operator()(i,j));
		}

		template<typename F>
		void component_wise(const Matrix<T,M,N>& m, F f)
		{
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					f(mat->operator()(i,j), m(i,j));
		}
	};

	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator+(Matrix<T,M,N> m, const Matrix<T,M,N>& n);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator-(Matrix<T,M,N> m, const Matrix<T,M,N>& n);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator*(Matrix<T,M,N> m, const T& t);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator*(const T& t, Matrix<T,M,N> m);
	template<typename T, size_t M, size_t N> Matrix<T,M,N> operator/(Matrix<T,M,N> m, const T& t);

	template<typename T, size_t M, size_t N, size_t S>
	Matrix<T,M,S> operator*(const Matrix<T,M,N>& m, const Matrix<T,N,S>& n);

	template<typename T, size_t M, size_t N>
	Matrix<T,N,M> transpose(const Matrix<T,M,N>& m);

	// Useful aliases
	template<typename T, size_t N> using Vector = Matrix<T,N,1>;
	template<typename T, size_t N> using SMatrix = Matrix<T,N,N>;

	// Vector Operations
	template<typename T, size_t N> T dot(const Vector<T,N>& a, const Vector<T,N>& b);
}

#include "mvl.tpp"
