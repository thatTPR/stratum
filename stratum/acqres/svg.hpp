#include <cmath>
#include <stdint.h>
#include <glm/glm.hpp>
#include <string>
// #include <variables.hpp>
#include <cstddef> 
#include <petri/templates.hpp>
namespace svg {
template <uint32_t Tag>
struct TAG {static constexpr uint32_t tag=Tag;};


template <size_t S>
constexpr uint32_t GTAG(const char (&c)[S]){
    return  (uint32_t(c[0] )<<(3*8) )  |
            (uint32_t( c[1])<<(8*2) )  |
            (uint32_t( c[2])<<8 )  |
            (uint32_t( c[3]) );
    };

template <const char (&h)[5]>
struct TAGC : TAG<GTAG(h)> {} ;


#define ANIMATIONELS animateTag, animateMotionTag, animateTransformTag, mpathTag, setTag
#define BASICSHAPES circleTag, ellipseTag, lineTag, polygonTag, polylineTag, rectTag
#define CONTAINERELS aTag, defsTag, gTag, markerTag, maskTag, patternTag, svgTag, switchTag, symbolTag
#define DESCRIPTIVEELS descTag, metadataTag, titleTag
#define FILTERPRIMITIVEELS feBlendVar, feColorMatrixTag, feComponentTransferTag, feCompositeTag, feConvolveMatrixTag, feDiffuseLightingTag, feDisplacementMapTag, feDropShadowTag, feFloodVar, feFuncATag, feFuncBTag, feFuncGTag, feFuncRTag, feGaussianBlurTag, feImageTag, feMergeTag, feMergeNodeTag, feMorphologyTag, feOffsetTag, feSpecularLightingTag, feTileTag, feTurbulenceTag
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

#define MACRO_FORWORD(x) struct x ;
#define XELSMAC(mac,x) max(x)
#define XLSMACENU(mac,x, ...) mac(x) \
XLSMACENU(mac,__VA__ARGS__) 

SLXMACENU(MACRO_FORWARD, ANIMATIONELS,BASICSHAPES,CONTAINERELS,DESCRIPTIVEELS,FILTERPRIMITIVEELS,GRADIENTELS,GRAPHICSELS,GRAPHICSREFERENCINGELS,LIGHTSOURCEELS,NEVERRENDEREDELS,PAINTSERVERELS,RENDERABLEELS,SHAPEELS,STRUCTURALELS,TEXTCONTENTELS,TEXTCONTENTCHILDELS,UNCATEGORIZEDELS)


struct OneOfType {std::string name;
    template <pri::Str s,typename t> 
    struct TY : CEStr<s> {using type = t;};
std::string str(){return name;};
    template <class bM,class... bMs>
    bool OneOf(){
        if(str()==bM::str()){return true;}
        else if constexpr (sizeof...(bMs)>0){return OneOf<bMs...>();}
        return false;
    };
};

struct Number : float{
    Number(std::string str){
        size_t p=0;float flt=0;
        for(;!std::isalnum(str[p]);++p){};
        for(;std::isalnum(str[p]);++p){flt+=str[p]-'0';};
        if(str[p]=='.'){++p;
            size_t i=0;
                    for(;std::isalnum(str[p]);++p){++i;flt*=10;flt+=str[p]-'0';};
                for(;i;--i){flt/=10;}
        };
    };
};
typedef std::vector<Number> NumberList ;
typedef Number Angle;


typedef std::string name;
#include <stdexcept>
struct percentage : public Number {
    percentage(std::string& st) {size_t s=0;for(; std::isdigit(st[s])  ;s++){*this*=10+st[s]-0;}
        for(;st[s]=' ';++s){};
        if(st[s]=='%'){return;}
        else{throw std::logic_error();}
    ;}
};
struct length : Number {};


struct lengthOrPercentage : Number{
    bool len;
    lengthOrPercentage(std::string& str){
        percentage pr;
        try(pr = percentage(str))
        catch(const std::logic_error& e){
            len=true;*this=pr;
        }
    };
};
using _x = Var<"x",lengthOrPercentage>;
using _y = Var<"y",lengthOrPercentage>;
using _dx = Var<"dx",lengthOrPercentage>;
using _dy = Var<"dy",lengthOrPercentage>;

template <typename T,typename... Ts>
struct Union : NSC variant<T,Ts...> {

    template <typename T,typename T,typename... Ts>
    static constexpr size_t getSize(){

    }
};

struct  Any {
    std::variant<Number,Pt>
} ;
typedef ListOfAny ;



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
    Number curl ; // means nothin;
    Number theta; // Direction of striation 
    bool radial; // Theta now means 
    glm::dvec2 strokeWidths;
    glm::dvec2 straightness;
    

};*/

// TODO make more modular (separate binar impl from gltf )

glm::dvec4 rgba16itorgbaf(glm::uvec4 s){glm::vec4 t = s.xyzw ;t= t/0xFF; };

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
    Number weight;
    Number random ;
    Number stabilize;
    glm::dmat4 filt ;
};
template <pri::Str s,uint32_t nc>
struct cssColor : CEStr<s>{ static constexpr uint32_t num= nc; }

