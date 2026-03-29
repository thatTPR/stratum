#ifndef FTGASP_HPP
#define FTGASP_HPP
enum RangeGaspBehavior {
GASP_GRIDFIT=0x0001,//
GASP_DOGRAY=0x0002,//
GASP_SYMMETRIC_GRIDFIT=0x0004,//
GASP_SYMMETRIC_SMOOTHING=0x0008,//
Reserved=0xFFF0//
};
typedef struct {
uint16   rangeMaxPPEM;
uint16   rangeGaspBehavior;
}GaspRange/* Record*/;

typedef struct {
uint16   version;
uint16   numRanges;
GaspRange*   gaspRanges;//[numRanges]
}gasp/* Header*/;
ACQRES(gasp/* Header*/){
one((f.version));
one((f.numRanges));
arr(f.gaspRanges, f.numRanges);
 };
USE_ACQRES(gasp/* Header*/)
#endif