var x = -2, y = 3;
var forwardMultiplyGate = function(x,y) {return x*y;};
var out = forwardMultiplyGate(x,y);

var h = 0.0001;

//computing derivative w.r.t x
var xph = x + h;
var out2 = forwardMultiplyGate(xph, y);
var x_derivative = (out2-out)/h;

//coumputing derivative w.r.t y
var yph = y + h;
var out3 = forwardMultiplyGate(x, yph);
var y_derivative = (out3- out)/h;

console.log(x_derivative, y_derivative);

//computing new out
var step_size = 0.01;
x = x + step_size*x_derivative;
y = y + step_size*y_derivative;
var out_new = forwardMultiplyGate(x,y);
console.log(out_new, out);
