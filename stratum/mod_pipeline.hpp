#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP
#include "mod_util.hpp"
namespace mod
{
    
enum shader_type {
/// Alltys


all,
gr,
vert,
frag,
geom,
tesc,
tese,
comp,
task,
mesh,
rgen,
rint,
rahit,
rchit,
rmiss,
rcall,
};
enum BufferUsage {
    // USAGE_TRANSFER_SRC_BIT
    // USAGE_TRANSFER_DST_BIT
    // USAGE_UNIFORM_TEXEL_BUFFER_BIT
    // USAGE_STORAGE_TEXEL_BUFFER_BIT
    // USAGE_UNIFORM_BUFFER_BIT
    // USAGE_STORAGE_BUFFER_BIT
    // USAGE_INDEX_BUFFER_BIT
    // USAGE_VERTEX_BUFFER_BIT
    // USAGE_INDIRECT_BUFFER_BIT
    // USAGE_SHADER_DEVICE_ADDRESS_BIT
    // USAGE_VIDEO_DECODE_SRC_BIT_KHR
    // USAGE_VIDEO_DECODE_DST_BIT_KHR
    // USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT
    // USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT
    // USAGE_CONDITIONAL_RENDERING_BIT_EXT
    // USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR
    // USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR
    // USAGE_SHADER_BINDING_TABLE_BIT_KHR
}
enum BindingType {
SAMPLER,
COMBINED_IMAGE_SAMPLER,
SAMPLED_IMAGE,
STORAGE_IMAGE,
UNIFORM_TEXEL_BUFFER,
STORAGE_TEXEL_BUFFER,
UNIFORM_BUFFER,
STORAGE_BUFFER,
UNIFORM_BUFFER_DYNAMIC,
STORAGE_BUFFER_DYNAMIC,
INPUT_ATTACHMENT,
INLINE_UNIFORM_BLOCK,
ACCELERATION_STRUCTURE,
};


enum bindingDtype {
    BINDING_image=0,
    BINDING_UBO=1,
    BINDING_SSBO=2,
} ;

struct binding {
    size_t pos ;
    bindingDtype dtype;
    BindingType btype; 
    binding() = default ;
    binding(size_t p,bindingDtype _dt) : pos(p),dtype(_dt) {}
};
template <typename >
struct bindingData {

};

struct bindingList : pri::list<binding> {

};

template <typename buf,BindingType bty, bindingDtype bdt>
struct bindingData {
    static constexpr BindingType bt = bty;
    static constexpr bindingDtype bd = bdt;
    buf* buffer;
    bindings(buf& _buffer) : buffer(&_buffer) {}
};
template <shader_type shadTy,typename buf,BindingType bt>
struct shaderModule {
    static constexpr shader_type sty = shadTy ;
    constexpr bool uboB = pri::is_one_of<bt,BindingType::UNIFORM_TEXEL_BUFFER,BindingType::UNIFORM_BUFFER,BindingType::UNIFORM_BUFFER_DYNAMIC,BindingType::INLINE_UNIFORM_BLOCK>::value;
    constexpr bool ssboB = pri::is_one_of<bt,BindingType::STORAGE_TEXEL_BUFFER,BindingType::STORAGE_BUFFER,BindingType::STORAGE_BUFFER_DYNAMIC>::value;
    using ty = buf;
    ty buf; 

    pri::list<binding> bindings;

    int code_size;
    const uint32_t* code; // SPIR-V Module
    std::string name ;
    std::vector<std::string> entry_points; // all entry points
    size_t entryPt;
    std::string codePath;
    void readCode(){
        
        std::ifstream file(codePath, std::ios::ate | std::ios::binary );
    size_t fileSize = static_cast<size_t>(file.tellg());
    code_size = filesize;
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    c = reinterpret_cast<const uint32_t*>(buffer.data());
    }
  
