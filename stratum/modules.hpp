#ifndef MODULES_HPP
#define MODULES_HPP
#include <typeindex>
#include <cstddef>
#include <math.h>
#include <vector>
#include <string>
#include <petri/vecs.hpp>
#include <petri/vects.hpp>
#include <tuple>
#include <map>
#include <lib/glm/glm.hpp>

struct app_info {
    char*  name;
    uint32_t  ver;
    char*  engname;
    char*  engver;
};



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
struct color        {
     using ty = ivec4; };
#ifdef ENU_VEC_STRATA_NO_GLM
struct enu_vec<image_formats::rgba32f>        { using ty =dvec4;};
struct enu_vec<image_formats::rgba16f>        { using ty =vec4;};
struct enu_vec<image_formats::rg32f>          { using ty =dvec2;};
struct enu_vec<image_formats::rg16f>          { using ty =vec2;};
struct enu_vec<image_formats::r11f_g11f_b10f> { using ty =svec3;};
struct enu_vec<image_formats::r32f>           { using ty =float32;};
struct enu_vec<image_formats::r16f>           { using ty =float16;};
struct enu_vec<image_formats::rgba16>         { using ty =ivec4;};
struct enu_vec<image_formats::rgb10_a2>       { using ty =sivec4 ;};
struct enu_vec<image_formats::rgba8>          { using ty =sivec4 ;};
struct enu_vec<image_formats::rg16>           { using ty =ivec2;};
struct enu_vec<image_formats::rg8>            { using ty =sivec2 ;};
struct enu_vec<image_formats::r16>            { using ty =int ;};
struct enu_vec<image_formats::r8>             { using ty =sint ;};
struct enu_vec<image_formats::rgba16_snorm>   { using ty =vec4;};
struct enu_vec<image_formats::rgba8_snorm>    { using ty =svec4 ;};
struct enu_vec<image_formats::rg16_snorm>     { using ty =vec2;};
struct enu_vec<image_formats::rg8_snorm>      { using ty =vec2 ;};
struct enu_vec<image_formats::r16_snorm>      { using ty =float;};
struct enu_vec<image_formats::r8_snorm>       { using ty =float ;};
struct enu_vec<image_formats::rgba32i>        { using ty =livec4;};
struct enu_vec<image_formats::rgba16i>        { using ty =ivec4 ;};
struct enu_vec<image_formats::rgba8i>         { using ty =sivec4;};
struct enu_vec<image_formats::rg32i>          { using ty =livec2;};
struct enu_vec<image_formats::rg16i>          { using ty =ivec2 ;};
struct enu_vec<image_formats::rg8i>           { using ty =sivec2 ;};
struct enu_vec<image_formats::r32i>           { using ty =int32 ;};
struct enu_vec<image_formats::r16i>           { using ty =int16;};
struct enu_vec<image_formats::r8i>            { using ty =int16 ;};
struct enu_vec<image_formats::rgba32ui>       { using ty =luvec4 ;};
struct enu_vec<image_formats::rgba16ui>       { using ty =uvec4 ;};
struct enu_vec<image_formats::rgb10_a2ui>     { using ty =suvec4 ;};
struct enu_vec<image_formats::rgba8ui>        { using ty =suvec4 ;};
struct enu_vec<image_formats::rg32ui>         { using ty =luvec2 ;};
struct enu_vec<image_formats::rg16ui>         { using ty =uvec2 ;};
struct enu_vec<image_formats::rg8ui>          { using ty =suvec2 ;};
struct enu_vec<image_formats::r32ui>          { using ty =uint32 ;};
struct enu_vec<image_formats::r16ui>          { using ty =uint32 ;};
struct enu_vec<image_formats::r8ui>           { using ty =suint ;};
#endif

