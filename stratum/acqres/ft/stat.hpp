typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   designAxisSize;
uint16   designAxisCount;
Offset32   designAxesOffset;
uint16   axisValueCount;
Offset32   offsetToAxisValueOffsets;
uint16   elidedFallbackNameID;
}Style/* attributes header:*/;
typedef struct {
Tag   axisTag;
uint16   axisNameID;
uint16   axisOrdering;
}AxisRecord:;
typedef struct {
uint16   format;
uint16   axisIndex;
uint16   flags;
uint16   valueNameID;
Fixed   value;
}AxisValueFormat1:;
typedef struct {
uint16   format;
uint16   axisIndex;
uint16   flags;
uint16   valueNameID;
Fixed   nominalValue;
Fixed   rangeMinValue;
Fixed   rangeMaxValue;
}AxisValueFormat2;
typedef struct {
uint16   format;
uint16   axisIndex;
uint16   flags;
uint16   valueNameID;
Fixed   value;
Fixed   linkedValue;
}AxisValueFormat3:;
typedef struct {
uint16   format;
uint16   axisCount;
uint16   flags;
uint16   valueNameID;
AxisValue*   axisValues;//[axisCount]
}AxisValueFormat4:;
ACQRES(AxisValueFormat4:){
one(format);
one(axisCount);
one(flags);
one(valueNameID);
arr(axisValues, axisCount);
 };
USE_ACQRES(AxisValueFormat4:)

typedef struct {
uint16   axisIndex;
Fixed   value;
}AxisValue/* record:*/;
