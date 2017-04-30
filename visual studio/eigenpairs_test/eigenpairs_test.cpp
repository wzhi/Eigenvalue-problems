#define _SCL_SECURE_NO_WARNINGS
#include "eigenpairs.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

typedef std::vector<double> vector_type;
typedef std::vector<vector_type> row_matrix_type;

void matrix_multiply(row_matrix_type const& a, double const* x, double * y)
{
	for (size_type i = 0; i < a.size(); ++i)
	{
		vector_type const& row = a[i];
		y[i] = std::inner_product(row.begin(), row.end(), x, 0.0);
	}
}

int main(void)
{
	const double tol = 1e-14;
	const size_type n = 3, p = 2, maxit = 100;
	const row_matrix_type a = {
		{  5, -2,  0}, // row 0
		{ -2,  3, -1}, // row 1
		{  0, -1,  1}  // row 2
	};
	auto apply_matrix = [&](double const* x, double * y)
	{
		matrix_multiply(a, x, y); // matrix "a" is referenced from enclosing scope
	};

	vector_type s(n*p), s_image(n*n), lambdas(p);
	const bool success = engsci331::eigenpairs(
		apply_matrix,
		n,
		p,
		lambdas.data(),
		s.data(),
		s_image.data(),
		tol,
		maxit);

	assert(success);

	for (size_type k = 0; k < p; ++k)
	{
		std::cout << "eigenpair " << k << ": " << std::endl;
		double const* sk = s.data() + k*n;
		std::fill_n(s_image.data(), n, 0.0);
		apply_matrix(sk, s_image.data());
		for (size_type i = 0; i < n; ++i)
			std::cout
			<< " relative residual " << i << ": "
			<< engsci331::compare(sk[i] * lambdas[k], s_image[i])
			<< std::endl;
	}

	return EXIT_SUCCESS;
}
