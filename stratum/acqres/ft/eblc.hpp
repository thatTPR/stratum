#ifndef FTEBLC_HPP
#define FTEBLC_HPP
#include "_glyphMetrics.hpp"
#include "ebdt.hpp"
enum bitDepth {
    blackWhite=1,	
    gray4=2,	
    gray16=4,	
    gray256=8,
    bgra=32
};
enum BitMapFlags {
HORIZONTAL_METRICS=0x01,    //Horizontal
VERTICAL_METRICS=0x02,	    //Vertical
Reserved=0xFC //For future use — set to 0.
};
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
enum Bitmap  {
HORIZONTAL_METRICS=0x01,
VERTICAL_METRICS=0x02,
Reserved=0xFC
};
uint16 _numOffsets;
typedef struct {
uint16   indexFormat;
uint16   imageFormat;
Offset32   imageDataOffset; // Offset from beggining of ebdt table
}IndexSubHeader;
typedef struct {
// IndexSubHeader   header;
Offset32*   sbitOffsets;//[numOffsets]

}IndexSubtableFormat1; // 4 byte Aligned offsets
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
}IndexSubtableFormat3; // 2 byte aligned offsets
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
template <bool cblc>
struct EBLC{
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapSize*   bitmapSizes;//[numSizes]

IndexSubtableList* indexSubtableLists; 
IndexSubtable* indexSubtables;

/// @brief  noldwr
size_t indexSubtablesSize ;

uint maxNBd(uint bitDepth){
    switch(bitDepth){
        case blackWhite :{return 1;}
        case gray4 :{return 4;}
        case gray16 :{return 16;}
        case gray256:[return 256;]
    }
    if constexpr (cblc){if(bitDepth == bgra ){return 32;}} 
};
uint bdMask(uint bitDepth){
    switch(bitDepth){
        case blackWhite :{return 0b1;}
        case gray4 :{return 0b11;}
        case gray16 :{return 0b1111;}
        case gray256:[return 0b11111111;]
    } 
    if constexpr(cblc){ if(bitDepth == bgra ){return 1024 -1};}
    
};
template <bool byteAligned>
glyyfbm res(EBDTf* ,bitDepth bd,Offset16 offset,uint32 imageSize,uint16 row,uint16 col){
    glyfbm res;
    res.width=col;
    res.height=imageSize*(8/bd)/res.width; 
    res.bitmap=new glm::uvec4[imageSize*8/bd];
        for(uint i=0;i<=imageSize;i++){
            if constexpr(cblc){
                if(bd == bgra){
                    uint8_t b,g,r,a;
                    b=*(f + offset+i )/256;i++;
                    g=*(f + offset+i )/256;i++;
                    r=*(f + offset+i )/256;i++;
                    a=*(f + offset+i )/256;i++;
                    float bf,gf,rf,af;
                    bf=b;bf=/256;gf=g;gf=/256;rf=r;rf=/256;af=a;af=/256;res.bitmap[i] = glm::uvec(rf,gf,bf,af);
                    continue ;
                };
            }
            int num =0;
            if constexpr(byteAligned){
                if((i+1)%(col*(8/bd)/8)==0){
                    num = col*(8/bd)%8/bd;
                };
            };
            num = num ? 8/bd;num+1;
            for(int j=0;j<num ;j++){
               
                uint num =*(f + offset +i) 
                num = num>>(8- (j+1)*bd) & bdMask(bd); 
                float divisor = maxNbd(bd)
                float val = num ; val/=divisor;
                res.bitmap[i *(8/bd) +j ]=glm::vec4(val,val,val,1);
            }
            };
        return res;
}
glyfbm getEbdt(EBDTf* f,bitDepth bd, uint16 format,Offset16 offset ,uint32 imageSize,uint16& row,uint16& col){
    #define ROW_COL_SMALL(f) row=f.f##f.smallMetrics.height;col=f.f##f.smallMetrics.width;
    #define ROW_COL_BIG(f) row=f.f##f.bigMetrics.height;col=f.f##f.bigMetrics.width;
    switch(format){
        case 1:{ROW_COL_SMALL(1)
            return res<true>(f,bd,offset,imageSize,row,col) ;}
        case 2:{ROW_COL_SMALL(2)
            return res<false>(f,bd,offset,imageSize,row,col) ;}
        // case 3:{return res<false>(f,bd,offset,imageSize,row,col) ;bm.f3.res<cblc>(bd,row,col);}
        // case 4:{return res<true>(f,bd,offset,imageSize,row,col) ;bm.f4.res<cblc>(bd,row,col);}
        case 5:{
            ;return res<false>(f,bd,offset,imageSize,row,col) ;}
        case 6:{ROW_COL_BIG(6)
            return res<true>(f,bd,offset,imageSize,row,col) ;}
        case 7:{ROW_COL_BIG(7)
            return res<false>(f,bd,offset,imageSize,row,col) ;}
        case 8:{return f.f8.get();}
        case 9:{return f.f9.get();}
    }
    if constexpr (cblc){
        switch (format){
            case 17 : {ROW_COL_SMALL(17);
                    return res<false>(f,bd,offset,imageSize,row,col) ;
            }
            case 18 : {ROW_COL_BIG(18)
            return res<false>(f,bd,offset,imageSize,row,col) ;}
            case 19 : {return res<false>(f,bd,offset,imageSize,row,col) ;}
        }
    }
}
glyfbm get(uint16 gid){
    IndexSubtable* h ;int dif;BitmapSize* bs;
    for(int i=0;i<numSizes;i++){
    for(int j=0;j<bitmapSizes[i].indexSubtableListSize;j++){
        if((indexSubtableLists[i][j].firstGlyphIndex <= gid) and (gid <= indexSubtableLists[i][j].lastGlyphIndex)){
            h= indexSubtableLists[i][j].indexSubtableOffset + &(indexSubtablesLists[i]);
            bs=&bitMapSizes[i]
            dif=indexSubtableLists[i][j].firstGlyphIndex-gid;break;
        }
    };
    };
    EBDT::EBDTf* bm;int format;
    
    glyfbm res;size_t s;
    uint16 row,col;
    switch(h->header.indexFormat){
    case 1 :{format=1;bm=&EBDT() +h->header.ImageDataOffsets;s=h->u.f1.sbitOffsets[dif+1]-h->u.f1.sbitOffsets[dif];
        res=getEbdt(bm,bs->bitDepth,h->header.imageFormat,h->u.f1.sbitOffsets[dif],s,row,col);break;};
    case 2 :{format=2;bm=&EBDT() +h->header.ImageDataOffsets;s=h->u.f2.imageSize;row=h->u.f2.bigMetrics.height;col=h->u.f2.bigMetrics.width;
        getEbdt(bm,bs->bitDepth,h->header.imageFormat,0,s,row,col);break};
    case 3 :{format=3;bm=&EBDT() +h->header.ImageDataOffsets;s=h->u.f3.sbitOffsets[dif+1]-h->u.f3.sbitOffsets[dif];
        res=getEbdt(bm,bs->bitDepth,h->header.imageFormat,h->u.f3.sbitOffsets[dif],s,row,col);  break;};
    case 4 :{format=4;bm=&EBDT() +h->header.ImageDataOffsets;s=h->u.f4.glyphArray[dif+1].sbitOffset-h->u.f4.glyphArray[dif].sbitOffset};
        res=getEbdt(bm,bs->bitDepth,h->header.imageFormat,h->u.f4.glyphArray[dif].sbitOffset,s,row,col);break;
    case 5 :{format=5;bm=&EBDT() +h->header.ImageDataOffsets;s=h->u.f5.imageSize;row=h->u.f5.bigMetrics.height;col=h->u.f5.bigMetrics.width;
        int d=gb.numComponents/2;int i;
        for( i=d;i<h->u.f5.numGlyphs;i++){
            if(h->u.f5.glyphIdArray[i] == gid){
                break ;
            }
            d=(d/2)>=1?d/2:1;
            if(h->u.f5.glyphIdArray[i] >gid){i-=d;}
            else{i+=d;}
        }
        if(i>=h->u.f5.numGlyphs){return};  
        res=getEbdt(bm,h->header.imageFormat,0,s,row,col);
        break;};
    };
    return res;
};
};

ACQRES(EBLC<false>){
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
USE_ACQRES(EBLC<false>)


#endif