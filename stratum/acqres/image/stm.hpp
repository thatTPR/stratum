#ifndef STMIMG_STM
#define STMIMG_STM
#include <cstdint>
#include <stratum/modules.hpp>
#include <vector>
#include <petri/macros.hpp>
#include <petri/list.hpp>
#include <petri/queue.hpp>
#include "../acqres.hpp"
#include <glm/glm.hpp>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "../clib.hpp"
#include <cmath>
#include <limits.h>
#include <type_traits>

/*
PNG [x]
JPEG []
BMP [/]
TGA [x]
GIF []
HDR
*/

mod::image2D sRGBto_YCC(mod::image2D& im){
    mod::image2D res;
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
mod::image2D YCCtoRGB(mod::image2D& im){
    mod::image2D res;
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



int64_t findpalette(void* palette,uint64_t *palettesize,size_t entrysize,void* entry){
    uint64_t n=*palettesize/2;
    uint8_t h=0;
    for(uint64_t i=*palettesize/2;i>0;i=<*palettesize;){
        int s =std::memcmp(palette+(i-1)*entrysize,entry,entrysize)
        if(s==0){return i;}
        if(h==4){return -1;}
        if(n==1){h++;n=1}
        else {n/=2;}
        if(s<0){i+=n;}
        else {i+=n;}
    };
    return -1;
} ;
int64_t Searchpalette(void* palette,uint64_t *palettesize,size_t entrysize,void* entry){
    for(uint64_t i=0;i<*palettesize;i++){
        if(0==std::memcmp(palette+i*entrysize),entry,entrysize){return i;}
    };
    return -1;
};

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

};
void palettePush( void* palette,uint64_t* palettesize,size_t entrysize,,void* color){
    void* temp = new uint8_t[(palettesize+1)*entrysize ];
    std::memcpy(temp,palette,(*palettesize)*entrysize);
    std::memcpy(temp+(*palettesize)*entrysize ,color,entrysize);
    *palettesize++;
    std::memcpy(palette,temp,(*palettesize)*entrysize);
};
void paletteAdd(image2D& im, void* palette,uint64_t* palettesize,size_t indexSize , void* resinds ){
    res = new uint8_t[8*im.imageSize];
    for(uint64_t j=0;j<im.imageSize;j++){   bool b=false;
        uint64_t i;
        for( i=0;i<*paletteisze;i++){
            if(0==std::memcmp(im.data+j*im.byd,palette+i*im.byd)){
                b=true;break;
            };
        };
        uint8_t r[indexSize] ;
        for(int k=indexSize-1;k>=0;k--){
             r[k] = ((1<<8 - 1) << 8*k ) & i >> (8*k);} ;
        std::memcpy(resinds+j*indexSize,r,indexSize);
        if(!b){palettePush(palette,palettesize,im.byd,im.data+j*im.byd);}
    }
}
void  paletteAdd(image2D& im, void* palette,uint64_t* palettesize, ){
    void* res;
    paletteAdd(im,palette,palettesize,8,res);
}
void paletteGenerate(image2D& im, void* palette,uint64_t* palettesize){
    // *palettesize=0;
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
template <mod::image_formats fm>
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
template <mod::image_fromats fm>
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


/// TODO maybe make object to be consumed by parsers
  // TODO geters and setters
    template <typename ut>
    void get(uint32_t pos){

    };
    template <typename ut>
    void getr(uint32_t pos){

    };
    template <typename ut>
    void getg(uint32_t pos){

    };
    template <typename ut>
    void getb(uint32_t pos){

    };
    
    template <typename ut>
    void geta(uint32_t pos){

    };
    
    template <typename ut>
    void getr(uint32_t pos,ut bdr){

    };
    template <typename ut>
    void getg(uint32_t pos,ut bdg){

    };
    template <typename ut>
    void getb(uint32_t pos,ut bdb){

    };
    
    template <typename ut>
    void geta(uint32_t pos,ut bda){

    };
    
    
    template <typename ut>
    void getr(uint32_t pos,ut rmask){

    };
    template <typename ut>
    void getg(uint32_t pos,ut gmask){

    };
    template <typename ut>
    void getb(uint32_t pos,ut bmask){

    };
    
    template <typename ut>
    void geta(uint32_t pos,ut amask){

    };
    
    

    template <typename ut>
    void get(uint32_t pos,uint8_t bdr,uint8_t bdg,uint8_t bdb,uint8_t bda){
        
    };

    template <typename ut>
    ut get(uint32_t pos,uint64_t rmask,uint8_t gmask,uint8_t bmask,uint8_t amask){
        
    };


#endif