using cssAliceBlue = cssColor<"AliceBlue",0xF0F8FF>;// #F0F8FF
using cssAntiqueWhite = cssColor<"AntiqueWhite",0xFAEBD7>;// #FAEBD7
using cssAqua = cssColor<"Aqua",0x00FFFF>;// #00FFFF
using cssAquamarine = cssColor<"Aquamarine",0x7FFFD4>;// #7FFFD4
using cssAzure = cssColor<"Azure",0xF0FFFF>;// #F0FFFF
using cssBeige = cssColor<"Beige",0xF5F5DC>;// #F5F5DC
using cssBisque = cssColor<"Bisque",0xFFE4C4>;// #FFE4C4
using cssBlack = cssColor<"Black",0x000000>;// #000000
using cssBlanchedAlmond = cssColor<"BlanchedAlmond",0xFFEBCD>;// #FFEBCD
using cssBlue = cssColor<"Blue",0x0000FF>;// #0000FF
using cssBlueViolet = cssColor<"BlueViolet",0x8A2BE2>;// #8A2BE2
using cssBrown = cssColor<"Brown",0xA52A2A>;// #A52A2A
using cssBurlyWood = cssColor<"BurlyWood",0xDEB887>;// #DEB887
using cssCadetBlue = cssColor<"CadetBlue",0x5F9EA0>;// #5F9EA0
using cssChartreuse = cssColor<"Chartreuse",0x7FFF00>;// #7FFF00
using cssChocolate = cssColor<"Chocolate",0xD2691E>;// #D2691E
using cssCoral = cssColor<"Coral",0xFF7F50>;// #FF7F50
using cssCornflowerBlue = cssColor<"CornflowerBlue",0x6495ED>;// #6495ED
using cssCornsilk = cssColor<"Cornsilk",0xFFF8DC>;// #FFF8DC
using cssCrimson = cssColor<"Crimson",0xDC143C>;// #DC143C
using cssCyan = cssColor<"Cyan",0x00FFFF>;// #00FFFF
using cssDarkBlue = cssColor<"DarkBlue",0x00008B>;// #00008B
using cssDarkCyan = cssColor<"DarkCyan",0x008B8B>;// #008B8B
using cssDarkGoldenRod = cssColor<"DarkGoldenRod",0xB8860B>;// #B8860B
using cssDarkGray = cssColor<"DarkGray",0xA9A9A9>;// #A9A9A9
using cssDarkGrey = cssColor<"DarkGrey",0xA9A9A9>;// #A9A9A9
using cssDarkGreen = cssColor<"DarkGreen",0x006400>;// #006400
using cssDarkKhaki = cssColor<"DarkKhaki",0xBDB76B>;// #BDB76B
using cssDarkMagenta = cssColor<"DarkMagenta",0x8B008B>;// #8B008B
using cssDarkOliveGreen = cssColor<"DarkOliveGreen",0x556B2F>;// #556B2F
using cssDarkOrange = cssColor<"DarkOrange",0xFF8C00>;// #FF8C00
using cssDarkOrchid = cssColor<"DarkOrchid",0x9932CC>;// #9932CC
using cssDarkRed = cssColor<"DarkRed",0x8B0000>;// #8B0000
using cssDarkSalmon = cssColor<"DarkSalmon",0xE9967A>;// #E9967A
using cssDarkSeaGreen = cssColor<"DarkSeaGreen",0x8FBC8F>;// #8FBC8F
using cssDarkSlateBlue = cssColor<"DarkSlateBlue",0x483D8B>;// #483D8B
using cssDarkSlateGray = cssColor<"DarkSlateGray",0x2F4F4F>;// #2F4F4F
using cssDarkSlateGrey = cssColor<"DarkSlateGrey",0x2F4F4F>;// #2F4F4F
using cssDarkTurquoise = cssColor<"DarkTurquoise",0x00CED1>;// #00CED1
using cssDarkViolet = cssColor<"DarkViolet",0x9400D3>;// #9400D3
using cssDeepPink = cssColor<"DeepPink",0xFF1493>;// #FF1493
using cssDeepSkyBlue = cssColor<"DeepSkyBlue",0x00BFFF>;// #00BFFF
using cssDimGray = cssColor<"DimGray",0x696969>;// #696969
using cssDimGrey = cssColor<"DimGrey",0x696969>;// #696969
using cssDodgerBlue = cssColor<"DodgerBlue",0x1E90FF>;// #1E90FF
using cssFireBrick = cssColor<"FireBrick",0xB22222>;// #B22222
using cssFloralWhite = cssColor<"FloralWhite",0xFFFAF0>;// #FFFAF0
using cssForestGreen = cssColor<"ForestGreen",0x228B22>;// #228B22
using cssFuchsia = cssColor<"Fuchsia",0xFF00FF>;// #FF00FF
using cssGainsboro = cssColor<"Gainsboro",0xDCDCDC>;// #DCDCDC
using cssGhostWhite = cssColor<"GhostWhite",0xF8F8FF>;// #F8F8FF
using cssGold = cssColor<"Gold",0xFFD700>;// #FFD700
using cssGoldenRod = cssColor<"GoldenRod",0xDAA520>;// #DAA520
using cssGray = cssColor<"Gray",0x808080>;// #808080
using cssGrey = cssColor<"Grey",0x808080>;// #808080
using cssGreen = cssColor<"Green",0x008000>;// #008000
using cssGreenYellow = cssColor<"GreenYellow",0xADFF2F>;// #ADFF2F
using cssHoneyDew = cssColor<"HoneyDew",0xF0FFF0>;// #F0FFF0
using cssHotPink = cssColor<"HotPink",0xFF69B4>;// #FF69B4
using cssIndianRed = cssColor<"IndianRed",0xCD5C5C>;// #CD5C5C
using cssIndigo = cssColor<"Indigo",0x4B0082>;// #4B0082
using cssIvory = cssColor<"Ivory",0xFFFFF0>;// #FFFFF0
using cssKhaki = cssColor<"Khaki",0xF0E68C>;// #F0E68C
using cssLavender = cssColor<"Lavender",0xE6E6FA>;// #E6E6FA
using cssLavenderBlush = cssColor<"LavenderBlush",0xFFF0F5>;// #FFF0F5
using cssLawnGreen = cssColor<"LawnGreen",0x7CFC00>;// #7CFC00
using cssLemonChiffon = cssColor<"LemonChiffon",0xFFFACD>;// #FFFACD
using cssLightBlue = cssColor<"LightBlue",0xADD8E6>;// #ADD8E6
using cssLightCoral = cssColor<"LightCoral",0xF08080>;// #F08080
using cssLightCyan = cssColor<"LightCyan",0xE0FFFF>;// #E0FFFF
using cssLightGoldenRodYellow = cssColor<"LightGoldenRodYellow",0xFAFAD2>;// #FAFAD2
using cssLightGray = cssColor<"LightGray",0xD3D3D3>;// #D3D3D3
using cssLightGrey = cssColor<"LightGrey",0xD3D3D3>;// #D3D3D3
using cssLightGreen = cssColor<"LightGreen",0x90EE90>;// #90EE90
using cssLightPink = cssColor<"LightPink",0xFFB6C1>;// #FFB6C1
using cssLightSalmon = cssColor<"LightSalmon",0xFFA07A>;// #FFA07A
using cssLightSeaGreen = cssColor<"LightSeaGreen",0x20B2AA>;// #20B2AA
using cssLightSkyBlue = cssColor<"LightSkyBlue",0x87CEFA>;// #87CEFA
using cssLightSlateGray = cssColor<"LightSlateGray",0x778899>;// #778899
using cssLightSlateGrey = cssColor<"LightSlateGrey",0x778899>;// #778899
using cssLightSteelBlue = cssColor<"LightSteelBlue",0xB0C4DE>;// #B0C4DE
using cssLightYellow = cssColor<"LightYellow",0xFFFFE0>;// #FFFFE0
using cssLime = cssColor<"Lime",0x00FF00>;// #00FF00
using cssLimeGreen = cssColor<"LimeGreen",0x32CD32>;// #32CD32
using cssLinen = cssColor<"Linen",0xFAF0E6>;// #FAF0E6
using cssMagenta = cssColor<"Magenta",0xFF00FF>;// #FF00FF
using cssMaroon = cssColor<"Maroon",0x800000>;// #800000
using cssMediumAquaMarine = cssColor<"MediumAquaMarine",0x66CDAA>;// #66CDAA
using cssMediumBlue = cssColor<"MediumBlue",0x0000CD>;// #0000CD
using cssMediumOrchid = cssColor<"MediumOrchid",0xBA55D3>;// #BA55D3
using cssMediumPurple = cssColor<"MediumPurple",0x9370DB>;// #9370DB
using cssMediumSeaGreen = cssColor<"MediumSeaGreen",0x3CB371>;// #3CB371
using cssMediumSlateBlue = cssColor<"MediumSlateBlue",0x7B68EE>;// #7B68EE
using cssMediumSpringGreen = cssColor<"MediumSpringGreen",0x00FA9A>;// #00FA9A
using cssMediumTurquoise = cssColor<"MediumTurquoise",0x48D1CC>;// #48D1CC
using cssMediumVioletRed = cssColor<"MediumVioletRed",0xC71585>;// #C71585
using cssMidnightBlue = cssColor<"MidnightBlue",0x191970>;// #191970
using cssMintCream = cssColor<"MintCream",0xF5FFFA>;// #F5FFFA
using cssMistyRose = cssColor<"MistyRose",0xFFE4E1>;// #FFE4E1
using cssMoccasin = cssColor<"Moccasin",0xFFE4B5>;// #FFE4B5
using cssNavajoWhite = cssColor<"NavajoWhite",0xFFDEAD>;// #FFDEAD
using cssNavy = cssColor<"Navy",0x000080>;// #000080
using cssOldLace = cssColor<"OldLace",0xFDF5E6>;// #FDF5E6
using cssOlive = cssColor<"Olive",0x808000>;// #808000
using cssOliveDrab = cssColor<"OliveDrab",0x6B8E23>;// #6B8E23
using cssOrange = cssColor<"Orange",0xFFA500>;// #FFA500
using cssOrangeRed = cssColor<"OrangeRed",0xFF4500>;// #FF4500
using cssOrchid = cssColor<"Orchid",0xDA70D6>;// #DA70D6
using cssPaleGoldenRod = cssColor<"PaleGoldenRod",0xEEE8AA>;// #EEE8AA
using cssPaleGreen = cssColor<"PaleGreen",0x98FB98>;// #98FB98
using cssPaleTurquoise = cssColor<"PaleTurquoise",0xAFEEEE>;// #AFEEEE
using cssPaleVioletRed = cssColor<"PaleVioletRed",0xDB7093>;// #DB7093
using cssPapayaWhip = cssColor<"PapayaWhip",0xFFEFD5>;// #FFEFD5
using cssPeachPuff = cssColor<"PeachPuff",0xFFDAB9>;// #FFDAB9
using cssPeru = cssColor<"Peru",0xCD853F>;// #CD853F
using cssPink = cssColor<"Pink",0xFFC0CB>;// #FFC0CB
using cssPlum = cssColor<"Plum",0xDDA0DD>;// #DDA0DD
using cssPowderBlue = cssColor<"PowderBlue",0xB0E0E6>;// #B0E0E6
using cssPurple = cssColor<"Purple",0x800080>;// #800080
using cssRebeccaPurple = cssColor<"RebeccaPurple",0x663399>;// #663399
using cssRed = cssColor<"Red",0xFF0000>;// #FF0000
using cssRosyBrown = cssColor<"RosyBrown",0xBC8F8F>;// #BC8F8F
using cssRoyalBlue = cssColor<"RoyalBlue",0x4169E1>;// #4169E1
using cssSaddleBrown = cssColor<"SaddleBrown",0x8B4513>;// #8B4513
using cssSalmon = cssColor<"Salmon",0xFA8072>;// #FA8072
using cssSandyBrown = cssColor<"SandyBrown",0xF4A460>;// #F4A460
using cssSeaGreen = cssColor<"SeaGreen",0x2E8B57>;// #2E8B57
using cssSeaShell = cssColor<"SeaShell",0xFFF5EE>;// #FFF5EE
using cssSienna = cssColor<"Sienna",0xA0522D>;// #A0522D
using cssSilver = cssColor<"Silver",0xC0C0C0>;// #C0C0C0
using cssSkyBlue = cssColor<"SkyBlue",0x87CEEB>;// #87CEEB
using cssSlateBlue = cssColor<"SlateBlue",0x6A5ACD>;// #6A5ACD
using cssSlateGray = cssColor<"SlateGray",0x708090>;// #708090
using cssSlateGrey = cssColor<"SlateGrey",0x708090>;// #708090
using cssSnow = cssColor<"Snow",0xFFFAFA>;// #FFFAFA
using cssSpringGreen = cssColor<"SpringGreen",0x00FF7F>;// #00FF7F
using cssSteelBlue = cssColor<"SteelBlue",0x4682B4>;// #4682B4
using cssTan = cssColor<"Tan",0xD2B48C>;// #D2B48C
using cssTeal = cssColor<"Teal",0x008080>;// #008080
using cssThistle = cssColor<"Thistle",0xD8BFD8>;// #D8BFD8
using cssTomato = cssColor<"Tomato",0xFF6347>;// #FF6347
using cssTurquoise = cssColor<"Turquoise",0x40E0D0>;// #40E0D0
using cssViolet = cssColor<"Violet",0xEE82EE>;// #EE82EE
using cssWheat = cssColor<"Wheat",0xF5DEB3>;// #F5DEB3
using cssWhite = cssColor<"White",0xFFFFFF>;// #FFFFFF
using cssWhiteSmoke = cssColor<"WhiteSmoke",0xF5F5F5>;// #F5F5F5
using cssYellow = cssColor<"Yellow",0xFFFF00>;// #FFFF00
using cssYellowGreen = cssColor<"YellowGreen",0x9ACD32>;// #9ACD32
#define CSSCOLORS cssAliceBlue,cssAntiqueWhite,cssAqua,cssAquamarine,cssAzure,cssBeige,cssBisque,cssBlack,cssBlanchedAlmond,cssBlue,cssBlueViolet,cssBrown,cssBurlyWood,cssCadetBlue,cssChartreuse,cssChocolate,cssCoral,cssCornflowerBlue,cssCornsilk,cssCrimson,cssCyan,cssDarkBlue,cssDarkCyan,cssDarkGoldenRod,cssDarkGray,cssDarkGrey,cssDarkGreen,cssDarkKhaki,cssDarkMagenta,cssDarkOliveGreen,cssDarkOrange,cssDarkOrchid,cssDarkRed,cssDarkSalmon,cssDarkSeaGreen,cssDarkSlateBlue,cssDarkSlateGray,cssDarkSlateGrey,cssDarkTurquoise,cssDarkViolet,cssDeepPink,cssDeepSkyBlue,cssDimGray,cssDimGrey,cssDodgerBlue,cssFireBrick,cssFloralWhite,cssForestGreen,cssFuchsia,cssGainsboro,cssGhostWhite,cssGold,cssGoldenRod,cssGray,cssGrey,cssGreen,cssGreenYellow,cssHoneyDew,cssHotPink,cssIndianRed,cssIndigo,cssIvory,cssKhaki,cssLavender,cssLavenderBlush,cssLawnGreen,cssLemonChiffon,cssLightBlue,cssLightCoral,cssLightCyan,cssLightGoldenRodYellow,cssLightGray,cssLightGrey,cssLightGreen,cssLightPink,cssLightSalmon,cssLightSeaGreen,cssLightSkyBlue,cssLightSlateGray,cssLightSlateGrey,cssLightSteelBlue,cssLightYellow,cssLime,cssLimeGreen,cssLinen,cssMagenta,cssMaroon,cssMediumAquaMarine,cssMediumBlue,cssMediumOrchid,cssMediumPurple,cssMediumSeaGreen,cssMediumSlateBlue,cssMediumSpringGreen,cssMediumTurquoise,cssMediumVioletRed,cssMidnightBlue,cssMintCream,cssMistyRose,cssMoccasin,cssNavajoWhite,cssNavy,cssOldLace,cssOlive,cssOliveDrab,cssOrange,cssOrangeRed,cssOrchid,cssPaleGoldenRod,cssPaleGreen,cssPaleTurquoise,cssPaleVioletRed,cssPapayaWhip,cssPeachPuff,cssPeru,cssPink,cssPlum,cssPowderBlue,cssPurple,cssRebeccaPurple,cssRed,cssRosyBrown,cssRoyalBlue,cssSaddleBrown,cssSalmon,cssSandyBrown,cssSeaGreen,cssSeaShell,cssSienna,cssSilver,cssSkyBlue,cssSlateBlue,cssSlateGray,cssSlateGrey,cssSnow,cssSpringGreen,cssSteelBlue,cssTan,cssTeal,cssThistle,cssTomato,cssTurquoise,cssViolet,cssWheat,cssWhite,cssWhiteSmoke,cssYellow,cssYellowGreen

