typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   horizAxisOffset;
Offset16   vertAxisOffset;
}BASE/* Header, version 1.0*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   horizAxisOffset;
Offset16   vertAxisOffset;
Offset32   itemVarStoreOffset;
}BASE/* Header, version 1.1*/;
typedef struct {
Offset16   baseTagListOffset;
Offset16   baseScriptListOffset;
}Axis/* table*/;
typedef struct {
uint16   baseTagCount;
Tag*   baselineTags;//[baseTagCount]
}BaseTagList/* table*/;
ACQRES(BaseTagList/* table*/){
one(baseTagCount);
arr(baselineTags, baseTagCount);
 };
USE_ACQRES(BaseTagList/* table*/)

typedef struct {
uint16   baseScriptCount;
BaseScriptRecord*   baseScriptRecords;//[baseScriptCount]
}BaseScriptList/* table*/;
ACQRES(BaseScriptList/* table*/){
one(baseScriptCount);
arr(baseScriptRecords, baseScriptCount);
 };
USE_ACQRES(BaseScriptList/* table*/)

typedef struct {
Tag   baseScriptTag;
Offset16   baseScriptOffset;
}BaseScriptRecord;
typedef struct {
Offset16   baseValuesOffset;
Offset16   defaultMinMaxOffset;
uint16   baseLangSysCount;
BaseLangSys*   baseLangSysRecords;//[baseLangSysCount]
}BaseScript/* table*/;
ACQRES(BaseScript/* table*/){
one(baseValuesOffset);
one(defaultMinMaxOffset);
one(baseLangSysCount);
arr(baseLangSysRecords, baseLangSysCount);
 };
USE_ACQRES(BaseScript/* table*/)

typedef struct {
Tag   baseLangSysTag;
Offset16   minMaxOffset;
}BaseLangSys/* record*/;
typedef struct {
uint16   defaultBaselineIndex;
uint16   baseCoordCount;
Offset16*   baseCoordOffsets;//[baseCoordCount]
}BaseValues/* table*/;
ACQRES(BaseValues/* table*/){
one(defaultBaselineIndex);
one(baseCoordCount);
arr(baseCoordOffsets, baseCoordCount);
 };
USE_ACQRES(BaseValues/* table*/)

typedef struct {
Offset16   minCoordOffset;
Offset16   maxCoordOffset;
uint16   featMinMaxCount;
FeatMinMax*   featMinMaxRecords;//[featMinMaxCount]
}MinMax/* table*/;
ACQRES(MinMax/* table*/){
one(minCoordOffset);
one(maxCoordOffset);
one(featMinMaxCount);
arr(featMinMaxRecords, featMinMaxCount);
 };
USE_ACQRES(MinMax/* table*/)

