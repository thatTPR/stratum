#ifndef ANSI_HPP
#define ANSI_HPP
#include <cstdint>
#include <string>
#include <charconv>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <stratum/petri/list.hpp>
#include <stratum/petri/tuple.hpp>
#include <stratum/petri/variant.hpp>
#include <stratum/petri/macros.hpp>
#include <stratum/petri/templates.hpp>

namespace pri {
#define BEL	0x07,  //  7       | 007   |  0x07      \a	^G	Terminal bell ,
#define BS	0x08,  //  8       | 010   |  0x08      \b	^H	Backspace ,
#define HT	0x09,  //  9       | 011   |  0x09      \t	^I	Horizontal TAB ,
#define LF	0x0A,  //  10      | 012   |  0x0A      \n	^J	Linefeed (newline) ,
#define VT	0x0B,  //  11      | 013   |  0x0B      \v	^K	Vertical TAB ,
#define FF	0x0C,  //  12      | 014   |  0x0C      \f	^L	Formfeed (also: New page NP) ,
#define CR	0x0D,  //  13      | 015   |  0x0D      \r	^M	Carriage return ,
#define ESC	0x1B,  //  27      | 033   |  0x1B      \e*	^[	Escape character ,
#define DEL 0x7F,  //  127     | 0177   |  0x7F      <none>	<none>	Delete character 
#define STR_BEL "\a*"
#define STR_BS  "\b*"
#define STR_HT  "\t*"
#define STR_LF  "\n*"
#define STR_VT  "\v*"
#define STR_FF  "\f*"
#define STR_CR  "\r*"
#define STR_ESC "\e*"
#define STR_DEL NULL

#define HEX_C_BEL "\x07"
#define HEX_C_BS  "\x08"
#define HEX_C_HT  "\x09"
#define HEX_C_LF  "\x0A"
#define HEX_C_VT  "\x0B"
#define HEX_C_FF  "\x0C"
#define HEX_C_CR  "\x0D"
#define HEX_C_ESC "\x1B"
#define HEX_C_DEL "\x7F"

enum ANSI_ESC {
     cursor_up= 'A',//	Cursor Up	(n=1)	Move cursor up by n
     cursor_down= 'B', //	Cursor Down	(n=1)	Move cursor down by n
     cursor_forward= 'C', //	Cursor Forward	(n=1)	Move cursor forward by n
     cursor_back= 'D', //	Cursor Back	(n=1)	Move cursor back by n
     cursor_next_line= 'E', //	Cursor Next Line	(n=1)	Move cursor to the beginning of the line n lines down
     cursor_prev_line= 'F', //	Cursor Previous Line	(n=1)	Move cursor to the beginning of the line n lines up
     cursor_horizontal_abs= 'G', //	Cursor Horizontal Absolute	(n=1)	Move cursor to the the column n within the current row
     cursor_pos= 'H', //	Cursor Position	(n=1, m=1)	Move cursor to row n, column m, counting from the top left corner
     erase_in_disp= 'J', /*	Erase in Display	(n=0)	Clear part of the screen. 0, 1, 2, and 3 have various specific functions
     0 ( same as missing) erase unitl end of screen
     1 erase until beggining of screen
     2 erase entire screen
     3 erase saved line */
    erase_in_line= 'K', /*	Erase in Line	
    
    0 (same as missing )	erase from cursor to end of line
    1 	erase start of line to the cursor
    2 	erase the entire line
    
    */
     scroll_up= 'S', //	Scroll Up	(n=1)	Scroll window up by n lines
     scroll_down= 'T', //	Scroll Down	(n=1)	Scroll window down by n lines
     cursor_save= 's', //	Save Cursor Position	()	Save current cursor position for use with u
     cursor_restore= 'u', //	Restore Cursor Position	()	Set cursor back to position last saved by s
     cursor_save_dec= 7,//	Save Cursor Position	()	Save current cursor position for use with u
     cursor_restore_dec= 8,//	Restore Cursor Position	()	Set cursor back to position last saved by s
     cursor_horizontal_abso= 'f', //	…	…	(same as G)
     SGR= 'm' //	SGR	(*)	Set graphics mode. More below
};
#define _cursor_up 65
#define _cursor_down 66
#define _cursor_forward 67
#define _cursor_back 68
#define _cursor_next_line 69
#define _cursor_prev_line 70
#define _cursor_horizontal_abs 71
#define _cursor_pos 72
#define _erase_in_disp 74
#define _erase_in_line 75
#define _scroll_up  83
#define _scroll_down 84
#define _cursor_save 115
#define _cursor_restore 117
#define _cursor_horizontal_abso 102 
#define _SGR 109

