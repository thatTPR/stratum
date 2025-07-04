#ifndef TFCMAP_HPP
#define TFCMAP_HPP

#include <math.h>
typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint8   glyphIdArray[256];//[256]
}cmapSubFormat0;
typedef struct {
uint16   firstCode;
uint16   entryCount;
int16   idDelta;
uint16   idRangeOffset;
}SubHeader/* Record:*/;

typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint16   subHeaderKeys[256];//[256]Array that maps high bytes into the subHeaders array: value is subHeaders index × 8.
SubHeader*   subHeaders;//[ ]
uint16*   glyphIdArray;//[ ]
uint16 maxSubHeaderKeys(){uint16 m=0;for(int i=0;i<256;i++){if(m<subHeaderKeys[i])m=subHeaderKeys[i];};};
}cmapSubFormat2;

ACQRES(cmapSubFormat2){
// one((f.format));
one((f.length));
one((f.language));
arr(f.subHeaderKeys, 256);
uint16 mshk = = f.maxSubHeaderKeys(); 
uint16 numSub = 1+mshk/8;
 
 arr(f.subHeaders,numSub  );
 for(int i =0 ; i < 1+mshk/8;i++){
    set((f.subHeaders[i].idRangeOffset));
    offone((f.glyphIdArray[i]), f.subHeaders[i].idRangeOffset );
 }
 };
USE_ACQRES(cmapSubFormat2)

typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint16   segCountX2;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
uint16*   endCode;//[segCount]
uint16   reservedPad;
uint16*   startCode;//[segCount]
int16*   idDelta;//[segCount]
uint16*   idRangeOffset;//[segCount]
uint16*   glyphIdArray;//[ ]
    uint16 searchRange(uint16 segCount){return pow(2,floor(log2(segCount)));}
    uint16 entrySelector(uint16 segCount){return floor(log2(segCount));} //log2(searchRange/2)
    uint16 rangeShift(uint16 segCount){return segCount*2 - searchRange(segCount);}
    uint16 glyphId(int8 c){ *(idRangeOffset[i]/2
            + (c - startCode[i])
            + idRangeOffset[i])};
}cmapSubFormat4;
ACQRES(cmapSubFormat4){
// one((f.format));
one((f.length));
one((f.language));
one((f.segCountX2));
one(f.searchRange);
one(f.entrySelector));
one((f.rangeShift));
arr(f.endCode, f.segCountX2/2);
 one((f.reservedPad));
arr(f.startCode, f.segCountX2/2);
 arr(f.idDelta, f.segCountX2/2);
 arr(f.idRangeOffset, f.segCountX2/2);
 for(int i =0 ; i < f.segCountX2;i++){
     if(f.idRangeOffset[i]>0)offone(f.glyphIdArray, f.idRangeOffset[i] ); }
 };
USE_ACQRES(cmapSubFormat4)

typedef struct {
uint16   format;
uint16   length;
uint16   language;
uint16   firstCode;
uint16   entryCount;
uint16*   glyphIdArray;//[entryCount]
}cmapSubFormat6;
ACQRES(cmapSubFormat6){
// one((f.format));
one((f.length));
one((f.language));
one((f.firstCode));
one((f.entryCount));
arr(f.glyphIdArray, f.entryCount);
 };
USE_ACQRES(cmapSubFormat6)

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   startGlyphID;
}SequentialMapGroup/* Record:*/;

typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint8*   is32;//[8192]
uint32   numGroups;
SequentialMapGroup*   groups;//[numGroups]
}cmapSubFormat8;
ACQRES(cmapSubFormat8){
// one((f.format));
one((f.reserved));
one((f.length));
one((f.language));
arr(f.is32, 8192);
 one((f.numGroups));
arr(f.groups, f.numGroups);
 };
USE_ACQRES(cmapSubFormat8)

typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   startCharCode;
uint32   numChars;
uint16   glyphIdArray;
}cmapSubFormat10;

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   startGlyphID;
}SequentialMapGroup/* Record:*/;
typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   numGroups;
SequentialMapGroup*   groups;//[numGroups]
}cmapSubFormat12:*/;
ACQRES(cmapSubFormat12){
// one((f.format));
one((f.reserved));
one((f.length));
one((f.language));
one((f.numGroups));
arr(f.groups, f.numGroups);
 };
