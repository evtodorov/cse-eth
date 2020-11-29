f_ = @(a,b) a*b + 2e+6/b + 2e+6 /a;
f  = @(x) f_(x(1),x(2));

x0 = [40 200];

options = optimoptions(@fmincon,...
          'Display', 'iter-detailed', ...
          'PlotFcns', @optimplotfval);
 
lb = [40 40];
ub = [200 200];
% -.75*x1 + x2 < 0
A = [-.75 1];
b = [0];

[x,fval] = fmincon(f,x0,A,b,[],[],lb,ub,@nonlcon_2_1_e,options);