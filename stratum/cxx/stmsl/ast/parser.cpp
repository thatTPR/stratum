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
                            val.back(l.u.name.substr(pp,p-pp+1));
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

        std::string line;
        
        pri::stack<posit> pos;
        posit& posb(){return pos.back()};
        ast* cast;     
        pcntxt cntxt ;
                pri::stack<std::ifstream> f;pri::stack<std::filesystem::path> curFilePath;

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
        void erase(){
            itPtr.pop();
            lexq.eraseFromEnd(itPtr.back());
        };

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
        template <>
        void close<lex::ty::rbrace>(){if(opens.top()==openedt<lex::ty::rbrace>::l){opens.pop();cast->popbl();}else{syserr.err<unexpectedToken>(*this);}};


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

        bool NewLine(){posb()++;if(std::getline(f.back(),line)){return true}; return false;}

        bool untilEOL(){return NewLine();};
        bool untilRBLcom(){
            while(NewLine()){
                for(;posb()<line.length();++posb()){
                    if(line[posb()]=='/' and (line[posb()-1]=='*')){return true;}
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
  if(isdigit(line[posb()])){
                        switch(lexq.back().t){
                            case lex::ty::NumUint : {lexq.back().addUnum(line[posb()]);continue;}
                            case lex::ty::NumFlt : {lexq.back().addUnum(line[posb()]);Mag++;continue;}
                            default : {lexq.back().setUnum(line[posb()]);};continue;}
                    }
                    else {if(lexq.back().t==lex::ty::NumFlt){lexq.back().setFlt(Mag);Mag=0;};}
             

                switch(line[posb()]){
                    case lex::ty::eq : {
                        switch(lexq.back().t){
                            case lex::ty::Not : {lexMod<Eval>(lex::ty::Noteq);break;}
                            case lex::ty::plus : {lexMod<Eval>(lex::ty::peq);break;}
                            case lex::ty::minus : {lexMod<Eval>(lex::ty::meq);break;}
                            case lex::ty::band : {lexMod<Eval>(lex::ty::andeq)break;}
                            case lex::ty::bor : {lexMod<Eval>(lex::ty::oreq);break;}
                            case lex::ty::mul : {lexMod<Eval>(lex::ty::muleq);break;}
                            case lex::ty::div : {lexMod<Eval>(lex::ty::diveq);break;}
                            default : { lexEmplace<Eval>(posb(),lex::ty::eq);}
                        };
                    }
                    case lex::ty::escape :{++posb();continue;}
                    case lex::ty::dq : {lexEmplace<Eval>(posb(),lex::ty::dq);continue;}
                    case lex::ty::sq : {lexEmplace<Eval>(posb(),lex::ty::sq);continue;}
                    case lex::ty::lparen :{lexEmplace<Eval>(posb(),lex::ty::lparen);continue;}
                    case lex::ty::rparen :{lexEmplace<Eval>(posb(),lex::ty::rparen);continue;}
                    case lex::ty::lbrace :{lexEmplace<Eval>(posb(),lex::ty::lbrace);continue;}
                    case lex::ty::rbrace :{lexEmplace<Eval>(posb(),lex::ty::rbrace);continue;}
                    case lex::ty::lbrack :{lexEmplace<Eval>(posb(),lex::ty::lbrack);continue;}
                    case lex::ty::rbrack :{lexEmplace<Eval>(posb(),lex::ty::rbrack);continue;}
                    case lex::ty::ltangle :{lexEmplace<Eval>(posb(),lex::ty::ltangle);continue;}
                    case lex::ty::dot :{
                        if(lexq.back().t==lex::ty::dot and(line[posb()+1]==lex::ty::dot)){
                            ++posb();lexMod<Eval>(lex::ty::pack,2);}
                        else {lexEmplace<Eval>(posb(),lex::ty::dot);}
                        continue;
                        }
                    case lex::ty::comma :{lexEmplace<Eval>(posb(),lex::ty::comma);continue;}
                    case lex::ty::semicolon :{lexEmplace<Eval>(posb(),lex::ty::semicolon);continue;}
                    case lex::ty::colon :{
                        if(lexq.back().t==lex::ty::colon){lexMod<Eval>(lex::ty::dcolon);}
                        else {lexEmplace<Eval>(posb(),lex::ty::colon);continue;}
                    }
                    case lex::ty::space :{
                        if(!(lexq.back().t == lex::ty::space or (lexq.back().t == lex::ty::nl))){
                            lexEmplace<Eval>(posb(),lex::ty::space);};
                            continue;}
                    case lex::ty::nl :{if(lexq.back().t == lex::ty::nl){lexEmplace<Eval>(posb(),lex::ty::nl);};continue;}
                    case lex::ty::plus : {if(line[posb()+1]==lex::ty::plus){lexEmplace<Eval>(posb(),lex::ty::pp);}else{lexEmplace<Eval>(posb(),lex::ty::plus);};continue;}
                    case lex::ty::minus : {{if(line[posb()+1]==lex::ty::minus){lexEmplace<Eval>(posb(),lex::ty::mm);}else{lexEmplace<Eval>(posb(),lex::ty::minus);};continue;}}
                    case lex::ty::band : {if(line[posb()+1]==lex::ty::band){lexEmplace<Eval>(posb(),lex::ty::oand);}else{lexEmplace<Eval>(posb(),lex::ty::band);};continue;}
                    case lex::ty::bor :{if(line[posb()+1]==lex::ty::bor){lexEmplace<Eval>(posb(),lex::ty::oor);}else{lexEmplace<Eval>(posb(),lex::ty::bor);};continue;}
                    case lex::ty::bxor : {lexEmplace<Eval>(posb(),lex::ty::bxor);continue;}
                    case lex::ty::mul : {
                        switch(lexq.back().t){
                            case lex::ty::div : {comPop();return untilRBLcom();}
                            default : {lexEmplace<Eval>(posb(),lex::ty::mul);break;}
                        };
                        continue;
                        }
                    case lex::ty::div : {
                    if(lexq.back().t== lex::ty::div){comPop();return untilEOL();}
                        lexEmplace<Eval>(posb(),lex::ty::div);break;
                    };
                    continue;}
                    case lex::ty::cond : {lexEmplace<Eval>(posb(),lex::ty::cond);continue;}
                                    
                };
                if(lexq.back().t==lex::ty::Name){lexq.back().addname(line[posb()]);}
                else{
                    if(lexq.back().t==lex::ty::dot){lexEmplace<Eval>(posb(),line[posb()]);lexq.back().t=lex::ty::member;};}
                    else{lexEmplace<Eval>(posb(),line[posb()]);}
                return true;
        };
       

        // pri::stack<stmt<temp::meta>::block*> openedBlocks;
        // pri::stack<expr<temp::meta>*> openedInitializers;
                

        inline bool Line(){
            if(NewLine()){for(;posb()<line.length();posb()++){if(!lexsw<true>()){return false;};}
            return true;}
            else{return false;}
        };
        template <bool Eval>
        inline bool next(){
            ++posb();
            if(posb()<line.length()){lexsw<Eval>();}
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
     
        
        template <lex::ty T,lex::ty... Ts>
        bool OneOfLex(lex& l){
            if(OneOfLex<T>(l)){return true;}
            return OneOfLex<Ts...>(l);
        };
        template <lex::ty T>
        bool OneOfLex(lex& l){
            return (l.t==T);
        };
        template <typename Kw,typename... Kws>
        bool OneOfKw(std::string str){
            if(KW::check(*this,str)){return true;}
            else {return OneOfKw<Kws...>(str);}
        };
        template <typename Kw>
        bool OneOfKw(std::string str){
            if(KW::check(*this,str)){return true;}
            else {return false;}
        };

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
                        if(!OneOfLex<Expects...>(ptr->t)){
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
        void untilDif(){while(OneOfLex<t,ts...>(lexptrback()->t)){nextTOK();}};
        template <lex::ty to,lex::ty... Expecteds>
        lexres untilExp(){
            lexres unexp;
            pri::deque<lex>::iter ptr=lexptrback();
            for(;lexptrback()->t!=to;++(lexptrback())){
                if(lexptrback()){lexptrback()=ptr;next();continue;}
                ptr=lexptrback();
                if(Continue(lexitback())){continue;}
                    if(!OneOfLex<Expecteds...>(lexitback().t)){unexp.push_back(lexptrback());}
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
                if(OneOfLex<lex::ty::Name,lex::ty::typeName>(s)){

                };
            };
        };
        template <typename KW,typename... KWs>
        stmt<meta> kwsStmt(pri::deque<lex> stripped){
            resStmt=stmt<meta>();
             for(lex s : stripped){
                if(OneOfLex<lex::ty::Name,lex::ty::kw,lex::ty::typeName>(s)){

                };
            };
        };
        
        pri::stack<accSpec> curAcc;
        template <accSpec acc>void access(){curAcc.back()=acc;};
        template <accSpec acc>void accessPush(){curAcc.push(acc);};
      
        
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
        bool kwFound(){
            if(KW::check(*this,lexitback().u.name)){KW::proc(*this);return true;}
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
                stmt<temp::meta>::param_list plist;bool Template=false;

        template <> param<temp::inst> get<param<temp::inst>>(){
            param<temp::meta> p;
            for(;!OneOfLex<lex::ty::comma,lex::ty::rangle>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::Name){
                    if(kw_Class::check(*this,lexitback().u.name)){p.t=param::ty::Typename;continue;}
                    if(kw_Typename::check(*this,lexitback().u.name)){p.t=param::ty::Typename;continue;}
                    if(kw_Template::check(*this,lexitback().u.name)){syserr.err<err::t::templateInInstantiation>(*this);continue;}
                    p.d=get<type<temp::inst>>();
                };
            
            return p;
        };
        
        template <> param<temp::meta> get<param<temp::meta>>(){
            param<temp::meta> p;bool tyNamed=false;
            for(;!OneOfLex<lex::ty::comma,lex::ty::rangle>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::dcolon){if(nsName.empty()){syserr::err<unexpectedToken>(*this);};continue;}
                if(lexitback().t==lex::ty::space){if(!nsName.empty()){tyName=true;}}
                if(lexitback().t==lex::ty::Name){
                    if(kw_Class::check(*this,lexitback().u.name)){tyNamed=true;p.t=param::ty::Typename;continue;}
                    if(kw_Typename::check(*this,lexitback().u.name)){tyNamed=true;p.t=param::ty::Typename;continue;}
                    if(kw_Template::check(*this,lexitback().u.name)){tyNamed=true;p.t=param::ty::Template;
                        untilExp<lex::ty::langle,lex::ty::space>();
                        for(;!OneOfLex<lex::ty::comma,lex::ty::rangle>();nextTOK()){
                            pri::get<pri::list<param<temp::meta>>>(p.d).push_back(get<param<temp::meta>>());
                        };
                        untilKWs<kw_Class,kw_Typename>();continue;}
                    p.name=lexitback().u.name;break;
                };
            };
            return p;
        };
        
        template <> stmt<temp::inst>::param_list get<stmt<temp::inst>::param_list>(){
            stmt<temp::inst>::param_list plist;
            lexres r= untilExp<lex::ty::langle,lex::ty::space,lex::ty::nl>();
            if(!r.empty()){syserr.err<err::t::unexpectedToken>(*this,r);}
                itPtr.push_back(itPtr.back());
                while(lexitback().t!=lex::ty::rangle){
                    plist.push_back(get<param<temp::inst>>());
                };
            return plist;
        };
        template <> stmt<temp::meta>::param_list get<stmt<temp::meta>::param_list>(){
            stmt<temp::meta>::param_list plist;
            lexres r= untilExp<lex::ty::langle,lex::ty::space,lex::ty::nl>();
            if(!r.empty()){syserr.err<err::t::unexpectedToken>(*this,r);}
                // open<lex::ty::langle>();
                itPtr.push_back(itPtr.back());
                while(lexitback().t!=lex::ty::rangle){
                    plist.push_back(get<param<temp::meta>>());
                };
            return plist;      
        };

        template <> type<temp::meta> get<type<temp::meta>>(){type<temp::meta> r;
            nsacc<temp::inst> ns;
            itPtr.push_back(lexptrback());
            for(;lexptrback();nextTOK()){
                if(lexitback().t==lex::ty::space){break;}
                if(lexitback().t==lex::ty::name){
                    ns.emplace_back(lexitback().u.name);
                };
                if(lexitback().t==lex::ty::dcolon){continue;}
                if(lexitback().t==lex::ty::lbrace){ns.back().plist=get<stmt<temp::inst>::param_list>();}
            };
            erase();
        };
        template <> type<temp::inst> get<type<temp::inst>>(){type<temp::inst> r;
                nsacc<temp::inst> ns;
                for()
        };
        template <lex::ty l>
        expr<temp::meta> getExprMeta(){expr<temp::meta> ex;
            itPtr.push_back(itPtr.back());
            for(nextTOK();lexitback().t!=l;nextTOK()){

            };
            erase();
            return ex;
        };


        template <typename STMTty>
        void _getStmt();
        template <>void _getStmt<stmt<temp::meta>::block>(){open<lex::ty::lbrace>();};  
        template <>void _getStmt<stmt<meta>::StmtNS>(){
            for(++lexptrback();lexptrback().t!=lex::ty::lbrace;++lexptrback()){
                if(lexptrback().t==lex::ty::Name){cast->emplace_back<stmt<meta>::StmtNS>(it->u.name;);
                    if(!cast->pushNS(pri::get<stmt<meta>::StmtNS>(cast->stmts.back()).body)){
                        syserr.err<err::t::namespaceNotAllowedInCurrentScope>(*this);};continue;}
                if(!OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback().t)){syserr.err<err::t::unexpectedToken>(*this);}
            };
            open<lex::ty::lbrace>();
        };
        template <>void _getStmt<typename stmt<meta>::StmtExpr>(){};
        template <>void _getStmt<stmt<meta>::StmtAssign>(){};
        template <>void _getStmt<stmt<meta>::StmtWhile>(){};
        template <>void _getStmt<stmt<meta>::StmtFor>(){};
        template <>void _getStmt<stmt<meta>::StmtForRange>(){};
        template <>void _getStmt<stmt<meta>::StmtDo>(){};
        template <>void _getStmt<stmt<meta>::StmtCase>(){};
        template <>void _getStmt<stmt<meta>::StmtSwitch>(){};
        template <>void _getStmt<stmt<meta>::StmtDefault(){}
        template <>void _getStmt<stmt<meta>::StmtIf>(){cast->pushStmt(stmt<q>::StmtIf());
            itPtr.push_back(itPtr.back());
            for(nextTOK();lexitback().t==lex::ty::lbrace;nextTOK()){
                if(lexitback().t==lex::ty::Name){
                    if(kw_Constexpr::check(*this,lexptrback()->u.name)){
                        cast->pushQual(qual::ConstExpr);
                    }
                    else {syserr.err<err::t::unexpectedToken>(*this);} 
                };
            };
            erase();
            open<lex::ty::lbrace>();
        };
        template <>void _getStmt<stmt<meta>::StmtElseIf>(){};
        template <>void _getStmt<stmt<meta>::StmtElse>(){    
            for(;lexitback().t==lex::ty::lbrace;nextTOK()){
                if(lexitback().t==lex::ty::Name){
                    if(kw_If::check(*this,lexitback().u.name)){
                        getStmt<stmt<meta>::StmtElseIf>();return;
                    }
                    else {

                    }
                };  
                if(lexitback().t==lex::ty::semicolon){syserr.err<expectedOpeningBrace>(*this);}
            };        
            open<lex::ty::lbrace>();
        };
        template <>void _getStmt<stmt<meta>::StmtReturn>(){cast->pushStmt(getExprMeta<lex::ty::semicolon>());};
        template <>void _getStmt<stmt<meta>::StmtFuncDefSpec>(){}
        template <>void _getStmt<stmt<meta>::StmtFuncDef>(){
            open<lex::ty::>()
            for(;lexitback().t;nextTOK())
        };
        template <>void _getStmt<stmt<meta>::StmtFuncDecl>(){
            type<temp::meta> ty= get<type<temp::meta>>();

        };
        template <>void _getStmt<stmt<meta>::StmtVarDecl>(){bool strct=false;
            if(lexitback().t==lex::ty::Name){
                if(OneOfKw<kw_Struct,kw_Class>(lexitback().u.name)){strct=true;};
            }
            // TODO

        }

        template <>void _getStmt<stmt<meta>::StmtDefTypeSpec>(){}
        template <>void _getStmt<stmt<meta>::StmtDefType>(){
            for(nextTOK();lexitback().t==lex::ty::space;nextTOK();){};
            for(nextTOK();lexitback().t==lex::ty::Name;nextTOK();){};
        };
        template <>void _getStmt<stmt<meta>::StmtDeclType>(){// Default to VarDecl and DefType and DefTypeSpec where appropiatte;
            for(nextTOK();lexitback().t==lex::ty::space;nextTOK();){};
            for(nextTOK();lexitback().t==lex::ty::Name;nextTOK();){};
            std::string tyname=lexitback().u.name;
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK());

            for(nextTOK();lexitback().t==lex::ty::semicolon;nextTOK();){
                if(OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t)){continue;}
                
                if(lexitback().t==lex::ty::Name){

                };
            };
        };
        
        template <>void _getStmt<stmt<meta>::StmtUsing>(){};
        template <>void _getStmt<stmt<meta>::StmtTypeDef>(){
            nextTOK();
            untilDif<lex::ty::space>();
            type<temp::inst> tyn=get<type<temp::inst>>();std::string n=get<std::string>();
            cast->emplace_back<stmt<meta>::StmtTypeDef>(tyn,n);
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
        
        template <>void _getStmt<stmt<meta>::StmtLayout>(){
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
                if(!OneOfLex<lex::ty::comma,lex::ty::space,lex::ty::Name>(lexptrback()->t)){
                    syserr.err<unexpectedToken>(*this);
                };
            };
            untilKW<kw_Buffer,kw_Uniform,kw_in,kw_out,kw_Flat>();
        };
        template <typename StmtTy>
        void getStmt(){
            itPtr.push_back(lexptrback());
            _getStmt<StmtTy>();
            erase();
        };

        void getTemplate(){
            itPtr.push_back(lexptrback());
            for(nextTOK();lexitback().t;nextTOK()){
                // if(OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t)){continue;}
                if(OneOfLex<lex::ty::lbrace>(lexitback().t)){
                     plist=get<stmt<temp::meta>::param_list>();Template=true;
                    break;
                }
            };
            for(nextTOK();lexitback().t!=lex::ty::semicolon;nextTOK()){
                if(lexitback().t==lex::ty::Name){
                    if(OneOfKw<kw_Class>(lexitback().u.name)){accessPush<accSpec::Private>();
                        access= getStmt<stmt<temp::meta>::StmtTypeDecl>();break;
                    }                    
                    if(OneOfKw<kw_Struct>(lexitback().u.name)){accessPush<accSpec::Public>();
                        getStmt<stmt<temp::meta>::StmtTypeDecl>();break;
                    }
                    getStmt<stmt<temp::meta>::StmtFuncDecl>()

                }
            };
            Template=false;plist=stmt<temp::meta>::param_list();
        };

        template <typename MSTMT_TY>
        void getMacro();
        void include(std::filesystem::path pth){pos.push_back(posit());this->curFilePath.push_back(pth) ;this->f.push_back(std::ifstream(pth));};
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
                    if(OneOfLex<lex::ty::div,lex::ty::escape>(lexptrback()->t)){
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
                    if(OneOfLex<lex::ty::div,lex::ty::escape>(lexptrback()->t)){
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
        template<>void getMacro<mStmtElifdef>(){IfDf<true>();};
        template<>void getMacro<mStmtIfndef>(){IfDf<false>();};
        template<>void getMacro<mStmtElifndef>(){IfDf<false>();};

        template<>void getMacro<mStmtElse>(){
            erase();
            cast->condition= !(cast->condition);
            if(cast->condition){
                untilKW<true,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();
            }else {untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();}
        };
        template<>void getMacro<mStmtEndIf>(){erase();};


        ast* fromFile(std::filesystem::path pth){ curFilePath.push_back(pth);
            cast=new ast();
        cwd.push(pth.parent_path());
        f.open(pth);
        pos.push_back(posit());
        while(Line()){untilKW<KW_LIST>();}
        if(pth.extension()==std::filesystem::path("hstmsl")){
           wrcph(pth,cur); 
        }
        cwd.pop();
        parserStack.pop();
        return cast;
        };
        ast& fromFile(std::string pth){filePos =0; std::filesystem::path s(pth);return fromFile(s); }
        parser() = default;
        

    }
}
#endif