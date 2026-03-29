#ifndef FTSVG_HPP
#define FTSVG_HPP


typedef struct {
uint16   startGlyphID;
uint16   endGlyphID;
Offset32   svgDocOffset;
uint32   svgDocLength;
}SVGDocumentRecord:;



typedef struct {
uint16   numEntries;
SVGDocumentRecord*   documentRecords;//[numEntries]

uint8** svgDocs ;//[numEntries]
}SVGDocumentList;
ACQRES(SVGDocumentList:){
one((f.numEntries));
arr(f.documentRecords, f.numEntries);
offmany(f.svgDocs,f.svgDocOffsets,f.numEntries);
 };
USE_ACQRES(SVGDocumentList:)

typedef struct {
uint16	version ;//	Table version (starting at 0). Set to 0.
Offset32	svgDocumentListOffset ;//	Offset to the SVGDocumentList, from the start of the SVG table. Must be non-zero.
uint32	reserved ;//	Set to 0.
SvgDocumentList svgDocumentList;
}SVG;
ACQRES(SVG){
   one(f.version);
   one(f.svgDocumentListOffset);
   one(f.reserved);
   offone(f.svgDocumentList,f.svgDocumentListOffset);
}
USE_ACQRES(SVG)


#endif
