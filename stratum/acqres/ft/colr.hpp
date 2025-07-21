#ifndef FTCOLR_HPP
#define FTCOLR_HPP
#include "_fontVarCommon.hpp"
#include "cpal.hpp"
#include <type_traits>
#include <petri/algo>

struct ClipBoxFormat1 {
// uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
};
using varIndBase = uint32;
struct varValueBase {
   uint16 mapCount;
   uint8* mapValue;
};
 
template <typename VarIndex>
struct ClipBoxFormat2 {
// uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
VarIndex   varIndexBase;
};
template <typename VarIndex>
struct ClipBoxFormat {
   uint8 format;
   union {
      ClipBoxFormat1 f1;
      ClipBoxFormat2<varIndBase> f2;
   }f;

};
ACQRES(ClipBoxFormat){
   one(f.format);
   switch(f.format){
      case 1 :{one(f.f1);}
      case 2 :{one(f.f2);}
   }
}
USE_ACQRES(ClipBoxFormat)
template <typename VarIndex>
struct Clip {
uint16   startGlyphID;
uint16   endGlyphID;
Offset24   clipBoxOffset;
//
ClipBoxFormat<VarIndex> clipBox;

};
ACQRES(Clip<varIndBase>){
   one(f.startGlyphID);
   one(f.endGlyphID);
   one(f.clipBoxOffset);
   offone(f.clipBox,f.clipBoxOffset)
}
USE_ACQRES(Clip<varIndBase>)
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
#define COND_IS_SAME(t1,t1) std::conditional<std::is_same<VarIndex,varIndBase>::value,t1,t2>::type

template <typename varIndexBase>
struct ColorStop {
F2DOT14   stopOffset;
COND_IS_SAME(uint16,glm::uvec4)   paletteIndex;
F2DOT14   alpha;
};
template <typename VarIndex>
struct VarColorStop {
F2DOT14   stopOffset;
COND_IS_SAME(uint16,glm::uvec4)   paletteIndex;
COND_IS_SAME(F2DOT14,float)   alpha;
VarIndex   varIndexBase;

};
typedef struct {
uint8   extend;
uint16   numStops;
ColorStop*   colorStops;//[numStops]
}ColorLine;
ACQRES(ColorLine){
one(f.extend);
one(f.numStops);
if(f.colorStops){for(int i=0;i<numStops;i++){f.colorStops[i].stopOffset=sizeof(ColorStop)*i+3;}}
arr(f.colorStops, f.numStops);
 };
USE_ACQRES(ColorLine)
template <typename VarIndex>
struct VarColorLine {
uint8   extend;
uint16   numStops;
VarColorStop<varIndBase>*   colorStops;//[numStops]

};
ACQRES(VarColorLine<varIndBase>){
one(f.extend);
one(f.numStops);
if(f.colorStops){for(int i=0;i<numStops;i++){f.colorStops[i].stopOffset=sizeof(VarColorStop<varIndBase>)*i+3;}}
arr(f.colorStops, f.numStops);
 };
USE_ACQRES(VarColorLine<varIndBase>)

