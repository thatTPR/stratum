#ifndef FTLTSH_HPP
#define FTLTSH_HPP
typedef struct {
    uint16	version	;//Version number—set to 0.
    uint16	numGlyphs	;//Number of glyphs (from numGlyphs in 'maxp' table).
    uint8*	yPixels;//[numGlyphs];//	The vertical pixel height at which the glyph can be assumed to scale linearly. On a per glyph basis.
}LTSH;
ACQRES(LTSH){
    one(f.version);
    one(f.numGlyphs);
    arr(f.yPixels,f.numGlyphs);
}
USE_ACQRES(LTSH)
#endif