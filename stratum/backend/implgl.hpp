#include <petri/list>
#include <stratum/modules.hpp>

#include <stratum/petri/list> 

#ifndef SHADMODS 
struct gpu_info {

    bool robustBufferAccess       ,  //Ensures bounds-checking for buffer accesses.
     fullDrawIndexUint32      ,  //Allows 32-bit indices for drawing.
     geometryShader           ,  //Supports geometry shaders.
     tessellationShader       ,  //Supports tessellation shaders.
     multiDrawIndirect        ,  //Allows multiple draw calls in a single command.
     wideLines                ,  //Enables rendering wide lines.
     largePoints              ,  //Enables rendering large points.
     textureCompressionETC2   ,  //ETC2 texture compression support.
     sparseBinding            ,  //Supports sparse resources (like sparse textures).


    bool ray_tracing_pipeline; /*
Adds support for ray tracing features.
Features structure: VkPhysicalDeviceRayTracingPipelineFeaturesKHR.
    */
    bool descriptor_indexing;/*
Adds support for descriptor indexing.
Features structure: VkPhysicalDeviceDescriptorIndexingFeatures.
    */    
    bool multiview;
/*
Adds support for rendering to multiple views (e.g., for VR).
Features structure: VkPhysicalDeviceMultiviewFeatures.
*/
    bool sampler_filter_minmax;

// Adds support for min/max filtering.
// Features structure: VkPhysicalDeviceSamplerFilterMinmaxFeaturesEXT.
 
};
#define PIPELINE_LAYOUT_CREATE_INFO
#define Buffer
#define Size

template <mod::shader_types sty, typename shmod,typename... shadMods>
struct get_tys {
    using type = std::conditional<shmod::sty == sty, ,get_tys<sty,shadMods>;
}; 
template <mod::shader_types sty, typename shmod>
struct get_tys {
    using type = std::conditional<shmod::sty == sty, shmod,emptyShmod>;
}; 


struct glimpl {


    using shader_type = mod::shader_type;
    using image_format = mod::image_formats;
    using topology = mod::TopologyPrimitive;
    using trasnform_image = mod::transform_image;
    using descriptor_type = mod::BindingType ; 
    using usage_flag = mod::BindingType;
    using image_usage = mod::image_usage;
    using share_mode = mod::shareMode;

    using Pipeline = void ;
    using wsurfaces = void;
    
    using imageBuffer = void;

    using imageBufferIter = pri::list<imageBuffer>::iter ;

    using shadModTup = pri::utuple<pri::list<shadMods>...> ;
    shadModTup shaderModules;

    pri::list<Pipeline> pipelines;
    pri::list<uint> winsurfaces;
    pri::list<device> devices;
    


virtual image_foramt get_format(mod::image_format imf){return imf};
virtual void bindImage(mod::image2D& im) ;

using imagety = void;
pri::list<imagety> imagePool ;

virtual void create_image2d( mod::image2D& im,mod::imageOpts opts= imageOpts());
using shaderStageBits = void;
virtual void getShaderType(shader_type STAGE);


     
virtual void createSwapChain();
virtual void set_up_dev();
virtual void create_fullscreen();
virtual void get_gpu_info(gpu_info gpinfo);
virtual _shader load_shader(const uint32_t shader[] );

template <mod::shader_type sty,typename buf,mod::BindingType bt>
virtual bool shaderModule(mod::shaderModule<sty,buf,bt>* module);
template <typename buf,mod::BindingType bt>
virtual int grModule(mod::grModule<buf,bt>* module);
template <typename buf,mod::BindingType bt>
virtual int allModule(mod::allModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int vertModule(mod::vertModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int fragModule(mod::fragModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int geomModule(mod::geomModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int tescModule(mod::tescModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int teseModule(mod::teseModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int compModule(mod::compModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int taskModule(mod::taskModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int meshModule(mod::meshModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rgenModule(mod::rgenModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rintModule(mod::rintModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rahitModule(mod::rahitModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rchitModule(mod::rchitModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rmissModule(mod::rmissModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rcallModule(mod::rcallModule<buf,bt>* module);


void updateUniform(device* dev, shaderModule* m );
void descriptor_set();
void descriptor_pool();
void create_swapchain();

virtual void load_SSBO(_shader shader,auto* buffer);
virtual void load_UBO(_shader shader,auto* buffer);
virtual void draw(_stage ;);
virtual void blend();

void exec(shader_module module) final{};
void pipeline_create(size_t shad_size , shader_module* modules )final{
    for(int i =0; i<shad_size;i++){
        this->
    };
};
};


#ifdef STRATA_VK
#include <strata/backend/impl_vk.hpp>
template <typename... shadMods>
using gl_impl= vk_impl<shadMods...>;
#endif 
#ifdef STRATA_DX
#include <strata/backend/impl_dx.hpp>
template <typename... shadMods>
using gl_impl= dx_impl<shadMods...> ;
#endif
#ifdef STRATA_GL
#include <strata/backend/impl_gl.hpp>
template <typename... shadMods>
using gl_impl = gl_impl<shadMods...>;
#endif
#ifdef IMPL_CL
#include <strata/backend/impl_cl.hpp>
template <typename... shadMods>
using gl_impl = cl_impl<shadMods...> ;
#endif

gl_impl gl;
