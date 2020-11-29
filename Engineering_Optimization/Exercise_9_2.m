%% Hooke and Jeeves
% ********** Exercise 9.2 *************************************************

% ********** Parameter definition *****************************************
density = 7800;
max_stress = 200.E6;
force = 10000.0;
lb = [0.0,0.2];
ub = [1.0,2.0];
syms x y;

% ********** Objective function *******************************************
mass_sym = calc_mass(x,y,density,force,max_stress);
mass = matlabFunction(mass_sym, 'Vars', {[x y]});
% ********** Search parameters ********************************************
x0=[0.2,0.2];
rstep = 10
stepsize = (ub-lb)./rstep
minstep = 1e-3;

% ********** Hooke and Jeeves *********************************************

%-------temp plot ---------
hold on;
ezsurf(mass_sym, [lb(1),ub(1),lb(2),ub(2)]);
view(-40, -40); 
%--------------------------
[ x, fval, func_calls ] = HookeAndJeeves( x0, rstep, stepsize, minstep, mass,'.r')
%hold off;
disp('------------------------------------')
rstep = 10
stepsize = (ub-lb)./2
[ x, fval, func_calls ] = HookeAndJeeves( x0, rstep, stepsize, minstep, mass,'.g')
disp('------------------------------------')
rstep = 12.5
stepsize = (ub-lb)./10
[ x, fval, func_calls ] = HookeAndJeeves( x0, rstep, stepsize, minstep, mass,'.y')
disp('------------------------------------')
rstep = 4
stepsize = (ub-lb)./4
[ x, fval, func_calls ] = HookeAndJeeves( x0, rstep, stepsize, minstep, mass,'.m')
disp('------------------------------------')
