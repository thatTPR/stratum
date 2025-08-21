#ifndef STM_TGA_HPP
#define STM_TGA_HPP
#include "stm.hpp"
struct tga {
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
    tga_header head;
    uint8_t* ID;
    uint8_t* colorMapData;
    uint8_t* imageData;
    uint8_t* rleregion;
uint8_t pd;uint8_t byted;
int ac;
int nm;
int nch;
uint8_t imageFormatBytes ;
uint32_t imDatas;
    modules::image2D im ;
    std::ifstream fi;

    uint8_t& cm_EntrySize(){return head.Color_map.entrySize;}
    uint16_t& cm_length(){return head.Color_map.length;}
    int8_t& pd(){return head.Image.pixelDepth;}
   
void setFormat(){
        im.imageFormat = ac>0?rgba32ui:rgb32ui;
if (ac > 0){im.imageFormat = rgba32ui;
    imageFormatBytes = modules::imageFormatBytes(image_formats::rgba32ui);}
else {im.imageFormat = rgb32ui;    
    imageFormatBytes = modules::imageFormatBytes(image_formats::rgb32ui);}
    }
    template <typename K>
    int8_t& getColorMap(int indt,int Offset){
        K* d =imageData+indt;
        return colorMapData[*d+Offset];
    };
    int8_t& getRgb(int indt,int Offset){
        return imageData[indt+Offset];
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

        for(int i=0;i<imDatas;i++){ 
             int indT = i*byted;int ind=i*imageFormatBytes ;
            alpha(ind,indT,ptr);
            colors(ind,indT,ptr);}
    }
   
    template <typename key>
    void loadColorMapped(int numCol){loadPtr(numCol,&getColorMap<key>);};
    
    template <typename key>
    void loadColorMapped(int numCol,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        imDatas=byted*w*h;
        fi.seekg((y*head.Image.width +x)*byted,std::ios_base::cur);
        for(int i=0;i<head.Image.height;i++){ 
            ld(imageData+head.Image.width*i,w.byted,fi);
        fi.seekg(head.Image.width *byted,std::ios_base::cur);
        };
        loadPtr(numCol,&getColorMap<key>);};

