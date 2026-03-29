#ifndef STM_JPEG_HPP
#define STM_JPEG_HPP

#include "stm.hpp"
#include "../clib.hpp"
struct jpeg {
    const uint8_t segstart = 0xFF;
    enum segs {
        _SOI	= 0xD8,//	none	        Start Of Image	
        _SOF0= 0xC0,//Baseline DCT	variable size	Start Of Frame (baseline DCT)	Indicates that this is a baseline DCT-based JPEG, and specifies the width, height, number of components, and component subsampling (e.g., 4:2:0).
        _SOF1= 0xC1,// Seq DCT ,HUFFMAN
        _SOF2= 0xC2,//Progressive DCT,HUFFMAN	variable size	Start Of Frame (progressive DCT)	Indicates that this is a progressive DCT-based JPEG, and specifies the width, height, number of components, and component subsampling (e.g., 4:2:0).
        _SOF3=0xC3,//Lossless Sequential,Huffman
        _SOF5=0xC5,//differential sequential DCT frame marker, Huffman coding
        _SOF6=0xC6,//SOF6 differential progressive DCT frame marker, Huffman coding
        _SOF7=0xC7,//SOF7 differential lossless process frame marker, Huffman coding
        _SOF9=0xC9,//extended DCT sequential,arithmetic coding
        _SOF10=0xC10,//progressive DCT,arithmetic coding
        _SOF11=0xC11,//lossless sequential,arithmetic coding
        _SOF13=0xCD,//differential sequential DCT frame marker, arithmetic coding
        _SOF14=0xCE,//SOF14 differential progressive DCT frame marker, arithmetic coding
        _SOF15=0xCF,//SOF15 differential lossless process frame marker, arithmetic coding
        _DHT	= 0xC4,//	variable size	Define Huffman Table(s)	Specifies one or more Huffman tables.
        _DQT	= 0xDB,//	variable size	Define Quantization Table(s)	Specifies one or more quantization tables.
        _DRI	= 0xDD,//	4 bytes	        Define Restart Interval	Specifies the interval between RSTn markers, in Minimum Coded Units (MCUs). This marker is followed by two bytes indicating the fixed size so it can be treated like any other variable size segment.
        _SOS	= 0xDA,//	variable size	Start Of Scan	Begins a top-to-bottom scan of the image. In baseline DCT JPEG images, there is generally a single scan. Progressive DCT JPEG images usually contain multiple scans. This marker specifies which slice of data it will contain, and is immediately followed by entropy-coded data.
        _RSTn= 0xD0,// (n=0..7)	none	Restart	Inserted every r macroblocks, where r is the restart interval set by a DRI marker. Not used if there was no DRI marker. The low three bits of the marker code cycle in value from 0 to 7.
        _RST7= 0xD7,// (n=0..7)	none	Restart	Inserted every r macroblocks, where r is the restart interval set by a DRI marker. Not used if there was no DRI marker. The low three bits of the marker code cycle in value from 0 to 7.
        _APPn= 0xE0,//	variable size	Application-specific	For example, an Exif JPEG file uses an APP1 marker to store metadata, laid out in a structure based closely on TIFF.
        _APPL= 0xEF,//	variable size	Application-specific	For example, an Exif JPEG file uses an APP1 marker to store metadata, laid out in a structure based closely on TIFF.
        _COM	= 0xFE,//	variable size	Comment	Contains a text comment.
        _DAC=0xCC,//define arithmetic coding
        _EXP=0xDF,//
        _DHP=0xDE,// Define hierarchical progression
        _DNL=0xDC,
        _EOI	= 0xD9,//	none	End Of Image	
    }
    uint8_t SOI;
    
    struct APPn {
        uint16_t length;
        uint8_t* data;
    }
    ACQRES(APPn){
        one(f.length);
        arr(f.data,f.length);
    }
    USE_ACQRES(APPn)

