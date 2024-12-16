#pragma once
#include "gltf.hpp"
#include "source.hpp"
#include "objects.hpp"
#include <petri/vects.hpp>
#include <filesystem>
#include <string>
#define fs std::filesystem


bool load_names = true;

#define ONE(macro, first)  macro(first)
#define ONE(macro, first , sec)  macro(first) macro(sec)
#define ONE(macro, first , sec , tri)  macro(first) macro(sec) macro(tri)
#define ONE(macro, first,...) macro(first) macro(__VA_LIST__)

enum jsonval{
    none,
    stri,
    intgr,
    dble,
    stri,
    arr,
    obj,
};
template <jsonval v> 
struct jsonval_t {
    using type = std::conditional<v==jsonval::intgr, int ,
                 std::conditional<v==jsonval::dble, dble ,
                 std::conditional<v==jsonval::uri, std::string ,
                 std::conditional<v==jsonval::stri, std::string , void>::type>,void>::type>,void>::type>
                 
};
    typedef union jsonvalu{
        int i;
        double dbl;
        std::string str;
    } jsonvalu;


class jsonvalue {
    public:
    jsonval valty;
    jsonvalu val;
    
    jsonvalue get(size_t pos,std::string s){
        std::string v;
        size_t pos = s.find_first_of(":");
        size_t pos1=s.find_first_of("\"",pos+1);
        size_t pos2=s.find_first_of("\"",pos1+1);
        if(s[pos] == '\"'){
            for(size_t i = pos;(s[i]!="\"") and (s[i-1]!="\\");i++){v+=s[i];};
            this->valty = jsonval::stri;};
            this->val->str = v; return *this;
            for(size_t i = pos;(v[i]!=" ");i++){v+=s[i];};
            size_t p = v.find_first_of(".");
            if(!p){p=v.end();}
            double dbl;
                int pow=1;
                for(size_t i = p ; i<v.begin();i--){ dbl+=pow*(v[i] - "0");pow=pow*10; };
            if(p){
                pow=1;
                for(size_t i = p ; i<v.end();i++){ pow=pow/10;dbl+=pow*(v[i] - "0"); };
            };
            return dbl;
            return *this;
        };
        
    
    
    template <jsonval v> 
    jsonval_t<v>::type get(bool names, size_t pos,std::string s){
        jsonval_t<v>::type res;
        jsonvalue t = get(pos,s);
        if(t.valty==valty::v){
            switch(t.valty){
                case valt::intgr : { res = t.val.in};
                case valt::dble : { res = t.val.dbl};
                case valt::stri : { res = t.val.str};
            };
        };
        return res;
    }; 
    void put(ostream fs){
        switch(this->valty){
            case jsonval::intgr : {fs<<this->val.i;};
            case jsonval::dble : {fs<<this->val.dbl;};
            case jsonval::uri : {fs<<"\""<<this->val.str<<"\"";};
            case jsonval::stri : {fs<<"\""<<this->val.str<<"\"";};
        };
    };
};

template <bool arr_val_, bool obj_val_ , jsonval V=jsonval::none  >
class property {
    public:
    const  std::string name = "property";
    static const bool arr_val=arr_val_ ; 
    static const bool obj_val=obj_val_ ; 
    const jsonval valt=jsonval::obj;
    property()=default{}; 

