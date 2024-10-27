// Pipeline management 
#pragma once 
#include "lib/vk/vulkan.h"
#include "sys.hpp"    
#include "sys_obj.hpp"
#include "sys_phy.hpp"

    template <class obj >
    class VkStage : Stage {
        obj o ; 
        virtual void init() ;
        virtual void run() ; 
    };
    
    class FixedFunction : VkStage {
        
        virtual void init(){

        };

    };
    class ShaderVkStage  : VkStage;
    template <Parser p>
    class Resource {
        virtual void buffer ;
        virtual void std::string path  ;
        p parser ; 
        virtual void load();
        Resource()
    };
    class Resource;

    class Draw : VkStage ;
    class Vertex : Draw  ;
    class Pixel : Draw ; 
    
    class Resource : VkStage;
    class DrawMeshTasks : VkStage ;
    class Dispatch : VkStage ;

    template 
    class InputAssembler : Draw , FixedFunction{ 
        bool vertexDepthBuffering ; 

    };
    class VertexShader : Draw , ShaderVkStage {

    };
    class TesselationControl : Draw , ShaderVkStage{

    };
    class TesselationPrimitiveGenerator  : Draw , FixedFunction{

    };
    class TesselationEvaluation  : Draw , ShaderVkStage {

    };

    class Geometry  : Draw , ShaderVkStage{

    };
    class VertexPostProcessing  : Draw , FixedFunction{

    };
    class Rasterization  : Draw, FixedFunction{

    };
    class EarlyPerFragmentTest  : Draw, FixedFunction{

    };
    class FragmentShader  : Draw , ShaderVkStage{

    };
    class LaterPerFragment  : Draw , FixedFunctionVkStage {

    };
    class Blending  : Draw , FixedFunction{

    };
    template <InputAssembler _InputAssembler,
            VertexShader _VertexShader,
            TesselationControl _TesselationControl,
            TesselationEvaluation _TesselationEvaluation,
            Geometry _Geometry,
            VertexPostProcessing _VertexPostProcessing,
            Rasterization _Rasterization,
            EarlyPerFragmentTest _EarlyPerFragmentTest,
            FragmentShader _FragmentShader,
            LaterPerFragment _LaterPerFragment,
            Blending _Blending>
    class DrawObj {
            std::conditional<_InputAssembler == void , void , _InputAssembler> InputAssembler_stage ; 
            std::conditional<_VertexShader == void , void , _VertexShader> VertexShader_stage ; 
            std::conditional<_TesselationControl == void , void , _TesselationControl> TesselationControl_stage ; 
            std::conditional<_TesselationEvaluation == void , void , _TesselationEvaluation> TesselationEvaluation_stage ; 
            std::conditional<_Geometry == void , void , _Geometry> Geometry_stage ; 
            std::conditional<_VertexPostProcessing == void , void , _VertexPostProcessing> VertexPostProcessing_stage ; 
            std::conditional<_Rasterization == void , void , _Rasterization> Rasterization_stage ; 
            std::conditional<_EarlyPerFragmentTest == void , void , _EarlyPerFragmentTest> EarlyPerFragmentTest_stage ; 
            std::conditional<_FragmentShader == void , void , _FragmentShader> FragmentShader_stage ; 
            std::conditional<_LaterPerFragment == void , void , _LaterPerFragment> LaterPerFragment_stage ; 
            std::conditional<_Blending == void , void , _Blending> Blending_stage ; 

            void init(){

            };
         
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

    class TaskAssembler : DrawMeshTasks , FixedFunctionVkStage {

    };
    class TaskShader :  DrawMeshTasks, ShaderVkStage {

    };
    class MeshAssembler :  DrawMeshTasks, FixedFunctionVkStage {

    };
    class MeshShader :  DrawMeshTasks , ShaderVkStage {

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
    
    class Compute : Dispatch , ShaderVkStage {

    };
    template <Compute _Compute>
    class DispatchObj : Dispatch {
        std::conditional<_Compute == void ,  void , Compute > Compute_stage ;
    };
    
    class NoPipeLineVk : NoPipeLine {

        VkShaderEXT shaderEXT ;
        vkCreateShadersEXT()
    } ;
    template <DrawObj DO,  IndirectObj IO , DrawMeshObj DMO , Dispatch DO>
    class PipeLineVk : Pipeline {
        DO Draw ; IO Indirect ; DMO DrawMesh ; DO Dispatch ;
        void init override (){

        };
    };
    class PipeLineVk : PipeLine {

    };
    class RenderEngineVk : RenderEngine {
        std::vector<PipeLineVk> pls; 
        std::vector<NoPipeLine> nopls;


    };
}
