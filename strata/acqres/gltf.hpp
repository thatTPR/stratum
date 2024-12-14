#pragma once
#include "gltf.hpp"
#include "source.hpp"
#include "objects.hpp"
#include <filesystem>
#include <string>
#define fs std::filesystem

enum jsonval{
    num,
    stri,
};
enum gltfval {
    intgr,
    dble,
    uri,
    stri,
    arr,
    obj 
};

    typedef union gltfvalu{
        int i;
        double dbl;
        std::string str;
    } gltfvalu;
class jsonvalue {
    public:
    gltfval valty;
    gltfvalu val;
    jsonvalue get(std::string s,size_t pos){
        std::string v;
        
        size_t pos=s.find_first_not_of(" ",pos);
        if(s[pos] == '\"'){
            for(size_t i = pos;(s[i]!="\"") and (s[i-1]!="\\");i++){v+=s[i];};
            if(this->valty!=gltfval::uri){this->valty = gltfval::stri;};
            this->val->str = v return ;
        }
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
    };
        
    void put(ofstream fs){
        switch(this->valty){
            case gltfval::intgr : {fs<<this->val.i;};
            case gltfval::dble : {fs<<this->val.dbl;};
            case gltfval::uri : {fs<<"\""<<this->val.str<<"\"";};
            case gltfval::stri : {fs<<"\""<<this->val.str<<"\"";};
        };
    };
};

class property {
    public:
    const  std::string name = "property";
    const bool arr_val=false ; 
    const bool obj_val=false ; 
    const gltfval val=gltfval::obj;

    const gltfval vals = 
    static constexpr is_arr(){return this->val==gltfval::arr;};
    static constexpr is_obj(){return this->val==gltfval::obj;};
    // TODO make arrs work by adding NOOOOO! I like this:
    std::conditional<arr_val,vect<decltype(*this)>,void>::type arr; 
    std::conditional<obj_val,decltype(*this),void>::type obj;
    virtual void parse();
    
    template<typename... T>
    decltype(*this) create(T... args)final{decltype(*this) n(args...) return n; };
    decltype(*this) create()final{decltype(*this) n; return n; };
    decltype(*this) feed_line(std::ifstream f ,std::string s,size_t pos, bool names);
    virtual void props(bool names , size_t pos, std::string s){

    };
    virtual void props(bool names, size_t pos , std::ifstream* f, std::string s){
        std::string h;
        (*f)>>h;
        size_t p;
    #define PROPS(prpt)  p = s.find(prpt::name);if(prpt::arr_val){if(s[p+prpt::name.size()]=='s'){pos++; }; prpt res ; this->_##prpt=res.feed_line(f,h,pos+prpt::name.size()+1,names); return;};};

    };
    void parse_obj(bool names, size_t pos , std::ifstream* f , std::string str){
        std::string s;
        while(*f>>s){
            size_t q = s.find_first_of("}",p+1);
            if(q){
            size_t p = s.find_first_of("\"");size_t n;
            if(p){ n = s.find_first_of("\"",p+1)};
            if((p and n ) and (s[n-1]!="\\") and ((q<n) and (q>p)) or (!(p&&n) and q ) ){return ;}; 
            }
            size_t n = s.find_first_of(":");
            if(n){this->props(names,n,f,s);continue;};
            n = s.find_first_of("{");
            if(n){this->parse_obj(names,n,f,s);};
             n = s.find_first_of("[");
            if(n){this->parse_arr(names,n,f,s);};

        };
    };  
    void parse_arr(bool names, size_t pos , std::ifstream* f,std::string str){
       std::string s;
        while(f>>s){
            size_t q = s.find_first_of("]",p+1);
            if(q){
            size_t p = s.find_first_of("\"");size_t n;
            if(p){ n = s.find_first_of("\"",p+1)};
            if((p and n )and(s[n-1]!="\\")and ((q<n) and (q>p)) or (!(p&&n) and q ) ){return ;}; 
            };
            size_t n = s.find_first_of(":");
            if(n){this->props(names,n,f,s);continue;};
            n = s.find_first_of("{");
            if(n){this->parse_obj(names,n,f,s);continue;};
             n = s.find_first_of("[");
            if(n){this->parse_arr(names,n,f,s);};
        };
    };
    decltype(*this) feed_line(bool names, size_t pos , std::ifstream* f, std::string s){
        if ((this->arr_val==true)or(this->arr_obj==true)){
         size_t poss=s.find_first_of("[{",pos+1;);
         if(poss){
         bool arr;
         if(s[poss] == '['){arr=true;}
         else arr=false;
         if(arr){this->parse_arr(names,pos,f);};
         else {this->parse_obj(names,pos,f);};
         };
        };
         this->val=this->get(s,pos);

         return *this;
    };
    property()=default{};
};
class name : public property {
    public:
    decltype(*this) feed_line(bool names, size_t pos , std::ifstream* f, std::string s){
       if(!names){return;};
       this->val=jsonvalue::get(s,pos);
       return *this;
    };
    property()=default{};
};
class uri : public property{
public: 
    static const bool arr_val=false ; 
    static const bool obj_val=false ; 
    
    std::string data;
    void ret(){

    };
    uri(std::string s){

    };
};
class arr : public property {

};
class str_arr : public arr, public property {
    static const gltfval ty =  gltfval::arr ;
    
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
class asset : public property{
public:
    static const std::string name = "asset";
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
         std::string s;
            f>>s;
            size_t pos = s.find_first_not_of(" \n\r");
            #define FEED_RET(prpt) p=s.find( prpt::name) ;if(p==sp){ if(prpt::arr_val){if(s[p+prpt::name.size()]=='s'){pos++;}; prpt res ;return res.feed_line(names,pos+prpt::name.size()+1,f,s);};
            FEED_RET(asset)
            FEED_RET(version)
            FEED_RET(generator)
            FEED_RET(copyright)
            FEED_RET(uri) 
            FEED_RET(extensionsUsed)
            FEED_RET(extensionsRequired)
            //
            sampler

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

