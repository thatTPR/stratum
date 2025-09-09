#ifndef MOD_MODEL_HPP
#define MOD_MODEL_HPP
#include "mod_util.hpp"
#include "mod_lod.hpp"
namespace mod{
using point_list = std::vector<uint>; 
using line_list = std::vector<uint>; 
using line_strip = std::vector<uint>;
using triangle_list = std::vector<uint>; 
using triangle_strip = std::vector<uint>; 
using triangle_fan = std::vector<uint>; 

using line_list_with_adjacency = std::vector<uint>; 
using line_strip_with_adjacency = std::vector<uint>;
using triangle_list_with_adjacency = std::vector<uint>;  
using triangle_strip_with_adjacency = std::vector<uint>; 
using patch_list = std::vector<uint>  ;


template <quality::QUALITY q>
struct  material_physical_properties     : quality::quality_t<q>{

    float mass ;
    bool collision_enabled = true ;
    unsigned float collision_dampening ; 
    float friction;
    material_physical_properties( bool _collision_enabled , unsigned float _collision_dampening ,float _friction  ): collision_enabled(_collision_enabled),collision_dampening(_collision_dampening) ,friction(_friction) {};
        material_physical_properties() ;
};


// elems are objects which can be put into to the scene w 
// Images can be rendered 

// This material rendering scheme can be applied to a mesh
struct Tmap {
    image2D image ;
    struct tmapOps{
    bool blendu=true;bool blendv=true;
    float boost;
    float mm_base=0 ; float mm_gain=1;
    glm::vec3 o = glm::vec3(0,0,0);  // Origin offset
    glm::vec3 s = glm::vec3(1,1,1);  // Scale
    glm::vec3 t = glm::vec3(0,0,0);
    uint32_t texres;
    bool clamp =false;
    float bm =1;
    char imfchan ;
    enum TYPE{
        sphere ,cube_top,  cube_bottom,  cube_front,  cube_back,    cube_left,  cube_right 
    }
    TYPE type;
    };
tmapOps ops;
};
template <quality::QUALITY q>
struct material : quality::quality_tf<q>  {
    public:
    std::enable_if<Q>3, image2D>::type map_disp;
    std::enable_if<Q>4, image2D>::type map_bump;
    std::enable_if<Q>2, image2D>::type map_matte;// matte channe
    std::enable_if<Q>2, image2D>::type map_refl;
    std::enable_if<Q>2, image2D>::type map_ambient;
    std::enable_if<Q>2, image2D>::type map_diffuse;
    std::enable_if<Q>2, image2D>::type map_specular;



    std::enable_if<Q>4,image2D>::type normal ;
    std::enable_if<Q>4,image2D>::type tangent   ;  
    image2D opacity_mask;
    glm::vec3 base_Color ;
    image2D baseColorMap;
    image2D subSurfaceColor;
    glm::vec3 subsurface_Color ;
    std::enable_if<Q>2 ,glm::vec3>::type emmisive_Color ;
    // float anisotropy ; // Normalised between -1 and 1  with 0 meaning none
    std::enable_if<Q>2,float>::type refraction ;
    float metallicity ;
    float roughness ;
    float specularity ;
    float opacity ;
    float position_offset ;
    float position_displacement ;    
    bool clear_Coat ;
    bool ambient_occlusion ;
    
    
    void Tangent(){
        using ty = enuvec<map_disp.imageFormat>::ty;
        tangent.imageFormat = image_formats::rgb32f;
        tangent.imageSize = map_disp.imageSize;
         for(uint32_t i=0;i<map_disp.height;i++){
            for(uint32_t j=0;j<map_disp.width;j++){

                uint32_t h  = map_disp.width;
                float hL=0;float hR=0;float hD=0;float hU=0;
                if(j>0){
                    hL = map_disp.data.getAt((j-1) + h*i);
                }
                if(j<map_disp.width){
                    hR = map_disp.data.getAt((j+1) + h*i);
                }
                if(i>0){hD = map_disp.data.getAt( j    + h(i-1));}
                if(i<ma_bump.height){
                    hU = map_disp.data.getAt( j    + h(i+1));
                }
 glm::f32vec3 tangent   = glm::vec3(2.0f * dx, 0.0f, hR - hL); // dP/dx
    glm::f32vec3 bitangent = glm::vec3(0.0f, 2.0f * dy, hU - hD); // dP/dy

    glm::f32vec3 normal = glm::normalize(glm::cross(tangent, bitangent));

               tangent.putAt(i*width + j,normal);
            }
        }
    }
    void Normal(){
        using ty = enuvec<map_disp.imageFormat>::ty;
        normal.imageFormat = image_formats::rgb32f;
        normal.imageSize = map_disp.imageSize;
         for(uint32_t i=0;i<map_disp.height;i++){
            for(uint32_t j=0;j<map_disp.width;j++){
                uint32_t h  = map_disp.width;
                float hL=0;float hR=0;float hD=0;float hU=0;
                if(j>0){
                    hL = map_disp.data.getAt((j-1) + h*i);
                }
                if(j<map_disp.width){
                    hR = map_disp.data.getAt((j+1) + h*i);
                }
                if(i>0){hD = map_disp.data.getAt( j    + h(i-1));}
                if(i<ma_bump.height){
                    hU = map_disp.data.getAt( j    + h(i+1));
                }
float dZdx = (hR - hL) / (2.0f * dx);
    float dZdy = (hU - hD) / (2.0f * dy);

    // Tangent vector along X (U direction)
    glm::f32vec3 tangent(1.0f, 0.0f, dZdx);

    // Bitangent vector along Y (V direction)
    glm::f32vec3 bitangent(0.0f, 1.0f, dZdy);

    // Surface normal = cross product of tangents

    glm::f32vec3 t = glm::normalize(glm::cross(tangent, bitangent));

               map_bump.putAt(i*width + j,t);
            }
        }
    }
   
