function [ f ,g ] = CardboardBoxGrad( x )
% Objective function for Exercise_2_1_a
%   f -> function;
%   g -> gradinet;
%   x -> [a,b] vector input;
a = x(1);
b = x(2);
%define the function
f = a*b + 2e+6/b + 2e+6 /a;

if nargout > 1  %if gradient is required
    g(1) = b - 2e+6 /a^2;
    g(2) = a - 2e+6 /b^2;
end %if nargout > 1

end % CardboardBoxGrad(x)

