typedef struct {
32 to 246   -107 to 107;
247 to 250   108 to 1131;
251 to 254   -1131 to -108;
28   -32768 to 32767;
255   -32768 to (32768 - 1/65536);
29   -(2^31) to (2^31 - 1);
30   any real number;
}Numerical/* value encoding*/;
typedef struct {
uint32   count;
uint8   offsetSize;
Offset8  Offset16  Offset24  Offset32*   offsets;//[count+1]
uint8   data;
}INDEX/* table*/;
ACQRES(INDEX/* table*/){
one(count);
one(offsetSize);
arr(offsets, count+1);
 one(data);
};
USE_ACQRES(INDEX/* table*/)

typedef struct {
uint8   majorVersion;
uint8   minorVersion;
uint8   headerSize;
uint16   topDICTSize;
}CFF2/* Header*/;
typedef struct {
uint8   format;
uint8*   fontDICTIDs;//[numGlyphs]
}FontDICTSelectFormat0/* table*/;
ACQRES(FontDICTSelectFormat0/* table*/){
one(format);
arr(fontDICTIDs, numGlyphs);
 };
USE_ACQRES(FontDICTSelectFormat0/* table*/)

typedef struct {
uint8   format;
uint16   numRanges;
Range3*   ranges;//[numRanges]
uint16   sentinel;
}FontDICTSelectFormat3/* table*/;
ACQRES(FontDICTSelectFormat3/* table*/){
one(format);
one(numRanges);
arr(ranges, numRanges);
 one(sentinel);
};
USE_ACQRES(FontDICTSelectFormat3/* table*/)

typedef struct {
uint16   first;
uint8   fontDICTID;
}Range3/* record*/;
typedef struct {
uint8   format;
uint32   numRanges;
Range4*   ranges;//[numRanges]
uint32   sentinel;
}FontDICTSelectFormat4/* table*/;
ACQRES(FontDICTSelectFormat4/* table*/){
one(format);
one(numRanges);
arr(ranges, numRanges);
 one(sentinel);
};
USE_ACQRES(FontDICTSelectFormat4/* table*/)

typedef struct {
uint32   first;
uint16   fontDICTID;
}Range4/* record*/;
typedef struct {
uint16   length;
uint8*   data;//[length]
}VariationStore/* table*/;
ACQRES(VariationStore/* table*/){
one(length);
arr(data, length);
 };
USE_ACQRES(VariationStore/* table*/)

