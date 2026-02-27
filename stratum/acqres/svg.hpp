#include <cmath>
#include <stdint.h>
#include <lib/glm/glm.hpp>
#include <acqres/source.hpp>
#include <strata/variables.hpp>




template<typename T>
tinygltf::Value::Object gltfApply(){

};
template <typename Tag>
tinygltf::Value::Object getTag(){

};



#define ANIMATIONELS animateTag, animateMotionTag, animateTransformTag, mpathTag, setTag
#define BASICSHAPES circleTag, ellipseTag, lineTag, polygonTag, polylineTag, rectTag
#define CONTAINERELS aTag, defsTag, gTag, markerTag, maskTag, patternTag, svgTag, switchTag, symbolTag
#define DESCRIPTIVEELS descTag, metadataTag, titleTag
#define FILTERPRIMITIVEELS feBlendTag, feColorMatrixTag, feComponentTransferTag, feCompositeTag, feConvolveMatrixTag, feDiffuseLightingTag, feDisplacementMapTag, feDropShadowTag, feFloodTag, feFuncATag, feFuncBTag, feFuncGTag, feFuncRTag, feGaussianBlurTag, feImageTag, feMergeTag, feMergeNodeTag, feMorphologyTag, feOffsetTag, feSpecularLightingTag, feTileTag, feTurbulenceTag
#define GRADIENTELS linearGradientTag, radialGradientTag, stopTag
#define GRAPHICSELS circleTag, ellipseTag, imageTag, lineTag, pathTag, polygonTag, polylineTag, rectTag, textTag, useTag
#define GRAPHICSREFERENCINGELS useTag
#define LIGHTSOURCEELS feDistantLightTag, fePointLightTag, feSpotLightTag
#define NEVERRENDEREDELS clipPathTag, defsTag, linearGradientTag, markerTag, maskTag, metadataTag, patternTag, radialGradientTag, scriptTag, styleTag, symbolTag, titleTag
#define PAINTSERVERELS linearGradientTag, patternTag, radialGradientTag
#define RENDERABLEELS aTag, circleTag, ellipseTag, foreignObjectTag, gTag, imageTag, lineTag, pathTag, polygonTag, polylineTag, rectTag, svgTag, switchTag, symbolTag, textTag, textPathTag, tspanTag, useTag
#define SHAPEELS circleTag, ellipseTag, lineTag, pathTag, polygonTag, polylineTag, rectTag
#define STRUCTURALELS defsTag, gTag, svgTag, symbolTag, useTag
#define TEXTCONTENTELS textPathTag, textTag, tspanTag
#define TEXTCONTENTCHILDELS textPathTag, tspanTag
#define UNCATEGORIZEDELS clipPathTag, filterTag, foreignObjectTag, scriptTag, styleTag, viewTag


struct OneOfType {std::string name;
    template <pri::Str s,ty t> 
    struct TY : CEStr<s> {static constexpr type = t;}
    std::string str(){return name;}

    template <class bM,class... bMs>
    bool OneOf(){
        if(str==bM::str()){type=bM::type;return true;}
        else if constexpr (sizeof...(bModes)>0){return OneOf<bMs>();}
        return false;
    };
}

typedef float Number;
typedef Number Angle;



struct OneOfType {std::string name;
    template <pri::Str s,ty t> 
    struct TY : CEStr<s> {static constexpr type = t;}
    std::string str(){return name;}

    template <class bM,class... bMs>
    bool OneOf(){
        if(str==bM::str()){type=bM::type;return true;}
        else if constexpr (sizeof...(bModes)>0){return OneOf<bMs>();}
        return false;
    };
}


struct percentage :Number {
    percentage(std::string& st) {for(size_t s=0;st[s] >='0' || (st[s] <='9' );s++){*this*=10+st[s]-0;}}
};

typedef std::vector<vec2> pts;
typedef std::vector<pts> dtag;

typedef std::vector<Number> NummberVec;
struct  Any {
    std::variant<Number,Pt>
} ;
typedef ListOfAny ;

struct attribName : public std::string  {};


struct Boolean {
    bool b;
    operator bool () { return b;}
    std::string str() { return b ? std::string("true"):std::string("false");}
    Boolean(std::string& str){b = (str=="false"):false?false}
};
std::string std::to_string(Boolean& bl){return bl.str();}



/*
struct striate : prop{
    glm::dvec2 center;
    float curl ; // means nothin;
    float theta; // Direction of striation 
    bool radial; // Theta now means 
    glm::dvec2 strokeWidths;
    glm::dvec2 straightness;
    

};*/

// TODO make more modular (separate binar impl from gltf )

glm::dvec4 rgba16itorgbaf(glm::uvec4 s){vec4 t = s.xyzw ;t= t/0xFF; };

enum fe {
    color=1,
    striate=2,
    fibrate=3,
    cybrate=4,
    perlin=5,
    simplex=6,
    convolve=7,
    turbulence=8
};



struct filt {
    glm::dvec4 col;
    float weight;
    float random ;
    float stabilize;
    glm::dmat4 filt ;
};
struct filtTag : Tag<"filt",glm::dmat4,Attrs<Tag<"color",color>,
                                       Tag<"weight",float>,
                                       Tag<"random",float>,
                                       Tag<"stabilize",float>,
                                         {

};

    static tinygltf::Value::Object detgltf(shape_at at);
    static struct filt getgltf(tinygltf::Value filt){

    };
