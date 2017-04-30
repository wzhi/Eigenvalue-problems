#include "scale.hpp"
#include <mex.h>

void mexFunction(
        int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{
    // Check for proper number of input and output arguments
    if (2 != nrhs) mexErrMsgTxt("Expected two input arguments.");
    if (1 < nlhs) mexErrMsgTxt("Expected one output arguments.");
    
    // Inputs
    mxArray const* palpha = prhs[0];
    mxArray const* px = prhs[1];
    
    // Preconditions
    if (!mxIsDouble(palpha) || !mxIsScalar(palpha))
        mexErrMsgTxt("First argument must be a scalar of type double.");
    if (!mxIsDouble(px))
        mexErrMsgTxt("Second argument must be of type double.");
    
    // Allocate output array
    mxArray * py = plhs[0] = mxDuplicateArray(px);
    
    // Extract native pointers
    double const alpha = mxGetScalar(palpha);
    double const* x = mxGetPr(px);
    double * y = mxGetPr(py);

    // Delegate to an "ordinary" C++ routine
    scale(mxGetNumberOfElements(px), alpha, x, y);
}
