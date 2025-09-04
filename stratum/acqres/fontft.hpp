#ifndef STRATA_FONT_HPP
#define STRATA_FONT_HPP
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <cstddef>
#include <type_traits>
#include <vector>
#include <string>
#include <petri/defs>
#include <petri/macros.hpp>
#include <glm/glm.hpp>
#include <uchar.h>
#include <stratum/acqres/acqres.hpp>
#include <algorithm>
#include <stratum/mod_paint.hpp>
#include <stratum/mod_font.hpp>
#include <type_traits>
#include <petri/tuple.hpp>
#include <petri/variant.hpp>
#include <petri/templates.hpp>
namespace ttf {

typedef uint32_t IndexP;


template <size_t s>
struct uintTT {
    uint8_t d[s];
    template <typename uintT>
    void fit(uintT r){
        constexpr size_t size = sizeof(uintT) ;
        for(size_t ss = 0 ; ss<s;ss++){
            if(size>ss){ d[s-ss] = r & ((1<<8 -1)<<(ss*8));}
        }
    }
    template <typename uintT>
    uintT get(){
                constexpr size_t size = sizeof(uintT) ;
        uintT r=0;
        for(size_t ss = 0 ; ss<s;ss++){
            if(size>ss){r|=d[s-ss]<<(8*ss);}
        }
    };
     operator size_t() {
        return get<size_t>();
    };
    decltype(*this) operator=(size_t s){
        fit<size_t>(s);return *this;
    };
    uintTT()

};
typedef uintTT<3> uint24_t ;

 typedef signed long Fixed; 
    typedef uint32_t Tag ;
    // typedef uint8_t[4] Tag ;
    typedef int16_t FWORD ;
    typedef uint16_t UFWORD ;
    typedef uint16_t F2DOT14 ;
    typedef uint16_t F2DOT14 ;
    typedef int64_t F2DOT14 ;
    
    
    typedef uint8_t Offset8 ;
    typedef uint16_t Offset16 ;
    typedef uint32_t Offset32 ;
    typedef uint24_t Offset24 ;
    typedef uint32_t Version16Dot16 ;
    
    typedef int16_t int16 ;
    typedef uint16_t uint16 ;
    typedef uint16_t uint16 ;
    typedef uint16_t uint16 ;
    typedef int64_t int64 ;
    
    
    typedef uint8_t uint8 ;
    typedef uint16_t uint16 ;
    typedef uint32_t uint32 ;
    // typedef uint24_t uint24 ;
    typedef uint32_t uint32 ;

    typedef int64_t LONGDATETIME;

    
    // Globals
    size_t _sizeTable;
    constexpr Tag font_tag(char s[4]){Tag i ;
    int8_t c = (int8_t)s[0];i = c<<24;
    c= (int8_t)s[1]; i = i+(c<<16) ;
    c = (int8_t)s[2];i = i+(c<<8);
    c= (int8_t)s[3];i=i+c; 
    return i;};
    
    void font_tag(Tag i, char* s){Tag r=i;s[0] = (char)(r>>24) ; s[1] = (char)(r>>16); s[2] = (char)(r>>8); s[3]=(char)(r);}
using coord = glm:::ivec2; 
struct glyfbm {
    uint16 glyphID;
    coord pos;
    int16   xMin;
    int16   yMin;
    int16   xMax;
    int16   yMax;
    uint16 height,width;
    glm::uvec4 color;
    float alpha ;
    uint32 size;
    glm::uvec4* bitmap;
    void blit(uint16 xOffset,uint16 yOffset,glyfm& bm){
        for(int i=xOffset;i<width;i++){
            for(int j=yOffset;j<height){
                if((i-xOffset)*bm.width+j-yOffset > bm.size){return;}
                bitmap[i*width+j]=bm.bitmap[(i-xOffset)*bm.width+j-yOffset];
            };
        }
    };
};  


template <size_t s>
constexpr size_t fontColorTupPos() {
    return pri::get_size<ptype<s>,mod::font::fontColor::tytup>(); 
};

template <> struct fontColorTupPos<1> {using ty = void;};



struct colorFT  {
    glm::uvec4 color;
    float alpha;
    uint16 numbaseGlyphs;
    uint16* baseGlyphs;
    uint16 numLayers;
    colrff<varValueBase,1>* layers;
    uint16 numValues;
    colrf<varValueBase>* values;

    ALIAS_VECT(colrf<varValueBase>,uint16,layers,numLayers)
    ALIAS_VECT(colrf<varValueBase>,uint16,values,numValues)
    
template < template <size_t > typename T,size_t s>
struct Tcase {
    static bool operator()(size_t is){
        if(is==s){T<is>();return true;}
        else {Tcase<T,sS...>()}
    };
};


template < template <size_t > typename T>
struct Tcase {
    static bool operator()(size_t is){
        if(is==s){T<is>();return true;}
        else {return false;}
    };
};

