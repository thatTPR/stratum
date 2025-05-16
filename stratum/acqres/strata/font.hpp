#ifndef STRATA_FONT_HPP
#define STRATA_FONT_HPP
#include <stratum/acqres/acqres.hpp>




namespace ttf {
    typedef signed long Fixed; 
    typedef uint32_t Tag
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
    
    typedef int16_t int16 ;
    typedef uint16_t uint16 ;
    typedef uint16_t uint16 ;
    typedef uint16_t uint16 ;
    typedef int64_t int64 ;
    
    
    typedef uint8_t uint8 ;
    typedef uint16_t uint16 ;
    typedef uint32_t uint32 ;
    typedef uint24_t uint24 ;
    typedef uint32_t uint32 ;
    
    Tag font_tag(char s[4]){Tag i; i[0] = (uint8_t)s[0];i[1] = (uint8_t)s[1];i[2] = (uint8_t)s[2];i[3] = (uint8_t)s[3];return i ;};
    char[4] font_tag(Tag s){char i[4] ; i[0] = (char)s[0];i[1] = (char)s[1];i[2] = (char)s[2];i[3] = (char)s[3];return i ; };
    // avar
    typedef struct { //AxisValueMap 
        F2DOT14	fromCoordinate	;A normalized coordinate value obtained using default normalization.
        F2DOT14	toCoordinate	;The modified, normalized coordinate value.
    }AxisValueMap
    typedef struct {//SegmentMaps 
    uint16	positionMapCount;//	The number of correspondence pairs for this axis.
    AxisValueMap	*axisValueMaps;//[positionMapCount]	The array of axis value map records for this axis.
    //Each axis value map record provides a single axis-value mapping correspondence.
    }SegmentMap;
    ACQRES(SegmentMap) {
        one(&(f->positionMapCount));
        arr((f->axisValueMaps),f->positionMapCount);
        
    };
    USE_ACQRES(SegmentMap) 
    typedef struct { //Axis variation 
        uint16	majorVersion ; //	Major version number of the axis variations table — set to 1.
        uint16	minorVersion ; //	Minor version number of the axis variations table — set to 0.
        uint16	reserved ; //)	Permanently reserved; set to 0.
        uint16	axisCount ; //	The number of variation axes for this font. This must be the same number as axisCount in the 'fvar' table.
        SegmentMap	*axisSegmentMaps ; //[axisCount]	The segment maps array — one segment map for each axis, in the order of axes specified in the 'fvar' table.
        //There must be one segment map for each axis defined in the 'fvar' table, and the segment maps for the different axes must be given in the order of axes specified in the 'fvar' table. The segment map for each axis is comprised of a list of axis-value mapping records.
    }avar ;

