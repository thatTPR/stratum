#pragma once
#include "../backend/impl_sdl"
#include "../backend/impl_sdl"
#include "../backend/impl_vk"

#include <map>
#include <vector>
#include <glm/vec4.hpp>
using namespace std; 



enum boxPrimitive {
    TRIANGLE_FAN,
    TRIANGLE_STRIP,
    
};

template <senv_c ec , sren_c rc>
class sgui {
    ec env ;
    rc ren ;
    map<> map ; 

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

