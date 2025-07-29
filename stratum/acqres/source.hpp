#include <lib/gltf.h>
#include <glm/glm.hpp>



template<size_t s,typename T, glm::qualifier Q>
std::vector<tingltf::Value> getvecgltfv(glm::vec<s,T,Q> s){
    using glmvec=glm::vec<s,T,Q>
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
    


template<size_t s, typename T , glm::qualifier Q>
glm::vec<s,T,Q> getvec(tinygltf::Value v){
    using glmvec = glm::vec<s,T,Q>
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
template <size_t r, size_t c, typename T, glm::qualifier Q>
std::vector<tinygltf::Value> getmatgltfv(glm::mat<r,c,T,Q> s ){
    using glmmat=glm::mat<r,c,T,Q>;
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
template <size_t r, size_t c, typename T, glm::qualifier Q>
glmmat getmat(tinygltf::Value v){
    using glmmat =glm::mat<r,c,T,Q>;glmmat res;
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

#include <strata/petri/meta.hpp>
template<typename T>
tinygltf::Value getgltfv(T s){
    if constexpr(is_glmvec<T>::value){
if constexpr( is_glmmat<T>::value){
        return getmatgltfv(v);
    };
        return getvecgltfv(v);
    };
    return getgltfValue<T>(s);
};
template <typename T>
T getv(tinygltf::Value v){
    if constexpr(std::is_same<T,int>::value){
        return v.GetNumberAsInt();
    } ;
    if constexpr(std::is_same<T,double>::value){
        return v.GetNumberAsDouble();
    } ;
    if constexpr(std::is_same<T,float>::value){
        return static_cast<float>(v.GetNumberAsDouble());
    } ;
    if constexpr(std::is_same<T,std::string>){
        return v.Get<std::string>();
    };
    if constexpr( has_value_type<T>::value &&  has_bool_type<T>::value ){
    if constexpr( has_col<T>::value){
        return getmatv(v);
    };
        return getvecv(v);
    };
    getValue<T>(v);
    
};


class acqres {
    // strct s ;
    vect<ivec4> ranges ;
    vect<ivec2> type_indices ;
    virtual void read();
    virtual void feed(ivec4 range){

    };

};
class prop {
    virtual std::vector<tinygltf::Value> getgltf();
    virtual prop get(tinygltf::Value v);
    virtual auto getBasic();
    virtual auto getPipelineModule(); // Gets all alignable modules for shader use
};
class acqres_prop : {
    public:
    std::string mimeType="STRATA_default=mime";
    std::vector<std::string> extensions;
    std::vector<std::string> _get_ext(){return this->extensions;}
};

#ifdef STRATA_CAPABILITY_VG2
#include "vg2.hpp"
#endif
