%% Exercise 3.3 Slider-crank mechanism optimization
% Find the lengths of the crank and rod to maximize the velocity at crank
% angle of 30 degrees for constant angular velocity of 100 Hz
clear;
%Parameters:
theta = deg2rad(30);%degrees (angle b/n axis and crank)
w     = 100;        %Hz

%Variables:
syms r L positive; %crank length, rod length
%intermediate
syms th real; %symbolic theta for intermediate steps
alpha = asin(r/L*sin(th));%rad (angle b/n axis and rod, from sin theorem)
beta  = pi - th - alpha; %rad 
S = sin(beta)*L/sin(th); %distance along axis. sin theorem again

%function to optimize
V = abs(subs(diff(S,th)*w,th,theta));%v=ds/dt= ds/dtheta * dtheta/dt @ theta=30

%constraints
S = subs(S,th,theta);
g1  = L - 2.5*r;
g21 = S - 10;
g22 = 20 - S;
g31 = r - 0.5;
g32 = 10 - r;
g41 = L - 2.5;
g42 = 25 - L;

%plot
domain = [0 30 0 12];
hold on;
ezcontour(V,domain)
%ezplot(g1==0,domain)
%ezplot(g21==0,domain)
%ezplot(g22==0,domain)
%ezplot(g31+1e-6*L==0,domain)
%ezplot(g32+1e-6*L==0,domain)
%ezplot(g41+1e-6*r==0,domain)
%ezplot(g42+1e-6*r==0,domain)

%plot conclusion -> everything at S = 10 is solution

%optimization
options = optimoptions(@fmincon,...
          'Display', 'iter-detailed');
f = @(x) eval(subs(-V,[L r],[x(1) x(2)]));
g = matlabFunction(-V, 'Vars',{[L r]});
nonlcon = @(x) nonlcon_3_3( x, g21, g22, L, r );
lb = [2.5 0.5];
ub = [25  10];
A = -[1 -2.5];
b = [0];
x0 = [15 5];
[x,fval] = fmincon(g,x0,A,b,[],[],lb,ub,nonlcon,options);
%plot(x0(1), x0(2), 'r*');
%plot(x(1), x(2), 'g*');