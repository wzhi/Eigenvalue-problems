#ifndef INCLUDED_SCALE_HPP
#define INCLUDED_SCALE_HPP

#include "types.hpp"

// Computes the scalar product y(i) = alpha*x(i), analogous to 
// the BLAS routine DSCAL (https://software.intel.com/en-us/node/520743).
void scale(size_type n, double const& alpha, double const* x, double * y)
{
    for (size_type i = 0; i < n; i++) y[i] = alpha*x[i];
}

#endif
