#pragma once
#include <sys.hpp>
#include <filesystem>

#include "stypes/stypes.h"
#include <stypes/Scontainers/stree>

#include "../../lib/imgui/imgui.h"
#include "../../lib/gltf.h"
#include "../../lib/format.cpp"
#include "../../lib/vk_/vk_engine.h"
#include "../../lib/sei.hpp"
#include "../../lib/glm/glm.hpp"
#include "../../lib/glm/vec3.hpp"
#include "../../lib/glm/vec2.hpp"
#include "../../lib/stb/stb_image.h"
#include "../../lib/stb/stb_image_resize.h"
#include "../../lib/stb/stb_image_write.h"

#define NANOSVG_ALL_COLOR_KEYWORDS	// Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION		// Expands implementation
#include "nanosvg.h"
namespace parser {

};

namespace sys {
namespace texture {
    
    struct textureInfo {
        glm::uvec2 resulution ;
        const char* suffix ;
        pipeline::stage stage ; 
        textureInfo(glm::uvec2 res, char* _name , char* _suffix, pipeline::stage _stage) : resolution(res), name(_name) , suffix(_suffix) , stage(_stage) {};
    };
    
    struct texture {
        textureInfo info ;
        image image ;
        virtual void rgba_static_image& get(){return image ;} ;
        texture(glm::uvec2 xy_res , std::string _name  ) : info.resolution(xy_res) , info.name(_name){};
        texture(glm::uvec2 xy_res , std::string _name , char* suffix) : info(textureInfo(xy_res, _name ,suffix)){};
    };
    struct diffuse : texture {
        textureInfo info = textureInfo(void , void , "diffuse", pipeline::stage.DS)
    };
    struct tangent : texture {
        textureInfo info = textureInfo(void , void , "tangent")   ; 
    };
    struct height : texture  {
        textureInfo info = textureInfo(void , void , "height")   ; 
        float scale ;
    };
    struct normal : texture {
        textureInfo info = textureInfo(void , void , "normal" , pipeline::stage.DS); 
    };
    struct normal_dx : texture {
        textureInfo info = textureInfo(void , void , "normal-dx" , pipeline::stage.DS); 
    };
    struct tangent : texture { // Maps normal space to tangent space ( tangent space is the direction the surface is facing centered coordinates)
        textureInfo info = textureInfo(void , void , "tangent" , pipeline::stage.DS); 
    };
    struct albedo : texture  { // Proportion of light reflected
        textureInfo info = textureInfo(void , void , "albedo", pipeline::stage.PS);  
    };
    struct ambient_occlusion : texture  { // Ambient occlusion
        textureInfo info = textureInfo(void , void , "ao", pipeline::stage.PS); 
    };
    struct metallic : texture  {
        textureInfo info = textureInfo(void , void , "metallic",pipeline::stage.PS)  ; 
    };
    struct roughness : texture  {
        textureInfo info = textureInfo(void , void , "roughness", pipeline::stage.PS)  ; 
    };
    struct opacity : texture {
        textureInfo info = textureInfo(void , void , "opacity", pipeline::stage.PS)  ; 
    };
    struct bump : texture {
        textureInfo info = textureInfo(void , void , "bump",  pipeline::stage.PS); // Pixel Shader
    };
    struct specular : texture {
        textureInfo info = textureInfo(void , void , "specular",  pipeline::stage.PS); // Pixel Shader
    };
    struct glow : texture {
        textureInfo info = textureInfo(void , void , "glow",  pipeline::stage.PS); // Pixel Shader
    };
    struct reflection_map : texture { // Can be taken from a reflection element in the case of static elements
        textureInfo info = textureInfo(void , void , "reflection",  pipeline::stage.PS); 
    };
    
    struct heat : texture  { // TODO make it an advances feature
        textureInfo info = textureInfo(void , void , "heat",  pipeline::stage.PS);
    };
    
    
    
    

    // Used when sharing the texture
    struct preview :  texture {
        textureaInfo info = textureInfo(void , void , "preview", void)  ; 
    };



};
namespace lod
{
    struct resource {

    };

    
    struct atlas{ // Can contain uv's and a bunc
        colorType tp  ;
        std::path p ; 
        std::vector<std::tuple<size_t , size_t, size_t , size_t> > sizes ; 
        size_t width , height , channels; 
        unsigned char* image ; 
        
