f_ = @(a,b) a*b + 2e+6/b + 2e+6 /a;
f  = @(x) f_(x(1),x(2));

x0 = [40 200];

options = optimoptions(@fmincon,...
          'Display', 'iter-detailed', ...
          'PlotFcns', @optimplotfval);
 
lb = [40 40];
ub = [200 200];

[x,fval] = fmincon(f,x0,A,b,[],[],lb,ub,[],options);