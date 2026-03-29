#ifndef GVAR_HPP
#define GVAR_HPP
#include "_fontVarCommon.hpp"
uint16 _sharedTupleCount;
typedef struct {
Tuple*   sharedTuples;//[sharedTupleCount]
}Sharedtuples;
ACQRES(Sharedtuples){
arr(f.sharedTuples, _sharedTupleCount);
 };
USE_ACQRES(Sharedtuples)

typedef struct {
uint16   tupleVariationCount;
Offset16   dataOffset;
TupleVariationHeader*   tupleVariationHeaders;//[tupleCount]
}GlyphVariationData;
ACQRES(GlyphVariationData){
one((f.tupleVariationCount));
one((f.dataOffset));
arr(f.tupleVariationHeaders, f.tupleCount);
 };
USE_ACQRES(GlyphVariationData)

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   axisCount;
uint16   sharedTupleCount;
Offset32   sharedTuplesOffset;
uint16   glyphCount;
uint16   flags;
Offset32   glyphVariationDataArrayOffset;
union {
    Offset16* _16;
    Offset32* _32;
}glyphVariationDataOffsets;
  

GlyphVariationData* glyphVarData;
}gvar;
ACQRES(gvar){
one(f.majorVersion);
one(f.minorVersion);
one(f.axisCount);
one(f.sharedTupleCount);
_sharedTuleCount = f.sharedTupleCount;
one(f.sharedTuplesOffset);
one(f.glyphCount);
one(f.flags);
one(f.glyphVariationDataArrayOffset);
uint16 fvardoffs = f.glyphCount + 1;
if(f.flags & 0x1){arr(f.glyphVariationDataOffsets._32, fvardoffs);
offmany(f.glyphVarData,f.glyphVariationDataOffsets,fvardoffs);}
else {arr(f.glyphVariationDataOffsets._16, fvardoffs);
    for(int i=0; i<fvardoffs;i++){
        Offset32 off = f.glyphVariationDataOffsets[i] * 2;
        offone(f.glyphVarData[i],off);
        f.glyphVariationDataOffsets[i] = off/2; 
    }


};
USE_ACQRES(gvar)
#endif