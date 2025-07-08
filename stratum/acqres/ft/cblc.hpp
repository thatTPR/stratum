#ifndef FTCBLC_HPP
#define FTCBLC_HPP
#include "eblc.hpp"
#include "ebdt.hpp"
enum bitDepth {
    blackWhite=1,	
    gray4=2,	
    gray16=4,	
    gray256=8
};
enum BitMapFlags {
HORIZONTAL_METRICS=0x01,    //Horizontal
VERTICAL_METRICS=0x02,	    //Vertical
Reserved=0xFC //For future use — set to 0.
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
BitmapSize _BitmapSize ;
ACQRES(BitmapSize){
    one(f);
    _BitmapSize = f;
}
USE_ACQRES(BitmapSize)

typedef struct {
EBLCh eblc;
CBDT* cbdt;

}CBLC;
ACQRES(CBLC){
    one(f.eblc);
}

#endif