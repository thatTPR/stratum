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
arr(f.hMetrics, f.numberOfHMetrics);
 arr(f.leftSideBearings, f.numGlyphs - numberOfHMetrics);
 };
USE_ACQRES(hmtx)
#endif