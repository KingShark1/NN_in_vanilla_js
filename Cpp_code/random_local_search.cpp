#include <iostream>
#include <limits>
#include <random>
#include <chrono>

double forwardMultiplyGate(double x, double y){
  return x * y;
}

double myrandom(){
  return rand()/RAND_MAX;
}

int main(){
  
  std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
  std::uniform_real_distribution<double> unif(0, 1);
  
  double tweak_amount = 0.01;
  double best_out = -1*std::numeric_limits<double>::infinity();
  int x = -2, y =3;
  double best_x = x;
  double best_y = y;
  
  for(int k=0; k<100; k++){
    double r1 = unif(rng);
    double r2 = unif(rng);
    
    double x_try = x + tweak_amount*(r1*2 -1);//update the random
    double y_try = y + tweak_amount*(r2*2 -1);//update the random
    double out = forwardMultiplyGate(x_try, y_try);
    if(out>best_out){
      best_out = out;
      best_x = x_try;
      best_y = y_try;
      
    }
    
  
  }
  std::cout << best_out << '\t' << best_x << '\t' << best_y << '\n';

  return 0;
}
