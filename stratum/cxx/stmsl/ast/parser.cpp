#ifndef STMSL_PARSER_CPP
#define STMSL_PARSER_CPP
#include <string>
#include <filesystem>
#include <petri/list.hpp>
#include <petri/stack.hpp>
#include <petri/queue.hpp>
#include <ifstream>
#include "sys.cpp"
#include "ast.hpp"
#include "keywords.hpp"

// #include <petri/regex.hpp>

namespace stmsl {



    class cphParser {
        public:
        ast<meta> fromFile(std::filesystem::path())
    }
    class parser {

        public:
        err& syserr;
        
        size_t linen=0;
        
        std::string line;size_t pos=0;
        size_t linepos;
        
        ast<meta> cast;

        
        pcntxt cntxt ;
        bool inFuncBlock;
        bool inWhile;bool inFor=false;bool inForRange;
        bool inIf=false;bool inSw=false;bool inCase=false;
        bool inVarDef;

        struct lex {
            enum ty {
                kw,name,
                lparen,rparen,
                lbrace,rbrace,
                lbrack,rbrack
                comma,space
            };
            std::string name; 
            
        };
        pri::queue<lex> lexq;
        pri::stack<stmt<meta::meta>::block> openedBlocks;
        pri::stack<expr<meta::meta>> openedInitializers;
                
        std::ifstream f;std::filesystem::path curFilePath;

        size_t linecur,linecurnext;
        bool interval(char c,char a,char b){return c>=a and c<=b ;}
        bool alnum(char c){return interval(c,'a','z') or interval(c,'A','Z') or interval(c,'0','9') or (c=='_');}
        size_t alnum(std::string s){size_t s=0;
            for(char c : s){if(!alnum(c)){return s;};s++;}
            return std::string::npos;
        }
  bool getLine(){pos=0;return bool(std::getline(f,line));};
        bool getLine(char del){pos=0;return bool(std::getline(f,line,del));};



        std::string untilEOL(){
            std::string s;
            for(;pos<line.length() and line[pos]!'\n';pos++){
                if(line[pos] == '\\'){pos++;
                    if(line[pos]=='\n'){pos=0;std::getline(f,line);}
                    continue;}
                s+=line[pos];
            }
            return s;
        };
        expr<meta> untilEOL(){
            std::string s=untilEOL();
            return expr<meta>(s);
        };
        expr<meta> untilSemiColon(){
            std::string s;
            size_t linecur=linen;
            for(;pos<line.length() and line[pos]!=';';pos++){
                if(line[pos] == '\n'){pos=0;std::getline(f,line);continue;}
                s+=line[pos];
            };
            size_t linecurnextt=linen;
            return expr<meta>(*this,s);
        };


        pos_t kwFound(KW& key){return line.find(key.name);};
        template <typename KW>
        void untilKW(){
            
        };
        template <typename KW>
        void untilKW(char del){
            
        };

        template <typename KW,typename... KWs >
        void untilKWs(){
            for()
        };

        expr<meta> parse(std::string str){
            for(size_t i=0;i<str.length();i++){
                if(str[i]==0){

                };
                
            };
        };
        template <typename KW,typename... KW>
        void _parse(){}
        void parse(){

        };
        ast<meta> include(std::filesystem::path pth){
            parser p;return p.fromFile(pth);
        };
      
        std::string Str;
        void proc(){
            for(;pos<=line.length();pos++){

            }

        };
        ast<meta> fromFile(std::filesystem::path pth){ curFilePath = pth;
        cwd.push(pth.parent_path());
        f.open(pth);
        pos=0;
        while(getLine()){proc();}
        if(pth.extension()==std::filesystem::path("hstmsl")){
           wrcph(pth,cur); 
        }
        cwd.pop();
        };
                ast<meta> fromFile(std::string pth){std::filesystem::path s(pth);return fromFile(s); }

    
}
}
#endif