    template <typename charT,typename COLRFty>
    mod::fontColor<charT> get(COLRFty& colrft){
        mod::fontColor<charT> r ;
        size_t cur;
        #define CFXMACRO(x)  x(2) x(3) x(4) x(5) x(6) x(7) x(8) x(9)   x(12) x(13) x(14) x(15) x(16) x(17) x(18) x(19) x(20) x(21) x(22) x(23) x(24) x(25) x(26) x(27) x(28) x(29) x(30) x(31) 
         #define CFIXMACRO(x) x(1) x(10) x(11) x(32)

         #define COMMACRO(n) ,n
         size_t indV;
         std::vector<size_t> colGlyphs;
         size_t curColGlyph=0;
         std::vector<std::pair<size_t,size_t>> composePaints;
         size_t curComposePaint=0;
         std::vector<std::pair<size_t,size_t>> inds;
          size_t curTup ;

         auto lamcase = [&]<size_t s>(){ptype<n>::ty h= pri::get<n-1>(values[indV].f).getPaint();
            std::vector<ptype<n>::ty& ref =pri::get<std::vector<ptype<n>::ty>>(r.tupvec) 
            ref.push_back(h) ;  r.layers.back().push_back(mod::fontColor::layerE(fontColorTupPos<n>(),ref.size()-1));
            inds.push_back(std::pair<size_t,size_t>(fontColrTupPos<n>(),pri::get<fontColrTupPos<n>()>(r.tupvec).size()-1)) ;
            curTup =fontColrTupPos<n>();
            continue;}
                
            auto swlam = [&](){
                if(Tcase<lamcase CFXMACRO(COMMACRO)>()){return;};
                switch(values[indV].format){

                    case 10 :{
                        colrff<varValueBase,10>& h = pri::get<10>(values[indV].f);
                        mod::fontColor::ColGlyph g(h.glyphID);
                        r.colglyph.push_back(g) ;
                        colGlyphs.push_back(h.paintOffset);continue;}
                    case 11 :{
colrff<varValueBase,11>& h = pri::get<11>(values[indV].f);
                    mod::fontColor::SubGlyph g(h.glyphID);r.subGlyph.push_back(g) ;continue;}

                    case 32 :{
                        colrff<varValueBase,32>& h = pri::get<11>(values[indV].f);
                        composePaints.push_back(std::pair<size_t,size_t>(h.sourcePaintOffset,h.backfropPaintOffset)) ;
                        // pri::get<std::vector<ptype<32>::ty>>(r.tupvec) 
                        r.composePts.push_back(h); 
                        continue;}
                }
            }
            auto incr = [&](){
                if(indV == colGlyphs[curColGlyph]){
                    pri::get<std::vector<mod::fontColor<ColGlyph>>(r.tupVec)[curColGlyph].lyr=mod::fontColor::layerE(curTup, pri::get(curTup,r.tupvec).size()-1);
                };
            }
         for(size_t s =0;s<numLayers;s++){
         auto lyrlam =[&](colrff<varValueBase,1>& lyr){
            if(lyr.firstLayerIndex>numLayers){
                size_t p = lyr.firstLayerIndex-numLayers;s++;
                for(size_t j=0;j<p;j++){
                    lyrlam(layers[s])
                    for(indV=lyr.firstLayerIndex;indV<lyt.numLayers;indV++){
                       swlam();incr();  }                   
                    s++; 
                };
            }
            else {
            for( indV=lyr.firstLayerIndex;indV<lyr.numLayers;indV++){
                    swlam();
                };
            }

            }
            r.layers.push_back(pri::list<mod::fontColor::layerE>());
            lyrlam(layers[s]);

        };
    };
};
struct glyfft{
    uint16 glyphID;
    coord pos;
    int16   numberOfContours;
    int16   xMin;
    int16   yMin;
    int16   xMax;
    int16   yMax;
    colorFT colors;
    uint16* endPts ;// [numberOfContours]
    uint16 advanceWidth ;
    int16 lsb;
    uint16 sizeContour;
    glm::ivec2* contours;/// [sizeContour]
    bool* onCurve;//[sizeContour] 
    int16 righSideBearing(font* f){return advanceWidth - xMax ;}
    int16 width(font* f){return xMax-xMin;}
    void popContour(uint index){
         numberOfContours--;
        uint16 dif = (endPts[index] - endPts[index-1]);
        uint8 sizeContour -= dif;
        for(int i=endPts[index-1]+1;i<=endPts[index] and i<sizeContour;i++){
            contours[i]=contours[i+dif];
        };
        for(int i=index ;i<numberOfContours;i++ )
        {
            endPts[i]=endPts[i+1];
        }
    };
    void addPt(uint indContour,int indPt,glm::uvec2 pt,bool onCurve ){
        sizeContour++;
        uint index =indContour==0?indPt:endPts[indContour-1]+indPt;
        glm::uvec2* cont = new glm::uvec2[sizeContour];
        bool* fl = new bool[sizeContour]; 
        cont[index] = pt; 
        fl[endPts[indContour-1] + indPt] = onCurve;
        for(int i=0;i<index;i++){
            cont[i]=countours[i];
            fl[i]=flags[i];
        };
        
        for(int i=index+1;i<sizeContour;i++){
            cont[i]=countours[i-1];
            fl[i]=flags[i-1]
        };
        contours=cont;
        onCurve=fl;
        for(int i=indContour;i<numberOfContours;i++){endPts[i]++;};
    };
    void popPt(uint indContour,int indPt){
        for(int i=endPts[indContour-1] + indPt;i<sizeContour;i++){
            cont[i]=countours[i+1];
            onCurve[i]=onCurve[i+1];
        };
    };
    void addContour(uint index){
        numberOfContours++;
        uint8 nendpt = endPts[index];
        uint8* enp = new uint16[numberOfContours];
        for(int i=0;i<=index;i++){
            enp[i]=endPts[i];
        };
        for(int i=index+1;i<numberOfContours;i++){
            enp[i]=enp[i-1];
        };
    };
    void addPtAndContour(uint index,glm::uvec2 pt,bool onCurve){
        addContour(index);
        addPt(index,0,pt,unCurve);
    };
    void fromGlyfHead(glyfHead* gh){
    glyfft res;
    numberOfContours = gh->numberOfContours;
    xMin = gh->xMin;
    yMin = gh->yMin;
    xMax = gh->xMax;
    yMax = gh->yMax;
    sizeContour= gh->f.sg.xCoordNum>gh->f.sg.yCoordNum?gh->f.sg.xCoordNum:gh->f.sg.yCoordNum;
    if(gh->numberOfContours>=0){
        endPts=uint16[numberOfContours];
        for(int i=0;numberOfContours;i++){endPts[i] = gh->f.sg.endPtsOfContours[i];}

        for(int i=0;i<gh->f.sg.flagNum;i++){
            if(gh->f.sg.flag[i] &( X_SHORT_VECTOR | X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR ) ){sizeContour++;continue;}
            if(gh->f.sg.flag[i] &( Y_SHORT_VECTOR | Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR ) ){sizeContour++;};
        };
        contours = new coord[sizeContour]; int x,y;x=0;y=0;
        flags = new PTflags[sizeContour]  ;
        for(int i=0;i<gh->f.sg.flagNum;i++){
            onCurve[j] =0;
            
             onCurve[fn]|=(gh->f.sg.flag[i] & ON_CURVE_POINT)?true:0;
             
                if(gh->f.sg.flag[i] & ( X_SHORT_VECTOR )){
                    if(gh->f.sg.flag[i]& X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR ){
                        contours[x].x =gh->f.sg.xCoordinates[j];
                    }
                    else {contours[x].x =-gh->f.sg.xCoordinates[j];}
                }
                else {
                    if(gh->f.sg.flag[i]& X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR ){
                        contours[fn].x =contours[y-1];--x;
                    }
                    else {
                        contours[fn].x = gh->f.sg.xCoordinates[j]<<8 + gh->f.sg.xCoordinates[j];
                    }
                }
                if(gh->f.sg.flag[fn] & ( Y_SHORT_VECTOR )){
                    if(gh->f.sg.flag[fn]& Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR ){
                        contours[fn].y =gh->f.sg.yCoordinates[j];
                    }
                    else {contours[fn].y =-gh->f.sg.yCoordinates[j];}
                }
                else {
                    if(gh->f.sg.flag[fn]& Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR ){
                        contours[fn].y =contours[y-1];--y;
                    }
                    else {
                        contours[fn].y = gh->f.sg.xCoordinates[y]<<8 + gh->f.sg.xCoordinates[y];
                    }
                };
             if(! (gh->f.sg.flags[i] & (X_SHORT_VECTOR | X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR))){
                contours[fn].x += contours[fn-1].x;};
             if(! (gh->f.sg.flags[i] & (Y_SHORT_VECTOR | Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR))){
                contours[fn].y += contours[fn-1].y;};
            x++;y++;
        };
    }
    else {
        
    }
}
    glyfHead get(){
        glyfHead gh;
        gh.numberOfContours=numberOfContours;
gh.xMin=xMin;
gh.yMin=yMin;
gh.xMax=xMax;
gh.yMax=yMax;
gh.f.sg.endPtsOfContours = endPts;

gh.f.sg.flags = new uint8[sizeContour];
gh.f.sg.flagNum = sizeContour;
gh.f.sg.xCoordinates = new int8[sizeContour];
gh.g.sg.yCooridnates = new int8[sizeContour];
for(int i=0;i<sizeContour;i++){
    gh.f.sg.flags[i]=0;
    if(onCurve[i]){gh.f.sg.flags[i]|= ON_CURVE_POINT ;}
        gh.f.sg.flags!=X_SHORT_VECTOR | Y_SHORT_VECTOR ;
    if(contours[i].x>=0){gh.f.sg.flags[i] |= X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR ;gh.f.sg.xCoordinates[i]=contours[i].x;}
    else {gh.f.sg.xCoordinates[i]=-contours[i].x;}
    if(contours[i].y>=0){gh.f.sg.flags[i] |= Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR ; gh.f.sg.yCoordinates[i]=contours[i].y;}
    else { gh.f.sg.yCoordinates[i]=-contours[i].y;}

};
return gh;
};
};
struct glyfftprim { // To convert to primitives
    coord pos;
    int16 nStrips;
    int16 nFans;

