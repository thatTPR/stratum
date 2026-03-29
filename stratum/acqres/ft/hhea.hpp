#ifndef FTHHEA_HPP
#define FTHHEA_HPP
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
FWORD   ascender;
FWORD   descender;
FWORD   lineGap;
UFWORD   advanceWidthMax;
FWORD   minLeftSideBearing;
FWORD   minRightSideBearing;
FWORD   xMaxExtent;
int16   caretSlopeRise;
int16   caretSlopeRun;
int16   caretOffset;
int16   reserved1;
int16   reserved2;
int16   reserved3;
int16   reserved4;
int16   metricDataFormat;
uint16   numberOfHMetrics;
}hhea;
#endif