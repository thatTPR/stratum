#pragma once
#include "_mode.hpp"
#include "../../../lib/sei_settings.hpp"
#include "../stypes/stypes.h"
#include <vector>
using namespace std ;
class tool { // Left toolbar of veiew
    std::string name ;
    virtual void* im ; // Image of the 
    virtual void* pt ; // 
};
template <>
class widget { // Top corners of view usally. control 

};
template <>
class gizmo {  // Gizmos are on top of any geometry in the scene

};

class view {
    virtual void render();
};
class primary : view {
    std::vector<tool> tools ; 
    std::vector<widget> widgets ; 
    std::vector<gizmo> gizmos ;  

    
    void contributeTool(tool t){

        this->tools.push_back(t);
    };
    void contributeWidget(widget w){
        this->widgets.push_back(w);
    };
    void contributeGizmo(gizmo g){
        this->gizmos.push_back(t);
    };
    virtual void render();

    primary(std::array<tool> t , std::array<widget> w )
};
class sidebar : view {
    std::vector<view> views ;
    virtual void contributeView(view v ) ;
    sidebar(view ...vs ) ;
};


class mode {
    std::string name ;
    sidebar left , right ;
    primary center ;
    virtual void contributeView(view v);
    virtual void contributeSideBarView(sidebar* sb );
};
template <mode ...m>
class modeSys {
    std::vector<mode> m ;
    void contributeMode(mode mo ){
        this->m.push_back(mo) ;
    };
}
modeSys ms; 
void contributeMode(mode m ){
    ms.contributeMode(m) ;
};