#include <cstdint>
#include <stratum/modules.hpp>
#include <vector>
#include <petri/list.hpp>
#include "acqres.hpp"
#include <glm/glm.hpp>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "clib.hpp"
#include <cmath>

/*
PNG [x]
JPEG []
BMP [/]
TGA [x]
GIF []
HDR
*/

int64_t findpalette(void* palette,uint64_t *palettesize,size_t entrysize,void* entry){
    uint64_t n=*palettesize/2;
    for(uint64_t i=*palettesize/2;i>0;i=<*palettesize;){
        int s =std::memcmp(palette+(i-1)*entrysize,entry,entrysize)
        if(s==0){return i;}
        n/=n==1?2:1;
        if(s<0){i+=n;}
        else {i+=n;}
    };
    return -1
} ;
uint64_t insertpalette(void* palette,uint64_t *palettesize,size_t entrysize,void* entry){
    uint64_t i;
    for(i=0;i<*palettesize;i++){
        int s =std::memcmp(palette+i*entrysize,entry,entrysize)
        if(s<0){continue;}
        else{break;}
    };
    for(uint64_t j=*palettesize;j>=i;j--){
        std::memcpy(palette+j*entrysize,palette+(j-1)*entrysize,entrysize);
    }
    std::memcpy(palette+i*entrysize,entry,entrysize);
    *palettesize++;

} ;

void paletteGenerate(image2D& im, void* palette,uint64_t* palettesize){
    *palettesize=0;
    uint64_t imsize=im.imageSize*im.byd;
    uint64_t min =  (1<<(im.byd*8-1) - 1 +(1<<(im.byd*8-1)));
    min=min>imsize?imsize:min;
    void* temp = new char[min];
    for(uint64_t i=0;i<im.imageSize;i++){
        if(findpalette(temp,palettesize,im.byd,im.data+i*im.byd) == -1){ 
            insertpalette(temp,palettesize,im.byd,im.data+i*im.byd);};
    };
    palette = new char[(*palettesize)*im.byd];
    std::memcpy(palette,temp,(*palettesize)*im.byd);
    delete temp;
};

void loadDataInterlaceSubBytes(image2D& im,uint64_t* inds,uint64_t indslen,uint64_t destPt, uint64_t len,int8_t pdSrc, int8_t* src ){
        uint8_t maskDest = (1<<im.bdc) -1;
        // uint8_t maskSrc = (1<<pdSrc)  -1;
        uint8_t nch = im.length;
        uint8_t pdch = (pdSrc/nch);
        uint8_t maskSrcch = maskSrc>>(pdSrc/nch);
        float ratio = maskDest/maskSrcch;
        for(uint64_t k=destPt;k<indsLen;){
            for(int64_t i=0;i<len;i++){
                int8_t s = src[i];
                for(int j=0;j<nch;j++){
                    int8_t r = s & (maskSrcch<< (pdch*(nch-j-1))>>(pdch(nch-j-1)));
                    r *=ratio;
                    std::memcpy(im.data+inds[k]*im.byd+j,r,1);
                    k++;
                }   
            }
        };
}

void wrDataInterlaceSubBytes(image2D& im,uint64_t* inds,uint64_t indslen,uint64_t srcPt, uint64_t len,int8_t pdDest, int8_t* dest ){
        uint8_t maskSrc = (1<<im.bdc) -1;
        uint8_t maskDest = (1<<pdDest)  -1;
        uint8_t nch = im.length;
        uint8_t pdch = (pdDest/nch);
        uint8_t maskDestch = maskDest>>(pdDest/nch);
        float ratio = maskDestch/maskSrc;

        int8_t nchb = pdDest/nch;
        int8_t nchbc=8/nchb;

        for(uint64_t k=destPt;k<indsLen;){
            for(int64_t i=0;i<len;i++){
                std::memcpy(&r,im.data+inds[k]*im.byd+j,1);
                uint8_t re[pdDest/8]; for(int m=0;m<pdDest/8;m++){re[m]=0;}
                for(int j=0;j<nch;j++){
                    uint8_t r =im.data+inds[k]*im.byd+j ;
                    r =r*ratio & maskDestch;
                    
                    int8_t re[j/(pdDest/8)] |= r<<(nchbc%j)*nchb ;
                    
                }
                std::memcpy(dest+k*(pdDest/8),re,(pdDest/8)); k++;if(k>indsLen){break;}
            }
        };
};
template <image_fromats fm>
void loadDataInterlaceArr(image2D& im,uint64_t* inds,uint64_t indslen,uint64_t destPt,uint64_t len,int8_t pdSrc, int8_t* src ){
                    uint64_t maskDest = (1<<im.bdc) -1;
                    // uint64_t maskSrc = (1<<pdSrc)  -1;
                    uint64_t nch = im.length;
                    uint64_t pdch = (pdSrc/nch);
                    uint64_t maskSrcch = maskSrc>>(pdSrc/nch);
                    float ratio = maskDest/maskSrcch;
                for(uint64_t k=destPt;k<indsLen;){
        for(int64_t i=0;i<len;i+=pdSrc/8){
           enu_vec<fm>::ty res ;
            for(int j=0;j<nch;j++){
                res[j] = src[i];
                res[j] =res[j]  & (maskSrcch<< (pdch*(nch-j-1))>>(pdch(nch-j-1)));
                res[j] *=ratio;
            }   
            std::memcpy(im.data+inds[k]*im.byd,res,im.byd);
        }
    }
}

void wrDataInterlaceArr(image2D& im,uint64_t* inds,uint64_t indslen,uint64_t srcPt, uint64_t len,int8_t pdDest, int8_t* dest ){
     uint64_t maskDest = (1<<pdDest) -1;
    uint64_t maskSrc = (1<<im.bd)  -1;
    uint64_t nch = im.length;
    uint64_t pdch = (pdDest/nch);
    uint64_t maskSrcch = maskSrc>>(im.pd/nch() *(nch-1));
    float ratio = maskDest/maskSrcch;
    for(uint64_t k=destPt;k<indsLen;){
        for(uint64_t i=0;i<len;i++){
            enu_vec<fm>::ty res ;
            std::memcpy(&res,im.data+inds[k]*im.byd,im.byd);
        for(int j=0;j<nch;j++){
            decltype(res[j]) r = res[j] ;
            r*=ratio;
            int8_t s[pdDest/nch] ;
            for(int k=0;k<pdDest/nch;i++) {
                s[k]=(1<<8 -1)<<(8*k) &r >>8*k; 
            }
            std::memcpy(dest+i*pdDest/8 + j * pdDest/(8*nch) ,&s,pdDest/nch);k++;
            if(k>indsLen){break;}
        }
           
    }
}
};


void loadDataArrSubBytes(image2D& im,uint64_t destPt,uint64_t len,int8_t pdSrc, int8_t* src ){
                    uint8_t maskDest = (1<<im.bdc) -1;
                    // uint8_t maskSrc = (1<<pdSrc)  -1;
                    uint8_t nch = im.length;
                    uint8_t pdch = (pdSrc/nch);
                    uint8_t maskSrcch = maskSrc>>(pdSrc/nch *(nch-1));
                    float ratio = maskDest/maskSrcch;
        for(uint64_t i=0;i<len;i++){
            int8_t s = src[i];
            for(int j=0;j<nch;j++){
                int8_t r = s & (maskSrcch<< (pdch*(nch-j-1))>>(pdch(nch-j-1)));
                r *=ratio;
                std::memcpy(im.data+destPt+i*im.byd+j,&r,1);
            }   
        }    
}
void wrDataArrSubBytes(image2D& im,uint64_t srcPt,uint64_t len,int8_t pdDest, int8_t* dest){
    uint8_t maskSrc = (1<<im.bdc) -1;
// uint8_t maskDest = (1<<pdDest)  -1;
uint8_t nch = im.length;
uint8_t pdch = (pdDest/nch);
uint8_t maskDch = maskDest>>(pdch>>(nch-1));
float ratio = maskDch/maskSrc;

int8_t nchb = pdDest/nch;
int8_t nchbc=8/nchb;
for(uint64_t i=0;i<len;i++){
    enu_vec<fm>::ty res;
    std::memcpy(&res,im.data+srcPt+i*im.byd,nch);
    uint8_t re[pdDest/8];for(int m=0;m<pdDest/8;m++){re[m]=0;}; int8_t offs=0;
    for(int j=0;j<nch;j++){
        decltype(res[j]) r = res[j];
        r *=ratio;
        re[offs/(pdDest/8)]|=r<<(nchb*(nchbc - (nchbc%offs)));
        offs++;
    }   
    std::memcpy(dest+i*(pdDest/8),&r,pdDest/8);
}

};
template <modules::image_formats fm>
void loadDataArr(image2D& im,uint64_t destPt,uint64_t len,int8_t pdSrc, int8_t* src ){
                    uint64_t maskDest = (1<<im.bdc) -1;
                    uint64_t maskSrc = (1<<pdSrc)  -1;
                    uint64_t nch = im.length;
                    uint64_t pdch = (pdSrc/nch);
                    uint64_t maskSrcch = maskSrc>>(pdSrc/nch);
                    float ratio = maskDest/maskSrcch;
           
        for(uint64_t i=0;i<len;i+=pdSrc/8){
            enu_vec<fm>::ty res ;
            for(int j=0;j<nch;j++){
                res[j] = src[i];
                res[j] =res[j]  & (maskSrcch<< (pdch*(nch-j-1))>>(pdch(nch-j-1)));
                res[j] *=ratio;
            }   
            std::memcpy(im.data+destPt+i+j,&res,im.byd);
        }
        }
template <modules::image_fromats fm>
void wrDataArr(image2D& im,uint64_t srcPt,uint64_t len,int8_t pdDest, int8_t* dest){
    uint64_t maskDest = (1<<pdDest) -1;
    uint64_t maskSrc = (1<<im.bd)  -1;
    uint64_t nch = im.length;
    uint64_t pdch = (pdDest/nch);
    uint64_t maskSrcch = maskSrc>>(im.pd/nch() *(nch-1));
    float ratio = maskDest/maskSrcch;
       
    for(uint64_t i=0;i<len;i++){
        enu_vec<fm>::ty res ;
        std::memcpy(&res,im.data+srcPt+i*im.byd,im.byd);
        for(int j=0;j<nch;j++){
            decltype(res[j]) r = res[j] ;
            r*=ratio;
            int8_t s[pdDest/nch] ;
            for(int k=0;k<pdDest/nch;i++) {
                s[k]=(1<<8 -1)<<(8*k) &r >>8*k; 
            }
            std::memcpy(dest+i*pdDest/8 + j * pdDest/(8*nch) ,&s,pdDest/nch);
        }   
    }
}

