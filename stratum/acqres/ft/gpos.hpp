typedef struct {
1   ;
2   ;
3   ;
4   ;
5   ;
6   ;
7   ;
8   ;
9   ;
}GposLookupType/* enumeration*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
}GPOS/* Header, version 1.0*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
Offset32   featureVariationsOffset;
}GPOS/* Header, version 1.1*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   valueFormat;
ValueRecord   valueRecord;
}SinglePosFormat1/* subtable*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   valueFormat;
uint16   valueCount;
ValueRecord*   valueRecords;//[valueCount]
}SinglePosFormat2/* subtable*/;
ACQRES(SinglePosFormat2/* subtable*/){
one(format);
one(coverageOffset);
one(valueFormat);
one(valueCount);
arr(valueRecords, valueCount);
 };
USE_ACQRES(SinglePosFormat2/* subtable*/)

typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   valueFormat1;
uint16   valueFormat2;
uint16   pairSetCount;
Offset16*   pairSetOffsets;//[pairSetCount]
}PairPosFormat1/* subtable*/;
ACQRES(PairPosFormat1/* subtable*/){
one(format);
one(coverageOffset);
one(valueFormat1);
one(valueFormat2);
one(pairSetCount);
arr(pairSetOffsets, pairSetCount);
 };
USE_ACQRES(PairPosFormat1/* subtable*/)

typedef struct {
uint16   pairValueCount;
PairValue*   pairValueRecords;//[pairValueCount]
}PairSet/* table*/;
ACQRES(PairSet/* table*/){
one(pairValueCount);
arr(pairValueRecords, pairValueCount);
 };
USE_ACQRES(PairSet/* table*/)

typedef struct {
uint16   secondGlyph;
ValueRecord   valueRecord1;
ValueRecord   valueRecord2;
}PairValue/* record*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   valueFormat1;
uint16   valueFormat2;
Offset16   classDef1Offset;
Offset16   classDef2Offset;
uint16   class1Count;
uint16   class2Count;
Class1*   class1Records;//[class1Count]
}PairPosFormat2/* subtable*/;
ACQRES(PairPosFormat2/* subtable*/){
one(format);
one(coverageOffset);
one(valueFormat1);
one(valueFormat2);
one(classDef1Offset);
one(classDef2Offset);
one(class1Count);
one(class2Count);
arr(class1Records, class1Count);
 };
USE_ACQRES(PairPosFormat2/* subtable*/)

typedef struct {
Class2*   class2Records;//[class2Count]
}Class1/* record*/;
ACQRES(Class1/* record*/){
arr(class2Records, class2Count);
 };
USE_ACQRES(Class1/* record*/)

typedef struct {
ValueRecord   valueRecord1;
ValueRecord   valueRecord2;
}Class2/* record*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   entryExitCount;
EntryExit*   entryExitRecords;//[entryExitCount]
}CursivePosFormat1/* subtable*/;
ACQRES(CursivePosFormat1/* subtable*/){
one(format);
one(coverageOffset);
one(entryExitCount);
arr(entryExitRecords, entryExitCount);
 };
USE_ACQRES(CursivePosFormat1/* subtable*/)

typedef struct {
Offset16   entryAnchorOffset;
Offset16   exitAnchorOffset;
}EntryExit/* record*/;
typedef struct {
uint16   format;
Offset16   markCoverageOffset;
Offset16   baseCoverageOffset;
uint16   markClassCount;
Offset16   markArrayOffset;
Offset16   baseArrayOffset;
}MarkBasePosFormat1/* subtable*/;
typedef struct {
uint16   baseCount;
BaseRecord*   baseRecords;//[baseCount]
}BaseArray/* table*/;
ACQRES(BaseArray/* table*/){
one(baseCount);
arr(baseRecords, baseCount);
 };
USE_ACQRES(BaseArray/* table*/)

typedef struct {
Offset16*   baseAnchorOffsets;//[markClassCount]
}BaseRecord;
ACQRES(BaseRecord){
arr(baseAnchorOffsets, markClassCount);
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
one(ligatureCount);
arr(ligatureAttachOffsets, ligatureCount);
 };
USE_ACQRES(LigatureArray/* table*/)

