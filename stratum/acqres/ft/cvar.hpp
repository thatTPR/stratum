typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   tupleVariationCount;
Offset16   dataOffset;
TupleVariationHeader*   tupleVariationHeaders;//[tupleVariationCount]
}cvar'/* table header:*/;
ACQRES(cvar'/* table header:*/){
one(majorVersion);
one(minorVersion);
one(tupleVariationCount);
one(dataOffset);
arr(tupleVariationHeaders, tupleVariationCount);
 };
USE_ACQRES(cvar'/* table header:*/)