    int16* nStripsPts;//Triangle+2
    int16* nFansPts;//

    glm::ivec2* strips;//nStripsPts 
    glm::ivec2* fan; // n
    
    colorFT* colors;//[nstrips]


    void from(glyfft g){

    };
};  

template <typename charT>
struct ftrange {
    glyfft* range;
    charT start,end;
    uint16 size;
    
    uint16 startGlyphID;

    glyfft* get(charT c){
        if(c>=start and c<=end){return &(glyfft[c-start]);}
        return &(range[0]);
    };
};


#define TAG_MEMBER(macro)\
macro("avar",avar)\
macro("BASE",BASE)\
macro("CBDT",CBDT)\
macro("CBLC",CBLC)\
macro("CFF ",CFF)\
macro("CFF2",CFF2)\
macro("cmap",cmap)\
macro("COLR",COLR)\
macro("CPAL",CPAL)\
macro("cvar",cvar)\
macro("cvt ",cvt)\
macro("DSIG",DSIG)\
macro("EBDT",EBDT)\
macro("EBLC",EBLC)\
macro("EBSC",EBSC)\
macro("fpgm",fpgm)\
macro("fvar",fvar)\
macro("gasp",gasp)\
macro("GDEF",GDEF)\
macro("glyf",glyf)\
macro("GPOS",GPOS)\
macro("GSUB",GSUB)\
macro("gvar",gvar)\
macro("hdmx",hdmx)\
macro("head",head)\
macro("hhea",hhea)\
macro("hmtx",hmtx)\
macro("HVAR",HVAR)\
macro("JSTF",JSTF)\
macro("kern",kern)\
macro("loca",loca)\
macro("LTSH",LTSH)\
macro("MATH",MATH)\
macro("maxp",maxp)\
macro("MERG",MERG)\
macro("meta",meta)\
macro("MVAR",MVAR)\
macro("name",name)\
macro("OS/2",os2)\
macro("PCLT",PCLT)\
macro("post",post)\
macro("prep",prep)\
macro("sbix",sbix)\
macro("STAT",STAT)\
macro("SVG ",SVG)\
macro("VDMX",VDMX)\
macro("vhea",vhea)\
macro("vmtx",vmtx)\
macro("VORG",VORG)\
macro("VVAR",VVAR)\



