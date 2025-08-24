#ifndef STM_BMP_HPP
#define STM_BMP_HPP
#include "stm.hpp"

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
uint32_t   compressionMethod;//1E	30	4	the compression method being used. See the next table for a ptr::ptr::list of possible values
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
    modules::image2D im;

    
bool alpha;
uint8_t cpalbyd;
uint16_t& pd(){return _BITMAPINFOHEADER.pixeldepth;} ;

    uint16_t& imSize(){return _BITMAPINFOHEADER.imageSize;};
    uint32_t ncolpal;
    uint32_t ncolPal(){return _BITMAPINFOHEADER.nColPalette==0?pow(2,pd()):_BITMAPINFOHEADER.nColPalette;}

    
    uint32_t rowsize;
    uint32_t rowSize(){
        rowsize=ceil(pd()* _BITMAPINFOHEADER.width/32)*4;
    }
    uint32_t pixelarraysize;
    uint32_t height(){return (_BITMAPINFOHEADER.height);}
    uint32_t width(){return (_BITMAPINFOHEADER.width);}
    uint32_t pixelArraySize(){pixelarraysize=rowsize()*abs(_BITMAPINFOHEADER.height);}
    void getCpColor(uint32_t index,void* data,uint8_t nCh){
            uint32_t i = index/(8/pd());
            uint32_t offset = 32- index%pd()*pd() -pd()  ;
            
            uint32_t mask = (1<<pd()-1)<<offset;
            uint32_t t =( pixels[i] );
            uint32_t n = t & mask>>offset;
            
            std::memcpy(data+index*nCh,colorTable+n,nCh);}       

//     #define CPY_COLOR(l,in,i) \
//     uint16_t l =(##lmask& pix )>>s##l; \
//     l = ratio##l * l;\
//     std::memcpy(im.data + i*ncolor +in,&l,1);  

// #define CPY_COLORS(i) { \
//     int8_t iterat=0; \
//        if(rmask){
//            CPY_COLOR(r,iterat,i) \
//            iterat++;} \
//        if(gmask){ \
//            CPY_COLOR(g,iterat,i) \
//            iterat++;} \
//        if(bmask){ \ 
//            CPY_COLOR(b,iterat,i) \
//            iterat++;} \
//        if(rgba and amask){ \
//            CPY_COLOR(a,iterat,i)\
//            iterat++;}\
// }\

std::fstream fs;

float ratioMask(uint32_t mask){
    uint32_t m = mask;
    while(m&0b1 != 0){m>>1;}
    float res =m/(im.byd/length);
}   ; 
void CPY_COLOR(uint32_t* mask,uint8_t in,uint32_t i,uint32_t pix) {

    uint16_t l =(*mask& pix )>>getDistMask(mask); 
    l = ratioMask(mask) * l;
    std::memcpy(im.data + i*byd +in,&l,1);  
}

void _COLORS(uint32_t i , uint32_t pix , void(*COLORSPTR)(uint32_t*,uint32_t i,uint32_t )){
    int8_t iterat=0; 
       if(rmask){
           COLORSPTR(&rmask,iterat,i,pix)
           iterat++;} 
       if(gmask){ 
           COLORSPTR(&gmask,iterat,i,pix)
           iterat++;} 
       if(bmask){ 
           COLORSPTR(&bmask,iterat,i,pix)
           iterat++;} 
       if(rgba and amask){ 
           COLORSPTR(&amask,iterat,i,pix)
           iterat++;}
};

void CPY_COLORS(uint32_t i,uint32_t pix) { 
    _COLORS(i,pix,&CPY_COLOR);
}    

void WR_COLOR(uint32_t* mask,uint8_t in,uint32_t i,uint32_t* pix){
    uint16_t l =(*mask& pix )>>getDistMask(mask); 
    l =  l/ratioMask(mask)  ;
    *pix!=l;
}
void WR_COLORS(uint32_t i,uint32_t* pix) { 
    _COLORS(i,pix,&WR_COLOR);
}

