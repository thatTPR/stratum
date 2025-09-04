#include <petri/list>
#include <stratum/modules.hpp>

#include <stratum/petri/list.hpp> 

#ifndef SHADMODS 
struct gpu_info {

    bool robustBufferAccess       ,  //Ensures bounds-checking for buffer accesses.
    bool fullDrawIndexUint32      ,  //Allows 32-bit indices for drawing.
    bool geometryShader           ,  //Supports geometry shaders.
    bool tessellationShader       ,  //Supports tessellation shaders.
    bool multiDrawIndirect        ,  //Allows multiple draw calls in a single command.
    bool wideLines                ,  //Enables rendering wide lines.
    bool largePoints              ,  //Enables rendering large points.
    bool textureCompressionETC2   ,  //ETC2 texture compression support.
    bool sparseBinding            ,  //Supports sparse resources (like sparse textures).


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

template <modules::shader_types sty, typename shmod,typename... shadMods>
struct get_tys {
    using type = std::conditional<shmod::sty == sty, ,get_tys<sty,shadMods>;
}; 
template <modules::shader_types sty, typename shmod>
struct get_tys {
    using type = std::conditional<shmod::sty == sty, shmod,emptyShmod>;
}; 

template <typename... shadMods>
struct glimpl {
    using Pipeline = void ;
    using wsurfaces = void;
    
    using imageBuffer = void;

    using imageBufferIter = pri::list<imageBuffer>::iter ;

    using shadModTup = pri::utuple<pri::list<shadMods>...> ;
    shadModTup shaderModules;

    pri::list<Pipeline> pipelines;
    pri::list<uint> winsurfaces;
    pri::list<device> devices;
    


virtual void get_format(modules::image_format imf);
virtual void bindImage(modules::image2D& im) ;

using imagety = void;
pri::list<imagety> imagePool ;

virtual void create_image2d( modules::image2D& im,mod::imageOpts opts= imageOpts());
using shaderStageBits = void;
virtual void getShaderType(shader_type STAGE);


     
virtual void createSwapChain();
virtual void set_up_dev();
virtual void create_fullscreen();
virtual void get_gpu_info(gpu_info gpinfo);
virtual _shader load_shader(const uint32_t shader[] );

template <modules::shader_type sty,typename buf,mod::BindingType bt>
virtual bool shaderModule(modules::shaderModule<sty,buf,bt>* module);
template <typename buf,mod::BindingType bt>
virtual int grModule(modules::grModule<buf,bt>* module);
template <typename buf,mod::BindingType bt>
virtual int allModule(modules::allModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int vertModule(modules::vertModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int fragModule(modules::fragModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int geomModule(modules::geomModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int tescModule(modules::tescModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int teseModule(modules::teseModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int compModule(modules::compModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int taskModule(modules::taskModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int meshModule(modules::meshModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rgenModule(modules::rgenModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rintModule(modules::rintModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rahitModule(modules::rahitModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rchitModule(modules::rchitModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rmissModule(modules::rmissModule<buf,bt>* module);
template <typename buf,mod::BindingType bt> 
virtual int rcallModule(modules::rcallModule<buf,bt>* module);


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
