#ifndef FTVDMX_HPP
#define FTVDMX_HPP
typedef struct {
    uint16	yPelHeight ;//	yPelHeight to which values apply.
    int16	yMax ;//	Maximum value (in pels) for this yPelHeight.
    int16	yMin ;//	Minimum value (in pels) for this yPelHeight.
}vTable;
typedef struct {
uint8   bCharSet;
uint8   xRatio;
uint8   yStartRatio;
uint8   yEndRatio;
}RatioRange;
enum CharSetValues0 {
No_subset=0,//   ; the VDMX group applies to all glyphs in the font. This is used for symbol or dingbat fonts.;
Windows_ANSI_subset=1//   ; the VDMX group was computed using only the glyphs required to complete the Windows ANSI character set. Windows will ignore any VDMX entries that are not for the ANSI subset (i.e. ANSI_CHARSET).;
};
enum CharSetValues1 {
No_subset=0,   ; the VDMX group applies to all glyphs in the font. If adding new character sets to existing font, add this flag and the groups necessary to support it. This should only be used in conjunction with ANSI_CHARSET.;
No_subset1=1   ; the VDMX group applies to all glyphs in the font. Used when creating a new font for Windows. No need to support SYMBOL_CHARSET.;
};
typedef struct {
uint16   recs;
uint8   startsz;
uint8   endsz;
vTable*   entry;//[recs]
}VDMXGroup;
ACQRES(VDMXGroup/* table*/){
one(f.recs);
one(f.startsz);
one(f.endsz);
arr(f.entry, f.recs);
 };
USE_ACQRES(VDMXGroup/* table*/)

typedef struct {
uint16   yPelHeight;
int16   yMax;
int16   yMin;
}vTable;

typedef struct {
uint16   version;
uint16   numRecs;
uint16   numRatios;
RatioRange*   ratRange;//[numRatios]
Offset16*   vdmxGroupOffsets;//[numRatios]

VDMXGroup* vdmxGroups;
}VDMX;
ACQRES(VDMX){
one((f.version));
one((f.numRecs));
one((f.numRatios));
arr(f.ratRange, f.numRatios);
 arr(f.vdmxGroupOffsets, f.numRatios);
 
 offmany(f.vdmxGroups,f.vdmxGroupOffsets,f.numRatios);
 
 };
USE_ACQRES(VDMX)
#endif