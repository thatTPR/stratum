#ifndef FT_FONTTABLE
#define FT_FONTTABLE
typedef struct {
uint16   scriptCount;
ScriptRecord*   scriptRecords;//[scriptCount]
}ScriptList/* table*/;
ACQRES(ScriptList/* table*/){
one((f.scriptCount));
arr(f.scriptRecords, f.scriptCount);
 };
USE_ACQRES(ScriptList/* table*/)

typedef struct {
Tag   scriptTag;
Offset16   scriptOffset;
}ScriptRecord;
typedef struct {
Offset16   defaultLangSysOffset;
uint16   langSysCount;
LangSysRecord*   langSysRecords;//[langSysCount]
}Script/* table*/;
ACQRES(Script/* table*/){
one((f.defaultLangSysOffset));
one((f.langSysCount));
arr(f.langSysRecords, f.langSysCount);
 };
USE_ACQRES(Script/* table*/)

typedef struct {
Tag   langSysTag;
Offset16   langSysOffset;
}LangSysRecord;
typedef struct {
Offset16   lookupOrderOffset;
uint16   requiredFeatureIndex;
uint16   featureIndexCount;
uint16*   featureIndices;//[featureIndexCount]
}LangSys/* table*/;
ACQRES(LangSys/* table*/){
one((f.lookupOrderOffset));
one((f.requiredFeatureIndex));
one((f.featureIndexCount));
arr(f.featureIndices, f.featureIndexCount);
 };
USE_ACQRES(LangSys/* table*/)

typedef struct {
uint16   featureCount;
FeatureRecord*   featureRecords;//[featureCount]
}FeatureList/* table*/;
ACQRES(FeatureList/* table*/){
one((f.featureCount));
arr(f.featureRecords, f.featureCount);
 };
USE_ACQRES(FeatureList/* table*/)

typedef struct {
Tag   featureTag;
Offset16   featureOffset;
}FeatureRecord;
typedef struct {
Offset16   featureParamsOffset;
uint16   lookupIndexCount;
uint16*   lookupListIndices;//[lookupIndexCount]
}Feature/* table*/;
ACQRES(Feature/* table*/){
one((f.featureParamsOffset));
one((f.lookupIndexCount));
arr(f.lookupListIndices, f.lookupIndexCount);
 };
USE_ACQRES(Feature/* table*/)

typedef struct {
uint16   lookupCount;
Offset16*   lookupOffsets;//[lookupCount]
}LookupList/* table*/;
ACQRES(LookupList/* table*/){
one((f.lookupCount));
arr(f.lookupOffsets, f.lookupCount);
 };
USE_ACQRES(LookupList/* table*/)

typedef struct {
uint16   lookupType;
uint16   lookupFlag;
uint16   subTableCount;
Offset16*   subtableOffsets;//[subTableCount]
uint16   markFilteringSet;
}Lookup/* table*/;
ACQRES(Lookup/* table*/){
one((f.lookupType));
one((f.lookupFlag));
one((f.subTableCount));
arr(f.subtableOffsets, f.subTableCount);
 one((f.markFilteringSet));
};
USE_ACQRES(Lookup/* table*/)

typedef struct {
uint16   format;
uint16   glyphCount;
uint16*   glyphArray;//[glyphCount]
}CoverageFormat1/* table: Individual glyph indices*/;
ACQRES(CoverageFormat1/* table: Individual glyph indices*/){
one((f.format));
one((f.glyphCount));
arr(f.glyphArray, f.glyphCount);
 };
USE_ACQRES(CoverageFormat1/* table: Individual glyph indices*/)

typedef struct {
uint16   format;
uint16   rangeCount;
RangeRecord*   rangeRecords;//[rangeCount]
}CoverageFormat2/* table: Range of glyphs*/;
ACQRES(CoverageFormat2/* table: Range of glyphs*/){
one((f.format));
one((f.rangeCount));
arr(f.rangeRecords, f.rangeCount);
 };
USE_ACQRES(CoverageFormat2/* table: Range of glyphs*/)

typedef struct {
    uint16 format;
    union {
        CoverageFormat1 f1;
        CoverageFormat2 f2;
    }f;
}Coverage;
ACQRES(Coverage){
    one(f.format);
    switch(f.format){
        case 1 : {one(f.f.f1);};
        case 2 : {one(f.f.f2);};
    }
}
USE_ACQRES(Coverage)
typedef struct {
uint16   startGlyphID;
uint16   endGlyphID;
uint16   startCoverageIndex;
}RangeRecord;
typedef struct {
// uint16   format;
uint16   startGlyphID;
uint16   glyphCount;
uint16*   classValues;//[glyphCount]
}ClassDefFormat1;
ACQRES(ClassDefFormat1/* table: Class array*/){
one(f.format);
one(f.startGlyphID);
one(f.glyphCount);
arr(f.classValues, f.glyphCount);
 };
