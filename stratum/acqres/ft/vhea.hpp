#ifndef FTVHEA_HPP
#define FTVHEA_HPP
typedef struct {
// Version16Dot16   version;
FWORD   ascent;
FWORD   descent;
FWORD   lineGap;
UFWORD   advanceHeightMax;
FWORD   minTop;
FWORD   minBottom;
FWORD   yMaxExtent;
int16   caretSlopeRise;
int16   caretSlopeRun;
int16   caretOffset;
int16   reserved1;
int16   reserved2;
int16   reserved3;
int16   reserved4;
int16   metricDataFormat;
uint16   numOfLongVerMetrics;
}VheaHeader10;
typedef struct {
// Version16Dot16   version;
FWORD   vertTypoAscender;
FWORD   vertTypoDescender;
FWORD   vertTypoLineGap;
UFWORD   advanceHeightMax;
FWORD   minTop;
FWORD   minBottom;
FWORD   yMaxExtent;
int16   caretSlopeRise;
int16   caretSlopeRun;
int16   caretOffset;
int16   reserved1;
int16   reserved2;
int16   reserved3;
int16   reserved4;
int16   metricDataFormat;
uint16   numOfLongVerMetrics;
}VheaHeader11;
uint16   _numOfLongVerMetrics;

VheaHeader11& operator=(VheaHeader10& f){return f;};
VheaHeader10& operator=(VheaHeader11& f){return f;};
typedef VheaHeader10 vhea ;
ACQRES(vhea){
    one(f);
    _numOfLongVerMetrics=f.numOfLongVerMetrics;
}
#endif