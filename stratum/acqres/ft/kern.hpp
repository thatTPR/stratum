#ifndef FTKERN_HPP
#define FTKERN_HPP
#include "_fontTableCommon.hpp"
#include <algorithm>
typedef struct {
uint16   left;
uint16   right;
FWORD   value;
}KernPair;

bool cmp(KernPair& l,KernPair& r){
        uint32 lhs = l.left<<16 +l.right;
        uint32 rhs = r.left<<16 +r.right;
        return lhs<rhs;
};

typedef struct {
uint16   nPairs;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
KernPair*   kernPairs;//[nPairs]
void sort(){
    
    bool b =true;
    while(b){b=false;
        for(int i=0;i<nPairs;i++){
            if(!cmp(kernPairs[nPairs-2-i],kernPairs[nPairsi-1-i])){
                KernPair tmp;
                tmp = kernPairs[nPairs-2-i];kernPairs[nPairs-2-i]=kernPairs[nPairs-1-i];kernPairs[nPairs-1-i]=tmp;
                b =true;
            }
            if(!cmp(kernPairs[i],kernPairs[i+1])){
                KernPair tmp;
                tmp = kernPairs[i];kernPairs[i]=kernPairs[i+1];kernPairs[i+1]=tmp;
                b =true;
            }
        }
    };
   
};
}KernSubtableFormat0;
ACQRES(KernSubtableFormat0){
one(f.nPairs);
one(f.searchRange);
one(f.entrySelector);
one(f.rangeShift);
arr(f.kernPairs, f.nPairs);
 };
USE_ACQRES(KernSubtableFormat0)


typedef struct {
uint16	firstGlyph ;//	First glyph in class range.
uint16	nGlyphs ;//	Number of glyph in class range.
uint16* classValue;
}kernClassHead;
ACQRES(kernClassHead){
    one(f.firstGlyph);
    one(f.nGlyphs);
    arr(f.classValue,f.nGlyphs);
}
USE_ACQRES(kernClassHead)
typedef struct {
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
    one(f.length);
    one(f.coverage);
    switch(f.version){
        case 0 : {one(f.f.f0);};
        case 2 : {one(f.f.f2);};
    }
    f.length =size(f);
}
USE_ACQRES(KernSub)
typedef struct {
uint16   version;
uint16   nTables;
KernSub* s;
    int16 getPair(uint16 gid ,uint16 gid2 ){
        KenrPair p ;p.left=gid;p.right=gid2;
        for(int i=0;i<nTables;i++){
            switch(s[i].version){
                case 0 :{                
                int n=s[i].f0.nPairs/2;int i=0;
                for(int j=s[i].f0.nPairs/2;i<s[i].f0.entrySelector,;i++){
                if(s[i].f0.kernPairs[j].left==gid and s[i].f0.kernPairs[j].right==gid2){
                    return s[i].f0.kernPairs[j].nGlyphs;};
                n=n/2;
                    if(s[i].f0.kernPairs[j].left < gid ){
                        j+=n;
                    }
                    else if(s[i].f0.kernPairs[j].left==gid) {
                        if(s[i].f0.kernPairs[j].right<gid2){
                            j+=n;
                        }
                        else {j-=n;}
                    }
                    else {j-=n;};
                }
            }};
            case 2 : {
                uint16 lg ;
                    if(s[i].f2.leftClass.firstGlyph<= gid){
                        uint16 dif = gid - s[i].f2.leftClass.firstGlyph;
                        if(dif < s[i].f2.leftClass.nGlyphs){
                            lg=s[i].f2.leftClass.classValue[dif];
                        }
                        else {
                            continue;
                        };};

                uint16 rg ;
               if(s[i].f2.rightClass.firstGlyph<= gid2){
                        uint16 dif = gid - s[i].f2.rightClass.firstGlyph;
                        if(dif < s[i].f2.rightClass.nGlyphs){
                            lg=s[i].f2.rightClass.classValue[dif];
                        }
                        else {
                            continue;
                        };};
                return *(s[i].f2.kerningArray + lg + rg); 
            }
        };
        return 0;
    };
}kern;
ACQRES(kern){
    one(f.version);
    one(f.nTables);
    arr(f.s,f.ntables);   
}
USE_ACQRES(kern)

#endif