struct png {
    
struct pngHeader {
    int8_t bit=0x89;
    int8_t png[3] = {0x50,0x4E, 0x47};
    int8_t dosEnd[2]={0x0D,0x0A} 
    int8_t com = 0x1A;
    int8_t UNIXend = 0x0A;
};
/// @defgroup png Chunks
int64_t tag(char* s){
    int8_t n = s[0];
    int64_t res = n;res=res<<8;
    n = s[1];res+=n;res=res<<8;
    n=s[2];res+=n;res=res<<8;
    n=s[3];res+=n;
};
#define PNG_TAG(n) const int64_t png##n=tag(#n);
#define PNGC length=pc.length; \
     name=pc.name; \
     crc=pc.crc; 
template <typename data>
struct pngC{
    int64_t length;
    int64_t name;
    data d;
    int64_t crc;
    void set(pngC<int8_t*>& pc){
        length=pc.length;
        name=pc.name;
        crc=pc.crc;
    }
    pngC<data>(pngC<int8_t*>& pc){
        set(pc);
     d = std::memcpy(&d,pc.bytes,length);    
}
};

using pngChunk  = pngC<int8_t*> ;
ACQRES(pngChunk<int8_t*>){
    one(f.length);
    one(f.name);
    arr(f.bytes,f.length);
    one(f.crc);
}
USE_ACQRES(pngChunk<int8_t*>)

#define PNGTAGS IDHR,IDAT,PLTE,IEND,bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt

REPEAT(PNG_TAG , PNGTAGS)

/*must be the first chunk; it contains (in this order) the image's
width (4 bytes)
height (4 bytes)
bit depth (1 byte, values 1, 2, 4, 8, or 16)
color type (1 byte, values 0, 2, 3, 4, or 6)
compression method (1 byte, value 0)
filter method (1 byte, value 0)
interlace method (1 byte, values 0 "no interlace" or 1 "Adam7 interlace") (13 data bytes total).*/
//IDHR,   
//IDAT,   
//PLTE,   // Containe palette
//IEND,   
//bKGD,  //gives the default background color. It is intended for use when there is no better choice available, such as in standalone image viewers (but not web browsers; see below for more details).
//cHRM,  //gives the chromaticity coordinates of the display primaries and white point.
//cICP,  //specifies the color space, transfer function and matrix coefficients as defined in ITU-T H.273.[26] It is intended for use with HDR imagery without requiring a color profile.[27]
//dSIG,  //is for storing digital signatures.[28]
//eXIf,  //stores Exif metadata.[29][30]
//gAMA,  //specifies gamma. The gAMA chunk contains only 4 bytes, and its value represents the gamma value multiplied by 100,000; for example, the gamma value 1/3.4 calculates to 29411.7647059 ((1/3.4)*(100,000)) and is converted to an integer (29412) for storage.[31]
//hIST,  //can store the histogram, or total amount of each color in the image.
//iCCP,  //is an ICC color profile.
//iTXt,  //contains a keyword and UTF-8 text, with encodings for possible compression and translations marked with language tag. The Extensible Metadata Platform (XMP) uses this chunk with a keyword 'XML:com.adobe.xmp'
//pHYs,  //holds the intended pixel size (or pixel aspect ratio); the pHYs contains "Pixels per unit, X axis" (4 bytes), "Pixels per unit, Y axis" (4 bytes), and "Unit specifier" (1 byte) for a total of 9 bytes.[32]
//sBIT,  //(significant bits) indicates the color-accuracy of the source data; this chunk contains a total of between 1 and 5 bytes, depending on the color type.[33][34][35]
//sPLT,  //suggests a palette to use if the full range of colors is unavailable.
//sRGB,  //indicates that the standard sRGB color space is used; the sRGB chunk contains only 1 byte, which is used for "rendering intent" (4 values—0, 1, 2, and 3—are defined for rendering intent).[36]
//sTER,  //stereo-image indicator chunk for stereoscopic images.[37]
//tEXt,  //can store text that can be represented in ISO/IEC 8859-1, with one key-value pair for each chunk. The "key" must be between one and 79 characters long. Separator is a null character. The "value" can be any length, including zero up to the maximum permissible chunk size minus the length of the keyword and separator. Neither "key" nor "value" can contain null character. Leading or trailing spaces are also disallowed.
//tIME,  //stores the time that the image was last changed.
//tRNS,  //contains transparency information. For indexed images, it stores alpha channel values for one or more palette entries. For truecolor and grayscale images, it stores a single pixel value that is to be regarded as fully transparent.
//zTXt,  //contains compressed text (and a compression method marker) with the same limits as tEXt.
/// 
struct IDHRd {
    /*
Color    Allowed    Interpretation
   Type    Bit Depths
   
   0       1,2,4,8,16  Each pixel is a grayscale sample.
   
   2       8,16        Each pixel is an R,G,B triple.
   
   3       1,2,4,8     Each pixel is a palette index;
                       a PLTE chunk must appear.
   
   4       8,16        Each pixel is a grayscale sample,
                       followed by an alpha sample.
   
   6       8,16        Each pixel is an R,G,B triple,
                       followed by an alpha sample. */

  enum colorType {
        grayscale=0,
        rgb=2,
        palette=3,
        grayscalealpha=4,
        rgba=6

    };
    enum filter {
    None=0,
    Sub=1,
    Up=2,
    Average=3,
    Paeth=4
    };
    int64_t width ;// (4 bytes);
    int64_t height ;// (4 bytes);
    int8_t bitdepth ;// (1 byte, values 1, 2, 4, 8, or 16);
    int8_t colortype ;// (1 byte, values 0, 2, 3, 4, or 6);
    int8_t compression ;// method (1 byte, value 0);
    int8_t filter ;// method (1 byte, value 0);
    int8_t interlace ;// method (1 byte, values 0 "no interlace" or 1 "Adam7 interlace") 
    
}
using IDHR = pngC<IDHRd>;

typedef glm::u8vec3 PLTEd;
using PLTE = pngC<PLTEd*> ;

struct IDAT : pngC<int8_t*> ;
union tRNSd {
    int8_t* three;
    int16_t* zero;
    struct {
        int16_t* r;
        int16_t* g;
        int16_t* b;
            
    } two;
};
struct tRNS : pngC<tRNSd>{
    tRNS(pngC<int8_t*> pc,pnh_IDHR& idhr,PLTE& plte){
        set(pc);
        PtRNS = pngC<pngtRNSd>(pc) ; 
        switch(idhr.d.colortype){
            case 3 : {
                std::memcpy(&d.three,pc.d ,plte.length/3);
            }
            case 0 : {
                std::memcpy(&d.zero,pc.d, pow(2,plte.d.bitdepth)-1);
            }
            case 2 : {
                std::memcpy(&d.two.r,pc.d, pow(2,plte.d.bitdepth)-1);
                std::memcpy(&d.two.g,pc.d + pow(2,idhr.d.bitdepth)-1, pow(2,idhr.d.bitdepth)-1);
                std::memcpy(&d.two.b,pc.d + (pow(2,idhr.d.bitdepth) -1)*2  , pow(2,idhr.d.bitdepth)-1);
            };}          
    };
};
using gAMA = pngC<int64_t> ;

struct cHRMd {
int32_t WhitePointx;   // 4 bytes
int32_t WhitePointy;   // 4 bytes
int32_t Redx;    //        4 bytes
int32_t Redy;    //        4 bytes
int32_t Greenx;    //      4 bytes
int32_t Greeny;    //      4 bytes
int32_t Bluex;    //       4 bytes
int32_t Bluey;    //       4 bytes
}
using cHRM = pngC<cHRMd>;

enum pngsRGB {
 Perceptual =0,
 Relative_colorimetric =1,
 Saturation =2,
 Absolute_colorimetric =3
}
typedef int8_t sRGBd ;
using sRGB = pngC<sRGBd> ;

struct iCCPd {
    char* str;
    int8_t null;
    int8_t compression;
    int8_t *nBytes;
}
struct iCCP : pngC<iCCPd>{
    iCCP(pngC<int8_t*> pc){
        set(pc);
        int i;
        for(i=0;pc.d[i]!='\0';i++ ){}
        std::memcpy(d.str,pc.d,i+1);
        d.null = '\0';
        d.compression = pc.d[i+1];
        std::memcpy(d.nBytes,pc.d+i+2);
    };
} ;
struct tEXtd {
    char* str;
    int8_t null;
    int8_t *nBytes;
}
struct pngtEXt : pngC<tEXtd> {
    tEXt(pngC<int8_t*> pc){
        set(pc);
        int i;
        for(i=0;pc.d[i]!='\0';i++ ){}
        std::memcpy(d.str,pc.d,i+1);
        piCCP.d.null = '\0';
        std::memcpy(d.nBytes,pc.d+i+1);break;
    };
}; 
using zTXt = ICCP ;

struct iTXtd {
    char* str;
    int8_t null;
    int8_t compressionFlag;
    int8_t compressionMethod;
    char* langtag;
    int8_t null2;
    char* keyword;
    int8_t null3;

