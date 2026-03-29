#ifndef FTAVAR_HPP
#define FTAVAR_HPP
typedef struct {
F2DOT14   fromCoordinate;
F2DOT14   toCoordinate;
}AxisValueMap/* record:*/;

typedef struct {
uint16   positionMapCount;
AxisValueMap*   axisValueMaps;//[positionMapCount]
}SegmentMaps/* record:*/;
ACQRES(SegmentMaps/* record:*/){
one((f.positionMapCount));
arr(f.axisValueMaps, f.positionMapCount);
 };
USE_ACQRES(SegmentMaps/* record:*/)

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   reserved;
uint16   axisCount;
SegmentMaps*   axisSegmentMaps;//[axisCount]
}Axis/* variation table:*/;
ACQRES(Axis/* variation table:*/){
one((f.majorVersion));
one((f.minorVersion));
one((f.reserved));
one((f.axisCount));
arr(f.axisSegmentMaps, f.axisCount);
 };
USE_ACQRES(Axis/* variation table:*/)
#endif