USE_ACQRES(cmapSubFormat12)

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   glyphID;
}ConstantMapGroup/* Record:*/;
typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   numGroups;
ConstantMapGroup*   groups;//[numGroups]
}cmapSubFormat13;
ACQRES(cmapSubFormat13){
// one((f.format));
one((f.reserved));
one((f.length));
one((f.language));
one((f.numGroups));
arr(f.groups, f.numGroups);
 };
USE_ACQRES(cmapSubFormat13)
typedef struct {
uint24   varSelector;
Offset32   defaultUVSOffset;
Offset32   nonDefaultUVSOffset;
}VariationSelector/* Record:*/;
typedef struct {
// uint16   format;
uint32   length;
uint32   numVarSelectorRecords;
VariationSelector*   varSelector;//[numVarSelectorRecords]
}cmapSubFormat14/;
ACQRES(cmapSubFormat14){
// one((f.format));
one((f.length));
one((f.numVarSelectorRecords));
arr(f.varSelector, f.numVarSelectorRecords);
 };
USE_ACQRES(cmapSubFormat14)

typedef struct {
uint24   startUnicodeValue;
uint8   additionalCount;
}UnicodeRange/* Record:*/;
typedef struct {
uint32   numUnicodeValueRanges;
UnicodeRange*   ranges;//[numUnicodeValueRanges]
}DefaultUVS/* Table:*/;
ACQRES(DefaultUVS/* Table:*/){
one((f.numUnicodeValueRanges));
arr(f.ranges, f.numUnicodeValueRanges);
 };
USE_ACQRES(DefaultUVS/* Table:*/)


typedef struct {
uint24   unicodeValue;
uint16   glyphID;
}UVSMapping/* Record:*/;
typedef struct {
uint32   numUVSMappings;
UVSMapping*   uvsMappings;//[numUVSMappings]
}NonDefaultUVS/* Table:*/;
ACQRES(NonDefaultUVS/* Table:*/){
one((f.numUVSMappings));
arr(f.uvsMappings, f.numUVSMappings);
 };
USE_ACQRES(NonDefaultUVS/* Table:*/)

typedef struct {
    uint16   format;
    union {
    cmapSubFormat0 f0;
    cmapSubFormat2 f2;
    cmapSubFormat4 f4;
    cmapSubFormat6 f6;
    cmapSubFormat8 f8;
    cmapSubFormat10 f10;
    cmapSubFormat12 f12;
    cmapSubFormat13 f13;
    cmapSubFormat14 f14 ;
} f;
}cmapSubFormat;
ACQRES(cmapSubFormat){
    one((f.format));
    switch(f.format){
        case 0 : {one((f.f.f0));};
        case 2 : {one((f.f.f2));};
        case 4 : {one((f.f.f4));};
        case 6 : {one((f.f.f6));};
        case 8 : {one((f.f.f8));};
        case 10 : {one((f.f.f10));};
        case 12 : {one((f.f.f12));};
        case 13 : {one((f.f.f13));};
        case 14 : {one((f.f.f14));};
    }
};
enum PlatformID {
        Unicode=0,
        Macntosh=1,
        ISO=2,
        Windows=3,
        Custom=4
    };
    // enum UnicodeID{
    //     0	Unicode 1.0 semantics—deprecated
    //     1	Unicode 1.1 semantics—deprecated
    //     2	ISO/IEC 10646 semantics—deprecated
    //     3	Unicode 2.0 and onwards semantics, Unicode BMP only
    //     4	Unicode 2.0 and onwards semantics, Unicode full repertoire
    //     5	Unicode variation sequences—for use with subtable format 14
    //     6	Unicode full repertoire—for use with subtable format 13
    // };
typedef struct {
uint16   platformID;
uint16   encodingID;
Offset32   subtableOffset;
}EncodingRecord;
typedef struct {
uint16   version;
uint16   numTables;
EncodingRecord*   encodingRecords;//[numTables]
}cmapHeader;
ACQRES(cmapHeader/* Header:*/){
one((f.version));
one((f.numTables));
arr(f.encodingRecords, f.numTables);
 };
USE_ACQRES(cmapHeader/* Header:*/)

typedef struct {
    cmapHeader head;
    cmapSubFormat* tables;
}cmap;
ACQRES(cmap){
    one((f.head));
    if(!f.cmapSubFormat){f.cmapSubFormat= new cmapSubFormat[f.head.numTables];};
    for(int i = 0; i <f.head.numTables;i++){
        offone(f.tables[i],f.head.encodingRecords[i].subtableOffset);
    };
}
USE_ACQRES(cmap)
#endif