    material_physical_properties<Q> physical_properties ;
             
};

qmemoryPool<material> materialPool;


float glm::vec2 slope(glm::vec2 s){return s.y/s.x;}

        glm::vec2 signSlope(float s){
            glm::vec2 s(s>0 ? 1.0: -1.0, glm::abs(s)<1 ? 1.0 : -1.0) ;return s;
        };

enum TopologyPrimitive {
    POINT_LIST = 0,
    LINE_LIST = 1,
    LINE_STRIP = 2,
    TRIANGLE_LIST = 3,
    TRIANGLE_STRIP = 4,
    TRIANGLE_FAN = 5,
    LINE_LIST_WITH_ADJACENCY = 6,
    LINE_STRIP_WITH_ADJACENCY = 7,
    TRIANGLE_LIST_WITH_ADJACENCY = 8,
    TRIANGLE_STRIP_WITH_ADJACENCY = 9,
    PATCH_LIST = 10,
}; 

template <DIM d>
using vertA = typename std::conditional<S==DIM::Tri,glm::vec4,glm::vec3>::type;
template <DIM d>
using vert = typename std::conditional<S==DIM::Tri,glm::vec3,glm::vec2>::type;

template <DIM d,bool alpha>
using vertex = typename std::conditional<alpha, vertA<d> , vert<d>>::type;  

template <DIM d,TopologyPrimitive tp,bool alpha>
struct topology_primitive_vec : std::vector<vertex<d,alpha>> {
    using ty = vertex<d,alpha>;
 T& operator[](int s){
            int h = s%size();
            return h<0?data()[size()+s]:s ;}
    using vertty = vertex<d,alpha> ;
    constexpr TopologyPrimitive tpty = tp ;
};

template <DIM d , quality::QUALITY q>
struct    mesh  : dim_t<d> , quality::quality_t<q>{
    using xyzwVert = vertA<d> ; 
    using xyzVert = vert<d> ; 

    // 0 Indexed
    std::vector<xyzwVert> vert; //..pointVertices
    std::vector<xyzVert> tvert; // textures vertices;
    std::vector<xyzVert> nvert; // normal vertices
    std::vector<xyzVert> pvert; // Parameter vertices


    std::vector<std::vector<xyzwVert>> lines;

    typedef glm::mat3x3 facevert;// v n t
    
    std::vector<std::vector<xyzwVert>> facevert;
    std::vector<std::vector<xyzwVert>> facenvert;
    std::vector<std::vector<xyzwVert>> facetvert;
    
    
    struct group {
        std::pair<uint32_t,uint32_t> vert;
        std::pair<uint32_t,uint32_t> tvert;
        std::pair<uint32_t,uint32_t> nvert;
        std::pair<uint32_t,uint32_t> pvert;
         