    void loadRunLength( int numCol, int8_t (*ptr)(int,int) ){
        setFormat();
        int inds=0;
        for(int i=0;i<imDatas;i++){
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
    void loadRunLength( int numCol,uint32_t w,uint32_t h,uint32_t x,uint32_t y, int8_t (*ptr)(int,int) ){
        // imDatas=byted*w*h;
        uint8_t* lastRl=new uint8_t[byted];
        uint32_t i=0;uint8_t am;uint32_t lim=(head.Image.width*y+x);
        while(i<lim){
            ld(lastRl,fi)
             am=(1<<7)&lastRl[0] ?lastRl[0] - (1<<7):1;
            i+=  am;
        };
        imageData = new uint8_t[w*h*byted];uint32_t ind=0;
        while(ind<w*h){
            lastRl[0] -=(i -lim);
            std::memcpy(imageData+ind*byted,lastRl,byted);
            uint32_t index=i-lim;lim=w;
            while(index<lim){
            ld(lastRl,fi);
            std::memcpy(imageData+(ind+index)*byted,lastRl,byted);
            am=(1<<7)&lastRl[0] ?lastRl[0] - (1<<7):1;
            index+= am ;
            };
            imageData[(ind+index)*byted]-=index-lim;
            ind+=lim;
        i=index-lim;lim=(head.Image.width-w);
        while(i<lim){
            ld(lastRl,fi);
            am=(1<<7)&lastRl[0] ?lastRl[0] - (1<<7):1;
            i+= am;
        };
        };
        loadRunLength(numCol,ptr);
    }
    template <typename key>
    void loadRunLengthColorMapped(int numcol){loadRunLength(numcol,&getColorMap<key>);};
    void loadRunLengthColorMapped(int numcol,uint32_t w,uint32_t h,uint32_t x,uint32_t y){loadRunLength(numcol,w,h,x,y,&getColorMap<key>);};

    void loadRunLengthRgba(int numcol){loadRunLength(numcol,&getRgb);}
    void loadRunLengthRgba(int numcol,uint32_t w,uint32_t h,uint32_t x,uint32_t y){loadRunLength(numcol,w,h,x,y,&getRgb);}
    
    void loadRgba(int numCol){
        loadPtr(numCol,&getRgb);
    };
    void loadRgba(int numCol,uint32_t w,uint32_t h,uint32_t x,uint32_t y){

        fi.seekg(y*byted*head.Image.width+x*byted,std::ios_base::cur);
        imDatas=byted* w*h;
        imageData=new uint8_t[imDatas];
        for(int i=0;i<h;i++){
            ld(imageData+i*byted*w, byted*w,fi );
            fi.seekg((head.Image.width- w)*byted,std::ios_base::cur);
        }
        loadPtr(numCol,&getRgb);
    };

    bool isFormatted(){
        bool res = pd%32==0 or (pd%16==0) or (pd%8==0) ;
        // std::memcpy(im.data, imageData,imDatas);
        if(res){
            ld(im.data,imDatas,fi);return false;
        }
        else {
            ld(imageData,imDatas,fi);
            return true;
        }
    };
    bool isFormatted(uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        bool res = pd%32==0 or (pd%16==0) or (pd%8==0) ;
        // std::memcpy(im.data ,imageData,imDatas);
          if(res){
            fi.seekg((y*head.Image.width +x)*byted+,std::ios_base::cur);
            for(int i = 0 ; i<h;i++){
                ld(im.data+i*w*byted,w*byted,fi);
                fi.seekg(head.Image.width *byted+,std::ios_base::cur);
            }
            ld(im.data,imDatas,fi);return false;
        }
        else {
            // ld(imageData,imDatas,fi);
            return true;
        }
    };
    void load1 (){
         if(isFormatted()){return;}
         switch(pd/8){
            case 4 :{loadColorMapped<int16_t>(3);return;}
            case 8 :{loadColorMapped<int32_t>(3);return;}
        }         
    }
    void load1(uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        if(isFormatted(w,h,x,y)){return;}
        switch(pd/8){
            case 4:{loadColorMapped<int16_t>(3,w,h,x,y);return;}
            case 8:{loadColorMapped<int32_t>(3,w,h,x,y);return;}
        }
    };
    void load2 (){
        if( isFormatted()){return;}
        loadRgba(3);
    };
    void load2 (uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        if( isFormatted(w,h,x,y)){return;}
        loadRgba(3);
    };
    void load9(){
        switch(pd/8){
            case 4 :{loadRunLengthColorMapped<int16_t>(3);return;}
            case 8 :{loadRunLengthColorMapped<int32_t>(3);return;}
        } 
        };
    void load9(uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        switch(pd/8){
            case 4 :{loadRunLengthColorMapped<int16_t>(3,w,h,x,y);return;}
            case 8 :{loadRunLengthColorMapped<int32_t>(3,w,h,x,y);return;}
        } 
    };
    void load10(){
        ld(imageData,imDatas,fi);
        loadRunLengthRgba(3);
    };
    void load10(uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        ld(imageData,imDatas,fi);
        loadRunLengthRgba(3,w,h,x,y);
    };
    void load3(){
        if(isFormatted()){return;};
        loadRgbBa(1);
    };
    void load3(uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        if(isFormatted(w,h,x,y)){return;};
        loadRgbBa(1);
    };

    void load11(){
        ld(imageData,imDatas,fi);
        loadRunLengthRgba(1);};
    

    void load11(uint32_t w,uint32_t h,uint32_t x,uint32_t y){
        loadRunLengthRgbaR(11,w,h,x,y);};

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
                        if(ac==0){im.imageFormat = image_formats::r8ui}}
        } 
    };
