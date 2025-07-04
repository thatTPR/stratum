#ifndef CVT_HPP
#define CVT_HPP

typedef struct {
    FWORD* items;
}cvt;
ACQRES(cvt){
    arr((f.items),_sizeTable/2)
}
#endif