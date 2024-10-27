#pragma once
#include "../backend/impl_sdl"
#include "../backend/impl_sdl"
#include "../backend/impl_vk"

#include <map>
#include <vector>
#include <glm/vec4.hpp>
using namespace std; 


class widget {
    
    std::vector<widget> childs; 
    virtual glm::vec4 rect  ;
    virtual void add(widget w)  {
        
    };
    virtual inline void insert(widget w , ){

    };
    virtual void operator+(widget w) final{
        this->add(w) ;
    };
    virtual void operator<<(widget w) final {
        this->insert(w) ;
    };

};

enum boxPrimitive {
    TRIANGLE_FAN,
    TRIANGLE_STRIP,
    
};
template <enum topologyPrimitive TP>
class nonRectWidget : widget {

    using topologyPrimitive = ;  
    std::vector<widget> childs ; 
    virtual void addWidget
};

template <senv_c ec , sren_c rc>
class sgui {
    ec env ;
    rc ren ;
    map<> map ; 
    virtual void begin(){

    };
    virtual void end(){

    };
    void run(){

    };
    void push(widget w){
        this->
    };
    void appendChild(widget w){

    };
    void operator+(widget w) final {
        this->tree_vec.add(w);
    };
    void operator<<(widget w) final {
        this->push(w);
    };
};