        size_t lod ; // How many downscalings are there 
        std::map<>

        get(uint ind ){

        };
        load_image(){
            this->image = stbi_load(p, &width, &height, &channels, 0);
            stbi

        };
        unsigned char* loadRegion(size_t x, size_t y, size_t xs , size_t ys ){
             if (data == NULL) {
                 // Handle error loading image
                 return NULL;
            }

            // Check if the specified region is valid
            if (x < 0 || y < 0 || x + xs > width || y + ys > height) {
                // Handle invalid region
                return NULL;
            }

            // Calculate the size of the cropped region
            int croppedSize = w * h * channels;
            unsigned char* croppedData = (unsigned char*)malloc(croppedSize);

            // Copy the specified region from the  image
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    for (int c = 0; c < channels; ++c) {
                        int Index = ((y + i) * Width + (x + j)) * Channels + c;
                        int croppedIndex = (i * w + j) * Channels + c;
                        croppedData[croppedIndex] = data[Index];
                    }
                }
            }
            stbi_image_free(data);
            return croppedData;
        };
        unsigned char* loadRegionDownScaling(size_t x, size_t y, size_t xs , size_t ys  , size_t downscaleFactor){ // TODO
                
        };
        void lod(){ // TODO in lod systems there is a a progrssively lower resolution. Everythin is placed below the image
        };        
        atlas(std::path p , std::vector<std::pair<size_t , size_t> > sizes ) :  p(p) , sizes(sizes) {};
    };
    struct file_atlas {
        std::vector<atlas> atlases;

        
    };
    
    typedef enum LOD {
        Normal,
        Downscaled, // All geometry gets reduced
        LowPoly,
        Imposter,        
        SpriteMap, // Simmillar to imposter but is not 3d in any way 
        PointParticle
    } LOD;
    template <base >
    struct Lodsys {
        bool ultra , high , medium ,low , sprite ;
    };
    

  
};

namespace quality
{
    
    typedef enum QUALITY
    {
        // Hyper, // Like super but adds even more realism through live homeostatic simulation
        // Super, // realistic shading model and material system taking into account a variety of factors. Thermal coloring. Bio-matter Tissue lighting
        Ultra = 0,
        VeryHigh = 1
        High = 2,
        MediumHigh = 3,
        MesiumLow = 4,
        Low = 5,
        VeryLow = 6 ,      
    } QUALITY;
    struct quality {
        QUALITY y setting ;

    };
    
    struct Qset {

        std::string name ;
        QUALITY  value ;
        QUALITY Limit ;
        QUALITY wLimit; // Warning Limit
        Qset(std::string name,  )


    };
    typedef std::pair<std::string, rgba_static_image > QualityCategory; 
    struct QualitySettings {
        std::vector<std::pair<QualityCategory  std::vector<Qset> > > contents;
    };

    struct quality {
        bool vSync ;
        typedef enum ANTI_ALIASING {
            bilinear, 
            trilinear,
            AniostropicFiltering,
        }ANTI_ALIASING;
        ANTI_ALIASING antiAliasing; 

        bool tesselation ;
        
        qen tesselation_quality ; 
        bool rayTracing ;
        bool pathTracing ;
        
        getDefaults();
    
    };
    
};
struct pos {
    glm::fvec3 p;
    
}
struct ori {
    glm::fvec o;
    void rotate(glm::vec3 or){
        this->o.xyz = this->o.xyz + or.xyz
    }
    operator+(vec3 x){
        this->rotate(x);
    };
    operator-(vec3 x){

    };
};  

struct coords
{
    virtual glm::fvec3 pos; // x y z
    virtual glm::fvec3 ori ;
 
    glm::vec3f get_pos()
    {
        return this->pos ;
    };

