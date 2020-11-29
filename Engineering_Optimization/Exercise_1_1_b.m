%% This script is the solution of Exercise 1.1a of the Engineering optimization course
%  author: etodorov

%define variables
xt = linspace(1,5);     %thickness
yD = linspace(1,75)';     %diameter

%parameters and constants
P = 45e+3;          % N (load)
L = 2540;           % mm (length)
E = 206e+3;         % MPa (Young's modulus)
rho = 7.83e-6;      % kg/mm3 (density)
s_y = 248;          % MPa (yield strenght)

%objective
m = rho*pi*yD*xt*L;     % kg (mass)

%constraints  g <= 0
g1 = P./(pi*yD*xt) - s_y;% stress constraint 

q = m*9.81/L;           % N/mm (line weight)
I = pi*yD.^3*xt/8.0;     % mm^4 (moment of inertia)
delta = 5*q*L^4/384.0/E./I; % mm (displacement)
g2 = delta - 0.001*L;    % displacement constraint

g3 = 1.25 - xt;          % geometric constraint

%plot
hold on;
contour(xt, yD, m);
contour(xt, yD, g1, [0 0]);
contour(xt, yD, g2, [0 0]);
contour(xt, yD, ones(size(yD))*g3, [0 0]);
hold off;