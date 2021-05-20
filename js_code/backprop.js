var forwardAddGate = function(x, y){return x + y;};
var forwardMulGate = function(x, y){return x*y;};

var x = -2, y = 5, z = -4;
var q = forwardAddGate(x,y);
var f = forwardMulGate(q, z);
console.log(x,y,z,q,f);

//gradient of MULTIPLY gate w.r.t its input
var derivative_f_wrt_z = q;
var derivative_f_wrt_q = z;

//gradient of add gate w.r.t its inputs
var derivative_q_wrt_x = 1.0;
var derivative_q_wrt_y = 1.0;

//chain rule
var derivative_f_wrt_x = derivative_q_wrt_x * derivative_f_wrt_q;
var derivative_f_wrt_y = derivative_q_wrt_y * derivative_f_wrt_q;

var gradient_f_wrt_xyz = [derivative_f_wrt_x, derivative_f_wrt_y, derivative_f_wrt_z];

//changing inputs
var step_size = 0.01
x = x + step_size * derivative_f_wrt_x;
y = y + step_size * derivative_f_wrt_y;
z = z + step_size * derivative_f_wrt_z;

var q = forwardAddGate(x, y);
var f = forwardMulGate(q, z);

console.log(x, y, z, q, f);