#include <cstdint>
#include <stratum/modules.hpp>
#include <vector>
#include <petri/list.hpp>
#include "acqres.hpp"
#include <glm/glm.hpp>
#include <cstring>
/*
PNG []
JPEG 
BMP []
TGA [x]
GIF []
HDR
*/


// Png

struct pngHeader {
    int8_t bit=0x89;
    int8_t png[3] = {0x50,0x4E, 0x47};
    int8_t dosEnd[2]={0x0D,0x0A} 
    int8_t com = 0x1A;
    int8_t UNIXend = 0x0A;
}
/// @defgroup png Chunks
int64_t tag(char* s){
    int8_t n = s[0];
    int64_t res = n;res=res<<8;
    n = s[1];res+=n;res=res<<8;
    n=s[2];res+=n;res=res<<8;
    n=s[3];res+=n;
}
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

    pngC(pngC<int8_t*> pc;){
     length=pc.length;
     name=pc.name;
     crc=pc.crc;
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
struct png_IDHRd {
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
    int8_t interlace ;// method (1 byte, values 0 "no interlace" or 1 "Adam7 interlace") (13 data bytes total).;
    
}
using png_IDHR = pngC<png_IDHRd>;

typedef glm::i8vec3 png_PLTEd;
using png_PLTE = pngC<png_PLTEd*> ;

struct png_IDATd {

    int8_t deflate;
    int8_t zlib_fcheck:
    int8_t* block;
    int8_t zlib_check;
}
struct png_IDAT : pngC<png_IDATd> {
  
    png_IDAT(pngC<int8_t*> pc){PNGC
        d.deflate=pc.d[0];
        d.zlib_fcheck = pc.d[1];
        d.block = std::memcpy(d.block,pc+2,length -3);
        d.slib_check = pc[length-1];
    };
}
union png_tRNSd {
    int8_t* three;
    int16_t* zero;
    struct {
        int16_t* r;
        int16_t* g;
        int16_t* b;
            
    } two;
};
using png_tRNS = pngC<png_tRNSd>;
using png_gAMA = pngC<int64_t>;

struct png_cHRMd {
int32_t WhitePointx;   // 4 bytes
int32_t WhitePointy;   // 4 bytes
int32_t Redx;    //        4 bytes
int32_t Redy;    //        4 bytes
int32_t Greenx;    //      4 bytes
int32_t Greeny;    //      4 bytes
int32_t Bluex;    //       4 bytes
int32_t Bluey;    //       4 bytes
}
using png_cHRM = pngC<png_cHRMd>;

enum pngsRGB {
 Perceptual =0,
 Relative_colorimetric =1,
 Saturation =2,
 Absolute_colorimetric =3
}
typedef int8_t png_sRGBd ;
using png_sRGB = pngC<png_sRGBd> ;

struct png_iCCPd {
    char* str;
    int8_t null;
    int8_t compression;
    int8_t *nBytes;
}
using png_iCCP = pngC<png_iCCPd> 
struct png_tEXtd {
    char* str;
    int8_t null;
    int8_t *nBytes;
}
using png_iTXt = pngC<png_tEXtd>; 
using png_zTXt = pngC<png_iCCPd> ;

struct png_iTXtd {
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
using png_iTXt = pngC<png_iTXtd>;

using png_bKGD = pngC<png_tRNSd>;
struct png_pHYsd {
    int32_t unitx;
    int32_t unity;
    int8_t unitSpecifier;
}
using png_pHYs = pngC<png_pHYsd>;
union png_sBITd {
    int8_t zero;
    int8_t two[3];
    int8_t three[3];
    int16_t four;
    int32_t six;
};
using png_sBIT = pngC<png_sBITd>;

struct png_sPLTd {
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
using png_sPLT = pngC<png_SPLd>;

typedef uint16_t* png_hISTd ;
using png_hIST = pngC<png_hISTd>;

struct png_tIMEd {
   uint16_t Year;//:   2 bytes (complete; for example, 1995, not 95)
   uint8_t Month;//:  1 byte (1-12)
   uint8_t Day;//:    1 byte (1-31)
   uint8_t Hour;//:   1 byte (0-23)
   uint8_t Minute;//: 1 byte (0-59)
   uint8_t Second;//: 1 byte (0-60) 
}
using png_tIME = pngC<png_tIMEd>;
struct png {
    pngHeader head;
    std::vector<pngu> chunks;

    image2D ld(std::string path ){
        png p ;
        std::ifstream fi(path);
        ld<pngHeader>(p.head,fi);

        png_IDHR PIDHR;png_PLTE PPLTE; list<png_IDAT> PIDAT; png_IEND pIEND ;

        #define PNG_DEF(p) png_##p P##p ;
        REPEAT(PNG_DEF bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt)
        

        png_tRNS PtRNS ;

        while(!fi.eof()){
            pngChunk  pc;
            ld<pngChunk>(pc,fi);
            
            switch(pc.name){
                case pngIDHR : {PIDHR =png_IDHR(pc);break;}
                case pngPLTE : {PPLTE=pngC<png_PLTEd>(pc);break;}
                case pngIDAT : {PIDAT.push_back(png_IDAT(pc,idhr));break;}
                case pngIEND : {break;};
                case pngtRNS : {
                    PtRNS = pngC<pngtRNSd>(pc) ; 
                    switch(PIDHR.d.colortype){
                        case 3 : {
                            std::memcpy(&PtRNS.d.three,pc.d ,PPLTE.length/3);
                        }
                        case 0 : {
                            std::memcpy(&PtRNS.d.zero,pc.d, pow(2,PIDHR.d.bitdepth)-1);
                        }
                        case 2 : {
                            std::memcpy(&PtRNS.d.two.r,pc.d, pow(2,PIDHR.d.bitdepth)-1);
                            std::memcpy(&PtRNS.d.two.g,pc.d + pow(2,PIDHR.d.bitdepth)-1, pow(2,PIDHR.d.bitdepth)-1);
                            std::memcpy(&PtRNS.d.two.b,pc.d + (pow(2,PIDHR.d.bitdepth) -1)*2  , pow(2,PIDHR.d.bitdepth)-1);
                        };
                        }
                        break;
                    }
                case pnggAMA : {PgAMA = pngC<pnggAMAd>(pc);
                    std::memcpy(&PgAMA.d,pc.d,4);break;
                }
                case pngCHRM :{PcHRM = pngC<pngCHRMd>(pc);};
                case pngsRGB :{psRGB = pngC<pngsRGBd>(pc);};
                case pngiCCP :{piCCP = pngC<pngiCCPd>(pc);int i;
                    for(i=0;pc.d[i]!='\0';i++ ){}
                    std::memcpy(piCCP.d.str,pc.d,i+1);
                    piCCP.d.null = '\0';
                    piCCP.d.compression = pc.d[i+1];
                    std::memcpy(piCCP.d.nBytes,pc.d+i+2);break;
                };
                case png_tEXt :{PtEXt = pngC<pngtEXtd>(pc);int i;
                    for(i=0;pc.d[i]!='\0';i++ ){}
                    std::memcpy(PtEXt.d.str,pc.d,i+1);
                    piCCP.d.null = '\0';
                    std::memcpy(PtEXt.d.nBytes,pc.d+i+1);break;
                };
                case pngzTXt:{PzTXt = pngC<pngiCCPd>(pc);int i;
                    for(i=0;pc.d[i]!='\0';i++ ){}
                    std::memcpy(PzTXt.d.str,pc.d,i+1);
                    PzTXt.d.null = '\0';
                    PzTXt.d.compression = pc.d[i+1] ;
                    std::memcpy(PzTXt.d.nBytes,pc.d+i+2);break;}
                case pngiTXt : {piTXt = pngC<pngiTXtd>(pc);int i;
                    for(i=0;pc.d[i]!='\0';i++ ){}
                    std::memcpy(PiTXt.d.str,pc.d,i+1);
                    PiTXt.d.null = '\0';
                    PiTXt.d.compressionFlag= pc.d[i+1];
                    PiTXt.d.compressionMethod=pc.d[i+2];
                    int j;
                    for(j=i+4;pc.d[j] !='\0';j++){}
                    std::memcpy(PiTXt.d.langtag,pc.d+i+4 ,j+1);
                    PiTXt.d.null2='\0';int k;
                    for(k=i+4 + j+2;pc.d[k] !='\0';k++){}
                    std::memcpy(PiTXt.d.keyword,pc.d+i+4+j+2 ,k+1);
                    PiTXt.d.null3='\0';
                    std::memcpy(PiTXt.d.nBytes,pc.d +i+4+j+2+k+1,pc.length-i-4-j-2-k-1);
                    break;
                }
                case pngbKGD : { PbKGD = pngC<png_tRNSd>(pc);
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
                    break;
                }
                case pngpHYs : {PpHYs = pngC<png_pHYsd>(pc);}
                case pngsBIT : {PsBIT = pngC<png_sBITd>(pc);
                switch(PIDHR.colortype) {
                    case 0:{std::memcpy(&PsBIT.d.zero,pc.d,1)} 
                    case 2:{std::memcpy(&PsBIT.d.two,pc.d,3)} 
                    case 3:{std::memcpy(&PsBIT.d.three,pc.d,3)} 
                    case 4:{std::memcpy(&PsBIT.d.four,pc.d,2)}
                    case 6:{std::memcpy(&PsBIT.d.six,pc.d,4)} 
                }
                break;
                }
                case pngsPLT :{PsPLT = pngC<png_sPLTd>(pc);
                    int i;
                    for(i=0;i<pc.d[i]!='\0';i++){}
                    std::memcpy(PsPLT.d.PaletteName,pc.d,i+1);
                    PsPLT.d.null='\0';
                    PsPLT.d.Sampledepth = pc.d[i+1];
 
                    int l = PsPLT.length - i -2;
                    switch(PsPLT.d.Sampledepth){
                        case 8 : {
                            PsPLT.d.pl = new png_sPLTd::rgbf[2* l/6];
                            for(int i=0;l>0;i++){
                                std::memcpy(&PsPLT.d.pl[i].one,pc.d+i+2 +i*6,4);
                                std::memcpy(&PsPLT.d.pl[i].frequency,pc.d+i+2 +i*6 +4,2);
                            }
                        }
                        case 16 : {
                            PsPLT.d.pl = new png_sPLTd::rgbf[2* l/10];
                                for(int i=0;l>0;i++){
                                std::memcpy(&PsPLT.d.pl[i].two,pc.d+i+2 +i*10,4);
                                std::memcpy(&PsPLT.d.pl[i].frequency,pc.d+i+2 +i*10 +8,2);
                            }

                        }
                    };
                    break;
                }
                case pnghIST : {PhIST = pngC<png_hISTd>(pc);
                    std::memcpy(PhIST.d, pc.d,pc.length);break;
                }
                case pnhtIME : {PtIME = pngC<png_tIMEd>(pc);}
                };
            p.chunks.push_back(pc);
        };
        image2D im;
        

    };

    void wr(std::string path,png p ){

    };
    void wr(std::string path,image2d& im){

    };
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
#include <cmath>
struct tga {
    tga_header head;
      int8_t* ID;
    int8_t* colorMapData;
    int8_t* imageData;
    
uint8_t pd;uint8_t byted;
int ac;
int nm;
int nch;
int16 imageFormatBytes ;

    image2D im ;

   
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
    void runLength(int ind,)
    void RunLength(int numCol,int indT,int ind,int8_t (*ptr)(int,int)){

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
}
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

}



image2D StmLoadImage(std::string name){
    // 
    size_t pos = name.find_last_of(".");
    if(pos!=std::string::npos){
        std::string s = name.substr(pos+1,10);
        switch(s){
            case std::string("png"):{png i ;return i.ld(name); } 
            case std::string("tga"):{tga i ; return i.ld(name);}
            case std::string("bmp"):{bmp i;return i.ld(name)}
        }
    }
};