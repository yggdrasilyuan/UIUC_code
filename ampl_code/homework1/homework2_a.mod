# decision variables
var x{1..5}>=0,<=100;
var y{1..6}>=0;
var z{1..6}>=0;

## objective function

maximize value:z[6];

## constraints
subject to cons1:x[1]+y[1]+y[2]-z[1]=200;
subject to cons2:1.005*z[1]+x[2]+y[3]-1.01*y[1]-z[2]=-100;
subject to cons3:1.005*z[2]+x[3]+y[4]-z[3]=150;
subject to cons4:1.005*z[3]+y[5]+x[4]-1.05*y[2]-z[4]=-50;
subject to cons5:1.005*z[4]+x[5]-1.04*y[3]-z[5]=300;
subject to cons6:1.005*z[5]-1.02**5*x[1]-1.02**4*x[2]-1.02*x[5]-1.02**3*x[3]-1.05*y[4]-1.02**2*x[4]-1.03*y[5]-z[6]=-600;

options solver gurobi;

solve;

display x,y,z,value;