void filt_color(im& i){};
void filt_striate(im& i){};
auto filt_fibrate(im& i , filt f  ){};
auto filt_cybrate(im& i , filt f ){};
auto filt_perlin(im& i , filt f ){};
auto filt_simplex(im& i , filt f ){};
auto filt_convolve(im& i , filt f ){};
auto filt_turbulence(im& i , filt f ){};
struct shape_at ;

#define AtTagSub Tag<"animateMotion",animateMotion>,\
    Tag<"animateTransform",animateTransform>,\
    Tag<"stroke",glm::dvec4>,\
    Tag<"fe",glm::mat4>
#define AtTagAts     Tag<"stroke_width",double>,\
    Tag<"fill",dvec4>,\
    Tag<"gradient",dmat4>,\
    Tag<"radialGradient",dmat4>


struct shape_atTag : Tag<"shape",void,
SubTags<AtTagSub>,
Attrs<AtTagAts>
> {};



#ifndef FEMAGIC
#define FEMAGIC 20000
#endif
glm::dmat4 feMagic(glm::dmat4 p, fe s){
    glmd::dmat4 s = p; s.x.w=(s.x.w)%1+((s.x.w)-(s.x.w)%1)*FEMAGIC+s;
    return s;
};
fe feMagic(glm::dmat4 p){
    double t = p.x.w;
    int s = (int)t;
    s = s%FEMAGIC ;
    return (fe)s;
};



struct RestartAnim : OneOfType {
    enum ty {always,whenNotActive,never} ; ty type=always;
    struct always : TY<"always",always> {};
    struct whenNotActive : TY<"whenNotActive",whenNotActive> {};
    struct never : TY<"never",never> {};
    #define TYPES always,whenNotActive,never
    RestartAnim(std::string& str) {name=str;OneOf<TYPES>();}
};
struct calcMode : OneOfType {
    enum ty {discrete, linear, paced, spline} ; ty type=linear;
    
    struct Tdiscrete : TY<"discrete",discrete>{};
    struct Tlinear : TY<"linear",linear>{};
    struct Tpaced : TY<"paced",paced>{};
    struct Tspline : TY<"spline",spline>{};
    struct always : TY<"always",always> {};
    #define TYPES  Tdiscrete,Tlinear,Tpaced,Tspline
    calcMode(std::string& str) {name=str;OneOf<TYPES>();}
};
struct calcMode : OneOfType {
    enum ty {replace, sum} ; ty type=replace;
    
    struct Treplace : TY<"replace",replace >{};
    struct Tsum : TY<"sum",sum> {};
    #define TYPES Treplace,Tsum
    calcMode(std::string& str) {name=str;OneOf<TYPES>();}
};
struct calcMode : OneOfType {
    enum ty {none, sum} ; ty type=none;
    
    struct Tnone : TY<"none",none >{};
    struct Tsum : TY<"sum",sum> {};
    #define TYPES Tnone,Tsum
    calcMode(std::string& str) {name=str;OneOf<TYPES>();}
};
using begin = Tag<"begin",secs>;
using dur = Tag<"dur",secs>;
using end = Tag<"end",secs>;
using min = Tag<"min",Number>;
using max = Tag<"max",Number>;
using restart = Tag<"restart",RestartAnim>;
using repeatCount = Tag<"repeatCount",Number>;
using repeatDur = Tag<"repeatDur",secs>;
using fill = Tag<"fill",color>;
using calcMode = Tag<"calcMode",calcMode>;
using values = Tag<"values",NumberVec>;
using keyTimes = Tag<"keyTimes",SecsVec>;
using keySplines = Tag<"keySplines",pts>;
using from = Tag<"from",ListOfAny>;
using to = Tag<"to",ListOfAny>;
using by = Tag<"by",ListOfAny>;
using attributeName = Tag<"attributeName",attribName>;
using additive = Tag<"additive",>;
using accumulate = Tag<"accumulate",>;
using onbegin = Tag<"onbegin",>;
using onend = Tag<"onend",>;
using onrepeat = Tag<"onrepeat",>;
#define ANIMATIONTIMINGATS begin, dur, end, min, max, restart, repeatCount, repeatDur, fill
#define ANIMATIONVALUEATS calcMode, values, keyTimes, keySplines, from, to, by
#define OTHERANIMATIONATS attributeName, additive, accumulate
#define ANIMATIONEVENTATS  onbegin, onend, onrepeat

struct clipPathTag :Tag<"clipPath",void,SubTags<AtTagSub>,Attrs<AtTagAts,
Tag<"clipPathUnits",std::string> {
    enum units {
        userSpaceOnUse,objectBoundingBox
    };
    operator bool (){return data=="userSpaceOnUse" };
};

typedef std::vector<> pathPts ;

struct aTag : Tag<"a",void,SubTags<>,Attrs> {};
struct animateTag : Tag<"animate",void,SubTags<DESCRIPTIVEELS>,Attrs<>> {};

