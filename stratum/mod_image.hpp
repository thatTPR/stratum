#ifndef MOD_IMAGE_HPP
#define MOD_IMAGE_HPP
#include "mod_lod.hpp"
namespace mod {
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

    constexpr uint8_t bitdepth(image_format imf,size_t s){
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
    constexpr uint8_t bitdepth_r(image_format imf){return bitdepth(imf,0);};
    constexpr uint8_t bitdepth_g(image_format imf){return bitdepth(imf,1);};
    constexpr uint8_t bitdepth_b(image_format imf){return bitdepth(imf,2);};
    constexpr uint8_t bitdepth_a(image_format imf){
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

constexpr uint8_t bitd(image_formats imf){return bitdepth_r(imf)+bitdepth_g(imf)+bitdepth_b(imf)+bitdepth_a(imf);}


constexpr uint8_t imageFormatBytes(image_formats imf){bitdepth(imf)/8;}

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
    void gamma(float g){
        uint8_t n[length][byd/length];

        for(uint32_t i=0;i<imageSize;i++){
            uint8_t s[byd/length] ;
            
            for(uint8_t j=0;j<length;j++){
                std::memcpy(s ,data+byd*i + j*(byd/length) ,byd/length);
                for(uint8_t h =byd/length-1;h>=0;h++){
                    float t= s[h];
                    rem = 
                }
                std::memcpy(data+byd*i + j*(byd/length) ,&s + (8-(byd/length)),byd/length);
            };
        };
    };
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
      

    image2D loadChannel(uint8_t s){
        int8_t bypd= bdc/8;
        image2D i;.width=width;i.height=height;
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
    template <typename clrFr, typename imT>
    bool zero(imT& im,uint32_t x,uint32_t y){
        void* p = im.data+sizeof(clrFr)*(im.width*x +y);
        for(uint32_t i=0;i<sizeof(clrFr);i++){
            if( *(p+i) != 0) {return false;}
        }
        return true;
    
    };

struct image2D : image1D {




    
    uint32_t height;


    using pt = glm::vec2;
    pt pow(pt p,uint8_t s){pt a=p;for(uint8_t ss=2;ss<s;ss++  ){a=a*p;};return a;}
    struct line{pt s,e; float len(){pt p ; p.x=e.x-s.x;p.y=e.y-s.y;return sqrt(p.x*p.x + p.yp.y); };
};

    template <typename clrFr>
    void dot(clrFr& c,uint32_t x,uint32_t y){std::memcpy(data+x+t*width,c,sizeof(c));};
    
    template <typename clrFr>
    void _dot(clrFr (*ptr)(x,y) ,uint32_t x,uint32_t y){dot(ptr(x,y),x,y)};
    

    template <typename clrFr>
    void stroke(clrFr& colr, float& strkw,float ang,line& l){
        float len = l.len();
        float theta = (ang+(M_PI/4) ) % (M_PI * 2);
        float strkh=strkw/2;
        size_t i = (size_t)len ;
        float lend=len/i;
        pt p{l.s.x,l.s.y};        
        float dist = len/i;
        for (size_t j=0;j<i;j++){
            line s{{p.x-cos(theta)*strkh , p.y - sin(theta)*strkh } ,{p.x+cos(theta)*strkh , p.y + sin(theta)*strkh } }; 
            float mag= sqrt(s.x*s.x , s.y*s.y) ;
            pt pp{p.x-cos(theta)*strkh , p.y - sin(theta)*strkh } ;
            size_t k=(size_t) mag ;size_t magd=mag/k; 
            for(size_t it=0;it<k;++it){
                dot(colr, (uint32_t)pp.x,(uint32_t)pp.y);
                pp.x+=cos(ang)*(magd) ; pp.y+=sin(ang)*magd; 
            };
            
            p.x+=cos(ang)*lend;p.y+=sin(ang)*lend;
         };      
    };
    template <typename clrFr>
    void _stroke(  clrFr& colr,float& strkw,float& phi,line& l){

        float strkh=strkw/2;
        float ang = (phi+(M_PI/4) ) % (M_PI * 2);
        line s{{l.s.x -(cos(ang)*strkh) ,l.s.x-(sin(ang)*strkh) },{ l.s.x+(cos(ang)*strkh) ,l.s.x+(sin(ang)*strkh) }};
        line e{{l.e.x -(cos(ang)*strkh) ,l.e.x-(sin(ang)*strkh) },{ l.e.x+(cos(ang)*strkh) ,l.e.x+(sin(ang)*strkh) }};
        stroke(colr,2,ang,s);stroke(colr,2,ang,e);
    };
    template <typename clrFr>
    void line(  clrFr& colr,float& strkw,line l){stroke(colr,strkw,l);}


    template <typename clrFr>
    void arc(clrFr colr , float strkw,pt c, float r, float phi,float end){
        float size = M_PI/2 * r;
        float step = 1/size;
        pt f=pt(c.x+r*cos(phi),c.y+r*sin(phi));
        for(float p=phi+step;p<end;++p){
            pt g=pt(c.x+r*cos(p),c.y+r*sin(p));
            _stroke(colr,strkw,p-M_PI_2,line(f,g));
            f=g;
        };
    };

    template <typename clrFr>
    void circle(  clrFr& colrFill,clrFr& strokeFill,float& strkw,float r,float cx,float cy){
        
        float size = M_PI*width;

        float delta = 1/(float)size / 2 M_PI;
        
        float len = 2*M_PI*r; float theta=delta;
        float slen = len/size;
        auto zpt = [&slen,&theta] (line& l) {
            r.e.x=cos(theta)*slen  ,r.e.y=sin(theta)*slen;
            r.e.x+=r.s.x;r.e.y+=r.s.y;
        };
        auto nextl = [&slen,&delta,&theta](line& l) -> line {
            line r;r.s.x=l.e.y;r.s.y=l.e.y;
            float theta +=delta;
            zpt(r);return r;
        };
        float strkw = v.strw*UserSpaceUnits ;
            line l{cx,cy-r};zpt(r);
            for(uint32_t i=0;i<size;i++){line rad{ {_cx,_cy} , {l.xa,l.ya}};
            float phi=(theta+ (M_PI/4)) % (M_PI*2);
            stroke<uint32_t>(colrFill,1,theta,rad);_stroke<uint32_t>(strokeFill,strkw,phi,l);l=nextl(l);}
    };

template <typename clrFr>
    void ellipseArc(  clrFr& colrFill,float& strkw,float rx,float ry,float cx,float cy, float phi ,float alpha,float rotation=0){

        float stepLen = 1/ (M_PI*(rx+ry))  ;
        float stepRad = 2*M_PI * stepLen;
        float a = 2*rx;
        float b= 2*ry;
        auto lam = [&](float ang)->pt{return pt(cx+a*cos(ang+rotation),cy+ b* sin(ang+rotation))};
        pt prev=lam(0);
        for(float i=stepRad;i<M_2_PI;i+=stepRad){
            pt p = lam(i);

            line rad{ {cx,cy} , p};
            pt pr = rad.e-rad.s;
            line arc = line(prev,p);
            pt pp = arc.e-arc.s;
            stroke<uint32_t>(colrFill,1,atan(pr.y,pr.x) ,rad);_stroke<uint32_t>(strokeFill,strkw,atan(pp.y,pp.x),arc);
            prev=p;
        };
    }

    template <typename clrFr>
    void ellipse(  clrFr& colrFill,clrFr& strokeFill,float& strkw,float rx,float ry,float cx,float cy){ellipseArc(strokeFill,strkw,rx,ry,cx,cy,0,2*M_PI);
    
        for(uint32_t i=0;i<width;i++){
            for(uint32_t j=0;j<height;j++){
                for(;zero<clrFr>(data+sizeof(clrFr)(x*width+y) ) ;j++ ){if(j==height){goto cont1;}};
                uint32_t jj =j;if(jj==height{continue;})
                for(;!zero<clrFr>(data+sizeof(clrFr)(x*width+y)) ;j++ ){if(j==height){goto cont1;};};
                for(;jj<j;jj++){dot(colrFill,i,jj);} ;continue;}
                cont1:
            };  
        }
    };
    template <typename clrFr>
    struct forward{clrFr& f;clrFr get(uint32_t x,uint32_t y) {return f;};forward(clrFr& s) : f(s);}
     template <typename clrFr>
    void _scan(clrFr (*ptr)(uint32_t ,uint32_t) ){
        bool zrx=false; 
        for(uint32_t x=0;x<width;i++){
            for(uint32_t y=0;y<height,y++){
                if(!zero<clrFr>(x,y))){
                    for(;!zero<clrFr>(im,x,y));y++){if(i==height){goto cont;};}
                    uint32_t yy=y;
                    for(;zero<clrFr>(im,x,y));y++){if(i==height){goto cont;};}
                    for(;yy<=y;yy++){_dot(ptr,x,yy);}                    
                    for(;!zero<clrFr>(im,x,y));y++){};
                    
                    continue;
                };
                cont:
            };
        };
    };
    template <typename clrFr>
    void scan(clrFr& d){
        forward ref(d);
        _scan(ref.get);
    }
    float plus(pt h){return sqrt(h.x*h.x + h.y*h.y);}



    uint32_t binomial(uint8_t n , uint8_t k){
        uint32_t res=1;
        for(uint32_t i =k+1;i<=n;i++){res*=i;};
        for(uint32_t i =1;i<=k;i++){res*=i;};
        return res;
    };
    
    template <typename clrFr,size_t ps>
    void bezier(bool fstart,clrFr colr ,float strkw, pt p[ps] ){
        float step =1 ;
        float ls = plus(p[0]-p[1]);
        float len =ls;
        for(size_t i=1;i<ps-1;i++){len+=plus(p[i+1]-p[i] ); }

        float step = 1 / len ;
        float lssteps = ls/len;
        pt last;
        if(fstart){
            float lssteps = ls/len;
            sit+=lssteps;
            last=p[1];
        };
        else {last=p[0];}
        for(;sit<1;sit+=step){
            pt h;
            for(uint8_t i=0 ;i<ps;i++  ){
                h+=(float)binomial(ps-1,i) * pow ( (1-sit) ,((float)ps-1-(float)i) )*pow(sit,(float)i) * p[i] ; 
            }
            line(colr,strkw,line(last,h)); 
            last =h;
        };
    }

    template <typename clrFr>
    void cubic(bool fstart,clrFr colr ,float strkw, pt x, pt y, pt z,pt w){bezier(fstart,colr,strkw,{x,y,z,w});};
    template <typename clrFr>
    void quadratic(bool fstart,clrFr colr ,float strkw, pt x, pt y, pt z){bezier(fstart,colr,strkw,{x,y,z});};
    


    template <typename clrFr>
    void arc(clrFr colr , float strkw,pt s, pt r, float angle, pt flag,pt eof){
        bool smallArc = flag.x==0;
        bool clockWise = flag.y==0;
        // Tangent at point
        float tgs = 
        float len = M_PI * plus(xy-s);
        pt center;
        
        float st,et;
        float d=  sqrt(pow(e.x-s.x,2) + pow(e.y-s.y , 2) ) ;
        float a=pow(r.x,2) -pow(r.y,2) + d*d;
        float h=sqrt(r.x*r.x-a*a);
        pt pp(s.x+a*((e.x-s.x)/d) , s.y+a*((e.y-s.y)/d));
        
        pt c1(pp.x+(h*(e.y-s.y)/d) , pp.y-(h*(e.x-s.x)/d)) ;
        pt c2(pp.x-(h*(e.y-s.y)/d) , pp.y+(h*(e.x-s.x)/d)) ;
        pt c=c1;

        if (!clockWise){c = c2; } ;
        pt cs=s-c ;pt ce=e-c; 
        float phi = atan(cs.y,cs.x);float alpha=atan(ce.y,ce.x);
        if(smallArc){float t=phi;phi = alpha ; alpha =phi }  ;
        if(phi>alpha){alpha+=M_PI} ;
        ellipseArc(colr, 0,r.x,r.y,c.x,c.y,phi,alpha,angle );
    };

    template <typename clrFr>
    void glyf(clrFr colr,pt& size,pt& p,mod::glyfft gl) ;
 
    void blend(uint32_t w, uint32_t h , void* d,uint32_t x,uint32_t y){
        for(uint32_t i;i<h;i++){std::memcpy(data+((y+i)*width+x)*byd , d + i*w*byd, w*byd);}
    };  
    void blit(uint32_t w, uint32_t h , void* d,uint32_t x,uint32_t y){
        for(uint32_t i;i<h;i++){std::memcpy(data+((y+i)*width+x)*byd , d + i*w*byd, w*byd);}
    };  
    void ImageSize(){imageSize=width*height;bd=bitd(imageFormat);bdc = bitdepth_r(imageFormat);byd = bitd(imageFormat)/8 ;length=enu_vec<imageFormat>::ty::length();}
        image2d(uint32_t size,image_format fm) : width(w),height(h),imageFormat(fm) {init();};
    image2D(uint32_t w,uint32_t h,image_format fm) : width(w),height(h),imageFormat(fm){ init();};

};
struct aimage2D : std::vector<image2D>{ 
    uint32_t swidth;
    uint32_t sheight;
}
struct image3D : image1D {
    uint32_t size_t height ;
    uint32_t size_t depth ;
    image3D(uint32_t w,uint32_t h,uint32_t d,image_format fm=image_format::rgba32ui) : width(w),height(h),depth(d),imageFormat(fm){Init();};
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
VIDEO_DECODE_DST_BIT = 0x00000400,
VIDEO_DECODE_SRC_BIT = 0x00000800,
VIDEO_DECODE_DPB_BIT = 0x00001000,
};


struct imageOpts {
    bool storage = true;
    bool sharing =false;
    image_usage usage = image_usage::TRANSFER_DST_BIT | image_usage::STORAGE_BIT ;
    image_dim dim;
    uint32_t w,h,depth;
    int miplevels;
    int arrlayers =1;
    sample_count sample =  sample_count::sample_1;
    imageOpts() = default ;
};

}
#endif