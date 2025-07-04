
typedef struct {
    // Version16Dot16	version ;//	0x00010000 for version 1.0.
    // uint16	numGlyphs ;//	The number of glyphs in the font.
    uint16	maxPoints ;//	Maximum points in a non-composite glyph.
uint16	maxContours ;//	Maximum contours in a non-composite glyph.
uint16	maxCompositePoints ;//	Maximum points in a composite glyph.
uint16	maxCompositeContours ;//	Maximum contours in a composite glyph.
uint16	maxZones ;//	1 if instructions do not use the twilight zone (Z0), or 2 if instructions do use Z0; should be set to 2 in most cases.
uint16	maxTwilightPoints ;//	Maximum points used in Z0.
uint16	maxStorage ;//	Number of Storage Area locations.
uint16	maxFunctionDefs ;//	Number of FDEFs, equal to the highest function number + 1.
uint16	maxInstructionDefs ;//	Number of IDEFs.
uint16	maxStackElements ;//	Maximum stack depth across Font Program ('fpgm' table), CVT Program ('prep' table) and all glyph instructions (in the 'glyf' table).
uint16	maxSizeOfInstructions ;//	Maximum byte count for glyph instructions.
uint16	maxComponentElements ;//	Maximum number of components referenced at “top level” for any composite glyph.
uint16	maxComponentDepth ;//	Maximum levels of recursion; 1 for simple components.
}version10;
    uint16	_numGlyphs ;
typedef struct {
    Version16Dot16	version ;//	0x00005000 for version 0.5
    uint16	numGlyphs ;//	The number of glyphs in the font.

    version10 v10;
}maxp;
ACQRES(maxp){
    one(f.version);
    one(f.numGlyphs);
    _numGlyphs = numGlyphs
    if(f.version ==0x00010000){one(f.v10);}
}
USE_ACQRES(maxp)