typedef struct {
uint16   componentCount;
ComponentRecord*   componentRecords;//[componentCount]
}LigatureAttach/* table*/;
ACQRES(LigatureAttach/* table*/){
one(componentCount);
arr(componentRecords, componentCount);
 };
USE_ACQRES(LigatureAttach/* table*/)

typedef struct {
Offset16*   ligatureAnchorOffsets;//[markClassCount]
}ComponentRecord;
ACQRES(ComponentRecord){
arr(ligatureAnchorOffsets, markClassCount);
 };
USE_ACQRES(ComponentRecord)

typedef struct {
uint16   format;
Offset16   mark1CoverageOffset;
Offset16   mark2CoverageOffset;
uint16   markClassCount;
Offset16   mark1ArrayOffset;
Offset16   mark2ArrayOffset;
}MarkMarkPosFormat1/* subtable*/;
typedef struct {
uint16   mark2Count;
Mark2*   mark2Records;//[mark2Count]
}Mark2Array/* table*/;
ACQRES(Mark2Array/* table*/){
one(mark2Count);
arr(mark2Records, mark2Count);
 };
USE_ACQRES(Mark2Array/* table*/)

typedef struct {
Offset16*   mark2AnchorOffsets;//[markClassCount]
}Mark2/* record*/;
ACQRES(Mark2/* record*/){
arr(mark2AnchorOffsets, markClassCount);
 };
USE_ACQRES(Mark2/* record*/)

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
typedef struct {
0x0001   X_PLACEMENT;
0x0002   Y_PLACEMENT;
0x0004   X_ADVANCE;
0x0008   Y_ADVANCE;
0x0010   X_PLACEMENT_DEVICE;
0x0020   Y_PLACEMENT_DEVICE;
0x0040   X_ADVANCE_DEVICE;
0x0080   Y_ADVANCE_DEVICE;
0xFF00   Reserved;
}ValueFormat/* flags*/;
typedef struct {
uint16   format;
int16   xCoordinate;
int16   yCoordinate;
}AnchorFormat1/* table*/;
typedef struct {
uint16   format;
int16   xCoordinate;
int16   yCoordinate;
uint16   anchorPoint;
}AnchorFormat2/* table*/;
typedef struct {
uint16   format;
int16   xCoordinate;
int16   yCoordinate;
Offset16   xDeviceOffset;
Offset16   yDeviceOffset;
}AnchorFormat3/* table*/;
typedef struct {
uint16   markCount;
MarkRecord*   markRecords;//[markCount]
}MarkArray/* table*/;
ACQRES(MarkArray/* table*/){
one(markCount);
arr(markRecords, markCount);
 };
USE_ACQRES(MarkArray/* table*/)

typedef struct {
uint16   markClass;
Offset16   markAnchorOffset;
}MarkRecord;
typedef struct {
    ;
00010000   0x00010000;
000A   TheScriptList;
001E   TheFeatureList;
002C   TheLookupList;
}Example/* 1*/;
typedef struct {
    ;
0001   1;
0008   LowerSubscriptsCoverage;
0002   0x0002;
   ValueRecord;
FFB0   -80;
    ;
0002   2;
0001   1;
*   rangeRecords;//[0]
01B3   ZeroSubscriptGlyphID;
01BC   NineSubscriptGlyphID;
0000   0;
}Example/* 2*/;
ACQRES(Example/* 2*/){
one();
one(1);
one(LowerSubscriptsCoverage);
one(0x0002);
one(ValueRecord);
one(-80);
one();
one(2);
one(1);
arr(rangeRecords, 0);
 one(ZeroSubscriptGlyphID);
one(NineSubscriptGlyphID);
one(0);
};
USE_ACQRES(Example/* 2*/)

typedef struct {
    ;
0002   2;
0014   DashSpacingCoverage;
0005   0x0005;
0003   3;
*   valueRecords;//[0]
0032   50;
0032   50;
*   valueRecords;//[1]
0019   25;
0019   25;
*   valueRecords;//[2]
000A   10;
000A   10;
    ;
0001   1;
0003   3;
004F   DashGlyphID;
0125   EnDashGlyphID;
0129   EmDashGlyphID;
}Example/* 3*/;
ACQRES(Example/* 3*/){
one();
one(2);
one(DashSpacingCoverage);
one(0x0005);
one(3);
arr(valueRecords, 0);
 one(50);
one(50);
arr(valueRecords, 1);
 one(25);
one(25);
arr(valueRecords, 2);
 one(10);
one(10);
one();
one(1);
one(3);
one(DashGlyphID);
one(EnDashGlyphID);
one(EmDashGlyphID);
};
USE_ACQRES(Example/* 3*/)