#include <cctype>


struct svgTag ;

template <pri::Str s,typename T, class SubT=SubTags<void>, class Ats=Attrs<void> , T vald= T()> 
struct STag : Tag<s,T,SubT,Ats,vald> {};

glm::uvec3 getColor(uint32_t h){return glm::vec3(  (h>>16) &0xFF / 0xFF, (h>>8) & 0xFF00 / 0xFF, h & 0xFF / 0xFF );};
uint32_t getcolor(std::string& g){
    uint32_t i;size_t p=1;
    for(;p<g.size();++p){
        i*=0x10;
        if(std::isdigit(g[p])){i+=g[p] - '0' ;}
        else {i+=0xA + (g[p] - 'A');}
    }
}
struct color : uint32_t {
    template <typename T, typename... Ts>
    void _OneOf(std::string& str){
        if(str==T::str()){*this = T::cno;}
        else if constexpr (sizeof...(Ts)>0){_OneOf<Ts...>(str);}
    };
    color(std::string& str) {
        if(str[0] = '#') {*this = getcolor(str);}
        else {_OneOf<CSSCOLORS>(str);}
    } ; 
    color () {*this =0xFFFFFFFF;}
};  
struct filtTag : SVar<"filt",glm::dmat4,Attrs<Var<"color",color>,
                                       Var<"weight",Number>,
                                       Var<"random",Number>,
                                       Var<"stabilize",Number>,
                                         {};
