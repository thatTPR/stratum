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
#include "lex.hpp"
#include "keywords.hpp"

// #include <petri/regex.hpp>

namespace stmsl {



    class cphParser {
        public:
        ast<meta> fromFile(std::filesystem::path())
    }
    class parser {
        public:
        
struct macro {
    std::string name ,val;
    std::vector<std::string> args;
    macro(std::string _name,std::string _val) : name(_name) : val(_val) {}
    macro(std::string _name,std::string _val,std::vector<std::string> arg) : name(_name) , val(_val) , args(arg) {}
};

struct macrosl {
    pri::list<macro> mlist ;
    void push(macro m ){
        for(macro mit : mlist){
            if(m.name == mit.name){
                mit.val=m.val;return;
            };
        }
        mlist.push_back(m);
    }
};
macrosl macros;


        err& syserr;
        
        size_t linen=0;
        
        std::string line;size_t pos=0;size_t filePos;
        size_t linepos;
        ast<meta> cast;

        
        pcntxt cntxt ;



        bool interval(char c,char a,char b){return c>=a and c<=b ;}
        bool isdigit(char c){return interval(c,'0,'9);}
        bool alnum(char c){return interval(c,'a','z') or interval(c,'A','Z') or isdigit(c) or (c=='_');}
        size_t alnum(std::string s){size_t s=0;
            for(char c : s){if(!alnum(c)){return s;};s++;}
            return std::string::npos;
        }


        
        using tylexq=pri::deque<lex>;
        pri::deque<lex> lexq;
size_t Mag=0;
        void lexsw(){
  if(isdigit(line[pos])){
                        switch(lexq.back().t){
                            case lex::ty::NumUint : {lexq.back().addUnum(line[pos]);continue;}
                            case lex::ty::NumFlt : {lexq.back().addUnum(line[pos]);Mag++;continue;}
                            default : {lexq.back().setUnum(line[pos]);};continue;}
                    }
                    else {if(lexq.back().t==lex::ty::NumFlt){lexq.back().setFlt(Mag);Mag=0;};}
             

                switch(line[pos]){
                    case lex::ty::escape :{pos++;continue;}
                    case lex::ty::lparen :{lexq.emplace_back(lex::ty::lparen);continue;}
                    case lex::ty::rparen :{lexq.emplace_back(lex::ty::rparen);continue;}
                    case lex::ty::lbrace :{lexq.emplace_back(lex::ty::lbrace);continue;}
                    case lex::ty::rbrace :{lexq.emplace_back(lex::ty::rbrace);continue;}
                    case lex::ty::lbrack :{lexq.emplace_back(lex::ty::lbrack);continue;}
                    case lex::ty::rbrack :{lexq.emplace_back(lex::ty::rbrack);continue;}
                    case lex::ty::ltangle :{lexq.emplace_back(lex::ty::ltangle);continue;}
                    case lex::ty::dot :{lexq.emplace_back(lex::ty::dot);continue;}
                    case lex::ty::comma :{lexq.emplace_back(lex::ty::comma);continue;}
                    case lex::ty::semicolon :{lexq.emplace_back(lex::ty::semicolon);continue;}
                    case lex::ty::colon :{lexq.emplace_back(lex::ty::colon);continue;}
                    case lex::ty::space :{
                        if(!(lexq.back().t == lex::ty::space or (lexq.back().t == lex::ty::nl))){
                            lexq.emplace_back(lex::ty::space);};
                            continue;}
                    case lex::ty::nl :{if(lexq.back().t == lex::ty::nl){lexq.emplace_back(lex::ty::nl);};continue;}
                    case lex::ty::plus : {if(line[pos+1]==lex::ty::plus){lexq.emplace_back(lex::ty::pp);}else{lexq.emplace_back(lex::ty::plus);};continue;}
                    case lex::ty::minus : {{if(line[pos+1]==lex::ty::minus){lexq.emplace_back(lex::ty::mm);}else{lexq.emplace_back(lex::ty::minus);};continue;}}
                    case lex::ty::band : {if(line[pos+1]==lex::ty::band){lexq.emplace_back(lex::ty::oand);}else{lexq.emplace_back(lex::ty::band);};continue;}
                    case lex::ty::bor :{if(line[pos+1]==lex::ty::bor){lexq.emplace_back(lex::ty::oor);}else{lexq.emplace_back(lex::ty::bor);};continue;}
                    case lex::ty::bxor : {lex.emplace_back(lex::ty::bxor);continue;}
                    case lex::ty::mul : {lex.emplace_back(lex::ty::mul);continue;}
                    case lex::ty::div : {lex.emplace_back(lex::ty::div);continue;}
                    case lex::ty::cond : {lex.emplace_back(lex::ty::cond);continue;}
                                    
                };
                if(lexq.back().t==lex::ty::Name){lexq.back().u.name+=line[pos];}
                else{
                    if(lexq.back().t==lex::ty::dot){lexq.emplace_back(line[pos]);lexq.back().t=lex::ty::member;};)}
                    else{lexq.emplace_back(line[pos]);}
                };
       
