#pragma once

#include "../lib/gltf.h"
#include "../lib/format.cpp"
#include "../lib/vk_/vk_engine.h"
#include <sei.hpp>
#include <glm/glm.hpp>
#include "../lib/smat/smat.hpp"
#include <material.hpp>

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


#include <type_traits>
#define NANOSVG_ALL_COLOR_KEYWORDS	// Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION		// Expands implementation
#include "nanosvg.h"

#ifndef PREC 
#define PREC defaultp
#endif

#define STR(x) #x



namespace sys {

namespace lod
{
    struct resource {

    };

    
    class atlas{ // Can contain uv's and a bunch other stuff
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
        atlas a ;   
        std::vector<> ref; 

    };
    
    typedef enum LOD {
        Normal,
        Imposter, // Looks like 3d image but always gets rendered at same angle not size though
        Sprite, // Simmillar to imposter but is not 3d in any way 
    
    } LOD;
    void makeImposter();
    
    class Lodsys {
        std::array<>
    };
    

  
};

namespace quality
{
    
    typedef enum QUALITY
    {
        UltraLow = 0 ,
        VeryLow = 1 ,      
        Low = 2,
        MediumLow = 3,
        MediumHigh = 4,
        High = 5,
        VeryHigh = 6
        UltraHigh = 7,
        // Hyper, // Like super but adds even more realism through live homeostatic simulation
        // Super, // realistic shading model and material system taking into account a variety of factors. Thermal coloring. Bio-matter Tissue lighting
    } QUALITY;
  
    
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


        RENDER_MODE render_mode ;
        
        getDefaults();
    
    };
   
    
};




template <DIM T>
class coords
{
    virtual glm::vec<T , float ,defaultp> pos; // x y z
    virtual glm::vec<T, float , defaultp> ori ; // orientation
 
    typeof(pos) get_pos()
    {
        return this->pos ;
    };

    typeof(ori) get_ori()
    {
        return this->ori ;
    }
    std::pair<typeof(pos) , typeof(ori)> get()
    {
        return {this->pos, this->ori };
    }
};

namespace style {
    /*
         Can apply styles modifing shading modes ( textures and tesselation rules)
    Produces another elem most of the time
    Does not modify animations
    */    
    template <elem T>
    class style {
        virtual void apply(T* e){};
    };
    class 
};

// The scene object is always responsible for loading objects accordingly from the world partitioning system and space partitioning systems

typedef enum PERSPECTIVE {
    ThirdPersonLeft,
    ThirdPersonRight,
    ThirdPersonCenter,
    IsoMetric ,
    FirstPerson,
    VR,
    AR
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
    void disocllusion() ;
    virtual scene(stypes::rgba_dyn_image _skybox) skybox(_skybox) {

    };

};
/*
space partitioning .
System for the partitioning entity rendering and loading space into chunks and streaming it to the player accordingly
*/

class structure {

};

namespace buffering { // Buffering of objects for cu

};
namespace pipeline {
   
    class Stage {
        virtual void init();
    };
    class FixedFunction : Stage {
        
        virtual void init(){

        };

    };
    class ShaderStage  : Stage {
        virtual void init(){}
    };
    
   
    #include "apparatus/indexer.hpp"
    template <Indexer i>
    class Resource {
        virtual void buffer ;
        virtual void std::string path  ;
        std::conditional<i , i , void > indexer ;
        p parser ; 
        virtual void load();
        Resource()
    };
   

    class Draw : Stage ;
    class Vertex : Draw  ;
    class Pixel : Draw ; 
    
    class Resource : Stage;
    class DrawMeshTasks : Stage ;
    class Dispatch : Stage ;

   // Forward Declaration for 
    class DrawStage: Draw , FixedFunction {

   };
    class InputAssembler : Vertex , FixedFunction{ 

        bool vertexDepthBuffering ; 

    };
    class VertexShader : Vertex , ShaderStage {

    };
    class TesselationControl : Vertex , ShaderStage{

    };
    class TesselationPrimitiveGenerator  : Vertex , FixedFunction{

    };
    class TesselationEvaluation  : Vertex , ShaderStage {
        TesselationPrimitiveGenerator* TPG ;
    };

    class Geometry  : Vertex , ShaderStage{
        VertexShader* VS ;
        TesselationEvaluation* TE ;
    };
    class VertexPostProcessing  : Vertex , FixedFunction{

    };
    class Rasterization  : Pixel, FixedFunction{

    };
    class EarlyPerFragmentTest  : Pixel, FixedFunction{

    };
    class FragmentShader  : Pixel , ShaderStage{

    };
    class LaterPerFragment  : Pixel , FixedFunctionStage {

    };
    class Blending  : Pixel , FixedFunction{

    };
    
    class DrawObj {
           InputAssembler _InputAssembler ; 
           VertexShader _VertexShader ; 
           TesselationControl _TesselationControl ; 
           TesselationEvaluation _TesselationEvaluation ; 
           Geometry _Geometry ; 
           VertexPostProcessing _VertexPostProcessing ; 
           Rasterization _Rasterization ; 
           EarlyPerFragmentTest _EarlyPerFragmentTest ; 
           FragmentShader _FragmentShader ; 
           LaterPerFragment _LaterPerFragment ; 
           Blending _Blending ; 
           virtual run()

