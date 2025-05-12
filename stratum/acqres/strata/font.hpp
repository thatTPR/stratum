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


template <typename T>
void load(T* t , std::fstream* f){
    f->read(reinterpret_cast<char*>(t)) ;
};

// #include <type_traits>
// template <typename T, size_t si>
// void ld(T* s,std::ifstream* fi){
//     if constexpr(std::is_pointer<T>::value){
//         fi->read(reinterpret_cast<char*>(s) , sizeof(s[0])* si)
//     }
//     else {
//         fi->read(reinterpret_cast<char*>(s) , sizeof(s) )
//     }
// };


template <typename T>
inline void ld(T* f, std::ifstream* fi, size_t s){
    ld(&(f[0]),fi,sizeof(f[0])*s);
};
template <typename T>
inline void ld(T* f, std::ifstream* fi){
    fi->read(reinterpret_cas<char*>(f), sizeof(*f));
};

namespace ttf {
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
        Offset32 subtableOffset; // 	Byte offset from beginning of table to the subtable for this encoding.
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
    template <>
    void load<f0>(f0* f, std::ifsteam* fi){
        ld(&(f->length),fi);
        ld(&(f->length),fi);
        ld(&(f->language),fi);
        ld(&(f->glyphIdArray),fi);
    };
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
    template <>
    void load<f2>(f2* f, std::ifstream* fi ){
        ld(&(f->length),fi);
        ld(&(f->language),fi);
        ld(&(f->subHeaderKeys),fi);
        uint16_t km = f->subHeaderKeys[0];
        for(const auto it : f->subHeaderKeys){
            if(it>km){
                km = it; 
            };
        };
        ld(&(f->subHeaders),fi, sizeof(f->subHeaders[0]) *(f->km/8+1 ) ));
        uint32_t s = 0 ;
        for(const auto& it : f->subHeaders){
            s+= it.entryCount;
        };
        ld(f->glyphIdArray,fi,s);
    };
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
    template <>
    void load<f4>(f4* f, std::ifstream* fi){
        uint16_t si = sizeof(f->format);
        ld(&(f->length),fi, ); si+= sizeof(f->length);
        ld(&(f->language),fi, ); si+= sizeof(f->language);
        ld(&(f->segCountX2),fi, ); si+= sizeof(f->segCountX2);
        ld(&(f->searchRange),fi, ); si+= sizeof(f->searchRange);
        ld(&(f->entrySelector),fi, ); si+= sizeof(f->entrySelector);
        ld(&(f->rangeShift),fi, ); si+= sizeof(f->rangeShift);
        uint16_t segCount = f->segCountX2/2;
        ld(&(f->endCode),fi, f->segCountX2); si += sizeof(f->endCode) ;
        ld(&(f->reservedPad),fi); si += sizeof(f->reservedPad) ;
        ld(&(f->startCode), fi,segCount); si+= sizeof(f->startCode) ; 
        ld(&(f->idDelta) fi,segCount); si+= sizeof(f->idDelta) ;
        ld(&(f->idRangeOffset),fi ,segCount); si+= sizeof(f->idRangeOffset)
        uint16_t si_gidarr= length - si ;        
        ld(&(f->glyphIdArray) ,fi, si_gidarr); 

    };
    typedef struct {
    //    Type	Name	Description
    uint16_t format ;//	Format number is set to 6.
    uint16_t length ;//	This is the length in bytes of the subtable.
    uint16_t language ;//	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
    uint16_t firstCode ;//	First character code of subrange.
    uint16_t entryCount ;//	Number of character codes in subrange.
    uint16_t *glyphIdArray;//[entryCount]	Array of glyph index values for character codes in the range.
    }f6 ;
    template <>
    void load<f6>(f4* f, std::ifstream* fi){
        ld(&(f->length),fi, ); 
        ld(&(f->language),fi, ); 
        ld(&(f->firstCode),fi, ); 
        ld(&(f->entryCount),fi, ); 
        ld(&(f->glyphIdArray),fi, f->entryCount); 
    };

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
        uint8_t is32[8192];	//Tightly packed array of bits (8K bytes total) indicating whether the particular 16-bit (index) value is the start of a 32-bit character code
        uint32_t numGroups ;//	Number of groupings which follow
        SequentialMapGroup	*groups;//[numGroups] ;//	Array of SequentialMapGroup records.
    }f8;
    template <>
    void load<f8>(f8* f, std::ifstream* fi){
        ld(&(f->reserved),fi);
        ld(&(f->length),fi);
        ld(&(f->language),fi);
        ld(&(f->is32),fi);
        ld(&(f->numGroups),fi);
        ld(&(f->numGroups),fi,f->numGroups);
    };

    typedef struct {
        uint16_t format  ; //	Subtable format; set to 10.
        uint16_t reserved  ; //	Reserved; set to 0
        uint32_t length  ; //	Byte length of this subtable (including the header)
        uint32_t language  ; //	For requirements on use of the language field, see “Use of the language field in 'cmap' subtables” in this document.
        uint32_t startCharCode  ; //	First character code covered
        uint32_t numChars  ; //	Number of character codes covered
        uint16_t *glyphIdArray;//	Array of glyph indices for the character codes covered
    }f10;
    template <>
    void load<f10>(f10* f, std::ifstream* fi){
        ld(&(f->reserved),fi);
        ld(&(f->length),fi);
        ld(&(f->language),fi);
        ld(&(f->startCharCode),fi);
        ld(&(f->numChars),fi);
        ld(&(f->glyphIdArray),fi,f->numChars);
    };

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
    template <>
    void load<f12>(f12* f, std::ifstream* fi){
        ld(&(f->reserved),fi, );
        ld(&(f->length),fi, );
        ld(&(f->language),fi, );
        ld(&(f->numGroups),fi, );
        ld(&(f->groups),fi, f->numGroups );
    };

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
    template <>
    void load<f13>(f13* f, std::ifstream* fi){
        ld(&(f->reserved),fi ,  );
        ld(&(f->length),fi ,  );
        ld(&(f->language),fi ,  );
        ld(&(f->numGroups),fi ,  );
        ld(&(f->groups),fi, f->numGroups)) ;        
    };

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
    template <>
    void load<f14>(f14* f, std::ifstream* fi){
        ld(&(f->length),fi);
        ld(&(f->numVarSelectorRecords),fi);
        ld(&(f->varSelector),fi , f->numVarSelectorRecords );
    };

    typedef union {
        f0 form0;
        f2 form2;
        f4 form4;
        f6 form6;
        f8 form8;
        f10 form10;
        f12 form12;
        f13 form13;
        f14 from14 ;
    }cmap_format;
    typedef struct{
        uint24_t startUnicodeValue ;//	First value in this range
        uint8_t additionalCount ;//	Number of additional values in this range
    }UnicodeRange;
    typedef struct {
        uint32_t numUnicodeValueRanges ;//	Number of Unicode character ranges.
        UnicodeRange*	ranges;//[numUnicodeValueRanges] ;//	Array of UnicodeRange records.
    }UVS;

    
    typedef struct {
        uint16_t format; 
        cmap_format* cmform; 
    }cmap_ftable;
    typedef struct {
        uint16_t version;
        uint16_t numTables;
        EncodingRecord *encodingRecords;//[numTabes];
        cmap_ftable* ftable ;
    }cmap;
    

    typedef struct {
        uint16_t	version ; ///	Table version number—set to 0.
        uint16_t	numBaseGlyphRecords ; ///	Number of BaseGlyph records.
        Offset32	baseGlyphRecordsOffset ; ///	Offset to baseGlyphRecords array, from beginning of COLR table.
        Offset32	layerRecordsOffset ; ///	Offset to layerRecords array, from beginning of COLR table.
        uint16_t	numLayerRecords ; ///	Number of Layer records.
    }COLR0
    typedef union {

    }COLR; 
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
        uint32_t * EndPtr = Table+((Length+3) & ~3 )/ sizeof(uint32_t) ;
        while(Table < EndPtr){Sum+=*Table++;};
        return Sum;
    };
    typedef union  {
/*avar
BASE
CBDT
CBLC
CFF
CFF2
cmap
COLR
CPAL
cvar
cvt
DSIG
EBDT
EBLC
EBSC
fpgm
fvar
gasp
GDEF
glyf
GPOS
GSUB
gvar
hdmx
head
hhea
hmtx
HVAR
JSTF
kern
loca
LTSH
MATH
maxp
MERG
meta
MVAR
PCLT
post
prep
sbix
STAT
SVG
VDMX
vhea
vmtx
VORG
VVAR*/
        avar _avar;
        BASE _BASE;
        CBDT _CBDT;
        CBLC _CBLC;
        CFF _CFF;
        CFF2 _CFF2;
        cmap _cmap;
        COLR _COLR;
        CPAL _CPAL;
        cvar _cvar;
        cvt _cvt ; 
        head _head;
        hhea _hhea;
        hmtx _hmtx;
        maxp _maxp;
        name _name;
        cvt _cvt;
        fpgm _fpgm;
        glyf _glyf;
        loca _loca;

    }tableu;
    typedef struct {
        TableDirectory td ;
        TableRecord* tr;
        tableu* table;

    }font;
    template <>
    void load<cmap>(cmap* f,std::ifstream* fi ){
        ld(f->version ,fi);
        ld(f->numTables ,fi);
        ld(f->encodingRecords ,fi  ,  f->numTables );
        for(int s = 0 ; s<f->numTables){
            uint16_t format; 
            fi->read(reinterpret_cast<char*>(&format), sizeof(uint16_t))
            switch(format){
                case 0 : { f->form0.format = format; load<f0>(f->form0,fi); continue;};
                case 2 : { f->form2.format = format; load<f2>(f->form2,fi); continue;};
                case 4 : { f->form4.format = format; load<f4>(f->form4,fi); continue;};
                case 6 : { f->form6.format = format; load<f6>(f->form6,fi); continue;};
                case 8 : { f->form8.format = format; load<f8>(f->form8,fi); continue;};
                case 10 :{ f->form10.format = format; load<f10>(f->form10,fi); continue;};
                case 12 :{ f->form12.format = format; load<f12>(f->form12,fi); continue;}; 
                case 13 :{ f->form13.format = format; load<f13>(f->form13,fi); continue;}; 
                case 14 :{ f->from14.format = format; load<f14>(f->form14,fi); continue;}; 
            };
      
        };

    };
    template <>
    void load<COLR>(COLR* f, std::ifstream fi){
        
        fi->read(reinterpret_cast<char*>(),sizeof(f->version));
        switch()
    };
    template<>
    void load<head>(head* h,std::ifstream fi);
    template<>
    void load<hhea>(hhea* h,std::ifstream*  fi);
    template<>
    void load<hmtx>(hmtx* h,std::ifstream*  fi);
    template<>
    void load<maxp>(maxp* h,std::ifstream*  fi);
    template<>
    void load<name>(name* h,std::ifstream*  fi);
    template<>
    void load<cvt>(cvt* h,std::ifstream*  fi);
    template<>
    void load<fpgm>(fpgm* h,std::ifstream*  fi);
    template<>
    void load<glyf>(glyf* h,std::ifstream*  fi);
    template<>
    void load<loca>(loca* h,std::ifstream*  fi);

    glyf getCharGlyf(font* f , char c){
        f->carmap.
        glyf _glyf ; 
        return _glyf;
    };
    glyf wcharGlyf(font* f, wchar_t c){

    };

    consteval uint8_t[4] font_tag(char s[4]){uint8_t i[4]; i[0] = (uint8_t)s[0];i[1] = (uint8_t)s[1];i[2] = (uint8_t)s[2];i[3] = (uint8_t)s[3];return i ;};
    void writeFont(char* path , font* f){

    };
    template <>
    void load<font>( font* f, std::ifstream* fi) {
        
        ld(&(f->td),sizeof(f->td),fi;
        ld(&(f->tr),fi,sizeof(f->tr[0]) * f->td->numtables));
        for(int i = 0 ; i < f->td.numTables;i++){
            switch(f->tr[i].tableTag){
                case font_tag("cmap") : {load<cmap>(f->table[i]._cmap, fi ); continue;}; 
                case font_tag("head") : {load<head>(f->table[i]._head, fi ); continue;};
                case font_tag("hhea") : {load<hhea>(f->table[i]._hhea, fi ); continue;};
                case font_tag("hmtx") : {load<hmtx>(f->table[i]._hmtx, fi ); continue;};
                case font_tag("maxp") : {load<maxp>(f->table[i]._maxp, fi ); continue;};
                case font_tag("name") : {load<name>(f->table[i]._name, fi ); continue;};
                case font_tag("cvt ") : {load<cvt>(f->table[i]._cvt, fi ); continue;};
                case font_tag("fpgm") : {load<fpgm>(f->table[i]._fpgm, fi ); continue;};
                case font_tag("glyf") : {load<glyf>(f->table[i]._glyf, fi ); continue;};
                case font_tag("loca") : {load<loca>(f->table[i]._loca, fi ); continue;};
            };
        };
        

    };

    typedef struct {
        float x,y; 
    }pts;
    typedef struct {
        uint8_t numPts;
        pts* pts ;
    }path;
//  Quadratic Spline
    void textPathLoad(font* f, uint16_t strsize , wchar_t* str , path load    ){// TODO

    }   ; 
};

typedef struct  [
    uint16_t x,y;
    uint16_t** bmp;  
]bitmap;

typedef struct {
    uint16_t textLength ;
    uint16_t* bounds[2] ;
    uint16_t size;
    uint8_t patchno; 
    uint16_t* vertsize;
    float** tripatches; 
}write;

bitmap toBMP(write w){

};
write towrite(char* s){

};


bitamp rasterize(char* str, uint8_t pts, font* f){

};
void loadGlyf(char c , font* f);


void loadTTF(){

};
void writeTTF(){

};
#endif