        pri::deque<lex>::iter itPtr;


        // pri::stack<stmt<temp::meta>::block*> openedBlocks;
        // pri::stack<expr<temp::meta>*> openedInitializers;
                
        std::ifstream f;std::filesystem::path curFilePath;
        bool NewLine(){filePos+=pos;pos=0;if(std::getline(f,line)){return true}; return false;}
        void Line(){for(NewLine();pos<line.length();pos++){lexsw();}};
        bool next(){
            pos++;
            if(pos<line.length()){lexsw();}
            else {if(!NewLine()){return false;};lexsw();}
            return true;
        };

        size_t linecur,linecurnext;


        lex& prevTOK(pri::deque<lex>::iter it){
            pri::deque<lex>::iter itr = it;--itr;return itr;};
        lex& nextTOK(pri::deque<lex>::iter it){
            pri::deque<lex>::iter itr = it;++itr;return itr;};
        void procTo(pri::deque<lex>::iter i){

        };


        pri::list<qual> qualifiers;
        template <typename attrib >
        void putQualifier(){qualifiers.push(attrib::qualty);};
        void clearQualifier(){qualifiers.clear();}

        size_t LocationCur;
        size_t BindingCur;

        template <typename LayoutTy>
        void putLayout(){cast.layouts.back()};
        template <>void putLayout<stmt<meta>::Binding>(){cast.layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        template <>void putLayout<stmt<meta>::Location>(){cast.layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        // template <>void putLayout<stmt<q>::Location>(){cast.layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        


        void LayoutNew(){cast.layouts.push_back(stmt<q>::StmtLayout());}
expr<meta> getExpr(){return getExprFrom(lexq.begin());}

        void setVersion(uint s){cast.version=s;};
        uint getNum(std::string s){
            uint i=0;
            for(char c : s) {
                if(isdigit(c)){i*=10;i+=(c-'0');}
            }
            return i;
        };
        ast<meta> include(std::filesystem::path pth){parser p;return p.fromFile(pth);};
        template <lex::ty t,template <temp q> typename T>
        T<meta> getFromUntilStripped(pri::deque<lex> stripped);

        template <lex::ty t>
        expr<meta> getFromUntilStripped<t,expr>(pri::deque<lex> stripped){

        };
        
        template <lex::ty t>
        stmt<meta>::block getFromUntilStripped<t,stmt<meta>::block>(pri::deque<lex> stripped){
            
        };
        

        template <lex::ty t>
        deque<lex> strippedUntil(pri::deque<lex>::iter it){
            deque<lex> stripped;pri::deque<lex>::iter ite=it;
            for(;ite->t!=t;++ite){
                if constexpr (t != lex::ty::space){
                    if(ite->t==lex::ty::space){continue;}
                }
                if constexpr (t != lex::ty::nl){
                    if(ite->t==lex::ty::nl){continue;}
                }
                stripped.push_back(*ite);
                if(stripped.back().t==lex::ty::name){pri::deque<lex>::iter pr=prevTOK(stripped.tail());
                    if(pr->t==lex::ty::name){pr->t=lex::ty::typeName;}}
            };
            return stripped;
        };
        template <lex::ty t,lex::ty By>
        deque<lex> strippedUntilBy(pri::deque<lex::iter it,pri::deque<lex::iter& res,bool* found){
            *res=false;
            deque<lex> stripped;pri::deque<lex>::iter ite=it;
            for(;ite->t!=t;++ite){
                if constexpr (t != lex::ty::space){
                    if(ite->t==lex::ty::space){continue;}
                }
                if constexpr (t != lex::ty::nl){
                    if(ite->t==lex::ty::nl){continue;}
                }
                stripped.push_back(*ite);
                if (ite->t==By){res=stripped.tail();*found=true;}// TODO err<found_2assignments in statement>
            };
            return stripped;
        };
        
        template <lex::ty t,template <temp q> typename T>
        T<meta> getFromUntil(pri::deque<lex>::iter it){
            deque<lex> stripped = strippedUntil<t>(it);
            return getFromUntilStripped<t,T>(stripped);
        };

        template <lex::ty t,lex::ty by ,template <temp q> typename T>
        T<meta> getFromUntilBy(pri::deque<lex>::iter it){
            pri::deque<lex>::iter itr;bool found;
            deque<lex> stripped = strippedUntilBy<t,by>(it,itr,found);
            return getFromUntilStrippedBy<t,by,T>
        };
        expr<meta> getExprUntil_EOSTMT(pri::deque<lex>::iter it){
            return getFromUntil<lex::ty::semicolon,stmt>(it);
        };
        expr<meta> getExprUntil_EOL(pri::deque<lex>::iter it){
            return getFromUntil<lex::ty::nl,expr>(it);
        };
        stmt<meta> getMetaUntil_EOSTMT(pri::deque<lex>::iter it){
            
        };
        tu<meta> getTUUntil_EOTU(pri::deque<lex>::iter it){

        };
        stmt<meta>::block getBlockUntil_EOL(pri::deque<lex>::iter it){
            return getExprFrom<lex::ty::nl,block>(it);
        };
        stmt<meta>::block getBlockUntil_EOBLOCK(pri::deque<lex>::iter it){
            pri::list<stmt<meta>> stmts;

        };
        template <typename KW,typename... KWs>
        bool kwFound() ;
        template <typename KW>
        bool kwFound(){
            size_t s= line.find(KW::name);  
            if(s==std::string::npos){
                pos=s+KW::name().length();KW inst;inst.proc(*this);
                return true;
            };
            return false;
        };
        template <typename KW,typename... KWs>
        bool kwFound(){
            if(kwFound<KW>()){return true;}
            else {return kwFound<KWs...>();}
        } ;
        
        template <typename KW,typename... KWs >
        void untilKW(char del);
        
        template <typename KW >
        void untilKW(char del){

        };
        
        template <typename KW,typename... KWs >
        void untilKW(char del){

        };

        template <typename KW,typename... KWs >
        void untilKW();
        template <typename KW>
        void untilKW(){KW k;while(kwFound(k)==std::string::npos){getLine();}};
        template <typename KW,typename... KWs>
        void untilKW(){
        KW k;
        while(kwFound<kw,KWs>(k)()){getLine();}
    
    };
        template <typename KW>
        void untilKW(char del){KW k;while(kwFound(k)){getLine(del);}};


        static const size_t  =context_join<KW,KWs...>::s;
        template <typename KW>
        void putKw(){
            KW::
        };  
        template <typename KW,typename... KWs >
        void untilKWs(){
            pri::deque<lex>::iter it = lexq.tail();


        };  
        template <typename MSTMT_TY>
        void getMacro();
        template<>void getMacro<mStmtInclude>(){};
        template<>void getMacro<mStmtIf>(){};
        template<>void getMacro<mStmtDefine>(){};
        template<>void getMacro<mStmtElif>(){};
        template<>void getMacro<mStmtElifdef>(){};
        template<>void getMacro<mStmtIfdef>(){};
        template<>void getMacro<mStmtIfndef>(){};
        template<>void getMacro<mStmtElse>(){};


        ast<meta> fromFile(std::filesystem::path pth){ curFilePath = pth;
        cwd.push(pth.parent_path());
        f.open(pth);
        pos=0;
        while(getLine()){Line();}
        if(pth.extension()==std::filesystem::path("hstmsl")){
           wrcph(pth,cur); 
        }
        cwd.pop();
        };
        ast<meta> fromFile(std::string pth){filePos =0; std::filesystem::path s(pth);return fromFile(s); }

    
}
}
#endif