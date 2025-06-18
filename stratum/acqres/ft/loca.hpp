typedef struct {
Offset16*   offsets;//[numGlyphs + 1]
}Short/* format*/;
ACQRES(Short/* format*/){
arr(offsets, numGlyphs + 1);
 };
USE_ACQRES(Short/* format*/)

typedef struct {
Offset32*   offsets;//[numGlyphs + 1]
}Long/* format*/;
ACQRES(Long/* format*/){
arr(offsets, numGlyphs + 1);
 };
USE_ACQRES(Long/* format*/)

