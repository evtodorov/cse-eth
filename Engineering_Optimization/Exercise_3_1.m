%% Exercise 3.1 Carboard box optimization
% An open top cardboard box for packing is to be manufactured as shown in the figure below. 
%The task is to find the minimum material cost for a required volume 
%given the cost function S(a,b) using MATALB symbolic computation
%Calculate the stationary points and check sufficiency conditions for the local minimum. 

syms a b real;

S = a*b+2e+6/b+2e+6/a;

gradS = [diff(S,a); diff(S,b)];
statPoints = solve(gradS==0,[a b]);

disp('Stationary points:');
a0 = eval(statPoints.a);
b0 = eval(statPoints.b);
disp([ 'a= ' num2str(a0) '; '... 
       'b= ' num2str(b0)]);

disp('Hessian:')
hessS = hessian(S,[a,b]);
disp('Hessian eigenvalues')
eval(eig(subs(hessS,[a b], [a0 b0])))