    void update(){
        if constexpr (uboB){ubo->update();}
        if constexpr (ssboB){ssbo->update();}
    };
    shaderModule(std::string _codePath,ssboty& _ssbo) : ssbo(_ssbo) ,codePath(_codePath){};
    shaderModule(std::string _codePath,uboty& _ubo) : ubo(_ubo) ,codePath(_codePath){};
    shaderModule(std::string _codePath,uboty& _ubo,ssboty& _ssbo) : ubo(_ubo),ssbo(_ssbo) ,codePath(_codePath){};

}

template <typename ssboT,typename uboT>
using allModule = shaderModule<shader_type::all,ssboT,uboT>;
template <typename ssboT,typename uboT>
using grModule = shaderModule<shader_type::gr,ssboT,uboT>;


template <typename ssboT,typename uboT>
using vertModule = shaderModule<shader_type::vert,ssboT,uboT>;
template <typename ssboT,typename uboT>
using fragModule = shaderModule<shader_type::frag,ssboT,uboT>;
template <typename ssboT,typename uboT>
using geomModule = shaderModule<shader_type::geom,ssboT,uboT>;
template <typename ssboT,typename uboT>
using tescModule = shaderModule<shader_type::tesc,ssboT,uboT>;
template <typename ssboT,typename uboT>
using teseModule = shaderModule<shader_type::tese,ssboT,uboT>;
template <typename ssboT,typename uboT>
using compModule = shaderModule<shader_type::comp,ssboT,uboT>;
template <typename ssboT,typename uboT>
using taskModule = shaderModule<shader_type::task,ssboT,uboT>;
template <typename ssboT,typename uboT>
using meshModule = shaderModule<shader_type::mesh,ssboT,uboT>;
template <typename ssboT,typename uboT>
using rgenModule = shaderModule<shader_type::rgen,ssboT,uboT>;
template <typename ssboT,typename uboT>
using rintModule = shaderModule<shader_type::rint,ssboT,uboT>;
template <typename ssboT,typename uboT>
using rahitModule = shaderModule<shader_type::rahit,ssboT,uboT>;
template <typename ssboT,typename uboT>
using rchitModule = shaderModule<shader_type::rchit,ssboT,uboT>;
template <typename ssboT,typename uboT>
using rmissModule = shaderModule<shader_type::rmiss,ssboT,uboT>;
template <typename ssboT,typename uboT>
using rcallModule = shaderModule<shader_type::rcall,ssboT,uboT>;


// NoBuffer 
using svertMod =shaderModule<void,void> ;
using sfragMod =shaderModule<void,void> ;
using sgeomMod =shaderModule<void,void> ;
using stescMod =shaderModule<void,void> ;
using steseMod =shaderModule<void,void> ;
using scompMod =shaderModule<void,void> ;
using staskMod =shaderModule<void,void> ;
using smeshMod =shaderModule<void,void> ;
using srgenMod =shaderModule<void,void> ;
using srintMod =shaderModule<void,void> ;
using srahitMod=shaderModule<void,void> ;
using srchitMod=shaderModule<void,void> ;
using srmissMod=shaderModule<void,void> ;
using srcallMod=shaderModule<void,void> ;


using image_shadmod = shaderModule<shader_type::frag,void,image2D>  ;


using font_vert_shadmod  = shaderModule<shader_type::vert,void,fontPrim>  ;
using font_frag_shadmod = shaderModule<shader_type::frag,void,fontPrim> ;

template <DIM d,QUALITY::quality q>
using mesh_vert_shadmod = shaderModule<shader_type::vert,void,mesh<d,q>> ;

template <DIM d,QUALITY::quality q>
using mesh_vert_shadmod = shaderModule<shader_type::vert,void,mesh<d,q>> ;



struct viewPort {
    float x,y,width,height;float minDepth=0.0,maxDepth=1.0;
    viewPort() = default; 
    
};

template <class... shaderMod >
struct lineCon {
    pri::tuple<shaderMod...> shadMods; // Each of these shaderModules conribute to a pipeline stage and they are 

    template <size_t s>
    void update_inst(){pri::get<s>(shadMods).update();}

};


    /*
         Can apply styles modifing shading modes ( textures and tesselation rules)
    Produces another elem most of the time
    Does not modify animations
    */    



class PipeLineAdapter {
    public:
    list<shaderModule> shadersMods ;
    


    void readShaderModule(std::string path,shaderModule& shmod){
        shmod.readCode(path);
        shaderMods.push_back(shmod);
    };
    // WindowObjects
    
    // Active memoryPool Objects;

    void issueCommand
    
};
template <typename PipeTy>
class Pipeline {

};
}