%% Exercise 3.2 Wire length
% Optimize the length of a wire given the start point Pstart = (40,40)
% and the end point Pend=(50,350). The wire is positioned in three planes 
% through top, side and bottom brick faces with a=500 b = 400 t=75.
% Solve as unconstrained problem.

%% Task 3.2.b
%Select an appropriate numerical optimization method from MATALB toolbox 
%and find the optimum for starting point (40 40)
% Given:
a = 500;    %mm
b = 400;    %mm
t = 75;     %mm
xs= 40;     %mm
ys= 40;     %mm
xe= 50;     %mm
ye= 350;    %mm

%Variables:
syms y1 y2 real;

% Define the objective function L. 
L = sqrt( (a - xs)^2 + (y1 - ys)^2 ) + ...  %front face
    sqrt( (y2- y1)^2 +    t^2      ) + ...  %side face
    sqrt( (xe - a)^2 + (ye - y2)^2 );       %rear face

% Select an appropriate numerical optimization method
options = optimoptions('fminunc',...
            'Algorithm', 'Quasi-Newton',...     %no gradients provided
            'Display', 'iter',...
            'PlotFcns', @optimplotfval);        %Display function value over iteration plot
x0 = [200 200]; %start in the middle of the wall
[x, fval]=fminunc(@(x) eval(subs(L, [y1 y2], x)),x0,options);
%Comment: The optimization converges to the logical solution, that the
%optimum solution is equivalent to a straight line if the wall is
%"unfolded".
