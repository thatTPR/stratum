#pragma once
#include "source.hpp"
#include "petri/vects.hpp"
#include "gltf.hpp"


class image : public property , public objnar{
    static const std::string name = "image";

};
class sampler : public property , public objnar {
    static const std::string name = "sampler";
};
class texture : public property , public objnar{
    image* _image;
    sampler* _sampler;
    virtual void props(){
        size_t p;
        PROPS(image)
        PROPS(sampler)
    };
    // void parse_obj(std::ifstream* f,size_t pos,bool names){

    // };  
    // void parse_arr(std::ifstream* f,size_t pos,bool names){
        
    //     for(int i = 0)
    // };


};
class material : public property , public objnar{
    texture* tex;
};
class buffer : public property , public objnar{
    int buffer;
};
class buffer_view : public property , public objnar{
    vect<buffer*> buf;
    vect<image*> buf; 
};

class accessor : public property , public objnar{

    buffer_views buffer_view;
    
};
class mesh : public property , public objnar{
public:
    vect<mesh> meshes;
    vect<accssors> meshes;
    vect<material> materials;
    
};
class skin : public property , public objnar{
    vect<accessor> accessors ;
};
class camera : public property , public objnar{

};

class node : public property , public objnar{
    vect<node*> nodes;
    vect<skin*> skins ;
    vect<camera*> cameras ;
    vect<mesh*>  meshes;
};
class animation : public property , public objnar{
    vect<accessor> accessors;

};
class scene : public property , public objnar{
    vect<node*> nodes;
};




class shader_module {

};