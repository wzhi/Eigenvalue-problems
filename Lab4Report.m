%% Lab Assignment 4: Numerical Methods for Eigenvalue Problems

%%
clear, rng(0)
addpath(fullfile(pwd, 'M-Files'))

%% Task 1: Shift-and-Invert transform
dbtype ShiftInvertTransform
%%
% Test case
A = [4 -4 -3 -3 2; -4 -2 5 0 -4; -3 5 5 5 4; -3 0 5 3 5; 2 -4 4 5 2];
sigma = 3;
[apply, recover] = ShiftInvertTransform(A, sigma);
x = [3; 3; -1; 2; -3]; % arbitrary input
y = [-3979/4966; -978/2483; -53/191; -1655/4966; 977/4966]; % exact result
assert(AlmostEqual(apply(x), y))
assert(AlmostEqual(recover(1.0), 4.0))

%% Data for later tasks
n = 30;
density = min(5/n, 0.5);
rc = 0.01;
A = Symmetrize(sprand(n, n, density, rc));
k = min(n, 5);
sigma = 0; % shift/target
tol = eps(100*n);
maxit = 100*n;

%% Task 2: Power method in MATLAB
dbtype Power
%%
[apply, recover] = ShiftInvertTransform(A, sigma);
%%
[s, lambda, converged, rnorm] = Power(apply, n, tol, maxit);
assert(converged)
assert(AlmostEqual(apply(s), s*lambda))
assert(AlmostEqual(norm(s), 1.0))
assert(rnorm(end) < tol)

% Task 3: Power method in C++
dbtype(fullfile('Header Files', 'power.hpp'))
%%
AssertMexExists('PowerMex')
%%
[s, lambda, converged] = PowerMex(apply, n, tol, maxit);
assert(converged)
assert(AlmostEqual(apply(s), s*lambda))
assert(rnorm(end) < tol)

%% Task 4: Multiple eigenpairs via deflation in MATLAB
dbtype EigenPairs
%%
[S, mu, converged, r] = EigenPairs(apply, n, k, tol, maxit);
%%
assert(converged)
assert(AlmostEqual(apply(S), S*diag(mu)))
assert(AlmostEqual(S'*S, eye(k)))

%% Tasks 5 & 6: Multiple eigenpairs via deflation in C++
% dbtype(fullfile('Header Files', 'eigenpairs.hpp'))
% %%
% Task 5
AssertMexExists('DeflateMex')
%%
x = rand(n, 1); y = rand(n, 1);
assert(AlmostEqual( ...
    Deflate(mu, S, x, y), ...
    DeflateMex(mu, S, x, y)))

%%
AssertMexExists('EigenPairsMex')
%%
[S, mu, converged] = EigenPairsMex(apply, n, k, tol, maxit);
%%
assert(converged)
assert(AlmostEqual(apply(S), S*diag(mu)))
assert(AlmostEqual(S'*S, eye(k)))

%% Task 7: Theory & discussion
%
% *TODO*: Please complete Task 7 here
%
%%
% 7.b) The most computationally expensive operation in powermex
% and eigenpairsmex is the matrix multiplication in the apply command. 
% This is implemented in matlab, hence the most expensive operation in 
% both the MEX and matlab implementations have similar speed.  
%%
% 7.c) 
% $$ RHS = -(Ax)\cdot x = (A^{T}x)\cdot x = (A^{T}x)^{T}x = x^{T}Ax = x\cdot (Ax) = (Ax)\cdot x = LHS $$
%%
% 7.d)
% When $$ As= {\lambda}s=0 $$, $$ As $$ vanishes on the graph.

