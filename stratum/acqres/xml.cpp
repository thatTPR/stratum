#ifndef ACQXML_CPP
#define ACQXML_CPP
#define MACROSP
#ifdef MACROSP
#define PRINT(s) std::cout<< s ;
#define PRINTQ(S) print(S);
#else
#define PRINT(s) 
#define PRINTQ(S) 
#endif
#define MACROSE
#ifdef MACROSE
#define PRINTE(S) print(S);
#else
#define PRINTE(S)
#define PRINTT(E) printTree(E);
#endif
#include <string>
#include <vector>
#include <stdint.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <petri/list.hpp>
std::string replace(std::string f , std::vector<std::pair<std::string,std::string>> reps){
    std::string ret = f; 
    size_t pos;
        for(const auto& it : reps){
            pos = ret.find(it.first);
            while(pos!=std::string::npos){
                ret.replace(pos,it.first.size(),it.second);
                pos = ret.find(it.first,pos);
            };
    };
    return ret ;
};

void getLine(std::ifstream& f,std::string* s){
    *s="";
    while(true){
        *s+=" ";
        f>>s->back();
        if(s->back()=='\n'){return ;};
    };
};
template<typename T>
class elTree {
    public:
    elTree<T>* parent ; 
    T data ;
    std::vector<elTree<T>> childs;

};
class xmlParser {
    public:
     const std::string start = "<" ;
     const std::string end = "/>" ;

     const std::string estart = "</";
     const std::string close  = ">" ;

     const std::string equot = "&quot";
     const std::string eapos = "&apos";
     const std::string elt = "&lt";
     const std::string egt = "&gt";
     const std::string eamp = "&amp";

     const std::string eq = "=";
     const std::string quot = "\"";
     const std::string apos = "\'";
    //  const std::string lt = "<";
    //  const std::string gt = ">";
     const std::string amp = "&";

     typedef std::pair<std::string ,std::string > attribute;



    class eltree  {
        public:
        eltree* parent;
        std::string name ;
        union elu {
            public:
            std::string str;
            const eltree* child;
            elu() {};
            elu(const std::string& st) : str(st) {};
            elu(const eltree* ch) : child(ch) {};
            
            ~elu() {delete this;};
        };
        struct element {
            int8_t t ; // 0:str , 1: el
            elu d;
            element() {};
            element(const element& el) : t(el.t){
                if(t==0){d.str=el.d.str;}
                else {d.child = el.d.child;}
            };
            element(const std::string& str) : t(0), d(str){};
            element(const eltree* child) : t(1), d(child){};
        };
        
        std::vector<attribute> attributes ;
        list<element> value ;
        
        eltree() {};
        eltree(const eltree& _Et) : parent(_Et.parent),name(_Et.name),attributes(_Et.attributes) , value(_Et.value) {};
        
    };
    eltree tree ;
    bool val(eltree& el,std::string* res,int pos=0){
        for(const eltree::element& it : el.value){
            if(it.t==0){*res = it.d.str;return true;};
        };
        return false;
    };
    bool val(eltree& el,eltree* res,int pos=0){
        for(const eltree::element& it : el.value){
            if(it.t==1){res =const_cast<eltree*>(it.d.child);return true;};
        };
        return false;
    };
    
   
    bool getChildByName(const eltree* el , std::string name , eltree* res){
        for(const eltree::element& it : el->value){
            if(it.t==0){continue;};
            if(it.d.child->name == name){
                res = const_cast<eltree*>(it.d.child);
                return true ;
            };
        };
        return false;
    };
    std::vector<eltree> getChildsByName(const eltree* el ,std::string name){
        std::vector<eltree> res;
        for(const eltree::element& it : el->value){
            if(it.t == 0){continue;};
            if(it.d.child->name == name){
                res.push_back(*(it.d.child));
          };
        };
        return res;
    };
    //std::vector<std::string> getValues(eltree& el,std::string name);
    
    std::string noescape(std::string f) {
        return replace(f,{
        {equot,quot},
        {eapos,apos},
        {elt,start},
        {egt,close},
        {eamp,amp}
        });
    };
    std::string escape(std::string f) {
        return replace(f,{
            {quot,equot},
            {apos,eapos},
            {start,elt},
            {close,egt},
            {amp,eamp}
            });
        };
    
