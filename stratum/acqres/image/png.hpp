#ifndef STM_PNG_HPP
#define STM_PNG_HPP
#include "stm.hpp"

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
    uint32_t length;
    uint32_t name;
    data d;
    int32_t crc;
    int32_t size(){return length+12;}
    void set(pngC<uint8_t*>& pc){
        length=pc.length;
        name=pc.name;
        crc=pc.crc;
    }
    pngC<data>(pngC<int8_t*>& pc){
        set(pc);
        if constexpr (std::is_pointer<data>::value or std::is_array<data>::value){
            std::memcpy(d,pc.bytes,length);}
        else {std::memcpy(&d,pc.bytes,length);}
    }
    pngC<uint8_t*> get(){
        pngC<uint8_t*> res;res.length=length;res.name=name;res.crc=crc;
        res.d = new uint8_t[length];
        if constexpr (std::is_pointer<data>::value or std::is_array<data>::value){
            std::memcpy(pc.d,d,length);    }
        else {std::memcpy(pc.d,&d,length);                }

    }
};

using pngChunk  = pngC<uint8_t*> ;
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

    IDHR PIDHR;PLTE PPLTE; IDAT PIDAT; IEND PIEND ;
    #define PNG_DEF(p) ##p P##p ;
    REPEAT(PNG_DEF, bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt )

    float gamma(){return PgAMA.d /100000}
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
                for( i=0;i<bdmul(destLen);i++) {
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
            idat = PIDAT  
                if(idat.length < IDAT_MAX_SIZE) {
                decomp =std::vector<uint8_t>(idat.length * 1032);
                    uncompress(decomp.data(),&destLen,idat.d,idat.length)    ;
                    decomp.resize(destLen);
                    Adam7Handle(i,im,loadPixel);
                }
                else {std::cerr("IDAT chunk too big");return;}
                i++;};
        
        inline uint32_t bdmul(uint32_t x){return bd()<8 ? x *(8/bd()) : x/(bd()/8)} 
    void loadNormalHandle(image2D& im,void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
    
         if(loadPixel == loadPlte){
                   pltemask= 1<<bd() - 1;uint64_t i;
                   uint8_t size=bdmul(destLen);
                for( i=0;i<size;i++) {
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
        // pix=0;    
        idat=  PIDAT ; 
            if(idat.length < IDAT_MAX_SIZE ){
                decomp =std::vector<uint8_t>(idat.length * 1032);
                uncompress(decomp.data(),&destLen,idat.d,idat.length);
                decomp.resize(destLen);
                loadNormalHandle(im,loadPixel);
            }
            else {std::cerr("IDAT Chunk To big")return;}
        
    }
    uint32_t pixseq;uint32_t pixFull;
    void loadNormal(image2D& im,uint32_t w,uint32_t h,uint32_t x,uint32_t y,void (*loadPixel)(image2D& ,uint64_t , uint64_t )){
        
        idat=PIDAT;
            if(idat.length < IDAT_MAX_SIZE ){
                decomp =std::vector<uint8_t>(idat.length * 1032);
                uncompress(decomp.data(),&destLen,idat.d,idat.length);
                decomp.resize(destLen);
                
                uint16_t size= bdmul(destLen);  
                uint32_t opix = pix;uint16_t lines;
                uint32_t eoffs ;
                if(pix+size >(y*width() + x )){
                    uint16_t firstLine = y*width() + x ;   
                    for(;firstLine>pix;firstLine+=width());
                    uint16_t poffs = firstLine-pix ;
                    uint16_t offset =   bdmul(x - (pix%width()));
                    ULongF destlenc=destLen;
                    eoffs = (size -offset)%width();
                     lines = linesSize/width(); 
                    std::vector<uint8_t> decopy = decomp;uint16_t sizeWidth = bdmul(width());;
                    destLen = bdmul(w);
                    for(uint32_t i =0;i<lines-1;i++ ){
                        pixseq=pix;
                        pix=w*(i+ (pix)/width())  ;
                        std::memcpy(decomp.data(),decopy().data()+sizeWidth*i+ offset , destLen);
                        loadNormalHandle(im,loadPixel);
                        pix=pixseq + width() ;
                    }
                    pixseq=pix;
                    pix=w*(lines-1 +pix/width() );
                    destLen = (destLenc-offset)&destLen ;
                    std::memcpy(decomp.data(),decopy().data()+sizeWidth*(lines-1) + offset,destLen );
                    loadNormalHandle(im,loadPixel);
                    pix = opix+poffs + (lines-1)*width() + eoffs;
                } 
            }
            else {std::cerr("IDAT Chunk To big")return;}
        
    };
     void (*loadPixel)(image2D& ,uint64_t , uint64_t ) ;
    void loadImage(image2D& im){
        if(PIDHR.interlace) {loadAdam7(im,loadPixel);}
        else {loadNormal(im,loadPixel);}
    }
    void loadImage(image2D& im,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        if(PIDHR.interlace) {loadAdam7(im,loadPixel);}
        else {loadNormal(im,loadPixel);}
    }


    std::ifstream& fi;
        std::fstream& fs;

    // image2D im;
    // Returns true if idat 
            #define BOOL_CHUNK(n) bool b##n=false;
        REPEAT(BOOL_CHUNK ,PLTE,bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt) 

    void idhrInit(image2D& im){
        im.width = width();
        im.height = height();
                
        if(PIDHR.compression != 0){std::cerr(std::string("IDHR chunk compression field value not 0 in image : ") +path ) ;}
        if(PIDHR.filter != 0){std::cerr(std::string("IDHR chunk filter field value not 0 in image : ") +path );}
        if(PIDHR.interlace != 0  or (PIDHR.interlace != 1)){std::cerr(std::string("IDHR chunk interlace value unknown in image :")+path );}
        im.init();
        pix=0;
        switch(PIDHR.colortype){
            case IDHRd::colorType::grayscale : {
                switch(bd()){ nch=1;
                case 1 : {im.imageFormat = image_formats:r8ui;}
                case 2 : {im.imageFromat = image_formats:r8ui;}
                case 4 : {im.imageFromat = image_formats:r8ui;}
                case 8 : {im.imageFromat = image_formats:r8ui;}
                case 16 : {im.imageFromat = image_formats:r16ui;} }
                loadPixel=&loadData;break;}
            case IDHRd::colorType::rgb : {nch=3;
                switch(bd()){
                case 8 : {im.imageFromat = image_formats::rgb8ui;}
                case 16 : {im.imageFromat = image_formats::rgb16ui;}}; loadPixel=&loadData;break;}
            case IDHRd::colorType::palette : {nch=3;im.imageFormat = image_formats.rgb8ui;loadPixel=&loadPlte;break;}        
            case IDHRd::colorType::grayscalealpha : {nch=2;
                switch(bd()){
                    case 8 : {im.imageFromat = image_formats::rg8ui;}
                    case 16 : {im.imageFromat = image_formats::rg8ui;}}
                loadPixel=&loadData;break;}
            case IDHRd::colorType::rgba : {nch=4;
                switch(bd()){
                    case 8 : {im.imageFromat = image_formats::rgba8ui;}
                    case 16 : {im.imageFromat = image_formats::rgba8ui;}}
                loadPixel=&loadData;break;}     
        }
    };
    void loadIDAT(mod::image2D& im){loadImage(im);}
    uint32_t seqW;uint32_t seqh;uint32_t seqx;uint32_t seqy;
    void loadIDATr(mod::image2D& im){loadImage(im,seqW,seqH,seqx,seqy);}
    pngChunk pc;
    template <typename stream>
    bool loadChunks(stream& fstr,mod::image2D& im,void loadidat(mod::image2D&)){
            ld<pngChunk>(pc,fstr);
            switch(pc.name){
                case pngIDHR :{PIDHR=IDHR(pc);idhrInit(im);return false;}
                case pngPLTE :{bPLTE=true;PPLTE=pngC<PLTEd>(pc);return false;}
                case pngIDAT :{PIDAT=pc;loadidat(im);return true;}
                case pngIEND :{PIEND=pngc<void>(pc);return false;};
                case pngtRNS :{btRNS=true;PrRNS =tRNS(pc,PIDHR,PPLTE);return false;}
                case pnggAMA :{bgAMA=true;PgAMA = gAMA(pc);return false;}
                case pngCHRM :{bCHRM=true;PcHRM = CHRM(pc);return false;}
                case pngsRGB :{bsRGB=true;psRGB = sRGB(pc);return false;}
                case pngiCCP :{biCCP=true;piCCP = iCCP(pc);return false;}
                case pngtEXt :{btEXt=true;PtEXt = tEXt(pc);return false;}
                case pngzTXt :{bzTXt=true;PzTXt = iCCP(pc);return false;}
                case pngiTXt :{biTXt=true;piTXt = iTXt(pc);return false;}
                case pngbKGD :{bbKGD=true;PbKGD = tRNS(pc);return false;}
                case pngpHYs :{bpHYs=true;PpHYs = pHYs(return false);}
                case pngsBIT :{bsBIT=true;PsBIT = sBIT(pc,PIDHR);return false;}
                case pngsPLT :{bsPLT=true;PsPLT = sPLT(pc);return false;}
                case pnghIST :{bhIST=true;PhIST = hIST(pc);return false;}
                case pnhtIME :{btIME=true;PtIME = tIME(pc);return false;}
                };
    };
    image2D ld(std::string path ){
        fi=std::ifstream(path,std::ios::binary);
        mod::image2D im;
        ld<pngHeader>(head,fi);
        while(!fi.eof()){
            bool idatcb = loadChunks<std::ifstream>(fi,im,&loadIDAT);
        }
        return im;
    };
    image2D ld(std::string path,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        fi=std::ifstream(path,std::ios::binary);
        mod::image2D im; 
        ld<pngHeader>(p.head,fi);
        seqW=w,seqH=h,seqx=x,seqy=y;
        while(!fi.eof()){
            loadChunks<std::ifstream>(fi,im,&loadIDATr);
            if(pix>((y+h)*width()+x)){return im;}
        };
        return im;
    };
    void wrPlte(image2D& im,uint64_t pt,uint64_t index){ // Index maybe size;
        uint64_t pltes=PLTE.length/3;
        int64_t s =findpalette(PLTE.d,pltes,3,im.data[pts]);

        std::memcpy(decomp.data()+(pt*bd()/8, &s + sizeof(s) - (bd()/8), bd()/8) );  
    }   ; 
    void wrData(image2D& im,uint64_t pt,uint64_t index){
        uint64_t len = destLen ;
        if(bd()<8 or (bd()/nch)<8){
            wrDataArrSubBytes(im,pt,len,bd(),demcomp.data());}
        else {
            switch(im.imageFormat){
                #define IMAGEFORMAT_CASE_LOAD(imf) \
                case image_formats::imf :{wrDataArr<image_formats::imf>(im,pt,len,bd(),decomp.data());};
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
        if(wrPixel==wrPlte){paletteGenerate(im,PLTE.d,&PLTE.length);
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
            wrData(im,wrPixel);
        }
    }
    void* plteRInds;
    void wrNormal(image2D& im,uint32_t w,uint32_t h,uint32_t x,uint32_t y,void (*wrPixel)(image2D& ,uint64_t , uint64_t )){
        pixseq=pix;
        uint32_t size = bdmul(destLen);
        int16_t off = x- pix%width() ;
        uint32_t firstLine = ((pix + off) / width()) / y ;
        uint16_t lines = (pix - Off + destLen) / width() +1;
        int16_t endoff = x - ((pix+size)%width());
        if(wrPixel==wrPlte){ uint16_t bytde=bdmul(1);
        if(off<0) {
            std::memcpy(decomp.data() + off*bytde,plteRInds + (firstLine*w + off)* bytde, bytde * (w-(pix+off)%width()%w )  );
        }
        for(uint32_t i = firstLine + 1*!(off>0) ;i<lines-1 + firstLine;i++){
            std::memcpy(decomp.data()+ ((i-firstLine)*width() + off)*bytde, plteRInds+(i*w)*bytde,w*bytde);}
            if(enoff<0){
                std::memcpy(decomp.data()+ ((i-firstLine)*width() + off)*bytde, plteRInds+i*w*bytde,(w+endoff)*bytde + );
            }
            else {std::memcpy(decomp.data()+ ((i-firstLine)*width() + off)*bytde, plteRInds+i*w*bytde,w*bytde);} 
                return ;}
        else {
            uint16_t bytde=im.byd;
            bd() = im.bd;
            // decomp.resize(im.byd * im.imageSize);
            // destLen=im.imageSize*im.byd;
              if(off<0) {
            std::memcpy(decomp.data() + off*bytde,im.data + (firstLine*w + off)* bytde, bytde * (w-(pix+off)%width()%w )  );
        }
        for(uint32_t i = firstLine + 1*!(off>0) ;i<lines-1 + firstLine;i++){
            std::memcpy(decomp.data()+ ((i-firstLine)*width() + off)*bytde, im.data+(i*w)*bytde,w*bytde);}
            if(enoff<0){
                std::memcpy(decomp.data()+ ((i-firstLine)*width() + off)*bytde, im.data+i*w*bytde,(w+endoff)*bytde + );
            }
            else {std::memcpy(decomp.data()+ ((i-firstLine)*width() + off)*bytde, im.data+i*w*bytde,w*bytde);} 
            // wrData(im,wrPixel);
        }   
    }
    queue<pngChunk> pcc;
    uint64_t chunksSize=0; int32_t wrroffs=0; int32_t sizech ;// Add int
    // void (*writePixel)(image2D& ,uint64_t , uint64_t );
    void wrImage(image2D& im,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        uint32_t max= IDAT_MAX_SIZE * 512;destLen=max;
        uncompress(decomp.data(),&destLen,PIDAT.d,PIDAT.length);
        chunksSize=PIDAT.size();
        if(pix+bdmul(destLen) > y *width() + x and (pix< x+w+(h+y)*width() ) ) {
        uint64_t paletteSize = PLTE.length;
        if(PIDHR.interlace) {wrAdam7(im,wrPixel);}
        else {wrNormal(im,w,h,x,y,wrPixel);}
        }
        else {pix+=bdmul(destLen)};

        // for(uint64_t i=0 ;i<decomp.size();i+=destLen){
                compress(PIDAT.d,&(PIDAT.length),decomp.data() ,destLen);
                // wroffs-=pc.size();
                if(wroffs<=pc.size()+PIDAT.size()){
                    fs.seekg(wrroffs+pc.size(),std::ios_base::cur);
                    wr(PIDAT,fs);
                    fs.seekg(+PIDAT.size()-wroffs-pc.size(),std::ios_base::cur);
                    wroffs+=PIDAT.size();
                } 
                else {pcc.push(PIDAT.get());}
        // }
    };
    
    void wrImage(image2D& im, void (*wrPixel)(image2D& ,uint64_t , uint64_t )){
        if(PIDHR.interlace) {wrAdam7(im,wrPixel);}
        else {wrNormal(im,wrPixel);}
        uint32_t max= IDAT_MAX_SIZE * 512;destLen=max;
        // PIDAT=(IDAT());
        for(uint64_t i=0 ;i<decomp.size();i+=destLen){
            uint32_t destLen=max;
            for(PIDAT.length>IDAT_MAX_SIZE;destLen/=2){
                compress(PIDAT.d+i*max,&(PIDAT.length),decomp.data() + i,destLen);
                wr(PIDAT,of);
                PIDAT = IDAT();
            };
        }
    };
    void wr(std::string path,mod::image2D& im ){
        *this = png() ;
        bool plt=true;
        
        // #define BOOL_CHUNK(n) bool b##n=false;
        // REPEAT(BOOL_CHUNK ,PLTE,bKGD,cHRM,cICP,dSIG,eXIf,gAMA,hIST,iCCP,iTXt,pHYs,sBIT,sPLT,sRGB,sTER,tEXt,tIME,tRNS,zTXt,IEND)

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
    void loadIDATwrR(mod::image2D& im){wrImage(im,seqW,seqH,seqx,seqy);}
    void wr(mod::image2D,std::string path,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        fs = std::fstream(path,std::ios::binary);
        seqW=w;seqH=h;seqx=x;seqy=y; 
        ld<pngHeader>(head,fs);
        while(!fi.eof()){
            loadChunks<std::fstream>(fs,im,&loadIDATwrR);
            wroffs-=pc.size();
            if(pc.name == pngPLTE) {
                uint32_t pltesize = PLTE.length/3;
                    uint32_t cppltesize =pltesize;
                
                paletteAdd(im,PPLTE.d,&pltesize,PIDHR.d.bitdepth/8,plteRInds);
                PPLTE.length*=3;bolPlte=false;
                wroffs += -ccpltesize ;
                pcc.push(PPLTE.get());
            }
            if(pc.name != pngIDAT){
                if(!pcc.empty()){
                    while(wroffs<=0 and  !pcc.empty()){
                        chunksSize=pcc.front().size();
                        fs.seekg(wroffs ,std::ios_base::cur);
                        wr(pcc.front(),fs);
                        wroffs+=chunksSize;
                        pcc.pop();
                    }    
                }
            }            
};
fs.seekg(wroffs ,std::ios_base::cur);
while(!pcc.empty()){
    wr(pcc.front(),fs);
    pcc.pop();
}

    };  
    png() {head = pngHeader();};
}
#endif