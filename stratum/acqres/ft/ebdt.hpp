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
uint8   imageData;
}GlyphBitmapFormat1;
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8   imageData;
}GlyphBitmapFormat2;
typedef struct {
uint8   imageData;
}GlyphBitmapFormat5;
typedef struct {
BigGlyphMetrics   bigMetrics;
uint8   imageData;
}GlyphBitmapFormat6;
typedef struct {
BigGlyphMetrics   bigMetrics;
uint8   imageData;
}GlyphBitmapFormat7;
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8   pad;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
}GlyphBitmapFormat8;
ACQRES(GlyphBitmapFormat8){
one((f.smallMetrics));
one((f.pad));
one((f.numComponents));
arr(f.components, f.numComponents);
 };
USE_ACQRES(GlyphBitmapFormat8)

typedef struct {
BigGlyphMetrics   bigMetrics;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
}GlyphBitmapFormat9;
ACQRES(GlyphBitmapFormat9){
one((f.bigMetrics));
one((f.numComponents));
arr(f.components, f.numComponents);
 };
USE_ACQRES(GlyphBitmapFormat9/* table*/)

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
}EBDTHeader;
typedef struct {
    EBDTHeader head;
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
    one(f.head);
}
#endif