struct enu_vec<image_formats::rgba32f>        { using ty =glm::highp_vec4;};
struct enu_vec<image_formats::rgba16f>        { using ty =glm::mediump_vec4;};
struct enu_vec<image_formats::rg32f>          { using ty =glm::hihip_vec2;};
struct enu_vec<image_formats::rg16f>          { using ty =glm::mediump_vec2;};
struct enu_vec<image_formats::r11f_g11f_b10f> { using ty =glm::mediump_vec3;};
struct enu_vec<image_formats::r32f>           { using ty =float32_t;};
struct enu_vec<image_formats::r16f>           { using ty =float16_t;};
struct enu_vec<image_formats::rgba16>         { using ty =glm::mediump_ivec4;};
struct enu_vec<image_formats::rgb10_a2>       { using ty =glm::mediump_ivec4 ;};
struct enu_vec<image_formats::rgba8>          { using ty =glm::lowp_ivec4 ;};
struct enu_vec<image_formats::rg16>           { using ty =glm::mediump_ivec2;};
struct enu_vec<image_formats::rg8>            { using ty =glm::lowp_ivec2 ;};
struct enu_vec<image_formats::r16>            { using ty =int16_t ;};
struct enu_vec<image_formats::r8>             { using ty =int8_t ;};
struct enu_vec<image_formats::rgba16_snorm>   { using ty =glm::mediump_vec4;};
struct enu_vec<image_formats::rgba8_snorm>    { using ty =glm::lowp_vec4 ;};
struct enu_vec<image_formats::rg16_snorm>     { using ty =glm::mediump_vec2;};
struct enu_vec<image_formats::rg8_snorm>      { using ty =glm::lowp_vec2 ;};
struct enu_vec<image_formats::r16_snorm>      { using ty =float;};
struct enu_vec<image_formats::r8_snorm>       { using ty =float ;};
struct enu_vec<image_formats::rgba32i>        { using ty =glm::hihgp_ivec4;};
struct enu_vec<image_formats::rgba16i>        { using ty =glm::mediump_ivec4 ;};
struct enu_vec<image_formats::rgba8i>         { using ty =glm::lowp_ivec4;};
struct enu_vec<image_formats::rg32i>          { using ty =glm::highp_ivec2;};
struct enu_vec<image_formats::rg16i>          { using ty =glm::mediump_ivec2 ;};
struct enu_vec<image_formats::rg8i>           { using ty =glm::lowp_ivec2<> ;};
struct enu_vec<image_formats::r32i>           { using ty =int32_t ;};
struct enu_vec<image_formats::r16i>           { using ty =int16_t;};
struct enu_vec<image_formats::r8i>            { using ty =int8_t ;};
struct enu_vec<image_formats::rgba32ui>       { using ty =glm::highp_uvec4 ;};
struct enu_vec<image_formats::rgba16ui>       { using ty =glm::mediump_uvec4 ;};
struct enu_vec<image_formats::rgb10_a2ui>     { using ty =glm::mediump_uvec4 ;};
struct enu_vec<image_formats::rgba8ui>        { using ty =glm::lowp_uvec4 ;};
struct enu_vec<image_formats::rg32ui>         { using ty =glm::highp_uvec2 ;};
struct enu_vec<image_formats::rg16ui>         { using ty =glm::mediump_uvec2 ;};
struct enu_vec<image_formats::rg8ui>          { using ty =glm::lowp+uvec2 ;};
struct enu_vec<image_formats::r32ui>          { using ty =uint32_t ;};
struct enu_vec<image_formats::r16ui>          { using ty =uint16_t ;};
struct enu_vec<image_formats::r8ui>           { using ty =uint8_t ;};


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

template <image_formats imf,size_t s>
struct image2d {
    using ty = enu_vec<imf>::ty;
    ty data[s][s];

    void read(acqres resource){
        this->data=resource.read();
    };

    
    auto read(acqres resource){
        
    };
};
template <image_formats imf,size_t x, size_t y , size_t  z>
struct image3d {
    using ty = enu_vec<imf>::ty;
    ty s[x][y][z]
};

template <image_formats imf>using im8    = image2d<imf,8>;
template <image_formats imf>using im16   = image2d<imf,16>;
template <image_formats imf>using im32   = image2d<imf,32>;
template <image_formats imf>using im164  = image2d<imf,164>;
template <image_formats imf>using im128  = image2d<imf,128>;
template <image_formats imf>using im256  = image2d<imf,256>;
template <image_formats imf>using im512  = image2d<imf,512>;
template <image_formats imf>using im1024 = image2d<imf,1024>;
template <image_formats imf>using im2048 = image2d<imf,2048>;
template <image_formats imf>using im4096 = image2d<imf,4096>;
template <image_formats imf>using im8192 = image2d<imf,8192>;
template <image_formats imf>using im16384= image2d<imf,16384>;
template <image_formats imf>using im32768= image2d<imf,32768>;