    glm::vec3f get_ori()
    {
        return this->ori ;
    }
    std::pair<glm::vec3f , glm::vec3f> get()
    {
        return {this->pos, this->ori };
    }
};



    struct field ;
    struct Field_2d : field {
        glm::fvec2 x ;
        glm::fvec2 y ;
        glm::angle phi ;
    }
    
    struct Field_3d : field {
        glm::fvec3 x ;
        glm::fvec3 y ;
        glm::angle phi ;
        glm::angle theta ;
    };
    struct Field_Sphere_3d : field{
        glm::fvec3 x ;
        
    };
    struct Field_Sphere_2d : field {
        glm::vec<float,2,glm::defaultp> x ; 
    };
    

    struct physics {
        bool gravity_override ;
        float gravity ;
        float air_current ;
        float magnetic;  

    };
  
    template <DIM T, volume>
    struct physicsField {
        
        float gradient ; 
        physics properties ; 
    };
    
    struct distorsion_3d {
        glm::fvec3 x ;
        glm::fvec3 y ;
        glm::fvec2 orientation ;
    };
    struct distortion_2d {

    };

    struct phsyics_constraint {
        glm::bvec3 pos_lock ;
        glm::bvec3 rot_lock ; 
    };
    struct physical_properties {
        
        float gravitational_mass  ;
        float inertial_mass ;
        // Normalised between 0 and 1 : with 1 meaning perfect elasticity and 0 meaning complete absorbtion ( no moving ⌈)
        bool collision = true ;
        float elasticity ; // Higher value means higher elasticity value above 1 means multiplied 
        
        float friction ;
        float refraction ; 
    };
    struct material_physical_properties {
        bool dynamic
        
        float gravitational_density ;
        float inertial_density ;

        bool collision = true ;
        float elasticity ;  // Higher value means higher elasticity value above 1 means multiplied  

        float friction ;
        float refraction ;

    };


// elems are objects which can be put into to the scene w 
// Images can be rendered 

// This materia rendering scheme can be applied to a mesh
struct material  {
    
    color<rgba32f> Base_Color ;
    color<rgba32f> Subsurface_Color ;
    color<rgba32f> Emmissive_Color ;
    color<rgba32f> ColorOpacity;
    float anisotropy ; // Normalised between -1 and 1  with 0 meaning none
    float Refraction;
    unsigned float metallicity ;
    unsigned float roughness ;
    unsigned float specularity ;
    unsigned float opacity ;
    unsigned float Position_offset ;
    unsigned float Position_displacement ;    
    bool Clear_Coat ;
    bool Ambient_Occlusion ;


    unsigned float friction ;
    phisical_properties 
    void getFriction()
    material load(parser p );

};
struct particle  {
    bool physics ;
    material_physical_properties ; 
    rgba base_color ;
    float density ; 
    dynamicMesh mesh ;
    particle(std::string name ){

    };
   
};
struct fluid  {
    unsigned float anisotropy ; // Normalised between  -1 and 1  with 0 meaning none
    color<rgba32f> Base Color ;
    image::rgba_static_image normal ;
    image::rgba_static_image tangent ;        
    image::rgba_static_image opacity_mask ;
    color<rgba32f> Emmissive Color ;
    unsigned float metallicity ; 
    unsigned float specularity ;
    unsigned float opacity ;

    unsigned float Viscosity ;
    unsigned float Surface_Tension ;
    

    fluid()      
    
};
struct fluidSource {
    fluid f ;
     
};
struct particleSource {

};


typedef enum DIM {
    Bi=2, 
    Tri=3,
    //Quad=4
}DIM;
template <DIM T>
struct vertex {
	glm::vec<T,f64 ,defaultp> position;
	glm::dvec3 normal;
	glm::dvec3 color;
	glm::dvec2 uv;
	static VertexInputDescription get_vertex_description();
};


typedef glm::uvec3 triangle_i ;
typedef glm::uvec4 square_i ;
typedef std::vector<uint> ngon_i ;

typedef std::vector<uint> vertex_group_i ; 

struct physicsVertInfo {
    glm::dvec4 vector ; // XYZW w is speed
    glm::dvec2 div_curl ; 
    glm::dvec3 grad ;
};
struct fluidMesh {
    std::vector<std::pair<vertex, > > vertices ;
    