typedef struct {
    ;
0001   1;
001E   PairKerningCoverage;
0004   0x0004;
0001   0x0001;
0002   2;
000E   PairSetTable;
0016   PairSetTable;
    ;
0001   1;
*   pairValueRecords;//[0]
0059   LowercaseOGlyphID;
   valueRecord1;
FFE2   -30;
   valueRecord2;
FFEC   -20;
    ;
0001   1;
*   pairValueRecords;//[0]
0059   LowercaseOGlyphID;
   valueRecord1;
FFD8   -40;
   valueRecord2;
FFE7   -25;
    ;
0001   1;
0002   2;
002D   UppercasePGlyphID;
0031   UppercaseTGlyphID;
}Example/* 4*/;
ACQRES(Example/* 4*/){
one();
one(1);
one(PairKerningCoverage);
one(0x0004);
one(0x0001);
one(2);
one(PairSetTable);
one(PairSetTable);
one();
one(1);
arr(pairValueRecords, 0);
 one(LowercaseOGlyphID);
one(valueRecord1);
one(-30);
one(valueRecord2);
one(-20);
one();
one(1);
arr(pairValueRecords, 0);
 one(LowercaseOGlyphID);
one(valueRecord1);
one(-40);
one(valueRecord2);
one(-25);
one();
one(1);
one(2);
one(UppercasePGlyphID);
one(UppercaseTGlyphID);
};
USE_ACQRES(Example/* 4*/)

typedef struct {
    ;
0002   2;
0018   PunctKerningCoverage;
0004   0x0004;
0000   0;
0022   LowercaseClassDef;
0032   PunctuationClassDef;
0002   2;
0002   2;
*   class1Records;//[0]
*   class2Records;//[0]
   valueRecord1;
0000   0;
*   class2Records;//[1]
   valueRecord1;
0000   0;
*   class1Records;//[1]
*   class2Records;//[0]
   valueRecord1;
0000   0;
*   class2Records;//[1]
   valueRecord1;
FFCE   -50;
    ;
0001   1;
0003   3;
0046   LowercaseVGlyphID;
0047   LowercaseWGlyphID;
0049   LowercaseYGlyphID;
    ;
0002   2;
0002   2;
*   classRangeRecords;//[0]
0046   LowercaseVGlyphID;
0047   LowercaseWGlyphID;
0001   1;
*   classRangeRecords;//[1]
0049   LowercaseYGlyphID;
0049   LowercaseYGlyphID;
0001   1;
    ;
0002   2;
0001   1;
*   classRangeRecords;//[0]
006A   PeriodPunctGlyphID;
006B   CommaPunctGlyphID;
0001   1;
}Example/* 5*/;
ACQRES(Example/* 5*/){
one();
one(2);
one(PunctKerningCoverage);
one(0x0004);
one(0);
one(LowercaseClassDef);
one(PunctuationClassDef);
one(2);
one(2);
arr(class1Records, 0);
 arr(class2Records, 0);
 one(valueRecord1);
one(0);
arr(class2Records, 1);
 one(valueRecord1);
one(0);
arr(class1Records, 1);
 arr(class2Records, 0);
 one(valueRecord1);
one(0);
arr(class2Records, 1);
 one(valueRecord1);
one(-50);
one();
one(1);
one(3);
one(LowercaseVGlyphID);
one(LowercaseWGlyphID);
one(LowercaseYGlyphID);
one();
one(2);
one(2);
arr(classRangeRecords, 0);
 one(LowercaseVGlyphID);
one(LowercaseWGlyphID);
one(1);
arr(classRangeRecords, 1);
 one(LowercaseYGlyphID);
one(LowercaseYGlyphID);
one(1);
one();
one(2);
one(1);
arr(classRangeRecords, 0);
 one(PeriodPunctGlyphID);
one(CommaPunctGlyphID);
one(1);
};
USE_ACQRES(Example/* 5*/)

