#ifndef FTEBSC_HPP
#define FTEBSC_HPP
#include "ebdt.hpp"
#include "eblc.hpp"
typedef struct {
SbitLineMetrics   hori;
SbitLineMetrics   vert;
uint8   ppemX;
uint8   ppemY;
uint8   substitutePpemX;
uint8   substitutePpemY;
}BitmapScale;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapScale*   strikes;//[numSizes]
}EBSC/* table*/;
ACQRES(EBSC){
one((f.majorVersion));
one((f.minorVersion));
one((f.numSizes));
arr(f.strikes, f.numSizes);
 };
USE_ACQRES(EBSC)
#endif