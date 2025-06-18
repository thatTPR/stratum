typedef struct {
uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
}COLR/* version 0:*/;
typedef struct {
uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
Offset32   baseGlyphListOffset;
Offset32   layerListOffset;
Offset32   clipListOffset;
Offset32   varIndexMapOffset;
Offset32   itemVariationStoreOffset;
}COLR/* version 1:*/;
typedef struct {
uint16   glyphID;
uint16   firstLayerIndex;
uint16   numLayers;
}BaseGlyph/* record:*/;
typedef struct {
uint16   glyphID;
uint16   paletteIndex;
}Layer/* record:*/;
typedef struct {
uint32   numBaseGlyphPaintRecords;
BaseGlyphPaintRecord*   baseGlyphPaintRecords;//[numBaseGlyphPaintRecords]
}BaseGlyphList/* table:*/;
ACQRES(BaseGlyphList/* table:*/){
one(numBaseGlyphPaintRecords);
arr(baseGlyphPaintRecords, numBaseGlyphPaintRecords);
 };
USE_ACQRES(BaseGlyphList/* table:*/)

typedef struct {
uint16   glyphID;
Offset32   paintOffset;
}BaseGlyphPaintRecord:;
typedef struct {
uint32   numLayers;
Offset32*   paintOffsets;//[numLayers]
}LayerList/* table:*/;
ACQRES(LayerList/* table:*/){
one(numLayers);
arr(paintOffsets, numLayers);
 };
USE_ACQRES(LayerList/* table:*/)

typedef struct {
uint8   format;
uint32   numClips;
Clip*   clips;//[numClips]
}ClipList/* table:*/;
ACQRES(ClipList/* table:*/){
one(format);
one(numClips);
arr(clips, numClips);
 };
USE_ACQRES(ClipList/* table:*/)

typedef struct {
uint16   startGlyphID;
uint16   endGlyphID;
Offset24   clipBoxOffset;
}Clip/* record:*/;
typedef struct {
uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
}ClipBoxFormat1/* table, static clip box:*/;
typedef struct {
uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
uint32   varIndexBase;
}ClipBoxFormat2/* table, variable clip box:*/;
typedef struct {
F2DOT14   stopOffset;
uint16   paletteIndex;
F2DOT14   alpha;
}ColorStop/* record:*/;
typedef struct {
F2DOT14   stopOffset;
uint16   paletteIndex;
F2DOT14   alpha;
uint32   varIndexBase;
}VarColorStop/* record:*/;
typedef struct {
uint8   extend;
uint16   numStops;
ColorStop*   colorStops;//[numStops]
}ColorLine/* table:*/;
ACQRES(ColorLine/* table:*/){
one(extend);
one(numStops);
arr(colorStops, numStops);
 };
USE_ACQRES(ColorLine/* table:*/)

typedef struct {
uint8   extend;
uint16   numStops;
VarColorStop*   colorStops;//[numStops]
}VarColorLine/* table:*/;
ACQRES(VarColorLine/* table:*/){
one(extend);
one(numStops);
arr(colorStops, numStops);
 };
USE_ACQRES(VarColorLine/* table:*/)

