typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   jstfScriptCount;
JstfScriptRecord*   jstfScriptRecords;//[jstfScriptCount]
}JSTF/* header*/;
ACQRES(JSTF/* header*/){
one(majorVersion);
one(minorVersion);
one(jstfScriptCount);
arr(jstfScriptRecords, jstfScriptCount);
 };
USE_ACQRES(JSTF/* header*/)

typedef struct {
Tag   jstfScriptTag;
Offset16   jstfScriptOffset;
}JstfScriptRecord;
typedef struct {
Offset16   extenderGlyphOffset;
Offset16   defJstfLangSysOffset;
uint16   jstfLangSysCount;
JstfLangSysRecord*   jstfLangSysRecords;//[jstfLangSysCount]
}JstfScript/* table*/;
ACQRES(JstfScript/* table*/){
one(extenderGlyphOffset);
one(defJstfLangSysOffset);
one(jstfLangSysCount);
arr(jstfLangSysRecords, jstfLangSysCount);
 };
USE_ACQRES(JstfScript/* table*/)

typedef struct {
Tag   jstfLangSysTag;
Offset16   jstfLangSysOffset;
}JstfLangSysRecord;
typedef struct {
uint16   glyphCount;
uint16*   extenderGlyphs;//[glyphCount]
}ExtenderGlyph/* table*/;
ACQRES(ExtenderGlyph/* table*/){
one(glyphCount);
arr(extenderGlyphs, glyphCount);
 };
USE_ACQRES(ExtenderGlyph/* table*/)

typedef struct {
uint16   jstfPriorityCount;
Offset16*   jstfPriorityOffsets;//[jstfPriorityCount]
}JstfLangSys/* table*/;
ACQRES(JstfLangSys/* table*/){
one(jstfPriorityCount);
arr(jstfPriorityOffsets, jstfPriorityCount);
 };
USE_ACQRES(JstfLangSys/* table*/)

typedef struct {
Offset16   gsubShrinkageEnableOffset;
Offset16   gsubShrinkageDisableOffset;
Offset16   gposShrinkageEnableOffset;
Offset16   gposShrinkageDisableOffset;
Offset16   shrinkageJstfMaxOffset;
Offset16   gsubExtensionEnableOffset;
Offset16   gsubExtensionDisableOffset;
Offset16   gposExtensionEnableOffset;
Offset16   gposExtensionDisableOffset;
Offset16   extensionJstfMaxOffset;
}JstfPriority/* table*/;
typedef struct {
uint16   lookupCount;
uint16*   lookupIndices;//[lookupCount]
}JstfModList/* table*/;
ACQRES(JstfModList/* table*/){
one(lookupCount);
arr(lookupIndices, lookupCount);
 };
USE_ACQRES(JstfModList/* table*/)

typedef struct {
uint16   lookupCount;
Offset16*   lookupOffsets;//[lookupCount]
}JstfMax/* table*/;
ACQRES(JstfMax/* table*/){
one(lookupCount);
arr(lookupOffsets, lookupCount);
 };
USE_ACQRES(JstfMax/* table*/)

typedef struct {
    ;
00010000   0x00010000;
0001   1;
*   jstfScriptRecords;//[0]
74686169   ''thai';
000C   ThaiScript;
}Example/* 1*/;
ACQRES(Example/* 1*/){
one();
one(0x00010000);
one(1);
arr(jstfScriptRecords, 0);
 one(''thai');
one(ThaiScript);
};
USE_ACQRES(Example/* 1*/)

typedef struct {
    ;
000C   ArabicExtenders;
0012   ArabicDefJstfLangSys;
0001   1;
*   jstfLangSysRecords;//[0]
50455220   “FAR ”;
0018   FarsiJstfLangSys;
    ;
0002   2;
01D3   TatweelGlyphID;
01D4   LongTatweelGlyphID;
    ;
0002   2;
000A   ArabicScriptJstfPriority1;
001E   ArabicScriptJstfPriority2;
    ;
0001   1;
002C   FarsiLangJstfPriority1;
}Example/* 2*/;
ACQRES(Example/* 2*/){
one();
one(ArabicExtenders);
one(ArabicDefJstfLangSys);
one(1);
arr(jstfLangSysRecords, 0);
 one(“FAR ”);
one(FarsiJstfLangSys);
one();
one(2);
one(TatweelGlyphID);
one(LongTatweelGlyphID);
one();
one(2);
one(ArabicScriptJstfPriority1);
one(ArabicScriptJstfPriority2);
one();
one(1);
one(FarsiLangJstfPriority1);
};
USE_ACQRES(Example/* 2*/)

typedef struct {
    ;
0028   EnableGSUBLookupsToShrink;
0000   NULL;
0000   NULL;
0000   NULL;
0000   NULL;
0000   NULL;
0038   DisableGSUBLookupsToExtend;
0000   NULL;
0000   NULL;
0000   NULL;
    ;
0000   NULL;
0000   NULL;
0000   NULL;
001C   DisableGPOSLookupsToShrink;
0000   NULL;
0000   NULL;
0000   NULL;
002C   EnableGPOSLookupsToExtend;
0000   NULL;
0000   NULL;
    ;
0003   3;
002E   46;
0035   53;
0063   99;
    ;
0003   3;
006C   108;
006E   110;
0070   112;
    ;
0003   3;
002E   46;
0035   53;
0063   99;
    ;
0003   3;
006C   108;
006E   110;
0070   112;
}Example/* 3*/;
typedef struct {
    ;
0001   1;
0004   WordSpaceExpandLookup;
    ;
0001   1;
0000   0x0000;
0001   1;
0008   WordSpaceExpandSubtable;
    ;
0001   1;
0008   WordSpaceCoverage;
0004   0x0004;
0168   360;
    ;
0001   1;
0001   1;
0022   WordSpaceGlyphID;
}Example/* 4*/;
