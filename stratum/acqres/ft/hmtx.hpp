typedef struct {
LongHorMetric*   hMetrics;//[numberOfHMetrics]
FWORD*   leftSideBearings;//[numGlyphs - numberOfHMetrics]
}Horizontal/* Metrics Table:*/;
ACQRES(Horizontal/* Metrics Table:*/){
arr(hMetrics, numberOfHMetrics);
 arr(leftSideBearings, numGlyphs - numberOfHMetrics);
 };
USE_ACQRES(Horizontal/* Metrics Table:*/)

typedef struct {
UFWORD   advanceWidth;
FWORD   lsb;
}LongHorMetric/* Record:*/;
