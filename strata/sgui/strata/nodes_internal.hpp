#pragma once
#include "nodes_editor.hpp"
#include "../../petri/vects.hpp"
#include <typeinfo>
#include <typeindex>
#include <map>
std::map<std::type_index,std::string> ty_ind_map;
void contribute_type(std::type_index i, std::string name){
    ty_ind_map[i] = name;
};

namespace pins {
    // For gcc type_index.name()
    // type
    // for fp : F @return @args E
    // F means is func E is end
    // 
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

};