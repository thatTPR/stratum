#ifndef FTCOLR_HPP
#define FTCOLR_HPP
#include "_fontVarCommon.hpp"
#include "cpal.hpp"

typedef struct {
// uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
}ClipBoxFormat1;
typedef struct {
// uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
uint32   varIndexBase;
}ClipBoxFormat2;
typedef struct {
   uint8 format;
   union {
      ClipBoxFormat1 f1;
      ClipBoxFormat2 f2;
   }f;

}ClipBoxFormat;
ACQRES(ClipBoxFormat){
   one(f.format);
   switch(f.format){
      case 1 :{one(f.f1);}
      case 2 :{one(f.f2);}
   }
}
USE_ACQRES(ClipBoxFormat)
typedef struct {
uint16   startGlyphID;
uint16   endGlyphID;
Offset24   clipBoxOffset;
//
ClipBoxFormat clipBox;

}Clip;
ACQRES(Clip){
   one(f.startGlyphID);
   one(f.endGlyphID);
   one(f.clipBoxOffset);
   offone(f.clipBox,f.clipBoxOffset)
}
USE_ACQRES(Clip)
typedef struct {
uint8   format;
uint32   numClips;
Clip*   clips;//[numClips]
}ClipList;
ACQRES(ClipList){
one(f.format);
one(f.numClips);
arr(f.clips, f.numClips);
 };
USE_ACQRES(ClipList)

typedef struct {
F2DOT14   stopOffset;
uint16   paletteIndex;
F2DOT14   alpha;
}ColorStop;
typedef struct {
F2DOT14   stopOffset;
uint16   paletteIndex;
F2DOT14   alpha;
uint32   varIndexBase;
}VarColorStop;
typedef struct {
uint8   extend;
uint16   numStops;
ColorStop*   colorStops;//[numStops]
}ColorLine;
ACQRES(ColorLine){
one(f.extend);
one(f.numStops);
arr(f.colorStops, f.numStops);
 };
USE_ACQRES(ColorLine)

typedef struct {
uint8   extend;
uint16   numStops;
VarColorStop*   colorStops;//[numStops]
}VarColorLine;
ACQRES(VarColorLine){
one(f.extend);
one(f.numStops);
arr(f.colorStops, f.numStops);
 };
USE_ACQRES(VarColorLine)

enum Extend {
EXTEND_PAD=0,
EXTEND_REPEAT=1,
EXTEND_REFLECT=2
};
union colrfu;
 struct colrf1 {
// uint8   format;
uint8   numLayers;
uint32   firstLayerIndex;
};//PaintColrLayers
 struct colrf2 {
// uint8   format;
uint16   paletteIndex;
F2DOT14   alpha;
void get(colorFT* cft,uint16* s){
   ColorRecord cr = ftcur->CPAL().get(paletteIndex);
   cft[*s].color= glm::uvec4(cr.eed,cr.green,cr.blue,cr.alpha);
   cft[*s].alpha=alpha;
   cft[*s].sizeColr=0;
   *s=*s+1;
}; 
};//PaintSolid table ;
struct colrf3 {
// uint8   format;
uint16   paletteIndex;
F2DOT14   alpha;
uint32   varIndexBase;
};//PaintVarSolid;
 struct colrf4 {
// uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
ColorLine colorLine;
};//PaintLinearGradient;
ACQRES(colrf4){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.x1);
   one(f.y1);
   one(f.x2);
   one(f.y2);
   offone(f.colorLine,f.colorLineOffset);
};
USE_ACQRES(colrf4)
struct colrf5 {
// uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
uint32   varIndexBase;
VarColorLine colorLine;
};//PaintVarLinearGradient;
ACQRES(colrf5){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.x1);
   one(f.y1);
   one(f.x2);
   one(f.y2);
   one(f.varIndexBase);
   offone(f.colorLine,f.colorLineOffset);
};
USE_ACQRES(colrf5)
struct colrf6 {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
ColorLine colorLine;
};//PaintRadialGradient:*/;
ACQRES(colrf6){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.radius0);
   one(f.x1);
   one(f.y1);
   one(f.radius1);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrf6)
struct colrf7 {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
uint32   varIndexBase;
VarColorLine colorLine;
};//PaintVarRadialGradient:*/;
ACQRES(colrf7){
      one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.radius0);
   one(f.x1);
   one(f.y1);
   one(f.radius1);
   one(f.varIndexBase);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrf7)

