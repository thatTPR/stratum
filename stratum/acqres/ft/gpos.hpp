#ifndef GPOS_HPP
#define GPOS_HPP
#include "_fontTableCommon.hpp"
enum GposLookupType {
Single_adjustment	           =1,	  // Adjust position of a single glyph
Pair_adjustment	             =2,	  //  Adjust position of a pair of glyphs
Cursive_attachment	          =3,	  // Attach cursive glyphs
Mark_to_base_attachment	     =4,	  //  Attach a combining mark to a base glyph
Mark_to_ligature_attachment	 =5,	  //  Attach a combining mark to a ligature
Mark_to_mark_attachment	     =6,	  //  Attach a combining mark to another mark
Contextual_positioning	      =7,	  // Position one or more glyphs in context
Chained_contexts_positioning =8,	//	Position one or more glyphs in chained context
Positioning_extension	       =9,	  //Extension mechanism for other positionings
};

typedef struct {
// uint16   format;
Offset16   coverageOffset;
uint16   valueFormat;
ValueRecord   valueRecord;
Coverage coverage;
}SinglePosFormat1/* subtable*/;
typedef struct {
// uint16   format;
Offset16   coverageOffset;
uint16   valueFormat;
uint16   valueCount;
ValueRecord*   valueRecords;//[valueCount]
}SinglePosFormat2/* subtable*/;
ACQRES(SinglePosFormat2/* subtable*/){
one(f.format);
one(f.coverageOffset);
one(f.valueFormat);
one(f.valueCount);
arr(f.valueRecords, f.valueCount);
offone(f.coverage,f.coverageOffset);
 };
USE_ACQRES(SinglePosFormat2/* subtable*/)

typedef struct {
    uint16   format;
    union {
        SinglePosFormat1 f1;
        SinglePosFormat2 f2;
        
    }f;
}SinglePos;
ACQRES(SinglePos){
    one(f.format);
    switch(f.format){
        case 1 :{one(f.f.f1);}
        case 2 :{one(f.f.f2);}
    };
}
USE_ACQRES(SinglePos)

typedef struct {
uint16   pairValueCount;
PairValue*   pairValueRecords;//[pairValueCount]
}PairSet/* table*/;
ACQRES(PairSet/* table*/){
one(f.pairValueCount);
arr(f.pairValueRecords, f.pairValueCount);
 };
USE_ACQRES(PairSet/* table*/)

typedef struct {
// uint16   format;
Offset16   coverageOffset;
uint16   valueFormat1;
uint16   valueFormat2;
uint16   pairSetCount;
Offset16*   pairSetOffsets;//[pairSetCount]

Coverage coverage;

PairSet* pairSets;

}PairPosFormat1/* subtable*/;
ACQRES(PairPosFormat1/* subtable*/){
one(f.format);
one(f.coverageOffset);
one(f.valueFormat1);
one(f.valueFormat2);
one(f.pairSetCount);
arr(f.pairSetOffsets, f.pairSetCount);
offone(f.coverage,f.coverageOffset);
offmany(f.pairSets,f.pairSetsOffsets,f.pairSetCount);;
};
USE_ACQRES(PairPosFormat1/* subtable*/)



typedef struct {
uint16   secondGlyph;
ValueRecord   valueRecord1;
ValueRecord   valueRecord2;
}PairValue/* record*/;
typedef struct {
ValueRecord   valueRecord1;
ValueRecord   valueRecord2;
}Class2/* record*/;
uint16 _class2Count;
typedef struct {
Class2*   class2Records;//[class2Count]
}Class1/* record*/;
ACQRES(Class1/* record*/){
arr(f.class2Records, _class2Count);
 };
USE_ACQRES(Class1/* record*/)
typedef struct {
// uint16   format;
Offset16   coverageOffset;
uint16   valueFormat1;
uint16   valueFormat2;
Offset16   classDef1Offset;
Offset16   classDef2Offset;
uint16   class1Count;
uint16   class2Count;
Class1*   class1Records;//[class1Count]

ClassDef classDef1;
ClassDef classDef2;
}PairPosFormat2/* subtable*/;
ACQRES(PairPosFormat2/* subtable*/){
one(f.format);
one(f.coverageOffset);
one(f.valueFormat1);
one(f.valueFormat2);
one(f.classDef1Offset);
one(f.classDef2Offset);
one(f.class1Count);
one(f.class2Count);
_class2Count = f.class2Count;
arr(f.class1Records, f.class1Count);
offone(f.classDef1,f.classDef1Offset);
offone(f.classDef2,f.classDef2Offset);
 };
