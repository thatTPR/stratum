#include <typeindex>
#include <petri/vecs.hpp>
#include <petri/vects.hpp>
#include <tuple>
#include <map>



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
r8ui
};

template<image_formats imf>
struct enu_vec        {
     using ty = ivec4; };

struct enu_vec<image_formats::rgba32f>        { using ty =lvec4};
struct enu_vec<image_formats::rgba16f>        { using ty =vec4};
struct enu_vec<image_formats::rg32f>          { using ty =vec2};
struct enu_vec<image_formats::rg16f>          { using ty =vec2};
struct enu_vec<image_formats::r11f_g11f_b10f> { using ty =svec2};
struct enu_vec<image_formats::r32f>           { using ty =float32};
struct enu_vec<image_formats::r16f>           { using ty =float16};
struct enu_vec<image_formats::rgba16>         { using ty =ivec4};
struct enu_vec<image_formats::rgb10_a2>       { using ty =ivec4 };
struct enu_vec<image_formats::rgba8>          { using ty =ivec4 };
struct enu_vec<image_formats::rg16>           { using ty =ivec2};
struct enu_vec<image_formats::rg8>            { using ty =ivec2 };
struct enu_vec<image_formats::r16>            { using ty =int };
struct enu_vec<image_formats::r8>             { using ty =int };
struct enu_vec<image_formats::rgba16_snorm>   { using ty =vec4};
struct enu_vec<image_formats::rgba8_snorm>    { using ty =vec4 };
struct enu_vec<image_formats::rg16_snorm>     { using ty =vec2};
struct enu_vec<image_formats::rg8_snorm>      { using ty =float };
struct enu_vec<image_formats::r16_snorm>      { using ty =float};
struct enu_vec<image_formats::r8_snorm>       { using ty =float };
struct enu_vec<image_formats::rgba32i>        { using ty =ivec4};
struct enu_vec<image_formats::rgba16i>        { using ty =ivec4 };
struct enu_vec<image_formats::rgba8i>         { using ty =ivec4};
struct enu_vec<image_formats::rg32i>          { using ty =ivec2};
struct enu_vec<image_formats::rg16i>          { using ty =ivec2 };
struct enu_vec<image_formats::rg8i>           { using ty =ivec2 };
struct enu_vec<image_formats::r32i>           { using ty =int32 };
struct enu_vec<image_formats::r16i>           { using ty =int16};
struct enu_vec<image_formats::r8i>            { using ty =int };
struct enu_vec<image_formats::rgba32ui>       { using ty =uvec4 };
struct enu_vec<image_formats::rgba16ui>       { using ty =uvec4 };
struct enu_vec<image_formats::rgb10_a2ui>     { using ty =uvec4 };
struct enu_vec<image_formats::rgba8ui>        { using ty =uvec4 };
struct enu_vec<image_formats::rg32ui>         { using ty =uvec2 };
struct enu_vec<image_formats::rg16ui>         { using ty =uvec2 };
struct enu_vec<image_formats::rg8ui>          { using ty =uvec2 };
struct enu_vec<image_formats::r32ui>          { using ty =uint32 };
struct enu_vec<image_formats::r16ui>          { using ty =uint32 };
struct enu_vec<image_formats::r8ui>           { using ty =uint };

template <image_formats imf,size_t s>
struct image2d {
    using ty = enu_vec<imf>::ty;
    ty s[s][s];

    void read(acqres resource;)

};
template <typename T,size_t x, size_t y , size_t  z>
struct image3d {
    using ty = enu_vec<imf>::ty;
    ty s[x][y]
};

template <image_formats imf>using im8    = image2d<imf,1024,1024>;
template <image_formats imf>using im16   = image2d<imf,1024,1024>;
template <image_formats imf>using im32   = image2d<imf,1024,1024>;
template <image_formats imf>using im164  = image2d<imf,1024,1024>;
template <image_formats imf>using im128  = image2d<imf,1024,1024>;
template <image_formats imf>using im256  = image2d<imf,1024,1024>;
template <image_formats imf>using im512  = image2d<imf,1024,1024>;
template <image_formats imf>using im1024 = image2d<imf,1024,1024>;
template <image_formats imf>using im2048 = image2d<imf,2048,2048>;
template <image_formats imf>using im4096 = image2d<imf,4096,4096>;
template <image_formats imf>using im8192 = image2d<imf,8192,8192>;
template <image_formats imf>using im16384= image2d<imf,16384,16384>;
template <image_formats imf>using im32768= image2d<imf,32768,32768>;

// Todo make more programmatic

template<typename... args>
class ty_index_map  {
    public:
    std::tuple<args...> r ;
    static const size_t size = sizeof...(args);
    arr<std::type_index,sizeof...(args)> tys;
    auto& operator[](std::type_index s; ){
        for(int i = 0 ; i <sizeof(size) ; i++){
            if(s==this->tys[i]){return this->r[i];};
        };
    };
    auto& operator[](size_t s){return this->r[s];};
    void ty_index_map(std::initializer_list<type_index> list){
        this->tys=new arr<std::type_index,sizeof...(args)>(list);
    };

};
#define tyind(t) type_index(typeid(t))

