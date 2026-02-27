#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP
#include "mod_util.hpp"
#include <allocator>
#include <vector>
#include <petri/tuple>
namespace mod
{
/// Alltys    
enum shader_type {all,gr,vert,frag,geom,tesc,tese,comp,task,mesh,rgen,rint,rahit,rchit,rmiss,rcall};

enum shareMode {EXCLUSIVE,CONCURRENT};

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

template <typename buf,BindingType bty, bindingDtype bdt>
struct bindingData {

    static constexpr BindingType bt = bty;
    static constexpr bindingDtype bd = bdt;
    buf* buffer;
    bindings(buf& _buffer) : buffer(&_buffer) {}
};
template <typename T,BindingType bt , class Allocator=std::allocator<T>>
struct binding : std::vector<T,Allocator>{
    constexpr BindingType Bty = bt;

};


template<template<typename T>typename container,  typename bindingT,typename... bindingTs>
struct descriptorPool {
    container<pri::tuple<bindingT,bindingTs...>> list;
    void updatePools(pri::list<bindT::ty*> listP,pri::list<bindTs::ty*>... listPools ){
        pri::get<s>(bindings).pub(&listP);
        updatePools<s+1>(listPools...);
    };
    template <size_t s,typename bindT>
    void updatePools(pri::list<bindT::ty*>& listP ){
        pri::get<s>(bindings).pub(&listP);
    };
    shaderModule(pri::list<bindingT::ty*> listPool ,pri::list<bindingTs::ty*>... listPools) {
        updatePools<0,bindingT,bindingTs...>(listPool,listPools...);
    };
};

template<  typename bindingT,typename... bindingTs>
using vectDescriptorPool = descriptorPool<std::vector,bindingT,bindingTs...>;
template<  typename bindingT,typename... bindingTs>
using listDescriptorPool = descriptorPool<pri::list,bindingT,bindingTs...>;

template <shader_type shadTy, typename bindingT,typename... bindingTs>
struct shaderModule {
    // static cosntexpr bool PODmodule = false;

    static constexpr shader_type sty = shadTy ;
    using ty = buf;
    using vectPoolTy = vectDescriptorPool<bindingT,bindingTs...>;
    using listPoolTy = listDescriptorPool<bindingT,bindingTs...>;

    
    int code_size;
    const uint32_t* code; // SPIR-V Module
    std::string name ;
    std::vector<std::string> entry_points; // all entry points
    size_t entryPt = 0;
    const std::string codePath;
    void readCode(){
        
        std::ifstream file(codePath, std::ios::ate | std::ios::binary );
    size_t fileSize = static_cast<size_t>(file.tellg());
    code_size = filesize;
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    c = reinterpret_cast<const uint32_t*>(buffer.data());
    }
    

    template <typename T>

    template <typename T>
    void appFunc(T& ref){
        ref.update();
    };

