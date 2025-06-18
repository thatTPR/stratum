typedef struct {
FWORD   value;
Offset16   deviceOffset;
}MathValueRecord;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   mathConstantsOffset;
Offset16   mathGlyphInfoOffset;
Offset16   mathVariantsOffset;
}MATH/* Header*/;
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
Offset16   mathItalicsCorrectionInfoOffset;
Offset16   mathTopAccentAttachmentOffset;
Offset16   extendedShapeCoverageOffset;
Offset16   mathKernInfoOffset;
}MathGlyphInfo/* table*/;
typedef struct {
Offset16   italicsCorrectionCoverageOffset;
uint16   italicsCorrectionCount;
MathValueRecord*   italicsCorrection;//[italicsCorrectionCount]
}MathItalicsCorrectionInfo/* table*/;
ACQRES(MathItalicsCorrectionInfo/* table*/){
one(italicsCorrectionCoverageOffset);
one(italicsCorrectionCount);
arr(italicsCorrection, italicsCorrectionCount);
 };
USE_ACQRES(MathItalicsCorrectionInfo/* table*/)

typedef struct {
Offset16   topAccentCoverageOffset;
uint16   topAccentAttachmentCount;
MathValueRecord*   topAccentAttachment;//[topAccentAttachmentCount]
}MathTopAccentAttachment/* table*/;
ACQRES(MathTopAccentAttachment/* table*/){
one(topAccentCoverageOffset);
one(topAccentAttachmentCount);
arr(topAccentAttachment, topAccentAttachmentCount);
 };
USE_ACQRES(MathTopAccentAttachment/* table*/)

typedef struct {
Offset16   mathKernCoverageOffset;
uint16   mathKernCount;
MathKernInfoRecord*   mathKernInfoRecords;//[mathKernCount]
}MathKernInfo/* table*/;
ACQRES(MathKernInfo/* table*/){
one(mathKernCoverageOffset);
one(mathKernCount);
arr(mathKernInfoRecords, mathKernCount);
 };
USE_ACQRES(MathKernInfo/* table*/)

typedef struct {
Offset16   topRightMathKernOffset;
Offset16   topLeftMathKernOffset;
Offset16   bottomRightMathKernOffset;
Offset16   bottomLeftMathKernOffset;
}MathKernInfoRecord;
typedef struct {
uint16   heightCount;
MathValueRecord*   correctionHeight;//[heightCount]
MathValueRecord*   kernValues;//[heightCount + 1]
}MathKern/* table*/;
ACQRES(MathKern/* table*/){
one(heightCount);
arr(correctionHeight, heightCount);
 arr(kernValues, heightCount + 1);
 };
USE_ACQRES(MathKern/* table*/)

typedef struct {
UFWORD   minConnectorOverlap;
Offset16   vertGlyphCoverageOffset;
Offset16   horizGlyphCoverageOffset;
uint16   vertGlyphCount;
uint16   horizGlyphCount;
Offset16*   vertGlyphConstructionOffsets;//[vertGlyphCount]
Offset16*   horizGlyphConstructionOffsets;//[horizGlyphCount]
}MathVariants/* table*/;
ACQRES(MathVariants/* table*/){
one(minConnectorOverlap);
one(vertGlyphCoverageOffset);
one(horizGlyphCoverageOffset);
one(vertGlyphCount);
one(horizGlyphCount);
arr(vertGlyphConstructionOffsets, vertGlyphCount);
 arr(horizGlyphConstructionOffsets, horizGlyphCount);
 };
USE_ACQRES(MathVariants/* table*/)

typedef struct {
Offset16   glyphAssemblyOffset;
uint16   variantCount;
MathGlyphVariantRecord*   mathGlyphVariantRecords;//[variantCount]
}MathGlyphConstruction/* table*/;
ACQRES(MathGlyphConstruction/* table*/){
one(glyphAssemblyOffset);
one(variantCount);
arr(mathGlyphVariantRecords, variantCount);
 };
USE_ACQRES(MathGlyphConstruction/* table*/)

typedef struct {
uint16   variantGlyph;
UFWORD   advanceMeasurement;
}MathGlyphVariantRecord;
typedef struct {
MathValueRecord   italicsCorrection;
uint16   partCount;
GlyphPart*   partRecords;//[partCount]
}GlyphAssembly/* table*/;
ACQRES(GlyphAssembly/* table*/){
one(italicsCorrection);
one(partCount);
arr(partRecords, partCount);
 };
USE_ACQRES(GlyphAssembly/* table*/)

typedef struct {
uint16   glyphID;
UFWORD   startConnectorLength;
UFWORD   endConnectorLength;
UFWORD   fullAdvance;
uint16   partFlags;
}GlyphPart/* record*/;
typedef struct {
''math'   Script tag to be used for features in math layout. The only language system supported with this tag is the default language system.;
   Math Script-style Alternates;
   Flattened Accent Forms;
   Dotless Forms;
}OpenType/* Layout tags for math processing*/;
