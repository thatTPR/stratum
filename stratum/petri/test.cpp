#include <iostream>
#include "tuple.hpp"
#include <int/ansi.hpp>
void test(bool b){
    if(b ) {
        std::string set = sgr(FG_GREEN);
        std::cout<<set<<"[x]";}
    else {std::string set = sgr(FG_RED);
std::cout<<set<<"[-]";}
std::string set = sgr(SG_reset) ;  
std::cout<<set<<std::endl;
}
int main()
{   
  
  std::cout<<"ptr::tuple: ";
  
  ptr::tuple<int,float,double> g; 
  ptr::get<1>(g) = 3.4;
  ptr::get<0>(g) = 3;
  ptr::tuple<int,char> h;
  auto& s = ptr::tuple_concat(g,h);
    ptr::get<4>(s) = 23;
  std::cout<<"tuple:\n";
  std::cout<<"basic:"
  test(bool (ptr::get<0>(g) == 3) ) ;
  std::cout<<"concat:";
  test(bool(ptr::get<4>(s)) == 23) ;
  
  ptr::variant<int,float,double> h;
  ptr::get<int>(g) = 4;
  text(bool (ptr::get<int>(g) == 4));
  

  
};