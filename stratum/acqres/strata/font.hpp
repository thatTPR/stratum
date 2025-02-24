#ifndef STRATA_FONT_HPP
#define STRATA_FONT_HPP
#include <stdio.h>
typedef uint8_t[4] Tag ;
typedef int16_t FWORD ;
typedef uint16_t UFWORD ;
typedef uint16_t F2DOT14 ;
typedef uint16_t F2DOT14 ;
typedef int64_t F2DOT14 ;


typedef uint8_t Offset8 ;
typedef uint16_t Offset16 ;
typedef uint32_t Offset32 ;
typedef uint24_t Offset24 ;
typedef uint32_t Version16Dot16 ;




typedef struct  [
    uint16_t x,y;
    uint16_t** bmp;  
]bitmap;

typedef struct {

};
namespace ttf [
    //cmap	//Character to glyph mapping
    enum PlatformID {
        Unicode=0,
        Macntosh=1,
        ISO=2,
        Windows=3,
        Custom=4
    };
    // enum UnicodeID{
    //     0	Unicode 1.0 semantics—deprecated
    //     1	Unicode 1.1 semantics—deprecated
    //     2	ISO/IEC 10646 semantics—deprecated
    //     3	Unicode 2.0 and onwards semantics, Unicode BMP only
    //     4	Unicode 2.0 and onwards semantics, Unicode full repertoire
    //     5	Unicode variation sequences—for use with subtable format 14
    //     6	Unicode full repertoire—for use with subtable format 13
    // };
    typedef struct {
        uint16_t platformID;
        uint16_t encodingID;
        Offset32 subtableOffset;
    }EncodingRecord;

    // Formats :
    //0:
    typedef struct {
        // Type	Name	Description
uint16_t format ; //	Format number is set to 0.
uint16_t length ; //	This is the length in bytes of the subtable.
uint16_t language ; //	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
uint8_t glyphIdArray[256]//	An array that maps character codes to glyph index values.
    }f0;
    typedef struct {
        uint16_t firstCode; //	First valid low byte for this SubHeader.
        uint16_t entryCount; //	Number of valid low bytes for this SubHeader.
        int16_t idDelta; 
        uint16_t idRangeOffset; 

    }SubHeader;
    typedef struct {
        uint16_t     format;	//Format number is set to 2.
        uint16_t length	    ; //,This is the length in bytes of the subtable.
        uint16_t language	; //,For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint16_t subHeaderKeys[256];//	Array that maps high bytes into the subHeaders array: value is subHeaders index × 8.
        SubHeader*	subHeaders ;//	Variable-length array of SubHeader records.
        uint16_t* glyphIdArray	;//Variable-length array containing sub-arrays used for mapping the low byte of 2-byte
    }f2;

    typedef struct {
        uint16_t format;//	Format number is set to 4.
        uint16_t length;//	This is the length in bytes of the subtable.
        uint16_t language;//	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint16_t segCountX2;//	2 × segCount.
        uint16_t searchRange;//	Maximum power of 2 less than or equal to segCount, times 2 ((2**floor(log2(segCount))) * 2, where “**” is an exponentiation operator)
        uint16_t entrySelector;//	Log2 of the maximum power of 2 less than or equal to segCount(log2(searchRange/2), which is equal to floor(log2(segCount)))
        uint16_t rangeShift;//	segCount times 2, minus searchRange((segCount * 2) - searchRange)
        uint16_t *endCode ;//[segCountx2];//	End characterCode for each segment, last=0xFFFF.
        uint16_t reservedPad;//	Set to 0.
        uint16_t *startCode; //[segCount];//	Start character code for each segment.
        int16_t *idDelta;//[segCount];//	Delta for all character codes in segment.
        uint16_t *idRangeOffset;//[segCount];//	Offsets into glyphIdArray or 0
        uint16_t *glyphIdArray;//	Glyph index array (arbitrary length)
    }f4;

    typedef struct {
    //    Type	Name	Description
    uint16_t format ;//	Format number is set to 6.
    uint16_t length ;//	This is the length in bytes of the subtable.
    uint16_t language ;//	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
    uint16_t firstCode ;//	First character code of subrange.
    uint16_t entryCount ;//	Number of character codes in subrange.
    uint16_t *glyphIdArray;//[entryCount]	Array of glyph index values for character codes in the range.
    }f6 ;

    typedef struct {
        uint32_t startCharCode ;//	First character code in this group; note that if this group is for one or more 16-bit character codes (which is determined from the is32 array), this 32-bit value will have the high 16-bits set to zero
        uint32_t endCharCode ;//	Last character code in this group; same condition as listed above for the startCharCode
        uint32_t startGlyphID ;//	Glyph index corresponding to the starting character code
    }SequentialMapGroup;
    typedef struct {
        uint16_t format ;//	Subtable format; set to 8.
        uint16_t reserved ;//	Reserved; set to 0
        uint32_t length ;//	Byte length of this subtable (including the header)
        uint32_t language ;//	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint8_t is32[8192];	Tightly packed array of bits (8K bytes total) indicating whether the particular 16-bit (index) value is the start of a 32-bit character code
        uint32_t numGroups ;	Number of groupings which follow
        SequentialMapGroup	*groups;//[numGroups] ;//	Array of SequentialMapGroup records.
    }f8;

    typedef struct {
        uint16_t format  ; //	Subtable format; set to 10.
        uint16_t reserved  ; //	Reserved; set to 0
        uint32_t length  ; //	Byte length of this subtable (including the header)
        uint32_t language  ; //	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint32_t startCharCode  ; //	First character code covered
        uint32_t numChars  ; //	Number of character codes covered
        uint16_t glyphIdArray[];//	Array of glyph indices for the character codes covered
    }f10;

    typedef struct {
        uint32_t startCharCode ; //	First character code in this group
        uint32_t endCharCode ; //	Last character code in this group
        uint32_t startGlyphID ; //	Glyph index corresponding to the starting character code

    }SequentialMapGroup;
    typedef struct {
        uint16_t format ;//	Subtable format; set to 12.
        uint16_t reserved ;//	Reserved; set to 0
        uint32_t length ;//	Byte length of this subtable (including the header)
        uint32_t language ;//	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint32_t numGroups ;//	Number of groupings which follow
        SequentialMapGroup	*groups;//[numGroups]	Array of SequentialMapGroup records.
    }f12;

    typedef struct {
        uint32_t startCharCode ;//	First character code in this group
        uint32_t endCharCode ;//	Last character code in this group
        uint32_t glyphID ;//	Glyph index to be used for all the characters in the group’s
    }ConstantMapGroup;
    typedef struct {
        uint16_t format ;//	Subtable format; set to 13.
        uint16_t reserved ;//	Reserved; set to 0
        uint32_t length ;//	Byte length of this subtable (including the header)
        uint32_t language ;//	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint32_t numGroups ;//	Number of groupings which follow
        ConstantMapGroup	*groups;//[numGroups]	Array of ConstantMapGroup records.
    }f13;

    typedef struct {
        uint24_t varSelector ;//	Variation selector
        Offset32	defaultUVSOffset ;//	Offset from the start of the format 14 subtable to Default UVS table. May be 0.
        Offset32	nonDefaultUVSOffset ;//	Offset from the start of the format 14 subtable to Non-Default UVS table. May be 0.
    }VariationSelector;
    typedef struct {
        uint16_t format; //	Subtable format; set to 14.
        uint32_t length; //	Byte length of this subtable (including this header)
        uint32_t numVarSelectorRecords; //	Number of variation Selector Records
        VariationSelector	*varSelector;//[numVarSelectorRecords]	Array of VariationSelector records.
    }f14;

    typedef union {
        f form;
        f2 form2;
        f4 form4;
        f6 form6;
        f8 form8;
        f10 form10;
        f12 form12;
        f13 form14;
    };
    typedef struct{
        uint24_t startUnicodeValue ;//	First value in this range
        uint8_t additionalCount ;//	Number of additional values in this range
    }UnicodeRange;
    typedef struct {
        uint32_t numUnicodeValueRanges ;//	Number of Unicode character ranges.
        UnicodeRange*	ranges;//[numUnicodeValueRanges] ;//	Array of UnicodeRange records.
    }UVS;

    typedef struct {
        uint16_t verson;
        uint16_t numTables;
        EncodingRecord *encodingRecords;//[numTabes];
    }cmap;


    //head	//Font header
    typedef struct {
        uint16_t majorVersion ;//	Major version number of the font header table — set to 1.
        uint16_t minorVersion ;//	Minor version number of the font header table — set to 0.
        Fixed	fontRevision ;//	Set by font manufacturer.
        uint32_t checksumAdjustment ;//	To compute: set it to 0, sum the entire font as uint32, then store 0xB1B0AFBA - sum. If the font is used as a component in a font collection file, the value of this field will be invalidated by changes to the file structure and font table directory, and must be ignored.
        uint32_t magicNumber ;//	Set to 0x5F0F3CF5.
        uint16_t flags ; /*	Bit 0: Baseline for font at y=0.

Bit 1: Left sidebearing point at x=0 (relevant only for TrueType rasterizers) — see additional information below regarding variable fonts.

Bit 2: Instructions may depend on point size.

Bit 3: Force ppem to integer values for all internal scaler math; may use fractional ppem sizes if this bit is clear. It is strongly recommended that this be set in hinted fonts.

Bit 4: Instructions may alter advance width (the advance widths might not scale linearly).

Bit 5: This bit is not used in OpenType, and should not be set in order to ensure compatible behavior on all platforms. If set, it may result in different behavior for vertical layout in some platforms. (See Apple’s specification for details regarding behavior in Apple platforms.)

Bits 6 – 10: These bits are not used in OpenType and should always be cleared. (See Apple’s specification for details regarding legacy use in Apple platforms.)

Bit 11: Font data is “lossless” as a result of having been subjected to optimizing transformation and/or compression (such as compression mechanisms defined by ISO/IEC 14496-18, MicroType® Express, WOFF 2.0, or similar) where the original font functionality and features are retained but the binary compatibility between input and output font files is not guaranteed. As a result of the applied transform, the DSIG table may also be invalidated.

Bit 12: Font converted (produce compatible metrics).

Bit 13: Font optimized for ClearType®. Note, fonts that rely on embedded bitmaps (EBDT) for rendering should not be considered optimized for ClearType, and therefore should keep this bit cleared.

Bit 14: Last Resort font. If set, indicates that the glyphs encoded in the 'cmap' subtables are simply generic symbolic representations of code point ranges and do not truly represent support for those code points. If unset, indicates that the glyphs encoded in the 'cmap' subtables represent proper support for those code points.

Bit 15: Reserved, set to 0. */
    uint16_t unitsPerEm ;//	Set to a value from 16 to 16384. Any value in this range is valid. In fonts that have TrueType outlines, a power of 2 is recommended as this allows performance optimization in some rasterizers.
    LONGDATETIME	created ;//	Number of seconds since 12:00 midnight that started January 1st, 1904, in GMT/UTC time zone.
    LONGDATETIME	modified ;//	Number of seconds since 12:00 midnight that started January 1st, 1904, in GMT/UTC time zone.
    int16_t xMin ;//	Minimum x coordinate across all glyph bounding boxes.
    int16_t yMin ;//	Minimum y coordinate across all glyph bounding boxes.
    int16_t xMax ;//	Maximum x coordinate across all glyph bounding boxes.
    int16_t yMax ;//	Maximum y coordinate across all glyph bounding boxes.
    uint16_t macStyle ;/*	Bit 0: Bold (if set to 1);
Bit 1: Italic (if set to 1)
Bit 2: Underline (if set to 1)
Bit 3: Outline (if set to 1)
Bit 4: Shadow (if set to 1)
Bit 5: Condensed (if set to 1)
Bit 6: Extended (if set to 1)
Bits 7 – 15: Reserved (set to 0). */
    uint16_t lowestRecPPEM ;//	Smallest readable size in pixels.
    int16_t fontDirectionHint ;/* a	Deprecated (Set to 2).
0: Fully mixed directional glyphs;
1: Only strongly left to right;
2: Like 1 but also contains neutrals;
-1: Only strongly right to left;
-2: Like -1 but also contains neutrals.*/
int16_t indexToLocFormat	 ; // 0 for short offsets (Offset16), 1 for long (Offset32).
int16_t glyphDataFormat	 ; // 0 for current format.
    }head;
    //hhea	//Horizontal header
    typedef struct {
        // Type	Name	Description
        uint16_t majorVersion;//	Major version number of the horizontal header table — set to 1.
        uint16_t minorVersion;//	Minor version number of the horizontal header table — set to 0.
        FWORD	ascender;//	Typographic ascent—see remarks below.
        FWORD	descender;//	Typographic descent—see remarks below.
        FWORD	lineGap;//	Typographic line gap.
        Negative lineGap;// values are treated as zero in some legacy platform implementations.
        UFWORD	advanceWidthMax;//	Maximum advance width value in 'hmtx' table.
        FWORD	minLeftSideBearing;//	Minimum left sidebearing value in 'hmtx' table for glyphs with contours (empty glyphs should be ignored).
        FWORD	minRightSideBearing;//	Minimum right sidebearing value; calculated as min(aw - (lsb + xMax - xMin)) for glyphs with contours (empty glyphs should be ignored).
        FWORD	xMaxExtent;//	Max(lsb + (xMax - xMin)).
        int16_t caretSlopeRise;//	Used to calculate the slope of the cursor (rise/run); 1 for vertical.
        int16_t caretSlopeRun;//	0 for vertical.
        int16_t caretOffset;//	The amount by which a slanted highlight on a glyph needs to be shifted to produce the best appearance. Set to 0 for non-slanted fonts
        int16_t reserved0;//	set to 0
        int16_t reserved1;//	set to 0
        int16_t reserved2;//	set to 0
        int16_t reserved3;//	set to 0
        int16_t metricDataFormat ;//	0 for current format.
        uint16_t numberOfHMetrics ;//	Number of hMetric entries in 'hmtx' table
    }hhea;
    //hmtx	//Horizontal metrics
    typedef struct {
        UFWORD	advanceWidth ;//	Advance width, in font design units.
        FWORD	lsb ;//	Glyph left side bearing, in font design units.
    }LongHorMetric;
    typedef struct {
        LongHorMetric	*hMetrics;//[numberOfHMetrics]	;//Paired advance width and left side bearing values for each glyph. Records are indexed by glyph ID.
        FWORD	*leftSideBearings;//[numGlyphs - numberOfHMetrics] ;//	Left side bearings for glyph IDs greater than or equal to numberOfHMetrics.
    }hmtx;
    //maxp	//Maximum profile
    typedef struct {
        Version16Dot16	version ;//	0x00010000 for version 1.0.
        uint16_t numGlyphs ;//	The number of glyphs in the font.
        uint16_t maxPoints ;//	Maximum points in a non-composite glyph.
        uint16_t maxContours ;//	Maximum contours in a non-composite glyph.
        uint16_t maxCompositePoints ;//	Maximum points in a composite glyph.
        uint16_t maxCompositeContours ;//	Maximum contours in a composite glyph.
        uint16_t maxZones ;//	1 if instructions do not use the twilight zone (Z0), or 2 if instructions do use Z0; should be set to 2 in most cases.
        uint16_t maxTwilightPoints ;//	Maximum points used in Z0.
        uint16_t maxStorage ;//	Number of Storage Area locations.
        uint16_t maxFunctionDefs ;//	Number of FDEFs, equal to the highest function number + 1.
        uint16_t maxInstructionDefs ;//	Number of IDEFs.
        uint16_t maxStackElements ;//	Maximum stack depth across Font Program ('fpgm' table), CVT Program ('prep' table) and all glyph instructions (in the 'glyf' table).
        uint16_t maxSizeOfInstructions ;//	Maximum byte count for glyph instructions.
        uint16_t maxComponentElements ;//	Maximum number of components referenced at “top level” for any composite glyph.
        uint16_t maxComponentDepth ;//	Maximum levels of recursion; 1 for simple components.
    }maxp;
    //name	//Naming table
    typedef struct {
        uint16_t platformID ;//	Platform ID.
        uint16_t encodingID ;//	Platform-specific encoding ID.
        uint16_t languageID ;//	Language ID.
        uint16_t nameID ;//	Name ID.
        uint16_t length ;//	String length (in bytes).
        Offset16	stringOffset ;//	String offset from start of storage area (in bytes).
    }NameRocord
    typedef struct {
        uint16_t version ;//	Table version number (=1).
        uint16_t count	; //Number of name records.
        Offset16	storageOffset ;//	Offset to start of string storage (from start of table).
        NameRecord	*nameRecord;//[count] ;//	The name records where count is the number of records.
        char* Variable ;//		Storage for the actual string data.
    }name0;
    typedef struct {
        uint16_t version ;//	Table version number (=1).
        uint16_t count	; //Number of name records.
        Offset16	storageOffset ;//	Offset to start of string storage (from start of table).
        NameRecord	*nameRecord;//[count] ;//	The name records where count is the number of records.
        uint16_t langTagCount;//	Number of language-tag records.
        LangTagRecord	*langTagRecord;//[langTagCount];//	The language-tag records where langTagCount is the number of records.
        char* Variable ;//		Storage for the actual string data.
    }name;
    //OS2	//OS/2 and Windows specific metrics
    typedef struct {
        char none;
    }OS2;
    //post	//PostScript information
    typedef struct {
        char none
    }post;
    
    typedef FOWRD cvt;
    typedef uint8_t* fpgm ;


    // glyf
    typedef struct {
        int16_t numberOfContours ;//  	If the number of contours is greater than or equal to zero, this is a simple glyph. If negative, this is a composite glyph — the value -1 should be used for composite glyphs.
        int16_t xMin ;//  	Minimum x for coordinate data.
        int16_t yMin ;//  	Minimum y for coordinate data.
        int16_t xMax ;//  	Maximum x for coordinate data.
        int16_t yMax ;//  	Maximum y for coordinate data.
        uint16	*endPtsOfContours;//[numberOfContours]	Array of point indices for the last point of each contour, in increasing numeric order.
        uint16	instructionLength;//	Total number of bytes for instructions. If instructionLength is zero, no instructions are present for this glyph, and this field is followed directly by the flags field.
        uint8	*instructions;//[instructionLength]	Array of instruction byte code for the glyph.
        uint8	*flags;//[variable]	Array of flag elements. See below for details regarding the number of flag array elements.
        uint8 	*xCoordinates;//[variable]	Contour point x-coordinates. See below for details regarding the number of coordinate array elements. Coordinate for the first point is relative to (0,0); others are relative to previous point.
        uint8 	*yCoordinates;//[variable]	Contour point y-coordinates. See below for details regarding the number of coordinate array elements. Coordinate for the first point is relative to (0,0); others are relative to previous point.
    }glyf;
    typedef struct {
        Offset16 *offset ; // [numGlyphs+1] ;
    }loca; 
    typedef uint8_t* prep ; // Set of instructions executed whenever point size or font or transformation change. n is the number of uint8 items that fit in the size of the table.


    

    typedef struct {
        Tag tableTag;
        uint32_t checksum ;
        Offset32 offset; 
        uint32_t length;
    }TableRecord;
    typedef struct {
        uint32_t	sfntVersion;//	0x00010000 or 0x4F54544F ('OTTO') — see below.
        uint16_t	numTables;//	Number of tables.
        uint16_t	searchRange;//	Maximum power of 2 less than or equal to numTables, times 16 ((2**floor(log2(numTables))) * 16, where “**” is an exponentiation operator).
        uint16_t	entrySelector;//	Log2 of the maximum power of 2 less than or equal to numTables (log2(searchRange/16), which is equal to floor(log2(numTables))).
        uint16_t	rangeShift;//	numTables times 16, minus searchRange ((numTables * 16) - searchRange).
        //TableRecord	*tableRecords;//[numTables]	Table records array—one for each top-level table in the font.
    }TableDirectory
    uint32_t CalcTableChecksum(uint32 *Table, uint32 Length){
        uint32_t  Sum = 0L;
        uint32_t * EndPtr = Table+((Lenfth+3) & ~3 )/ sizeof(uint32_t) ;
        while(Table < EndPtr){Sum+=*Table++;};
        return Sum;
    };

    typedef struct {
        TableDirectory td ;
        TableRecord* s;
        uint16_t num_cmap;
        cmap* carmap;
        uint16_t num_head;
        head* fontheader;
        uint16_t num_hhea;
        hhea* horiheader;
        uint16_t num_hmtx;
        hmtx* horimet;
        uint16_t num_maxp;
        maxp* maxiprof;
        uint16_t num_name;
        name* naming;

        uint16_t num_cvt;
        cvt* controlValTable;
        uint16_t num_fpgm;
        fpgm* fontprogram;
        uint16_t num_glyf;
        glyf* glyph;
        uint16_t num_loca;
        loca* locind;

    }font;

    void load_cmap(font* f, TableRecord tr);
    void load_head(font* f, TableRecord tr);
    void load_hhea(font* f, TableRecord tr);
    void load_hmtx(font* f, TableRecord tr);
    void load_maxp(font* f, TableRecord tr);
    void load_name(font* f, TableRecord tr);
    void load_cvt(font* f, TableRecord tr);
    void load_fpgm(font* f, TableRecord tr);
    void load_glyf(font* f, TableRecord tr);
    void load_loca(font* f, TableRecord tr);

    glyf getCharGlyf(font* f , char c){
        f->carmap.
        glyf _glyf ; 
        return _glyf;
    };
    glyf wcharGlyf(font* f, wchar_t c){

    };

    constexpr uint16_t font_tag(char s[4]){return (s[0]<<24|s[1]<<16|s[2]<<8|s[3]);};
    void writeFont(char* path , font* f){

    };
    void loadFont(char* path , font* f) {
        std::ifstream in(std::string(path)) ;
        in.read(reinterpret_cast<char*>(f->td);

        

    };
];



bitamp rasterize(char* str, uint8_t pts, font* f){

};
void loadGlyf(char c , font* f);


void loadTTF(){

};
void writeTTF(){

};
#endif