enum Extend {
EXTEND_PAD=0,
EXTEND_REPEAT=1,
EXTEND_REFLECT=2
};
float alphaval(F2DOT14 f){
   const float mask = 0b11111111111111;
   float r = f & mask;
   r = r/(1<<14) + (f & (0b11<<14))>>14 ;
   return r;
};
template <typename T>
void getCpal(T* colf, colorFT* cf){
   ColorRecord cr = CPAL().get(colrf->paletteIndex);
   cf->color= glm::uvec4(cr.red,cr.green,cr.blue,cr.alpha);
   cf->alpha=colf->alpha;
};
template <typename VarIndex>
union colrfu;
#define REPEAT(macro, n) macro(n)
#define REPEAT(macro, n,...) REPEAT(macro,n)\
REPEAT(macro,__VA__ARGS__)
#define COLRF_GET_MEMBER(member) r.member =member;
#define COLRF_GET(fn,...) \
colrf##fn<varValueBase> get(){colrf##fn<varValueBase> r; \
REPEAT(COLRF_GET_MEMBER,__VA__ARGS__) \
return r;\
}
 struct colrf1 {
// uint8   format;
uint8   numLayers;
uint32   firstLayerIndex;

};//PaintColrLayers
template <typename VarIndex>
 struct colrf2 {
// uint8   format;
COND_IS_SAME(uint16,glm::uvec4)   paletteIndex;
COND_IS_SAME(F2DOT14,float)   alpha;
corlf2<varValueBase> get(){corlf2<varValueBase> r;r.paletteIndex=CPAL().get(paletteIndex).get();r.alpha=alphaval(alpha);}
};//PaintSolid table ;
template <typename VarIndex> // Uint32 or struct{uint16,uint8*}
struct colrf3 {
// uint8   format;
COND_IS_SAME(uint16,glm::uvec4)  paletteIndex;
F2DOT14   alpha;
VarIndex   varIndexBase;
corlf4<varValueBase> get(){corlf4<varValueBase> r;r.paletteIndex=CPAL().get(paletteIndex).get();r.alpha=alphaval(alpha);}
};//PaintVarSolid;
#define TEMPLATE_TYPE_OFFSET std::enable_if<std::is_same<VarIndex,varIndBase>::value,Offset24>::type
#define TEMPLATE_IND_OFFSET COND_IS_SAME(Offset24,IndexP)
template <typename VarIndex>
 struct colrf4 {
// uint8   format;
TEMPLATE_TYPE_OFFSET colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
ColorLine colorLine;
COLRF_GET(4,x0,y0,x1,y1,x2,y2,colorLine)
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
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf5 {
// uint8   format;
TEMPLATE_TYPE_OFFSET colorLineOffset; 
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
VarIndex   varIndexBase;
VarColorLine<VarIndex> colorLine;

CORLF_GET(5,x0,y0,x1,y1,x2,y2)
};//PaintVarLinearGradient;
ACQRES(colrf5<varIndBase>){
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
USE_ACQRES(colrf5<varIndBase>)
template <typename VarIndex>
struct colrf6 {
\\uint8   format;
TEMPLATE_TYPE_OFFSET colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
ColorLine colorLine;
COLRF_GET(6,x0,y0,radius0,x1,y1,radius1,colorLine)
};//PaintRadialGradient:*/;
ACQRES(colrf6<varIndBase>){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.radius0);
   one(f.x1);
   one(f.y1);
   one(f.radius1);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrf6<varIndBase>)
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf7 {
\\uint8   format;
TEMPLATE_TYPE_OFFSET   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
VarIndex   varIndexBase;
VarColorLine<VarIndex> colorLine;
COLRF_GET(7,x0,y0,radius0,x1,y1,radius1)
};//PaintVarRadialGradient:*/;
ACQRES(colrf7<varIndBase>){
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
USE_ACQRES(colrf7<varIndBase>)
template <typename VarIndex>
struct colrf8 {
\\uint8   format;
TEMPLATE_TYPE_OFFSET colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
ColorLine colorLine;
COLRF_GET(8,centerX,centerY,startAngle,endAngle,colorLine)
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
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf9 {
\\uint8   format;
TEMPLATE_TYPE_OFFSET colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
VarIndex   varIndexBase;
VarColorLine<VarIndex> colorLine;
COLRF_GET(9,centerX,centerY,startAngle,endAngle,colorLine)
};//PaintVarSweepGradient:*/;
ACQRES(colrf9<varIndBase>){
one(f.colorLineOffset);
one(f.centerX);
one(f.centerY);
one(f.startAngle);
one(f.endAngle);
one(f.varIndexBase);
offone(f.colorLine,colorLineOffset);
}
USE_ACQRES(colrf9<varIndBase>)
template <typename VarIndex>
 struct colrf10 {
\\uint8   format;
TEMPLATE_IND_OFFSET paintOffset;
uint16   glyphID;
// SpecialHandle
COLRF_GET(10,paintOffset,glyphID)
colrfu* get(colrf<varIndBase>* start,uint16 index){return (&start[index]+paintOffset);};
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
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct VarAffine2x3 {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
VarIndex   varIndexBase;
VarAffine2x3<varValueBase> operator=(decltype(*this)& l){
   VarAffine2x3<varValueBase> r;
   r.xx=xx;   r.yx=yx;   r.xy=xy;   r.yy=yy;   r.dx=dx;   r.dy=dy;}
};
template < typename SCOLR>
colrf<varIndBase>* getPaintOffset(SCOLR& start){
   return (&start-sizeof(uint8)+start.paintOffset);
};
#define TEMPLATE_PAINT_OFFSET Offset24
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf12  {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
TEMPLATE_TYPE_OFFSET transformOffset; // Stores Index to value in VarValueBase
Affine2x3 transform;
COLRF_GET(12,paintOffset,transform)
} ;//PaintTransform:*/;
ACQRES(colrf12<varIndBase>){
   one(f.paintOffset);
   one(f.transformOffset);
   offone(f.transform,f.transformOffset);
}
USE_ACQRES(colrf12<varIndBase>)
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf13  {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
Offset24 transformOffset; // Stores Index to value in VarValueBase
VarAffine2x3<VarIndex> transform;
COLRF_GET(13,paintOffset,transform)
};//PaintVarTransform:*/;
ACQRES(colrf13<varIndBase>){
   one(f.paintOffset);
   one(f.transformOffset);
   offone(f.transform,f.transformOffset);
}
USE_ACQRES(colrf13<varIndBase>)
struct colrf14  {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
FWORD   dx;
FWORD   dy;
COLRF_GET(14,dx,dy)
};//PaintTranslate:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
 struct colrf15  {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
FWORD   dx;
FWORD   dy;
VarIndex   varIndexBase;
COLRF_GET(15,dx,dy)
};//PaintVarTranslate:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf16  {
\\uint8   format;
TEMPLATE_TYPE_OFFSET   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
COLRF_GET(16,scalex,scaley)
};//PaintScale:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf17 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
VarIndex   varIndexBase;
COLRF_GET(17,scalex,scaley)
};//PaintVarScale:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf18{
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
COLRF_GET(18,paintOffset,scaleX,scaleY,centerX,centerY)
};//PaintScaleAroundCenter:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
 struct colrf19  {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
VarIndex   varIndexBase;
COLRF_GET(19,paintOffset,scaleX,scaleY,centerX,centerY)
} ;//PaintVarScaleAroundCenter:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf20  {
\\uint8   format;
TEMPLATE_TYPE_OFFSET   paintOffset;
F2DOT14   scale;
COLRF_GET(20,paintOffset,scale)
};//PaintScaleUniform:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf21{
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   scale;
VarIndex   varIndexBase;
COLRF_GET(21,paintOffset,scale)
};//PaintVarScaleUniform:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf22 {
\\uint8   format;
TEMPLATE_TYPE_OFFSET  paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
COLRF_GET(22,paintOffset,scale,centerX,centerY)

};//PaintScaleUniformAroundCenter:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf23 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
VarIndex varIndexBase;
COLRF_GET(23,paintOffset,scale,centerX,centerY)
} ;//PaintVarScaleUniformAroundCenter:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf24 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   angle;
COLRF_GET(24,paintOffset,angle)

};//PaintRotate:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf25 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   angle;
VarIndex   varIndexBase;
COLRF_GET(25,paintOffset,angle)
};//PaintVarRotate:*/;

