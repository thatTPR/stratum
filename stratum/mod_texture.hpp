#ifndef MOD_TEXTURE_HPP
#define MOD_TEXUTRE_HPP
#include "mod_util.hpp"
#include "mod_lod.hpp"
#include "mod_image.hpp"
namespace mod {

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
}
#endif