struct colrf8 {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
ColorLine colorLine;
};//PaintSweepGradient:*/;
ACQRES(colrf7){
   one(f.colorLineOffset);
   one(f.centerX);
   one(f.centerY);
   one(f.startAngle);
   one(f.endAngle);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrf6)

struct colrf9 {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
uint32   varIndexBase;
VarColorLine colorLine;
};//PaintVarSweepGradient:*/;
ACQRES(colrf9){
one(f.colorLineOffset);
one(f.centerX);
one(f.centerY);
one(f.startAngle);
one(f.endAngle);
one(f.varIndexBase);
offone(f.colorLine,colorLineOffset);
}
USE_ACQRES(colrf9)
 struct colrf10 {
\\uint8   format;
Offset24   paintOffset;
uint16   glyphID;
// SpecialHandle
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintGlyph:*/;
struct colrf11 {
\\uint8   format;
uint16   glyphID;
};//PaintColrGlyph:*/;
typedef struct  {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
}Affine2x3;
typedef struct  {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
uint32   varIndexBase;
}VarAffine2x3;
struct colrf12  {
\\uint8   format;
Offset24   paintOffset;
Offset24   transformOffset;
Affine2x3 transform;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};

} ;//PaintTransform:*/;
ACQRES(colrf12){
   one(f.paintOffset);
   one(f.transformOffset);
   offone(f.transform,f.transformOffset);
}
USE_ACQRES(colrf12)
struct colrf13  {
\\uint8   format;
Offset24   paintOffset;
Offset24   transformOffset;
VarAffine2x3 transform;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintVarTransform:*/;
ACQRES(colrf13){
   one(f.paintOffset);
   one(f.transformOffset);
   offone(f.transform,f.transformOffset);
}
USE_ACQRES(colrf13)
 struct colrf14  {
\\uint8   format;
Offset24   paintOffset;
FWORD   dx;
FWORD   dy;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintTranslate:*/;
 struct colrf15  {
\\uint8   format;
Offset24   paintOffset;
FWORD   dx;
FWORD   dy;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};

};//PaintVarTranslate:*/;
struct colrf16  {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};

};//PaintScale:*/;
struct colrf17 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};

};//PaintVarScale:*/;
struct colrf18{
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintScaleAroundCenter:*/;
 struct colrf19  {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
} ;//PaintVarScaleAroundCenter:*/;
struct colrf20  {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};

};//PaintScaleUniform:*/;
struct colrf21{
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintVarScaleUniform:*/;
struct colrf22 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintScaleUniformAroundCenter:*/;
 struct colrf23 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
} ;//PaintVarScaleUniformAroundCenter:*/;
struct colrf24 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintRotate:*/;
struct colrf25 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintVarRotate:*/;
struct colrf26 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintRotateAroundCenter:*/;
struct colrf27 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintVarRotateAroundCenter:*/;
struct colrf28 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintSkew:*/;
struct colrf29 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintVarSkew:*/;
struct colrf30 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
};//PaintSkewAroundCenter:*/;
struct colrf31 {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+paintOffset);};
} ;//PaintVarSkewAroundCenter:*/;
enum CompositeMode {
   COMPOSITE_CLEAR=0,
   COMPOSITE_SRC=1,
   COMPOSITE_DEST=2,
   COMPOSITE_SRC_OVER=3,
   COMPOSITE_DEST_OVER=4,
   COMPOSITE_SRC_IN=5,
   COMPOSITE_DEST_IN=6,
   COMPOSITE_SRC_OUT=7,
   COMPOSITE_DEST_OUT=8,
   COMPOSITE_SRC_ATOP=9,
   COMPOSITE_DEST_ATOP=10,
   COMPOSITE_XOR=11,
   COMPOSITE_PLUS=12,
   COMPOSITE_SCREEN=13,
   COMPOSITE_OVERLAY=14,
   COMPOSITE_DARKEN=15,
   COMPOSITE_LIGHTEN=16,
   COMPOSITE_COLOR_DODGE=17,
   COMPOSITE_COLOR_BURN=18,
   COMPOSITE_HARD_LIGHT=19,
   COMPOSITE_SOFT_LIGHT=20,
   COMPOSITE_DIFFERENCE=21,
   COMPOSITE_EXCLUSION=22,
   COMPOSITE_MULTIPLY=23,
   COMPOSITE_HSL_HUE=24,
   COMPOSITE_HSL_SATURATION=25,
   COMPOSITE_HSL_COLOR=26,
   COMPOSITE_HSL_LUMINOSITY=27
};

