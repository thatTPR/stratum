typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapSize*   bitmapSizes;//[numSizes]
}EBLC/* Header*/;
ACQRES(EBLC/* Header*/){
one(majorVersion);
one(minorVersion);
one(numSizes);
arr(bitmapSizes, numSizes);
 };
USE_ACQRES(EBLC/* Header*/)

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
}BitmapSize/* record*/;
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
}SbitLineMetrics/* record*/;
typedef struct {
0x01   HORIZONTAL_METRICS;
0x02   VERTICAL_METRICS;
0xFC   Reserved;
}Bitmap/* flags enumeration*/;
typedef struct {
uint8   height;
uint8   width;
int8   horiBearingX;
int8   horiBearingY;
uint8   horiAdvance;
int8   vertBearingX;
int8   vertBearingY;
uint8   vertAdvance;
}BigGlyphMetrics/* record*/;
typedef struct {
uint8   height;
uint8   width;
int8   bearingX;
int8   bearingY;
uint8   advance;
}SmallGlyphMetrics/* record*/;
typedef struct {
IndexSubtableRecord   indexSubtableRecords;
}IndexSubtableList/* table*/;
typedef struct {
uint16   firstGlyphIndex;
uint16   lastGlyphIndex;
Offset32   indexSubtableOffset;
}IndexSubtableRecord;
typedef struct {
uint16   indexFormat;
uint16   imageFormat;
Offset32   imageDataOffset;
}IndexSubHeader/* record*/;
typedef struct {
IndexSubHeader   header;
Offset32*   sbitOffsets;//[numOffsets]
}IndexSubtableFormat1/* table*/;
ACQRES(IndexSubtableFormat1/* table*/){
one(header);
arr(sbitOffsets, numOffsets);
 };
USE_ACQRES(IndexSubtableFormat1/* table*/)

typedef struct {
IndexSubHeader   header;
uint32   imageSize;
BigGlyphMetrics   bigMetrics;
}IndexSubtableFormat2/* table*/;
typedef struct {
IndexSubHeader   header;
Offset16*   sbitOffsets;//[numOffsets]
}IndexSubtableFormat3/* table*/;
ACQRES(IndexSubtableFormat3/* table*/){
one(header);
arr(sbitOffsets, numOffsets);
 };
USE_ACQRES(IndexSubtableFormat3/* table*/)

typedef struct {
IndexSubHeader   header;
uint32   numGlyphs;
GlyphIdOffsetPair*   glyphArray;//[numGlyphs + 1]
}IndexSubtableFormat4/* table*/;
ACQRES(IndexSubtableFormat4/* table*/){
one(header);
one(numGlyphs);
arr(glyphArray, numGlyphs + 1);
 };
USE_ACQRES(IndexSubtableFormat4/* table*/)

typedef struct {
uint16   glyphID;
Offset16   sbitOffset;
}GlyphIdOffsetPair/* record*/;
typedef struct {
IndexSubHeader   header;
uint32   imageSize;
BigGlyphMetrics   bigMetrics;
uint32   numGlyphs;
uint16*   glyphIdArray;//[numGlyphs]
}IndexSubtableFormat5/* table*/;
ACQRES(IndexSubtableFormat5/* table*/){
one(header);
one(imageSize);
one(bigMetrics);
one(numGlyphs);
arr(glyphIdArray, numGlyphs);
 };
USE_ACQRES(IndexSubtableFormat5/* table*/)