    #define PROPS_MEMB(arg) arg _##arg; 
    #define PROPERTIES prop1 prop2 
    #define GLOBJ(name, ...) class ##name_globj : public property<arr_val,obj_val> {\
    public:
        ONE(PROPS_MEMB,__VA_LIST__) \
    };

    jsonval_t<v>::type value;
    GLOBJ(prpobjname, )
    vect<> arr;
    
    decltype(*this) create()final{decltype(*this) n; return n; };
    decltype(*this) feed_line(std::ifstream f ,std::string s,size_t pos, bool names);
    void get(std::string s)
    void feed_line();

    virtual bool props(globj* ob,jsonval vt, size_t pos , std::ifstream* f, std::string s){

    #define PROPS(prpt)  p = s.find(prpt::name);\
    if(p!=s.npos){ if(prpt::arr_val){size_t m=s.find("s\"",p+1);\
     if(m){pos=m+2; }; prpt res ; \
     res_##prpt=res.feed_line(vt,pos,f,h); ob._##prpt = res;};return true;}  ;

    #define PROPERTS(...)     size_t p=0; ONE(PROPS, __VA_LIST__)
    // PROPERTS(PROPERTIES)

    };

    decltype(*this) feed_line(jsonval vt,size_t pos , std::ifstream* f, std::string s);
    void propers(globj* ob,jsonval vt, size_t pos, std::ifstream* f,std::string s){
        
        if(this->props(ob,vt,pos,f,h)){return;};
        decltype(*this) b;
        b.feed_line(vt,pos,f,h);
    };
    // TODO handle commas and empty lines as well as no /n ( go by comma instead of new line) 
    void parse_obj( globj* obj,size_t pos , std::ifstream* f , std::string str){ // Pos is after first {
        std::string s =str;size_t n=pos;
        do{
            n = s.find_first_of(":",n);
            if(n!=s.npos){this->propers(jsonval::none,names,n,f,s);
            };
            n = s.find_first_of("[");
            if(n!=s.npos){this->propers(json_val::arr,names,n,f,s);;};
            n = s.find_first_of("{",n+1);
            if(n!=s.npos){this->propers(json_val::obj,names,n,f,s);};
            n = s.find_first_of("}",);
            if(n!=s.npos){return ;}; 

        }while(*f>>s);
    };  
    void parse_arr( size_t pos , std::ifstream* f,std::string str){ // Pos is after first [
       std::string s = str; size_t n = pos;
        do{
            n = s.find_first_of(":",n);
            if(n!=s.npos){globobj obj;this->props(&obj,jsonval::none,n,f,s); this->arr.push(obj);continue; };
            n = s.find_first_of("{");
            if(n!=s.npos){this->propers(jsonval::obj,n+1,f,s);continue;};
            if(n!=s.npos){this->arr.push(new globj); this->parse_obj(&(this->arr[this->arr.size()-1]),jsonval::none,n+1,f,s);continue;};
             n = s.find_first_of("[");
            if(n!=s.npos){this->propers(jsonval::arr,n+1,f,s);continue;};
            n = s.find_first_of("]");
            if(n!=s.npos){return;};
        }while((*f)>>s);
    };
    decltype(*this) feed_line(jsonval vt,size_t pos , std::ifstream* f, std::string s){ // Pos is at ":" provides at ":"

        switch(vt){
        case jsonval::none: {
        std::string h; (*f)>>h;
        size_t empty = h.find_first_not_of(" \n");
        if(empty){bool valg=true;};
        if ((this->arr_val==true)or(this->arr_obj==true)){
         size_t poss=s.find_first_of("[",pos+1;);
         if(poss != s.npos){this->parse_arr(pos,f);valg=false;break};
        poss=s.find_first_of("{",pos+1);
         if(poss != s.npos) { this->parse_obj(&(this->arr[this->arr.size()]),poss+1,f);valg=false;};
        };
        if(valg){this->val=jsonvalue::get<v>(names,pos,s);};
         return ;};
        case jsonval::intgr: {this->val=jsonvalue::get<jsonval::intgr>(pos,s);return *this;};
        case jsonval::dble : {this->val=jsonvalue::get<jsonval::dble>(pos,s);return *this;};
        case jsonval::stri : {this->val=jsonvalue::get<jsonval::stri>(pos,s);return *this;};
        case jsonval::obj  : {this->parse_obj(&(this->obj),pos,f,s);return *this;};
        case jsonval::arr  : {this->parse_arr(pos,f,s);return *this;};
        };
        std::string st;
        (*f)>>st;
        this->feed_line(vt,names,0,f,st);
    };
    
};
class name : public property<false,false> {
    public:
    name(std::string s)=default{this->val=s};
    decltype(*this) feed_line( size_t pos , std::ifstream* f, std::string s)override{
       if(!load_names){return NULL;};
       this->val=jsonvalue::get<>(s,pos);
       return *this;
    };
};
class uri : public property<false,false>{
public: 
   
    
    std::string data;
    void ret(){

    };
    uri(std::string s){

    };
};
class arr : public property<true,false> ;
class str_arr : public arr {
    static const jsonval ty =  jsonval::arr ;
    
    void parse()
};
class obj : public property {

};
class objnar : public property , public arr ,public obj{ // Can be array of objects
    static const arr_val = true;
    static const obj_val = true;
    
    void parse()final{

    };
};

class version : public property{
public: 
    static const std::string name = "version"  ; 
};
class generator : public property{
public: 
    static const std::string name = "generator" ; 
};
class copyright : public property{
public: 
    static const std::string name = "copyright" ;
    std::string data;
};
class asset : public property<true,true>{
public:
    static const std::string name = "asset";

    GLOBJ(version,generator,copyright);
    void props(jsonval vt, size_t pos , std::ifstream* f, std::string s)override{
        PROPERTS(version,generator,copyright)
    };
};


 class byte_length : public property {
    public :
    const std::string name = "byteLength";
 };

class extensionsUsed : public property , public str_arr {
    static const std::string name= "extensionsUsed"
};
class extensionsRequired :  public property , public str_arr {
    static const std::string name ="extensionsRequired"
};
class properties {
    public:
    auto feed_line( ifstream f,bool names=false){
        load_names = names;
         std::string s;
            f>>s;
            size_t pos = s.find_first_not_of(" \n\r");
            #define FEED_RET(prpt) p=s.find( prpt::name) ; if(p==sp){ if(prpt::arr_val){size_t m=s.find("s\"",p+1); if(m){pos=m+2; }}; prpt res ;return res.feed_line(jsonval::none,names,pos,f,s);};
            FEED_RET(asset)
            FEED_RET(extensionsUsed)
            FEED_RET(extensionsRequired)
            FEED_RET(scene) // Objects
            FEED_RET(animation)
            FEED_RET(node)
            FEED_RET(camera)
            FEED_RET(skin)
            FEED_RET(mesh)
            FEED_RET(accessor)
            FEED_RET(bufferView)
            FEED_RET(buffer)
            FEED_RET(material)
            FEED_RET(texture)
            FEED_RET(sampler)
            FEED_RET(image)
    
    };
    property void feed(int pos_prop, int pos_str , std::string s , bool names){

    };
    
};

class gLtf : public acqres {
    
    void fromglb
};  


class gltf : public gLtf{ // 
    void load(ifstream file , bool names){

    };
    void write(ofstream file){

    };
} ;
class glb : public gLtf {

};

