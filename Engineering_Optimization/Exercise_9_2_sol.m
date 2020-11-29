%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%EDIT: The starting point in "Exercise_9.m" should have been x0 =[0.2,0.2]
%%Solutions in pdf belong to the starting point x0 =[0.2,0.2]%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ********** Exercise 9.2 *************************************************
clc;

% ********** Parameter definition *****************************************
density = 7800;
max_stress = 200.E6;
force = 10000.0;
lb = [0.0,0.2];
ub = [1.0,2.0];
n = 2;                          %number of variables, in this case x and y
rstep = 10;                     %step-size factor
rstep2 = 10;
x0 =[0.2,0.2];

% ********** Initialization ***********************************************
x = x0;
min_step = 0.001;
mass0 = calc_mass(x(1),x(2),density,force,max_stress);
massp = mass0; 
mass = mass0;
step = [(ub(1)-lb(1))/rstep,(ub(2)-lb(2))/rstep];
stepp = [0,0];
xb = x;
eval = 0;
% ********** Hooke and Jeeves *********************************************
while((step ~= stepp) | (mass < massp))
    xp = x;
    stepp = step;
    
    %treat each variable in turn
    for i=1:n
        massp = mass;
        x(i) = xp(i) + step(i);
        mass = calc_mass(x(1),x(2),density,force,max_stress);
        eval = eval + 1;
        if(mass >= massp)
            x(i) = xp(i)-step(i);
            mass = calc_mass(x(1),x(2),density,force,max_stress);
            eval = eval + 1;
            if(mass >= massp)
                x(i) = xp(i);
                mass = massp;
            end
        end
    end
    
    %check if no move was made and reduce step sizes
    if(x == xp)
        for i=1:n
            if(step(i) > min_step)
                step(i) = step(i) / rstep2;
            end
        end
    else
        
        %try pattern move
        xp = x;
        masspm = mass;
        for i=1:n
            x(i) = x(i)+(x(i)-xb(i));
        end
        mass = calc_mass(x(1),x(2),density,force,max_stress);
        eval = eval + 1;
        if(mass >= masspm)
            x = xp;
            mass = masspm;
        end
        % record new base point
        xb = xp;
    end
end

            
    
    