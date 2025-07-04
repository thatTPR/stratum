#ifndef FTHEAD_HPP
#define FTHEAD_HPP
 int16   _indexToLocFormat;

typedef struct {
 uint16   majorVersion;
 uint16   minorVersion;
 Fixed   fontRevision;
 uint32   checksumAdjustment;
 uint32   magicNumber;
 uint16   flags;
 /*Bit 0: Baseline for font at y=0.

Bit 1: Left sidebearing point at x=0 (relevant only for TrueType rasterizers) — see additional information below regarding variable fonts.

Bit 2: Instructions may depend on point size.

Bit 3: Force ppem to integer values for all internal scaler math; may use fractional ppem sizes if this bit is clear. It is strongly recommended that this be set in hinted fonts.

Bit 4: Instructions may alter advance width (the advance widths might not scale linearly).

Bit 5: This bit is not used in OpenType, and should not be set in order to ensure compatible behavior on all platforms. If set, it may result in different behavior for vertical layout in some platforms. (See Apple’s specification for details regarding behavior in Apple platforms.)

Bits 6 – 10: These bits are not used in OpenType and should always be cleared. (See Apple’s specification for details regarding legacy use in Apple platforms.)

Bit 11: Font data is “lossless” as a result of having been subjected to optimizing transformation and/or compression (such as compression mechanisms defined by ISO/IEC 14496-18, MicroType® Express, WOFF 2.0, or similar) where the original font functionality and features are retained but the binary compatibility between input and output font files is not guaranteed. As a result of the applied transform, the DSIG table may also be invalidated.

Bit 12: Font converted (produce compatible metrics).

Bit 13: Font optimized for ClearType®. Note, fonts that rely on embedded bitmaps (EBDT) for rendering should not be considered optimized for ClearType, and therefore should keep this bit cleared.

Bit 14: Last Resort font. If set, indicates that the glyphs encoded in the 'cmap' subtables are simply generic symbolic representations of code point ranges and do not truly represent support for those code points. If unset, indicates that the glyphs encoded in the 'cmap' subtables represent proper support for those code points.

Bit 15: Reserved, set to 0.*/
 uint16   unitsPerEm;
 LONGDATETIME   created;
 LONGDATETIME   modified;
 int16   xMin;
 int16   yMin;
 int16   xMax;
 int16   yMax;
 uint16   macStyle;
 /*Bit 0: Bold (if set to 1);
Bit 1: Italic (if set to 1)
Bit 2: Underline (if set to 1)
Bit 3: Outline (if set to 1)
Bit 4: Shadow (if set to 1)
Bit 5: Condensed (if set to 1)
Bit 6: Extended (if set to 1)
Bits 7 – 15: Reserved (set to 0).*/
 uint16   lowestRecPPEM;
 int16   fontDirectionHint ;
 int16   indexToLocFormat;
 int16   glyphDataFormat;
}head /* glyphs that have contours. Glyphs with no contours should be ignored for the purposes of these calculations.only*/;
ACQRES(head){
    one(f);
    _indexToLocFormat=f.indexToLocFormat;
}
#endif