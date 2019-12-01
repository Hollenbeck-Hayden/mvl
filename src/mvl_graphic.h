#include "mvl.h"

namespace mvl
{
	/**
	 * Vector in homogeneous coordinates
	 */
	template<typename T, size_t N>
	class HVector : public Vector<T, N+1>
	{
	public:
		// Constructors
		HVector();

		// Construction from size N vectors
		HVector(const AbstractVector<T,N,1>& v);
		HVector<T,N>& operator=(const AbstractVector<T,N,1>& v);

		// Construction from size N+1 vectors
		template<class V> HVector(const V& v) : Vector<T,N+1>(v) { (*this)[N] = 1; };
		template<class V> HVector(V&& v) : Vector<T,N+1>(std::move(v)) { (*this)[N] = 1; };
	};

	/**
	 * Matrix in homogeneous coordinates
	 */
	template<typename T, size_t N>
	class HMatrix : public Operator<T,N+1>
	{
	public:
		// Constructors
		HMatrix();

		// Construction from size N matrices
		HMatrix(const AbstractVector<T,N+1,N+1>& v);
		HMatrix<T,N>& operator=(const AbstractVector<T,N+1,N+1>& v);

		// Construction from size N+1 matrices
		template<class V> HMatrix(const V& v) : Operator<T,N+1>(v) { (*this)[N][N] = 1; }
		template<class V> HMatrix(V&& v) : Operator<T,N+1>(std::move(v)) { (*this)[N][N] = 1; }
	};
};