    struct EXP {
        uint16_t le;
        uint8_t Eh_Ev ; // High4 : Eh ; Low4 :Ev ( expand horizontally/vertically)
    }
    struct DHT {
        uint16_t length;
        std::vector<clib::huff_tree> trees;
        bool id(uint8_t id,clib::huff_tree& ht){
            uint16_t n0=0;
            for(uint16_t i=0;i<length;i+=trees[i].length){
                if(trees[no].htid()==id){ht=trees[i];return true;}
                no++;
            }
            return false;
        }
    };
    ACQRES(DHT) {
        one(f.length);
        uint16_t l = length;
        int i;
        trees.resize(f.s);
        for( i=0;l>0;i++){trees.push_back(huffmanTree());
            one(f.trees[i].htInfo); l--;
            arr(f.tress[i].codeLengths,16); l-=16;
            size_t s=0;
            for(int i=0;i<16;i++){s+=f.codeLengths[i];}l-=s;
            if(!f.trees[i].symbols){new f.trees.symbols=new uint8_t[s];}
            arr(f.trees[i].symbols,s);
        };
        f.s=i;
        trees.resize(f.s);
    }
    USE_ACQRES(DHT)
    struct DAC {
        uint16_t length;
       
        clib::actb *table;
    };
    ACQRES(DAC){
        one(f.length);
        arr(f.table,f.length);
    }
    USE_ACQRES(DAC)
    struct DQT {
        uint16_t length;
        uint16_t n;
        struct qtb{
            uint8_t prec_did;// High4 : prec; low4: dest id
            uint8_t Q[64];
            uint8_t destid(){return prec_did &0b1111;}
            uint8_t prec(){return prec_did >>4;}
            void get(uint8_t mat[8][8]){
                std::memcpy(mat,Q,64);
            };
            void put(uint8_t mat[8][8]){
                std::memcpy(Q,mat,64);
            };
            
        };qtb* qtable;

        bool did(uint8_t s ,qtb& res){
            for(uint16_t i=0;i<n;i++){
                if(qtable[i].destid()==s){res=qtable[i];return true;}
            }
            return false;
        }
    };
    ACQRES(DQT){
        one(f.length);
        one(f.n)
        one(f.qtable,f.n);
    } 
    USE_ACQRES(DQT)
    typedef uint16_t DRI ;
 struct SOF{
        uint16_t length ;
        uint8_t samplePrecision;

        uint16_t Y; // Lines
        uint16_t X; // Samples per line
        uint16_t Nf;

        struct cmpspec {
            uint8_t cid;
            uint8_t hsf_vsf;
            uint8_t qtbDestSel;
            uint8_t hsf(){return hsf_vsf>>4;}
            uint8_t vsf(){return hsf_vsf&0b1111;}
        };cmpspec* cmSpec;
        bool findCID(uint8_t id, cmpspec& res){
            for(uint32_t i=0;i<Nf;i++){if(cmSpec[i].cid==id){res=cmSpec[i].cid;return true; };}
            return false;
        }
    };

    ACQRES(SOF){
        f.length = 1 + 3*2 + 3*f.Nf;
        one(f.length);
        one(f.samplePrecision);
        one(f.Y);
        one(f.X);
        one(f.Nf);
        arr(f.cmSpec,f.Nf);
    }
    USE_ACQRES(SOF)


    struct SOS { 
        uint16_t length;
        uint8_t numCom;
        struct cmspec {
            uint8_t id;
            uint8_t TdTa; // high4:DC, low4:AC
            uint8_t tdc(){return TdTa>>4;}
            uint8_t tac(){return TdTa&0b1111;}
            void tdc(uint8_t s){ TdTa&=0b00001111;TdTa+=(s&0b1111)<<4;}
            void tac(uint8_t s){ TdTa&=0b11110000;TdTa+=s&0b1111 ;}
        };cmspec* comSpec; // by1:id by2:HT
        uint8_t spectralStart=0x00;// DCT(progressive and differential) first DCT coef;;; lossless : Predictor in  , 
        uint8_t spectralEnd=0x3F; // last DCT coef in zig zag.,,, no meaning for sequential DCT and lossless;
        uint8_t successiveApprox; ; // High4 : DCT pt transform ; Low4 : DCT and Lossless pt transform
        std::vector<uint8_t> data;
    };  
    template <>
    void ld(SOS& f,std::ifstream& fi){
        ld(f.length,fi);
        ld(f.numCom,fi);
        ld(f.comSpec,f.numCom,fi);
        ld(f.spectralStart,fi);
        ld(f.spectralEnd,fi);
        ld(f.successiveApprox,fi);
        uint8_t o;bool t=true;
        while(t){
            ld(o,fi);
            f.data.push_back(o);
            if(o==0xFF){ld(o,fi);
                if(o==0xD9){t=false;break;}}
        } 
    }
    
