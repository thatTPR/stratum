#pragma once
#include <stratum/modules.hpp>
#include <map>
#include <vector>
#include <glm/vec4.hpp>
#include <cstddef>
using namespace std; 

#include <stratum/sgui/sgui_widgets.hpp>
#include <stratum/backend/impl.hpp>
// 
namespace sgui {
    template <class... widgetTs>
    class window : public container<widgetTs...>;
    
    #define SGUI_GAME_WINTS window<viewport> 
    #define SGUI_STRATUM_WINTS window<editor>,window<sidebar>,window<viewport>,window<canvas> 


    template <class... windowTs>
    using Wmanmir = container<widgetTs...>;
    #ifndef SGUI_WINTS
    #define SGUI_WINTS SGUI_GAME_WINTS
    #endif
    Wmanmir<SGUI_WINTS> wmanmir;
    template <class... widgetTs>
    class window : public container<widgetTs...> { // Uses SYS form backend to make docking
        public:
        containerw* parent;
        uint8_t  window; // Index to window handle 
        
        font f; // Global font for the 
        
        window(){parent=&wmanmir;}
    };

    #ifndef CANVAS_LIMIT
    #define CANVAS_LIMIT 10
    #endif
    canvas canvas_arr[CANVAS_LIMIT];
    int c_cur=0;
    canvas* canv;
    int add_canvas(canvas* c){cavas_arr[c_cur+1] = c; c_cur++; w_cur = c;};
    
}