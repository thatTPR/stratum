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
        void close(){if(opens.top()==openedt<t>::l){opens.pop();}else{err::e<unexpectedToken>(*this);}};
        template <>
        void close<lex::ty::rbrace>(){if(opens.top()==openedt<lex::ty::rbrace>::l){opens.pop();cast->popbl();}else{err::e<unexpectedToken>(*this);}};


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
  

               char getCharLit(){
            char res;
            ++posb();
           if(line[posb()]=='\\'){
if(line[posb()+1]=='\''){res+='\''}//	single quote	byte 0x27 in ASCII encoding
else if(line[posb()+1]=='\"'){res+='\"'}//	double quote	byte 0x22 in ASCII encoding
else if(line[posb()+1]=='?'){res+='\?'}//	question mark	byte 0x3f in ASCII encoding
else if(line[posb()+1]=='\\'){res+='\\'}//	backslash	byte 0x5c in ASCII encoding
else if(line[posb()+1]=='a'){res+='\a';}//	audible bell	byte 0x07 in ASCII encoding
else if(line[posb()+1]=='b'){res+='\b';}//	backspace	byte 0x08 in ASCII encoding
else if(line[posb()+1]=='f'){res+='\f';}//	form feed - new page	byte 0x0c in ASCII encoding
else if(line[posb()+1]=='n'){res+='\n';}//	line feed - new line	byte 0x0a in ASCII encoding
else if(line[posb()+1]=='r'){res+='\r';}//	carriage return	byte 0x0d in ASCII encoding
else if(line[posb()+1]=='t'){res+='\t';}//	horizontal tab	byte 0x09 in ASCII encoding
else if(line[posb()+1]=='v'){res+='\v';}//	vertical tab
}
else {res=line[posb()];}
return res;
}
        std::string getStrLit(){
            std::string res;
            for(++posb();line[posb()]!='\'';++posb()){if((posb()==line.length())){NewLine();}
            if(line[posb()]=='\\'){
                if(line[posb()+1]=='\''){res+='\''}//	single quote	byte 0x27 in ASCII encoding
                else if(line[posb()+1]=='\"'){res+='\"'}//	double quote	byte 0x22 in ASCII encoding
                else if(line[posb()+1]=='?'){res+='\?'}//	question mark	byte 0x3f in ASCII encoding
                else if(line[posb()+1]=='\\'){res+='\\'}//	backslash	byte 0x5c in ASCII encoding
                else if(line[posb()+1]=='a'){res+='\a';}//	audible bell	byte 0x07 in ASCII encoding
                else if(line[posb()+1]=='b'){res+='\b';}//	backspace	byte 0x08 in ASCII encoding
                else if(line[posb()+1]=='f'){res+='\f';}//	form feed - new page	byte 0x0c in ASCII encoding
                else if(line[posb()+1]=='n'){res+='\n';}//	line feed - new line	byte 0x0a in ASCII encoding
                else if(line[posb()+1]=='r'){res+='\r';}//	carriage return	byte 0x0d in ASCII encoding
                else if(line[posb()+1]=='t'){res+='\t';}//	horizontal tab	byte 0x09 in ASCII encoding
                else if(line[posb()+1]=='v'){res+='\v';}//	vertical tab
                else {++posb();}
            }
        }
    }

        
              bool Spaced=false;size_t Mag=0;
        template <bool Eval>
        void lexsw(){
                if(OneOfLex<lex::ty::space,lex::ty::nl>(line[posb()])){
                    for(;OneOfLex<lex::ty::space,lex::ty::nl>(line[posb()]) ;++posb()){if((posb()==line.length())){NewLine();};}
                    
                    Spaced=true;}

                if(isdigit(line[posb()])){
                    if(Spaced){if(lexq.back().t==lex::ty::NumFlt){lexq.back().setFlt(Mag);Mag=0;};
                        lexEmplace(posb(),lex::ty::NumUint);lexq.back().setUnum(line[posb()]);Spaced=false;return;}

                    else {if(lexq.back().t==lex::ty::Name){lexq.back().addname(line[posb()]);return;}
                        switch(lexq.back().t){
                            case lex::ty::Name : {lexq.back().u.name+=line[posb()];break;}
                            case lex::ty::NumUint : {lexq.back().addUnum(line[posb()]);break;}
                            case lex::ty::NumFlt : {lexq.back().addUnum(line[posb()]);Mag++;break;}
                            default : {lexEmplace(posb(),lex::ty::NumUint);lexq.back().setUnum(line[posb()]);};break;;}
                    }
                }
                else {if(lexq.back().t==lex::ty::NumFlt){lexq.back().setFlt(Mag);Mag=0;};}
                if(alnum(line[posb()])){
                    if(Spaced){lexEmplace<Eval>(posb(),line[posb()]);Spaced=false;return;}
                    if(lexq.back().t==lex::ty::Name){lexq.back().addname(line[posb()]);}
                    else{
                        if(lexq.back().t==lex::ty::NumUint and lexq.back().u.unum==0){
                            if(line[posb()]=='x'){lexMod<Eval>(lex::ty::lithex);return;}
                            else if(line[posb()]=='b'){lexMod<Eval>(lex::ty::litbin);return;};        
                        }
                        lexEmplace<Eval>(posb(),line[posb()]);return;
                    }
                }
                if(Spaced){Spaced=false;}

                switch(line[posb()]){
                    case lex::ty::ltangle :{
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){
                                if(line.length()>(posb()+2)){
                            if(line[posb()+1]==lex::ty::gtangle){lexEmplace<Eval>(psob(),lex::ty::three)}}
                                
                                lexEmplace<Eval>(posb(),lex::ty::lteq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::ltangle);return;}
                    case lex::ty::gtangle :{
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){lexEmplace<Eval>(posb(),lex::ty::gteq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::gtangle);return;}
                    case lex::ty::lparen :{lexEmplace<Eval>(posb(),lex::ty::lparen);return;}
                    case lex::ty::rparen :{lexEmplace<Eval>(posb(),lex::ty::rparen);return;}
                    case lex::ty::lbrace :{lexEmplace<Eval>(posb(),lex::ty::lbrace);return;}
                    case lex::ty::rbrace :{lexEmplace<Eval>(posb(),lex::ty::rbrace);return;}
                    case lex::ty::lbrack :{
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::lbrack){lexEmplace<Eval>(posb(),lex::ty::ldi);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::lbrack);return;}
                    case lex::ty::rbrack :{
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::rbrack){lexEmplace<Eval>(posb(),lex::ty::rdi);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::rbrack);return;}
                    case lex::ty::bnot : {
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){lexEmplace<Eval>(posb(),lex::ty::Noteq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::bnot);return;}
                    case lex::ty::eq : {
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){lexEmplace<Eval>(posb(),lex::ty::eqeq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::eq);return;}
                    case les::ty::mod : {
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::mod){lexEmplace<Eval>(posb(),lex::ty::modeq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::mod);return;}
               
                    case lex::ty::dq : {lexEmplace<Eval>(posb(),lex::ty::dq);lexq.back().u.name=getStrLit();return;}
                    case lex::ty::sq : {lexEmplace<Eval>(posb(),lex::ty::sq);lexq.back().u.chr=getCharLit();return;}
                    case lex::ty::dot :{
                            if(line.length()>(posb()+1)){if(line[posb()+1]==lex::ty::mul){lexEmplace<Eval>(posb(),lex::ty::dotptr);return;}
                            if(line[posb()+1]==lex::ty::dot){
                                if(line.length()>(posb()+2)){
                                    if(line[posb()+2]==lex::ty::dot){lexEmplace<Eval>(posb(),lex::ty::pack);return;}
                                }
                            }}
                            lexEmplace<Eval>(posb(),lex::ty::dot);return;}
                    case lex::ty::comma :{lexEmplace<Eval>(posb(),lex::ty::comma);return;}
                    case lex::ty::semicolon :{lexEmplace<Eval>(posb(),lex::ty::semicolon);return ;}
                    case lex::ty::colon :{
                        if(line.length()>(posb()+1)){if(line[posb()+1]==lex::ty::colon){
                            if(line.length()>(posb()+2)){
                                if(line[posb()+2]==lex::ty::mul){lexEmplace<Eval>(posb(),lex::ty::ptrmember);return;}
                            }
                            lexEmplace<Eval>(posb(),lex::ty::dcolon);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::colon);
                        return;
                    }
                    case lex::ty::plus : {
                        if(line.length()>(posb()+1)){
                            switch(line[posb()+1]){
                                case lex::ty::plus : {lexEmplace<Eval>(posb(),lex::ty::pp);return;}
                                case lex::ty::eq : {lexEmplace<Eval>(posb(),lex::ty::peq);return;}
                            }};
                        lexEmplace<Eval>(posb(),lex::ty::plus);return;
                    }
                    case lex::ty::minus : {
                        if(line.length()>(posb()+1)){
                            switch(line[posb()+1]){
                                case lex::ty::minus : {lexEmplace<Eval>(posb(),lex::ty::mm);return;}
                                case lex::ty::eq : {lexEmplace<Eval>(posb(),lex::ty::meq);return;}
                                case lex::ty::gtangle : {
                                    if(line.length()>(posb()+2)){if(line[posb()+2]==lex::ty::mul){lexEmplace<Eval>(posb(),lex::ty::arrowptr);return;}}
                                    lexEmplace<Eval>(posb(),lex::ty::arrow);return;
                                }
                            }}
                        lexEmplace<Eval>(posb(),lex::ty::minus);return;}
                    case lex::ty::band :{
                        if(line.length()>(posb()+1)){
                            switch(line[posb()+1]){
                                case lex::ty::band : {lexEmplace<Eval>(posb(),lex::ty::oand);return;}
                                case lex::ty::eq : {lexEmplace<Eval>(posb(),lex::ty::andeq);return;}
                            }};
                        lexEmplace<Eval>(posb(),lex::ty::band);return;}
                    case lex::ty::bor :{
                        if(line.length()>(posb()+1)){
                            switch(line[posb()+1]){
                                case lex::ty::bor : {lexEmplace<Eval>(posb(),lex::ty::oor);return;}
                                case lex::ty::eq : {lexEmplace<Eval>(posb(),lex::ty::oreq);return;}
                            }}
                        lexEmplace<Eval>(posb(),lex::ty::bor);return;}
                    case lex::ty::bxor : {
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){lexEmplace<Eval>(posb(),lex::ty::xoreq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::bxor);return;}
                    case lex::ty::mul : {
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){lexEmplace<Eval>(posb(),lex::ty::muleq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::mul);return;}
                    case lex::ty::div : {
                        if(line.length()>(posb()+1)){
                            if(line[posb()+1]==lex::ty::eq){lexEmplace<Eval>(posb(),lex::ty::diveq);return;}}
                        lexEmplace<Eval>(posb(),lex::ty::div);return;}

                    case lex::ty::cond : {lexEmplace<Eval>(posb(),lex::ty::cond);return;}
                    case lex::ty::escape :{++posb();return;}
                    default : {return ;};
                };
                
        };
       

        // pri::stack<stmt<temp::meta>::block*> openedBlocks;
        // pri::stack<expr<temp::meta>*> openedInitializers;
                

        inline void Line(){
            if(NewLine()){for(;posb()<line.length();++posb()){lexsw<true>();}
        };
        class FileEnd {
            bool b;
            FIleEnd(bool bl) :b(bl){}
        };
        template <bool Eval>
        inline void next(){
            ++posb();
            if(posb()<line.length()){lexsw<Eval>();}
            else {if(!NewLine()){throw FileEnd(true);};lexsw<Eval>();}
            
        };
        bool nextTOK();
        bool checkName(){
            if(lexitback().t==lex::ty::Name){
                macro& m;
                if(macros.get(lexitback().u.name,&m)){
                    itPtr.push_back(lexptrback());
                    pri::deque<lex> q;
                    if(m.function()){
                        nextTOK();
                        if(lexitback().t!=lex::ty::lparen){--lexptrback();err::e<err::t::expectedToken,lex::ty::lparen>(*this);}
                        else {
                            pri::deque<std::string> args;bool arg=true;
                            for(nextTOK();lexitback().t!=lex::ty::rparen;nextTOK()){
                                if(OneOfLex<lex::ty::space>(lexitback().t)){continue;}
                                if(OneOfLex<lex::ty::comma>(lexitback().t)){arg=true;;}
                                if(checkName()){
                                    for(;lexitback().t==lex::ty::space;nextTOK()){}
                                    if(lexitback().t==lex::ty::Name){
                                        if(!arg){err::e<err::t::macro>(*this);}
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
        bool nextTOK(){
            while(lexptrback()==lexq.tail()){next<true>();}
            ++lexptrback();if(it->t==lex::ty::Name){checkName();}
        };
            
    };
   
        template <lex::ty T,lex::ty... Ts>
        bool OneOfLex(lex l){return pri::OneOf<lex::ty,T,Ts...>(l);}
        

        template <typename Kw,typename... Kws>
        bool OneOfKw(std::string str){
            if(KW::check(str)){return true;}
            else if constexpr(sizeof...(Kws)){return OneOfKw<Kws...>(str);}
            else return false;
        };
      
        using lexres=pri::deque<pri::deque<lex>::iter>;
       
        
        template <lex::ty to,lex::ty... tok>
        void until(){
            for(;lexptrback()->t!=to ;nextTOK()){
                if(!OneOfLex<tok...>(lexitback().t)){throw UnexpectedToken(lexitback());}
            };
        };
        template <lex::ty to,lex::ty... tok>
        bool untilWarn(){bool wrn=false;
            for(;lexptrback()->t!=to ;nextTOK()){
                if(!OneOfLex<tok...>(lexitback().t)){wrn=true;}
            };
            return wrn;
        };
        template <lex::ty t,lex::ty... ts>
        void untilDif(){while(OneOfLex<t,ts...>(lexptrback()->t)){nextTOK();}};
        template <lex::ty... ts>
        void untilOneOf(){while(!OneOfLex<t,ts>(lexitback().t)){nextTOK();}}
        
   
        template <lex::ty fromTok,lex::ty toTok,template <temp q> typename T>
        T<temp::meta> _getFromUntil(){return getFromUntil<fromTok,toTok,T<temp::meta>();};



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
        void Stmt();
        
       
        
        pri::stack<accSpec> curAcc;
        template <accSpec acc>void access(){curAcc.back()=acc;};
        template <accSpec acc>void accessPush(){curAcc.push(acc);};
        template <lex::ty tok>
        stmt<temp::meta>::block getBlockUntil(){
            for(;lexptrback().t!=tok;++(lexptrback())){
                getStmtUntil_EOSTMT()
            };
        };

        template <typename KW,typename... KWs>
        bool kwFound(){
            if constexpr (KW::check(lexitback().u.name)){KW::proc(*this);return true;}
            if constexpr (sizeof...(KWs)>0){return kwFound<KWs>();}
            return false;
        } ;
      
        template <bool Eval,typename KW,typename... KWs>
        void untilKW(){for(;!OneOfKw<KW,KWs...>();nextTOK()){};};
        
        // Handling Structs
        template <temp q,template<temp> typename T,typename... Args> T<q>& get();
        
        template <temp q> value<temp::meta>::accMember_list<q> get<q,value<temp::meta>::accMember_list<q>>(){
            value<temp::meta>::accMember_list<q> res;
            for(;!OneOfLex<lex::ty::comma,lex::ty::eq,lex::ty::gtangle>(lexitback().t);nextTOK()){
                if(lex::ty::Name==lexitback().t){

                    res.push_back(value<q>::accMember(lexitback().u.name));
                    nextTOK();
                    if(lex::ty::ltangle==lexitback().t){res.back().plist=get<temp::inst,param_list>();nextTOK();}
                    if(lex::ty::dcolon==lexitback().t){continue;}}
                    else{break;}
                }                
            };
        };        
        template <temp q> value<q> handleDeclType(){
            value<q> res;nextTOK();
            if(lexitback().t!=lex::ty::lparen){throw TypeError()};}nextTOK();
            if(lexitback().t!=lex::ty::Name){throw TypeError();};
            
            resty<temp::meta> res;result r;param_list<q> plist;
            res=cast->findName(lexitback().u.name,&r);if(r==result::rVar){return pri::get<stmt<temp::meta>::VarDecl>(res).tp;}
            if(!Until<lex::ty::dcolon>()){throw TypeError()};nextTOK();}
            for(nextTOK();lexitback().t!=lex::ty::rparen;nextTOK()){
                if(!OneOfLex<lex::ty::dcolon>(lexitback().t)){continue;}
                
                if(OneOfLex<lex::ty::ltangle>(lexitback().t)){plist=get<temp::inst,param_list>();pri::get<type<q>>(res).get(plist);}
                
                if(lex::ty::Name==lexitback().t){if(!cast->find(lexitback().u.name,&res,&r)){err::e(*this,NameNotFound());}}
                if(OneOf<lex::)

            };
        };
        
        template <temp q> value<q>& get<q,value,value<q>::ty::typeValue>(){
            res.t=value<temp::inst>::ty::typeValue;
            resty<temp::meta> rs;result r;
            if(kw_Decltype::check(lexitback().u.name)){ typ = handleDeclType<temp::inst>();}
            rs=cast->findName(lexitback().u.name,&r);
            for(nextTOK();OneOfLex<lex::ty::Name,lex::ty::dcolon,lex::ty::ltangle>(lexitback().t);nextTOK()){
                if(OneOfLex<lex::ty::ltangle>(lexitback().t)){if(r==ast<q>::result::rType){
                    pri::get<type<temp::meta>>(rs)=pri::get<type<temp::meta>>(rs).get(get<temp::inst,param_list>());};}
                if(OneOfLex<lex::ty::Name>(lexitback().u.name)){      
                    if(!cast->find(lexitback.u.name,&rs,&r)){err::e(*this,NameNotFound());}}
            };
            switch(r){
                case ast<q>::result::rType : {
                    if constexpr (q==temp::meta){return pri::get<stmt<q>::Using>(rs).expr;}
                    else {return pri::get<stmt<q>::Using>(rs).expr;}
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
                    if(!cast->find(lexitback.u.name,&rs,&r)){err::e(*this,NameNotFound());}}
            };
            switch(r){
                case ast<q>::result::rVar : {
                    if constexpr (q==temp::meta){return pri::get<stmt<q>::VarDecl>(rs).tp;}
                    else {return value(pri::get<stmt<q>::VarDecl>(rs).tp);}
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


       
         bool correct(lex::ty& acc, result* r,resty<temp::meta>* res){
            switch(acc){
                case lex::ty::none : {return true;}
                case lex::ty::arrow: {return isPtrCompound<temp::meta>(r,res);}
                case lex::ty::dot: {return hasMember<temp::meta>(r,res);}
                case lex::ty::dotptr: {return isCompound<temp::meta>(r,res);}
                case lex::ty::arrowptr: {return isPtrCompound<temp::meta>(r,res);}
                case lex::ty::dcolon: {return isCompound<temp::meta>(r,res);}
                // case lex::ty::dcolptr: {return isCompound<temp::meta>(r,res);}
                default :  {throw UnexpectedToken();}
            }
        }
        bool member(lex::ty& acc,result* r,resty<temp::meta>* res){
            switch(acc){
                case lex::ty::none : {return true;}
                case lex::ty::arrow: {return isMember<temp::meta>(r,res);}
                case lex::ty::dot: {return isMember<temp::meta>(r,res);}
                case lex::ty::dotptr: {return isMemberPtr<temp::meta>(r,res);}
                case lex::ty::arrowptr: {return isMemberPtr<temp::meta>(r,res);}
                case lex::ty::dcolon: {return *(r==result::rType);}
                // case lex::ty::dcolptr: {return *(r==result::rType);}
                default :  {throw UnexpectedToken();}
            }
        };
        bool ref_handle(lex::ty& acc , result* r,resty<temp::meta>* res){
            try {if(!correct(acc,r,res)){throw MemberAccess(*res);}}
            catch(const bool& e){return true;}
            if(!cast->find(lexitback().u.name,&res,&r)){
                value<temp::inst>::accMember_List<temp::inst> mlist;
                switch(*r){
                    case result::rType: {mlist.emplace_back(pri::get<type<temp::meta>*>(*res));}
                    default : {}
                }
                mlist.emplace_back(lexitback().u.name);
                for(nextTOK();!OneOfLex<lex::ty::dcolon,lex::ty::Name,lex::ty::ltangle>(lexitback().t);nextTOK()){
                    if(!OneOfLex<lex::ty::Name>(lexitback().t)){break;}
                    if(lexitback().t==lex::ty::ltangle){mlist.back().plist=get<temp::inst,parama_list>();mlist.back().temp=true;continue;}
                    if(lexitback().t==lex::ty::dcolon){
                        nextTOK();for(;OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK()){}
                        if(OneOfLex<lex::ty::Name>(lexitback().t)){
                            mlist.emplace_back(lexitback().u.name);
                        };
                        
                    }
                }
                pri::get<value<temp::meta>>(*res)=mlist;*r=result::rValue;
                return false;
            };
            nextTOK();
            switch(*r){
                case result::rType :{pri::get<value<temp::meta>>(*res)=pri::get<type<temp::meta>>(*res).get(plist);break;}
                case result::rMethod :{pri::get<value<temp::meta>>(*res)=pri::get<stmt<temp::meta>::FuncDecl>(*res).get(plist);break;}
                case result::rFunc :{pri::get<value<temp::meta>>(*res)=pri::get<type<temp::meta>>(*res).get(plist);break;}
                default :{*r=result::rErr;throw ParamMismatch(plist);}
            }
            return true;
        };
        bool findTp(lex::ty& acc,result* r,resty<temp::meta>* res){

        };
        template <> param<temp::inst>& get<temp::inst,param>(){
            if(!Until<lex::ty::Name,lex::ty::ltangle>()){};
            expr<temp::meta> values=getExpr<lex::ty::comma,lex::ty::rangle>();
            value<temp::inst>& v=values.val();
            param<temp::inst> res;
            pri::get<expr<temp::meta>>(res.varg)=v;;
            switch(v.t){
                case value<temp::inst>::ty::ptrmember:{res.t=param<temp::meta>::ty::PtrToMember;}
                case value<temp::inst>::ty::typeValue:{res.t=param<temp::meta>::ty::Typename;}
                case value<temp::inst>::ty::literal:{res.t=param<temp::meta>::ty::Type;}
                case value<temp::inst>::ty::varRef:{res.t=param<temp::meta>::ty::Type;}
            };
            return res;            
        };
        
        template <temp q> param<temp::meta>& get<temp::meta,param>(){
             
            param<temp::meta> res;
            for(;!OneOfLex<lex::ty::comma,lex::ty::rtangle>();nextTOK()){
                if(kw_Template::check(lexitback().u.name)){
                    until<lex::ty::ltangle,lex::ty::space,lex::ty::nl>();
                    param_list<temp::meta> pl=get<temp::meta,param_list>();
                    res.t=param<temp::meta>::ty::Template;
                    res.pl=pl;
                    untilDif<lex::ty::space,lex::ty::rtanfgle,lex::ty::nl>();
                    if(lexitback().t==lex::ty::Name){if(!OneOfKw<kw_Typename,kw_Class,kw_Struct>(lexitback().u.name) ){err::e(*this);}
                    else{nextTOK();try{until<lex::ty::Name,lex::ty::space,lex::ty::nl}catch(const UnexpectedToken& e){return res;}
                    res.name=lexitback().u.name;return res;    }
                };
                }
                else if(OneOfKw<kw_Typename>(lexitback().u.name)){
                    nextTOK();res.t=param<temp::meta>::ty::Typename;
                    if(lexitback().t==lex::ty::Name){res.name=lexitback().u.name;return res;}
                    else {throw UnexpectedToken(); }
                }
                else if( OneOfKw<kw_Class,kw_Struct>(lexitback().u.name)){res.t=param<temp::meta>::ty::Typename;
                    nextTOK();
                    if(lexitback().t==lex::ty::Name){
                        std::string n=lexitback().u.name;
                        nextTOK();
                        if(OneOfLex<lex::ty::comma,lex::ty::gtangle>(lexitback().t)){res.t=param<temp::meta>::ty::Typename;res.name=lexitback().u.name;return res;}
                        else if(lexitback().t==lex::ty::Name){
                            result r=result::rErr;resty<q> rs;
                            rs=cast->findName(n,&r);
                            res.name=lexitback().u.name;
                            if(r=result::rType ){res.arg=pri::get<type<q>*>(rs);;return res;}
                            else if(r==result::rValue){res.val = pri::get<value<q>>(rs);res.t=param<q>::ty::Type;return res;}
                            else{err::warn(*this,TypeNotFound());}
                        }
                        else if(lexitback().t==lex::ty::dcolon){
                            result r=result::rErr;resty<q> rs;lex::ty acc=lex::ty::dcolone;
                            rs=cast->findName(n,&r);
                            for(nextTOK();ref_handle(acc,&r,&rs);){}
                            res.name=lexitback().u.name;
                            if(r=result::rType ){res.arg=pri::get<type<q>*>(rs);;return res;}
                            else if(r==result::rValue){res.val = pri::get<value<q>>(rs);res.t=param<q>::ty::Type;return res;}
                            else{err::warn(*this,TypeNotFound());}

                        };
                        else {throw UnexpectedToken(); }
                    }
                    else {throw UnexpectedToken();}
                }
                else {// TODO make sure about   ptrmember
                     if(lexitback().t==lex::ty::Name){res.t=param<temp::meta>::ty::Type;
                        std::string n=lexitback().u.name;
                        nextTOK();
                        if(OneOfLex<lex::ty::comma,lex::ty::gtangle>(lexitback().t)){res.t=param<temp::meta>::ty::Typename;res.name=lexitback().u.name;return res;}
                        else if(lexitback().t==lex::ty::Name){
                            result r=result::rErr;resty<q> rs;
                            rs=cast->findName(n,&r);nextTOK();
                            if(lexitback().t==lex::ty::Name){res.name=lexitback().u.name;}
                            if(r=result::rType ){res.arg=pri::get<type<q>*>(rs);;return res;}
                            else if(r==result::rValue){res.val = pri::get<value<q>>(rs);res.t=param<q>::ty::Type;return res;}
                            else{err::warn(*this,TypeNotFound());}
                        }
                        else if(lexitback().t==lex::ty::dcolon){
                            result r=result::rErr;resty<q> rs;lex::ty acc=lex::ty::dcolon;
                            rs=cast->findName(n,&r);
                            for(nextTOK();ref_handle(acc,&r,&rs);){};nextTOK();
                            if(lexitback().t==lex::ty::Name){res.name=lexitback().u.name;}
                            if(r=result::rType ){res.arg=pri::get<type<q>*>(rs);;return res;}
                            else if(r==result::rValue){res.val = pri::get<value<q>>(rs);res.t=param<q>::ty::Type;return res;}
                            else{err::warn(*this,TypeNotFound());}

                        };
                        else {throw UnexpectedToken(); }
                    }
                };
            }
        };
        
        template <temp q> param_list<q> get<q,param_list>(){param_list plist;
            itPtr.push_back(itPtr.back());
            if(nextTOK();!OneOfLex<lex::ty::rangle>(lexitback().t);nextTOK()){
                if(OneOfLex<lex::ty::comma>(lexitback().t)){continue;}
                    plist.push_back(get<q,param>());
            }
            erase();
            return plist;
        };
        ///TODO This function is useless at parsing stage TODO
        template <temp q> type<q> get<q,type>(){type<q> r;stmt<temp::inst>::param_list plist;  
            result r=result::rErr;
            resty<temp::meta> res ;
            itPtr.push_back(lexptrback());
            try {res=cast->findName(lexitback().u.name,&r);}
            catch (const NameNotFound& nsexc){err::e(*this,nsexc);}
            if(r!=result::rErr){
                for(nextTOK();OneOfLex<lex::ty::name,lex::ty::dcolon>(lexitback().t) and (r==result::rNs);nextTOK() ){
                    if(OneOfLex<lex::ty::dcolon>(lexitback().t)){;continue;}
                    if(lexitback().t==lex::ty::Name){
                        try {    res= cast->findNameFromNs(&pri::get<stmt<temp::meta>::NS>(res),lexitback().u.name,&r);}
                        catch (const NameNotFound& nsexc){err::e(*this,nsexc);continue;}
                    }
                    else {err::e<err::t::unexpectedToken(*this);}
                }
                for(nextTOK();OneOfLex<lex::ty::name,lex::ty::dcolon>(lexitback().t);nextTOK()){
                    if(OneOfLex<lex::ty::dcolon>(lexitback().t)){continue;}
                    if(lexitback().t==lex::ty::Name){
                        try {res=cast->findNameFromTp(pri::get<type<temp::meta>>(res),lexitback().u.name,&r);}
                        catch (const NameNotFound& exc) {err::e::t::typeNotFound>(*this);}
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
                        catch(const NameNotFound& exc){err::e::t::typeNotFound>(*this);}
                        nextTOK();
                        if(lexitback().t==lex::ty::ltangle){
                            stmt<temp::inst>::param_list plist=get<stmt<temp::inst>::param_list>();
                            res=cast->getTp(res,plist);
                            break;
                        };
                    }
                }
            }
            else {err::e::t::typeNotFound>(*this);}
            erase();
            return Plist
        };
       
       
        template <lex::ty... l >
        stmt<temp::meta>::VarDecl getVarDecl(){
            stmt<temp::meta>::VarDecl vdecl;
            for(;OneOfLex<lex::ty::Name>(lexitback().t);nextTOK();){
                if(kw_in::check(lexitback().u.name)){vdecl.in=true;};
                else if(kw_out::check(lexitback().u.name)){vdecl.out=true;};
                else if(kw_const::check(lexitback().u.name)){vdecl.Const=true;};
                else {break;}
            };
            if(kw_Auto::check(lexitback().u.name)){vdecl.Auto=true;}
            else {vdecl.tp = get<temp::inst,value>();}
            for(nextTOK();OneOfLex<l...>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::Name){vdecl.name=lexitback().u.name;break;}
            };
            for(nextTOK();!OneOfLex<l...>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::eq){vdecl.DefaultValue=getExpr<l...>();return vdecl;}
            };
            return vdecl;
        };
        stmt<temp::meta>::arg_list getArgList(){  stmt<temp::meta>::arg_list args;
                for(;!OneOfLex<lex::ty::rparen>(lexitback().t);nextTOK()){
                    args.push_back(getExpr<lex::ty::comma,lex::ty::rparen>());
                    if(OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback()->t)){continue;}
                };
                return args;
        };
        #define LEX_ACC lex::ty::arrow,lex::ty::dot,lex::ty::dotptr,lex::ty::arrowptr,lex::ty::dcolon,lex::ty::dcolptr
        template <lex::ty... l> 
        expr<temp::meta> getExprName(){expr<temp::meta> ret;
            if(lexitback().u.name==std::string("true")){res.pushLiteral(true);}
            if(lexitback().u.name==std::string("false")){res.pushLiteral(false);}
            if(kw_New::check(lexitback().u.name)){ret.push<op::ty::opNew,expr::node::opty::prefixUnary>();}
            if(kw_Delete::check(lexitback().u.name)){ret.push<op::ty::opNew,expr::node::opty::prefixUnary>();}
            if(kw_Noexcept::check(lexitback().u.name)){res.push<op::ty::opNoExcept,expr::node::opt::prefixUnary>();
                nextTOK();until<lex::ty::lparen,lex::ty::space,lex::ty::nl>();
                ret.pushExpr( getExpr<lex::ty::rparen>());return ret;
            }
                    
            r=result::rErr;lex::ty lastAcc=lex::ty::none;
            for(nextTOK();!OneOfLex<l...>(lexitback().t) ;nextTOK()){
                if(OneOfLex<LEX_ACC>(lexitback().t)){lastAcc=lexitback().t;nextTOK();continue;}
                if(OneOfLex<lex::ty::Name>(lexitback().t)){
                    if(kw_This::check(lexitback().u.name)){ret.emplaceExpr(value<temp::meta>(cast->strcts.back(),value<temp::inst>::ty::thisRef));}
                    else if(!cast->find(lexitback().u.name,&n,&r)){
                        for(;!OneOfLex<l...>(lexptrback()->t);nextTOK()){while(OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback()->t)){continue;}
                        if(it->t==lex::ty::lparen){nextTOK();auto args=getArgList();
                            if(r==result::rMethod or (r==result::rFunc)){
                                value<temp::meta> vl = get<temp::meta,value>(pri::get<stmt<temp::meta>::FuncDecl*>(n),args);
                                ret.push(vl);return ret;
                            };
                        }
                
                        }
                    }
                }
            }
            return ret;
        };
        template <lex::ty l>
        void expectErr(){
            if(lexitback().t==l){return }
            else{err::e::(*this,UnexpectedToken());for(nextTOK();lexitback().t!=lex::ty::Name;nextTOK()){};}
        }
        attrib::argList getAtArgsList(){
            attrib::argList res;
            for(nextTOK();lexitback().t!=lex::ty::rparen;nextTOK()){
                if(lexitback().t==lex::ty::comma){continue;}
                res.push_back(lexitback());};nextTOK();return res;
        };
        attrib_list getAttribs(){
            attrib_list atlist;
            nextTOK();
            expectWarn<lex::ty::Name>();
            if(kw_Using::check(lexitback().u.name)){
                nextTOK();expectErr<lex::ty::Name>();
                atlist.useNs=true;atlist.nsUse=lexitback().u.name;
                nextTOK();expectErr<lex::ty::colon>();

                for(nextTOK();lexitback().t!=lex::ty::rdi){
                    if(lexitback().t==lex::ty::Name){atlist.emplace_back(lexitback().u.name);
                        nextTOK();}
                    if(lexitback().t==lex::ty::lparen){atlist.back().args=getAtArgsList();continue;}                      
                }
                expectErr<lex::ty::Name>();
            };
            else {
                for(nextTOK();lexitback().t!=lex::ty::rdi){
                    if(lexitback().t==lex::ty::Name){atlist.emplace_back(lexitback().u.name);
                        nextTOK();if(lexitback().t!=lex::ty::dcolon){atlist.back().Ns=true;nextTOK();
                            expectWarn<lex::t::Name>();
                            atlist.back().nsacc=atlist.back().nsacc;
                            atlist.back().name=lexitback().u.name;}
                    }
                    if(lexitback().t==lex::ty::lparen){atlist.back().args=getAtArgsList();continue;}                      
                }
            }
            return atlist;
        };
        value<temp::meta> getRef(){
            resty res;
            result res;
            std::string name=lexitback().u.name;
            nextTOK();if(!OneOfLex<lex::ty::dcolon,>(lexitback().t))
        };
        lambda<temp::meta>::captureList getCaptures(){
            lambda<temp::meta>::captureList res;bool byRef=false;bool arg=false;
            for(nextTOK();lexitback().t!=lex::ty::rbrack;nextTOK()){
                if(lexitback().t==lex::ty::Name){
                    arg=true;
                };
                if(lexitback().t==lex::ty::band){byRef=true;}
                if(lexitback().t==lex::ty::eq){res.copy=true;}
                if(lexitback().t==lex::ty::comma){
                    if(arg){
                        try{res.push(byRef,vl)}catch(const RepeatedName& e){err::e(*this,e);};}
                    }
                    else if(byRef){res.byCopy=false;}
            };
        }
    
        value<temp::meta> getLambda(){lambda<temp::meta> res;
            until<lex::ty::lbrack>();
            lambda<temp::meta>::captureList clist=getCaptures;
            nextTOK();stmt<temp::meta>::arg_list l;res.
            if(lex::ty::ltangle){res.Template=true;res.plist=get<temp::meta,param_list>();cast->curtemp.push_back(&res.plist);nextTOK();}
            if(lex::ty::ldi){res.front_ats=getAttribs();nextTOK();}
            if(lex::ty::lparen){l=getArgList();nextTOK();}
            else{err::e(*this,UnexpectedToken<lambda<temp::meta>>());}
            if(lex::ty::Name){if(kw_Noexcept::check(lexitback().u.name)){res.Noexcept=true;};nextTOK();}
            if(lex::ty::ldi){res.back_ats=getAttribs();nextTOK();}
            if(lex::ty::arrow){res.trailing=true;nextTOK();res.rettp=get<temp::meta,value>();nextTOK();}
            if(lex::ty::lbrace){for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){Stmt();}}
            else{err::e(*this,UnexpectedToken<lambda<temp::meta>>());}
            if(res.Template){cast->curtemp.pop_back();}
            value<temp::meta> vl;vl.t=value<temp::meta>::lambdav;pri::get<lambda<temp::meta>>(vl.val)=res;
            return res;
        };
        template <lex::ty... l>
        expr<temp::meta> getExpr(){
            expr<temp::meta> res;
            if(lexitback().t==lex::ty::lbrack){res.tree.val = getLambda();return res;};
            auto prevName = [&res](){return res.tree.lhs!=nullptr};
            itPtr.push_back(lexptrback());
            auto unary = <op::ty opT>[&](){if(prevName()){res.push<opT,expr::node::opty::postfixUnary>()}else{res.push<opT,expr::node::opty::prefixUnary>()}}
            stmt<temp::meta>::FuncDecl fdecl;type<temp::inst> restt;
            for(;!OneOfLex<l...>(lexptrback()->t);nextTOK()){
                switch(lexitback().t){
                    case lex::ty::Name :{restt = getExprName<l...>();}
                    case lex::ty::Numflt:{res.push(lexitback().u.flt);};
                    case lex::ty::Numuint:{res.push(lexitback().u.num);};
                    case lex::ty::bnot : {res.push<op::ty::opbnot>();break;};
                    case lex::ty::band:{res.push<op::ty::oband>();break;}
                    case lex::ty::dot:{res.push<op::ty::opdot,expr<temp::meta>::node::opty::binary>();;continue;}
                    case lex::ty::arrow:{res.push<op::ty::arrow,expr<temp::meta>::node::opty::binary>();continue;}
                    #ifdef CHAR_LITERALS
                    case lex::ty::sq :{res.pushLiteral(lexitback().u.chr);}
                    case lex::ty::dq :{res.pushLiteral(lexitback().u.name);}
                    #endif
                    case lex::ty::lparen:{res.Start();break;}
                    case lex::ty::rparen:{res.Close();break;}
                    case lex::ty::lbrace:{ res.push(getValueInitializer());break;}
                    case lex::ty::lbrack:{res.push<op::ty::oindex>(); res.push(getExpr<lex::ty::rbrack>());break;;}
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
                    case lex::ty::comma:{err::e<err::t::unexpectedToken>(*this);break;}
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
        void SStmt()
        void FStmt()
        template <>void _getStmt<stmt<temp::meta>::block>(){
            for(;lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();};
            cast->popbl();
        };  
        void getBody(){
            lexq.push_back(lexitback());
            _getStmt<stmt<temp::meta>::block>();
            erase()
        };
        template <>void _getStmt<stmt<meta>::NS>(){
            for(++lexptrback();lexptrback().t!=lex::ty::lbrace;++lexptrback()){
                if(lexptrback().t==lex::ty::Name){cast->emplace_back<stmt<meta>::NS>(it->u.name;);
                    if(!cast->pushNS(pri::get<stmt<meta>::NS>(cast->curBlock()->back()))){
                        err::e<err::t::namespaceNotAllowedInCurrentScope>(*this);};continue;}
                if(!OneOfLex<lex::ty::space,lex::ty::nl>(lexptrback().t)){err::e<err::t::unexpectedToken>(*this);}
            };
            open<lex::ty::lbrace>();
        };
        template <>void _getStmt<stmt<temp::meta>::While>(){
            stmt<temp::meta>::While* res=cast->pushStmt<stmt<temp::meta>::While>();
            nextTOK();expectErr<lex::ty::lparen>();nextTOK();res->condition=getExpr<lex::rparen>();
            nextTOK();expectErr<lex::ty::lbrace>();
            for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();}
            nextTOK();
        };
        template <>void _getStmt<stmt<temp::meta>::For>(){
            
            nextTOK();expectErr<lex::ty::lparen>();
            itPtr.push(lexptrback());
            for(nextTOK();!OneOfLex<lex::ty::semicolon,lex::ty::colon>(lexitback().t);nextTOK()){}
            nextTOK();res->init=getExpr<lex::ty::semicolon,lex::ty::colon>();
            if(OneOfLex<lex::ty::colon>(lexitback().t)){itPtr.pop();
                stmt<temp::meta>::ForRange* res=cast->pushStmt<stmt<temp::meta>::ForRange>(stmt<temp::meta>::ForRange());
                nextTOK();
                res->vardecl=getVarDecl<lex::ty::colon>();nextTOK();
                res->ref=getExpr<lex::ty::rparen>();nextTOK();
            }
            else{stmt<temp::meta>::For* res=cast->pushStmt<stmt<temp::meta>::For>(stmt<temp::meta>::For());
                if(lexitback().t!=lex::ty::semicolon){res->init=getExpr<lex::ty::semicolon>();nextTOK();}
                else{nextTOK();}
                if(lexitback().t!=lex::ty::semicolon){res->condition=getExpr<lex::ty::semicolon>();nextTOK();}
                else {nextTOK();}
                if(lexitback().t!=lex::ty::rparen){res->incr=condition<lex::ty::rparen>();}                                
            }
            nextTOK();expectErr<lex::ty::lbrace>();
            for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();}
            nextTOK();
        };
        template <>void _getStmt<stmt<temp::meta>::Do>(){
            cast->pushStmt<stmt<temp::meta>::Do>(stmt<temp::meta>::Do());
            nextTOK();
            if(lexitback().t==lex::ty::lbrace){
                for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();}
                nextTOK();
            }
            else FStmt();
        };
        template <>void _getStmt<stmt<temp::meta>::Case>(){};
        template <>void _getStmt<stmt<temp::meta>::Switch>(){
            nextTOK();
            for()
            SStmt(); 

        };
        template <>void _getStmt<stmt<temp::meta>::Default>(){

        };
        template <>void _getStmt<stmt<temp::meta>::OperatorDecl>(){
            
        };
        template <>void _getStmt<stmt<temp::meta>::Try>(){
            stmt<temp::meta>::Try res; 
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK()){}
            if(!OneOfLex<lex::ty::lbrace>(lexitback().t)){err::e<err::t::unexpectedToken>(*this);}
            cast->pushbl(res.body);
            for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();};
            cast->popbl();
            cast->pushStmt(res);
        };
        
        template <>void _getStmt<stmt<temp::meta>::Catch>(){
            cast->pushStmt<stmt<temp::meta>::Catch>();
            stmt<temp::meta>::Catch& res= pri::get<stmt<temp::meta>::Catch>(*getStmt());
            cast->tries.top()->catches.push_back(&res);nextTOK();
            nextTOK();expectErr<lex::ty::lparen>();
            res.var=getVarDecl<lex::ty::rparen>();nextTOK();
            expectErr<lex::ty::lbrace>();
            for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();}
            cast->popbl();nextTOK();
            if(lexitback().t==lex::ty::semicolon){
                cast->tries.pop_back();
            }
            kwFound<kw_Catch>();

        };
        template <>void _getStmt<stmt<temp::meta>::Throw>(){
            nextTOK();
            expr<temp::temp::meta> vl=getExpr<lex::ty::semicolon>();
            cast->pushStmt<stmt<temp::meta>::Throw>(vl);
        };
        
        template <>void _getStmt<stmt<temp::meta>::If>(){bool ConstExpr=false;
            for(nextTOK();lexitback().t!=lex::ty::lparen;nextTOK()){
                if(OneOfKw<kw_ConstExpr>(lexitback().u.name)){ConstExpr=true;}
                else {err::e<err::t::unexpectedToken>(*this);}
            };
            stmt<temp::meta>::If* r=cast->pushStmt<stmt<temp::meta>::If>(stmt<temp::meta>::If(getExpr<lex::ty::rparen>()));
            if(ConstExpr){r.ConstExpr=true;}
            for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt();};
            
        };
        template <typename T> void Else(T* r){
            stmt<temp::meta>* last=cast->getStmt();
            switch(last->t){
                case stmt<q>::stmtty::eIf:{r->elIf=false;pri::get<stmt<temp::meta>::If*>(r->Ifs)=&pri::get<stmt<temp::meta>::If>(last->var);}
                case stmt<q>::stmtty::eElseIf:{r->elIf=true;pri::get<stmt<temp::meta>::ElseIf*>(r->Ifs)=&pri::get<stmt<temp::meta>::ElseIf>(last->var);}
            }    
        }
        template <>void _getStmt<stmt<temp::meta>::ElseIf>(){bool ConstExpr=false;
            for(nextTOK();lexitback().t!=lex::ty::lparen;nextTOK()){
                if(checkName()){
                    if(OneOfKw<kw_ConstExpr>(lexitback().u.name)){ConstExpr=true;}
                    else {err::e<err::t::unexpectedToken>(*this);}
                }
            };
            stmt<temp::meta>::ElseIf* r=cast->pushStmt<stmt<temp::meta>::ElseIf>(stmt<temp::meta>::ElseIf(getExpr<lex::ty::rparen>()));
            if(ConstExpr){r->ConstExpr=true;}
            Else<stmt<temp::meta>::ElseIf>(r);
            for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt()};
                        cast->popbl();

        };
        template <>void _getStmt<stmt<temp::meta>::Else>(){
            nextTOK();
            if(kw_If::check(lexiback().u.name)){_getStmt<stmt<temp::meta>::ElseIf>();return;}
            stmt<temp::meta>::Else* r;
            r=cast->pushStmt<stmt<temp::meta>::Else>(stmt<temp::meta>::Else());
            Else<stmt<temp::meta>::Else>(r);
            if(lexitback().t==lex::ty::lbrace){for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){FStmt()};cast->popbl();}
            else {if(kw_Return::check(lexitback().u.name)){_getStmt<temp::meta>::Return>();};
            else{_getStmt<temp::meta>::Expr>();}
            }
        };
        stmt<temp::meta>::FuncDef* curfunc;
        template <>void _getStmt<stmt<temp::meta>::Return>(){cast->pushStmt<stmt<temp::meta>::Return>(getExpr<lex::ty::semicolon,lex::ty::rbrace>());};
        template <>void _getStmt<stmt<temp::meta>::FuncDef>(){
            stmt<temp::meta>::FuncDef& res=*curfunc;
            for(;lexitback().t;nextTOK())
        };
        

        
        // Starts after type is specified
        template <>void _getStmt<stmt<temp::meta>::VarDecl>(){// Default To FuncDecl, where appropiate;
            bool bStrct; bool bUnion;
            if(OneOfKw<kw_Struct,kw_Class,kw_Union>(lexitback().u.name)){};

            for(;OneOfLex<lex::ty::semicolon>(lexitback().t);nextTOK()){
                if(lexitback().t==lex::ty::lparen){_getStmt<stmt<temp::meta>::}
            };
        };
        template <>void _getStmt<stmt<temp::meta>::DeclType>(){
            for(nextTOK();OneOfLex<lex::ty::space,lex::ty::nl>(lexitback().t);nextTOK();){};
            if(lexitback().t!=lex::ty::name){_getStmt<stmt<temp::meta>::Expr>();return ;}
            
            if(kw_Template::check(lexitback().u.name)){
                StmtDeclType
            }
        };
        
        
        template <>void _getStmt<stmt<temp::meta>::Using>(){
            stmt<temp::meta>::Using& res=cast->GetUsing();
            nextTOK();expectErr<lex::ty::Name>();bool inln=false;
            if(kw_inline::check(lexitback().u.name)){nextTOK();expectErr<lex::ty::Name>();}
            if(kw_Namespace::check(lexitback().u.name)){res.Namespace=true;nextTOK();expectErr<lex::ty::Name>();
                res.name=lexitback().u.name;nextTOK();expectErr<lex::ty::semicolon>();return res;}
            res.name= lexitback().u.name;
            res.prms=*curtemp.back();curtemp.back()=&res.prms;
            until<lex::ty::eq,>();nextTOK();
            until<lex::ty::Name,>();
            res.expr=get<temp::inst,value>();
            until<lex::ty::semicolon>();
        };
        template <>void _getStmt<stmt<temp::meta>::TypeDef>(){
            cast->pushStmt<stmt<temp::meta>::TypeDef>(stmt<temp::meta>::TypeDef());
            stmt<temp::meta>::TypeDef& res=cast->getTypeDef();
            nextTOK();
            res.expr=get<temp::inst,value>();nextTOK();expectErr<lex::ty::Name>();
            res.name=lexitback().u.name;
        };
        
        template <stmt<temp::meta>::Layout::stand st, Str s >struct lyt_std{
            stmt<temp::meta>::Layout::stand t =st;
            static constexpr auto value = s;
            std::string name(){return std::string(value.data.data());}

        };
        using std430 = lyt_std<stmt<temp::meta>::Layout::stand::std430,"std430">;
        using std140 = lyt_std<stmt<temp::meta>::Layout::stand::std430,"std140">;

        template <typename STD,typename... STDs>
        bool getStd(stmt<temp::meta>::Layout& s){
            if(getStd(s)){return true;}
            return getStd<STDs...>(s);
        };
        template <typename STD>
        bool getStd(stmt<temp::meta>::Layout& s){
            if(lexptrback()->u.name==STD::name()){s.st=STD::t;return true;};
            return false;
        };
        
        // using getLytAt = BoolFunc<stmt<temp::meta>::Layout,getLytAt,lyt_at,lyt_ats...>;
        template <typename lyt_at,typename... lyt_ats>
        bool getLytAt(stmt<temp::meta>::Layout& s){
            if(getLytAt<lyt_at>(s)){return true;};
            return getLytAt<,lyt_ats...>(s);
        };
        template <typename lyt_at>
        bool getLytAt(stmt<temp::meta>::Layout& s){
            if(lexptrback()->u.name==lyt_at::name()){
                s.t=lyt_at::lytTy;
                lexres unexp=untilExp<lex::ty::eq,lex::ty::space>();
                unexp+=untilExp<lex::ty::NumUint,lex::ty::space>();
                if(!unexp.empty()){err::e<err::t::unexpectedToken>(*this,unexp);};
                s.loc=lexptrback().u.unum;
                return true;
            };
            return false;
        };
        void getLytVar(stmt<temp::meta>::Layout& lyt ){
            for(;OneOfKw<kw_in,kw_out,kw_inout,>(lexitback().t);nextTOK()){
                if(checkName()){
                    if(kw_Uniform::check(lexitback().u.name)){lyt.uniform=true;}
                    if(kw_Flat::check(lexitback().u.name)){lyt.flat=true;}
                }
            };
            if(kw_in::check(lexitback().u.name)){lyt.in=true;}
            if(kw_inout::check(lexitback().u.name)){lyt.in=true;lyt.out=true;}
            if(kw_out::check(lexitback().u.name)){lyt.out=true;}
            lyt.vart=stmt<temp::meta>::Layout::tyT::var;
            for(nextTOK();!OneOfLex<lex::ty::semicolon,lex::ty::lbrace>(lexitback().t);nextTOK()){
                if(lex::ty::Name==lexitback().t){
                    if(kw_Buffer::check(lexitback().u.name)){lyt.vart=stmt<temp::meta>::Layout::tyT::buffer;continue;};
                    if(kw_Uniform::check(lexitback().u.name)){lyt.vart=stmt<temp::meta>::Layout::tyT::uniform;continue;};
                    if(lyt.vart==stmt<temp::meta>::Layout::tyT::var){

                        cast->ptr.vd=&pri::get<stmt<temp::meta>::VarDecl>(lyt.data);getStmt<stmt<temp::meta>::VarDecl>() ;
                        lyt.name=pri::get<stmt<temp::meta>::VarDecl>(lyt.data).name;
                        return;
                    }
                    else {lyt.name=name;}
                
                }
                else if(!OneOfLex<lex::ty::space,lex::ty::nl>()){err::e<err::t::unexpectedToken>(*this);}
            }
            if(lexitback().t==lex::ty::lbrace){cast->ptr.dt=pri::get<stmt<temp::meta>::DefType>(lyt.data);getStmt<stmt<temp::meta>::TypeDef>();}
        };
        template <>void _getStmt<stmt<temp::meta>::Layout>(){
            
            cast->pushStmt<stmt<temp::meta>::Layout>();stmt<temp::meta>::Layout& lyt=cast->layouts.back();
            nextTOK();
            if(lexitback().t!=lex::ty::lparen){err::e<unexpectedToken,stmt<temp::meta>::Layout>(*this);}
            for(;lexptrback()->t==lex::ty::rparen;nextTOK()){
                lexres unexp=untilExp<lex::ty::eq,lex::ty::space>();
                if( checkName()) {
                    if(getStd<std430,std140>(lyt)){continue;}
                    if(getLytAt<kw_Location,kw_Binding>(lyt)){continue;};
                };
                if(!OneOfLex<lex::ty::comma,lex::ty::space,lex::ty::Name>(lexptrback()->t)){
                    err::e<unexpectedToken>(*this);
                };
            };
            getLytVar();
        };
        template <>void _getStmt<stmt<temp::meta>::Expr>(){stmt<temp::meta>::Expr res=GetExpr<lex::ty::semicolon>();
            cast->pushStmt(res);};

        template <typename StmtTy>
        void getStmt(){
            itPtr.push_back(lexptrback());
            _getStmt<StmtTy>();
            erase();
        };
        integralT getEnumIntegral(){
            integralT res;
            nextTOK();
            expectErr<lex::ty::Name>();
            if(kw_signed::check(lexitback().u.name)){res.s=integralT::sing::Unsinged;nextTOK();}
            else if(kw_unsigned::check(lexitback().u.name)){res.s=integralT::sing::Singed;nextTOK();expectErr<lex::ty::Name>();}
            else if(kw_short::check(lexitback().u.name)){}
            else if(kw_long::check(lexitback().u.name)){
                nextTOK();expectErr<lex::ty::Name>();
                if( kw_long::check(lexitback().u.name)){integralT::len::LongLong;nextTOK();}
                else{res.l=integralT::len::Long;}
                expectErr<lex::ty::Name>();
            }
                if(std::string("int") ==lexitback().u.name){res.t=integralT::ty::flt;}
                eles if(std::string("float") ==lexitback().u.name){res.t=integralT::ty::Int}
                eles if(std::string("double") ==lexitback().u.name){res.t=integralT::ty::Double}
                else if(std::string("char") ==lexitback().u.name){res.t=integralT::ty::Ch;}
                else {
                    result r;resty<temp::meta> rs;lex::ty acc=lex::ty::none;
                    ref_handle(acc,&r,&rs);
                    switch(r){
                        case result::rValue :{res.mt=pri::get<value<temp::meta>>(rs);}
                        case result::rType : {res.mt=pri::get<type<temp::meta>*>(rs);}
                    }
                }
            return res;
        };

        void Enum(bool bTemp,stmt<temp::meta>::param_list& plist){stmt<temp::meta>::Enum res;
            nextTOK();
            if(lexitback().t==lex::ty::Name){if(kw_Struct::check(lexitback().u.name) or(kw_class::check(lexitback().u.name))){enclass=true;nextTOK();}};
            if(lexitback().t==lex::ty::rdi){res.ats=getAttribs();nextTOK();}
            res.name=lexitback().u.name;nextTOK();
            if(lexitback().t==lex::ty::colon){res.SpeqSeq=true;res.intt=getEnumIntegral();};
            nextTOK();
            stmt<temp::meta>* ptr=cast->pushStmt(res);
            if(lexitback().t==lex::ty::lbrace){
                for(nextTOK();lexitback().t!=lex::ty::rbrace;nextTOK()){
                    if(lexitback().t!=lex::ty::Name){
                        ptr->emplace_back(lexitback().u.name);
                        nextTOK();
                        if(lexitback().t==lex::ty::eq){ptr->back().cexprval=GetExpr<lex::ty::comma>();}
                        if(lexitback().t!=lex::ty::comma){err::e(this,UnexpectedToken<stmt<temp::meta>::Enum>());}
                        
                    }
                    else {err::e(this,UnexpectedToken<stmt<temp::meta>::Enum>());};
                };
            }
        };
        template <bool Strct>
        struct AccDefault {static constexpr bool acc=Strct?accSpec::Public:accSpec::Private;}
        template <bool Strct>
        type<temp::meta>::inher_list getInherList(){
            type<temp::meta>::inher_list res;
            for(nextTOK();!OneOfLex<lex::ty::semicolon,lex::ty::lbrace>(lexitback().t)){
                expectErr<lex::ty::Name>();
                if(lexitback().t==lex::ty::Name){
                    if(kw_Public::check(lexitback().u.name)){res.emplace_back(accSpec::Public);nextTOK();}
                    else if(kw_Protected::check(lexitback().u.name)){res.emplace_back(accSpec::Protected);nextTOK();}
                    else if(kw_Private::check(lexitback().u.name)){res.emplace_back(accSpec::Private);nextTOK();}
                    else {res.emplace_back(get<temp::meta,value>(),AccDefault<Strct>::acc);nextTOK();}
                    if(lexitback().t==lex::ty::Name){ res.back().t=get<temp::meta,value>();nextTok();}
                }
            };
            return res;
        };

        template <bool Strct>
        void Strct(bool bTemp,stmt<temp::meta>::param_list& plist){
            nextTOK();
            result r;resty<temp::meta> res;expectErr<lex::ty::Name>();
            std::string name=lexitback().u.name;
            nextTOK();stmt<temp::meta>::TypeDecl* tp;
            try{tp=cast->findTpDecl(name);
            if(lexitback().t==lex::ty::dcolon){
                while(tp->
            }
            else if (lexitback().t==lex::ty::colon){
                type<temp::meta>::inher_list lst=getInherList();
            }
            }catch(const TypeNotFound e){

            }
            
        };
        void Union(bool bTemp,stmt<temp::meta>::param_list& plist){
            try {until<lex::ty::Name,lex::ty::space,lex::ty::nl>();}
            catch (const UnexpectedToken& e){
                if(e.what().t==lex::ty::lbrace){
                    getStmt<stmt<temp::meta>::Union>();
                    try{until<lex::ty::Name,lex::space,lex::ty::nl>();}
                    catch (const UnexpectedToken& e){return;}
                    stmt<temp::meta>::VarDecl res;cast->pushStmt(res);

                }
                else{err::e(*this,e);}
            }
        };
        void Using(bool bTemp,stmt<temp::meta>::param_list& plist){
            cast->pushStmt<stmt<meta>::Using>(stmt<meta>::Using());
            stmt<temp::meta>::Using& res=get<stmt<meta>::Using>(cast->last().var);
            if(bTemp){res.prms=plist;}
            getStmt<stmt<temp::meta>::Using>();
        };
        
       
        template <bool Strct,bool Func>
        void NameStmt(){
            auto r= result::rErr;
            resty<temp::meta> res;
            lex::ty lastAcc=lex::ty::none;
            for(;!OneOfLex<lex::ty::semicolon>(lexitback().t);nextTOK()){
                if(OneOfLex<LEX_ACC>()){lastAcc=lexitback().t;
                    if(lastAcc==lex::ty::colptr){throw UnexpectedToken();}
                    continue;}
                if(lexitback().t==lex::ty::Name){
                    try{if(ref_handle(lastAcc,&r,&res)){continue;}else break;}
                    catch(const ParamMismatch& e){err::e(*this,e);}
                    catch(const MemberAccess& e){err::e(*this,e);}
                }
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
                        access= getStmt<stmt<temp::meta>::DeclType>();break;
                    }                    
                    if(OneOfKw<kw_Struct>(lexitback().u.name)){accessPush<accSpec::Public>();
                        getStmt<stmt<temp::meta>::DeclType>();break;
                    }
                    getStmt<stmt<temp::meta>::FuncDecl>()

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
            else {err::e<err::t::fileNotFound>(*this,pth);}
        };
        void includeAbs(std::filesystem::path l){
            for(std::filesystem::path p : dirs.arr ){
                std::filesystem::path pth = p;pth/=l;
                if(std::filesystem::exists(ps)){parser pn;cast->include(pn.fromFile(pth,*this));return;}
            };
            err::e<err::t::fileNotFound>(*this,pth);
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
                    if(lexptrback()->t!=lex::ty::name){err::e<err::t::include_closing_angle_brackets>(*this);break;}
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
                    if(lexptrback()->t!=lex::ty::name){err::e<err::t::include_closing_dq>(*this);break;}
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

        struct mtype {
            pri::variant<stmt<temp::meta>::FuncDecl,stmt<temp::meta>::OperatorDecl,stmt<temp::meta>::TypeDecl> var;
            enum class ty{Func,Oper,rType} ;ty t;
        };
        mtype getMtype(){
            if(kw_Class::check(lexitback().u.name or kw_Struct::check(lexitback().u.name))){
                nextTOK();until<lex::ty::Name,lex::ty::space>();
                result r;resty<temp::meta> res;lex::ty acc=lex::ty::none;
                ref_handle(acc,&r,&res);
                if(r==result::rType){}
            }
            
        };
        void GetFriend(){nextTOK();
            until<lex::ty::Name,lex::ty::space>();bool bPack=false;bool blist=true;
            lexq.push_back(lexptrback());
            for(;!OneOfLex<lex::ty::semicolon>(lexitback().t);nextTOK()){
                mtype res=getMtype();
                if(lexitback().t==lex::ty::pack){bPack=true;}
                if(lexitback().t==lex::ty::comma){blist=true;}
            };
            lexq.pop_back();
            
        };
        template <bool Strct,bool Func, bool Sw>
        bool StmtPush(){
            if(OneOfLex<lex::ty::Name>(lexitback().t)){
                if(lexitback().t!=lex::ty::lbrack){
                    stmt<q>::block* res=cast->pushStmt(block());
                    for(nextTOK();lexitback().t!=lex::ty::rbrack){FStmt();}
                    nextTOK();cast->curBl.pop_back();
                };
                if(kwFound<KW_LISTM>()){return true;}
                stmt<temp::meta>::param_list plist ;bool bTemp=false;
                if(kw_Template::check(lexitback().u.name)){bTemp=true;
                    if(Func){err::e(*this,UnexpectedToken("Template Not allowed in function body"));}
                    nextTOK();unil<lex::ty::ltangle,lex::ty::space,lex::ty::nl>();
                    plist = get<temp::meta,param_list>();until<lex::ty::Name,lex::ty::rtangle,lex::ty::space,lex::ty::nl>();
                }
                if constexpr (Strct){
                    if(kw_Operator::check(lexitback().u.name)){GetOperator<Strct>();}
                    else if(kw_Friend::check(lexitback().u.name)){GetFriend();}
                    else if(kwFound<KW_ACCS>()){return;};
                }
                if constexpr (!Func) {
                    if(kw_Enum::check(lexitback().u.name)){Enum(bTemp,plist);return;}
                    else if(kw_Struct::check(lexitback().u.name) ){Strct<true>(bTemp,plist);return;}
                    else if(kw_class::check(lexitback().u.name)){Strct<false>(bTemp,plist);return;}
                    else if(kw_Union::check(lexitback().u.name)){Union(bTemp,plist);return;}
                    else if(kw_Using::check(lexitback().u.name)){Using(bTemp,plist);return;}
                    else {NameStmt<Strct,Func>();}
                }
                else {
                    if constexpr (Sw){if(kwFound<KW_SWSTMT>()){return;}}
                    if(kwFound<KW_LISTSTMT>()){return;}
                    else {NameStmt<Strc,Func>();}
                };
            }
            else {
                if constexpr (func || !Strct){getStmt<stmt<temp::meta>::Expr>();}
                else {throw UnexpectedToken();}
            }
            
        };
        void FStmt(){if(!kwFound<KW_LISTM>()){
            if(cast->nsblck){StmtPush<false,true>();}else{StmtPush<true,true,false>();}}}
        void SStmt(){
                        if(!kwFound<KW_LISTM>()){
            if(cast->nsblck){StmtPush<false,true>();}else{StmtPush<true,true,true>();}}}

        void Stmt(){
            if(!kwFound<KW_LISTM>()){
            if(cast->nsblck){if(cast->fblck){StmtPush<false,true,false>();}else{StmtPush<false,false,false>();}
            else{if(cast->fblck){StmtPush<true,true>();}else{StmtPush<true,false>();}};
        };

        ast* fromFile(std::filesystem::path pth){ curFilePath.push_back(pth);
            cast=new ast();
        cwd.push(pth.parent_path());
        f.open(pth);
        pos.push_back(posit());bool fend=false;
        try {while(Line()){Stmt();}}
        catch (const FileEnd& e){fend=e.b;}
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