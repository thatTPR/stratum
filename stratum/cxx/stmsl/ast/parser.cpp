#ifndef STMSL_PARSER_CPP
#define STMSL_PARSER_CPP
#include <string>
#include <filesystem>
#include <petri/list.hpp>
#include <petri/stack.hpp>
#include <petri/queue.hpp>
#include <petri/templates.hpp>
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

    size_t argc; bool pack;
    pri::deque<std::string> args;
    bool function(){return argc>0 || pack;}
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
    bool checkName(std::string s,size_t* s){
        for(size_t i=0;i<args.size();i++){if(s==args[i]){ *s=i;return true;}}
        return false;
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
    
    
};

struct macrosl {
    template <Str s>
    struct builtinMacro : s {

    };
    using mVA_ARG = builtinMacro<"__VA_ARGS__">;
    pri::list<macro> mlist ;
    pri::stack<expr<inst>> condition;
   
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


    
    bool expand(macro& m,pri::deque<lex>* ptr,pri::deque<std::string> s={}){
        if(s.length()!=m.argc or (m.pack)){return false;};
        for(lex l : m.value){
            if(l.t==lex::ty::Name){
                size_t i ;
                if(mVA_ARG::get()==l.u.name){
                    for(size_t j=m.args.size();j<s.size();s++){ptr->emplace_back(s[j]);}
                } 
                else if(m.checkName(l.u.name,&i)){
                    ptr->emplace_back(s[i]);
                }
                else {ptr->emplace_back(l.u.name);}
                continue;
            }
            if(l.t==lex::ty::tokpaste){continue;}
        };
        return true;
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
        ast<temp::meta>* cast;     
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
                    case lex::ty::bnot : {lexEmplace<Eval>(posb(),lex::ty::bnot);break;}
                    case lex::ty::eq : {
                        switch(lexq.back().t){
                            case lex::ty::Not : {lexMod<Eval>(lex::ty::Noteq);break;}
                            case lex::ty::plus : {lexMod<Eval>(lex::ty::peq);break;}
                            case lex::ty::minus : {lexMod<Eval>(lex::ty::meq);break;}
                            case lex::ty::band : {lexMod<Eval>(lex::ty::andeq)break;}
                            case lex::ty::bor : {lexMod<Eval>(lex::ty::oreq);break;}
                            case lex::ty::mul : {lexMod<Eval>(lex::ty::muleq);break;}
                            case lex::ty::div : {lexMod<Eval>(lex::ty::diveq);break;}
                            case lex::ty::ltangle { lexMod<Eval>(lex::ty::lteq;break;)}
                            case lex::ty::gtangle { lexMod<Eval>(lex::ty::gteq;break;)}
                            case lex::ty::bxor { lexMod<Eval>(lex::ty::xoreq;break;)}
                            case lex::ty::mod {lexMod<Eval>(lex::ty::modeq);break;}
                            default : { lexEmplace<Eval>(posb(),lex::ty::eq);}
                        };
                    }
                    case les::ty::mod : {lexEmplace<Eval>(posb(),lex::ty::mod);break;};
                    case lex::ty::escape :{++posb();continue;}
                    case lex::ty::dq : {lexEmplace<Eval>(posb(),lex::ty::dq);break;}
                    case lex::ty::sq : {lexEmplace<Eval>(posb(),lex::ty::sq);break;}
                    case lex::ty::lparen :{lexEmplace<Eval>(posb(),lex::ty::lparen);break;}
                    case lex::ty::rparen :{lexEmplace<Eval>(posb(),lex::ty::rparen);break;}
                    case lex::ty::lbrace :{lexEmplace<Eval>(posb(),lex::ty::lbrace);break;}
                    case lex::ty::rbrace :{lexEmplace<Eval>(posb(),lex::ty::rbrace);break;}
                    case lex::ty::lbrack :{lexEmplace<Eval>(posb(),lex::ty::lbrack);break;}
                    case lex::ty::rbrack :{lexEmplace<Eval>(posb(),lex::ty::rbrack);break;}
                    case lex::ty::ltangle :{
                        if(lexq.back().t==lex::ty::eq){lexMod<Eval>(lex::ty::lteq);}
                        else if(lexq.back().t==lex::ty::minus){lexMod<Eval>(lex::ty::arrow);}
                        else{lexEmplace<Eval>(posb(),lex::ty::ltangle);};break;}

                    case lex::ty::gtangle :{if(lexq.back().t==lex::ty::eq){lexMod<Eval>(lex::ty::gteq);}
                                            else if(lexq.back().t==lex::ty::lteq){lexMod<Eval>(lex::ty::three);}
                                            else{lexEmplace<Eval>(posb(),lex::ty::gtangle);};break;}
                    case lex::ty::dot :{
                        if(lexq.back().t==lex::ty::dot and(line[posb()+1]==lex::ty::dot)){
                            ++posb();lexMod<Eval>(lex::ty::pack,2);}
                        else {lexEmplace<Eval>(posb(),lex::ty::dot);}
                        break;
                        }
                    case lex::ty::comma :{lexEmplace<Eval>(posb(),lex::ty::comma);break;}
                    case lex::ty::semicolon :{lexEmplace<Eval>(posb(),lex::ty::semicolon);continue;}
                    case lex::ty::colon :{
                        if(lexq.back().t==lex::ty::colon){lexMod<Eval>(lex::ty::dcolon);}
                        else {lexEmplace<Eval>(posb(),lex::ty::colon);continue;}
                    }
                    case lex::ty::space :{
                        if(!(lexq.back().t == lex::ty::space or (lexq.back().t == lex::ty::nl))){
                            lexEmplace<Eval>(posb(),lex::ty::space);};
                            continue;}
                    case lex::ty::nl :{if(lexq.back().t == lex::ty::nl){lexEmplace<Eval>(posb(),lex::ty::nl);};break;;}
                    case lex::ty::plus : {if(line[posb()+1]==lex::ty::plus){lexEmplace<Eval>(posb(),lex::ty::pp);}else{lexEmplace<Eval>(posb(),lex::ty::plus);};break;;}
                    case lex::ty::minus : {{if(line[posb()+1]==lex::ty::minus){lexEmplace<Eval>(posb(),lex::ty::mm);}else{lexEmplace<Eval>(posb(),lex::ty::minus);};};break;;}
                    case lex::ty::band : {if(line[posb()+1]==lex::ty::band){lexEmplace<Eval>(posb(),lex::ty::oand);}else{lexEmplace<Eval>(posb(),lex::ty::band);};break;;}
                    case lex::ty::bor :{if(line[posb()+1]==lex::ty::bor){lexEmplace<Eval>(posb(),lex::ty::oor);}else{lexEmplace<Eval>(posb(),lex::ty::bor);};break;;}
                    case lex::ty::bxor : {lexEmplace<Eval>(posb(),lex::ty::bxor);break;}
                    case lex::ty::mul : {if(lexq.back().t==lex::ty::arrow){lexMod<Eval>(lex::ty::arrowptr);break;}
                                        else if(lexq.back().t==lex::ty::dot){lexMod<Eval>(lex::ty::dotptr);break;}
                                        else if(lexq.back().t==lex::ty::dcolon){lexMod<Eval>(lex::ty::dcolptr);break;}
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
        bool checkName(){
            if(lexitback().t==lex::ty::Name){
                macro& m;
                if(macros.get(lexitback().u.name,&m)){
                    itPtr.push_back(lexptrback());
                    pri::deque<lex> q;
                    if(m.function()){
                        nextTOK();
                        if(lexitback().t!=lex::ty::lparen){--lexptrback();syserr.err<err::t::expectedToken,lex::ty::lparen>(*this);}
                        else {
                            pri::deque<std::string> args;bool arg=true;
                            for(nextTOK();lexitback().t!=lex::ty::rparen;nextTOK()){
                                if(OneOfLex<lex::ty::space>(lexitback().t)){continue;}
                                if(OneOfLex<lex::ty::comma>(lexitback().t)){arg=true;;}
                                if(checkName()){
                                    for(;lexitback().t==lex::ty::space;nextTOK()){}
                                    if(lexitback().t==lex::ty::Name){
                                        if(!arg){syserr.err<err::t::macro>(*this);}
                                        else {args.push_back(lexitback().u.name);arg=false;}
                                    }
                                };
                            }
                            macros.expand(m,&q,args);
                        }
                    }
                    else {macros.expand(m,&q);}
                    erase();
                    lexq.concat(q);
                    nextTOK();
                };
                return true;
            }
            return false;
        };
        void nextTOK(){
            pri::deque<lex>::iter it =lexptrback();
            ++it;
            if(!it){while(!it){next<true>();}}
            lexptrback()=it;
            if(it->t==lex::ty::Name){checkName();}
        };
            
        template <lex::ty T,lex::ty... Ts>
        bool OneOfLex(lex& l){
            if(OneOfLex<T>(l)){return true;}
            return OneOfLex<Ts...>(l);
        };
        template <lex::ty T>
        bool OneOfLex(lex& l){
            return (l.t==T);
        };

        bool OneOfOps(lex& l){
            return OneOfLex<lex::ty::>( l);
        };
        template <typename Kw,typename... Kws>
        bool OneOfKw(std::string str){
            if(KW::check(str)){return true;}
            else {return OneOfKw<Kws...>(str);}
        };
        template <typename Kw>
        bool OneOfKw(std::string str){
            if(KW::check(str)){return true;}
            else {return false;}
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
       
        
        template <lex::ty to,lex::ty... tok>
        void until(){
            for(;lexptrback()->t!=to ;nextTOK()){
                if(!OneOfLex<tok...>(lexitback().t)){throw UnexpectedToken(lexitback());}
            };
        };
        template <lex::ty t,lex::ty... ts>
        void untilDif(){while(OneOfLex<t,ts...>(lexptrback()->t)){nextTOK();}};
        template <lex::ty... ts>
        void untilOneOf(){while(!OneOfLex<t,ts>(lexitback().t)){nextTOK();}}
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
        
       
        
        pri::stack<accSpec> curAcc;
        template <accSpec acc>void access(){curAcc.back()=acc;};
        template <accSpec acc>void accessPush(){curAcc.push(acc);};
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

        

        template <typename KW,typename... KWs>
        bool kwFound(){
            // if constexpr (KW::kt = kwty::swizzlePrim){KW k ;if(k.check(*this,lexitback().u.name)){k.proc(*this);return true;}}
            else {if(KW::check(lexitback().u.name)){KW::proc(*this);return true;}}
            return kwFound<KWs...>();
        } ;
        template <typename KW>
        bool kwFound(){
            // if constexpr (KW::kt = kwty::swizzlePrim){KW k ;if(k.check(*this,lexitback().u.name)){k.proc(*this);return true;}}
            else {if(KW::check(lexitback().u.name)){KW::proc(*this);return true;}}
            return false;
        } ;

        template <bool Eval,typename KW,typename... KWs>
        void untilKW(){for(;!kwFound<KW,KWs...>();nextTOK<Eval>()){}
            for(;lexptrback()->t!=lex::ty::Name;nextTOK<Eval>()){};
        };
        
        
        template <bool Eval,typename KW,typename... KWs>
        void _untilKW(){for(;!_kwFound<KW,KWs...>();next<Eval>){
            for(;lexptrback()->t!=lex::ty::Name;next<Eval>()){};};};
        
        static const size_t  =context_join<KW,KWs...>::s;
        template<lex::ty t,lex::ty... acc>
        bool Until(){
            for(;OneOfLex<acc...>(lexitback().t) and (lexitback().t!=t);nextTOK()){}
            if(lexitback().t!=t){syserr.err(*this,ErrorNoToken<t>());return false;}
            return true;
        };

        // Handling Structs
        template <temp q,template<temp> typename T,typename... Args> T<q>& get();
        
        template<> std::string get<std::string>(){
            untilDif<lex::ty::space,lex::ty::nl>();
            if(lexptrback().t==lex::ty::name){
                return lexptrback().u.name;
            }
            else {syserr.err<err::t::unexpectedToken>(*this);return std::string();}
        };
        template <temp q> value<temp::meta>::memberAcc<q> get<value<temp::meta>::memberAcc>(){
            value<temp::meta>::memberAcc<q> res;
            for(;!OneOfLex<lex::ty::comma,lex::ty::eq,lex::ty::gtangle>(lexitback().t);nextTOK()){
                if(lex::ty::Name==lexitback().t){res.push_back(value<q>::accMember(lexitback().u.name));}
                if(Until<lex::ty::ltangle,lex::ty::space,lex::ty::nl>()){res.back().plist=get<q,param_list>();}
                else {if(lex::ty::dcolon==lexitback().t){continue;}}
            };
        };        
        template <temp q> type<q>* handleDeclType(){
            type<q> res;
            nextTOK();
            if(!Until<lex::ty::lparen,lex::ty::space>()){throw TypeError()};nextTOK();}
            if(!Until<lex::ty::Name,lex::ty::space>()){throw TypeError()};nextTOK();}
            resty<temp::meta> res;result r;param_list<q> plist;
            res=cast->findName(lexitback().u.name,&r);if(r==result::rVar){return pri::get<stmt<temp::meta>::StmtVarDecl>(res).tp;}
            if(!Until<lex::ty::dcolon,lex::ty::space,lex::ty::nl>()){throw TypeError()};nextTOK();}
            for(nextTOK();lexitback().t!=lex::ty::rparen;nextTOK()){
                if(!OneOfLex<lex::ty::dcolon>(lexitback().t)){continue;}
                
                if(OneOfLex<lex::ty::ltangle>(lexitback().t)){plist=get<temp::inst,param_list>();pri::get<type<q>>(res).get(plist);}
                
                if(lex::ty::Name==lexitback().t){if(!cast->find(lexitback().u.name,&res,&r)){syserr.err(*this,NameNotFound());}}
                if(OneOf<lex::)

            }
        };

