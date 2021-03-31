#include <iostream>
#include "babel.hpp"
#include <windows.h>




int main()
{

   std::list<double> p = {5,3,4,-2,15,2,-5,8,3,20 ,2 ,2 ,2};
   auto mm = babel::ALGO::FFT(p);
  // for (auto& d : mm)
    //   std::cout << d << ", ";
    std::cout << babel::MATH::binomial_coefficient(5, 3);
    std::cout << babel::MATH::binomial_coefficient<5, 3>();
    return 0;
}