    #define TABLE 5
    #define RGB 2

    #define FG_BLACK 30
    #define FG_RED 31
    #define FG_GREEN 32
    #define FG_YELLOW 33
    #define FG_BLUE 34
    #define FG_MAGENTA 35
    #define FG_CYAN 36
    #define FG_WHITE 37
    #define FG_color 38 //	Set foreground color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, see above
    #define FG_off 39 //	Default foreground color	implementation defined (according to standard)
    //AIXTERM NON STANDARD
    #define FG_BRIGHT_BLACK 90
    #define FG_BRIGHT_RED 91
    #define FG_BRIGHT_GREEN 92
    #define FG_BRIGHT_YELLOW 93
    #define FG_BRIGHT_BLUE 94
    #define FG_BRIGHT_MAGENTA 95
    #define FG_BRIGHT_CYAN 96
    #define FG_BRIGHT_WHITE 97

    #define BG_BLACK 40
    #define BG_RED 41
    #define BG_GREEN 42
    #define BG_YELLOW 43
    #define BG_BLUE 44
    #define BG_MAGENTA 45
    #define BG_CYAN 46
    #define BG_WHITE 47
    #define BG_color 48 //	Set background color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, see below
    #define BG_off 49 //	Default background color	implementation defined (according to standard)
    // AIXTERMnon standard
    #define BG_BRIGHT_BLACK 100
    #define BG_BRIGHT_RED 101
    #define BG_BRIGHT_GREEN 102
    #define BG_BRIGHT_YELLOW 103
    #define BG_BRIGHT_BLUE 104
    #define BG_BRIGHT_MAGENTA 105
    #define BG_BRIGHT_CYAN 106
    #define BG_BRIGHT_WHITE 107


#define SG_reset 0 //	Reset / Normal	all attributes off
#define SG_bold 1 //	Bold or increased intensity	
#define SG_faint 2 //	Faint (decreased intensity)	Not widely supported.
#define SG_italic 3 //	Italic	Not widely supported. Sometimes treated as inverse.
#define SG_underline 4 //	Underline	
#define SG_slow_blink 5 //	Slow Blink	less than 150 per minute
#define SG_rapid_blink 6 //	Rapid Blink	MS-DOS ANSI.SYS; 150+ per minute; not widely supported
#define SG_reverse 7 //	[[reverse video]]	swap foreground and background colors
#define SG_conceal 8 //	Conceal	Not widely supported.
#define SG_crossed 9 //	Crossed-out	Characters legible, but marked for deletion. Not widely supported.
#define SG_primary 10 //	Primary(default) font	
#define SG_font_1 11
#define SG_font_2 12
#define SG_font_3 13
#define SG_font_4 14
#define SG_font_5 15
#define SG_font_6 16
#define SG_font_7 17
#define SG_font_8 18
#define SG_font_9 19 //	Alternate font	Select alternate font n-10
#define SG_fraktur 20 //	Fraktur	hardly ever supported
#define SG_bold_off 21 //	Bold off or Double Underline	Bold off not widely supported; double underline hardly ever supported.
#define SG_normal_intensity 22 //	Normal color or intensity	Neither bold nor faint
#define SG_italic_off 23 //	Not italic, not Fraktur	
#define SG_underline_off 24 //	Underline off	Not singly or doubly underlined
#define SG_blink_off 25 //	Blink off	
#define SG_reverse_off 27 //	reverse off	
#define SG_reveal 28 //	Reveal	conceal off
#define SG_not_crossed 29 //	Not crossed out	
 //30–39	Set foreground color	See color table above