typedef struct {
0   EXTEND_PAD;
1   EXTEND_REPEAT;
2   EXTEND_REFLECT;
}Extend/* enumeration:*/;
typedef struct {
uint8   format;
uint8   numLayers;
uint32   firstLayerIndex;
}PaintColrLayers/* table (format 1):*/;
typedef struct {
uint8   format;
uint16   paletteIndex;
F2DOT14   alpha;
}PaintSolid/* table (format 2):*/;
typedef struct {
uint8   format;
uint16   paletteIndex;
F2DOT14   alpha;
uint32   varIndexBase;
}PaintVarSolid/* table (format 3):*/;
typedef struct {
uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
}PaintLinearGradient/* table (format 4):*/;
typedef struct {
uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
uint32   varIndexBase;
}PaintVarLinearGradient/* table (format 5):*/;
typedef struct {
uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
}PaintRadialGradient/* table (format 6):*/;
typedef struct {
uint8   format;
Offset24   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
uint32   varIndexBase;
}PaintVarRadialGradient/* table (format 7):*/;
typedef struct {
uint8   format;
Offset24   colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
}PaintSweepGradient/* table (format 8):*/;
typedef struct {
uint8   format;
Offset24   colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
uint32   varIndexBase;
}PaintVarSweepGradient/* table (format 9):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
uint16   glyphID;
}PaintGlyph/* table (format 10):*/;
typedef struct {
uint8   format;
uint16   glyphID;
}PaintColrGlyph/* table (format 11):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
Offset24   transformOffset;
}PaintTransform/* table (format 12):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
Offset24   transformOffset;
}PaintVarTransform/* table (format 13):*/;
typedef struct {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
}Affine2x3/* table:*/;
typedef struct {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
uint32   varIndexBase;
}VarAffine2x3/* table:*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
FWORD   dx;
FWORD   dy;
}PaintTranslate/* table (format 14):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
FWORD   dx;
FWORD   dy;
uint32   varIndexBase;
}PaintVarTranslate/* table (format 15):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
}PaintScale/* table (format 16):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
uint32   varIndexBase;
}PaintVarScale/* table (format 17):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
}PaintScaleAroundCenter/* table (format 18):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}PaintVarScaleAroundCenter/* table (format 19):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
}PaintScaleUniform/* table (format 20):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
uint32   varIndexBase;
}PaintVarScaleUniform/* table (format 21):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
}PaintScaleUniformAroundCenter/* table (format 22):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}PaintVarScaleUniformAroundCenter/* table (format 23):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
}PaintRotate/* table (format 24):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
uint32   varIndexBase;
}PaintVarRotate/* table (format 25):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
}PaintRotateAroundCenter/* table (format 26):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}PaintVarRotateAroundCenter/* table (format 27):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
}PaintSkew/* table (format 28):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
uint32   varIndexBase;
}PaintVarSkew/* table (format 29):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
}PaintSkewAroundCenter/* table (format 30):*/;
typedef struct {
uint8   format;
Offset24   paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
uint32   varIndexBase;
}PaintVarSkewAroundCenter/* table (format 31):*/;
typedef struct {
uint8   format;
Offset24   sourcePaintOffset;
uint8   compositeMode;
Offset24   backdropPaintOffset;
}PaintComposite/* table (format 32):*/;
typedef struct {
   ;
0   COMPOSITE_CLEAR;
1   COMPOSITE_SRC;
2   COMPOSITE_DEST;
3   COMPOSITE_SRC_OVER;
4   COMPOSITE_DEST_OVER;
5   COMPOSITE_SRC_IN;
6   COMPOSITE_DEST_IN;
7   COMPOSITE_SRC_OUT;
8   COMPOSITE_DEST_OUT;
9   COMPOSITE_SRC_ATOP;
10   COMPOSITE_DEST_ATOP;
11   COMPOSITE_XOR;
12   COMPOSITE_PLUS;
   ;
13   COMPOSITE_SCREEN;
14   COMPOSITE_OVERLAY;
15   COMPOSITE_DARKEN;
16   COMPOSITE_LIGHTEN;
17   COMPOSITE_COLOR_DODGE;
18   COMPOSITE_COLOR_BURN;
19   COMPOSITE_HARD_LIGHT;
20   COMPOSITE_SOFT_LIGHT;
21   COMPOSITE_DIFFERENCE;
22   COMPOSITE_EXCLUSION;
23   COMPOSITE_MULTIPLY;
   ;
24   COMPOSITE_HSL_HUE;
25   COMPOSITE_HSL_SATURATION;
26   COMPOSITE_HSL_COLOR;
27   COMPOSITE_HSL_LUMINOSITY;
}CompositeMode/* enumeration:*/;
