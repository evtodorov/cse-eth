function [ c, ceq ] = nonlcon_3_3( x, g21, g22, L, r )
%Non-linear inequality and equality constraints for Exercise_3_3_e
%   Detailed explanation goes here
c = [eval(subs(g21,[L r],[x(1) x(2)])), ...
     eval(subs(g22,[L r],[x(1) x(2)]))];
ceq = [];
end
