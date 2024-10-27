#pragma once
#include <cstdint>
#include <string>
#include <tuple>
#include <charconv>
#include <vector>
#include <iostream>
using namespace std ;
#define uint unsigned int 
#define PANG_CEXPR constexpr
// #define ENUM_TO_STR(x) string(1,static_cast<char>(x))
template <typename T>
consteval string ENUM_TO_STR(T a){
  return string(1,static_cast<char>(a));
};
typedef enum ASCII_HEX {
BEL	=0x07,  //  7       | 007   |  0x07      \a	^G	Terminal bell ,
BS	=0x08,  //  8       | 010   |  0x08      \b	^H	Backspace ,
HT	=0x09,  //  9       | 011   |  0x09      \t	^I	Horizontal TAB ,
LF	=0x0A,  //  10      | 012   |  0x0A      \n	^J	Linefeed (newline) ,
VT	=0x0B,  //  11      | 013   |  0x0B      \v	^K	Vertical TAB ,
FF	=0x0C,  //  12      | 014   |  0x0C      \f	^L	Formfeed (also: New page NP) ,
CR	=0x0D,  //  13      | 015   |  0x0D      \r	^M	Carriage return ,
ESC	=0x1B,  //  27      | 033   |  0x1B      \e*	^[	Escape character ,
DEL =0x7F,  //  127     | 0177   |  0x7F      <none>	<none>	Delete character 
}ASCII_HEX;
←→→←→←←
 string ascii_c(ASCII_HEX code){
     switch(code){
    case BEL : return "\a*";
    case BS : return "\b*";
    case HT : return "\t*";
    case LF : return "\n*";
    case VT : return "\v*";
    case FF : return "\f*";
    case CR : return "\r*";
    case ESC : return "\e*";
    case DEL : return NULL ;}
};
string ascii_hex_c(ASCII_HEX code){
    switch(code){
    case ASCII_HEX::BEL : return "\x07";
    case ASCII_HEX::BS : return "\x08";
    case ASCII_HEX::HT : return "\x09";
    case ASCII_HEX::LF : return "\x0A";
    case ASCII_HEX::VT : return "\x0B";
    case ASCII_HEX::FF : return "\x0C";
    case ASCII_HEX::CR : return "\x0D";
    case ASCII_HEX::ESC : return "\x1B";
    case ASCII_HEX::DEL : return "\x7F";
    };
};