    template <>
    void wr(SOS& f,STD::ofstream& fi){
        f.length = 1 + f.numCom * 2 + 3 + f.data.size();
        ld(f.length,fi);
        ld(f.numCom,fi);
        ld(f.comSpec,f.numCom,fi);
        ld(f.spectralStart,fi);
        ld(f.spectralEnd,fi);
        ld(f.successiveApprox,fi);
        wr(f.data.data(),f.data.size(),fi);
    };
    struct COM {
        uint16_t length;
        char* text;
    };
    ACQRES(COM){
        one(f.length);
        arr(f.text,f.length);
    };
    USE_ACQRES(COM) 

    struct DNL {
        uint16_t len;
        uint16_t nl;
    };

/// @internal DATA
        uint8_t segstart;
        uint8_t SOI_ = seg::_SOI;
        bool DRIb=false;
        bool sequential=true;bool lossless=false;bool differential=false;bool dct=true;bool progressive=true;
        bool hierarchical=true;
        bool arithmetic;bool huff; 
        bool dnlDef=false;
        DRI DRI_;
        SOF DHP_;    
        SOF SOF_;
            
        EXP EXP_;
        DHT DHT_;
        DQT DQT_;
        DRI DRI_;
        APPn APPn_;
        COM COM_;
        DNL DNL_;
            SOS SOS_;

    segs SOFT;
    uint8_t RST;bool rst;


void  setSOF0(){SOFT = segs::_SOF0;  dct=true;lossless=false;sequential=true;arithmetic=false;huff=false;differential=false; progressive = false;}; 
void  setSOF1(){SOFT = segs::_SOF1;  dct=true;lossless=false;sequential=true;arithmetic=false;huff=true;differential=false; progressive = false;}; 
void  setSOF2(){SOFT = segs::_SOF2;  dct=true;lossless=true;sequential=true;arithmetic=false;huff=true;differential=false; progressive = true;}; 
void  setSOF3(){SOFT = segs::_SOF3;  dct=false;lossless=false;sequential=true;arithmetic=false;huff=true;differential=false; progressive = false;}; 
void  setSOF5(){SOFT = segs::_SOF5;  dct=true;lossless=false;sequential=true;arithmetic=false;huff=true;differential=true; progressive = false;}; 
void  setSOF6(){SOFT = segs::_SOF6;  dct=true;lossless=false;sequential=false;arithmetic=false;huff=true;differential=true; progressive = true;}; 
void  setSOF7(){SOFT = segs::_SOF7;  dct=false;lossless=true;sequential=false;arithmetic=false;huff=true;differential=false; progressive = false;}; 
void  setSOF9(){SOFT = segs::_SOF9;  dct=true;lossless=false;sequential=true;arithmetic=true;huff=false;differential=false; progressive = false;}; 
void  setSOF10(){SOFT = segs::_SOF10;dct=true;lossless=false;sequential=true;arithmetic=true;huff=false;differential=false; progressive = false;}; 
void  setSOF11(){SOFT = segs::_SOF11;dct=false;lossless=false;sequential=true;arithmetic=true;huff=false;differential=false; progressive = false;};
void  setSOF13(){SOFT = segs::_SOF13;dct=true;lossless=false;sequential=true;arithmetic=true;huff=false;differential=true; progressive = false;}; 
void  setSOF14(){SOFT = segs::_SOF14;dct=true;lossless=false;sequential=true;arithmetic=true;huff=false;differential=true; progressive = true;}; 
void  setSOF15(){SOFT = segs::_SOF15;dct=false;lossless=false;sequential=true;arithmetic=true;huff=false;differential=true; progressive = false;}; 
/// @endinternal

