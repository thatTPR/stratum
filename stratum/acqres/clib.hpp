#ifndef CLIB_HPP
#define CLIP_HPP

#include <lib/zlib-1.3.1/zlib.h>
#include <cstdint>
// DEFLATE
#include <string>

lzw_encode(char* src,size_t l, char* dest, size_t* destlen ){
    std::string s;
    int lastSym;
    for(int i=0;i<l;i++){
        size_t p = s.findstr(std::string(src[i]));
        if(p!=std::string::npos){lastsym=i;
            s+=std::string(src[i]);
        };  
    };
    
}
lzw_decode(char* src,size_t l, char* dest,size_t* destLen){

};
#endif