void loadSet(){
im = image2d();
    ld<tga_header>(this->head,fi);
    ld(this->ID,this->head.ID_length,fi);
    if(this->head.Color_map_type !=0){
        ld(this->colorMapData,this->head.Color_map.length,this->head.Color_map.entrySize,fi);
    }
    pd = this->head.Image.pixelDepth;
    byted =pd/8+ (pd%8==0?0:1);

    size_t imDatas=this->head.Image.width*this->head.Image.height*byted;
    
    im.width = this->head.Image.width;
    im.height = this->head.Image.height;
    
    pd = this->head.Image.pixelDepth;
    ac =  this->head.Image.getAlpha();
    nm = pd -ac;
    nch = nm/3;  
    imDatas=this->head.Image.width*this->head.Image.height * this->head.Image.pixelDepth/8;
    
};
// modules::image2D mipMap(std::string path,uint8_t level){
//     fi=std::ifstream(path);
//     loadSet();
//     im.width = this->head.Image.width/level;
//     im.height = this->head.Image.height/level;
    
//     switch(this->head.Image_type ){
//         case 1:{selectrgba();load1mip(level);}
//         case 2:{selectrgba();load2mip(level);}
//         case 9:{selectrgba();load9mip(level);}
//         case 10:{selectrgba();load10mip(level);}
//         case 3:{selectGrayScale();load3mip(level);}
//         case 11:{selectGrayScale();load11mip(level);}
//     }       
//     return im;
// };
modules::image2D ld(std::string path,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
     fi=std::ifstream(path);
    loadSet();

    // ld(this->ImageData, imDatas,fi);

    switch(this->head.Image_type ){
        case 1:{selectrgba();load1(w,h,x,y);}
        case 2:{selectrgba();load2(w,h,x,y);}
        case 9:{selectrgba();load9(w,h,x,y);}
        case 10:{selectrgba();load10(w,h,x,y);}
        case 3:{selectGrayScale();load3(w,h,x,y);}
        case 11:{selectGrayScale();load11(w,h,x,y);}
    }       
    return im;

};
modules::image2D ld(std::string path){
    fi=std::ifstream(path);
    loadSet();

    // ld(this->ImageData, imDatas,fi);

    switch(this->head.Image_type ){
        case 1:{selectrgba();load1();}
        case 2:{selectrgba();load2();}
        case 9:{selectrgba();load9();}
        case 10:{selectrgba();load10();}
        case 3:{selectGrayScale();load3();}
        case 11:{selectGrayScale();load11();}
    }       
    return im;
};
std::vector<uint8_t> imageD;
std::vector<uint8_t> colorMapD;
std::fstream& fs;