  typedef union  {
        avar _avar;
        BASE _BASE;
        CBDT _CBDT;
        CBLC _CBLC;
        CFF _CFF;
        CFF2 _CFF2;
        cmap _cmap;
        COLR _COLR;
        CPAL _CPAL;
        cvar _cvar;
        cvt _cvt;
        DSIG _DSIG;
        EBDT _EBDT;
        EBLC _EBLC;
        EBSC _EBSC;
        fpgm _fpgm;
        fvar _fvar;
        gasp _gasp;
        GDEF _GDEF;
        glyf _glyf;
        GPOS _GPOS;
        GSUB _GSUB;
        gvar _gvar;
        hdmx _hdmx;
        head _head;
        hhea _hhea;
        hmtx _hmtx;
        HVAR _HVAR;
        JSTF _JSTF;
        kern _kern;
        loca _loca;
        LTSH _LTSH;
        MATH _MATH;
        maxp _maxp;
        MERG _MERG;
        meta _meta;
        MVAR _MVAR;
        name _name;  
        os2 _os2;
        PCLT _PCLT;
        post _post;
        prep _prep;
        sbix _sbix;
        STAT _STAT;
        SVG _SVG;
        VDMX _VDMX;
        vhea _vhea;
        vmtx _vmtx;
        VORG _VORG;
        VVAR _VVAR;
    }tableu;
    /// @brief otff //[]


uint16 _ftTBI;// Table Inex
uint32 _length ;
typedef struct {
Tag   tableTag;
uint32   checksum;
Offset32   offset;
uint32   length;
/// @category: noldwr
uint16 index;
}TableRecord;
ACQRES(TableRecord){
    one(f);
    _length = f.length;
    f.index=_ftTbi;
};
USE_ACQRES(TableRecord);
   typedef struct {
uint32   sfntVersion;
uint16   numTables;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
TableRecord*   tableRecords;//[numTables]
}TableDirectory;
ACQRES(TableDirectory){
one(f.sfntVersion);
one(f.numTables);
one(f.searchRange);
one(f.entrySelector);
one(f.rangeShift);
arr(f.tableRecords, f.numTables);
 };
USE_ACQRES(TableDirectory)

typedef struct {
// Tag   ttcTag;
// uint16   majorVersion;
// uint16   minorVersion;
// uint32   numFonts;
// Offset32*   tableDirectoryOffsets;//[numFonts]
uint32   dsigTag;
uint32   dsigLength;
uint32   dsigOffset;
}TTCHeader2;
ACQRES(TTCHeader2){
// one(f.numFonts);
// arr(f.tableDirectoryOffsets, f.numFonts);
one(f.dsigTag);
one(f.dsigLength);
one(f.dsigOffset);
};
USE_ACQRES(TTCHeader2)


struct TTChead  { // TODO
    Tag   ttcTag;
uint16   majorVersion;
uint16   minorVersion;
uint32   numFonts;
Offset32*   tableDirectoryOffsets;//[numFonts]
    //
    TTCHeader2 f2;
    TableDirectory* tableDirectories;//[numFonts]