    eltree* cur = &tree;
    
    enum tok{
        sp,
        lt,
        gt,
        quotOpen,
        apostOpen,
        value,
        ltEnd,
        gtEnd,
        eqs,
        name,
        id,
        elStart,
        elval,
        el,
        com
    };
     struct lexe {
        tok t;
        std::string d;
    };
   
    list<lexe> lexq ;

    list<lexe>::iter lexqfind(tok t,list<lexe>::iter s){
        list<lexe>::iter c(s);
        for(; c; ++c){
            if(c->t  == t){return c;}
        };
        return lexq.end();
    };
    list<lexe>::iter lexqrfind(tok t, list<lexe>::iter s ){
        list<lexe>::iter c(s); 
        for(; c ; --c ){
            if(c->t  == t){return c;}
        };
        return lexq.end();
    };

    std::string get(tok t){
              switch(t){
                case tok::sp : {return "sp";};
                case tok::lt : {return "lt";};
                case tok::gt : {return "gt";};
                case tok::quotOpen : {return "quotOpen";};
                case tok::apostOpen : {return "apostOpen";};
                case tok::value : {return "value";};
                case tok::ltEnd : {return "ltEnd";};
                case tok::gtEnd : {return "gtEnd";};
                case tok::eqs : {return "eqs";};
                case tok::name : {return "name";};
                case tok::id : {return "id";};
                case tok::elStart : {return "elStart";};
                case tok::elval : {return "elval";};
                case tok::el : {return "el";};
                case tok::com : {return "com";};
                default : {return "";};
            };
                
        };
    void print(list<lexe>& q){
        for(const lexe& it : q){
            std::cout<<get(it.t)<<" ";
        };
        std::cout<<std::endl;
    };
    int depth(){
        int i=0;
        for(const auto& it : lexq){
            if(it.t == tok::elStart)i++; 
        };
        return i;
    };
    int lexDepth(){ list<lexe>::iter i = lexqrfind(tok::elStart,lexq.end()-1); int j = 1;
        if(!i){return 0;};
        while( i ){ i= lexqrfind(tok::elStart,i) ; j++;};
        return j;
    };
    bool Strb = false;bool instart; bool inval=false; bool inel=false; bool inclose=false;
    std::string stri ;
    void feed(std::string& line){
        PRINT(std::endl<<"feed: "<<line<<std::endl)
        PRINT("LS:"<<lexq.size()<<std::endl)
        PRINTQ(lexq)
        for(int i = 0 ; i < line.size();i++){
            if(lexq.back().t == tok::com){
                if(line[i]=='>'){lexq.pop_back();};
                continue;};
            auto lval = [&](int p){
                std::string str;
                    if(p){str = line.substr(i,p-i+1) ; i = p;}
                    else {
                        Strb = true;
                        str = line.substr(i);
                    };
                    this->lexq.push_back({tok::value,str});
            };
            if(Strb == true){
                std::string str; size_t p ; 
                switch(lexq.back().d.front()) {
                    case '\'' : {p =  line.find("\'");};
                    case '"' : {p = line.find("\"");};
                };
                if(p){str = line.substr(0,p); Strb = false;}
                else {str = line; }   
                lexq.back().d+=str;
                continue ;
            };
            if(line[i]== '"'){PRINT(":\"")
                if(lexq.back().t == tok::elval ){lexq.back().d+=line[i];};
                if(lexq.back().t == tok::elStart){lexq.push_back({tok::elval,std::string()+line[i]});};
                size_t p = line.find("\"",i+1);
                lval(p);
                continue;
            };
            if(line[i] == '\'' ){PRINT(":'")
                if(lexq.back().t == tok::elval ){lexq.back().d+=line[i];};
                if(lexq.back().t == tok::elStart){lexq.push_back({tok::elval,std::string()+line[i]});};
                size_t p = line.find("\'",i+1);
                lval(p);
                continue;
            };
            if(line[i]== '='){PRINT(":=")
                if(lexq.back().t == tok::elval ){stri+=line[i];};
                if(lexq.back().t == tok::elStart){lexq.push_back({tok::elval,std::string()+line[i]});};
                lexq.push_back({tok::eqs,eq});
                continue ;
            };
            if(line[i] == '<' ){PRINT(":<") // <
                if(line[i+1] == '/'){ lexq.push_back({tok::ltEnd,""});i++;continue;};
                if(line[i+1] == '!'){size_t pos = line.find(">",i+1);
                    if(pos){i=pos;continue;}
                    else{
                        lexq.push_back({tok::com , ""});break;
                    };
                };
                if(lexq.back().t == tok::elval){
                        PRINTQ(lexq)
                        const std::string s = lexq.back().d;
                        const eltree::element  el= eltree::element(s) ;
                        cur->value.push_back(eltree::element(el));
                        PRINT(";<")
                        lexq.pop_back();
                };
                PRINT(";<")
                const eltree::element el= eltree::element(cur);
                cur->value.push_back(el);
                cur = const_cast<eltree*>(cur->value.back().d.child) ;
                lexq.push_back({tok::lt,"<"});
                continue;
            };
            auto ltHandle = [&](list<lexe>::iter it){
                list<lexe>::iter k = lexqfind(tok::name, it);
                if(k){cur->name = k->d ;
                    while(k){
                        k = lexqfind(tok::eqs, k);
                        if(k){cur->attributes.push_back({ (j-1)->d,(j+1)->d});k=j+1;}
                    };
                }; }
                else {lexq.push_back({tok::el,""});};
                lexq.erase(it,lexq.end());
            };
            if(line[i] == '/' && line[i+1]=='>'){PRINT(":/>") // />
                list<lexe>::iter pos = lexqrfind(tok::lt , lexq.end()-1);
                if(pos){ltHandle(pos);};              
                cur = cur->parent; 
                i++;
                lexq.push_back({tok::el,cur->name});
                continue;
            };
            if(line[i] == '>' ){PRINT(":>") // >
            
                PRINTQ(lexq)
                
                for(list<lexe>::iter ite=lexq.end() ; ite;--ite) { PRINT("loop")
                    switch(ite->t){
                        case tok::lt : { 
                            ltHandle(ite);
                            lexq.push_back({tok::elStart,cur->name});
                            lexq.push_back({tok::elval,""});
                            break;                            
                        };
                        case tok::ltEnd :{
                            list<lexe>::iter k = lexqfind(tok::name , ite);
                            if(k){
                                PRINT("curName:"<<cur->name << " "<< (ite+1)->d<< " ")
                                    int s = cur->parent->value.size()-1;
                                    std::string estr = k->d;std::string dstr;
                                    while(!( (estr==dstr) and (cur->name==estr) )){                                          
                                        if(cur->name == estr){
                                             k = lexqrfind(tok::elStart, k-1);
                                            //  int j = lexqfind(tok::elval,k);
                                            //  while(j){cur->data.value.push_back(lexq[j].d);
                                            //          j = lexqfind(tok::elval,j);};
                                            if(k){
                                                dstr = k->d;
                                                lexq.erase(k,lexq.end());
                                                if(dstr == estr){break;};
                                            }
                                            else {lexq.erase(ite,lexq.end());break;};
                                        }
                                        else {
                                            if(cur!=(cur->parent->value.front().d.child)){
                                                list<eltree::element>::iter el = cur->parent->value.end()-1;
                                                while(el->t != 1){--el;};
                                                cur=const_cast<eltree*>(el->d.child);}
                                            else{cur=cur->parent;                                                                                              
                                                list<eltree::element>::iter el=cur->parent->parent->value.end()-1;
                                                while(el->t != 1){--el;};
                                            };
                                        }                                    
                                    }
                            }
                            else {k = lexqrfind(tok::elStart,ite); if(k){  lexq.erase(k,lexq.end());};};
                            lexq.push_back({tok::elval,""});
                            cur = cur->parent; 
                            PRINTQ(lexq)
                            break;
                        };
                        
                    };
                    if(lexq.back().t == tok::elStart or (lexq.back().t == tok::el)){break;};
                };
                continue;
            };
            // if(lexq.size()==0){continue;};
            if(isspace(line[i])){ PRINT("S")
                switch(lexq.back().t){
                    case tok::elval : {lexq.back().d+=line[i];continue;};
                    case tok::value : {lexq.push_back({tok::sp,""});continue;};
                    case tok::name : {lexq.push_back({tok::sp,""});continue;};
                    case tok::sp : {continue;};
                };
                continue ;
            }
            else {PRINT("Ns")
                switch(lexq.back().t){
                    case tok::sp : {lexq.pop_back();lexq.push_back({tok::id,std::string()+line[i]});continue;}
                    case tok::id : {lexq.back().d+=line[i];continue;};
                    case tok::eqs : { lexq.push_back({tok::value,""});continue;};
                    case tok::lt : {lexq.push_back({tok::name,std::string()+line[i]});continue;};
                    case tok::name : {lexq.back().d+=line[i];continue;};
                    case tok::value : {lexq.back().d+=line[i];continue;};
                    case tok::elval : {lexq.back().d+=line[i];continue;};
                    case tok::ltEnd : {lexq.push_back({tok::name,std::string()+line[i]});continue;};
                };
                continue;
            };
        };
    };
    
    std::string line;
    std::ifstream* file;
    bool feed(){
        if(std::getline(*file,line)){
            feed(line);
            return true;
        }
        return false;
    };
    void parse(std::string filestr){
        std::ifstream fi(filestr) ;
        file =&fi;
        while(feed());
    };
    void funcFeed(void (*funct)(xmlParser*) , std::ifstream& filein){
        file =&filein;
        while(feed()){
            funct(this);
        };
      
    };