    char* nBytes;
}
using iTXt : pngC<iTXtd>{
     iTXt(pngC<int8_t*> pc){
int i;
for(i=0;pc.d[i]!='\0';i++ ){}
std::memcpy(d.str,pc.d,i+1);
d.null = '\0';
d.compressionFlag= pc.d[i+1];
d.compressionMethod=pc.d[i+2];
int j;
for(j=i+4;pc.d[j] !='\0';j++){}
std::memcpy(d.langtag,pc.d+i+4 ,j+1);
d.null2='\0';int k;
for(k=i+4 + j+2;pc.d[k] !='\0';k++){}
std::memcpy(d.keyword,pc.d+i+4+j+2 ,k+1);
d.null3='\0';
std::memcpy(d.nBytes,pc.d +i+4+j+2+k+1,pc.length-i-4-j-2-k-1);
     }
};

struct bKGD : pngC<tRNSd>{
bKGD(pngC<int8_t*> pc,IDHR& PIDHR){
            set(pc);
switch(PIDHR.d.colortype){
            case 3 : {
                std::memcpy(&PbKGD.d.three,pc.d ,PPLTE.length/3);
            }
            case 0 : {std::memcpy(&PbKGD.d.zero,pc.d, pow(2,PIDHR.d.bitdepth)-1);}
            case 4 : {std::memcpy(&PbKGD.d.zero,pc.d, pow(2,PIDHR.d.bitdepth)-1);} 
            case 2 : {
                std::memcpy(&PbKGD.d.two.r,pc.d, pow(2,PIDHR.d.bitdepth)-1);
                std::memcpy(&PbKGD.d.two.g,pc.d + pow(2,PIDHR.d.bitdepth)-1, pow(2,PIDHR.d.bitdepth)-1);
                std::memcpy(&PbKGD.d.two.b,pc.d + (pow(2,PIDHR.d.bitdepth) -1)*2  , pow(2,PIDHR.d.bitdepth)-1);
            };
            case 6 : {
                std::memcpy(&PbKGD.d.two.r,pc.d, pow(2,PIDHR.d.bitdepth)-1);
                std::memcpy(&PbKGD.d.two.g,pc.d + pow(2,PIDHR.d.bitdepth)-1, pow(2,PIDHR.d.bitdepth)-1);
                std::memcpy(&PbKGD.d.two.b,pc.d + (pow(2,PIDHR.d.bitdepth) -1)*2  , pow(2,PIDHR.d.bitdepth)-1);
            }
        }
        }
};
struct pHYsd {
    int32_t unitx;
    int32_t unity;
    int8_t unitSpecifier;
}
using pHYs = pngC<pHYsd>;
union sBITd {
    int8_t zero;
    int8_t two[3];
    int8_t three[3];
    int16_t four;
    int32_t six;
};
using sBIT : pngC<sBITd>{
    sBIT(pngC<int8_t*> pc,IDHR& PIDHR){
        switch(PIDHR.colortype) {
        case 0:{std::memcpy(&PsBIT.d.zero,pc.d,1);break;}; 
        case 2:{std::memcpy(&PsBIT.d.two,pc.d,3);break;}; 
        case 3:{std::memcpy(&PsBIT.d.three,pc.d,3);break;}; 
        case 4:{std::memcpy(&PsBIT.d.four,pc.d,2);break;};
        case 6:{std::memcpy(&PsBIT.d.six,pc.d,4);break;};}}
};

struct sPLTd {
    char* Palettename:    1-79 bytes (character string)
    int8_t null;
    int8_t Sampledepth;
    union rgbf{
        struct {
            uint8_t Red;
            uint8_t Green;
            uint8_t Blue;
            uint8_t Alpha;
        }one;
        struct {
            uint16_t Red;
            uint16_t Green;
            uint16_t Blue;
            uint16_t Alpha;
        }two;
        uint16_t frequency;
    };
    rgbf* pl;

}
struct sPLT : pngC<SPLd> {
    sPLT(pngC<int8_t*> pc){int i;
for(i=0;i<pc.d[i]!='\0';i++){};
std::memcpy(d.PaletteName,pc.d,i+1);
d.null='\0';
d.Sampledepth = pc.d[i+1];

int l = length - i -2;
switch(d.Sampledepth){
    case 8 : {
        d.pl = new sPLTd::rgbf[2* l/6];
        for(int i=0;l>0;i++){
            std::memcpy(&d.pl[i].one,pc.d+i+2 +i*6,4);
            std::memcpy(&d.pl[i].frequency,pc.d+i+2 +i*6 +4,2);
        }
    }
    case 16 : {
        d.pl = new sPLTd::rgbf[2* l/10];
            for(int i=0;l>0;i++){
            std::memcpy(&d.pl[i].two,pc.d+i+2 +i*10,4);
            std::memcpy(&d.pl[i].frequency,pc.d+i+2 +i*10 +8,2);
        }
    }
};
}
}

typedef uint16_t* hISTd ;
using hIST = pngC<hISTd>;

struct tIMEd {
   uint16_t Year;//:   2 bytes (complete; for example, 1995, not 95)
   uint8_t Month;//:  1 byte (1-12)
   uint8_t Day;//:    1 byte (1-31)
   uint8_t Hour;//:   1 byte (0-23)
   uint8_t Minute;//: 1 byte (0-59)
   uint8_t Second;//: 1 byte (0-60) 
}
using tIME = pngC<tIMEd>;

struct IEND = pngC<void>;

    pngHeader head;
    std::vector<pngu> chunks;

    IDHR PIDHR;PLTE PPLTE; list<IDAT> PIDAT; IEND PIEND ;
    #define PNG_DEF(p) ##p P##p ;
    REPEAT(PNG_DEF, bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt )

    int8_t& bd(){return PIDHR.bitdepth;}
    int64_t& width(){return PIDHR.width;}
    int64_t& height(){return PIDHR.height;}
    void getImageSegment()

    uint8_t nch;
    uint8_t pltemask;
        uint64_t pix;
    IDAT& idat;
    std::vector<uint8_t> decomp;
    uLongf destLen ;

    void loadPlte(image2D& im,uint64_t pt, uint64_t index){
        uint64_t offs =  index%(8/bd());
        uint8_t ind= idat.d[ index*(8/bd())] ;
        uint8_t offset = bd()*(8/bd() - offs*(8/bd()))
        uint8_t ind = ind & (pltemask << offset) >> offset;
        glm::u8vec3 s =PPLTE.d[ind];
        im.putAt<image_formats::rgb8>(x*y,s);
    };
    void loadData(image2D& im,uint64_t pt, uint64_t index){
        uint64_t len = destLen ;
        if(bd()<8 or (bd()/nch)<8){
            loadDataArrSubBytes(im,pt,len,bd(),idat.d);}
        else {
            switch(im.imageFormat){
                #define IMAGEFORMAT_CASE_LOAD(imf) \
                case image_formats::imf :{loadDataArr<image_formats::imf>(im,pt,len,bd(),idat.d);};
                REPEAT(IMAGEFORMAT_CASE_LOAD , r8ui,r16ui,rgb8ui,rgb1ui,rg8ui,rgba8ui);
            }
        }
    };  
    uint32_t wc ;
    uint32_t hc ;
    uint32_t na7;
    std::vector<uint64_t> inds;
    void loadDataAdam7(image2D& im,uint64_t pt, uint64_t index){
        uint64_t len = destLen ;
        if(bd()<8 or (bd()/nch)<8){
            loadDataInterlaceSubBytes(im,inds.data(),inds.size(),pt,destLen,bd(),decomp.data());
        }
        else {
            for(uint32_t i=0;i<len;i++){
                switch(im.imageFormat){
                    #define IMAGEFORMAT_CASE_LOAD_ADAM(imf) \
                    case image_formats::imf :{loadDataInterlaceArr<image_formats::imf>(im,inds,inds.size(),pt,destLen,bd(),idat.d);};
                    REPEAT(IMAGEFORMAT_CASE_LOAD_ADAM , r8ui,r16ui,rgb8ui,rgb1ui,rg8ui,rgba8ui);
                }
            }
        }
    };  

    void Adam7Handle(image2D& im,uint16_t step, void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
        if(loadPixel == loadPlte){
                pltemask= 1<<bd() - 1;uint64_t i;
                for( i=0;i<destLen*(8/bd());i++) {
                    loadPlte(im,inds[pix+i],i);
                }
                pix+=i;
                return ;}
            if(bd() == im.bd   ){uint32_t i;
                for(i=0;<i<destLen;i++){
                    std::memcpy(im.data + inds[pix+i] * im.byd,decomp.data() + im.byd*i ,im.byd);
                }
            pix+=i ;return;
            }
            else {loadDataAdam7(im,pix,0);}
    }
    void a7setInds(){
         wc = width()/8 ; // Set heights of 
        hc = height()/8 ; // Set heights of 
        na7 = wc*hc;
        pix=0;
        int8_t wcm=width()%8;int8_t hcm=height()%8;
inds.resize(na7) ;inds[0]=0;uint64_t wd=width()/2 ;uint64_t hd=height()/2 ; 
        for(int i=1;i<na7;i*=2){
            if(i%2==0){
                for(int k=1;k<=i;k++){
                    inds[i+k]=inds[i]+wd;
                };wd/=2;
            }
            else {
                for(int k=1;k<=i;k++){
                    inds[i+k]=inds[i]+hd*width();
                };hd/=2;
            }
        };
    }
    void loadAdam7(image2D& im, void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
        a7setInds()
            // if(PIDAT.size()!=256){std::cerr("IDAT chunk num != 256 Adam7 inoperable");}
            int i=0;
            for(idat : PIDAT ) { 
                if(idat.length < IDAT_MAX_SIZE) {
                decomp =std::vector<uint8_t>(idat.length * 1032);
                    uncompress(decomp.data(),&destLen,idat.d,idat.length)    ;
                    decomp.resize(destLen);
                    Adam7Handle(i,im,loadPixel);
                }
                else {std::cerr("IDAT chunk too big");return;}
                i++;};
        }
    
