#ifndef CVT_HPP
#define CVT_HPP

typedef struct {
    FWORD* items;
}cvt;
ACQRES(cvt){
    uint16 sizeTable=_length/2
    arr(f.items,sizeTable);
}
#endif