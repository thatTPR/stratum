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
#define NSC pri::
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
        NSC list<element> value ;
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
   
    NSC list<lexe> lexq ;
    xmlParser(){tree.name = "root";  lexq.push_back({tok::el,std::string("root")});}
    NSC list<lexe>::iter lexqfind(tok t,NSC list<lexe>::iter s){
        for(NSC list<lexe>::iter c(s); c; ++c){
            if(c->t  == t){return c;}
        };
        return lexq.end();
    };
    NSC list<lexe>::iter lexqrfind(tok t, NSC list<lexe>::iter s ){
 
        for(NSC list<lexe>::iter c(s); c ; --c ){
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
    void print(NSC list<lexe>& q){
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
    int lexDepth(){ NSC list<lexe>::iter i = lexqrfind(tok::elStart,lexq.tail()); int j = 1;
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
            auto ltHandle = [&](NSC list<lexe>::iter it){
                NSC list<lexe>::iter k = lexqfind(tok::name, it);
                if(k){cur->name = k->d ;
                    while(k){
                        k = lexqfind(tok::eqs, k);
                        NSC list<lexe>::iter prev = k;
                        NSC list<lexe>::iter next = k;
                        if(k){cur->attributes.push_back({ (prev--)->d,(next++)->d});++k;}
                    };
                }; 
                lexq.erase(it,lexq.end());
            };
            if(line[i] == '/' && line[i+1]=='>'){PRINT(":/>") // />
                NSC list<lexe>::iter pos = lexqrfind(tok::lt , lexq.tail());
                if(pos){ltHandle(pos);};              
                cur = cur->parent; 
                i++;
                continue;
            };
            if(line[i] == '>' ){PRINT(":>") // >
                PRINTQ(lexq)
                for(NSC list<lexe>::iter ite=lexq.tail() ; ite;--ite) { PRINT("loop")
                    switch(ite->t){
                        case tok::lt : { 
                            ltHandle(ite);
                            lexq.push_back({tok::elStart,cur->name});
                            lexq.push_back({tok::elval,std::string()});
                            ite=lexq.begin() ;break;                            
                        };
                        case tok::ltEnd :{
                            NSC list<lexe>::iter k = lexqfind(tok::name , ite);
                            if(k){
                                PRINT("curName:"<<cur->name << " "<< k->d<< " ")
                                    std::string estr = k->d; 

                                    for( ;k and !(k->t == tok::elStart and k->d == estr);--k){};
                                    if(k){lexq.erase(k,lexq.end());}
                                    else break;
                                    for(NSC list<eltree::element>::iter el = cur->parent->value.tail();
                                    cur->name!=estr ;--el ){
                                        if(!el){cur=cur->parent; el = cur->parent->value.tail();};
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
        
        
        bool dfsmatch(NSC list<eltree::element>::iter el, NSC list<eltree::element>::iter patt,T* res){
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
                NSC list<eltree::element>::iter patIter = patt->child->value.begin();
                NSC list<eltree::element>::iter elIter = el->child->value.begin(); 
                if(!dfsmatch(elIter,patIter,res)){return false;};
            }
            if(!patt->child->attributes.empty()){;
            if( patt->child->attributes.back().first == iterate){
                if(!iter){
                    int num = stoit(patt->child->attributes.back().second);
                    funct(num,std::string(),res);
                };
                iter=true;
                NSC list<eltree::element>::iter patIter = patt;
                NSC list<eltree::element>::iter elIter = el; ++elIter;
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
                NSC list<eltree::element>::iter  patti= patt;
                NSC list<eltree::element>::iter eli= el;
                ++eli;++patti;
                if(eli ) {if(!dfsmatch(eli,patti,res)){return false;}}
                else if(patti){return false;}

            }
            return true;
        };      
        bool matchPat( T* res, NSC list<eltree::element>::iter& l){
            
            NSC list<eltree::element>::iter last = l;
                       
            NSC list<eltree::element>::iter patlast = pat->value.begin();
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
 
    bool open(NSC list<eltree::element>::iter el){
        if(el.next()){return false;};
        NSC list<lexe>::iter s = lexqrfind(tok::elStart,lexq.tail());
        std::string parentName = el->child->parent->name;
        for(;s;--s){
            if(s->t == tok::elStart){
                if(s->d == el->child->name){return parentName == s.prev()->d? true : false;}
            }
        }
        return false;
    };
     bool lastEl(NSC list<eltree::element>::iter el){
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
    void match(std::vector<pattern<Ty>>& pats,NSC list<eltree::element>::iter l , void (*cb)(Ty) ){        
        NSC list<eltree::element>::iter ls = l;
        for(;ls;++ls){
            for(bool fd=feed();ls->child->name.length()==0 and fd ; fd=feed()){};
            bool childsnfed= true;          
            NSC list<eltree::element>::iter last = ls;  
            for(pattern<Ty>& it : pats){  
            size_t sc=1;
            last = ls;NSC list<eltree::element>::iter lasts = last;
            for(;last and sc<=it.patSize ;++last){lasts = last;sc++;};
            last = lasts;
            for( bool fd = feed();sc<it.patSize and !lastEl(last) and fd;fd = feed() ){ 
                 if(!ls->child->value.empty() and childsnfed  ){
                    NSC list<eltree::element>::iter lastc = ls->child->value.begin();
                    match<Ty>(pats,lastc,cb);childsnfed = false;
                }
                if( it.pat->value.front().child->name != ls->child->name){break;};
                sc=1; last = ls; NSC list<eltree::element>::iter lasts = last;
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
                    NSC list<eltree::element>::iter lastc = ls->child->value.begin();
                    match<Ty>(pats,lastc,cb); childsnfed =false;
            };
            
    };
};
   
    template <typename T>
    void feed(std::vector<pattern<T>>& pat, void (*cb)(T), std::ifstream& filein){ 
        file = &filein;
        NSC list<eltree::element>::iter last = tree.value.begin();
        while(feed()){
            if(tree.value.size()>0){
                last = tree.value.begin();
                if(last)break;
            }
        };
        // NSC list<eltree::element>::iter parent(eltree::element(&tree));
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


#include <type_traits>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// Primary template → false
template<typename T>
struct is_glm_type : std::false_type {};

// Match all glm::vec types
template<glm::length_t L, typename T, glm::qualifier Q>
struct is_glm_type<glm::vec<L, T, Q>> : std::true_type {};

// Match all glm::mat types
template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct is_glm_type<glm::mat<C, R, T, Q>> : std::true_type {};

// Match all glm::qua (quaternion) types
template<typename T, glm::qualifier Q>
struct is_glm_type<glm::qua<T, Q>> : std::true_type {};

// Helper variable (C++17)
template<typename T>
constexpr bool is_glm_type_v =
    is_glm_type<std::remove_cv_t<std::remove_reference_t<T>>>::value;
template<typename T>
struct glm_dimensions;

// ------------------
// VECTORS
// ------------------

template<glm::length_t L, typename T, glm::qualifier Q>
struct glm_dimensions<glm::vec<L, T, Q>> {
    static constexpr glm::length_t rows = L;
    static constexpr glm::length_t cols = 1;
};

// ------------------
// MATRICES
// ------------------

template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct glm_dimensions<glm::mat<C, R, T, Q>> {
    static constexpr glm::length_t rows = R;
    static constexpr glm::length_t cols = C;
};

// ------------------
// QUATERNIONS
// ------------------

template<typename T, glm::qualifier Q>
struct glm_dimensions<glm::qua<T, Q>> {
    static constexpr glm::length_t rows = 4;
    static constexpr glm::length_t cols = 1;
};

// Helper alias
template<typename T>
using glm_dim = glm_dimensions<std::remove_cv_t<std::remove_reference_t<T>>>;
std::vector<std::string> split(const std::string& input, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, delimiter))
        result.push_back(item);

    return result;
};
template <typename T>
struct is_vector : std::false_type {}

template <typename T> struct is_vector<std::vector<T>> : std::true_type {}

template <typename T>
T fromStr(std::string& str){
    if constexpr (is_vector<T>){
        T res;size_t si=0;
        std::vector<std::string> strs = split(str,' ');
        for(auto& i : val){res[si]=fromStr(i);++si;}
        return res;
    } 
    else if constexpr (std::is_integral_v<T>){
        return (T)std::stoi(str);
    };
    else if constexpr (is_glm_type<T>){
        size_t row = glm_dim<T>::rows;
        size_t cols = glm_dim<T>::cols;        
            std::vector<std::string strss = split(si,',');
            T a;size_t h  =0;
            for(size_t i=0;i<rows;i++){
                for(size_t j=0;j<cols;j++){a[i][j] = strss[h];h++;}
            };
            return a;

    }
    return T(str);
} ;
template <typename T>
std::string toStr(T& val) {
    if constexpr (is_vector<T>){
        std::string res ;for(auto& i : val){res+=toStr(i);}
        return res;
    } 
    else if constexpr (std::is_integral_v<T>){return std::to_string(val);};
    else if constexpr (is_glm_type<T>){
        std::string v;
         size_t row = glm_dim<T>::rows;
        size_t cols = glm_dim<T>::cols;
        std::vector<std::string> strs=split(str,' ');
        
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){v+= std::to_string(val[i][j]) ;v++" ";}
        }
        return v;
    }
    return std::to_string(val);

};


 template <pri::Str s,size_t si,typename Tag,typename... Tags>
    struct getType{ 
        static constexpr bool TS  = sizeof...(Tags)>0;
        static constexpr bool cnd  = s.data==Tag::get_str();

        using next =typename std::conditional <TS,getType<s,si+1,Tags...>,void>::type ;
        using type =typename std::conditional < cnd, Tag , next::type , void>::type; 
        static constexpr size_t size = cnd? si : std::is_same<next,void>::value? 0: next::size; 
    };

template <class Tag,class... Tags>
class SubTags {
    static constexpr size_t size = 1 = sizeof...(Tags) ;
    using typetup= NSC tuple<std::vector<Tag>,std::vector<Tags>...>;
    typetup data;
    std::vector<std::pair<size_t,size_t>> inds;

    template <template <typename A> typename T>
    using typetupt = NSC tuple<std::vector<T<Tag>,std::vector<T<Tags>>...>;

    template <size_t  s, typename TagT,typename... TagTs>
    struct _typeno {using type = std::conditional <!(s>0) , TagT ,typename _typeno<s-1, TagTs...>::type>::type ;} 
    template <size_t s>
    using typeno  = typename _typeno<Tag,Tags...>::type ;

    template <pri::Str s,typename T=getTypeStr<s,0,Tag,Tags...>> 
    std::vector<T::type>& getStr(){return NSC get<T::size>(data);}

    template <size_t s>
    void _write(xmlParser& prs,std::pair<size_t,size_t>& in){
        if(s==in.first){prs.cur->attributes.emplace_back(NSC get<s>(data)[in[second]].str(), toStr(NSC get<s>(data)[in.second]));}
        else if constexpr (NSC tuple_size<typetup>() > s){_write<s+1>(prs,in);}        
    };
    void write(xmlParser& prs,std::ofstream& ofs){
        for(std::pair<size_t,size_t> in: inds) {_write<0>(prs,ofs,in);}
        
        prs.write(&prs.tree,ofs);
    };

    template <size_t s>
    void _read(xmlParser& prs){
        if (s<=sizeof...(Tags) ) {NSC get<s>(data).read(prs); _read<s+1>(prs,ofs)};
    };

    void read(xmlParser& prs){_read(prs,ifs);    };

    template <size_t Si,template <typename T> Func>
    void _apply(std::pair<size_t,size_t> s){
        if(s.first==Si){Func(NSC get<Si>(*this)[s.second])};
        else if constexpr (sizeof...(NSC size(*this)) > Si){ _apply<Si+1,Func>(s);}
    };

    template <typename ATag,typename TTag, typename... TTags>
    static constexpr bool _TagOneOf(){
        if constexpr (std::is_same<TTag,ATag>::value){return true;}
        else if constexpr (sizeof...(TTAgs)>0){return _TagOneOf<ATag,TTags>();}
        else return false;
    };
    template <typename TTag>
    static constexpr bool TagOneOf(){return _TagOneOf<TTag<Tag,Tags...>();};  

    template <template <typename T> Func>
    void apply(){for(std::pair<size_t,size_t>& i : inds) {apply<0,Func>(i);};};
    
    template <size_t s, class Tag,class... Tags>
    void _parseb(std::ifstream& f,std::string& name ){
        if(Tag::str() == name) {NSC get<s>(data).push_back(Tag());inds.push_back({s,NSC get<s>(data).size()}) ;NSC get<s>(data).back().bparse(f)}
        else if constexpr ( sizeof...(Tags)>0){return _parseb<s+1,Tags...>(f,name);}
    };
    void parseb(std::ifstream& f){
        uint8_t sizest;
        f>>size;
        std::string name;name.resize(size);
        f.read(name.data() ,size) ;
    };

    template <size_t s, class Tag,class... Tags>
    void writeb(size_t& i ,size_t& se,std::ofstream& f){
        if(i==s){NSC get<s>(data)[se].bwrite(f);}
        else if constexpr (s < sizeof...(Tags)){_writeb<s+1>(i,se,f)};
    };
    template <size_t s , class ts,class... ts>
    bool _OneOf(xmlParser::element& el){
        if(ts.str()==el.child->name){NSC get<s>(data).emplace_back(el); inds.push_back(std::pair<size_t,size_t>(s,NSC get<s>(data).size));
            return true;}
        if constexpr (s<= sizeof...(Tags)){return _OneOfAts<s+1,ts>(el);}
    }
    bool OneOf(xmlParser::element& el){return _OneOfAts<0,Tag,Tags...>(el);}

    template <class Attrs>
    SubTags<Tag,Tags...> get() {};

    template <size_t s, typename TagT,typename TagTT,typename... TagTTs>
    constexpr void _set(TagT& arg){
        if constexpr (std::is_same<TagTT,TagT>::value){
            NSC get<s>(data).push_back(arg);inds.push_back(s,(size_t)(NSC get<s>(data).size()-1));return;
        }
        else {_set<s+1,TagT,TagTTs...>(arg);}
    };
    template <typename TagT,tepname... TagTs>
    constexpr sets(TagT a, TagTs... args){
        _set<0,TagT,Tag,Tags...>(a);
        sets<TagTs...>(args...) ;
    };
    template <typename... TagTs>
    constexpr SubTags(TagTs... a) {}
    template <typename Func>
    void call(std::string& str){};


    
    auto& get(size_t& s){

    };
    template <template <typenmae T> typename Func ,size_t si=0>
    void call(std::pair<size_t,size_t>& pr){
        if constexpr (pr.first==si){ Func(NSC get<si>(data)[inds]);return ;}
        else {call<Func,si>(pr);}
    } ;
    template <template <typename T> typename Func>
    void callall(){for(auto& it : inds){call<Func>(it);}};
};

template <typename... Ts>
struct TAttrs  {
    NSC tuple<Ts...> data;
    template <size_t s,typename TT, typename TTs>
    void set(TT& a,TTs... args) {
        NSC get<s>(data)=a ;set<s+1,TTs...>(args...) ; 
    };
    TAttrs(Ts... args) {set<0,Ts...>(args...) ;}
}

template <pri::Str s, typename T>
struct Var : T , CEStr<s>{} ;

template <class Var,class... Vars>
class Attrs  {
    std::vector<size_t> inds;
    using inhtupty =NSC tuple<Var,Vars...>  ;
    inhtupty data;



    template <pri::Str s,typename T = getType<s,0,Var,Vars...>> 
    T::type& getStr() { NSC::get<T::size>(data);};
    template <pri::Str s>
    constexpr bool hasStr(){return ! std::is_same<getType<s,0,Var,Vars...>::type,void>::value;}

    template <typename VarT>
    void tag_atWrite(VarT& d;std::ofstream& ofs){
        ofs<<VarT::str()<<"="<<'\"'<<d.get()<<'\"'; 
    };
    template <size_t s>
    void _get(std::vector<xmlParser::attribute>& attrs){
        attrs.emplace_back(NSC get<s>(*this).str());writeStr(NSC get<s>(*this).data);
    };
    std::vector<xmlParser::attribute> get(){std::vector<xmlParser::attribute> ats;}; 

    template <size_t i,>
    void _write(std::ofstream& ofs){
        ofs<<toString(NSC get<i>(*this));
        if constexpr ( i<NSC tuple_size(data)){_write<i+1>(ofs)};
    };
    void write(std::ofstream& ofs){_write<0>(ofs);}

    template <size_t s , class ts,class... ts>
    bool _OneOfAts(xmlParser::attribute& at){
        if(ts.str()==at.first){NSC get<s>(*this).read(at.second);return true;}
        if constexpr (s<= sizeof...(Vars)){return _OneOfAts<s+1,ts>(at);}
    };

    bool OneOfAts(xmlParser::attribute& at){return _OneOfAts<0,Var,Vars...>(at);}

    template <size_t s,typename T,typename... Ts>
    constexpr void set(T arg,Ts... args){NSC get<s>(data)=arg;set<s+1,Ts...>(args...);}

    constexpr Attrs(Var tp,Vars... args) {set<0,Var,Vars...>(arg,args...);}
};

#include <petri/templates.hpp>


template <pri::Str s,typename T, class SubT=SubTags<void>, class Ats=Attrs<void> , T vald= T()> 
struct Tag : CEStr<s> {
    using type=T;
    using ATSTY = Ats;
    using SUBTY = SubT;
    T data; 
    Ats ats;
    SubT subs;
    using Subtype =SubT;
    
    void read(eltree* el){
        for(xmlParser::attribute& atit : el->attributes ){if(Ats.OneOf(atit)){continue;}};
        
        bool str=true;
        for( xmlParser::element& elit  :  el->value){if(!str  ){subs.OneOf(elit);}str!=str;}
    };
    xmlParser::attribute atr(){return xmlParser::attribute(str(),toStr(data));}

    void write(eltree* el){
        for(xmlParser::attribute& atit : el->attributes ){if(Ats.OneOf(atit)){continue;}};
    };

    void write(std::ofstream& ofs){

        eltree* el; 
        xmlParser prs;
        el = prs.tree;
        write(el);
        for()
        prs.write(el,ofs);
    };
    void parse(xmlParser& prs){
        eltree* el = prs.cur;
        eltree* par= prs.cur->parent;
        while(par->value.back().child != el){if(!prs.feed()){break;};}
        read(el);
    };

    void bwrite(std::ofstream& f){
        uint8_t s = (uint8_t)str().size() ;
        f<<s;
        uint32_t sizeoffs = subs.inds.size();
        f<<sizeoffs;
        
        pos_t p= f.tellp();
        f.seekg(p+4*sizeoffs) ;
        pos_t offc=0;pos_t soffs = f.tellp();
        for(auto i : subs.inds){
            subs.writeb<0>(i.first,i.second,f);
            pos_t h = f.tellp();f.seekp(p+offc*4) ;uint32_t offs= h-p; f<<offs;
            f.seekp(h);++offc;
        }
    }
    void bparse(std::ifstream& f){
        uint8_t sizetag ;
        uint32_t sizeoffs;
        f>>ats.data>>sizeoffs;
        std::vector<uint32_t> offs(sizeoffs) ;
        uint32_t pos =f.tellp();
        for(auto& it : offs) {f>>it;};
        for(auto& it : offs) {f.seekg(pos+it);subs.parseb(f);};
    };


    Tag(Ats _ats,SubT vals){
        ats=_ats;
        subs=vals;
    } ;

    Tag(xmlParser::element& el){}
    Tag(xmlParser& prs) {parse(prs);}
    Tag(std::string&& str){
        xmlParser prs(str);prs.parseStr(prs);
        parse(prs);
    }

    
};

template <pri::Str s,typename T,T vald= T()>
struct ATag : Tag<s,T,SubTags<void>,Attrs<void>,vald> {};


// TODO from tag to binary ; 
template <class Subs>
struct bsubt ;
template <class TagTy>
struct btag : TagTy {
    using type = T;
    uint32_t TAG  ;
    
    using Ats = typename Attrs<TagTy::>  ;
    using SubTs = typename ;
    Ats ats;
    SubT subs;

    void addto(std::vector<std::string>& re,std::string str ) {
        for(auto& i : re) {if(re==str){return;}}
        re.push_back(str);
    };
    template <size_t s>
    void _getTAGS(std::vector<std::string>& str){
        if constexpr (s < TagTy::size){
            btag<TagTy::typeno<s>>::getTAGS(str);
            _getTAGS<s+1>(str);
        }
    };
    std::vector<std::string> getTAGS(){
        std::vector<std::string> res;
        res.addTo(res,TagTy::str());
        _getTAGS<0>(str);
    };
    uint32_t get(std::string& str){
        uint32_t h=0 ;
        for(char c : str){h+=c;h=h<<8 ;};
    };
    bool nin(std::string& g, std::vector<std::string>& s){
        for(auto& i : s){if(g==i){return false;}};
        return true;
    };
    std::string strip(std::string& s,std::vector<std::string>& alr){
        std::string res;size_t i=0;size_t j=0; size_t lj=0;
        while(nin(res,alr)) {
            res[i] = s[j] ;
            for(auto it : alr) {if(alr[i] != res[i]){
                for(++i;i<4;++i){++j;if(!(j<s.size()) {--j;}
                res[i]=s[j]; };
                return res;
            }
            j++;i++;
            if(i==4) {i=0;j=lj+1;lj++ ;}
        }
    };
    std::map<std::string,uint32_t> getmap() {
        std::vector<std::string> st =getTAGS();
        std::vector<std::string > alr;
        std::map<std::string,uint32_t> res;
        for(std::string& s : st){
            if(s.size()<4){alr.push_back(s);res[s] = get(s);}
            else {
                std::string g= strip(s,alr) ;
                alr.push_back(g) ; res[g] = get(g) ;
            }
        }
        return res;
    };
    template <size_t s, typename TagT>
    void _getTag(std::map<std::string,uint32_t> st){
        TagTy::SUBTY::
    };

    template <typename TagT>
    void getTag(uint32_t& mstr){
        auto i = getmap();
        TAG = i[TagTy::str()] ;
        _getTag<0>()
    };


};



template <typename... Tag>
void parseTags(xmlParser& prs) {

};




 template <typename TagT>
 Tag bread(std::ifstream& ifs) {
    auto lam = <typename tagt>[&ifs]() {}
     
 };
 
 template <typename TagT>
 void bwrite(TagT& tt,std::ofstream& ifs) {
    
 };



#endif