struct animateMotionTag : Tag<"animateMotion",SubTags<DESCRIPTIVEELS,mpathTag>,
Attrs<
Tag<"keyPoints",NumberTuple>,
Tag<"path",dAt>,
Tag<"rotate",Number>,
ANIMATIONTIMINGATS,ANIMATIONVALUEATS,OTHERANIMATIONATS,ANIMATIONEVENTATS
>> {};

struct animateTransformTag : Tag<"animateTransform",void, SubTags<DESCRIPTIVEELS> ,Attrs<by,from,to,typeAnim>

>> {};

struct circleTag : Tag<"circle",void,SubTags<AtTagSub>,Attrs<AtTagAts,
Tag<"cx",float>,
Tag<"cy",float>,
Tag<"r",float>,
Tag<"pathLength",float>,
,dTag>> {};
struct clipPathTag : Tag<"clipPath",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,textTag,useTag>,Attrs<
Tag<"clipPathUnits",filtUnits>
>> {};
struct defsTag : Tag<"defs",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag, filterTag, foreignObjectTag, imageTag, markerTag, maskTag, patternTag, scriptTag, styleTag, switchTag, textTag, viewTag,
>,Attrs<GLOBALATTRS>> {};
struct descTag : Tag<"desc",void,SubTags<ALLELEMS>,Attrs<GLOBALATTRS>> {};
struct ellipseTag : Tag<"ellipse",void,SubTags<AtTagSub>,
Attrs<AtTagAts,
Tag<"cx",float>,
Tag<"cy",float>,
Tag<"rx",float>,
Tag<"ry",float>,
Tag<"pathLength",float>
>> {};


#define PTMAGIC 2000
#define CUBIC 0,
#define QUAD 1,
#define LINE 2,
double fract(double s){return s - std::floor(s);};  
glm::dvec2 ptpmagic(glm::dvec2 p , int8_t g){ // Stays at 
    glm::dvec2 s = p;
    s.y=(fract(s.y))+std::floor(s.y)*PTMAGIC+g;
    return s;
};
int8_t ptpmagic(glm::dvec2 p ){ // Stays at 
    int8_t PT;    glm::dvec2 s = p;
         int PT=int(std::floor(s.y))%PTMAGIC;
    return PT;
};
void ptmagic(glm::dvec2& p){
    p.y = std::floor(p.y)/PTMAGIC + fract(p.y);
};
struct textpathTag : Tag<"textpath",void,SubTags<AtTagSub,Tag<"text",std::string>,pathTag> ,Attrs<AtTagAts,dAt>,Attrs<AtTagAts>> {};

struct gTag: Tag<"g",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,
    Attrs<AtTagAts>
>;

struct blend_mode {
    std::string str;
    enum ty{normal,multiply,screen,overlay,darken,lighten,color_dodge,color_burn,hard_light,soft_light,difference,exclusion,hue,saturation,color,luminosity};
    ty type;
   template <pri::Str s, ty t>
   struct blendMode :  pri::CEStr<s>{static constexpr ty type= t;};
    struct bmnormal : blendMode <"normal",normal > {};               //The final color is the top color, regardless of what the bottom color is. The effect is like two opaque pieces of paper overlapping.
    struct bmmultiply : blendMode <"multiply",multiply > {};               //The final color is the result of multiplying the top and bottom colors. A black layer leads to a black final layer, and a white layer leads to no change. The effect is like two images printed on transparent film overlapping.
    struct bmscreen : blendMode <"screen",screen > {};               //The final color is the result of inverting the colors, multiplying them, and inverting that value. A black layer leads to no change, and a white layer leads to a white final layer. The effect is like two images shining onto a projection screen.
    struct bmoverlay : blendMode <"overlay",overlay > {};               //The final color is the result of multiply if the bottom color is darker, or screen if the bottom color is lighter. This blend mode is equivalent to hard-light but with the layers swapped.
    struct bmdarken : blendMode <"darken",darken > {};               //The final color is composed of the darkest values of each color channel.
    struct bmlighten : blendMode <"lighten",lighten > {};               //The final color is composed of the lightest values of each color channel.
    struct bmcolor_dodge : blendMode <"color-dodge", > {};color_dodge          //The final color is the result of dividing the bottom color by the inverse of the top color. A black foreground leads to no change. A foreground with the inverse color of the backdrop leads to a fully lit color. This blend mode is similar to screen, but the foreground only needs to be as light as the inverse of the backdrop to create a fully lit color.
    struct bmcolor_burn : blendMode <"color-burn", > {};color_burn          //The final color is the result of inverting the bottom color, dividing the value by the top color, and inverting that value. A white foreground leads to no change. A foreground with the inverse color of the backdrop leads to a black final image. This blend mode is similar to multiply, but the foreground only needs to be as dark as the inverse of the backdrop to make the final image black.
    struct bmhard_light : blendMode <"hard-light", > {};hard_light          //The final color is the result of multiply if the top color is darker, or screen if the top color is lighter. This blend mode is equivalent to overlay but with the layers swapped. The effect is similar to shining a harsh spotlight on the backdrop.
    struct bmsoft_light : blendMode <"soft-light", > {};soft_light          //The final color is similar to hard-light, but softer. This blend mode behaves similar to hard-light. The effect is similar to shining a diffused spotlight on the backdrop.
    struct bmdifference : blendMode <"difference",difference > {};               //The final color is the result of subtracting the darker of the two colors from the lighter one. A black layer has no effect, while a white layer inverts the other layer's color.
    struct bmexclusion : blendMode <"exclusion",exclusion > {};               //The final color is similar to difference, but with less contrast. As with difference, a black layer has no effect, while a white layer inverts the other layer's color.
    struct bmhue : blendMode <"hue",hue > {};               //The final color has the hue of the top color, while using the saturation and luminosity of the bottom color.
    struct bmsaturation : blendMode <"saturation",saturation > {};               //The final color has the saturation of the top color, while using the hue and luminosity of the bottom color. A pure gray backdrop, having no saturation, will have no effect.
    struct bmcolor : blendMode <"color",color > {};               //The final color has the hue and saturation of the top color, while using the luminosity of the bottom color. The effect preserves gray levels and can be used to colorize the foreground.
    struct bmluminosity : blendMode <"luminosity",luminosity > {};               //The final color has the luminosity of the top color, while using the hue and saturation of the bottom color. This blend mode is equivalent to color, but with the layers swapped.

#define BLENDMODES bmnormal,bmmultiply,bmscreen,bmoverlay,bmdarken,bmlighten,bmcolor_dodge,bmcolor_burn,bmhard_light,bmsoft_light,bmdifference,bmexclusion,bmhue,bmsaturation,bmcolor,bmluminosity

