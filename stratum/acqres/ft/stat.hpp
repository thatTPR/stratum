#ifndef FTSTAT_HPP
#define FTSTAT_HPP
enum AxisValFlags{
    OLDER_SIBLING_FONT_ATTRIBUTE=0x0001	,//	If set, this axis value table provides axis value information that is applicable to other fonts within the same font family. This is used if the other fonts were released earlier and did not include information about values for some axis. If newer versions of the other fonts include the information themselves and are present, then this table is ignored.
    ELIDABLE_AXIS_VALUE_NAME=0x0002	,//	If set, it indicates that the axis value represents the “normal” value for the axis and may be omitted when composing name strings.
    Reserved=0xFFFC	//	Reserved for future use — set to zero.
};
typedef struct {
uint16   axisIndex;
Fixed   value;
}AxisValueRecord;
typedef struct {
// uint16   format;
// uint16   axisIndex;
// uint16   flags;
// uint16   valueNameID;
Fixed   value;
}AxisValueFormat1;
typedef struct {
// uint16   format;
// uint16   axisIndex;
// uint16   flags;
// uint16   valueNameID;
Fixed   nominalValue;
Fixed   rangeMinValue;
Fixed   rangeMaxValue;
}AxisValueFormat2;
typedef struct {
// uint16   format;
// uint16   axisIndex;
// uint16   flags;
// uint16   valueNameID;
Fixed   value;
Fixed   linkedValue;
}AxisValueFormat3;
typedef struct {
// uint16   format;
// uint16   axisCount;
// uint16   flags;
// uint16   valueNameID;
AxisValue*   axisValues;//[axisCount]
}AxisValueFormat4;
ACQRES(AxisValueFormat4:){
one(f.format);
one(f.axisCount);
one(f.flags);
one(f.valueNameID);
arr(f.axisValues, f.axisCount);
 };
USE_ACQRES(AxisValueFormat4:)
typedef struct {
    uint16 format;
    uint16   axisIndex;
uint16   flags;
uint16   valueNameID;

    union {
        AxisValueFormat1 f1;
        AxisValueFormat2 f2;
        AxisValueFormat3 f3;
        AxisValueFormat4 f4;
    }f;
}AxisVal;
ACQRES(AxisVal){
    one(f.format);
one(f.axisCount);
one(f.flags);
one(f.valueNameID);
switch (f.format)
{
case 1:{one(f.f.f1);};
case 2:{one(f.f.f2);};
case 3:{one(f.f.f3);};
case 4:{one(f.f.f4);};
};
}
USE_ACQRES(AxisVal)
typedef struct {
Tag   axisTag;
uint16   axisNameID;
uint16   axisOrdering;
}AxisRecord;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   designAxisSize;
uint16   designAxisCount;
Offset32   designAxesOffset;
uint16   axisValueCount;
Offset32   offsetToAxisValueOffsets;
uint16   elidedFallbackNameID;

AxisRecord*	designAxes;//[designAxisCount]	The design-axes array.
Offset16* AxisValueOffsets; 

AxisVal* axisValues;
 

}STAT;
ACQRES(STAT){
one(f.majorVersion);
one(f.minorVersion);
one(f.designAxisSize);
one(f.designAxisCount);
one(f.designAxesOffset);
one(f.axisValueCount);
one(f.offsetToAxisValueOffsets);
one(f.elidedFallbackNameID);
offarr(f.designAxes,f.designAxesOffset,f.designAxisCount);
offarr(f.AxisValueOffsets,f.offsetToAxisValueOffsets,f.axisValueCount);
offmany(f.axisValues,f.AxisValueOffsets,f.axisValueCount);
}
USE_ACQRES(STAT)
#endif