        DrawObj(InputAssembler _InputAssembler,
            VertexShader _VertexShader,
            TesselationControl _TesselationControl,
            TesselationEvaluation _TesselationEvaluation,
            Geometry _Geometry,
            VertexPostProcessing _VertexPostProcessing,
            Rasterization _Rasterization,
            EarlyPerFragmentTest _EarlyPerFragmentTest,
            FragmentShader _FragmentShader,
            LaterPerFragment _LaterPerFragment,
            Blending _Blending)  _InputAssembler(_InputAssembler),
             _VertexShader(_VertexShader),
             _TesselationControl(_TesselationControl),
             _TesselationEvaluation(_TesselationEvaluation),
             _Geometry(_Geometry),
             _VertexPostProcessing(_VertexPostProcessing),
             _Rasterization(_Rasterization),
             _EarlyPerFragmentTest(_EarlyPerFragmentTest),
             _FragmentShader(_FragmentShader),
             _LaterPerFragment(_LaterPerFragment),
             _Blending(_Blending)       
    };
    
    class Index : Resource{
    }
    class Vertex : Resource {

    };

    class Uniform : Resource {

    };
    class UniformTexel : Resource {

    };
    class SampledImages : Resource {

    };
    class Storage : Resource {

    };
    class StorageTexel : Resource {

    };
    class StorageImages : Resource {

    };
    class PushConstants : Resource{

    };
    class DepthStencil : Resource{

    };

    class InputAttachments :  {

    };
    class ColorAttachments : Resource {

    };
    
    template <Index _Index,Vertex _Vertex,Uniform _Uniform,UniformTexel _UniformTexel,SampledImages _SampledImages,Storage _Storage,StorageTexel _StorageTexel,StorageImages _StorageImages,PushConstants _PushConstants,DepthStencil _DepthStencil,InputAttachments _InputAttachments,ColorAttachments _ColorAttachments>
    class IndirectObj {
        std::conditional<_Index == void, void ,Index> Index_stage ; 
        std::conditional<_Vertex == void, void ,Vertex> Vertex_stage ; 
        std::conditional<_Uniform == void, void ,Uniform> Uniform_stage ; 
        std::conditional<_UniformTexel == void, void ,UniformTexel> UniformTexel_stage ; 
        std::conditional<_SampledImages == void, void ,SampledImages> SampledImages_stage ; 
        std::conditional<_Storage == void, void ,Storage> Storage_stage ; 
        std::conditional<_StorageTexel == void, void ,StorageTexel> StorageTexel_stage ; 
        std::conditional<_StorageImages == void, void ,StorageImages> StorageImages_stage ; 
        std::conditional<_PushConstants == void, void ,PushConstants> PushConstants_stage ; 
        std::conditional<_DepthStencil == void, void ,DepthStencil> DepthStencil_stage ; 
        std::conditional<_InputAttachments == void, void ,InputAttachments> InputAttachments_stage ; 
        std::conditional<_ColorAttachments == void, void ,ColorAttachments> ColorAttachments_stage ; 

        IndirectObj()
    };

    class TaskAssembler : DrawMeshTasks , FixedFunctionStage {

    };
    class TaskShader :  DrawMeshTasks, ShaderStage {

    };
    class MeshAssembler :  DrawMeshTasks, FixedFunctionStage {

    };
    class MeshShader :  DrawMeshTasks , ShaderStage {

    };
    template <TaskAssembler _TaskAssembler,
                TaskShader _TaskShader,
                MeshAssembler _MeshAssembler,
                MeshShader _MeshShader >
    class DrawMeshObj {
        std::conditional<_TaskAssembler == void , void , _TaskAssembler > TaskAssembler_stage ; 
        std::conditional<_TaskShader == void , void , _TaskShader > TaskShader_stage ; 
        std::conditional<_MeshAssembler == void , void , _MeshAssembler > MeshAssembler_stage ; 
        std::conditional<_MeshShader == void , void , _MeshShader > MeshShader_stage ; 

    };
    
    class Compute : Dispatch , ShaderStage {

    };
    class DispatchObj : Dispatch {
        std::conditional<_Compute == void ,  void , Compute > Compute_stage ;
    };
    

    class NoPipeLine : PipeLine {

        VkShaderEXT shaderEXT ;
        vkCreateShadersEXT()
    } ;
    
    class PipeLine {
        Do Draw ; IO Indirect ; Dmo DrawMesh ; DO Dispatch ;

        virtual PipeLine( ) ;
        void init()
    };
    class PipeLineVk {

    };

    class RenderEngine {
        std::vector<PipeLine> pls; 
        std::vector<NoPipeLine> nopls;

        
    };
};

class pipelineManager {
    std::vector<pipeline> 
};
// namespace DX {
//     class DX : PipeLine  {
//     struct PipeLineStruct {
//         std::vector<Stage> pipeline_stages; 
//         std::vector<Stage> shader_stages; 
//     };
//     struct PipeLinePointer {
//         std::vector<Stage*> pipeline_stages; 
//         std::vector<Stage*> shader_stages;
//     };
       
//         struct PipeLinePointer PipeLineP ;
        
//         void setPipeLinePointer(){
            
//         };
//         PipeLineStruct getPipelineStruct(){
//             PipeLineStruct buf ; 
//             if(this->pipeLineP == NULL){
               
//                 return buf
//             };
            
//         };
//         PipeLine(IA ia, VS vs , HS hs, TS ts , DS ds , GS gs , SO so , RS rs , PS ps , OM om ) : 
//         _ia(ia), _vs(vs) , _hs(hs), _ts(ts) , _ds(ds) , _gs(gs) , _so(so) , _rs(rs) , _ps(ps) , _om(om) {
//             setPipeLinePointer();
//         };
//     };
// };
}