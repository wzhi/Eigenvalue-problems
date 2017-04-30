function [S, lambdas, converged, r] = EigenPairs(apply, n, k, varargin)
%EIGENPAIRS  Dominant eigenpairs of a symmetric matrix operator.
% [S,L]=EIGENPAIRS(A) computes the complete eigendecomposition
%                     A*S = S*DIAG(L)
% of a matrix A, where {S(:,i), L(i)} is the i'th eigenpair.
%
% [S,L]=EIGENPAIRS(APPLY,N) works with a function APPLY that computes a
% matrix-vector product APPLY(X)=A*X with N=LENGTH(A).
%
% EIGENPAIRS(APPLY,N,K) returns the partial eigendecomposition comprising
% just the K dominant eigenpairs.
%
% EIGENPAIRS(APPLY,N,K,TOL,MAXIT) uses the convergence test
%     MAX(ABS(APPLY(S) - S*DIAG(LAMBDA))) < TOL
% or terminates the iteration for any single eigenpair after MAXIT steps.
%
% [S,L,CONVERGED]=EIGENPAIRS(..) indicates convergence to the specified
% tolerance if CONVERGED is TRUE.
%
% See also EIG, EIGS, POWER, SHIFTINVERT.

narginchk(1, inf)

if isnumeric(apply)
    assert(ismatrix(apply), 'Operator should be matrix-valued')
    assert(isreal(apply), 'Operator should be real-valued')
    assert(isequal(apply', apply), 'Operator should be symmetric')
    if nargin < 2 || isempty(n)
        n = length(apply);
    end
    apply = @(x) apply*x; % uniform interface to matrix product
end

if nargin < 3 || isempty(k)
    k = n;
end

assert(k <= n)

% Pre-allocate outputs
S = zeros(n, k);
lambdas = zeros(k, 1);
r = cell(1, k); % maximum relative residuals for each eigenpair

for i = 1 : k
    
    % Deflate locked eigenpairs
    % TODO
    % deflated = @(x) apply(x) - "TODO";
    
    deflated = @(x) Deflate(lambdas, S, x, apply(x));
    
    % Determine next eigenpair
    % TODO
    [s, lambda, converged, rnorm] = Power(deflated, n, varargin{1},varargin{2});
    
    if ~converged
        break;
    end
    
    % Expand outputs (locked eigenpairs)
    % TODO
    S(:,i)=s;
    lambdas(i,1)=lambda;
    r{1,i}=rnorm;
    
end