template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf26 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
COLRF_GET(26,paintOffset,angle,centerX,centerY)
};//PaintRotateAroundCenter:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf27 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
VarIndex   varIndexBase;
COLRF_GET(24,paintOffset,angle,centerX,centerY)
};//PaintVarRotateAroundCenter:*/;
struct colrf28 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
COLRF_GET(28,paintOffset,xSkewAngle,ySkewAngle)
};//PaintSkew:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf29 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
VarIndex   varIndexBase;
COLRF_GET(29,paintOffset,xSkewAngle,ySkewAngle)
};//PaintVarSkew:*/;
struct colrf30 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
COLRF_GET(30,paintOffset,xSkewAngle,ySkewAngle,centerX,centerY)
};//PaintSkewAroundCenter:*/;
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf31 {
\\uint8   format;
TEMPLATE_PAINT_OFFSET paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
VarIndex   varIndexBase;
COLRF_GET(31,paintOffset,xSkewAngle,ySkewAngle,centerX,centerY)
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
template <typename VarIndex>
struct colrf32 {
\\uint8   format;
TEMPLATE_IND_OFFSET sourcePaintOffset;
uint8   compositeMode;
TEMPLATE_IND_OFFSET backdropPaintOffset;
CORLF_GET(32,sourcePaintoffset,compositeMode,backdropPaintOffset)
};//PaintComposite:*/;



template <typename VarIndex>
union colrfu {
   #define UNI(n) colrf##n<VarIndex> f##n;
   colrf1 f1;
   REPEAT(UNI , 2,3,4,5,6,7,8,9,10)
   colrf11 f11;
   REPEAT(UNI,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32)   
}
template <typename VarIndex>
struct colrf {
   uint8 format;
   colrfu<varIndex> f;
};
#define SWCASE(n) case n : {one(f.f##n);};

ACQRES(colrf<varIndBase>){
   one(f.format);
   switch(f.format){
      REPEAT(SWCASE,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32);
   }
}
USE_ACQRES(colrf<varIndBase>)
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
 struct BaseGlyphList{
uint32   numBaseGlyphPaintRecords;
BaseGlyphPaintRecord*   baseGlyphPaintRecords;//[numBaseGlyphPaintRecords]
colrf<varIndBase>* paintTables;
};
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
if(!f.paintTables){f.paintTables=new colrf<varIndBase>[numPaintTables];}
for(int i=0;i<f.numBaseGlyphPaintRecords;i++){
   offone(f.paintTables[i],f.baseGlyphPaintRecords.paintOffset);
};
 };
