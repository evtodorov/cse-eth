function stop = myplot3(x,optimValues,state) %Default PlotFcns or OutputFcn defintions
    stop = false;            %Default (expected) output
    fval = optimValues.fval; %Get value from struct
    
    density = 7800;
    max_stress = 200.E6;
    force = 10000.0;
    syms x_ y_;
switch state %switch-case depending on different value in state
    case 'init' %Initial optimization step - x0
        f = calc_mass(x_,y_,density,force,max_stress);         %Inline function definition
        h = ezsurf(f, [0.0, 1.0, 0.2, 2.0]);                  %Surface plot
        h.EdgeColor = 'none';
        view(-40, -40);                                      %Plot view angle
        hold on;                                            %Plot to same chart
    case 'iter' %Iteration steps - x
        plot3(x(1), x(2), fval, 'r.', 'MarkerSize', 20);    %Plot point x(x(1), x(2));
    case 'done' %Final step - x*
        plot3(x(1), x(2), fval, 'm.', 'MarkerSize', 40);    %Plot point x(x(1), x(2));
end

