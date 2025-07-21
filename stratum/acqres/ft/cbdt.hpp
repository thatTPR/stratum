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
    
        GlyphBitmapFormat1 f1;
        GlyphBitmapFormat2 f2;
        GlyphBitmapFormat3 f3;
        GlyphBitmapFormat4 f4;
        GlyphBitmapFormat5 f5;
        GlyphBitmapFormat6 f6;
        GlyphBitmapFormat7 f7;
        GlyphBitmapFormat8 f8;
        GlyphBitmapFormat9 f9;
        // CBDT
        GlyphBitmapFormat17 f17;
        GlyphBitmapFormat18 f18;
        GlyphBitmapFormat19 f19;


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
            case 1:{offone(f.f.f1,ist->header.imageDataOffset);};
            case 2:{offone(f.f.f2,ist->header.imageDataOffset);};
            case 3:{offone(f.f.f3,ist->header.imageDataOffset);};
            case 4:{offone(f.f.f4,ist->header.imageDataOffset);};
            case 5:{offone(f.f.f5,ist->header.imageDataOffset);};
            case 6:{offone(f.f.f6,ist->header.imageDataOffset);};
            case 7:{offone(f.f.f7,ist->header.imageDataOffset);};
            case 8:{offone(f.f.f8,ist->header.imageDataOffset);};
            case 9:{offone(f.f.f9,ist->header.imageDataOffset);};

            
            case 17:{offone(f.f.f17,ist->header.imageDataOffset);}
            case 18:{offone(f.f.f18,ist->header.imageDataOffset);}
            case 19:{offone(f.f.f19,ist->header.imageDataOffset);}
        }
        f.numBitmaps++;

    }
}
};
    USE_ACQRES(CBDT)

#endif