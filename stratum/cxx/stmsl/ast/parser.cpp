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
    template <typename... T>
    void emplace(T... arg){push(macro(arg...));};
    bool exists(std::string name){
        for(macro m : mlist){
            if(m.name==name){return true;}
        };
        return false;
    };
};
macrosl macros;



    class cphParser {
        public:
        ast fromFile(std::filesystem::path())
    };
    
    class parser {
        public:
        


        // err& syserr = syserr;
        
        size_t linen=0;
        
        std::string line;
        size_t pos=0;size_t filePos;
        size_t linepos;
        ast cast;

        
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
                    case lex::ty::dq : {lexq.emplace_back(filePos,linen,pos,lex::ty::dq);continue;}
                    case lex::ty::sq : {lexq.emplace_back(filePos,linen,pos,lex::ty::sq);continue;}
                    case lex::ty::lparen :{lexq.emplace_back(filePos,linen,pos,lex::ty::lparen);continue;}
                    case lex::ty::rparen :{lexq.emplace_back(filePos,linen,pos,lex::ty::rparen);continue;}
                    case lex::ty::lbrace :{lexq.emplace_back(filePos,linen,pos,lex::ty::lbrace);continue;}
                    case lex::ty::rbrace :{lexq.emplace_back(filePos,linen,pos,lex::ty::rbrace);continue;}
                    case lex::ty::lbrack :{lexq.emplace_back(filePos,linen,pos,lex::ty::lbrack);continue;}
                    case lex::ty::rbrack :{lexq.emplace_back(filePos,linen,pos,lex::ty::rbrack);continue;}
                    case lex::ty::ltangle :{lexq.emplace_back(filePos,linen,pos,lex::ty::ltangle);continue;}
                    case lex::ty::dot :{lexq.emplace_back(filePos,linen,pos,lex::ty::dot);continue;}
                    case lex::ty::comma :{lexq.emplace_back(filePos,linen,pos,lex::ty::comma);continue;}
                    case lex::ty::semicolon :{lexq.emplace_back(filePos,linen,pos,lex::ty::semicolon);continue;}
                    case lex::ty::colon :{
                        if(lexq.back().t==lex::ty::colon){lexq.back().t=lex::ty::dcolon;}
                        else {lexq.emplace_back(filePos,linen,pos,lex::ty::colon);continue;}
                    }
                    case lex::ty::space :{
                        if(!(lexq.back().t == lex::ty::space or (lexq.back().t == lex::ty::nl))){
                            lexq.emplace_back(filePos,linen,pos,lex::ty::space);};
                            continue;}
                    case lex::ty::nl :{if(lexq.back().t == lex::ty::nl){lexq.emplace_back(filePos,linen,pos,lex::ty::nl);};continue;}
                    case lex::ty::plus : {if(line[pos+1]==lex::ty::plus){lexq.emplace_back(filePos,linen,pos,lex::ty::pp);}else{lexq.emplace_back(filePos,linen,pos,lex::ty::plus);};continue;}
                    case lex::ty::minus : {{if(line[pos+1]==lex::ty::minus){lexq.emplace_back(filePos,linen,pos,lex::ty::mm);}else{lexq.emplace_back(filePos,linen,pos,lex::ty::minus);};continue;}}
                    case lex::ty::band : {if(line[pos+1]==lex::ty::band){lexq.emplace_back(filePos,linen,pos,lex::ty::oand);}else{lexq.emplace_back(filePos,linen,pos,lex::ty::band);};continue;}
                    case lex::ty::bor :{if(line[pos+1]==lex::ty::bor){lexq.emplace_back(filePos,linen,pos,lex::ty::oor);}else{lexq.emplace_back(filePos,linen,pos,lex::ty::bor);};continue;}
                    case lex::ty::bxor : {lex.emplace_back(filePos,linen,pos,lex::ty::bxor);continue;}
                    case lex::ty::mul : {lex.emplace_back(filePos,linen,pos,lex::ty::mul);continue;}
                    case lex::ty::div : {lex.emplace_back(filePos,linen,pos,lex::ty::div);continue;}
                    case lex::ty::cond : {lex.emplace_back(filePos,linen,pos,lex::ty::cond);continue;}
                                    
                };
                if(lexq.back().t==lex::ty::Name){lexq.back().u.name+=line[pos];}
                else{
                    if(lexq.back().t==lex::ty::dot){lexq.emplace_back(filePos,linen,pos,line[pos]);lexq.back().t=lex::ty::member;};)}
                    else{lexq.emplace_back(filePos,linen,pos,line[pos]);}
                };
       
        pri::stack<pri::deque<lex>::iter> itPtr;

        // pri::stack<stmt<temp::meta>::block*> openedBlocks;
        // pri::stack<expr<temp::meta>*> openedInitializers;
                
        std::ifstream f;std::filesystem::path curFilePath;
        bool NewLine(){linen++;filePos+=pos;pos=0;if(std::getline(f,line)){return true}; return false;}
        bool Line(){
            if(NewLine()){for(;pos<line.length();pos++){lexsw();}
            return true;}
            else{return false;}
        };
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
        
        template <lex::ty tok>
        void until(){
            itPtr.push(itPtr.back());
            pri::deque<lex>::iter ptr=itPtr.back();
            ++ptr;
            for(;(itPtrc->t==tok);++ptr){
                if(!ptr){next();ptr=itPtr.back();}
                else{itPtr.back()=ptr;}
            };
            
        };


        pri::list<qual> qualifiers;
        template <typename attrib >
        void putQualifier(){qualifiers.push(attrib::qualty);};
        void clearQualifier(){qualifiers.clear();}

        size_t LocationCur;
        size_t BindingCur;

        template <typename LayoutTy>
        void putLayout(){cast->layouts.back()};
        template <>void putLayout<stmt<meta>::Binding>(){cast->layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        template <>void putLayout<stmt<meta>::Location>(){cast->layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        // template <>void putLayout<stmt<q>::Location>(){cast->layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        


        void LayoutNew(){cast->layouts.push_back(stmt<q>::StmtLayout());}
expr<meta> getExpr(){return getExprFrom(lexq.begin());}

        void setVersion(uint s){cast->version=s;};
        uint getNum(std::string s){
            uint i=0;
            for(char c : s) {
                if(isdigit(c)){i*=10;i+=(c-'0');}
            }
            return i;
        };
       
        template <lex::ty t,template <temp q> typename T>
        T<meta> getFromUntilStripped(pri::deque<lex> stripped);

        template <lex::ty t>
        expr<meta> getFromUntilStripped<t,expr>(pri::deque<lex> stripped){

        };
        
        template <lex::ty t>
        stmt<meta>::block getFromUntilStripped<t,stmt<meta>::block>(pri::deque<lex> stripped){
            
        };
        

        template <lex::ty t>
        pri::deque<lex> strippedUntil(){
            pri::deque<lex> stripped;
            for(;itPtr.back()->t!=t;++(itPtr.back())){
                if constexpr (t != lex::ty::space){
                    if(ite->t==lex::ty::space){continue;}
                }
                if constexpr (t != lex::ty::nl){
                    if(ite->t==lex::ty::nl){continue;}
                }
                stripped.push_back(*(itPtr.back()));
                if(stripped.back().t==lex::ty::name){pri::deque<lex>::iter pr=prevTOK(stripped.tail());
                    if(pr->t==lex::ty::name){pr->t=lex::ty::typeName;}}
            };
            return stripped;
        };
        template <lex::ty t,lex::ty By>
        pri::deque<lex> strippedUntilBy(pri::deque<lex>::iter& res,bool* found){
            *res=false;
            deque<lex> stripped;
            for(;itPtr.back()->t!=t;++(itPtr.back())){
                if constexpr (t != lex::ty::space){
                    if(ite->t==lex::ty::space){continue;}
                }
                if constexpr (t != lex::ty::nl){
                    if(ite->t==lex::ty::nl){continue;}
                }
                stripped.push_back(*itPtr.back());
                if (itPtr.back()->t==By){res=stripped.tail();*found=true;}// TODO err<found_2assignments in statement>
            };
            return stripped;
        };
        
        template <lex::ty t,template <temp q> typename T>
        T<meta> getFromUntil(){
            deque<lex> stripped = strippedUntil<t>(it);
            return getFromUntilStripped<t,T>(stripped);
        };

        template <lex::ty t,lex::ty by ,template <temp q> typename T>
        T<meta> getFromUntilBy(){
            pri::deque<lex>::iter itr;bool found;
            deque<lex> stripped = strippedUntilBy<t,by>(itr,found);
            return getFromUntilStrippedBy<t,by,T>();
        };
        expr<meta> getExprUntil_EOSTMT(){
            return getFromUntil<lex::ty::semicolon,stmt>();
        };
        expr<meta> getExprUntil_EOL(){
            expr<meta> m= getFromUntil<lex::ty::nl,expr>();
            erase()
        };
        stmt<meta> getMetaUntil_EOSTMT(){
            
        };
        tu<meta> getTUUntil_EOTU(){

        };
        stmt<meta>::block getBlockUntil_EOL(){
            return getExprFrom<lex::ty::nl,block>(it);
        };
        stmt<meta>::block getBlockUntil_EOBLOCK(){
            pri::list<stmt<meta>> stmts;

        };
        template <typename KW,typename... KWs>
        bool kwFound(pri::deque<lex>::iter it) ;
        template <typename KW>
        bool kwFound(pri::deque<lex>::iter it){return KW::check(*this,it->u.name);};
        template <typename KW,typename... KWs>
        bool kwFound(pri::deque<lex>::iter it){
            if(kwFound<KW>()){return true;}
            else {return kwFound<KWs...>();}
        } ;
        
        expr<meta> resExpr;stmt<meta> resStmt;
        template <lex::ty T>
        bool lexTyOneOf(lex& l){
            return (l.t==T);
        };
        template <lex::ty T,lex::ty... Ts>
        bool lexTyOneOf(lex& l){
            if(lexTyOneOf<T>(l)){return true;}
            return lexTyOneOf<Ts...>(l);
        };
        
        template <typename KW,typename... KWs>
        expr<meta> kwsExpr(pri::deque<lex> stripped){
            resExpr=expr<meta>();
            for(lex s : stripped){
                if(lexTyOneOf<lex::ty::Name,lex::ty::typeName>(s)){

                };
            };
        };
        template <typename KW,typename... KWs>
        stmt<meta> kwsStmt(pri::deque<lex> stripped){
            resStmt=stmt<meta>();
             for(lex s : stripped){
                if(lexTyOneOf<lex::ty::Name,lex::ty::kw,lex::ty::typeName>(s)){

                };
            };
        };
        

        void pushVecDecl(size_t d);
        void pushMatDecl(size_t dx,size_t dy);
        void pushVecConstructor(size_t d);
        void pushMatConstructor(size_t dx,size_t dy);
        stmt<meta> Stmt(pri::deque<lex> stripped){return kwsStmt<KW_LIST>(stripped);};
        expr<meta> Expr(pri::deque<lex> stripped){return kwsExpr<KW_LISTPRIM>(stripped);};

        template <typename KW,typename... KWs >
        void untilKW();
        template <typename KW>
        void untilKW(){KW k;while(kwFound(k)==std::string::npos){next();}};

        template <typename KW,typename... KWs>
        void untilKW(){
        KW k;
        for(;kwFound<kw,KWs>(k)();next()){};    
    };

        static const size_t  =context_join<KW,KWs...>::s;
        template <typename KW>
        void putKw(){KW::type;};
          
        
        void erase(){itPtr.pop();
            lexq.eraseFromEnd(itPtr.back());itPtr.pop();
        };

        template <typename MSTMT_TY>
        void getMacro(){expr<meta> e = kwsExpr();};

        void include(std::filesystem::path pth){parser p;cast->include(p.fromFile(pth));};
        void includeRel(std::filesystem::path l){
            std::filesystem::path wd=cwd.back();
            std::filesystem::path pth = wd;pth/=l;
            if(std::filesystem::exists(pth)){
                parser pn;cast->include(pn.fromFile(pth,*this));}
            else {syserr.err<err::t::fileNotFound>(*this);}
        };
        void includeAbs(std::filesystem::path l){
            for(std::filesystem::path p : dirs.arr ){
                std::filesystem::path pth = p;pth/=l;
                if(std::filesystem::exists(ps)){parser pn;cast->include(pn.fromFile(pth,*this));return;}
            };
            syserr.err<err::t::fileNotFound>(*this);
        };
        template<>void getMacro<mStmtInclude>(){
             itPtr.push(itPtr.back());
            until<lex::ty::nl>();
            ++(itPtr.back());
            if(itPtr.back()->t==lex::ty::ltangle){
                ++(itPtr.back());
                std::filesystem::path p;
                for(;itPtr.back()->t!=lex::ty::gtangle;++(itPtr.back())){
                    if(lexTyOneOf<lex::ty::div,lex::ty::escape>(itPtr.back()->t)){
                        continue;
                    }
                    if(itPtr.back()->t!=lex::ty::name){syserr.err<err::t::include_closing_angle_brackets>(*this);break;}
                    p/=std::filesystem::path(itPtr.back()->u.name);
                }
                includeAbs(p);
            };
            else if(itPtr.back()->t==lex::ty::dq){
                ++itPtr.back();
                std::filesystem::path p;
                for(;itPtr.back()->t!=lex::ty::dq;itPtr.back()){
                    if(lexTyOneOf<lex::ty::div,lex::ty::escape>(itPtr.back()->t)){
                        continue;
                    }
                    if(itPtr.back()->t!=lex::ty::name){syserr.err<err::t::include_closing_dq>(*this);break;}
                    p/=std::filesystem::path(itPtr.back()->u.name);
                }
                includeRel(p);
            }
            else {err<>();}            
            erase();
        };
        template<>void getMacro<mStmtIf>(){
            // itPtr.push(itPtr.back())
            expr<meta> ex = getExprUntil_EOL();
            cast->tus.emplace_back(ex);
            erase();
            
        };
        template<>void getMacro<mStmtDefine>(){
            itPtr.push(until<lex::ty::Name>());
            macros.emplace(ptr->u.name,getExprUntil_EOL());
            erase();
        };
        template<>void getMacro<mStmtElif>(){
            itPtr.push(itPtr.back());
            cast->tus.emplace_back(getExprUntil_EOL());
            erase();
        };
        template <bool b>
        bool cond(bool t){return b?t:!t;};
        template <bool b>
        void IfDf(){
            itPtr.push(until<lex::ty::Name>());
            if( cond<b>(macros.exists(ptr->u.name))){
                erase();
                cast->tus.emplace_back(expr<meta>(true));
                untilKW<kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>()
            }
            else{
                erase();   
                cast->tus.emplace_back(expr<meta>(false));
                untilKW<kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>()
            }
        };
        
        template<>void getMacro<mStmtIfdef>(){IfDf<true>();};
        template<>void getMacro<mStmtElifdef>(){IfDf<true>();  };
        template<>void getMacro<mStmtIfndef>(){IfDf<false>()};
        template<>void getMacro<mStmtElifndef>(){IfDf<false>()};

        template<>void getMacro<mStmtElse>(){
            erase();
            cast->tus.emplace_back(cast->tus.back().condition.Not());
        };
        template<>void getMacro<mStmtEndIf>(){
            cast->tus.emplace_back(true);
        };




        ast* fromFile(std::filesystem::path pth){ curFilePath = pth;
            emplace_ast(pth);cast=&(asts.back());
        cwd.push(pth.parent_path());
        f.open(pth);
        pos=0;
        while(Line()){untilKW<KW_LIST>();}
        if(pth.extension()==std::filesystem::path("hstmsl")){
           wrcph(pth,cur); 
        }
        cwd.pop();
        };
        ast fromFile(std::string pth){filePos =0; std::filesystem::path s(pth);return fromFile(s); }

    
}
}
#endif