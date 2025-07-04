#ifndef FT_GLYPHMETRICS_HPP
#define FT_GLYPHMETRICS_HPP
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
#endif