    void loadNormalHandle(image2D& im,void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
    
         if(loadPixel == loadPlte){
                   pltemask= 1<<bd() - 1;uint64_t i;
                for( i=0;i<destLen*(8/bd());i++) {
                    loadPlte(im,pix+i,i);
                }
                pix+=i;
                return ;
            }
            if(bd() == im.bd   ){
                std::memcpy(im.data + pix * im.byd,decomp.data() ,destLen);
                pix+=destLen/im.byd ;return;
            }
            else {loadPixel(im,pix,0);}
    }
    #ifndef IDAT_MAX_SIZE
    #define IDAT_MAX_SIZE 8193
    #endif
    void loadNormal(image2D& im,void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
        pix=0;
    
        for( idat : PIDAT) {
            if(idat.length < IDAT_MAX_SIZE ){
                decomp =std::vector<uint8_t>(idat.length * 1032);
               uncompress(decomp.data(),&destLen,idat.d,idat.length);
               decomp.resize(destLen);
                loadNormalHandle(im,loadPixel);
            }
            else {std::cerr("IDAT Chunk To big")return;}
        };
    }
    void loadImage(image2D& im, void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
        if(PIDHR.interlace) {loadAdam7(im,loadPixel);}
        else {loadNormal(im,loadPixel);}
    }
    image2D ld(std::string path ,bool subImage=false, uint32_t x=0,uint32_t y=0, uint32_t width=0,uint32_t height=0){
        png p ;
        std::ifstream fi(path);
        ld<pngHeader>(p.head,fi);

        tRNS PtRNS ;
        #define BOOL_CHUNK(n) bool b##n=false;
        REPEAT(BOOL_CHUNK ,bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt)

        while(!fi.eof()){
            pngChunk  pc;
            ld<pngChunk>(pc,fi);
            switch(pc.name){
                case pngIDHR :{PIDHR=IDHR(pc);break;}
                case pngPLTE :{PPLTE=pngC<PLTEd>(pc);break;}
                case pngIDAT :{PIDAT.push_back(pc);break;}
                case pngIEND :{PIEND=pngc<void>(pc);break;};
                case pngtRNS :{btRNS=true;PrRNS =tRNS(pc,PIDHR,PPLTE);break;}
                case pnggAMA :{bgAMA=true;PgAMA = gAMA(pc);break;}
                case pngCHRM :{bCHRM=true;PcHRM = CHRM(pc);break;};
                case pngsRGB :{bsRGB=true;psRGB = sRGB(pc);break;};
                case pngiCCP :{biCCP=true;piCCP = iCCP(pc);break;};
                case pngtEXt :{btEXt=true;PtEXt = tEXt(pc);break;};
                case pngzTXt :{bzTXt=true;PzTXt = iCCP(pc);break;}
                case pngiTXt :{biTXt=true;piTXt = iTXt(pc);break;}
                case pngbKGD :{bbKGD=true;PbKGD = tRNS(pc);break;}
                case pngpHYs :{bpHYs=true;PpHYs = pHYs(pc);}
                case pngsBIT :{bsBIT=true;PsBIT = sBIT(pc,PIDHR);break;}
                case pngsPLT :{bsPLT=true;PsPLT = sPLT(pc);break;}
                case pnghIST :{bhIST=true;PhIST = hIST(pc);break;}
                case pnhtIME :{btIME=true;PtIME = tIME(pc);break;}
                };
            // p.chunks.push_back(pc);
        };
        image2D im;
        im.width = width();
        im.height = height();
                
        if(PIDHR.compression != 0){std::cerr(std::string("IDHR chunk compression field value not 0 in image : ") +path ) ;}
        if(PIDHR.filter != 0){std::cerr(std::string("IDHR chunk filter field value not 0 in image : ") +path );}
        if(PIDHR.interlace != 0  or (PIDHR.interlace != 1)){std::cerr(std::string("IDHR chunk interlace value unknown in image :")+path );}
        im.init();
        switch(PIDHR.colortype){
            case IDHRd::colorType::grayscale : {
                switch(bd()){ nch=1;
                case 1 : {im.imageFormat = image_formats:r8ui;}
                case 2 : {im.imageFromat = image_formats:r8ui;}
                case 4 : {im.imageFromat = image_formats:r8ui;}
                case 8 : {im.imageFromat = image_formats:r8ui;}
                case 16 : {im.imageFromat = image_formats:r16ui;} }
                loadImage(im,&loadData);break;}
            case IDHRd::colorType::rgb : {nch=3;
                switch(bd()){
                case 8 : {im.imageFromat = image_formats::rgb8ui;}
                case 16 : {im.imageFromat = image_formats::rgb16ui;}}; loadImage(im,&loadData);break;}
            case IDHRd::colorType::palette : {nch=3;im.imageFormat = image_formats.rgb8ui;loadImage(im,&loadPlte);break;}        
            case IDHRd::colorType::grayscalealpha : {nch=2;
                switch(bd()){
                    case 8 : {im.imageFromat = image_formats::rg8ui;}
                    case 16 : {im.imageFromat = image_formats::rg8ui;}}
                loadImage(im,&loadData);break;}
            case IDHRd::colorType::rgba : {nch=4;
                switch(bd()){
                    case 8 : {im.imageFromat = image_formats::rgba8ui;}
                    case 16 : {im.imageFromat = image_formats::rgba8ui;}}
                loadImage(im,&loadData);break;}     
                }
                return im;
    };
    void wrPlte(image2D& im,uint64_t pt,uint64_t index){ // Index maybe size;
        uint64_t pltes=PLTE.length/3;
        int64_t s =findpalette(PLTE.d,pltes,3,im.data[pts]);

        std::memcpy(decomp.data()+(pt*bd()/8, &s + sizeof(s) - (bd()/8), bd()/8) ;  
    }   ; 
    void wrData(image2D& im,uint64_t pt,uint64_t index){
        uint64_t len = destLen ;
        if(bd()<8 or (bd()/nch)<8){
            wrDataArrSubBytes(im,pt,len,bd(),demcomp.data());}
        else {
            switch(im.imageFormat){
                #define IMAGEFORMAT_CASE_LOAD(imf) \
                case image_formats::imf :{wrDataArr<image_formats::imf>(im,pt,len,bd(),decom.data());};
                REPEAT(IMAGEFORMAT_CASE_LOAD , r8ui,r16ui,rgb8ui,rgb1ui,rg8ui,rgba8ui);
            }
        }
    };
    void wrDataAdam7(image2D& im,uint64_t pt,uint64_t index){
         uint64_t len = destLen ;
        if(bd()<8 or (bd()/nch)<8){
            wrDataInterlaceSubBytes(im,inds.data(),inds.size(),pt,destLen,bd(),decomp.data());
        }
        else {
            for(uint32_t i=0;i<len;i++){
                switch(im.imageFormat){
                    #define IMAGEFORMAT_CASE_LOAD_ADAM(imf) \
                    case image_formats::imf :{wrDataInterlaceArr<image_formats::imf>(im,inds,inds.size(),pt,destLen,bd(),decomp.data());};
                    REPEAT(IMAGEFORMAT_CASE_LOAD_ADAM , r8ui,r16ui,rgb8ui,rgb1ui,rg8ui,rgba8ui);
                }
            }
        }
    };
    uint32_t plteentries;
    
    void Adam7wrHandle(image2d& im,uint16_t step,void (*wrPixel)(image2D& ,uint64_t , uint64_t )){
        if(wrPixel==wrPlte){paletteGenerate(im,PLTE.d,PLTE.length);
            PLTE.length*=3;
            uint8_t byd=1 ;
            while((1<<8*byd-1) < PLTE.length){byd++;}
            bd() = 8*(byd);
            decomp.resize(bd()/8 * im.imageSize);
             pltemask= 1<<bd() - 1;uint64_t i;
                for( i=0;i<im.imageSize;i++) {
                    wrPlte(im,inds[i],i);
                }
                pix+=i;
                return ;}
        else {
            bd() = im.bd;
            decomp.resize(im.byd * im.imageSize);
            wrDataAdam7(im,step,wrPixel);
        }
    };
    void wrAdam7(image2D& im, void (*wrPixel)(image2D& ,uint64_t , uint64_t )){
        a7setInds();
        Adam7wrHandle(im,pix,wrPixel);
    }
    void wrNormal(image2D& im, void (*wrPixel)(image2D& ,uint64_t , uint64_t )){
        if(wrPixel==wrPlte){paletteGenerate(im,PLTE.d,PLTE.length);
            PLTE.length*=3;
            uint8_t byd=1 ;
            while((1<<8*byd-1) < PLTE.length){byd++;}
            bd() = 8*(byd);
            decomp.resize(bd()/8 * im.imageSize);
             pltemask= 1<<bd() - 1;uint64_t i;
                for( i=0;i<im.imageSize;i++) {
                    wrPlte(im,inds[i],i);
                }
                pix+=i;
                return ;}
        else {
            bd() = im.bd;
            decomp.resize(im.byd * im.imageSize);
            destLen=im.imageSize*im.byd;
            wrData(im,,wrPixel);
        }
    }
    void wrImage(image2D& im, void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
        if(PIDHR.interlace) {wrAdam7(im,loadPixel);}
        else {wrNormal(im,loadPixel);}
        uint32_t max= IDAT_MAX_SIZE * 512;destLen=max;
        PIDAT.push_back(IDAT());
        for(uint64_t i=0 ;i<decomp.size();i+=destLen){
            uint32_t destLen=max;
            for(PIDAT.back().length>IDAT_MAX_SIZE;destLen/=2){
                compress(PIDAT.back().d,&(PIDAT.back().length),decomp.data() + i,destLen)    ;
            };
            PIDAT.push_back(IDAT());
        }
    };
    void wr(std::string path,image2d& im ){
        *this = png() ;
        bool plt=true;
        
        #define BOOL_CHUNK(n) bool b##n=false;
        REPEAT(BOOL_CHUNK ,PLTE,bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt,IEND)

        bool bIDHR=true;bool bIDAT=true;
        switch(im.imageFormat){
            case image_formats::r8ui : {nch=1;PIDHR.d.colortype = IDHRd::colorType::grayscale;}
            case image_formats::r16ui : {nch=1;PIDHR.d.colortype = IDHRd::colorType::grayscale;}
            case image_formats::rg8ui : {nch=2;PIDHR.d.colortype = IDHRd::colorType::grayscalealpha;}
            case image_formats::rgb8ui : {nch=3;PIDHR.d.colortype = IDHRd::colorType::rgb;}
            case image_formats::rgba8ui : {nch=4;PIDHR.d.colortype = IDHRd::colorType::rgba;}
            case image_formats::rgb16ui : { nch=3;PIDHR.d.colortype = IDHRd::colorType::rgb;}
            case image_fromats::rgba16ui : {nch=4;PIDHR.d.colortype = IDHRd::colorType::rgba;}
        }
        if(plt){wrImage(im,&wrPlte);}
        else{wrImage(im,&wrData);}
        std::ofstream of(path);
        #define WR_CHUNK(n) if(b##n){wr<n>(P##n,of);}
        REPEAT(WR_CHUNK,IDHR ,PLTE,bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt,IDAT,IEND)
    };
    png() {head = pngHeader();};
}
// Jpeg

// Tga
#include <limits.h>
#include <type_traits>
enum tga_ColorMapType {
no=0 ,//if image file contains no color map
yes=1 //
//2–127 reserved by Truevision
//128–255 available for developer use
} 
enum tga_ImageType {
no=0, //no image data is present
uncompressed_color_mapped=1, //uncompressed color-mapped image
uncompressed_truecolor=2, //uncompressed true-color image
uncompressed_grayscale=3, //uncompressed grayscale image
run_length_color_mapped=9, //run-length encoded color-mapped image
run_length_truecolor=10, //run-length encoded true-color image
run_length_grayscale=11 //run-length encoded grayscale image
}
struct tga_header {
	int8_t  ID_length;	//Length of the image ID field
	int8_t  Color_map_type;//		Whether a color map is included
	int8_t  Image_type;//	Compression and color types
	struct{
        uint16_t firstIndex;
        uint16_t length;
        uint8_t entrySize;
    }  Color_map;//	 specification	Describes the color map
	struct {
        int16_t xOrigin;
        int16_t yOrigin;
        int16_t width;
        int16_t height;
        int8_t pixelDepth;
        int8_t descriptor;//3-0 alpha depth;  5-4 pixelOrdering 

