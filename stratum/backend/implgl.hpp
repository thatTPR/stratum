#include <petri/list>
#include <stratum/modules.hpp>




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

class gl_impl {
    public:
    list<Pipeline> pipelines;
    list<uint> winsurfaces;
    list<device> devices;
    

    list<shaderModule> all_modules;
    
    list<shaderModule> vert_modules;
    list<shaderModule> frag_modules;
    list<shaderModule> geom_modules;
    list<shaderModule> tesc_modules;
    list<shaderModule> tese_modules;
    list<shaderModule> comp_modules;
    list<shaderModule> task_modules;
    list<shaderModule> mesh_modules;
    list<shaderModule> rgen_modules;
    list<shaderModule> rint_modules;
    list<shaderModule> rahit_modules;
    list<shaderModule> rchit_modules;
    list<shaderModule> rmiss_modules;
    list<shaderModule> rcall_modules;
    


virtual auto get_format(image_format imf);
virtual auto getShaderType(shader_type STAGE)

     
virtual void createSwapChain();
virtual void set_up_dev();
virtual void create_fullscreen();
virtual void get_gpu_info(gpu_info gpinfo);
virtual _shader load_shader(const uint32_t shader[] );
virtual bool shaderModule(shaderModule* module);
virtual int grModule(shaderModule* module);
virtual int glslModule(shaderModule* module);
virtual int vertModule(vertModule* module);
virtual int fragModule(fragModule* module);
virtual int geomModule(geomModule* module);
virtual int tescModule(tescModule* module);
virtual int teseModule(teseModule* module);
virtual int compModule(compModule* module);
virtual int taskModule(taskModule* module);
virtual int meshModule(meshModule* module);
virtual int rgenModule(rgenModule* module);
virtual int rintModule(rintModule* module);
virtual int rahitModule(rahitModule* module);
virtual int rchitModule(rchitModule* module);
virtual int rmissModule(rmissModule* module);
virtual int rcallModule(rcallModule* module);
virtual void updateUniform(device* dev, shaderModule* m );
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
using gl_impl= vk_impl;
#endif 
#ifdef STRATA_DX
#include <strata/backend/impl_dx.hpp>
using gl_impl= dx_impl ;
#endif
#ifdef STRATA_GL
#include <strata/backend/impl_gl.hpp>
using gl_impl = gl_impl;
#endif
#ifdef IMPL_CL
#include <strata/backend/impl_cl.hpp>
using gl_impl = cl_impl ;
#endif

gl_impl gl;