void filt_color(im& i){};
void filt_striate(im& i){};
auto filt_fibrate(im& i , filt f  ){};
auto filt_cybrate(im& i , filt f ){};
auto filt_perlin(im& i , filt f ){};
auto filt_simplex(im& i , filt f ){};
auto filt_convolve(im& i , filt f ){};
auto filt_turbulence(im& i , filt f ){};
struct shape_at ;



#define AtTagSub animateMotionTag,\
    animateTransformTag,\
    Var<"stroke",color>,\
    Var<"fe",glm::mat4>
#define AtTagAts     Var<"stroke-width",Number>,\
    Var<"fill",color>,\
    Var<"fill-opacity",Percentage>,\
    Var<"stroke-opacity",Percentage>,\
    Var<"stroke",color>,\


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
struct sec : Number {
    sec(std::string& str){
        Number t=0;size_t p=0;
        for(;std::isdigit(str[p]);++p){t*=10;t+=str[p]-'0';}
        if(str[p]=='.'){++p;}
        size_t i=0;
        for(;std::isdigit(str[p]);++p){++i;t*=10;t+=str[p]-'0';}
        while(i){t/=10;}
        std::string st;
        for(;std::isalnum(str[p]);++p){st+=std::string(str[p]);}
        if(st==std::string("ms")){t/=1000;}
        *this=t;
    }
};

template <typename T> 
struct vec : std::vector<T> {
    vec(std::string& str){
        std::string st;
        for(size_t p=0;p<str.length();++p){if(str[p]==';'){emplace_back(st);st=std::string();}else{st+=str[p];};}
    };
};
struct secVec : vec<sec> {};


template <typename T> 
struct list : std::vector<T> {
    list(std::string& str){
        std::string st;
        for(size_t p=0;p<str.length();++p){if(str[p]==' '){emplace_back(st);st=std::string();}else{st+=str[p];};}
    };
};


struct any : std::variant<Number,sec>{}
struct listOfAny :vec<any>{}
using begin = Var<"begin",secs>;
using dur = Var<"dur",secs>;
using end = Var<"end",secs>;
using min = Var<"min",Number>;
using max = Var<"max",Number>;
using restart = Var<"restart",RestartAnim>;
using repeatCount = Var<"repeatCount",Number>;
using repeatDur = Var<"repeatDur",secs>;
using fill = Var<"fill",color>;
using calcMode = Var<"calcMode",calcMode>;
using values = Var<"values",NumberVec>;
using keyTimes = Var<"keyTimes",vec<sec>>;
using keySplines = Var<"keySplines",vec<dVar>>;
using from = Var<"from",ListOfAny>;
using to = Var<"to",ListOfAny>;
using by = Var<"by",ListOfAny>;
struct attributeName : Var<"attributeName",attribName>{
    attributeName(std::string& str){}
};
using additive = Var<"additive",>;
using accumulate = Var<"accumulate",>;
using onbegin = Var<"onbegin",>;
using onend = Var<"onend",>;
using onrepeat = Var<"onrepeat",>;
#define ANIMATIONTIMINGATS begin, dur, end, min, max, restart, repeatCount, repeatDur, fill
#define ANIMATIONVALUEATS calcMode, values, keyTimes, keySplines, from, to, by
#define OTHERANIMATIONATS attributeName, additive, accumulate
#define ANIMATIONEVENTATS  onbegin, onend, onrepeat


struct attribName : Var<"attributeName",std::string> {};

struct clipPathTag : TAGC<"clpp", STag<"clipPath",void,SubTags<AtTagSub>,Attrs<AtTagAts,
Var<"clipPathUnits",filtUnits> {
    enum units {userSpaceOnUse,objectBoundingBox};units t;
    operator bool (){return data=="userSpaceOnUse" };
    using type = units;
    type get(svgTag& cnt){return t;}
};