int64_t findCl(uint8_t byd,void* d){
    for(uint64_t i=0;i<colorMapD.size();i+=byd){
        if(memcmp(d,colorMapD.data()+i,byd)){
            return i;
        }
    }; 
    return -1;
} ;
void wrCmap(image2D& image){
    pd() = 8;uint64_t i;

    for(i=0;i<image.imageSize;i+=im.byd){uint64_t sicd;colorMapD.size()
        int64_t s = findpalette(colorMapD.data(),&sicd,im.byd,im.data()+i);
        if(s==-1){
            colorMapD.resize(colorMapD.size()+image.byd);
            s=(colorMapD.size()-image.byd)
            std::memcpy(colorMapD.data()+s , im.data+i,image.byd);
        }
        s/=8;
        std::memcpy(imageD.data()+(i/image.byd)*pd(),&s,pd());
    };
    // Resize bitdepths;
    uint64_t s;
    for(;i<s;pd()--){s=1<<(pd()*8 -1)-1 + (1<<(pd()*8-1));}
    for(uint64_t n=0;n<imageD.size()/8;n++){
        std::memcpy(imageD.data()+n*pd(),imageD.data()+n*8 + 8-pd(),pd() );
    };  
    imageD.resize(imageD.size()/8*pd() );

};
uint32_t lengthCm ; 
uint32_t updateCmap(image2D& image,std::vector<uint8_t>& cmdata){
     std::vector<uint8_t> cpdata;
     lengthCm = head.Color_map.length;
     for(uint32_t i =0i<image.imageSize;i++ ){bool found=false;
        cmdata.resize(cmdata.size()+byted);
        auto getil = [&](uint32_t inds){
            uint8_t d[byted];
            for(uint8_t k = byted;k>0;k--){
                d[k] = inds& (0b11111111<<(8*k)) >> (8*k) ;
            };
            std::memcpy(cmdata.data()+cmdata.size()-byted,d,byted);
        }

            for(uint32_t j = 0;head.Color_map.length;j++){
                if(0==std::memcmp(image.data+i*image.byd,colorMapData+j*image.byd,byted) ){
                    std::memcpy(cmdata.data()+cmdata.size()-byted,colorMapData+j*image.byd,byted);
                    getil(j);
                    found=true;break;};
            };
            if(!found){
                for(uint32_t j = 0; j<cpdata.size()/byted;j++){
                    if(0==std::memcmp(image.data+i*image.byd,cpdata.data()+j*image.byd,byted)){
                        std::memcpy(cmdata.data()+cmdata.size()-byted,cpdata.data()+j*image.byd,byted);
                        getil(head.Color_map.length+1+j);
                        found=true;break;
                    }
                }
            }
            if(!found){head.Color_map.length++;
                cpdata.resize(cpdata.size()+image.byd);
                std::memcpy(cpdata.data()+ image.byd*(cpdata.size()-1),image.data+i*image.byd ,image.byd);
                getil(head.Color_map.length+1+cpdata.size());
            }
        };
        uint32_t res= cpdata.size();
    std::vector<uint8_t> cp(cpdata.size() + head.Color_map.length * head.Color_map.entrySize);
    std::memcpy(cp.data(),colorMapData,head.Color_map.length*head.Color_map.entrySize);
    std::memcpy(cp.data()+head.Color_map.length*head.Color_map.entrySize,cpdata.data(),res);
    delete colorMapData ;
    colorMapData = uint8_t[cp.size()];
    std::memcpy(colorMapData,cp,cp.size());
    return res;
}
void wrNorm(image2D& image,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
    fs.seekp((y*head.Image.width + x)*byted ,std::ios_base::cur);
    for(int i=0;i<h;i++){
        wr(image.data,w*byted,fs);
        fs.seekp((head.Image.width-w)*byted,std::ios_base::cur)
    }
};

