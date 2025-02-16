#include <glm/glm.hpp>
#include <vector>
namespace variable {
    enum varty {
        res=0,
        mod=1,
        ev=2
    };  
    template <typename T >
struct variable {
    public:
    varty ty ;
     const std::string tyname ; // Names
    std::string name;
    size_t s;
    T data; 
     widgettemp<T> data;
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
typedef  glm::vec3  point ;
template<> struct variable<point>  {
    vert ty ; 
     const std::string tyname = "point" ;
     std::string name;
     size_t s ; 
    point data;
    widget<point> data; 
};

struct vertex  {
    glm::vec3 pt ; 
};

template <size_t length,glm::qualifier Q>
struct vert_gen : vertex {
    glm::vec<length,float,Q  > pt; 

};

using 
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
    glm::mat4 polynom4flt ; 
    uint bone; 
};
struct animation_mul {
    glm::mat4 polynom4flt ;
    uint bone; 
};

struct kinematic_add {
    uint bone ;
     
};

std::tuple<> vert_variables ;

//    frag:
using fragcolor = variable<> ;

struct color {

};
struct filter{

};
//    geom:
struct primConvert {
    
};


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