    template <class bMode,class... bModes>
    bool OneOf(){
        if(str==bMode::str()){type=bMode::type;return true;}
        else if constexpr (sizeof...(bModes)>0){return OneOf<bModes>();}
        return false;
    };
    template <class bMode,class... bModes>
    std::string GetStr(){
        if(type==bMode::type){return bMode::str();}
        else if constexpr (sizeof...(bModes)>0){return GetStr<bModes>();}
        return std::string();
    };
    std::string str(){return GetStr<BLENDMODES>()};
blend_mode(std::string& strs){ str = strs;OneOf<BLENDMODES>();}
};
std::string std::to_string(blend_mode& bm){return bm.str();};


#define FILTPRIMAT Tag<"x",float>,Tag<"y",float>,Tag<"width",float>,Tag<"height",float>,Tag<"result",Reference>
struct feBlendTag : Tag<
"feBlend",void,SubTags<AtTagSub>,Attrs<AtTagAts,
Tag<"in",Reference>,
Tag<"in2",Reference>,
Tag<"mode",blend_mode>,
FILTPRIMAT
>
> {};
struct colMatrixType : OneOfType{
    enum ty{matrix, saturate, hueRotate, luminanceToAlpha};
    ty type;
   struct cmmatrix : TY<"matrix",matrix> {};
   struct cmsaturate : TY<"saturate",saturate> {}; 
   struct cmhueRotate : TY<"hueRotate",hueRotate> {}; 
   struct cmluminanceToAlpha : TY<"luminanceToAlpha",luminanceToAlpha> {}; 

#define CMTYPES cmmatrix,cmsaturate,cmhueRotate,cmluminanceToAlpha
    
    template <class bMode,class... bModes>
    std::string GetStr(){
        if(type==bMode::type){return bMode::str();}
        else if constexpr (sizeof...(bModes)>0){return GetStr<bModes>();}
        return std::string();
    };
    std::string str(){return GetStr<CMTYPES>()};
colMatrixType(std::string& strs){ name = strs;OneOf<CMTYPE>();}
};

struct Reference  {
    std::string name;

    operator std::string () {return name;};
    Reference (std::string& str) { name = str;}
};
struct feColorMatrixTag : Tag<
"feColorMatrix",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,
Tag<"in",Reference>,
Tag<"type",colMatrixType>,
Tag<"values",std::vector<float>> ,FILTPRIMAT>
> {};
struct feComponentTransferTag : Tag<
"feComponentTransfer",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,Tag<"in",Reference>,FILTPRIMAT>
> {};
struct operatorType : OneOfType {
    enum ty {over,in,out,atop,xor,lighter,arithmetic};
    ty type;
    struct otover : TY<"over",over>{} ;
    struct otin : TY<"in",in>{} ;
    struct otout : TY<"out",out>{} ;
    struct otatop : TY<"atop",atop>{} ;
    struct otxor : TY<"xor",xor>{} ;
    struct otlighter : TY<"lighter",lighter>{} ;
    struct otarithmetic : TY<"arithmetic",arithmetic>{} ;
    #define OTMACS otover ,otin ,otout ,otatop ,otxor ,otlighter ,otarithmetic

    
    template <class bMode,class... bModes>
    std::string GetStr(){
        if(type==bMode::type){return bMode::str();}
        else if constexpr (sizeof...(bModes)>0){return GetStr<bModes>();}
        return std::string();
    };
    std::string str(){return GetStr<OTMACS>()};
operatorType(std::string& strs){ str = strs;OneOf<OTMACS>();}
};


