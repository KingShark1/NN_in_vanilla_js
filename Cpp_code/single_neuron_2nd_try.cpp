#include <iostream>
#include <math.h>

struct Unit{
  //value computed in forward pass
  double value;

  //derivative of circuit output w.r.t this unit computed
  double grad;
};

struct sigmoidGate{
  double sig(double x){return 1/(1+exp(-x));}
  Unit u0, utop;
  Unit forward(Unit u0){
    utop.value = sig(u0.value);
    utop.grad = 0.0;
    return utop;
  }
  void backward(){
    double g = sig(u0.value);
    u0.grad += (g*(1-g))*utop.grad;
  }
};

int main(){
  
  Unit x{2.0, 0.0};
  sigmoidGate sg0;
  
  Unit s = sg0.forward(x);
  std::cout << s.value <<'\n';
  
  

  std::cout << '\n';
  return 0;
}