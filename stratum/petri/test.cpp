#include <iostream>
#include "tuple.hpp"
#include <int/ansi.hpp>
void test(bool b){
    if(b ) {
        std::string set = ansi(std::string)
        std::cout<<HEX_C_ESC<<FG_GREEN<<"[x]";}
    else {std::cout<<HEX_C_ESC<<FG_RED<<"[-]";}
  std::cout<<HEX_C_ESC<<SG_reset<<std::endl;
}
int main()
{   
  
  std::cout<<"ptr::tuple: ";
  
  ptr::tuple<int,float,double> g; 
  ptr::get<1>(g) = 3.4;
  ptr::get<0>(g) = 3;
  
  
  test(bool(ptr::get<0>(g) == 3) ) ;

  
};