struct edgeMode :OneOfType {
    std::string name;
    enum ty {duplicate,wrap,none};
    struct emduplicate  : TY<"duplicate",duplicate> {};
    struct emwrap  : TY<"wrap",wrap> {};
    struct emnone  : TY<"none",none> {};
#define EMMACS emduplicate,emwrap,emnone
     template <class bMode,class... bModes>
    std::string GetStr(){
        if(type==bMode::type){return bMode::str();}
        else if constexpr (sizeof...(bModes)>0){return GetStr<bModes>();}
        return std::string();
    };
    std::string str(){return GetStr<EMMACS>()};
edgeMode(std::string& strs){ str = strs;OneOf<EMMACS>();}
};

struct channelSelector {
     enum ty {r,g,b,a};
     ty type;
    template <pri::Str s,ty t>
    struct em : pri::CEStr<s> {static constexpr ty type = t;}

    struct emr  : em<"rR",r> {};
    struct emg  : em<"gG",g> {};
    struct emb  : em<"bB",b> {};
    struct ema  : em<"aA",a> {};

    #define EMMACS emr,emg,emb,ema
    template <class bMode,class... bModes>
    bool OneOf(){
        if( bMode::str().find(str[0])){type=bMode::type;return true;}
        else if constexpr (sizeof...(bModes)>0){return OneOf<bModes>();}
        return false;
    };
     template <class bMode,class... bModes>
    std::string GetStr(){
        if(type==bMode::type){return bMode::str();}
        else if constexpr (sizeof...(bModes)>0){return GetStr<bModes>();}
        return std::string();
    };
    std::string str(){return GetStr<EMMACS>()};
edgeMode(std::string& strs){ name = strs;OneOf<EMMACS>();}
}

struct feConvolveMatrixTag : Tag<
"feConvolveMatrix",void,SubTags<AtTagSub>,Attrs<AtTagAts,FILTPRIMAT,
Tag<"in",Reference>,
Tag<"order",Number>,
Tag<"kernelMatrix",NumberVec>,
Tag<"divisior",Number>,
Tag<"bias",Number>,
Tag<"targetX",Number>,
Tag<"targetY",Number>,
Tag<"edgeMode",edgeMode>,
Tag<"kernelUnitLength",Number>,
Tag<"preserveAlpha",Boolean>
>
> {};
struct feDiffuseLightingTag : Tag<
"feDiffuseLighting",void,SubTags<AtTagSub>,Attrs<AtTagAts,FILTPRIMAT,
Tag<"in",Reference>,
Tag<"surfaceScale",Number>,
Tag<"diffuseConstant",Number>,
Tag<"kernelUnitLength",Number>,
>
> {};


struct feDisplacementMapTag : Tag<
"feDisplacementMap",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT,
Tag<"in",Reference>,
Tag<"in2",Reference>,
Tag<"scale",Number>,
Tag<"xChannelSelector",channelSelector>,
Tag<"yChannelSelector",channelSelector>,
>
> {};
struct feDistantLightTag : Tag<
"feDistantLight",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,Tag<"azimuth",Number>,Tag<"elevation",Number>>
> {};
struct feDropShadowTag : Tag<
"feDropShadow",void,SubTags<AtTagSub,animateTag,scriptTag,setTag>,Attrs<AtTagAts,FILTPRIMAT,
Tag<"dx",Number>,
Tag<"dy",Number>,
Tag<"reference",Number>,
Tag<"stdDeviation",Number>

>
> {};
struct feFloodTag : Tag<
"feFlood",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT,Tag<"flood-color",color>,Tag<"flood-opacity",Number>
> {};
struct feFuncATag : Tag<"feFuncA",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};
struct feFuncBTag : Tag<"feFuncB",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};
struct feFuncGTag : Tag<"feFuncG",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};
struct feFuncRTag : Tag<"feFuncR",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};

struct feGaussianBlurTag : Tag<
"feGaussianBlur",void,SubTags<AtTagSub>,Attrs<AtTagAts,FILTPRIMAT,Tag<"in",Reference>,Tag<"stdDeviation",Number>,Tag<"edgeMode",edgeMode>> > {};
struct feImageTag : Tag<
"feImage",void,SubTags<AtTagSub,animateTag,setTag,animateTransformTag>,Attrs<AtTagAts,FILTPRIMAT,
Tag<"crossorigin",crossorigin>,
Tag<"fetchpriority",fetchpriority>,
Tag<"preserveAspectRatio",preserveAspectRatio>,
Tag<"href",href>
>
> {};
struct feMergeTag : Tag<
"feMerge",void,SubTags<AtTagSub,feMergeNodeTag>,Attrs<>> {};
struct feMergeNodeTag : Tag<
"feMergeNode",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<Tag<"in",Reference>>> {};
struct feMorphologyTag : Tag<
"feMorphology",void,SubTags<AtTagSub>,Attrs<Tag<"in",Reference>,Tag<"operator",operatorType>,Tag<"radius",Number>,FILTPRIMAT>
> {};
struct feOffsetTag : Tag<
"feOffset",void,SubTags<AtTagSub>,Attrs<Tag<"in",Reference>,Tag<"dx",Number>,Tag<"dy",Number>,FILTPRIMAT>
> {};
struct fePointLightTag : Tag<
"fePointLight",void,SubTags<animateTag,setTAg>,Attrs<Tag<"x",Number>,Tag<"y",Number>,Tag<"z",Number>>
> {};


