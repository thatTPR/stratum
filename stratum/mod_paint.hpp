#ifndef MOD_PAINT_HPP
#define MOD_PAINT_HPP
#include "mod_util.hpp"
#include <array>
namespace mod
{
namespace paint {
    enum paintTy {
        
        solid,
        gradientLinear,
        gradientSweep,
        gradientRadial,
        Affine,
        rotate,
        skew,
        rotateAroundCenter,
        skewAroundCenter,
        translate,

    };

    struct toFloat {

        float* get_flt_arr(){float* start =(float*)&v}
    }
    struct colorStop : toFloat{glm::vec4 col;float alpha;}

    typedef std::vector<colorStop> colorLine ;

    template <typename T>
    struct var {
        using ty = T;
        T data;
        std::vector<T> vars;
    };
    template <typename T> struct ColorLine {T data;colorLine cl;}
    template <typename T> struct VarColorLine {T data;var<colorLine> cl;}
    
    // using  paintVarSweepGradient=  VarColorLine::mod::paint::var<mod::paint::gradientSweep>>
    
    typedef colorStop solid;
    
    struct gradientLinear : toFloat {
        glm::vec2 p1;
        glm::vec2 p2;
        glm::vec2 rotation;
        std::array<float,6> getFlts(){std::array<float,6>(p1.x,p1.y,p2.x,p2.,rotation.x,rotation.y);} 
    };
    struct gradientSweep : toFloat{
        glm::vec2 center;
        float startAngle;
        float endAngle;
        std::array<float,4> getFlts(){std::array<float,4>(center.x,center.y,startAngle,endAngle);} 
    };
    struct gradientRadial: toFloat {
        glm::vec2 startCenter;
        float rad1;
        glm::vec2 endCenter;
        float rad2;

    };
    struct Affine: toFloat {
        glm::vec2 xbasis;
        glm::vec2 ybasis;
        glm::vec2 dxdy;
    };
   
    
    // Transforms
    struct scale :  glm::vec2 ,toFloat {} ;
    
    struct scaleAroundCenter : toFloat {
        glm::vec2 d; 
        glm::vec2 center;
    };

    struct rotate :float, toFloat;

    struct rotateAroundCenter : toFLoat {
        rotate d;
        glm::vec2 center;
    };
    struct skew :toFLoat, glm::vec2  {};
    struct skewAroundCenter: toFloat{
        skew d;
        glm::vec2 center;
    };
    
    struct translate : toFloat , glm::vec2 {};

    struct fillPaint {}

    struct paints : toFloat{
        int psize;
        glm::ivec psoffs[16];
    };
}
}
#endif
