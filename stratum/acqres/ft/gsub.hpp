typedef struct {
1   ;
2   ;
3   ;
4   ;
5   ;
6   ;
7   ;
8   ;
}GsubLookupType/* enumeration*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
}GSUB/* Header, version 1.0*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   scriptListOffset;
Offset16   featureListOffset;
Offset16   lookupListOffset;
Offset32   featureVariationsOffset;
}GSUB/* Header, version 1.1*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
int16   deltaGlyphID;
}SingleSubstFormat1/* subtable*/;
typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   glyphCount;
uint16*   substituteGlyphIDs;//[glyphCount]
}SingleSubstFormat2/* subtable*/;
ACQRES(SingleSubstFormat2/* subtable*/){
one(format);
one(coverageOffset);
one(glyphCount);
arr(substituteGlyphIDs, glyphCount);
 };
USE_ACQRES(SingleSubstFormat2/* subtable*/)

typedef struct {
uint16   glyphCount;
uint16*   substituteGlyphIDs;//[glyphCount]
}Sequence/* table*/;
ACQRES(Sequence/* table*/){
one(glyphCount);
arr(substituteGlyphIDs, glyphCount);
 };
USE_ACQRES(Sequence/* table*/)

typedef struct {
uint16   glyphCount;
uint16*   alternateGlyphIDs;//[glyphCount]
}AlternateSet/* table*/;
ACQRES(AlternateSet/* table*/){
one(glyphCount);
arr(alternateGlyphIDs, glyphCount);
 };
USE_ACQRES(AlternateSet/* table*/)

typedef struct {
uint16   format;
Offset16   coverageOffset;
uint16   ligatureSetCount;
Offset16*   ligatureSetOffsets;//[ligatureSetCount]
}LigatureSubstFormat1/* subtable*/;
ACQRES(LigatureSubstFormat1/* subtable*/){
one(format);
one(coverageOffset);
one(ligatureSetCount);
arr(ligatureSetOffsets, ligatureSetCount);
 };
USE_ACQRES(LigatureSubstFormat1/* subtable*/)

typedef struct {
uint16   ligatureCount;
Offset16*   ligatureOffsets;//[LigatureCount]
}LigatureSet/* table*/;
ACQRES(LigatureSet/* table*/){
one(ligatureCount);
arr(ligatureOffsets, LigatureCount);
 };
USE_ACQRES(LigatureSet/* table*/)

typedef struct {
uint16   ligatureGlyph;
uint16   componentCount;
uint16*   componentGlyphIDs;//[componentCount - 1]
}Ligature/* table*/;
ACQRES(Ligature/* table*/){
one(ligatureGlyph);
one(componentCount);
arr(componentGlyphIDs, componentCount - 1);
 };
USE_ACQRES(Ligature/* table*/)

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
}ReverseChainSingleSubstFormat1/* subtable*/;
ACQRES(ReverseChainSingleSubstFormat1/* subtable*/){
one(format);
one(coverageOffset);
one(backtrackGlyphCount);
arr(backtrackCoverageOffsets, backtrackGlyphCount);
 one(lookaheadGlyphCount);
arr(lookaheadCoverageOffsets, lookaheadGlyphCount);
 one(glyphCount);
arr(substituteGlyphIDs, glyphCount);
 };
USE_ACQRES(ReverseChainSingleSubstFormat1/* subtable*/)

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
0006   LiningNumeralCoverage;
00C0   192;
    ;
0002   2;
    1;
*   rangeRecords;//[0]
004E   78;
0058   87;
0000   0;
}Example/* 2*/;
ACQRES(Example/* 2*/){
one();
one(1);
one(LiningNumeralCoverage);
one(192);
one();
one(2);
one(1);
arr(rangeRecords, 0);
 one(78);
one(87);
one(0);
};
USE_ACQRES(Example/* 2*/)

