typedef struct {
uint16   version;
uint16   numRanges;
GaspRange*   gaspRanges;//[numRanges]
}gasp'/* Header*/;
ACQRES(gasp'/* Header*/){
one(version);
one(numRanges);
arr(gaspRanges, numRanges);
 };
USE_ACQRES(gasp'/* Header*/)

typedef struct {
uint16   rangeMaxPPEM;
uint16   rangeGaspBehavior;
}GaspRange/* Record*/;
typedef struct {
0x0001   GASP_GRIDFIT;
0x0002   GASP_DOGRAY;
0x0004   GASP_SYMMETRIC_GRIDFIT;
0x0008   GASP_SYMMETRIC_SMOOTHING;
0xFFF0   Reserved;
}RangeGaspBehavior/* flags*/;
