#ifndef STMSL_LEX
#define STMSL_LEX
#include <queue>
namespace stmsl {
    struct posit {
            size_t ln=0;
            size_t col=0;size_t filePos=0;
            decltype(*this) operator++(){col++;}
            decltype(*this) operator++(int){filePos+=col;col=0;}
            bool operator<(size_t& i){return col<i;}

            posit() = default;
        };
    struct lex {
            enum ty {Name,NumFlt,NumUint,
                kw,typeName,typeNameConstructor,
                member,swizzle,
                escape='\\',
                Not='!',
                lparen='(',
                rparen=')',
                lbrace='{',
                rbrace='}',
                lbrack='[',
                rbrack=']',
                dq='\"',
                sq='\'',
                dot='.',
                plus='+',
                minus='-',
                band='&',
                bor='|',
                bxor='^',
                mul='*',
                div='/',
                ltangle='<',
                gtangle='>',
                comma=',',
                semicolon=';',
                colon=':',
                dcolon,
                space=' ',
                cond='?',
                nl='\n',
                pack,
                str="#",tokpaste,
                pp,mm,oand,oor,

                err
            };
            ty t;
            union {
                float flt;int unum;
                std::string name;
                // type<meta>* ty;
            }u;
        posit pos;
            void setUnum(char c){u.unum=(c-'0');}
            void addUnum(char c){u.unum*=10;u.unum+=(c-'0');}
            void addflt(char c){u.unum*=10;u.unum+=(c-'0');}
            void setFlt(size_t p){float f=u.unum;for(;p!=0;p--){f/=10;};
                u.flt=f;
            };
            bool isType(ty ts){return t=ts;}
            template <ty... ts>
            bool Variant(ts... first){return first==t || ...;};

            template <ty... ts>
            bool typeOf(){return ts==t || ...;}

            lex(ty tt) : t(tt){} 
            lex(char c)  {t=ty::Name;u.name=std::string(c);}
            
            lex(uint n) : u.unum(n){t=NumUint;};
            lex(int n) : u.inum(n){t=NumInt;};
            lex(float n) : u.flt(n){t=NumFlt;};
            lex(std::string n) : u.name(n) {t=Name;}
            lex(std::string n,lex _l) : u.name(n) ,pos(l.pos) {t=Name;}


            lex(posit _pos,ty tt) : pos(_pos)  t(tt){} 
            lex(posit _pos,char c) : pos(_pos) {t=ty::Name;u.name=std::string(c);}
            lex(posit _pos,uint n) : pos(_pos)  u.unum(n){t=NumUint;};
            lex(posit _pos,int n) : pos(_pos)  u.inum(n){t=NumInt;};
            lex(posit _pos,float n) : pos(_pos)  u.flt(n){t=NumFlt;};
        };
                using tylexq=pri::deque<lex>;

};
template <typename StreamT>
StreamT& strmLex(StreamT& os,  lex& v) {    
    switch(v.t){
case lex::ty::NumFlt :              {return os<<v.u.flt;}
case lex::ty::NumUint :             {return os<<v.u.unum;}
case lex::ty::Name :                {return os<<v.u.name}
case lex::ty::kw :                  {return os<<v.u.name;}
case lex::ty::typeName :            {return os<<v.u.name;}
case lex::ty::typeNameConstructor : {return os<<v.u.name;}
case lex::ty::member :              {return os<<v.u.name;}
case lex::ty::swizzle :             {return os<<v.u.name;}
case lex::ty::tokpaste :            {return os<<"##";}
case lex::ty::pp :                  {return os<<"++";}
case lex::ty::mm :                  {return os<<"--";}
case lex::ty::oand :                {return os<<"&&";}
case lex::ty::oor :                 {return os<<"||";}
default : {return os<<std::string(v.t);}
}
}

std::stringstream& operator<<(std::stringstream& str,lex& v){
    return strmLex<std::stringstream>(str,v);
};
std::ostream& operator<<(std::ostream& os,lex& v){return strmLex<std::ostream>(os,v);}

#endif