    float turbulence ;
    double cycleSeconds;

};
struct particleMesh { // Closed bounding box fill everything
    std::vector<vertex> vertices ; 
    std::vector<uint> bounding ;
    std::vector<uint> internal ;
};

struct armature {
    glm::vec3 orientation ;
    glm::vec3 pos; 

    bool orientation_locked ;
    bool locked ;
     
    uint size ;
    std::vector<armature*> start ; // If set to 1 
    std::vector<armature*> end ; 
    
    vertex_group_i vertices ;

    virtual void transform(){
    };

    void setStartOrigin(){this.start = NULL ;     }
};

struct elemInfo {
    std::string name ;
    
};


template <DIM T>
struct elem { 
    std::vector<vertex<T>> vec ;
    std::vector<>
    std::vector<std::pair<elem* , std::pair<std::vector<uint>, std::vector>>   
};
struct icon : elem {

};


template <DIM T>
struct model : elem<T> {
    std::string name ; 

    
    physics::physical_properties physicalProperties ;
    material mat ;




    void snapping(){ // 

    }
    virtual void details();
    virtual void layer();
    virtual void compile():

};
struct flat_model : model<> {
    std::string name ;
    double thickness ; 
};

struct ngon_collection {
    std::map<uint , std::vector<std::vector<uint>>> ngons ; 
    bool checkExists(uint size , std::vector<uint> &ngon_vertices){
        for(const auto &i : this->ngons[size]){
            if (i == ngon_vertices){
                return true
            };
        }
        return false;
    };
    void addNgon(std::vector<uint> &ngon_vertices){
        size_t t = ngon_vertices.size ;
        if(checkExists(t , ngon_vertices))        
    };
    operator[](std::vector<uint> &ngon_vertices){
        
    };
};

enum topologyPrimitive {
    
};
//  VkPrimitiveTopology {
//     VK_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
//     VK_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
//     VK_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
//     VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
//     VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
//     VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
// } VkPrimitiveTopology;

using point_list = std::vector<uint> 
using line_list = std::vector<std::pair<uint,uint>> 
using line_strip = std::vector<uint> 
using triangle_list = std::vector<std::tuple<uint, uint ,uint>> 
using triangle_strip = std::vector<uint> 
using triangle_fan = std::vector<uint> 
typedef enum ADJACENCY{
    T=0,
    F=1
}ADJACENCY ;
using line_list_with_adjacency = std::vector<std::tuple<uint,uint,adjacency>> 
using line_strip_with_adjacency = std::vector<std::tuple<uint , adjacency>> 
using triangle_list_with_adjacency = std::vector<std::tuple<uint,uint,uint, adjacency>> 
using triangle_strip_with_adjacency = std::vector<uint ,adjacency> 
using patch_list = std::vector<>  

template <DIM S>
struct mesh {
	std::vector<vertex<S>> vertices;

    std::vector<triangle_i> triangles ;
    std::vector<square_i> squares;
    std::vector<ngon_i> ngons ; 
    ngon_collection ngon ;
    double thickness ;

    
};
template <DIM S>
struct staticMesh : model { // Does 

};
template <DIM S>
struct dynamicMesh : model {

};
template <DIM S>
struct softBody : dynamicMesh {

};
template <DIM S>
struct cloth : dynamicMesh {
    std::vector<vertex> vertices;
    
};
struct skeletalMesh : model {
};
struct entity : dynamicMesh  
{
    virtual virtual render();
    virtual update();
};
struct flora : entity {

};
// Actors are entities which can be possessed by controlSchemes

struct actor : entity 
{
        mesh mainBody ; 
};
struct fauna : entity {

};
struct human : actor , skeletalMesh 
{
    std::string name ;
};

struct attach_int {
    
    std::pair<uint,std::vector< uint> first ;  
    std::pair<uint,std::vector< uint > sec;
    attach_int::mode one_to_one ;
    update_one_to_one(){
        if(first.second.size == sec.second.size){
            one_to_one = true ;}
            else one_to_one = false ;
    }  ;
};

struct attach_points {
    elem* el ;
    std::vector<uint> verts ; 
};

