#ifndef FTCBLC_HPP
#define FTCBLC_HPP
#include "eblc.hpp"
#include "ebdt.hpp"
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
BitmapSize _BitmapSize ;
ACQRES(BitmapSize){
    one(f);
    _BitmapSize = f;
}
USE_ACQRES(BitmapSize)

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapSize*   bitmapSizes;//[numSizes]
}CBLC;
ACQRES(CBLC){
one(f.majorVersion);
one(f.minorVersion);
one(f.numSizes);
arr(f.bitmapSizes, f.numSizes);
 };
USE_ACQRES(CBLC)

#endif