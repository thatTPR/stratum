#ifndef FTSBIX_HPP
#define FTSBIX_HPP
#include "maxp.hpp"

typedef struct {
    int16	originOffsetX ;//	The horizontal (x-axis) position of the left edge of the bitmap graphic in relation to the glyph design space origin.
    int16	originOffsetY ;//	The vertical (y-axis) position of the bottom edge of the bitmap graphic in relation to the glyph design space origin.
    Tag	graphicType ;//	Indicates the format of the embedded graphic data: one of 'jpg ', 'png ' or 'tiff', or the special format 'dupe'.
    uint8*	data;	//The actual embedded graphic data. The total length is inferred from sequential entries in the glyphDataOffsets array and the fixed size (8 bytes) of the preceding fields.

}glyphData;
const size_t gds= sizeof(int16)*2 + sizeof(Tag);
ACQRES(glyphData){
       one(f.originOffsetX);
        one(f.originOffsetY);
        one(f.graphicType);
        arr(f.data,gds);
};  
USE_ACQRES(glyphData)
typedef struct 
{
    uint16	ppem;//	The PPEM size for which this strike was designed.
    uint16	ppi;//	The device pixel density (in PPI) for which this strike was designed. (E.g., 96 PPI, 192 PPI.)
    Offset32*	glyphDataOffsets;//[numGlyphs+1]	Offset from the beginning of the strike data header to bitmap data for an individual glyph ID.
}strike;
size_t strikeSize ;
ACQRES(strike){
    one(f.ppem);
    one(f.ppi);
    int16_t gdos=_numGlyps+1;
    arr(f.glyphDataOffsets,gdos);

}
USE_ACQRES(strike)

typedef struct {
uint16   version;
uint16   flags;
uint32   numStrikes;
Offset32*   strikeOffsets;//[numStrikes]

strike* strikes;
glyphData* gd;
}sbixHeader;
ACQRES(sbixHeader){
one(f.version);
one(f.flags);
one(f.numStrikes);
arr(f.strikeOffsets, f.numStrikes);
if(!f.strikes){f.strikes=new strike[f.numStrikes];};
size_t gdSize =f.numStrikes * (_numGlyphs+1); 
if(!f.gd){f.gd=new glyphData[gdSize];};
for(int i=0;i<f.numStrikes-1;i++){
    offone(f.strikes[i],f.strikeOffsets[i]);
    strikeSize+=f.strikeOffsets[i+1]-f.strikeOffsets[i];
    for(int j =1;j<_numGlyphs+1;j++){
        gds= f.strikes[i].glyphDataOffsets[j] - strikes[i].glyphDataOffsets[j-1] - sizeof(int16) *2 - sizeof(Tag);
        offone(f.gd[i*(_numGlyphs+1)+j-1],f.strikes[i].glyphDataOffsets[j-1]);
    }
        
};
};
USE_ACQRES(sbixHeader)