struct aTag : TAGC<"a___"> ,Tag<"a",void,SubTags<>,Attrs<Var<"download",URL>,Var<"href",URL>> {};
struct repeatCount : uint32_t {
    repeatCount(std::string s){
        if(s=="indefinite"){*this = 0xFFFFFFFF;}
        else {for(char c : s){*this *=10 ; *this+=c-'0';};}
    }
};
struct animateTag : STag<"animate",void,SubTags<DESCRIPTIVEELS>,Attrs<attribName,Var<"values",NumberVec>,Var<"dur",Time> ,Var<"repeatCount",repCount> >> {};



struct dType {
    enum ty {
/*MoveTo:*/ M, m ,
/*LineTo:*/ L, l, H, h, V, v,
/*Cubic Bézier curve:*/ C, c, S, s,
/*Quadratic Bézier curve:*/ Q, q, T, t,
/*Elliptical arc curve:*/ A, a,
/*ClosePath: */Z, z,
none
    };
    template <char c,ty t> 
    struct cr {static constexpr char ch=  c;static constexpr ty type= t;};
    struct _M : cr<'M',M>{};
    struct _m : cr<'m',m>{};
    struct _L : cr<'L',L>{};
    struct _l : cr<'l',l>{};
    struct _H : cr<'H',H>{};
    struct _h : cr<'h',h>{};
    struct _V : cr<'V',V>{};
    struct _v : cr<'v',v>{};
    struct _C : cr<'C',C>{};
    struct _c : cr<'c',c>{};
    struct _S : cr<'S',S>{};
    struct _s : cr<'s',s>{};
    struct _Q : cr<'Q',Q>{};
    struct _q : cr<'q',q>{};
    struct _T : cr<'T',T>{};
    struct _t : cr<'t',t>{};
    struct _A : cr<'A',A>{};
    struct _a : cr<'a',a>{};
    struct _Z : cr<'Z',Z>{};
    struct _z : cr<'z',z>{};
#define TYS _M,_m,_L,_l,_H,_h,_V,_v,_C,_c,_S,_s,_Q,_q,_T,_t,_A,_a,_Z,_z

std::vector<ty> t;
std::vector<size_t > offs;
vec<pt> p;
template <typename CR,typename... CRs>
    constexpr char getTy( ty& t){
        if (CR::type==t){return CR::ch;}
        if constexpr (sizeof...(Crs)>0){return getTy<CRs...>(t);}
        return none;
};
template <typename CR,typename... CRs>
constexpr ty getTyStr(char c){
        if (CR::type==t){return CR::ch;}
        if constexpr (sizeof...(Crs)>0){return getTy<CRs...>(t);}
        return none;
 };
        operator std::string () {
            std::string str;size_t j=0;
            for(size_t i=0;i++) {
                str+=std::string(" ");str+= getTy<TYS>(t[i]);
                str+=std::string(" ");
                for(size_t j=offs[i];j<offs[i+1];j++){
                    str+=to_string(p[j]); str+=" ";
                }
            } 
        };
        dType(std::string& str){
            for(size_t i =0;i<str.length();i++){
                while(str[p]==' '){p++;}
                if(std::isdigit(str[i])) {Number fl = getNum(str,i);p.push_back(fl,0);
                    for(;str[i]!=',';++i ){}
                    ++i;                    for(;str[i]!=' ';++i ){};
                    p.back().y=getNum(str,i);
                }
                else {
                    ty c= getTyStr(str[i]);++i;
                    offs.push_back(p.size()) ;
                }

            }
        };

};


struct animateMotionTag : TAGC<"anmm">, Tag<"animateMotion",SubTags<DESCRIPTIVEELS,mpathTag>,
Attrs<
Var<"keyPoints",keyPoints>,
Var<"path",dType>,
Var<"rotate",Number>,
ANIMATIONTIMINGATS,ANIMATIONVALUEATS,OTHERANIMATIONATS,ANIMATIONEVENTATS
>> {};

struct animateTransformTag : TAGC<"anmt">, STag<"animateTransform",void, SubTags<DESCRIPTIVEELS> ,Attrs<by,from,to,typeList > > {};

struct circleTag : TAGC<"circ">, STag<"circle",void,SubTags<AtTagSub>,Attrs<AtTagAts,
Var<"cx",Number>,
Var<"cy",Number>,
Var<"r",Number>,
Var<"pathLength",Number>,
,dVar>> {};
struct clipPathTag : TAGC<"clpp">, STag<"clipPath",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,textTag,useTag>,Attrs<
Var<"clipPathUnits",filtUnits>
>> {};
struct defsTag : TAGC<"defs">, STag<"defs",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag, filterTag, foreignObjectTag, imageTag, markerTag, maskTag, patternTag, scriptTag, styleTag, switchTag, textTag, viewTag,
>,Attrs<GLOBALATTRS>> {};
struct descTag : TAGC<"desc"> Tag<"desc",void,SubTags<ALLELEMS>,Attrs<GLOBALATTRS>> {};
struct ellipseTag : STag<"ellipse",void,SubTags<AtTagSub>,
Attrs<AtTagAts,
Var<"cx",Number>,
Var<"cy",Number>,
Var<"rx",Number>,
Var<"ry",Number>,
Var<"pathLength",Number>
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
struct textpathTag : TAGC<"tpth"> Tag<"textpath",void,SubTags<AtTagSub,Tag<"text",std::string>,pathTag> ,Attrs<AtTagAts,Var<"d",path>,Attrs<AtTagAts>> {};

struct gTag: STag<"g",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,
    Attrs<AtTagAts>
>{};

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


struct amplitude : STag<"amplitude" ,Number> {};

using _width = Var<"width",lengthOrPercentage>;
using _height = Var<"height",lengthOrPercentage>;

#define FILTPRIMAT _x,_y,_width,_height,Tag<"result",Reference>,amplitude ;
struct feBlendTag : fe_base, TAGC<"febl">, STag<
"feBlend",void,SubTags<AtTagSub>,Attrs<AtTagAts,
Tag<"in",Reference>,
Tag<"in2",Reference>,
Tag<"mode",blend_mode>,
FILTPRIMAT>> {};
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
struct feColorMatrixTag : fe_base, TAGC<"fecm">, STag<
"feColorMatrix",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,
Tag<"in",Reference>,
Tag<"type",colMatrixType>,
Tag<"values",std::vector<Number>> ,FILTPRIMAT>> {};
struct feComponentTransferTag : fe_base,TAGC<"fect">, Tag<
"feComponentTransfer",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,Tag<"in",Reference>,FILTPRIMAT>> {};
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

