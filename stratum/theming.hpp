#pragma once

#include <glm/glm.hpp>

#define S_BUTTON_BG     glm::lowp_uvec4(0,0,0,160)
#define S_BUTTON_TINT     glm::lowp_uvec4(70 , 140, 224, 100)
#define S_BUTTON_TINT_ON  glm::lowp_uvec4(70 , 140 ,224, 200 )

#define S_BG            glm::lowp_uvec4(0,0,0,20)

#define S_NODE_BG       glm::lowp_uvec4(0,0,0,200)
#define S_NODE_TINT       glm::lowp_uvec4(0,0,0,200)

namespace theme {
    class widgetTheme {
 
        glm::lowp_uvec4 widget_BG     ; // Used as bg color
        glm::lowp_uvec4 widget_TINT     ;
        glm::lowp_uvec4 text ;
        glm::lowp_uvec4 text_selected ;
        glm::lowp_uvec4 text_highlighted ;
        glm::lowp_uvec4 border ; 
         widgetTheme( glm::lowp_uvec4 _s_widget_BG   , // Used as bg color
        glm::lowp_uvec4 _widget_TINT     ,
        glm::lowp_uvec4 _widget_TINT_ON  ,
        glm::lowp_uvec4 _text ,
        glm::lowp_uvec4 _text_selected ,
        SfeVec4 _border ;  
        ) :widget_BG(_widget_BG), widget_TINT(_s_widget_TINT), widget_TINT_ON(_s_widget_TINT_ON), text(_s_text), text_selected(_s_text_selected) , border(_border){};
    };

    void getDefaultTheme(){
        return  ;
    }
}
    class iconTheme {
        std::string ext ; // Filename extensions
        std::string imagePath ;     
    };

