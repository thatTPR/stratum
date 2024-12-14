
#define ONE(macro, f) \
macro(f) 

#define ONE(macro, f,s) \
macro(f) \
macro(s) 
#define ONE(macro, first,...) \ 
macro(first) \
ONE(macro,__VA_ARGS__) 


#define FUNCS_EV(type) \



#define FUNCS_RES(type) \



#define EVENT_REFS(type) \
#define EVENT_REFS##type  \
using ##type_pin_ev=pin<type>; \
using ##type_pinref_ev=pinref<type>; \
using ##type_pinptr_ev=pinptr<type>;\
FUNCS_EV(type) 

#define RES_REFS(type) \
#define RES_REFS##type \
using ##type_pin_res=event_pin<type>; \
using ##type_pinref_res=event_pinref<type>; \
using ##type_pinptr_res=event_pinptr<type>;\
FUNC_RES(type) 


#define EVENT(type) \
#define EVENT_##type  \
using ##type_pin_ev=pin<type>; \
FUNCS_EV(type) 

#define RES(type) \
#define RES_##type \
using ##type_pin_res=event_pin<type>; \
FUNC_RES(type) 




#define PINS(macro,...) \ 
ONE(macro,__VA_ARGS__ ) \





PINS_EVENT(...) PINS(EVENT , __ARGV__ )
PINS_RES(...) PINS(RES , __ARGV__)

#define GET_REF_EV(ty)  ##ty_pinref_ev
#define GET_REF_RES(ty) ##ty_pinref_res
#define GET_PTR_EV(ty)  ##ty_pinptr_ev
#define GET_PTR_RES(ty) ##ty_pinptr_res
#define GET_EV(ty)  ##ty_pin_ev
#define GET_RES(ty) ##ty_pin_res

#define F_REF_EV(ty)    ##ty_pinref_ev
#define F_REF_RES(ty)   ##ty_pinref_res
#define F_PTR_EV(ty)    ##ty_pinptr_ev
#define F_PTR_RES(ty)   ##ty_pinptr_res
#define F_VAL_EV(ty)    ##ty_pin_ev
#define F_VAL_RES(ty)   ##ty_pin_res

#include "../../petri/all.hpp"
PINS_EVENT(bvec2,bvec3,bvec4,dvec2,dvec3,dvec4,ldvec2,ldvec3,ldvec4,uvec2,uvec3,uvec4,ivec2,ivec3,ivec4,luvec2,luvec3,luvec4,livec2,livec3,livec4,vec2,vec3,vec4,bmat2x2,bmat2x3,bmat2x4,bmat3x2,bmat3x3,bmat3x4,bmat4x2,bmat4x3,bmat4x4,dmat2x2,dmat2x3,dmat2x4,dmat3x2,dmat3x3,dmat3x4,dmat4x2,dmat4x3,dmat4x4,umat2x2,umat2x3,umat2x4,umat3x2,umat3x3,umat3x4,umat4x2,umat4x3,umat4x4,imat2x2,imat2x3,imat2x4,imat3x2,imat3x3,imat3x4,imat4x2,imat4x3,imat4x4,fmat2x2,fmat2x3,fmat2x4,fmat3x2,fmat3x3,fmat3x4,fmat4x2,fmat4x3,fmat4x4,ldmat2x2,ldmat2x3,ldmat2x4,ldmat3x2,ldmat3x3,ldmat3x4,ldmat4x2,ldmat4x3,ldmat4x4,lumat2x2,lumat2x3,lumat2x4,lumat3x2,lumat3x3,lumat3x4,lumat4x2,lumat4x3,lumat4x4,limat2x2,limat2x3,limat2x4,limat3x2,limat3x3,limat3x4,limat4x2,limat4x3,limat4x4)
PINS_RES()


#define IN_DEF(a) ##a in_##a;
#define IN_HANDLE(a) in_##a.handle();
#define IN_ARG(a) ##a i_##a,
#define IN_SETF(a,set) this->in_##a=set ; 
#define IN_SET_ARG(a,arg) this->in_##a=i_##a;


#define PIN_IN(pin) 
IN_DEF(pin) \
void in_set(IN_ARG(pin)){ IN_SET(pin)};\
void in_handle(){IN_HANDLE(pin)};\

#define OUT_DEF(a) ##a out_##a;
#define OUT_HANDLE(a) out_##a.handle();
#define OUT_ARG(a) ##a o_##a,
#define OUT_SETF(a,set) this->out_##a=set ; 
#define OUT_SET(a) this->out_##a=o_##a; 