        int8_t getAlpha(){
            return descriptor & 0b1111 ;
        }
        int8_t getOrder(){return descriptor & 0b110000;}
        /// bt  5 4
//bottom Left   0 0    
//bottom Right  0 1     
//top Left      1 0  
//top Right     1 1   
    }  Image;// specification	Image dimensions and format
  
};
struct tga {
    tga_header head;
    uint8_t* ID;
    uint8_t* colorMapData;
    uint8_t* imageData;
    
uint8_t pd;uint8_t byted;
int ac;
int nm;
int nch;
int16 imageFormatBytes ;

    image2D im ;

    uint8_t& cm_EntrySize(){return head.Color_map.entrySize;}
    uint16_t& cm_length(){return head.Color_map.length;}
    int8_t& pd(){return head.Image.pixelDepth;}
   
void setFormat(){
        im.imageFormat = ac>0?rgba32ui:rgb32ui;
if (ac > 0){im.imageFormat = rgba32ui;
    imageFormatBytes = imageFormatBytes<rgba32ui>();}
else {im.imageFormat = rgb32ui;    
    imageFormatBytes = imageFormatBytes<rgb32ui>();}
    }
    template <typename K>
    int8_t& getColorMap(int indt,int Offset){
        k* d =imageData+indt;
        return colorMapData[*d+offset];
    };
    int8_t& getRgb(int indt,int Offset){
        return imageData[indt+offset];
    };

    int byteOffset ;
    int bitOffset ;
    int acByteDepth;

    void alpha(int ind,int indT,int8_t (*ptr)(int ,int )){
        if(ac > 0){                
                if(ac/8==0 and ((ac + bitOffset) < 8)){
                    int8_t mask=1<<(ac+1)-1;
                    mask = mask<<(8-ac) ; mask= mask>>bitOffset ;
                    uint32_t  n= mask& ptr(indT,byteOffset) <<bitOffset >>(8-ac);
                    float ratio = UINT_LEAST32_MAX/mask;
                    float num = n * ratio;
                    n = num;
                    std::memcpy(im.data+ind,&n,4);
                }
                else {
                    int8_t mask = (1<<(8-bitOffset)+1)-1;
                    uint32_t n = mask& (ptr(indT,byteOffset));
                    for(int j=1;j<acByteDepth;j++){
                        n=n<<8 + ptr(indT,byteOffset+j);
                    }
                    int8_t bitdif = (ac-bitoffset)%8;
                    mask = 1<< (bitdif +1) -1;
                    n = n<< bitdif + mask&(ptr(indT,acByteDepth))>>bitdif;
                                        float ratio = UINT_LEAST32_MAX/mask;
                        float num = n * ratio;
                    n = num;
                    std::memcpy(im.data+ind,&n,4);
                }
        }
    }
    void colors(int ind,int indT,int8_t (*ptr)(int ,int )){
         int nchm = nch/8;
            int nchBit = nch&8;
                uint32_t n ;
                for(int j=0;j<=numCol-1;j++){
                    n=0;int8_t dif = (j*nch%8);
                    int8_t mask = 1<<(dif+1)-1;
                    n+=  ptr(indT,j*nchm ) & mask;
                    int8_t nchmdif = (nch-dif)/8;
                    for(int k =1;k<=nchmdif;k++){
                        n += n<<8 + ptr(indT,j*nchm +k);
                    };

                    n+= n<<(nch-dif)%8 +ptr(indT+j*nchm+k) ;
                    float ratio = UINT_LEAST32_MAX/mask;
                    float num = n*ratio;
                    n=num;
                    std::memcpy(im.data+ind+j*4,&n,4);
        }
    }
    void loadPtr( int numCol,int8_t (*ptr)(int ,int )){
         setFormat();
    byteOffset = nm/8;
    bitOffset = nm%8;
    acByteDepth = ac/8 + (ac%8==0)?0:1;

        for(int i=0;i<imDatas/byted;i++){ 
             int indT = i*byted;int ind=i*imageFormatBytes ;
            alpha(ind,indT,ptr);
            colors(ind,indT,ptr);}
    }
    template <typename key>
    void loadColorMapped(int numCol){
        loadPtr(numCol,&getColorMap<key>);

    };
    
    void loadRunLength( int numCol, int8_t (*ptr)(int,int) ){
        setFormat();
        int inds=0;
        for(int i=0;i<imDatas/byted;i++){
            int indT = i*byted;int ind=inds*imageFormatBytes ;
            int8_t packet = ptr(indT,0);
            int pc = (packet &(1<<7))?packet-(1<<7):1;

            alpha(ind,indT,ptr);
            colors(ind,indT,ptr);
            for(int j=0;j<pc;j++){
                std::memcpy(im.data+inds*imageFormatBytes,im.data+ind,(numCol+1)*4);
                inds++;
            };
            inds++;
        };
    };
    template <typename key>
    void loadRunLengthColorMapped(int numcol){loadRunLength(numcol,&getColorMap<key>);};

    void loadRunLengthRgba(int numcol){loadRunLength(numcol,&getRgb);}
    
    void loadRgba(int numCol){
        loadPtr(numCol,&getRgb);
    };
    bool isFormatted(){
        bool res = pd%32==0?1:(pd%16==0)?1:(pd%8==0)

        std::memcpy(d.data.p.imageData,imDatas);
        return true
    };
    void load1 (){
         if(isFormatted() ){return;}
         switch(pd/8){
            case 4 :{loadColorMapped<int16_t>(3);return;}
            case 8 :{loadColorMapped<int32_t>(3);return;}
        } 
         
         
    }
    
    void load2 (){
        if( isFormatted()){return;}
        loadRgbBa(3);
    };
    void load9(){
        switch(pd/8){
            case 4 :{loadRunLengthColorMapped<int16_t>(3);return;}
            case 8 :{loadRunLengthColorMapped<int32_t>(3);return;}
        } 
        };
    void load10(){
        loadRunLengthRgba(3);
    };
    void load3(){
        if(isFormatted()){return;};
        loadRgbBa(1);
    };
    void load11(){loadRunLengthRgba(11);};

    void selectrgba(){
        switch(nch){
            case 8 : {
                if(ac==8) {im.imageFormat =image_formats::rgba8ui;return;}
                if(ac==0) {im.imageFormat =image_formats::rgb8ui;return;}}

            }
            case 10 : {
                if(ac==2) {im.imageFormat = image_formats::rgba10_a2ui}

            };
            case 16 : {
                if(ac==16){im.imageFormat = image_formats::rgba16ui}
                if(ac==0) {im.imageFormat =image_formats::rgb16ui;return;}

            } 
        }  
    