    int8_t dct(uint8_t u,uint8_t v,uint8_t x,uint8_t y){
        return cos((2 * x + 1) * u * PI / 16.0) *
                           cos((2 * y + 1) * v * PI / 16.0);    };  

void alpha(uint8_t n){return n==0?0.707106781:1;}
void dct8x8(double input[8][8], double output[8][8]) {
    const int N =8;
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

void dctCoef(mod::image2D& YCC ,uint16_t x,uint16_t y , double* coef[8][8]){ // TODO
  
};

void losslessCoef(mod::image2D& YCC ,uint16_t x,uint16_t y , double* coef[8][8]){ // TODO
  
};
void dctCoef(mod::image2D& YCC ,uint16_t x,uint16_t y , double ycoef[8][8],double crcoef[8][8],double cbcoef[8][8]){
    glm::u8vec3 vec[8][8];
    for(int i=y;i<8;i++){
        std::memcpy(vec+(i-hstep)*24,YCC.data+i*24*YCC.width+x*24,24*8);
    };
    double input[8][8];        
    for(int i=0;i<3;i++){
        for(int j=0;j<8;j++){
        for(int k=0;k<8;k++){
            input[j][k]=vec[j][k][i] -128;
        } } 
        switch(i){
            case 0 :{dct8x8(input,ycoef);}
            case 1 :{dct8x8(input,crcoef);}
            case 2 :{dct8x8(input,cbcoef);}
        }
    };
};
void losslessCoef(mod::image2D& YCC ,uint16_t x,uint16_t y , double ycoef[8][8],double crcoef[8][8],double cbcoef[8][8]){
    glm::u8vec3 vec[8][8];
    for(int i=y;i<8;i++){
        std::memcpy(vec+(i-hstep)*24,YCC.data+i*24*YCC.width+x*24,24*8);
    };
    double input[8][8];        
    for(int i=0;i<3;i++){
        for(int j=0;j<8;j++){
        for(int k=0;k<8;k++){
            input[j][k]=vec[j][k][i] -128;}}
               switch(i){
            case 0 :{ycoef=input;}
            case 1 :{crcoef=input;}
            case 2 :{cbcoef=input;}
    }
       
}}

void losslessCoef()
const uint8_t qmatrix[8][8] = {
{16,11,10,16,24, 40, 51, 61},
{12,12,14,19,26, 58, 60, 55},
{14,13,16,24,40, 57, 69, 56},
{14,17,22,29,51, 87, 80, 62},
{18,22,37,56,68, 109,103,77},
{24,35,55,64,81, 104,113,92},
{49,64,78,87,103,121,120,101},
{72,92,95,98,112,100,103,99},
}

void setDQT(uint8_t *mat[8][8],uint8_t* prec,uint8_t* destid, size_t s){
    DQT_.n=;
    DQT_.qtable = new DQT::qtb[DQT_.n];
    for(uint32_t i =0; i <s;i++){
        DQT_.qtable[i].prec_did = prec[i]<<4 | destid[i] ;
        std::memcpy(DQT_.qtable[i].Q,mat[i],64);
    };
};
void qmatrix(uint8_t qmat[8][8],uint8_t qmatrix[8][8], uint8_t quality){
   float factor = quality/100 + 1;
    for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        qmat[i][j]=qmatrix[i][j]/factor;
    }
    }
}
int bitSize(int8_t s){int8_t si = s;
    int i;for(i=0;si!=0;i++){si=si>>1;};return i;
};  

uint8_t matzigzag[8][8] = {
{ 0,  1,  5,  6, 14, 15, 27, 28}
{ 2,  4,  7, 13, 16, 26, 29, 42}
{ 3,  8, 12, 17, 25, 30, 41, 43}
{ 9, 11, 18, 24, 31, 40, 44, 53}
{10, 19, 23, 32, 39, 45, 52, 54}
{20, 22, 33, 38, 46, 51, 55, 60}
{21, 34, 37, 47, 50, 56, 59, 61}
{35, 36, 48, 49, 57, 58, 62, 63}
}