struct feConvolveMatrixTag : fe_base,TAGC<"fecn">, STag<
"feConvolveMatrix",void,SubTags<AtTagSub>,Attrs<AtTagAts,FILTPRIMAT,
Var<"in",Reference>,
Var<"order",Number>,
Var<"kernelMatrix",NumberVec>,
Var<"divisior",Number>,
Var<"bias",Number>,
Var<"targetX",Number>,
Var<"targetY",Number>,
Var<"edgeMode",edgeMode>,
Var<"kernelUnitLength",Number>,
Var<"preserveAlpha",Boolean>
>
> {};
struct feDiffuseLightingTag : fe_base,TAGC<"fedf">, STag<
"feDiffuseLighting",void,SubTags<AtTagSub>,Attrs<AtTagAts,FILTPRIMAT,
Var<"in",Reference>,
Var<"surfaceScale",Number>,
Var<"diffuseConstant",Number>,
Var<"kernelUnitLength",Number>,
>
> {};


struct feDisplacementMapTag : fe_base, TAGC<"fedp">, STag<
"feDisplacementMap",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT,
Var<"in",Reference>,
Var<"in2",Reference>,
Var<"scale",Number>,
Var<"xChannelSelector",channelSelector>,
Var<"yChannelSelector",channelSelector>,
>
> {};
struct feDistantLightTag : fe_base, TAGC<"feds">, STag<
"feDistantLight",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,Var<"azimuth",Number>,Var<"elevation",Number>>
> {};
struct feDropShadowTag : fe_base, TAGC<"feds">, STag<
"feDropShadow",void,SubTags<AtTagSub,animateTag,scriptTag,setTag>,Attrs<AtTagAts,FILTPRIMAT,
Var<"dx",Number>,
Var<"dy",Number>,
Var<"reference",Number>,
Var<"stdDeviation",Number>

>
> {};
struct feFloodTag  : TAGC<"fefl">, STag<
"feFlood",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT,Var<"flood-color",color>,Var<"flood-opacity",Number>
> {};
struct feFuncATag : fe_base,TAGC<"fefA">, STag<"feFuncA",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};
struct feFuncBTag : fe_base,TAGC<"fefB">, STag<"feFuncB",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};
struct feFuncGTag : fe_base,TAGC<"fefG">, STag<"feFuncG",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};
struct feFuncRTag : fe_base,TAGC<"fefR">, STag<"feFuncR",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<AtTagAts,FILTPRIMAT>> {};

struct feGaussianBlurTag : fe_base, TAGC<"fegb"> ,  STag<
"feGaussianBlur",void,SubTags<AtTagSub>,Attrs<AtTagAts,FILTPRIMAT,Var<"in",Reference>,Var<"stdDeviation",Number>,Var<"edgeMode",edgeMode>> > {};
struct feImageTag : fe_base, STag<
"feImage",void,SubTags<AtTagSub,animateTag,setTag,animateTransformTag>,Attrs<AtTagAts,FILTPRIMAT,
Var<"crossorigin",crossorigin>,
Var<"fetchpriority",fetchpriority>,
Var<"preserveAspectRatio",preserveAspectRatio>,
Var<"href",href>
>
> {};
struct feMergeTag : fe_base, TAGC<"femt">, STag<
"feMerge",void,SubTags<AtTagSub,feMergeNodeTag>,Attrs<>> {};
struct feMergeNodeTag : fe_base, TAGC<"femnn">, STag<
"feMergeNode",void,SubTags<AtTagSub,animateTag,setTag>,Attrs<Var<"in",Reference>>> {};
struct feMorphologyTag : fe_base, TAGC<"femp">, STag<
"feMorphology",void,SubTags<AtTagSub>,Attrs<Var<"in",Reference>,Var<"operator",operatorType>,Var<"radius",Number>,FILTPRIMAT>
> {};
struct feOffsetTag : fe_base, TAGC<"feof">, STag<
"feOffset",void,SubTags<AtTagSub>,Attrs<Var<"in",Reference>,Var<"dx",Number>,Var<"dy",Number>,FILTPRIMAT>
> {};
struct fePointLightTag : fe_base, TAGC<"fepl">, STag<
"fePointLight",void,SubTags<animateTag,setTAg>,Attrs<Var<"x",Number>,Var<"y",Number>,Var<"z",Number>>
> {};


struct feSpecularLightingTag : fe_base, TAGC<"fesl">, STag<
"feSpecularLighting",void,SubTags<AtTagSub,LIGHTSOURCEELS>,Attrs<FILTPRIMAT,
Var<"in",Reference>,
Var<"surfaceScale",Number>,
Var<"specularConstant",Number>,
Var<"specularExponent",Number>,
Var<"kernelUnitLength",Number>>
> {};
struct feSpotLightTag : fe_base, TAGC<"fesp">, STag<
"feSpotLight",void,SubTags<animateTag,setTag>,Attrs<
Var<"x",Number>,
Var<"y",Number>,
Var<"z",Number>,
Var<"pointsAtX",Number>,
Var<"pointsAtY",Number>,
Var<"pointsAtZ",Number>,
Var<"specularExponent",Number>,
Var<"limitingConeAngle",Number>,
>
> {};
struct feTileTag : fe_base, TAGC<"feti"> ,Tag<
"feTile",void,SubTags<animateTag,setTag>,Attrs<Var<"in",Reference>,FILTPRIMAT>
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

struct feTurbulenceTag : fe_base, TAGC<"fetu">, STag<
"feTurbulence",void,SubTags<animateTag,setTag>,Attrs<FILTPRIMAT,
Var<"baseFrequency",Number>,
Var<"numOctaves",Number>,
Var<"seed",Number>,
Var<"stitchTiles",Number>,
Var<"type",turbulenceType> >> {};

struct filterTag : TAGC<"filt">, STag<
"feTurbulence",void,SubTags<DESCRIPTIVEELS,FILTERPRIMITIVEELS,animateTag,setTag>,Attrs<
Var<"x",Number>,
Var<"y",Number>,
Var<"width",Number>,
Var<"height",Number>,
Var<"filterUnits",filtUnits>,
Var<"primitiveUnits",filtUnits>>
> {};

struct foreingObjectTag: TAGC<"fobj">, STag<
"feTurbulence",void,SubTags<DESCRIPTIVEELS,FILTERPRIMITIVEELS,animateTag,setTag>,Attrs<
Var<"x",Number>,
Var<"y",Number>,
Var<"width",Number>,
Var<"height",Number>>> {

};

struct gTag : TAGC<"gtag">, STag<"g",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreignObjectTag,imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>, 
Attrs<> {} ;

struct preserveAspectRatio :TAGC<"pasp">,  OneOfType {
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
    template <size_t S>
    preserveAspecRatio(char c[s]){name = std::string(c);OneOf<TYPES>();}
};
using _preserveAspecRatio = Var<"preserveAspecRatio",preserveAspectRatio>;
struct crossorigin : OneOfType {
   enum ty {anonymous,use_credentials};ty type;
   struct anonymousTY : TY<"anonymous"            , anonymous> {} ;
   struct use_credentialsTY : TY<"use-credentials", use_credentials> {} ;
    #define TYPES anonymous,use_credentials
     crossorigin(std::string& str) { name= str ; OneOfType<TYPES>();}
};
using _crossorigin = Var<"crossorigin", crossorigin>; 

