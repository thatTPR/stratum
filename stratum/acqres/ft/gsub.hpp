#ifndef GSUB_HPP
#define GSUB_HPP
#include "fontTableCommon.hpp"
typedef struct {
Single=1	 ,//	Replace one glyph with one glyph
Multiple=2	 ,//	Replace one glyph with more than one glyph
Alternate=3	 ,//	Replace one glyph with one of many glyphs
Ligature=4	 ,//	Replace multiple glyphs with one glyph
Contextual=5	 ,// substitution	Replace one or more glyphs in context
Chained=6	 ,// contexts substitution	Replace one or more glyphs in chained context
Substitution=7	 ,// extension	Extension mechanism for other substitution types
Reverse=8	 // chaining context single	Applied in reverse order, replace single glyph in chained contexts

}GsubLookupType/* enumeration*/;
typedef struct {
// uint16   format;
Offset16   coverageOffset;
int16   deltaGlyphID;

Coverage coverage;
}SingleSubstFormat1;
ACQRES(SingleSubstFormat1){
    one(f.coverageOffset);
    one(f.deltaGlyphID);
    offone(f.coverage,f.coverageOffset);
}
USE_ACQRES(SingleSubstFormat1)
typedef struct {
// uint16   format;
Offset16   coverageOffset;
uint16   glyphCount;
uint16*   substituteGlyphIDs;//[glyphCount]

Coverage coverage;
}SingleSubstFormat2;
ACQRES(SingleSubstFormat2){
one((f.coverageOffset));
one((f.glyphCount));
arr(f.substituteGlyphIDs, f.glyphCount);

offone(f.coverage,f.coverageOffset);
};
USE_ACQRES(SingleSubstFormat2)
typedef struct {
    uint16 format;
    union {
        SingleSubstFormat1 f1;
        SingleSubstFormat2 f2;       
    }f;
}SingleSubstFormat;
ACQRES(SingleSubstFormat){
one(f.format); 
switch(f.format){
    case 1 : {one(f.f.f1);};
    case 2 : {one(f.f.f2);};
}};
USE_ACQRES(SingleSubstFormat)

typedef struct {
uint16   glyphCount;
uint16*   substituteGlyphIDs;//[glyphCount]
}Sequence/* table*/;
ACQRES(Sequence/* table*/){
one((f.glyphCount));
arr(f.substituteGlyphIDs, f.glyphCount);
 };
USE_ACQRES(Sequence/* table*/)

typedef struct {
uint16   glyphCount;
uint16*   alternateGlyphIDs;//[glyphCount]
}AlternateSet/* table*/;
ACQRES(AlternateSet/* table*/){
one((f.glyphCount));
arr(f.alternateGlyphIDs, f.glyphCount);
 };
USE_ACQRES(AlternateSet/* table*/)


typedef struct {
uint16   ligatureGlyph;
uint16   componentCount;
uint16*   componentGlyphIDs;//[componentCount - 1]
}Ligature/* table*/;
ACQRES(Ligature/* table*/){
one((f.ligatureGlyph));
one((f.componentCount));
arr(f.componentGlyphIDs, f.componentCount - 1);
};
USE_ACQRES(Ligature/* table*/)
typedef struct {
uint16   ligatureCount;
Offset16*   ligatureOffsets;//[LigatureCount]

Ligature* ligature;
}LigatureSet/* table*/;
ACQRES(LigatureSet/* table*/){
one((f.ligatureCount));
arr(f.ligatureOffsets, f.LigatureCount);
offmany(f.ligature,f.ligatureOffsets,f.LigatureCount);;

 };
USE_ACQRES(LigatureSet/* table*/)

typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   ligatureSetCount;
Offset16*   ligatureSetOffsets;//[ligatureSetCount]

LigatureSet* ligatureSet;//[ligatureSetCount]
}LigatureSubstFormat1/* subtable*/;
ACQRES(LigatureSubstFormat1/* subtable*/){
one((f.format));
one((f.coverageOffset));
one((f.ligatureSetCount));
arr(f.ligatureSetOffsets, f.ligatureSetCount);
offmany(f.ligatureSet,f.ligatureSetOffsets,f.ligatureSetCount);;
 };
USE_ACQRES(LigatureSubstFormat1/* subtable*/)


typedef struct {
uint16   format;
uint16   extensionLookupType;
Offset32   extensionOffset;
}SubstExtensionFormat1/* subtable*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   backtrackGlyphCount;
Offset16*   backtrackCoverageOffsets;//[backtrackGlyphCount]
uint16   lookaheadGlyphCount;
Offset16*   lookaheadCoverageOffsets;//[lookaheadGlyphCount]
uint16   glyphCount;
uint16*   substituteGlyphIDs;//[glyphCount]
}ReverseChainSingleSubstFormat1;
ACQRES(ReverseChainSingleSubstFormat1/* subtable*/){
one((f.format));
one((f.coverageOffset));
one((f.backtrackGlyphCount));
arr(f.backtrackCoverageOffsets, f.backtrackGlyphCount);
 one((f.lookaheadGlyphCount));
arr(f.lookaheadCoverageOffsets, f.lookaheadGlyphCount);
 one((f.glyphCount));
arr(f.substituteGlyphIDs, f.glyphCount);
 };
USE_ACQRES(ReverseChainSingleSubstFormat1)
typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;

ScriptList scriptList;
FeatureList featureList;
LookupList lookupList;

}GSUB10;
ACQRES(GSUB10){
    one(f.scriptListOffset);
    one(f.featureListOffset);
    one(f.lookupListOffset);

    offone(f.scriptList,f.scriptListOffset);
    offone(f.featureList,f.featureListOffset);
    offone(f.lookupList,f.lookupListOffset);
}
USE_ACQRES(GSUB10)
typedef struct {
// uint16   majorVersion;
// uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
Offset32   featureVariationsOffset;

ScriptList scriptList;
FeatureList featureList;
LookupList lookupList;
FeatureVariations featureVariations;

}GSUB11;
ACQRES(GSUB11){
    one(f.scriptListOffset);
    one(f.featureListOffset);
    one(f.lookupListOffset);
    one(f.featureVariationsOffset);

    offone(f.scriptList,f.scriptListOffset);
    offone(f.featureList,f.featureListOffset);
    offone(f.lookupList,f.lookupListOffset);
    offone(f.featureVariations,f.featureVariationsOffset);

}
USE_ACQRES(GSUB11)

typedef struct {
uint16   majorVersion;
uint16   minorVersion;

    union {
        GSUB10 f0;
        GSUB11 f1;
    }f;
}GSUB
ACQRES(GSUB){
    one(f.majorVersion);
    one(f.minorVersion);
    switch(f.minorVersion){
        case 0 : {one(f.f.f0);}
        case 1 : {one(f.f.f1);}
    }
}
USE_ACQRES(GSUB)
#endif