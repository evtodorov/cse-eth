function [ x, fval, func_calls, itters ] = HookeAndJeeves( x0, rstep, stepsize, minstep, func, plot )
%Implementation of the Hooke and Jeeves search method
%[ x, fval, func_calls, itters ] = HookeAndJeeves( x0, rstep, stepsize, minstep, func )
% Input:
%   x0          - initial position
%   rstep       - reduction factor
%   stepsize    - initial stepsize
%   minstep     - minimum allowed stepsize
%   func        - the function to be optimized (single input)
% Output:
%   x           - optimum location
%   fval        - optimum value
%   func_calls  - number of calls to the objective function
%   itters      - number of itterations 
conditions = 1;
optimum = func(x0);
func_calls = 1;
baseX = x0;
itters = 0;

while conditions
%Documentation:
%x0     is the point from which the exploration starts
%x      is the point to which the exploration moves
%baseX  is the BASE POINT
%trial  is  the value of the function at the current point
%optimum is the best value achieved so far

%----temp plot---------
    plot3(baseX(1),baseX(2),optimum, plot, 'MarkerSize', 20)
    text(baseX(1),baseX(2),optimum, int2str(itters),'Color','yellow','FontSize',12);
%----------------------

    itters = itters + 1;
    %Attempt exploratory move
    x = x0;
    for i=1:length(x0)
        %positive step
        x(i) = x0(i) + stepsize(i);
        trial = func(x);
        func_calls = func_calls + 1;
        if trial < optimum
            optimum = trial;
            continue;
        end
        %negative step
        x(i) = x0(i) - stepsize(i);
        trial = func(x);
        func_calls = func_calls + 1;
        if trial < optimum
            optimum = trial;
            continue;
        end
        %if it doesn't get better
        x(i) = x0(i);   %back to the initial
    end
    %If no moves
    if all(x==baseX)
        if all(stepsize <= minstep)
            conditions = 0;
        else
            stepsize = stepsize .* ( (stepsize > minstep)/rstep + (stepsize <= minstep) );
        end
        continue;
    end
    %Set base-point
    x0 = x + (x-baseX);
    baseX = x;
    %Attempt pattern move
    trial = func(x0);
    func_calls = func_calls + 1;
    if trial <= optimum
        optimum = trial; 
    else
        x0 = baseX;
    end
end
x = x0;
fval = optimum;

end

