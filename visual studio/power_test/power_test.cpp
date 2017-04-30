#define _SCL_SECURE_NO_WARNINGS
#include "power.hpp"

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
	const size_type n = 3, maxit = 100;
	const row_matrix_type a = {
		{ 0, 3, 6 },
		{ 1, 4, 7 },
		{ 2, 5, 7 }
	};
	auto apply_matrix = [&](double const* x, double * y)
	{
		matrix_multiply(a, x, y);
	};

	double lambda;
	vector_type s(n), s_image(n);
	const bool success = engsci331::power(
		apply_matrix,
		n,
		lambda,
		s.data(),
		s_image.data(),
		tol,
		maxit);

	assert(success);

	apply_matrix(s.data(), s_image.data());
	for (size_type i = 0; i < s.size(); ++i)
		std::cout
		<< " relative residual " << i << ": "
		<< engsci331::compare(s[i] * lambda, s_image[i])
		<< std::endl;

	return EXIT_SUCCESS;
}
