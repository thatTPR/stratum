#include <variant>
#include "glm/glm.hpp"
#include "sys.hpp"
#include "../stypes/"
using namespace quality ;
using namespace pipeline ;
namespace texture {
    
    struct textureInfo {
        glm::uvec2 resulution ;
        std::string name ;
        const char* suffix ;
        textureInfo(glm::uvec2 res, char* _name , char* _suffix) : resolution(res), name(_name) , suffix(_suffix)  {};
    };
    template <image >
    typedef struct texture {
        textureInfo info ;
        virtual image::rgba_static_arr image ;
        image::rgba_static_arr get(){return image ;} 
        texture(textureInfo _info, image::rgba_static_arr _image) : info(_info) , image(_image) {};
    }texture ;
    typedef struct dyn_texture : texture {
        textureInfo info ;

    }dyn_texture;
    typedef struct diffuse : texture {
        textureInfo info = textureInfo(NULL , NULL , "diffuse", pipeline::stage.DS)
    }diffuse ;
    struct tangent : texture {
        textureInfo info = textureInfo(NULL , NULL , "tangent")   ; 
    };
    struct height : texture  {
        textureInfo info = textureInfo(NULL , NULL , "height")   ; 
        float scale ;
    };
    struct normal : texture {
        textureInfo info = textureInfo(NULL , NULL , "normal" ); 
    };
    struct normal_dx : texture {
        textureInfo info = textureInfo(NULL , NULL , "normal-dx" ); 
    };
    struct tangent : texture { // Maps normal space to tangent space ( tangent space is the direction the surface is facing centered coordinates)
        textureInfo info = textureInfo(NULL , NULL , "tangent" ); 
    };
    struct albedo : texture  { // Proportion of light reflected
        textureInfo info = textureInfo(NULL , NULL , "albedo");  
    };
    struct ambient_occlusion : texture  { // Ambient occlusion
        textureInfo info = textureInfo(NULL , NULL , "ao"); 
    };
    struct metallic : texture  {
        textureInfo info = textureInfo(NULL , NULL , "metallic");  
    };
    struct roughness : texture  {
        textureInfo info = textureInfo(NULL , NULL , "roughness"); 
    };
    struct opacity : texture {
        textureInfo info = textureInfo(NULL , NULL , "opacity"); 
    };
    
    struct bump : texture {
        textureInfo info = textureInfo(NULL , NULL , "bump");
    };
    struct specular : texture {
        textureInfo info = textureInfo(NULL , NULL , "specular"); // Pixel Shader
    };
    struct glow : texture {
        textureInfo info = textureInfo(NULL , NULL , "glow"); // Pixel Shader
    };
    struct reflection_map : texture { // Can be taken from a reflection element in the case of static elements
        textureInfo info = textureInfo(NULL , NULL , "reflection");
    };

    struct reflection_elem : elem , texture {

    };

    struct heat : texture  { 
        textureInfo info = textureInfo(NULL , NULL , "heat",  pipeline::stage.PS);
    };
    
    

    // Used when sharing the texture
    struct preview :  texture {
        textureInfo info = textureInfo(NULL , NULL , "preview", NULL)  ; 
    };

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
using patch_list = std::vector<uint>  // TODO


typedef enum DIM {
    Bi=2, 
    Tri=3,
}DIM;
template <DIM t>
using dim_pos = typename <std::conditional<t == DIM.Bi , glm::vec2 , 
                typename std::conditional<t == DIM.Tri , glm::vec3 , void>::type>::type
struct material_physical_properties {
    bool dynamic
    float gravitational_density ;
    float inertial_density ;
    bool collision_enabled = true ;
    unsigned float collision_dampening ; // 

        float friction ;
        float refraction ;
        material_physical_properties(float _grav_mass, float _inert_mass , bool _collision_enabled , unsigned float _collision_dampening ,float _friction , float _refraction ): grav_mass(_grav_mass),inert_mass(_inert_mass),collision_enabled(_collision_enabled),collision_dampening(_collision_dampening) ,friction(_friction) ,refraction(_refraction){};
        material_physical_properties() ;
    };


// elems are objects which can be put into to the scene w 
// Images can be rendered 

// This materia rendering scheme can be applied to a mesh
struct material  {
    public:
    std::array<std::array<glm::vec4>> normal ;
    std::array<std::array<glm::vec4>> tangent   ;  
    std::array<std::array<glm::vec4>> opacity_mask  ;
    glm::vec4 base_Color ;
    glm::vec4 subsurface_Color ;
    glm::vec4 emmisive_Color ;
    float anisotropy ; // Normalised between -1 and 1  with 0 meaning none
    float refraction ;
    unsigned float metallicity ;
    unsigned float roughness ;
    unsigned float specularity ;
    unsigned float opacity ;
    unsigned float position_offset ;
    unsigned float position_displacement ;    
    bool clear_Coat ;
    bool ambient_occlusion ;
  
