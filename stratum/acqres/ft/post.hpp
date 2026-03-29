#ifndef FTPOST_HPP
#define FTPOST_HPP
typedef struct {
Version16Dot16	version	;
//0x00010000 for version 1.0
/*0x00020000 for version 2.0
  0x00025000 for version 2.5 (deprecated)
  0x00030000 for version 3.0*/
Fixed	italicAngle ;//	Italic angle in counter-clockwise degrees from the vertical. Zero for upright text, negative for text that leans to the right (forward).
FWORD	underlinePosition ;//	Suggested y-coordinate of the top of the underline.
FWORD	underlineThickness ;//	Suggested values for the underline thickness. In general, the underline thickness should match the thickness of the underscore character (U+005F LOW LINE), and should also match the strikeout thickness, which is specified in the OS/2 table.
uint32	isFixedPitch ;//	Set to 0 if the font is proportionally spaced, non-zero if the font is not proportionally spaced (i.e. monospaced).
uint32	minMemType42 ;//	Minimum memory usage when an OpenType font is downloaded.
uint32	maxMemType42 ;//	Maximum memory usage when an OpenType font is downloaded.
uint32	minMemType1 ;//	Minimum memory usage when an OpenType font is downloaded as a Type 1 font.
uint32	maxMemType1 ;//	Maximum memory usage when an OpenType font is downloaded as a Type 1 font.
}postv;
typedef struct {
uint16	numGlyphs;//	Number of glyphs (this should be the same as numGlyphs in 'maxp' table).
uint16*	glyphNameIndex;//[numGlyphs]	Array of indices into the string data. See below for details.
uint8*	stringData;//[variable]	Storage for the string data.
}postv2 ;
ACQRES(v2){
    one(f.numGlyps);
    arr(f.glyphNameIndex,f.numGlyphs);
    arr(f.glyphNameIndex,f.numGlyphs);
    uint32 l = _length - sizeof(postv)-sizeof(f.numGlyphs) - sizeof(f.glyphNameIndex)*f.numGlyphs;
    arr(f.stringData,l);
}
USE_ACQRES(postv2)
typedef struct {
    uint16	numGlyphs ;//	Number of glyphs.
    int8*	offset ;//[numGlyphs]	Difference between the glyph index and the standard order of the glyph.
}postv25;
ACQRES(v25){
    one(f.numGlyps);
    arr(f.offset,f.numGlyphs);
}
USE_ACQRES(postv2)

typedef struct {
    postv ver;
    postv2 v2;
    postv25 v25;
}post;
ACQRES(post){
    one(f.ver);
    switch(f.ver.version){
        case 0x00020000 : {one(f.v2); }
        case 0x00025000 : {one(f.v25); }
    };
}
#endif