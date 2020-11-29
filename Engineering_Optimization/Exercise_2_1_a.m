%% Exercise 2.1
% Back to the cardboard box optimization
%
% An open top cardboard box for packing is to be manufactured as shown in the figure below. 
% The objective is to find the minimum material cost for a required volume and subject to set of bounding constraints. 
% Assume that the material cost equals the outer surface area of the box.

%initial guess
x0 = [10. 25.];

%Optimization options
options = optimoptions(@fminunc, ...        %funtion to optimize
        'Algorithm', 'trust-region', ...    %algorithm selection
        'GradObj', 'on',...                 %gradients are provided
        'Display', 'iter-detailed', ...     %Command window output
        'PlotFcns', @optimplotfval);        %Builr-in plot function call

 %Solve
 [x,fval,exitflag,output] = fminunc(@CardboardBoxGrad, x0, options);
 