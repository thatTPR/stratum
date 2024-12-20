#include <fstream>
#include <petri/vecs.hpp>
#include <petri/vects.hpp>
#include <lib/gltf.h>
#include <glm/glm.hpp>


template<typename glmvec>
std::vector<tingltf::Value> getvecgltfv(glmvec s){
    std::vector<tinygltf::Value> array ;
    size_t constexpr len = glmvec::length();
    array.resize(len);
    std::vector<tinygltf::Value> array = v.Get<tinygltf::Value::Array>();
    array[0] = tinygltf::Value(x.x); 
    array[1] = tinygltf::Value(s.y);
    if constexpr (len<3){return res;};
    array[2] = tinygltf::Value(s.z)
    if constexpr (len<4){return res;};
    array[4] = tinygltf::Value(s.w);
    return array;
    };
    
}; 
template<typename glmvec>
glmvec getvec(tinygltf::Value v){
    glmvec res;
    constexpr size_t len = glmvec::length();
    std::vector<tinygltf::Value> array = v.Get<tinygltf::Value::Array>();
    if constexpr (std::is_same_v<glmvec::value_type, float>) {
    rex.x = array[0].GetNumberAsDouble(); 
    res.y= array[1].GetNumberAsDouble()
    if constexpr (len<3){return res;};
    res.z = array[2].GetNumberAsDouble();
    if constexpr (len<4){return res;};
    res.w = array[3].GetNumberAsDouble();
    return res;
    } else if constexpr (std::is_same_v<glmvec::valuetype, double>) {
    rex.x = array[0].GetNumberAsDouble(); 
    res.y= array[1].GetNumberAsDouble()
    if constexpr (len<3){return res;};
    res.z = array[2].GetNumberAsDouble();
    if constexpr (len<4){return res;};
    res.w = array[3].GetNumberAsDouble();
    return res;
    } else if constexpr (std::is_same_v<glmvec::value_type, int>) {
    rex.x = array[0].GetNumberAsInt(); 
    res.y= array[1].GetNumberAsInt()
    if constexpr (len<3){return res;};
    res.z = array[2].GetNumberAsInt();
    if constexpr (len<4){return res;};
    res.w = array[3].GetNumberAsInt();
    return res;
    };

 
};
template <typename glmmat>
std::vector<tinygltf::Value> getmatgltfv(gmlmmat s ){
    constexpr size_t  rows = glmmat::row_type::length();
    constexpr size_t  cols = glmmat::col_type::length();
    std::vector<tinygltf::Value> array;
    array.resize(rows);
    array[0]= tinygltf::Value(getvecgltfv<glmmat::rowtype>(s.x)); 
    array[1]= tinygltf::Value(getvecgltfv<glmmat::rowtype>(s.y));
    if constexpr (row<3){return array;};
    std::vector<tinygltf::Value> arrayz;
    array[2] =tinygltf::Value( getvecgltfv<glmmat::rowtype>(s.z));
    if constexpr (row<4){return array;};
    std::vector<tinygltf::Value> arrayw;
    array[3] = tinygltf::Value(getvecgltfv<glmmat::rowtype>(s.w));
    return array;
};
template<typename glmmat>
glmmat getmat(tinygltf::Value v){
    glmmat res;

   
    std::vector<tinygltf::Value> array = v.Get<tinygltf::Value::Array>();
    if constexpr (std::is_same_v<glmmat::value_type, float>) {
    rex.x = getv<glmmat::rowtype>(array[0]); 
    res.y= getv<glmmat::rowtype>(array[1]);
    if constexpr (row<3){return res;};
    res.z = getv<glmmat::rowtype>(array[2]);
    if constexpr (row<4){return res;};
    res.w = getv<glmmat::rowtype>(array[3]);
    return res;
    } else if constexpr (std::is_same_v<glmmat::valuetype, double>) {
    rex.x = getv<glmmat::rowtype>(array[0]); 
    res.y= getv<glmmat::rowtype>(array[1]);
    if constexpr (row<3){return res;};
    res.z = getv<glmmat::rowtype>(array[2]);
    if constexpr (row<4){return res;};
    res.w = getv<glmmat::rowtype>(array[3]);
    return res;
    } else if constexpr (std::is_same_v<glmmat::value_type, int>) {
    rex.x = getv<glmmat::rowtype>(array[0]); 
    res.y= getv<glmmat::rowtype>(array[1]);
    if constexpr (row<3){return res;};
    res.z = getv<glmmat::rowtype>(array[2]);
    if constexpr (row<4){return res;};
    res.w = getv<glmmat::rowtype>(array[3]);
    return res;
    };

};



class acqres {
    // strct s ;
    vect<ivec4> ranges ;
    vect<ivec2> type_indices ;
    virtual void read();
    virtual void feed(ivec4 range){

    };

};
class acqres_prop {
    public:
    std::string mimeType="STRATA_default=mime";
    std::vector<std::string> extensions;
    std::vector<std::string> _get_ext(){return this->extensions;}
};

#ifdef STRATA_CAPABILITY_VG2
#include "vg2.hpp"
#endif