    void selectGrayScale(){
        switch(nm){
            case 8 : {if(ac==8){im.imageFormat = image_formats::rg8ui;};
                        if(ac==0){im.imageFormat = image_formats::r8ui}
        }
            
        } 
    };
image2D ld(std::string path){
    std::ifstream fi(path);
    i = image2d();
    ld<tga_header>(this->head,fi);
    ld(this->ID,this->head.ID_length,fi);
    if(this->head.Color_map_type !=0){
        ld(this->colorMapData,this->head.Color_map.length,fi);
    }
    pd = this->head.Image.pixelDepth;
    byted = pd%8==0?pd/8:pd/8+1;

    size_t imDatas=this->head.Image.width*this->head.Image.height*byted;
    ld(this->ImageData, imDatas,fi);

    im.width = this->head.Image.width;
    im.height = this->head.Image.height;

    pd = this->Image.pixelDepth;
    ac =  this->Image.getAlpha();
    nm = pd -ac;
    nch = nm/3;  
    switch(this->head.Image_type ){
        case 1:{selectrgba();load1();}
        case 2:{selectrgba();load2();}
        case 9:{selectrgba();load9();}
        case 10:{selectrgba();load10();}
        case 3:{selectGrayScale();load3();}
        case 11:{selectGrayScale();load11();}
    }       
    return i;
};
std::vector<uint8_t> imageD;
std::vector<uint8_t> colorMapD;

int64_t findCl(uint8_t byd,void* d){
    for(uint64_t i=0;i<colorMapD.size();i+=byd){
        if(memcmp(d,colorMapD.data()+i,byd)){
            return i;
        }
    }; 
    return -1;
} ;
void wrCmap(image2D& im){
    pd() = 8;uint64_t i;

    for(i=0;i<im.imageSize;i+=im.byd){
        int64_t s = findpalette(colorMapD.data(),&colorMapD.size(),im.byd,im.data()+i);
        if(s==-1){
            colorMapD.resize(colorMapD.size()+im.byd);
            s=(colorMapD.size()-im.byd)
            std::memcpy(colorMapD.data()+s , im.data+i,im.byd);
        }
        s/=8;
        std::memcpy(imageD.data()+(i/im.byd)*pd(),&s,pd());
    };
    // Resize bitdepths;
    uint64_t s;
    for(;i<s;pd()--){s=1<<(pd()*8 -1)-1 + (1<<(pd()*8-1));}
    for(uint64_t n=0;n<imageD.size()/8;n++){
        std::memcpy(imageD.data()+n*pd(),imageD.data()+n*8 + 8-pd(),pd() );
    };  
    imageD.resize(imageD.size()/8*pd() );

};
void wrCmapRLE(image2D& im){
    pd() = 8;uint64_t i;
    uint8_t rep=0;uint32_t entries=0;
    for(i=0;i<im.imageSize;i+=im.byd){
        if(std::memcmp(im.data+i,im.data+i-im.byd , im.byd)==0 and (rep<(1<<7))){rep++;}
        else {uint8_t reps = rep +(1<<7);
            memcpy(imageD.data()+entries*(pd()+1),&reps,1);
            rep=0;entries++;};
        int64_t s = findCl(im.byd,im.data()+i);
        if(s==-1){
            colorMapD.resize(colorMapD.size()+im.byd);
            s=(colorMapD.size()-im.byd)
            std::memcpy(colorMapD.data()+s , im.data+i,im.byd);
        }
        
    };
    // Resize bitdepths;
    uint64_t s;
    for(;i<s;pd()--){s=1<<(pd()*8 -1)-1 + (1<<(pd()*8-1));}
    for(uint64_t n=0;n<imageD.size()/8;n++){
        std::memcpy(imageD.data()+n*(pd()+1),imageD.data()+n*9 + 8-pd(),pd()+1 );
    };  
    imageD.resize(imageD.size()/8*(pd()+1) );

};
void wrNorm(image2D& im){
    pd()=im.byd;uint8_t rep-0;uint32_t entries=0
    imageD.resize(pd()*im.imageSize);
    std::memcpy(imageD.data(),im.data,pd()*im.imageSize);
};
void wrRLE(image2D& im){
    pd()=im.byd;
    for(int i=0;i<im.imageSize;i+=im.byd){
        if(std::memcmp(im.data+i,im.data+i-im.byd , im.byd)==0 and (rep<(1<<7))){rep++;}
        else{uint8_t reps = rep+(1<<7);
            memcpy(imageD.data()+entries*(pd()+1),&reps,1);
            rep=0;entries++;
            memcpy(imageD.data()+entries*(pd()+1)+1,im.data+i,pd() );
        }
    };
}
void wr(image2D& im,std::string path,bool cpl=false,bool rle=true){
    uint8_t bda =modules::bitdepth_a(im.imageFormat);
    head.Image.descriptor=bda &0b1111 + 0b110000; 
    head.Image.width=im.width;head.Image.height=im.height;
    cm_entrySize() = im.byd;
    colorMapD= std::vector<uint8_t>(im.byd*im.imageSize);
    if(im.length()<=2){
        if(rle){head.Image_type=tga_ImageType::run_length_grayscale;wrRLE(im);}
        else{head.Image_type=tga_ImageType::uncompressed_grayscale;wrNorm(im);}
    }
    else {
        if(rle){head.Image_type=tga_Image_type::run_length_color_mappped;wrCmapRLE(im);}
        else{head.Image_type=tga_ImageType::uncompressed_color_mappped;wrCmap(im);}
    }
    std::ofstream of(path);
    wr<tga_header>(head,of);
    wr<uint8_t>(ID,head.ID_LENGTH,of);
    wr<uint8_t>(colorMapD,colorMapD.size(),of);
    wr<uint8_t>(imageD,imageD.size(),of);
};
};
// bmp 
#include "clib.hpp"
struct uint24 {
    uint8_t d[3];
}
typedef uint32_t DWORD
struct OS2XBITMAPCOREHEADER{ // Not Used since windows 2000
uint32_t sizeHead;//0E	14	4	The size of this header (12 bytes)
uint16_t width;//12	18	2	The bitmap width in pixels (unsigned 16-bit)
uint16_t height;//14	20	2	The bitmap height in pixels (unsigned 16-bit)
uint16_t colorPlaneNum;//16	22	2	The number of color planes, must be 1
uint16_t bpp;//18	24	2	The number of bits per pixel
};

struct bmpHead {
    
    enum Field {
BM=0x424D, // Windows 3.1x, 95, NT, ... etc.
BA=0x4241, // OS/2 struct bitmap array
CI=0x4349, // OS/2 struct color icon
CP=0x434F, // OS/2 const color pointer
IC=0x4943, // OS/2 struct icon
PT=0x4F53 // OS/2 pointer
}
    uint16_t field;
    uint32_t filesize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t Offset; // Offset to image data
}

struct BITMAPINFOHEADER {
    enum CompressionMethod {
BI_RGB=0,	//	none	Most common
BI_RLE8=1,	//	RLE 8-bit/pixel	Can be used only with 8-bit/pixel bitmaps
BI_RLE4=2,	//	RLE 4-bit/pixel	Can be used only with 4-bit/pixel bitmaps
BI_BITFIELDS=3,	//	OS22XBITMAPHEADER: Huffman 1D	BITMAPV2INFOHEADER: RGB bit field masks,BITMAPV3INFOHEADER+: RGBA
BI_JPEG=4,	//	OS22XBITMAPHEADER: RLE-24	BITMAPV4INFOHEADER+: JPEG image for printing[14]
BI_PNG=5,	//		BITMAPV4INFOHEADER+: PNG image for printing[14]
BI_ALPHABITFIELDS=6,	//	RGBA bit field masks	only Windows CE 5.0 with .NET 4.0 or later
BI_CMYK=11,	//	none	only Windows Metafile CMYK[4]
BI_CMYKRLE8=12,	//	RLE-8	only Windows Metafile CMYK
BI_CMYKRLE4=13	//	RLE-4	only Windows Metafile CMYK
    }
uint32_t   size;             //0E	14	4	the size of this header, in bytes (40)
int32_t   width;            //12	18	4	the bitmap width in pixels (signed integer)
int32_t   height;           //16	22	4	the bitmap height in pixels (signed integer)
uint16_t   colorPlaneNum;    //1A	26	2	the number of color planes (must be 1)
uint16_t   pixeldepth;       //1C	28	2	the number of bits per pixel, which is the color depth of the image. Typical values are 1, 4, 8, 16, 24 and 32.
uint32_t   compressionMethod;//1E	30	4	the compression method being used. See the next table for a list of possible values
uint32_t   imageSize;        //22	34	4	the image size. This is the size of the raw bitmap data; a dummy 0 can be given for BI_RGB bitmaps.
uint32_t   ppmX;             //26	38	4	the horizontal resolution of the image. (pixel per metre, signed integer)
uint32_t   ppmY;             //2A	42	4	the vertical resolution of the image. (pixel per metre, signed integer)
uint32_t   nColPalette;      //2E	46	4	the number of colors in the color palette, or 0 to default to 2^n
uint32_t   nImportantColor;  //32	50	4	the number of important colors used, or 0 when every color is important; generally ignored

}

struct  OS22XBITMAPHEADER{
    enum Halftoning {
none=0,		//Most common
Error_diffusion=1,//		Halftoning parameter 1 (offset 64) is the percentage of error damping. 100 indicates no damping. 0 indicates that errors are not diffused
PANDA=2,//	:PANDA Processing Algorithm for Noncoded Document Acquisition	Halftoning parameters 1 and 2 (offsets 64 and 68, respectively) represent the X and Y dimensions, in pixels, respectively, of the halftoning pattern used
Super_circle=3	//Super-circle	Halftoning parameters 1 and 2 (offsets 64 and 68, respectively) represent the X and Y dimensions, in pixels, respectively, of the halftoning pattern used
    }
uint16_t resolutionsUnit ;//36	54	2	An enumerated value specifying the units for the horizontal and vertical resolutions (offsets 38 and 42). The only defined value is 0, meaning pixels per metre
uint16_t padding;//38	56	2	Padding. Ignored and should be zero
uint16_t direction;//3A	58	2	An enumerated value indicating the direction in which the bits fill the bitmap. The only defined value is 0, meaning the origin is the lower-left corner. Bits fill from left-to-right, then bottom-to-top.Note that Windows bitmaps (which don't include this field) can also specify an upper-left origin (bits fill from left-to-right, then top-to-bottom) by using a negative value for the image height
uint16_t halftoningAlg;//3C	60	2	An enumerated value indicating a halftoning algorithm that should be used when rendering the image.
uint32_t halftoningP1;//3E	62	4	Halftoning parameter 1 (see below)
uint32_t halftoningP2;//42	66	4	Halftoning parameter 2 (see below)
uint32_t colorEncoding;//46	70	4	An enumerated value indicating the color encoding for each entry in the color table. The only defined value is 0, indicating RGB.
uint32_t appDefdId;//4A	74	4	An application-defined identifier. Not used for image rendering
}
struct bmp {
    bmpHead  head; 
    OS2XBITMAPCOREHEADER _BITMAPCOREHEADER;
    BITMAPINFOHEADER _BITMAPINFOHEADER;
    uint32_t rmask;
    uint32_t gmask;
    uint32_t bmask;
    uint32_t amask;
    uint8_t getSizeMask(uint32_t *m){
        uint32_t ma - *m;
        while(ma & 1 ==0){ma>>1;}
        
        uint8_t size=0;
        while(ma & 1 ){ma>>1;size++;}
        return size;
    };
    uint8_t getDistMask(uint32_t *m){
        uint32_t ma = *m;
        uint8_t m=0;
        while(ma & 1 ==0){m++;ma>>1;}
    };
    enum mask {
        none,
        rgb,
        rgba
    }
    uint8_t maskb=mask::none;

    uint8_t* colorTable;
    
    OS22XBITMAPHEADER _OS22XBITMAPHEADER;
    DWORD* pixels;

    uint32_t imageSize;
    image2d im;

    
bool alpha;

uint16_t& pd(){return _BITMAPINFOHEADER.pixeldepth;} ;

