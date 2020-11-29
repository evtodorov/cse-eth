function [ stop ] = myplot( x, optimValues, state )
% Custom plot function for Exercise_2_1_b
%   This function plots both the objective function as well as the 
%   optimization iteration steps
%
%   Syntax based on >> web(fullfile(docroot, 'optim/ug/optimization-options-reference.html'))

stop = false;
fval = optimValues.fval;
a    = x(1);
b    = x(2);
switch state
    case 'init'
        hold on;
        foo = @(x,y) x.*y + 2e+6./x + 2e+6./y;
        ezsurf(foo,[.01 250 .01 250]);
        view(115,40);
        plot3(a,b,fval, '.b', 'MarkerSize', 30);
    case 'iter'
        plot3(a,b,fval, '.r', 'MarkerSize', 20);
    case 'done'
        plot3(a,b,fval, '.g', 'MarkerSize', 40);
end %switch state
 
end %myplot
