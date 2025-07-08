#ifndef FTEBLC_HPP
#define FTEBLC_HPP
#include "_glyphMetrics.hpp"
#include "cblc.hpp"
typedef struct {
int8   ascender;
int8   descender;
uint8   widthMax;
int8   caretSlopeNumerator;
int8   caretSlopeDenominator;
int8   caretOffset;
int8   minOriginSB;
int8   minAdvanceSB;
int8   maxBeforeBL;
int8   minAfterBL;
int8   pad1;
int8   pad2;
}SbitLineMetrics;
enum Bitmap  {
HORIZONTAL_METRICS=0x01,
VERTICAL_METRICS=0x02,
Reserved=0xFC
};
uint16 _numOffsets;
typedef struct {
uint16   indexFormat;
uint16   imageFormat;
Offset32   imageDataOffset; // OFfset from beggining of ebdt table
}IndexSubHeader;
typedef struct {
// IndexSubHeader   header;
Offset32*   sbitOffsets;//[numOffsets]
}IndexSubtableFormat1;
ACQRES(IndexSubtableFormat1){
arr(f.sbitOffsets, _numOffsets);
 };
USE_ACQRES(IndexSubtableFormat1)

typedef struct {
// IndexSubHeader   header;
uint32   imageSize;
BigGlyphMetrics   bigMetrics;
}IndexSubtableFormat2;
typedef struct {
// IndexSubHeader   header;
Offset16*   sbitOffsets;//[numOffsets]
}IndexSubtableFormat3;
ACQRES(IndexSubtableFormat3){
arr(f.sbitOffsets, _numOffsets);
 };
USE_ACQRES(IndexSubtableFormat3)
typedef struct {
uint16   glyphID;
Offset16   sbitOffset;
}GlyphIdOffsetPair;
typedef struct {
// IndexSubHeader   header;
uint32   numGlyphs;
GlyphIdOffsetPair*   glyphArray;//[numGlyphs + 1]
}IndexSubtableFormat4;
ACQRES(IndexSubtableFormat4){
one(f.numGlyphs);uint16 numGl =f.numGlyphs+1; 
arr(f.glyphArray, numGl);f.numGlyphs=numGl-1;
 };
USE_ACQRES(IndexSubtableFormat4)


typedef struct {
// IndexSubHeader   header;
uint32   imageSize;
BigGlyphMetrics   bigMetrics;
uint32   numGlyphs;
uint16*   glyphIdArray;//[numGlyphs]
}IndexSubtableFormat5;
ACQRES(IndexSubtableFormat5){
one(f.imageSize);
one(f.bigMetrics);
one(f.numGlyphs);
arr(f.glyphIdArray, f.numGlyphs);
 };
USE_ACQRES(IndexSubtableFormat5)

typedef struct {
    IndexSubHeader   header;
    union{
IndexSubtableFormat1 f1;
IndexSubtableFormat2 f2;
IndexSubtableFormat3 f3;
IndexSubtableFormat4 f4;
IndexSubtableFormat5 f5;
    } u;
}IndexSubtable;
uint8 _ebdtFormat ;
ACQRES(IndexSubtable){
    one(f.header);
    _ebtdFormat=f.header.imageFormat;
    switch (f.header.indexFormat){
    case 1 : {one(f.u.f1);};
    case 2 : {one(f.u.f2);};
    case 3 : {one(f.u.f3);};
    case 4 : {one(f.u.f4);};
    case 5 : {one(f.u.f5);};
    }
}
USE_ACQRES(IndexSubtable)

typedef struct {
    uint16   firstGlyphIndex;
    uint16   lastGlyphIndex;
    Offset32   indexSubtableOffset;
}IndexSubtableRecord;
typedef IndexSubtableRecord* IndexSubtableList;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapSize*   bitmapSizes;//[numSizes]

IndexSubtableList* indexSubtableLists; 
IndexSubtable* indexSubtables;
/// @brief  noldwr
size_t indexSubtablesSize ;
}EBLC;

ACQRES(EBLC){
one(f.majorVersion);
one(f.minorVersion);
one(f.numSizes);
arr(f.bitmapSizes, f.numSizes);
if(!f.indexSubtableLists){f.indexSubtableLists = new IndexSubtableList[f.numSizes];};
size_t s =0;
for(int i=0;i<f.numSizes;i++){
    s+=f.bitmapSizes[i].indexSubtableListSize;
    offarr(f.indexSubtableLists[i],f.bitmapSizes[i].indexSubtableListOffset,f.bitmapSizes[i].indexSubtableListSize);
};
if(!f.indexSubtables){f.indexSubtables= new IndexSubtable[s];};indexSubtablesSize =s;
int k=0;
for(int i=0;i<f.numSizes;i++){
    for(int j=0;j<f.bitmapSizes[i].indexSubtableListSize;j++){
        _numOffsets = f.indexSubtableLists[i][j].lastGlyphIndex-f.indexSubtableLists[i][j].firstGlyphIndex + 2;
        offone(f.indexSubtables[k],f.indexSubtableLists[i][j].indexSubtableOffset);
        k++;
    };
}
 };
USE_ACQRES(EBLC)
#endif