USE_ACQRES(ClassDefFormat1/* table: Class array*/)
typedef struct {
uint16   startGlyphID;
uint16   endGlyphID;
uint16   class;
}ClassRange;
typedef struct {
// uint16   format;
uint16   classRangeCount;
ClassRange*   classRangeRecords;//[classRangeCount]
}ClassDefFormat2;
ACQRES(ClassDefFormat2/* table: Class ranges*/){
one(f.format);
one(f.classRangeCount);
arr(f.classRangeRecords, f.classRangeCount);
 };
USE_ACQRES(ClassDefFormat2/* table: Class ranges*/)

typedef struct {
    uint1 format;
    union  {
        ClassDefFormat1 f1;
        ClassDefFormat2 f2;
    }f;
    
}ClassDef;
ACQRES(ClassDef){
    one(f.format);
    switch(f.format){
        case 1 : {one(f.f.f1);};
        case 1 : {one(f.f.f2);};
    }
}
USE_ACQRES(ClassDef)


typedef struct {
uint16   sequenceIndex;
uint16   lookupListIndex;
}SequenceLookup/* record*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   seqRuleSetCount;
Offset16*   seqRuleSetOffsets;//[seqRuleSetCount]
}SequenceContextFormat1/* table*/;
ACQRES(SequenceContextFormat1/* table*/){
one((f.format));
one((f.coverageOffset));
one((f.seqRuleSetCount));
arr(f.seqRuleSetOffsets, f.seqRuleSetCount);
 };
USE_ACQRES(SequenceContextFormat1/* table*/)

typedef struct {
uint16   seqRuleCount;
Offset16*   seqRuleOffsets;//[seqRuleCount]
}SequenceRuleSet/* table—all contexts beginning with the same glyph*/;
ACQRES(SequenceRuleSet/* table—all contexts beginning with the same glyph*/){
one((f.seqRuleCount));
arr(f.seqRuleOffsets, f.seqRuleCount);
 };
USE_ACQRES(SequenceRuleSet/* table—all contexts beginning with the same glyph*/)

typedef struct {
uint16   glyphCount;
uint16   seqLookupCount;
uint16*   inputSequence;//[glyphCount - 1]
SequenceLookup*   seqLookupRecords;//[seqLookupCount]
}SequenceRule/* table*/;
ACQRES(SequenceRule/* table*/){
one((f.glyphCount));
one((f.seqLookupCount));
arr(f.inputSequence, f.glyphCount - 1);
 arr(f.seqLookupRecords, f.seqLookupCount);
 };
USE_ACQRES(SequenceRule/* table*/)

typedef struct {
uint16   format;
Offset16   coverageOffset;
Offset16   classDefOffset;
uint16   classSeqRuleSetCount;
Offset16*   classSeqRuleSetOffsets;//[classSeqRuleSetCount]
}SequenceContextFormat2/* table*/;
ACQRES(SequenceContextFormat2/* table*/){
one((f.format));
one((f.coverageOffset));
one((f.classDefOffset));
one((f.classSeqRuleSetCount));
arr(f.classSeqRuleSetOffsets, f.classSeqRuleSetCount);
 };
USE_ACQRES(SequenceContextFormat2/* table*/)

typedef struct {
uint16   classSeqRuleCount;
Offset16*   classSeqRuleOffsets;//[classSeqRuleCount]
}ClassSequenceRuleSet/* table*/;
ACQRES(ClassSequenceRuleSet/* table*/){
one((f.classSeqRuleCount));
arr(f.classSeqRuleOffsets, f.classSeqRuleCount);
 };
USE_ACQRES(ClassSequenceRuleSet/* table*/)

typedef struct {
uint16   glyphCount;
uint16   seqLookupCount;
uint16*   inputSequence;//[glyphCount - 1]
SequenceLookup*   seqLookupRecords;//[seqLookupCount]
}ClassSequenceRule/* table*/;
ACQRES(ClassSequenceRule/* table*/){
one((f.glyphCount));
one((f.seqLookupCount));
arr(f.inputSequence, f.glyphCount - 1);
 arr(f.seqLookupRecords, f.seqLookupCount);
 };
