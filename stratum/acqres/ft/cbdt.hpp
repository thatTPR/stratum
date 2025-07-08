#ifndef FTCBDT_HPP
#define FTCBDTT_HPP
#include "_glyphMetrics.hpp"
#include "eblc.hpp"


typedef struct {
SmallGlyphMetrics   glyphMetrics;
uint32   dataLen;
uint8*   data;//[dataLen]
}GlyphBitmapFormat17;
ACQRES(GlyphBitmapFormat17){
one(f.glyphMetrics);
one(f.dataLen);
arr(f.data, f.dataLen);
 };
USE_ACQRES(GlyphBitmapFormat17)

typedef struct {
BigGlyphMetrics   glyphMetrics;
uint32   dataLen;
uint8*   data;//[dataLen]
}GlyphBitmapFormat18;
ACQRES(GlyphBitmapFormat18){
one(f.glyphMetrics);
one(f.dataLen);
arr(f.data, f.dataLen);
 };
USE_ACQRES(GlyphBitmapFormat18)

typedef struct {
uint32   dataLen;
uint8*   data;//[dataLen]
}GlyphBitmapFormat19;
ACQRES(GlyphBitmapFormat19){
one(f.dataLen);
arr(f.data, f.dataLen);
 };
USE_ACQRES(GlyphBitmapFormat19)

typedef union {
    
        GlyphBitmapFormat17 f17;
        GlyphBitmapFormat18 f18;
        GlyphBitmapFormat19 f19;


}GlyphBitmapFormat;

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
        GlyphBitmapFormat form;
    }CBDT;
    ACQRES(CBDT){
one(f.majorVersion);
one(f.minorVersion);
        switch(_ebdtFormat){ 
            case 17:{one(f.form.f17);}
            case 18:{one(f.form.f18);}
            case 19:{one(f.form.f19);}
        };
        one(f.form);

    };
    USE_ACQRES(CBDT)

#endif