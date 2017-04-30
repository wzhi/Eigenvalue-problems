#define _SCL_SECURE_NO_WARNINGS
#include "eigenpairs.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

int main(void)
{
	const size_type n = 5, p = 3;
	const std::vector<double>
		lambdas = { 1, 2, -1 },
		s = { 0, -1, -1, -1, 0, 0, 1, 1, 2, 0, 3, -1, 2, 1, 1 },
		x = { -1, -1, 3, 3, 0 },
		yref = { 23, -25, -4, -31, 6 };
	std::vector<double>
		y = { 2, 3, 3, -1, -1 };

	assert(lambdas.size() == p);
	assert(s.size() == n*p);
	assert(x.size() == n);
	assert(y.size() == n);

	engsci331::deflate(n, p, lambdas.data(), s.data(), x.data(), y.data());

	for (size_type i = 0; i < n; ++i)
		std::cout 
		<< "difference " << i << ": " 
		<< std::abs(y[i] - yref[i]) 
		<< std::endl;

	return EXIT_SUCCESS;
}
