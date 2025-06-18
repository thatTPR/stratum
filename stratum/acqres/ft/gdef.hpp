typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   glyphClassDefOffset;
Offset16   attachListOffset;
Offset16   ligCaretListOffset;
Offset16   markAttachClassDefOffset;
}GDEF/* Header, version 1.0*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   glyphClassDefOffset;
Offset16   attachListOffset;
Offset16   ligCaretListOffset;
Offset16   markAttachClassDefOffset;
Offset16   markGlyphSetsDefOffset;
}GDEF/* Header, version 1.2*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   glyphClassDefOffset;
Offset16   attachListOffset;
Offset16   ligCaretListOffset;
Offset16   markAttachClassDefOffset;
Offset16   markGlyphSetsDefOffset;
Offset32   itemVarStoreOffset;
}GDEF/* Header, version 1.3*/;
typedef struct {
1   Base glyph (single character, spacing glyph);
2   Ligature glyph (multiple character, spacing glyph);
3   Mark glyph (non-spacing combining glyph);
4   Component glyph (part of single character, spacing glyph);
}GlyphClassDef/* enumeration*/;
typedef struct {
Offset16   coverageOffset;
uint16   glyphCount;
Offset16*   attachPointOffsets;//[glyphCount]
}AttachList/* table*/;
ACQRES(AttachList/* table*/){
one(coverageOffset);
one(glyphCount);
arr(attachPointOffsets, glyphCount);
 };
USE_ACQRES(AttachList/* table*/)

typedef struct {
uint16   pointCount;
uint16*   pointIndices;//[pointCount]
}AttachPoint/* table*/;
ACQRES(AttachPoint/* table*/){
one(pointCount);
arr(pointIndices, pointCount);
 };
USE_ACQRES(AttachPoint/* table*/)

typedef struct {
Offset16   coverageOffset;
uint16   ligGlyphCount;
Offset16*   ligGlyphOffsets;//[ligGlyphCount]
}LigCaretList/* table*/;
ACQRES(LigCaretList/* table*/){
one(coverageOffset);
one(ligGlyphCount);
arr(ligGlyphOffsets, ligGlyphCount);
 };
USE_ACQRES(LigCaretList/* table*/)

typedef struct {
uint16   caretCount;
Offset16*   caretValueOffsets;//[caretCount]
}LigGlyph/* table*/;
ACQRES(LigGlyph/* table*/){
one(caretCount);
arr(caretValueOffsets, caretCount);
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
}MarkGlyphSets/* table*/;
ACQRES(MarkGlyphSets/* table*/){
one(format);
one(markGlyphSetCount);
arr(coverageOffsets, markGlyphSetCount);
 };
USE_ACQRES(MarkGlyphSets/* table*/)

