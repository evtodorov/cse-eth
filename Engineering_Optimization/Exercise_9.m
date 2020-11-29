% ********** Exercise 9.1 *************************************************
clc;
clear all;
close all;
% ********** Parameter definition *****************************************
density = 7800;
max_stress = 200.E6;
force = 10000.0;
lb = [0.0,0.2];
ub = [1.0,2.0];
syms x y;

% ********** Objective function *******************************************
mass = calc_mass(x,y,density,force,max_stress);
mass1 = matlabFunction(mass, 'Vars', {[x y]});

% ********** fmincon ******************************************************
x0=[0.3,0.3];
options = optimoptions(@fmincon,...     %Optimization options
    'Display', 'iter-detailed',...      %Command window output
    'PlotFcns', @myplot3);        %Built-in plot function call
[z,fval,exitflag,output] = fmincon(mass1,x0,[],[],[],[],lb,ub,[],options);