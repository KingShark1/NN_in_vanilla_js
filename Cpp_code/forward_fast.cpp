#include <iostream>
#include <math.h>


double forwardCircuitFast(double a, double b, double c, double x, double y){
  return 1/(1+exp(-(a*x + b*y + c)));
}

int main(){
  double a =1.0, b=2.0, c=-3.0, x=-1.0, y=3;
  double h = 0.0001;
  double grad_list[5];
  char name[5] = {'a', 'b', 'c', 'x', 'y'};
  grad_list[0] = (forwardCircuitFast(a+h,b,c,x,y)-forwardCircuitFast(a,b,c,x,y))/h;
  grad_list[1] = (forwardCircuitFast(a,b+h,c,x,y)-forwardCircuitFast(a,b,c,x,y))/h;
  grad_list[2] = (forwardCircuitFast(a,b,c+h,x,y)-forwardCircuitFast(a,b,c,x,y))/h;
  grad_list[3] = (forwardCircuitFast(a,b,c,x+h,y)-forwardCircuitFast(a,b,c,x,y))/h;
  grad_list[4] = (forwardCircuitFast(a,b,c,x,y+h)-forwardCircuitFast(a,b,c,x,y))/h;
  for(int idx=0; idx<5; idx++){
    std::cout << name[idx] << '\t';
  }
  std::cout << '\n';
  for(int idx=0; idx<5; idx++){
    std::cout << grad_list[idx] << '\t';
  }
  std::cout << '\n'; 
  return 0 ;
}