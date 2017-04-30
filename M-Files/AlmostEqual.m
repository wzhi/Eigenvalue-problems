function result = AlmostEqual(x, y, tol) 
%ALMOSTEQUAL  True if relative difference is small.
narginchk(2, 3)
if nargin < 3 || isempty(tol)
    tol = 1e-12;
end
result = norm(Compare(x(:), y(:)), inf) < tol;
