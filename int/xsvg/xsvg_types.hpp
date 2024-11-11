// Char types
#include "svg_tags.hpp"
#include <regex>
#include <math.h>
#include <time.h>
#include <type_traits>
// template <>
// void is_digit()
// template <>
// void is_alpha()

namespace svg_types {



template <typename num>
class value_t{
    class d ;
    d def
    virtual num def();
    virtual void r(std::string& str,  size_t& pos,  num& no);
    virtual void w(std::string& str,  size_t& pos,  num& no);
    value_t(def d) :def(d){};
} ;


// 

template <typename num>
class number : value_t{
    //   number ::= integer
    //             | [+-]? [0-9]* "." [0-9]+
    // number ::= integer ([Ee] integer)?
    //         | [+-]? [0-9]* "." [0-9]+ ([Ee] integer)?
    num def ;
    void r(std::string& str, size_t& pos , num& no){
        while(iswdigit(str[pos])){
            if(iswdigit(str[pos])){                        
                    no = no*10 + (str[pos] - '0') ;
                    continue ;
            };
            if(str[pos]=='.'){
                    int digit_ord = 1; 
                        pos++;
                    while(iswdigit(str[pos])){
                        no = no*10 + (str[pos] - '0'); digit_ord=10*digit_ord;
                        pos++ ;
                    };        
            };
            if(str[pos] == 'e' || str[pos] == 'E'){
                        pos++;
                        num sign=1  ;
                        if(str[pos] == '+'){sign = 1};
                        else (str[pos] == '-'){sign = -1};
                        pos++;
                        num n = 0 ; 
                        while (iswdigit(str[pos])){
                            n=n*10+(str[pos] - '0');
                        };
                        digit_ord=digit_ord * pow(10,n*sign);
                    } ;
                    no = no / digit_ord;
            };
            
        }
    std::string get_scientific(num& no){
        int p = log10(no) ; 
        num n = no / pow(10,p);
        std::string s = std::to_string(n) + "e" + std::to_string(p) ; 
        return s ;
    };
    void w(std::string& str, size_t& pos,  num& no){
        std::string s = inline number<num>::get_scientific(no);
        str.insert(pos , s );
        pos+= s.size();         
    };
    operator()(num n) {this->def = n};
    number(num n) :def(n){};
};
template <typename num>
class angle : value_t {
    
    // angle ::= number (~"deg" | ~"grad" | ~"rad")?
    num n ; 
    typedef enum  {
        deg=0, //90
        grad=1, // 100
        rad=3  // pi/2
    }type;
    type r(std::string& str , size_t& pos , num& no){
        inline number<num>::r(str,pos,no);
        pos++;
        if(str.find("deg",pos)==pos){return type::deg;};
        if(str.find("grad",pos)==pos){return type::grad;};
        if(str.find("rad",pos)==pos){return type::rad;};
    };
    void w(std::string& str,  size_t& pos , num& no){
        inline number<num>::w(str,pos,no);
    };
    class def
};
template <typename num>
class anything : value_t<num>{
    