void wrRLE(image2D& image,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
    byted = image.byd;
    uint8_t* lastrle = new uint8_t[byted+1]; 
    std::vector<uint8_t> rleim(image.imageSize*(byted+1));uint8_t rep=0; uint32_t inds=0;
    uint32_t i,j;
    std::vector<uint32_t> rlelineinds{0};


    auto lam = [&](){
            rleim.data()[inds*(byted+1)] =1<<7 + rep -1;inds++;rep=0;
            std::memcpy(rleim.data()+inds*(byted+1)+1,image.data+(i*w+j)*byted,byted);
    }

        for( i=0;i<h;i++){
            std::memcpy(rleim.data()+inds*(byted+1)+1,image.data+i*w*byted,byted);
            for( j=1;j<w;j++){
            if(0==std::memcmp(rleim.data()+inds*(byted+1)+1, image.data+(i*w+j)*byted,byted)){
                rep++;}
                else {lam();};
            if(rep==0b01111111){lam();};
        };
        rlelineinds.push_back(inds);
    };
    rleim.resize(inds);
        std::vector<uint8_t> rleimBuf ;uint32_t rleimLastInd=0;
    std::vector<uint32_t> rleimbufinds{0};
    
    uint32_t i ;uint8_t val ;uint32_t lim=(head.Image.width*y +x );
    for(i=0;i<lim;i+=val){
        ld(lastrle,byted+1,fs);
        val = lastrle[0] & (1<<7) ?  lastrle[0] -(1<<7) + 1 : 1;
    }

    uint8_t lastrl=new uint8_t[byted+1];
    uint8_t nextrl =0;uint8_t over;
    auto lrl = [&](uint8_t& rlh){
        over = i-lim;
        uint8_t r = rlh & (1<<7) ? rlh-(over+1) : 0;
        nextrl = rlh - r;rlh=r;
    fs.seekg(-1-byted,std::ios_base::cur);
    wr(r,fs);
    fs.seekg(byted,std::ios_base::cur);    
    }
    lrl(lastrle[0]);
    rleimBuf.resize(byted+1);
    rleimBuf[0]=nextrl;
    std::memcpy(rleimBuf.data()+1,lastrle+1,byted);
int32_t offs=0;
    uint32_t index =0;
    lim=w;
    uint32_t ind;
    for( ind=0;ind<h;ind++){
        
        rleimbufinds.push_back(rleimbufinds.back()+1);      
        for(i=over;i<lim;i+=val){offs+=(byted+1);
            rleimBuf.resize(rleimBuf.size()+byted+1);
            ld(rleimBuf.data()+rleimbufinds.back()*(byted+1),byted+1,fs);rleimbufinds.back()++;
        };
        if(i-lim>0){
            lrl (*( rleimBuf.data()+(rleimbufinds.back()-1)*(byted+1)));
            rleimBuf.resize(rleimBuf.size()+byted+1);
            rleimBuf[rleimBuf.size()-byted-1] = nextrl;
            std::memcpy(rleimBuf.data() + rleimBuf.size()-byted, rleimBuf.data() + rleimBuf.size()-2*byted-1, byted  );
        }
        else {over=0;}

        uint32_t sim = (rlelinesinds[index+1] - rlelinesinds[index]) *(byted+1);
        uint32_t sd = (rleimbufinds[index+1] - rleimbufinds[index]) *(byted+1);
        for(;offs > (sim+sd) and (index<ind);){
            fs.seekg(-offs,std::ios_base::cur);
            wr(rleim.data()+rlelineinds[ind]*(byted+1) ,sim  ,fs );offs-=sim;
            wr(rleimBuf.data()+rleimbufinds[ind]*(byted+1,sd,fs);offs-=sd;
        index++;            
            sim = rlelinesinds[ind+1] - rlelinesinds[ind]) *(byted+1);
             sd = (rleimbufinds[index+1] - rleimbufinds[index]) *(byted+1);
        }
    };

}