// void RLEWR_COLORS(uint32_t* mask,uint8_t in,uint32_t i,uint32_t pix){
//     uint16_t l =(*mask& pix )>>getDistMask(mask); 
//     l = ratioMask(mask) * l;
//     std::memcpy(im.data + i*byd +in,&l,1);  
// };
// void RLE_GET(uint32_t i,uint32_t pix){
// _COLORS(i,pix,&RLEWR_COLORS);
// };
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

    uint32_t wseq;uint32_t hseq;    uint32_t xseq;uint32_t yseq;

    DWORD findcolr(void* data,uint8_t bpp){
        
        for(DWORD i=0;i<_BITMAPINFOHEADER.nColPalette;i++){
            if(0==std::memcmp(colorTable+i*cpalbyd , data , cpalbyd)){return i;};
        }
        
    };
void cpyImage(uint8_t bpp,uint8_t ncolor){
setVals(bpp);
for(uint32_t i ;i<imageSize;i++){
    uint32_t pix ;
    std::memcpy(&pix,pixels+i* bc,ncolor)
     CPY_COLORS(i,pix)
}
};
void cpyImage(uint8_t bpp,uint8_t ncolor,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
    setVals(bpp);
    fi.seekg(4*(_BITMAPINFOHEADER.width*y+x),std::ios_base::cur)
for(uint32_t i=0;i<h;i++){
    for(uint32_t j=0;i<w;j++){
        uint32_t pix;
        ld(pix,fi);
        CPY_COLORS(i*w+j,pix);
    };
    fi.seekg(4*(_BITMAPINFOHEADER.width-w),std::ios_base::cur)
};
};
void wrImage(uint8_t bpp,uint8_t ncolor,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
    setVals(bpp);
    fs.seekg(4*(_BITMAPINFOHEADER.width*y+x),std::ios_base::cur)
for(uint32_t i=0;i<h;i++){
    for(uint32_t j=0;i<w;j++){
        uint32_t pix;
        std::memcpy(&pix, im.data+i*w+j,4);
        WR_COLORS(i,pix);
        wr(pix,fs);
    };
    fs.seekg(4*(_BITMAPINFOHEADER.width-w),std::ios_base::cur)
};
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
            CPY_COLORS(iter,pix)
            iter++;
            uint32_t rle =  pix>>(sr+sg+sb+sa);
            for(;rle;--rle){
                std::memcpy(im.data+iter*ncolor,im.data+(iter-1)*ncolor,ncolor);
                    ++iter;
            }
    };
}
    void RLEr(uint8_t bpp,uint8_t ncolor,uint32_t w,uint32_t h,uint32_t x,uint32_t y ){
         setVals(bpp);
        uint32_t iter=0;
        uint32_t lim = y*width()+x;
        uint8_t val = 0;
        uint32_t pix;
        for(uint32_t i=0;i<lim;i+=val){
            ld(pix,fi);
            val = pix>>(sr+sg+sb+sa);
        };
        uint8_t over = (i-lim); 
        uint32_t lastrl = over<<(sr+sg+sb+sa);
        lastrl |= (pix&(rmask))|(pix&(bmask))|(pix&(gmask))|(pix&(amask));        
        for(uint32_t i=0;i<h;i++){
            
            for(uint32_t j=over;j<w;j+=val){
                ld(&pix,fi);
                val = pix>>(sr+sg+sb+sa);
                CPY_COLORS(iter,pix)
                iter++;
                uint32_t rle = val> w-1 ? w-1 : val ; 
                for(;rle;--rle){
                    std::memcpy(im.data+iter*ncolor,im.data+(iter-1)*ncolor,ncolor);++iter;}
            }
            over = j  - lim;
             uint32_t lastrl = over<<(sr+sg+sb+sa);
        lastrl |= (pix&(rmask))|(pix&(bmask))|(pix&(gmask))|(pix&(amask));        
            
            for(uint32_t k =over ; k<width() - w ; k++){
                ld(&pix,fi);
                val = pix>>(sr+sg+sb+sa);
            };
            over = k-(width() + w) ;
            rle = over ;
            iter++;
for(;rle;--rle){std::memcpy(im.data+iter*ncolor,im.data+(iter-1)*ncolor,ncolor);++iter;}

        }
}
    void RLEwr(uint8_t bpp,uint8_t ncolor,uint32_t w,uint32_t h,uint32_t x,uint32_t y ){
          setVals(bpp);
          uint32_t mask = rmask | gmask | bmask | amask; 
        auto rle = [](uint32_t val ) {
            return (val - (val & mask))>>getSizeMaks(&mask);
        };
        auto rleadd = [](uint32_t& val,uint8_t v ) {
            val+= v<<getSizeMask(&mask);          };
        
            std::vector<uint32_t > rleim;
            std::vector<uint32_t> rleiminds{0};uint32_t indim;
            auto rlepush = [](uint32_t ind){
                uint8_t pix[4];
                std::memcpy(pix,im.data+ind*byd,4);
                uint32_t res;
                    int8_t iterat=0; 
       if(rmask){
        res|=(pix[iterat]/ratioMask(rmask))<<(rs);
           iterat++;} 
       if(gmask){ 
        res|=(pix[iterat]/ratioMask(gmask))<<(rg);
           iterat++;} 
       if(bmask){ 
                res|=(pix[iterat]/ratioMask(bmask))<<(rb);

           iterat++;} 
       if(rgba and amask){ 
                res|=(pix[iterat]/ratioMask(amask))<<(ra);
           iterat++;}
            
            rleim.push_back(res);}
         for(uint32_t i =0;i<im.height;i++){
            uint32_t j=0
             uint32_t pix ; 
                        std::memcpy(&pix,im.data+(i*w+j)*im.byd,4);
                        rlepush(pix);
            j++;
             for(uint32_t j=1;j<im.width;j++){
                 if(0==std::memcmp(im.data+(i*w+j)*im.byd,im.data+(i*w+j-1)*im.byd,im.byd)){
                     rleadd(rleim.back());
                     rleiminds.back()++;
                    }
                    else {
                        uint32_t pix ; 
                        std::memcpy(&pix,im.data+(i*w+j)*im.byd,4);
                        rlepush(pix);}
            };
rlemiminds.push_back(rlemiminds.back()+1)
         };

        //   for(uint32_t i = 0 ; i< )
        uint32_t iter=0;
        uint32_t lim = y*width()+x;
        uint8_t val = 0;
        uint32_t pix;uint32_t i;
        uint32_t offs= 0;
        for(i=0;i<lim;i+=val){
            ld(pix,fs);offs+=4;
            val = pix>>(sr+sg+sb+sa);
        };
        uint8_t over = (i-lim); 
        uint32_t lastrl = over<<(sr+sg+sb+sa);
        lastrl |= (pix&(rmask))|(pix&(bmask))|(pix&(gmask))|(pix&(amask));        
        std::vector<uint32_t > val;
        std::vector<uint32_t > valinds; uint32_t indval=0;
        for(uint32_t i=0;i<h;i++){
            uint32_t j;
            for(uint32_t j=over;j<w;j+=val){
                ld(&pix,fs);offs++;
                val = pix>>(sr+sg+sb+sa);
            };

            over = j-lim;
            for( j=over;j<width()-w;j+=val){
                ld(&pix,fs);offs++;val.push_back(pix);valinds.back()++;
                val = pix>>(sr+sg+sb+sa);
            }
            valinds.push_back(valinds.back()+1);
             uint32_t lastrl = over<<(sr+sg+sb+sa);
        lastrl |= (pix&(rmask))|(pix&(bmask))|(pix&(gmask))|(pix&(amask));        
            
        uint32_t rles=rleiminds[indim+1]- rleiminds[indim];
            uint32_t vals=valinds[indval+1] -valinds[indval];
            while(offs>vals+rles){
                for(int i=rleiminfs[indim];i<rles;i++){
                    wr(rleim[i],fs);offs--;
                };
                indim++;
                for(int i=valinds[indval];i<vals;i++){
                    wr(val[i],fs);offs--;
                };indval++;
            
        uint32_t rles=rleiminds[indim+1]- rleiminds[indim];
            uint32_t vals=valinds[indval+1] -valinds[indval];
            }
        }
        while(!fs.eof()){
            uint32_t lim = offs;
            for( uint32_t j=0;j<lim;j+=val){
                ld(&pix,fs);offs++;val.push_back(pix);valinds.back()++;
            }
            valinds.push_back(valinds.back()+1);
            uint32_t vals=valinds[indval+1] -valinds[indval];
            while(offs>vals){
                for(int i=valinds[indval];i<vals;i++){
                    wr(val[i],fs);offs--;
                };indval++;
                uint32_t vals=valinds[indval+1] -valinds[indval];
            }
        }
        for(;indval<valinds.size();indval++){
            for(int i=valinds[indval];i<vals;i++){
                wr(val[i],fs);offs--;
            };
        }
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
                    im.data=new char[width()*height()*3];
                    
                        for(uint32_t i=0;i<imageSize;i++ ){
                            for(uint8_t j=0;j<4;j++){
                            uint8_t r;   
                            std::memcpy(&r,pixels+i*2,imageSize*4);
                            r = r*ratio;
                            std::memcpy(im.data+i*4+j,&r,1);
                        }
                    return;
                 }
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
                    getCpColor(i,im.data,ncolor);
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
    void getColorR(uint8_t bpp){
         uint8_t ncolor= bool(rmask) + bool(gmask) + bool(bmask);
        if(alpha){ncolor+=bool(amask);}
        if(bpp==32){
                fs.seekg(4*(yseq*width()+x),std::ios_base::cur)
                for(uint32_t i =0;i<hseq;i++){
                    ld(im.data+4*wseq*i,wseq*4,fs);
                    fs.seekg(4*(width()-wseq)+x),std::ios_base::cur)
                }
            
            return;
        };
        if(bpp==24 ){
                if(_BITMAPINFOHEADER.compressionMethod == BI_JPEG){
                    RLEr(24,ncolor,wseq, hseq, xseq, yseq);
                    return 
                }
                if(maskb==mask::rgb){
                    im.imageFormat=image_formats::rgb8;
                    fs.seekg(3*(yseq*width()+x),std::ios_base::cur)
                for(uint32_t i =0;i<hseq;i++){
                    ld(im.data+4*wseq*i,wseq*4,fs);
                
                    fs.seekg(3*(width()-wseq)+x),std::ios_base::cur)
                }
                    im.swaprg();
                    return;
                }
        }
        
        if(bpp==16){
            if(maskb==mask::rgba){
                if ((getSizeMask(&rmask)==4)and
                and (getSizeMask(&gmask)==4)
                and (getSizeMask(&bmask)==4)
                and (getSizeMask(&amask)==4)){
                    float ratio = UCHAR_MAX/((1<<4) -1);
                    im.imageFormat=image_formats::rgba8;
                    im.data=new char[width()*height()*3];
                        fs.seekg(2*(yseq*width()+x),std::ios_base::cur);
                        for(uint32_t i=0;i<imageSize;i++ ){
                            for(uint8_t j=0;j<2;j++){
                                uint8_t r;   
                                uint8_t a;
                                ld(r,fs);
                                a =(r&0b11110000>>4)*ratio;
                            std::memcpy(im.data+i*4+j,&a,1);
                                a =(r&0b1111)*ratio;
                            std::memcpy(im.data+i*4+j+1,&a,1);
                        }
                        
                    }
                    return;
                
                }
            }   
        };
        if(bpp==8){
            if(_BITMAPINFOHEADER.compressionMethod == BI_RLE8){
                RLEr(8,ncolor);
                return;
            }
            else {
                im.imageFormat=image_formats::argb8;
                fs.seekg( bpp*(width()+xseq),std::ios_base::cur)
                for (int i = 0; i < hseq; i++)
                {
                    for (int j = 0; j <wseq; i++)
                    {
                        DWORD pix ;
                        ld(pix,fs);
                        std::memcpy(im.data+(i*wseq+j)*im.byd , colorTable+pix*4,4);
                    }
                fs.seekg((width()-wseq)*4),std::ios_base::cur)                    
                }
                im<<1;i.imageFormat=image_formats::rgba8;
                return;
            }
        };
        if(bpp == 4 and (_BITMAPINFOHEADER.compressionMethod == BI_RLE4)){
            RLEr(4,ncolor);
        }
        cpyImage(bpp,ncolor,wseq,hseq,xseq,yseq);

    }
 void putColorR(uint8_t bpp){
         uint8_t ncolor= bool(rmask) + bool(gmask) + bool(bmask);
        if(alpha){ncolor+=bool(amask);}
        if(bpp==32){
                fs.seekg(4*(yseq*width()+x),std::ios_base::cur)
                for(uint32_t i =0;i<hseq;i++){
                    wr(im.data+4*wseq*i,wseq*4,fs);
                
                    fs.seekg(4*(width()-wseq)+x),std::ios_base::cur)
                }
            
            return;
        };
        if(bpp==24 ){
                if(_BITMAPINFOHEADER.compressionMethod == BI_JPEG){
                    RLEwr(24,ncolor);
                    return 
                }
                if(maskb==mask::rgb){
                    im.imageFormat=image_formats::rgb8;
                    fs.seekg(3*(yseq*width()+x),std::ios_base::cur)
                for(uint32_t i =0;i<hseq;i++){
                    wr(im.data+4*wseq*i,wseq*4,fs);
                
                    fs.seekg(3*(width()-wseq)+x),std::ios_base::cur)
                }
                    return;
                }
        }
        
        if(bpp==16){
            if(maskb==mask::rgba){
                if ((getSizeMask(&rmask)==4)and
                and (getSizeMask(&gmask)==4)
                and (getSizeMask(&bmask)==4)
                and (getSizeMask(&amask)==4)){
                    float ratio = UCHAR_MAX/((1<<4) -1);
                    im.imageFormat=image_formats::rgba8;
                    im.data=new char[width()*height()*3];
                        fs.seekg(2*(yseq*width()+x),std::ios_base::cur);
                        for(uint32_t i=0;i<imageSize;i++ ){
                            for(uint8_t j=0;j<2;j++){
                                uint8_t r;   
                                uint8_t a;
                                std::memcpy(&a,im.data+i*4+j,1);
                                r +=a/ratio<<4;
                                std::memcpy(&a,im.data+i*4+j+1,1);
                                r +=a/ratio;
                                wr(r,fs);
                        }
                    }
                    return;
                
                }
            }   
        };
        if(bpp==8){
            if(_BITMAPINFOHEADER.compressionMethod == BI_RLE8){
                RLEwr(8,ncolor);
                return;
            }
            else {
                im.imageFormat=image_formats::argb8;
                fs.seekg( bpp*(width()+xseq),std::ios_base::cur)
                for (int i = 0; i < hseq; i++)
                {
                    for (int j = 0; j <wseq; i++)
                    {
                        DWORD pix = findcolr(bpp, im.data+(i*wseq+j)*im.byd);
                        wr(pix,fs);
                    }
                fs.seekg((width()-wseq)*4),std::ios_base::cur)                    
                }
                return;
            }
        };
        if(bpp == 4 and (_BITMAPINFOHEADER.compressionMethod == BI_RLE4)){
            RLEwr(4,ncolor);
        }
        wrImage(bpp,ncolor,wseq,hseq,xseq,yseq);

    }
    
    std::ifstream fi;
    void init(){
im = image2d();
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
        if(head.field != bmpHead::Field::BM){
            ld(_OS22XBITMAPHEADER,fi);
        }
        ncolpal = ncolPal(); 

        
    };
    modules::image2D ld(std::string path,uint32_t w,uint32_t h,uint32_t x,uint32_t y ){
        fi=std::ifstream(path);
        ld(this->head,fi);
        init();
                rowSize();
        pixelArraySize();
        
        ld(colorTable,ncolpal,fi);
        getColor(pd());

    };
    image2D ld(std::string path){
         fi=std::ifstream(path);
        ld(this->head,fi);
        init();        
        rowSize();
        pixelArraySize();
        
        ld(colorTable,ncolpal,fi)
        ld<DWORD>(pixels,0,head.Offset,imageSize,fi);
        getColor<false>(pd());
    }
    void wr(sd::string path,image2D& im){
        std::ofstream of(path);
        _BITMAPINFOHEADER.width=im.width;
        _BITMAPINFOHEADER.height=im.height;
        _BITMAPINFOHEADER.imageSize=im.byd*im.imageSize;
        pd()=8*im.byd;
        head.field = bmpHEAD::Field::BA;

        wr(head,of);
        wr(_BITMAPINFOHEADER,of);
        wr(im.data,_BITMAPINFOHEADER.imageSize,of);
         
    };  
}
#endif