
#ifdef STM_IMAGE_GIF
#include "stm.hpp"

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
    
    modules::image2D ld(std::string path){
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
        paletteGenerate(aim[0],GIFCOLORTABLE,&destplt);
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

#endif