typedef struct {
    ;
0001   1;
000E   DiagonalWritingCoverage;
0002   2;
*   entryExitRecords;//[0]
0016   KafEntryAnchor;
001C   KafExitAnchor;
*   entryExitRecords;//[1]
0022   HaEntryAnchor;
0028   HaExitAnchor;
    ;
0001   1;
0002   2;
0203   KafGlyphID;
027E   HaGlyphID;
    ;
0001   1;
05DC   1500;
002C   44;
    ;
0001   1;
0000   0;
FFEC   -20;
    ;
0001   1;
05DC   1500;
002C   44;
    ;
0001   1;
0000   0;
FFEC   -20;
}Example/* 6*/;
ACQRES(Example/* 6*/){
one();
one(1);
one(DiagonalWritingCoverage);
one(2);
arr(entryExitRecords, 0);
 one(KafEntryAnchor);
one(KafExitAnchor);
arr(entryExitRecords, 1);
 one(HaEntryAnchor);
one(HaExitAnchor);
one();
one(1);
one(2);
one(KafGlyphID);
one(HaGlyphID);
one();
one(1);
one(1500);
one(44);
one();
one(1);
one(0);
one(-20);
one();
one(1);
one(1500);
one(44);
one();
one(1);
one(0);
one(-20);
};
USE_ACQRES(Example/* 6*/)

typedef struct {
    ;
0001   1;
000C   MarkGlyphsCoverage;
0014   BaseGlyphsCoverage;
0002   2;
001A   MarkGlyphsArray;
0030   BaseGlyphsArray;
    ;
0001   1;
0002   2;
0333   fathatanMarkGlyphID;
033F   kasraMarkGlyphID;
    ;
0001   1;
0001   1;
0190   tahBaseGlyphID;
    ;
0002   2;
*   markRecords;//[0]
0000   0;
000A   fathatanMarkAnchor;
*   markRecords;//[1]
0001   1;
0010   kasraMarkAnchor;
    ;
0001   1;
015A   346;
FF9E   -98;
    ;
0001   1;
0105   261;
0058   88;
    ;
0001   1;
*   baseRecords;//[0]
0006   AboveBaseAnchor;
000C   BelowBaseAnchor;
    ;
0001   1;
033E   830;
0640   1600;
    ;
0001   1;
033E   830;
FFAD   -83;
}Example/* 7*/;
ACQRES(Example/* 7*/){
one();
one(1);
one(MarkGlyphsCoverage);
one(BaseGlyphsCoverage);
one(2);
one(MarkGlyphsArray);
one(BaseGlyphsArray);
one();
one(1);
one(2);
one(fathatanMarkGlyphID);
one(kasraMarkGlyphID);
one();
one(1);
one(1);
one(tahBaseGlyphID);
one();
one(2);
arr(markRecords, 0);
 one(0);
one(fathatanMarkAnchor);
arr(markRecords, 1);
 one(1);
one(kasraMarkAnchor);
one();
one(1);
one(346);
one(-98);
one();
one(1);
one(261);
one(88);
one();
one(1);
arr(baseRecords, 0);
 one(AboveBaseAnchor);
one(BelowBaseAnchor);
one();
one(1);
one(830);
one(1600);
one();
one(1);
one(830);
one(-83);
};
USE_ACQRES(Example/* 7*/)

