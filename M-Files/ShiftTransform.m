function [apply, recover] = ShiftTransform(A, sigma)
%SHIFTTRANSFORM Computes a shift transformation.
% APPLY=SHIFTTRANSFORM(A,SIGMA) returns a function handle such that
%          APPLY(X) = (A - SIGMA*EYE(SIZE(A))*X.
% [APPLY,RECOVER]=SHIFTTRANSFORM(A,SIGMA) also returns a function 
% handle to the inverse transform
%          RECOVER(MU) = MU + LAMBDA
% SHIFTTRANSFORM(A) uses a zero shift, SIGMA = 0.0.
if nargin < 2 || isempty(sigma)
    sigma = 0.0;
end
    function y = Apply(x)
        y = A*x - x*sigma;
    end
    function lambda = Recover(mu)
        lambda = sigma + mu;
    end
apply = @Apply;
recover = @Recover;
end
