#include <petri/list>
#include <filesystem>
#include <ifstream>
#include <string>
#include <stdexcept>
#include "../petri/templates.hpp"
using namespace std ;
#define NSC pri::

struct xmlParser {

typedef std::pair<std::string ,std::string > attribute;
class eltree{
        public:
        eltree* parent=nullptr;
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
        vlback(){return value.empty()? value.back().str(): str ;  };
        eltree() {};
        eltree(const eltree& _Et) : parent(_Et.parent),name(_Et.name),attributes(_Et.attributes) , value(_Et.value) {};
        
    };
    eltree tree ;
    eltree* cur=&tree;

template <typename T>
    struct error : std::runtime_error {
        T d;eltree* e;std::string str(){
            if constexpr (std::is_same<T,attribute>())
        }
        error(T& _d,eltree* _e = cur ) : d(_d) , e(_e) {}; 
    };
    struct attribute_error : error<attribute  > ;

     struct lex {
        enum ty {name,str,value,
            lt='<',gt='>',slash='/', gtend,ltcomm , gtcomm , eq='=',apm='&',dq='\"'
        } t;
        lex& operator=(ty _T) {t= _T;return *this;}
        std::string name;
    };
    std::ifstream fi;
    std::string line;size_t p=0;
    lex c;

    template <lex... ls>
    bool oneof(){return pri::OneOf<lex::ty,ls...>(cur.t) ;}

    void getComment(){
        while(cur){

        };
    };

    void getStrLit(){
        for(line[pos]='\"';pos++){
            if(pos>=line.size()){pos=0;std::getline(fi,line);}
            if(line[pos]=='\\' ){pos++; cur.name+=pos>line.size()?'\n':  line[pos];continue;}
            cur.name+=line[pos];
        };
    };
    std::string getValue(){

    };

    void next(){p++;if(p>=line.size()){std::getline(fi,line);p=0;};}
    void lexe();

    void getVal(){
        next();
        if(cur==str){
            cur.attributes.back().second=cur.name;
        }
        else throw attribute_error("No string value for attribute")
    };
    
