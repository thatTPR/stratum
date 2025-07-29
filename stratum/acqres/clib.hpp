#include <cstdint>
#define ZFAST_BITS 9
struct zlibHuffman {
   uint16_t fast[1 << ZFAST_BITS];
   uint16_t firstcode[16];
   int maxcode[17];
   uint16_t firstsymbol[16];
   unsigned char  size[288];
   uint16_t value[288];
}

struct zlib_buf {
   unsigned char *zbuffer, *zbuffer_end;
   int num_bits;
   uint32_t code_buffer;

   char *zout;
   char *zout_start;
   char *zout_end;
   int   z_expandable;

    z_length, z_distance;
}

template <typename T>
zlib_buf buildHuffman(T* data,size_t symbol, size_t s ){
    zlib_buf buf;
    zlib_buf buf; 
};



template <size_t s>
struct integral_sized {
    using t= 
    std::conditional<s==1,uint8_t,
    std::conditional<(s==2),uint16_t,
    std::condtional<s<=4,uint32_t,uint32_t>::type>::type>::type ;
    
}

void rle_encode(size_t byten,void* src,size_t Size,void* dest,void (*copy)(void* , size_t )){

};

void rle_decode(size_t byten,void* src,size_t Size,void* dest, void (*copy)(void* , size_t )){
    

    for(int i=0;i<Size;i++){

    };
};
