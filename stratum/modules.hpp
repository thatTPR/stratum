#ifndef MODULES_HPP
#define MODULES_HPP
#include <petri/macros.hpp>
#include <typeindex>
#include <cstddef>
#include <ifstream>
#include <math.h>
#include <vector>
#include <string>
#include <petri/vecs.hpp>
#include <petri/vects.hpp>
#include <tuple>
#include <map>
#include <lib/glm/glm.hpp>
#include <cstring>
#include <math.h>
#include <petri\list.hpp>


namespace modules {

    

struct app_info {
    char*  name;
    uint32_t  ver;
    char*  engname;
    char*  engver;
};

#define NAME_FALSE false
#define NAME_TRUE true



template <typename T>
struct named {
    std::string name;
    T data;
    named<T>& operator=(T& d){data=d;}
    named(std::string n, T& d) :name(n),data(d)  {};
} ;


enum image_formats {// Floating-point layout image formats:
rgba32f,
rgba16f,
rg32f,
rg16f,
r11f_g11f_b10f,
r32f,
r16f,
rgba16,
rgb10_a2,
rgba8,
rg16,
rg8,
r16,
r8,
rgba16_snorm,
rgba8_snorm,
rg16_snorm,
rg8_snorm,
r16_snorm,
r8_snorm,     // Signed integer layout image formats:
rgba32i,
rgba16i,
rgba8i,
rg32i,
rg16i,
rg8i,
r32i,
r16i,
r8i,       // Unsigned integer layout image formats:
rgba32ui,
rgba16ui,
rgb10_a2ui,
rgba8ui,
rg32ui,
rg16ui,
rg8ui,
r32ui,
r16ui,
r8ui,


rgb32f,
rgb16f,
rgb16,
rgb8,
rgb16_snorm,
rgb8_snorm,
rgb32i,
rgb16i,
rgb8i,
rgb32ui,
rgb16ui,
rgb8ui,




argb32f,
argb16f,
argb16,
a2_rgb10,
argb8,
argb16_snorm,
argb8_snorm,
ar8_snorm,     // Signed integer lyout image foarmts:
argb32i,
argb16i,
argb8i,
argb32ui,
argb16ui,
a2_rgb10ui,
argb8ui,

};


#define IMAGE_FORMATS rgba32f,rgba16f,rg32f,rg16f,r11f_g11f_b10f,r32f,r16f,rgba16,rgb10_a2,rgba8,rg16,rg8,r16,r8,rgba16_snorm,rgba8_snorm,rg16_snorm,rg8_snorm,r16_snorm,r8_snorm,rgba32i,rgba16i,rgba8i,rg32i,rg16i,rg8i,r32i,r16i,r8i,rgba32ui,rgba16ui,rgb10_a2ui,rgba8ui,rg32ui,rg16ui,rg8ui,r32ui,r16ui,r8ui,

    constexpr int8_t bitdepth(image_format imf,size_t s){
        switch(imf){
    case rgb10_a2ui:{return 10;}
    case a2_rgb10ui:{return 10;}
    case rgb10_a2:{return 10;}
    case a2_rgb10:{return 10;}

    case rgba32f: {return 32 ;}
    case argb32f:{return 32;}
    case rgba16f: {return 16 ;}
    case argb16f: {return 16 ;}
    if constexpr (s<3 ){
        case rg32f: {return 32 ;}
        case rg16f: {return 16 ;}}
    if constexpr (s<4){
        case r11f_g11f_b10f: {return 11 ;}
    }
    if constexpr (s==1){
        case r32f: {return 32 ;}
        case r16f: {return 16 ;}
    }
    case rgba16: {return 16 ;}
    case argb16: {return 16 ;}
    if constexpr (s==4){
        case rgb10_a2: {return 2 ;}
    }
    else {case rgb10_a2: {return 10 ;}}
    case rgba8: {return 8 ;}
    if constexpr (s<3){
        case rg16: {return 16 ;}
    }
        if constexpr (s<2){
    case rg8: {return 8 ;}}
        if constexpr (s==1){
    case r16: {return 16 ;}
    case r8: {return  8 ;}}
    case rgba16_snorm: {return 16 ;}
    case rgba8_snorm: {return 8 ;}
    case argb16_snorm: {return 16 ;}
    case argb8_snorm: {return 8 ;}
        if constexpr (s<3){
    case rg16_snorm: {return 16 ;}
    case rg8_snorm: {return 8 ;}}
        if constexpr (s==1){
    case r16_snorm: {return 16 ;}
    case r8_snorm: {return 8 ;}}
    case rgba32i: {return 32 ;}
    case rgba16i: {return 16 ;}
    case rgba8i: {return 8 ;}
    case argb32i: {return 32 ;}
    case argb16i: {return 16 ;}
    case argb8i: {return 8 ;}
        if constexpr (s<3){
    case rg32i: {return 32 ;}
    case rg16i: {return 16 ;}
    case rg8i: {return 8 ;}}
        if constexpr (s==1){
    case r32i: {return 32 ;}
    case r16i: {return 16 ;}
    case r8i: {return 8 ;}}
    case rgba32ui: {return 32 ;}
    case rgba16ui: {return 16 ;}
    case argb32ui: {return 32 ;}
    case argb16ui: {return 16 ;}
    
    if constexpr (s==4){case rgb10_a2ui: {return 10 ;}            }
        else {case rgb10_a2ui: {return 10 ;}}
    case rgba8ui: {return 8 ;}
    case argb8ui: {return 8 ;}
        if constexpr (s<3){    
    case rg32ui: {return 32 ;}
    case rg16ui: {return 16 ;}
    case rg8ui: {return 8 ;}}
            if constexpr (s==1){
    case r32ui: {return 32 ;}
    case r16ui: {return 16 ;}
    case r8ui: {return 8 ;}}    
    if constexpr(s<4){
        case rgb32f:{return 32; }     
        case rgb16f:{return 16; }     
        case rgb16:{return 16; }      
        case rgb8:{return 8; }       
        case rgb16_snorm:{return 16; }
        case rgb8_snorm:{return 8; } 
        case rgb32i:{return 32; }     
        case rgb16i:{return 16; }     
        case rgb8i:{return 8; }      
        case rgb32ui:{return 32; }    
        case rgb16ui:{return 16; }    
        case rgb8ui:{return 8; }     
    }

return 0;
    }};
    constexpr int8_t bitdepth_r(image_format imf){return bitdepth(imf,0);};
    constexpr int8_t bitdepth_g(image_format imf){return bitdepth(imf,1);};
    constexpr int8_t bitdepth_b(image_format imf){return bitdepth(imf,2);};
    constexpr int8_t bitdepth_a(image_format imf){
            switch(imf){
    case rgb10_a2ui:{return 2;}
    case a2_rgb10ui:{return 2;}
    case rgb10_a2:{return 2;}
    case a2_rgb10:{return 2;}
    }
        return bitdepth(imf,3);};

