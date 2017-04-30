function y = Deflate(lambdas, S, x, y)
y = y - S*(diag(lambdas)*(S.'*x));
