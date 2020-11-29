%% Exercise 2.2.b
%parameters
global F L tw tf E rho;
F = 50e+3;  %N
L = 2e+3;   %mm
tw= 8;      %mm
tf= 15;     %mm
E = 206e+3; %MPa
rho=7.85e-6;%kg/mm3

Sy = 120;   %MPa
delta = 4;  %mm

%variables
syms h w positive;

%objective
m = rho*L* ( (h-2*tf)*tw + 2*tf*w );    %kg
%mGrad_h = rho*L*tw
%mGrad_w = rho*L*2*tf

%constraints f(x) <= 0
M = 0.125*F*L;  %Nm
I = tw*(h-2*tf)^3 /12. ...
    + 2*( ...
            w*tf^3/12. ...
         +  w*tf*( (h-tf)/2. ) ^2 ...
               ); %mm4
g1 = M*h/I/2.      - Sy;    %MPa (yield stress)
g2 =0.013*F*L^3/E/I-delta;  %mm  (max deflection)

%graphics
domain = [40 160 30 130];
hold on;
figure(1);
ezcontour(m, domain); 
ezplot(g1==0,domain);
ezplot(g2==0,domain);

%symbolic to matlab
m = matlabFunction(m, 'Vars', {[h w]});
g = matlabFunction([g1; g2], 'Vars', {[h w]});

%guesses
lb = [50 40];
ub = [150 120];
x0 = [120 110];

%optimization
options = optimoptions(@fmincon,...     %solver
        'Display', 'iter-detailed',...  %
        'PlotFcns', @optimplotfval);

[x, fval] = fmincon(m,x0,[],[],[],[],lb,ub,...
            @(x) wrapper_nonlcon(g (x) ),...
            options);
  figure(1);
 plot(x(1),x(2),'pr');