struct decoding : OneOfType {
   enum ty {async,sync,_auto};ty type;
   struct asyncTY : TY<"async",async> {}; 
   struct syncTY : TY<"sync",sync> {}; 
   struct _autoTY : TY<"auto",_auto> {}; 
    #define TYPES asyncTY,syncTY,_autoTY
    decoding(std::string& str) { name= str ; OneOfType<TYPES>();}

};
using _decoding = Var<"decoding",decoding>;
struct fetchpriority : OneOfType {
  enum ty {high,low,_auto};ty type;
   struct highTY : TY<"high",high> {}; 
   struct lowTY : TY<"low",low> {}; 
   struct _autoTY : TY<"auto",_auto> {}; 
    #define TYPES highTY,lowTY,_autoTY

    fetchpriority(std::string& str) { name = str; OneOf<TYPES>();}
};
using _fetchpriority = Var<"fetchpriority",fetchpriority>;

struct spreadMethod : OneOfType {
  enum ty {pad,reflect,repeat};ty type;
   
  struct padTY : TY<"pad",pad> {}; 
   struct reflectTY : TY<"reflect",reflect> {}; 
   struct repeatTY : TY<"repeat",repeat> {}; 
    #define TYPES padTY,reflectTY,repeatTY

    spreadMethod(std::string& str) { name = str; OneOf<TYPES>();}
};
using _spreadMethod = Var<"spreadMethod",spreadMethod>;


struct imageTag : TAGC<"imag">, STag<"image",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,animateTag,animateMotionTag,animateTransformTag,scriptTag,setTag,styleTag>,
Attrs<
Var<"x",Number>,
Var<"y",Number>,
Var<"width",Number>,
Var<"height",Number>,
Var<"href",URL>,
_preserveAspecRatio,
_crossorigin,
_decoding,
_fetchpriority
>> {};

struct lineTag : TAGC<"line">, STag<"line",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<AtTagAts
Var<"x1",Number>,
Var<"x2",Number>,
Var<"y1",Number>,
Var<"y2",Number>,
Var<"pathLength",Number>
>> {};


struct linearGradientTag : TAGC<"lgrd">, STag<"linearGradient",void,SubTags<DESCRIPTIVEELS,animateTag,animateTransformTag,scriptTag,setTag,stopTag,styleTag>,Attrs<
Var<"gradientUnits",filtUnits>,
Var<"gradientTransform",TransformList>,
Var<"href",URL>,
Var<"href",spreadMethod>,
Var<"x1",Number>,
Var<"x2",Number>,
Var<"y1",Number>,
Var<"y2",Number>
 >> {};


 struct viewBoxT : vec<Number> {pt getPt(){return pt(at(0),at(1));}; pt getDim(){return pt(at(2), at(3)) ;};};
 
 struct markerTag : TAGC<"mrkr">, STag<"marker",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreignObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Var<"markerHeight",Number>,
 Var<"markerUnits",filtUnits>,
 Var<"markerWith",Number>,
 Var<"orient",Angle>,
 Var<"preserveAspecRatio",preserveAspecRatio>,
 Var<"refX",Number>,
 Var<"refY",Number>, 
 Var<"viewBox",viewBoxT>
 >> {};
 struct maskTag : TAGC<"mask">, STag<"mask",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Var<"height",Number>,
 Var<"mask-type",maskType>,
 Var<"maskContentUnits",filtUnits>,
 Var<"maskUnits",filtUnits>,
 Var<"x",Number>,
 Var<"y",Number>,
 Var<"width",Number>,
 >> {};
 struct metadataTag : TAGC<"mdat">, STag<"metadata",void,SubTags<AtTagSub>,Attrs<AtTagSub>> {};
 struct mpathTag : STag<"mpath",void,SubTags<DESCRIPTIVEELS>,Attrs<Tag<"href",Reference>>> {};
 

    Number getNum(std::string& str,size_t& p){
        Number n;size_t comma = 0;
        for(;str[p] >'=0' or (str[p]<='9';p++) ){
            n=str[p]- '0';

            p++;if(str[p]=='.'){comma++;continue;}
            if(comma>0){comma++;}
        }
        while(comma>0){n/=10;--comma;}
        return n;
    };
    
struct transformType {
        enum ty {scale,rotate,skewX,skewY} ;
    ty gett(std::string& str){
        if(str=="scale"){return scale;}
        if(str=="rotate"){return rotate;}
        if(str=="skewX"){return skewX;}
        if(str=="skewY"){return skewY;}
        return rotate;
    };
   std::string  gets(ty& str){
        if(str==scale){return "scale";}
        if(str==rotate){return "rotate";}
        if(str==skewX){return "skewX";}
        if(str==skewY){return "skewY";}
        return skewY;
    };

    transformType(std::string& str) {t=gett(str);}
};

struct transformList : vec<transformType> {};
 struct pt : glm::vec2{ 
     pt(std::string str){
    size_t p=0;std::string st;
    for(;!std::isalnum(str[p]);++p){st+=str[p];}
    while(;str[p]!=','){++p;}
    ++p;x=Number(pt);
    for(;std::isalnum(str[p]);++p){};
 }
};
std::string to_string(pt& p){
    std::string str;str+=std::to_string(p.x);
    str+=",";
    str+=std::to_string(p.y);return str;
};


struct dVar : Var<"d",dType> {dVar(std::string& str){data=dType(str);}};

struct pathTag : TAGC<"path">, STag<"path",SubTags<ANIMATIONELS,DESCRIPTIVEELS> ,Attrs<dVar, Var<"pathLength",Number>> > {
    struct type {
        Number pathLength ;
        dVar d;
        type(svgTag& cnt,selfType& tp) {d=tp.getStr<"d">();};
    };

};
 struct patternTag : STag<"pattern",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,GRADIENTELS,SHAPEELS,STRUCTURALELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs<
 Var<"height",Number>,
 Var<"href",Raference>,
 Var<"paternContentUnits",filtUnits>,
 Var<"patternTransform",transformList>,
 Var<"patternUnits",filtUnits>,
 Var<"preserveAspectRatio",preserveAspectRatio>,
 Var<"viewBox",NumberVec>,
 Var<"width",Number>,
 Var<"x",Number>
 >> {};
 typedef Vec<pt> pts;
 struct polygonTag : TAGC<"plgn">, STag<"polygon",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<Var<"points",pts>,Var<"pathLength",Number>>> {}
 struct polylineTag : TAGC<"plln">, STag<"polyline",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<Var<"points",pts>,Var<"pathLength",Number>>> {};
 struct radialGradientTag : STag<"radialGradient",void,SubTags<DESCRIPTIVEELS,animateTag,animateTransformTag,scriptTag,setTag,stopTag,styleTag>,
 Attrs<
 Var<"cx",Number>,
 Var<"cy",Number>,
 Var<"fr",Number>,
 Var<"fx",Number>,
 Var<"fy",Number>,
 Var<"gradientUnits",filtUnits>,
 Var<"gradientTransform",NumberVec>,
 Var<"href",URL>,
 Var<"r",Number>,
 Var<"spreaMethod",spreadMethod>,
 >> {};
 
