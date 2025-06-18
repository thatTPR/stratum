typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   axesArrayOffset;
uint16   (reserved);
uint16   axisCount;
uint16   axisSize;
uint16   instanceCount;
uint16   instanceSize;
}Font/* variations header:*/;
typedef struct {
Tag   axisTag;
Fixed   minValue;
Fixed   defaultValue;
Fixed   maxValue;
uint16   flags;
uint16   axisNameID;
}VariationAxisRecord;
typedef struct {
Fixed*   coordinates;//[axisCount]
}UserTuple/* record:*/;
ACQRES(UserTuple/* record:*/){
arr(coordinates, axisCount);
 };
USE_ACQRES(UserTuple/* record:*/)

typedef struct {
uint16   subfamilyNameID;
uint16   flags;
UserTuple   coordinates;
uint16   postScriptNameID;
}InstanceRecord:;