const uint8_t luminmat[8][8] = {
{16, 11, 10, 16, 124, 140, 151, 161},
{12, 12, 14, 19, 126, 158, 160, 155},
{14, 13, 16, 24, 140, 157, 169, 156},
{14, 17, 22, 29, 151, 187, 180, 162},
{18, 22, 37, 56, 168, 109, 103, 177},
{24, 35, 55, 64, 181, 104, 113, 192},
{49, 64, 78, 87, 103, 121, 120, 101},
{72, 92, 95, 98, 112, 100, 103, 199}
}
const uint8_t chrommat[8][8] = {
{17, 18, 24, 47, 99, 99, 99, 99},
{18, 21, 26, 66, 99, 99, 99, 99},
{24, 26, 56, 99, 99, 99, 99, 99},
{47, 66, 99, 99, 99, 99, 99, 99},
{99, 99, 99, 99, 99, 99, 99, 99},
{99, 99, 99, 99, 99, 99, 99, 99},
{99, 99, 99, 99, 99, 99, 99, 99},
{99, 99, 99, 99, 99, 99, 99, 99},

void matZigZag(int8_t in[8][8],int8_t out[64]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            out[8*i+j]=*(in + matzigzag[i][j]);
        }
    }
};
void matZigZagGet(int8_t in[64],int8_t out[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            out[i][j] = *(in + matzigzag[i][j])
        }
    }
};
uint8_t bitNo(int8_t val){
    uint8_t r=0;int8_t v=val
    for(;v;v>>1){r++;};
    return r;
};
void Rle(std::vector<int8_t>& result, int8_t mat[64]){
    uint8_t zero=0;uint8_t ind=0;
    result.resize(64);
    for(int i=1;i<64;i++){
        if(mat[i]==0){zero++;}
        else {
            result[ind]=zero<<4+bitNo(mat[i]);ind++;
            result[ind]=mat[i];ind++; }
        if(zero ==16){result[ind]=15<<4;ind++;result[ind]=0;ind++;}
    };
ind--;
    for(;result[ind]==0;ind-=2){}
    ind++;
    result[ind]=0;ind++;result[ind]=0;
    result.resize(ind);  
};
void RLEd(std::vector<int8_t>& in,int8_t mat[64]){
    uint8_t ind=0;
    for(int i=1;i<in.size();i++){
        for(int j=0;j<in[j];j++){
            mat[ind]=in[i+1];ind++;
        }
        i++;
    };
};
void offset=0;
void addToVec(std::vector<int8_t>& rles,std::vector<std::vector<int8_t>> rl ,int8_t* rle ;uint8_t size){
    uint32_t s = rles.size();
    uint32_t si = size -offset;
    int8_t* rleptr = rle + offset;
    rles.resize(s+si);
    std::memcpy(rles.data(),rleptr,si);
    std::vector<int8_t> vec(si);
    std::memcpy(vec.data(),rleptr,si);
    rl.push_back(vec);
};

template <typename table>
void qt(mod::image2D& YCC,uint8_t quality){
    std::vector<int8_t> rles;
    std::vector<std::vector<int8_t>> rl; 
    double ycoef[8][8];double crcoef[8][8];double cbcoef[8][8];
    DQT_.qtable[0].get(ycoef);
    DQT_.qtable[1].get(crcoef);
    DQT_.qtable[1].get(cbcoef);

    void (*addVec)(std::vector<int8_t>& ,std::vector<std::vector<int8_t>>rl,int8_t* rls,uint8_t size) ;
    void (*coef)(mod::image2D&,uint32_t,uint32_t,double[8][8],double[8][8],double[8][8]) ; 

    void (*encode)(char* src,size_t srcsize,table* tab,char* dest,size_t* destsie) ;
    if constexpr (std::is_same<table,clib::actbs>::value ){encode = &arithmetic_encode;}
    if constexpr (std::is_same<table,clib::huff_tree>::value ){ encode  = &huffman_encode;}
    
    // Differential progressive sequential  handle
    if(sequential){offset = 0;}
    if(lossless){coef=&losslessCoef}
    else if(dct){coef = &dctCoef;}
    double prevDc;
    for(uint32_t j=0;i<wd;j++){
        
        for(uint32_t i=0;i<hd;i++){ // TODO do by length and sample spec
            double yc[8][8];double cr[8][8];double cb[8][8];
            // uint32_t i,j;i=k/wd; j=k%wd;
            // DQT::qtb dc ; DQT_.did(SOS_.cmspec[j].tdc(),dc);
            // DQT::qtb ac ; DQT_.did(SOS_.cmspec[j].tac(),ac);

            // uint8_t dcmat[8][8] ; dc.get(dcmat);
            // uint8_t acmat[8][8] ; ac.get(acmat);
        
            coef(YCC,j,i,yc,cr,cb);
            qmatrix(ycoef,ycoef,quality);
            qmatrix(crcoef,crcoef,quality);
            qmatrix(cbcoef,cbcoef,quality);

        std::vector<int8_t> rle ;int8_t dest[64];size_t destSize; huffmanTree tree;  

        matZigZag(dest,ycoef);
        Rle(rle,dest);
        addToVec(rles,rl,rle.data(),size); 
        matZigZag(dest,crcoef);
        Rle(rle,dest);
        addToVec(rles,rl,rle.data(),size);
        matZigZag(dest,cbcoef);
        Rle(rle,dest);
        addToVec(rles,rl,rle.data(),size);
    };
    };
    
    // Dc differenece encode ;
    if(differential) {
        for(int i=acs.size()-1;i>0;i--){acs[i] = acs[i] - acs[i-1];};
    }
        table* tree; char* dest;size_t* destlen;
   
tree->htInfo=0;tree->length();
    auto lam =[&](){size_t s=data.SOS_.data.size();
        data.SOS_.data.resize(s+*destlen)
        std::memcpy(SOS_.data.data()+s,dest,*destlen);}
    encode(rles.data(),rles.size(),tree,dest,destlen);
    if constexpr (std::is_same<table,clib::actbs>::value ){}
    if constexpr (std::is_same<table,clib::huff_tree>::value ){}
    
    tree->htInfo=0b00010001;tree->length();
    DHT_.trees.push_back(*tree) ; 
    lam();
}


