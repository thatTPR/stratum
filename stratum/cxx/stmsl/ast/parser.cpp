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
// size_t Mag=0;
        pri::stack<pri::deque<lex>::iter> itPtr;
        pri::stack<lex::ty> opens;
        template <lex::ty t>struct openedt{static constexpr lex::ty l;}
        template <>struct openedt<lex::ty::rbrace>{static constexpr lex::ty l=lex::ty::lbrace;}
        template <>struct openedt<lex::ty::rbrack>{static constexpr lex::ty l=lex::ty::lbrack;}
        template <>struct openedt<lex::ty::rparen>{static constexpr lex::ty l=lex::ty::lparen;}
        template <>struct openedt<lex::ty::rangle>{static constexpr lex::ty l=lex::ty::langle;}
        template <lex::ty t>
        void open(){
            opens.push(t);
            // switch constexpr (t){
            //     case lex::ty::lparen : {opens.push(t)};
            //     case lex::ty::lbrace : {opens.push(t)};
            //     case lex::ty::lbrack : {opens.push(t)};
            //     default 
            // };
        };
        template <lex::ty t>
        void close(){if(opens.top()==openedt<t>::l){opens.pop();}else{syserr.err<unexpectedToken>(*this);}};

        pri::deque<lex>::iter& lexptrback(){return itPtr.back();}
        lex& lexitback(){return *(lexptrback());}

         template <lex::ty tokT>void up_cntxt();
         template <>void up_cntxt<lex::ty::NumUint>(){};
         template <bool Eval,typename... TS >
         void lexEmplace(TS... args){
            if constexpr(Eval){lexq.emplace_back(args...);lexptrback()=lexq.tail();}
            else {lexq.emplace_back(args...);lex(args...);}
         };
         template <bool Eval>
         void lexMod(lex::ty t,size_t s=1){
            if constexpr(Eval){lexq.back().t=t;lexq.back().pos.ecol+=s;}         }

        bool NewLine(){pos++;if(std::getline(f,line)){return true}; return false;}

        bool untilEOL(){return NewLine();};
        bool untilRBLcom(){
            while(NewLine()){
                for(;pos<line.length();++pos){
                    if(line[pos]=='/' and (line[pos-1]=='*')){return true;}
                };
            }
            return false;
        };
        void comPop(){
            if(lexitback()==lexq.back()){--lexptrback();}
            lexq.pop_back();
        };
        template <bool Eval>
        bool lexsw(){
  if(isdigit(line[pos])){
                        switch(lexq.back().t){
                            case lex::ty::NumUint : {lexq.back().addUnum(line[pos]);continue;}
                            case lex::ty::NumFlt : {lexq.back().addUnum(line[pos]);Mag++;continue;}
                            default : {lexq.back().setUnum(line[pos]);};continue;}
                    }
                    else {if(lexq.back().t==lex::ty::NumFlt){lexq.back().setFlt(Mag);Mag=0;};}
             

                switch(line[pos]){
                    case lex::ty::eq : {
                        switch(lexq.back().t){
                            case lex::ty::Not : {lexMod<Eval>(lex::ty::Noteq);break;}
                            case lex::ty::plus : {lexMod<Eval>(lex::ty::peq);break;}
                            case lex::ty::minus : {lexMod<Eval>(lex::ty::meq);break;}
                            case lex::ty::band : {lexMod<Eval>(lex::ty::andeq)break;}
                            case lex::ty::bor : {lexMod<Eval>(lex::ty::oreq);break;}
                            case lex::ty::mul : {lexMod<Eval>(lex::ty::muleq);break;}
                            case lex::ty::div : {lexMod<Eval>(lex::ty::diveq);break;}
                            default : { lexEmplace<Eval>(pos,lex::ty::eq);}
                        };
                    }
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
                            ++pos;lexMod<Eval>(lex::ty::pack,2);}
                        else {lexEmplace<Eval>(pos,lex::ty::dot);}
                        continue;
                        }
                    case lex::ty::comma :{lexEmplace<Eval>(pos,lex::ty::comma);continue;}
                    case lex::ty::semicolon :{lexEmplace<Eval>(pos,lex::ty::semicolon);continue;}
                    case lex::ty::colon :{
                        if(lexq.back().t==lex::ty::colon){lexMod<Eval>(lex::ty::dcolon);}
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
                    case lex::ty::mul : {
                        switch(lexq.back().t){
                            case lex::ty::div : {comPop();return untilRBLcom();}
                            default : {lexEmplace<Eval>(pos,lex::ty::mul);break;}
                        };
                        continue;
                        }
                    case lex::ty::div : {
                    if(lexq.back().t== lex::ty::div){comPop();return untilEOL();}
                        lexEmplace<Eval>(pos,lex::ty::div);break;
                    };
                    continue;}
                    case lex::ty::cond : {lexEmplace<Eval>(pos,lex::ty::cond);continue;}
                                    
                };
                if(lexq.back().t==lex::ty::Name){lexq.back().addname(line[pos]);}
                else{
                    if(lexq.back().t==lex::ty::dot){lexEmplace<Eval>(pos,line[pos]);lexq.back().t=lex::ty::member;};}
                    else{lexEmplace<Eval>(pos,line[pos]);}
                return true;
        };
       

        // pri::stack<stmt<temp::meta>::block*> openedBlocks;
        // pri::stack<expr<temp::meta>*> openedInitializers;
                
        std::ifstream f;std::filesystem::path curFilePath;
        inline bool Line(){
            if(NewLine()){for(;pos<line.length();pos++){if(!lexsw<true>()){return false;};}
            return true;}
            else{return false;}
        };
        template <bool Eval>
        inline bool next(){
            ++pos;
            if(pos<line.length()){lexsw<Eval>();}
            else {if(!NewLine()){return false;};lexsw<Eval>();}
            return true;
        };

        void nextTOK(){
            pri::deque<lex>::iter it =lexptrback();
            for(++it;;++it){
                if(!it){it=lexptrback();next<true>();}
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
     
        
        template <bool Eval,lex::ty tok,lex::ty... Expects>
        void until(){
            // itPtr.push(lexptrback());
            pri::deque<lex>::iter ptr=lexptrback();
            ++ptr;
            for(;(itPtrc->t!=tok);++ptr){
                if(!ptr){next<Eval>();ptr=lexptrback();}
                else{lexptrback()=ptr;
                    if(ptr->t==tok){return;};
                    if constexpr (sizeof...(Expects)>0){
                        if(!isOneOf<Expects...>(ptr->t)){
                            syserr.err<err::t::unexpectedToken,lex>(*this,*ptr );
                        };
                    }
                }
            };
        };
        
        template <lex::ty Tok,lex::ty... Toks>
        bool _isOneOf(lex::ty t){
            if(t==Tok){return true;}
            if constexpr (sizeof...(Toks)==0){return false;}
            return isOneOf<Toks...>(t);
        };
        template <lex::ty... Toks>
        bool isOneOf(lex::ty t){
            if(sizeof...(Toks)==0){return true;}
            else return _isOneOf<Toks...>(t);
        };
        
     
        // template <>void putLayout<stmt<q>::Location>(){cast->layouts.back().t=stmt<q>::StmtLayout::ty::binding;};
        


        void LayoutNew(){cast->layouts.push_back(stmt<q>::StmtLayout());}
expr<meta> getExpr(){return getExprFrom(lexq.begin());}

        void setVersion(uint s){cast->version=s;};
        
       


        template <lex::ty T>
        bool lexTyOneOf(lex& l){
            return (l.t==T);
        };
        template <lex::ty T,lex::ty... Ts>
        bool lexTyOneOf(lex& l){
            if(lexTyOneOf<T>(l)){return true;}
            return lexTyOneOf<Ts...>(l);
        };
        template <lex::ty to,lex::ty... exp>
        bool Continue(lex& i){
                if constexpr (to != lex::ty::space){
                    if(i.t==lex::ty::space){return true;}};
                if constexpr (to != lex::ty::nl){
                    if(i.t==lex::ty::nl){return true;}};
                return false;
        };
        using lexres=pri::deque<pri::deque<lex>::iter>;
        void evalName(){
            pri::deque<std::string > nsName;
            pri::deque<lex>::iter start=itPtr.prev();
            for(;start!=lexptrback();++start){
                if(start->t==lex::ty::dcolon){continue;}
                nsName.push_back(start->u.name);
            };
            cast->findName(nsName);
        };
        
        template <lex::ty to>
        void until(){
            pri::deque<lex>::iter ptr=lexptrback();
            for(;lexptrback()->t!=to;++(lexptrback())){
                if(lexptrback()){lexptrback()=ptr;next();continue;}
                ptr=lexptrback();
            };
        };
        template <lex::ty t,lex::ty... ts>
        void untilDif(){while(isOneOf<t,ts...>(lexptrback()->t)){nextTOK();}};
        template <lex::ty to,lex::ty... Expecteds>
        lexres untilExp(){
            lexres unexp;
            pri::deque<lex>::iter ptr=lexptrback();
            for(;lexptrback()->t!=to;++(lexptrback())){
                if(lexptrback()){lexptrback()=ptr;next();continue;}
                ptr=lexptrback();
                if(Continue(lexitback())){continue;}
                    if(!lexTyOneOf<Expecteds...>(lexitback().t)){unexp.push_back(lexptrback());}
            };
            return unexp;
        };
        template <lex::ty fromTok,lex::ty toTok,lex::ty... Expecteds>
        lexres  fromUntilExp(){
            lexres r=untilExp<fromTok>();
            r+=untilExp<toTok,Expecteds...>();
            return r;
        };
        template <lex::ty fromTok,lex::ty toTok>
        void fromUntil(){
            until<fromTok>();
            until<toTok,Expecteds...>();
        };
        template <lex::ty fromTok,typename T>
        T getLexedTo();
        template <lex::ty fromTok,lex::ty toTok,typename T>
        T getLexedFromTo();
        template <lex::ty fromTok,lex::ty toTok,typename T,lex::ty... exp>
        T getFromUntil(){
            fromUntil<fromTok,toTok,exp...>();
            return getLexed<fromTok,toTok,T>();
        };
        template <lex::ty to,typename T,lex::ty... exp>
        T getFromUntil(){
            fromUntil<fromTok,toTok,exp...>();
            return getLexed<fromTok,toTok,T>();
        };

        template <lex::ty terminator , lex::ty... expecteds>
        struct TypePrRule {
            static constexpr lex::ty term=terminator;

        };
        template <typename... VarTs>
        void lex(){

        };
        
        template <lex::ty fromTok,lex::ty toTok,template <temp q> typename T>
        T<temp::meta> _getFromUntil(){return getFromUntil<fromTok,toTok,T<temp::meta>();};


        template <lex::ty t, typename T>
        T getUntil(){
            lexres r=until<t,T>();

            return ;
        };

        template <lex::ty t,template <temp q> typename T>
        T<temp::meta> _getUntil(){return getUntil<t,T<temp::meta>();        };
        
        template <lex::ty tokFrom,lex::ty tokUntil , typename T>
        T getFromUntil(){
            itPtr.push_back(lexptrback());
            deque<lex> stripped = strippedFromUntil<t,by>(itr,found);
            return getFromUntilStripped<t,by,T>();

        };     
        template <lex::ty tokFrom,lex::ty tokUntil ,template <temp q> typename T>
        T<temp::meta> _getFromUntil(){return getFromUntil<tokFrom,tokUntil,T<temp::meta>>()};
        
       
        expr<meta> resExpr;stmt<meta> resStmt;
        
        
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
            for(;lexptrback().t!=tok;++(lexptrback())){
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
        void untilKW(){for(;!kwFound<KW,KWs...>();next<Eval>){
            for(;lexptrback()->t!=lex::ty::Name;next<Eval>()){};};};
        };
        
        template <bool Eval,typename KW,typename... KWs>
        void _untilKW(){for(;!_kwFound<KW,KWs...>();next<Eval>){
            for(;lexptrback()->t!=lex::ty::Name;next<Eval>()){};};};
        
        static const size_t  =context_join<KW,KWs...>::s;
        template <typename KW>
        void putKw(){KW::type;};
        template <typename KW>
        void putKWt(){

        };
        
        // Handling Structs
        template <typename T> T get();
        template<> std::string get<std::string>(){
            untilDif<lex::ty::space,lex::ty::nl>();
            if(lexptrback().t==lex::ty::name){
                return lexptrback().u.name;
            }
            else {syserr.err<err::t::unexpectedToken>(*this);return std::string();}
        };
        template <> param<temp::inst> get<param<temp::inst>(){
            param<temp::meta> p;
            for(;!isOneOf<lex::ty::comma,lex::ty::rangle>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::Name){
                    if(kw_Class::check(*this,lexitback().u.name)){p.t=param::ty::Typename;continue;}
                    if(kw_Typename::check(*this,lexitback().u.name)){p.t=param::ty::Typename;continue;}
                    if(kw_Template::check(*this,lexitback().u.name)){p.t=param::ty::Template;
                        untilExp<lex::ty::langle,lex::ty::space>();
                        for(;!isOneOf<lex::ty::comma,lex::ty::rangle>();nextTOK()){
                            p.d=get<param<temp::inst>>());
                        };
                        untilKWs<kw_Class,kw_Typename>();continue;}
                    p.name=lexitback().u.name;break;
                };
            };
        };
        template <> param<temp::meta> get<param<temp::meta>(){
            param<temp::meta> p;bool tyNamed=false;
            for(;!isOneOf<lex::ty::comma,lex::ty::rangle>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::dcolon){if(nsName.empty()){syserr::err<unexpectedToken>(*this);};continue;}
                if(lexitback().t==lex::ty::space){if(!nsName.empty()){tyName=true;}}
                if(lexitback().t==lex::ty::Name){
                    if(kw_Class::check(*this,lexitback().u.name)){tyNamed=true;p.t=param::ty::Typename;continue;}
                    if(kw_Typename::check(*this,lexitback().u.name)){tyNamed=true;p.t=param::ty::Typename;continue;}
                    if(kw_Template::check(*this,lexitback().u.name)){tyNamed=true;p.t=param::ty::Template;
                        untilExp<lex::ty::langle,lex::ty::space>();
                        for(;!isOneOf<lex::ty::comma,lex::ty::rangle>();nextTOK()){
                            pri::get<pri::list<param<temp::meta>>>(p.d).push_back(get<param<temp::meta>>());
                        };
                        untilKWs<kw_Class,kw_Typename>();continue;}
                    p.name=lexitback().u.name;break;
                };
            };
            erase();
            return p;
        };
        
        template <> stmt<temp::inst>::param_list get<stmt<temp::inst>::param_list>(){
            stmt<temp::inst>::param_list plist;
            lexres r= untilExp<lex::ty::langle,lex::ty::space,lex::ty::nl>();
            if(!r.empty()){syserr.err<err::t::unexpectedToken>(*this,r);}
                open<lex::ty::langle>();
                itPtr.push_back(itPtr.back());
                lexres rs = untilExp<lex::ty::comma,lex::ty::space,lex::
        };

        template <> type<temp::inst> get<type<temp::inst>>(){
            nstype nsNames;
            if(lexitback().t!=lex::ty::name){syserr.err<err::t::unexpectedToken>(*this);}
            nsNames.
            for(;)
            type<temp::inst> ty;
            
            for(;;)
        };
        template <> stmt<temp::meta>::param_list get<stmt<temp::meta>::param_list>(){
            
            stmt<temp::meta>::param_list plist;
            lexres r= untilExp<lex::ty::langle,lex::ty::space,lex::ty::nl>();
            if(!r.empty()){syserr.err<err::t::unexpectedToken>(*this,r);}
                open<lex::ty::langle>();
                pri::deque<lex>::iter it=itPtr.back();
                itPtr.push_back(itPtr.back());
                lexres rs = untilExp<lex::ty::comma,lex::ty::space,lex::nl,lex::ty::Name,lex::ty::eq,lex::ty::dcolon,lex::ty::langle,lex::ty::rangle>();
                if(!rs.empty()){syserr.err<err::t::unexpectedToken>(*this,rs);}
                
        };

        template <typename STMTty>
        void getStmt();
        
        template <>void getStmt<stmt<temp::meta>::block>(){
            itPtr.push_back(lexptrback());
            opened<lex::ty::lbrace>()
        };  
        template <>void getStmt<stmt<meta>::StmtNS>(){
            ;
            itPtr.push_back(lexptrback());
            until<lex::ty::lbrace>();
            pri::deque<lex>::iter it= itPtr.prev();itPtr.pop();
            for(++it;lexptrback()!=it;++it){
                if(it->t==lex::ty::Name){cast->emplace_back<stmt<meta>::StmtNS>(it->u.name;);}
            };
            untilClosedWith<lex::ty::rbrace>();
        };
        template <>void getStmt<stmt<meta>::StmtDeclType>(){};
        template <>void getStmt<stmt<meta>::StmtDefType>(){
            itPtr.push_back(lexptrback());
            untilExp<lex::ty::lbrace,lex::ty::space,lex::ty::colon,lex::ty::name>();
        };
        template <>void getStmt<typename stmt<meta>::StmtExpr>(){};
        template <>void getStmt<stmt<meta>::StmtAssign>(){};
        template <>void getStmt<stmt<meta>::StmtWhile>(){};
        template <>void getStmt<stmt<meta>::StmtFor>(){};
        template <>void getStmt<stmt<meta>::StmtForRange>(){};
        template <>void getStmt<stmt<meta>::StmtDo>(){};
        template <>void getStmt<stmt<meta>::StmtCase>(){};
        template <>void getStmt<stmt<meta>::StmtSwitch>(){};
        template <>void getStmt<stmt<meta>::StmtDefault(){}
        template <>void getStmt<stmt<meta>::StmtIf>(){};
        template <>void getStmt<stmt<meta>::StmtElse>(){};
        template <>void getStmt<stmt<meta>::StmtElseIf>(){};
        template <>void getStmt<stmt<meta>::StmtReturn>(){};
        template <>void getStmt<stmt<meta>::StmtFuncDecl>(){}
        template <>void getStmt<stmt<meta>::StmtFuncDef>(){}
        template <>void getStmt<stmt<meta>::StmtVarDecl>(){}
        template <>void getStmt<stmt<meta>::StmtUsing>(){};
        template <>void getStmt<stmt<meta>::StmtTypeDef>(){
            itPtr.push_back(lexptrback());
            nextTOK();
            untilDif<lex::ty::space>();
            type<temp::inst> tyn=get<type<temp::inst>>();std::string n=get<std::string>();
            cast->emplace_back<stmt<meta>::StmtTypeDef>(tyn,n);
            erase();
        };

        
        template <stmt<meta>::StmtLayout::stand st, Str s >struct lyt_std{
            stmt<meta>::StmtLayout::stand t =st;
            static constexpr auto value = s;
            std::string name(){return std::string(value.data.data());}

        };
        using std430 = lyt_std<stmt<meta>::StmtLayout::stand::std430,"std430">;
        using std140 = lyt_std<stmt<meta>::StmtLayout::stand::std430,"std140">;

        template <typename STD,typename... STDs>
        bool getStd(stmt<temp::meta>::StmtLayout& s){
            if(getStd(s)){return true;}
            return getStd<STDs...>(s);
        };
        template <typename STD>
        bool getStd(stmt<temp::meta>::StmtLayout& s){
            if(lexptrback()->u.name==STD::name()){s.st=STD::t;return true;};
            return false;
        };
        
        // using getLytAt = BoolFunc<stmt<temp::meta>::StmtLayout,getLytAt,lyt_at,lyt_ats...>;
        template <typename lyt_at,typename... lyt_ats>
        bool getLytAt(stmt<temp::meta>::StmtLayout& s){
            if(getLytAt<lyt_at>(s)){return true;};
            return getLytAt<,lyt_ats...>(s);
        };
        template <typename lyt_at>
        bool getLytAt(stmt<temp::meta>::StmtLayout& s){
            if(lexptrback()->u.name==lyt_at::name()){
                s.t=lyt_at::lytTy;
                lexres unexp=untilExp<lex::ty::eq,lex::ty::space>();
                unexp+=untilExp<lex::ty::NumUint,lex::ty::space>();
                if(!unexp.empty()){syserr.err<err::t::unexpectedToken>(*this,unexp);};
                s.loc=lexptrback().u.unum;
                return true;
            };
            return false;
        };
        
        template <>void getStmt<stmt<meta>::StmtLayout>(){
            cast->emplace_back<stmt<temp::meta>::StmtLayout>();
            stmt<temp::meta>::StmtLayout& lyt=cast->get<stmt<temp::meta>::StmtLayout>();
            itPtr.push_back(lexptrback());
            until<lex::ty::semicolon>();
            pri::deqeue<lex>::iter it=lexptrback();lexptrback()=itPtr.prev();
            lexres unexp = untilExp<lex::ty::lparen,lex::ty::space>();
            for(;lexptrback()->t==lex::ty::rparen;++lexptrback()){
                lexres unexp=untilExp<lex::ty::eq,lex::ty::space>();
                if( lexptrback()->t==lex::ty::Name) {
                    if(getStd<std430,std140>(lyt)){continue;}
                    if(getLytAt<kw_Location,kw_Binding>(lyt)){continue;};
                };
                if(!isOneOf<lex::ty::comma,lex::ty::space,lex::ty::Name>(lexptrback()->t)){
                    syserr.err<unexpectedToken>(*this);
                };
            };
            untilKW<kw_Buffer,kw_Uniform,kw_in,kw_out,kw_Flat>();
        };


        template <typename MSTMT_TY>
        void getMacro();

        void include(std::filesystem::path pth){parser p;cast->include(p.fromFile(pth));};
        void includeRel(std::filesystem::path l){
            std::filesystem::path wd=cwd.back();
            std::filesystem::path pth = wd;pth/=l;
            if(std::filesystem::exists(pth)){
                parser pn;cast->include(pn.fromFile(pth,*this));}
            else {syserr.err<err::t::fileNotFound>(*this,pth);}
        };
        void includeAbs(std::filesystem::path l){
            for(std::filesystem::path p : dirs.arr ){
                std::filesystem::path pth = p;pth/=l;
                if(std::filesystem::exists(ps)){parser pn;cast->include(pn.fromFile(pth,*this));return;}
            };
            syserr.err<err::t::fileNotFound>(*this,pth);
        };
        template<>void getMacro<mStmtInclude>(){
             itPtr.push(lexptrback());
            until<lex::ty::nl>();
            ++(lexptrback());
            if(lexptrback()->t==lex::ty::ltangle){
                ++(lexptrback());
                std::filesystem::path p;
                for(;lexptrback()->t!=lex::ty::gtangle;++(lexptrback())){
                    if(lexTyOneOf<lex::ty::div,lex::ty::escape>(lexptrback()->t)){
                        continue;
                    }
                    if(lexptrback()->t!=lex::ty::name){syserr.err<err::t::include_closing_angle_brackets>(*this);break;}
                    p/=std::filesystem::path(lexptrback()->u.name);
                }
                includeAbs(p);
            };
            else if(lexptrback()->t==lex::ty::dq){
                ++lexptrback();
                std::filesystem::path p;
                for(;lexptrback()->t!=lex::ty::dq;lexptrback()){
                    if(lexTyOneOf<lex::ty::div,lex::ty::escape>(lexptrback()->t)){
                        continue;
                    }
                    if(lexptrback()->t!=lex::ty::name){syserr.err<err::t::include_closing_dq>(*this);break;}
                    p/=std::filesystem::path(lexptrback()->u.name);
                }
                includeRel(p);
            }
            else {err<>();}            
            erase();
        };
        template<>void getMacro<mStmtIf>(){
            // itPtr.push(lexptrback())
            cast->condition= getExprUntil_EOL();
            // cast->tus.emplace_back(ex);
            erase();
            untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();
        };
        template<>void getMacro<mStmtDefine>(){
            until<lex::ty::Name>();
            macros.emplace(lexptrback()->u.name,strippedUntil<lex::ty::nl>());
            erase();
        };
        template<>void getMacro<mStmtElif>(){getMacro<mStmtIf>();};
        template <bool b>
        bool cond(bool t){return b?t:!t;};
        template <bool b>
        void IfDf(){
            itPtr.push_back(lexptrback());until<lex::ty::Name>();
            erase();
            if( cond<b>(macros.exists(ptr->u.name))){
                untilKW<true,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();}
            else{untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();}
        };
        
        template<>void getMacro<mStmtIfdef>(){IfDf<true>();};
        template<>void getMacro<mStmtElifdef>(){IfDf<true>();  };
        template<>void getMacro<mStmtIfndef>(){IfDf<false>()};
        template<>void getMacro<mStmtElifndef>(){IfDf<false>()};

        template<>void getMacro<mStmtElse>(){
            erase();
            cast->condition= !(cast->condition);
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