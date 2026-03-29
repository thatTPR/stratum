#ifndef FTGDEF_HPP
#define FTGDEF_HPP
#include "gpos.hpp"
#include "_fontTableCommon.hpp"
enum GlyphClassDefEnum {
Base_glyph = 1,//    (single character, spacing glyph);
Ligature_glyph = 2,//    (multiple character, spacing glyph);
Mark_glyph = 3,//    (non-spacing combining glyph);
Component_glyph = 4 //  (part of single character, spacing glyph);
};
typedef struct {
Offset16   coverageOffset;
uint16   glyphCount;
Offset16*   attachPointOffsets;//[glyphCount]
}AttachList/* table*/;
ACQRES(AttachList/* table*/){
one((f.coverageOffset));
one((f.glyphCount));
arr(f.attachPointOffsets, f.glyphCount);
 };
USE_ACQRES(AttachList/* table*/)

typedef struct {
uint16   pointCount;
uint16*   pointIndices;//[pointCount]
}AttachPoint/* table*/;
ACQRES(AttachPoint/* table*/){
one((f.pointCount));
arr(f.pointIndices, f.pointCount);
 };
USE_ACQRES(AttachPoint/* table*/)

typedef struct {
Offset16   coverageOffset;
uint16   ligGlyphCount;
Offset16*   ligGlyphOffsets;//[ligGlyphCount]
}LigCaretList/* table*/;
ACQRES(LigCaretList/* table*/){
one((f.coverageOffset));
one((f.ligGlyphCount));
arr(f.ligGlyphOffsets, f.ligGlyphCount);
 };
USE_ACQRES(LigCaretList/* table*/)

typedef struct {
uint16   caretCount;
Offset16*   caretValueOffsets;//[caretCount]
}LigGlyph/* table*/;
ACQRES(LigGlyph/* table*/){
one((f.caretCount));
arr(f.caretValueOffsets, f.caretCount);
 };
USE_ACQRES(LigGlyph/* table*/)

typedef struct {
uint16   format;
int16   coordinate;
}CaretValueFormat1/* table: Design units only*/;
typedef struct {
uint16   format;
uint16   caretValuePointIndex;
}CaretValueFormat2/* table: Contour point*/;
typedef struct {
uint16   format;
int16   coordinate;
Offset16   deviceOffset;
}CaretValueFormat3/* table: Design units plus Device or VariationIndex table*/;
typedef struct {
uint16   format;
uint16   markGlyphSetCount;
Offset32*   coverageOffsets;//[markGlyphSetCount]
Coverage* coverage;
}MarkGlyphSets/* table*/;
ACQRES(MarkGlyphSets/* table*/){
one((f.format));
one((f.markGlyphSetCount));
arr(f.coverageOffsets, f.markGlyphSetCount);
offarr(f.coverage,f.coverageOffsets,f.markGlyphSetCount);
 };
USE_ACQRES(MarkGlyphSets/* table*/)

typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   glyphClassDefOffset;
Offset16   attachListOffset;
Offset16   ligCaretListOffset;
Offset16   markAttachClassDefOffset;
//
ClassDef glyphClassDef; 
ClassDef attachList;
ClassDef ligCaretList;
ClassDef markAttachClass;
}GDEF10;
ACQRES(GDEF10){
    one(f.glyphClassDefOffset);
    one(f.attachListOffset);
    one(f.ligCaretListOffset);
    one(f.markAttachClassDefOffset);
    offone(f.glyphClassDef,f.glyphClassDefOFfset);
    offone(f.attachList,f.attachListOffset);
    offone(f.ligCaretList,f.ligCaretListOffset);
    offone(f.markAttachClassDef,f.markAttachClassDefOffset);
}
USE_ACQRES(GDEF10)
typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   glyphClassDefOffset;
Offset16   attachListOffset;
Offset16   ligCaretListOffset;
Offset16   markAttachClassDefOffset;
Offset16   markGlyphSetsDefOffset;

//
ClassDef glyphClassDef; //
ClassDef attachList;
ClassDef ligCaretList;
ClassDef markAttachClass;
MarkGlyphSets markGlyphSetsDef;
}GDEF12;
ACQRES(GDEF12){
    one(f.glyphClassDefOffset);
    one(f.attachListOffset);
    one(f.ligCaretListOffset);
    one(f.markAttachClassDefOffset);
    one(f.markGlyphSetsDefOffset);
    
    offone(f.glyphClassDef,f.glyphClassDefOFfset);
    offone(f.attachList,f.attachListOffset);
    offone(f.ligCaretList,f.ligCaretListOffset);
    offone(f.markAttachClassDef,f.markAttachClassDefOffset);
    offone(f.markGlyphSetsDef,f.markGlyphSetsDefOffset);
}
USE_ACQRES(GDEF12)
typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   glyphClassDefOffset;
Offset16   attachListOffset;
Offset16   ligCaretListOffset;
Offset16   markAttachClassDefOffset;
Offset16   markGlyphSetsDefOffset;
Offset32   itemVarStoreOffset;

////
GlyphClassDef glyphClassDef; 
AttachList attachList;
LigCaretList ligCaretList;
MarkAttachClassDef markAttachClass;
MarkGlyphSetsDef markGlyphSetsDef;
ItemVariationStore itemVarStore;
}GDEF13;
ACQRES(GDEF13){
    one(f.glyphClassDefOffset);
    one(f.attachListOffset);
    one(f.ligCaretListOffset);
    one(f.markAttachClassDefOffset);
    one(f.markGlyphSetsDefOffset);
    one(f.itemVarStoreOffset);

    offone(f.glyphClassDef,f.glyphClassDefOFfset);
    offone(f.attachList,f.attachListOffset);
    offone(f.ligCaretList,f.ligCaretListOffset);
    offone(f.markAttachClassDef,f.markAttachClassDefOffset);
    offone(f.markGlyphSetsDef,f.markGlyphSetsDefOffset);
    offone(f.itemVarStore,f.itemVarStoreOffset);

}
USE_ACQRES(GDEF13)

typedef struct {
uint16   majorVersion;
uint16   minorVersion;

    union {
    GDEF10 f10;
    GDEF12 f12;
    GDEF13 f13;
}f;

    
}GDEF ; 
ACQRES(GDEF){
    one(f.majorVersion);
    one(f.minorVersion);
    switch(f.minorVersion){
        case 0 : {one(f.f10);};
        case 2 : {one(f.f12);};
        case 3 : {one(f.f13);};
    }

}
USE_ACQRES(GDEF)
#endif