    uint16_t& imSize(){return _BITMAPINFOHEADER.imageSize;};
    uint32_t ncolpal;
    uint32_t ncolPal(){return _BITMAPINFOHEADER.nColPalette==0?pow(2,pd()):_BITMAPINFOHEADER.nColPalette;}

    
    uint32_t rowsize;
    uint32_t rowSize(){
        rowsize=ceil(pd()* _BITMAPINFOHEADER.width/32)*4;
    }
    uint32_t pixelarraysize;
    uint32_t pixelArraySize(){pixelarraysize=rowsize()*abs(_BITMAPINFOHEADER.height);}
    void getCpColor(uint32_t index,void* data,uint8_t nCh){
            uint32_t i = index/(8/pd());
            uint32_t offset = 32- index%pd()*pd() -pd()  ;
            
            uint32_t mask = (1<<pd()-1)<<offset;
            uint32_t t =( pixels[i] );
            uint32_t n = t & mask>>offset;
            
            std::memcpy(data+index*nCh,colorTable+n,nCh);}       
   
    #define CPY_COLOR(l,in,i) \
    uint16_t l =(##lmask& pix )>>s##l; \
    l = ratio##l * l;\
    std::memcpy(im.data + i*ncolor +in,&l,1);  

#define CPY_COLORS(i) { \
    int8_t iterat=0; \
       if(rmask){
           CPY_COLOR(r,iterat,i) \
           iterat++;} \
       if(gmask){ \
           CPY_COLOR(g,iterat,i) \
           iterat++;} \
       if(bmask){ \ 
           CPY_COLOR(b,iterat,i) \
           iterat++;} \
       if(rgba and amask){ \
           CPY_COLOR(a,iterat,i)\
           iterat++;}\
}\


        uint8_t bc;  
        uint8_t sr=0;
        uint8_t sg=0;
        uint8_t sb=0;
        uint8_t sa=0;
        uint32_t MAXr;float ratior ;
        uint32_t MAXg;float ratiog ;
        uint32_t MAXb;float ratiob ;float ratioa ;

void setVals(uint8_t bpp){
bc=bpp%8==0?bpp/8:bpp/8+1;
sr=getDistMask(&rmask);
sg=getDistMask(&gmask);
sb=getDistMask(&bmask);
MAXr=rmask>>sr;ratior = UCHAR_MAX/MAXr;
MAXg=gmask>>sg;ratiog = UCHAR_MAX/MAXg;
MAXb=bmask>>sb;ratiob = UCHAR_MAX/MAXb; ratioa ;
if(alpha){sa=getDistMask(&amask);   MAXa=amask>>sa; ratioa = UCHAR_MAX/MAXa; }

}
void cpyImage(uint8_t bpp,uint8_t ncolor){
setVals(bpp);
for(uint32_t i ;i<imageSize;i++){
    uint32_t pix ;
    std::memcpy(&pix,pixels+i* bc,ncolor)
     CPY_COLORS(i)
}
};

void RleCpColor(uint32_t index,uint32_t in,void* data,uint8_t nCh){
            uint32_t i = index/(8/pd());
            uint32_t offset = 32- index%pd()*pd() -pd()  ;
            
            uint32_t mask = (1<<pd()-1)<<offset;
            uint32_t t =( pixels[i] );
            uint32_t n = t & mask>>offset;

    std::memcpy(data+in*nCh,colorTable+n,nCh);
};
    void RLEcp(uint8_t bpp,uint8_t ncolor){
        setVals(bpp);
        uint32_t iter=0;
        for(uint32_t i ;i<imageSize;i++){
        RleCpColor(i,iter,d,ncolor);
            for(;rle;--rle){
                std::memcpy(im.data+iter*ncolor,im.data+(iter-1)*ncolor,ncolor);
                    ++iter;
            }
        }
    }
    void RLE(uint8_t bpp,uint8_t ncolor){
        setVals(bpp);
        uint32_t iter=0;
        for(uint32_t i ;i<imageSize;i++){
     uint32_t pix ;
std::memcpy(&pix,pixels+i*bc,4)
            CPY_COLORS(iter)
            iter++;
            uint32_t rle =  pix>>(sr+sg+sb+sa);
            for(;rle;--rle){
                std::memcpy(im.data+iter*ncolor,im.data+(iter-1)*ncolor,ncolor);
                    ++iter;
            }
    };
}
    void getColor(uint8_t bpp){

        
        uint8_t ncolor= bool(rmask) + bool(gmask) + bool(bmask);
        if(alpha){ncolor+=bool(amask);}

        if(bpp==32){
            im.imageFormat=image_formats::rgba8;
            std::memcpy(im.data,pixels,imageSize*4);
            return;
        };
        if(bpp==24 ){
             if(_BITMAPINFOHEADER.compressionMethod == BI_JPEG){
                RLE(24,ncolor);
                return 
             }
            if(maskb==mask::rgb){
                im.imageFormat=image_formats::rgb8;
                std::memcpy(im.data,pixels,imageSize*3);
                im.swaprg();
                return;
            }   
        };
        if(bpp==16){
            if(maskb==mask::rgba){
                if ((getSizeMask(&rmask)==4)and
                and (getSizeMask(&gmask)==4)
                and (getSizeMask(&bmask)==4)
                and (getSizeMask(&amask)==4)){
                    float ratio = UCHAR_MAX/((1<<4) -1);
                    im.imageFormat=image_formats::rgba8;
                    for(uint32_t i=0;i<imageSize;i++ ){
                        for(uint8_t j=0;j<4;j++){
                            uint8_t r;   
                            std::memcpy(&r,pixels+i*2,imageSize*4);
                            r = r*ratio;
                            std::memcpy(im.data+i*4+j,&r,1);
                        }
                    };
                    return;
                }
            }   
        };
        if(bpp==8){
            if(_BITMAPINFOHEADER.compressionMethod == BI_RLE8){
                RLE(8,ncolor);
                return;
            }
            else {
                im.imageFormat=image_formats::argb8;
                for(int i=0;i<imageSize;i++){
                    getCpColor(index,im.image,ncolor);
                }
                im<<1;i.imageFormat=image_formats::rgba8;
                return;
            }
        };
        if(bpp == 4 and (_BITMAPINFOHEADER.compressionMethod == BI_RLE4)){
            RLE(4,ncolor);
        }
        cpyImage(bpp,ncolor);
    };

    image2d ld(std::string path){
        std::ifstream fi(path);
        ld(this->head,fi);
        i = image2d();
        bool huffman = false;
        bool alpha =false;
        ld(_BITMAPINFOHEADER,fi) ;
            if(_BITMAPINFOHEADER.compressionMethod == BI_BITFIELDS){huffman = true;maskb=mask::rgb;
                 ld(rmask,fi);
                 ld(gmask,fi);
                 ld(bmask,fi);}
            if(_BITMAPINFOHEADER.compressionMethod == BI_ALPHABITFIELDS){maskb=mask::rgba; alpha=true;
            ld(rmask,fi);
            ld(gmask,fi);
            ld(bmask,fi);
            ld(amask,fi);}
        imageSize=_BITMAPINFOHEADER.imageSize;
        if(head.field != bmpHead::BM){
            ld(_OS22XBITMAPHEADER,fi);
        }
        ncolpal = ncolPal(); 

        ld(colorTable,ncolpal,fi)
        ld<DWORD>(pixels,0,head.Offset,imageSize,fi);

        imSize()
        rowSize();
        pixelArraySize();

        getColor(pd());
    }
    void wr(sd::string path,image2D& im){

    };  
}

// JPEG

struct jpeg {


    const uint8_t segstart = 0xFF;
    enum segs {
        SOI	= 0xD8,//	none	        Start Of Image	
        SOF0= 0xC0,//	variable size	Start Of Frame (baseline DCT)	Indicates that this is a baseline DCT-based JPEG, and specifies the width, height, number of components, and component subsampling (e.g., 4:2:0).
        SOF2= 0xC2,//	variable size	Start Of Frame (progressive DCT)	Indicates that this is a progressive DCT-based JPEG, and specifies the width, height, number of components, and component subsampling (e.g., 4:2:0).
        DHT	= 0xC4,//	variable size	Define Huffman Table(s)	Specifies one or more Huffman tables.
        DQT	= 0xDB,//	variable size	Define Quantization Table(s)	Specifies one or more quantization tables.
        DRI	= 0xDD,//	4 bytes	        Define Restart Interval	Specifies the interval between RSTn markers, in Minimum Coded Units (MCUs). This marker is followed by two bytes indicating the fixed size so it can be treated like any other variable size segment.
        SOS	= 0xDA,//	variable size	Start Of Scan	Begins a top-to-bottom scan of the image. In baseline DCT JPEG images, there is generally a single scan. Progressive DCT JPEG images usually contain multiple scans. This marker specifies which slice of data it will contain, and is immediately followed by entropy-coded data.
        RSTn= 0xDn,// (n=0..7)	none	Restart	Inserted every r macroblocks, where r is the restart interval set by a DRI marker. Not used if there was no DRI marker. The low three bits of the marker code cycle in value from 0 to 7.
        APPn= 0xEn,//	variable size	Application-specific	For example, an Exif JPEG file uses an APP1 marker to store metadata, laid out in a structure based closely on TIFF.
        COM	= 0xFE,//	variable size	Comment	Contains a text comment.
        EOI	= 0xD9,//	none	End Of Image	
    }

    int8_t dct(uint8_t u,uint8_t v,uint8_t x,uint8_t y){
        return cos((2 * x + 1) * u * PI / 16.0) *
                           cos((2 * y + 1) * v * PI / 16.0);
    };  
    void dct8x8(double input[8][8], double output[8][8]) {
    for (int u = 0; u < N; ++u) {
        for (int v = 0; v < N; ++v) {
            double sum = 0.0;
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    sum += input[x][y] *dct(u,v,x,y);
                }
            }
            output[u][v] = 0.25 * alpha(u) * alpha(v) * sum;
        }
    }
}

// Inverse DCT
void idct8x8(double input[8][8], double output[8][8]) {
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            double sum = 0.0;
            for (int u = 0; u < N; ++u) {
                for (int v = 0; v < N; ++v) {
                    sum += alpha(u) * alpha(v) * input[u][v] *dct(u,v,x,y);
                }
            }
            output[x][y] = 0.25 * sum;
        }
    }
}

