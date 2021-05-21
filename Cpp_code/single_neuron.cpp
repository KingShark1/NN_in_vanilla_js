#include <iostream>
#include <math.h>

struct Unit{
  //value computed in forward pass
  double value;

  //derivative of circuit output w.r.t this unit computed
  double grad;
};

struct multiplyGate{
  Unit  u0, u1, utop;
  Unit forward(Unit u0, Unit u1){
    utop.value = u0.value*u1.value;
    utop.grad = 0.0;
    return utop;
  }
  
  void backward(Unit u0, Unit u1, Unit utop){
    u0.grad += u1.value * utop.grad;
    u1.grad += u0.value * utop.grad;
  }
};

struct addGate{
  Unit u0, u1, utop;
  Unit forward(Unit u0, Unit u1){
    utop.value = u0.value + u1.value;
    utop.grad = 0.0;
    return utop;
  }
  void backward(Unit u0, Unit u1, Unit utop){
    u0.grad += 1*utop.grad;
    u1.grad += 1*utop.grad; 
  }
};

struct sigmoidGate{
  double sig(double x){return 1/(1+exp(-x));}
  Unit u0, utop;
  Unit forward(Unit u0){
    utop.value = sig(u0.value);
    utop.grad = 0.0;
    return utop;
  }
  void backward(Unit u0, Unit utop){
    double g = sig(u0.value);
    u0.grad += (g*(1-g))*utop.grad;
  }
};
/*
void backward(Unit s,
                multiplyGate mulg0,
                multiplyGate mulg1,
                addGate addg0,
                addGate addg1,
                sigmoidGate sg0){
  s.grad = 1.0;
  sg0.backward();
  addg1.backward();
  addg0.backward();
  mulg1.backward();
  mulg0.backward();
}*/

void update(Unit a, Unit b, Unit c, Unit x, Unit y){
  double step_size = 0.01;
  a.value += step_size*a.grad;
  b.value += step_size*b.grad;
  c.value += step_size*c.grad;
  x.value += step_size*x.grad;
  y.value += step_size*y.grad;
}


int main(){
  //creating input units
  Unit a{1.0, 1.0};
  Unit b{2.0, 1.0};
  Unit c{-3.0, 1.0};
  Unit x{-1.0, 1.0};
  Unit y{3.0, 1.0};

  //creating the gates
  multiplyGate mulg0;
  multiplyGate mulg1;
  addGate addg0;
  addGate addg1;
  sigmoidGate sg0;

  //Unit s = forwardNeuron(a, b, c, x, y, mulg0, mulg1, addg0, addg1, sg0);
  //backward(s, mulg0, mulg1, addg0, addg1, sg0);
  //update(a, b, c, x, y);
  //std::cout << a.grad <<'\n' << a.value << '\n';
  //s = forwardNeuron(a,b,c,x,y,mulg0, mulg1, addg0, addg1, sg0);
  
  //forward pass
  Unit ax = mulg0.forward(a, x);
  Unit by = mulg1.forward(b, y);
  Unit axpby = addg0.forward(ax, by);
  Unit axpbypc = addg1.forward(axpby, c);
  Unit s = sg0.forward(axpbypc);
  std::cout << "circuit output \t " << s.value << '\n';

  //backward pass
  s.grad = 1.0;
  sg0.backward(axpbypc, s); // writes gradient into axpbypc
  addg1.backward(axpby, c, axpbypc); // writes gradients into axpby and c
  addg0.backward(ax, by, axpby); // writes gradients into ax and by
  mulg1.backward(b, y, by); // writes gradients into b and y
  mulg0.backward(a, x, ax); // writes gradients into a and x

  update(a, b, c, x, y);
  
  //forward pass again
  ax = mulg0.forward(a, x);
  by = mulg1.forward(b, y);
  axpby = addg0.forward(ax, by);
  axpbypc = addg1.forward(axpby, c);
  s = sg0.forward(axpbypc);
  std::cout << "circuit output \t " << s.value << '\n';

  return 0;
}