USE_ACQRES(BaseGlyphList)

typedef struct {
uint32   numLayers;
Offset32*   paintOffsets;//[numLayers]
colrf<varIndBase>* paintTables;
}LayerList;
ACQRES(LayerList){
one(f.numLayers);
arr(f.paintOffsets, f.numLayers);
offmany(f.paintTables,f.paintOffset,f.numLayers);
};
USE_ACQRES(LayerList)

struct COLR0 {
// uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
// OffsetTables;
BaseGlyph* baseGlyphRecords;
Layer* layerRecords ;
   colorFT get(uint16 gid){
      colorFT result ;
      auto cmpBg =  [](BaseGlyph& a  ){BaseGlyph res ;res.glyphID=gid;return res.glyphID==a.glyphID ? 0 : (res.glyphID<a.glyphID)? -1 : 1 ;}

      BaseGlyph Bg = bsearch<BaseGlyph>(baseGlyphRecords,numBaseGlyphRecords,cmpBg);       
      // GetNumGlyphs;
      result.baseGlyphs=new colrf<varValueBase>[result.numbaseGlyphs];
      for(int i=res.firstLayerIndex;i<res.numLayers-1+res.firstLayerIndex;i++)
      {
         result.baseGlyphs[i].format=2;
         result.baseGlyphs[i].f.f2.paletteIndex= CPAL().get(layerRecords[i].paletteIndex).get();  
      }
      return result;
   };
 
};
ACQRES(COLR0){
   one(f.numBaseGlyphRecords);
   one(f.baseGlyphRecordsOffset);
   one(f.layerRecordsOffset);
   one(f.numLayerRecords);
   offarr(f.baseGlyphRecords,f.baseGlyphRecordsOffset,f.numBaseGlyphRecords);
   offarr(f.layerRecords,f.layerRecordsOffset,f.numLayerRecords); 
}
USE_ACQRES(COLR0)