    constexpr bool RGBA(image_format imf){
        switch(imf){
            case rgb10_a2{return true;}
            case rgb10_a2ui{return true;}
            case rgba8:{return true;}
            case rgba8:{return true;}
            case rgba8ui:{return true;}
            case rgba8ui:{return true;}
            case rgba8_snorm:{return true;}
            case rgba8_snorm:{return true;}
            case rgba16:{return true;}
            case rgba16:{return true;}
            case rgba16ui:{return true;}
            case rgba16ui:{return true;}
            case rgba16_snorm:{return true;}
            case rgba16_snorm:{return true;}
            case rgba32:{return true;}
            case rgba32:{return true;}
            case rgba32ui:{return true;}
            case rgba32ui:{return true;}
            case rgba32_snorm:{return true;}
            case rgba32_snorm:{return true;}
        }
        return false;
    }
    constexpr bool ARGB(image_format imf){
                switch(imf){
            case a2_rgb10{return true;}
            case a2_rgb10ui{return true;}
            case argb8:{return true;}
            case argb8:{return true;}
            case argb8ui:{return true;}
            case argb8ui:{return true;}
            case argb8_snorm:{return true;}
            case argb8_snorm:{return true;}
            case argb16:{return true;}
            case argb16:{return true;}
            case argb16ui:{return true;}
            case argb16ui:{return true;}
            case argb16_snorm:{return true;}
            case argb16_snorm:{return true;}
            case argb32:{return true;}
            case argb32:{return true;}
            case argb32ui:{return true;}
            case argb32ui:{return true;}
            case argb32_snorm:{return true;}
            case argb32_snorm:{return true;}
        }
        return false;

    }

constexpr int8_t bitd(image_formats imf){return bitdepth_r(imf)+bitdepth_g(imf)+bitdepth_b(imf)+bitdepth_a(imf);}


constexpr int8_t imageFormatBytes(image_formats imf){bitdepth(imf)/8;}

typedef short f16 ; 

template<image_formats imf>
struct enu_vec{
     using ty = glm::ivec4 };
template <>struct enu_vec<image_formats::rgba32f>        { using ty =glm::f32vec4;};
template <>struct enu_vec<image_formats::rgba16f>        { using ty =glm::f16vec4;};
template <>struct enu_vec<image_formats::rg32f>          { using ty =glm::f32vec2;};
template <>struct enu_vec<image_formats::rg16f>          { using ty =glm::f16vec2;};
template <>struct enu_vec<image_formats::r11f_g11f_b10f> { using ty =glm::f16vec3;};
template <>struct enu_vec<image_formats::r32f>           { using ty =glm::f32;};
template <>struct enu_vec<image_formats::r16f>           { using ty =f16;};
template <>struct enu_vec<image_formats::rgba16>         { using ty =glm::i16vec4;};
template <>struct enu_vec<image_formats::rgb10_a2>       { using ty =glm::i16vec4;};
template <>struct enu_vec<image_formats::rgba8>          { using ty =glm::i8vec4;};
template <>struct enu_vec<image_formats::rg16>           { using ty =glm::i16vec2;};
template <>struct enu_vec<image_formats::rg8>            { using ty =glm::i8vec2;};
template <>struct enu_vec<image_formats::r16>            { using ty =f16 ;};
template <>struct enu_vec<image_formats::r8>             { using ty =uint8_t ;};
template <>struct enu_vec<image_formats::rgba16_snorm>   { using ty =glm::i16vec4;};
template <>struct enu_vec<image_formats::rgba8_snorm>    { using ty =glm::i8vec4 ;};
template <>struct enu_vec<image_formats::rg16_snorm>     { using ty =glm::i16vec2;};
template <>struct enu_vec<image_formats::rg8_snorm>      { using ty =glm::i8vec2 ;};
template <>struct enu_vec<image_formats::r16_snorm>      { using ty =glm::i16;};
template <>struct enu_vec<image_formats::r8_snorm>       { using ty =glm::i8 ;};
template <>struct enu_vec<image_formats::rgba32i>        { using ty =glm::i32vec4;};
template <>struct enu_vec<image_formats::rgba16i>        { using ty =glm::i16vec4 ;};
template <>struct enu_vec<image_formats::rgba8i>         { using ty =glm::i8vec4;};
template <>struct enu_vec<image_formats::rg32i>          { using ty =glm::f32vec2;};
template <>struct enu_vec<image_formats::rg16i>          { using ty =glm::i16vec2 ;};
template <>struct enu_vec<image_formats::rg8i>           { using ty =glm::i8vec2 ;};
template <>struct enu_vec<image_formats::r32i>           { using ty =glm::i32 ;};
template <>struct enu_vec<image_formats::r16i>           { using ty =glm::i16;};
template <>struct enu_vec<image_formats::r8i>            { using ty =glm::i8 ;};
template <>struct enu_vec<image_formats::rgba32ui>       { using ty =glm::u32vec4 ;};
template <>struct enu_vec<image_formats::rgba16ui>       { using ty =glm::u16vec4 ;};
template <>struct enu_vec<image_formats::rgb10_a2ui>     { using ty =glm::u16vec4 ;};
template <>struct enu_vec<image_formats::rgba8ui>        { using ty =glm::u8vec4 ;};
template <>struct enu_vec<image_formats::rg32ui>         { using ty =glm::u32vec2 ;};
template <>struct enu_vec<image_formats::rg16ui>         { using ty =glm::u16vec2 ;};
template <>struct enu_vec<image_formats::rg8ui>          { using ty =glm::u8vec2 ;};
template <>struct enu_vec<image_formats::r32ui>          { using ty =uint32_t ;};
template <>struct enu_vec<image_formats::r16ui>          { using ty =uint16_t ;};
template <>struct enu_vec<image_formats::r8ui>           { using ty =uint8_t ;};

template <>struct enu_vec<image_formats::rgb32f>           { using ty =glm::f32vec3 ;};
template <>struct enu_vec<image_formats::rgb16f>           { using ty =glm::f16vec3 ;};
template <>struct enu_vec<image_formats::rgb16>           { using ty =glm::i16vec3 ;};
template <>struct enu_vec<image_formats::rgb8>           { using ty =glm::i8vec3 ;};
template <>struct enu_vec<image_formats::rgb16_snorm>           { using ty =glm::i16vec3 ;};
template <>struct enu_vec<image_formats::rgb8_snorm>           { using ty =glm::i8vec3 ;};
template <>struct enu_vec<image_formats::rgb32i>           { using ty =glm::i32vec3 ;};
template <>struct enu_vec<image_formats::rgb16i>           { using ty =glm::i16vec3 ;};
template <>struct enu_vec<image_formats::rgb8i>           { using ty =glm::i8vec3 ;};
template <>struct enu_vec<image_formats::rgb32ui>           { using ty =glm::ui32vec3 ;};
template <>struct enu_vec<image_formats::rgb16ui>           { using ty =glm::ui16vec3 ;};
template <>struct enu_vec<image_formats::rgb8ui>           { using ty =glm::ui8vec3 ;};



template<image_formats imf>
struct enu_unit{
     using ty = glm::ivec4 };
template <>struct enu_unit<image_formats::rgba32f>        { using ty =glm::f32;};
template <>struct enu_unit<image_formats::rgba16f>        { using ty =f16;};
template <>struct enu_unit<image_formats::rg32f>          { using ty =glm::f32;};
template <>struct enu_unit<image_formats::rg16f>          { using ty =f16;};
template <>struct enu_unit<image_formats::r11f_g11f_b10f> { using ty =f16;};
template <>struct enu_unit<image_formats::r32f>           { using ty =glm::f32;};
template <>struct enu_unit<image_formats::r16f>           { using ty =f16;};
template <>struct enu_unit<image_formats::rgba16>         { using ty =glm::i16;};
template <>struct enu_unit<image_formats::rgb10_a2>       { using ty =glm::i16;};
template <>struct enu_unit<image_formats::rgba8>          { using ty =glm::i8;};
template <>struct enu_unit<image_formats::rg16>           { using ty =glm::i16;};
template <>struct enu_unit<image_formats::rg8>            { using ty =glm::i8;};
template <>struct enu_unit<image_formats::r16>            { using ty =glm::i16 ;};
template <>struct enu_unit<image_formats::r8>             { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rgba16_snorm>   { using ty =glm::i16;};
template <>struct enu_unit<image_formats::rgba8_snorm>    { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rg16_snorm>     { using ty =glm::i16;};
template <>struct enu_unit<image_formats::rg8_snorm>      { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::r16_snorm>      { using ty =glm::i16;};
template <>struct enu_unit<image_formats::r8_snorm>       { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rgba32i>        { using ty =glm::i32;};
template <>struct enu_unit<image_formats::rgba16i>        { using ty =glm::i16 ;};
template <>struct enu_unit<image_formats::rgba8i>         { using ty =glm::i8;};
template <>struct enu_unit<image_formats::rg32i>          { using ty =glm::f32;};
template <>struct enu_unit<image_formats::rg16i>          { using ty =glm::i16 ;};
template <>struct enu_unit<image_formats::rg8i>           { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::r32i>           { using ty =glm::i32 ;};
template <>struct enu_unit<image_formats::r16i>           { using ty =glm::i16;};
template <>struct enu_unit<image_formats::r8i>            { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rgba32ui>       { using ty =glm::u32 ;};
template <>struct enu_unit<image_formats::rgba16ui>       { using ty =glm::u16 ;};
template <>struct enu_unit<image_formats::rgb10_a2ui>     { using ty =glm::u16 ;};
template <>struct enu_unit<image_formats::rgba8ui>        { using ty =glm::u8 ;};
template <>struct enu_unit<image_formats::rg32ui>         { using ty =glm::u32 ;};
template <>struct enu_unit<image_formats::rg16ui>         { using ty =glm::u16 ;};
template <>struct enu_unit<image_formats::rg8ui>          { using ty =glm::u8 ;};
template <>struct enu_unit<image_formats::r32ui>          { using ty =glm::uint32_t ;};
template <>struct enu_unit<image_formats::r16ui>          { using ty =glm::uint16_t ;};
template <>struct enu_unit<image_formats::r8ui>           { using ty =glm::uint8_t ;};

template <>struct enu_unit<image_formats::rgb32f>          { using ty =glm::f32 ;};
template <>struct enu_unit<image_formats::rgb16f>          { using ty =glm::f16 ;};
template <>struct enu_unit<image_formats::rgb16>           { using ty =glm::i16 ;};
template <>struct enu_unit<image_formats::rgb8>            { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rgb16_snorm>     { using ty =glm::i16 ;};
template <>struct enu_unit<image_formats::rgb8_snorm>      { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rgb32i>          { using ty =glm::i32 ;};
template <>struct enu_unit<image_formats::rgb16i>          { using ty =glm::i16 ;};
template <>struct enu_unit<image_formats::rgb8i>           { using ty =glm::i8 ;};
template <>struct enu_unit<image_formats::rgb32ui>         { using ty =glm::uint32_t ;};
template <>struct enu_unit<image_formats::rgb16ui>         { using ty =glm::uint16_t ;};
template <>struct enu_unit<image_formats::rgb8ui>          { using ty =glm::uint8_t ;};

glm::lowp_ivec4 uint32ToRGBA(uint32_t color) {
    glm::ivec4 s;
    s.r = (color >> 24) & 0xFF; // Extract Red channel (highest byte)
    s.g = (color >> 16) & 0xFF; // Extract Green channel
    s.b = (color >> 8)  & 0xFF; // Extract Blue channel
    s.a = (color)       & 0xFF; // Extract Alpha channel (lowest byte)
    return s;
};
glm::lowp_ivec4 uint16torgba(uint16_t color) {
    glm::ivec4 s;
    s.r = (color >> 12) & 0xF; // Extract Red channel (highest byte)
    s.g = (color >> 8 )  & 0xF; // Extract Green channel
    s.b = (color >> 4)  & 0xF; // Extract Blue channel
    s.a = (color)       & 0xF; // Extract Alpha channel (lowest byte)
    return s;
};

int32_t f32_to_i32(f32_t s){
    int_32_t r =  s*
};  




enum texture_format {
TEXTURE_1D                  = 0  ,  // Images in this texture all are 1-dimensional. They have width, but no height or depth.
TEXTURE_2D                  = 1  ,  // Images in this texture all are 2-dimensional. They have width and height, but no depth.
TEXTURE_3D                  = 2  ,  // Images in this texture all are 3-dimensional. They have width, height, and depth.
TEXTURE_RECTANGLE           = 3  ,  // The image in this texture (only one image. No mipmapping) is 2-dimensional. Texture coordinates used for these textures are not normalized.
TEXTURE_BUFFER              = 4  ,  // The image in this texture (only one image. No mipmapping) is 1-dimensional. The storage for this data comes from a Buffer Object.
TEXTURE_CUBE_MAP            = 5  ,  // There are exactly 6 distinct sets of 2D images, each image being of the same size and must be of a square size. These images act as 6 faces of a cube.
TEXTURE_1D_ARRAY            = 6  ,  // Images in this texture all are 1-dimensional. However, it contains multiple sets of 1-dimensional images, all within one texture. The array length is part of the texture's size.
TEXTURE_2D_ARRAY            = 7  ,  // Images in this texture all are 2-dimensional. However, it contains multiple sets of 2-dimensional images, all within one texture. The array length is part of the texture's size.
TEXTURE_CUBE_MAP_ARRAY      = 8  ,  // Images in this texture are all cube maps. It contains multiple sets of cube maps, all within one texture. The array length * 6 (number of cube faces) is part of the texture size.
TEXTURE_2D_MULTISAMPLE      = 9  ,  // The image in this texture (only one image. No mipmapping) is 2-dimensional. Each pixel in these images contains multiple samples instead of just one value.
TEXTURE_2D_MULTISAMPLE_ARRAY= 10 ,  // Combines 2D array  and 2D multisample types. No mipmapping.
};

size_t im_size[]= {8 ,16 ,32 ,164 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768};

struct image1D {
    // std::string name;
    uint32_t x;
    uint32_t y;
    uint32_t width; 
    uint32_t imageSize=0;
    image_format imageFormat;
    void* data;
    uint8_t byd ;
    uint8_t bdc;
    int8_t bd ;
    uint8_t length;
    uint8_t bitdim(uint8_t pos){
        switch(pos){
            case 0 :{return bitdepth_r(imageFormat);}
            case 1 :{return bitdepth_g(imageFormat);}
            case 2 :{return bitdepth_b(imageFormat);}
            case 3 :{return bitdepth_a(imageFormat);}
        }
    };
    template <image_formats fm>
    void putAt(uint64_t pt,enu_vec<fm>::ty v){
        if(fm==imageFormat){
            std::memcpy(  data+pt*byd, &v,byd) ;
            return ;
        }
mask = 1<<bdc -1;
maskd=1<<(sizeof(enu_vec<fm>::ty)/length())-1;      
for(int i=0;i<length;i++){ 
    uint8_t bdc=bitdim(i);              
    uint32_t mask = 1<<bdc -1;          
    data[byd*pt + i*bdc/8 ] += v[i] & mask 
}
    };
    template <image_formats fm>
    enu_vec<fm>::ty getAt(uint64_t pt){
        enu_vec<fm>::ty v;
        if(fm==imageFormat){
            &v = data+pt*byd;
            return v;
        }
        
            mask = 1<<bdc -1;
            uint32_t maskd=1<<(sizeof(enu_vec<fm>::ty)/length())-1;
            if(length>1){
                for(int i=0;i<length;i++){ 
                    v[i]= (data+byd*pt) & (mask<<((l -i -1)*bdc) );
                    v[i]*= (maskd/mask);
                }
            } 
            else {v = data[byd*pt] & (mask<<((l-1)*bdc));v*= (maskd/mask); };
            return v;
        }
      
    };
    image2D loadChannel(uint8_t s){
        int8_t bypd= bdc/8;
        image2D i;
        i.data = new char[imageSize * bdc]
        for(uint32_t i;i<imageSize;i++){
            std::memcpy(i.data+i*bypd,data+i*byd+s*bypd,bypd);
        }; 
        return i; 
    };
    void operator<<(uint8_t s){
        
        int8_t bypd= bdc/8;
        
        int8_t nc =bool(bitdepth_r(imageFormat))+bool(bitdepth_g(imageFormat))+bool(bitdepth_b(imageFormat))+bool(bitdepth_a(imageFormat));
         for(uint32_t i=0;i<imageSize;i++){
            void* temp ;
            void* t2
            std::memcpy(temp,data+i*bd,bdc);
            std::memcpy(data+i*bd,data+i*bd+bdc,(nc-1)*bdc);
            std::memcpy(data+i*bd+bdc*(nc-1),temp,bdc);
        }
    };
    void operator>>(uint8_t s){
        
        int8_t bypd= bdc/8;
        int8_t nc =bool(bitdepth_r(imageFormat))+bool(bitdepth_g(imageFormat))+bool(bitdepth_b(imageFormat))+bool(bitdepth_a(imageFormat));
         for(uint32_t i=0;i<imageSize;i++){
            void* temp ;
            void* t2
            std::memcpy(temp,data+i*byd + bdc*(nc-1),bypd);
            std::memcpy(data+i*byd+bypd,data+i*bd,(nc-1)*bypd);
            std::memcpy(data+i*byd,temp,bypd);
        }  
    };
    void swap(uint pos1,uint pos2 ){        
        
        int8_t bypd= bdc/8;


        for(uint32_t i=0;i<imageSize;i++){
            void* temp ;
            std::memcpy(temp,data+i*byd+ pos1*bypd,bypd);
            std::memcpy(data+i*byd+pos1*bypd,data+i*byd+ pos2*bypd,bypd);
            std::memcpy(data+i*byd+pos2*bypd,temp,bypd);
        }
    }
    void swaprb(){
        if constexpr (bitedepths<imageFormat>::RGBA()){
            swap(0,2);}
        if constexpr (bitedepths<imageFormat>::ARGB()){
            swap(1,3);}
        }
    void swaprg(){
if constexpr (bitedepths<imageFormat>::RGBA()){
            swap(0,1);}
        if constexpr (bitedepths<imageFormat>::ARGB()){
            swap(1,2);}

    };
    
    template<image_format fm>
    decltype(*this) to(){
        decltype(*this) im(width,height,fm);
        im.imageFormat=fm;
        int8_t bdCur=bd;
        int8_t bdDest=bitd(fm);
        for(int i=0;i<imageSize){
            int8_t bitsOffsetCur=0;
            enu_vec<fm>::ty cr = getAt<enu_vec<fm>::ty>(i);
            for(int j =0;j< length ;j++){
                uint8_t bitCur = bitdIm(i);
                uint8_t bitDest = im.bitdIm(i);
                
                uint32_t maskCur = 1<<bitCur-1;
                uint32_t maskDest = 1<<bitDest-1; 
                re[j] = (float)(cr[j] * (maskDest/maskCur));
            }
            im.putAt(i,re);
        };
        return i;
    };
    bool blend(uint32_t w, uint32_t h , void* d,uint32_t x,uint32_t y){//TODO
        if(w+x>( width-1) or (h+y)>(height-1) ){return false;}
        for(uint32_t i;i<h;i++){
        std::memcpy(data+((y+i)*width+x)*byd , d + i*w*byd, w*byd);
        }
    };  
    bool blit(uint32_t w, uint32_t h , void* d,uint32_t x,uint32_t y){
         if(w+x>( width-1) or (h+y)>(height-1) ){return false;}
        for(uint32_t i;i<h;i++){
        std::memcpy(data+((y+i)*width+x)*byd , d + i*w*byd, w*byd);
        }
        return true;
    };  

    void ImageSize(){imageSize=width;bd=bitd(imageFormat);bdc = bitdepth_r(imageFormat);byd = bitd(imageFormat)/8 ;length=enu_vec<imageFormat>::ty::length();}
    void init(){ImageSize();data= new uint8_t[(byd * imageSize];}
    
    image1D(size_t s,image_format fm) : width(s),height(s),imageFormat(fm){init();};
};
struct image2D : image1D {
    uint32_t height;
    void blend(uint32_t w, uint32_t h , void* d,uint32_t x,uint32_t y){
        for(uint32_t i;i<h;i++){
        std::memcpy(data+((y+i)*width+x)*byd , d + i*w*byd, w*byd);
        }
    };  
    void blit(uint32_t w, uint32_t h , void* d,uint32_t x,uint32_t y){
        for(uint32_t i;i<h;i++){
        std::memcpy(data+((y+i)*width+x)*byd , d + i*w*byd, w*byd);
        }
    };  
        void ImageSize(){imageSize=width*height;bd=bitd(imageFormat);bdc = bitdepth_r(imageFormat);byd = bitd(imageFormat)/8 ;length=enu_vec<imageFormat>::ty::length();}
    image2d(uint32_t size,image_format fm) : width(w),height(h),imageFormat(fm) {Init();};
    image2D(uint32_t w,uint32_t h,image_format fm) : width(w),height(h),imageFormat(fm){Init();};

};
struct aimage2D : std::vector<image2D>{ 
    uint32_t swidth;
    uint32_t sheight;
}
struct image3D : image1D {
    uint32_t size_t height ;
    uint32_t size_t depth ;
    image3D(uint32_t w,uint32_t h,uint32_t d,image_format fm) : width(w),height(h),depth(d),imageFormat(fm){Init();};
};

image2D im8(image_format imf){return image2d(8,imf);}
image2D im16(image_format imf){return image2d(16,imf);}
image2D im32(image_format imf){return image2d(32,imf);}
image2D im164(image_format imf){return image2d(164,imf);}
image2D im128(image_format imf){return image2d(128,imf);}
image2D im256(image_format imf){return image2d(256,imf);}
image2D im512(image_format imf){return image2d(512,imf);}
image2D im1024(image_format imf){return image2d(1024,imf);}
image2D im2048(image_format imf){return image2d(2048,imf);}
image2D im4096(image_format imf){return image2d(4096,imf);}
image2D im8192(image_format imf){return image2d(8192,imf);}
image2D im16384(image_format imf){return image2d(16384,imf);}
image2D im32768(image_format imf){return image2d(32768,imf);}


typedef uint32_t Time ; // hh:mm:ss:ms // One Bytes Each


 
struct image2D_dyn : image2D {
    uint32_t imageCount;
    uint16_t hz;
    void ImageSize(){imageSize=width*height*imageCount;};
    uint32_t getPt(Time t){ // Convert to pt
        uint32_t ms = T & (1<<8 -1);
        uint32_t s = T & ((1<<8 -1)<<8) >>8 ;
        uint32_t m = T & ((1<<8 -1)<<16) >>16 ;
        uint32_t h = T & ((1<<8 -1)<<24) >>24 ;
        uint32_t pt = h*hz*3600+m*hz*60+ s*hz + ms*hz/1000;
        return pt;
    };
    void insertPt(image2d_dyn im ,uint32_t pt){
        uint8_t byd= bitd(imageFormat)/8;
        void* d  = new char[byd * width*height * (imageCount + im.imageCount) ];

        std::memcpy(d,data,byd * width*height * pt );
        std::memcpy(d+byd * width*height * pt,im.data, im.imageSize);
        std::memcpy(d+byd*width*height*(pt+im.imageCount),data+byd*width*height*pt,byd*width*height*(imageCount-pt));
        imageCount+=im.imageCount;
    };
    void insertTime(image2d_dyn im , Time t){
        insertPt(im,getPt(t));
    };
};



/*
Shader Type	Abbreviation	Purpose
Vertex Shader	VS	Transforms vertices, applies MVP matrices
Tessellation Control Shader	TCS	Determines tessellation level
Tessellation Evaluation Shader	TES	Computes final vertex positions
Geometry Shader	GS	Modifies or generates geometry
Fragment Shader	FS	Determines final pixel color
Compute Shader	CS	General-purpose GPU processing
Ray Generation Shader	rgen	Launches rays in ray tracing
Any-Hit Shader	rahit	Processes potential ray hits
Closest-Hit Shader	rchit	Determines shading for confirmed ray hits
Miss Shader	rmiss	Handles cases where rays miss all objects
Intersection Shader	rint	Custom intersection logic for complex shapes
Amplification Shader	AS	Controls LOD and culling in new pipelines
Mesh Shader	MS	Replaces Vertex + Geometry shaders for efficiency
*/

enum transform_image {
    none,
    rotate90,
    rotate180,
    roate270,
    mirror,
    mirror_rotate90,
    mirror_rotate180,
    mirror_roate270
};

enum sample_count {
    sample_1 = 0x00000001,
    sample_2 = 0x00000002,
    sample_4 = 0x00000004,
    sample_8 = 0x00000008,
    sample_16 = 0x00000010,
    sample_32 = 0x00000020,
    sample_64 = 0x00000040,
};
enum image_usage {
TRANSFER_SRC_BIT = 0x00000001,
TRANSFER_DST_BIT = 0x00000002,
SAMPLED_BIT = 0x00000004,
STORAGE_BIT = 0x00000008,
COLOR_ATTACHMENT_BIT = 0x00000010,
DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
TRANSIENT_ATTACHMENT_BIT = 0x00000040,
INPUT_ATTACHMENT_BIT = 0x00000080,
VIDEO_DECODE_DST_BIT_KHR = 0x00000400,
VIDEO_DECODE_SRC_BIT_KHR = 0x00000800,
VIDEO_DECODE_DPB_BIT_KHR = 0x00001000,
FRAGMENT_DENSITY_MAP_BIT_EXT = 0x00000200,
FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x00000100,
ATTACHMENT_FEEDBACK_LOOP_BIT_EXT = 0x00080000,
INVOCATION_MASK_BIT_HUAWEI = 0x00040000,
SAMPLE_WEIGHT_BIT_QCOM = 0x00100000,
SAMPLE_BLOCK_MATCH_BIT_QCOM = 0x00200000,
SHADING_RATE_IMAGE_BIT_NV = VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
};
struct image {
    bool storage = true;
    bool sharing =false;
    image_usage usage = image_usage::TRANSFER_DST_BIT | image_usage::STORAGE_BIT ;
    image_dim dim;
    uint32_t w,h,depth;
    int miplevels;
    int arrlayers =1;
    sample_count sample =  sample_count::sample_1;
    image() = default { this->storage}
};


namespace quality
{
    
    enum QUALITY
    {
        UltraLow = 0 ,
        VeryLow = 1 ,      
        Low = 2,
        MediumLow = 3,
        MediumHigh = 4,
        High = 5,
        VeryHigh = 6
        Ultra = 7,
        // Hyper, // Like super but adds even more realism through live homeostatic simulation
        // Super, // realistic shading model and material system taking into account a variety of factors. Thermal coloring. Bio-matter Tissue lighting
    };
  
    
    class quality_setting {

        std::string name ;
        QUALITY  value ;
        QUALITY limit ;
        QUALITY wlimit; // Warning Limit
        quality_setting(std::string name, QUALITY  value ,
        QUALITY limit ,
        QUALITY warnlimit ) : name(name), value(value) , limit(limit) , limit(warnlimit) {};
    };
    typedef std::pair<std::string, std::array<std::array<glm::vec4>> > quality_category; 
    class quality_def {
        std::vector<std::pair<QualityCategory  std::vector<Qset> > > contents;
    };
    class quality {
        QUALITY qnum  ;
        bool vSync ;
        typedef enum ANTI_ALIASING {
            off = 0 ,
            bilinear, 
            trilinear,
            AnisotropicFiltering,
        }ANTI_ALIASING;
        virtual ANTI_ALIASING anti_aliasing; 
      

        // This should be a maximum value and the behaviour should adapt to the model detail.
    //    typedef enum TESSELATION_QUALITY {
    //         OFF,
    //         

    //     }TESSELATION_QUALITY;
           
        typedef enum tesselation_mode {
            off =  0,
            REG
            PN, // Point normal
        } tesselation_mode;
        tesselation_mode tesselation ; 
         

        enum RENDER_MODE 
            ray_tracing,
            path_tracing,
            ray_casting,
            photon_mapping
        };    
};
   


/// @brief 
namespace texture {
    
    
     struct texture  { // TODO
        image2D image;
        
        texture(textureInfo _info, image::rgba_static_arr _image) : info(_info) , image(_image) {};
    } ;
    
    struct dyn_texture : texture {
        textureInfo info ;

    };
    
    struct diffuse : texture {
        textureInfo info = textureInfo(NULL , NULL , "diffuse", pipeline::stage.DS)
    } ;
    
    
    struct tangent : texture {
        textureInfo info = textureInfo(NULL , NULL , "tangent")   ; 
    };
    
    struct height : texture  {
        textureInfo info = textureInfo(NULL , NULL , "height")   ; 
        float scale ;
    };
    
    struct normal : texture {
        textureInfo info = textureInfo(NULL , NULL , "normal" ); 
    };
    
    struct normal_dx : texture {
        textureInfo info = textureInfo(NULL , NULL , "normal-dx" ); 
    };
    
    struct tangent : texture { // Maps normal space to tangent space ( tangent space is the direction the surface is facing centered coordinates)
        textureInfo info = textureInfo(NULL , NULL , "tangent" ); 
    };
    
    struct albedo : texture  { // Proportion of light reflected
        textureInfo info = textureInfo(NULL , NULL , "albedo");  
    };
    
    struct ambient_occlusion : texture  { // Ambient occlusion
        textureInfo info = textureInfo(NULL , NULL , "ao"); 
    };
    
    struct metallic : texture  {
        textureInfo info = textureInfo(NULL , NULL , "metallic");  
    };
    
    struct roughness : texture  {
        textureInfo info = textureInfo(NULL , NULL , "roughness"); 
    };
    
    struct opacity : texture {
        textureInfo info = textureInfo(NULL , NULL , "opacity"); 
    };
    
    
    struct bump : texture {
        textureInfo info = textureInfo(NULL , NULL , "bump");
    };
    
    struct specular : texture {
        textureInfo info = textureInfo(NULL , NULL , "specular"); // Pixel Shader
    };
    
    struct glow : texture {
        textureInfo info = textureInfo(NULL , NULL , "glow"); // Pixel Shader
    };
    
    struct reflection_map : texture { // Can be taken from a reflection element in the case of static elements
        textureInfo info = textureInfo(NULL , NULL , "reflection");
    };

    
    struct reflection_elem : elem , texture {

    };
    
    struct heat : texture  { 
        textureInfo info = textureInfo(NULL , NULL , "heat",  pipeline::stage.PS);
    };
    
    

    // Used when sharing the texture

    struct preview :  texture {
        textureInfo info = textureInfo(NULL , NULL , "preview", NULL)  ; 
    };

};

//  VkPrimitiveTopology {
//     VK_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
//     VK_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
//     VK_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
//     VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
//     VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
//     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
//     VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
// } VkPrimitiveTopology;

using point_list = std::vector<uint>; 
using line_list = std::vector<uint>; 
using line_strip = std::vector<uint>;
using triangle_list = std::vector<uint>; 
using triangle_strip = std::vector<uint>; 
using triangle_fan = std::vector<uint>; 

using line_list_with_adjacency = std::vector<uint>; 
using line_strip_with_adjacency = std::vector<uint>;
using triangle_list_with_adjacency = std::vector<uint>;  
using triangle_strip_with_adjacency = std::vector<uint>; 
using patch_list = std::vector<uint>  ;


enum DIM {
    Bi=2, 
    Tri=3,
}DIM;
template <DIM t>
using dim_pos = typename <std::conditional<t == DIM.Bi , glm::vec2 , 
                typename std::conditional<t == DIM.Tri , glm::vec3 , void>::type>::type

template <quality::QUALITY q>
struct material_physical_properties    {

    float mass ;
    bool collision_enabled = true ;
    unsigned float collision_dampening ; 
    float friction;
    material_physical_properties( bool _collision_enabled , unsigned float _collision_dampening ,float _friction  ): collision_enabled(_collision_enabled),collision_dampening(_collision_dampening) ,friction(_friction) {};
        material_physical_properties() ;
};


// elems are objects which can be put into to the scene w 
// Images can be rendered 

// This material rendering scheme can be applied to a mesh
struct Tmap {
    image2D image ;
    struct tmapOps{
    bool blendu=true;bool blendv=true;
    float boost;
    float mm_base=0 ; float mm_gain=1;
    glm::vec3 o = glm::vec3(0,0,0);  // Origin offset
    glm::vec3 s = glm::vec3(1,1,1);  // Scale
    glm::vec3 t = glm::vec3(0,0,0);
    uint32_t texres;
    bool clamp =false;
    float bm =1;
    char imfchan ;
    enum TYPE{
        sphere ,cube_top,  cube_bottom,  cube_front,  cube_back,    cube_left,  cube_right 
    }
    TYPE type;
    };
tmapOps ops;
};
template <quality::QUALITY Q>
struct material   {
    public:
    std::enable_if<Q>3, image2D>::type map_disp;
    std::enable_if<Q>4, image2D>::type map_bump;
    std::enable_if<Q>2, image2D>::type map_matte;// matte channe
    std::enable_if<Q>2, image2D>::type map_refl;
    std::enable_if<Q>2, image2D>::type map_ambient;
    std::enable_if<Q>2, image2D>::type map_diffuse;
    std::enable_if<Q>2, image2D>::type map_specular;



    std::enable_if<Q>4,image2D>::type normal ;
    std::enable_if<Q>4,image2D>::type tangent   ;  
    image2D opacity_mask;
    glm::vec3 base_Color ;
    image2D baseColorMap;
    image2D subSurfaceColor;
    glm::vec3 subsurface_Color ;
    std::enable_if<Q>2 ,glm::vec3>::type emmisive_Color ;
    // float anisotropy ; // Normalised between -1 and 1  with 0 meaning none
    std::enable_if<Q>2,float>::type refraction ;
    float metallicity ;
    float roughness ;
    float specularity ;
    float opacity ;
    float position_offset ;
    float position_displacement ;    
    bool clear_Coat ;
    bool ambient_occlusion ;
    
    
    void Tangent(){
        using ty = enuvec<map_disp.imageFormat>::ty;
        tangent.imageFormat = image_formats::rgb32f;
        tangent.imageSize = map_disp.imageSize;
         for(uint32_t i=0;i<map_disp.height;i++){
            for(uint32_t j=0;j<map_disp.width;j++){

                uint32_t h  = map_disp.width;
                float hL=0;float hR=0;float hD=0;float hU=0;
                if(j>0){
                    hL = map_disp.data.getAt((j-1) + h*i);
                }
                if(j<map_disp.width){
                    hR = map_disp.data.getAt((j+1) + h*i);
                }
                if(i>0){hD = map_disp.data.getAt( j    + h(i-1));}
                if(i<ma_bump.height){
                    hU = map_disp.data.getAt( j    + h(i+1));
                }
 glm::f32vec3 tangent   = glm::vec3(2.0f * dx, 0.0f, hR - hL); // dP/dx
    glm::f32vec3 bitangent = glm::vec3(0.0f, 2.0f * dy, hU - hD); // dP/dy

    glm::f32vec3 normal = glm::normalize(glm::cross(tangent, bitangent));

               tangent.putAt(i*width + j,normal);
            }
        }
    }
    void Normal(){
        using ty = enuvec<map_disp.imageFormat>::ty;
        normal.imageFormat = image_formats::rgb32f;
        normal.imageSize = map_disp.imageSize;
         for(uint32_t i=0;i<map_disp.height;i++){
            for(uint32_t j=0;j<map_disp.width;j++){
                uint32_t h  = map_disp.width;
                float hL=0;float hR=0;float hD=0;float hU=0;
                if(j>0){
                    hL = map_disp.data.getAt((j-1) + h*i);
                }
                if(j<map_disp.width){
                    hR = map_disp.data.getAt((j+1) + h*i);
                }
                if(i>0){hD = map_disp.data.getAt( j    + h(i-1));}
                if(i<ma_bump.height){
                    hU = map_disp.data.getAt( j    + h(i+1));
                }
float dZdx = (hR - hL) / (2.0f * dx);
    float dZdy = (hU - hD) / (2.0f * dy);

    // Tangent vector along X (U direction)
    glm::f32vec3 tangent(1.0f, 0.0f, dZdx);

    // Bitangent vector along Y (V direction)
    glm::f32vec3 bitangent(0.0f, 1.0f, dZdy);

    // Surface normal = cross product of tangents

    glm::f32vec3 t = glm::normalize(glm::cross(tangent, bitangent));

               map_bump.putAt(i*width + j,t);
            }
        }
    }
   
    material_physical_properties<Q> physical_properties ;
             
};
#define QUALITIES_ENUM 0,1,2,3,4,5,6,7

template < template <DIM , quality::QUALITY > typename T>
struct qdmemoryPool {
    #define NAMED2_DEF(n)     list<named<T<DIM::two,n>*>> named2##n;
    #define NAMED3_DEF(n)     list<named<T<DIM::tri,n>*>> named3##n;
    REPEAT(NAMED_MATERIALS_DEF,QUALITIES_ENUM) 
    #define DATA2_DEF(n)     list<T<DIM::two,n>> d2##n;
    #define DATA3_DEF(n)     list<T<DIM::tri,n>> d3##n;
    REPEAT(NAMED_MATERIALS_DEF,QUALITIES_ENUM) 

    template <DIM d,quality::QUALITY q>
    void add(T<d,q> m){
        #define ADD_MMACRO(D,Q) case Q :{d##D##Q.push_back(m);return;}
        #define ADD_MMACRO2(Q) ADD_MMACRO(2,Q) 
        #define ADD_MMACRO3(Q) ADD_MMACRO(3,Q) 
        if constexpr(d==2){
            switch constexpr (q){REPEAT(ADD_MMACRO2,QUALITIES_ENUM)}}
        if constexpr (d==3) {switch constexpr (q){
                REPEAT(ADD_MMACRO3,QUALITIES_ENUM)};}
    }
    template <DIM d,quality::QUALITY q>
    void addNamed(named<T<d,q>> m){
        #define ADDN_MMACRO(D,Q) case Q :{d##D##Q.push_back(m.data);named##D##Q.push_back(named<T<D,Q>*>(m.name,&(d##D##Q.back())))return;}
        #define ADDN_MMACRO2(Q) ADD_MMACRO(2,Q) 
        #define ADDN_MMACRO3(Q) ADD_MMACRO(3,Q) 
        if constexpr(d==2){
            switch constexpr (q){REPEAT(ADDN_MMACRO2,QUALITIES_ENUM)}}
        if constexpr (d==3) {switch constexpr (q){
                REPEAT(ADDN_MMACRO3,QUALITIES_ENUM)};}
    }

    template <DIM d,quality::QUALITY q>
    list<T<d,q>>& get(){
        #define GET_MMACRO(D,Q) case Q :{return d##D##Q;}
        #define GET_MMACRO2(Q) ADD_MMACRO(2,Q) 
        #define GET_MMACRO3(Q) ADD_MMACRO(3,Q) 
        if constexpr(d==2){
            switch constexpr (q){REPEAT(GET_MMACRO2,QUALITIES_ENUM)}}
        if constexpr (d==3) {switch constexpr (q){
                REPEAT(GET_MMACRO,QUALITIES_ENUM)};}
    }
    template <DIM d,quality::QUALITY q>
    list<named<T<d,q>>>& getNamed(){
        #define GETN_MMACRO(D,Q) case Q :{return named##D##Q;}
        #define GETN_MMACRO2(Q) GETN_MMACRO(2,Q) 
        #define GETN_MMACRO3(Q) GETN_MMACRO(3,Q) 
        if constexpr(d==2){
            switch constexpr (q){REPEAT(GETN_MMACRO2,QUALITIES_ENUM)}}
        if constexpr (d==3) {switch constexpr (q){
                REPEAT(GETN_MMACRO3,QUALITIES_ENUM)};}
    }
};


template < template <DIM > typename T>
struct dmemoryPool {
    list<named<T<DIM::two>*>> named2;
    list<named<T<DIM::tri>*>> named3;
    list<T<DIM::two>> d2;
    list<T<DIM::tri>> d3;

    template <DIM d>
    void add(T<d> m){
        if constexpr(d==2){
d2.push_back(m);return;}
        if constexpr (d==3) {
d3.push_back(m);return;}
    }
    template <DIM d>
    void addNamed(named<T<d>> m){
               if constexpr(d==2){
d2.push_back(m.data);named2.push_back(named<T<2>*>(m.name,&d2.back()));return;}
        if constexpr (d==3) {
d3.push_back(m.data);named3.push_back(named<T<3>*>(m.name,&d3.back());return;}
    }
};


template < template <quality::QUALITY> typename T>
struct qmemoryPool {

    #define QUALDEF(q)     list<named<T<q>*>> named##q; \
    list<T<q>> d##q;

    REPEAT(QUALDEF,QUALITIES_ENUM)

    template <quality::QUALITY q>
    void add(T<d> m){
        switch constexpr(q) {
            #define QUALCASE(q) case q : {d##q.push_back(m);}
            REPEAT(QUALCASE,QUALITIES_ENUM) 
        }
    }
    template <quality::QUALITY q>
    void addNamed(named<T<q>> m){
            switch constexpr(q) {
            #define QUALCASENAME(q) case q : {d##q.push_back(m.data);named##q.push_back(named<T<q>*>(m.name,&d##q.back());}
            REPEAT(QUALCASENAME,QUALITIES_ENUM) 
        }

    }

    template <quality::QUALITY q>
    list<T<q>>& get(T<d> m){
        switch constexpr(q) {
            #define QUALCASEGET(q) case q : {return d##q;}
            REPEAT(QUALCASE,QUALITIES_ENUM) 
        }
    }
    template <quality::QUALITY q>
    list<T<q>*> getNamed(named<T<q>> m){
            switch constexpr(q) {
            #define QUALCASENAME(q) case q : {return named##q;}
            REPEAT(QUALCASENAME,QUALITIES_ENUM) 
        }

    }    
};
qmemoryPool<material> materialPool;



enum TopologyPrimitive {
    POINT_LIST = 0,
    LINE_LIST = 1,
    LINE_STRIP = 2,
    TRIANGLE_LIST = 3,
    TRIANGLE_STRIP = 4,
    TRIANGLE_FAN = 5,
    LINE_LIST_WITH_ADJACENCY = 6,
    LINE_STRIP_WITH_ADJACENCY = 7,
    TRIANGLE_LIST_WITH_ADJACENCY = 8,
    TRIANGLE_STRIP_WITH_ADJACENCY = 9,
    PATCH_LIST = 10,
} 


template <DIM S , quality::QUALITY q>
struct mesh {
    using xyzwVert = std::conditional<S==DIM::tri,glm::vec4,glm::vec3>;
    using xyzVert = std::conditional<S==DIM::tri,glm::vec3,glm::vec2>;

    // 0 Indexed
    std::vector<xyzwVert> vert; //..pointVertices
    std::vector<xyzVert> tvert; // textures vertices;
    std::vector<xyzVert> nvert; // normal vertices
    std::vector<xyzVert> pvert; // Parameter vertices


    std::vector<std::vector<xyzwVert>> lines;

    std::vector<std::vector<xyzwVert>> facevert;
    std::vector<std::vector<xyzwVert>> facenvert;
    std::vector<std::vector<xyzwVert>> facetvert;
    
    
    struct group {
        std::pair<uint32_t,uint32_t> vert;
        std::pair<uint32_t,uint32_t> tvert;
        std::pair<uint32_t,uint32_t> nvert;
        std::pair<uint32_t,uint32_t> pvert;
         
        std::pair<uint32_t,uint32_t> lines;
        std::pair<uint32_t,uint32_t> faces;
        private: 
        material<Q>* material;
    };
    struct materialGroup: group   {
        std::vector<material<Q>*> materials;
    }
    private:
    std::vector<group> groups ;
    std::vector<materialsGroup> materialsGroup;
    
};
dqmemoryPool<mesh> meshPool;



template <DIM S>
struct mesh_prim  {
        using xyzwVert = std::conditional<S==DIM::tri,glm::vec4,glm::vec3>;
    using xyzVert = std::conditional<S==DIM::tri,glm::vec3,glm::vec2>;


    #define PRIMITIVE_ENUM POINT_LIST,LINE_LIST,LINE_STRIP,TRIANGLE_LIST,TRIANGLE_STRIP,TRIANGLE_FAN,LINE_LIST_WITH_ADJACENCY,LINE_STRIP_WITH_ADJACENCY,TRIANGLE_LIST_WITH_ADJACENCY,TRIANGLE_STRIP_WITH_ADJACENCY,PATCH_LIST
    #define PRIM_DEFS(n,NAME) name##n

    #define NORMALS(name) PRIM_DEFS(n,name) 
    #define TEXTURES(name) PRIM_DEFS(t,name)

    #define VERTS(name) PRIM_DEFS(v,name) 
    #define PARAMS(name) PRIM_DEFS(p,name)

    REPEAT(NORMALS,PRIMITIVE_ENUM)
    REPEAT(TEXTURES,PRIMITIVE_ENUM)
    REPEAT(VERTS,PRIMITIVE_ENUM)
    REPEAT(PARAMS,PRIMITIVE_ENUM)
    
    mesh_prim(mesh<S>& p){
        if(p.lines.size()>0){bLINES_STRIP = true;
        for(const std::vector<uint32_t> line : p.lines){

            pLINE_STRIP.push_back(line.ve)
        };};
        // Get Mesh
        for(const face& f : p.faces){
            for(uint32_t i = 0; i < f.vertices.size();i++){
                
            };
        };
    };
};
dmemoryPool<mesh_prim> meshPrimPool;



template <DIM S>
struct dynamicMesh : mesh<S> {
        using xyzwVert = std::conditional<S==DIM::tri,glm::vec4,glm::vec3>;
    using xyzVert = std::conditional<S==DIM::tri,glm::vec3,glm::vec2>;    

struct bonePtGroup : vertGroup {
    xyzwVert vert;
    xyzVert pvert;
    xyzVert tvert;

    std::pair<uint32_t,uint32_t> faces;
    std::pair<uint32_t,uint32_t> lines;
    uint16_t boneUp;
    std::vector<uint16_t> boneDown;
    uint16_t boneDown;
    void addPt(uint16_t pt){bonePtIndices.push_back(pt);}
};
std::vector<bonePtgroup> vertGroups;
};




template <DIM d, quality::QUALITY q>
struct particle{
    material_physical_properties<q> mpt ; 
    rgba base_color ;
    float density ; 
    dynamicMesh<d,q> mesh ;
};

template <DIM d, quality::QUALITY q>
struct fluid  {
    material_physical_properties<q> mpt ; 
    float viscosity;
    rgba base_color ;
    float density ; 
    dynamicMesh<d,q> mesh ;

    fluid(){}
  
};
template <DIM d, quality::QUALITY q>
struct smoke {
    material_physical_properties<q> mpt ; 
    float buoyancy; // -1 -- 1;
};

template <DIM d, quality::QUALITY q, template <DIM , quality::QUALITY > typename T>
struct source   {
    T<d,q> p;
    glm::vec3 pos; 
};
template < DIM d, quality::QUALITY q>
particleSource = source<d,q,paricle> ; 
template <DIM d, quality::QUALITY q>>
using fluidSource = source<d,q,fluid> ;
template <DIM d, quality::QUALITY q>>
using smokeSource = source<d,q,fluid> ;

struct animation {
    list<std::vector<glm::vec3>> pts ;

};

template <DIM S,quality::QUALITY Q> 
struct model : mesh<S,Q> {
    struct manifold { // Have a group conventiion
        std::string name;
        std::pair<uint32_t,uint32_t> vert;
        std::pair<uint32_t,uint32_t> tvert;
        std::pair<uint32_t,uint32_t> nvert;
        std::pair<uint32_t,uint32_t> pvert;
         
        std::pair<uint32_t,uint32_t> lines;
        std::pair<uint32_t,uint32_t> faces;
        std::vector<mesh<S,Q>::materialGroup> materialGroups ;
        std::vector<mesh<S,Q>::group> groups ; 
    };
    std::vector<manifold > manifolds;

    std::vector<animation> anim;
};
dqmemoryPool<model> modelPool 





template <DIM S>
struct dynamicMesh_prim {

};

template <DIM S>
struct softBody : dynamicMesh<S> {
    
};
struct cloth : dynamicMesh<> {
    
};
template <DIM S>
struct entity : dynamicMesh<S>  
{
    virtual virtual render();
    virtual update();
};
template <DIM S>
struct flora : mesh<S> {

};
template <DIM S>
struct dyn_flora : dynamicMesh<S> {

};
// Actors are entities which can be possessed by controlSchemes

struct actor : model  {

};
struct fauna : model {

};
struct human : model
{
    std::string name ;
};

struct attach_int {
    
    std::pair<uint,std::vector< uint> first ;  
    std::pair<uint,std::vector< uint > sec;
    attach_int::mode one_to_one ;
    update_one_to_one(){
        if(first.second.size == sec.second.size){
            one_to_one = true ;}
            else one_to_one = false ;
    }  ;
};

struct attach_points {
    elem* el ;
    std::vector<uint> verts ; 
};

struct group { // Groups elements together in one shared animation unit .
    
    struct attach {
        typedef enum ATTACH_MODE {
        one_to_one , 
        one_to_multiple, 
        one_to_notmultiple,
        multiple_to_one,
        notmultiple_to_one
         } ATTACH_MODE;

        attach::ATTACH_MODE m ; 
        uint first 
        uint second ; 
        std::vector<uint> verts_second ;
        std::vector<uint> verts_first ; 

    };
    std::string name ;
    std::vector<elem*> elems ;
    
    std::map<uint , std::vector<group::attach> >  ><std::pair<elem*, elem* >> attachments;

    void addAttachment ({uint first_i, std::vector<uint> verts } ,  attach_points sec ){
        if(this->elems.find(first.el) ){

        };
    };

};
struct component {
   
    std::string name; 
    std::vector<elem*> elements; 
    std::vector<group*> groups ;
};
struct collection {
    std::string name ;
    std::vector<elem*> elems ;
    std::vector<group*> groups ;
    std::vector<component*> component ;
             
};
// Allows the creation and instantiation of objects in scene based on a base elem
struct chain { 
    struct ref {
        coords ; 
    };
    elem base ; 
    std::vector<elem>  ; 
};



//





struct Lsys {
        
    typedef int16_t number ;
    typedef int16_t[3] vec ;
    typedef int16_t[4] color ; // TODO add all texturing values;
    typedef int16_t[2] complex;

    enum {
        color,
        
    };
    uint8_t Vsize;
    uint8_t omegaSize;
    uint8_t PSize; 
    int16_t* V ; // Alphabet
    int16_t* omega; // Start
    int16_t* P ; // Production rules
    

};



struct LoadDomainInfo{glm::ivec2 coords, int view_distance , void chunks_distance,int fog };

struct LoadWorldInfo{int index, glm::ivec3 coords };
void load_world_domain(glm::ivec3 coords, int view_distance);


    const rgb BLACK(0, 0, 0);
    const rgb WHITE(255, 255, 255);
    const rgb RED(255, 0, 0);
    const rgb GREEN(0, 255, 0);
    const rgb BLUE(0, 0, 255);
    const rgb YELLOW(255, 255, 0);
    const rgb CYAN(0, 255, 255);
    const rgb MAGENTA(255, 0, 255);
    const rgb ORANGE(255, 165, 0);  
    const rgb PURPLE(128, 0, 128); 
    const rgb BROWN(139, 69, 19); 
    const rgb PINK(255, 192, 203);  
    const rgb GRAY(128, 128, 128);
    const rgb LIME(0, 255, 0);      
    const rgb TEAL(0, 128, 128);    
    const rgb INDIGO(75, 0, 130);   
    const rgb GOLD(255, 215, 0);    


  
    // Variables

    enum normType {
        loop,
        ground,
    }
    template <typename T, T minimum, T maximum , normType nt>
    class norm_val : T{
        static const T min = minimum; 
        static const T max = maximum ;
        static const normType normty = nt; 
        
        T val ;
        public:
        virtual norm_val func(T res){
            if constexpr ( nt == normType::loop){
                return min+ ((res)-min)%(max-min)}
            
            if constexpr( nt == normType::ground){
                return (res)>max ? max :( ( res)<min? min : res ); 
            };
        };
        
        norm_val operator+(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val+rhs.val;
           return func(res);
        };
        norm_val operator-(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val-rhs.val;
            return func(res) ;
        };
        norm_val operator*(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val/rhs.val;
           return func(res);
        };
        norm_val operator/(norm_val& lhs, norm_val& rhs) override {
            T res = lhs.val/rhs.val;
            return func(res) ;
        };

    };
    template <typename T>
    using radian = normval<T,0,M_PI,normType::loop>;
    template <typename T>
    using subunit = normval<T,0,1,normType::ground>;
    template <typename T>
    using zsubunit = normval<T,-1,1,normType::ground>;
    
    template <typename T>
    class rangeValue  {
        T val ;
        T minimum ; 
        T maximum ;
        
    };
namespace lod
{
    struct resource {

    };

    template <quality::QUALITY Q>
    struct atlas{ // Can contain uv's and a bunch other stuff

        material<Q> image ; 
        
        uint32_t width;
        uint32_t height;

        uint64_t widthFull;
        uint64_t heightFull;
        size_t lod ; // How many downscalings are there 
        

        glm::uvec2 getLODuv(uint ind ){ // Order Down,right,

        };
        glm::uvec2 getSetuv(uint ind){

        };
        loadMaterial(){
            
        };
       
        void lod(material<Q> im){ // TODO in lod systems there is a a progrssively lower resolution. Everything is placed below the image
            
        };        
        atlas(std::path p , std::vector<std::pair<size_t , size_t> > sizes ) :  p(p) , sizes(sizes) {};
    };
    class file_atlas {
        std::vector<atlas> atlases;
    };
   
    struct lod {
        void 
    };
    
    enum LOD {
        Normal,
        Imposter, // Looks like 3d image but always gets rendered at same angle not size though
        Sprite, // Simmillar to imposter but is not 3d in any way 
    
    } LOD;
    void makeImposter();
    void makeSprite(){};
    void makeSprieFan(){};

    template <DIM d,quality::QUALITY q, template <template <DIM ,quality::QUALITY >> typename T>
    struct qdlod {
       
        T<d,q>& original;
        std::vector<T<d,q>> sub;
        template <DIM d,quality::QUALITY q>
        void LodSys(uint8_t s){
            T<d,q> original.Lod(s);
        };
    }
    template <DIM d, template <template <DIM ,>> typename T>
    struct dlod {
       
        T<d>& original;
        std::vector<T<d>> sub;
        template <DIM d>
        void LodSys(uint8_t s){
            T<d> original.Lod(s);
        };
    }
    template <quality::QUALITY q, template <template <quality::QUALITY >> typename T>
    struct dlod {
       
        T<q>& original;
        std::vector<T<q>> sub;
        template <quality::QUALITY q>
        void LodSys(uint8_t s){
             sub.push_back(original.Lod(s));
        };
    }

     

    struct lodSys {
        
    }
};
  




template <DIM T>
struct coords
{
    std::conditional<T==2,glm::vec2,glm::vec3>::type pos; // x y z
    std::conditional<T==2,glm::vec2,glm::vec3>::type ori ; // orientation
};


// The scene object is always responsible for loading objects accordingly from the world partitioning system and space partitioning systems

enum PERSPECTIVE {
    ThirdPersonLeft,
    ThirdPersonRight,
    ThirdPersonCenter,
    IsoMetric ,
    FirstPerson,
    VR,
    AR
};
namespace camera {
    typedef glm::fvec2 dof ;

    enum EFFECT {
        pixel, // For camera effects applied to pixels 
        texel,
        vertex // For camera effects applied to 
    }EFFECT;
    
    class perspective {
        glm::mat4 ; 
        glm::uvec2 center ; 
        glm::uvec2 left ; 
        glm::uvec2 right ; 
        glm::uvec2 up  ;
        glm::uvec2 down ; 
    };
    class orthoganal : perspective {

    };
    struct effects {
        bool distance_blur; 

    };
    class camera {

    };
};

class ThirdPerson {
    
    float fov,aspect,znear,zfar;
    glm::mat4 getMatrix(glm::vec3 pos){
        mat = glm::perspective(fov,aspect,znear,zfar);
    };
    void move( glm::vec3 amount , glm::mat4 projectionMatrix  ){

    };
};
class FirstPerson {
    glm::mat4 mat; 

    void getMatrix()
};



class perspective {
    PERSPECTIVE v ;

};
template <DIM d>
class cloud {
    
};
namespace sp
{
    class generator {
       
    };
    class biome {
        std::string name ; 
        generator  ;
        
        std::vector<fauna> fauna ; 
    };
    template<generator gen>
    class terrain {
            std::vector<std::vector<>>; 
            gen generator ;
            uv uv ;  
         
    };
    template <DIM T>
    class chunk
    {
        int size ; 
        glm::ivec3 ;
        std::vector<element> elements ;
       
    };
    template <DIM T , size_t s >
    class chunkingShape {

    };
    
    template <DIM T , size_t s  >
    class sp  {
       
         resourceParser ; 
        int maxDistance;

        uint depth ; // Chunk tree depth
        uint min  ;
        uint max ;

        std::vector<sp* > space_partitionings ;

        virtual glm::vec<3 ,float , defaultp   > chunkCoord ; // x 
        virtual source
        
        void positionalCulling(); // Cull everything based on positional perspective
        void perspectiveCulling(); // Cull everything not in the view frustum
        void disOocclusion();

    };

    template <DIM T , size_t levels>
    class planet : sp  {
        std::string name ; 
        std::vector<scene> scene ; 
        rayleigh rayleig_scattering
        mie mie_scattering ;

    };
    template <DIM T , size_t level>
    class MegaStruct : planet {

    };
   
    
};


template <DIM d , sp space_part >
class scene {
    template <DIM d, glm::qualifier Q>
    class lightSource {
        glm::vec<d,float , Q > position;
        glm::vec<d, float , >
    };
    template <DIM d>
    class lightSourceChromatic  {
        glm::vec<d,float , glm::defaultp > position;
        glm::vec<d , float> ; 
    };
    struct skybox {
        rgba_dyn_image images ;
        std::vector<uint > ind_images;  
    };

    skybox sky; 
    world world_partition ; 
    space space_partition ;
    
    bool pos_culling = true; ;
    bool frustum_culling = true ;  

    void positionalCulling();
    void frustumCulling();
    void backFaceCulling() ; 
    void backFaceCulling() ;
    void occlusion();
    void disocllusion() ;
    virtual scene(stypes::rgba_dyn_image _skybox) skybox(_skybox) {

    };

};
    
enum shader_type {
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

struct shaderModule {
    shader_type shader_type;
    auto* ubo  ;bool unib=false  ; uint32_t ubosize; bool dynsUbo;
    auto* ssbo  ;bool shab=false ;  uint32_t ssbosize; bool dynsSsbo;
    int code_size;
    const uint32_t* code; // SPIR-V Module
    std::string name ;
    std::vector<std::string> entry_points; // all entry points
    std::string codePath;
    void readCode(std::string p){
        codePath=p;
        std::ifstream file(p, std::ios::ate | std::ios::binary );
    size_t fileSize = static_cast<size_t>(file.tellg());
    code_size = filesize;
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    c = reinterpret_cast<const uint32_t*>(buffer.data());
    }
    void uboBind(){

    };
    template <typename T>
    void ssboBind(T ssBufo){
        ssbosize=sizeof(ssBufo);
        std::memcpy(ssbo,&ssBufo,ssbo);
    }
    
    }

    /*
         Can apply styles modifing shading modes ( textures and tesselation rules)
    Produces another elem most of the time
    Does not modify animations
    */    



class PipeLineAdapter {
    std::vector<ShaderModule*> points ;

    
    virtual void contribution(){

    };
};

class style {
    virtual void apply(PipeLineAdapter e){};
};


class PipeLines {

};

#endif