typedef struct {
uint16   majorVersion;
uint16   minorVersion;
}EBDT/* Header*/;
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
uint16   glyphID;
int8   xOffset;
int8   yOffset;
}EbdtComponent/* record*/;
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8   imageData;
}GlyphBitmapFormat1/* table*/;
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8   imageData;
}GlyphBitmapFormat2/* table*/;
typedef struct {
uint8   imageData;
}GlyphBitmapFormat5/* table*/;
typedef struct {
BigGlyphMetrics   bigMetrics;
uint8   imageData;
}GlyphBitmapFormat6/* table*/;
typedef struct {
BigGlyphMetrics   bigMetrics;
uint8   imageData;
}GlyphBitmapFormat7/* table*/;
typedef struct {
SmallGlyphMetrics   smallMetrics;
uint8   pad;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
}GlyphBitmapFormat8/* table*/;
ACQRES(GlyphBitmapFormat8/* table*/){
one(smallMetrics);
one(pad);
one(numComponents);
arr(components, numComponents);
 };
USE_ACQRES(GlyphBitmapFormat8/* table*/)

typedef struct {
BigGlyphMetrics   bigMetrics;
uint16   numComponents;
EbdtComponent*   components;//[numComponents]
}GlyphBitmapFormat9/* table*/;
ACQRES(GlyphBitmapFormat9/* table*/){
one(bigMetrics);
one(numComponents);
arr(components, numComponents);
 };
USE_ACQRES(GlyphBitmapFormat9/* table*/)

