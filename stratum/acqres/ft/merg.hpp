#ifndef FTMERG_HPP
#define FTMERG_HPP

enum MergeFlags {
MERGE_LTR =0x01,
GROUP_LTR =0x02,
SECOND_IS_SUBORDINATE_LTR =0x04,
Reserved =0x08,
MERGE_RTL =0x10,
GROUP_RTL =0x20,
SECOND_IS_SUBORDINATE_RTL =0x40,
Reserved =0x80
};
typedef struct {
    uint8*   mergeEntries;//[mergeClassCount]
}MergeEntryRow/* record*/;
ACQRES(MergeEntryRow/* record*/){
    arr(f.mergeEntries, _mergeClassCount);
};
USE_ACQRES(MergeEntryRow/* record*/)

typedef struct {
MergeEntryRow*   mergeEntryRows;//[mergeClassCount]
}MergeEntry/* table*/;
ACQRES(MergeEntry/* table*/){
arr(f.mergeEntryRows, _mergeClassCount);
 };
USE_ACQRES(MergeEntry/* table*/)

typedef struct {
uint16   version;
uint16   mergeClassCount;
Offset16   mergeDataOffset;
uint16   classDefCount;
Offset16   offsetToClassDefOffsets;
/// @addindex
MergeEntry mergeData ;
Offset16* classDefsOffsets;
ClassDef* classDefs;
}merg;
ACQRES(merg){
    one(f.version);
    one(f.mergeClassCount);
    one(f.mergeDataOffset);
    one(f.classDefCount);
    one(f.offsetToClassDefOffsets);

    offone(f.mergeData,f.mergeDataOffset);
    offarr(f.classDefsOffsets,f.offsetToClassDefOffsets,f.classDefCount);
    offmany(f.classDefs,f.classDefsOffsets,f.classDefCount);;
    
}
USE_ACQRES(merg)

#endif