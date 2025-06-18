typedef struct {
uint16   version;
uint16   mergeClassCount;
Offset16   mergeDataOffset;
uint16   classDefCount;
Offset16   offsetToClassDefOffsets;
}MergHeader;
typedef struct {
MergeEntryRow*   mergeEntryRows;//[mergeClassCount]
}MergeEntry/* table*/;
ACQRES(MergeEntry/* table*/){
arr(mergeEntryRows, mergeClassCount);
 };
USE_ACQRES(MergeEntry/* table*/)

typedef struct {
uint8*   mergeEntries;//[mergeClassCount]
}MergeEntryRow/* record*/;
ACQRES(MergeEntryRow/* record*/){
arr(mergeEntries, mergeClassCount);
 };
USE_ACQRES(MergeEntryRow/* record*/)

typedef struct {
0x01   MERGE_LTR;
0x02   GROUP_LTR;
0x04   SECOND_IS_SUBORDINATE_LTR;
0x08   Reserved;
0x10   MERGE_RTL;
0x20   GROUP_RTL;
0x40   SECOND_IS_SUBORDINATE_RTL;
0x80   Reserved;
}Merge/* entry flags*/;
