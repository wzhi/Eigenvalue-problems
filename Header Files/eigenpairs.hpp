#ifndef INCLUDED_EIGENPAIRS_HPP
#define INCLUDED_EIGENPAIRS_HPP

#include "power.hpp"
#include <algorithm> // for std::copy, std::generate
#include <cmath> // for std::sqrt
#include <functional> // for std::bind
#include <numeric> // for std::inner_product
#include <random> // for std::uniform_real_distribution


namespace engsci331
{

	inline void deflate(
		size_type n,
		size_type p,
		double const* lambdas,
		double const* s,
		double const* x,
		double * y)
	{
		// TODO for ENGSCI.331
		for (int i = 0;i < p;i++) {
			double temp = 0;
			for (int j = 0;j < n;j++) {
				temp += *(s+j+i*n) * x[j];
			}
			temp = lambdas[i] * temp;
			//inner product calculations
			for (int j = 0;j < n;j++) {
				y[j] -=  *(s+j+i*n)*temp;
			}
		}

	}

	template<class MatrixProductOperator>
	inline bool eigenpairs(
		MatrixProductOperator apply,
		size_type n,
		size_type p,
		double * lambdas,
		double * s,
		double * work,
		double const& tol,
		size_type maxit)
	{
		bool success=true;
		
		for (int i = 0;i < p;i++) {
			//set deflate function to pass on as apply
			auto deflatef = [&](double const* x, double * y)
			{
				apply(x, y);
				engsci331::deflate(n, i, lambdas, s, x, y);
			};
			bool Csuccess = engsci331::power(deflatef,n,lambdas[i],s+i*n,work,tol,maxit);
			if (!Csuccess) success = false;
		}
		return true; // if all eigenpairs have converged
	}

} // namespace

#endif // INCLUDED_EIGENPAIRS_HPP
