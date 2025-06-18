typedef struct {
uint16   majorVersion;
uint16   minorVersion;
}CbdtHeader;
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
smallGlyphMetrics   glyphMetrics;
uint32   dataLen;
uint8*   data;//[dataLen]
}GlyphBitmapFormat17/* table*/;
ACQRES(GlyphBitmapFormat17/* table*/){
one(glyphMetrics);
one(dataLen);
arr(data, dataLen);
 };
USE_ACQRES(GlyphBitmapFormat17/* table*/)

typedef struct {
bigGlyphMetrics   glyphMetrics;
uint32   dataLen;
uint8*   data;//[dataLen]
}GlyphBitmapFormat18/* table*/;
ACQRES(GlyphBitmapFormat18/* table*/){
one(glyphMetrics);
one(dataLen);
arr(data, dataLen);
 };
USE_ACQRES(GlyphBitmapFormat18/* table*/)

typedef struct {
uint32   dataLen;
uint8*   data;//[dataLen]
}GlyphBitmapFormat19/* table*/;
ACQRES(GlyphBitmapFormat19/* table*/){
one(dataLen);
arr(data, dataLen);
 };
USE_ACQRES(GlyphBitmapFormat19/* table*/)