 //40–49,	Set background color	See color table above

#define SG_framed 51  //	Framed	
#define SG_encircled 52  //	Encircled	
#define SG_overlined 53  //	Overlined	
#define SG_framed_off 54  //	Not framed or encircled	
#define SG_overlined_off 55  //	Not overlined	
#define SG_ideogram_underline 60  //	ideogram underline	hardly ever supported
#define SG_ideogram_double_underline 61  //	ideogram double underline	hardly ever supported
#define SG_ideogram_overline 62  //	ideogram overline	hardly ever supported
#define SG_ideogram_double_overline 63  //	ideogram double overline	hardly ever supported
#define SG_ideogram_stress 64  //	ideogram stress marking	hardly ever supported
#define SG_ideogram_off 65  //	ideogram attributes off	reset the effects of all of 60-64

// 90–97, //	Set bright foreground color	aixterm (not in standard)
// 100–107, //	Set bright background color	aixterm (not in standard)

#define XSGMAC(x) x(cursor_up) x(cursor_down) x(cursor_forward) x(cursor_back) x(cursor_next_line) x(cursor_prev_line) x(cursor_horizontal_abs) x(scroll_up) x(scroll_down) x(cursor_save) x(cursor_restore) x(cursor_save_dec) x(cursor_restore_dec) x(cursor_horizontal_abso)

std::string ansi(std::string s){return std::string(HEX_C_ESC)+std::string("[")+ s + (char)ANSI_ESC::SGR;    };
    #define FUNC_SGR(n)  std::string __##n(uint8_t n) {return ansi(std::to_string(n) +(char)ANSI_ESC::n);};

std::string ansi(uint8_t s){return std::string(HEX_C_ESC)+std::string("[")+ std::to_string(s) + (char)ANSI_ESC::SGR;};

template <bool FG>
struct color256 {static constexpr bool fg=FG;uint8_t n;
  constexpr color256(uint8_t _n): n(_n){}
};
template <bool BG>
struct colorRgb{static constexpr bool fg=FG;uint8_t r,g,b;
  constexpr colorRgb(uint8_t _r,uint8_t _g,uint8_t _b) : r(_r) , g(_g) , b(_b) {}
};


color256<false> bg256(){uint8_t n} {color256<false>(n);}
colorRgb<false> bgRgb(uint8_t r,uint8_t g,uint8_t b){colorRgb<false>(r,g,b);}
color256<true> fg256(uint8_t n){color256<true>(n);} 
colorRgb<true> fgRgb(uint8_t r,uint8_t g,uint8_t b){colorRgb<true>(r,g,b);}



template <typename T>
std::string putAnsi(T a);

template <typename T>
std::string addAnsi(T a){return std::string(";") +putAnsi(a);};
template<> std::string putAnsi<uint8_t>(uint8_t a){return std::string(";")+std::string(a);}
template<> std::string putAnsi<color256<true>>(color256 a){return putAnsi(FG_color)+addAnsi(a.n);};
template<> std::string putAnsi<color256<false>>(color256 a){return putAnsi(FG_color)+addAnsi(a.n);};
template<> std::string putAnsi<colorRgb<true>>(color256 a){return putAnsi(FG_color)+addAnsi(a.r)+addAnsi(a.g);addAnsi(a.b);};
template<> std::string putAnsi<colorRgb<false>>(color256 a){return putAnsi(FG_color)+addAnsi(a.r)+addAnsi(a.g);addAnsi(a.b);};
template <typename T,typename... Ts>
std::string ansi(T ar,Ts... args){
  std::string s=std::string(HEX_C_ESC)+std::string("[")+putAnsi(ar);
  (s+=addAnsi(args))...;
  return s;
};



