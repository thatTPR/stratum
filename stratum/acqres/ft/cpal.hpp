#ifndef FTCPAL_HPP
#define FTCPAL_HPP
struct ColorRecord{
uint8   blue;
uint8   green;
uint8   red;
uint8   alpha;
    glm::uvec4 get(){return glm::uvec4(red,green,blue,alpha);}
    ColorRecord(glm::uvec4& g) : blue(g.r),green(g.g), red(g.r),alpha(g.a) {};   
};
enum PaletteFlags{
	USABLE_WITH_LIGHT_BACKGROUND=0x0001,//	Bit 0: palette is appropriate to use when displaying the font on a light background such as white.
	USABLE_WITH_DARK_BACKGROUND=0x0002,//	Bit 1: palette is appropriate to use when displaying the font on a dark background such as black.
	Reserved=0xFFFC//	Reserved for future use — set to 0.
}
typedef struct {
// uint16   version;
uint16   numPaletteEntries;
uint16   numPalettes;
uint16   numColorRecords;
Offset32   colorRecordsArrayOffset;
uint16*   colorRecordIndices;//[numPalettes]
//
ColorRecord* colorRecords // [numColorRecords]
}CPAL0;
ACQRES(CPAL0){
one(f.version);
one(f.numPaletteEntries);
one(f.numPalettes);
one(f.numColorRecords);
one(f.colorRecordsArrayOffset);
arr(f.colorRecordIndices, f.numPalettes);
offarr(f.colorRecords,f.colorRecordsArrayOffset,f.numColorRecords)
};
USE_ACQRES(CPAL0)

typedef struct {
// uint16   version;
uint16   numPaletteEntries;
uint16   numPalettes;
uint16   numColorRecords;
Offset32   colorRecordsArrayOffset;
uint16*   colorRecordIndices;//[numPalettes]
Offset32   paletteTypesArrayOffset;
Offset32   paletteLabelsArrayOffset;
Offset32   paletteEntryLabelsArrayOffset;//
/// 
ColorRecord* colorRecords; // [numColorRecords]
uint32*	paletteTypes;//[numPalettes];
uint16* paletteLabels;//[numPalettes];
uint16*	paletteEntryLabels;//[numPaletteEntries]	
    
}CPAL1;
ACQRES(CPAL1){
one(f.version);
one(f.numPaletteEntries);
one(f.numPalettes);
one(f.numColorRecords);
one(f.colorRecordsArrayOffset);
arr(f.colorRecordIndices, f.numPalettes);
 one(f.paletteTypesArrayOffset);
one(f.paletteLabelsArrayOffset);
one(f.paletteEntryLabelsArrayOffset);
offarr(f.colorRecords,f.colorRecordsArrayOffset,f.numColorRecords);
offarr(f.paletteTypes,f.paletteTypesArrayOffset,f.numPalettes);
offarr(f.paletteLabel,f.paletteLabelsArrayOffset,f.numPalettes);
offarr(f.paletteEntryLabels,f.paletteEntryLabelsArrayOffset,f.numPaletteEntries);
};
USE_ACQRES(CPAL1)

typedef struct {
    uint16 version;
    union {
        CPAL0 f0;
        CPAL1 f1;
    }c;
    ColorRecord get(uint16 palI ){
        switch(f.version){
        case 0 : {return c.f0.colorRecords[palI];);};
        case 1 : {return c.f1.colorRecords[palI];};
    }
        
    };
}CPAL;
ACQRES(CPAL){
    one(f.version);
    switch(f.version){
        case 0 : {one(F.c.f0);};
        case 1 : {one(F.c.f1);};
    }
}
USE_ACQRES(CPAL)

#endif