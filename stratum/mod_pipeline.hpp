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

enum shareMode {
    EXCLUSIVE,CONCURRENT
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

template <typename buf,BindingType bty, bindingDtype bdt>
struct bindingData {

    static constexpr BindingType bt = bty;
    static constexpr bindingDtype bd = bdt;
    buf* buffer;
    bindings(buf& _buffer) : buffer(&_buffer) {}
};
template <typename T,BindingType bt>
struct binding{
    constexpr BindingType Bty = bt;


    using ty = T;
    std::vector<T> data ;
    pri::list<T>* listPool;

    struct iterator {
        using viter=  std::vector<T>::iterator ;
        using liter=  pri::list<T>::iter ; 

        viter veciter;
        liter listiter; 
        T& operator*(){return *veciter;}
        T& operator->(){return veciter.operator->();}
        decltype(*this) operator++(){++veciter;++listiter;return *this;}
        decltype(*this) operator--(){--veciter;--listiter;return *this;}
        decltype(*this) operator++(int){veciter++;listiter++;return *this;}
        decltype(*this) operator--(int){veciter--;listiter--;return *this;}
        decltype(*this) operator+=(size_t i){for(size_t s=0;s<i;s++){operator++()} ;return *this ;}
        decltype(*this) operator-=(size_t i){for(size_t s=0;s<i;s++){operator--()} ;return *this ;}
        iterator(viter& r,liter& v) : veciter(r),listiter(v) {}
    };

    struct riterator : iterator {
        decltype(*this) operator--(){++veciter;++listiter;return *this;}
        decltype(*this) operator++(){--veciter;--listiter;return *this;}
        decltype(*this) operator--(int){veciter++;listiter++;return *this;}
        decltype(*this) operator++(int){veciter--;listiter--;return *this;}
        using iterator::iterator(viter& r,liter& v) ;
    }


    iterator begin(){return iterator(data.begin(),listPool->begin()) ; };
    iterator end(){return iterator(data.end(),listPool->end())};
    riterator rbegin(){return riterator(data.begin(),listPool->begin()) ; };
    riterator rend(){return riterator(data.end(),listPool->end())};
    riterator ibegin(){return riterator(data.begin()+data.size()-1,listPool->ibegin()) ; };
    riterator iend(){return riterator(data.begin(),listPool->iend()) ;};


    T& front(){return data.front();}
    T& back(){return data.back();}


    size_t size(){return data.size();}
    void insert(iterator& it,T& d){
        data.insert(it.veciter,d);
        listPool->insert(it.listiter,d);
    };
    void push_back(T&& d){
        listPool->push_back(d); data.push_back(d);
    };
    void erase(iterator& it  ){
        listPool->erase(it.listiter);
        data.erase(it.veciter);
    };

    void pub(pri::list<T*>* n){listPool=n;}
    void get(pri::list<T*>* pts){data.clear();
        for(T* it : *listPool){data.push_back(*it);}
    };
    void get(std::vector<T>& pts){
        data= pts;
    };
    void update()
        if(data.size()==0){
            get(listPool);
        }
        else {
            for(typy& it : updates){
                switch(pri::get<0>(it) ){
                    case updatesEn::pushB : {data.push_back(*pri::get<1>(it));}
                    case updatesEn::erase : {data.erase(data.begin()+pri::get<2>(it));}
                    case updatesEn::insert : {data.insert(data.begin()+pri::get<2>(it),*pri::get<1>(it));}
                }
            };
        }
    }

    binding(pri::list<T*>* d) : listPool(d);
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

    get

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



struct viewPort {
    float x,y,width,height;float minDepth=0.0,maxDepth=1.0;
    viewPort() = default; 
    
};

template <typename shaderModule, typename... shaderModules >
struct pipelinePool {
    using tupty = pri::tuple<shaderModule,shaderModules...>;
    tupty tup;

    void updateAll(){

    };

    void initialize(){
        for
    };  
}


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