    void update(){    pri::applyAll<appFunc,bindingTs...>(bindings)    ;};
    shaderModule(std::string _codePath) :codePath(_codePath){entryPt = 0;};
    shaderModule(std::string _codePath,std::vector<std::string> entryPts) :codePath(_codePath){entryPt = 0;
        entry_points = entryPts;
    
    };
    template <size_t s,typename bindT,typename... bindTs>
};

template <typename shaderModule,typename... shaderModules>
struct pipelineModule {
    pri::tuple<shaderModule,shaderModules...> shadmods;

};

template <typename T,BindingType bt >
using allModule = shaderModule<shader_type::all,T,bt>;
template <typename T,BindingType bt >
using grModule = shaderModule<shader_type::gr,T,bt>;


template <typename T,BindingType bt >
using vertModule = shaderModule<shader_type::vert,T,bt>;
template <typename T,BindingType bt >
using fragModule = shaderModule<shader_type::frag,T,bt>;
template <typename T,BindingType bt >
using geomModule = shaderModule<shader_type::geom,T,bt>;
template <typename T,BindingType bt >
using tescModule = shaderModule<shader_type::tesc,T,bt>;
template <typename T,BindingType bt >
using teseModule = shaderModule<shader_type::tese,T,bt>;
template <typename T,BindingType bt >
using compModule = shaderModule<shader_type::comp,T,bt>;
template <typename T,BindingType bt >
using taskModule = shaderModule<shader_type::task,T,bt>;
template <typename T,BindingType bt >
using meshModule = shaderModule<shader_type::mesh,T,bt>;
template <typename T,BindingType bt >
using rgenModule = shaderModule<shader_type::rgen,T,bt>;
template <typename T,BindingType bt >
using rintModule = shaderModule<shader_type::rint,T,bt>;
template <typename T,BindingType bt >
using rahitModule = shaderModule<shader_type::rahit,T,bt>;
template <typename T,BindingType bt >
using rchitModule = shaderModule<shader_type::rchit,T,bt>;
template <typename T,BindingType bt >
using rmissModule = shaderModule<shader_type::rmiss,T,bt>;
template <typename T,BindingType bt >
using rcallModule = shaderModule<shader_type::rcall,T,bt>;


// NoBuffer 
using svertMod =shaderModule<shader_type::vert> ;
using sfragMod =shaderModule<shader_type::frag> ;
using sgeomMod =shaderModule<shader_type::geom> ;
using stescMod =shaderModule<shader_type::tesc> ;
using steseMod =shaderModule<shader_type::tese> ;
using scompMod =shaderModule<shader_type::comp> ;
using staskMod =shaderModule<shader_type::task> ;
using smeshMod =shaderModule<shader_type::mesh> ;
using srgenMod =shaderModule<shader_type::rgen> ;
using srintMod =shaderModule<shader_type::rint> ;
using srahitMod=shaderModule<shader_type::rahit> ;
using srchitMod=shaderModule<shader_type::rchit> ;
using srmissMod=shaderModule<shader_type::rmiss> ;
using srcallMod=shaderModule<shader_type::rcall> ;


using image_shadmod = shaderModule<shader_type::frag,void,image2D>  ;


using font_vert_shadmod  = shaderModule<shader_type::vert,fontPrim,>  ;
using font_frag_shadmod = shaderModule<shader_type::frag,fontPrim,> ;

template <DIM d,QUALITY::quality q,BindingType bt=BindingType::STORAGE_TEXEL_BUFFER>
using mesh_vert_shadmod = shaderModule<shader_type::vert,mesh<d,q>,bt> ;

template <DIM d,QUALITY::quality q,BindingType bt=BindingType::STORAGE_TEXEL_BUFFER>
using mesh_vert_shadmod = shaderModule<shader_type::vert,mesh<d,q>,bt> ;


template <typename shaderModule, typename... shaderModules >
struct pipelinePool {
    static concstexpr bool dataPoolT = shaderModule ;
    using tupty = pri::tuple<shaderModule,shaderModules...>;
    using tupty
    tupty tup;




    void updateAll(){};

    void initialize(){};  
};



template <Claas>

template <typeanem T ,template <typename A>class Group >
struct reference {
    T* data;
    Group<T>* p;

    reference(Group<T>& _p , T* d) : data(d) , p(&_p) {};
};






template <class shaderMod,class... shaderMod >
struct lineCon {
    // pri::tuple<shaderMod...> ; // Each of these shaderModules conribute to a pipeline stage and they are 
    
    template <shader_type st,class shadMod>
    struct isSt{using type =typename std::conditional<shadMod::sty==st,shadMod,void>::type ; }


    template <shader_type st>
    struct tuptyst  {
        pri::utuple<isSt<st,shadMod>::type,isSt<st,shaderMods>::type...>::type >> tupd;

        struct iterator {constexpr size_t s=0;    
            constexpr iterator& operator++(){s++;return *this;}
            constexpr iterator& operator--(){s++;return *this;}
            constexpr iterator(size_t _s) : s(_s){}
        }
        auto& begin(){return pri::get<0>(tupd);};
        auto& end(){return pri::get<tuple_size(tupd)>(*this);};

        void contribute(){

        };
    };

    tuptyst<shader_type::all> allSM;
    tuptyst<shader_type::gr> grSM; 
    tuptyst<shader_type::vert> vertSM; 
    tuptyst<shader_type::frag> fragSM; 
    tuptyst<shader_type::geom> geomSM; 
    tuptyst<shader_type::tesc> tescSM; 
    tuptyst<shader_type::tese> teseSM; 
    tuptyst<shader_type::comp> compSM; 
    tuptyst<shader_type::task> taskSM; 
    tuptyst<shader_type::mesh> meshSM; 
    tuptyst<shader_type::rgen> rgenSM; 
    tuptyst<shader_type::rint> rintSM; 
    tuptyst<shader_type::rahit> rahitSM; 
    tuptyst<shader_type::rchit> rchitSM; 
    tuptyst<shader_type::rmiss> rmissSM; 
    tuptyst<shader_type::rcall> rcallSM; 

    void contribute(){
        
    };

};

    /*
         Can apply styles modifing shading modes ( textures and tesselation rules)
    Produces another elem most of the time
    Does not modify animations
    */    

class PipeLineAdapter {
    public:
  
    
    
};
}
#endif