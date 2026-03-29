#include <strata/backend/modules.hpp>
#define COLORSFORM rgba32f,rgba16f,rg32f,rg16f,r11f_g11f_b10f,r32f,r16f,rgba16,rgb10_a2,rgba8,rg16,rg8,r16,r8,rgba16_snorm,rgba8_snorm,rg16_snorm,rg8_snorm,r16_snorm,r8_snorm,rgba32i,rgba16i,rgba8i,rg32i,rg16i,rg8i,r32i,r16i,r8i,rgba32ui,rgba16ui,rgb10_a2ui,rgba8ui,rg32ui,rg16ui,rg8ui,r32ui,r16ui,r8ui
#define VECS bvec2,bvec3,bvec4,uvec2,uvec3,uvec4,ivec2,ivec3,ivec4,vec2,vec3,vec4,bmat2x2,bmat2x3,bmat2x4,bmat3x2,bmat3x3,bmat3x4,bmat4x2,bmat4x3,bmat4x4,umat2x2,umat2x3,umat2x4,umat3x2,umat3x3,umat3x4,umat4x2,umat4x3,umat4x4,imat2x2,imat2x3,imat2x4,imat3x2,imat3x3,imat3x4,imat4x2,imat4x3,imat4x4,mat2x2,mat2x3,mat2x4,mat3x2,mat3x3,mat3x4,mat4x2,mat4x3,mat4x4
#define IMS im8,im16,im32,im164,im128,im256,im512,im1024,im2048,im4096,im8192,im16384,im32768

#define ONE(macro, x) macro(x)
#define ONE(macro, first, ...)  macro(first) ONE(macro,__VA_LIST__) 

#define ONE(macro ,first , second) macro(first ) macro(second)

#define IMF(imf) /
using ##imf_im8 = im8<image_formats::##imf>;/
using ##imf_im16 = im16<image_formats::##imf>;/
using ##imf_im32 = im32<image_formats::##imf>;/
using ##imf_im164 = im164<image_formats::##imf>;/
using ##imf_im128 = im128<image_formats::##imf>;/
using ##imf_im256 = im256<image_formats::##imf>;/
using ##imf_im512 = im512<image_formats::##imf>;/
using ##imf_im1024 = im1024<image_formats::##imf>;/
using ##imf_im2048 = im2048<image_formats::##imf>;/
using ##imf_im4096 = im4096<image_formats::##imf>;/
using ##imf_im8192 = im8192<image_formats::##imf>;/
using ##imf_im16384 = im16384<image_formats::##imf>;/
using ##imf_im32768 = im32768<image_formats::##imf>;

#define IMG_INSTS(imf) ##imf_im8,##imf_im16,##imf_im32,##imf_im164,##imf_im128,##imf_im256,##imf_im512,##imf_im1024,##imf_im2048,##imf_im4096,##imf_im8192,##imf_im16384,##imf_im32768

#define tyind(t) type_index(typeid(t))
#define TY_INDEX_STR(imf) {tyind(##imf_im8),"##imf_im8"},{tyind(##imf_im16),"##imf_im16"},{tyind(##imf_im32),"##imf_im32"},{tyind(##imf_im164),"##imf_im164"},{tyind(##imf_im128),"##imf_im128"},{tyind(##imf_im256),"##imf_im256"},{tyind(##imf_im512),"##imf_im512"},{tyind(##imf_im1024),"##imf_im1024"},{tyind(##imf_im2048),"##imf_im2048"},{tyind(##imf_im4096),"##imf_im4096"},{tyind(##imf_im8192),"##imf_im8192"},{tyind(##imf_im16384),"##imf_im16384"},{tyind(##imf_im32768),"##imf_im32768"},

#define TPASTE(tok,a) ##tok_a

#define TPASTE_TYIND(imf) tyind(##imf_t),

#define TY_IMF(imf)  enu_vec<image::formats::##imf>::ty

#define COL_VF_STR(imf) {tyind(TY_IMF),"##imf"},
#define COL_VF(imf) enu_vec<image::formats::##imf>::ty