    material_physical_properties<quality q> physical_properties ;
             
    void parserGltf(std::string gltfMaterialPath){

    };

    material(){

    }
};
struct particle  {
    std::string name ;

    bool physics ;
    material_physical_properties ; 
    rgba base_color ;
    float density ; 
    dynamicMesh mesh ;
    particle(std::string name ){

    };
   
};
struct fluid  {
    unsigned float anisotropy = void; // Normalised between  -1 and 1  with 0 meaning none
    color::rgba Base Color = void;
    image::rgba_static_image normal = void;
    image::rgba_static_image tangent = void;        
    image::rgba_static_image opacity_mask = void;
    color::rgba Emmisive Color = void;
    float metallicity = void; 
    float specularity = void;
    float opacity = void;
    float transparency ;
    float viscosity = void;
    unsigned float surface_tension = void;
    

    fluid(){
        
        this- addDataIns(
            {
         
                
            }
        )
        
        
    }
};

struct particle {
    float size ;
    float density ;

};
struct fluidSource {
    fluid f ;
     
};
struct particleSource {

};



template <DIM T>
struct vertex {
	glm::vec<T,float ,defaultp> position;
	glm::vec<T, float , defualtp> normal;
	glm::vec<T , float ,defaultp>;
	glm::vec2 uv;
	static VertexInputDescription get_vertex_description();
};


typedef glm::uvec3 triangle_i ;
typedef glm::uvec4 square_i ;
typedef std::vector<uint> ngon_i ;



struct physicsVertInfo {
    glm::dvec4 vector ; // XYZW w is speed
    glm::dvec2 div_curl ; 
    glm::dvec3 grad ;
};
struct fluidMesh { // This is used for water bodies and smoke and the like
    std::vector<std::pair<vertex, > > vertices ;
    
    float turbulence ;
    double cycleSeconds = 2 ; // Default is 

};
struct particleMesh { // Closed bounding box fill everything
    std::vector<vertex> vertices ; 
    std::vector<uint> bounding ;
    std::vector<uint> internal ;
};
;
typedef std::vector<uint> vert_group ; 
template <DIM T>
typedef struct armature {

    glm::vec<T , float , defaultp> orientation ;
    glm::vec<T , float  , defaultp> pos; 

    bool orientation_locked ;
    bool locked ;
     
    uint size ;
    uint start_size ; 
    uint end_size ;

    std::vector<uint> start ; // If set to 1 
    std::vector<uint> end ; 
    
    std::vector<uint > startVertices ;
    std::vector<uint> endVertices ;
    std::vector<uint> midVertices ; 
    
    virtual void transform(){
    };

    void setStartOrigin(){
        this.start = NULL ; 
    }
}armature;

struct elemInfo {
    
    std::string name ;
    
};

struct elemSource {

};
template <DIM T>
struct elem { 

    std::vector<vertex<T>> vec ;
    std::vector<uint> uv ;
    std::vector<armature<T>> vec ;
    std::vector<Texture>

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
struct flat_model : model<DIM> {
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

template <DIM S>
struct mesh {
	std::vector<vertex<S>> vertices;

    point_list point_l ;
    line_list line_s ;
    line_strip line_strip ;

    std::vector<triangle_i> triangles ;
    std::vector<square_i> squares;
    std::vector<ngon_i> ngons ; 
    ngon_collection ngon ;
    double thickness ;

    
};
template <DIM S>
struct staticMesh : mesh { // Does 

};
template <DIM S>
struct dynamicMesh : mesh {

};
template <DIM S>
struct softBody : dynamicMesh {

};
template <DIM S>
struct cloth : dynamicMesh {
    std::vector<vertex> vertices;
    
};
template <DIM S>
struct wire : dynamicMesh{
    std::vector<vertex> vertices ; 
    float stiffness ;
    float elasticity ; 
};
struct entity : dynamicMesh  
{
    virtual virtual render();
    virtual update();
};
struct flora : elem {

};
// Actors are entities which can be possessed by controlSchemes

struct actor : entity 
{
        mesh mainBody ; 
};
struct fauna : entity {

};
struct human : entity 
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
// Allows the creation and instantiation of objects in scene based on a base elem
struct chain { 
    struct ref {
        coords ; 
    };
    elem base ; 
    std::vector<elem>  ; 
};

