#ifndef INCLUDED_MEX_HELPERS_HPP
#define INCLUDED_MEX_HELPERS_HPP

#include "types.hpp"
#include <algorithm>
#include <mex.h>

struct smart_mx_pointer
{
    mxArray * ptr;
    smart_mx_pointer(mxArray * p = 0): ptr(p)
    { }
    ~smart_mx_pointer()
    {
        mxDestroyArray(this->ptr);
    }
    double * data()
    {
        return static_cast<double *>(mxGetData(this->ptr));
    }
};

inline bool is_number(mxArray const* p)
{
    return mxIsScalar(p) && mxIsDouble(p);
}

inline bool is_matrix(mxArray const* p)
{
    return
            mxIsDouble(p) && !mxIsComplex(p)
            && mxGetNumberOfDimensions(p) == 2;
}

inline bool is_row_vector(mxArray const* p)
{
    return is_matrix(p) && mxGetM(p) == 1;
}

inline bool is_column_vector(mxArray const* p)
{
    return is_matrix(p) && mxGetN(p) == 1;
}

inline bool is_vector(mxArray const* p)
{
    return is_column_vector(p) || is_row_vector(p);
}

inline bool is_function(mxArray const* p)
{
    // Verify that first argument is a callable entity
    switch (mxGetClassID(p))
    {
        case mxCHAR_CLASS:
        case mxFUNCTION_CLASS:
            return true;
        default:
            return false;
    }
}

void apply_matlab_operator(
        mxArray const* pfun, size_type n,
        double const* x, double * y)
{
    // Copy argument to MATLAB array
    smart_mx_pointer xx(
            mxCreateDoubleMatrix(static_cast<int>(n), 1, mxREAL));
    std::copy(x, x + n, xx.data());
    
    // Invoke function in MATLAB's workspace
    mxArray * plhs[] = { NULL };
    mxArray * prhs[] = { const_cast<mxArray *>(pfun), xx.ptr };
    mexCallMATLAB(1, plhs, 2, prhs, "feval");
    
    smart_mx_pointer yy(plhs[0]);
    if (yy.ptr == NULL)
        mexErrMsgTxt("Error evaluating MATLAB callback.");
    if (mxGetM(yy.ptr) != n || mxGetN(yy.ptr) != 1)
        mexErrMsgTxt("Result has unexpected shape.");
    std::copy(yy.data(), yy.data() + n, y);
}

#endif // INCLUDED_MEX_HELPERS_HPP