    template <pri::Str s ,char _c >
    struct escape : pri::CEStr<s> {
        static constexpr char c = _c;
        constexpr char chr(){return c;}  
        static constexpr size_t s = str().size();
    };
struct lt<"lt",'<'>;
struct gt<"gt",'>'>;
struct amp<"amp",'&'>;
struct quot<"quot",'\"'>;
struct apos<"apos",'\''>;
template <calss escT,class... escTs>
constexpr size_t maxs(){
    if constexpr (sizeof...(escTs)){return escT().str().size() > maxs() ? escT::str().size() : maxs<escTs...>()  ;
    else return escT().str().size();
};


    template <class eT, class... eTs>
    char _getEscape(std::string& str){
        for(;str.size()<=maxs<et,eTs...>();next()){
            if(str==eT::str()){return eT::chr();}
            else {}
        };
        throw std::logic_error();
    };

    void getEscape(){++pos;std::string str;try{str+=_getEscape<lt,gt,amp,quot,apos>(str);}
        catch (const std::logic_error& e){ };    
        cur->vlback()=str;
    };
    void getTagVal(){
            for(nextt();line[pos]!=lt;next()){
                if(pos[line] amp : {cur=amp;getEscape();};)
                cur->str +=line[pos]; 
            };

    };
    void closeTag(){cur = cur->parent();};
    void closeTag(std::string name){
        while(cur->name !=name and (cur->parent!=nullptr)){cur=cur->parent;
            for(auto it = cur->value.begin() ; ;++it) { if (cur->value.child->name==name){cur=cur->value.child; break; } 
        }
        cur=cur->parent;
    };
    void getTag(){
        next();lexe();
        if(c.t==str) {std::string st = c.name; next(); if(c.t==lex::ty::gtend ){ closeTag(st);}};
        while(!oneof<gt,gtend>()){next();lexe(); };
        if(oneof<gt>()){getTagVal();getTag();}
        else closeTag();
    };  
    void lexe(){
        switch(line[p]) {
            case lt  :  {
                if(line[p+1] == '-'  and line[p+1] == '-'){getComment();next();return;};
                else {c=lt;getTag();return;}
            };
            case slash : { if(line[p+1] = 'gt'){  c= gtend;  p++;closeTag();};else {cur= slash;}return; };
            case gt : {c=gt;;return;};
            case eq : {c=eq;getVal();};
            case dq : {c=str;getStrLit();};
            default : {c=name;for(std::alnum(line[pos]) ; next() ){
                    c.name+=line[pos];
                };
            }
        };
    };

    
    void parse(std::string path){
        std::filesystem::path pth(path);
        if (!std::filesystem::is_regular_file(pth)){throw std::runtime_error("file type");}
        fi= std::ifstream(path);
        while(std::getline(if,line)){};
    };
    void print(){

    };
    void put(std::string pth ){
        std::ofstream file(pth);

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
        
        
        bool dfsmatch(pri::list<eltree::element>::iter el, pri::list<eltree::element>::iter patt,T* res){
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
                pri::list<eltree::element>::iter patIter = patt->child->value.begin();
                pri::list<eltree::element>::iter elIter = el->child->value.begin(); 
                if(!dfsmatch(elIter,patIter,res)){return false;};
            }
            if(!patt->child->attributes.empty()){;
            if( patt->child->attributes.back().first == iterate){
                if(!iter){
                    int num = stoit(patt->child->attributes.back().second);
                    funct(num,std::string(),res);
                };
                iter=true;
                pri::list<eltree::element>::iter patIter = patt;
                pri::list<eltree::element>::iter elIter = el; ++elIter;
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
                pri::list<eltree::element>::iter  patti= patt;
                pri::list<eltree::element>::iter eli= el;
                ++eli;++patti;
                if(eli ) {if(!dfsmatch(eli,patti,res)){return false;}}
                else if(patti){return false;}

            }
            return true;
        };      
        bool matchPat( T* res, pri::list<eltree::element>::iter& l){
            
            pri::list<eltree::element>::iter last = l;
                       
            pri::list<eltree::element>::iter patlast = pat->value.begin();
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
 
    bool open(pri::list<eltree::element>::iter el){
        if(el.next()){return false;};
        pri::list<lexe>::iter s = lexqrfind(tok::elStart,lexq.tail());
        std::string parentName = el->child->parent->name;
        for(;s;--s){
            if(s->t == tok::elStart){
                if(s->d == el->child->name){return parentName == s.prev()->d? true : false;}
            }
        }
        return false;
    };
     bool lastEl(pri::list<eltree::element>::iter el){
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
    void match(std::vector<pattern<Ty>>& pats,pri::list<eltree::element>::iter l , void (*cb)(Ty) ){        
        pri::list<eltree::element>::iter ls = l;
        for(;ls;++ls){
            for(bool fd=feed();ls->child->name.length()==0 and fd ; fd=feed()){};
            bool childsnfed= true;          
            pri::list<eltree::element>::iter last = ls;  
            for(pattern<Ty>& it : pats){  
            size_t sc=1;
            last = ls;pri::list<eltree::element>::iter lasts = last;
            for(;last and sc<=it.patSize ;++last){lasts = last;sc++;};
            last = lasts;
            for( bool fd = feed();sc<it.patSize and !lastEl(last) and fd;fd = feed() ){ 
                 if(!ls->child->value.empty() and childsnfed  ){
                    pri::list<eltree::element>::iter lastc = ls->child->value.begin();
                    match<Ty>(pats,lastc,cb);childsnfed = false;
                }
                if( it.pat->value.front().child->name != ls->child->name){break;};
                sc=1; last = ls; pri::list<eltree::element>::iter lasts = last;
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
                    pri::list<eltree::element>::iter lastc = ls->child->value.begin();
                    match<Ty>(pats,lastc,cb); childsnfed =false;
            };
            
    };
};
   
    template <typename T>
    void feed(std::vector<pattern<T>>& pat, void (*cb)(T), std::ifstream& filein){ 
        file = &filein;
        pri::list<eltree::element>::iter last = tree.value.begin();
        while(feed()){
            if(tree.value.size()>0){
                last = tree.value.begin();
                if(last)break;
            }
        };
        // pri::list<eltree::element>::iter parent(eltree::element(&tree));
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


    xmlParser() = default;
};