/*
    class pattern {

    };
    
    std::vector<T> pattern(pattern p, void (*cb)() ) {

    };
*/


    void print(const eltree* el , size_t space){ 
        auto l = [](size_t space){
            std::string s ;
            for(int i = 0 ; i < space;i++){
                s+=" ";
            };
            return s;
        };
        size_t spacesi = space ;
        std::string sp = l(spacesi); 
        std::cout<<sp<<"name:("<<el->name<<")"<<std::endl<<sp<<"ats:";
        for(const attribute& it : el->attributes){
            std::cout<<it.first<<"="<<it.second<<" ";
        };
        if(el->value.size()>0){
            std::cout<<std::endl<<sp<<"childs:"<<std::endl;
        spacesi+=4;
        for(const eltree::element& it : el->value){if(it.t == 1){print((it.d.child),spacesi);};};
        std::cout<<std::endl;
    };};
    void print(const eltree* el){
        print(el,0);
    };
    void printTree(const eltree* el){
            std::cout<<"<"<<el->name<<" ";
            for(const attribute& at : el->attributes){
                std::cout<<at.first<<"="<<at.second<<" ";  };
            std::cout<<">";int i=0;
            for(const eltree::element& it : el->value){
                if(it.t == 0){
                    std::cout<<it.d.str;
                }
                else printTree((it.d.child));
            };
            std::cout<<"</"<<el->name<<">"<<std::endl;
};
    void write(const eltree* el,std::ofstream& file){
        file<<std::endl<<"<"<<el->name;
        for(const attribute& at : el->attributes  ){file<<" "<<at.first<<"="<<at.second;};
        file<<">";

        for(const eltree::element it : el->value){
            if(it.t == 0){file<<it.d.str;}
            else {write(it.d.child,file);}
        };
        file<<"</"<<el->name<<">";
    };
    void write(std::string filein){
        std::ofstream f(filein);
        write(&tree,f);
    };

    void searchFile();// TOOD
    // xmlParser(xmlParser& p) : cur() {};

};

/*
class xmlVariant {
    enum class var {
        number, 
        str, 
        reference,
        array
    };

};

class xmlLibrary {


    class value {
        public:
        static auto v;
        auto (*set)(std::string );
        auto (*get)(value*);

        auto getter() final {get(this);};
    };
    class attribute {
        std::string name ; 
        
    };
    class element {
        std::string name ;
        std::vector<attributes> values;
    };

    virtual void parse(xmlParser::eltree& element){

    };
    void parse(xmlParser* p)final{
        parse(p->cur);
    };
    void feed()final {
        xmlParser p ; 
        p.funcFeed(&parse);
    };
};
*/
#endif