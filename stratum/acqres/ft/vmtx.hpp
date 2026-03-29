#ifndef FTVMTX_HPP
#define FTVMTX_HPP
#include "vhea.hpp"
typedef struct {
    UFWORD	advanceHeight;//	The advance height of the glyph, in font design units.
    FWORD	topSideBearing;//	The top sidebearing of the glyph, in font design units.
}vmetrics;

typedef struct {
    vmetrics* vmet;
    FWORD*	topSideBearing;	The top sidebearing of the glyph, in font design units.
}vmtx;
ACQRES(vmtx){
    arr(vmet,_numOfLongVerMetrics);
    size_t topSide=_numGlyphs =_numOfLongVerMetrics;
    arr(f.topSideBearing,topSide);
}
USE_ACQRES(vmtx)
#endif