typedef enum ANSICODE { // all suffixed 
    cursor_up='A',//	Cursor Up	(n=1)	Move cursor up by n
    cursor_down='B', //	Cursor Down	(n=1)	Move cursor down by n
    cursor_forward='C', //	Cursor Forward	(n=1)	Move cursor forward by n
    cursor_back='D', //	Cursor Back	(n=1)	Move cursor back by n
    cursor_next_line='E', //	Cursor Next Line	(n=1)	Move cursor to the beginning of the line n lines down
    cursor_prev_line='F', //	Cursor Previous Line	(n=1)	Move cursor to the beginning of the line n lines up
    cursor_horizontal_abs='G', //	Cursor Horizontal Absolute	(n=1)	Move cursor to the the column n within the current row
    cursor_pos='H', //	Cursor Position	(n=1, m=1)	Move cursor to row n, column m, counting from the top left corner
    erase_in_disp='J', /*	Erase in Display	(n=0)	Clear part of the screen. 0, 1, 2, and 3 have various specific functions
     0 ( same as missing) erase unitl end of screen
     1 erase until beggining of screen
     2 erase entire screen
     3 erase saved line */
    erase_in_line='K', /*	Erase in Line	
    
    0 (same as missing )	erase from cursor to end of line
    1 	erase start of line to the cursor
    2 	erase the entire line
    
    */
    scroll_up='S', //	Scroll Up	(n=1)	Scroll window up by n lines
    scroll_down='T', //	Scroll Down	(n=1)	Scroll window down by n lines
    cursor_save='s', //	Save Cursor Position	()	Save current cursor position for use with u
    cursor_restore='u', //	Restore Cursor Position	()	Set cursor back to position last saved by s
    cursor_save_dec=7, //	Save Cursor Position	()	Save current cursor position for use with u
    cursor_restore_dec=8, //	Restore Cursor Position	()	Set cursor back to position last saved by s
    cursor_horizontal_abso='f', //	…	…	(same as G)
    SGR='m', //	SGR	(*)	Set graphics mode. More below
}ANSICODE;



     std::string ansi(std::string s){
        return ascii_hex_c(ASCII_HEX::ESC)+  "["+ s ;
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
   

typedef enum coltype {
    TABLE=5,
    RGB=2
}color;
typedef enum FG {
    BLACK=30,
    RED=31,
    GREEN=32,
    YELLOW=33,
    BLUE=34,
    MAGENTA=35,
    CYAN=36,
    WHITE=37,
    fg_color=38, //	Set foreground color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, see below
    fg_off=39, //	Default foreground color	implementation defined (according to standard)
    // AIXTERM NON STANDARD
    BRIGHT_BLACK=90,
    BRIGHT_RED=91,
    BRIGHT_GREEN=92,
    BRIGHT_YELLOW=93,
    BRIGHT_BLUE=94,
    BRIGHT_MAGENTA=95,
    BRIGHT_CYAN=96,
    BRIGHT_WHITE=97
}FG;
typedef enum BG {
    BG_BLACK=40,
    BG_RED=41,
    BG_GREEN=42,
    BG_YELLOW=43,
    BG_BLUE=44,
    BG_MAGENTA=45,
    BG_CYAN=46,
    BG_WHITE=47,
    BG_color=48, //	Set background color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, see below
    BG_off=49, //	Default background color	implementation defined (according to standard)
    // AIXTERM non standard
    BG_BRIGHT_BLACK=100,
    BG_BRIGHT_RED=101,
    BG_BRIGHT_GREEN=102,
    BG_BRIGHT_YELLOW=103,
    BG_BRIGHT_BLUE=104,
    BG_BRIGHT_MAGENTA=105,
    BG_BRIGHT_CYAN=106,
    BG_BRIGHT_WHITE=107
}BG;

typedef enum SG {
 
reset=0, //	Reset / Normal	all attributes off
bold=1, //	Bold or increased intensity	
faint=2, //	Faint (decreased intensity)	Not widely supported.
italic=3, //	Italic	Not widely supported. Sometimes treated as inverse.
underline=4, //	Underline	
slow_blink=5, //	Slow Blink	less than 150 per minute
rapid_blink=6, //	Rapid Blink	MS-DOS ANSI.SYS; 150+ per minute; not widely supported
reverse=7, //	[[reverse video]]	swap foreground and background colors
conceal=8, //	Conceal	Not widely supported.
crossed=9, //	Crossed-out	Characters legible, but marked for deletion. Not widely supported.
primary=10, //	Primary(default) font	
font_1=11,
font_2=12,
font_3=13,
font_4=14,
font_5=15,
font_6=16,
font_7=17,
font_8=18,
font_9=19, //	Alternate font	Select alternate font n-10
fraktur=20, //	Fraktur	hardly ever supported
bold_off=21, //	Bold off or Double Underline	Bold off not widely supported; double underline hardly ever supported.
normal_intensity=22, //	Normal color or intensity	Neither bold nor faint
italic_off=23, //	Not italic, not Fraktur	
underline_off=24, //	Underline off	Not singly or doubly underlined
blink_off=25, //	Blink off	
reverse_off=27, //	reverse off	
reveal=28, //	Reveal	conceal off
not_crossed=29, //	Not crossed out	
 //30–39	Set foreground color	See color table below

 //40–49,	Set background color	See color table below

framed=51, //	Framed	
encircled=52, //	Encircled	
overlined=53, //	Overlined	
framed_off=54, //	Not framed or encircled	
overlined_off=55, //	Not overlined	
ideogram_underline=60, //	ideogram underline	hardly ever supported
ideogram_double_underline=61, //	ideogram double underline	hardly ever supported
ideogram_overline=62, //	ideogram overline	hardly ever supported
ideogram_double_overline=63, //	ideogram double overline	hardly ever supported
ideogram_stress=64, //	ideogram stress marking	hardly ever supported
ideogram_off=65, //	ideogram attributes off	reset the effects of all of 60-64

// 90–97, //	Set bright foreground color	aixterm (not in standard)
// 100–107, //	Set bright background color	aixterm (not in standard)
}SG;
#define _r SG::reset
#define _b SG::bold
#define _f SG::faint
#define _i SG::italic
#define _u SG::underline
#define _sb SG::slow_blink
#define _rb SG::rapid_blink
#define _rev SG::reverse
#define _conceal SG::conceal
#define _s SG::crossed // Strikethrough
#define _bf_f  SG::normal_intensity
#define _i_f  SG::italic_off
#define _u_f  SG::underline_off
#define _b_f  SG::blink_off
#define _rev_f  SG::reverse_off
#define _conceal_f  SG::reveal
#define _s_f  SG::not_crossed
   
   string bg(uint r, uint g ,uint b){
                return   to_string(BG::BG_color) +";" + "2"+ ";"+ to_string(r)+";"+to_string(g)+ ";"+to_string(b)  ;

   };
   string bg(uint n){
                return   to_string(BG::BG_color) +";" + "5"+ ";"+ to_string(n)   ;
    
   };
   string fg(uint r, uint g , uint b){
        return    to_string(FG::fg_color)+";" + "2"+ ";"+ to_string(r)+";"+to_string(g)+ ";"+to_string(b)  ;  
    
   };
   string fg(uint n){
        return  to_string(FG::fg_color)+";" + "5"+ ";"+ to_string(n) ;
   };
    string col(FG t){
        if(t==FG::fg_color){
            throw("Color code not allowed");
            return NULL ;
        };
        return  to_string(t)   ;

   };
   string col(BG t){
         if(t==BG::BG_color){
            throw("Color code not allowed");
        }
            return to_string(t)   ;
   };
   string sg(SG t){
        return  to_string(t)  ;

   };
   string sgv(std::vector<SG> vec){
      string res; 
      for(SG v : vec){
        res += sg(v) + ";" ; 
        
      };
      res.pop_back();
      return res ;
   };
   string sgr_compose(string s){
    return  ascii_hex_c(ASCII_HEX::ESC)  +"["+ s + ENUM_TO_STR(ANSICODE::SGR);
   };
    
    template <typename... T >
    auto sgr(T... args) {// 
        std::string s = (sgr_compose(std::string(args)) + ... ) + ENUM_TO_STR(ANSICODE::SGR) ;
        
        return s ;
 };




//  string operator"" _fmts(char* str , std::size_t ){
    
//  }; 

using col_var=  variant<tuple<uint,uint,uint> , uint >

  // 0-7 standard,   8-15 high intentsity
  // 16-51 dark color
  // + 36 next brightness
  // if 196>= last color brightness
  // 232-255 blacks
  // 16-51 52-87 88-123 124-159 160-195 196-231 232-255 
  // 16 black, 51 light blue ; 196 bright red, 231 white
  //
  typedef enum color_table{
    standard,
    high_intensity,
    blocks,
    grayscale,
    none
  }color_table;
   color_table check_col(uint& col){
      if(col<8){
        return color_table::standard;
      }
      else(col<16){
        return color_table::high_intensity;
      }
      
      else(col<232){
        return color_table::block_6;
      }
      else(col<256{
        return color_table::grayscale;
      }
      else {
        return color_table::none ;
      }
    }
  };
  tuple<uint,uint,uint> row_block_col(uint& col){
    tuple<uint,uint,uint> tup ; 
    rem_div[0] = (col -16) / 6 ; 
    
  };
  void col_brighter_row(uint& col){
      col+=36 ;
  };
  void col_darker_row(uint& col){
    col-=36;
  };
  void col_add(uint& col, uint amount){ // can put minus // amount Should be <= 5
    col+=amount; 
  };
class basic_ansis {
  vector<variant<string, uint>> vec ;

};
// Probably not in any way constexpr-able
  PANG_CEXPR vector<variant<string, int>> operator<<(vector<variant<string,int>>& vec, vector<variant<string , int>> vec2){
    return vec.append_range(vec2) ;
  };
  PANG_CEXPR vector<variant<string,int>> operator<<(vector<variant<string,int>>& vec, variant<string , int> val){
    return vec.push_bacK(val)
  };
  PANG_CEXPR vector<variant<string,int>> operator<<(variant<string,int>> vall , variant<string,int>>& valr) {
      vector<variant<int,string>> t; t.push_back(val1); t.push_back(valr);
      return t; 
  };
class ansis : basic_ansis {
  variant<uint, tuple<uint,uint,uint> > fg ; // text color
  variant<uint, tuple<uint,uint,uint> > bg ; // Bg Color

  vector<variant<string, uint>> vec ; //
  vector<variant<string, uint>> operator+(vector<varaint<string,uint>> &vec,  variant<string,uint> v){
      vec.push_back(v);
      return vec ;
  };
  
  template <typename... T>
  void operator()(T... args ){
    sgr(args...)
  };
  
  ansis& operator<<( variant< string& , uint> str){
      lhs->vec.push_back(str);
  };
  ansis& operator<<( SG s){
      this->sg_vec.push_back(s) ;
  };
  template <typename T >
  ansis& operator<<(T val, col_var  ){
    if(val == typeid())
  };
  
  
  // Example usage
};

class ansio { 
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
          case SG::primary : {this->font = t; return sg(t); }
          case SG::font_1 : {this->font = t; return sg(t); }
          case SG::font_2 : {this->font = t; return sg(t); }
          case SG::font_3 : {this->font = t; return sg(t); }
          case SG::font_4 : {this->font = t; return sg(t); }
          case SG::font_5 : {this->font = t; return sg(t); }
          case SG::font_6 : {this->font = t; return sg(t); }
          case SG::font_7 : {this->font = t; return sg(t); }
          case SG::font_8 : {this->font = t; return sg(t); }
          case SG::font_9 : {this->font = t; return sg(t); }
          case SG::fraktur : {this->fraktur = true; return sg(t); }
          case SG::bold_off : {this->bold = false; return sg(t); }
          case SG::normal_intensity : {this->faint = false; return sg(t); }
          case SG::italic_off : {this->italic = false; return sg(t); }
          case SG::underline_off : {this->underline = false; return sg(t); }
          case SG::blink_off : {this->blink = SG::blink_off; return sg(t); }
          case SG::reverse_off : {this->reverse = false; return sg(t); }
          case SG::reveal : {this->conceal = false; return sg(t); }
          case SG::not_crossed : {this->crossed = false; return sg(t); }
          case SG::framed : {this->framed = true; return sg(t); }
          case SG::encircled : {this->encircled = true; return sg(t); }
          case SG::overlined : {this->overlined = true; return sg(t); }
          case SG::framed_off : {this->framed = false; this->encircled = false ; return sg(t); }
          case SG::overlined_off : {this->overlined = false; return sg(t); }
          case SG::ideogram_underline : {this->ideogram_underline = true; return sg(t); }
          case SG::ideogram_double_underline : {this->ideogram_double_underline = true; return sg(t); }
          case SG::ideogram_overline : {this->ideogram_overline = true; return sg(t); }
          case SG::ideogram_double_overline : {this->ideogram_double_overline = true; return sg(t); }
          case SG::ideogram_stress : {this->ideogram_stress = true; return sg(t); }
          case SG::ideogram_off : {this->ideogram_off = true; return sg(t); }
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


void test_cout(){

};

// Example usage 
int main(){
    

        string a = "   Alexandru.Popp@LAP-AlexP  C:    System32 " ;

        string set = sgr(bg(122,123,0), fg(225,0,225) , sgv({_b , _u }) ) ;
        std::cout<< set ;
        std::cout<<a ;
        string se = sgr(sg(_r));
        std::cout<< se;
        std::cout<< a ;


       
}