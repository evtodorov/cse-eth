%% Exercise 3.2 Wire length
% Optimize the length of a wire given the start point Pstart = (50,50)
% and the end point Pend=(50,350). The wire is positioned in three planes 
% through top, side and bottom brick faces with a=500 b = 400 t=75.
% Solve as unconstrained problem.

%% Task 3.2.a
% Given:
a = 500;    %mm
b = 400;    %mm
t = 75;     %mm
xs= 50;     %mm
ys= 50;     %mm
xe= 50;     %mm
ye= 350;    %mm

%Variables:
syms y1 y2 real;

% Define the objective function L. 
L = sqrt( (a - xs)^2 + (y1 - ys)^2 ) + ...  %front face
    sqrt( (y2- y1)^2 +    t^2      ) + ...  %side face
    sqrt( (xe - a)^2 + (ye - y2)^2 );       %rear face

% Calculate the shortest wire length Lmin directly using the optimality conditions.
gradL = [diff(L,y1) diff(L, y2)];
sol = solve(gradL==0,[y1 y2]);
disp(['y1 = ' num2str(eval(sol.y1))])
disp(['y2 = ' num2str(eval(sol.y2))])
% Test for the type of stationary point.
hessL = hessian(L);
hessL_num = eval(subs(hessL,[y1 y2],[sol.y1 sol.y2]))
eigs = eig(hessL_num) %minimum <=> all eigs are positive
if eigs > 0
disp('Positive eigenvalues <=> positive deifnite matrix <=> minimum')
end
% Display a contour plot of the objective function with the minimum point shown
hold on;
ezcontour(L, [0 b 0 b]);
plot(sol.y1, sol.y2, 'r*')
hold off;

%Comment: The optimization converges to the logical solution, that the
%optimum solution is equivalent to a straight line if the wall is
%"unfolded".