    tableu* tbs ;//[ td.numTables]

 
};
ACQRES(TTChead){
one(f.ttcTag);
one(f.majorVersion);
one(f.minorVersion);
one(f.numFonts);
size_t tbsSize=0;
switch(f.majorVersion){
    case 2 : {one(f.f2);    }
};

if(!f.tableDirectories){f.tableDirectories = new TableDirectory[f.numFonts];};
for(int i=0;i<f.numFonts;i++){offone(f.tableDirectories[i],f.tableDirectoryOffsets[i]);};
size_t s=0;
for(int i=0;i<f.numFonts;i++){s+=f.tableDirectories.numTables;};
if(!f.tbs){f.tbs=new tableu[s];};
_ftTBI=0;
for(int i=0;i<f.numFonts;i++){
    for(int j =0;j<f.tableDirectories[i].numTables){
        switch(f.tableDirectories[i].tableRecords[j].tableTag){
            #define TABLE_RECORD_COL(tag,member) case font_tag(tag):{offone(f.tbs[_ftTBI]._##member,f.tableDirectories[i].tableRecords[j].offset);\
                f.tableDirectories[i].tableRecords[j].length=f.tbs[_ftTBI]._##member  ;\
            };
            TAG_MEMBER(TABLE_RECORD_COL)
        }
        _ftTBI++;
    }
}
}
USE_ACQRES(TTChead)
typedef TTChead fontcollection ;


uint32_t CalcTableChecksum(uint32_t *Table, uint32_t Length){
       uint32 Sum = 0L;
uint32 *EndPtr = Table+((Length+3) & ~3) / sizeof(uint32);
while (Table < EndPtr)
    Sum += *Table++;
return Sum;
}
#define REPEAT(macro)
#define REPEAT(macro,a) macro(a)
#define REPEAT(macro,a,...) macro(a) REPEAT(macro,__VA_ARG__)

