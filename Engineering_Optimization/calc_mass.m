function [mass] = calc_mass(x,y,density,force,max_stress)

% ********** Calculate angles *********************************************
ang1=atan(y/x);
ang2=atan(y/(1.-x));

% ********** Calculate forces in members **********************************
t1=(-force/2.0)/sin(ang1);
t2=-t1*cos(ang1);
t3=-t1*sin(ang1)/sin(ang2);
t4=(t1*cos(ang1))-(t3*cos(ang2));

% ********** Calculate the lengths ****************************************
l1=sqrt(x^2+y^2);
l2=1.0;
l3=sqrt((1-x)^2+y^2);
l4=1-x;              %calculate half of 14 so that mass can just be doubled

% ********** Calculate areas for fully stressed design ********************
a(1)=abs(t1)/max_stress;
a(2)=abs(t2)/max_stress;
a(3)=abs(t3)/max_stress;
a(4)=abs(t4)/max_stress;

% ********** Calculate force times length for each member *****************
v1=a(1)*l1;
v2=a(2)*l2;
v3=a(3)*l3;
v4=a(4)*l4;

% ********** Calculate the mass *******************************************
mass=2.0*density*(v1+v2+v3+v4);
end

