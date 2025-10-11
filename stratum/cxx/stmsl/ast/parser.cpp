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
    std::string name ;
    pri::deque<lex> value;
    size_t filePos,ln,col;

    size_t argc;
    std::vector<std::string> args;
    void argc(pri::deque<lex> val){bool open =false;size_t s=0;
        pri::deque<lex>::iter it = val.begin();
        for(;it;++it){lex& l=*it;
            if( l.t==lex::ty::rparen){++it;break;};
            if(open ){
                if(l.t==lex::ty::comma){s++;};
                if(l.t==lex::ty::Name){args+=l.u.name;}
                continue;}
            if(l.t==lex::ty::lparen){open=true;continue;}
            else{break;}
        }
        for(;it;++it){value.push_back(*it);}
        argc=s;
    };
    macro(std::string _name,pri::deque<lex> _val) : name(_name)  {
        pri::deque<lex> val;
        for(lex l : _val){
            if(l.t==lex::ty::Name){
                size_t p=0;
                size_t pp=0
                for(p = l.u.name.find_first_of("#",p);;p = l.u.name.find_first_of("#",p)){
                    if(p!=std::string::npos  ){
                         if(l.u.name[p+1] == lex::ty::str){
                            val.emplace_back(l.u.name.substr(pp,p-pp+1));
                            val.emplace_back(lex::ty::tokpaste);
                            p+=2;pp+=2;
                         }
                         else {
                            val.emplace_back(l.u.name.substr(pp,p-pp+1));
                            val.emplace_back(lex::ty::str);
                            p++;pp++;
                         }
                    }
                    else {
                        val.emplace_back(l.u.name.substr(pp));break;
                    }
                }
                continue;
            };
            val.push_back(l);
        };
        argc(val);
    };
    
    
    bool get(pri::deque<lex>* ptr,std::vector<std::string> s={}){
        if(s.length()!=argc){return false;};
        for(lex l : value){
            if(l.t==lex::ty::Name){size_t p=0;bool found=false;
                for(std::string n : args){
                    if(l.u.name == n){ptr->emplace_back(s[p],l);found=true;break;}
                    p++;
                }
                if(found){continue;}

            }
            ptr->push_back(l);
        }
        return true;
    };
};