USE_ACQRES(PairPosFormat2/* subtable*/)
typedef struct {
    uint16 format;
    union {
        PairPosFormat1 f1;
        PairPosFormat2 f2;
}f;
}PairPos;
ACQRES(PairPos){
    one(f.format);
    switch(f.format){
        case 1 : {one(f.f.f1);}
        case 2 : {one(f.f.f2);}
    }
}
USE_ACQRES(PairPos)

typedef struct {
Offset16   entryAnchorOffset;
Offset16   exitAnchorOffset;
Anchor entryAnchor;
Anchor exitAnchor;
}EntryExit/* record*/;
ACQRES(EntryExit){
    one(f.entryAnchorOffset);
    one(f.exitAnchorOffset);
    offone(f.entryAnchor,f.entryAnchorOffset);
    offone(f.exitAnchor,f.exitAnchorOffset);
}
USE_ACQRES(EntryExit)
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   entryExitCount;
EntryExit*   entryExitRecords;//[entryExitCount]
Coverage coverage;
}CursivePosFormat1/* subtable*/;
ACQRES(CursivePosFormat1/* subtable*/){
one(f.format);
one(f.coverageOffset);
one(f.entryExitCount);
arr(f.entryExitRecords, f.entryExitCount);
offone(f.coverage,f.coverageOffset);
 };
USE_ACQRES(CursivePosFormat1/* subtable*/)


typedef struct {
uint16   baseCount;
BaseRecord*   baseRecords;//[baseCount]
}BaseArray/* table*/;
ACQRES(BaseArray/* table*/){
one(f.baseCount);
arr(f.baseRecords, f.baseCount);
 };
USE_ACQRES(BaseArray/* table*/)

typedef struct {
Offset16*   baseAnchorOffsets;//[markClassCount]
}BaseRecord;
ACQRES(BaseRecord){
arr(f.baseAnchorOffsets, f.markClassCount);
 };
USE_ACQRES(BaseRecord)

typedef struct {
uint16   format;
Offset16   markCoverageOffset;
Offset16   ligatureCoverageOffset;
uint16   markClassCount;
Offset16   markArrayOffset;
Offset16   ligatureArrayOffset;
}MarkLigPosFormat1/* subtable*/;
typedef struct {
uint16   ligatureCount;
Offset16*   ligatureAttachOffsets;//[ligatureCount]
}LigatureArray/* table*/;
ACQRES(LigatureArray/* table*/){
one(f.ligatureCount);
arr(f.ligatureAttachOffsets, f.ligatureCount);
 };
USE_ACQRES(LigatureArray/* table*/)

typedef struct {
uint16   componentCount;
ComponentRecord*   componentRecords;//[componentCount]
}LigatureAttach/* table*/;
ACQRES(LigatureAttach/* table*/){
one(f.componentCount);
arr(f.componentRecords, f.componentCount);
 };
USE_ACQRES(LigatureAttach/* table*/)
uint16 _markClassCount ;
typedef struct {
Offset16*   ligatureAnchorOffsets;//[markClassCount]
}ComponentRecord;
ACQRES(ComponentRecord){
arr(f.ligatureAnchorOffsets, _markClassCount);
 };
USE_ACQRES(ComponentRecord)
typedef struct {
Offset16*   mark2AnchorOffsets;//[markClassCount]
}Mark2/* record*/;
ACQRES(Mark2/* record*/){
arr(f.mark2AnchorOffsets, f.markClassCount);
 };
USE_ACQRES(Mark2/* record*/)

typedef struct {
uint16   mark2Count;
Mark2*   mark2Records;//[mark2Count]
}Mark2Array/* table*/;
ACQRES(Mark2Array/* table*/){
one(f.mark2Count);
arr(f.mark2Records, f.mark2Count);
 };
USE_ACQRES(Mark2Array/* table*/)


typedef struct {
uint16   format;
Offset16   mark1CoverageOffset;
Offset16   mark2CoverageOffset;
uint16   markClassCount;
Offset16   mark1ArrayOffset;
Offset16   mark2ArrayOffset;

}MarkMarkPosFormat1;
ACQRES(MarkMarkPosFormat1){
one(f.format);
one(f.mark1CoverageOffset);
one(f.mark2CoverageOffset);
one(f.markClassCount);
_markClassCount =f.markClassCount; 
one(f.mark1ArrayOffset);
one(f.mark2ArrayOffset);
}
USE_ACQRES(MarkMarkPosFormat1)

