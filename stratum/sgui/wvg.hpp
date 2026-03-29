#pragma once 
#include <cstddef>
#include <tuple>
#include <acqres/svg.hpp>
#define NSC std::
namespace sgui {

    const uint8_t _g = 0; 
    enum ty {blend=6,ColorMatrix=7,feComponentTransfer=8,feComposite=9,feConvolveMatrix=10,feDisplacementMatrix=11,feDiffuseLighting=12,feDistantLight=13,feDropShadow=14,fe feFlood=15,fe
        feFuncA=16,,feFuncR=18,feFuncG=19,feFuncB=20,feGaussianBlur=21,feImage=22,feMerge=23,feMergeNode=24,feMorphology=25,feOffset=26,fePointLight=27,feSppecularLighting=28,feSpotlight=29,fetile=30,feTurbulence=31};
    // const uint8_t _Filter = ; 
    const uint8_t _Circle =32;
    const uint8_t _Rect =33;
    const uint8_t _Ellipse = 34;
    const uint8_t _Triangle = 35; 
    const uint8_t _Text=36;
    const uint8_t _Path=37
    const uint8_t _ClipPath=38;

    struct mask {

    };
    



    template <typename... Tags>
    struct  Subs : NSC tuple<Tags...> {}

    template <size_t s,uint8_t inp>
    struct Input{static constexpr size_t pos=s;static constexpr uint8_t itype = inp;};
    template <typename... Inps > 
    using Inputs = NSC tuple<Inps...> {}

template <uint s>
struct Tag {static constexpr uint16_t code=s; };

struct feblend{blend_mode blm ;};
struct feColorMatrix{};
struct feComponentTransfer{};
struct feComposite{};
struct feConvolveMatrix{};
struct feDisplacementMatrix{};
struct feDiffuseLighting{};
struct feDistantLight{};
struct feDropShadow{};
struct feFlood{};
struct feFuncA{};
struct feFuncR{};
struct feFuncG{};
struct feFuncB{};
struct feGaussianBlur{};
struct feImage{};
struct feMerge{};
struct feMergeNode{};
struct feMorphology{};
struct feOffset{};
struct fePointLight{};
struct feSppecularLighting{};
struct feSpotlight{};
struct fetile{};
struct feTurbulence {};

#define FILTS feblend,feColorMatrix,feComponentTransfer,feComposite,feConvolveMatrix,feDisplacementMatrix,feDiffuseLighting,feDistantLight,feDropShadow,feFlood,feFuncA,feFuncR,feFuncG,feFuncB,feGaussianBlur,feImage,feMerge,feMergeNode,feMorphology,feOffset,fePointLight,feSppecularLighting,feSpotlight,fetile,feTurbulence

template <typename T>
struct filter {
    T data;
    glm::mat4x4 filt;
};


    template <uint8_t code  >
    struct  ShapeTag   {
        float x,y;

        template <typename T>
        Tag(T& svgTag) {

        };
    };
template <uint8_t code ,typename Subs, typename Inputs , typename  T>
struct  TTag  : Tag<code,Subs,Inputs,sizeof(T)/sizeof(float)>{
    TTag(T& ref){flt=ref.getFlts()} 
};

    
    struct Circle : Tag<_Circle,Subs<float> > {} ;
    struct Ellipse : Tag<_Ellipse,Subs<float,float> {};
    struct Rect : Tag<_Rect,Subs<float,float> , Att > {};
    struct Path : Tag<_Path,Subs<float,float> , {};
    struct wvg : mod::pipeline {
        float* flts;
        template <typename T, T wvg::* ptr>
        void contrib()
        wvg() {};
    };





typedef struct {
    union {
        
    };

} refer;



struct filterPrim {
    enum fes {fblend,fColorMatrix,fComponentTransfer,fComposite,fConvolveMatrix,fDisplacementMatrix,fDiffuseLighting,fDistantLight,fDropShadow,fFlood,fFuncA,fFuncR,fFuncG,fFuncB,fGaussianBlur,fImage,fMerge,fMergeNode,fMorphology,fOffset,fPointLight,fSppecularLighting,fSpotlight,ftile,fTurbulence};
    fes t;
        union {
        feblend blend;
        feColorMatrix ColorMatrix;
        feComponentTransfer ComponentTransfer;
        feComposite Composite;
        feConvolveMatrix ConvolveMatrix;
        feDisplacementMatrix DisplacementMatrix;
        feDiffuseLighting DiffuseLighting;
        feDistantLight DistantLight;
        feDropShadow DropShadow;
        feFlood Flood;
        feFuncA FuncA;
        feFuncR FuncR;
        feFuncG FuncG;
        feFuncB FuncB;
        feGaussianBlur GaussianBlur;
        feImage Image;
        feMerge Merge;
        feMergeNode MergeNode;
        feMorphology Morphology;
        feOffset Offset;
        fePointLight PointLight;
        feSppecularLighting SppecularLighting;
        feSpotlight Spotlight;
        fetile tile;
        feTurbulence Turbulence;
    };
    
};

struct frag {
    glm::vec4 color;
    
};


    struct wvgPipepline {

    };


};