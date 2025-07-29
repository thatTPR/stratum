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


/*
space partitioning .
System for the partitioning entity rendering and loading space into chunks and streaming it to the player accordingly
*/



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