struct feSpecularLightingTag : Tag<
"feSpecularLighting",void,SubTags<AtTagSub,LIGHTSOURCEELS>,Attrs<FILTPRIMAT,
Tag<"in",Reference>,
Tag<"surfaceScale",Number>,
Tag<"specularConstant",Number>,
Tag<"specularExponent",Number>,
Tag<"kernelUnitLength",Number>>
> {};
struct feSpotLightTag : Tag<
"feSpotLight",void,SubTags<animateTag,setTag>,Attrs<
Tag<"x",Number>,
Tag<"y",Number>,
Tag<"z",Number>,
Tag<"pointsAtX",Number>,
Tag<"pointsAtY",Number>,
Tag<"pointsAtZ",Number>,
Tag<"specularExponent",Number>,
Tag<"limitingConeAngle",Number>,
>
> {};
struct feTileTag : Tag<
"feTile",void,SubTags<animateTag,setTag>,Attrs<Tag<"in",Reference>,FILTPRIMAT>
> {};

struct turbulenceType : OneOfType {
    std::string name;
    enum ty {fractalNoise,turbulence};
    struct  fractalNoiseTY : TY<"fractalNoise",fractalNoise>{};
    struct      turbulenceTY : TY<"turbulence",turbulence>{};
    #define TYPES fractalNoiseTY,turbulenceTY 
std::string    str(){return name;}
    turbulenceType(std::string& name) {str=name;OneOf<TYPES>();}
};
struct turbulenceType : OneOfType {
    std::string name;
    enum ty {noStitch,stitch};
    template <pri::Str s,ty t> 
    struct TY : CEStr<s> {static constexpr type = t;}
    struct noStitchTY : TY<"noStitch",noStitch>{};
    struct stitchTY : TY<"stitch",stitch>{};
    #define TYPES noStitchTY,stitchTY 
std::string    str(){return name;}
    turbulenceType(std::string& name) {str=name;OneOf<TYPES>();}
};

struct filtUnits : OneOfType {
    std::string name;
    enum ty {userSpaceOnUse,objectBoundingBox};
    
    struct userSpaceOnUseTY : TY<"userSpaceOnUse",noStitch>{};
    struct objectBoundingBoxTY : TY<"objectBoundingBox",stitch>{};
    #define TYPES userSpaceOnUseTY,objectBoundingBoxTY
std::string    str(){return name;}
    filtUnits(std::string& name) {str=name;OneOf<TYPES>();}
};

struct feTurbulenceTag : Tag<
"feTurbulence",void,SubTags<animateTag,setTag>,Attrs<FILTPRIMAT,
Tag<"baseFrequency",Number>,
Tag<"numOctaves",Number>,
Tag<"seed",Number>,
Tag<"stitchTiles",Number>,
Tag<"type",turbulenceType> >> {};

struct filterTag : Tag<
"feTurbulence",void,SubTags<DESCRIPTIVEELS,FILTERPRIMITIVEELS,animateTag,setTag>,Attrs<
Tag<"x",Number>,
Tag<"y",Number>,
Tag<"width",Number>,
Tag<"height",Number>,
Tag<"filterUnits",filtUnits>,
Tag<"primitiveUnits",filtUnits>>
> {};

struct foreingObjectTag: Tag<
"feTurbulence",void,SubTags<DESCRIPTIVEELS,FILTERPRIMITIVEELS,animateTag,setTag>,Attrs<
Tag<"x",Number>,
Tag<"y",Number>,
Tag<"width",Number>,
Tag<"height",Number>>> {

};

struct preserveAspecRatio : OneOfType {
   enum ty {none , xMinYMin , xMidYMin , xMaxYMin , xMinYMid , xMidYMid , xMaxYMid , xMinYMax ,xMidYMax,xMaxYMax,meet, slice};ty type;
        struct noneTY : TY<"none",none> {}; 
        struct xMinYMinTY : TY<"xMinYMin",xMinYMin> {}; 
        struct xMidYMinTY : TY<"xMidYMin",xMidYMin> {}; 
        struct xMaxYMinTY : TY<"xMaxYMin",xMaxYMin> {}; 
        struct xMinYMidTY : TY<"xMinYMid",xMinYMid> {}; 
        struct xMidYMidTY : TY<"xMidYMid",xMidYMid> {}; 
        struct xMaxYMidTY : TY<"xMaxYMid",xMaxYMid> {}; 
        struct xMinYMaxTY : TY<"xMinYMax",xMinYMax> {}; 
        struct xMidYMaxTY : TY<"xMidYMax",xMidYMax> {};
        struct xMaxYMaxTY : TY<"xMaxYMax",xMaxYMax> {};
        struct meetTY : TY<"meet",meet> {};
        struct sliceTY : TY<"slice",slice> {};
        #define TYPES noneTY,xMinYMinTY,xMidYMinTY,xMaxYMinTY,xMinYMidTY,xMidYMidTY,xMaxYMidTY,xMinYMaxTY,xMidYMaxTY,xMaxYMaxTY,meetTY,sliceTY
    preserveAspecRatio(std::string& str) { name = str; OneOf<TYPES>();}

};
struct crossorigin : OneOfType {
   enum ty {anonymous,use_credentials};ty type;
   struct anonymousTY : TY<"anonymous"            , anonymous> {} ;
   struct use_credentialsTY : TY<"use-credentials", use_credentials> {} ;
    #define TYPES anonymous,use_credentials
     crossorigin(std::string& str) { name= str ; OneOfType<TYPES>();}
};
struct decoding : OneOfType {
   enum ty {async,sync,_auto};ty type;
   struct asyncTY : TY<"async",async> {}; 
   struct syncTY : TY<"sync",sync> {}; 
   struct _autoTY : TY<"auto",_auto> {}; 
    #define TYPES asyncTY,syncTY,_autoTY
    decoding(std::string& str) { name= str ; OneOfType<TYPES>();}

};
struct fetchpriority : OneOfType {
  enum ty {high,low,_auto};ty type;
   struct highTY : TY<"high",high> {}; 
   struct lowTY : TY<"low",low> {}; 
   struct _autoTY : TY<"auto",_auto> {}; 
    #define TYPES highTY,lowTY,_autoTY

