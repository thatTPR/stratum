typedef struct {
uint16   version;
uint16   flags;
uint32   numStrikes;
Offset32*   strikeOffsets;//[numStrikes]
}sbixHeader;
ACQRES(sbixHeader){
one(version);
one(flags);
one(numStrikes);
arr(strikeOffsets, numStrikes);
 };
USE_ACQRES(sbixHeader)

