#ifndef INCLUDED_POWER_HPP
#define INCLUDED_POWER_HPP

#include <iostream>

#include "scale.hpp"
#include "types.hpp"

#include <algorithm> // for std::copy, std::generate
#include <cmath> // for std::sqrt
#include <functional> // for std::bind
#include <numeric> // for std::inner_product
#include <random> // for std::uniform_real_distribution

namespace engsci331
{

	// Returns (uniform) relative difference between its arguments
	inline double compare(double const& x, double const& y)
	{
		using std::abs;
		const double scale = 0.5*(abs(x) + abs(y));
		return abs(x - y) / (1 + scale);
	}

	// Dot product of two arrays of length n
	inline double dot(double const* x, double const* y, size_type n)
	{
		return std::inner_product(x, x + n, y, 0.0);
	}

	// Two-norm of a vector of length n
	inline double norm(double const* x, size_type n)
	{
		return std::sqrt(dot(x, x, n));
	}

	template<class MatrixProductOperator>
	inline bool power(
		MatrixProductOperator apply,
		size_type n,
		double & lambda,
		double * s,
		double * s_image,
		double const& tol,
		size_type maxit)
	{
		// Random initial iterate
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution(-1, 1);
		std::generate(s, s + n, std::bind(distribution, generator));
		//std::fill(s, s + n, 1.0); // Perhaps useful for testing

		// Normalise initial iterate
		// TODO
		for(int i=0;i<n;i++){
			s[i]=(s[i])/norm(s,n);
		}
		size_type iter = 0;
		bool converged = false;
		while (iter++ < maxit && !converged)
		{
			// Matrix-vector product
			// TODO
            apply(s,s_image);
			// Estimate eigenvalue magnitude
			// TODO
            lambda=norm(s_image,n);
			lambda=fabs(lambda);
			// Eigenvalue sign
			// TODO
            double res=dot(s,s_image,n);
            double sign=res>0?1.0:-1.0;
            lambda=sign*lambda;
			// Convergence test
			double mismatch = 0;
			// TODO: Maximum relative residual, using "compare(.., ..)"
			for(int i=0;i<n;i++){
				double current=compare((s[i])*lambda,s_image[i]);
				mismatch=std::max(mismatch,current);
			}
			converged = mismatch < tol;

			// Normalise eigenvector estimate
			for(int i=0;i<n;i++)
				s[i]=(s_image[i])/norm(s_image,n);
		}
		return converged;
	}

} //  namespace

#endif // INCLUDED_POWER_HPP
