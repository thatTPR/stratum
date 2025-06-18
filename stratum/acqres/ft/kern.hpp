typedef struct {
uint16   version;
uint16   nTables;
}KernHeader;
typedef struct {
uint16   nPairs;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
KernPair*   kernPairs;//[nPairs]
}KernSubtableFormat0;
ACQRES(KernSubtableFormat0){
one(nPairs);
one(searchRange);
one(entrySelector);
one(rangeShift);
arr(kernPairs, nPairs);
 };
USE_ACQRES(KernSubtableFormat0)

typedef struct {
uint16   left;
uint16   right;
FWORD   value;
}KernPair/* record*/;
typedef struct {
uint16   rowWidth;
Offset16   leftClassOffset;
Offset16   rightClassOffset;
Offset16   kerningArrayOffset;
}KernSubtableFormat2;
