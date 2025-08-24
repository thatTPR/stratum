#pragma once
#include <cstdint>
#include <string>
#include <tuple>
#include <charconv>
#include <vector>
#include <iostream>
using namespace std;
#include "ansicode.hpp"

#define uint unsigned int 
#define ENUM_TO_STR(x) string(1,static_cast<char>(x))
    string ansi(std::string s){
        return HEX_C_ESC+  "["+ s ;
    };
    string crs_up(uint n) {
        return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_up)) );
    };
    string crs_down(uint n){
        return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_down)) );
    };
      string crs_forward(uint n){
    return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_forward)) );
    };
      string crs_back(uint n){
    return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_back)) );
    };
      string crs_next_line(uint n){
    return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_next_line)) );
    };
      string crs_prev_line(uint n){
    return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_prev_line)) );
    };
    string crs_horizontal_abs(uint n){
    return ansi( to_string(n) + ENUM_TO_STR((ANSICODE::cursor_horizontal_abs)) );
    };
    string crs_pos(uint n){
        return ansi( to_string(n) + ";"  + ENUM_TO_STR((ANSICODE::cursor_pos)) ) ;
    };
    string er_in_disp(uint n){
        if(n>3){
            throw("Error n cannot be bigger than 3 for erase in display");
        };
    return ansi(  to_string(n)+";" + ENUM_TO_STR((ANSICODE::erase_in_disp)) );
    };
      string er_in_line(uint n){
        if(n>3){
            throw("Error n cannot be bigger than 2 for erase in display");
        };
    return ansi( to_string(n)+";"  + ENUM_TO_STR((ANSICODE::erase_in_line)) ) ;
    };
      string scr_up(uint n){
    return ansi(  to_string(n) + ENUM_TO_STR((ANSICODE::scroll_up)) );
    };
      string scr_down(uint n){
    return ansi(  to_string(n) + ENUM_TO_STR((ANSICODE::scroll_down)) );
    };
      string crs_save(){
    return ansi(   ENUM_TO_STR((ANSICODE::cursor_save)) );
    };
      string crs_restore(){
    return ansi( ENUM_TO_STR((ANSICODE::cursor_restore)) );
    };
      string crs_save_dec(){
    return ansi( ENUM_TO_STR((ANSICODE::cursor_save_dec)) );
    };
      string crs_restore_dec(){
    return ansi( ENUM_TO_STR((ANSICODE::cursor_restore_dec)) );
    };
      string crs_horizontal_abso(uint n){
    return ansi(  to_string(n) + ENUM_TO_STR((ANSICODE::cursor_horizontal_abso)) );
    };
   

#define _r SG_reset
#define _b SG_bold
#define _f SG_faint
#define _i SG_italic
#define _u SG_underline
#define _sb SG_slow_blink
#define _rb SG_rapid_blink
#define _rev SG_reverse
#define _conceal SG_conceal
#define _s SG_crossed // Strikethrough

   
   string bg(uint r, uint g ,uint b){
                return   to_string(BG_color) +";" + "2"+ ";"+ to_string(r)+";"+to_string(g)+ ";"+to_string(b)  ;

   };
   string bg(uint n){
                return   to_string(BG_color) +";" + "5"+ ";"+ to_string(n)   ;
    
   };
   string fg(uint r, uint g , uint b){
        return    to_string(FG_color)+";" + "2"+ ";"+ to_string(r)+";"+to_string(g)+ ";"+to_string(b)  ;  
    
   };
   string fg(uint n){
        return  to_string(FG_color)+";" + "5"+ ";"+ to_string(n) ;
   };
    string col(FG t){
        if(t==FG_color){
            throw("Color code not allowed");
            return NULL ;
        };
        return  to_string(t)   ;

   };
   string col(BG t){
         if(t==BG_color){
            throw("Color code not allowed");
        }
            return to_string(t)   ;
   };
   
    string sgr_compose(string s){
     return HEX_C_ESC  +"["+ s + SGR;
    };

 
    string sgr(int s ) {
        std::string s = sgr_compose(std::string(s))  ;
        return s ;
    };
   



//  string operator"" _fmts(char* str , std::size_t ){
    
//  }; 


class ansis {

  vector<string> vec ; 
  vector<SG> sg_vec ; 
  void operator
  void bg();
  void fg();
  void operator()(int s ){sgr(s);};
 
  
  // Example usage
};

class ansio { //ansi stream object to help manage state correctly for 
  public:
  using ansi_str = ansis  ;
  string message ; 