typedef struct {
    ;
0001   1;
000C   MarkGlyphsCoverage;
0014   LigGlyphsCoverage;
0002   2;
001A   MarkGlyphsArray;
0030   LigGlyphsArray;
    ;
0001   1;
0002   2;
033C   sukunMarkGlyphID;
033F   kasratanMarkGlyphID;
    ;
0001   1;
0001   1;
0234   LamWithMeemWithJeem;
    ;
0002   2;
*   markRecords;//[0]
0000   0;
000A   sukunMarkAnchor;
*   markRecords;//[1]
0001   1;
0010   kasratanMarkAnchor;
    ;
0001   1;
015A   346;
FF9E   -98;
    ;
0001   1;
0105   261;
01E8   488;
    ;
0001   1;
0004   LamWithMeemWithJeemLigAttach;
    ;
0003   3;
*   componentRecords;//[0]
000E   AboveLamAnchor;
0000   NULL;
*   componentRecords;//[1]
0000   NULL;
0014   BelowMeemAnchor;
*   componentRecords;//[2]
0000   NULL;
0000   NULL;
    ;
0001   1;
0271   625;
0708   1800;
    ;
0001   1;
0178   376;
FE90   -368;
}Example/* 8*/;
ACQRES(Example/* 8*/){
one();
one(1);
one(MarkGlyphsCoverage);
one(LigGlyphsCoverage);
one(2);
one(MarkGlyphsArray);
one(LigGlyphsArray);
one();
one(1);
one(2);
one(sukunMarkGlyphID);
one(kasratanMarkGlyphID);
one();
one(1);
one(1);
one(LamWithMeemWithJeem);
one();
one(2);
arr(markRecords, 0);
 one(0);
one(sukunMarkAnchor);
arr(markRecords, 1);
 one(1);
one(kasratanMarkAnchor);
one();
one(1);
one(346);
one(-98);
one();
one(1);
one(261);
one(488);
one();
one(1);
one(LamWithMeemWithJeemLigAttach);
one();
one(3);
arr(componentRecords, 0);
 one(AboveLamAnchor);
one(NULL);
arr(componentRecords, 1);
 one(NULL);
one(BelowMeemAnchor);
arr(componentRecords, 2);
 one(NULL);
one(NULL);
one();
one(1);
one(625);
one(1800);
one();
one(1);
one(376);
one(-368);
};
USE_ACQRES(Example/* 8*/)

typedef struct {
    ;
0001   1;
000C   Mark1GlyphsCoverage;
0012   Mark2GlyphsCoverage;
0001   1;
0018   Mark1GlyphsArray;
0024   Mark2GlyphsArray;
    ;
0001   1;
0001   1;
0296   dammaMarkGlyphID;
    ;
0001   1;
0001   1;
0289   hamzaMarkGlyphID;
    ;
0001   1;
*   markRecords;//[0]
0000   0;
0006   dammaMarkAnchor;
    ;
0001   1;
00BD   189;
FF99   -103;
    ;
0001   1;
*   mark2Records;//[0]
0004   AboveMark2Anchor;
    ;
0001   1;
00DD   221;
012D   301;
}Example/* 9*/;
ACQRES(Example/* 9*/){
one();
one(1);
one(Mark1GlyphsCoverage);
one(Mark2GlyphsCoverage);
one(1);
one(Mark1GlyphsArray);
one(Mark2GlyphsArray);
one();
one(1);
one(1);
one(dammaMarkGlyphID);
one();
one(1);
one(1);
one(hamzaMarkGlyphID);
one();
one(1);
arr(markRecords, 0);
 one(0);
one(dammaMarkAnchor);
one();
one(1);
one(189);
one(-103);
one();
one(1);
arr(mark2Records, 0);
 one(AboveMark2Anchor);
one();
one(1);
one(221);
one(301);
};
USE_ACQRES(Example/* 9*/)