        template <temp q> value<q>& get<q,value,value<q>::ty::typeValue>(){
            res.t=value<temp::inst>::ty::typeValue;
            resty<temp::meta> rs;result r;
            if(kw_Decltype::check(lexitback().u.name)){ typ = handleDeclType<temp::inst>();}
            rs=cast->findName(lexitback().u.name,&r);
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::Name,lex::ty::dcolon,lex::ty::ltangle>(lexitback().t);nextTOK()){
                if(OneOfLex<lex::ty::space>(lexitback().t)){continue;}
                if(OneOfLex<lex::ty::ltangle>(lexitback().t)){if(r==ast<q>::result::rType){
                    pri::get<type<temp::meta>>(rs)=pri::get<type<temp::meta>>(rs).get(get<temp::inst,param_list>());};}
                if(OneOfLex<lex::ty::Name>(lexitback().u.name)){      
                    if(!cast->find(lexitback.u.name,&rs,&r)){syserr.err(*this,NameNotFound());}}
            };
            switch(r){
                case ast<q>::result::rType : {
                    if constexpr (q==temp::meta){return pri::get<stmt<q>::StmtUsing>(rs).expr;}
                    else {return pri::get<stmt<q>::StmtUsing>(rs).expr;}
                }
                default :{throw TypeNotFound();};
            }
        };
        template <temp q> value<q>& get<q,value,value<q>::ty::ptrmember>(){
            value<q> res;res.t=value<temp::inst>::ty::ptrmember;
            resty<temp::meta> rs;result r;
             if(kw_Decltype::check(lexitback().u.name)){ typ = handleDeclType<temp::inst>();}
            rs=cast->findName(lexitback().u.name,&r);
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::Name,lex::ty::dcolon,lex::ty::ltangle,lex::ty::eq>(lexitback().t);nextTOK()){
                if(OneOfLex<lex::ty::space>(lexitback().t)){continue;}
                if(OneOfLex<lex::ty::ltangle>(lexitback().t)){if(r==ast<q>::result::rType){
                    pri::get<type<temp::meta>>(rs)=pri::get<type<temp::meta>>(rs).get(get<temp::inst,param_list>());};}
                if(OneOfLex<lex::ty::Name>(lexitback().u.name)){      
                    if(!cast->find(lexitback.u.name,&rs,&r)){syserr.err(*this,NameNotFound());}}
            };
            switch(r){
                case ast<q>::result::rVar : {
                    if constexpr (q==temp::meta){return pri::get<stmt<q>::StmtVarDecl>(rs).tp;}
                    else {return value(pri::get<stmt<q>::StmtVarDecl>(rs).tp);}
                }
                default throw NameNotFound();
            }
        };
        expr<temp::inst> getCexpr(){

        };
         template <lex::ty... l> 
        expr<temp::meta> getExprName();
         template <lex::ty... l> 
        expr<temp::meta> getExpr();


        template <> param<temp::inst>& get<temp::inst,param>(){
            if(!Until<lex::ty::Name,lex::ty::space,lex::ty::ltangle,lex::ty::nl>()){};
            expr<temp::meta> values=getExpr<lex::ty::comma,lex::ty::rangle>();
            value<temp::inst> v=values.val();
            switch(v.t){
                case value<temp::inst>::ty::ptrmember:
                case value<temp::inst>::ty::typeValue:
                case value<temp::inst>::ty::literal:
                case value<temp::inst>::ty::varRef:

            }
            return param<temp::inst>();            
        };
        template <temp q> param<q>& get<q,param>(){
            param<q> p;ast<q>::resty res;ast<q>::result r=ast<q>::result::rErr;
            if(!Until<lex::ty::Name,lex::ty::space,lex::ty::ltangle,lex::ty::nl>()){}
            for(;!OneOfLex<lex::ty::comma,lex::ty::rangle,lex::ty::semicolon>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::band){pri::get<value<q>>(p.varg)= get<q,value,value<q>::ty::ptrmember>();
                    for(nextTOK();lexitback().t!=lex::ty::Name;nextTOK()){};
                    p.name=lexitback().u.name();return p.name;
                };
                if(lexitback().t==lex::ty::Name){
                    if(kw_Class::check(lexitback().u.name)){p.t=param::ty::Type;continue;}
                    else if(kw_Typename::check(lexitback().u.name)){p.t=param::ty::Typename;continue;}
                    else if(kw_Template::check(lexitback().u.name)){p.t=param::ty::Template;
                    if constexpr(q==temp::meta){

                    }
                    else {

                    }
                    continue;
                    }
                    p.t=param<q>::ty::Type;
                    p.arg=&get<q,type>();
                }             
                if(lexitback().t==lex::ty::eq){nextTOK();p.value_def=true;p.valdef=get<temp::inst,param>();}
            }
            return p;
        };
        
        

  
        template <typename... Ts>
        type<temp::inst> getType(Ts... args){return type<temp::inst>(args...);};
        
        template <temp q> param_list<q> get<q,param_list>(){param_list plist;
            itPtr.push_back(itPtr.back());
            if(nextTOK();!OneOfLex<lex::ty::rangle>(lexitback().t);nextTOK()){
                if(OneOfLex<lex::ty::space,lex::ty::comma>(lexitback().t)){continue;}
                    plist.push_back(get<param<q>>());
            }
            return plist;};
     
        template <temp q> type<q> get<q,type>(){type<q> r;stmt<temp::inst>::param_list plist;  
            result r=result::rErr;
            resty<temp::meta> res ;
            itPtr.push_back(lexptrback());
            try {res=cast->findName(lexitback().u.name,&r);}
            catch (const NameNotFound& nsexc){syserr.err(*this,nsexc);}
            if(r!=result::rErr){
                for(nextTOK();OneOfLex<lex::ty::name,lex::ty::dcolon>(lexitback().t) and (r==result::rNs);nextTOK() ){
                    if(OneOfLex<lex::ty::dcolon>(lexitback().t)){;continue;}
                    if(lexitback().t==lex::ty::Name){
                        try {    res= cast->findNameFromNs(&pri::get<stmt<temp::meta>::StmtNS>(res),lexitback().u.name,&r);}
                        catch (const NameNotFound& nsexc){syserr.err(*this,nsexc);continue;}
                    }
                    else {syserr.err<err::t::unexpectedToken(*this);}
                }
                for(nextTOK();OneOfLex<lex::ty::name,lex::ty::dcolon>(lexitback().t);nextTOK()){
                    if(OneOfLex<lex::ty::dcolon>(lexitback().t)){continue;}
                    if(lexitback().t==lex::ty::Name){
                        try {res=cast->findNameFromTp(pri::get<type<temp::meta>>(res),lexitback().u.name,&r);}
                        catch (const NameNotFound& exc) {syserr<err::t::typeNotFound>(*this);}
                        nextTOK();
                        if(lexitback().t==lex::ty::ltangle){
                            stmt<temp::inst>::param_list plist=get<stmt<temp::inst>::param_list>();
                            res=cast->getTp(r,plist);
                            break;
                        };
                    }
                }
                for(nextTOK();OneOfLex<lex::ty::name,lex::ty::dcolon>(lexitback().t);nextTOK()){
                    if(OneOfLex<lex::ty::dcolon>(lexitback().t)){continue;}
                    if(lexitback().t==lex::ty::Name){
                        try {r=cast->findNameFromTp<temp::meta>(r,lexitback().u.name);}
                        catch(const NameNotFound& exc){syserr<err::t::typeNotFound>(*this);}
                        nextTOK();
                        if(lexitback().t==lex::ty::ltangle){
                            stmt<temp::inst>::param_list plist=get<stmt<temp::inst>::param_list>();
                            res=cast->getTp(res,plist);
                            break;
                        };
                    }
                }
            }
            else {syserr<err::t::typeNotFound>(*this);}
            erase();
        };
       
        // template <typename T ,typename QKW, typename... QKWs>
        // bool Qualify(T& ref){
        //     if(KW::check(lexitback().u.name)){ref->*(KW::ptr<T>::val)=true;return true;}
        //     else {return Qualify<T,QKWs...>(ref);}
        // };
        // template <typename T ,typename QKW>
        // bool Qualify(T& ref){
        //     if(KW::check(lexitback().u.name)){ref->*(KW::ptr<T>::val)=true;}
        //     else {return false;}
        // };
       
        template <lex::ty... l >
        stmt<temp::meta>::StmtVarDecl getVarDecl(){
            stmt<temp::meta>::StmtVarDecl vdecl;
            for(;OneOfLex<lex::ty::space,lex::ty::nl,lex::ty::Name>(lexitback().t)){
                if(kw_in::check(lexitback().u.name)){vdecl.in=true;};
                else if(kw_out::check(lexitback().u.name)){vdecl.out=true;};
                else if(kw_const::check(lexitback().u.name)){vdecl.Const=true;};
                else {break;}
            };
            vdecl.tp = get<temp::meta,value>();
            for(nextTOK();OneOfLex<l...>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::Name){vdecl.name=lexitback().u.name;break;}
            };
            for(nextTOK();OneOfLex<l...>(lexitback().t);nextTOK()){};
            return vdecl;
        };
             
        pri::deque<expr<temp::meta>> getArgList(){  pri::deque<expr<temp::meta>> args;
                for(;!OneOfLex<lex::ty::rparen>(lexitback().t);nextTOK()){
                    args.push_back(getExprMeta<lex::ty::comma,lex::ty::rparen>());
                    if(OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback()->t)){continue;}
                };
                return args;
        };
        #define LEX_ACC lex::ty::arrow,lex::ty::dot,lex::ty::dotptr,lex::ty::arrowptr,lex::ty::dcolon,lex::ty::dcolptr
        template <lex::ty... l> 
        expr<temp::meta> getExprName(){expr<temp::meta> ret;
            if(kw_New::check(lexitback().u.name)){ret.push<op::ty::opNew,expr::node::opty::prefixUnary>();}
            if(kw_Delete::check(lexitback().u.name)){ret.push<op::ty::opNew,expr::node::opty::prefixUnary>();}
                    
            expr<temp::meta> res;r=result::rErr;lex::ty lastAcc=lex::ty::none;
            for(nextTOK();!OneOfLex<l...>(lexitback().t) ;nextTOK()){
                if(OneOfLex<LEX_ACC>(lexitback().t)){lastAcc=lexitback().t;nextTOK();continue;}
                if(OneOfLex<lex::ty::Name>(lexitback().t)){
                    if(kw_This::check(lexitback().u.name)){ret.emplaceExpr(value<temp::meta>(cast->strcts.back(),value<temp::inst>::ty::thisRef));}
                    else if(!cast->find(lexitback().u.name,&n,&r)){
                        for(;!OneOfLex<l...>(lexptrback()->t);nextTOK()){while(OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback()->t)){continue;}
                        if(it->t==lex::ty::lparen){nextTOK();auto args=getArgList();
                            if(r==result::rMethod or (r==result::rFunc)){
                                value<temp::meta> vl = get<temp::meta,value>(pri::get<stmt<temp::meta>::StmtFuncDecl*>(n),args);
                                ret.push(vl);return ret;
                            };
                        }
                
                        }
                    }
                }
            return ret;
        };

        // template <lex::ty... l>
        // value<temp::meta>::funcCall getExprCall();
        #ifdef CHAR_LITERALS
        value<temp::inst> getCharLiteral();
        value<temp::inst> getStrLiteral();
        #endif

        template <lex::ty... l>
        expr<temp::meta> getExprMeta(){
            expr<temp::meta> res;
            auto prevName = [&res](){return res.tree.lhs!=nullptr};
            itPtr.push_back(lexptrback());
            auto unary = <op::ty opT>[&](){if(prevName()){res.push<opT,expr::node::opty::postfixUnary>()}else{res.push<opT,expr::node::opty::prefixUnary>()}}
            stmt<temp::meta>::StmtFuncDecl fdecl;type<temp::inst> resty;
            for(;!OneOfLex<l...>(lexptrback()->t);nextTOK()){
                switch(lexitback().t){
                    case lex::ty::Name :{resty = getExprName<LEXOPERS,l...>();}
                    case lex::ty::Numflt:{res.push(lexitback().u.flt);};
                    case lex::ty::Numuint:{res.push(lexitback().u.num);};
                    case lex::ty::bnot : {res.push<op::ty::opbnot>();break;};
                    case lex::ty::band:{res.push<op::ty::oband>();break;}
                    case lex::ty::dot:{res.push<op::ty::opdot,expr<temp::meta>::node::opty::binary>();;continue;}
                    case lex::ty::arrow:{res.push<op::ty::arrow,expr<temp::meta>::node::opty::binary>();continue;}
                    #ifdef CHAR_LITERALS
                    case lex::ty::sq :{res.pushLiteral(getCharLiteral());}
                    case lex::ty::dq :{res.pushLiteral(getStrLiteral());}
                    #endif
                    case lex::ty::lparen:{res.Start();break;}
                    case lex::ty::rparen:{res.Close();break;}
                    case lex::ty::lbrace:{ res.push(getValueInitializer());break;}
                    case lex::ty::lbrack:{res.push<op::ty::oindex>(); res.push(getExprMeta<lex::ty::rbrack>());break;;}
                    case lex::ty::Not:{res.push<op::ty::opNot,expr::node::opty::prefixUnary>();break;}
                    case lex::ty::plus:{res.push<op::ty::oplus>();break;}
                    case lex::ty::minus:{res.push<op::ty::ominus>();break;}
                    case lex::ty::bor:{res.push<op::ty::obor>();break;}
                    case lex::ty::bxor:{res.push<op::ty::obxor>();break;}
                    case lex::ty::mul:{res.push<op::ty::omul>();break;}
                    case lex::ty::div:{res.push<op::ty::odiv>();break;}
                    case lex::ty::ltangle:{if(!atTemplateType){res.push<op::ty::olt>()};break;}
                    case lex::ty::lteq:{res.push<op::ty::ogt>();break;}
                    case lex::ty::gtangle:{res.push<op::ty::ogt>();break;}
                    case lex::ty::gteq:{res.push<op::ty::ogteq>();break;}
                    case lex::ty::comma:{syserr.err.err<err::t::unexpectedToken>(*this);break;}
                    case lex::ty::semicolon:{return res;}
                    case lex::ty::colon:{res.push<op::ty::opcolon>();break;}
                    case lex::ty::space:{break;}
                    case lex::ty::cond:{res.push<op::ty::cond,expr::node::opty::ternary>();atCond=true;break;}
                    case lex::ty::eq:{res.push<op::ty::eq>();break;}
                    case lex::ty::peq:{res.push<op::ty::opeq>();break;}
                    case lex::ty::meq:{res.push<op::ty::omeq>();break;}
                    case lex::ty::xoreq:{res.push<op::ty::opxoreq>();break;}
                    case lex::ty::andeq:{res.push<op::ty::opandeq>();break;}
                    case lex::ty::oreq:{res.push<op::ty::oporeq>();break;}
                    case lex::ty::Noteq:{res.push<op::ty::opNoteq>();break;}
                    case lex::ty::muleq:{res.push<op::ty::opmuleq>();break;}
                    case lex::ty::diveq:{res.push<op::ty::opdiveq>();break;}
                    case lex::ty::pack:{unary<op::ty::oppack>();break;}
                    case lex::ty::oand:{res.push<op::ty::opand>();break;}
                    case lex::ty::oor:{res.push<op::ty::opor>();break;}
                    case lex::ty::three:{res.push<op::ty::opthree>();break;}
                    case lex::ty::pp:{unary<op::ty::opp>();break;}
                    case lex::ty::mm:{unary<op::ty::omm>();break;}
                }
            }
            return res;
        };
                template <> arg_list<temp::meta> get<stmt<temp::meta>::arg_list>();

        template <typename STMTty>
        void getStmt();
        template <typename STMTty>
        void _getStmt();
        void Stmt();
        template <>void _getStmt<stmt<temp::meta>::block>(){
            for(;lexitback().t!=lex::ty::rbrace;nextTOK()){Stmt();};
            cast->popbl();
        };  
        void getBody(){
            lexq.push_back(lexitback());
            _getStmt<stmt<temp::meta>::block>();
            erase()
        };
        template <>void _getStmt<stmt<meta>::StmtNS>(){
            for(++lexptrback();lexptrback().t!=lex::ty::lbrace;++lexptrback()){
                if(lexptrback().t==lex::ty::Name){cast->emplace_back<stmt<meta>::StmtNS>(it->u.name;);
                    if(!cast->pushNS(pri::get<stmt<meta>::StmtNS>(cast->curBlock()->back()))){
                        syserr.err<err::t::namespaceNotAllowedInCurrentScope>(*this);};continue;}
                if(!OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback().t)){syserr.err<err::t::unexpectedToken>(*this);}
            };
            open<lex::ty::lbrace>();
        };
        template <>void _getStmt<stmt<meta>::StmtWhile>(){};
        template <>void _getStmt<stmt<meta>::StmtFor>(){};
        template <>void _getStmt<stmt<meta>::StmtForRange>(){};
        template <>void _getStmt<stmt<meta>::StmtDo>(){};
        template <>void _getStmt<stmt<meta>::StmtCase>(){};
        template <>void _getStmt<stmt<meta>::StmtSwitch>(){};
        template <>void _getStmt<stmt<meta>::StmtDefault>(){}
        template <>void _getStmt<stmt<meta>::StmtTry>(){
            stmt<meta>::StmtTry res; 
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK()){}
            if(!OneOfLex<lex::ty::lbrace>(lexitback().t)){syserr.err<err::t::unexpectedToken>(*this);}
            cast->pushbl(res.body);
            getBody();
            cast->pushStmt(res);
        };
        template <>void _getStmt<stmt<meta>::StmtCatch>(){
            stmt<meta>::StmtCatch res;
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK()){}
            if(!OneOfLex<lex::ty::lparen>(lexitback().t)){syserr.err<err::t::unexpectedToken>(*this);}
            res.var=getVarDecl<lex::ty::rparen>();
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK()){}
            if(!OneOfLex<lex::ty::lbrace>(lexitback().t)){syserr.err<err::t::unexpectedToken>(*this);}
            cast->pushbl(&res.body);getBody();
            cast->tries.top()->catches.push_back(res);
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>();nextTOK()){};
            if(OneOfLex<lex::ty::semicolon>()){cast->tries.pop();}
        };
        template <>void _getStmt<stmt<meta>::StmtThrow>(){
            nextTOK();
            expr<temp::meta> vl=getExpr<lex::ty::semicolon>();
            cast->pushStmt<stmt<meta>::StmtThrow>(vl);
        };
        
        template <>void _getStmt<stmt<meta>::StmtIf>(){bool ConstExpr=false;
            for(nextTOK();lexitback().t!=lex::ty::lparen;nextTOK()){
                if(checkName()){
                    if(OneOfKw<kw_ConstExpr>(lexitback().u.name)){ConstExpr=true;}
                    else {syserr.err<err::t::unexpectedToken>(*this);}
                }
            };
            cast->pushStmt<stmt<meta>::StmtIf>(getExprMeta<lex::ty::rparen>())
            if(ConstExpr){cast->pushQual<qual::qConstExpr>;}
            for(nextTOK();lexitback().t!=lex::ty::lbrace;nextTOK()){};
            _getStmt<stmt<temp::meta>::block>();
        };
        template <>void _getStmt<stmt<meta>::StmtElseIf>(){bool ConstExpr=false;
            for(nextTOK();lexitback().t!=lex::ty::lparen;nextTOK()){
                if(checkName()){
                    if(OneOfKw<kw_ConstExpr>(lexitback().u.name)){ConstExpr=true;}
                    else {syserr.err<err::t::unexpectedToken>(*this);}
                }
            };
            cast->pushStmt(stmt<q>::StmtIf(getExprMeta<lex::ty::rparen>())
            if(ConstExpr){cast->pushQual<qual::qConstExpr>;}
            for(nextTOK();lexitback().t!=lex::ty::lbrace;nextTOK()){};
            open<lex::ty::lbrace>();
        };
        template <>void _getStmt<stmt<meta>::StmtElse>(){    
            for(;lexitback().t==lex::ty::lbrace;nextTOK()){
                if(checkName()){
                    if(kw_If::check(lexitback().u.name)){
                        getStmt<stmt<meta>::StmtElseIf>();return;
                    }
                    else {

                    }
                };  
                if(lexitback().t==lex::ty::semicolon){syserr.err<expectedOpeningBrace>(*this);}
            };        
            open<lex::ty::lbrace>();
        };
        stmt<meta>::StmtFuncDef* curfunc;
        template <>void _getStmt<stmt<meta>::StmtReturn>(){cast->pushStmt<stmt<meta>::StmtReturn>(getExprMeta<lex::ty::semicolon>());};
        template <>void _getStmt<stmt<meta>::StmtFuncDef>(){
            stmt<meta>::StmtFuncDef& res=*curfunc;
            for(;lexitback().t;nextTOK())
        };
        template <>void _getStmt<stmt<meta>::StmtFuncDecl>(){
            type<temp::meta> ty= get<type<temp::meta>>();

        };

        template <>void _getStmt<stmt<meta>::StmtDefType>(){
            
        };
        // Starts after type is specified
        template <>void _getStmt<stmt<meta>::StmtVarDecl>(){// Default To FuncDecl, where appropiate;
            bool bStrct; bool bUnion;
            if(OneOfKw<kw_Struct,kw_Class,kw_Union>(lexitback().u.name)){};

            for(;OneOfLex<lex::ty::semicolon>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::lparen){_getStmt<stmt<meta::}
            };
        };
        template <>void _getStmt<stmt<meta>::StmtDeclType>(){
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK();){};
            if(lexitback().t!=lex::ty::name){_getStmt<stmt<meta>::StmtExpr>();return ;}
            
            if(kw_Template::check(lexitback().u.name)){
                StmtDeclType
            }
        };
        
        
        template <>void _getStmt<stmt<meta>::StmtUsing>(){
            stmt<meta>::StmtUsing& res=pri::get<stmt<meta>::StmtUsing>(cast->last<stmt<meta>::StmtUsing>().var);
            nextTOK();until<lex::ty::Name,lex::ty::space>();
            if(kw_Namespace::check(lexitback().u.name)){res.Namespace=true;nextTOK();until<lex::ty::Name,lex::ty::space,lex::ty::nl>();
                res.name=lexitback().u.name;nextTOK();until<lex::ty::semicolon,lex::ty::space,lex::ty::nl>();return res;}
            res.name= lexitback().u.name;
            res.prms=*curtemp.back();curtemp.back()=&res.prms;
            until<lex::ty::eq,lex::ty::space>();nextTOK();
            until<lex::ty::Name,lex::ty::space>();
            res.expr=get<temp::inst,value>();
            until<lex::ty::semicolon,lex::ty::space>();
        };
        template <>void _getStmt<stmt<meta>::StmtTypeDef>(){
            cast->pushStmt<stmt<meta>::StmtTypeDef>(stmt<meta>::StmtUsing());
            stmt<meta>::StmtTypeDef& res=pri::get<stmt<meta>::TypeDef>(cast->curBlock().back().var);
            nextTOK();
            untilDif<lex::ty::space>();
            res.expr=get<temp::inst,value>();until<lex::ty::Name,lex::ty::space,lex::ty::nl>();
            res.name=lexitback().u.name;
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
        void getLytVar(stmt<meta>::StmtLayout& lyt ){
            for(;OneOfKw<kw_in,kw_out,kw_inout,>(lexitback().t);nextTOK()){
                if(checkName()){
                    if(kw_Uniform::check(lexitback().u.name)){lyt.uniform=true;}
                    if(kw_Flat::check(lexitback().u.name)){lyt.flat=true;}
                }
            };
            if(kw_in::check(lexitback().u.name)){lyt.in=true;}
            if(kw_inout::check(lexitback().u.name)){lyt.in=true;lyt.out=true;}
            if(kw_out::check(lexitback().u.name)){lyt.out=true;}
            lyt.vart=stmt<temp::meta>::StmtLayout::tyT::var;
            for(nextTOK();!OneOfLex<lex::ty::semicolon,lex::ty::lbrace>(lexitback().t);nextTOK()){
                if(lex::ty::Name==lexitback().t){
                    if(kw_Buffer::check(lexitback().u.name)){lyt.vart=stmt<temp::meta>::StmtLayout::tyT::buffer;continue;};
                    if(kw_Uniform::check(lexitback().u.name)){lyt.vart=stmt<temp::meta>::StmtLayout::tyT::uniform;continue;};
                    if(lyt.vart==stmt<temp::meta>::StmtLayout::tyT::var){

                        cast->ptr.vd=&pri::get<stmt<temp::meta>::StmtVarDecl>(lyt.data);getStmt<stmt<temp::meta>::StmtVarDecl>() ;
                        lyt.name=pri::get<stmt<temp::meta>::StmtVarDecl>(lyt.data).name;
                        return;
                    }
                    else {lyt.name=name;}
                
                }
                else if(!OneOfLex<lex::ty::space,lex::ty::nl>()){syserr.err<err::t::unexpectedToken>(*this);}
            }
            if(lexitback().t==lex::ty::lbrace){cast->ptr.dt=pri::get<stmt<temp::meta>::StmtDefType>(lyt.data);getStmt<stmt<temp::meta>::StmtTypeDef>();}
        };
        template <>void _getStmt<stmt<meta>::StmtLayout>(){
            if(cast->curBl().empty())
            cast->pushStmt<stmt<temp::meta>::StmtLayout>();stmt<temp::meta>::StmtLayout& lyt=cast->layouts.back();
            nextTOK();
            if(lexitback().t!=lex::ty::lparen){syserr.err<unexpectedToken,stmt<meta>::StmtLayout>(*this);}
            for(;lexptrback()->t==lex::ty::rparen;++lexptrback()){
                lexres unexp=untilExp<lex::ty::eq,lex::ty::space>();
                if( checkName()) {
                    if(getStd<std430,std140>(lyt)){continue;}
                    if(getLytAt<kw_Location,kw_Binding>(lyt)){continue;};
                };
                if(!OneOfLex<lex::ty::comma,lex::ty::space,lex::ty::Name>(lexptrback()->t)){
                    syserr.err<unexpectedToken>(*this);
                };
            };
            getLytVar();
        };
        template <>void _getStmt<stmt<temp::meta>::StmtExpr>(){
            stmt<meta>::StmtExpr res;
            if(lexitback().t==name){ // Unsure yet if is Expr may default to StmtVarDecl which can default to a number of StmtTs;
                itPtr.push_back(lexitback());lex::ty c=untilOneOf<lex::ty::colon,lex::ty::semicolon,lex::ty::lparen,lex::ty::lbrace>();
                if(c==lex::ty::semicolon){

                };
                itPtr.pop_back();
                switch(c){
                    case lex::ty::colon: {getStmt<stmt<temp::meta>::StmtTypeDecl>();return;}
                    case lex::ty::lbrace :{getStmt<stmt<temp::meta>::StmtTypeDecl>();return;}
                    case lex::ty::lparen :{getStmt<stmt<temp::meta>::StmtFuncDecl>();return;}
                };
            }
            for(;!OneOfLex<lex::ty::semicolon>(lexitback().t);nextTOK()){
                if(OneOfLex<lex::ty::Name>(lexitback().t)){
                    
                };
            };
            cast->pushStmt(res);
        };

        template <typename StmtTy>
        void getStmt(){
            itPtr.push_back(lexptrback());
            _getStmt<StmtTy>();
            erase();
        };
        void Enum(bool bTemp,stmt<temp::meta>::param_list& plist){stmt<temp::meta>::Enum res;res
            until<lex::ty::Name,lex::ty::space,lex::ty::nl>();
            if(kw_Struct::check(lexitback().u.name) or(kw_class::check(lexitback().u.name))){enclass=true;};
            else{res.name=lexitback().u.name;}
            until<lex::ty::lbrace,lex::ty::space,lex::ty::nl>();getStmt<Enum>() 
        }
        template <bool Strct>
        void Strct(bool bTemp,stmt<temp::meta>::param_list& plist){
            // Could Be Function
        };
        void Union(bool bTemp,stmt<temp::meta>::param_list& plist){
            try {until<lex::ty::Name,lex::ty::space,lex::ty::nl>();}
            catch (const UnexpectedToken& e){
                if(e.what().t==lex::ty::lbrace){
                    getStmt<stmt<temp::meta>::StmtUnion>();
                    try{until<lex::ty::Name,lex::space,lex::ty::nl>();}
                    catch (const UnexpectedToken& e){return;}
                    stmt<temp::meta>::StmtVarDecl res;cast->pushStmt(res);

                }
                else{syserr.err(*this,e);}
            }
        };
        void Using(bool bTemp,stmt<temp::meta>::param_list& plist){
            cast->pushStmt<stmt<meta>::StmtUsing>(stmt<meta>::StmtUsing());
            stmt<temp::meta>::StmtUsing& res=pri::get<stmt<meta>::StmtUsing>(cast->last().var);
            if(bTemp){res.prms=plist;}
            getStmt<stmt<temp::meta>::StmtUsing>();
        };
        
        bool correct( result* r,resty<temp::meta>* res){
            switch(lexitback().t){
                case lex::ty::arrow: {return isPtrCompound<temp::meta>(r,res);}
                case lex::ty::dot: {return hasMember(r<temp::meta>,res);}
                case lex::ty::dotptr: {return isCompound<temp::meta>(r,res);}
                case lex::ty::arrowptr: {return isPtrCompound<temp::meta>(r,res);}
                case lex::ty::dcolon: {return isCompound<temp::meta>(r,res);}
                case lex::ty::dcolptr: {return isCompound<temp::meta>(r,res);}
                default :  {throw UnexpectedToken();}
            }
        }
        bool handle(lex::ty& acc , result* r,resty<temp::meta>* res){
            param_list<temp::inst> plist;
            if(cast->find(lexitback().u.name,&res,&r)){};

            if(lex::ty::ltangle==lexitback().t){plist=get<temp::inst,param_list>();
                *r=result::rValue;
                switch(*r){
                case result::rType :{pri::get<value<temp::meta>>(*res)=pri::get<type<temp::meta>>(*res).get(plist);}
                case result::rMethod :{pri::get<value<temp::meta>>(*res)=pri::get<stmt<temp::meta>::StmtFuncDecl>(*res).get(plist);}
                case result::rFunc :{pri::get<value<temp::meta>>(*res)=pri::get<type<temp::meta>>(*res).get(plist);}
                default :{syserr.err(*this,ParamMismatch(plist));result::rErr;}
                }
            }
            if(OneOfLex<LEX_ACC>(lexitback().t)){
                switch(lexitback().t){
                    case 
                }
                lastAcc=lexitback().t;
            }
        };
        template <bool Strct,bool Func>
        void NameStmt(){
            auto r= result::rErr;
            resty<temp::meta> res;
            lex::ty lastAcc=lex::ty::none;
            for(;OneOfLex<lex::ty::semicolon>(lexitback().t);){
                handle(lastAcc,&r,&res);}
                else break;
            };
            if(lexitback().t==lex::ty::lparen){

            };
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
                if(checkName()){
                    if(OneOfKw<kw_Class>(lexitback().u.name)){accessPush<accSpec::Private>();
                        access= getStmt<stmt<temp::meta>::StmtDeclType>();break;
                    }                    
                    if(OneOfKw<kw_Struct>(lexitback().u.name)){accessPush<accSpec::Public>();
                        getStmt<stmt<temp::meta>::StmtDeclType>();break;
                    }
                    getStmt<stmt<temp::meta>::StmtFuncDecl>()

                }
            };
            Template=false;plist=stmt<temp::meta>::param_list();
        };

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
        template<>void _getMacro<mStmtInclude>(){
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
        template<>void _getMacro<mStmtIf>(){
            // itPtr.push(lexptrback())
            cast->condition= getExprUntil_EOL();
            // cast->tus.emplace_back(ex);
            erase();
            untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();
        };
        template<>void _getMacro<mStmtDefine>(){
            until<lex::ty::Name>();
            macros.emplace(lexptrback()->u.name,strippedUntil<lex::ty::nl>());
            erase();
        };
        template<>void _getMacro<mStmtElif>(){getMacro<mStmtIf>();};
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
        
        template<>void _getMacro<mStmtIfdef>(){IfDf<true>();};
        template<>void _getMacro<mStmtElifdef>(){IfDf<true>();};
        template<>void _getMacro<mStmtIfndef>(){IfDf<false>();};
        template<>void _getMacro<mStmtElifndef>(){IfDf<false>();};

        template<>void _getMacro<mStmtElse>(){
            erase();
            cast->condition= !(cast->condition);
            if(cast->condition){
                untilKW<true,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();
            }else {untilKW<false,kw_Else,kw_elif,kw_elifdef,kw_elifndef,kw_endif>();}
        };
        template<>void _getMacro<mStmtEndIf>(){erase();};
        template <typename T> getMacro(){_getMacro<T>();}
        template <bool Strct,bool Func>
        bool StmtPush(){
            for(;OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK()){}
            if(OneOfLex<lex::ty::Name>(lexitback().t)){
                if(kwFound<KW_LISTM>()){return true;}
                stmt<temp::meta>::param_list plist ;bool bTemp=false;
                if(kw_Template::check(lexitback().u.name)){bTemp=true;
                    if(Func){syserr.err(*this,UnexpectedToken("Template Not allowed in function body"));}
                    nextTOK();unil<lex::ty::ltangle,lex::ty::space,lex::ty::nl>();
                    plist = get<temp::meta,param_list>();until<lex::ty::Name,lex::ty::rtangle,lex::ty::space,lex::ty::nl>();
                }
                if constexpr (!Func) {
                    if(kw_Enum::check(lexitback().u.name)){Enum(bTemp,plist);return;}
                    else if(kw_Struct::check(lexitback().u.name) ){Strct<true>(bTemp,plist);return;}
                    else if(kw_class::check(lexitback().u.name)){Strct<false>(bTemp,plist);return;}
                    else if(kw_Union::check(lexitback().u.name)){Union(bTemp,plist);return;}
                    else if(kw_Using::check(lexitback().u.name)){Using(bTemp,plist);return;}
                    else if constexpr(Strct){if(kwFound<KW_ACCS>()){return;}else{NameStmt<Strct,func>();}}
                    else {NameStmt<Strct,Func>();}
                }
                else {
                    if(kwFound<LW_LISTSTMT>()){return;}
                    else {NameStmt<Strc,Func>();}
                };
            }
            else {
                if constexpr (func || !Strct){getStmt<stmt<temp::meta>::StmtExpr>();}
                else {throw UnexpectedToken();}
            }
            
        };
        void Stmt(){

            if(cast->nsblck){if(cast->fblck){StmtPush<false,true>();}else{StmtPush<false,false>();}
            else{if(cast->fblck){StmtPush<true,true>();}else{StmtPush<true,false>();}
        };
       
        ast* fromFile(std::filesystem::path pth){ curFilePath.push_back(pth);
            cast=new ast();
        cwd.push(pth.parent_path());
        f.open(pth);
        pos.push_back(posit());
        while(Line()){Stmt();}
        if(pth.extension()==std::filesystem::path("hstmsl")){wrcph(pth,cur); }
        cwd.pop();
        parserStack.pop();
        return cast;
        };
        ast& fromFile(std::string pth){filePos =0; std::filesystem::path s(pth);return *fromFile(s); }
        parser() = default;
        

}
}
#endif