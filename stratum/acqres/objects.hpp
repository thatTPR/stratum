#pragma once
#include "source.hpp"
#include "petri/vects.hpp"
#include "gltf.hpp"


class image : public property<true,true> , public objnar{
    static const std::string name = "image";
    const bool arr_val=true ; 
    const bool obj_val=true ; 
    const gltfval val = val::obj ;

};
class sampler : public property , public objnar {
    static const std::string name = "sampler";
};
class texture : public property<true,true> , public objnar{
    class globj : public property<true,true,> {
        image* _image;
        sampler* _sampler;
    };
    globj obj;
    virtual auto props()override{
        PROPERTS(image,sampler)
    };
    


};
class material : public property , public objnar{
    texture* tex;
};
class buffer : public property , public objnar{
    int buffer;
};
class buffer_view : public property , public objnar{
    public:
    vect<buffer*> buf;
    vect<image*> buf; 
    const bool arr_val=false ; 
    const bool obj_val=false ; 
    const gltfval = gltfval::intgr;
    void props(bool names, size_t pos , std::ifstream* f, std::string s)){
        size_t p;
    };
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


