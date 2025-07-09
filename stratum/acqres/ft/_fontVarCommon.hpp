#ifndef FT_FONTVARCOMMON_HPP
#define FT_FONTVARCOMMON_HPP
uint16 _axisCount ;
typedef struct {
F2DOT14*   coordinates;//[axisCount]
}Tuple;
ACQRES(Tuple){
arr(f.coordinates, _axisCount); // Specified in fvar
 };
USE_ACQRES(Tuple/* record:*/)

typedef struct {
uint16   tupleVariationCount;
Offset16   dataOffset;
TupleVariationHeader*   tupleVariationHeaders;//[tupleVariationCount]
}GlyphVariationData/* header:*/;
ACQRES(GlyphVariationData/* header:*/){
one(f.tupleVariationCount);
one(f.dataOffset);
arr(f.tupleVariationHeaders, f.tupleVariationCount);
 };
USE_ACQRES(GlyphVariationData/* header:*/)



typedef struct {
uint16   variationDataSize;
uint16   tupleIndex;
Tuple   peakTuple;
Tuple   intermediateStartTuple;
Tuple   intermediateEndTuple;
}TupleVariationHeader;
enum tupleIndex{
   EMBEDDED_PEAK_TUPLE = 0x8000,
   INTERMEDIATE_REGION = 0x4000,
   PRIVATE_POINT_NUMBERS = 0x2000,
   Reserved = 0x1000,
   TUPLE_INDEX_MASK = 0x0FFF
};
typedef struct {
// uint8   format;
uint8   entryFormat;
uint16   mapCount;
uint8*   mapData;//[variable]
}DeltaSetIndexMapf0;
ACQRES(DeltaSetIndexMapf0){
one(f.format);
one(f.entryFormat);
one(f.mapCount);
arr(f.mapData, f.variable);
 };
USE_ACQRES(DeltaSetIndexMapf0/* format 0:*/)
#include "cvar.hpp"
typedef struct {
// uint8   format;
uint8   entryFormat;
uint32   mapCount;
uint8*   mapData;//[variable]
}DeltaSetIndexMapf1;
ACQRES(DeltaSetIndexMapf1){
one(f.format);
one(f.entryFormat);
one(f.mapCount);
arr(f.mapData, f.variable);
 };
USE_ACQRES(DeltaSetIndexMapf1)

typedef struct {
   uint8 format;
   union {
      DeltaSetIndexMapf0 f0;     
      DeltaSetIndexMapf0 f1;     
   }u;

}DeltaSetIndexMap ;
ACQRES(DeltaSetIndexMap){
   one(f.format);
   switch(f.format){
      case 0:{one(f.u.f0);}
      case 1:{one(f.u.f1);}
   }
};
typedef struct {
0x0F   INNER_INDEX_BIT_COUNT_MASK;
0x30   MAP_ENTRY_SIZE_MASK;
0xC0   Reserved;
}entryFormat/* field masks:*/;
typedef struct {
uint16   axisCount;
uint16   regionCount;
VariationRegion*   variationRegions;//[regionCount]
}VariationRegionList;
ACQRES(VariationRegionList:){
one(f.axisCount);
_axisCount = f.axisCount;
one(f.regionCount);
arr(f.variationRegions, f.regionCount);
 };
USE_ACQRES(VariationRegionList)

typedef struct {
RegionAxisCoordinates*   regionAxes;//[axisCount]
}VariationRegion/* record:*/;
ACQRES(VariationRegion/* record:*/){
arr(f.regionAxes, _axisCount);
 };
USE_ACQRES(VariationRegion/* record:*/)

typedef struct {
F2DOT14   startCoord;
F2DOT14   peakCoord;
F2DOT14   endCoord;
}RegionAxisCoordinates;

typedef struct {
uint16   itemCount;
uint16   wordDeltaCount;
uint16   regionIndexCount;
uint16*   regionIndexes;//[regionIndexCount]
DeltaSet*   deltaSets;//[itemCount]
}ItemVariationData;
ACQRES(ItemVariationData){
one(f.itemCount);
one(f.wordDeltaCount);_worldDeltaCount = f.worldDeltaCount;
one(f.regionIndexCount);_regionIndexCount = f.regionIndexCount;
arr(f.regionIndexes, f.regionIndexCount);

arr(f.deltaSets, f.itemCount);
 };
USE_ACQRES(ItemVariationData)
typedef struct {
uint16   format;
Offset32   variationRegionListOffset;
uint16   itemVariationDataCount;
Offset32*   itemVariationDataOffsets;//[itemVariationDataCount]

ItemVariationData* itemVariationData;//[itemVariationDataCount]
}ItemVariationStore;
ACQRES(ItemVariationStore){
one(f.format);
one(f.variationRegionListOffset);
one(f.itemVariationDataCount);
arr(f.itemVariationDataOffsets, f.itemVariationDataCount);
if(!f.itemVariationData){f.itemVariationData = new ItemVariationData[f.itemVariationDataCount];};
for(int i=0;i<f.itemVatiationDataCount;i++){offone(f.itemVariationData[i],f.itemVariationDataOffsets[i]);};
 };
USE_ACQRES(ItemVariationStore)
uint16 _regionIndexCount;


typedef struct {
   int16 one;
   int8 two; 
}dd1;
typedef struct {
   int32 one; 
   int16 two;
}dd2;
typedef struct {
//int16 and int8 or int32 and int16*   
 dd1 deltaData;//[regionIndexCount]
}DeltaSet1;
typedef struct {
//int16 and int8 or int32 and int16*   
 dd2 deltaData;//[regionIndexCount]
}DeltaSet2;
ACQRES(DeltaSet1/* record:*/){
arr(f.deltaData​, _regionIndexCount);
 };
USE_ACQRES(DeltaSet1/* record:*/)
ACQRES(DeltaSet2/* record:*/){
arr(f.deltaData​, _regionIndexCount);
 };
USE_ACQRES(DeltaSet2)

enum wordDeltaEnum{
LONG_WORDS =0x8000,		//Flag indicating that “word” deltas are long (int32)
WORD_DELTA_COUNT_MASK =0x7FFF//	Count of “word” deltas
};
typedef struct {
   union {
      dd1 d1;
      dd2 d2;
   }f;

}DeltaSet ;
ACQRES(DeltaSet){
   if(_worldDeltaCount & LONG_WORDS){one(f.f.d2)}
   else {one(f.f.d1);};
}
USE_ACQRES(DeltaSet)


#endif