modules::image2D sRGBto_YCC(modules::image2D& im){
    modules::image2D res;
    for(uint64_t i=0;i<im.imageSize*im.byd;i++){
        uint8_t rgb[3] ;
        std::memcpy(rgb,im.data+i,3);
        int8_t ycc[3] ;
        int8_t ycc[0]=  fmin(fmax(0,round(0.299 *rgb[0] + 0.587 *rgb[1] + 0114*rgb[2])),255); 
        int8_t ycc[1] = fmin(fmax(0,round(-0.1687 *rgb[0]- 0.3313*rgb[1]+ 0.5*rgb[2] + 128 )),255);
        int8_t ycc[2] = fmin(fmax(0,round(0.5 *rgb[0]- 0.4187 *rgb[1]- 0.0813*rgb[2] +128)),255); 
        std::memcpy(res.data+i,ycc,3);
    };
};
modules::image2D YCCtoRGB(modules::image2D& im){
    modules::image2D res;
    for(uint64_t i=0;i<im.imageSize*im.byd;i++){
        int8_t ycc[3] ;
        std::memcpy(ycc,im+i,3);
        int8_t rgb[3] ;
        int8_t rgb[0]=  fmin(fmax(0,round(ycc[0] + 1.402*(ycc[1] -128))),255); 
        int8_t rgb[1] = fmin(fmax(0,round(ycc[0] - 0.3441 *(ycc[2] - 128) -0.71241(ycc[1] -128) )),255);
        int8_t rgb[2] = fmin(fmax(0,round(ycc[0] + 1.772 *(ycc[2] -128))),255); 
        std::memcpy(res.data+i,rgb,3);
    };
};
    void get8x8image(modules::image2D& im,uint32_t w, uint32_t h){
        
    }
    modules::image2D ld(std::string path){
        
    };

};
#ifdef STM_IMAGE_GIF

struct gif {
    typedef uint8_t char;
    typedef uint16_t WORD;
    typedef struct _GifHeader{
  // Header
  BYTE Signature[3];     /* Header Signature (always "GIF") */
  BYTE Version[3];       /* GIF format version("87a" or "89a") */
  // Logical Screen Descriptor
  WORD ScreenWidth;      /* Width of Display Screen in Pixels */
  WORD ScreenHeight;     /* Height of Display Screen in Pixels */
  BYTE Packed;           /* Screen and Color Map Information */
  
//Bits 0-2	Size of the Global Color Table
//Bit 3	Color Table Sort Flag
//Bits 4-6	Color Resolution
//Bit 7	Global Color Table Flag

  BYTE BackgroundColor;  /* Background Color Index */
  BYTE AspectRatio;      /* Pixel Aspect Ratio */
} GIFHEAD;
    GIFHEAD head;

    uint8_t NumberGlobalColorTable(){return 1L<<(head.Packed & 0b111 + 1);}
    uint8_t SizeGlobalColorTable(){return 1L<<(head.Packed & 0b111 + 1);}
    bool ColorTableSortFlag(){return head.Packed &0b1000;}
    uint8_t ColorResolution(){return (head.Packed &0b1110000) >> 4 + 1;}
    bool ColorTableFlag(){return (head.Packed &0b10000000) ;}
    WORD& width(){return head.ScreenWidth;} 
    WORD& height(){return head.ScreenHeight;} 
    
    glm::u8vec3* GIFCOLORTABLE;
    uint32_t ColorTableSize(){return 3L* (1L<<sizeGlobaleColorTable());}
    
 typedef struct _GifImageDescriptor
{
  BYTE Separator;    /* Image Descriptor identifier */
  WORD Left;         /* X position of image on the display */
  WORD Top;          /* Y position of image on the display */
  WORD Width;        /* Width of the image in pixels */
  WORD Height;       /* Height of the image in pixels */
  BYTE Packed;       /* Image and Color Table Data Information */

// Bit 0	Local Color Table Flag
// Bit 1	Interlace Flag
// Bit 2	Sort Flag
// Bits 3-4	Reserved
// Bits 5-7	Size of Local Color Table Entry
 bool LocalColorTableFlag(){return 0b1 & Packed;}
 bool InterlaceFlag(){return 0b10 & Packed;}
 bool SortFlag(){return 0b100 & Packed;}
 uint8_t SizeLocalColorTable(){return (0b1110000 & Packed)>>4 + 1;}
uint32_t ColorTableSize(){return 3L * (1L << (SizeLocalColorTable() ));}
uint32_t ColorTableNumberOfEntries(){return 1L << SizeLocalColorTable() ;}

    glm::u8vec3* GIFCOLORTABLE;

    std::vector<std::vector<uint8_t>> blocks; 
    std::vector<uint8_t> data;
} GIFIMGDESC;

std::vector<GIFIMGDESC> imgs;
 // Interlaces scanlines:
 // 0 8 ... 0++8
 // 4 12 ... 4++8
// 2 6 10 14 .. 2++4
// 1 3 5 7 // 1++2
    void loadNormal(image2D& im,GIFIMGDESC& gifim,uint64_t step,glm::uvec3* ct){
        std::memcpy(im.data+step*im.byd,ct+3*gifim.data[step],im.byd);
    }
    void loadInterlace(image2D& im,GIFIMGDESC& gifim,uint64_t step , glm::uvec3* ct){
            if((step/gifim.Width)%8==0 )    {std::memcpy(im.data+ ((step%gifim.Width) + (step/gifim.Width) * 8 * gifim.Width) *im.byd,ct+3*gifim.data[step]);}
            if((step/gifim.Width + 4)%8==0 ){std::memcpy(im.data+ ((step%gifim.Width) + (step/gifim.Width +4) * 8 * gifim.Width) *im.byd,ct+3*gifim.data[step]);}
            if((step/gifim.Width + 2)%4==0 ){std::memcpy(im.data+ ((step%gifim.Width) + (step/gifim.Width +2) * 4 * gifim.Width) *im.byd,ct+3*gifim.data[step]);}
            if((step/gifim.Width + 1)%2==0 ){std::memcpy(im.data+ ((step%gifim.Width) + (step/gifim.Width +1) * 2 * gifim.Width) *im.byd,ct+3*gifim.data[step]);}
                   
    };
    
    modules::aimage2D ld(std::string path){
        std::ifstream fi(path);
        ld(head,fi);
        if(head.ColorTableFlag()){
            ld<glm::u8vec3>(GIFCOLORTABLE,sizeGlobalColorTable()/3,fi);}
        modules::aimage2D vec;
        vec.swidth=  width();
        vec.sheight= height();
        void (*ptr)(image2D& ,GIFIMGDESC& ,uint32_t,glm::uvec3* ) ;
        while(!fi.eof() ){
            GIFIMGDESC gifim; 
            ld(gifim.Separator,fi);
            if(gifim.Separator!=0x2C){break;}
            ld(gifim.Left,fi);
            ld(gifim.Top,fi);
            ld(gifim.Width,fi);
            ld(gifim.Height,fi);
            ld(gifim.Packed,fi);
            if(gifim.InterlaceFlag()){ptr=&loadInterlace;}
            else{ptr=&loadNormal;}
            glm::u8vec3* ct;
            if(gifim.LocalColorTableFlag()){
                ld(gifim.GIFCOLORTABLE,gifim.colorTableNumberOfEntries,fi)
                ct=gifim.GIFCOLORTABLE;
            }
            else{ct=GIFCOLORTABLE;}
            image2D im(gifim.Width,gifim.height,image_formats::rgb8ui);
            im.x=gifim.Left;im.y=gifim.Right;
            uint8_t byte;
            ld(byte,fi);
            uint64_t step=0;
            while(byte!=0){
                gifim.blocks.push_back(std::vector<uint8_t>(byte));
                ld(blocks.back().data(),byte);
                std::vector<uint8_t> decoded(block.size()*10);
                size_t destLen;
                lzw_decode(block.data(),block.size(),decoded.data(),&destLen);
                decoded.resize(destLen);
                for(uint64_t i=0;i<destLen;i++){
                    ptr(im,gifim,step,ct);step++;
                }
                ld(byte,fi);
            };
            vec.push_back(im);
        }
    };

    void wr(std::string path, modules::aimage2D aim){
        std::ofstream of(path);
        head.Signature="GIF";
        head.Version="87a";
        head.ScreenWidth=aim.swidth;
        head.ScreenHeight=aim.sheight;
        head.Packed=0b11110000;
        uint32_t destplt;
        palettegenerate(aim[0],GIFCOLORTABLE,&destplt);
        uint32_t plts=destplt;
        int i=0;for(;destplt!=0;destplt>>1){i++;};i--;
        head.Packed|=i&0b111;
        wr(head,fi);
        wr(GIFCOLORTABLE,plts);
        
        for(image2D im : aim){
            GIFIMGDESC ims ;
            ims.Separator=0x2C;
            ims.Left=im.x;
            ims.Right=im.y;
            ims.Width=im.Width;
            ims.Height=im.height;
            ims.Packed=0b00000;
            bool failed=false;
            for(uint64_t i=0;i< im.imageSize;i++){
                int16_t t=findpalette(GIFCOLORTABLE,&plts,3,im.data+3*i);
                if(t>=0){int8_t res = t&(1<<8 -1);ims.data.push_back(res)};
                else {failed=true;break;}
            };
                            uint32_t pltsize;
            if(failed){ims.data.clear();
                uint32_t destplts;
                paletteGenerate(im,ims.GIFCOLORTABLE,&destplt);
                pltsize=destplts;
                int i=0;for(;destplts!=0;destplts>>1){i++;};i--;
                im.packed|=((i& 0b111)<<4);
                 for(uint64_t i=0;i< im.imageSize;i++){
                int16_t t=findpalette(ims.GIFCOLORTABLE,&pltsize,3,im.data+3*i);
                int8_t res = t&(1<<8 -1);ims.data.push_back(res)};
            }
            wr(ims.Separator,of);
            wr(ims.Left,of);
            wr(ims.Right,of);
            wr(ims.Width,of);
            wr(ims.Height,of);
            wr(ims.Packed,of);
            if(failed){wr(GIFCOLORTABLE,pltsize,of);}
            size_t s;
            std::vector<uint8_t> block(ims.data.size());
            lzw_encode(ims.data.data(),&ims.data.size(),block.data(),&s);
            block.resize(s);
            wr(block.data(),s,of);
            }
    };

}

#endif

image2D StmLoadImage(std::string name){
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
