#ifndef FTKERN_HPP
#define FTKERN_HPP
#include "_fontTableCommon.hpp"
typedef struct {
uint16   left;
uint16   right;
FWORD   value;
}KernPair/* record*/;


typedef struct {
uint16   nPairs;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
KernPair*   kernPairs;//[nPairs]
}KernSubtableFormat0;
ACQRES(KernSubtableFormat0){
one((f.nPairs));
one((f.searchRange));
one((f.entrySelector));
one((f.rangeShift));
arr(f.kernPairs, f.nPairs);
 };
USE_ACQRES(KernSubtableFormat0)


typedef struct {
uint16	firstGlyph ;//	First glyph in class range.
uint16	nGlyphs ;//	Number of glyph in class range.
ClassDef classDef;
}kernClassHead;
ACQRES(kernClassHead){
    one(f.firstGlyph);
    one(f.nGlyphs);
    one(f.classDef);
}
USE_ACQRES(kernClassHead)
typedef struct { // TODO maybe check offset dtypes
uint16   rowWidth;
Offset16   leftClassOffset;
Offset16   rightClassOffset;
Offset16   kerningArrayOffset;
/// @brief
kernClassHead leftClass ; 
kernClassHead rightClass ; 
FWORD* kerningArray;
}KernSubtableFormat2;
ACQRES(KernSubtableFormat2){
    one(f.rowWidth);
    one(f.leftClassOffset);
    one(f.rightClassOffset);
    one(f.kerningArrayOffset);
    offone(f.leftClass,f.leftClassOffset);
    offone(f.rightClass,f.rightClassOffset);
    offarr(f.kerningArray,f.kerningArrayOffset,f.rowWidth);
}
USE_ACQRES(KernSubtableFormat2)
enum KernCoverage {
horizontal =	0,//	1 if table has horizontal data, 0 if vertical.
minimum =	1,//	
cross_stream=2,//
override =	3,//	If this bit is set to 1 the value in this table should replace the value currently being accumulated.
reserved =4,//4-7	Reserved—set to zero.
format=	8//8-15	Format of the subtable. Only formats 0 and 2 have been defined. Formats 1 and 3 through 255 are reserved for future use.
};
typedef struct {
    
uint16	version ;//	Kern subtable version number—set to 0.
uint16	length ;//	Length of the subtable, in bytes (including this header).
uint16	coverage ;//	What type of information is contained in this table.

union {
    KernSubtableFormat0 f0;
    KernSubtableFormat2 f2;
}f;

}KernSub;
ACQRES(KernSub){
    one(f.version);
    one(f.llength);
    one(f.coverage);
    switch(f.version){
        case 0 : {one(f.f.f0);};
        case 2 : {one(f.f.f2);};
    }

}
USE_ACQRES(KernSub)
typedef struct {
uint16   version;
uint16   nTables;
KernSub* s;

}kern;
ACQRES(kern){
    one(f.version);
    one(f.nTables);
    arr(f.s,f.ntables);   
}
USE_ACQRES(kern)

#endif