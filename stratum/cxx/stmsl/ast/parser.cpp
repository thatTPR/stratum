#ifndef STMSL_PARSER_CPP
#define STMSL_PARSER_CPP
#include "../ast/ast.hpp"
#include <string>
#include <filesystem>
#include <ifstream>
#include "sys.cpp"
#include "ast.hpp"
#include "keywords.hpp"


namespace stmsl {

    class cphParser {
        public:
        ast<meta> fromFile(std::filesystem::path())
    }
    class parser {
        public:
        size_t line=0;
        
        std::string line;size_t pos=0;
        size_t linepos;
        
        ast<meta> cast;
        
        
        pcntxt cntxt ;
        bool inFuncBlock;
        bool inWhile;bool inFor=false;bool inForRange;
        bool inIf=false;bool inSw=false;bool inCase=false;
        bool inVarDef;
        pri::stack<stmt<meta::meta>::block> openedBlocks;
        pri::stack<expr<meta::meta>> openedInitializers;
        pri::stack<>
        
        std::ifstream f;
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
        template <typename KW>
        void untilKW(){

        };
        template <typename KW,typename... KWs >
        void untilKWs(){

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
        }
        ast<meta> fromFile(std::filesystem::path pth){
        cwd.push(pth.parent_path());
        f.open(s);
        while(std::getline(f,line)){
            
        }
        if(pth.extension()==std::filesystem::path("hstmsl")){
           wrcph(pth,cur); 
        }
        cwd.pop();
        };
                ast<meta> fromFile(std::string pth){std::filesystem::path s(pth);return fromFile(s); }

    
}
}
#endif