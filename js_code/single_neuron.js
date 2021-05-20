var Unit = function(value, grad){
  //value computed in forward pass
  this.value = value;

  //the derivative of circuit ouput w.r.t this unit computed
  //in backward pass
  this.grad = grad;
}

var multiplyGate = function(){ };
multiplyGate.prototype = {
  forward: function(u0, y1){
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
