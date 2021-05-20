#include <iostream>

double forwardMultiplyGate(double x, double y){
  return x * y;
}

int main(){
  double x = -2.0, y = 3.0;
  double out = forwardMultiplyGate(x, y);
  std::cout << out << '\n';
  double h = 0.0001;

  //computing derivatives w.r.t x
  double xph = x + h;
  double out2 = forwardMultiplyGate(xph, y);
  double x_derivative = (out2 - out)/ h;
  std::cout << x_derivative << '\n';

  //computing derivative w.r.t y
  double yph = y + h;
  double out3 = forwardMultiplyGate(x, yph);
  double y_derivative = (out3-out)/ h;
  std::cout << y_derivative << '\n'; 

  //computing new out
  double step_size = 0.01;
  x = x + step_size*x_derivative;
  y = y + step_size*y_derivative;
  double out_new = forwardMultiplyGate(x, y);
  std::cout << out_new << '\n';

  
  return 0;
}