typedef struct {
    ;
0002   2;
000E   VerticalPunctuationCoverage;
0004   4;
0131   VerticalOpenBracketGlyph;
0135   VerticalClosedBracketGlyph;
013E   VerticalOpenParenthesisGlyph;
0143   VerticalClosedParenthesisGlyph;
    ;
0001   1;
0004   4;
003C   HorizontalOpenBracketGlyph;
0040   HorizontalClosedBracketGlyph;
004B   HorizontalOpenParenthesisGlyph;
004F   HorizontalClosedParenthesisGlyph;
}Example/* 3*/;
typedef struct {
    ;
0001   1;
0008   FfiDecompCoverage;
0001   1;
000E   FfiDecompSequence;
    ;
0001   1;
0001   1;
00F1   ffiGlyphID;
    ;
0003   3;
001A   fGlyphID;
001A   fGlyphID;
001D   iGlyphID;
}Example/* 4*/;
typedef struct {
    ;
0001   1;
0008   AltAmpersandCoverage;
0001   1;
000E   AltAmpersandSet;
    ;
0001   1;
0001   1;
003A   DefaultAmpersandGlyphID;
    ;
0002   2;
00C9   AltAmpersand1GlyphID;
00CA   AltAmpersand2GlyphID;
}Example/* 5*/;
typedef struct {
    ;
0001   1;
000A   LigaturesCoverage;
0002   2;
0014   ELigaturesSet;
0020   FLigaturesSet;
    ;
0002   2;
0001   1;
*   rangeRecords;//[0]
0019   eGlyphID;
001A   fGlyphID;
0000   0;
    ;
0001   1;
0004   etcLigature;
    ;
015B   etcGlyphID;
0003   3;
0028   tGlyphID;
0017   cGlyphID;
    ;
0002   2;
0006   ffiLigature;
000E   fiLigature;
    ;
00F1   ffiGlyphID;
0003   3;
001A   fGlyphID;
001D   iGlyphID;
    ;
00F0   fiGlyphID;
0002   2;
001D   iGlyphID;
}Example/* 6*/;
ACQRES(Example/* 6*/){
one();
one(1);
one(LigaturesCoverage);
one(2);
one(ELigaturesSet);
one(FLigaturesSet);
one();
one(2);
one(1);
arr(rangeRecords, 0);
 one(eGlyphID);
one(fGlyphID);
one(0);
one();
one(1);
one(etcLigature);
one();
one(etcGlyphID);
one(3);
one(tGlyphID);
one(cGlyphID);
one();
one(2);
one(ffiLigature);
one(fiLigature);
one();
one(ffiGlyphID);
one(3);
one(fGlyphID);
one(iGlyphID);
one();
one(fiGlyphID);
one(2);
one(iGlyphID);
};
USE_ACQRES(Example/* 6*/)

typedef struct {
    ;
0001   1;
000A   DashCoverage;
0002   2;
0012   SpaceAndDashSubRuleSet;
0020   DashAndSpaceSubRuleSet;
    ;
0001   1;
0002   2;
0028   SpaceGlyph;
005D   DashGlyph;
    ;
0001   1;
0004   SpaceAndDashSubRule;
    ;
0002   2;
0001   1;
005D   DashGlyph;
*   seqLookupRecords;//[0]
0000   0;
0001   1;
    ;
0001   1;
0004   DashAndSpaceSubRule;
    ;
0002   2;
0001   1;
0028   SpaceGlyph;
*   seqLookupRecords;//[0]
0001   1;
0001   1;
}Example/* 7*/;
ACQRES(Example/* 7*/){
one();
one(1);
one(DashCoverage);
one(2);
one(SpaceAndDashSubRuleSet);
one(DashAndSpaceSubRuleSet);
one();
one(1);
one(2);
one(SpaceGlyph);
one(DashGlyph);
one();
one(1);
one(SpaceAndDashSubRule);
one();
one(2);
one(1);
one(DashGlyph);
arr(seqLookupRecords, 0);
 one(0);
one(1);
one();
one(1);
one(DashAndSpaceSubRule);
one();
one(2);
one(1);
one(SpaceGlyph);
arr(seqLookupRecords, 0);
 one(1);
one(1);
};
USE_ACQRES(Example/* 7*/)

typedef struct {
    ;
0002   2;
0010   SetMarksHighCoverage;
001C   SetMarksHighClassDef;
0004   4;
0000   NULL;
0000   NULL;
0032   SetMarksHighSubClassSet2;
0040   SetMarksVeryHighSubClassSet3;
    ;
0001   1;
0004   4;
0030   tahGlyphID;
0031   dhahGlyphID;
0040   cafGlyphID;
0041   gafGlyphID;
    ;
0002   2;
0003   3;
*   classRangeRecords;//[0]
0030   tahGlyphID;
0031   dhahGlyphID;
0002   2;
*   classRangeRecords;//[1]
0040   cafGlyphID;
0041   gafGlyphID;
0003   3;
*   classRangeRecords;//[2]
00D2   fathatanDefaultGlyphID;
00D3   dammatanDefaultGlyphID;
0001   1;
    ;
0001   1;
0004   SetMarksHighSubClassRule2;
    ;
0002   2;
0001   1;
0001   1;
*   seqLookupRecords;//[0]
0001   1;
0001   1;
    ;
0001   1;
0004   SetMarksVeryHighSubClassRule3;
    ;
0002   2;
0001   1;
0001   1;
*   seqLookupRecords;//[0]
0001   1;
0002   2;
}Example/* 8*/;
ACQRES(Example/* 8*/){
one();
one(2);
one(SetMarksHighCoverage);
one(SetMarksHighClassDef);
one(4);
one(NULL);
one(NULL);
one(SetMarksHighSubClassSet2);
one(SetMarksVeryHighSubClassSet3);
one();
one(1);
one(4);
one(tahGlyphID);
one(dhahGlyphID);
one(cafGlyphID);
one(gafGlyphID);
one();
one(2);
one(3);
arr(classRangeRecords, 0);
 one(tahGlyphID);
one(dhahGlyphID);
one(2);
arr(classRangeRecords, 1);
 one(cafGlyphID);
one(gafGlyphID);
one(3);
arr(classRangeRecords, 2);
 one(fathatanDefaultGlyphID);
one(dammatanDefaultGlyphID);
one(1);
one();
one(1);
one(SetMarksHighSubClassRule2);
one();
one(2);
one(1);
one(1);
arr(seqLookupRecords, 0);
 one(1);
one(1);
one();
one(1);
one(SetMarksVeryHighSubClassRule3);
one();
one(2);
one(1);
one(1);
arr(seqLookupRecords, 0);
 one(1);
one(2);
};
USE_ACQRES(Example/* 8*/)

