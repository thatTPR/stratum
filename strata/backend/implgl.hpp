#include <vector>
#include <strata/backend/modules.hpp>
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

class strata_impl {
    public:
    std::vector<Pipeline> pipelines;
    std::vector<winsurface> winsurfaces;
    std::vector<device> devices;
    

    std::vector<shaderModule> all_modules;
    std::vector<vertModule> vert_modules;
    std::vector<fragModule> frag_modules;
    std::vector<geomModule> geom_modules;
    std::vector<tescModule> tesc_modules;
    std::vector<teseModule> tese_modules;
    std::vector<compModule> comp_modules;
    std::vector<taskModule> task_modules;
    std::vector<meshModule> mesh_modules;
    std::vector<rgenModule> rgen_modules;
    std::vector<rintModule> rint_modules;
    std::vector<rahitModule> rahit_modules;
    std::vector<rchitModule> rchit_modules;
    std::vector<rmissModule> rmiss_modules;
    std::vector<rcallModule> rcall_modules;
    
virtual void createSwapChain();
virtual void set_up_dev();
virtual void create_fullscreen();
virtual void updateUniform(device* dev, );
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