const std::map<std::type_index,std::string> ty_index_vecs{// Vecs
{tyind(bvec2),"bvec2"},{tyind(bvec3),"bvec3"},{tyind(bvec4),"bvec4"},{tyind(uvec2),"uvec2"},{tyind(uvec3),"uvec3"},{tyind(uvec4),"uvec4"},{tyind(ivec2),"ivec2"},{tyind(ivec3),"ivec3"},{tyind(ivec4),"ivec4"},{tyind(vec2),"vec2"},{tyind(vec3),"vec3"},{tyind(vec4),"vec4"},{tyind(bmat2x2),"bmat2x2"},{tyind(bmat2x3),"bmat2x3"},{tyind(bmat2x4),"bmat2x4"},{tyind(bmat3x2),"bmat3x2"},{tyind(bmat3x3),"bmat3x3"},{tyind(bmat3x4),"bmat3x4"},{tyind(bmat4x2),"bmat4x2"},{tyind(bmat4x3),"bmat4x3"},{tyind(bmat4x4),"bmat4x4"},{tyind(umat2x2),"umat2x2"},{tyind(umat2x3),"umat2x3"},{tyind(umat2x4),"umat2x4"},{tyind(umat3x2),"umat3x2"},{tyind(umat3x3),"umat3x3"},{tyind(umat3x4),"umat3x4"},{tyind(umat4x2),"umat4x2"},{tyind(umat4x3),"umat4x3"},{tyind(umat4x4),"umat4x4"},{tyind(imat2x2),"imat2x2"},{tyind(imat2x3),"imat2x3"},{tyind(imat2x4),"imat2x4"},{tyind(imat3x2),"imat3x2"},{tyind(imat3x3),"imat3x3"},{tyind(imat3x4),"imat3x4"},{tyind(imat4x2),"imat4x2"},{tyind(imat4x3),"imat4x3"},{tyind(imat4x4),"imat4x4"},{tyind(mat2x2),"mat2x2"},{tyind(mat2x3),"mat2x3"},{tyind(mat2x4),"mat2x4"},{tyind(mat3x2),"mat3x2"},{tyind(mat3x3),"mat3x3"},{tyind(mat3x4),"mat3x4"},{tyind(mat4x2),"mat4x2"},{tyind(mat4x3),"mat4x3"},{tyind(mat4x4),"mat4x4"},
{tyind(im8),"im8"},{tyind(im16),"im16"},{tyind(im32),"im32"},{tyind(im164),"im164"},{tyind(im128),"im128"},{tyind(im256),"im256"},{tyind(im512),"im512"},{tyind(im1024),"im1024"},{tyind(im2048),"im2048"},{tyind(im4096),"im4096"},{tyind(im8192),"im8192"},{tyind(im16384),"im16384"},{tyind(im32768),"im32768"}

};

const map<std::type_index, std::string> ty_index_structs = {
      
};

map<type_index,std::string> ty_index = ty_index + ; 

ty_index_map<
bvec2,bvec3,bvec4,uvec2,uvec3,uvec4,ivec2,ivec3,ivec4,vec2,vec3,vec4,bmat2x2,bmat2x3,bmat2x4,bmat3x2,bmat3x3,bmat3x4,bmat4x2,bmat4x3,bmat4x4,umat2x2,umat2x3,umat2x4,umat3x2,umat3x3,umat3x4,umat4x2,umat4x3,umat4x4,imat2x2,imat2x3,imat2x4,imat3x2,imat3x3,imat3x4,imat4x2,imat4x3,imat4x4,mat2x2,mat2x3,mat2x4,mat3x2,mat3x3,mat3x4,mat4x2,mat4x3,mat4x4,
im8,im16,im32,im164,im128,im256,im512,im1024,im2048,im4096,im8192,im16384,im32768,

> type_ind(
tyind(bvec2),tyind(bvec3),tyind(bvec4),tyind(uvec2),tyind(uvec3),tyind(uvec4),tyind(ivec2),tyind(ivec3),tyind(ivec4),tyind(vec2),tyind(vec3),tyind(vec4),tyind(bmat2x2),tyind(bmat2x3),tyind(bmat2x4),tyind(bmat3x2),tyind(bmat3x3),tyind(bmat3x4),tyind(bmat4x2),tyind(bmat4x3),tyind(bmat4x4),tyind(umat2x2),tyind(umat2x3),tyind(umat2x4),tyind(umat3x2),tyind(umat3x3),tyind(umat3x4),tyind(umat4x2),tyind(umat4x3),tyind(umat4x4),tyind(imat2x2),tyind(imat2x3),tyind(imat2x4),tyind(imat3x2),tyind(imat3x3),tyind(imat3x4),tyind(imat4x2),tyind(imat4x3),tyind(imat4x4),tyind(mat2x2),tyind(mat2x3),tyind(mat2x4),tyind(mat3x2),tyind(mat3x3),tyind(mat3x4),tyind(mat4x2),tyind(mat4x3),tyind(mat4x4),

);


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
struct image2D {
    size_t x; 
    size_t y;
    image_format imf[x][y];
};
struct image3D {
    size_t x ; 
    size_t y ;
    size_t z ;
    image_format imf;

};

struct buffer_options {

};

struct shader_module {
    arr<int> uniform;
    arr<uniform_option>
    arr<int>  buffs; // Ubos and SSBO
    arr<buffer_Options> 
    arr<int> ins;

    arr<int> out;
    
}shader_module;

class module {

};