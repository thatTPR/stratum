#ifndef FTEBDT_HPP
#define FTEBDT_HPP
#include "_glyphMetrics.hpp"
#include "eblc.hpp"
#include "ebsc.hpp"
uint32 _imageSize;
struct GlyphBitmapFormat1 { // Byte Aligned
SmallGlyphMetrics   smallMetrics;
uint8*   imageData;
    
    size_t size(uint16 height,uint16 width,uint bitd){
        size_t bytes = bitd*(height*width)  ;
    bytes=bytes/8 + ((bitd*width)%8==0)?0:height;
    return bytes;
    }
};
ACQRES(GlyphBitmapFormat1){
    one(f.smallMetrics);
    size_t bytes = f.size(smallMetrics.height,smallMetrics.width,_BitmapSize.bitDepth)  ;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat1)
struct GlyphBitmapFormat2 {
SmallGlyphMetrics   smallMetrics;
uint8*   imageData;
size_t size(uint16 height,uint16 width,uint bitd){
        size_t bytes = bitd*(height*width);
        bytes/=8;
        return bytes;
    }
};
ACQRES(GlyphBitmapFormat2){
    one(f.smallMetrics);
    size_t bytes = f.size(smallMetrics.height,smallMetrics.width,_BitmapSize.bitDepth)  ;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat2)
struct GlyphBitmapFormat5 {
uint8*   imageData;
/// @brief no ldwr
uint32 imageSize; 
};
ACQRES(GlyphBitmapFormat5){
    f.imageSize = _imageSize;
     arr(f.imageData,f.imageSize );
}
USE_ACQRES(GlyphBitmapFormat5)
struct GlyphBitmapFormat6 {
BigGlyphMetrics   bigMetrics;
uint8*   imageData;
    size_t size(uint16 height,uint16 width,uint bitd){
        return GlyphBitmapFormat1::size(height,width,bitd);
    }
};
ACQRES(GlyphBitmapFormat6){
    one(f.bigMetrics);
    size_t bytes =  f.size(smallMetrics.height,smallMetrics.width,_BitmapSize.bitDepth)   ;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat6)
struct GlyphBitmapFormat7 {
BigGlyphMetrics   bigMetrics;
uint8*   imageData;
     size_t size(uint16 height,uint16 width,uint bitd){
        return GlyphBitmapFormat2::size(height,width,bitd);
    }
};
ACQRES(GlyphBitmapFormat7){
    one(f.bigMetrics);
    size_t bytes =  f.size(smallMetrics.height,smallMetrics.width,_BitmapSize.bitDepth)  ;
    bytes = (bytes%8==0)?0:1 + bytes/8;
    arr(f.imageData, bytes );
}
USE_ACQRES(GlyphBitmapFormat7)

typedef struct {
uint16   glyphID;
int8   xOffset;
int8   yOffset;
}EbdtComponent;

struct GlyphBitmapFormat8 {
SmallGlyphMetrics   smallMetrics;
uint8   pad;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
    void get(){
        glyfbm r;r.height=smallMetrics.height;r.width=smallMetrics.width;
        for(int i=0;i<numComponents;i++){
            glyfbm b =EBLC().get(components[i].glyphID);
            r.blit(components[i].xOffset,components[i].yOffset,b);
        }
        return r;
    }
};
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
    glyfbm get(){
        glyfbm r;r.height=bigMetrics.height;r.width=bigMetrics.width;
        for(int i=0;i<numComponents;i++){
            glyfbm b =EBLC().get(components[i].glyphID);
            r.blit(components[i].xOffset,components[i].yOffset,b);
        }
        return r;
    }

}GlyphBitmapFormat9;
ACQRES(GlyphBitmapFormat9){
one(f.bigMetrics);
one(f.numComponents);
arr(f.components, f.numComponents);
 };
USE_ACQRES(GlyphBitmapFormat9/* table*/)

union EBDTf{
        GlyphBitmapFormat1 f1;
        GlyphBitmapFormat2 f2;
        GlyphBitmapFormat3 f3;
        GlyphBitmapFormat4 f4;
        GlyphBitmapFormat5 f5;
        GlyphBitmapFormat6 f6;
        GlyphBitmapFormat7 f7;
        GlyphBitmapFormat8 f8;
        GlyphBitmapFormat9 f9;
      
};

struct EBDT {
  uint16   majorVersion;
uint16   minorVersion;
    EBDTf* bitmaps;

    /// @brief noldwr
    size_t numBitmaps;
    

};
ACQRES(EBDT){
one(f.majorVersion);
one(f.minorVersion);
f.numBitmaps=0;
for(int i=0;i<EBLC().numSizes;i++){
    for(int j=0;j<EBLC().bitmapSizes[i].indexSubtableListSize.;j++){
        IndexSubtable* ist = EBLC().indexSubtablesList[i]+ EBLC().indexSubtablesList[i][j].indexSubtableOffset
        uint16 dif = EBLC().indexSubtableList[i][j].lastGlyphIndex-EBLC().indexSubtableList[i][j].firstGlyphIndex+1;

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
        }
        f.numBitmaps++;

    }
}
}
USE_ACQRES(EBDT)
#endif