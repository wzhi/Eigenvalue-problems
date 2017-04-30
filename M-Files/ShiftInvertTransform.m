function [apply, recover, elapsed] = ShiftInvertTransform(A, sigma)
%SHIFTINVERTTRANSFORM Computes a shift-invert transformation.
%
% APPLY=SHIFTINVERTTRANSFORM(A,SIGMA) returns a function handle such that
%   APPLY(X) = (A - SIGMA*EYE(SIZE(A))\X = INV(A - SIGMA*EYE(SIZE(A)))*X.
% Internally, the shifted matrix is factorized only once.
%
% [APPLY,RECOVER]=SHIFTINVERTTRANSFORM(A,SIGMA) also returns a
% function handle to the inverse transform
%          RECOVER(MU) = SIGMA + 1./MU.
%
% SHIFTINVERTTRANSFORM(A) uses a zero shift, SIGMA = 0.0.
%
% See also SHIFTTRANSFORM.

if nargin < 2 || isempty(sigma)
    sigma = 0.0;
end
elapsedTime = 0;

% TODO
[m n]=size(A);
[L U p]=lu(A-sigma.*eye(m));
    function y = Apply(x)
        tic;
        z=L\p*x;
        y=U\z;
        elapsedTime = elapsedTime + toc;
    end

    function lambda = Recover(mu)
        if any(abs(mu) < eps)
            warning( ...
                [mfilename ':SingularTransform'], ...
                'Singular transformation')
        end
        lambda=sigma+mu^(-1);
    end
    function t = Elapsed
        t = elapsedTime;
    end
apply = @Apply;
recover = @Recover;
elapsed = @Elapsed;
end
