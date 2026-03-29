/*

Initial byte b0	 |    Value range	          | Value calculation	        |   Size in bytes  | Usage
--------------------------------------------------------------------------------------------------------
32 to 246	     |    -107 to 107	          | b0 - 139	                |       1	       |both
247 to 250	     |    108 to 1131	          | (b0 - 247) * 256 + b1 + 108	|       2	       |both
251 to 254	     |    -1131 to -108           | -(b0 - 251) * 256 - b1 - 108|   	2	       |both
28               |    -32768 to 32767         |	interpret b1 and b2 as int16|   	3	       |both
255	             |-32768 to (32768 - 1/65536) |	interpret b1 to b4 as Fixed	|       5	       |CharString only
29	             |-(2^31) to (2^31 - 1)	      | interpret b1 to b4 as int32	|       5	       |DICT only
30	             | any real number	          |  following bytes are	    |    unlimited     |DICT only
                                              | binary coded decimal (see below)|
                                              
Nibble value  |	Nibble (hex) |	Represents in ASCII
0 to 9	      |     0 to 9	 |       0 to 9
10	          |      a	     |   . (decimal point)
11	          |      b	     |   E
12	          |      c	     |   E-
13	          |      d	     |   (reserved)
14	          |      e	     |   - (minus)
15	          |      f	     |   end of number                                           
                                              

                                              */  
typedef struct {
uint32   count;
uint8   offsetSize;
union u{
    Offset8* Off8;
    Offset16* Off16;
    Offset24* Off24;
    Offset32* Off32;    
};
u   offsets;//[count+1]
uint8*   data;//[variable]
}INDEX;
ACQRES(INDEX){
one(f.count);
one(f.offsetSize);
uint8 count = f.count+1;
uint32 length;
switch(f.offsetSize){
    case 1 : {arr(f.offsets.Off8, count);length=f.offsets.Off8-1;}
    case 2 : {arr(f.offsets.Off16, count);length=f.offsets.Off16-1;}
    case 3 : {arr(f.offsets.Off24, count);length=f.offsets.Off24-1;}
    case 4 : {arr(f.offsets.Off32, count);length=f.offsets.Off32-1;}
};
 arr(f.data,length);
};
USE_ACQRES(INDEX)

typedef struct {
// uint8   format;
uint8*   fontDICTIDs;//[numGlyphs]
}FontDICTSelectFormat0/* table*/;
ACQRES(FontDICTSelectFormat0/* table*/){
one(f.format);
arr(f.fontDICTIDs, _numGlyphs);
 };
USE_ACQRES(FontDICTSelectFormat0/* table*/)
typedef struct {
uint16   first;
uint8   fontDICTID;
}Range3/* record*/;

typedef struct {
// uint8   format;
uint16   numRanges;
Range3*   ranges;//[numRanges]
uint16   sentinel;
}FontDICTSelectFormat3/* table*/;
ACQRES(FontDICTSelectFormat3/* table*/){
one(f.format);
one(f.numRanges);
arr(f.ranges, f.numRanges);
 one(f.sentinel);
};
USE_ACQRES(FontDICTSelectFormat3/* table*/)

typedef struct {
uint32   first;
uint16   fontDICTID;
}Range4/* record*/;

typedef struct {
// uint8   format;
uint32   numRanges;
Range4*   ranges;//[numRanges]
uint32   sentinel;
}FontDICTSelectFormat4/* table*/;
ACQRES(FontDICTSelectFormat4/* table*/){
one(f.format);
one(f.numRanges);
arr(f.ranges, f.numRanges);
 one(f.sentinel);
};
USE_ACQRES(FontDICTSelectFormat4/* table*/)

struct FontDICTSelectFormat {
    uint8 format;
    union {
        FontDICTSelectFormat0 f0; 
        FontDICTSelectFormat3 f2;
        FontDICTSelectFormat4 f4;
    }u;
}
enum TopDictOperator{
CharStringINDEXOffset=0x11, VariationStoreOffset=0x18,
FontDICTINDEXOffset=0x0c,FontDICTINDEXOffsetEnd=0x24
FontDICTSelectOffset=0x0c, FontDICTSelectOffset=0x25
//Numeric operands are encoded as binary coded decimal. 
// Specifies the scale factor for glyph coordinates within the em square,
//  similar to the unitsPerEm field in the 'head' table.
//  However, a reciprocal value is used (thus 1 / unitsPerEm). 
// This value occurs as the first and fourth operands—both scale operands must have the same value
//. Other operands must be zero.
FontMatrix=0x0c 0x07,
}
struct DICT {

};
typedef struct {
uint16   length;
uint8*   data;//[length]
}VariationStore;
ACQRES(VariationStore){
one(f.length);
arr(f.data, f.length);
 };
USE_ACQRES(VariationStore)

typedef struct {
uint8   majorVersion;
uint8   minorVersion;
uint8   headerSize;
uint16   topDICTSize;

DICT topDict;
}CFF2;
ACQRES(CFF2){
one(f.majorVersion);
one(f.minorVersion);
one(f.headerSize);
one(f.topDICTSize); 
one(f.topDict);  
}