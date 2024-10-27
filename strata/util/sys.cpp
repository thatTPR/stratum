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
        std::string name ;
        const char* suffix ;
        pipeline::stage stage ; 
        textureInfo(glm::uvec2 res, char* _name , char* _suffix, pipeline::stage _stage) : resolution(res), name(_name) , suffix(_suffix) , stage(_stage) {};
    };
    
    struct texture {
        textureInfo info ;
        rgba_static_image image ;
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
    struct heat : texture  { // TODO make it an advances feature
        textureInfo info = textureInfo(void , void , "heat",  pipeline::stage.PS);
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

    struct reflection_elem : elem , texture {

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

    
    class atlas{ // Can contain uv's and a bunc
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
    class file_atlas {
        std::vector<atlas> atlases;

        
    };
    class lod {
        atlasing a ;   
        std::vector<> ref; 

    };
    
    typedef enum LOD {
        Normal,
        Imposter, // Looks like 3d image but always gets rendered at same angle
        SpriteMap, // Simmillar to imposter but is not 3d in any way 
    } LOD;
    void makeImposter();
    template <base >
    class Lodsys {
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
    
    class Qset {

        std::string name ;
        qen  value ;
        qen Limit ;
        qen wLimit; // Warning Limit
        Qset(std::string name , )


    };
    typedef std::pair<std::string, rgba_static_image > QualityCategory; 
    class QualitySettings {
        std::vector<std::pair<QualityCategory  std::vector<Qset> > > contents;
    };

    class quality {
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
class pos {
    glm::fvec3 p;
    
}
class ori {
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

class coords
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



    class field ;
    class Field_2d : field {
        glm::fvec2 x ;
        glm::fvec2 y ;
        glm::angle phi ;
    }
    
    class Field_3d : field {
        glm::fvec3 x ;
        glm::fvec3 y ;
        glm::angle phi ;
        glm::angle theta ;
    };
    class Field_Sphere_3d : field{
        glm::fvec3 x ;
        
    };
    class Field_Sphere_2d : field {
        glm::vec<float,2,glm::defaultp> x ; 
    };
    

// TODO allign correctly
    class physics {
        bool gravity_override ;
        float gravity ;
        float air_current ;
        float magnetic;  

    };
  
    template <DIM T, volume>
    class physicsField {
        
        float gradient ; 
        physics properties ; 
    };
    
    class distorsion_3d {
        glm::fvec3 x ;
        glm::fvec3 y ;
        glm::fvec2 orientation ;
    };
    class distortion_2d {

    };

    class physics_constraint {
        
        glm::bvec3 xyz_pos_lock ;
        glm::bvec3 xyx_rot_lock ; 
    };
    class physical_properties {
        public:
        
        float gravitational_mass  ;
        float inertial_mass ;
        // Normalised between 0 and 1 : with 1 meaning perfect elasticity and 0 meaning complete absorbtion ( no moving ⌈)
        bool collision_enabled = true ;
        unsigned float collision_dampening ; // Higher value means higher elasticity value above 1 means multiplied 
        
        float friction ;
        float refraction ; 
        physical_properties(float _grav_mass, float _inert_mass , bool _collision_enabled , unsigned float _collision_dampening ,float _friction , float _refraction ): grav_mass(_grav_mass),inert_mass(_inert_mass),collision_enabled(_collision_enabled),collision_dampening(_collision_dampening) ,friction(_friction) ,refraction(_refraction){};
    };
    class material_physical_properties {
        bool dynamic
        
        float gravitational_density ;
        float inertial_density ;

        bool collision_enabled = true ;
        unsigned float collision_dampening ; // 

        float friction ;
        float refraction ;
        material_physical_properties(float _grav_mass, float _inert_mass , bool _collision_enabled , unsigned float _collision_dampening ,float _friction , float _refraction ): grav_mass(_grav_mass),inert_mass(_inert_mass),collision_enabled(_collision_enabled),collision_dampening(_collision_dampening) ,friction(_friction) ,refraction(_refraction){};

    };


// elems are objects which can be put into to the scene w 
// Images can be rendered 

// This materia rendering scheme can be applied to a mesh
class material  {
    
    image::rgba_static_image normal = void;
    image::rgba_static_image tangent = void  ;  
    image::rgba_static_image Opacity_mask= void ;
    color::rgba Base_Color = void;
    color::rgb Subsurface_Color= void ;
    color::rgba Emmisive_Color= void ;
    float anisotropy = void; // Normalised between -1 and 1  with 0 meaning none
    float Refraction=void;
    unsigned float metallicity= void ;
    unsigned float roughness= void ;
    unsigned float specularity= void ;
    unsigned float opacity= void ;
    unsigned float Position_offset = void;
    unsigned float Position_displacement = void;    
    bool Clear_Coat = void;
    bool Ambient_Occlusion = void;

    
    unsigned float friction ;
                
    void set_normal(image::rgba_static_image var){
        this->normal = var;
    };                
    void set_tangent(image::rgba_static_image var){
        this->tangent = var ;
    };                
    void set_Opacity_mask(image::rgba_static_image var){
        this->Opacity_mask = var ;
    };                
    void set_Base_Color(color::rgba var){
        this->Base_Color = var ;
    };                
    void set_Subsurface_Color(color::rgb var){
        this->Subsurface_Color = var ;
    };                
    void set_Emmisive_Color(color::rgba var){
        this->Emmisive_Color = var ;
    };                
    void set_metallicity(unsigned float var){
        this->metallicity = var ;
    };                
    void set_roughness(unsigned float var){
        this->roughness = var ;
    };                
    void set_specularity(unsigned float var){
        this->specularity = var ;
    };                
    void set_opacity(unsigned float opacity){
        this->opacity = var ;
    };                
    void set_Position_offset(unsigned float var){
        this->Position_offset = var ;
    };                
    void set_Position_displacement(unsigned float var){
        this->Position_displacement = var ;
    };                
    void set_anisotropy(float var){
        this->anisotropy = var ;
    };                
    void set_Refraction(float var){
        this->Refraction = var ;
    };                
    void set_Clear_Coat(bool var){
        this->Clear_Coat = var ;
    };                    
    void set_Ambient_Occlusion(bool var){
        this->Ambient_Occlusion = var ;
    };            
    void parserGltf(std::string gltfMaterialPath){

    };

    material(){

    }
};
class particle  {
    std::string name ;

    bool physics ;
    material_physical_properties ; 
    rgba base_color ;
    float density ; 
    dynamicMesh mesh ;
    particle(std::string name ){

    };
   
};
class fluid  {
    unsigned float anisotropy = void; // Normalised between  -1 and 1  with 0 meaning none
    color::rgba Base Color = void;
    image::rgba_static_image normal = void;
    image::rgba_static_image tangent = void;        
    image::rgba_static_image opacity_mask = void;
    color::rgba Emmisive Color = void;
    unsigned float metallicity = void; 
    unsigned float specularity = void;
    unsigned float opacity = void;
    unsigned float Viscosity = void;
    unsigned float Surface_Tension = void;
    

    fluid(){
        
        this- addDataIns(
            {
         
                
            }
        )
        
        
    }
};
class fluidSource {
    fluid f ;
     
};
class particleSource {

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
class fluidMesh {
    std::vector<std::pair<vertex, > > vertices ;
    
    float turbulence ;
    double cycleSeconds;

};
class particleMesh { // Closed bounding box fill everything
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

    void setStartOrigin(){
        this.start = NULL ; 
    }
};

struct elemInfo {
    std::string name ;
    
};


template <DIM T>
class elem { 
    std::vector<vertex<T>> vec ;
    std::vector<>
    std::vector<std::pair<elem* , std::pair<std::vector<uint>, std::vector>>   
};
class icon : elem {

};


template <DIM T>
class model : elem<T> {
    std::string name ; 

    
    physics::physical_properties physicalProperties ;
    material mat ;




    void snapping(){ // 

    }
    virtual void details();
    virtual void layer();
    virtual void compile():

};
class flat_model : model<> {
    std::string name ;
    double thickness ; 
};

class ngon_collection {
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
class mesh {
	std::vector<vertex<S>> vertices;

    std::vector<triangle_i> triangles ;
    std::vector<square_i> squares;
    std::vector<ngon_i> ngons ; 
    ngon_collection ngon ;
    double thickness ;

    
};
template <DIM S>
class staticMesh : model { // Does 

};
template <DIM S>
class dynamicMesh : model {

};
template <DIM S>
class softBody : dynamicMesh {

};
template <DIM S>
class cloth : dynamicMesh {
    std::vector<vertex> vertices;
    
};
class skeletalMesh : model {
};
class entity : dynamicMesh  
{
    virtual virtual render();
    virtual update();
};
class flora : entity {

};
// Actors are entities which can be possessed by controlSchemes

class actor : entity 
{
        mesh mainBody ; 
};
class fauna : entity {

};
class human : actor , skeletalMesh 
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

class group { // Groups elements together in one shared animation unit .
    
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
class component {
   
    std::string name; 
    std::vector<elem*> elements; 
    std::vector<group*> groups ;
};
        class collection {
            std::string name ;
            std::vector<elem*> elems ;
            std::vector<group*> groups ;
            std::vector<component*> component ;
             
};

namespace style {

    template <element T>
    class style {
        
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
    class perspective {
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
    
};
class FirstPerson {

};


class hud {
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
    template <DIM T>
    class chunk
    {
        int size ; 
        glm::ivec3 ;
        std::vector<element> elements ;
       
    };
    template <DIM T , size_t s >
    class chunkingShape {

    };
    
    template <DIM T , size_t s  >
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

    template <DIM T , size_t levels>
    class planet : sp  {
        std::string name ; 
        std::vector<scene> scene ; 
        rayleigh rayleig_scattering
        mie mie_scattering ;

    };
    template <DIM T , size_t level>
    class MegaStruct : planet {

    };
   
    
};


template <DIM d , sp space_part >
class scene {
    template <DIM d, glm::qualifier Q>
    class lightSource {
        glm::vec<d,float , Q > position;
        glm::vec<d, float , >
    };
    template <DIM d>
    class lightSourceChromatic  {
        glm::vec<d,float , glm::defaultp > position;
        glm::vec<d , float> ; 
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
