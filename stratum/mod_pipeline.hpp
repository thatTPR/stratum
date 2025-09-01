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


enum bindingDtype {
    BINDING_image=0,
    BINDING_UBO=1,
    BINDING_SSBO=2,
} ;

struct binding {
    size_t pos ;
    bindingDtype dtype; 
    binding(size_t p,bindingDtype _dt) : pos(p),dtype(_dt) {}
};

template <shader_type shadTy,typename ssboT,typename uboT>
struct shaderModule {
    static constexpr shader_type sty = shadTy ;
    constexpr bool uboB = !std::is_same<uboT,void>::value;
    constexpr bool ssboB = !std::is_same<uboT,void>::value;
    using uboty = uboT;
    using ssboty = ssboT;
    using tyubo = std::enable_if<uboB,uboT>::type ;
    using tyssbo = std::enable_if<ssboB,ssboT>::type ;   

    tyubo* ubo  ;
    tyssbo* ssbo  ;

    pri::list<binding> bindings;

    int code_size;
    const uint32_t* code; // SPIR-V Module
    std::string name ;
    std::vector<std::string> entry_points; // all entry points
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
    
    void ssboBind(ssboty& ssBuf);
    void uboBind(ubotyy& uBuf);



    struct loader(){
        
    };

    void update(){
        if constexpr (uboB){ubo->update();}
        if constexpr (ssboB){ssbo->update();}
    };
    shaderModule(std::string _codePath,ssboty& _ssbo) : ssbo(_ssbo) ,codePath(_codePath){};
    shaderModule(std::string _codePath,uboty& _ubo) : ubo(_ubo) ,codePath(_codePath){};
    shaderModule(std::string _codePath,uboty& _ubo,ssboty& _ssbo) : ubo(_ubo),ssbo(_ssbo) ,codePath(_codePath){};



}


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



template <class... shaderMod >
struct lineCon {
    pri::tuple<shaderMod...> shadMods; // Each of these shaderModules conribute to a pipeline stage and they are 

    template <size_t s>
    void update_inst(){pri::get<s>(shadMods).update();}


    template <size_t s>
    void inst_

    void update(){

    };

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