    XSGMAC(FUNC_SGR)
    //cursor_pos,
    //erase_in_disp,erase_in_line,
    std::string ansi_cursor(std::string s){return std::string(HEX_C_ESC)+std::string("[") + s ;}
    std::string ansi_cursor_up(uint8_t n){return              ansi_cursor(std::to_string(n)+std::to_string(_cursor_up));}
    std::string ansi_cursor_down(uint8_t n){return            ansi_cursor(std::to_string(n)+std::to_string(_cursor_down));}
    std::string ansi_cursor_forward(uint8_t n){return         ansi_cursor(std::to_string(n)+std::to_string(_cursor_forward));}
    std::string ansi_cursor_back(uint8_t n){return            ansi_cursor(std::to_string(n)+std::to_string(_cursor_back));}
    std::string ansi_cursor_next_line(uint8_t n){return       ansi_cursor(std::to_string(n)+std::to_string(_cursor_next_line));}
    std::string ansi_cursor_prev_line(uint8_t n){return       ansi_cursor(std::to_string(n)+std::to_string(_cursor_prev_line));}
    std::string ansi_cursor_horizontal_abs(uint8_t n){return  ansi_cursor(std::to_string(n)+std::to_string(_cursor_horizontal_abs));}
    std::string ansi_erase_in_line(uint8_t n){return          ansi_cursor(std::to_string(n)+std::to_string(_erase_in_line));}
    std::string ansi_scroll_up(uint8_t n){return              ansi_cursor(std::to_string(n)+std::to_string(_scroll_up));}
    std::string ansi_scroll_down(uint8_t n){return            ansi_cursor(std::to_string(n)+std::to_string(_scroll_down));}
    std::string ansi_cursor_save(){return                     ansi_cursor(std::to_string(_cursor_save));}
    std::string ansi_cursor_restore(){return                  ansi_cursor(std::to_string(_cursor_restore));}
    std::string ansi_cursor_horizontal_abso(uint8_t n){return ansi_cursor(std::to_string(n)+std::to_string(_cursor_horizontal_abso));}


   std::string ansi_cursor_pos(uint8_t n,uint8_t m){
        return ansi( std::to_string(n) + ";"+ std::to_string(m) + (char)ANSI_ESC::cursor_pos) ;
    };

   std::string ansi_erase_in_display(uint8_t n){
        if(n>3){
            throw("Error n cannot be bigger than 3 for erase in display");
        };
    return ansi(  std::to_string(n)+";" + (char)ANSI_ESC::erase_in_disp );
    };
     std::string __erase_in_line(uint8_t n){
        if(n>3){
            throw("Error n cannot be bigger than 2 for erase in display");
        };
    return ansi( std::to_string(n)+";"  + (char)ANSI_ESC::erase_in_line ) ;
    };   
std::string bg(uint8_t r, uint8_t g ,uint8_t b){
return   ansi(std::to_string(BG_color) +";" + "2"+ ";"+ std::to_string(r)+";"+std::to_string(g)+ ";"+std::to_string(b))  ;
};
std::string bg(pri::tuple<uint8_t,uint8_t,uint8_t> r){
return bg(pri::get<0>(r),pri::get<1>(r),pri::get<2>(r));
};
std::string bg(uint8_t n){
return   ansi(std::to_string(BG_color) +";" + "5"+ ";"+ std::to_string(n))   ;

};
std::string fg(uint8_t r, uint8_t g , uint8_t b){
return    ansi(std::to_string(FG_color)+";" + "2"+ ";"+ std::to_string(r)+";"+std::to_string(g)+ ";"+std::to_string(b));  ;  
};
std::string fg(pri::tuple<uint8_t,uint8_t,uint8_t> r){
return fg(pri::get<0>(r),pri::get<1>(r),pri::get<2>(r));
};

std::string fg(uint8_t n){
return  ansi(std::to_string(FG_color)+";" + "5"+ ";"+ std::to_string(n)) ;
};

std::string sgreset(){return ansi(std::string());}

class ansio;
template <typename T>
class ansio_at {
    T val;
    ansio_at(T _val): val(_val){};
    operator[](ansio& as);
    ansio_at<T> operator=(T d){
        return ansio_at<T>(val);
    };
};



class ansio { //ansi stream object to help manage state correctly for 
  public:
  std::string message ; 
  using rgbTy =pri::tuple<uint8_t , uint8_t , uint8_t >;
  // Members so that different defaults can be used
   rgbTy rgb_fg ;
   uint8_t n_fg ;  // Set to -1 if rgb, set to 39 if default
   rgbTy rgb_bg ; 
   uint8_t n_bg ; // set to -1 if rgb set to 49 if default 

   bool brgbFg;bool brgbBg;
   
   
   #define UINT_ATTS(x) x(blink) x(font) 

   #define ATTSBOOL(x) x(bold) x(faint) x(italic)  x(underline) x(reverse) x(conceal)  x(crossed)  x(fraktur)  x(framed)  x(encircled)  x(overlined)  x(ideogram)

