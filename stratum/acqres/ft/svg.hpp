typedef struct {
uint16   numEntries;
SVGDocumentRecord*   documentRecords;//[numEntries]
}SVGDocumentList:;
ACQRES(SVGDocumentList:){
one(numEntries);
arr(documentRecords, numEntries);
 };
USE_ACQRES(SVGDocumentList:)

typedef struct {
uint16   startGlyphID;
uint16   endGlyphID;
Offset32   svgDocOffset;
uint32   svgDocLength;
}SVGDocumentRecord:;
typedef struct {
   ;
0000   version;
0000000A   svgDocumentListOffset;
00000000   reserved;
   ;
0005   numEntries;
*   documentRecords;//[0]
0001   startGlyphID;
0001   endGlyphID;
0000003E   svgDocOffset;
0000019F   svgDocLength;
*   documentRecords;//[1]
0002   startGlyphID;
0002   endGlyphID;
000001DD   svgDocOffset;
000002FF   svgDocLength;
*   documentRecords;//[2]
0003   startGlyphID;
000C   endGlyphID;
000004DC   svgDocOffset;
000006F4   svgDocLength;
*   documentRecords;//[3]
000D   startGlyphID;
000E   endGlyphID;
000001DD   svgDocOffset;
000002FF   svgDocLength;
*   documentRecords;//[4]
000F   startGlyphID;
0013   endGlyphID;
00000BD0   svgDocOffset;
00000376   svgDocLength;
}Example/* 1:*/;
ACQRES(Example/* 1:*/){
one();
one(version);
one(svgDocumentListOffset);
one(reserved);
one();
one(numEntries);
arr(documentRecords, 0);
 one(startGlyphID);
one(endGlyphID);
one(svgDocOffset);
one(svgDocLength);
arr(documentRecords, 1);
 one(startGlyphID);
one(endGlyphID);
one(svgDocOffset);
one(svgDocLength);
arr(documentRecords, 2);
 one(startGlyphID);
one(endGlyphID);
one(svgDocOffset);
one(svgDocLength);
arr(documentRecords, 3);
 one(startGlyphID);
one(endGlyphID);
one(svgDocOffset);
one(svgDocLength);
arr(documentRecords, 4);
 one(startGlyphID);
one(endGlyphID);
one(svgDocOffset);
one(svgDocLength);
};
USE_ACQRES(Example/* 1:*/)

