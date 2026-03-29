#ifndef FTFVAR_HPP
#define FTFVAR_HPP
enum VarAxisFlags {
HIDDEN_AXIS=0x0001,//		The axis should not be exposed directly in user interfaces.
Reserved=0xFFFE//		Reserved for future use — set to 0.
};
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
arr(f.coordinates, f.axisCount);
 };
USE_ACQRES(UserTuple/* record:*/)

typedef struct {
uint16   subfamilyNameID;
uint16   flags;
UserTuple   coordinates;
uint16   postScriptNameID;
}InstanceRecord:;

typedef struct { // Header
uint16   majorVersion;
uint16   minorVersion;
Offset16   axesArrayOffset;
uint16   reserved;
uint16   axisCount;
uint16   axisSize;
uint16   instanceCount;
uint16   instanceSize;
//
VariationAxisRecord*	axes;//[axisCount]	The variation axis array.
InstanceRecord*	instances;//[instanceCount]	The named instance array.
}fvar;
ACQRES(fvar){
    one((f.majorVersion));
    one((f.minorVersion));
    one((f.axesArrayOffset));
    one((f.reserved));
    one((f.axisCount));
    one((f.axisSize));
    one((f.instanceCount));
    one((f.instanceSize)); 
    offarr((f.axes),f.axesArrayOffset,f.axisCount);  
    arr(f.instances,f.axisCount);
}
USE_ACQRES(fvar)

#endif