   #define ATTS(x)  UINT_ATTS(x) ATTSBOOL(X)
   
   #define SG_ATTS(en) SG_##en,
   #define ENUM_ATTS(en) s_##en ,


   enum atTy {
        blink ,font,
        bold ,faint ,italic,underline ,reverse,conceal ,crossed ,fraktur ,framed ,encircled ,overlined ,ideogram,
    fg_uint,bg_uint,fg_rgb,bg_rgb,
reserved
  };
  

  #define ATT_MEMB(en) atTy::_en,
  
  template <atTy v>
    struct typeat {
      using type =typename std::conditional<pri::eqs_one_of<atTy,v,atTy::blink,atTy::font,atTy::ideogram>::value == true , uint8_t ,
      typename std::conditional<pri::eqs_one_of<atTy,v,atTy::fg_uint,atTy::bg_uint>::value == true,uint8_t,
      typename std::conditional<pri::eqs_one_of<atTy,v,atTy::fg_rgb,atTy::bg_rgb>::value == true,rgbTy,bool>::type>::type>::type;
    };



    bool _bold ; 
    bool _faint ; 
    bool _italic ; 
    bool _underline ;
    uint8_t _blink = SG_blink_off ;
    bool _reverse ; 
    bool _conceal ; 
    bool _crossed ;
    uint8_t _font = SG_primary ; // Default - options 10 - SG::font_9
    bool _fraktur ; 
    bool _framed ; 
    bool _encircled ; 
    bool _overlined ; 
    uint8_t _ideogram;




      static constexpr uint8_t offen(atTy en){
        switch (en) {
  case atTy::blink :  { return SG_blink_off;}
  case atTy::font : {  return SG_primary;}
  case atTy::bold : {  return SG_bold_off;}
  case atTy::faint :  { return SG_normal_intensity;}
  case atTy::italic :  { return SG_italic_off;}
  case atTy::underline :  { return SG_underline_off;}
  case atTy::reverse :  { return SG_reverse_off;}
  case atTy::conceal :  { return SG_normal_intensity;}
  case atTy::crossed :  { return SG_underline_off;}
  case atTy::fraktur :  { return SG_primary;} 
  case atTy::framed :  { return SG_framed_off;} 
  case atTy::encircled :  { return SG_underline_off;} 
  case atTy::overlined :  { return SG_overlined_off;} 
  case atTy::ideogram :  { return SG_ideogram_off;} 
        }
        return SG_reset;
      };
      static constexpr uint8_t onen(atTy en){
        switch (en) {
  case atTy::blink : { return SG_slow_blink;}
  case atTy::font : { return SG_font_1;}
  case atTy::bold : { return SG_bold;}
  case atTy::faint : { return SG_faint;}
  case atTy::italic : { return SG_italic;}
  case atTy::underline : { return SG_underline;}
  case atTy::reverse : { return SG_reverse;}
  case atTy::conceal : { return SG_conceal;}
  case atTy::crossed : { return SG_crossed;}
  case atTy::fraktur : { return SG_fraktur;} 
  case atTy::framed : { return SG_framed;} 
  case atTy::encircled : { return SG_encircled;} 
  case atTy::overlined : { return SG_overlined;} 
  case atTy::ideogram : { return SG_ideogram_underline;} 
        }; 
        return SG_bold;
    }

