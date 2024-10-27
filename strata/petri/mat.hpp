#pragma once
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif
template <typename T, size_t r, size_t c  >
class mat {
    T[r][c] d ;
    inline virtual void transpose(){

    };
    inline virtual void inverse(){

    };
   
};