struct colrf32 {
\\uint8   format;
Offset24   sourcePaintOffset;
uint8   compositeMode;
Offset24   backdropPaintOffset;
colrfu* get(colrfu* start,uint16 index){return (&start[index]+sourcePaintOffset);};
};//PaintComposite:*/;

union colrfu {
   colrf1 f1;
   colrf2 f2;
   colrf3 f3;
   colrf4 f4;
   colrf5 f5;
   colrf6 f6;
   colrf7 f7;
   colrf8 f8;
   colrf9 f9;
   colrf10 f10;
   colrf11 f11;
   colrf12 f12;
   colrf13 f13;
   colrf14 f14;
   colrf15 f15;
   colrf16 f16;
   colrf17 f17;
   colrf18 f18;
   colrf19 f19;
   colrf20 f20;
   colrf21 f21;
   colrf22 f22;
   colrf23 f23;
   colrf24 f24;
   colrf25 f25;
   colrf26 f26;
   colrf27 f27;
   colrf28 f28;
   colrf29 f29;
   colrf30 f30;
   colrf31 f31;
   colrf32 f32;
}

typedef struct {
   uint8 format;
   colrfu f;
}colrf;
ACQRES(colrf){
   one(f.format);
   switch(f.format){
      case 1: {one(f.f1);};
      case 2: {one(f.f2);};
      case 3: {one(f.f3);};
      case 4: {one(f.f4);};
      case 5: {one(f.f5);};
      case 6: {one(f.f6);};
      case 7: {one(f.f7);};
      case 8: {one(f.f8);};
      case 9: {one(f.f9);};
      case 10: {one(f.f10);};
      case 11: {one(f.f11);};
      case 12: {one(f.f12);};
      case 13: {one(f.f13);};
      case 14: {one(f.f14);};
      case 15: {one(f.f15);};
      case 16: {one(f.f16);};
      case 17: {one(f.f17);};
      case 18: {one(f.f18);};
      case 19: {one(f.f19);};
      case 20: {one(f.f20);};
      case 21: {one(f.f21);};
      case 22: {one(f.f22);};
      case 23: {one(f.f23);};
      case 24: {one(f.f24);};
      case 25: {one(f.f25);};
      case 26: {one(f.f26);};
      case 27: {one(f.f27);};
      case 28: {one(f.f28);};
      case 29: {one(f.f29);};
      case 30: {one(f.f30);};
      case 31: {one(f.f31);};
      case 32: {one(f.f32);};
   }
}
typedef struct {
   uint16   glyphID;
   uint16   paletteIndex;// CPAL table entry
}Layer;

typedef struct {
uint16   glyphID;
uint16   firstLayerIndex;
uint16   numLayers;
}BaseGlyph;
typedef struct {
uint16   glyphID;
Offset32   paintOffset;
}BaseGlyphPaintRecord;
typedef struct {
uint32   numBaseGlyphPaintRecords;
BaseGlyphPaintRecord*   baseGlyphPaintRecords;//[numBaseGlyphPaintRecords]
colrf* paintTables;
}BaseGlyphList;
ACQRES(BaseGlyphList){
one(f.numBaseGlyphPaintRecords);
arr(f.baseGlyphPaintRecords, f.numBaseGlyphPaintRecords);
int numPaintTables=0;
uint16* indPtTb = new uint16[f.numBaseGlyphPaintRecords]; 
for(int i=0;i<f.numBaseGlyphPaintRecords;i++){int j;
   for(j=0;j<i;j++){
      if(f.baseGlyphPaintRecords[j].paintOffset==f.baseGlyphPaintRecords[i].paintOffset){break;}
   };
   if(j<i){continue;};
   numPaintTables++;
};
if(!f.paintTables){f.paintTables=new colrf[numPaintTables];}
for(int i=0;i<f.numBaseGlyphPaintRecords;i++){
   arr(f.paintTables,numPaintTables)
};
 };
USE_ACQRES(BaseGlyphList)

typedef struct {
uint32   numLayers;
Offset32*   paintOffsets;//[numLayers]
colrf* paintTables;
}LayerList;
ACQRES(LayerList){
one(f.numLayers);
arr(f.paintOffsets, f.numLayers);
offmany(f.paintTables,f.paintOffset,f.numLayers);
};
USE_ACQRES(LayerList)

