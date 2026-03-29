#ifndef CVAR_HPP
#define CVAR_HPP
#include "_fontVarCommon.hpp"
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   tupleVariationCount;
Offset16   dataOffset;
TupleVariationHeader*   tupleVariationHeaders;//[tupleVariationCount]
}cvar /* table header:*/;
ACQRES(cvar/* table header:*/){
one((f.majorVersion));
one((f.minorVersion));
one((f.tupleVariationCount));
one((f.dataOffset));
arr(f.tupleVariationHeaders, f.tupleVariationCount);
 };
USE_ACQRES(cvar/* table header:*/)


#endif