typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   axisCount;
uint16   sharedTupleCount;
Offset32   sharedTuplesOffset;
uint16   glyphCount;
uint16   flags;
Offset32   glyphVariationDataArrayOffset;
Offset16 or Offset32*   glyphVariationDataOffsets;//[glyphCount + 1]
}gvar'/* header:*/;
ACQRES(gvar'/* header:*/){
one(majorVersion);
one(minorVersion);
one(axisCount);
one(sharedTupleCount);
one(sharedTuplesOffset);
one(glyphCount);
one(flags);
one(glyphVariationDataArrayOffset);
arr(glyphVariationDataOffsets, glyphCount + 1);
 };
USE_ACQRES(gvar'/* header:*/)

typedef struct {
Tuple*   sharedTuples;//[sharedTupleCount]
}Shared/* tuples array:*/;
ACQRES(Shared/* tuples array:*/){
arr(sharedTuples, sharedTupleCount);
 };
USE_ACQRES(Shared/* tuples array:*/)

typedef struct {
uint16   tupleVariationCount;
Offset16   dataOffset;
TupleVariationHeader*   tupleVariationHeaders;//[tupleCount]
}GlyphVariationData/* header:*/;
ACQRES(GlyphVariationData/* header:*/){
one(tupleVariationCount);
one(dataOffset);
arr(tupleVariationHeaders, tupleCount);
 };
USE_ACQRES(GlyphVariationData/* header:*/)

