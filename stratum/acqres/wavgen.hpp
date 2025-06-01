// wfg
#include <cstddef>
#include <stratum/acqres/wav.hpp>  
// #include <glm/glm.hpp>
// typedef glm::ivec4 
// typedef glm::imat4 filt
enum headers {
    head=0,
    filt=1 ,
    
    synth=2,

};
struct head {
    int8_t headNo ;
    int8_t* headers;
 

};
typedef struct  {
    
}filt;
typedef struct   {
    int8_t filtsize; 
    int8_t* filt; 
    
    int32_t trfiSize; 
    int8_t* trfi ;
}synth;

typedef struct {
    int8_t threadno ;
    int16_t size; 
    int16_t** vibe; //[threadno][size] ;  
}wfgen;
typedef void (*trfi)(synth* , wavh* , wfgen* )
void codeParse(synth* s, wavh* meta, wfgen* synthcall){
    int8_t trfi[s->trfiSize]= s->trfi ;

};