struct group { // Groups elements together in one shared animation unit .
    
    struct attach {
        typedef enum ATTACH_MODE {
        one_to_one , 
        one_to_multiple, 
        one_to_notmultiple,
        multiple_to_one,
        notmultiple_to_one
         } ATTACH_MODE;

        attach::ATTACH_MODE m ; 
        uint first 
        uint second ; 
        std::vector<uint> verts_second ;
        std::vector<uint> verts_first ; 

    };
    std::string name ;
    std::vector<elem*> elems ;
    
    std::map<uint , std::vector<group::attach> >  ><std::pair<elem*, elem* >> attachments;

    void addAttachment ({uint first_i, std::vector<uint> verts } ,  attach_points sec ){
        if(this->elems.find(first.el) ){

        };
    };

};
struct component {
   
    std::string name; 
    std::vector<elem*> elements; 
    std::vector<group*> groups ;
};
        struct collection {
            std::string name ;
            std::vector<elem*> elems ;
            std::vector<group*> groups ;
            std::vector<component*> component ;
             
};

namespace style {

    template <element T>
    struct style {
        
    };

};

// The scene object is always responsible for loading objects accordingly from the world partitioning system and space partitioning systems

typedef enum PERSPECTIVE {
    ThirdPersonLeft,
    ThirdPersonRight,
    ThirdPersonCenter,
    IsoMetric ,
    FirstPerson,
    orthographic // For 2d but also usable for 3d cad software ; 
}PERSPECTIVE;
namespace camera {
    typedef glm::fvec2 dof ;

    typedef enum EFFECT {
        pixel, // For camera effects applied to pixels 
        texel,
        vertex // For camera effects applied to 
    }EFFECT;
    struct perspective {
        glm::uvec2 center ; 
        glm::uvec2 left ; 
        glm::uvec2 right ; 
        glm::uvec2 up  ;
        glm::uvec2 down ; 
    };
    struct orthoganal : perspective {

    };
    struct effects {
        bool distance_blur; 

    };
    struct camera {

    };
};

struct ThirdPerson {
    
};
struct FirstPerson {

};


struct hud {
};
struct perspective {
    PERSPECTIVE v ;

};
template <DIM d>
struct cloud {
    
};
namespace sp
{
    struct generator {
       
    };
    struct biome {
        std::string name ; 
        generator  ;
        
        std::vector<fauna> fauna ; 
    };
    template<generator gen>
    struct terrain {
            std::vector<std::vector<>>; 
            gen generator ;
            uv uv ;  
         
    };
    template <DIM T>
    struct chunk
    {
        int size ; 
        glm::ivec3 ;
        std::vector<element> elements ;
       
    };
    template <DIM T , size_t s >
    struct chunkingShape {

    };
    
    template <DIM T , size_t s  >
    struct sp  {
       
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

    template <DIM T , size_t levels>
    struct planet : sp  {
        std::string name ; 
        std::vector<scene> scene ; 
        rayleigh rayleig_scattering
        mie mie_scattering ;

    };
    template <DIM T , size_t level>
    struct MegaStruct : planet {

    };
   
    
};


template <DIM d , sp space_part >
struct scene {
    template <DIM d, glm::qualifier Q>
    struct lightSource {
        glm::vec<d,float , Q > position;
        glm::vec<d, float , >
    };
    template <DIM d>
    struct lightSourceChromatic  {

        glm::vec<d,float , glm::defaultp > position;
        glm::vec<d , float,glm::defaultp> position; 
    };
    struct skybox {
        rgba_dyn_image images ;
        std::vector<uint > ind_images;  
    };

    skybox sky; 
    world world_partition ; 
    space space_partition ;
    
    bool pos_culling = true; ;
    bool frustum_culling = true ;  

    void positionalCulling();
    void frustumCulling();
    void backFaceCulling() ; 
    void backFaceCulling() ;
    void occlusion();
    void disocclusion() ;
    virtual scene(stypes::rgba_dyn_image _skybox) skybox(_skybox) {

    };

};
/*
space partitioning .
System for the partitioning entity rendering and loading space into chunks and streaming it to the player accordingly
*/
