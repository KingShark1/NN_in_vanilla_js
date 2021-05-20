#include <iostream>

double forwardAdd(double x, double y){return x + y;}
double forwardMul(double q, double z){return q * z;}

int main(){
  double x = -2.0, y = 5.0, z = -4.0;
  double q = forwardAdd(x ,y);
  double f = forwardMul(q, z);
  std::cout << x << '\t' << y << '\t' << z << '\t'<< q <<'\t'<< f << '\n';
  
  double deriv_f_wrt_z = q;
  double deriv_f_wrt_q = z;
  double deriv_q_wrt_x = 1.0;
  double deriv_q_wrt_y = 1.0;
  
  //applying chain rule
  double deriv_f_wrt_x = deriv_q_wrt_x * deriv_f_wrt_q;
  double deriv_f_wrt_y = deriv_q_wrt_y * deriv_f_wrt_q;

  double deriv_f_wrt_xyz[] = {deriv_f_wrt_x, deriv_f_wrt_y, deriv_f_wrt_z};

  //changing inputs
  double step_size = 0.01;
  x = x + step_size * deriv_f_wrt_x;
  y = y + step_size * deriv_f_wrt_y;
  z = z + step_size * deriv_f_wrt_z;

  q = forwardAdd(x, y);
  f = forwardMul(q, z);

  std::cout << x << '\t' << y << '\t' << z << '\t'<< q <<'\t'<< f << '\n';
  return 0;
}