    // anything ::= Char*
};
template <typename num>
class time : value_t{
   // time s, or ms
   enum {
    ms=0,
    s =1, 
   };
   void r(){
        if(str.find("ms",pos) == pos) {return time()};
        if(str.find("s",pos) == pos) {return  };

   };
    void w(std::string& str,  size_t& pos , num& no){

   };
};
template <typename num>
class clock_value {
//     Clock-val         ::= Full-clock-val | Partial-clock-val
//                       | Timecount-val
// Full-clock-val    ::= Hours ":" Minutes ":" Seconds ("." Fraction)?
// Partial-clock-val ::= Minutes ":" Seconds ("." Fraction)?
// Timecount-val     ::= Timecount ("." Fraction)? (Metric)?
// Metric            ::= "h" | "min" | "s" | "ms"
// Hours             ::= DIGIT+; any positive number
// Minutes           ::= 2DIGIT; range from 00 to 59
// Seconds           ::= 2DIGIT; range from 00 to 59
// Fraction          ::= DIGIT+
// Timecount         ::= DIGIT+
// 2DIGIT            ::= DIGIT DIGIT
// DIGIT             ::= [0-9]


// Full clock values:
// 02:30:03 = 2 hours, 30 minutes and 3 seconds
// 50:00:10.25 = 50 hours, 10 seconds and 250 milliseconds
// Partial clock value:
// 02:33 = 2 minutes and 33 seconds
// 00:10.5 = 10.5 seconds = 10 seconds and 500 milliseconds
// Timecount values:
// 3.2h = 3.2 hours = 3 hours and 12 minutes
// 45min = 45 minutes
// 30s = 30 seconds
// 5ms = 5 milliseconds
// 12.467 = 12 seconds and 467 milliseconds
// Fractional values are just (base 10) floating point definitions of seconds. Thus:
// 00.5s = 500 milliseconds
// 00:00.005 = 5 milliseconds

    struct clock_val {
        int ms,
        int s, 
        int min,
        int hours
    };
    #ifndef SINCE_1900
#define SINCE_1900
#endif
    struct tm operator+(clock_val s , tm t ){
        struct tm n =t ;  
        if(s.ms<500){
            n.tm_sec=t.tm_sec + s.s ;
        };
        else {n.tm_sec = t.tm_sec +s.s;}
        n.tm_min = t.tm_min + s.min ; 
        n.tm_hour = t.tm_hour + s.hours ; 
        if((int sec_rem = n.tm_sec/60 )>=1){ n.tm_sec+=n.tm_sec%60; n.tm_min+=sec_rem;}
        if((int min_rem = n.tm_min/60 )>=1){ n.tm_min+=n.tm_min%60; n.tm_hour+=min_rem;}
        if((int hour_rem = n.tm_hour/24) >=1){ n.tm_hour+=n.tm_hour%60; n.tm_mday+=hour_rem; 
            n.tm_yday++ ;n.tm_wday++; 
            if(n.tm_yday >365 -1*((SINCE_1900+n.tm_year)/4) && ((!((SINCE_1900+n.tm_year)/100)) || ((SINCE_1900+n.tm_year)/400)  )) {
                n.tm_yday
            };
            if((int wday_rem = n.tm_wday /7) >= 1){n.tm_wday+= n.tm_wday%7  };
        }
            return n;
    };
    void r(std::string& str , size_t& pos, clock_val){
        inline number<num>::r(str,pos,no);
        pos++
       
        if(str.find("min",pos) == pos) {return };


    };
    void w(std::string& str , size_t& pos , num& no)
};

template <typename num>
class color : value_t{
//     color    ::= "#" hexdigit hexdigit hexdigit (hexdigit hexdigit hexdigit)?
//               | "rgb("integer integer integer")"
//               | "rgb("integer "%" integer "%" integer "%)"
//               | color-keyword
// hexdigit ::= [0-9A-Fa-f]


    void r();
    void w()
};
template <typename num>
class frequency : value_t {
    // number Hz | KHz
};

template <typename num>
class percentage : value_t {
   // Number % 
};



    
};



// template <typename def_t  , typename f_value_t , typename... value_t >
// // class value_t_variant {
// //     public:
// //     using variant = std::tuple<f_value_t , value_t...> ;
// //     using type = std::conditional_t<std::is_same_v<std::decay_t<def_t>, f_value_t>, f_value_t, typename value_t_variant<def_t, value_t...>::type>;

// //     def_t def ;
// //     value_t_variant(def_t val) : def(val) {};
// // };

// // template <typename def_t   , typename... value_t >
// // class value_t_variant_t {
// //     public:
// //     using variant = std::tuple<value_t...>
// //     using type = value_t_variant<def_t, value_t...> ;
// //     static const def_t def ; 
// //     value_t_variant_t (def_t val) : def(val) {};
// // };

