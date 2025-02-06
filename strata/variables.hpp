#include <glm/glm.hpp>
namespace variable {
late <typename T>
struct variable {
    std::string name;
    std::string tyname ;
    T data;
    virtual void widget();
};
template <typename T>
struct mod_var : variable<T>{

};
template <typename T>
struct res_var : variable<T> {

};
template <typename T>
struct ev_var {

};


// Sections :
//vert,
//frag,
//geom,

//tesc,
//tese,
//comp,
//task,
//mesh,
//rgen,
//rint,
//rahit,
//rchit,
//rmiss,
//rcall,




//    vert:
struct point  {
    glm::vec3 pt ;
};
struct vertex  {
    glm::vec3 pt ; 
};
template <size_t length,glm::qualifier Q>
struct vert_gen : vertex {
    glm::vec<length,float,Q  > pt; 

};

struct motion_add {
    glm::vec4 add ;
    uint bone;
};
struct motion_mul {
    glm::vec4 mul;
    uint bone;
};
using var_motion_add = variable<motion_add> ; 
using var_motion_mul = variable<motion_mul> ;

struct animation_add {
    glm::vec4 polynom ; 
    uint bone; 
};
struct animation_mul {
    glm::vec4 polynom ;
    uint bone; 
};



std::tuple<> vert_variables ;

//    frag:
using fragcolor = variable<> ;
//    geom:
//    tesc:
//    tese:
//    comp:
//    task:
//    mesh:
//    rgen:
//    rint:
//    rahit:
//    rchit:
//    rmiss:
//    rcall:




template <typename T>
class variable_widget : widget{
    public:
    using ty = T; 
    ty data;
} ;


template <typename T , size_t r,  size_t c,glm::qualifier q>
class variable_mat : variable_widget<glm::mat<T,r,c,q>> {
    
    void draw(){
    if constexpr(std::is_same<T,float>::value){

    }   ; 


}; 
};
};