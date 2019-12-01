#include <cstddef>
#include <functional>
#include <memory>

namespace mvl
{
	/**
	 * An array wrapper used to quickly move / cast vectors.
	 * typename T		Data type
	 * size_t   M		Number of rows
	 * size_t   N		Number of columns
	 */
	template<typename T, size_t M, size_t N>
	class DataMatrix
	{
	public:
		// Constructors
		DataMatrix();

		// Copy constructor
		DataMatrix(const DataMatrix<T,M,N>& d);
		DataMatrix<T,M,N>& operator=(const DataMatrix<T,M,N>& d);

		// Element Access
		T& operator()(size_t i, size_t j);
		const T& operator()(size_t i, size_t j) const;

	private:
		T data[N][M];
	};

	/**
	 * A class used to represent a MxN vector over a field T. 
	 * While it is labeled "abstract", you may actually create objects
	 * from this class if somehow the matrix or vector subclasses don't
	 * fit your purpose.
	 * typename T		data type
	 * size_t   M		number of rows
	 * size_t   N		number of columns
	 */
	template<typename T, size_t M, size_t N>
	class AbstractVector
	{
	public:
		// Constructors
		AbstractVector();

		// Copy semantics
		AbstractVector(const AbstractVector<T,M,N>& v);
		AbstractVector<T,M,N>& operator=(const AbstractVector<T,M,N>& v);

		// Move semantics
		AbstractVector(AbstractVector<T,M,N>&& v);
		AbstractVector<T,M,N>& operator=(AbstractVector<T,M,N>&& v);

		// Destructor
		virtual ~AbstractVector();

		// Element Access
			T& operator()(size_t i, size_t j)	;
		const	T& operator()(size_t i, size_t j) const	;

		// Column / Row Access
		AbstractVector<T,1,N> getRow(size_t i) const;
		AbstractVector<T,M,1> getCol(size_t i) const;

		void setRow(size_t i, const AbstractVector<T,1,N>& row);
		void setCol(size_t j, const AbstractVector<T,M,1>& col);

		// Arithmetic Operators
		AbstractVector<T,M,N>& operator+=(const AbstractVector<T,M,N>& v);
		AbstractVector<T,M,N>& operator-=(const AbstractVector<T,M,N>& v);
		AbstractVector<T,M,N>& operator*=(const T& v);
		AbstractVector<T,M,N>& operator/=(const T& v);

		// Comparison
		bool operator==(const AbstractVector<T,M,N>& v) const;
		bool operator!=(const AbstractVector<T,M,N>& v) const;

		// Display
		virtual void print() const;

	protected:
		void component_wise(std::function<void(T&)> action);
		void component_wise(const AbstractVector<T,M,N>& v, std::function<void(T&, const T&)> action);

		std::unique_ptr<DataMatrix<T,M,N>> mat;
	};

	// Arithmetic Operations
	template<typename T, size_t M, size_t N> AbstractVector<T,M,N> operator+(AbstractVector<T,M,N> v, const AbstractVector<T,M,N>& u);
	template<typename T, size_t M, size_t N> AbstractVector<T,M,N> operator-(AbstractVector<T,M,N> v, const AbstractVector<T,M,N>& u);
	template<typename T, size_t M, size_t N> AbstractVector<T,M,N> operator*(AbstractVector<T,M,N> v, const T& t);
	template<typename T, size_t M, size_t N> AbstractVector<T,M,N> operator/(AbstractVector<T,M,N> v, const T& t);
	template<typename T, size_t M, size_t N> AbstractVector<T,M,N> operator*(const T& t, AbstractVector<T,M,N> v);

	template<typename T, size_t M, size_t N, size_t S> AbstractVector<T,M,S> operator*(const AbstractVector<T,M,N>& v, const AbstractVector<T,N,S>& u);

	/**
	 * A MxN matrix over a field T.
	 */
	template<typename T, size_t M, size_t N>
	class Matrix : public AbstractVector<T,M,N>
	{
	public:
		// Inherited Constructors
		using AbstractVector<T,M,N>::AbstractVector;
		using AbstractVector<T,M,N>::operator=;

		// Copy / Move Constructors
		Matrix() : AbstractVector<T,M,N>() {}
		template<class V> Matrix(const V& v) : AbstractVector<T,M,N>(v) {}
		template<class V> Matrix(V&& v) : AbstractVector<T,M,N>(std::move(v)) {}
	};

	/**
	 * A NxN linear operator over a field T.
	 */
	template<typename T, size_t N>
	class Operator : public Matrix<T,N,N>
	{
	public:
		// Inherited Constructors
		using AbstractVector<T,N,N>::AbstractVector;
		using AbstractVector<T,N,N>::operator=;
		using Matrix<T,N,N>::Matrix;
		using Matrix<T,N,N>::operator=;

		// Copy / Move Constructors
		Operator() : AbstractVector<T,N,N>() {}
		template<class V> Operator(const V& v) : Matrix<T,N,N>(v) {}
		template<class V> Operator(V&& v) : Matrix<T,N,N>(std::move(v)) {}
	};

	/**
	 * An column vector of size N over a field T.
	 */
	template<typename T, size_t N>
	class Vector : public AbstractVector<T,N,1>
	{
	public:
		// Inherited Constructors
		using AbstractVector<T,N,1>::AbstractVector;
		using AbstractVector<T,N,1>::operator=;

		// Copy / Move Constructors
		Vector() : AbstractVector<T,N,1>() {}
		template<class V> Vector(const V& v) : AbstractVector<T,N,1>(v) {}
		template<class V> Vector(V&& v) : AbstractVector<T,N,1>(std::move(v)) {}

		// Element Access
			T& operator[](size_t i)		;
		const	T& operator[](size_t i) const	;

		// Display
		virtual void print() const;
	};


	// Factory methods
	template<typename T, size_t N> Operator<T,N> identity_matrix();
};

#include "mvl.tpp"
