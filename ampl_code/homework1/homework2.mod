# decision variables
var x1>=0;
var x2>=0;
var x3>=0;
var x4>=0;
var x5>=0;
var x6>=0;
var y1>=0;
var y2>=0;
var y3>=0;
var y4>=0;
var y5>=0;
var z1>=0;
var z2>=0;
var z3>=0;
var z4>=0;
var z5>=0;
var z6>=0;


## objective function

maximize value:z6;

## constraints
subject to cons1:x1+y1+y2-z1=200;
subject to cons2:1.005*z1+x2+y3-1.02*x1-1.01*y1-z2=-100;
subject to cons3:1.005*z2+x3+y4-1.02*x2-z3=150;
subject to cons4:1.005*z3+y5+x4-1.02*x3-1.05*y2-z4=-50;
subject to cons5:1.005*z4+x5-1.02*x4-1.04*y3-z5=300;
subject to cons6:1.005*z5-1.02*x5-1.05*y4-1.03*y5-z6=-600;
subject to cons7:x1<=100;
subject to cons8:x2<=100;
subject to cons9:x3<=100;
subject to cons10:x4<=100;
subject to cons11:x5<=100;
subject to cons12:x6<=100;
