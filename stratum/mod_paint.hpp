#ifndef MOD_PAINT_HPP
#define MOD_PAINT_HPP
#include "mod_util.hpp"
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
    struct colorStop {glm::uvec4 col;float alpha;}

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
    
    struct gradientLinear{
        glm::vec2 p1;
        glm::vec2 p2;
        glm::vec2 rotation;
    };
    struct gradientSweep{
        glm::vec2 center;
        float startAngle;
        float endAngle;
    };
    struct gradientRadial{
        glm::vec2 startCenter;
        unsigned float rad1;
        glm::vec2 endCenter;
        unsigned float rad2;

    };
    struct Affine{
        glm::vec2 xbasis;
        glm::vec2 ybasis;
        glm::vec2 dxdy;
    };
   
    
    // Transforms
    typedef glm::vec2 scale;
    
    struct scaleAroundCenter {
        glm::vec2 d; 
        glm::vec2 center;
    };

    typedef float rotate ;
    };
    struct rotateAroundCenter {
        rotate d;
        glm::vec2 center;
    };
    typedef glm::vec2  skew;
    struct skewAroundCenter{
        skew d;
        glm::vec2 center;
    };
    
    typedef glm::vec2 translate;

    struct paint {

    };
    struct paintPrim {
        
    };

}
} // namespace mod
#endif
