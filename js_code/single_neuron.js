var Unit = function(value, grad){
  //value computed in forward pass
  this.value = value;

  //the derivative of circuit ouput w.r.t this unit computed
  //in backward pass
  this.grad = grad;
}

var multiplyGate = function(){ };
multiplyGate.prototype = {
  forward: function(u0, u1){
    //store pointers to input Units u0 and u1 and
    //output unit utop
    this.u0 = u0;
    this.u1 = u1;
    this.utop = new Unit(u0.value * u1.value, 0.0);
    return this.utop;
  },
  backward: function(){
    this.u0.grad += this.u1.value * this.utop.grad;
    this.u1.grad += this.u0.value * this.utop.grad;
  }
}

var addGate = function(){ };
addGate.prototype = {
  forward: function(u0, u1){
    this.u0 = u0;
    this.u1 = u1;
    this.utop = new Unit(u0.value + u1.value, 0.0);
    return this.utop;
  },
  backward: function(){
    //add gate derivative wrt both inputs is 1
    this.u0.grad += 1* this.utop.grad;
    this.u1.grad += 1* this.utop.grad;
  }
}

var sigmoidGate = function() { 
  // helper function
  this.sig = function(x) { return 1 / (1 + Math.exp(-x)); };
};
sigmoidGate.prototype = {
  forward: function(u0) {
    this.u0 = u0;
    this.utop = new Unit(this.sig(this.u0.value), 0.0);
    return this.utop;
  },
  backward: function() {
    var s = this.sig(this.u0.value);
    this.u0.grad += (s * (1 - s)) * this.utop.grad;
  }
}

var a = new Unit(1.0, 0.0);
var b = new Unit(2.0, 0.0);
var c = new Unit(-3.0, 0.0);
var x = new Unit(-1.0, 0.0);
var y = new Unit(3.0, 0.0);

//creating gates
var mulg0 = new multiplyGate();
var mulg1 = new multiplyGate();
var addg0 = new addGate();
var addg1 = new addGate();
var sg0 = new sigmoidGate();

//do the forward pass
var forwardNeuron = function() {
  ax = mulg0.forward(a, x);
  by = mulg1.forward(b, y);
  axpby = addg0.forward(ax, by);
  axpbypc = addg1.forward(axpby, c);
  s = sg0.forward(axpbypc);
};
forwardNeuron();

console.log('cicuit output: ' + s.value);

//simply iterating in reverse order to backprop
s.grad = 1.0;
sg0.backward();
addg1.backward();
addg0.backward();
mulg1.backward();
mulg0.backward();

var step_size = 0.01;
a.value += step_size * a.grad; // a.grad is -0.105
b.value += step_size * b.grad; // b.grad is 0.315
c.value += step_size * c.grad; // c.grad is 0.105
x.value += step_size * x.grad; // x.grad is 0.105
y.value += step_size * y.grad; // y.grad is 0.210

forwardNeuron();
console.log('circuit output after one backprop: ' + s.value); // prints 0.8825