typedef struct {
// uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
// OffsetTables;
BaseGlyph* baseGlyphRecords;
Layer* layerRecords ;
   void get(uint16 gid, colorFT* cft, uint16* s){
      int m ;
      int n = numBaseGlyphRecords/2;
      int i ;
      ColorRecord* crs ;
      for(i=n;n>=1;){
         if(baseGlyphRecords[i].glyphID == gid){m=baseGlyphRecords[i].numLayers;
             crs = new ColorRecord[m]; 
            for(int j =baseGlyphRecords[i].firstLayerIndex,j<=m;j++){
               if(layerRecords[j].glyphID==gid){
                  crs[j]=fcur->cpal().get(layerRecords[j].paletteIndex);}
            } 
            break;

         };
         n=n/2;
         if(baseGlyphRecords[i].glyphID> gid) {i-=n; }
         else(baseGlyphRecords[i].glyphID<gid){i+=n;};
      }
      *s=m;
       cft = colorFT[m] ;
      for(int i=0;i<m;i++){
         cft[i].sizeColr = 1;
         cft[i].flags = 0x1;
         
         cft[i].color=glm::uvec4(crs[i].red,crs[i].green,crs[i].blue,crs[i].alpha);
      }


    } ;
}COLR0;
ACQRES(COLR0){
   one(f.numBaseGlyphRecords);
   one(f.baseGlyphRecordsOffset);
   one(f.layerRecordsOffset);
   one(f.numLayerRecords);
   offarr(f.baseGlyphRecords,f.baseGlyphRecordsOffset,f.numBaseGlyphRecords);
   offarr(f.layerRecords,f.layerRecordsOffset,f.numLayerRecords); 
}
USE_ACQRES(COLR1)
typedef struct {
// uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
Offset32   baseGlyphListOffset;
Offset32   layerListOffset;
Offset32   clipListOffset;
Offset32   varIndexMapOffset;
Offset32   itemVariationStoreOffset;
// OffsetTables;
BaseGlyph* baseGlyphRecords;
Layer* layerRecords ;// [numLayerRecords]
BaseGlyphList baseGlyphList;
LayerList layerList;
ClipList clipList;
DeltaSetIndexMap deltaSetIndexMap;
ItemVariationStore itemVariationStore;


void get(uint16 gid, colorFT* cft, uint16* s){
   uint16 firstlyr , numlyr;int n = numlyr;
   for(int i=0;i<numBaseGlyphRecords;i++){
      if(gid == baseGlyphRecords[i].glyphID ){
         firstlyr=baseGlyphRecords[i].firstLayerIndex;
         numlyr=baseGlyphRecords[i].numLayers;
      }
   }
   ColorRecord* crs = new ColorRecord[numlyr];
   for(int j=firstlyr;j<=numlyr;j++){
      crs[j]=fcur->cpal().get(fcur.layerRecords[i].paletteIndex);
   };
   colrf* paint;
   int half=baseGlyphList.numBaseGlyphPaintRecords/2;
   for(int i=half;half>=1;){
      if(baseGlyphList.baseGlyphPaintRecords[i].glyphID == gid){
         colrf* paint = &baseGlyphList+baseGlyphList.baseGlyphPaintRecords[i].paintOffset;
         break;
      }
      half=half>1?half/2:1;
      if(baseGlyphList.baseGlyphPaintRecords[i].glyphID > gid){i-=half;}
      if(baseGlyphList.baseGlyphPaintRecords[i].glyphID < gid){i+=half;}
   }
   uint16 numColr;
   auto getNumLyr =[&](colrf* p){
      if(p->format==1){ uint32 num = p->f.f1.numLayers; 
      for(int i=p->f.f1.firstLayerIndex ;i<num;i++){
         num+=getNumLyr(&layerList.paintTables[i]);
      };
      return numLayers;
      };
      return 0;
   };
   uint32 numLyr = getNumLyr(paint);
   cft = new colorFT[numLyr];
      colorFT* subGlyph ;uint16* subGlyphsSize;

   auto getColr =[&](colrf* f,colorFT* cft, uint16* s){
      if(paint->format == 1){
         for(int i = f->f.f1.firstLayerIndex;i<f->f.f1.numLayers +f->f.f1.firstLayerIndex -1;i++){
            uint16 n = getNumLyr(&layerList.paintTables[i]);
            cft[i-f->f.f1.firstLayerIndex].sizeColr = n;
            cft[i-f->f.f1.firstLayerIndex].flags = new uint32[n];
            cft[i-f->f.f1.firstLayerIndex].values = new glm::uvec4[n];
            getColr(&layerList.paintTables[i],cft,s);
         }
      }
      if()
      else {*s++;
         switch(f->format ){
         case 2:{f->f.f2.get(colorFT* cft,s);*cft.flags[s]|= colorFT::flags::solid_fill;*s++ }//[x]
         case 3:{f->f.f3
   
         ColorRecord cr = ftcur->CPAL().get(paletteIndex);
   cft[*s].color= glm::uvec4(cr.red,cr.green,cr.blue,cr.alpha);
   cft[*s].alpha=f->f.f3.alpha;
   cft[*s].sizeColr;
   
         switch(deltaSetIndexMap.format){
            case 0 :{deltaSetIndexMap.f0;};
            case 1 :{deltaSetIndexMap.f1.}
         } 

         //[f->f.f3->varIndexBase);
            *cft.flags[s]|=colorFT::flags::var | colorFT::flags::solid_fil ;
}
         case 4:{*cft.flags[s]|=colorFT::flags::linear_gradient;}
         case 5:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::linear_gradient;}
         case 6:{*cft.flags[s]|=colorFT::flags::radial_gradient;}
         case 7:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::radial_gradient;}
         case 8:{*cft.flags[s]|=colorFT::flags::sweep_gradient;}
         case 9:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::sweep_gradient;}
         case 10:{f->f.f10.get(colorFT* cft,s);}
         case 11:{*cft.subGlyphs[s]=f->f.f11.glyphID;
                   *cft.flags[s]|=colorFT::flags::subGlyph;  }
         case 12:{*cft.flags[s]|=colorFT::flags::affine;}
         case 13:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::affine;}
         case 14:{*cft.flags[s]|=colorFT::flags::translate;}
         case 15:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::translate;}
         case 16:{*cft.flags[s]|=colorFT::flags::scale;}                      
         case 17:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::scale;}
         case 18:{*cft.flags[s]|=colorFT::flags::scale | colroFT::flags::center;}                      
         case 19:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::scale | colroFT::flags::center;}
         case 20:{*cft.flags[s]|=colorFT::flags::scale_uniform;}                      
         case 21:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::scale_uniform;}
         case 22:{*cft.flags[s]|=colorFT::flags::scale_uniform |colorFT::flags::center ;}                      
         case 23:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::scale_uniform |colorFT::flags::center ;}
         case 24:{*cft.flags[s]|=colorFT::flags::rotate  ;}                                                             
         case 25:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::rotate  ;}                                       
         case 26:{*cft.flags[s]|=colorFT::flags::rotate |colorFT::flags::center ;}                                                           
         case 27:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::rotate |colorFT::flags::center ;}                                     
         case 28:{*cft.flags[s]|=colorFT::flags::skew  ;}                                             
         case 29:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::skew  ;}                       
         case 30:{*cft.flags[s]|=colorFT::flags::skew |colorFT::flags::center ;}                      
         case 31:{*cft.flags[s]|=colorFT::flags::var | colorFT::flags::skew |colorFT::flags::center ;}
         case 32:{*cft.flags[s]!=colorFT::flags::composite;}
         };
      };
   };
   uint16 s=0;
   getColr(paint,cft,&s);

   s=numLyr;
   // Merge SubGlyphs
   colorFT* res;
   uint16* resSize;

   for(int i=0 ; i<)


};
}COLR1;
ACQRES(COLR1){
   one(f.numBaseGlyphRecords);
   one(f.baseGlyphRecordsOffset);
   one(f.layerRecordsOffset);
   one(f.numLayerRecords);
   one(f.baseGlyphListOffset);
   one(f.layerListOffset);
   one(f.clipListOffset);
   one(f.varIndexMapOffset);
   one(f.itemVariationStoreOffset);
   offarr(f.baseGlyphRecords,f.baseGlyphRecordsOffset,f.numBaseGlyphRecords);
   offarr(f.layerRecords,f.layerRecordsOffset,f.numLayerRecords);
   offarr(f.baseGlyphList,f.baseGlyphListOffset,);
   offone(f.layerList,f.layerListOffset);
   offone(f.clipList,f.clipListOffset);
   offone(f.deltaSetIndexMap,f.varIndexMapOffset;
   offone(f.itemVariationStore,f.itemVariationStoreOffset;
}
USE_ACQRES(COLR1)

typedef struct {
   uint16 version;
   union  {
   COLR0 c0;
   COLR1 c1;
} c;
   voi get(uint16 gid){
       switch(version){
      case 0 : {return c.c0.get(gid);};
      case 1 : (return c.c1.get(gid););
   };
   };
}COLR;
ACQRES(COLR){
   one(f.version);
   switch(f.version){
      case 0 : {one(f.c.c0);};
      case 1 : (one(f.c.c1););
   };
}
USE_ACQRES(COLR)
#endif