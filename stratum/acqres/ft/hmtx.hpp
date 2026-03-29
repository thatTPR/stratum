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
arr(f.hMetrics, hhea().numberOfHMetrics);
 arr(f.leftSideBearings, maxp().numGlyphs - hhea().numberOfHMetrics);
 };
USE_ACQRES(hmtx)
#endif