uint32_t ind=0;
template <typename table>
void dqt(mod::image2D& YCC,uint8_t quality){
    std::vector<int8_t> rles;
    std::vector<std::vector<int8_t>> rl; 
  
    offset = 0;
    void (*addVec)(std::vector<int8_t>& ,std::vector<std::vector<int8_t>>rl,int8_t* rls,uint8_t size) ;
    void (*coefGet)(mod::image2D&,uint32_t,uint32_t,double[8][8],double[8][8],double[8][8]) ; 

    void (*decode)(char* src,size_t srcsize,table* tab,char* dest,size_t* destsie) ;
  
    // Differential progressive sequential  handle
    if(sequential){offset = 0;}
    if(lossless){coefGet=&losslessCoefGet}
    else if(dct){coefGet = &dctCoefGet;}
    double prevDc;
uint32_t inds = ind;

 // Dc differenece encode ;
    table* tree; uint8_t* dest;size_t* destlen; 
    if constexpr (std::is_same<table,clib::actbs>::value ){decode= &arithmetic_decode;}
    if constexpr (std::is_same<table,clib::huff_tree>::value ){encode == &huffman_decode;}
    
    decode(SOS_.data.data(),SOS_.data.size(),tree,fest,destlen);

    if constexpr (std::is_same<table,clib::actbs>::value ){decode=  &arithmetic_decode;DAC_.table=tree->tbs;DAC_.length=tree->size/2; }
    if constexpr (std::is_same<table,clib::huff_tree>::value ){encode = &huffman_decode;tree->htInfo=0b00010001;tree->length();
    DHT_.trees.push_back(*tree) ; }

    uint32_t dataOffs=0;
    
    for(uint32_t k=0;k<SOS_.numCom  and (ind<im.imageSize);k++){
            SOF::cmpspec dc;DQT_.did(SOS_.comSpec[k].tdc(),dc);
            SOF::cmpspec ac;DQT_.did(SOS_.comSpec[k].tac(),ac);


            // double yc[8][8];double cr[8][8];double cb[8][8];
            uint32_t i,j;i=ind/wd; j=ind%wd;
            DQT::qtb dc ; DQT_.did(SOS_.cmspec[j].tdc(),dc);
            DQT::qtb ac ; DQT_.did(SOS_.cmspec[j].tac(),ac);

            uint8_t dcmat[8][8] ; dc.get(dcmat);
            uint8_t acmat[8][8] ; ac.get(acmat);
        

        int8_t dest[64];size_t destSize; huffmanTree tree;  
        uint32_t it;
        for( it = dataOffs;dest[it]==0 and (dest[it+1] == 0);it++){}
        it+=2;
        std::vector<int8_t> rle(it-dest);
        std::memcpy(rle.data(),dest+dataOffs,rle.size())
        dataOffs=it;
        Rled(rle,dest);
        matZigZagGet(dest,ycoef);
        addToVec(rles,rl,rle.data(),size); acs.push_back(ycoef[0]);


        Rled(rle,dest);
        matZigZagGet(dest,crcoef);
        addToVec(rles,rl,rle.data(),size);acs.push_back(crcoef[0]);
        Rled(rle,dest);
        matZigZagGet(dest,cbcoef);
        addToVec(rles,rl,rle.data(),size);acs.push_back(cbcoef[0]);
    };
    };
    
   
}
mod::image2D qtinit(mod::image2D& im){
    
    uint8_t wm=YCC.width %8 ; 
    uint8_t hm=YCC.height %8 ; 
    uint8_t wd=YCC.width /8 ; 
    uint8_t hd=YCC.height /8 ; 
    SOF_.X = im.width;
    SOF_.Y = im.height;
    // SOF_.
    DQT_.n = 2;
    DQT_.qtable = new DQT::qtb[2];
    DQT_.qtable[0].put(luminmat);
    DQT_.qtable[0].prec_did = 0;
    DQT_.qtable[1].put(chrommat);
    DQT_.qtable[1].prec_did = 1;

    SOS_.numCom = wd*hd*im.length;
    SOS_.comSpec=new SOS::cmspec[SOS_.numCom];
    for(uint32_t i=0;i<SOS_.numCom;i++){
        SOS_.comSpec[i].id = i;
        SOS_.comSpec[i].TdTa = i%3?(3<<4)|0:(4<<4)|1;
    }

    
    return sRGBtoYCC(im);

};
void qtwr(mod::image2D& im,uint32_t w,uint32_t h,uint32_t x,uint32_t y){
    mod::image2D YCC = qtinit(im);
    
    qt<clib::huff_tree>(YCC,w,h,x,y);


};
void qtwr(mod::image2D& im,uint8_t quality,segs SOFmark){
    mod::image2D YCC = qtinit(im);
    switch(SOFmark) {
        #define SOFMARK (m) case segs::_##m : {set##m;break;}
        REPEAT(SOFMARK SOF0,SOF1,SOF2,SOF3,SOF5,SOF6,SOF7,SOF9,SOF10,SOF11,SOF13,SOF14,SOF15)
        }
    }
    qt<clib::huff_tree>(YCC,quality);

};

