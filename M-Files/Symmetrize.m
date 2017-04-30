function A = Symmetrize(A)
%SYMMETRIZE  Symmetric part of a matrix
A = 0.5*(A + A');