        std::pair<uint32_t,uint32_t> lines;
        std::pair<uint32_t,uint32_t> faces;
        private: 
        material<Q>* material;
    };
    struct materialGroup: group   {
        std::vector<material<Q>*> materials;
    }
    private:
    std::vector<group> groups ;
    std::vector<materialsGroup> materialsGroup;
    
};
dqmemoryPool<mesh> meshPool;

struct vectorImage {
    std::vector<glm::vec2> vert;
    std::vector<glm::vec2> tvert;
    std::vector<glm::vec3> nvert;

}


template <DIM d>
struct  mesh_prim   : dim_t<d>{
    using xyzwVert = typename std::conditional<S==DIM::Tri,glm::vec4,glm::vec3>::type;
    using xyzVert = typename std::conditional<S==DIM::Tri,glm::vec3,glm::vec2>::type;


    #define PRIMITIVE_ENUM POINT_LIST,LINE_LIST,LINE_STRIP,TRIANGLE_LIST,TRIANGLE_STRIP,TRIANGLE_FAN,LINE_LIST_WITH_ADJACENCY,LINE_STRIP_WITH_ADJACENCY,TRIANGLE_LIST_WITH_ADJACENCY,TRIANGLE_STRIP_WITH_ADJACENCY,PATCH_LIST
    template <typename vert,TopologyPrimitive tp>
    struct prim {
        constexpr TopologyPrimitive tpty =tp ; 
        sdt::vector<vert> d ;
    };

    template <typename vert,TopologyPrimitive... tp>
    using prims = pri::tuple<prim<vert,tp>...> ; 
    
    prims<xyzVert,PRIMITIVE_ENUM> verts;
    prims<xyzVert,PRIMITIVE_ENUM> params;
    prims<xyzVert,PRIMITIVE_ENUM> normals;
    prims<xyzVert,PRIMITIVE_ENUM> texture;
    

    
    mesh_prim(mesh<S>& p){
        if(p.lines.size()>0){bLINES_STRIP = true;
        for(const std::vector<uint32_t> line : p.lines){

            pLINE_STRIP.push_back(line.ve)
        };};
        // Get Mesh
        for(const face& f : p.faces){
            for(uint32_t i = 0; i < f.vertices.size();i++){
                
            };
        };
    };
};
dmemoryPool<mesh_prim> meshPrimPool;





template <DIM d>
struct   dynamicMesh : mesh<S>  , dim_t<d>{
        using xyzwVert = std::conditional<S==DIM::Tri,glm::vec4,glm::vec3>;
    using xyzVert = std::conditional<S==DIM::Tri,glm::vec3,glm::vec2>;    

struct bonePtGroup : vertGroup {
    xyzwVert vert;
    xyzVert pvert;
    xyzVert tvert;

    std::pair<uint32_t,uint32_t> faces;
    std::pair<uint32_t,uint32_t> lines;
    uint16_t boneUp;
    std::vector<uint16_t> boneDown;
    uint16_t boneDown;
    void addPt(uint16_t pt){bonePtIndices.push_back(pt);}
};
std::vector<bonePtgroup> vertGroups;
};




template <DIM d, quality::QUALITY q>
struct    particle : dim_t<d> , quality::quality_t<q>{
    material_physical_properties<q> mpt ; 
    rgba base_color ;
    float density ; 
    dynamicMesh<d,q> mesh ;
};

template <DIM d, quality::QUALITY q>
struct    fluid   : dim_t<d> , quality::quality_t<q>{
    material_physical_properties<q> mpt ; 
    float viscosity;
    rgba base_color ;
    float density ; 
    dynamicMesh<d,q> mesh ;

    fluid(){}
  
};
template <DIM d, quality::QUALITY q>
struct    smoke  : dim_t<d> , quality::quality_t<q>{
    material_physical_properties<q> mpt ; 
    float buoyancy; // -1 -- 1;
};

template <DIM d, quality::QUALITY q, template <DIM , quality::QUALITY > typename T>
struct   source    : dim_t<d> , quality::quality_t<q>{
    T<d,q> p;
    glm::vec3 pos; 
};
template < DIM d, quality::QUALITY q>
particleSource = source<d,q,paricle> ; 
template <DIM d, quality::QUALITY q>>
using fluidSource = source<d,q,fluid> ;
template <DIM d, quality::QUALITY q>>
using smokeSource = source<d,q,fluid> ;

struct animation {
    list<std::vector<glm::vec3>> pts ;

};

template <DIM d,quality::QUALITY q> 
struct  model : mesh<S,Q>  , dim_t<d>{
    struct manifold { // Have a group convention
        std::string name;
        std::pair<uint32_t,uint32_t> vert;
        std::pair<uint32_t,uint32_t> tvert;
        std::pair<uint32_t,uint32_t> nvert;
        std::pair<uint32_t,uint32_t> pvert;
         
