#ifndef FTPREP_HPP
#define FTPREP_HPP
typedef struct {
uint8* val;	//Set of instructions executed whenever point size or font or transformation change. n is the number of uint8 items that fit in the size of the table.
}prep;
ACQRES(prep){
    arr(val,_length);
}
USE_ACQRES(prep)
#endif