using imicon = im128<image_formats::rgba16>;

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
/* Not really needed with reflect
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

static const std::map<std::type_index,std::string> ty_index{// Vecs
{tyind(bvec2),"bvec2"},{tyind(bvec3),"bvec3"},{tyind(bvec4),"bvec4"},{tyind(uvec2),"uvec2"},{tyind(uvec3),"uvec3"},{tyind(uvec4),"uvec4"},{tyind(ivec2),"ivec2"},{tyind(ivec3),"ivec3"},{tyind(ivec4),"ivec4"},{tyind(vec2),"vec2"},{tyind(vec3),"vec3"},{tyind(vec4),"vec4"},{tyind(bmat2x2),"bmat2x2"},{tyind(bmat2x3),"bmat2x3"},{tyind(bmat2x4),"bmat2x4"},{tyind(bmat3x2),"bmat3x2"},{tyind(bmat3x3),"bmat3x3"},{tyind(bmat3x4),"bmat3x4"},{tyind(bmat4x2),"bmat4x2"},{tyind(bmat4x3),"bmat4x3"},{tyind(bmat4x4),"bmat4x4"},{tyind(umat2x2),"umat2x2"},{tyind(umat2x3),"umat2x3"},{tyind(umat2x4),"umat2x4"},{tyind(umat3x2),"umat3x2"},{tyind(umat3x3),"umat3x3"},{tyind(umat3x4),"umat3x4"},{tyind(umat4x2),"umat4x2"},{tyind(umat4x3),"umat4x3"},{tyind(umat4x4),"umat4x4"},{tyind(imat2x2),"imat2x2"},{tyind(imat2x3),"imat2x3"},{tyind(imat2x4),"imat2x4"},{tyind(imat3x2),"imat3x2"},{tyind(imat3x3),"imat3x3"},{tyind(imat3x4),"imat3x4"},{tyind(imat4x2),"imat4x2"},{tyind(imat4x3),"imat4x3"},{tyind(imat4x4),"imat4x4"},{tyind(mat2x2),"mat2x2"},{tyind(mat2x3),"mat2x3"},{tyind(mat2x4),"mat2x4"},{tyind(mat3x2),"mat3x2"},{tyind(mat3x3),"mat3x3"},{tyind(mat3x4),"mat3x4"},{tyind(mat4x2),"mat4x2"},{tyind(mat4x3),"mat4x3"},{tyind(mat4x4),"mat4x4"},
// 
{dvec4,"dvec4"},{vec4,"vec4"},{dvec2,"dvec2"},{vec2,"vec2"},{svec3,"svec3"},{float32,"float32"},{float16,"float16"},{ivec4,"ivec4"},{sivec4,"sivec4"},{sivec4,"sivec4"},{ivec2,"ivec2"},{sivec2,"sivec2"},{int,"int"},{sint,"sint"},{vec4,"vec4"},{svec4,"svec4"},{vec2,"vec2"},{vec2,"vec2"},{float,"float"},{float,"float"},{livec4,"livec4"},{ivec4,"ivec4"},{sivec4,"sivec4"},{livec2,"livec2"},{ivec2,"ivec2"},{sivec2,"sivec2"},{int32,"int32"},{int16,"int16"},{int16,"int16"},{luvec4,"luvec4"},{uvec4,"uvec4"},{suvec4,"suvec4"},{suvec4,"suvec4"},{luvec2,"luvec2"},{uvec2,"uvec2"},{suvec2,"suvec2"},{uint32,"uint32"},{uint32,"uint32"},{suint,"suint"},
// Images and colors
ONE(TY_INDEX_STR,COLORSFORM)
// Color formats
ONE(COL_VF_STR,rgba32f,rgba16f,rg32f,rg16f,r11f_g11f_b10f,r32f,r16f,rgba16,rgb10_a2,rgba8,rg16,rg8,r16,r8,rgba16_snorm,rgba8_snorm,rg16_snorm,rg8_snorm,r16_snorm,r8_snorm,rgba32i,rgba16i,rgba8i,rg32i,rg16i,rg8i,r32i,r16i,r8i,rgba32ui,rgba16ui,rgb10_a2ui,rgba8ui,rg32ui,rg16ui,rg8ui,r32ui,r16ui,r8ui)

};
*/



#define IMS_FROM_COLORS_FORM(im,colors_form) im<colors_form> \
ty_index_map< \
/* Vecs */ \
VECS,  \
TY_IMF(COLORSFORM), \
ONE(IMG_INSTS,COLORSFORM) \ // Images with all color fomat vecs

>
 type_ind({
ONE(TY_INDEX,VECS),
ONE(TY_INDEX,TY_IMF(COLORS_FORM),
ONE(TY_INDEX,ONE(IMG_INSTS,COLORSFORM))
});

// TODO cubemap based destruct 
void readFile(const std::string& filename , const uint32_t* c , int* code_size) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    size_t fileSize = static_cast<size_t>(file.tellg());
    (*code_size) = filesize;
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    c = reinterpret_cast<const uint32_t*>(buffer.data());
}

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
     
    auto* ubo  ;bool unib=false  ; uint16_t ubosize; bool dynsUbo;
    auto* ssbo  ;bool shab=false ;  uint16_t ssbosize; bool dynsSsbo;
    int code_size;
    const uint32_t** code; // SPIR-V Module

    std::vector<std::string> entry_points; // all entry points
    
};



