#ifndef FTMATH_HPP
#define FTMATH_HPP
#include "_fontTableCommon.hpp"
typedef struct {
FWORD   value;
Offset16   deviceOffset;
}MathValueRecord;
typedef struct {
int16   scriptPercentScaleDown;
int16   scriptScriptPercentScaleDown;
UFWORD   delimitedSubFormulaMinHeight;
UFWORD   displayOperatorMinHeight;
MathValueRecord   mathLeading;
MathValueRecord   axisHeight;
MathValueRecord   accentBaseHeight;
MathValueRecord   flattenedAccentBaseHeight;
MathValueRecord   subscriptShiftDown;
MathValueRecord   subscriptTopMax;
MathValueRecord   subscriptBaselineDropMin;
MathValueRecord   superscriptShiftUp;
MathValueRecord   superscriptShiftUpCramped;
MathValueRecord   superscriptBottomMin;
MathValueRecord   superscriptBaselineDropMax;
MathValueRecord   subSuperscriptGapMin;
MathValueRecord   superscriptBottomMaxWithSubscript;
MathValueRecord   spaceAfterScript;
MathValueRecord   upperLimitGapMin;
MathValueRecord   upperLimitBaselineRiseMin;
MathValueRecord   lowerLimitGapMin;
MathValueRecord   lowerLimitBaselineDropMin;
MathValueRecord   stackTopShiftUp;
MathValueRecord   stackTopDisplayStyleShiftUp;
MathValueRecord   stackBottomShiftDown;
MathValueRecord   stackBottomDisplayStyleShiftDown;
MathValueRecord   stackGapMin;
MathValueRecord   stackDisplayStyleGapMin;
MathValueRecord   stretchStackTopShiftUp;
MathValueRecord   stretchStackBottomShiftDown;
MathValueRecord   stretchStackGapAboveMin;
MathValueRecord   stretchStackGapBelowMin;
MathValueRecord   fractionNumeratorShiftUp;
MathValueRecord   fractionNumeratorDisplayStyleShiftUp;
MathValueRecord   fractionDenominatorShiftDown;
MathValueRecord   fractionDenominatorDisplayStyleShiftDown;
MathValueRecord   fractionNumeratorGapMin;
MathValueRecord   fractionNumDisplayStyleGapMin;
MathValueRecord   fractionRuleThickness;
MathValueRecord   fractionDenominatorGapMin;
MathValueRecord   fractionDenomDisplayStyleGapMin;
MathValueRecord   skewedFractionHorizontalGap;
MathValueRecord   skewedFractionVerticalGap;
MathValueRecord   overbarVerticalGap;
MathValueRecord   overbarRuleThickness;
MathValueRecord   overbarExtraAscender;
MathValueRecord   underbarVerticalGap;
MathValueRecord   underbarRuleThickness;
MathValueRecord   underbarExtraDescender;
MathValueRecord   radicalVerticalGap;
MathValueRecord   radicalDisplayStyleVerticalGap;
MathValueRecord   radicalRuleThickness;
MathValueRecord   radicalExtraAscender;
MathValueRecord   radicalKernBeforeDegree;
MathValueRecord   radicalKernAfterDegree;
int16   radicalDegreeBottomRaisePercent;
}MathConstants/* table*/;


typedef struct {
Offset16   italicsCorrectionCoverageOffset;
uint16   italicsCorrectionCount;
MathValueRecord*   italicsCorrection;//[italicsCorrectionCount]
}MathItalicsCorrectionInfo/* table*/;
ACQRES(MathItalicsCorrectionInfo/* table*/){
one((f.italicsCorrectionCoverageOffset));
one((f.italicsCorrectionCount));
arr(f.italicsCorrection, f.italicsCorrectionCount);
 };
USE_ACQRES(MathItalicsCorrectionInfo/* table*/)

typedef struct {
Offset16   topAccentCoverageOffset;
uint16   topAccentAttachmentCount;
MathValueRecord*   topAccentAttachment;//[topAccentAttachmentCount]
}MathTopAccentAttachment/* table*/;
ACQRES(MathTopAccentAttachment/* table*/){
one((f.topAccentCoverageOffset));
one((f.topAccentAttachmentCount));
arr(f.topAccentAttachment, f.topAccentAttachmentCount);
 };
USE_ACQRES(MathTopAccentAttachment/* table*/)



typedef struct {
uint16   heightCount;
MathValueRecord*   correctionHeight;//[heightCount]
MathValueRecord*   kernValues;//[heightCount + 1]
}MathKern/* table*/;
ACQRES(MathKern/* table*/){
one((f.heightCount));
arr(f.correctionHeight, f.heightCount);
 arr(f.kernValues, f.heightCount + 1);
 };
USE_ACQRES(MathKern/* table*/)

typedef struct {
Offset16   topRightMathKernOffset;
Offset16   topLeftMathKernOffset;
Offset16   bottomRightMathKernOffset;
Offset16   bottomLeftMathKernOffset;

MathKern topRightMathKern ;
MathKern topLeftMathKern ;
MathKern bottomRightMathKern ;
MathKern bottomLeftMathKern ;

}MathKernInfoRecord;
ACQRES(MathKernInfoRecord){
   one(f.topRightMathKernOffset);
   one(f.topLeftMathKernOffset);
   one(f.bottomRightMathKernOffset);
   one(f.bottomLeftMathKernOffset);

offone(f.topRightMathKern,f.topRightMathKernOffset);
offone(f.topLeftMathKern,f.topLeftMathKernOffset);
offone(f.bottomRightMathKern,f.bottomRightMathKernOffset);
offone(f.bottomLeftMathKern,f.bottomLeftMathKernOffset);
}
USE_ACQRES(MathKernInfoRecord)

