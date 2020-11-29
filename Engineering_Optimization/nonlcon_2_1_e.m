function [ c, ceq ] = nonlcon_2_1_e( x )
%Non-linear inequality and equality constraints for Exercise_2_1_e
%   Detailed explanation goes here
c = x(1)^2 - 160 * x(1) + 6400 - x(2);
ceq = [];
end

