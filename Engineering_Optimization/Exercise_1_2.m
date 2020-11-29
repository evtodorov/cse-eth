%% Solution to exercies 1.2: Minimize the cost of column in compression

%define symbloc variables
syms D t;

%set plot boundries
domain = [10 150 1 9];  % [xmin xmax ymin ymax] = [Dmin Dmax tmin tmax]

%constants 
g = 9.81;               % [m/s^2] earth gravitiational acceleration 

%parameters
P = 24500.;             % [N] compressive load
L = 2500.;              % [mm] length
E = 83400.;             % [MPa] Young's modulus
rho = 2.5e-6;           % [kg/mm^3] density
s_y = 49.;               % [MPa] yield strength

%intermediates
A = pi*D*t;             % [mm^2] area
I = A*(D^2+t^2)/8.;     % [mm^4] moment of inertia
w = rho*A*L*g;          % [N] weight

%objective
f = 5*w + 2*D;          % cost

%constraints g <= 0
g1 = P/A - s_y == 0;    %stress
g2 = P/A - pi^2*E*I/L^2/A == 0; %buckling
g3 = 20 - D == 0;       %geometric
g4 = D - 140 == 0;      %geometric
g5 = 2 - t == 0;        %geometric
g6 = t -8 == 0;         %geometric

%plots
hold on;

plot1 = ezplot(g1, domain); set(plot1, 'Color', 'Red');
plot2 = ezplot(g2, domain); set(plot2, 'Color', 'Yellow');
plot3 = ezplot(g3 + t, domain);
plot4 = ezplot(g4 + t, domain);
plot5 = ezplot(g5 + D, domain);
plot6 = ezplot(g6 + D, domain);
ezcontour(f,domain);

%observe that optimum solution is intersection of buckling and geometric
%(g2, g5)
%solve for the location of that intersection
opt = solve(g2,g5);
opt_t = eval(opt.t);
opt_D = eval(opt.D);
plot(opt_D,opt_t,'ro','MarkerSize',10);
hold off;