typedef struct {
Tag   featureTag;
Offset16   minCoordOffset;
Offset16   maxCoordOffset;
}FeatMinMax/* record*/;
typedef struct {
uint16   format;
int16   coordinate;
}BaseCoordFormat1/* table: Design units only*/;
typedef struct {
uint16   format;
int16   coordinate;
uint16   referenceGlyph;
uint16   baseCoordPoint;
}BaseCoordFormat2/* table: Design units plus contour point*/;
typedef struct {
uint16   format;
int16   coordinate;
Offset16   deviceOffset;
}BaseCoordFormat3/* table: Design units plus Device or VariationIndex table*/;
typedef struct {
    ;
00010000   0x00010000;
0008   HorizontalAxisTable;
010C   VerticalAxisTable;
    ;
0004   HorizBaseTagList;
0012   HorizBaseScriptList;
    ;
0003   3;
68616E67   ''hang';
6964656F   ''ideo';
726F6D6E   ''romn';
    ;
0004   4;
*   baseScriptRecords;//[0]
6379726C   ''cyrl';
001A   HorizCyrillicBaseScriptTable;
*   baseScriptRecords;//[1]
6465766E   ''devn';
0060   HorizDevanagariBaseScriptTable;
*   baseScriptRecords;//[2]
68616E69   ''hani';
008A   HorizHanBaseScriptTable;
*   baseScriptRecords;//[3]
6C61746E   ''latn';
00B4   HorizLatinBaseScriptTable;
}Example/* 1*/;
ACQRES(Example/* 1*/){
one();
one(0x00010000);
one(HorizontalAxisTable);
one(VerticalAxisTable);
one();
one(HorizBaseTagList);
one(HorizBaseScriptList);
one();
one(3);
one(''hang');
one(''ideo');
one(''romn');
one();
one(4);
arr(baseScriptRecords, 0);
 one(''cyrl');
one(HorizCyrillicBaseScriptTable);
arr(baseScriptRecords, 1);
 one(''devn');
one(HorizDevanagariBaseScriptTable);
arr(baseScriptRecords, 2);
 one(''hani');
one(HorizHanBaseScriptTable);
arr(baseScriptRecords, 3);
 one(''latn');
one(HorizLatinBaseScriptTable);
};
USE_ACQRES(Example/* 1*/)

typedef struct {
    ;
000C   HorizCyrillicBaseValuesTable;
0022   HorizCyrillicDefault;
0001   1;
*   baseLangSysRecords;//[0]
52555320   “RUS ”;
0030   HorizRussianMinMaxTable;
}Example/* 2*/;
ACQRES(Example/* 2*/){
one();
one(HorizCyrillicBaseValuesTable);
one(HorizCyrillicDefault);
one(1);
arr(baseLangSysRecords, 0);
 one(“RUS ”);
one(HorizRussianMinMaxTable);
};
USE_ACQRES(Example/* 2*/)

typedef struct {
   ;
0002   2;
0003   3;
000A   HorizHangingBaseCoordForCyrl;
000E   HorizIdeographicBaseCoordForCyrl;
0012   HorizRomanBaseCoordForCyrl;
   ;
0001   1;
05DC   1500;
    ;
0001   1;
FEE0   -288;
    ;
0001   1;
0000   0;
}Example/* 3A*/;
typedef struct {
hanging   1500;
roman   0;
ideographic   -288;
}Example/* 3B: Identical baseline values*/;
typedef struct {
hanging   1788;
roman   288;
ideographic   0;
}Example/* 3B: Assigned baseline values with default baselines at 0*/;
typedef struct {
    ;
0006   HorizCyrillic;
000A   HorizCyrillic;
0000   0;
    ;
0001   1;
FF38   -200;
    ;
0001   1;
0674   1652;
    ;
000E   HorizRussianLangSys;
0012   HorizRussianLangSys;
0001   1;
*   featMinMaxRecords;//[0]
7469746C   ''titl';
0016   HorizRussianFeature;
001A   HorizRussianFeature;
   ;
0001   1;
FF08   -248;
    ;
0001   1;
06A4   1700;
    ;
0001   1;
FED8   -296;
    ;
0001   1;
06D8   1752;
}Example/* 4A*/;
ACQRES(Example/* 4A*/){
one();
one(HorizCyrillic);
one(HorizCyrillic);
one(0);
one();
one(1);
one(-200);
one();
one(1);
one(1652);
one();
one(HorizRussianLangSys);
one(HorizRussianLangSys);
one(1);
arr(featMinMaxRecords, 0);
 one(''titl');
one(HorizRussianFeature);
one(HorizRussianFeature);
one();
one(1);
one(-248);
one();
one(1);
one(1700);
one();
one(1);
one(-296);
one();
one(1);
one(1752);
};
USE_ACQRES(Example/* 4A*/)

typedef struct {
    ;
0000   NULL;
000C   HorizCyrillicDefault;
0001   1;
*   baseLangSysRecords;//[0]
52555320   ''RUS ';
001A   HorizRussian;
    ;
0006   HorizCyrillic;
000A   HorizCyrillic;
0000   0;
    ;
0001   1;
FF38   -200;
    ;
0001   1;
0674   1652;
    ;
0000   NULL;
0000   NULL;
0001   1;
*   featMinMaxRecords;//[0]
7469746C   ''titl';
000E   HorizRussianFeature;
0012   HorizRussianFeature;
    ;
0001   1;
FED8   -296;
    ;
0001   1;
06D8   1752;
}Example/* 4B*/;
ACQRES(Example/* 4B*/){
one();
one(NULL);
one(HorizCyrillicDefault);
one(1);
arr(baseLangSysRecords, 0);
 one(''RUS ');
one(HorizRussian);
one();
one(HorizCyrillic);
one(HorizCyrillic);
one(0);
one();
one(1);
one(-200);
one();
one(1);
one(1652);
one();
one(NULL);
one(NULL);
one(1);
arr(featMinMaxRecords, 0);
 one(''titl');
one(HorizRussianFeature);
one(HorizRussianFeature);
one();
one(1);
one(-296);
one();
one(1);
one(1752);
};
USE_ACQRES(Example/* 4B*/)

typedef struct {
    ;
0001   1;
FEE8   -280;
}Example/* 5*/;
typedef struct {
    ;
0002   2;
FEE8   -280;
0128   IntegralSignGlyphID;
0043   67;
}Example/* 6*/;
typedef struct {
    ;
0003   3;
    -280;
000C   HorizMathMin;
    ;
000B   11;
000F   15;
0001   1;
    1;
    1;
    1;
    1;
5540   1;
}Example/* 7*/;