  // Members so that different defaults can be used
   std::tuple<uint , uint , uint > rgb_fg ;
   uint n_fg ;  // Set to -1 if rgb, set to 39 if default
   std::tuple<uint, uint , uint > rgb_bg ; 
   uint n_bg ; // set to -1 if rgb set to 49 if default 

    
    bool bold ; 
    bool faint ; 
    bool italic ; 
    bool underline ;
    SG blink  ;
    bool reverse ; 
    bool conceal ; 
    bool crossed ;
    SG font = SG::primary ; // Default - options 10 - SG::font_9
    bool fraktur ; 
    bool framed ; 
    bool encircled ; 
    bool overlined ; 
    bool ideogram_off;
    bool ideogram_underline ; 
    bool ideogram_double_underline ; 
    bool ideogram_overline ; 
    bool ideogram_double_overline ; 
    bool ideogram_stress ; 
private :
  string ansis_SG(SG t){
    switch (t){
          case _r : {return sg(t);}
          case _b : {this->bold = true; return sg(t); }
          case _f : {this->faint = true; return sg(t); }
          case _i : {this->italic = true; return sg(t); }
          case _u : {this->underline = true; return sg(t); }
          case _sb : {this->blink = SG::slow_blink; return sg(t); }
          case _rb : {this->blink = SG::rapid_blink; return sg(t); }
          case _rev : {this->reverse = true; return sg(t); }
          case _conceal : {this->conceal = true; return sg(t); }
          case _s : {this->crossed = true; return sg(t); }
          case SG_primary : {this->font = t; return sg(t); }
          case SG_font_1 : {this->font = t; return sg(t); }
          case SG_font_2 : {this->font = t; return sg(t); }
          case SG_font_3 : {this->font = t; return sg(t); }
          case SG_font_4 : {this->font = t; return sg(t); }
          case SG_font_5 : {this->font = t; return sg(t); }
          case SG_font_6 : {this->font = t; return sg(t); }
          case SG_font_7 : {this->font = t; return sg(t); }
          case SG_font_8 : {this->font = t; return sg(t); }
          case SG_font_9 : {this->font = t; return sg(t); }
          case SG_fraktur : {this->fraktur = true; return sg(t); }
          case SG_bold_off : {this->bold = false; return sg(t); }
          case SG_normal_intensity : {this->faint = false; return sg(t); }
          case SG_italic_off : {this->italic = false; return sg(t); }
          case SG_underline_off : {this->underline = false; return sg(t); }
          case SG_blink_off : {this->blink = SG::blink_off; return sg(t); }
          case SG_reverse_off : {this->reverse = false; return sg(t); }
          case SG_reveal : {this->conceal = false; return sg(t); }
          case SG_not_crossed : {this->crossed = false; return sg(t); }
          case SG_framed : {this->framed = true; return sg(t); }
          case SG_encircled : {this->encircled = true; return sg(t); }
          case SG_overlined : {this->overlined = true; return sg(t); }
          case SG_framed_off : {this->framed = false; this->encircled = false ; return sg(t); }
          case SG_overlined_off : {this->overlined = false; return sg(t); }
          case SG_ideogram_underline : {this->ideogram_underline = true; return sg(t); }
          case SG_ideogram_double_underline : {this->ideogram_double_underline = true; return sg(t); }
          case SG_ideogram_overline : {this->ideogram_overline = true; return sg(t); }
          case SG_ideogram_double_overline : {this->ideogram_double_overline = true; return sg(t); }
          case SG_ideogram_stress : {this->ideogram_stress = true; return sg(t); }
          case SG_ideogram_off : {this->ideogram_off = true; return sg(t); }
    }
  };
  public:
  
  template <typename... T>
  void ansis_sgr(T... args){


  };

  void reset(){
    string s = sgr(sg(_r));
    std::cout << s ;
    this->n_bg =  49;
    this->n_fg = 39 ; 
    this->rgb_fg = {300, 300 ,300} ;
    this->rgb_bg = {300,300,300} ; 
    this->bold = false ;
    this->faint = false ;
    this->italic = false ;
    this->underline = false ;
    this->blink = SG::blink_off ;
    this->reverse = false ;
    this->conceal = false ;
    this->crossed = false ;
    this->font = SG::primary ;
    this->fraktur = false ;
    this->framed = false ;
    this->encircled = false ;
    this->overlined = false ;
    this->ideogram_underline = false ;
    this->ideogram_double_underline = false ;
    this->ideogram_overline = false ;
    this->ideogram_double_overline = false ;
    this->ideogram_stress = false ;
  };
   
  void operator--(){
    this->reset();
  };
    void set_fg(uint n){

    };
    void set_fg(uint r, uint g, uint b);
    void set_bg(uint n ){

    };
    void set_bg(uint r, uint g, uint b){

    };
    
    // string set_sgr(tuple<uint, uint, uint > fg_rgb ,tuple<uint, uint, uint > bg_rgb, SG... args ){
    //   string set =sgr( sgr_fg(fg_rgb.1, fg_rgb.2 , fg_rgb.3) , sgr_bg(bg_rgb.1, bg_rgb.2 , bg_rgb.3), sg(args...) ) ; 
    //   return set  ;
    // };
    // string operator[](tuple<uint, uint, uint > fg_rgb ,tuple<uint, uint, uint > bg_rgb, SG... args){
    //   string set =sgr( sgr_fg(fg_rgb.1, fg_rgb.2 , fg_rgb.3) , sgr_bg(bg_rgb.1, bg_rgb.2 , bg_rgb.3), sg(args...) ) ; 
    //   return set  ;
    // };
    // void operator<<(string message , tuple<uint, uint, uint > fg_rgb ,tuple<uint, uint, uint > bg_rgb, SG... args){
    //         string set =sgr( sgr_fg(fg_rgb.1, fg_rgb.2 , fg_rgb.3) , sgr_bg(bg_rgb.1, bg_rgb.2 , bg_rgb.3), sg(args...) ) ; 
    //   std::cout<<set << message  << ;
    //          set =sgr( sg(SG::_r) ) ; 
    // };
    // void operator<<(string message ,  uint fg_n , uint  bg_n , SG... args){
    //         string set =sgr( sgr_fg(fg_rgb.1, fg_rgb.2 , fg_rgb.3) , sgr_bg(bg_rgb.1, bg_rgb.2 , bg_rgb.3), sg(args...) ) ; 
    //   std::cout<<set << message  << ;
    //          set =sgr( sg(SG::_r) ) ; 
    // };
    
    // ansis ansis(){

    //  this->reset();
    //  return this ; 
    // };
    
};



// // Example usage 
// int main(){
    

//         string a = "Text Printed cool" ;
//         string set = sgr(bg(122,123,0), fg(225,0,225) , sgv({_b , _u }) ) ;
//         std::cout<< set ;
//         std::cout<<a ;
//         string se = sgr(sg(_r));
//         std::cout<< se;
//         std::cout<< a ;


       
// };