#define CASE_ONE(n) case n : {one(f.u,f##n);}\


     struct font {
                TableDirectory td ;
        tableu* table;

        #define TBINDEX(m) int ##mI=-1;m& m(){return table[##mI]._##m;};
        REPEAT(TBINDEX,avar, BASE, CBDT, CBLC, CFF, CFF2, cmap, COLR, CPAL, cvar, cvt, DS,G, EBDT, EBLC, EBSC, fpgm, fvar, gasp, GDEF, glyf, GPOS, GSUB, gvar, hdmx, head, hhea, hmtx, HVAR, JSTF, kern, loca, LTSH, MATH, maxp, MERG, meta, MVAR, name, os2, PCLT, post, prep, sbix, STAT, SVG, VDMX, vhea, vmtx, VORG, VVAR)
     
        #include "ft/avar.hpp" //[x]
#include "ft/base.hpp" //[x]
#include "ft/ebsc.hpp" //[x]
    #include "ft/ebdt.hpp" //[x]
    #include "ft/eblc.hpp" //[x]

#include "ft/cbdt.hpp" //[x]
#include "ft/cblc.hpp" //[x]
#include "ft/cff.hpp" //[]
#include "ft/cff2.hpp" //[]
#include "ft/cmap.hpp" //[x]
#include "ft/loca.hpp" //[x]
    #include "ft/colr.hpp" //[x]
    #include "ft/cpal.hpp" //[x]
    #include "ft/cvar.hpp" //[x]
    #include "ft/cvt.hpp" //[x]
    #include "ft/dsig.hpp" //[x]
    #include "ft/fpgm.hpp" //[x]
    #include "ft/fvar.hpp" //[x]
    #include "ft/gasp.hpp" //[x]
    #include "ft/gdef.hpp" //[x]
    #include "ft/glyf.hpp" //[x]
    #include "ft/gpos.hpp" //[x]
    #include "ft/gsub.hpp" //[x]
    #include "ft/gvar.hpp" //[x]
    #include "ft/hdmx.hpp" //[x]
    #include "ft/head.hpp" //[x]
    #include "ft/hhea.hpp" //[x]
    #include "ft/hmtx.hpp" //[x]
    #include "ft/hvar.hpp" //[x]
    // #include "ft/ibmfc.hpp" //[]
    #include "ft/jstf.hpp" //[x]
    #include "ft/kern.hpp" //[x]
    #include "ft/ltsh.hpp" //[x]
    #include "ft/math.hpp" //[x]
    #include "ft/maxp.hpp" //[x]
    #include "ft/merg.hpp" //[x]
    #include "ft/meta.hpp" //[x]
    #include "ft/mvar.hpp" //[x]
    #include "ft/name.hpp" //[x]
    #include "ft/ompl.hpp" //[y]
    #include "ft/os2.hpp" //[x]
    #include "ft/pclt.hpp" //[x]
    #include "ft/post.hpp" //[x]
    #include "ft/prep.hpp" //[x]
    #include "ft/sbix.hpp" //[x]
    #include "ft/stat.hpp" //[x]
    #include "ft/svg.hpp" //[x]
    #include "ft/vdmx.hpp" //[x]
    #include "ft/vhea.hpp" //[x]
    #include "ft/vmtx.hpp" //[x]
    #include "ft/vorg.hpp" //[x]
    #include "ft/vvar.hpp" //[x]

        constexpr bool wcb = std::is_same<wchar_t,char16_t>::value ; 
        using cVec = std::vector<ftrange<char>> cglyfs ;   ; 
        using wcVec = std::vector<ftrange<wchar_t>> wcglyf;  ;
        using c16Vec = std::enable_if< wcb, std::vector<ftrange<char16_t>>>::type  c16glyf;  
        using c32Vec = std::vector<std::vector<char32_t>> c32glyf;   

        template <typename charT>
        struct vectype {
            using type = std::conditional<charT>
            constexpr  type font::* ptr ; 
        }; 
        cVec cglyfs ;
        wcVec wcglyf;
        c16Vec c16glyf;
        c32Vec c32glyf;
        template <> struct vectype <char> {
             using type = cVec
            constexpr  type font::* ptr = &font::cglyf; }
        template <> struct vectype <wchar_t> {
             using type = wcVec;
            constexpr  type font::* ptr = &font::wcglyf; }
        template <> struct vectype <wchar_t> {
             using type = c16Vec;
            constexpr  type font::* ptr = &font::c16glyf; }
        
        template <> struct vectype <char32_t> {
             using type = c32Vec;
            constexpr  type font::* ptr = &font::c32glyf; }
        
        template <typename charT> 
        uint16 getGid(charT c);
template <>uint16 getGid(char c){
            uint16 res=0;
            for(int j=0;i<f->cglyfs.size();j++){
                if(f->cglyfs[j].start<=fstr.c and f->cglyfs[j].start>=fstr.c ){
                    return f->cglyfs[j].startGlyphId  f->cglyfs[j].range[fstr.c -f->cglyfs[j].end]; 
                }
            }
            return res;
        };
template <>uint16 getGid(wchar_t c){
            uint16 res=0;
            for(int j=0;i<f->wcglyfs.size();j++){
                if(f->wcglyfs[j].start<=fstr.c and f->wcglyfs[j].start>=fstr.c ){
                    return  f->wcglyfs[j].startGlyphId+ f->wcglyfs[j].range[fstr.c -f->wcglyfs[j].start]; 
                }
            }
            return res;
        };
template <>uint16 getGid(char16_t c){
        if constexpr (std::is_same<wchar_t,char16_t>::value ){return getGid<wchar_t>(c);};
             uint16 res=0;
            for(int j=0;i<f->c16glyfs.size();j++){
                if(f->c16glyfs[j].start<=fstr.c and f->c16glyfs[j].start>=fstr.c ){
                    return  f->c16glyfs[j].startGlyphId+ f->c16glyfs[j].range[fstr.c -f->c16glyfs[j].start]; 
                }
            }
            return res;
        };
template <>uint16 getGid(char32_t c){
             uint16 res=0;
            for(int j=0;i<f->c32glyfs.size();j++){
                if(f->c32glyfs[j].start<=fstr.c and f->c32glyfs[j].start>=fstr.c ){
                    return  f->c32glyfs[j].startGlyphId+ f->c32glyfs[j].range[fstr.c -f->c32glyfs[j].start]; 
                }
            }
            return res;
        };

    
    template <typename charT>
    glyfft get(charT c,options opts){glyfft res;
        uint16 gid;
        if(cmapI>=0 and locaI>=0 and glyfI>=0){
            gid=  cmapGlyphId<charT>((&cmap()),c)
            if(_indexToLocFormat==0){
                res.fromtGlyfHead(glyf().loca(loca().f.s.offsets[gid]));
            };
        }  
        if(hmtxI>=0; and hheaI>=0){
            res.advanceWidth=hmtx().hMetrics[gid].advanceWidth;
            res.lisb=hmtx().hMetrics[gid].lsb;
        };
        if(opts.color and COLRI and CPALI){
            res.colors=COLR().get(gid);
        };
        return res;
    };
    
template <typename charT>
void loadGlyphs(uint16 size, charT* start, charT *end,options opts){

if(cmapI>=0 and locaI>=0 and glyfI>=0){
    
    for(int i=0;i<s;i++){uint32* r;size_t s;
        std::vector<glyfft> re; 
        cmapGlyphIds<charT>(&(table[cmapI]._cmap),start,end,&s,r);
        // Loca                
        if(_indexToLocFormat==0){ // Loca
            for(int j=0 ; j <s;j++ ){
                glyfHead* gh = glyf().loca(loca().f.s.offsets[r[j]]);
                glyfft ftr;ftr.fromGlyfHead(gh);ftr.glyphID = r[j];
                re.push_back(ftr);
                
            }
            else {
                for(int j=0;j<s;j++){
                    glyfHead* gh = glyf().loca(loca().f.s.offsets[r[j]]);
                    glyfft ftr;ftr.fromGlyfHead(gh);ftr.glyphID = r[j];
                    re.push_back(ftr);   
                }
            };            
        }
        
       if(hmtxI>=0 and hheaI>=0){
                re.back().advanceWidth=hmtx().hMetrics[r[j]].advanceWidth;
                re.back().lsb=hmtx().hMetrics[r[j]].lsb;}

        ftrange fr ;
        fr.range = re.data();
        fr.start = start[i];re.end=end[i];re.size=s;
        if constexpr(std::is_same<charT,char>::value){cglyphs.push_back(fr);} 
        if constexpr(std::is_same<charT,wchar_t>::value){wcglyphs.push_back(fr);}
        if constexpr(std::is_same<charT,char16_t>::value ){
            if constexpr(std::is_same<wchar_t,char16_t>::value){
                wcglyphs.push_back(fr);}
            else c16glyph.push_back(fr);
            }
        if constexpr(std::is_same<charT,char32_t>::value){wcglyphs.push_back(fr);}
    }
    
    if(opts.color and COLRI and CPALI){
        for(int i =0 ;i<s;i++){
            // TODO
        }  
    };
    
    
};
};
        
       
        void loadAll(options opts=NULL){
            uint16 numRanges;
            uint16* starts;uint16* ends;
            cmap().getRanges(&numRanges,starts,ends);
            loadGlyphs(numRanges,starts,ends,opts);
        };

    void setGLYF(glyf& g){

        Offset32* offsets = new Offset32[g.s];
        offsets[0]=0;
        for(int i=1;i<g.s;i++){
            offsets[i]=offsets[i-1]+sizeof(g[i]);
        };
        if(head().indexToLocFormat==0){
            Offset16* offs = new Offset16[g.s];
            for(int i=0;i<g.s;i++){offs[i]=offsets[i]/2;}
            loca().f.s=offs;}
            else { loca().f.l=offsets;};
    };
    void setCOLR(COLR& c){//TODO

    };

    template <typename Tb>
    void addTable(Tb table,int index){
        
    };

     };
    // font* ftcur;
    ACQRES(font){
        ftcur = &f;
        one(f.td);
        int headI=-1;
        int16 xMin,yMin,xMax,yMax;xMin=-8192;yMin=-8192;xMax=8192;yMax=8192;
        if(!f.table){f.table = new tableu[f.td.numTables];};
        for(int i  =0 ;i<f.td.numTables;i++){
            if(f.td.tableRecords[i].tableTag== Tag("glyf")){
               #define GLYF_TABLE f.table[f.td.tableRecords[i].index]._glyf
               if(GLYF_TABLE.xMin<xMin){xMin=GLYF_TABLE.xMin;}   
               if(GLYF_TABLE.yMin<yMin){yMin=GLYF_TABLE.yMin;}   
               if(GLYF_TABLE.xMax>xMax){xMax=GLYF_TABLE.xMax;}   
               if(GLYF_TABLE.yMax>xMax){xMax=GLYF_TABLE.yMax;}   
            }
            if(f.td.tableRecords[i].tableTag== Tag("head")){headI=f.td.tableRecords[i].index;};
            bool EBLCfound;
            switch(f.td.tableRecords[i].tableTag){
                #define TABLE_RECORD(tag,member) case font_tag(tag):{offone((f.table[i]._##member),f.td.tableRecords[i].offset);f.td.tableRecords[i].length=size(f.table[i]._##member);f.##memberI=i;};
                case font_tag("EBLC"):{offone(f.table[i]._EBLC),f.td.tableRecords[i].offset;f.td.tableRecords[i].length=size(f.table[i]._EBLC);f.EBLCI=i;
                    EBLCfound=true;
                };
                case font_tag("EBDT"):{offone(f.table[i]._EBDT),f.td.tableRecords[i].offset;f.td.tableRecords[i].length=size(f.table[i]._EBDT);f.EBLCI=i;}
                TAG_MEMBER(TABLE_RECORD)          
            }
            _length=f.td.tableRecords[i].length;
        }
        if(headI>=0){
        f.table[headI]._head.xMin=xMin;
        f.table[headI]._head.yMin=yMin;
        f.table[headI]._head.xMax=xMax;
        f.table[headI]._head.xMax=xMax;
        }
    }   
    USE_ACQRES(font)