    // template <atTy e, typename T,T val>
    // struct ansiat : integral_constant<T,val>;
struct vtype {vtype(){};};
static  vtype vty;
    template <typename T>
    T ansio::* getptr(atTy e){
        switch  (e){
          // #define CASE_GET_PTR(x)  case atTy::e : {return &s._e ;}
case atTy::blink : {return &ansio::_blink;}; 
case atTy::font : {return &ansio::_font;};
case atTy::bold : {return &ansio::_bold;}; 
case atTy::faint : {return &ansio::_faint;}; 
case atTy::italic : {return &ansio::_italic;};
case atTy::underline : {return &ansio::_underline;}; 
case atTy::reverse : {return &ansio::_reverse;};
case atTy::conceal : {return &ansio::_conceal;}; 
case atTy::crossed : {return &ansio::_crossed;}; 
case atTy::fraktur : {return &ansio::_fraktur;}; 
case atTy::framed : {return &ansio::_framed;}; 
case atTy::encircled : {return &ansio::_encircled;}; 
case atTy::overlined : {return &ansio::_overlined;}; 
case atTy::ideogram : {return &ansio::_ideogram;};
          case atTy::fg_uint : {return &ansio::n_fg;}
          case atTy::bg_uint : {return &ansio::n_bg;}
          case atTy::fg_rgb : {return &ansio::rgb_fg;}
          case atTy::bg_rgb : {return &ansio::rgb_bg;}
          case atTy::reserved : {return &ansio::vty;}
        }
    };
  template <typename T> 
struct at  {
      T ansio::* Ptr ;
      T val ;
      atTy en ;
      uint8_t value;
      uint8_t on = onen(en) ;
       uint8_t off= offen(en);
      void set(){on = onen(en);off=offen(en);}
      at() =default;
      at(atTy _en,T _val,T ansio::* _Ptr) : val(_val), en(_en), Ptr(_Ptr){set();}
      at(atTy _en,vtype _value) :  en(_en)   {}
      at(atTy _en,uint8_t _value) :  en(_en) , value(_value)  {set();}
      at(atTy _en,uint8_t _value,ansio& ss) :  en(_en) , value(_value),Ptr(getptr<T>(_en,ss))  {set();}
      
      at<T> operator=(uint8_t d){return at<T>(en,d,Ptr);};
      at<T> operator=(int d){return operator=(uint8_t(d));};
      at<T> operator=(bool d){return at<T>(en,d?on:off,Ptr);};

    } ;

template < atTy e, typename T,T val>
    struct ansiat : std::integral_constant<T,val> {
      using ty = T;
      static constexpr atTy atty = e ;
      static constexpr T value = val;
       
      }; 

      

    using valtype= pri::variantvalue<at<bool>,at<rgbTy>,at<uint8_t>>  ;
    
    pri::list<valtype> Overrides;



    void clear(){message.clear();};
  void operator--(int) {clear();};
  

  void resetQueued(){
    clear();
    for( valtype& v : Overrides){
      switch(v.cur){
        case 0 :{
          at<bool>& r = pri::get<at<bool>>(v);
          message+=ansi((this->*(r.Ptr))?r.on:r.off);};
        
        case 1 : {
          at<rgbTy>& r = pri::get<at<rgbTy>>(v);
            if(r.Ptr == &ansio::rgb_fg ){fg(this->*(r.Ptr));}
            if(r.Ptr == &ansio::rgb_bg ){bg(this->*(r.Ptr));}
            continue;
        }
        case 2 : {
          at<uint8_t>& r = pri::get<at<uint8_t>>(v);
          if(r.Ptr == &ansio::n_fg){fg(this->*(r.Ptr));continue;}
          if(r.Ptr == &ansio::n_bg){bg(this->*(r.Ptr));continue;}
          ansi(this->*(r.Ptr));
        }
      }
      Overrides.clear();
  };
}
  void valdefa(){
  std::string s = sgreset();
  std::cout << s ;
  this->n_bg =  49;
  this->n_fg = 39 ; 
  this->rgb_fg = {245, 245 ,245} ;
  this->rgb_bg = {245,245,245} ; 
  this->_bold = false ;
  this->_faint = false ;
  this->_italic = false ;
  this->_underline = false ;
  this->_blink = SG_blink_off ;
  this->_reverse = false ;
  this->_conceal = false ;
  this->_crossed = false ;
  this->_font = SG_primary ;
  this->_fraktur = false ;
  this->_framed = false ;
  this->_encircled = false ;
  this->_overlined = false ;
  this->_ideogram = SG_ideogram_off ;
  };
   

  void ansis_sgr(){}

