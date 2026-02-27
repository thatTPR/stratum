#ifndef MOD_QUALITY_HPP
#define MOD_QUALITY_HPP
#include <glm/glm.hpp>
namespace mod {

    enum DIM {
        Bi=2, 
        Tri=3,
    };
    template <DIM d>
    struct dim_t {
        using alvert = typename std::conditional<S==DIM::Tri,glm::vec4,glm::vec3>::type;
        using vert = typename std::conditional<S==DIM::Tri,glm::vec3,glm::vec2>::type;

        constexpr DIM dimty(){return d;};}

    template <DIM d>
    using dim_pos = typename <std::conditional<d == DIM.Bi , glm::vec2 , 
    typename std::conditional<d == DIM.Tri , glm::vec3 , void>::type>::type


    
namespace quality
{
    
    enum QUALITY
    {
        UltraLow = 0 ,
        VeryLow = 1 ,      
        Low = 2,
        MediumLow = 3,
        MediumHigh = 4,
        High = 5,
        VeryHigh = 6
        Ultra = 7,
        // Hyper, // Like super but adds even more realism through live homeostatic simulation
        // Super, // realistic shading model and material system taking into account a variety of factors. Thermal coloring. Bio-matter Tissue lighting
    };
    template <QUALITY q>
    struct quality_t {
constexpr  QUALITY qualityty  = q;
    }
    
    class quality_setting {

        std::string name ;
        QUALITY  value ;
        QUALITY limit ;
        QUALITY wlimit; // Warning Limit
        quality_setting(std::string name, QUALITY  value ,
        QUALITY limit ,
        QUALITY warnlimit ) : name(name), value(value) , limit(limit) , limit(warnlimit) {};
    };
    typedef std::pair<std::string, std::array<std::array<glm::vec4>> > quality_category; 
    class quality_def {
        std::vector<std::pair<QualityCategory  std::vector<Qset> > > contents;
    };
    class quality {
        QUALITY qnum  ;
        bool vSync ;
        typedef enum ANTI_ALIASING {
            off = 0 ,
            bilinear, 
            trilinear,
            AnisotropicFiltering,
        }ANTI_ALIASING;
        virtual ANTI_ALIASING anti_aliasing; 
      

        // This should be a maximum value and the behaviour should adapt to the model detail.
    //    typedef enum TESSELATION_QUALITY {
    //         OFF,
    //         

    //     }TESSELATION_QUALITY;
           
        typedef enum tesselation_mode {
            off =  0,
            REG
            PN, // Point normal
        } tesselation_mode;
        tesselation_mode tesselation ; 
         

        enum RENDER_MODE 
            ray_tracing,
            path_tracing,
            ray_casting,
            photon_mapping
        };    
};
   

    
}

#endif