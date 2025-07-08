#ifndef FTEBDT_HPP
#define FTEBDT_HPP
#include "_glyphMetrics.hpp"
#include "eblc.hpp"
#include "ebsc.hpp"

typedef struct {
uint16   glyphID;
int8   xOffset;
int8   yOffset;
}EbdtComponent;
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8*   imageData;
}GlyphBitmapFormat1;
ACQRES(GlyphBitmapFormat1){
    one(f.smallMetrics);
    size_t bytes = _BitmapSize.bitDepth*(_BitmapSize.ppemX*_BitmapSize.ppemX)  ;
    if(bytes%8 !=0){bytes=bytes/8 + _BitmapSize.ppemy;};
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat1)
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8*   imageData;
}GlyphBitmapFormat2;
ACQRES(GlyphBitmapFormat2){
    one(f.smallMetrics);
    size_t bytes = _BitmapSize.bitDepth*(_BitmapSize.ppemX*_BitmapSize.ppemX) ;
    bytes = (bytes%8==0)?0:1 + bytes/8;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat2)
typedef struct {
uint8*   imageData;
}GlyphBitmapFormat5;
ACQRES(GlyphBitmapFormat5){
    size_t bytes = _BitmapSize.bitDepth*(_BitmapSize.ppemX*_BitmapSize.ppemX) ;
    bytes = (bytes%8==0)?0:1 + bytes/8;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat5)
typedef struct {
BigGlyphMetrics   bigMetrics;
uint8*   imageData;
}GlyphBitmapFormat6;
ACQRES(GlyphBitmapFormat6){
    one(f.bigMetrics);
    size_t bytes = _BitmapSize.bitDepth*(_BitmapSize.ppemX*_BitmapSize.ppemX)  ;
    if(bytes%8 !=0){bytes=bytes/8 + _BitmapSize.ppemy;};
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat6)
typedef struct {
BigGlyphMetrics   bigMetrics;
uint8*   imageData;
}GlyphBitmapFormat7;
ACQRES(GlyphBitmapFormat7){
    one(f.bigMetrics);
    size_t bytes = _BitmapSize.bitDepth*(_BitmapSize.ppemX*_BitmapSize.ppemX) ;
    bytes = (bytes%8==0)?0:1 + bytes/8;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat7)
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8   pad;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
}GlyphBitmapFormat8;
ACQRES(GlyphBitmapFormat8){
one(f.smallMetrics);
one(f.pad);
one(f.numComponents);
arr(f.components, f.numComponents);
 };
USE_ACQRES(GlyphBitmapFormat8)

typedef struct {
BigGlyphMetrics   bigMetrics;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
}GlyphBitmapFormat9;
ACQRES(GlyphBitmapFormat9){
one(f.bigMetrics);
one(f.numComponents);
arr(f.components, f.numComponents);
 };
USE_ACQRES(GlyphBitmapFormat9/* table*/)


typedef struct {
  uint16   majorVersion;
uint16   minorVersion;
    union {
        GlyphBitmapFormat1 f1;
        GlyphBitmapFormat2 f2;
        GlyphBitmapFormat3 f3;
        GlyphBitmapFormat4 f4;
        GlyphBitmapFormat5 f5;
        GlyphBitmapFormat6 f6;
        GlyphBitmapFormat7 f7;
        GlyphBitmapFormat8 f8;
        GlyphBitmapFormat9 f9;
    } f;
}EBDT;
ACQRES(EBDT){
one(f.majorVersion);
one(f.minorVersion);
    switch(_ebdtformat){
        case 1:{one(f.f.f1);};
        case 2:{one(f.f.f2);};
        case 3:{one(f.f.f3);};
        case 4:{one(f.f.f4);};
        case 5:{one(f.f.f5);};
        case 6:{one(f.f.f6);};
        case 7:{one(f.f.f7);};
        case 8:{one(f.f.f8);};
        case 9:{one(f.f.f9);};
    }
}
#endif