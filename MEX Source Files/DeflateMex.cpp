#include "eigenpairs.hpp"
#include "mex_helpers.hpp"
#include "types.hpp"

#include <mex.h>

void mexFunction(
        int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{    
    // Check for proper number of input and output arguments
    if (nrhs != 4) mexErrMsgTxt("Expected four input arguments.");
    if (nlhs != 1) mexErrMsgTxt("Expected one output arguments.");
    
    // Inputs
    mxArray const* lambdas = prhs[0];
    mxArray const* s = prhs[1];
    mxArray const* x = prhs[2];
    mxArray * y = plhs[0] = mxDuplicateArray(prhs[3]);
    
    // Check data type of input argument
    if (!is_vector(lambdas))
        mexErrMsgTxt("Argument lambdas should be a real vector.");
    if (!is_matrix(s))
        mexErrMsgTxt("Argument S should be a real matrix.");
    if (!is_column_vector(x))
        mexErrMsgTxt("Argument x should be a column vector.");
    if (!is_column_vector(y))
        mexErrMsgTxt("Argument y should be a column vector.");
    
    // Get the size and pointers to input data
    const std::size_t
            ml = mxGetM(lambdas),
            nl = mxGetN(lambdas),
            ms = mxGetM(s),
            ns = mxGetN(s),
            mx = mxGetM(x),
            nx = mxGetN(x);
    
    if (1 != ml && nl != 1)
        mexErrMsgTxt("Argument lambdas must be a vector.");
    if (1 != mx && nx != 1)
        mexErrMsgTxt("Argument x must be a vector.");
    if (ms != mx || ml*nl != ns)
        mexErrMsgTxt("Inner matrix dimensions must agree.");
    
    engsci331::deflate(
            static_cast<size_type>(ms),
            static_cast<size_type>(ns),
            mxGetPr(lambdas),
            mxGetPr(s),
            mxGetPr(x),
            mxGetPr(y));
}