    ACQRES(avar){
        one(&(f->majorVersion));
        one(&(f->minorVersion));
        one(&(f->reserved));
        one(&(f->axisCount));
        arr((f->axisSegmentMaps),f->axisCount);
    };
    USE_ACQRES(avar)
    /* 
    Base
    */
typedef struct {//FeatMinMax record
    Tag	featureTag ;//	4-byte feature identification tag — must match feature tag in FeatureList.
    Offset16	minCoordOffset ;//	Offset to BaseCoord table that defines the minimum extent value, from beginning of MinMax table (may be NULL).
    Offset16	maxCoordOffset ;//	Offset to BaseCoord table that defines the maximum extent value, from beginning of MinMax table (may be NULL).
}FeatMinMax;
typedef struct {//MinMax table
    Offset16	minCoordOffset;//	Offset to BaseCoord table that defines the minimum extent value, from the beginning of MinMax table (may be NULL).
    Offset16	maxCoordOffset;//	Offset to BaseCoord table that defines maximum extent value, from the beginning of MinMax table (may be NULL).
    uint16	featMinMaxCount;//	Number of FeatMinMaxRecords — may be zero (0).
    FeatMinMax*	featMinMaxRecords;//[featMinMaxCount]	Array of FeatMinMax records, in alphabetical order by featureTag.
}MinMax;`
ACQRES(MinMax) {    one(&(f->minCoordOffset);
    one(&(f->maxCoordOffset));
    one(&(f->featMinMaxCount));
    arr((f->featMinMaxRecords),f->featMinMaxCount);
};
USE_ACQRES(MinMax) 

typedef struct {//BaseLangSys record
    Tag	baseLangSysTag;//	4-byte language system identification tag.
    Offset16	minMaxOffset;//	Offset to MinMax table, from beginning of BaseScript table.
}BaseLangSys;

typedef struct {
    uint16	format ;//	Format identifier — format = 1.
    int16	coordinate ;//	X or Y value, in design units.
    }BaseCoordf1;
    
    typedef struct {
    uint16	format;//	Format identifier — format = 2.
    int16	coordinate;//	X or Y value, in design units.
    uint16	referenceGlyph;//	Glyph ID of control glyph.
    uint16	baseCoordPoint;//	Index of contour point on the reference glyph.}BaseCoordf2;
    }BaseCoordf2;
    typedef struct {
    uint16	format ;//	Format identifier — format = 3.
    int16	coordinate ;//	X or Y value, in design units.
    Offset16	deviceOffset ;//	Offset to Device table (non-variable font) / Variation Index table (variable font) for X or Y value, from beginning of BaseCoord table (may be NULL).
    }BaseCoordf3;
    
    typedef union  {
        BaseCoordf1 f1;
        BaseCoordf2 f2;
        BaseCoordf3 f3;
    }BaseCoordFormat;
    ACQRES(BaseCoordFormat) {
        one(f->f1);
        switch(f->f1.format){
            case 2 : {
                one(&(f->f2.referenceGlypth));
                one(&(f->f2.baseCoordPoint));
            };
            case 3 : {
                one(&(f->f2.deviceOffset),fi);
            };
        } ;
    };
    USE_ACQRES(BaseCoordFormat)
    
typedef struct {//BaseValues table
    uint16	defaultBaselineIndex;//	Index number of default baseline for this script — equals index position of baseline tag in baselineTags array of the BaseTagList.
    uint16	baseCoordCount;//	Number of BaseCoord tables defined — should equal baseTagCount in the BaseTagList.
    Offset16	*baseCoordOffsets;//[baseCoordCount]	Array of offsets to BaseCoord tables, from beginning of BaseValues table — order matches baselineTags array in the BaseTagList.
}BaseValues;
 ACQRES(BaseValues) {    
    one(&(f->defaultBaselineIndex));
    one(&(f->baseCoordCount));
    arr((f->baseCoordOffsets),f->baseCoordCount);
};
USE_ACQRES(BaseValues) 

typedef struct {
    Offset16	baseValuesOffset ;//	Offset to BaseValues table, from beginning of BaseScript table (may be NULL).
    Offset16	defaultMinMaxOffset ;//	Offset to MinMax table, from beginning of BaseScript table (may be NULL).
    uint16	baseLangSysCount ;//	Number of BaseLangSys records defined — may be zero (0).
    BaseLangSys	*baseLangSysRecords ;//[baseLangSysCount]	Array of BaseLangSys records, in alphabetical order by BaseLangSysTag.
}BaseScript;
ACQRES(BaseScript) {    
    one(&(f->baseValuesOffset)) ;
    one(&(f->defaultMinMaxOffset)) ;
    one(&(f->baseLangSysCount)) ;
    arr((f->baseLangSysRecords),f->baseLangSysCount);
};
USE_ACQRES(BaseScript) 

typedef struct {//    BaseScriptRecord
    Tag	baseScriptTag ;//	4-byte script identification tag.
    Offset16	baseScriptOffset ;//	Offset to BaseScript table, from beginning of BaseScriptList.
}BaseScriptRecord;
typedef struct {//BaseScriptList table
    uint16	baseScriptCount;//	Number of BaseScriptRecords defined.
    BaseScriptRecord	*baseScriptRecords;//[baseScriptCount]	Array of BaseScriptRecords, in alphabetical order by baseScriptTag.
}BaseScriptList;
ACQRES(BaseScriptList) {    
    one(&(f->baseScriptCount));
    arr((f->maseScriptRecords),f->baseScriptCount) ;
};
USE_ACQRES(BaseScriptList) 


typedef struct{//BaseTagList 
    uint16	baseTagCount ;//	Number of baseline identification tags in this text direction — may be zero (0).
    Tag	*baselineTags ;//[baseTagCount]	Array of 4-byte baseline identification tags — must be in alphabetical order.
}BaseTagList;
 ACQRES(BaseScriptList) {
    one(&(f->baseTagCount));
    arr((f->baselineTags),f->baseTagCount);
};
USE_ACQRES(BaseScriptList) 


    typedef struct {//Axis table
Offset16	baseTagListOffset	;//Offset to BaseTagList table, from beginning of Axis table (may be NULL).
Offset16	baseScriptListOffset	;//Offset to BaseScriptList table, from beginning of Axis table.
}Axis;    

    
typedef struct {
        uint16	majorVersion ; //	Major version of the BASE table, = 1.
        uint16	minorVersion ; //	Minor version of the BASE table, = 0.
        Offset16	horizAxisOffset ; //	Offset to horizontal Axis table, from beginning of BASE table (may be NULL).
        Offset16	vertAxisOffset ; //	Offset to vertical Axis table, from beginning of BASE table (may be NULL).
    }base10;
    typedef struct {
        uint16	majorVersion ; //	Major version of the BASE table, = 1.
        uint16	minorVersion ; //	Minor version of the BASE table, = 1.
        Offset16	horizAxisOffset ; //	Offset to horizontal Axis table, from beginning of BASE table (may be NULL).
        Offset16	vertAxisOffset ; //	Offset to vertical Axis table, from beginning of BASE table (may be NULL).
        Offset32	itemVarStoreOffset ; //	Offset to ItemVariationStore table, from beginning of BASE table (may be null).
    }base11;
    typedef union {
        base10 b10;
        base11 b11 ;
    }basehead;
    typedef struct {
        MinMax d;
        BaseCoordFormat min;
        BaseCoordFormat max;
        BaseCoordFormat* Mincoord ;
        BaseCoordFormat* Maxcoord ;
    }MinMaxBox;
    ACQRES(MinMaxBox) {
        one(&(f->d)) ;
        offone(&(f->min) ,f->d.minCoordOffset) ; 
        offone(&(f->max) ,f->d.maxCoordOffset) ;
        f->Mincoord = new BaseCoordFormat[f->d.featMinMaxCount];
        f->Maxcoord = new BaseCoordFormat[f->d.featMinMaxCount];
        for(int i = 0 ; i < f->d.featMinMaxCount){
            offone(&(f->Mincoord),f->d.featMinMaxRecords[i].minCoordOffset);
            offone(&(f->Maxcoord),f->d.featMinMaxRecords[i].maxCoordOffset);
        };
    };
    USE_ACQRES(MinMaxBox)
    typedef struct {
        BaseScript baseScript ;
        BaseValues baseValues;
        BaseCoordFormat* baseCoordValues;
        MinMaxBox* minMax;
    }BaseScriptBox;
    ACQRES(BaseScriptBox) {
        one(&(f->baseScript));
        offone(&(f->baseValues),f->baseScript.baseValuesOffset);
        for(int i = 0 ; i < f->baseValues.baseCoordCount){
            offone(&(f->baseCoordValues[i]),f->baseScript.baseValuesOffset + f->baseValues.baseCoordOffsets[i]);
        };
        for(int i = 0 ; i < f->baseScript.baseLangSysCount;i++){
            one(&(f->minMax[i]))
        };
    };
    USE_ACQRES(BaseScriptBox)
    typedef struct  {
        Axis ax;
        BaseTagList baseTagList;
        BaseScriptList baseScriptList;
        BaseScriptBox* baseScript ; 
        
    }AxisBox;
    ACQRES(AxisBox) {
        one(&(f->ax));
        if(f->ax.baseTagListOffset != NULL){
            offone(&(f->baseTagList),f->ax.baseTagListOffset);
        };
        offone(&(f->baseScriptList),f->ax.baseScriptListOffset);
        for(int i =0 ; i < f->baseScriptList.baseScriptCount;i++){
            offone(&(f->baseScript[i]),f->baseScriptList.baseScriptRecords[i].baseScriptOffset);
        };
    }
    USE_ACQRES(AxisBox) 
    typedef struct {
        basehead head;
        AxisBox hori ;    
        AxisBox verti ;

    }BASE;
    ACQRES(BASE) {
        one((f->head));
        if(f->head.b10.minorVersion == 1){
            one(&(f->head.b11.itemVarStoreOffset));
        };
        offone(&(f->hori),f->head.horiAxisOffset);
        offone(&(f->hori),f->head.vertAxisOffset);
    };
    USE_ACQRES(BASE)

    // CBDT

    typedef struct {//BigGlyphMetrics record
        uint8	height;//	Number of rows in the bitmap.
        uint8	width;//	Number of columns in the bitmap.
        int8	horiBearingX;//	Distance in pixels from the horizontal origin to the left edge of the bitmap.
        int8	horiBearingY;//	Distance in pixels from the horizontal origin to the top edge of the bitmap.
        uint8	horiAdvance;//	Horizontal advance width in pixels.
        int8	vertBearingX;//	Distance in pixels from the vertical origin to the left edge of the bitmap.
        int8	vertBearingY;//	Distance in pixels from the vertical origin to the top edge of the bitmap.
        uint8	vertAdvance;//	Vertical advance width in pixels.
    }BigGlyphMetrics;
    typedef struct { //SmallGlyphMetrics record
        uint8	height ;//	Number of rows in the bitmap.
        uint8	width ;//	Number of columns in the bitmap.
        int8	bearingX ;//	Distance in pixels from the horizontal origin to the left edge of the bitmap (for horizontal text); or distance in pixels from the vertical origin to the top edge of the bitmap (for vertical text).
        int8	bearingY ;//	Distance in pixels from the horizontal origin to the top edge of the bitmap (for horizontal text); or distance in pixels from the vertical origin to the left edge of the bitmap (for vertical text).
        uint8	advance ;//	Horizontal or vertical advance width in pixels.
    }SmallGlyphMetrics;

typedef struct {//GlyphBitmapFormat17 table
    smallGlyphMetrics	glyphMetrics;//	Metrics information for the glyph
    uint32	dataLen;//	Length of data in bytes
    uint8*	data;//[dataLen]	Raw PNG data
    
}   GlyphBitmapFormat17;
ACQRES(GlyphBitmapFormat17){
    one(&(f->glypMetrics));
    one(&(f->dataLen));
    arr((d->data),f->dataLen);
};

USE_ACQRES(GlyphBitmapFormat17)
typedef struct {//GlyphBitmapFormat18 table

    bigGlyphMetrics	glyphMetrics;//	Metrics information for the glyph
    uint32	dataLen;	//Length of data in bytes
    uint8	*data;//[dataLen]	Raw PNG data    
}GlyphBitmapFormat18;
ACQRES(GlyphBitmapFormat18){
    one(&(f->glypMetrics));
    one(&(f->dataLen));
    arr((d->data),f->dataLen);
};
USE_ACQRES(GlyphBitmapFormat18){

typedef struct {//GlyphBitmapFormat19 table
    uint32	dataLen;//	Length of data in bytes
    uint8	*data;//[dataLen]	Raw PNG data

}GlyphBitmapFormat19;
ACQRES(GlyphBitmapFormat19){
    one(&(f->dataLen));
    arr((d->data),f->dataLen);
};
USE_ACQRES(GlyphBitmapFormat19)
typedef union {
    GlyphBitmapFormat18 f17 ;
    GlyphBitmapFormat18 f18 ; 
    GlyphBitmapFormat19 f19 ;
}cbdtFormat;




    typedef struct {
    uint16	majorVersion ;//	Major version of the CBDT table, = 3.
    uint16	minorVersion ;//	Minor version of the CBDT table, = 0.
    }cbdtHead;
    typedef struct {
        cbdtHead head ;
        cbdtFormat form;
    }CBDT;
    ACQRES(CBDT){
        one(&(f->head));
        one(&(f->form));
    };
    USE_ACQRES(CBDT)

    // CBLC
    typedef struct{
    int8	ascender ;
    int8	descender ;
    uint8	widthMax ;
    int8	caretSlopeNumerator ;
    int8	caretSlopeDenominator ;
    int8	caretOffset ;
    int8	minOriginSB ;
    int8	minAdvanceSB ;
    int8	maxBeforeBL ;
    int8	minAfterBL ;
    int8	pad1 ;
    int8	pad2 ;
    }SbitLineMetrics;    
    typedef struct {
    Offset32	indexSubtableListOffset;//	Offset to index subtable from beginning of CBLC.
    uint32	indexSubtableListSize;//	Number of bytes in corresponding index subtables and array.
    uint32	numberOfIndexSubtables;//	There is an index subtable for each range or format change.
    uint32	colorRef;//	Not used; set to 0.
    SbitLineMetrics	hori;//	Line metrics for text rendered horizontally.
    SbitLineMetrics	vert;//	Line metrics for text rendered vertically.
    uint16	startGlyphIndex;//	Lowest glyph index for this size.
    uint16	endGlyphIndex;//	Highest glyph index for this size.
    uint8	ppemX;//	Horizontal pixels per em.
    uint8	ppemY;//	Vertical pixels per em.
    uint8	bitDepth;//	In addition to already defined bitDepth values 1, 2, 4, and 8 used for monochrome and grayscale bitmaps, the value of 32 is used to identify color bitmaps with 8 bit per channel BGRA pixel data.
    int8	flags;//	Vertical or horizontal (see the Bitmap flags section of the EBLC table chapter).
    }BitmapSize;

    typedef struct {
        uint16	majorVersion ;//	Major version of the CBLC table, = 3.
        uint16	minorVersion ;//	Minor version of the CBLC table, = 0.
        uint32	numSizes ;//	Number of BitmapSize records.
        BitmapSize	*bitmapSizes ;//[numSizes]	BitmapSize records array.
        // Note that the first version of the CBLC table is 3.0.    
    }CblcHeader;
    ACQRES(CblcHeader){
        one(&(f->majorVersion));
        one(&(f->minorVersion));
        one(&(f->numSizes));
        arr(f->bitmapSizes,f->numSizes);
    };
    USE_ACQRES(CblcHeader)
    

    // CFF2
    typedef struct {
    uint8	majorVersion ;//	Format major version (set to 2).
    uint8	minorVersion ;//	Format minor version (set to 0).
    uint8	headerSize ;//	Header size (set to 5).
    uint16	topDICTSize ;//	Length of TopDICT subtable.
    }CFF2head;
    typedef struct {
        CFF2head head;
    }CFF2;
    template     void ld<CFF2>(CFF2* f , std::ifstream* fi){

    };
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
    }CMAPf0;
    template     void ld<CMAPf0>(CMAPf0* f, std::ifsteam* fi){
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
    }CMAPf2;
    template     void ld<CMAPf2>(CMAPf2* f, std::ifstream* fi ){
        ld(&(f->length),fi);
        ld(&(f->language),fi);
        ld(&(f->subHeaderKeys),fi);
        uint16_t km = f->subHeaderKeys[0];
        for(const auto it : f->subHeaderKeys){
            if(it>km){
                km = it; 
            };
        };
        ld(&(f->subHeaders),fi, (f->km/8+1 ) ));
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
    }CMAPf4;
    template     void ld<CMAPf4>(CMAPf4* f, std::ifstream* fi){
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
    template     void ld<CMAPf6>(CMAPf4* f, std::ifstream* fi){
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
    }CMAPf8;
    template     void ld<CMAPf8>(CMAPf8* f, std::ifstream* fi){
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
    }CMAPf10;
    template     void ld<CMAPf10>(CMAPf10* f, std::ifstream* fi){
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
    }CMAPf12;
    template     void ld<CMAPf12>(CMAPf12* f, std::ifstream* fi){
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
    }CMAPf13;
    template     void ld<CMAPf13>(CMAPf13* f, std::ifstream* fi){
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
    }CMAPf14;
    template     void ld<CMAPf14>(CMAPf14* f, std::ifstream* fi){
        ld(&(f->length),fi);
        ld(&(f->numVarSelectorRecords),fi);
        ld(&(f->varSelector),fi , f->numVarSelectorRecords );
    };

    typedef union {
        CMAPf0 f0;
        CMAPf2 f2;
        CMAPf4 f4;
        CMAPf6 f6;
        CMAPf8 f8;
        CMAPf10 f10;
        CMAPf12 f12;
        CMAPf13 f13;
        CMAPf14 f14 ;
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
        uint16_t version;
        uint16_t numTables;
        EncodingRecord *encodingRecords;//[numTabes];
        cmap_format* ftable ;
    }cmap;
    
// COLR tb
template <typename T>
inline void loadOneBack(T* f, std::ifstream* fi){
    fi->seekp(ti->tellp()-1);
    ld(f,fi);
} ;
typedef struct{//PaintColrLayers
uint8	format ;//	Set to 1.
uint8	numLayers ;//	Number of offsets to paint tables to read from LayerList.
uint32	firstLayerIndex ;//	Index (base 0) into the LayerList.
}COLRf1;
template void ld<COLRf1>(COLRf1* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintSolid, 
    uint8	format ;//	Set to 2.
    uint16	paletteIndex ;//	Index for a CPAL palette entry.
    F2DOT14	alpha ;//	Alpha value.
}COLRf2;
template void ld<COLRf2>(COLRf2* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintVarSolid
    uint8	format ;//	Set to 3.
    uint16	paletteIndex ;//	Index for a CPAL palette entry.
    F2DOT14	alpha ;//	Alpha value. For variation, use varIndexBase + 0.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}COLRf3;
template void ld<COLRf3>(COLRf3* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintLinearGradient, 
    uint8	format ;//	Set to 4.
    Offset24	colorLineOffset ;//	Offset to ColorLine table, from beginning of PaintLinearGradient table.
    FWORD	x0 ;//	Start point (p₀) x coordinate.
    FWORD	y0 ;//	Start point (p₀) y coordinate.
    FWORD	x1 ;//	End point (p₁) x coordinate.
    FWORD	y1 ;//	End point (p₁) y coordinate.
    FWORD	x2 ;//	Rotation point (p₂) x coordinate.
    FWORD	y2 ;//	Rotation point (p₂) y coordinate.
}COLRf4;
template void ld<COLRf4>(COLRf4* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintVarLinearGradient
    uint8	format;//	Set to 5.
    Offset24	colorLineOffset;//	Offset to VarColorLine table, from beginning of PaintVarLinearGradient table.
    FWORD	x0;//	Start point (p₀) x coordinate. For variation, use varIndexBase + 0.
    FWORD	y0;//	Start point (p₀) y coordinate. For variation, use varIndexBase + 1.
    FWORD	x1;//	End point (p₁) x coordinate. For variation, use varIndexBase + 2.
    FWORD	y1;//	End point (p₁) y coordinate. For variation, use varIndexBase + 3.
    FWORD	x2;//	Rotation point (p₂) x coordinate. For variation, use varIndexBase + 4.
    FWORD	y2;//	Rotation point (p₂) y coordinate. For variation, use varIndexBase + 5.
    uint32	varIndexBase;//	Base index into DeltaSetIndexMap.
}COLRf5;
template void ld<COLRf5>(COLRf5* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ //PaintRadialGradient, 
    uint8	format ;//	Set to 6.
    Offset24	colorLineOffset ;//	Offset to ColorLine table, from beginning of PaintRadialGradient table.
    FWORD	x0 ;//	Start circle center x coordinate.
    FWORD	y0 ;//	Start circle center y coordinate.
    UFWORD	radius0 ;//	Start circle radius.
    FWORD	x1 ;//	End circle center x coordinate.
    FWORD	y1 ;//	End circle center y coordinate.
    UFWORD	radius1 ;//	End circle radius.
}COLRf6;
template void ld<COLRf6>(COLRf6* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ //PaintVarRadialGradient
    uint8	format;//	Set to 7.
    Offset24	colorLineOffset;//	Offset to VarColorLine table, from beginning of PaintVarRadialGradient table.
    FWORD	x0;//	Start circle center x coordinate. For variation, use varIndexBase + 0.
    FWORD	y0;//	Start circle center y coordinate. For variation, use varIndexBase + 1.
    UFWORD	radius0;//	Start circle radius. For variation, use varIndexBase + 2.
    FWORD	x1;//	End circle center x coordinate. For variation, use varIndexBase + 3.
    FWORD	y1;//	End circle center y coordinate. For variation, use varIndexBase + 4.
    UFWORD	radius1;//	End circle radius. For variation, use varIndexBase + 5.
    uint32	varIndexBase;//	Base index into DeltaSetIndexMap.
}COLRf7;
template void ld<COLRf7>(COLRf7* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintSweepGradient 
    uint8	format ;//	Set to 8.
    Offset24	colorLineOffset ;//	Offset to ColorLine table, from beginning of PaintSweepGradient table.
    FWORD	centerX ;//	Center x coordinate.
    FWORD	centerY ;//	Center y coordinate.
    F2DOT14	startAngle ;//	Start of the angular range of the gradient: add 1.0 and multiply by 180° to retrieve counter-clockwise degrees.
    F2DOT14	endAngle ;//	End of the angular range of the gradient: add 1.0 and multiply by 180° to retrieve counter-clockwise degrees.
}COLRf8;
template void ld<COLRf8>(COLRf8* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintVarSweepGradient 
    uint8	format;//	Set to 9.
    Offset24	colorLineOffset;//	Offset to VarColorLine table, from beginning of PaintVarSweepGradient table.
    FWORD	centerX;//	Center x coordinate. For variation, use varIndexBase + 0.
    FWORD	centerY;//	Center y coordinate. For variation, use varIndexBase + 1.
    F2DOT14	startAngle;//	Start of the angular range of the gradient: add 1.0 and multiply by 180° to retrieve counter-clockwise degrees. For variation, use varIndexBase + 2.
    F2DOT14	endAngle;//	End of the angular range of the gradient: add 1.0 and multiply by 180° to retrieve counter-clockwise degrees. For variation, use varIndexBase + 3.
    uint32	varIndexBase;//	Base index into DeltaSetIndexMap.
}COLRf9;
template void ld<COLRf9>(COLRf9* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintGlyph 
uint8	format;//	Set to 10.
Offset24	paintOffset;//	Offset to a Paint table, from beginning of PaintGlyph table.
uint16	glyphID;//	Glyph ID for the source outline.
}COLRf10;
template void ld<COLRf10>(COLRf10* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintColrGlyph 
    uint8	format ;//	Set to 11.
    uint16	glyphID ;//	Glyph ID for a BaseGlyphList base glyph.

}COLRf11;
template void ld<COLRf11>(COLRf11* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintTransform 
    uint8	format ;//	Set to 12.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintTransform table.
    Offset24	transformOffset ;//	Offset to an Affine2x3 table, from beginning of PaintTransform table.

}COLRf12;
template void ld<COLRf12>(COLRf12* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintVarTransform 
    uint8	format ;//	Set to 13.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarTransform table.
    Offset24	transformOffset ;//	Offset to a VarAffine2x3 table, from beginning of PaintVarTransform table.

}COLRf13;

typedef struct{//Affine2x3 
Fixed	xx ;//	x-component of transformed x-basis vector.
Fixed	yx ;//	y-component of transformed x-basis vector.
Fixed	xy ;//	x-component of transformed y-basis vector.
Fixed	yy ;//	y-component of transformed y-basis vector.
Fixed	dx ;//	Translation in x direction.
Fixed	dy ;//	Translation in y direction.
}Affine2x3;
typedef struct {//VarAffine2x3 table:

Fixed	xx ;//	x-component of transformed x-basis vector. For variation, use varIndexBase + 0.
Fixed	yx ;//	y-component of transformed x-basis vector. For variation, use varIndexBase + 1.
Fixed	xy ;//	x-component of transformed y-basis vector. For variation, use varIndexBase + 2.
Fixed	yy ;//	y-component of transformed y-basis vector. For variation, use varIndexBase + 3.
Fixed	dx ;//	Translation in x direction. For variation, use varIndexBase + 4.
Fixed	dy ;//	Translation in y direction. For variation, use varIndexBase + 5.
uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}VarAffine2x3;
template void ld<COLRf13>(COLRf13* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintTranslate 
    uint8	format ;//	Set to 14.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintTranslate table.
    FWORD	dx ;//	Translation in x direction.
    FWORD	dy ;//	Translation in y direction.
   

}COLRf14;
template void ld<COLRf14>(COLRf14* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ //PaintVarTranslate 
    uint8	format ;//	Set to 15.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarTranslate table.
    FWORD	dx ;//	Translation in x direction. For variation, use varIndexBase + 0.
    FWORD	dy ;//	Translation in y direction. For variation, use varIndexBase + 1.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.

}COLRf15;
template void ld<COLRf15>(COLRf15* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct {//PaintScale     uint8	format	Set to 16.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintScale table.
    F2DOT14	scaleX ;//	Scale factor in x direction.
    F2DOT14	scaleY ;//	Scale factor in y direction.
}COLRf16;
template void ld<COLRf16>(COLRf16* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ //PaintVarScale
    uint8	format ;//	Set to 17.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarScale table.
    F2DOT14	scaleX ;//	Scale factor in x direction. For variation, use varIndexBase + 0.
    F2DOT14	scaleY ;//	Scale factor in y direction. For variation, use varIndexBase + 1.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.

}COLRf17;
template void ld<COLRf17>(COLRf17* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintScaleAroundCenter
    uint8	format ;//	Set to 18.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintScaleAroundCenter table.
    F2DOT14	scaleX ;//	Scale factor in x direction.
    F2DOT14	scaleY ;//	Scale factor in y direction.
    FWORD	centerX ;//	x coordinate for the center of scaling.
    FWORD	centerY ;//	y coordinate for the center of scaling.
}COLRf18;
template void ld<COLRf18>(COLRf18* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintVarScaleAroundCenter
    uint8	format ;//	Set to 19.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarScaleAroundCenter table.
    F2DOT14	scaleX ;//	Scale factor in x direction. For variation, use varIndexBase + 0.
    F2DOT14	scaleY ;//	Scale factor in y direction. For variation, use varIndexBase + 1.
    FWORD	centerX ;//	x coordinate for the center of scaling. For variation, use varIndexBase + 2.
    FWORD	centerY ;//	y coordinate for the center of scaling. For variation, use varIndexBase + 3.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
  
}COLRf19;
template void ld<COLRf19>(COLRf19* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{  //PaintScaleUniform 
    uint8	format ;//	Set to 20.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintScaleUniform table.
    F2DOT14	scale ;//	Scale factor in x and y directions.
  
}COLRf20;
template void ld<COLRf20>(COLRf20* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//  PaintVarScaleUniform
    uint8	format ;//	Set to 21.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarScaleUniform table.
    F2DOT14	scale ;//	Scale factor in x and y directions. For variation, use varIndexBase + 0.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
   
}COLRf21;
template void ld<COLRf21>(COLRf21* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ //PaintScaleUniformAroundCenter
    uint8 	format;//	Set to 22.
    Offset24 	paintOffset;//	Offset to a Paint subtable, from beginning of PaintScaleUniformAroundCenter table.
    F2DOT14 	scale;//	Scale factor in x and y directions.
    FWORD 	centerX;//	x coordinate for the center of scaling.
    FWORD 	centerY;//	y coordinate for the center of scaling.
    
}COLRf22;
template void ld<COLRf22>(COLRf22* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintVarScaleUniformAroundCenter 
    uint8	format ;//	Set to 23.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarScaleUniformAroundCenter table.
    F2DOT14	scale ;//	Scale factor in x and y directions. For variation, use varIndexBase + 0.
    FWORD	centerX ;//	x coordinate for the center of scaling. For variation, use varIndexBase + 1.
    FWORD	centerY ;//	y coordinate for the center of scaling. For variation, use varIndexBase + 2.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}COLRf23;
template void ld<COLRf23>(COLRf23* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintRotate 
    uint8	format ;//	Set  to 24.
    Offset24	paintOffset ;//	Offset  to a Paint subtable, from beginning of PaintRotate table.
    F2DOT14	angle ;//	Rotation  angle, 180° in counter-clockwise degrees per 1.0 of value.
   
}COLRf24;
template void ld<COLRf24>(COLRf24* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ // PaintVarRotate
    uint8	format ;//	Set to 25.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarRotate table.
    F2DOT14	angle ;//	Rotation angle, 180° in counter-clockwise degrees per 1.0 of value. For variation, use varIndexBase + 0.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
  
}COLRf25;
template void ld<COLRf25>(COLRf25* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{  //PaintRotateAroundCenter 
    uint8	format ;//	Set to 26.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintRotateAroundCenter table.
    F2DOT14	angle ;//	Rotation angle, 180° in counter-clockwise degrees per 1.0 of value.
    FWORD	centerX ;//	x coordinate for the center of rotation.
    FWORD	centerY ;//	y coordinate for the center of rotation.
   
}COLRf26;
template void ld<COLRf26>(COLRf26* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{ //PaintVarRotateAroundCenter
    uint8	format ;//	Set to 27.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarRotateAroundCenter table.
    F2DOT14	angle ;//	Rotation angle, 180° in counter-clockwise degrees per 1.0 of value. For variation, use varIndexBase + 0.
    FWORD	centerX ;//	x coordinate for the center of rotation. For variation, use varIndexBase + 1.
    FWORD	centerY ;//	y coordinate for the center of rotation. For variation, use varIndexBase + 2.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}COLRf27;
template void ld<COLRf27>(COLRf27* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//PaintSkew table (format 28):
    uint8	format ;//	Set to 28.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintSkew table.
    F2DOT14	xSkewAngle ;//	Angle of skew in the direction of the x-axis, 180° in counter-clockwise degrees per 1.0 of value.
    F2DOT14	ySkewAngle ;//	Angle of skew in the direction of the y-axis, 180° in counter-clockwise degrees per 1.0 of value.
    
}COLRf28;
template void ld<COLRf28>(COLRf28* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{    //PaintVarSkew
    uint8	format ;//	Set to 29.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarSkew table.
    F2DOT14	xSkewAngle ;//	Angle of skew in the direction of the x-axis, 180° in counter-clockwise degrees per 1.0 of value. For variation, use varIndexBase + 0.
    F2DOT14	ySkewAngle ;//	Angle of skew in the direction of the y-axis, 180° in counter-clockwise degrees per 1.0 of value. For variation, use varIndexBase + 1.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.

}COLRf29;
template void ld<COLRf29>(COLRf29* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{    //PaintSkewAroundCenter 
    uint8	format ;//	Set to 30.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintSkewAroundCenter table.
    F2DOT14	xSkewAngle ;//	Angle of skew in the direction of the x-axis, 180° in counter-clockwise degrees per 1.0 of value.
    F2DOT14	ySkewAngle ;//	Angle of skew in the direction of the y-axis, 180° in counter-clockwise degrees per 1.0 of value.
    FWORD	centerX ;//	x coordinate for the center of rotation.
    FWORD	centerY ;//	y coordinate for the center of rotation.

}COLRf30;
template void ld<COLRf30>(COLRf30* f, std::ifstream* fi){loadOneBack(f,fi);};
typedef struct{//    PaintVarSkewAroundCenter 
    uint8	format ;//	Set to 31.
    Offset24	paintOffset ;//	Offset to a Paint subtable, from beginning of PaintVarSkewAroundCenter table.
    F2DOT14	xSkewAngle ;//	Angle of skew in the direction of the x-axis, 180° in counter-clockwise degrees per 1.0 of value. For variation, use varIndexBase + 0.
    F2DOT14	ySkewAngle ;//	Angle of skew in the direction of the y-axis, 180° in counter-clockwise degrees per 1.0 of value. For variation, use varIndexBase + 1.
    FWORD	centerX ;//	x coordinate for the center of rotation. For variation, use varIndexBase + 2.
    FWORD	centerY ;//	y coordinate for the center of rotation. For variation, use varIndexBase + 3.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}COLRf31;
template void ld<COLRf31>(COLRf31* f, std::ifstream* fi){
    
};
enum CompositeMode{
// Value	Name	Description
// Porter-Duff modes	
COMPOSITE_CLEAR=0,	//	Clear
COMPOSITE_SRC=1,	//	Source (“Copy” in Composition & Blending Level 1)
COMPOSITE_DEST=2,	//	Destination
COMPOSITE_SRC_OVER=3,	//	Source Over
COMPOSITE_DEST_OVER=4,	//	Destination Over
COMPOSITE_SRC_IN=5,	//	Source In
COMPOSITE_DEST_IN=6,	//	Destination In
COMPOSITE_SRC_OUT=7,	//	Source Out
COMPOSITE_DEST_OUT=8,	//	Destination Out
COMPOSITE_SRC_ATOP=9,	//	Source Atop
COMPOSITE_DEST_ATOP=1,0	//	Destination Atop
COMPOSITE_XOR=1,1	//	XOR
COMPOSITE_PLUS=1,2	//	Plus (“Lighter” in Composition & Blending Level 1)
// Separable color blend modes:	
COMPOSITE_SCREEN=13, //		screen
COMPOSITE_OVERLAY=14, //		overlay
COMPOSITE_DARKEN=15, //		darken
COMPOSITE_LIGHTEN=16, //		lighten
COMPOSITE_COLOR_DODGE=17, //		color-dodge
COMPOSITE_COLOR_BURN=18, //		color-burn
COMPOSITE_HARD_LIGHT=19, //		hard-light
COMPOSITE_SOFT_LIGHT=20, //		soft-light
COMPOSITE_DIFFERENCE=21, //		difference
COMPOSITE_EXCLUSION=22, //		exclusion
COMPOSITE_MULTIPLY=23, //		multiply
// Non-separable color blend modes:	
COMPOSITE_HSL_HUE=24,//		hue
COMPOSITE_HSL_SATURATION=25,//		saturation
COMPOSITE_HSL_COLOR=26,//		color
COMPOSITE_HSL_LUMINOSITY=27//		luminosity
};
typedef struct{// PaintComposite 
    uint8	format ;//	Set to 32.
    Offset24	sourcePaintOffset ;//	Offset to a source Paint table, from beginning of PaintComposite table.
    uint8	compositeMode ;//	A CompositeMode enumeration value.
    Offset24	backdropPaintOffset ;//	Offset to a backdrop Paint table, from beginning of PaintComposite table.
}COLRf32;
template void ld<COLRf32>(COLRf32* f, std::ifstream* fi){loadOneBack(f,fi);};
    typedef union {
        COLRf0 f0;
        COLRf1 f1;
        COLRf2 f2;
        COLRf3 f3;
        COLRf4 f4;
        COLRf5 f5;
        COLRf6 f6;
        COLRf7 f7;
        COLRf8 f8;
        COLRf9 f9;
        COLRf10 f10;
        COLRf11 f11;
        COLRf12 f12;
        COLRf13 f13;
        COLRf14 f14;
        COLRf15 f15;
        COLRf16 f16;
        COLRf17 f17;
        COLRf18 f18;
        COLRf19 f19;
        COLRf20 f20;
        COLRf21 f21;
        COLRf22 f22;
        COLRf23 f23;
        COLRf24 f24;
        COLRf25 f25;
        COLRf26 f26;
        COLRf27 f27;
        COLRf28 f28;
        COLRf29 f29;
        COLRf30 f30;
        COLRf31 f31;
        COLRf32 f32;
        
    }COLR_format;
void ld<COLR_format>(COLR_format* f, std::ifstream* fi){
    uint8 s;
    ld(&s ,fi);
    switch(s){
        case 1 : {f->f1 = 1; ld<COLRf1>(&(f->f1),fi);continue;};
        case 2 : {f->f2 = 2; ld<COLRf2>(&(f->f2),fi);continue;};
        case 3 : {f->f3 = 3; ld<COLRf3>(&(f->f3),fi);continue;};
        case 4 : {f->f4 = 4; ld<COLRf4>(&(f->f4),fi);continue;};
        case 5 : {f->f5 = 5; ld<COLRf5>(&(f->f5),fi);continue;};
        case 6 : {f->f6 = 6; ld<COLRf6>(&(f->f6),fi);continue;};
        case 7 : {f->f7 = 7; ld<COLRf7>(&(f->f7),fi);continue;};
        case 8 : {f->f8 = 8; ld<COLRf8>(&(f->f8),fi);continue;};
        case 9 : {f->f9 = 9; ld<COLRf9>(&(f->f9),fi);continue;};
        case 10 : {f->f10 = 10; ld<COLRf10>(&(f->f10),fi);continue;};
        case 11 : {f->f11 = 11; ld<COLRf11>(&(f->f11),fi);continue;};
        case 12 : {f->f12 = 12; ld<COLRf12>(&(f->f12),fi);continue;};
        case 13 : {f->f13 = 13; ld<COLRf13>(&(f->f13),fi);continue;};
        case 14 : {f->f14 = 14; ld<COLRf14>(&(f->f14),fi);continue;};
        case 15 : {f->f15 = 15; ld<COLRf15>(&(f->f15),fi);continue;};
        case 16 : {f->f16 = 16; ld<COLRf16>(&(f->f16),fi);continue;};
        case 17 : {f->f17 = 17; ld<COLRf17>(&(f->f17),fi);continue;};
        case 18 : {f->f18 = 18; ld<COLRf18>(&(f->f18),fi);continue;};
        case 19 : {f->f19 = 19; ld<COLRf19>(&(f->f19),fi);continue;};
        case 20 : {f->f20 = 20; ld<COLRf20>(&(f->f20),fi);continue;};
        case 21 : {f->f21 = 21; ld<COLRf21>(&(f->f21),fi);continue;};
        case 22 : {f->f22 = 22; ld<COLRf22>(&(f->f22),fi);continue;};
        case 23 : {f->f23 = 23; ld<COLRf23>(&(f->f23),fi);continue;};
        case 24 : {f->f24 = 24; ld<COLRf24>(&(f->f24),fi);continue;};
        case 25 : {f->f25 = 25; ld<COLRf25>(&(f->f25),fi);continue;};
        case 26 : {f->f26 = 26; ld<COLRf26>(&(f->f26),fi);continue;};
        case 27 : {f->f27 = 27; ld<COLRf27>(&(f->f27),fi);continue;};
        case 28 : {f->f28 = 28; ld<COLRf28>(&(f->f28),fi);continue;};
        case 29 : {f->f29 = 29; ld<COLRf29>(&(f->f29),fi);continue;};
        case 30 : {f->f30 = 30; ld<COLRf30>(&(f->f30),fi);continue;};
        case 31 : {f->f31 = 31; ld<COLRf31>(&(f->f31),fi);continue;};
        case 32 : {f->f32 = 32; ld<COLRf32>(&(f->f32),fi);continue;};
    }
};
typedef struct {
    uint16	glyphID ;//	Glyph ID of the base glyph.
    uint16	firstLayerIndex ;//	Index (base 0) into the layerRecords array.
    uint16	numLayers ;//	Number of color layers associated with this glyph.
} BaseGlyph;
typedef struct {
    uint16	glyphID ;//	Glyph ID of the glyph used for a given layer.
    uint16	paletteIndex ;//	Index (base 0) for a palette entry in the CPAL table.
}Layer ;
typedef struct {
    uint16	glyphID ;//	Glyph ID of the base glyph.
    Offset32	paintOffset ;//	Offset to a Paint table, from beginning of BaseGlyphList table.
}BaseGlyphPaintRecord;
typedef struct {
    uint32	numBaseGlyphPaintRecords	;
BaseGlyphPaintRecord	*baseGlyphPaintRecords ;//[numBaseGlyphPaintRecords]	
}BaseGlyphList;
typedef struct {
    uint32	numLayers;	
    Offset32	*paintOffsets; //[numLayers]	Offsets to Paint tables, from beginning of LayerList table.
}LayerList; 

typedef struct {
    uint16	startGlyphID ;//	First glyph ID in the range.
    uint16	endGlyphID ;//	Last glyph ID in the range.
    Offset24	clipBoxOffset ;//	Offset to a ClipBox table, from beginning of ClipList table.
}Clip;

typedef struct {
    uint8	format ;//	Set to 1.
    uint32	numClips ;//	Number of Clip records.
    Clip	*clips ;//[numClips]	Clip records. Sorted by startGlyphID.
}ClipList;

typedef struct{
uint8	format	;//Set to 1.
FWORD	xMin	;//Minimum x of clip box.
FWORD	yMin	;//Minimum y of clip box.
FWORD	xMax	;//Maximum x of clip box.
FWORD	yMax	;//Maximum y of clip box.
}ClipBoxFormat1;

typedef struct {
uint8	format ;//	Set to 2.
FWORD	xMin ;//	Minimum x of clip box. For variation, use varIndexBase + 0.
FWORD	yMin ;//	Minimum y of clip box. For variation, use varIndexBase + 1.
FWORD	xMax ;//	Maximum x of clip box. For variation, use varIndexBase + 2.
FWORD	yMax ;//	Maximum y of clip box. For variation, use varIndexBase + 3.
uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}ClipBoxFormat2;

typedef struct {
    F2DOT14	stopOffset ;//	Position on a color line.
    uint16	paletteIndex ;//	Index for a CPAL palette entry.
    F2DOT14	alpha ;//	Alpha value.
}ColorStop;

enum Extend{ 
EXTEND_PAD=0,	//	Use nearest color stop.
EXTEND_REPEAT=1,//  Repeat from farthest color stop.
EXTEND_REFLECT=2//  Mirror color line from nearest end.
};
typedef struct {
    uint8	*extend ;//'	An Extend enum value.
    uint16	*numStops ;//'	Number of ColorStop records.
    ColorStop	*colorStops ;//'[numStops]
}ColorLine;
typedef struct {
    F2DOT14	stopOffset ;//	Position on a color line. For variation, use varIndexBase + 0.
    uint16	paletteIndex ;//	Index for a CPAL palette entry.
    F2DOT14	alpha ;//	Alpha value. For variation, use varIndexBase + 1.
    uint32	varIndexBase ;//	Base index into DeltaSetIndexMap.
}    VarColorStop;

typedef struct {
    uint8	extend ;//	An Extend enum value.
    uint16	numStops ;//	Number of ColorStop records.
    VarColorStop	colorStops ;//[numStops]	Allows for variations.

}VarColorLine;


    typedef struct {
        uint16_t	version ; ///	Table version number—set to 0.
        uint16_t	numBaseGlyphRecords ; ///	Number of BaseGlyph records.
        Offset32	baseGlyphRecordsOffset ; ///	Offset to baseGlyphRecords array, from beginning of COLR table.
        Offset32	layerRecordsOffset ; ///	Offset to layerRecords array, from beginning of COLR table.
        uint16_t	numLayerRecords ; ///	Number of Layer records.
    }COLR0;
    typedef struct {
        uint16	version ;//	Table version number—set to 1.
        uint16	numBaseGlyphRecords ;//	Number of BaseGlyph records; may be 0 in a version 1 table.
        Offset32	baseGlyphRecordsOffset ;//	Offset to baseGlyphRecords array, from beginning of COLR table (may be NULL).
        Offset32	layerRecordsOffset ;//	Offset to layerRecords array, from beginning of COLR table (may be NULL).
        uint16	numLayerRecords ;//	Number of Layer records; may be 0 in a version 1 table.
        Offset32	baseGlyphListOffset ;//	Offset to BaseGlyphList table, from beginning of COLR table.
        Offset32	layerListOffset ;//	Offset to LayerList table, from beginning of COLR table (may be NULL).
        Offset32	clipListOffset ;//	Offset to ClipList table, from beginning of COLR table (may be NULL).
        Offset32	varIndexMapOffset ;//	Offset to DeltaSetIndexMap table, from beginning of COLR table (may be NULL).
        Offset32	itemVariationStoreOffset ;//	Offset to ItemVariationStore, from beginning of COLR table (may be NULL).
    }COLR1 ;
    typedef union {
        COLR0 v0 ;
        COLR1 v1 ;
    }COLRU;
    typedef struct {
        COLRU colr;

    }COLR ;
    // CPAL;
    typedef struct {

    }CPAL; 

    // EBDT
    typedef struct {
        uint16	glyphID ;//	Component glyph ID
        int8	xOffset ;//	Position of component left
        int8	yOffset ;//	Position of component top
        }EbdtComponent;
        
    
typedef struct { // Bytealigned Bitmap
SmallGlyphMetrics	smallMetrics;//	Metrics information for the glyph
uint8	*imageData;//[variable]	Byte-aligned bitmap data
}GlyphBitmapFormat1;
ACQRES(GlyphBitmapFormat1){
    one(&(f->smallMetrics));
    size_t s = f->smallMetrics.width % 8 == 0 ? 
    f->smallMetrics.width *  f->smallMetrics.height / 8 : 
    (1+f->smallMetrics.width) *  f->smallMetrics.height / 8;

    arr(f->imageData,};
USE_ACQRES(GlyphBitmapFormat1)

typedef struct { // BitAligned Bitmap
SmallGlyphMetrics	smallMetrics ;//	Metrics information for the glyph
uint8	*imageData ;//[variable]	Bit-aligned bitmap data
}GlyphBitmapFormat2;
ACQRES(GlyphBitmapFormat2){
    one(&(f->smallMetrics));
    arr(f->imageData,f->smallMetrics.height * f->smallMetrics.width / 8);
};
USE_ACQRES(GlyphBitmapFormat2)

// Glyph bitmap format 2 is the same as format 1 except that the bitmap data is bit aligned. This means that the data for a new row will begin with the bit immediately following the last bit of the previous row. The start of each glyph must be byte aligned, so the last row of a glyph may require padding. This format takes a little more time to parse, but saves file space compared to format 1.
typedef struct {
    uint8	*imageData ;//[variable]	Bit-aligned bitmap data
}GlyphBitmapFormat5;

typedef struct {
uint8	*imageData //[variable]	Byte-aligned bitmap data
}GlyphBitmapFormat6;
typedef struct {
BigGlyphMetrics	bigMetrics;//	Metrics information for the glyph
uint8	*imageData;//[variable]	Bit-aligned bitmap data
}GlyphBitmapFormat7;

typedef struct {
SmallGlyphMetrics	smallMetrics;//	Metrics information for the glyph
uint8	pad;//	Pad to 16-bit boundary
uint16	numComponents;//	Number of components
EbdtComponent*	components;//[numComponents]	Array of EbdtComponent records
}GlyphBitmapFormat8;

typedef struct {
BigGlyphMetrics	bigMetrics ;//	Metrics information for the glyph
uint16	numComponents ;//	Number of components
EbdtComponent	components ;//[numComponents]	Array of EbdtComponent records
}GlyphBitmapFormat9;
typedef struct {
    uint16	majorVersion ;//	Major version of the EBDT table, = 2.
    uint16	minorVersion ;//	Minor version of the EBDT table, = 0.
}EBDThead;
typedef struct {
    EBDThead head ;
}EBDT; 

//EBLC


/*/
The bitDepth field of the BitmapSize record is used to specify the number of levels of gray used in the embedded bitmaps. The following bit depths are supported:

Value	Description
1	black/white
2	4 levels of gray
4	16 levels of gray
8	256 levels of gray

Bitmap flags

The flags field of the BitmapSize record uses the following flags to indicate the direction of small glyph metrics: horizontal or vertical. The remaining bits are reserved.

Bitmap flags enumeration

Mask	Name	Description
0x01	HORIZONTAL_METRICS	Horizontal
0x02	VERTICAL_METRICS	Vertical
0xFC	Reserved	For future use — set to 0.
// The colorRef and bitDepth fields are reserved for future enhancements. For monochrome bitmaps they should have the values colorRef=0 and bitDepth=1.

// Associated with the image data for every glyph in a strike is a set of glyph metrics. These glyph metrics describe bounding box height and width, as well as side bearing and advance width information. The following figures illustrate different metric values used for horizontal or vertical layout.

// Glyph line-direction and cross-stream metrics for horizontal text
// Metrics in horizontal text
// Glyph line-direction and cross-stream metrics for vertical text
// Metrics in vertical text
// Glyph metrics can be found in one of two places. For ranges of glyphs (not necessarily the whole strike) whose metrics may be different for each glyph, the glyph metrics are stored along with the glyph image data in the EBDT table. Details of how this is done are described in the EBDT table chapter. For ranges of glyphs whose metrics are identical for every glyph, significant space can be saved by storing a single copy of the glyph metrics in the IndexSubTable in the EBLC.

// There are also two different formats for glyph metrics: big glyph metrics and small glyph metrics. Big glyph metrics define metrics information for both horizontal and vertical layouts. This is important in fonts (such as Kanji) where both types of layout may be used. Small glyph metrics define metrics information for one layout direction only. Which direction applies, horizontal or vertical, is determined by the flags field in the BitmapSize record.

*/

typedef struct {
    uint16	firstGlyphIndex ;//	First glyph ID of this range.
    uint16	lastGlyphIndex ;//	Last glyph ID of this range (inclusive).
    Offset32	indexSubtableOffset ;//	Offset to an IndexSubtable from the start of the IndexSubtableList.
}IndexSubtableRecord;

typedef struct {
    IndexSubtableRecord	indexSubtableRecords;//[numberOfIndexSubtables ]	Array of IndexSubtableRecords.
}IndexSubtableList;
// The number of IndexSubtableRecord elements is specified by the numberOfIndexSubtables field in the BitmapSize record.

// Records must be sorted by firstGlyphIndex, and records should not have overlapping glyph ID ranges.



typedef struct {
    uint16	indexFormat ;//	Format of the IndexSubtable.
    uint16	imageFormat ;//	Format of EBDT image data.
    Offset32	imageDataOffset ;//	Offset to image data in EBDT table.
}IndexSubHeader;
 

typedef struct {
    IndexSubHeader	header;//	Header info.
    Offset32	sbitOffsets;//[numOffsets]	Offsets to bitmap data for each glyph in the range.
    // Format 1 can be used when glyphs have variable metrics. Offsets for the bitmap data are 4-byte aligned.
    // The number of offsets required is determined from the lastGlyphIndex and firstGlyphIndex fields in the IndexSubtableRecord. One extra entry is required to provide the size of data for the last glyph. Thus, numOffsets = lastGlyphIndex – firstGlyphIndex + 2.
}IndexSubtableFormat1;

typedef struct {
    IndexSubHeader	header ;///	Header info.
    uint32	imageSize ;///	All the glyphs are of the same size.
    BigGlyphMetrics	bigMetrics ;///	All glyphs have the same metrics; glyph data may be compressed, byte-aligned, or bit-aligned.
    // Format 2 can be used when glyphs have identical metrics. The bitmap data for all glyphs will be the same size, so an array of offsets is not required.
}IndexSubtableFormat2;

typedef struct {
    IndexSubHeader	header;//	Header info.
    Offset16	sbitOffsets;//[numOffsets]	Offsets to bitmap data for each glyph in the range.
}IndexSubtableFormat3
// Format 3 can be used when glyphs have variable metrics. Offsets for the bitmap data are 2-byte aligned. The number of offsets required is determined from the lastGlyphIndex and firstGlyphIndex fields in the IndexSubtableRecord. One extra entry is required to provide the size of data for the last glyph. Thus, numOffsets = lastGlyphIndex – firstGlyphIndex + 2.


 typedef struct {
     IndexSubHeader	header;//	Header info.
     uint32	numGlyphs;//	Array length.
     GlyphIdOffsetPair*	glyphArray;//[numGlyphs + 1]	One per glyph.
 }IndexSubtableFormat4

typedef struct {
    uint16	glyphID;//	Glyph ID of glyph present.
    Offset16	sbitOffset;//	Location in EBDT.
}GlyphIdOffsetPair ;


typedef struct {
uint32	imageSize;//	All glyphs have the same data size.
BigGlyphMetrics	bigMetrics;//	All glyphs have the same metrics.
uint32	numGlyphs;//	Array length.
uint16	*glyphIdArray;//[numGlyphs]	One per glyph, sorted by glyph ID.
}IndexSubtableFormat5;

typedef struct {
    int8	ascender;
    int8	descender;
    uint8	widthMax;
    int8	caretSlopeNumerator;
    int8	caretSlopeDenominator;
    int8	caretOffset;
    int8	minOriginSB;
    int8	minAdvanceSB;
    int8	maxBeforeBL;
    int8	minAfterBL;
    int8	pad1;
    int8	pad2;    
}SbitLineMetrics; 
 enum BitMapSizeFlags {
    HORIZONTAL_METRICS =0x01,//		Horizontal
    VERTICAL_METRICS =0x02,//		Vertical
    Reserved =0xFC//	For future use — set to 0.
 };
enum BitDepth{
    bw = 1,	// Black and white
// grayleveles
    gray4 = 2,	 
    gray16 = 4,	 
    gray256 = 8,	 
};

typedef struct {
    Offset32	indexSubtableListOffset;//	Offset to IndexSubtableList, from beginning of EBLC.
    uint32	indexSubtableListSize;//	Total size in bytes of the IndexSubtableList including its array of IndexSubtables.
    uint32	numberOfIndexSubtables;//	Number of IndexSubtables in the IndexSubtableList.
    uint32	colorRef;//	Not used; set to 0.
    SbitLineMetrics	hori;//	Line metrics for text rendered horizontally.
    SbitLineMetrics	vert;//	Line metrics for text rendered vertically.
    uint16	startGlyphIndex;//	Lowest glyph index for this size.
    uint16	endGlyphIndex;//	Highest glyph index for this size.
    uint8	ppemX;//	Horizontal pixels per em.
    uint8	ppemY;//	Vertical pixels per em.
    uint8	bitDepth;//	bit depth: 1, 2, 4, or 8.
    int8	flags;//	Vertical or horizontal (see Bitmap Flags, below).
}BitmapSize;

typedef struct {
    uint16	majorVersion;//	Major version of the EBLC table, = 2.
    uint16	minorVersion;//	Minor version of the EBLC table, = 0.
    uint32	numSizes;//	Number of BitmapSize records.
    BitmapSize	*bitmapSizes;//[numSizes]	BitmapSize records array.
}EBLChead;



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
    template     void ld<maxp>(maxp* f, std::ifstream* fi){ld(f,fi);};
    //name	//Naming table
    typedef struct {
        uint16_t platformID ;//	Platform ID.
        uint16_t encodingID ;//	Platform-specific encoding ID.
        uint16_t languageID ;//	Language ID.
        uint16_t nameID ;//	Name ID.
        uint16_t length ;//	String length (in bytes).
        Offset16	stringOffset ;//	String offset from start of storage area (in bytes).
    }NameRecord;
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
        Version16Dot16	version;//	//
        Fixed	italicAngle;//	Italic angle in counter-clockwise degrees from the vertical. Zero for upright text, negative for text that leans to the right (forward).
        FWORD	underlinePosition;//	Suggested y-coordinate of the top of the underline.
        FWORD	underlineThickness;//	Suggested values for the underline thickness. In general, the underline thickness should match the thickness of the underscore character (U+005F LOW LINE), and should also match the strikeout thickness, which is specified in the OS/2 table.
        uint32	isFixedPitch;//	Set to 0 if the font is proportionally spaced, non-zero if the font is not proportionally spaced (i.e. monospaced).
        uint32	minMemType42;//	Minimum memory usage when an OpenType font is downloaded.
        uint32	maxMemType42;//	Maximum memory usage when an OpenType font is downloaded.
        uint32	minMemType1;//	Minimum memory usage when an OpenType font is downloaded as a Type 1 font.
        uint32	maxMemType1;//	Maximum memory usage when an OpenType font is downloaded as a Type 1 font.
    }postHead;
    typedef struct {
        uint16	numGlyphs	;Number of glyphs.
        int8	*offset;//[numGlyphs]	Difference between the glyph index and the standard order of the glyph.
    }post2_5;
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
        uint16_t	*endPtsOfContours;//[numberOfContours]	Array of point indices for the last point of each contour, in increasing numeric order.
        uint16_t	instructionLength;//	Total number of bytes for instructions. If instructionLength is zero, no instructions are present for this glyph, and this field is followed directly by the flags field.
        uint8_t	*instructions;//[instructionLength]	Array of instruction byte code for the glyph.
        uint8_t	*flags;//[variable]	Array of flag elements. See below for details regarding the number of flag array elements.
        uint8_t 	*xCoordinates;//[variable]	Contour point x-coordinates. See below for details regarding the number of coordinate array elements. Coordinate for the first point is relative to (0,0); others are relative to previous point.
        uint8_t 	*yCoordinates;//[variable]	Contour point y-coordinates. See below for details regarding the number of coordinate array elements. Coordinate for the first point is relative to (0,0); others are relative to previous point.
    }glyf;
    typedef struct {
        Offset16 *offset ; // [numGlyphs+1] ;
    }loca; 
    typedef uint8_t* prep ; // Set of instructions executed whenever point size or font or transformation change. n is the number of uint8_t items that fit in the size of the table.


    

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
        // TableRecord	*tableRecords;//[numTables]	Table records array—one for each top-level table in the font.
    }TableDirectory

    uint32_t CalcTableChecksum(uint32_t *Table, uint32_t Length){
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
    template     void ld<cmap>(cmap* f,std::ifstream* fi ){
        ld(f->version ,fi);
        ld(f->numTables ,fi);
        ld(f->encodingRecords ,fi  ,  f->numTables );
        for(int s = 0 ; s<f->numTables){
            uint16_t format; 
            fi->read(reinterpret_cast<char*>(&format), sizeof(uint16_t))
            switch(format){
                case 0 : { f->form0.format = format; ld<CMAPf0>(f->f0,fi); continue;};
                case 2 : { f->form2.format = format; ld<CMAPf2>(f->f2,fi); continue;};
                case 4 : { f->form4.format = format; ld<CMAPf4>(f->f4,fi); continue;};
                case 6 : { f->form6.format = format; ld<CMAPf6>(f->f6,fi); continue;};
                case 8 : { f->form8.format = format; ld<CMAPf8>(f->f8,fi); continue;};
                case 10 :{ f->form10.format = format; ld<CMAPf10>(f->f10,fi); continue;};
                case 12 :{ f->form12.format = format; ld<CMAPf12>(f->f12,fi); continue;}; 
                case 13 :{ f->form13.format = format; ld<CMAPf13>(f->f13,fi); continue;}; 
                case 14 :{ f->from14.format = format; ld<CMAPf14>(f->f14,fi); continue;}; 
            };
      
        };

    };
    template     void ld<COLR>(COLR* f, std::ifstream* fi){
        uint16_t version ;
        ld(&version,fi);
        
        switch(version){
            case 0 : { f->colr.v0.version = version; ld(f->colr.v1,fi);break;}
            case 1 : { f->colr.v1.version = version; ld(f->colr.v1,fi);break;}
        };

    };
    template<>
    void ld<head>(head* f,std::ifstream fi);
    template<>
    void ld<hhea>(hhea* f,std::ifstream*  fi);
    template<>
    void ld<hmtx>(hmtx* f,std::ifstream*  fi);
    template<>
    void ld<maxp>(maxp* f,std::ifstream*  fi);
    template<>
    void ld<name>(name* f,std::ifstream*  fi);
    template<>
    void ld<cvt>(cvt* f,std::ifstream*  fi);
    template<>
    void ld<fpgm>(fpgm* f,std::ifstream*  fi);
    template<>
    void ld<glyf>(glyf* f,std::ifstream*  fi);
    template<>
    void ld<loca>(loca* f,std::ifstream*  fi);
    template     void ld<post>(post* f, std::ifstream* fi){

    };

    glyf getCharGlyf(font* f , char c){
        f->carmap.
        glyf _glyf ; 
        return _glyf;
    };
    glyf wcharGlyf(font* f, wchar_t c){

    };

    template     void ld<font>( font* f, std::ifstream* fi) {
        
        ld(&(f->td),sizeof(f->td),fi;
        ld(&(f->tr),fi,sizeof(f->tr[0]) * f->td->numtables));
        for(int i = 0 ; i < f->td.numTables;i++){
            switch(f->tr[i].tableTag){
                case font_tag("cmap") : {ld<cmap>(f->table[i]._cmap, fi ); continue;}; 
                case font_tag("head") : {ld<head>(f->table[i]._head, fi ); continue;};
                case font_tag("hhea") : {ld<hhea>(f->table[i]._hhea, fi ); continue;};
                case font_tag("hmtx") : {ld<hmtx>(f->table[i]._hmtx, fi ); continue;};
                case font_tag("maxp") : {ld<maxp>(f->table[i]._maxp, fi ); continue;};
                case font_tag("name") : {ld<name>(f->table[i]._name, fi ); continue;};
                case font_tag("cvt ") : {ld<cvt>(f->table[i]._cvt, fi ); continue;};
                case font_tag("fpgm") : {ld<fpgm>(f->table[i]._fpgm, fi ); continue;};
                case font_tag("glyf") : {ld<glyf>(f->table[i]._glyf, fi ); continue;};
                case font_tag("loca") : {ld<loca>(f->table[i]._loca, fi ); continue;};
            };
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