typedef struct {
Offset16   mathKernCoverageOffset;
uint16   mathKernCount;
MathKernInfoRecord*   mathKernInfoRecords;//[mathKernCount]
}MathKernInfo/* table*/;
ACQRES(MathKernInfo/* table*/){
one((f.mathKernCoverageOffset));
one((f.mathKernCount));
arr(f.mathKernInfoRecords, f.mathKernCount);
 };
USE_ACQRES(MathKernInfo/* table*/)

typedef struct {
uint16   variantGlyph;
UFWORD   advanceMeasurement;
}MathGlyphVariantRecord;
typedef struct {
uint16   glyphID;
UFWORD   startConnectorLength;
UFWORD   endConnectorLength;
UFWORD   fullAdvance;
uint16   partFlags;
}GlyphPart/* record*/;
typedef struct {
MathValueRecord   italicsCorrection;
uint16   partCount;
GlyphPart*   partRecords;//[partCount]
}GlyphAssembly/* table*/;
ACQRES(GlyphAssembly/* table*/){
one(f.italicsCorrection);
one(f.partCount);
arr(f.partRecords, f.partCount);
 };
USE_ACQRES(GlyphAssembly/* table*/)

typedef struct {
Offset16   glyphAssemblyOffset;
uint16   variantCount;
MathGlyphVariantRecord*   mathGlyphVariantRecords;//[variantCount]
/// @brief
GlyphAssembly glyphAssembly;
}MathGlyphConstruction/* table*/;
ACQRES(MathGlyphConstruction/* table*/){
one((f.glyphAssemblyOffset));
one((f.variantCount));
arr(f.mathGlyphVariantRecords, f.variantCount);
offone(f.glyphAssembly,f.glyphAssemblyOffset); 
};
USE_ACQRES(MathGlyphConstruction/* table*/)

typedef struct {
UFWORD   minConnectorOverlap;
Offset16   vertGlyphCoverageOffset;
Offset16   horizGlyphCoverageOffset;
uint16   vertGlyphCount;
uint16   horizGlyphCount;
Offset16*   vertGlyphConstructionOffsets;//[vertGlyphCount]
Offset16*   horizGlyphConstructionOffsets;//[horizGlyphCount]

Coverage vertGlyphCoverage;
Coverage horizGlyphCoverage;
MathGlyphConstruction* vertGlyphConstruction;
MathGlyphConstruction* horizGlyphConstruction;
}MathVariants/* table*/;
ACQRES(MathVariants/* table*/){
one((f.minConnectorOverlap));
one((f.vertGlyphCoverageOffset));
one((f.horizGlyphCoverageOffset));
one((f.vertGlyphCount));
one((f.horizGlyphCount));
arr(f.vertGlyphConstructionOffsets, f.vertGlyphCount);
 arr(f.horizGlyphConstructionOffsets, f.horizGlyphCount);
 offone(f.vertGlyphCoverage,f.vertGlyphCoverageOffset);
 offone(f.horizGlyphCoverage,f.horizGlyphCoverageOffset);
 offmany(f.vertGlyphConstruction,f.vertGlyphConstructionOffsets,f.vertGlyphCount);
 offmany(f.horizGlyphConstruction,f.horizGlyphConstructionOffsets,f.horizGlyphCount);
 };
USE_ACQRES(MathVariants/* table*/)



typedef struct {
Offset16   mathItalicsCorrectionInfoOffset;
Offset16   mathTopAccentAttachmentOffset;
Offset16   extendedShapeCoverageOffset;
Offset16   mathKernInfoOffset;

/// @brief 
MathItalicsCorrectionInfo mathItalicsCorrectionInfo;
MathTopAccentAttachment mathTopAccentAttachment;
Coverage extendedShapeCoverage;
MathKernInfo mathKernInfo;
}MathGlyphInfo/* table*/;
ACQRES(MathGlyphInfo){
one(mathItalicsCorrectionInfoOffset);
one(mathTopAccentAttachmentOffset);
one(extendedShapeCoverageOffset);
one(mathKernInfoOffset);

offone(f.mathItalicsCorrectionInfo,f.mathItalicsCorrectionInfoOffset);
offone(f.mathTopAccentAttachment,f.mathTopAccentAttachmentOffset);
offone(f.extendedShapeCoverage,f.extendedShapeCoverageOffset);
offone(f.mathKernInfo,f.mathKernInfoOffset);
}
USE_ACQRES(MathGlyphInfo)

/*
 {
'math'	//Script tag to be used for features in math layout. The only language system supported with this tag is the default language system.
'ssty' //
'flac' //Flattened Accent Forms
'dtls'	//Dotless Forms

}OpenType Layout tags for math processing */
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   mathConstantsOffset;
Offset16   mathGlyphInfoOffset;
Offset16   mathVariantsOffset;
/// @brief 
MathConstants mathConstants;
MathGlyphInfo mathGlyphInfo;
MathVariants mathVariants;

}MATH;
ACQRES(MATH){
   one(f.majorVersion);
   one(f.minorVersion);
   one(f.mathConstantsOffset);
   one(f.mathGlyphInfoOffset);
   one(f.mathVariantsOffset);

   offone(f.mathConstants,f.mathConstantsOffset);
   offone(f.mathGlyphInfo,f.mathGlyphInfoOffset);
   offone(f.mathVariants,f.mathVariantsOffset);
}
USE_ACQRES(MATH)
#endif