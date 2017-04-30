#include "mex_helpers.hpp"
#include "power.hpp"
#include <mex.h>
#include <vector> // for std::vector

void mexFunction (
        int nlhs, mxArray * plhs[],
        int nrhs, const mxArray * prhs[])
{
    // Check arities
    if (4 != nrhs) mexErrMsgTxt("Unexpected number of input arguments.");
    if (3 < nlhs) mexErrMsgTxt("Too many output arguments.");
    
    // Named arguments
    const mxArray * pfun = prhs[0]; // handle to matrix-vector operator
    const mxArray * pn = prhs[1]; // matrix dimension
    const mxArray * ptol = prhs[2]; // stopping tolerance
    const mxArray * pmaxit = prhs[3]; // iteration bound
    
    // Preconditions
    if (!is_function(pfun))
        mexErrMsgTxt("First argument should be a function handle.");
    if (!is_number(pn))
        mexErrMsgTxt("Argument n should be a scalar double.");
    if (!is_number(ptol))
        mexErrMsgTxt("Argument tol should be a scalar double.");
    if (!is_number(pmaxit))
        mexErrMsgTxt("Argument maxit should be a scalar integer double.");
    
    // Extract argument values from MATLAB workspace
    const size_type n = static_cast<size_type>(mxGetScalar(pn));
    const double tol = mxGetScalar(ptol);
    const size_type maxit = static_cast<size_type>(mxGetScalar(pmaxit));
    
    // Captures matrix-vector operator and dimension
    auto applicator = [n, pfun](double const* x, double * y) -> void
    {
        apply_matlab_operator(pfun, n, x, y);
    };
    
    // Native storage
    std::vector<double> 
            s_buffer(n), // eigenvector
            work_buffer(n); // work array
    double lambda; // eigenvalue
    
    // Delegate computation to library routine
    const bool converged = engsci331::power(
            applicator,
            n,
            lambda,
            &s_buffer[0],
            &work_buffer[0],
            tol,
            maxit);
    
    // Copy outputs from native arrays to MATLAB arrays
    mxArray * s = plhs[0] = 
            mxCreateDoubleMatrix(static_cast<int>(n), 1, mxREAL);
    std::copy(s_buffer.begin(), s_buffer.end(), mxGetPr(s));
    plhs[1] = mxCreateDoubleScalar(lambda);
    plhs[2] = mxCreateLogicalScalar(converged);
}