typedef struct {
    ;
0001   1;
0008   WordCoverage;
0001   1;
000E   WordPosRuleSet;
    ;
0001   1;
0001   1;
02A6   hehInitialGlyphID;
    ;
0001   1;
0004   WordPosRule;
    ;
0003   3;
0001   1;
02DD   thalFinalGlyphID;
02C6   hehIsolatedGlyphID;
   ;
0002   2;
0001   1;
}Example/* 10*/;
typedef struct {
    ;
0002   2;
0012   MoveAccentsCoverage;
0020   MoveAccentsClassDef;
0005   5;
0000   NULL;
0060   UCWideOverhangPosClass1Set;
0070   UCNarrowOverhangPosClass2Set;
0000   NULL;
0000   NULL;
    ;
0001   1;
0005   5;
0029   UppercaseFGlyphID;
0033   UppercasePGlyphID;
0037   UppercaseTGlyphID;
0039   UppercaseVGlyphID;
003A   UppercaseWGlyphID;
    ;
0002   2;
000A   10;
*   classRangeRecords;//[0]
0029   UppercaseFGlyphID;
0029   UppercaseFGlyphID;
0002   2;
*   classRangeRecords;//[1]
0033   UppercasePGlyphID;
0033   UppercasePGlyphID;
0002   2;
*   classRangeRecords;//[2]
0037   UppercaseTGlyphID;
0037   UppercaseTGlyphID;
0001   1;
*   classRangeRecords;//[3]
0039   UppercaseVGlyphID;
003A   UppercaseWGlyphID;
0001   1;
*   classRangeRecords;//[4]
0042   LowercaseAGlyphID;
0042   LowercaseAGlyphID;
0003   3;
*   classRangeRecords;//[5]
0046   LowercaseEGlyphID;
0046   LowercaseEGlyphID;
0003   3;
*   classRangeRecords;//[6]
004A   LowercaseIGlyphID;
004A   LowercaseIGlyphID;
0003   3;
*   classRangeRecords;//[7]
0051   LowercaseOGlyphID;
0051   LowercaseOGlyphID;
0003   3;
*   classRangeRecords;//[8]
0056   LowercaseUGlyphID;
0056   LowercaseUGlyphID;
0003   3;
*   classRangeRecords;//[9]
00F5   TildeAccentGlyphID;
00F6   UmlautAccentGlyphID;
0004   4;
    ;
0001   1;
0004   UCWideOverhangPosClassRule;
    ;
0003   3;
0001   1;
0003   3;
0004   4;
*   seqLookupRecords;//[0]
0002   2;
0001   1;
    ;
0001   1;
0004   UCNarrowOverhangPosClassRule;
    ;
0003   3;
0001   1;
0003   3;
0004   4;
*   seqLookupRecords;//[0]
0000   0;
0002   2;
}Example/* 11*/;
ACQRES(Example/* 11*/){
one();
one(2);
one(MoveAccentsCoverage);
one(MoveAccentsClassDef);
one(5);
one(NULL);
one(UCWideOverhangPosClass1Set);
one(UCNarrowOverhangPosClass2Set);
one(NULL);
one(NULL);
one();
one(1);
one(5);
one(UppercaseFGlyphID);
one(UppercasePGlyphID);
one(UppercaseTGlyphID);
one(UppercaseVGlyphID);
one(UppercaseWGlyphID);
one();
one(2);
one(10);
arr(classRangeRecords, 0);
 one(UppercaseFGlyphID);
one(UppercaseFGlyphID);
one(2);
arr(classRangeRecords, 1);
 one(UppercasePGlyphID);
one(UppercasePGlyphID);
one(2);
arr(classRangeRecords, 2);
 one(UppercaseTGlyphID);
one(UppercaseTGlyphID);
one(1);
arr(classRangeRecords, 3);
 one(UppercaseVGlyphID);
one(UppercaseWGlyphID);
one(1);
arr(classRangeRecords, 4);
 one(LowercaseAGlyphID);
one(LowercaseAGlyphID);
one(3);
arr(classRangeRecords, 5);
 one(LowercaseEGlyphID);
one(LowercaseEGlyphID);
one(3);
arr(classRangeRecords, 6);
 one(LowercaseIGlyphID);
one(LowercaseIGlyphID);
one(3);
arr(classRangeRecords, 7);
 one(LowercaseOGlyphID);
one(LowercaseOGlyphID);
one(3);
arr(classRangeRecords, 8);
 one(LowercaseUGlyphID);
one(LowercaseUGlyphID);
one(3);
arr(classRangeRecords, 9);
 one(TildeAccentGlyphID);
one(UmlautAccentGlyphID);
one(4);
one();
one(1);
one(UCWideOverhangPosClassRule);
one();
one(3);
one(1);
one(3);
one(4);
arr(seqLookupRecords, 0);
 one(2);
one(1);
one();
one(1);
one(UCNarrowOverhangPosClassRule);
one();
one(3);
one(1);
one(3);
one(4);
arr(seqLookupRecords, 0);
 one(0);
one(2);
};
USE_ACQRES(Example/* 11*/)