USE_ACQRES(ClassSequenceRule/* table*/)

typedef struct {
uint16   format;
uint16   glyphCount;
uint16   seqLookupCount;
Offset16*   coverageOffsets;//[glyphCount]
SequenceLookup*   seqLookupRecords;//[seqLookupCount]
}SequenceContextFormat3/* table*/;
ACQRES(SequenceContextFormat3/* table*/){
one((f.format));
one((f.glyphCount));
one((f.seqLookupCount));
arr(f.coverageOffsets, f.glyphCount);
 arr(f.seqLookupRecords, f.seqLookupCount);
 };
USE_ACQRES(SequenceContextFormat3/* table*/)

typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   chainedSeqRuleSetCount;
Offset16*   chainedSeqRuleSetOffsets;//[chainedSeqRuleSetCount]
}ChainedSequenceContextFormat1/* table*/;
ACQRES(ChainedSequenceContextFormat1/* table*/){
one((f.format));
one((f.coverageOffset));
one((f.chainedSeqRuleSetCount));
arr(f.chainedSeqRuleSetOffsets, f.chainedSeqRuleSetCount);
 };
USE_ACQRES(ChainedSequenceContextFormat1/* table*/)

typedef struct {
uint16   chainedSeqRuleCount;
Offset16*   chainedSeqRuleOffsets;//[chainedSeqRuleCount]
}ChainedSequenceRuleSet/* table*/;
ACQRES(ChainedSequenceRuleSet/* table*/){
one((f.chainedSeqRuleCount));
arr(f.chainedSeqRuleOffsets, f.chainedSeqRuleCount);
 };
USE_ACQRES(ChainedSequenceRuleSet/* table*/)

typedef struct {
uint16   backtrackGlyphCount;
uint16*   backtrackSequence;//[backtrackGlyphCount]
uint16   inputGlyphCount;
uint16*   inputSequence;//[inputGlyphCount - 1]
uint16   lookaheadGlyphCount;
uint16*   lookaheadSequence;//[lookaheadGlyphCount]
uint16   seqLookupCount;
SequenceLookup*   seqLookupRecords;//[seqLookupCount]
}ChainedSequenceRule/* table*/;
ACQRES(ChainedSequenceRule/* table*/){
one((f.backtrackGlyphCount));
arr(f.backtrackSequence, f.backtrackGlyphCount);
 one((f.inputGlyphCount));
arr(f.inputSequence, f.inputGlyphCount - 1);
 one((f.lookaheadGlyphCount));
arr(f.lookaheadSequence, f.lookaheadGlyphCount);
 one((f.seqLookupCount));
arr(f.seqLookupRecords, f.seqLookupCount);
 };
USE_ACQRES(ChainedSequenceRule/* table*/)

typedef struct {
uint16   format;
Offset16   coverageOffset;
Offset16   backtrackClassDefOffset;
Offset16   inputClassDefOffset;
Offset16   lookaheadClassDefOffset;
uint16   chainedClassSeqRuleSetCount;
Offset16*   chainedClassSeqRuleSetOffsets;//[chainedClassSeqRuleSetCount]
}ChainedSequenceContextFormat2/* table*/;
ACQRES(ChainedSequenceContextFormat2/* table*/){
one((f.format));
one((f.coverageOffset));
one((f.backtrackClassDefOffset));
one((f.inputClassDefOffset));
one((f.lookaheadClassDefOffset));
one((f.chainedClassSeqRuleSetCount));
arr(f.chainedClassSeqRuleSetOffsets, f.chainedClassSeqRuleSetCount);
 };
USE_ACQRES(ChainedSequenceContextFormat2/* table*/)

typedef struct {
uint16   chainedClassSeqRuleCount;
Offset16*   chainedClassSeqRuleOffsets;//[chainedClassSeqRuleCount]
}ChainedClassSequenceRuleSet/* table*/;
ACQRES(ChainedClassSequenceRuleSet/* table*/){
one((f.chainedClassSeqRuleCount));
arr(f.chainedClassSeqRuleOffsets, f.chainedClassSeqRuleCount);
 };
USE_ACQRES(ChainedClassSequenceRuleSet/* table*/)

