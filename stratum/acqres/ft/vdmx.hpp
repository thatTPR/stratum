typedef struct {
uint16   version;
uint16   numRecs;
uint16   numRatios;
RatioRange*   ratRange;//[numRatios]
Offset16*   vdmxGroupOffsets;//[numRatios]
}VdmxHeader;
ACQRES(VdmxHeader){
one(version);
one(numRecs);
one(numRatios);
arr(ratRange, numRatios);
 arr(vdmxGroupOffsets, numRatios);
 };
USE_ACQRES(VdmxHeader)

typedef struct {
uint8   bCharSet;
uint8   xRatio;
uint8   yStartRatio;
uint8   yEndRatio;
}RatioRange/* record*/;
typedef struct {
0   No subset; the VDMX group applies to all glyphs in the font. This is used for symbol or dingbat fonts.;
1   Windows ANSI subset; the VDMX group was computed using only the glyphs required to complete the Windows ANSI character set. Windows will ignore any VDMX entries that are not for the ANSI subset (i.e. ANSI_CHARSET).;
}Character/* Set Values, Version 0*/;
typedef struct {
0   No subset; the VDMX group applies to all glyphs in the font. If adding new character sets to existing font, add this flag and the groups necessary to support it. This should only be used in conjunction with ANSI_CHARSET.;
1   No subset; the VDMX group applies to all glyphs in the font. Used when creating a new font for Windows. No need to support SYMBOL_CHARSET.;
}Character/* Set Values, Version 1*/;
typedef struct {
uint16   recs;
uint8   startsz;
uint8   endsz;
vTable*   entry;//[recs]
}VDMXGroup/* table*/;
ACQRES(VDMXGroup/* table*/){
one(recs);
one(startsz);
one(endsz);
arr(entry, recs);
 };
USE_ACQRES(VDMXGroup/* table*/)

typedef struct {
uint16   yPelHeight;
int16   yMax;
int16   yMin;
}vTable/* record*/;
