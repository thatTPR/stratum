#ifndef FTFMTX_HPP
#define FTFMTX_HPP

typedef struct {
    UFWORD   advanceWidth;
    FWORD   lsb;
}LongHorMetric;
typedef struct {
LongHorMetric*   hMetrics;//[numberOfHMetrics]
FWORD*   leftSideBearings;//[numGlyphs - numberOfHMetrics]
}hmtx;
ACQRES(hmtx){
arr(f.hMetrics, ftcur->hhea().numberOfHMetrics);
 arr(f.leftSideBearings, ftcur->maxp().numGlyphs - ftcur->hhea().numberOfHMetrics);
 };
USE_ACQRES(hmtx)
#endif