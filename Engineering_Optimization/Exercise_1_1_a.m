%% This script is the solution of Exercise 1.1a of the Engineering optimization course
%  author: etodorov

%define symbloic variables
xt = sym('xt');     %thickness
yD = sym('yD');     %diameter

%parameters and constants
P = 45e+3;          % N (load)
L = 2540;           % mm (length)
E = 206e+3;         % MPa (Young's modulus)
rho = 7.83e-6;      % kg/mm3 (density)
s_y = 248;          % MPa (yield strenght)

%set plot boundaries 
domain = [1 5 1 75];    % [xmin xmax ymin ymax]

%objective
m = rho*pi*xt*yD*L;     % kg (mass)

%constraints  g <= 0
g1 = P/(pi*yD*xt) - s_y == 0;% stress constraint 

q = m*9.81/L;           % N/mm (line weight)
I = pi*yD^3*xt/8.0;     % mm^4 (moment of inertia)
delta = 5*q*L^4/384.0/E/I; % mm (displacement)
g2 = delta - 0.001*L == 0;    % displacement constraint

g3 = 1.25 - xt == 0;          % geometric constraint

%plot
hold on;
ezcontour(m, domain); 
ezplot(g1, domain);
ezplot(g2 + xt, domain);
ezplot(g3 + yD, domain);
hold off;