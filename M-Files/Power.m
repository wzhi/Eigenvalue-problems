function [s, lambda, converged, rnorm] = Power(apply, n, tol, maxit)
%POWER Eigenpair of a symmetric matrix via the power method.
% [S,LAMBDA]=POWER(A) computes the dominant eigenvalue LAMBDA and the
% associated eigenvector S of a symmetric matrix A i.e.
%                     A*S = S*LAMBDA.
%
% [S,LAMBDA]=POWER(APPLY,N) where APPLY is a function that computes a
% matrix-vector product APPLY(X)=A*X and N=LENGTH(A).
%
% POWER(APPLY,N,TOL,MAXIT) uses the convergence test
%     MAX(ABS(A*S - S*LAMBDA)) < TOL
% or terminates the iteration after MAXIT steps.
%
% [S,LAMBDA,CONVERGED]=POWER(..) indicates convergence to the specified
% tolerance if CONVERGED is TRUE.
%
% [S,LAMBDA,CONVERGED,RNORM]=POWER(..) returns an array of residual norms
%  MAX(ABS(A*S - S*LAMBDA)), with one value for each iteration.
%
% See also EIG, EIGS, EIGENPAIRS, SHIFTINVERT.

narginchk(1, 4)

% Accommodate numeric operators
if isnumeric(apply)
    assert(ismatrix(apply), 'Operator should be matrix-valued')
    n = length(apply);
    apply = @(x) apply*x; % uniform interface to matrix product
end

if nargin < 3 || isempty(tol)
    tol = eps(10);
end

if nargin < 4 || isempty(maxit)
    maxit = 500;
end

% Initial estimate of eigenvector
s = 2*rand(n, 1) - 1;
s = s/norm(s);

% Initialise
iter = 0;
converged = false;
rnorm = zeros(1, maxit);
lambda=1;
while iter < maxit && ~converged
    
    assert(Compare(norm(s), 1) < tol, 'Invariant')
    
    % Apply operator
    % TODO
    As=apply(s);
    
    % Estimate eigenvalue magnitude
    % TODO
    
    lambda=norm(As);
    
    
    % Eigenvalue sign
    lambda=sign(dot(As,s))*lambda;
    
    % Convergence test
    iter = iter + 1;
    rnorm(iter) = norm(Compare(As, s*lambda), inf);
    converged = rnorm(iter) < tol;
    
    % Normalise result (or next iterate)
    s = As/norm(As);
    
end

% Release unused entries
rnorm(iter + 1 : end) = [];

if ~converged && nargout < 3
    message = 'Didn''t converge to desired tolerance of %g in %d steps';
    warning(message, tol, iter)
end
