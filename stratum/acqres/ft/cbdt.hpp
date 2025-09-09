#ifndef FTCBDT_HPP
#define FTCBDTT_HPP
#include "_glyphMetrics.hpp"
#include "eblc.hpp"

            #define XCBDT(x) x(1) x(2) x(3) x(4) x(5) x(6) x(7) x(8) x(9) x(17) x(18) x(19)
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
    #define UMEMB(n) GlyphBitmapFormat##n f##n; 
    XCBDT(UMEMB)


}CBDTf;

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
       CBDTf f;
    }CBDT;
    ACQRES(CBDT){
one(f.majorVersion);
one(f.minorVersion);
f.numBitmaps=0;
for(int i=0;i<CBLC().numSizes;i++){
    for(int j=0;j<CBLC().bitmapSizes[i].indexSubtableListSize.;j++){
        IndexSubtable* ist = CBLC().indexSubtablesList[i]+ CBLC().indexSubtablesList[i][j].indexSubtableOffset
        uint16 dif = CBLC().indexSubtableList[i][j].lastGlyphIndex-CBLC().indexSubtableList[i][j].firstGlyphIndex+1;

        switch(ist->header.indexFormat){
            case 1 :{_imageSize=ist->u.f1.sbitOffsets[dif+1]-ist->u.f1.sbitOffsets[0];}
            case 2 :{_imageSize=ist->u.f2.imageSize;}
            case 3 :{_imageSize=ist->u.f3.sbitOffsets[dif+1]-ist->u.f3.sbitOffsets[0];}
            case 4 :{_imageSize=ist->u.f4.glyphArray[ist->u.f4.numGlyphs].sbitOffset-ist->u.f4.glyphArray[0].sbitOffset;}
            case 5 :{_imageSize=ist->u.f5.imageSize;}
        }
        switch(ist->header.imageFormat){
            #define OFFMEMBCASE(n) case n:{offone(f.f.f##n,ist->header.imageDataOffset);};

            XCBDT(OFFMEMBCASE)
        }
        f.numBitmaps++;

    }
}
};
    USE_ACQRES(CBDT)

#endif