  template <typename ansiAt,typename... ansiAts>
  void ansis_sgr(ansiAt at,ansiAts... args){
    auto OverrideLam = [&](){
      valtype vt;pri::get<ansiAt::ty>(vt) = at<ansiAt::ty>(at.atty,at.value,getptr(at.atty)); 
      Overrides.push_back(vt);};
    
      OverrideLam();
      switch  (at.atty){
        case atTy::reserved : {resetQueued();}
        // #define ATTY_CASE(en) case atTy::##en : {OvverrideLam();message+=ansi(at.value);} 
        // UINT_ATTS(ATTY_CASE)
        // ATTSBOOL(ATTY_CASE)        
        case atTy::bg_rgb :  {message+=bg(at.value);brgbFg=true;}
        case atTy::bg_uint : {message+=bg(at.value);brgbFg=false;}
        case atTy::fg_rgb :  {message+=fg(at.value);brgbBg=true;}
        case atTy::fg_uint : {message+=fg(at.value);brgbBg=false;}
        default : {message+=ansi(at.value);
      }
    };
    ansis_sgr(args...);};


void ansis_sgrat(){}

  template <typename at,typename... ats>
  void ansis_sgrat(at a,ats... args){
    auto OverrideLam = [&](){
      valtype vt ; pri::get<at>(vt) = a;   Overrides.push_back(vt);};
      OverrideLam();
      switch  (a.en){
        case atTy::reserved : {resetQueued();}
        // #define ATTY_CASE(en) case atTy::##en : {OvverrideLam();message+=ansi(at.value);} 
        // UINT_ATTS(ATTY_CASE)
        // ATTSBOOL(ATTY_CASE)        
        case atTy::bg_rgb :  {message+=bg(a.value);brgbFg=true;}
        case atTy::bg_uint : {message+=bg(a.value);brgbFg=false;}
        case atTy::fg_rgb :  {message+=fg(a.value);brgbBg=true;}
        case atTy::fg_uint : {message+=fg(a.value);brgbBg=false;}
        default : {message+=ansi(a.value);
      }
    };
    ansis_sgrat(args...);};




    // std::string getReset(){clear();
    //   message+=ansi(SG_reset);
    //   if(brgbFg){message+=fg(rgb_fg);};
    //   {message+=fg(n_fg);}
    //   if(brgbBg){message+=bg(rgb_fg);};
    //   {message+=bg(n_fg);}
      
    //   #define RESET_ATTS(en) if(_##en){ansis_sgr(at<bool>(atTy::en,0).off);} ;
    //   ATTSBOOL(RESET_ATTS)  
    //   if(blink!=SG_blink_off){ansis_sgr(ansiat<atTy::blink,typeat<atTy::s_blink>::type,SG_blink_off>::value);} ;
    //   if(font!=SG_primary){ansis_sgr(ansiat<atTy::font,typeat<atTy::s_font>::type,SG_primary>::value);} ;
    //   return message;};
    std::string operator--(){resetQueued();return message;};
  std::string get(){return message;};
  
 std::string ansis_SG(uint8_t t){
    switch (t){
          case SG_reset : {break;}
          case SG_bold : {_bold = true; break;}
          case SG_faint : {_faint = true; break;}
          case SG_italic : {_italic = true; break;}
          case SG_underline : {_underline = true; break;}
          case SG_slow_blink : {_blink = SG_slow_blink; break;}
          case SG_rapid_blink : {_blink = SG_rapid_blink; break;}
          case SG_reverse : {_reverse = true; break;}
          case SG_conceal : {_conceal = true; break;}
          case SG_crossed : {_crossed = true; break;}
          case SG_primary : {_font = t; break;}
          case SG_font_1 : {_font = t; break;}
          case SG_font_2 : {_font = t; break;}
          case SG_font_3 : {_font = t; break;}
          case SG_font_4 : {_font = t; break;}
          case SG_font_5 : {_font = t; break;}
          case SG_font_6 : {_font = t; break;}
          case SG_font_7 : {_font = t; break;}
          case SG_font_8 : {_font = t; break;}
          case SG_font_9 : {_font = t; break;}
          case SG_fraktur : {_fraktur = true; break;}
          case SG_bold_off : {_bold = false; break;}
          case SG_normal_intensity : {_faint = false;_bold=false; break;}
          case SG_italic_off : {_italic = false; break;}
          case SG_underline_off : {_underline = false; break;}
          case SG_blink_off : {_blink = SG_blink_off; break;}
          case SG_reverse_off : {_reverse = false; break;}
          case SG_reveal : {_conceal = false; break;}
          case SG_not_crossed : {_crossed = false; break;}
          case SG_framed : {_framed = true; break;}
          case SG_encircled : {_encircled = true; break;}
          case SG_overlined : {_overlined = true; break;}
          case SG_framed_off : {_framed = false; _encircled = false ; break;}
          case SG_overlined_off : {_overlined = false; break;}
          case SG_ideogram_underline : {_ideogram = t; break;}
          case SG_ideogram_double_underline : {_ideogram = t; break;}
          case SG_ideogram_overline : {_ideogram = t; break;}
          case SG_ideogram_double_overline : {_ideogram = t; break;}
          case SG_ideogram_stress : {_ideogram = t; break;}
          case SG_ideogram_off : {_ideogram = t; break;}
    }
    return ansi(t);
  };
};

template <typename charT,typename osstr ,osstr& ref>
class ansis  {
  public:
  static constexpr osstr& r = ref;
  using type = ansis<charT,osstr,ref>;
  using str_ty=  std::basic_string<charT> ;

