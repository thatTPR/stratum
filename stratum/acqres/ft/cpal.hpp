typedef struct {
uint16   version;
uint16   numPaletteEntries;
uint16   numPalettes;
uint16   numColorRecords;
Offset32   colorRecordsArrayOffset;
uint16*   colorRecordIndices;//[numPalettes]
}CPAL/* version 0*/;
ACQRES(CPAL/* version 0*/){
one(version);
one(numPaletteEntries);
one(numPalettes);
one(numColorRecords);
one(colorRecordsArrayOffset);
arr(colorRecordIndices, numPalettes);
 };
USE_ACQRES(CPAL/* version 0*/)

typedef struct {
uint16   version;
uint16   numPaletteEntries;
uint16   numPalettes;
uint16   numColorRecords;
Offset32   colorRecordsArrayOffset;
uint16*   colorRecordIndices;//[numPalettes]
Offset32   paletteTypesArrayOffset;
Offset32   paletteLabelsArrayOffset;
Offset32   paletteEntryLabelsArrayOffset;
}CPAL/* version1*/;
ACQRES(CPAL/* version1*/){
one(version);
one(numPaletteEntries);
one(numPalettes);
one(numColorRecords);
one(colorRecordsArrayOffset);
arr(colorRecordIndices, numPalettes);
 one(paletteTypesArrayOffset);
one(paletteLabelsArrayOffset);
one(paletteEntryLabelsArrayOffset);
};
USE_ACQRES(CPAL/* version1*/)

typedef struct {
uint8   blue;
uint8   green;
uint8   red;
uint8   alpha;
}ColorRecord;
