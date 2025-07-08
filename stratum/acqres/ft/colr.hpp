typedef struct {
   uint16   glyphID;
   uint16   paletteIndex;
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
}BaseGlyphList;
ACQRES(BaseGlyphList){
one(f.numBaseGlyphPaintRecords);
arr(f.baseGlyphPaintRecords, f.numBaseGlyphPaintRecords);
 };
USE_ACQRES(BaseGlyphList)

typedef struct {
uint32   numLayers;
Offset32*   paintOffsets;//[numLayers]
}LayerList;
ACQRES(LayerList){
one(f.numLayers);
arr(f.paintOffsets, f.numLayers);
 };
USE_ACQRES(LayerList)

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
typedef struct {
// uint8   format;
uint8   numLayers;
uint32   firstLayerIndex;
}colrf1;//PaintColrLayers
typedef struct {
// uint8   format;
uint16   paletteIndex;
F2DOT14   alpha;
}colrf2;//PaintSolid table ;
typedef struct {
// uint8   format;
uint16   paletteIndex;
F2DOT14   alpha;
uint32   varIndexBase;
}colrf3;//PaintVarSolid;
typedef struct {
// uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
}colrf4;//PaintLinearGradient;
typedef struct {
// uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
uint32   varIndexBase;
}colrf5;//PaintVarLinearGradient;
typedef struct {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
}colrf6 ;//PaintRadialGradient:*/;
typedef struct {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
uint32   varIndexBase;
}colrf7 ;//PaintVarRadialGradient:*/;
typedef struct {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
}colrf8 ;//PaintSweepGradient:*/;
typedef struct {
\\uint8   format;
Offset24   colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
uint32   varIndexBase;
}colrf9 ;//PaintVarSweepGradient:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
uint16   glyphID;
}colrf10 ;//PaintGlyph:*/;
typedef struct {
\\uint8   format;
uint16   glyphID;
}colrf11 ;//PaintColrGlyph:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
Offset24   transformOffset;
}colrf12 ;//PaintTransform:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
Offset24   transformOffset;
}colrf13 ;//PaintVarTransform:*/;
typedef struct {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
}Affine2x3;
typedef struct {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
uint32   varIndexBase;
}VarAffine2x3;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
FWORD   dx;
FWORD   dy;
}colrf14 ;//PaintTranslate:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
FWORD   dx;
FWORD   dy;
uint32   varIndexBase;
}colrf15 ;//PaintVarTranslate:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
}colrf16 ;//PaintScale:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
uint32   varIndexBase;
}colrf17 ;//PaintVarScale:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
}colrf18 ;//PaintScaleAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}colrf19 ;//PaintVarScaleAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
}colrf20 ;//PaintScaleUniform:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
uint32   varIndexBase;
}colrf21 ;//PaintVarScaleUniform:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
}colrf22 ;//PaintScaleUniformAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}colrf23 ;//PaintVarScaleUniformAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
}colrf24 ;//PaintRotate:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
uint32   varIndexBase;
}colrf25 ;//PaintVarRotate:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
}colrf26 ;//PaintRotateAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}colrf27 ;//PaintVarRotateAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
}colrf28 ;//PaintSkew:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
uint32   varIndexBase;
}colrf29 ;//PaintVarSkew:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
}colrf30 ;//PaintSkewAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}colrf31 ;//PaintVarSkewAroundCenter:*/;
typedef struct {
\\uint8   format;
Offset24   sourcePaintOffset;
uint8   compositeMode;
Offset24   backdropPaintOffset;
}colrf32 ;//PaintComposite:*/;
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
// uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
// OffsetTables;
BaseGlyph* baseGlyphRecords;
Layer* layerRecords ;
   get(uint16 gid){
      int n = numBaseGlyphRecords/2;
      int i ;
      for(i=n;n>=1;){
         if(baseGlyphRecords[i].glyphID == gid){
            ColorRecord* crs = new ColorRecord[baseGlyphRecords[i].numLayers]; 
            for(int j =baseGlyphRecords[i].firstLayerIndex,j<baseGlyphRecords[i].numLayers;j++){
               if(layerRecords[j].glyphID==gid){
                  crs[j]=fcur->cpal().get(layerRecords[j].paletteIndex);}
            } 
            
         };
         n=n/2;
         if(baseGlyphRecords[i].glyphID> gid) {i-=n; }
         else(baseGlyphRecords[i].glyphID<gid){i+=n;};
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
Layer* layerRecords ;
BaseGlyphList baseGlyphList;
LayerList layerList;
ClipList clipList;
    get(uint16 gid){
      
    } ;
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
   offone(f.baseGlyphList,f.baseGlyphListOffset);
   offone(f.layerList,f.layerListOffset);
   offone(f.clipList,f.clipListOffset);
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
