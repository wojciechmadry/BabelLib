#include <iostream>
#include "babel.hpp"
#include <windows.h>




int main()
{

   std::vector<double> p = {5,3,4,-2,15,2,-5,8,3,20 ,2 ,2 ,2};
  std::cout << babel::ALGO::sum(p);
    return 0;
}
