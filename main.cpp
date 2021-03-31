#include <iostream>
#include "babel.hpp"
#include <windows.h>




int main()
{

   std::vector<double> p = {5,3,4,-2,15,2,-5,8,3,20 ,2 ,2 ,2};
   auto mm = babel::ALGO::find_min_max_ptr(p);
   *mm.first = 200;
   for(auto el : p)
       std::cout << el << ' ';

    return 0;
}