  ansio ss ;  

    type& operator<<(str_ty c){r<<c;return *this;};
    type& operator<<(charT c){r<<c;return *this;};
    // type& operator<<(float& c){r<<c;return *this;};
    // type& operator<<(double& c){r<<c;return *this;};
    type& operator<<(float& c){r<<c;return *this;};
    type& operator<<(double& c){r<<c;return *this;};
    type& operator<<(uint8_t& c){r<<c;return *this;};
    type& operator<<(uint16_t& c){r<<c;return *this;};
    type& operator<<(uint32_t& c){r<<c;return *this;};
    type& operator<<(uint64_t& c){r<<c;return *this;};
    type& operator<<(int8_t& c){r<<c;return *this;};
    type& operator<<(int16_t& c){r<<c;return *this;};
    type& operator<<(int32_t& c){r<<c;return *this;};
    type& operator<<(int64_t& c){r<<c;return *this;};

    type& operator<<(ansio::at<bool>&& c){ss.ansis_sgrat(c);
      r<<ss.message;return *this;};
    type& operator<<(ansio::at<uint8_t>&& c){ss.ansis_sgrat(c);
      r<<ss.message;return *this;};
    type& operator<<(ansio::at<ansio::rgbTy>&& c){ss.ansis_sgrat(c);
      r<<ss.message;return *this;};

      type& operator<<(ansio::at<ansio::vtype>& c){
      r<<(--ss);return *this;};

    template <typename T,typename ansiAt,typename... ansiAts>
    void style(T text,ansiAt at,ansiAts... ats){
      ss.ansis_sgr(at,ats...);
      r<<text;
      this<<--ss;
    }
    ansis() = default ;
};
 ansio::at<bool> sg_bold(ansio::atTy::bold,SG_bold); 
 ansio::at<bool> sg_faint(ansio::atTy::faint,SG_faint);
 ansio::at<bool> sg_italic(ansio::atTy::italic,SG_italic);
 ansio::at<bool> sg_underline(ansio::atTy::underline,SG_underline);
 ansio::at<uint8_t> sg_blink(ansio::atTy::blink,SG_blink_off);
 ansio::at<bool> sg_reverse(ansio::atTy::reverse,SG_reverse);
 ansio::at<bool> sg_conceal(ansio::atTy::conceal,SG_conceal);
 ansio::at<bool> sg_crossed(ansio::atTy::crossed,SG_crossed);
 ansio::at<uint8_t> sg_font(ansio::atTy::font,SG_primary);
 ansio::at<bool> sg_fraktur(ansio::atTy::fraktur,SG_fraktur);
 ansio::at<bool> sg_framed(ansio::atTy::framed,SG_framed);
 ansio::at<bool> sg_encircled(ansio::atTy::encircled,SG_encircled);
 ansio::at<bool> sg_overlined(ansio::atTy::overlined,SG_overlined);
 ansio::at<uint8_t> sg_ideogram(ansio::atTy::ideogram,SG_ideogram_off);
 ansio::at<ansio::vtype> ends ; 


 ansis<char,std::ostream,std::cout> acout;
 ansis<char,std::ostream,std::cerr> acerr;
 ansis<char,std::ostream,std::clog> aclog;


 ansis<wchar_t,std::wostream,std::wcout> awcout;
 ansis<wchar_t,std::wostream,std::wcerr> awcerr;
 ansis<wchar_t,std::wostream,std::wclog> awclog;

}
#endif