typedef struct {
uint16   backtrackGlyphCount;
uint16*   backtrackSequence;//[backtrackGlyphCount]
uint16   inputGlyphCount;
uint16*   inputSequence;//[inputGlyphCount - 1]
uint16   lookaheadGlyphCount;
uint16*   lookaheadSequence;//[lookaheadGlyphCount]
uint16   seqLookupCount;
SequenceLookup*   seqLookupRecords;//[seqLookupCount]
}ChainedClassSequenceRule/* table*/;
ACQRES(ChainedClassSequenceRule/* table*/){
one((f.backtrackGlyphCount));
arr(f.backtrackSequence, f.backtrackGlyphCount);
 one((f.inputGlyphCount));
arr(f.inputSequence, f.inputGlyphCount - 1);
 one((f.lookaheadGlyphCount));
arr(f.lookaheadSequence, f.lookaheadGlyphCount);
 one((f.seqLookupCount));
arr(f.seqLookupRecords, f.seqLookupCount);
 };
USE_ACQRES(ChainedClassSequenceRule/* table*/)

typedef struct {
uint16   format;
uint16   backtrackGlyphCount;
Offset16*   backtrackCoverageOffsets;//[backtrackGlyphCount]
uint16   inputGlyphCount;
Offset16*   inputCoverageOffsets;//[inputGlyphCount]
uint16   lookaheadGlyphCount;
Offset16*   lookaheadCoverageOffsets;//[lookaheadGlyphCount]
uint16   seqLookupCount;
SequenceLookup*   seqLookupRecords;//[seqLookupCount]
}ChainedSequenceContextFormat3/* table*/;
ACQRES(ChainedSequenceContextFormat3/* table*/){
one((f.format));
one((f.backtrackGlyphCount));
arr(f.backtrackCoverageOffsets, f.backtrackGlyphCount);
 one((f.inputGlyphCount));
arr(f.inputCoverageOffsets, f.inputGlyphCount);
 one((f.lookaheadGlyphCount));
arr(f.lookaheadCoverageOffsets, f.lookaheadGlyphCount);
 one((f.seqLookupCount));
arr(f.seqLookupRecords, f.seqLookupCount);
 };
USE_ACQRES(ChainedSequenceContextFormat3/* table*/)

enum  DeltaFormatvalues {
LOCAL_2_BIT_DELTAS=0x0001,
LOCAL_4_BIT_DELTAS=0x0002,
LOCAL_8_BIT_DELTAS=0x0003,
VARIATION_INDEX=0x8000,
Reserved=0x7FFC
};
typedef struct {
uint16   startSize;
uint16   endSize;
uint16   deltaFormat;
uint16*   deltaValue;//[ ]
}Device/* table*/;
ACQRES(Device/* table*/){
one((f.startSize));
one((f.endSize));
one((f.deltaFormat));
arr(f.deltaValue, f. );
 };
USE_ACQRES(Device/* table*/)

typedef struct {
uint16   deltaSetOuterIndex;
uint16   deltaSetInnerIndex;
uint16   deltaFormat;
}VariationIndex/* table*/;

typedef struct {
Offset32   conditionSetOffset;
Offset32   featureTableSubstitutionOffset;
}FeatureVariationRecord;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   featureVariationRecordCount;
FeatureVariationRecord*   featureVariationRecords;//[featureVariationRecordCount]
}FeatureVariations/* table*/;
ACQRES(FeatureVariations/* table*/){
one((f.majorVersion));
one((f.minorVersion));
one((f.featureVariationRecordCount));
arr(f.featureVariationRecords, f.featureVariationRecordCount);
 };
USE_ACQRES(FeatureVariations/* table*/)

typedef struct {
uint16   conditionCount;
Offset32*   conditionOffsets;//[conditionCount]
}ConditionSet/* Table*/;
ACQRES(ConditionSet/* Table*/){
one((f.conditionCount));
arr(f.conditionOffsets, f.conditionCount);
 };
USE_ACQRES(ConditionSet/* Table*/)

typedef struct {
uint16   format;
uint16   axisIndex;
F2DOT14   filterRangeMinValue;
F2DOT14   filterRangeMaxValue;
}ConditionFormat1/* table*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   substitutionCount;
FeatureTableSubstitutionRecord*   substitutions;//[substitutionCount]
}FeatureTableSubstitution/* table*/;
ACQRES(FeatureTableSubstitution/* table*/){
one((f.majorVersion));
one((f.minorVersion));
one((f.substitutionCount));
arr(f.substitutions, f.substitutionCount);
 };
USE_ACQRES(FeatureTableSubstitution/* table*/)

typedef struct {
uint16   featureIndex;
Offset32   alternateFeatureOffset;
}FeatureTableSubstitutionRecord;
#endif