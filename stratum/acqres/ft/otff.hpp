typedef struct {
uint32   sfntVersion;
uint16   numTables;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
TableRecord*   tableRecords;//[numTables]
}TableDirectory:;
ACQRES(TableDirectory:){
one(sfntVersion);
one(numTables);
one(searchRange);
one(entrySelector);
one(rangeShift);
arr(tableRecords, numTables);
 };
USE_ACQRES(TableDirectory:)

typedef struct {
Tag   tableTag;
uint32   checksum;
Offset32   offset;
uint32   length;
}TableRecord:;
typedef struct {
Tag   ttcTag;
uint16   majorVersion;
uint16   minorVersion;
uint32   numFonts;
Offset32*   tableDirectoryOffsets;//[numFonts]
}TTCHeader/* Version 1.0:*/;
ACQRES(TTCHeader/* Version 1.0:*/){
one(ttcTag);
one(majorVersion);
one(minorVersion);
one(numFonts);
arr(tableDirectoryOffsets, numFonts);
 };
USE_ACQRES(TTCHeader/* Version 1.0:*/)

typedef struct {
Tag   ttcTag;
uint16   majorVersion;
uint16   minorVersion;
uint32   numFonts;
Offset32*   tableDirectoryOffsets;//[numFonts]
uint32   dsigTag;
uint32   dsigLength;
uint32   dsigOffset;
}TTCHeader/* Version 2.0:*/;
ACQRES(TTCHeader/* Version 2.0:*/){
one(ttcTag);
one(majorVersion);
one(minorVersion);
one(numFonts);
arr(tableDirectoryOffsets, numFonts);
 one(dsigTag);
one(dsigLength);
one(dsigOffset);
};
USE_ACQRES(TTCHeader/* Version 2.0:*/)

