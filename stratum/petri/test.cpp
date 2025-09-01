#include <iostream>
#include "tuple.hpp"
#include "variant.hpp"
#include "ansi.hpp"
void test(bool b){
    if(b ) {
        std::string set = pri::fg(FG_BLUE);
        std::cout<<"["<<set<<"x";set =pri::sgreset();
        std::cout<<set<<"]";}
    else {std::string set = pri::fg(FG_RED);
std::cout<<"["<<set<<"-"<<pri::sgreset()<<"]";}
std::cout<<std::endl;
}
int main()
{   
  pri::acout<<"AnsiTests" ;std::cout<<std::endl;
  pri::acout<<(pri::sg_bold=true)<<"bold"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_faint=true)<<"faint"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_italic=true)<<"italic"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_underline=true)<<"underline"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_blink=true)<<"blink"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_reverse=true)<<"reverse"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_conceal=true)<<"conceal"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_crossed=true)<<"crossed"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_font=SG_font_3)<<"font"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_fraktur=true)<<"fraktur"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_framed=true)<<"framed"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_encircled=true)<<"encircled"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_overlined=true)<<"overlined"<<pri::ends;std::cout<<std::endl;
pri::acout<<(pri::sg_ideogram=SG_ideogram_double_underline)<<"ideogram"<<pri::ends;std::cout<<std::endl;

std::cout << "Cursror Move : Erased 88888888888888"<<std::endl ;
std::cout<<"cursor_up & cursor_down"<<pri::ansi_cursor_up(1)<<pri::ansi_erase_in_line(1)<<pri::ansi_cursor_down(1)<<std::endl;
std::cout<<"cursor_forward &&&& cursor_back"<<pri::ansi_cursor_back(13)<<"123"<<pri::ansi_cursor_forward(10)<<std::endl;
// std::cout<<"cursor_next_line &&&& cursor_prev_line"<<std::endl;
std::cout<<"cursor_horizontal_abs"<<pri::ansi_cursor_horizontal_abs(7)<<pri::ansi_erase_in_line(1)<<pri::ansi_cursor_horizontal_abs(21)<<std::endl; ;
// std::cout<<"scroll_up"<<
// std::cout<<"scroll_down"<<
std::cout<<"cursor_save &&&&"<<pri::ansi_cursor_back(4)<<pri::ansi_erase_in_line(2)<<pri::ansi_cursor_restore();
std::cout<<"cursor_restore" ;

  
  std::cout<<"pri::tuple: ";
  
  pri::tuple<int,float,double> g; 
  pri::get<1>(g) = 3.4;
  pri::get<0>(g) = 3;
  test(bool (pri::get<0>(g) == 3) ) ;
  // pri::tuple<int,char> h;
  // auto& s = pri::concat_tuples(g,h);
  //   pri::get<4>(s) = 23;
  // std::cout<<"tuple:\n";
  // std::cout<<"concat:";
  // test(bool(pri::get<4>(s)) == 23) ;
  std::cout<<"pri::variant: ";
  pri::variant<int,float,double> h;
  pri::get<int>(h) = 4;
  test(bool (pri::get<int>(h) == 4));
  

  
};