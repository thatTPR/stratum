typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   reserved;
uint16   axisCount;
SegmentMaps*   axisSegmentMaps;//[axisCount]
}Axis/* variation table:*/;
ACQRES(Axis/* variation table:*/){
one(majorVersion);
one(minorVersion);
one(reserved);
one(axisCount);
arr(axisSegmentMaps, axisCount);
 };
USE_ACQRES(Axis/* variation table:*/)

typedef struct {
uint16   positionMapCount;
AxisValueMap*   axisValueMaps;//[positionMapCount]
}SegmentMaps/* record:*/;
ACQRES(SegmentMaps/* record:*/){
one(positionMapCount);
arr(axisValueMaps, positionMapCount);
 };
USE_ACQRES(SegmentMaps/* record:*/)

typedef struct {
F2DOT14   fromCoordinate;
F2DOT14   toCoordinate;
}AxisValueMap/* record:*/;
