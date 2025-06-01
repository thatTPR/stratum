#ifndef ACQXML_CPP
#define ACQXML_CPP
#include <string>
#include <vector>
#include <stdint.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <petri/list.hpp>
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
            eltree* child;
            elu() {};
            elu(std::string& st) : str(st) {};
            elu(eltree* ch) : child(ch) {};
            
            ~elu() {delete this;};
        };
        struct element {
            int8_t t ; // 0:str , 1: el
            elu d;
            element(const element& el) : t(el.t){
                if(t==0){d.str=el.d.str;}
                else {d.child = el.d.child;}
            };
            element(const std::string str) {
                t = 0;d.str = str;
            };
            element(eltree* child) {
                t=1;d.child= child;
            };
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
            if(it.t==1){res = it.d.child;return true;};
        };
        return false;
    };
    
   
    bool getChildByName(eltree& el , std::string name , eltree* res){
        for(int i = 0 ;  i < el.value.size();i++){
            if(el.value[i].t==0){continue;};
            if(el.value[i].d.child->name == name){
                res = (el.value[i].d.child);
                return true ;
            };
        };
        return false;
    };
    std::vector<eltree> getChildsByName(eltree& el ,std::string name){
        std::vector<eltree> res;
        for(int i = 0 ;  i < el.value.size();i++){
            if(el.value[i].t == 0){continue;};
            if(el.value[i].d.child->name == name){
                res.push_back(*(el.value[i].d.child));
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
   
    list<lexe> lexq{{tok::elval,std::string("&lt/&gt")}};

    int lexqfind(tok t,int s){    
        list<lexe>::node* cur=lexq.first;int i;
        for( i = 0 ; i<= s;i++){    cur =cur->next;};
        for(int i = s; i<lexq.size() ;i++){
            if(cur->cur.t  == t){return i;};
            cur = cur->next;
        };
        return 0;
    };
    int lexqrfind(tok t, int s){
        list<lexe>::node* cur=lexq.last;int i;
        for( i = lexq.size()-1 ; i>=0;i--){    cur =cur->prev;};
        for(int i = s; i<lexq.size() ;i--){
            if(cur->cur.t  == t){return i;};
            cur = cur->prev;
        };
        return 0;
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
        list<lexe>::node* cur = q.first;
        int size = q.size();

        while(size>0){
            std::cout<<get(cur->cur.t)<<" ";
            cur=cur->next;
            size--;
        };
        std::cout<<std::endl;
    };
    int depth(){
        eltree* current = cur ;
        int i=0;
        while(current->name != std::string()){
            current = current->parent;
            i++;
        };
        return i;
    };
    int lexDepth(){int i = lexqrfind(tok::elStart,lexq.size()-1); int j = 1;
        if(!i){return 0;};
        while( i ){ i= lexqrfind(tok::elStart,i) ; j++;};
        return j;
    };
    bool Strb = false;bool instart; bool inval=false; bool inel=false; bool inclose=false;
    std::string stri ;
    void feed(std::string& line){
        PRINT(std::endl<<"feed: "<<line<<std::endl)
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
                        lexq.push_back({tok::com , ""});
                    };
                };
                if(lexq.size()>0 and (lexq.back().t == tok::elval)){
                        PRINTQ(lexq)
                        const std::string s = lexq.back().d;
                        const eltree::element  el= eltree::element(s) ;
                        cur->value.push_back(el);
                        PRINT(";<")
                        lexq.pop_back();
                };
                PRINT(";<")
                const eltree::element el= eltree::element(cur);
                cur->value.push_back(el);
                cur = (cur->value.back().d.child) ;
                lexq.push_back({tok::lt,"<"});
                continue;
            };
            auto ltHandle = [&](int it){
                int k = lexqfind(tok::name, it);
                if(k){cur->name = lexq[k].d ;
                for(; k  < lexq.size()-1 ; k++){
                    int j = lexqfind(tok::eqs, k);
                    if(j){cur->attributes.push_back({lexq[j-1].d,lexq[j+1].d});k=j+1;}
                    else {break;}
                }; }
                else {lexq.push_back({tok::el,""});};
                lexq.erase(lexq.end()-(lexq.size()-it),lexq.end());
            };
            if(line[i] == '/' && line[i+1]=='>'){PRINT(":/>") // />
                int it ; 
                int pos = lexqrfind(tok::lt , lexq.size()-1);
                if(pos){
                    ltHandle(pos);
                }              
                cur = cur->parent; 
                i++;
                lexq.push_back({tok::el,cur->name});
                continue;

            };
            if(line[i] == '>' ){PRINT(":>") // >
            
                int it;
                PRINTQ(lexq)
                for(it=lexq.size()-1 ; it>=0;it--){ PRINT("loop");
                    switch(lexq[it].t){
                        case tok::lt : { 
                            ltHandle(it);
                            lexq.push_back({tok::elStart,cur->name});
                            lexq.push_back({tok::elval,""});
                                break;                            
                        };
                        case tok::ltEnd :{
                            int k = lexqfind(tok::name , it);
                            if(k){
                                PRINT("curName:"<<cur->name << " "<< lexq[it+1].d<< " ")
                                    int s = cur->parent->value.size()-1;
                                    std::string estr = lexq[it+1].d;std::string dstr;
                                    while(!( (estr==dstr) and (cur->name==estr) )){                                          
                                        if(cur->name == estr){
                                             k = lexqrfind(tok::elStart, k-1);
                                            //  int j = lexqfind(tok::elval,k);
                                            //  while(j){cur->data.value.push_back(lexq[j].d);
                                            //          j = lexqfind(tok::elval,j);};
                                            if(k){
                                                dstr = lexq[k].d;
                                                lexq.erase(lexq.end() - (lexq.size()-k),lexq.end());
                                                if(dstr == estr){break;};
                                            }
                                            else {lexq.erase(lexq.end() - (lexq.size()-it),lexq.end());break;};
                                        }
                                        else {
                                            if(cur!=(cur->parent->value.front().d.child)){
                                                while(cur->parent->value[s].t != 1){s--;};
                                                cur=(cur->parent->value[s].d.child);}
                                            else{cur=cur->parent;                                                                                              
                                                s=cur->parent->parent->value.size()-1;
                                                while(cur->parent->parent->value[s].t != 1){s--;};
                                            };
                                        }
                                
                                        if(cur->name == std::string()){
                                            lexq.erase(lexq.begin(),lexq.end());
                                            int l=tree.value.size()-1; 
                                            while(tree.value[i].t != 1){l--;};
                                            cur = (tree.value[i].d.child) ;
                                            while(cur->value.size()>0){
                                                lexq.push_back({tok::elStart,cur->name});
                                                l = cur->value.size()-1;
                                                while(cur->value[l].t != 1){l--;};
                                                cur = (cur->value[l].d.child);
                                            };
                                            break;
                                        };
                                    
                                    }
                            }
                            else {k = lexqrfind(tok::elStart,it); if(k){  lexq.erase(lexq.end()-(lexq.size()-k),lexq.end());};};
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
            

            if(lexq.size()==0){continue;};
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
std::getline(       fi,line);
std::cout<<line<<std::endl ;
bool doct;
        if  (line.find("<!")){
                doct=true;
                size_t pos = line.find(">") ;
                if(pos){doct = true;};
        };
        if(!doct) {feed(line);}
            
    
        while(!fi.eof()){
            line=std::string();
std::getline(       fi,line); 
            feed(line);
        };
    };
    void funcFeed(void (*funct)(xmlParser*) , std::ifstream& filein){
        file =&filein;
        feed();
        PRINT("func"<<line<<std::endl);

        bool doct;
        if  (line.find("<!")){
            doct = true;
                size_t pos = line.find(">") ;
                if(pos ){doct = true;};
        }
        if(!doct) {feed();}

        do{
            funct(this);
        }while(!feed());
      
    };
    void print(eltree* el , size_t space){ 
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
        for(int i = 0 ; i<el->attributes.size();i++){
            std::cout<<el->attributes[i].first<<"="<<el->attributes[i].second<<" ";
        };
        if(el->value.size()>0){
            std::cout<<std::endl<<sp<<"childs:"<<std::endl;
        spacesi+=4;
        for(int i =0 ; i < el->value.size();i++){if(el->value[i].t == 1){print((el->value[i].d.child),spacesi);};};
        std::cout<<std::endl;
    };};
    void print(eltree* el){
        print(el,0);
    };
    void printTree(eltree* el){
            std::cout<<"<"<<el->name<<" ";
            for(int i =0 ;i < el->attributes.size();i++){
                std::cout<<el->attributes[i].first<<"="<<el->attributes[i].second<<" ";  };
            std::cout<<">";int i=0;
            for(auto it : el->value){
                if(it.t == 0){
                    std::cout<<it.d.str;
                }
                else printTree(it.d.child);
            };
            std::cout<<"</"<<el->name<<">"<<std::endl;
};
    void write(eltree* el,std::ofstream& file){
        file<<std::endl<<"<"<<el->name;
        for(std::pair<std::string,std::string> at : el->attributes  ){file<<" "<<at.first<<"="<<at.second;};
        file<<">";

        for(auto it : el->value){
            if(it.t == 0){file<<it.d.str;}
            else {
                write(it.d.child,file);
            }
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