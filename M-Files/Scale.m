function y = Scale(alpha, x)
%SCALE Scalar multiplication.
% SCALE(ALPHA,X) multiplies an array X by the scalar ALPHA.
% This is a literal translation of the MEx-file SCALEMEX, and 
% is only intended to provide a familiar contrast.
% See also TIMES.

% Check for proper number of input and output arguments
if 2 ~= nargin
    error('Expected two input arguments.')
end

if 1 < nargout
    error('Expected one output argument.')
end

if ~isnumeric(alpha) || ~isscalar(alpha)
    error('First argument must be a scalar numeric type.')
end

if ~isnumeric(x)
    error('Second argument must be numeric')
end

% We would never write MATLAB code like this in practice!
% Rather, we would prefer "y = alpha*x".
y = zeros(size(x));
for i = 1 : numel(x)
    y(i) = alpha*x(i);
end
