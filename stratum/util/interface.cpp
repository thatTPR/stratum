#pragma once 
#include <sys.cpp>
#include <apparatus.cpp>
#include "stypes/stypes.h"
#include <typeinfo>

    class brush {
        std::string name = (std::string)typeid(this)  ; 
        unsigned float radius ; 

        void spherePreview(){

        };
        void stroke( sys::elem e ,  std::vector<smat::dvec2> points_on_uv  ){

        };
    };


 
namespace modelling {
    class modelling {

    };
    struct modellingEdit {

    };
    struct sculptingEdit {

    };
    struct paintingEdit {
        
        
    };
    struct brushEdit{

    };

};

namespace destruction {

};

namespace graph {

};

namespace canvas {
    class canvas {

    };
    class canvas_graph {
        // Render Canvas View providing gizmo
        enum modes {
            SideWays,
            Paralle
        };

    };
};