    fetchpriority(std::string& str) { name = str; OneOf<TYPES>();}
};


struct spreadMethod : OneOfType {
  enum ty {pad,reflect,repeat};ty type;
   
  struct padTY : TY<"pad",pad> {}; 
   struct reflectTY : TY<"reflect",reflect> {}; 
   struct repeatTY : TY<"repeat",repeat> {}; 
    #define TYPES padTY,reflectTY,repeatTY

    spreadMethod(std::string& str) { name = str; OneOf<TYPES>();}
};



struct imageTag : Tag<"image",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,animateTag,animateMotionTag,animateTransformTag,scriptTag,setTag,styleTag>,
Attrs<
Tag<"x",Number>,
Tag<"y",Number>,
Tag<"width",Number>,
Tag<"height",Number>,
Tag<"href",URL>,
Tag<"preserveAspecRatio",preserveAspecRation>,
Tag<"crossorigin",crossorigin>,
Tag<"decoding",decoding>,
Tag<"fetchpriority",fetchpriority>
>> {}

struct lineTag : Tag<"line",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<
Tag<"x1",Number>,
Tag<"x2",Number>,
Tag<"y1",Number>,
Tag<"y2",Number>
Tag<"pathLength",Number>
>> {}


struct linearGradientTag : Tag<"linearGradient",void,SubTags<DESCRIPTIVEELS,animateTag,animateTransformTag,scriptTag,setTag,stopTag,styleTag>,Attrs<
Tag<"gradientUnits",filtUnits>,
Tag<"gradientTransform",TransformList>,
Tag<"href",URL>,
Tag<"href",spreadMethod>,
Tag<"x1",Number>,
Tag<"x2",Number>,
Tag<"y1",Number>,
Tag<"y2",Number>
 >> {}
 struct markerTag : Tag<"marker",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Tag<"markerHeight",Number>,
 Tag<"markerUnits",filtUnits>,
 Tag<"markerWith",Number>,
 Tag<"orient",Angle>,
 Tag<"preserveAspecRatio",preserveAspecRatio>,
 Tag<"refX",Number>,
 Tag<"refY",Number>, 
 Tag<"viewBox",NumberVec>
 >> {}
 struct maskTag : Tag<"mask",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Tag<"height",Number>,
 Tag<"mask-type",maskType>,
 Tag<"maskContentUnits",filtUnits>,
 Tag<"maskUnits",filtUnits>,
 Tag<"x",Number>,
 Tag<"y",Number>,
 Tag<"width",Number>,
 >> {}
 struct metadataTag : Tag<"metadata",void,SubTags<AtTagSub>,Attrs<AtTagSub>> {}
 struct mpathTag : Tag<"mpath",void,SubTags<DESCRIPTIVEELS>,Attrs<Tag<"href",Reference>>> {}
 
struct pathTag : Tag<"path",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS> ,Attrs<Tag<"d",std::vector<pathPts>>, Tag<"pathLength",Number>> > {};
 struct patternTag : Tag<"pattern",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,GRADIENTELS,SHAPEELS,STRUCTURALELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Tag<"height",Number>,
 Tag<"href",Raference>,
 Tag<"paternContentUnits",filtUnits>,
 Tag<"patterTransform",NumberVec>,
 Tag<"patternUnits",filtUnits>,
 Tag<"preserveAspectRatio",preserveAspectRatio>,
 Tag<"viewBox",NumberVec>,
 Tag<"width",Number>,
 Tag<"x",Number>
 >> {}
 struct polygonTag : Tag<"polygon",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<Tag<"points",pts>,Tag<"pathLength",Number>>> {}
 struct polylineTag : Tag<"polyline",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<Tag<"points",pts>,Tag<"pathLength",Number>>> {};
 struct radialGradientTag : Tag<"radialGradient",void,SubTags<DESCRIPTIVEELS,animateTag,animateTransformTag,scriptTag,setTag,stopTag,styleTag>,
 Attrs<
 Tag<"cx",Number>,
 Tag<"cy",Number>,
 Tag<"fr",Number>,
 Tag<"fx",Number>,
 Tag<"fy",Number>,
 Tag<"gradientUnits",filtUnits>,
 Tag<"gradientTransform",NumberVec>,
 Tag<"href",URL>,
 Tag<"r",Number>,
 Tag<"spreaMethod",spreadMethod>,
 >> {};
 