void reduce(fontcollection& fc){
    size<TTChead>(fc);
};
fontcollection makeCollection(font* f,size_t num){// TODO make it correct
    fontcollection ret;ret.numFonts=num;
    ret.tableDirectories = TableDirectories[num];size_t numTables=0;
    for(int i=0;i<num;i++){ret.tableDirectories[i]=f[i].td;numTables+=f[i].td.numTables;};
    ret.tbs = new tableu[numTables];int k=0;
    for(int i=0;i<num;i++){ // make joinCollection
        for(int j=0;j<ret.tableDirectories[i].numTables;j++){
            ret.tbs[k]=f[i].table[j];k++;
        }
    };
    size<TTChead>(ret);
};
font getFont(fontcollection* fc,uint tdIndex){
    font f;size_t tableNum;f.td=fc->tableDirectories[tdIndex];
    f.table = new tableu[fc->tableDirectories[tdIndex].numTables];
    for(int i=0;i<fc->tableDirectories[tdIndex].numTables;i++){
        f.table[i]=fc->tbs[fc->tableDirectories[tdIndex].tableRecords[i]];
        f.td.tableRecords[i].index=i;
    };
    return f;
};

#include "fontansi.hpp"

typedef struct {
    uint16 em; // Size of space
    bool kern; // shrink spaces between faces
    bool color;
    uint16 lineSize;
}options;