void wrCmap(image2D& image,uint32_t w,uint32_t h,uint32_t x,uint32_t y){// starts at read colorMap
    std::vector<uint8_t> cmdata;
    uint32_t size = updateCmap(image,cmdata);
    if(size==0){
        fs.seekg((y*head.Image.width +x)*byted,std::ios_base::cur);
        while(uint32_t i=0;i<h;i++){
            wr(cmdata.data()+i*w*byted,w*byted,fs);
            fs.seekg((head.Image.width-w)*byted,fs);
        }
        return;}
    std::vector<uint8_t> data(size); uint32_t colorMapDataSize=  head.Color_map.entrySize * head.Color_map.length;

    if(size<(imDatas)){
        ld(data.data(),size,fs);
        fs.seekg(-size,std::ios_base::cur);
        wr(colorMapData+colorMapDataSize-size,size,fs);
    }
    else {
        ld(data.data(),imDatas,fs);
        fs.seekg(-imDatas,fs);
        wr(colorMapData+colorMapDataSize-size,size,fs);
        for(uint32_t i=0;i<h;i++){
            std::memcpy(data.data()+byted*(head.Image.width*(i+y)+x) ,cmdata()+w*i*byted,w*byted  );
        }
        wr(data.data(),imDatas,fs);return;
    }
    bool highavailmem = false;
    if(highavailmem){ /// @brief :no
        std::vector<uint8_t> img(imDatas);
    std::memcpy(img.data(),data.data(),size);
    ld(img.data()+size,byted*head.Image.width*head.Image.height-size,fs);
    for(uint32_t i=0;i<h;i++){
        std::memcpy(img.data()+(i*head.Image.width+x)*byted,image.data+i*w*byted,w*byted);
    }
    wr(img.data()+size,byted*(head.Image.width*head.Image.height)-size,fs);
    }
    else//!highavailmem
    {
        uint32_t s = 0;uint32_t lim = y*head.Image.width+x*byted;
        std::vector<uint8_t> imgch(size) ;
        for(;s<lim;s+=size){
            ld(imgch.data(),size,fs);
            fs.seekg(-size,std::ios_base::cur);
            wr(data.data(),size,fs);
            std::memcpy(data.data(),imgch.data(),size);
        };
        uint32_t over=s-lim;
        uint16_t starts = over / (head.Image.width*byted); 
        int32_t extraLine = over% head.Image.width*byted;
        for(uint16_t i=0;i<h;i+=starts){
            uint16_t j;
            for( j=0;(j<starts-1) and ((i+j)<h);j++){
                std::memcpy(data.data()+size-over + (i+j)*head.Image.width*byted , cmdata.data()+w*(i+j)*byted,w*byted);
            };
            ld(imgch.data(),size,fs);
            fs.seekg(-size,std::ios_base::cur);
            if(extraLine<w*byted){
                std::memcpy(data.data()+size-over + (i+j)*head.Image.width*byted , cmdata.data()+w*(i+j)*byted,extraLine );
            }
            else {
                std::memcpy(data.data()+size-over + (i+j)*head.Image.width*byted , cmdata.data()+w*(i+j)*byted,w*byted );
            }
            wr(data.data(),size,fs);
            std::memcpy(data.data(),imgch.data(),size);
            if(extraLine<w*byted){
                std::memcpy(data.data(), cmdata.data()+w*(i+j+1)*byted - ((w*byted)-extraLine),((w*byted)-extraLine) );
            };
            lim += starts* head.Image.width*byted;
            over=(y+(i+j))*head.Image.width -lim;
            starts = over / (head.Image.width*byted); 
            extraLine = over% head.Image.width*byted;
        };
        s= head.Image.width*(y+h)*byted+extraLine-w*byted;
        for(;s<imDatas;s+=size){
            ld(imgch.data(),size,fs);
            fs.seekg(-size,std::ios_base::cur);
            wr(data.data(),size,fs);
            std::memcpy(data.data(),imgch.data(),size);
        };  
        ld(imgch.data(),imDatas-(s-size),fs);
        fs.seekg(-(imDatas-(s-size)),fs);
        wr(data.data(),size,fs);
        wr(imgch.data(),imDatas-(s-size),fs);
    }
}
void wrCmapRLE(image2D& image){
    std::vector<uint8_t> cmdata;
    uint32_t size = updateCmap(image,cmdata);

    uint8_t rep=0;uint32_t entries=0;
    for(i=0;i<image.imageSize;i+=image.byd){
        if(std::memcmp(image.data+i,image.data+i-image.byd , image.byd)==0 and (rep<(1<<7))){rep++;}
        else {uint8_t reps = rep +(1<<7);
            memcpy(imageD.data()+entries*(pd()+1),&reps,1);
            rep=0;entries++;};
        int64_t s = findCl(image.byd,image.data()+i);
        if(s==-1){
            colorMapD.resize(colorMapD.size()+image.byd);
            s=(colorMapD.size()-image.byd)
            std::memcpy(colorMapD.data()+s , image.data+i,image.byd);
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

void wrRLEsize0(uint32_t w,uint32_t h,uint32_t x,uint32_t y,uint8_t* cmdata){ // TODO
 uint8_t lastrle[byted+1];uint8_t val;uint32_t i;
        for( i=0;i<y*head.Image.width+x;i+=val){
            ld(lastrle,byted+1,fs);
            val = lastrle[0] &(1<<7)?(lastrle[0] - 1<<7 ) : 1;
        };
        lastrle[0] -= (i-val);
        uint8_t lastrl[byted+1];
        for(i=0;i<h*head.Image.width+w;i+=val){
            uint32_t j ;
            for(j=0;j<w;j+=val){
                ld(lastrl,byted+1,fs);
                fs.seekg(-(byted+1),std::ios_base::cur);
                val = cmdata[i*w+j] &(1<<7)?(lastrl[0] - 1<<7 ) : 1;
            };
            for(j=0;j<head.Image.width-w;j+=val){
                ld(lastrl,byted+1,fs);
                val=val = lastrl[0] &(1<<7)?(lastrl[0] - 1<<7 ) : 1;

            };
    };
}
void wrCmapRLE(image2D& image,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
    std::vector<uint8_t> cmdata;
    uint32_t size = updateCmap(image,cmdata);
    modules::image2D img ;
    img.data = cmdata.data();
    if(size==0){
        // wrRLEsize0(w,h,x,y,cmdata.data())
        wrRLE(img,w,h,x,y);return;
    }
    uint32_t colorMapDataSize=  head.Color_map.entrySize * head.Color_map.length;
    
    // byted = image.byd;
    uint8_t* lastrle = new uint8_t[byted+1]; 
    std::vector<uint8_t> rleim(image.imageSize*(byted+1));uint8_t rep=0; uint32_t inds=0;
    uint32_t i,j;
    std::vector<uint32_t> rlelineinds{0};


    auto lam = [&](){
            rleim.data()[inds*(byted+1)] =1<<7 + rep -1;inds++;rep=0;
            std::memcpy(rleim.data()+inds*(byted+1)+1,image.data+(i*w+j)*byted,byted);
    }

        for( i=0;i<h;i++){ 
            std::memcpy(rleim.data()+inds*(byted+1)+1,cmdata.data()+i*w*byted,byted);
            for( j=1;j<w;j++){
            if(0==std::memcmp(rleim.data()+inds*(byted+1)+1, cmdata.data()+(i*w+j)*byted,byted)){
                rep++;}
                else {lam();};
            if(rep==0b01111111){lam();};
        };
        rlelineinds.push_back(inds);
    };
    rleim.resize(inds);
    // Here offseted
        std::vector<uint8_t> rleimBuf ;uint32_t rleimLastInd=0;
    std::vector<uint32_t> rleimbufinds{0};bool wrcmda=false;
    uint32_t i ;uint8_t val ;uint32_t lim=(head.Image.width*y +x );
    
    uint8_t lastrl=new uint8_t[byted+1];
    uint8_t nextrl =0;
    auto lrl = [&](uint8_t& rlh){
        over = i-lim;
        uint8_t r = rlh & (1<<7) ? rlh-(over+1) : 0;
        nextrl = rlh - r;rlh=r;
    fs.seekg(-1-byted,std::ios_base::cur);
    wr(r,fs);
    fs.seekg(byted,std::ios_base::cur);    
    }
    uint8_t over=0;int32_t offs=0;
// Here it writes evertyhing upto region in buffer, Mayhaps more mem efficient?
        for(i=over;i<lim;i+=val){offs+=(byted+1); 
            rleimBuf.resize(rleimBuf.size()+byted+1);
            ld(rleimBuf.data()+rleimbufinds.back()*(byted+1),byted+1,fs);rleimbufinds.back()++;
        };
        if(i-lim>0){
            lrl (*( rleimBuf.data()+(rleimbufinds.back()-1)*(byted+1)));
            rleimBuf.resize(rleimBuf.size()+byted+1);
            rleimBuf[rleimBuf.size()-byted-1] = nextrl;
            std::memcpy(rleimBuf.data() + rleimBuf.size()-byted, rleimBuf.data() + rleimBuf.size()-2*byted-1, byted  );
        }
        auto wrcm = [&](){
            if(offs>size and !wrcmda){
                fs.seekg(-offs,std::ios_base::cur)
                fs.wr(colorMapData+colorMapDataSize-size,size,fs);
                fs.seekg(offs-size,std::ios_base::cur);
                offset = offs-size;wrcmda = true;
            };  
        }
        wrcm();
    
    uint32_t index =0;
    lim=w;
    uint32_t ind;
    for( ind=0;ind<h;ind++){
        
        rleimbufinds.push_back(rleimbufinds.back()+1);      
        for(i=over;i<lim;i+=val){offs+=(byted+1);
            rleimBuf.resize(rleimBuf.size()+byted+1);
            ld(rleimBuf.data()+rleimbufinds.back()*(byted+1),byted+1,fs);rleimbufinds.back()++;
        };
        if(i-lim>0){
            lrl (*( rleimBuf.data()+(rleimbufinds.back()-1)*(byted+1)));
            rleimBuf.resize(rleimBuf.size()+byted+1);
            rleimBuf[rleimBuf.size()-byted-1] = nextrl;
            std::memcpy(rleimBuf.data() + rleimBuf.size()-byted, rleimBuf.data() + rleimBuf.size()-2*byted-1, byted  );
        }
        else {over=0;}

        uint32_t sim = (rlelinesinds[index+1] - rlelinesinds[index]) *(byted+1);
        uint32_t sd = (rleimbufinds[index+1] - rleimbufinds[index]) *(byted+1);
        wrcm()
        for(;offs > (sim+sd) and (index<ind);){
            fs.seekg(-offs,std::ios_base::cur);
            wr(rleim.data()+rlelineinds[ind]*(byted+1) ,sim  ,fs );offs-=sim;
            wr(rleimBuf.data()+rleimbufinds[ind]*(byted+1,sd,fs);offs-=sd;
        index++;            
            sim = rlelinesinds[ind+1] - rlelinesinds[ind]) *(byted+1);
             sd = (rleimbufinds[index+1] - rleimbufinds[index]) *(byted+1);
        }
    };

};
void wrNorm(image2D& image){
    byted=image.byd;uint8_t rep=0;uint32_t entries=0
    imageD.resize(byted*image.imageSize);
    std::memcpy(imageD.data(),image.data,byted*image.imageSize);
};

void wrRLE(image2D& image){
    byted=image.byd;
    for(int i=0;i<image.imageSize;i+=image.byd){
        if(std::memcmp(image.data+i,image.data+i-image.byd , image.byd)==0 and (rep<(1<<7))){rep++;}
        else{uint8_t reps = rep+(1<<7);
            memcpy(imageD.data()+entries*(byted+1),&reps,1);
            rep=0;entries++;
            memcpy(imageD.data()+entries*(byted+1)+1,image.data+i,pd() );
        }
    };
}

void wr(image2D& image,std::string path,bool cpl=false,bool rle=true){
    uint8_t bda =modules::bitdepth_a(image.imageFormat);
    head.Image.descriptor=bda &0b1111 + 0b110000; 
    head.Image.width=image.width;head.Image.height=image.height;
    cm_entrySize() = image.byd;
    colorMapD= std::vector<uint8_t>(image.byd*image.imageSize);
    if(image.length()<=2){
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
void wr(image2D& image,std::string path,bool cpl=false,bool rle=true,uint32_t w,uint32_t h,uint32_t x,uint32_t y){// TODO

fi =std::ifstream(path);
    loadSet();
    pos_type p= fi.tellp();
    delete fi;
    fs=std::fstream(path);
    fs.seekg(p);

    if(cpl){
        if(rle) {wrCmapRLE(image,w,h,x,y);}
        else {wrCmap(image,w,h,x,y);}
    }
    else {
        if(rle){wrRLE(image,w,h,x,y);}
        else {wrNorm(image,w,h,x,y);}
    }

};
};
#endif