struct rectTag : TAGC<"rect">, STag<"rect",void,SubTags<AtTagSub,ANIMATIONELS,DESCRIPTIVEELS>,Attrs<AtTagAts,
Var<"x",Number>,
Var<"y",Number>,
Var<"width",Number>,
Var<"height",Number>,
Var<"rx",Number>,
Var<"ry",Number>,
Var<"pathLength",Number>,
,dVar>,>;
struct mediaType : OneOfType {
    enum ty {image} ;ty type;
};
 struct scriptTag : TAGC<"scrp">, STag<"script",void,SubTags<AtTagAts>,Attrs<
 Var<"crossorigin",>,
 Var<"fetchpriority",fetchpriority>,
 Var<"href",URL>,
 Var<"type",mediaType>,
 >> {}
 struct setTag : TAGC<"sett">, STag<"set",void,SubTags<DESCRIPTIVEELS>,Attrs<to,attributeName>> {}
 struct stopTag : TAGC<"stop">, STag<"stop",void,SubTags<animateTag,scriptTag,setTag,styleTag>,Attrs<
 Var<"offset",Number>,
 Var<"stop-color",color>,
 Var<"stop-opacity",Number>
 >> {};
 struct styleTag : TAGC<"styl">, STag<"style",void,SubTags<AllElements>,Attrs<
 Var<"type",mediaType>,
 Var<"media",mediaType>,
 Tag<"tiyle",std::string>,
 >> {};

 struct svgTag : TAGC<"svgt">, STag<"svg",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,
 imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,Attrs< Var<"baseProfile",std::string>,
 Var<"x",Number>,
 Var<"y",Number>,
 Var<"width",Number>,
 Var<"height",Number>,
 Var<"viewBox",vec<Number>>,
 _preserveAspecRatio,
 Var<"version",Number>,
 Var<"viewBox",Vec<Number>> > 
 > {
    struct st{

    };
    template <typename T>
    void getRef(std::string& str){

    };

 };
 struct switchTag : TAGC<"swtc">, STag<"switch",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,aTag,foreingObjectTag,gTag,imageTag,svgTag,switchTag,textTag,useTag>,
 Attrs<
 Var<"requiredExtensions",URLLIST>,
 Var<"systemLanguage",languageList>
 >> { using btype = bsvgTag;
  };
 struct symbolTag : TAGC<"symb">, STag<"symbol",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS,SHAPEELS,STRUCTURALELS,GRADIENTELS,aTag,clipPathTag,filterTag,foreingObjectTag,imageTag,markerTag,maskTag,patternTag,scriptTag,styleTag,switchTag,textTag,viewTag>,
 Attrs<
 Var<"height",Number>,
 Var<"preserveAspecRatio",preserveAspecRatio>,
 Var<"refX",Number>,
 Var<"refY",Number>,
 Var<"viewBox",NumberList>,
 Var<"width",Number>,
 Var<"x",Number>,
 Var<"y",Number>,
 >> {};

 struct lengthAjust : OneOfType {
    enum ty {spacing,spacingAndGLyphs} ; ty type;
    spacingTY : TY<"spacing",spacing> {};,
    spacingAndGLyphsTY : TY<"spacingAndGLyphs",spacingAndGLyphs> {};
    #define TYPES spacingTY,spacingAndGLyphsTY
    lengthAjust(std::string& str){ name=str;OneOf<TYPES>() ;}
 };

 struct sideAt {enum ty{left,right};
    sideAt(std::string& str){if(str==std::string("left")){t=left;}else{t=right;}}
 };

struct font_family : Var<"font-family",Num{};
struct font_size : Var<"font-size",Number{};
struct font_size_adjust : Var<"font-size-adjust",Number{};
struct font_stretch : Var<"font-stretch",Number{};
struct _font_style {
    enum ty {normal,italic,oblique};ty t;
    font_style (std::string str){
        switch(str){
            case std::string("normal") : {t=normal;};
            case std::string("italic") : {t=italic;};
            case std::string("oblique") : {t=oblique;};
        };
    };
};
struct font_style : Var<"font-style",_font_style{};
// struct font_variant : Var<"font-variant",_font_variant{};
struct font_weight : Var<"font-weight",_font_weight{};

#define TEXTAts font_family,font_size,font_size_adjust,font_stretch,font_stlye,font_weight

 struct textTag : TAGC<"text">, STag<"text",std::string,SubTags<ANIMATIONELS,DESCRIPTIVEELS,TEXTCONTENTCHILDELS,aTag>,Attrs<TEXTAts,AtTagAts,
 _x,_y, 
_dx,_dy,
 Var<"rotate",Number>,
 Var<"lengthAdjust",Number>,
 Var<"textLength",Number>>> {};
 struct textPathTag : TAGC<"tpat">, STag<"textPath",std::string,SubTags<DESCRIPTIVEELS,aTag,animateTag,setTag,tspanTag>,Attrs<TEXTAts,AtTAgAts,
 Var<"href",URL>,
 Var<"lengthAjust",lengthAjust>,
 Var<"method",methodAdjust>,
  Var<"path",dType>,
Var<"side",sideAt>,
 Var<"spacing",spacingType>,
 Var<"startOffset",Number>,
 Var<"textLength",Number>,
 >> {
    
 };
 struct titleTag :TAGC<"tile">, Tag<"title",std::string,SubTags<ALLELEMS>,Attrs<TEXTAts,void>> {}
 struct tspanTag : TAGC<"tspn">, STag<"tspan",void,SubTags<DESCRIPTIVEELS,aTag,animateTag,setTag,tspanTag>,Attrs<TEXTAts,
 _x,_y, 
 Var<"dx",Number>,
 Var<"dy",Number>,
 Var<"rotate",c>,
 Var<"lengthAdjust",lengthAdjust>,
 Var<"textLength",Number>
 >> {};
 struct useTag : TAGC<"uset">, STag<"use",void,SubTags<ANIMATIONELS,DESCRIPTIVEELS>,Attrs<Var<"href",URL>>> {};
 struct viewTag : TAGC<"view">, STag<"view",void,SubTags<DESCRIPTIVEELS>,Attrs<
 Var<"preserveAspecRatio",preserveAspecRatio>,
 Var<"viewBox",NumberList>,
 >> {};


}