struct macrosl {
    pri::list<macro> mlist ;
    pri::stack<expr<inst>> condition;
    bool operator==(ast<temp::meta> st){

    };
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
    template <bool func>
    bool exists(std::string name){
        for(macro m : mlist){
            if(m.name==name){
                return true;}
        };
        return false;
    };
    bool get(std::string name,macro* ma){
        for(macro m : mlist){
            if(m.name==name){*ma=m;
                return true;}
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
        
        
        std::string line;
        
        posit pos;
        ast* cast;     
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

         template <lex::ty tokT>void up_cntxt();
         template <>void up_cntxt<lex::ty::NumUint>(){};
         template <bool Eval,typename... TS >
         void lexEmplace(TS... args){
            if constexpr(Eval){lexq.emplace_back(args...);}
            else {lexq.back()=lex(args...);}
         };
         template <bool Eval>
        void lexsw(){
  if(isdigit(line[pos])){
                        switch(lexq.back().t){
                            case lex::ty::NumUint : {lexq.back().addUnum(line[pos]);continue;}
                            case lex::ty::NumFlt : {lexq.back().addUnum(line[pos]);Mag++;continue;}
                            default : {lexq.back().setUnum(line[pos]);};continue;}
                    }
                    else {if(lexq.back().t==lex::ty::NumFlt){lexq.back().setFlt(Mag);Mag=0;};}
             

                switch(line[pos]){
                    case lex::ty::escape :{++pos;continue;}
                    case lex::ty::dq : {lexEmplace<Eval>(pos,lex::ty::dq);continue;}
                    case lex::ty::sq : {lexEmplace<Eval>(pos,lex::ty::sq);continue;}
                    case lex::ty::lparen :{lexEmplace<Eval>(pos,lex::ty::lparen);continue;}
                    case lex::ty::rparen :{lexEmplace<Eval>(pos,lex::ty::rparen);continue;}
                    case lex::ty::lbrace :{lexEmplace<Eval>(pos,lex::ty::lbrace);continue;}
                    case lex::ty::rbrace :{lexEmplace<Eval>(pos,lex::ty::rbrace);continue;}
                    case lex::ty::lbrack :{lexEmplace<Eval>(pos,lex::ty::lbrack);continue;}
                    case lex::ty::rbrack :{lexEmplace<Eval>(pos,lex::ty::rbrack);continue;}
                    case lex::ty::ltangle :{lexEmplace<Eval>(pos,lex::ty::ltangle);continue;}
                    case lex::ty::dot :{
                        if(lexq.back().t==lex::ty::dot and(line[pos+1]==lex::ty::dot)){
                            ++pos;lex.back().t=lex::ty::pack;}
                        else {lexEmplace<Eval>(pos,lex::ty::dot);}
                        continue;
                        }
                    case lex::ty::comma :{lexEmplace<Eval>(pos,lex::ty::comma);continue;}
                    case lex::ty::semicolon :{lexEmplace<Eval>(pos,lex::ty::semicolon);continue;}
                    case lex::ty::colon :{
                        if(lexq.back().t==lex::ty::colon){lexq.back().t=lex::ty::dcolon;}
                        else {lexEmplace<Eval>(pos,lex::ty::colon);continue;}
                    }
                    case lex::ty::space :{
                        if(!(lexq.back().t == lex::ty::space or (lexq.back().t == lex::ty::nl))){
                            lexEmplace<Eval>(pos,lex::ty::space);};
                            continue;}
                    case lex::ty::nl :{if(lexq.back().t == lex::ty::nl){lexEmplace<Eval>(pos,lex::ty::nl);};continue;}
                    case lex::ty::plus : {if(line[pos+1]==lex::ty::plus){lexEmplace<Eval>(pos,lex::ty::pp);}else{lexEmplace<Eval>(pos,lex::ty::plus);};continue;}
                    case lex::ty::minus : {{if(line[pos+1]==lex::ty::minus){lexEmplace<Eval>(pos,lex::ty::mm);}else{lexEmplace<Eval>(pos,lex::ty::minus);};continue;}}
                    case lex::ty::band : {if(line[pos+1]==lex::ty::band){lexEmplace<Eval>(pos,lex::ty::oand);}else{lexEmplace<Eval>(pos,lex::ty::band);};continue;}
                    case lex::ty::bor :{if(line[pos+1]==lex::ty::bor){lexEmplace<Eval>(pos,lex::ty::oor);}else{lexEmplace<Eval>(pos,lex::ty::bor);};continue;}
                    case lex::ty::bxor : {lexEmplace<Eval>(pos,lex::ty::bxor);continue;}
                    case lex::ty::mul : {lexEmplace<Eval>(pos,lex::ty::mul);continue;}
                    case lex::ty::div : {lexEmplace<Eval>(pos,lex::ty::div);continue;}
                    case lex::ty::cond : {lexEmplace<Eval>(pos,lex::ty::cond);continue;}
                                    
                };
                if(lexq.back().t==lex::ty::Name){lexq.back().u.name+=line[pos];}
                else{
                    if(lexq.back().t==lex::ty::dot){lexEmplace<Eval>(pos,line[pos]);lexq.back().t=lex::ty::member;};)}
                    else{lexEmplace<Eval>(pos,line[pos]);}
                };
       
        pri::stack<pri::deque<lex>::iter> itPtr;

        // pri::stack<stmt<temp::meta>::block*> openedBlocks;
        // pri::stack<expr<temp::meta>*> openedInitializers;
                
        std::ifstream f;std::filesystem::path curFilePath;
        bool NewLine(){pos++;if(std::getline(f,line)){return true}; return false;}
        bool Line(){
            if(NewLine()){for(;pos<line.length();pos++){lexsw<true>();}
            return true;}
            else{return false;}
        };
        template <bool Eval>
        bool next(){
            ++pos;
            if(pos<line.length()){lexsw<Eval>();}
            else {if(!NewLine()){return false;};lexsw<Eval>();}
            return true;
        };
        size_t linecur,linecurnext;


        lex& prevTOK(pri::deque<lex>::iter it){
            pri::deque<lex>::iter itr = it;--itr;return itr;};
        lex& nextTOK(pri::deque<lex>::iter it){
            pri::deque<lex>::iter itr = it;++itr;return itr;};
        
        template <bool Eval,lex::ty tok>
        void until(){
            itPtr.push(itPtr.back());
            pri::deque<lex>::iter ptr=itPtr.back();
            ++ptr;
            for(;(itPtrc->t!=tok);++ptr){
                if(!ptr){next<Eval>();ptr=itPtr.back();}
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
        template <lex::ty fromTok,lex::ty toTok>
        pri::deque<lex> strippedFromUntil(pri::deque<lex>::iter& res,bool* found){
            *res=false;
            deque<lex> stripped;
            for(;itPtr.back()->t!=toTok;++(itPtr.back())){
                if constexpr (fromTok != lex::ty::space){
                    if(ite->t==lex::ty::space){continue;}
                }
                if constexpr (fromTok != lex::ty::nl){
                    if(ite->t==lex::ty::nl){continue;}
                }
                stripped.push_back(*itPtr.back());
                if (itPtr.back()->t==fromTok){res=stripped.tail();*found=true;}
            };
            return stripped;
        };
        
        template <lex::ty t,template <temp q> typename T>
        T<meta> getFromUntil(){
            pri::deque<lex> stripped = strippedUntil<t>();
            return getFromUntilStripped<t,T>(stripped);

            erase();
        };
        template <lex::ty t>
        stmt<meta> getFromUntil<t,stmt>(){
        pri::deque<lex> stripped =strippedUntil<t>();
        stmt<meta> res;
        };

        template <lex::ty tokFrom,lex::ty tokUntil ,template <temp q> typename T>
        T<meta> getFromUntil(){
            itPtr.push_back(itPtr.back());

            deque<lex> stripped = strippedFromUntil<t,by>(itr,found);
            return getFromUntilStripped<t,by,T>();
        };
        template <lex::ty tok>
        expr<meta> getExprUntil(){return getFromUntil<tok,expr>();};
        expr<meta> getExprUntil_EOSTMT(){return getExprUntil<lex::ty::semicolon>();};
        expr<meta> getExprUntil_EOL(){return getExprUntil<lex::ty::nl>();};
        template <lex::ty tok>
        stmt<meta> getStmtUntil(){return getFromUntil<tok,stmt>();};
        stmt<meta> getStmtUntil_EOSTMT(){return getStmtUntil<lex::ty::semicolon>();};
        
        tu<meta> getTUUntil_EOTU(){

        };
        stmt<meta>::block getBlockUntil_EOL(){
            return getExprFrom<lex::ty::nl,block>(it);
        };
        stmt<meta>::block getBlockUntil_EOBLOCK(){
            pri::list<stmt<meta>> stmts;

        };
        
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
        
        pri::stack<accSpec> curAcc;
        template <accSpec acc>void access(){curAcc.back()=acc;};
        template <accSpec acc>void accessPush(){curAcc.push(acc);};
        
        void getStruct(){
            bool decl;
            if(decl){curAcc.pop();}
        };
        
        void pushVecDecl(size_t d);
        void pushMatDecl(size_t dx,size_t dy);
        void pushVecConstructor(size_t d);
        void pushMatConstructor(size_t dx,size_t dy);

        template <lex::ty tok>
        stmt<temp::meta>::block getBlockUntil(){
            for(;itPtr.back().t!=tok;++(itPtr.back())){
                getStmtUntil_EOSTMT()
            };
        };
        bool LOOP_DO=false;
        template <typename T>
        T getLoopStmt();
        template <> stmt<temp::meta>::StmtFor getLoopStmt<stmt<temp::meta>::StmtFor>(){
            until<lex::ty::lparen>();
            getBlockUntil<stmt::ty::rparen>();
        };

        template <typename T>
        void putLoop(){
            if(LOOP_DO){
                pri::get<T>(pri::get<stmt<meta>::StmtDo>(cast->tus.back().curBlock()).loop) = getLoopStmt<T>();
                LOOP_DO = false;
            }
            else {cast->tus.back().stmts.push_back(getLoopStmt<T>());}
        };

        

        stmt<meta> Stmt(pri::deque<lex> stripped){return kwsStmt<KW_LIST>(stripped);};
        expr<meta> Expr(pri::deque<lex> stripped){return kwsExpr<KW_LISTPRIM>(stripped);};

        template <typename KW,typename... KWs>
        bool kwFound(pri::deque<lex>::iter it){
            if(KW::check(*this,it->u.name)){KW::proc(*this);return true;}
            else {return kwFound<KWs...>();}
            return false;
        } ;
        template <typename KW,typename... KWs>
        bool _kwFound(){KW k;
            if(k.check(*this,it->u.name)){k.proc(p);return true;}
            else {return kwFound<KWs...>();}
            return false;
        } ;

        template <bool Eval,typename KW,typename... KWs>
        void untilKW(){for(;!kwFound<KW,KWs>();next<Eval>){
            for(;itPtr.back()->t!=lex::ty::Name;next<Eval>()){};};};
        };};
        
        template <bool Eval,typename KW,typename... KWs>
        void _untilKW(){for(;!_kwFound<KW,KWs>();next<Eval>){
            for(;itPtr.back()->t!=lex::ty::Name;next<Eval>()){};};};
        
        static const size_t  =context_join<KW,KWs...>::s;
        template <typename KW>
        void putKw(){KW::type;};
          
        
        void erase(){itPtr.pop();
            lexq.eraseFromEnd(itPtr.back());itPtr.pop();
        };

        template <typename MSTMT_TY>
        void getMacro();

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
            cast->condition= getExprUntil_EOL();
            // cast->tus.emplace_back(ex);
            erase();
            untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();
        };
        template<>void getMacro<mStmtDefine>(){
            until<lex::ty::Name>();
            macros.emplace(itPtr.back()->u.name,strippedUntil<lex::ty::nl>());
            erase();
        };
        template<>void getMacro<mStmtElif>(){getMacro<mStmtIf>();};
        template <bool b>
        bool cond(bool t){return b?t:!t;};
        template <bool b>
        void IfDf(){
            itPtr.push(until<lex::ty::Name>());
            if( cond<b>(macros.exists(ptr->u.name))){
                erase();
                // cast->tus.emplace_back(expr<meta>(true));
                untilKW<true,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>()
            }
            else{
                erase();   
                // cast->tus.emplace_back(expr<meta>(false));
                untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>()
            }
        };
        
        template<>void getMacro<mStmtIfdef>(){IfDf<true>();};
        template<>void getMacro<mStmtElifdef>(){IfDf<true>();  };
        template<>void getMacro<mStmtIfndef>(){IfDf<false>()};
        template<>void getMacro<mStmtElifndef>(){IfDf<false>()};

        template<>void getMacro<mStmtElse>(){
            erase();
            cast->condition(!(cast->condition));
            if(cast->condition){
                untilKW<true,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();
            }else {untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();}
        };
        template<>void getMacro<mStmtEndIf>(){erase();};




        ast* fromFile(std::filesystem::path pth){ curFilePath = pth;parserStack.push(this);
            emplace_ast(pth);cast=&(asts.back());
        cwd.push(pth.parent_path());
        f.open(pth);
        pos=0;
        while(Line()){untilKW<KW_LIST>();}
        if(pth.extension()==std::filesystem::path("hstmsl")){
           wrcph(pth,cur); 
        }
        cwd.pop();
        parserStack.pop();
        return cast;
        };
        ast fromFile(std::string pth){filePos =0; std::filesystem::path s(pth);return fromFile(s); }

        

    }
}
#endif