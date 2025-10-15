#ifndef STMSL_INTRINSICS_HPP
#define STMSL_INTRINSICS_HPP
#include "ast.hpp"
#include <petri/templates.hpp>
namespace stmtsl {

struct decl {
    ty dty;
    type t;    
std::string TypeID(){std::string n;
    if constexpr(t.tempState == temp::meta){
        n+="<";
        for(param<q> it : t.prms){
            n+=it.str();n+=",";        }
        n[n.length()-1]=">";
    }
    switch(t.t){
case type<q>::ty::Buffer : {n="Buffer_";n+=name;
    for(type it : t.ts){n+=TypeID(it);}
}
case type<q>::ty::strct : {n="Strct_";n+=name;
    for(type it : t.ts){n+=TypeID(it);}
}
case type<q>::ty::arr : {n="Arr";n+=name;
    n+=dims[0];
    for(size_t i=1;i<n.dim;i++){n+="x";n+=dims[i];}
    break;
}
case type<q>::ty::Image2D : {n="Image2D";break;}
case type<q>::ty::Image3D : {n="Image3D";break;}
case type<q>::ty::Sampler : {n="Sampler";break;}
case type<q>::ty::Void : {n="Void";break;}
case type<q>::ty::Float : {n="Float";break;}
case type<q>::ty::Int : {n="Int";break;}
case type<q>::ty::Uint : {n="Uint";break;}
case type<q>::ty::Bool : {n="Bool";break;}
case type<q>::ty::Vec : {n="Vec";n+=dims[0];break;}
case type<q>::ty::Mat : {n="Mat";n+=dims[0];n+=dims[1];break;}
case type<q>::ty::Imat : {n="Imat";n+=dims[0];break;}
case type<q>::ty::Ivec : {n="Ivec";n+=dims[0];n+=dims[1];break;}
case type<q>::ty::Uvec : {n="Uvec";n+=dims[0];break;}
case type<q>::ty::Umat : {n="Umat";n+=dims[0];n+=dims[1];break;}
case type<q>::ty::Bvec : {n="Bvec";n+=dims[0];break;}
case type<q>::ty::Bmat : {n="Bmat";n+=dims[0];n+=dims[1];break;}
}
return n;
}
    std::string name;
    lex ltok; 
    size_t fpos;size_t ln,col;
    decl(lex l ) : name(l.u.name),fpos(l.filePos),ln(l.ln) ,col(l.col) :
} ;

const type<temp::inst> _Void("void",type::prim::Void);
const type<temp::inst> _Float("Float",type::prim::Float);
const type<temp::inst> _UInt("UInt",type::prim::Uint);
const type<temp::inst> _Int("Int",type::prim::Int);
const type<temp::inst> _Bool("Bool",type::prim::Bool);


type<temp::meta> Vec("Vec",type::ty::vec,);
type<temp::meta> Mat("Mat",type::ty::mat,);

using UsingInst = typename stmt<temp::inst>::StmtUsing;
const type<temp::inst> vec2("vec2",Vec,{&_Float,2});
const type<temp::inst> vec3("vec3",Vec,{&_Float,3});
const type<temp::inst> vec4("vec4",Vec,{&_Float,4});
const type<temp::inst> ivec2("ivec2",Vec,{&_Int,2});
const type<temp::inst> ivec3("ivec3",Vec,{&_Int,3});
const type<temp::inst> ivec4("ivec4",Vec,{&_Int,4});
const type<temp::inst> uvec2("uvec2",Vec,{&_UInt,2});
const type<temp::inst> uvec3("uvec3",Vec,{&_UInt,3});
const type<temp::inst> uvec4("uvec4",Vec,{&_UInt,4});
const type<temp::inst> ivec2("ivec2",Vec,{&_Int,2});
const type<temp::inst> ivec3("ivec3",Vec,{&_Int,3});
const type<temp::inst> ivec4("ivec4",Vec,{&_Int,4});
const type<temp::inst> bvec2("bvec2",Vec,{&_Bool,2});
const type<temp::inst> bvec3("bvec3",Vec,{&_Bool,3});
const type<temp::inst> bvec4("bvec4",Vec,{&_Bool,4});
const type<temp::inst> mat2("vec2",Mat,{&_Float,2});
const type<temp::inst> mat3("vec3",Mat,{&_Float,3});
const type<temp::inst> mat4("vec4",Mat,{&_Float,4});
const type<temp::inst> imat2("ivec2",Mat,{&_Int,2});
const type<temp::inst> imat3("ivec3",Mat,{&_Int,3});
const type<temp::inst> imat4("ivec4",Mat,{&_Int,4});
const type<temp::inst> umat2("uvec2",Mat,{&_UInt,2});
const type<temp::inst> umat3("uvec3",Mat,{&_UInt,3});
const type<temp::inst> umat4("uvec4",Mat,{&_UInt,4});
const type<temp::inst> imat2("ivec2",Mat,{&_Int,2});
const type<temp::inst> imat3("ivec3",Mat,{&_Int,3});
const type<temp::inst> imat4("ivec4",Mat,{&_Int,4});
const type<temp::inst> bmat2("bvec2",Mat,{&_Bool,2});
const type<temp::inst> bmat3("bvec3",Mat,{&_Bool,3});
const type<temp::inst> bmat4("bvec4",Mat,{&_Bool,4});
const type<temp::inst> mat2x2("mat2x2",Mat,{&_Float,2,2});
const type<temp::inst> mat3x2("mat3x2",Mat,{&_Float,3,2});
const type<temp::inst> mat4x2("mat4x2",Mat,{&_Float,4,2});
const type<temp::inst> imat2x2("imat2x2",Mat,{&_Int,2,2});
const type<temp::inst> imat3x2("imat3x2",Mat,{&_Int,3,2});
const type<temp::inst> imat4x2("imat4x2",Mat,{&_Int,4,2});
const type<temp::inst> umat2x2("umat2x2",Mat,{&_UInt,2,2});
const type<temp::inst> umat3x2("umat3x2",Mat,{&_UInt,3,2});
const type<temp::inst> umat4x2("umat4x2",Mat,{&_UInt,4,2});
const type<temp::inst> imat2x2("imat2x2",Mat,{&_Int,2,2});
const type<temp::inst> imat3x2("imat3x2",Mat,{&_Int,3,2});
const type<temp::inst> imat4x2("imat4x2",Mat,{&_Int,4,2});
const type<temp::inst> bmat2x2("bmat2x2",Mat,{&_Bool,2,2});
const type<temp::inst> bmat3x2("bmat3x2",Mat,{&_Bool,3,2});
const type<temp::inst> bmat4x2("bmat4x2",Mat,{&_Bool,4,2});//
const type<temp::inst> mat2x3("vec2x3",Mat,{&_Float,2,3});
const type<temp::inst> mat3x3("vec3x3",Mat,{&_Float,3,3});
const type<temp::inst> mat4x3("vec4x3",Mat,{&_Float,4,3});
const type<temp::inst> imat2x3("ivec2x3",Mat,{&_Int,2,3});
const type<temp::inst> imat3x3("ivec3x3",Mat,{&_Int,3,3});
const type<temp::inst> imat4x3("ivec4x3",Mat,{&_Int,4,3});
const type<temp::inst> umat2x3("uvec2x3",Mat,{&_UInt,2,3});
const type<temp::inst> umat3x3("uvec3x3",Mat,{&_UInt,3,3});
const type<temp::inst> umat4x3("uvec4x3",Mat,{&_UInt,4,3});
const type<temp::inst> imat2x3("ivec2x3",Mat,{&_Int,2,3});
const type<temp::inst> imat3x3("ivec3x3",Mat,{&_Int,3,3});
const type<temp::inst> imat4x3("ivec4x3",Mat,{&_Int,4,3});
const type<temp::inst> bmat2x3("bvec2x3",Mat,{&_Bool,2,3});
const type<temp::inst> bmat3x3("bvec3x3",Mat,{&_Bool,3,3});
const type<temp::inst> bmat4x3("bvec4x3",Mat,{&_Bool,4,3});//
const type<temp::inst> mat2x4("vec2x4",Mat,{&_Float,2,4});
const type<temp::inst> mat3x4("vec3x4",Mat,{&_Float,3,4});
const type<temp::inst> mat4x4("vec4x4",Mat,{&_Float,4,4});
const type<temp::inst> imat2x4("ivec2x4",Mat,{&_Int,2,4});
const type<temp::inst> imat3x4("ivec3x4",Mat,{&_Int,3,4});
const type<temp::inst> imat4x4("ivec4x4",Mat,{&_Int,4,4});
const type<temp::inst> umat2x4("uvec2x4",Mat,{&_UInt,2,4});
const type<temp::inst> umat3x4("uvec3x4",Mat,{&_UInt,3,4});
const type<temp::inst> umat4x4("uvec4x4",Mat,{&_UInt,4,4});
const type<temp::inst> imat2x4("ivec2x4",Mat,{&_Int,2,4});
const type<temp::inst> imat3x4("ivec3x4",Mat,{&_Int,3,4});
const type<temp::inst> imat4x4("ivec4x4",Mat,{&_Int,4,4});
const type<temp::inst> bmat2x4("bvec2x4",Mat,{&_Bool,2,4});
const type<temp::inst> bmat3x4("bvec3x4",Mat,{&_Bool,3,4});
const type<temp::inst> bmat4x4("bvec4x4",Mat,{&_Bool,4,4});

#define INTRINSIC_TYS vec2,vec3,vec4,ivec2,ivec3,ivec4,uvec2,uvec3,uvec4,ivec2,ivec3,ivec4,bvec2,bvec3,bvec4,mat2,mat3,mat4,imat2,imat3,imat4,umat2,umat3,umat4,imat2,imat3,imat4,bmat2,bmat3,bmat4,mat2x2,mat3x2,mat4x2,imat2x2,imat3x2,imat4x2,umat2x2,umat3x2,umat4x2,imat2x2,imat3x2,imat4x2,bmat2x2,bmat3x2,bmat4x2,mat2x3,mat3x3,mat4x3,imat2x3,imat3x3,imat4x3,umat2x3,umat3x3,umat4x3,imat2x3,imat3x3,imat4x3,bmat2x3,bmat3x3,bmat4x3,mat2x4,mat3x4,mat4x4,imat2x4,imat3x4,imat4x4,umat2x4,umat3x4,umat4x4,imat2x4,imat3x4,imat4x4,bmat2x4,bmat3x4,bmat4x4
 
void addTypes(shad_stage::stage st){

};

};
#endif