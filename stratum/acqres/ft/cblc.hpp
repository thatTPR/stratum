typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapSize*   bitmapSizes;//[numSizes]
}CblcHeader;
ACQRES(CblcHeader){
one(majorVersion);
one(minorVersion);
one(numSizes);
arr(bitmapSizes, numSizes);
 };
USE_ACQRES(CblcHeader)

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