void ldStartScan(mod::image2D& im){
    for(uint8_t i==0;i<SOS_.numberOfCOmponents;i++){
        SOS::cmspec&  SOScs=  SOS_.comSpec[i];
        SOF::cmpspec& SOFcs; bool bocs = SOF_.findCID(SOScs.id,SOFcs);
        uint8_t tdc = SOScs.tdc();
        uint8_t tda = SOScs.tac();
        DQT::qtb& qt;bool boqt=DQT_.did(SOFcs.qtbDestSel,qt);
        if(arithmeticCoding){
            dqt<DAC>(YCC);
        }
        if(huff){
            clib::huff_tree& htdc;
            clib::huff_tree& htac;
            bool bohtdc = DHT_.id(tdc,htdc);
            bool bohtac = DHT_.id(tda,htda);
                        dqt<clib::huff_tree>(YCC);

        }
    };
};



uint32_t compno=0;
void dequantize(mod::image2D& YCC,uint32_t x,uint32_t y,uint32_t w,uint32_t h){ // Starts at scan
    for(uint32_t i=0;data.SOS_.numCom;i++){
        uint8_t dc=data.SOS_.comSpec.tdc();
        uint8_t ac=data.SOS_.comSpec.tac();
    
    };
};
 
void dequantize(mod::image2D& YCC){ // 
    dequantize(YCC,0,0,data.SOF_.width,data.SOF_.height);
};


    void ld(mod::image2D& im,std::ifstream& fi){
        ld(segstart,fi);
        ld(SOI_,fi);
        uint8_t seg;
        uint8_t segt=seg::_SOI;
        ld(seg,fi);
        ld(segt,fi);
        while(segt!=segs::_EOI and (seg == segstart)){
            if(segt>=_RSTN and (segt<=_RST7) ){RST=segt-segs::_RSTn;rst=true;};
            switch(segt){
                #define CASE_JPEGTAG(n) case _##n : {ld(##n_,fi);break;} 
                REPEAT(CASE_JPEGTAG,DHT,DQT,APPn,COM,DNL)   
                        case _DNL {ld(DNL_,fi);}
                        case _DRI : { DRIb=true; ld(DRI_,fi);}break;
                        case _SOS : {ld(SOS_,fi);ldStartScan(im);break;}

                        case _SOF0 : {ld(SOF_,fi);setSOF0();break;};
                        case _SOF1 : {ld(SOF_,fi);setSOF1();break;};
                        case _SOF2 : {ld(SOF_,fi);setSOF2();break;};
                        case _SOF3 : {ld(SOF_,fi);setSOF3();break;};
                        case _SOF5 : {ld(SOF_,fi);setSOF5();break;};
                        case _SOF6 : {ld(SOF_,fi);setSOF6();break;};
                        case _SOF7 : {ld(SOF_,fi);setSOF7();break;};
                        case _SOF9 : {ld(SOF_,fi);setSOF9();break;};
                        case _SOF10 : {ld(SOF_,fi);setSOF10();break;};
                        case _SOF11 : {ld(SOF_,fi);setSOF11();break;};
                        case _SOF13 : {ld(SOF_,fi);setSOF13();break;};
                        case _SOF14 : {ld(SOF_,fi);setSOF14();break;};
                        case _SOF15 : {ld(SOF_,fi);setSOF15();break;};
                        case _DHP  : (ld(DHP_,fi);hierarchical=true;)
                        case _EXP : { ld(EXP_,fi);}
                    }
            if(segt >= segt::_SOF0 and (segt<=_SOF11)){
                if(SOF_.Y == 0){dnlDef = true;}
                else{im.height=SOF_.Y;
                    im.width = SOF_.X;
                    im.length = SOF_.Nfl
                
                }
            };
            ld(seg,fi);
            ld(segt,fi);
        };
    };
    void wrSeg(std::ofstream& of,segs s){wr(segstart,of);wr(s,of);}
    void wr(std::ofstream& of){
        wrSeg(of,segs::_SOI);
        wrSegs(of,SOFT);wr(SOF_,of);}
        else{wrSegs(of,segs::_SOF2);wr(data,SOF2_,of);}
        wrSeg(of,segs::_DQT);wr(data.DQT,of);
        // wr(data.DRI_);
        wrSeg(of,segs::_DHT);wr(data.DHT_,of);
        wrSeg(of,segs::_SOF);wr(data.SOF_,of);
        if(dnlDef){
        wrSeg(of,segs::_DNL);wr(data.DNL_,of);
        }
        wrSeg(of,segs::_SOS);wr(data.SOS_,of);

        wrSeg(of,segs::_APPn);wr(data.APPn_,of);
        wrSeg(of,segs::_COM);wr(data.COM_,of);
        wrSeg(of,segs::_EOI);
    }
    void encode(mod::image2D& im,uint8_t quality){
        data.SOF_.width=im.width;
        data.SOF_.height=im.height;
        data.SOF_.numcomponents=3;
        uint8_t cmpsb[] = {4,4,4};
        std::memcpy(data.SOF_.componentSubSampling,&cmpsb,3);
        
        setDQT({qmatrix},1);
        std::memcpy(data.DQT_.qtable,qmatrix,64);
        

        if(im.imageFormat!=mod::image_formats::rgb8){im.to<mod::image_formats::rgb8>();};

        image2D& YCC = sRGBto_YCC(im) ;
        quantize(YCC,qmatrix,quality);
    };  
    mod::image2D decode( uint32_t x,uint32_t y,uint32_t w,uint32_t h){
        mod::image2D im;
        dequantize(im,x,y,w,h);
        mod::image2D res=YCCtoRGB(im);
        return res;
    }
    void wr(std::string path ,mod::image2D& im, uint8_t quality=100){
        encode(im,quality);
    }
    mod::image2D ld(std::string path, uint32_t x,uint32_t y,uint32_t w,uint32_t h){
        std::ifstream fi(path);
        ld(data,fi,x,y,w,h);
        mod::image2D im=decode(x,y,w,h);
    };
     mod::image2D ld(std::string path){
        std::ifstream fi(path);
        ld(data,fi);
        mod::image2D im;ld(im,fi);
    };


};

#endif