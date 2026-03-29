#ifndef STM_IMAGE_HPP
#define STM_IMAGE_HPP
#include "image/stm.hpp"
mod::image2D StmLoadImage(std::string name){
    // 
    size_t pos = name.find_last_of(".");
    if(pos!=std::string::npos){
        std::string s = name.substr(pos+1,10);
        switch(s){
            case std::string("png"):{png i ;return i.ld(name); } 
            case std::string("tga"):{tga i ; return i.ld(name);}
            case std::string("bmp"):{bmp i;return i.ld(name)}
            case std::string("jpeg"):{bmp i;return i.ld(name)}
            case std::string("jpeg"):{jpeg i;return i.ld(name)}
            case std::string("jpg"):{jpeg i;return i.ld(name)}
        }
    }
};

#include "image/png.hpp"
#include "image/tga.hpp"
#include "image/bmp.hpp"
#include "image/jpeg.hpp"
#include "image/gif.hpp"

#endif