        std::pair<uint32_t,uint32_t> lines;
        std::pair<uint32_t,uint32_t> faces;
        std::vector<mesh<S,Q>::materialGroup> materialGroups ;
        std::vector<mesh<S,Q>::group> groups ; 
    };
    std::vector<manifold > manifolds;

    std::vector<animation> anim;
};
dqmemoryPool<model> modelPool 





template <DIM d>
struct  dynamicMesh_prim  : dim_t<d>{

};

template <DIM d>
struct  softBody : dynamicMesh<S>  , dim_t<d>{
    
};
struct cloth : dynamicMesh<> {
    
};
template <DIM d>
struct entity : dynamicMesh<d>  
{
    virtual virtual render();
    virtual update();
};
template <DIM d>
struct  flora : mesh<d>  , dim_t<d>{

};
template <DIM d>
struct  dyn_flora : dynamicMesh<d>  , dim_t<d>{

};
// Actors are entities which can be possessed by controlSchemes


struct actor : model  {
    // Obscure first Person
        
};
struct fauna : model {

};
struct human : model
{
    
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



//





struct Lsys {
        
    typedef int16_t number ;
    typedef int16_t[3] vec ;
    typedef int16_t[4] color ; // TODO add all texturing values;
    typedef int16_t[2] complex;

    enum {
        color,
        
    };
    uint8_t Vsize;
    uint8_t omegaSize;
    uint8_t PSize; 
    int16_t* V ; // Alphabet
    int16_t* omega; // Start
    int16_t* P ; // Production rules
    

};



struct LoadDomainInfo{glm::ivec2 coords, int view_distance , void chunks_distance,int fog };

struct LoadWorldInfo{int index, glm::ivec3 coords };
void load_world_domain(glm::ivec3 coords, int view_distance);


    const rgb BLACK(0, 0, 0);
    const rgb WHITE(255, 255, 255);
    const rgb RED(255, 0, 0);
    const rgb GREEN(0, 255, 0);
    const rgb BLUE(0, 0, 255);
    const rgb YELLOW(255, 255, 0);
    const rgb CYAN(0, 255, 255);
    const rgb MAGENTA(255, 0, 255);
    const rgb ORANGE(255, 165, 0);  
    const rgb PURPLE(128, 0, 128); 
    const rgb BROWN(139, 69, 19); 
    const rgb PINK(255, 192, 203);  
    const rgb GRAY(128, 128, 128);
    const rgb LIME(0, 255, 0);      
    const rgb TEAL(0, 128, 128);    
    const rgb INDIGO(75, 0, 130);   
    const rgb GOLD(255, 215, 0);    


  
    // Variables

    enum normType {
        loop,
        ground,
    }
    template <typename T, T minimum, T maximum , normType nt>
    class norm_val : T{
        static const T min = minimum; 
        static const T max = maximum ;
        static const normType normty = nt; 
        
        T val ;
        public:
        virtual norm_val func(T res){
            if constexpr ( nt == normType::loop){
                return min+ ((res)-min)%(max-min)}
            
            if constexpr( nt == normType::ground){
                return (res)>max ? max :( ( res)<min? min : res ); 
            };
        };
        
        norm_val operator+(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val+rhs.val;
           return func(res);
        };
        norm_val operator-(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val-rhs.val;
            return func(res) ;
        };
        norm_val operator*(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val/rhs.val;
           return func(res);
        };
        norm_val operator/(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val/rhs.val;
            return func(res) ;
        };

    };
    template <typename T>
    using radian = normval<T,0,M_PI,normType::loop>;
    template <typename T>
    using subunit = normval<T,0,1,normType::ground>;
    template <typename T>
    using zsubunit = normval<T,-1,1,normType::ground>;
    
    template <typename T>
    class rangeValue  {
        T val ;
        T minimum ; 
        T maximum ;
        
    };

}
#endif