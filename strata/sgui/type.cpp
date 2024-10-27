#include <map>
#include <filesystem>
#ifdef TYPE_STB
#include <stb/stb_truetype.h> 
#elifdef TYPE_FREETYPE
#include <freetype/freetype.h>
#endif

using namespace std ;

typedef enum styling {
    Bold= 0b0001, 
    Italic=0b0010,
    Underline=0b0100,
    Strikethrough=0b1000 , 
} styling ;

template<typename fontinfo>
class type_manager {
    public: 
    typedef 
    std::map<std::path , fontinfo> fonts ;
    virtual getFontInfo(fontinfo* fontinf, std::path fontPath, ){

    };
    virtual fontBitMap bake_fontbitmap(std::string font , fontinfo font ,styling flags ){

    };
    virtual int bake_
};
#ifdef TYPE_STB
#include "stb/stb_truetype.h"
class type_manager_stb {
    std::map<std::path , std::  > ;
};

};
#endif

#ifdef TYPE_FREETYPE
#include "freetype/freetype.h"

class type_manager_frtp {
    
};
#endif
