#pragma once
#include "nodes_editor.hpp"
#include "../../petri/vects.hpp"
#include <typeinfo>
#include <typeindex>
#include <map>


// TODO more runtime type checks
bool issame(auto t,auto r){return std::is_same<decltype(r),decltype(t)>::value;};
bool issamedecl(auto t,auto r)return std::is_same<std::remove_reference<decltype(t),std::remove_reference<decltype(r)>>::value;};

std::map<std::type_index,std::string> ty_ind_map;
void contribute_type(std::type_index i, std::string name){
    ty_ind_map[i] = name;
};

namespace pins {
  
    class type_ident {
        std::type_index index;
        std::string name;

    };
    class rflct {
        virtual void ret();
    };
    class strctre : public rflct{
        std::string name;
        arr<std::type_ident> members;
        std::string fabricate(){ std::string n;
            for(int i=0;i<this->members.size();i++){
                n+="typedef struct "+this->name+"{"
            };
        };
    }  ;
    class clss {
        arr<std::type_index> members_public;
        arr<std::type_index> members_protected;
        arr<std::type_index> members_private;

        vect<size_t> index_fp_public;
        vect<size_t> index_fp_protected;
        vect<size_t> index_fp_private;
        

    };
};

namespace refs {

template <typename T >
class pinptr :public pin<T*> {
    public:
    virtual T& data_ref() override {return this->data;};
    virtual T* data_ptr() override {return this->data;};
    virtual T data() override  {return *(this->data);};
    virtual void handle() override {inline pin::handle();};

    pinptr(pintypes tp,std::string name,T& data){
        this->pintype=tp;
        this->name= name;
        this->d=&&(data);
    };
    pinptr(pin<T> s){
        this->d = &(s.d);
        this->name = s.name;
        this->pintype=s.pintype;
    };
    pinptr()
};
template <typename T> 
class pinref : public pin<T&>{
    virtual  T& data_ref() override {return this->data;};
    virtual T* data_ptr() override {return *(this->data);};
    virtual T data() override {T s = this->data; return s;};
};

class event_pin : public pin<events::event,pintype::res> {
    public:
    virtual void handle(){

    };
} ;

class event_pinptr :public pinptr<events::event,pintype::event>{

} ;
class event_pinref : public pinref<events::event,pintype::event>;


template <typeame T>
class res_pin : public pin<T,pintype::res> ;
template <typename T>
using res_pinptr = res_pin<T*,pintype::res> ;
template <typename T> 
using res_pinref = res_pin<T&,pintype::res>;
#define res(T,name) \
  using ##name_ptr res_pin_ptr<T>; \
  using ##name_rer res_pin_ref<T>; \
  using ##name res_pin<T> ; \

#define ev(T,name) \
  using ##name_ptr =event_pin_ptr<T>; \
  using ##name_ref =event_pin_ref<T>; \
  using ##name =event_pin<T> ; \

#define ptr(name) ##name_ptr
#define ref(name) ##name_ref




template <typename T>
class instance_pin : pin<T> {
    
};
template <typename T>
struct modifier_pin : pin<T>


// Template for cxx primitive types and their array flavors
template <typename T>
struct cxxpin : pin<T> {

};



// Container Pin

#include <glm/glm.hpp>
#include <strata/petri/meta.hpp>
using namespace glm;
template <typename T>
struct glmpin : pin<T> { // This is supposed
    constexpr bool isvec = is_glmvec<T>::value; 
    constexpr bool ismat = is_glmmat<T>::value;  
};

template <typename glmv>
struct vecglmpin : pin<std::vector<glmv<T>>> { // No Dropdown // TODO <<>> symbol for them
    constexpr bool isvec = is_glmvec<T>::value; 
    constexpr bool ismat = is_glmmat<T>::value;  

    void 
};


#define GLMVMAC(gl) \
struct glmp##gl : glmpin<gl>;\
template <typename T>
struct vecglmp##gl : vecglmpin<gl>  ;



#define GLMVPINDEF( ...)  ONE(GLMVAC,__VA_ARGS__)
GLMVPINDEF(vec2,vec3,vec4,bvec2,bvec3,bvec4,dvec2,dvec3,dvec4,uvec2,uvec3,uvec4,ivec2,ivec3,ivec4)

#define GLMMAC(gl)\
GLMVAC(gl##2)  \
GLMVAC(gl##3) \ 
GLMVAC(gl##4)  \
GLMVAC(gl##2x3) \
GLMVAC(gl##2x4) \
GLMVAC(gl##3x2) \
GLMVAC(gl##3x4) \




#define GLMMPINDEF(...) ONE(GLMMAC,__VA_ARGS__)
GLMMPINDEF(bmat,dmat,mat,umat,imat)

#define GLPIN(glmt) glmp##glmt
#define VPIN(glmt) glmp##glmt 

};