template <typename charT>
 using facemap = std::map<charT,glyfvec> ; 

template <typename charT>
ftrange vectorize(font* f,std::basic_string<charT> ansistr,options opts){
    using strT=std::basic_string<charT>;
    int i;
    strT s;
    formatStr fstr= ansiStrip(s);
    ftrange<charT> res;
    if(f->cmapI>=0 and f->locaI>=0 and f->glyfI>=0){
        res=f->loadGlyphs(str,f,opts);
    }
    else {
        throw std::string("no cmap or loca or glyf");
    }
    res.range[0].pos = glm::uvec2(opts.em,0);
    if(f->hmtxI>=0 and f->hheaI>=0){
        for(int i=1;i<fstr.str.size();i++){
            res.range[i].pos=glm::uvec2(0,0);
            uint16 left=f->getGid(str[i-1]);
            uint16 right=f->getGid(str[i]);
        if(opts.kerning){
                int16 k = kern().getPair(left,right);
                res.line[i].pos.x =res.range[i-1].pos.x+ res.range[i-1].advanceWidth +res.range[i].lsb + k ;
        }
        else {
            for(int i=1;i<fstr.str.size();i++){
                // Make sure all characters are 1 em in width
                int16 dif = (opts.em-(res.range[i].xMax - res.range[i].xMin))/2;
                dif=dif>0?dif:-dif;
                res.range[i].pos.x =res.range[i-1].pos.x+ opts.em + dif;
            };
        }
        }
    }
    else {throw std::string("no hmtx or hheai tables");};

    res.em = opts.em;
    // colors
    
    return res;
};


typedef struct {
    uint16 x,y;
    uint8** data;
}ftbm;

ftbm rasterize(font* f,std::wstring ansistr,){

};


};
#endif