class ShaderModule {
    shader_type shad_ty;
    size_t uni_size;
    size_t sssbo_size;
    auto ubo;
    auto ssbo;
    std::string codePath ; // SPIR-V module path;
    shaderModule shadmod;
    void read_code(){readFile(std::string(this->code),this->shadmod.code,&(this->shadmod.code_size); )};
    void bind(bool ubo_,bool ssbo_){
        if(ubo_){this->shadmod.unib=true ;this->shadmod.ubo = static_cast<void*>(&(this->unibuf));};
        if(ssbo_){this->shadmod.shab=true ;this->shadmod.ssbo = static_cast<void*>(&(this->unibuf));};
    };
    ShaderModule(shader_type st) : shad_ty(st);
};
// TODO make node editor with inout support


class kernModule : ShaderModule {
};
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
enum image_dim {
    one=0,
    two=1,
    three=2,
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
struct im_shaderModule : ShaderModule {

    image im;
    
};

/*
shaderModule
vertModule
fragModule
geomModule
tescModule
teseModule
compModule
taskModule
meshModule
rgenModule
rintModule
rahitModule
rchitModule
rmissModule
rcallModule*/
template <typename _ubo,typename _ssbo> 
struct  all_shmod : ShaderModule<shader_type::all,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  gr_shmod : ShaderModule<shader_type::gr,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  vert_shmod : ShaderModule<shader_type::vert,_ubo,_ssbo> ;
template <typename _ubo,typename _ssbo> 
struct  frag_shmod : ShaderModule<shader_type::frag,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  geom_shmod : ShaderModule<shader_type::geom,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  tesc_shmod : ShaderModule<shader_type::tesc,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  tese_shmod : ShaderModule<shader_type::tese,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  comp_shmod : ShaderModule<shader_type::comp,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  task_shmod : ShaderModule<shader_type::task,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  mesh_shmod : ShaderModule<shader_type::mesh,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  rgen_shmod : ShaderModule<shader_type::rgen,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  rint_shmod : ShaderModule<shader_type::rint,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  rahit_shmod : ShaderModule<shader_type::rahit,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  rchit_shmod : ShaderModule<shader_type::rchit,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  rmiss_shmod : ShaderModule<shader_type::rmiss,_ubo,_ssbo>;
template <typename _ubo,typename _ssbo> 
struct  rcall_shmod : ShaderModule<shader_type::rcall,_ubo,_ssbo>;


struct LoadDomainInfo{glm::ivec2 coords, int view_distance , void chunks_distance,int fog };

struct LoadWorldInfo{int index, glm::ivec3 coords };
void load_world_domain(glm::ivec3 coords, int view_distance, );


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


    template <uint length ,  typename T , glm::qualifier Q>
    class image {
        uint x ; 
        uint y  ; 
        std::mat<glm::vec<length,T ,Q> >  content ;  
        
        image(uint _x , uint _y) : x(_x) , y(_y){
            
        }
    };

    template <uint length , typename T , glm::prectision prec >
    class dyn_image : image<length, T , prec  > {

        virtual std::array<>
    };
    
   
    
    template<colorType ct, size_t x ,size_t y>
    using image = std::array<std::array<ct,x> ,y>;
    template <colorType ct, size_t x , size_t y >
    using rgba_static_arr = image<ct,x,y>;
    template <size_t frames , colorType ct, size_t x , size_t y>
    using rgba_dyn_arr = std::array<image<ct,x,y>,frames> ;
    template <colorType ct, size_t x , size_t y>
    using rgb_static_arr =  image<ct,x,y> ;
    template <colorType ct,size_t frames, size_t x , size_t y>
    using rgb_dyn_arr = std::array<image<ct,x,y>,frames> ;
    

    typedef std::vector<std::vector<rgba>>               rgba_static ; 
    typedef std::vector<std::vector<std::array<rgba>>>   rgba_dyn ;
    
    typedef std::vector<std::vector<rgb>>                rgb_static ; 
    typedef std::vector<std::vector<std::vector<rgb>>>   rgb_dyn ;
    
    union rgba_either {
        rgba_static_image static_img,
        rgba_dyn_image dyn_img
    };


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

    


#endif