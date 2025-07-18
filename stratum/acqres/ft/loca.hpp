#ifndef FTLOCA_HPP
#define FTLOCA_HPP
#include "glyf.hpp"
#include "head.hpp"

// indexed by glyphID
typedef struct {
Offset16*   offsets;//[numGlyphs + 1] // offset[i]=Offset/2

}Short;
ACQRES(Short){size_t s = _numGlyphs+1;
arr(f.offsets,s);

 };
USE_ACQRES(Short)

typedef struct {
Offset32*   offsets;//[numGlyphs + 1]

}Long;
ACQRES(Long){size_t s =  _numGlyphs+1;
arr(f.offsets,s);
 };
USE_ACQRES(Long)

typedef struct {
    
    union {
        Short s;
        Long l;
    }f;

}loca;
ACQRES(loca){
    switch(_indexToLocFormat){
        case 0 : {one(f.f.s);}
        case 1 : {one(f.f.l);}
    }
}
#endif