typedef struct {
    ;
0003   3;
0003   3;
0001   1;
0010   XhtDescLCCoverage;
003C   MathSignCoverage;
0044   LCCoverage;
*   seqLookupRecords;//[0]
0001   1;
0001   1;
    ;
0001   1;
0014   20;
0033   LCaGlyphID;
0035   LCcGlyphID;
0037   LCeGlyphID;
0039   LCgGlyphID;
003B   LCiGlyphID;
003C   LCjGlyphID;
003F   LCmGlyphID;
0040   LCnGlyphID;
0041   LCoGlyphID;
0042   LCpGlyphID;
0043   LCqGlyphID;
0044   LCrGlyphID;
0045   LCsGlyphID;
0046   LCtGlyphID;
0047   LCuGlyphID;
0048   LCvGlyphID;
0049   LCwGlyphID;
004A   LCxGlyphID;
004B   LCyGlyphID;
004C   LCzGlyphID;
    ;
0001   1;
0002   2;
011E   EqualsSignGlyphID;
012D   PlusSignGlyphID;
    ;
0002   2;
0001   1;
*   rangeRecords;//[0]
0033   LCaGlyphID;
004C   LCzGlyphID;
0000   0;
}Example/* 12*/;
ACQRES(Example/* 12*/){
one();
one(3);
one(3);
one(1);
one(XhtDescLCCoverage);
one(MathSignCoverage);
one(LCCoverage);
arr(seqLookupRecords, 0);
 one(1);
one(1);
one();
one(1);
one(20);
one(LCaGlyphID);
one(LCcGlyphID);
one(LCeGlyphID);
one(LCgGlyphID);
one(LCiGlyphID);
one(LCjGlyphID);
one(LCmGlyphID);
one(LCnGlyphID);
one(LCoGlyphID);
one(LCpGlyphID);
one(LCqGlyphID);
one(LCrGlyphID);
one(LCsGlyphID);
one(LCtGlyphID);
one(LCuGlyphID);
one(LCvGlyphID);
one(LCwGlyphID);
one(LCxGlyphID);
one(LCyGlyphID);
one(LCzGlyphID);
one();
one(1);
one(2);
one(EqualsSignGlyphID);
one(PlusSignGlyphID);
one();
one(2);
one(1);
arr(rangeRecords, 0);
 one(LCaGlyphID);
one(LCzGlyphID);
one(0);
};
USE_ACQRES(Example/* 12*/)

typedef struct {
    ;
0001   1;
0001   1;
}Example/* 13*/;
typedef struct {
    ;
0001   1;
000E   Cov;
0099   0x0099;
   valueRecord;
0050   80;
00D2   210;
0018   XPlaDeviceTable;
0020   YAdvDeviceTable;
    ;
0002   2;
0001   1;
*   rangeRecords;//[0]
00C8   200;
00D1   209;
0000   0;
    ;
000B   11;
000F   15;
0001   1;
    1;
    1;
    1;
    1;
5540   1;
    ;
000B   11;
000F   15;
0001   1;
    1;
    1;
    1;
    1;
5540   1;
}Example/* 14*/;
ACQRES(Example/* 14*/){
one();
one(1);
one(Cov);
one(0x0099);
one(valueRecord);
one(80);
one(210);
one(XPlaDeviceTable);
one(YAdvDeviceTable);
one();
one(2);
one(1);
arr(rangeRecords, 0);
 one(200);
one(209);
one(0);
one();
one(11);
one(15);
one(1);
one(1);
one(1);
one(1);
one(1);
one(1);
one();
one(11);
one(15);
one(1);
one(1);
one(1);
one(1);
one(1);
one(1);
};
USE_ACQRES(Example/* 14*/)

typedef struct {
    ;
0001   1;
00BD   189;
FF99   -103;
}Example/* 15*/;
typedef struct {
    ;
0002   2;
0142   322;
0384   900;
000D   13;
}Example/* 16*/;
typedef struct {
    ;
0003   3;
0117   279;
0515   1301;
000A   XDevice;
0014   YDevice;
    ;
000C   12;
0011   17;
0002   2;
    1;
    1;
    1;
1111   1;
    2;
2200   2;
    ;
000C   12;
0011   17;
0002   2;
    1;
    1;
    1;
1111   1;
    2;
2200   2;
}Example/* 17*/;
typedef struct {
    ;
0002   2;
*   markRecords;//[0]
0000   0;
000A   graveMarkAnchor;
*   markRecords;//[1]
0001   1;
0010   cedillaMarkAnchor;
}Example/* 18*/;
ACQRES(Example/* 18*/){
one();
one(2);
arr(markRecords, 0);
 one(0);
one(graveMarkAnchor);
arr(markRecords, 1);
 one(1);
one(cedillaMarkAnchor);
};
USE_ACQRES(Example/* 18*/)