struct COLR1{
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


colrf<varValueBase> get(colrf<varIndBase>& cfvar){
   colrf<varValueBase> r;r.format=cfvar.format;
   #define GET_COLRF_CASE(n) case n : {r.f.f##n=cfvar.f.f##n.get();break;}
   #define GET_COLRF_VAR_CASE(n) case n :{r.f.f##n=cfvar.f.f##n.get();r.f.f##n.varIndexBase=varIndexBaseCopy(cfvar.f.f##n.varIndexBase);break;}
   switch (cfvar.format)
   {
      case 1 :{r.f.f1= cfvar.f.f1;break;}
      case 5 :{r.f.f5=cfvar.f.f5.get();r.f.f5.varIndexBase=varIndexBaseCopy(cfvar.f.f5.varIndexBase);r.f.f5.colorLine=varColorLineCopy(cfvar.f.f5.colorLine);break;}
      case 7 :{r.f.f7=cfvar.f.f7.get();r.f.f7.varIndexBase=varIndexBaseCopy(cfvar.f.f7.varIndexBase);r.f.f7.colorLine=varColorLineCopy(cfvar.f.f7.colorLine);break;}
      case 9 :{r.f.f9=cfvar.f.f9.get();r.f.f9.varIndexBase=varIndexBaseCopy(cfvar.f.f9.varIndexBase);r.f.f9.colorLine=varColorLineCopy(cfvar.f.f9.colorLine);break;}
      case 11 : {r.f.f11=cfvar.f.f11;break};
      REPEAT(GET_COLRF_VAR_CASE,3,15,17,19,21,23,25,27,29,31)
      case 13 :{r.f.f13=cfvar.f.f13.get();r.f.f13.transform.varIndexBase=varIndexBaseCopy(cfvar.f.f13.transform.varIndexBase);break};
      REPEAT(GET_COLRF_CASE,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32)              
   }
return r;
};
colrf<varValueBase>* getLayers(colrf1& f , size_t* s){
   *s=f.numLayers;
   colrf<varValueBase>* r = new colrf<varValueBase>[*s];
   for(int i=f.firstLayerIndex;i<*s;i++){
      r[i]=get(layerList.paintTables[i]);
   } ;
};
varValueBase varIndexBaseCopy(uint32 s){
varValueBase b;
switch(deltaSetIndexMap.format){
   case 0 :{b.mapValue =deltaSetIndexMap.f0.mapData+s;b.mapCount=deltaSetIndexMap.f0.mapCount *( ((deltaSetIndexMap.f0.entryFormat & MAP_ENTRY_SIZE_MASK) >> 4) + 1); };
   case 1 :{b.mapValue =deltaSetIndexMap.f1.mapData+s;b.mapCount=deltaSetIndexMap.f1.mapCount *( ((deltaSetIndexMap.f1.entryFormat & MAP_ENTRY_SIZE_MASK) >> 4) + 1); }
};              
};

VarColorLine<varValueBase> varColorLineCopy(VarColorLine<varIndBase>& l){
   VarColorLine<varValueBase> r;
   r.extend=l.extend;r.numStops=l.numStops;
   r.colorStops=new VarColorStop<varValueBase>[r.numStops];
   for(int i=0;i<r.numStops;i++){
      r.colorStops[i].paletteIndex=CPAL().get(l.colorStops[i].paletteIndex).get();
      r.colorStops[i].alpha=alphaval(l.colorStops[i].alpha);
      r.colorStops[i].varIndexBase=varColorLineCopy(l.colorStops[i].varIndexBase);
   }
}

colorFT get( uint16 gid){
     colorFT result ;
      if(numBaseGlyphRecords>0){

         auto cmpBg =  [&](BaseGlyph& a  ){BaseGlyph res ;res.glyphID=gid;return res.glyphID==a.glyphID ? 0 : (res.glyphID<a.glyphID)? -1 : 1 ;}
         BaseGlyph res ;res.glyphID=gid;

      res= bsearch<BaseGlyph>(baseGlyphRecords,numBaseGlyphRecords,cmpBg);
      result.numbaseGlyphs = res.numLayers;
      result.baseGlyphs=res.
      // GetNumGlyphs;
      result.baseGlyphs=new colrf<varValueBase>[result.numbaseGlyphs];
      for(int i=res.firstLayerIndex;i<res.numLayers-1+res.firstLayerIndex;i++)
      {
         result.baseGlyphs[i].format=2;
         result.baseGlyphs[i].f.f2.paletteIndex= CPAL().get(layerRecords[i].paletteIndex).get();  
      }
   } 
// BaseGlyphList

auto cmpBgl = [&](BaseGlyphPaintRecord& a){BaseGlyphPaintRecord r;r.glyphID=gid;return r.glyphID==a.glyphID ? 0 : (r.glyphID<a.glyphID)? -1 : 1 ;}};
baseGlyphList.baseGlyphPaintRecords[i].
BaseGlyphPaintRecord a = bsearch<BaseGlyphPaintRecord>(baseGlyphList.baseGlyphPaintRecords,BaseGlyphList.numBaseGlyphPaintRecords,cmpBgl);
colrf<varIndBase>* colrTable = (&baseGlyphList + baseGlyphList.paintOffset);

// LayerList 

   colrf<varValueBase> colrStart = get(colrTable);
   if(colrStart.format==1){
      size_t s;
      result.values = getLayers(colrStart.f.f1,&s);  
      result.numValues=s;
   }
   else (colrStart.format==32)


   
};



};//COLR1
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
   colorFT get(uint16 gid){
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