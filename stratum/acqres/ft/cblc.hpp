#ifndef FTCBLC_HPP
#define FTCBLC_HPP
#include "eblc.hpp"
#include "ebdt.hpp"


typedef EBLC<true> CBLC;
ACQRES(CBLC){
one(f.majorVersion);
one(f.minorVersion);
one(f.numSizes);
arr(f.bitmapSizes, f.numSizes);
if(!f.indexSubtableLists){f.indexSubtableLists = new IndexSubtableList[f.numSizes];};
size_t s =0;
for(int i=0;i<f.numSizes;i++){
    s+=f.bitmapSizes[i].indexSubtableListSize;
    offarr(f.indexSubtableLists[i],f.bitmapSizes[i].indexSubtableListOffset,f.bitmapSizes[i].indexSubtableListSize);
};
if(!f.indexSubtables){f.indexSubtables= new IndexSubtable[s];};indexSubtablesSize =s;
int k=0;
for(int i=0;i<f.numSizes;i++){
    for(int j=0;j<f.bitmapSizes[i].indexSubtableListSize;j++){
        _numOffsets = f.indexSubtableLists[i][j].lastGlyphIndex-f.indexSubtableLists[i][j].firstGlyphIndex + 2;
        offone(f.indexSubtables[k],f.indexSubtableLists[i][j].indexSubtableOffset);
        k++;
    };
}
 };
USE_ACQRES(CBLC)


}

#endif