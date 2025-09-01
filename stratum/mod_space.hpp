#ifndef MOD_SPACE_HPP
#define MOD_SPACE_HPP
#include "mod_util.hpp"
#include "mod_lod.hpp"
namespace  mod
{
    
template <DIM d>
struct coords
{
    std::conditional<T==2,glm::vec2,glm::vec3>::type pos; // x y z
    std::conditional<T==2,glm::vec2,glm::vec3>::type ori ; // orientation
};


// The scene object is always responsible for loading objects accordingly from the world partitioning system and space partitioning systems

enum PERSPECTIVE {
    ThirdPersonLeft,
    ThirdPersonRight,
    ThirdPersonCenter,
    IsoMetric ,
    FirstPerson,
    VR,
    AR
};
namespace camera {
    typedef glm::fvec2 dof ;

    enum EFFECT {
        pixel, // For camera effects applied to pixels 
        texel,
        vertex // For camera effects applied to 
    }EFFECT;
    
    class perspective {
        glm::mat4 ; 
        glm::uvec2 center ; 
        glm::uvec2 left ; 
        glm::uvec2 right ; 
        glm::uvec2 up  ;
        glm::uvec2 down ; 
    };
    class orthoganal : perspective {

    };
    struct effects {
        bool distance_blur; 

    };
    class camera {

    };
};

class ThirdPerson {
    
    float fov,aspect,znear,zfar;
    glm::mat4 getMatrix(glm::vec3 pos){
        mat = glm::perspective(fov,aspect,znear,zfar);
    };
    void move( glm::vec3 amount , glm::mat4 projectionMatrix  ){

    };
};
class FirstPerson {
    glm::mat4 mat; 

    void getMatrix()
};



class perspective {
    PERSPECTIVE v ;

};
template <DIM d>
class cloud {
    
};
namespace sp
{
    class generator {
       
    };
    class biome {
        std::string name ; 
        generator  ;
        
        std::vector<fauna> fauna ; 
    };
    template<generator gen>
    class terrain {
            std::vector<std::vector<>>; 
            gen generator ;
            uv uv ;  
         
    };
    template <DIM d>
    class chunk
    {
        int size ; 
        glm::ivec3 ;
        std::vector<element> elements ;
       
    };
    template <DIM d , size_t s >
    class chunkingShape {

    };
    
    template <DIM d , size_t s  >
    class sp  {
       
         resourceParser ; 
        int maxDistance;

        uint depth ; // Chunk tree depth
        uint min  ;
        uint max ;

        std::vector<sp* > space_partitionings ;

        virtual glm::vec<3 ,float , defaultp   > chunkCoord ; // x 
        virtual source
        
        void positionalCulling(); // Cull everything based on positional perspective
        void perspectiveCulling(); // Cull everything not in the view frustum
        void disOocclusion();

    };

    
    
};


template <DIM d  >
class scene {
    using xyzVert = std::conditional<S==DIM::Tri,glm::vec3,glm::vec2>::type;
    template < typename T>
    struct coorded {
        
        T data;
        xyzVert position; 
        xyzVert orientation;
    };
    template <typename T>
    struct coordedResized : coorded<T> {
        float sizefactor;
    };

    struct lightSource : coorded<T>{
        float intensity;
    } ;


    class lightSourceChromatic : lightSource {
        glm::vec3 color ;
    };
    struct skybox {  
        image2D im;
        glm::vec3 rotation;
        glm::vec3 rotationAxis;  
        void rotate(uint32_t time);
    };
    struct dynamicSkyBox {

    };

    skybox sky; 
    world world_partition ; 
    space space_partition ;

    std::vector<named<model>* > modoels;
    
    bool pos_culling = true; ;
    bool frustum_culling = true ;  

    void positionalCulling();
    void frustumCulling();
    void backFaceCulling() ; 
    void backFaceCulling() ;
    void occlusion();
    void disocllusion() ;
    virtual scene(stypes::rgba_dyn_image _skybox) skybox(_skybox) {

    };

};
dmemoryPool<scene> scenePool;
}
#endif