#ifndef FTEBLC_HPP
#define FTEBLC_HPP
#include "_glyphMetrics.hpp"
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

typedef struct {
Offset32   indexSubtableListOffset;
uint32   indexSubtableListSize;
uint32   numberOfIndexSubtables;
uint32   colorRef;
SbitLineMetrics   hori;
SbitLineMetrics   vert;
uint16   startGlyphIndex;
uint16   endGlyphIndex;
uint8   ppemX;
uint8   ppemY;
uint8   bitDepth;
int8   flags;
}BitmapSize;
BitMapSize* _BitmapSize;
ACQRES(BitmapSize){
    one(f.indexSubtableListOffset);
    one(f.indexSubtableListSize);
    one(f.numberOfIndexSubtables);
    one(f.colorRef);
    one(f.hori);
    one(f.vert);
    one(f.startGlyphIndex);
    one(f.endGlyphIndex);
    one(f.ppemX);
    one(f.ppemY);
    one(f.bitDepth);
    one(f.flags);
    _BitmapSize = f;
}
USE_ACQRES(BitmapSize)

typedef struct {
    uint16   firstGlyphIndex;
    uint16   lastGlyphIndex;
    Offset32   indexSubtableOffset;
}IndexSubtableRecord;
typedef struct {
IndexSubtableRecord*   indexSubtableRecords;// [numberOfIndexSubtables ]
}IndexSubtableList;
ACQRES(IndexSubtableList){
    arr(f.indexSubtableRecords,_BitMapSize->numberOfIndexSubtables);
}
USE_ACQRES(IndexSubtableList)
typedef struct {
uint16   indexFormat;
uint16   imageFormat;
Offset32   imageDataOffset;
}IndexSubHeader;
typedef struct {
// IndexSubHeader   header;
Offset32*   sbitOffsets;//[numOffsets]
}IndexSubtableFormat1;
ACQRES(IndexSubtableFormat1){
one(f.header);
arr(f.sbitOffsets, f.numOffsets);
 };
USE_ACQRES(IndexSubtableFormat1)

typedef struct {
// IndexSubHeader   header;
uint32   imageSize;
BigGlyphMetrics   bigMetrics;
}IndexSubtableFormat2;
typedef struct {
IndexSubHeader   header;
Offset16*   sbitOffsets;//[numOffsets]
}IndexSubtableFormat3;
ACQRES(IndexSubtableFormat3){
one((f.header));
arr(f.sbitOffsets, f.numOffsets);
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
one(f.header);
one(f.numGlyphs);
arr(f.glyphArray, f.numGlyphs + 1);
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
one(f.header);
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
}IndexSubtableFormat;
ACQRES(IndexSubtableFormat){
    one(f.header);
    switch (f.header.indexFormat)
    {
    case 1 : {one(f.u.f1);};
    case 2 : {one(f.u.f2);};
    case 3 : {one(f.u.f3);};
    case 4 : {one(f.u.f4);};
    case 5 : {one(f.u.f5);};
    }
}
USE_ACQRES(IndexSubtableFormat)
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapSize*   bitmapSizes;//[numSizes]
}EBLC;
ACQRES(EBLC){
one(f.majorVersion);
one(f.minorVersion);
one(f.numSizes);
arr(f.bitmapSizes, f.numSizes);
 };
USE_ACQRES(EBLC)
#endif