typedef struct {
    ;
0003   3;
0003   3;
0002   2;
0014   AscenderDescenderCoverage;
0030   XheightCoverage;
0052   DescenderCoverage;
*   seqLookupRecords;//[0]
0000   0;
0001   1;
*   seqLookupRecords;//[1]
0002   2;
0002   2;
    ;
0001   1;
000C   12;
0033   bGlyphID;
0035   dGlyphID;
0037   fGlyphID;
0038   gGlyphID;
0039   hGlyphID;
003B   jGlyphID;
003C   kGlyphID;
003D   lGlyphID;
0041   pGlyphID;
0042   qGlyphID;
0045   tGlyphID;
004A   yGlyphID;
    ;
0001   1;
000F   15;
0032   aGlyphID;
0034   cGlyphID;
0036   eGlyphID;
003A   iGlyphID;
003E   mGlyphID;
003F   nGlyphID;
0040   oGlyphID;
0043   rGlyphID;
0044   sGlyphID;
0045   tGlyphID;
0046   uGlyphID;
0047   vGlyphID;
0048   wGlyphID;
0049   xGlyphID;
004B   zGlyphID;
    ;
0001   1;
0005   5;
0038   gGlyphID;
003B   jGlyphID;
0041   pGlyphID;
0042   qGlyphID;
004A   yGlyphID;
}Example/* 9*/;
ACQRES(Example/* 9*/){
one();
one(3);
one(3);
one(2);
one(AscenderDescenderCoverage);
one(XheightCoverage);
one(DescenderCoverage);
arr(seqLookupRecords, 0);
 one(0);
one(1);
arr(seqLookupRecords, 1);
 one(2);
one(2);
one();
one(1);
one(12);
one(bGlyphID);
one(dGlyphID);
one(fGlyphID);
one(gGlyphID);
one(hGlyphID);
one(jGlyphID);
one(kGlyphID);
one(lGlyphID);
one(pGlyphID);
one(qGlyphID);
one(tGlyphID);
one(yGlyphID);
one();
one(1);
one(15);
one(aGlyphID);
one(cGlyphID);
one(eGlyphID);
one(iGlyphID);
one(mGlyphID);
one(nGlyphID);
one(oGlyphID);
one(rGlyphID);
one(sGlyphID);
one(tGlyphID);
one(uGlyphID);
one(vGlyphID);
one(wGlyphID);
one(xGlyphID);
one(zGlyphID);
one();
one(1);
one(5);
one(gGlyphID);
one(jGlyphID);
one(pGlyphID);
one(qGlyphID);
one(yGlyphID);
};
USE_ACQRES(Example/* 9*/)

typedef struct {
    ;
0001   1;
0068   ThickExitCoverage;
0000   0;
0000   null - not used;
0001   1;
0026   ThickEntryCoverage;
000C   12;
00A7   BEm2;
00B9   BEi3;
00C5   JIMm3;
00D4   JIMi2;
00EA   SINm2;
00F2   SINi2;
00FD   SADm2;
010D   SADi2;
011B   TOEm3;
012B   TOEi3;
013B   AINm2;
0141   AINi2;
    ;
0001   1;
001F   31;
00A5   ALEFf1;
00A9   BEm4;
00AA   BEm5;
00E2   DALf1;
0167   KAFf1;
0168   KAFfs1;
0169   KAFm1;
016D   KAFm5;
016E   KAFm6;
0170   KAFm8;
0183   GAFf1;
0184   GAFfs1;
0185   GAFm1;
0189   GAFm5;
018A   GAFm6;
018C   GAFm8;
019F   LAMf1;
01A0   LAMm1;
01A1   LAMm2;
01A2   LAMm3;
01A3   LAMm4;
01A4   LAMm5;
01A5   LAMm6;
01A6   LAMm7;
01A7   LAMm8;
01A8   LAMm9;
01A9   LAMm10;
01AA   LAMm11;
01AB   LAMm12;
01AC   LAMm13;
01EC   HAYf2;
    ;
0001   1;
000C   12;
00A6   BEm1;
00B7   BEi1;
00C3   JIMm1;
00D2   JIMi1;
00E9   SINm1;
00F1   SINi1;
00FC   SADm1;
010C   SADi1;
0119   TOEm1;
0129   TOEi1;
013A   AINm1;
0140   AINi1;
}Example/* 10*/;
