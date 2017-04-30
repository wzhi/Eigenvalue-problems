#include "eigenpairs.hpp"
#include "mex_helpers.hpp"
#include <mex.h>
#include <vector> // for std::vector

void mexFunction (
        int nlhs, mxArray * plhs[],
        int nrhs, const mxArray * prhs[])
{
    // Check arities
    if (5 != nrhs) mexErrMsgTxt("Unexpected number of input arguments.");
    if (3 < nlhs) mexErrMsgTxt("Too many output arguments.");
    
    // Named arguments
    const mxArray * pfun = prhs[0]; // handle to matrix-vector operator
    const mxArray * pn = prhs[1]; // matrix dimension
    const mxArray * pp = prhs[2]; // number of eigenpairs
    const mxArray * ptol = prhs[3]; // stopping tolerance
    const mxArray * pmaxit = prhs[4]; // iteration bound
    
    // Preconditions
    if (!is_function(pfun))
        mexErrMsgTxt("First argument should be a function handle.");
    if (!is_number(pn))
        mexErrMsgTxt("Argument n should be a scalar double.");
    if (!is_number(pp))
        mexErrMsgTxt("Argument p should be a scalar double.");
    if (!is_number(ptol))
        mexErrMsgTxt("Argument tol should be a scalar double.");
    if (!is_number(pmaxit))
        mexErrMsgTxt("Argument maxit should be a scalar integer double.");
    
    // Extract argument values from MATLAB workspace
    const size_type n = static_cast<size_type>(mxGetScalar(pn));
    const size_type p = static_cast<size_type>(mxGetScalar(pp));
    const double tol = mxGetScalar(ptol);
    const size_type maxit = static_cast<size_type>(mxGetScalar(pmaxit));
    
    // Captures matrix-vector operator and dimension
    auto applicator = [n, pfun](double const* x, double * y) -> void
    {
        apply_matlab_operator(pfun, n, x, y);
    };
    
    // Native storage
    std::vector<double> 
            lambdas_buffer(p), // eigenvalues
            s_buffer(n*p), // eigenvectors
            work_buffer(n); // work array
    
    // Delegate computation to library routine
    const bool succeeded = engsci331::eigenpairs(
            applicator,
            n, p,
            &lambdas_buffer[0],
            &s_buffer[0],
            &work_buffer[0],
            tol,
            maxit);
    
    // Copy outputs from native arrays to MATLAB arrays
    mxArray * s = plhs[0] = mxCreateDoubleMatrix(
            static_cast<int>(n), static_cast<int>(p), mxREAL);
    std::copy(s_buffer.begin(), s_buffer.end(), mxGetPr(s));    
    mxArray * lambdas = plhs[1] = 
                mxCreateDoubleMatrix(static_cast<int>(p), 1, mxREAL);
    std::copy(lambdas_buffer.begin(), 
            lambdas_buffer.end(), mxGetPr(lambdas));
    plhs[2] = mxCreateLogicalScalar(succeeded);
}
