#ifndef ACQXML_CPP
#define ACQXML_CPP
// #define MACROSP
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
#include <algorithm>
#include <string>
#include <sstream>
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
 //   const std::string lt = "<";
 //   const std::string gt = ">";
      const std::string amp = "&";

     typedef std::pair<std::string ,std::string > attribute;



    class eltree  {
        public:
        eltree* parent;
        std::string name ;
        struct element {
            std::string str;
            eltree* child;
            
            element(const element& el)  {
                str = el.str;
                child= el.child;}
            element( element& el)  {
                str = el.str;
                child= el.child;}
        
            element(const std::string& _str) { str = _str ;};
            element( std::string& _str) { str = _str  ;};
            element( eltree* _child) { child = _child ;};
        };
        
        std::vector<attribute> attributes ;
        std::string str;
        list<element> value ;
        void clear(){
            eltree* el ;
            for(element& it : value){
                it.child->clear();
                it.str.clear();
            };
            name.clear();
            attributes.clear();
        };
        eltree() {};
        eltree(const eltree& _Et) : parent(_Et.parent),name(_Et.name),attributes(_Et.attributes) , value(_Et.value) {};
        
    };
    eltree tree ;
    bool val(eltree& el,std::string* res,int pos=0){
        for(const eltree::element& it : el.value){
            *res = it.str;return true;
        };
        return false;
    };
    bool val(eltree& el,eltree* res,int pos=0){
        for(const eltree::element& it : el.value){
            res =(it.child);
        };
        return false;
    };
    
   
    bool getChildByName( const eltree* el , std::string name , eltree** res){
        for(const eltree::element& it : el->value){
            if(it.child->name == name){
                *res = (it.child);
                return true ;
            };
        };
        return false;
    };
    std::vector<eltree*> getChildsByName(const eltree* el ,std::string name){
        std::vector<eltree*> res;
        for(const eltree::element& it : el->value){
            if(it.child->name == name){
                res.push_back(it.child);
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
        sp=0,
        lt=1,
        gt=2,
        quotOpen=3,
        apostOpen=4,
        value=5,
        ltEnd=6,
        gtEnd=7,
        eqs=8,
        name=9,
        id=10,
        elStart=11,
        elval=12,
        el=13,
        com=14
    };
    struct lexe {
        tok t;
        std::string d;
        lexe() {};
        lexe(lexe& l) : t(l.t)  {
            d = std::string(l.d);
        };
        lexe(const lexe& l) : t(l.t)  {
            d = std::string(l.d);
        }

        lexe(tok et,std::string ds){t=et;d=ds;};
        
        // lexe(tok et,std::string& ds){t=et;d=ds;};
    };
   
    list<lexe> lexq ;
    xmlParser(){tree.name = "root";  lexq.push_back({tok::el,std::string("root")});}
    list<lexe>::iter lexqfind(tok t,list<lexe>::iter s){
        for(list<lexe>::iter c(s); c; ++c){
            if(c->t  == t){return c;}
        };
        return lexq.end();
    };
    list<lexe>::iter lexqrfind(tok t, list<lexe>::iter s ){
 
        for(list<lexe>::iter c(s); c ; --c ){
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
    int lexDepth(){ list<lexe>::iter i = lexqrfind(tok::elStart,lexq.rbegin()); int j = 1;
        if(!i){return 0;};
        while( i ){ i= lexqrfind(tok::elStart,i) ; j++;};
        return j;
    };
    bool Strb = false;
   
    void feed(std::string& line){
        PRINT(std::endl<<"feed: "<<line<<std::endl)
        PRINT("LS:"<<lexq.size()<<std::endl)
        PRINTQ(lexq)
        for(int i = 0 ; i < line.size();i++){
            if(lexq.back().t == tok::com){
                size_t pos = line.find(">");
                if(pos){lexq.pop_back();i = pos;continue;}
                else break;};
            auto lval = [&](size_t p){
                std::string str;
                    if(p != std::string::npos){str = line.substr(i,p-i+1) ; i = p;}
                    else {
                        Strb = true;
                        str = line.substr(i);
                    };
                    switch(lexq.back().t ){
                        case tok::elval : {lexq.back().d+=line[i]+str;break;}
                        case tok::eqs : {lexq.push_back({tok::value,line[i]+str});break;}
                        case tok::el : {lexq.push_back({tok::elval,line[i]+str});break;}
                        case tok::value : {lexq.back().d+=line[i]+str;break;};
                    };                    
            };
            if(Strb == true){
                std::string str; size_t p ; 
                switch(lexq.back().d.front()) {
                    case '\'' : {p =  line.find("\'");};
                    case '"' : {p = line.find("\"");};
                };
                if(p != std::string::npos){str = line.substr(0,p); Strb = false;}
                else {str = line; }   
                lexq.back().d+=str;
                continue ;
            };
            if(line[i]== '"'){PRINT(":\"")
                size_t p = line.find("\"",i+1);
                lval(p);
                continue;
            };
            if(line[i] == '\'' ){PRINT(":'")
                size_t p = line.find("\'",i+1);
                lval(p);
                continue;
            };
            if(line[i]== '='){PRINT(":=")
                if(lexq.back().t == tok::elval ){lexq.back().d+=line[i];continue;};
                if(lexq.back().t == tok::elStart){lexq.push_back({tok::elval,std::string()+line[i]});continue;};
                lexq.push_back({tok::eqs,eq});
                continue ;
            };
            if(line[i] == '<' ){PRINT(":<") // <
                if(line[i+1] == '/'){ 
                    if(lexq.back().t == tok::elval){
                        if(cur->value.empty()){cur->str = lexq.back().d;}
                        else {cur->value.back().str =lexq.back().d;}
                        lexq.pop_back();};
                    lexq.push_back({tok::ltEnd,std::string()});i++;continue;};
                if(line[i+1] == '!'){size_t pos = line.find(">",i+1);
                    if(pos){i=pos;continue;}
                    else{
                        lexq.push_back({tok::com , std::string()});break;
                    };
                };
                if(lexq.back().t == tok::elval){
                        // eltree::element el(lexq.back().d); 
                        if(cur->value.empty()){cur->str = lexq.back().d;}
                        else {cur->value.back().str=lexq.back().d;}
                        PRINT(";<")
                        lexq.pop_back();
                };
                PRINT(";<")
                eltree* el= new eltree();
                el->parent  = cur;
                cur->value.push_back(el);
                cur = el ;
                lexq.push_back({tok::lt,std::string("<")});
                continue;
            };
            auto ltHandle = [&](list<lexe>::iter it){
                list<lexe>::iter k = lexqfind(tok::name, it);
                if(k){cur->name = k->d ;
                    while(k){
                        k = lexqfind(tok::eqs, k);
                        list<lexe>::iter prev = k;
                        list<lexe>::iter next = k;
                        if(k){cur->attributes.push_back({ (prev--)->d,(next++)->d});++k;}
                    };
                }; 
                lexq.erase(it,lexq.end());
            };
            if(line[i] == '/' && line[i+1]=='>'){PRINT(":/>") // />
                list<lexe>::iter pos = lexqrfind(tok::lt , lexq.rbegin());
                if(pos){ltHandle(pos);};              
                cur = cur->parent; 
                i++;
                continue;
            };
            if(line[i] == '>' ){PRINT(":>") // >
                PRINTQ(lexq)
                for(list<lexe>::iter ite=lexq.rbegin() ; ite;--ite) { PRINT("loop")
                    switch(ite->t){
                        case tok::lt : { 
                            ltHandle(ite);
                            lexq.push_back({tok::elStart,cur->name});
                            lexq.push_back({tok::elval,std::string()});
                            ite=lexq.begin() ;break;                            
                        };
                        case tok::ltEnd :{
                            list<lexe>::iter k = lexqfind(tok::name , ite);
                            if(k){
                                PRINT("curName:"<<cur->name << " "<< k->d<< " ")
                                    std::string estr = k->d; 

                                    for( ;k and !(k->t == tok::elStart and k->d == estr);--k){};
                                    if(k){lexq.erase(k,lexq.end());}
                                    else break;
                                    for(list<eltree::element>::iter el = cur->parent->value.rbegin();
                                    cur->name!=estr ;--el ){
                                        if(!el){cur=cur->parent; el = cur->parent->value.rbegin();};
                                        if(el->child->name == estr){
                                            cur = el->child;
                                        }                                        
                                    };
                                    
                                    
                            }
                            else {k = lexqrfind(tok::elStart,ite); if(k){  lexq.erase(k,lexq.end());};};
                            lexq.push_back({tok::elval,std::string()});
                            cur = cur->parent; 
                            PRINTQ(lexq)
                            ite=lexq.begin();break;
                        };
                        
                    };
                    if(lexq.back().t == tok::elStart or (lexq.back().t == tok::el)){break;};
                };
                continue;
            };
            // if(lexq.size()==0){continue;};
            if(isspace(line[i])){ PRINT("S")
                switch(lexq.back().t){
                    case tok::elval : {lexq.back().d+=line[i];break;};
                    case tok::value : {lexq.push_back({tok::sp,std::string()});break;};
                    case tok::name : {lexq.push_back({tok::sp,std::string()});break;};
                };
                continue ;
            }
            else {PRINT("Ns")
                switch(lexq.back().t){
                    case tok::sp : {lexq.pop_back();lexq.push_back({tok::id,std::string()+line[i]});break;}
                    case tok::id : {lexq.back().d+=line[i];break;};
                    case tok::eqs : { lexq.push_back({tok::value,std::string()+line[i]});break;};
                    case tok::lt : {lexq.push_back({tok::name,std::string()+line[i]});break;};
                    case tok::name : {lexq.back().d+=line[i];break;};
                    case tok::value : {lexq.back().d+=line[i];break;};
                    case tok::elval : {lexq.back().d+=line[i];break;};
                    case tok::ltEnd : {lexq.push_back({tok::name,std::string()+line[i]});break;};
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
        file = new std::ifstream(filestr) ;
        while(feed());
    };

   
    void funcFeed(void (*funct)(xmlParser*)){
          while(feed()){
            funct(this);
        };
    };
    void funcFeed(void (*funct)(xmlParser*) , std::ifstream& filein){
        file = &filein ;    
        funcFeed(funct);
    };
    void funcFeed(void (*funct)(xmlParser*) , std::string filein){
        file = new std::ifstream(filein);
        if(file->is_open()){
            std::cout<<"Opened File:"<<filein;
        }
        else{std::cout<<"failed to open file";};
        funcFeed(funct);    

    };
    void parseStr(std::string xml){
        std::stringstream s(xml); 
        while(std::getline(s,line)){
            feed(line);
        };
    };
    template <typename T>
    class pattern{
        public:
        xmlParser* p;
        eltree* pat;
        const std::string var = "$val"; // Followed by number giving index of ptr->to member
        const std::string iterate = "$iter"; // // Followed by number giving index of ptr->to member
        const std::string opor =  "&|";
        size_t patSize =0 ; 
        size_t matches = 0 ;
        void (*funct)(int,std::string s, T*  ) ;
        int stoit(std::string& s){
            int i = 0 ;
            for(char c : s){
                int d = c-'0';
                i=i*10+d;
            } 
            return i;
        };  
        
        
        bool dfsmatch(list<eltree::element>::iter el, list<eltree::element>::iter patt,T* res){
            if(!patt  ){return true;}
            if(!el){return false;}
            if(el->child->name != patt->child->name){return false;};
            bool iter = false;
            if(!patt->child->value.empty()){
                if(!patt->child->attributes.empty()){
            if( patt->child->attributes.back().first == iterate){iter=true;
                funct(stoit(patt->child->attributes.back().second),std::string(),res);
            };};
                if(el->child->value.empty()){return false;};
                list<eltree::element>::iter patIter = patt->child->value.begin();
                list<eltree::element>::iter elIter = el->child->value.begin(); 
                if(!dfsmatch(elIter,patIter,res)){return false;};
            }
            if(!patt->child->attributes.empty()){;
            if( patt->child->attributes.back().first == iterate){
                if(!iter){
                    int num = stoit(patt->child->attributes.back().second);
                    funct(num,std::string(),res);
                };
                iter=true;
                list<eltree::element>::iter patIter = patt;
                list<eltree::element>::iter elIter = el; ++elIter;
                if(elIter){if(!dfsmatch(elIter,patIter,res)){return false;}}
                else return true;
            }
            else if(patt->child->attributes.back().first == var){
                int num = stoit(patt->child->attributes.back().second);
                std::string value =el->str;
                value+=el->child->str;
                for(eltree::element& it: el->child->value){
                value+=it.str;}
                funct(num,value,res);}
            };
            
                if(!iter){
                list<eltree::element>::iter  patti= patt;
                list<eltree::element>::iter eli= el;
                ++eli;++patti;
                if(eli ) {if(!dfsmatch(eli,patti,res)){return false;}}
                else if(patti){return false;}

            }
            return true;
        };      
        bool matchPat( T* res, list<eltree::element>::iter& l){
            
            list<eltree::element>::iter last = l;
                       
            list<eltree::element>::iter patlast = pat->value.begin();
            if(!last){return false;};
            
            if(last->child->name == patlast->child->name ){
                bool s  = dfsmatch(last,patlast,res);
                if(s){
                    return true;}
                else return false; 
            };
            return false;
    };
        pattern(std::string xml , void (*f)(int,std::string,T* tb) ){
            funct = f;
            p = new xmlParser();
            p->parseStr(xml);
            pat = &p->tree;
            patSize = 0;
            for( eltree::element& it : pat->value  ){patSize++;}
        };
    };
 
    bool open(list<eltree::element>::iter el){
        if(el.next()){return false;};
        list<lexe>::iter s = lexqrfind(tok::elStart,lexq.rbegin());
        std::string parentName = el->child->parent->name;
        for(;s;--s){
            if(s->t == tok::elStart){
                if(s->d == el->child->name){return parentName == s.prev()->d? true : false;}
            }
        }
        return false;
    };
     bool lastEl(list<eltree::element>::iter el){
        bool op = open(el);
        if(op){
                for(bool fd = feed();open(el); fd=feed()){};
            if(el.next())return false;
            else return true;
        }
        else {
            if(el.next())return false;
            else return true;
        }
    };

    template <typename Ty>
    void match(std::vector<pattern<Ty>>& pats,list<eltree::element>::iter l , void (*cb)(Ty) ){        
        list<eltree::element>::iter ls = l;
        for(;ls;++ls){
            for(bool fd=feed();ls->child->name.length()==0 and fd ; fd=feed()){};
            bool childsnfed= true;          
            list<eltree::element>::iter last = ls;  
            for(pattern<Ty>& it : pats){  
            size_t sc=1;
            last = ls;list<eltree::element>::iter lasts = last;
            for(;last and sc<=it.patSize ;++last){lasts = last;sc++;};
            last = lasts;
            for( bool fd = feed();sc<it.patSize and !lastEl(last) and fd;fd = feed() ){ 
                 if(!ls->child->value.empty() and childsnfed  ){
                    list<eltree::element>::iter lastc = ls->child->value.begin();
                    match<Ty>(pats,lastc,cb);childsnfed = false;
                }
                if( it.pat->value.front().child->name != ls->child->name){break;};
                sc=1; last = ls; list<eltree::element>::iter lasts = last;
                for(;last and sc<=it.patSize ;++last){lasts = last;sc++;};
                last = lasts;
            };
            bool found = false;
            if(sc>= it.patSize and it.pat->value.front().child->name == ls->child->name){
                if(last){
                    Ty res;
                    if(it.matchPat(&res,ls)){cb(res); found = true;break;};}}
                    if(found)break;
            };   
            if(!ls->child->value.empty() and childsnfed  ){
                    list<eltree::element>::iter lastc = ls->child->value.begin();
                    match<Ty>(pats,lastc,cb); childsnfed =false;
            };
            
    };
};
   
    template <typename T>
    void feed(std::vector<pattern<T>>& pat, void (*cb)(T), std::ifstream& filein){ 
        file = &filein;
        list<eltree::element>::iter last = tree.value.begin();
        while(feed()){
            if(tree.value.size()>0){
                last = tree.value.begin();
                if(last)break;
            }
        };
        // list<eltree::element>::iter parent(eltree::element(&tree));
        match<T>(pat,last,cb);
    };

    template <typename T>
    void feed(pattern<T>& pat, void (*cb)(T),std::ifstream& filein){
        std::vector<pattern<T>> p  = {pat};
        feed<T>(p,cb,filein);
    };
 
    




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
        for(const eltree::element& it : el->value){print((it.child),spacesi);};};
        std::cout<<std::endl;
    };
    void print(const eltree* el){
        print(el,0);
    };
    void printTree(const eltree* el){
            std::cout<<"<"<<el->name;
            for(const attribute& at : el->attributes){
                std::cout<<" "<<at.first<<"="<<at.second;  };
            std::cout<<">";int i=0;
            for(const eltree::element& it : el->value){
                std::cout<<it.str;
                printTree((it.child));
                
            };
            std::cout<<"</"<<el->name<<">"<<std::endl;
};
    void write(const eltree* el,std::ofstream& file){
        file<<std::endl<<"<"<<el->name;
        for(const attribute& at : el->attributes  ){file<<" "<<at.first<<"="<<at.second;};
        file<<">";

        file<<el->str;
        for(const eltree::element& it : el->value){
            file<<it.str;
             write(it.child,file);
        };
        file<<"</"<<el->name<<">";
    };
    void write(std::string filein){
        std::ofstream f(filein);
        write(&tree,f);
    };

    void searchFile();// TOOD
    // xmlParser(xmlParser& p) : cur() {};
    ~xmlParser(){
        lexq.clear();
        tree.clear();
    }
};


template <typename... Tags>
struct xmlLib : xmlParser {
    template <typename T>
    struct tag {
        T data;
        std::string name ;
        virtual void parse(xmlParser::eltree& tree);
        virtual void write(xmlParser::eltree& tree);
    };

    template <typename ... Args>
    using elems = tuple<tag<Args>...> ;

    elems<Tags...> tags;

    void parse();
    void updateTree(){

    };
    void write(std::ofstream& file){
        write(&tree,file)
    };


    // Tuple of tags;
}
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