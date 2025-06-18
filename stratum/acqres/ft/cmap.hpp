typedef struct {
uint16   version;
uint16   numTables;
EncodingRecord*   encodingRecords;//[numTables]
}cmap'/* Header:*/;
ACQRES(cmap'/* Header:*/){
one(version);
one(numTables);
arr(encodingRecords, numTables);
 };
USE_ACQRES(cmap'/* Header:*/)

typedef struct {
uint16   platformID;
uint16   encodingID;
Offset32   subtableOffset;
}EncodingRecord:;
typedef struct {
uint16   format;
uint16   length;
uint16   language;
uint8*   glyphIdArray;//[256]
}cmap'/* Subtable Format 0:*/;
ACQRES(cmap'/* Subtable Format 0:*/){
one(format);
one(length);
one(language);
arr(glyphIdArray, 256);
 };
USE_ACQRES(cmap'/* Subtable Format 0:*/)

typedef struct {
uint16   format;
uint16   length;
uint16   language;
uint16*   subHeaderKeys;//[256]
SubHeader*   subHeaders;//[ ]
uint16*   glyphIdArray;//[ ]
}cmap'/* Subtable Format 2:*/;
ACQRES(cmap'/* Subtable Format 2:*/){
one(format);
one(length);
one(language);
arr(subHeaderKeys, 256);
 arr(subHeaders,  );
 arr(glyphIdArray,  );
 };
USE_ACQRES(cmap'/* Subtable Format 2:*/)

typedef struct {
uint16   firstCode;
uint16   entryCount;
int16   idDelta;
uint16   idRangeOffset;
}SubHeader/* Record:*/;
typedef struct {
uint16   format;
uint16   length;
uint16   language;
uint16   segCountX2;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
uint16*   endCode;//[segCount]
uint16   reservedPad;
uint16*   startCode;//[segCount]
int16*   idDelta;//[segCount]
uint16*   idRangeOffset;//[segCount]
uint16*   glyphIdArray;//[ ]
}cmap'/* Subtable Format 4:*/;
ACQRES(cmap'/* Subtable Format 4:*/){
one(format);
one(length);
one(language);
one(segCountX2);
one(searchRange);
one(entrySelector);
one(rangeShift);
arr(endCode, segCount);
 one(reservedPad);
arr(startCode, segCount);
 arr(idDelta, segCount);
 arr(idRangeOffset, segCount);
 arr(glyphIdArray,  );
 };
USE_ACQRES(cmap'/* Subtable Format 4:*/)

typedef struct {
uint16   format;
uint16   length;
uint16   language;
uint16   firstCode;
uint16   entryCount;
uint16*   glyphIdArray;//[entryCount]
}cmap'/* Subtable Format 6:*/;
ACQRES(cmap'/* Subtable Format 6:*/){
one(format);
one(length);
one(language);
one(firstCode);
one(entryCount);
arr(glyphIdArray, entryCount);
 };
USE_ACQRES(cmap'/* Subtable Format 6:*/)

typedef struct {
uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint8*   is32;//[8192]
uint32   numGroups;
SequentialMapGroup*   groups;//[numGroups]
}cmap'/* Subtable Format 8:*/;
ACQRES(cmap'/* Subtable Format 8:*/){
one(format);
one(reserved);
one(length);
one(language);
arr(is32, 8192);
 one(numGroups);
arr(groups, numGroups);
 };
USE_ACQRES(cmap'/* Subtable Format 8:*/)

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   startGlyphID;
}SequentialMapGroup/* Record:*/;
typedef struct {
uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   startCharCode;
uint32   numChars;
uint16   glyphIdArray;
}cmap'/* Subtable Format 10:*/;
typedef struct {
uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   numGroups;
SequentialMapGroup*   groups;//[numGroups]
}cmap'/* Subtable Format 12:*/;
ACQRES(cmap'/* Subtable Format 12:*/){
one(format);
one(reserved);
one(length);
one(language);
one(numGroups);
arr(groups, numGroups);
 };
USE_ACQRES(cmap'/* Subtable Format 12:*/)

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   startGlyphID;
}SequentialMapGroup/* Record:*/;
typedef struct {
uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   numGroups;
ConstantMapGroup*   groups;//[numGroups]
}cmap'/* Subtable Format 13:*/;
ACQRES(cmap'/* Subtable Format 13:*/){
one(format);
one(reserved);
one(length);
one(language);
one(numGroups);
arr(groups, numGroups);
 };
USE_ACQRES(cmap'/* Subtable Format 13:*/)

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   glyphID;
}ConstantMapGroup/* Record:*/;
typedef struct {
uint16   format;
uint32   length;
uint32   numVarSelectorRecords;
VariationSelector*   varSelector;//[numVarSelectorRecords]
}cmap'/* Subtable Format 14:*/;
ACQRES(cmap'/* Subtable Format 14:*/){
one(format);
one(length);
one(numVarSelectorRecords);
arr(varSelector, numVarSelectorRecords);
 };
USE_ACQRES(cmap'/* Subtable Format 14:*/)

typedef struct {
uint24   varSelector;
Offset32   defaultUVSOffset;
Offset32   nonDefaultUVSOffset;
}VariationSelector/* Record:*/;
typedef struct {
uint32   numUnicodeValueRanges;
UnicodeRange*   ranges;//[numUnicodeValueRanges]
}DefaultUVS/* Table:*/;
ACQRES(DefaultUVS/* Table:*/){
one(numUnicodeValueRanges);
arr(ranges, numUnicodeValueRanges);
 };
USE_ACQRES(DefaultUVS/* Table:*/)

typedef struct {
uint24   startUnicodeValue;
uint8   additionalCount;
}UnicodeRange/* Record:*/;
typedef struct {
uint32   numUVSMappings;
UVSMapping*   uvsMappings;//[numUVSMappings]
}NonDefaultUVS/* Table:*/;
ACQRES(NonDefaultUVS/* Table:*/){
one(numUVSMappings);
arr(uvsMappings, numUVSMappings);
 };
USE_ACQRES(NonDefaultUVS/* Table:*/)

typedef struct {
uint24   unicodeValue;
uint16   glyphID;
}UVSMapping/* Record:*/;