struct rectTag : Tag<"rect",void,SubTags<AtTagSub,ANIMATIONELS,DESCRIPTIVEELS>,Attrs<AtTagAts,
Tag<"x",float>,
Tag<"y",float>,
Tag<"width",float>,
Tag<"height",float>,
Tag<"rx",float>,
Tag<"ry",float>,
Tag<"pathLength",float>,
,dTag>,>;
struct mediaType : OneOfType {
    enum ty {image} ;ty type;
};
 struct scriptTag : Tag<"script",void,SubTags<AtTagAts>,Attrs<
 Tag<"crossorigin",>,
 Tag<"fetchpriority",fetchpriority>,
 Tag<"href",URL>,
 Tag<"type",mediaType>,
 >> {}
 struct setTag : Tag<"set",void,SubTags<DESCRIPTIVEELS>,Attrs<to,attributeName>> {}
 struct stopTag : Tag<"stop",void,SubTags<animateTag,scriptTag,setTag,styleTag>,Attrs<
 Tag<"offset",Number>,
 Tag<"stop-color",color>,
 Tag<"stop-opacity",Number>
 >> {};
 struct styleTag : Tag<"style",void,SubTags<AllElements>,Attrs<
 Tag<"type",mediaType>,
 Tag<"media",mediaType>,
 Tag<"tiyle",std::string>,
 >> {};
 struct svgTag : Tag<"svg",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Tag<"baseProfile",>,
 Tag<"height",>,
 Tag<"preserveAspectRatio",preserveAspectRatio>,
 Tag<"version",Number>,
 Tag<"viewBox",NumberVec>,
 Tag<"width",Number>,
 Tag<"x",Number>,
 Tag<"y",Number>,
 >> {};
 struct switchTag : Tag<"switch",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,aTag,foreingObjectTag,gTag,imageTag,svgTag,switchTag,textTag,useTag>,
 Attrs<
 Tag<"requiredExtensions",URLLIST>,
 Tag<"systemLanguage",languageList>
 >> {}
 struct symbolTag : Tag<"symbol",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,
 Attrs<
 Tag<"height",Number>,
 Tag<"preserveAspecRatio",preserveAspecRatio>,
 Tag<"refX",Number>,
 Tag<"refY",Number>,
 Tag<"viewBox",NumberList>,
 Tag<"width",Number>,
 Tag<"x",Number>,
 Tag<"y",Number>,
 >> {}

 struct lengthAjust : OneOfType {
    enum ty {spacing,spacingAndGLyphs} ; ty type;
    spacingTY : TY<"spacing",spacing> {};,
    spacingAndGLyphsTY : TY<"spacingAndGLyphs",spacingAndGLyphs> {};
    #define TYPES spacingTY,spacingAndGLyphsTY
    lengthAjust(std::string& str){ name=str;OneOf<TYPES>() ;}
 }

 struct textTag : Tag<"text",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,TEXTCONTENTCHILDELS,aTag>,Attrs<
 Tag<"x",Number>,
 Tag<"y",Number>, 
 Tag<"dx",Number>,
 Tag<"dy",Number>,
 Tag<"rotate",Number>,
 Tag<"lengthAdjust",Number>,
 Tag<"textLength",Number>>> {};
 struct textPathTag : Tag<"textPath",void,SubTags<DESCRIPTIVEELS,aTag,animateTag,setTag,tspanTag>,Attrs<
 Tag<"href",URL>,
 Tag<"lengthAjust",lengthAjust>,
 Tag<"method",methodAdjust>,
//  Tag<"path",d>,
//  Tag<"side",>,
 Tag<"spacing",spacingType>,
 Tag<"startOffset",Number>,
 Tag<"textLength",Number>,
 >> {};
 struct titleTag : Tag<"title",void,SubTags<ALLELEMS>,Attrs<>> {}
 struct tspanTag : Tag<"tspan",void,SubTags<DESCRIPTIVEELS,aTag,animateTag,setTag,tspanTag>,Attrs<
 Tag<"x",Number>,
 Tag<"y",Number>,
 Tag<"dx",Number>,
 Tag<"dy",Number>,
 Tag<"rotate",c>,
 Tag<"lengthAdjust",lengthAdjust>,
 Tag<"textLength",Number>
 >> {};
 struct useTag : Tag<"use",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<Tag<"href",URL>>> {};
 struct viewTag : Tag<"view",void,SubTags<DESCRIPTIVEELS>,Attrs<
 Tag<"preserveAspecRatio",preserveAspecRatio>,
 Tag<"viewBox",NumberList>,
 >> {};


struct svgTag : Tag<"svg",void,
SubTags<
gTag,
polylineTag,
rectTag,
ellipseTag,
pathTag,
textpathTag
>,
 Attrs<Tag<"name",std::string> > > {};
 