typedef struct {
uint16   format;
uint16   extensionLookupType;
Offset32   extensionOffset;
}PosExtensionFormat1/* subtable*/;
typedef struct {
int16   xPlacement;
int16   yPlacement;
int16   xAdvance;
int16   yAdvance;
Offset16   xPlaDeviceOffset;
Offset16   yPlaDeviceOffset;
Offset16   xAdvDeviceOffset;
Offset16   yAdvDeviceOffset;
}ValueRecord;
enum ValueFormat{
X_PLACEMENT=0x0001,
Y_PLACEMENT=0x0002,
X_ADVANCE=0x0004,
Y_ADVANCE=0x0008,
X_PLACEMENT_DEVICE=0x0010,
Y_PLACEMENT_DEVICE=0x0020,
X_ADVANCE_DEVICE=0x0040,
Y_ADVANCE_DEVICE=0x0080,
Reserved=0xFF00,
};
typedef struct{
// uint16   format;
int16   xCoordinate;
int16   yCoordinate;
} AnchorFormat1;
typedef struct {
// uint16   format;
int16   xCoordinate;
int16   yCoordinate;
uint16   anchorPoint;
}AnchorFormat2;
typedef struct{
// uint16   format;
int16   xCoordinate;
int16   yCoordinate;
Offset16   xDeviceOffset;
Offset16   yDeviceOffset;
} AnchorFormat3;
typedef struct {
    uint16 format;
    union {
        AnchorFormat1 f1;
        AnchorFormat2 f2;
        AnchorFormat3 f3;
    }f;

}Anchor;
ACQRES(Anchor){
    one(f.format);
    switch(f.format){
        case 1 :{one(f.f.f1);};
        case 2 :{one(f.f.f2);};
        case 3 :{one(f.f.f3);};
    }
}
USE_ACQRES(Anchor)
typedef struct {
uint16   markClass;
Offset16   markAnchorOffset;

Anchor markAnchor;
}MarkRecord;
ACQRES(MarkRecord){
    one(f.markClass);
    one(f.markAnchorOffset);
    offone(f.markAnchor,f.markAnchorOffset)
}
USE_ACQRES(MarkRecord)
typedef struct {
uint16   markCount;
MarkRecord*   markRecords;//[markCount]
}MarkArray/* table*/;
ACQRES(MarkArray/* table*/){
one(f.markCount);
arr(f.markRecords, f.markCount);
 };
USE_ACQRES(MarkArray/* table*/)

typedef struct {
uint16   format;
Offset16   markCoverageOffset;
Offset16   baseCoverageOffset;
uint16   markClassCount;
Offset16   markArrayOffset;
Offset16   baseArrayOffset;
/// @brief

Coverage markCoverage;
Coverage baseCoverage;
MarkArray markArray;
BaseArray baseArray;
}MarkBasePosFormat1/* subtable*/;
ACQRES(MarkBasePosFormat1){
    one(f.markCoverageOffset);
    one(f.baseCoverageOffset);
    one(f.markClassCount);
    one(f.markArrayOffset);
    one(f.baseArrayOffset);

    offone(f.markCoverage,f.markCoverageOffset);
    offone(f.baseCoverage,f.baseCoverageOffset);
    offone(f.markArray,f.markArrayOffset);
    offone(f.baseArray,f.baseArrayOffset);

}
USE_ACQRES(MarkBasePosFormat1)
typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
/// @brief
ScriptList scriptList;
FeatureList featureList;
LookupList lookupList;


}GPOS10;
ACQRES(GPOS10){
one(f.scriptListOffset);
one(f.featureListOffset);
one(f.lookupListOffset);

offone(f.scriptList,f.scriptListOffset);
offone(f.featureList,f.featureListOffset);
offone(f.lookupList,f.lookupListOffset);
}
USE_ACQRES(GPOS10)

typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
Offset32   featureVariationsOffset;
//
ScriptList scriptList;
FeatureList featureList;
LookupList lookupList;
FeatureVariations featureVariations;
}GPOS11;
ACQRES(GPOS11){
    one(f.scriptListOffset);
    one(f.featureListOffset);
    one(f.lookupListOffset);
    one(f.featureVariationsOffset);

    offone(f.scriptList,f.scriptListOffset);
    offone(f.featureList,f.featureListOffset);
    offone(f.lookupList,f.lookupListOffset);
    offone(f.featureVariations,f.featureVariationsOffset);

}
USE_ACQRES(GPOS11)
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
    union {
        GPOS10 f10;
        GPOS11 f11;
    }gpos;
    
}GPOS;
ACQRES(GPOS){
    one(f.majorVersion);
    one(f.minorVersion);
    switch(f.minorVersion){
        case 0 : {one(f.gpos.f10);}
        case 1 : {one(f.gpos.f11);}
    }
}

USE_ACQRES(GPOS)