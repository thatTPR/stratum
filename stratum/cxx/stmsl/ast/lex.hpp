#ifndef STMSL_LEX
#define STMSL_LEX
#include <queue>
namespace stmsl {
    struct lex {
            enum ty {Name,NumFlt,NumUint,
                kw,typeName,member,
                escape='\\',
                lparen='(',
                rparen=')',
                lbrace='{',
                rbrace='}',
                lbrack='[',
                rbrack=']',
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
                space=' ',
                cond='?',
                nl='\n',
            
                pp,mm,oand,oor
            };
            ty t;
            union {
                float flt;int unum;
                std::string name;
            }u;
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
        };
                using tylexq=pri::deque<lex>;

};
#endif