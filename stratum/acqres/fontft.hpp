#ifndef STRATA_FONT_HPP
#define STRATA_FONT_HPP
#include <cstdint>
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
#include <petri/defs>

namespace ttf {

typedef uint32_t IndexP;


typedef uintT<3> uint24_t ;

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
    uint8 compositeMode;
    glm::uvec4 color;
    float alpha;
    uint16 numbaseGlyphs;
    uint16* baseGlyphs;
    std::vector<colrff<varValueBase,1>> layers;
    std::vector<colrf<varValueBase>> values;



    template <typename charT,typename COLRFty>
    mod::fontColor<charT> get(){
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




         auto lamcase = [&]<size_t s>(size_t i){ 
             ptype<n>::ty h= pri::get<n-1>(values[indV].f).getPaint();
             std::vector<ptype<n>::ty& ref =pri::get<std::vector<ptype<n>::ty>>(r.tupvec) 
             ref.push_back(h) ;  r.layers.back().push_back(mod::fontColor::layerE(fontColorTupPos<n>(),ref.size()-1));
             inds.push_back(std::pair<size_t,size_t>(fontColrTupPos<n>(),pri::get<fontColrTupPos<n>()>(r.tupvec).size()-1)) ;
             curTup =fontColrTupPos<n>();
            
            return ;}
                
            auto swlam = [&](){
                if(pri::Tcase<lamcase CFXMACRO(COMMACRO)>(values[indV].format)){return;};
                switch(values[indV].format){

                    case 10 :{
                        colrff<varValueBase,10>& h = pri::get<10>(values[indV].f);
                        mod::fontColor::ColGlyph g(h.glyphID);
                        // r.Colglyph.push_back(g) ;
                    pri::get<std::vector<mod::fontColor::ColGlyph>>(r.tupvec).push_back(g); 
                        colGlyphs.push_back(h.paintOffset);inds.push_back(std::pair<size_t,size_t>(1,pri::get<1>(r.tupvec).size()-1)),continue;}
                    case 11 :{
colrff<varValueBase,11>& h = pri::get<11>(values[indV].f);
                    mod::fontColor::SubGlyph g(h.glyphID);
                    // r.subGlyph.push_back(g) ;
                    pri::get<std::vector<mod::fontColor::SubGlyph>>(r.tupvec).push_back(g); inds.push_back(std::pair<size_t,size_t>(0,pri::get<0>(r.tupvec).size()-1));
                    continue;}
                    case 32 :{
                        colrff<varValueBase,32>& h = pri::get<11>(values[indV].f);
                        composePaints.push_back(std::pair<size_t,size_t>(h.sourcePaintOffset,h.backfropPaintOffset)) ;
                        pri::get<std::vector<ptype<32>::ty>>(r.tupvec).push_back(mod::fontColor::compose(h.compositeMode)); inds.push_back(std::pair<size_t,size_t>(2,pri::get<2>(r.tupvec).size()-1)); 
                        // r.composePts.push_back(h); 
                        continue;}
                }
            }
            auto incr = [&](){
                if(indV == colGlyphs[curColGlyph]){
                    pri::get<std::vector<mod::fontColor<ColGlyph>>(r.tupVec)[curColGlyph].lyr=mod::fontColor::layerE(curTup, pri::get(curTup,r.tupvec).size()-1);
                };
            }
         for(size_t s =0;s<layers.size();s++){
            colrff<varValueBase,1>& lyr = layers[s];

            if(lyr.firstLayerIndex>layers.size()){
                size_t p = lyr.firstLayerIndex-layers.size();s++;
                r.layers.push_back(mod::fontColor::indexE(-p,lyr.layers.size()));      
            
            }
            else { r.layers.push_back(mod::fontColor::layerE(lyr.firstLayerIndex,lyr.layers.size()));}

         }
         for(indV=0;s<values.size();indV++){swlam()};

         for( std::pair<size_t,size_t>& i :inds){
            r.index.push_back(i.first,i.second)
         };
        

        for(size_t it =0;it<inds.size();it++){
            std::pair<size_t,size_t>& iter =  inds[it];
            if(it==colGlyphs[curColGlyph]){
                pri::get<1>(r.tupvec)[curColGlyph].lyr=mod::fontColor::layerE(iter.first,iter.second);curColGlyph++;
            };
        };
        for(size_t it=0;it<composePaints.size();it++){
            size_t src = composePaints[it].first;
            size_t dst = composePaints[it].second;
            pri::get<2>(r.tupvec)[it].src=mod::fontColor::layerE(inds[src].first,inds[src].second);
            pri::get<2>(r.tupvec)[it].b=mod::fontColor::layerE(inds[dst].first,inds[dst].second);
        };
        size_t s=0;
        for(mod::fontColor::layerE& it : r.layers){
            if(it.posTup>=0){
                it.posTup = inds[it.posTup];
                }
            
            s++;

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

    float slope(glm::vec2 left,glm::vec2 center,glm::vec2 right){
    glm::vec2 x = center - left +(right - center);
    return x.y/x.x; 
}
glm::vec2 ovec(float t){
    return glm::vec2(1,t);
};
glm::vec2 ovec(mat2x2 i){
    glm::vec2 r = i.y - i.x;
    return r; 
};

float der(vec2 o){return o.y/o.x }


bool intersect(glm::imat2x2 line , imat2x2 seg){
    glm::vec2 ol = ovec(line) ;
    glm::mat2x2 os = glm::mat2x2(seg.x - line.x,seg.y -line.x)  ;

    float dx = der(os.x);
    float dy = der(os.y);

    float dl = der(ol);

    return dx<dl ? dl<dy : ((dy<dl) ? true : false);
};
bool isInside(glm::vec2 pt,uint indFirst,uint indLast){
    
    uint count=0;
        glm::vec2 cur = curved.pts[indLast];
        glm::vec2 next = curved.pts[indFirst];
        glm::vec2 midPt = (cur + next)/2;

        glm::mat2x2 firstPtSeg = glm::mat2x2(midPt,pt) ;        
    count = 1;
    for(uint i=indFirst;i<indLast;i++){
        cur= contours.pts[i];
        next= contours.pts[i+1];
        glm::mat2x2 seg(cur,next) ;
        if(intersect(firstPtSeg,seg)){count++;};
    }
    
    return count%2? true :  false;
};

    void swap(size_t end1,size_t end2){
        size_t start1=end1!=0?endPts[end1-1]+1:0 ;
        size_t start2 = endPts[end2-1] + 1;
        size_t s1=endPts[end1]-start1+1;
        size_t s2=(endPts[end2]-start2+1);

        size_t dif = end2-end1;
            glm::ivec2* temp1 = new glm::ivec2[s1];
            pri::memcpy(temp , contours+start1,s1);
            glm::ivec2* temp2 = new glm::ivec2[s2];
            pri::memcpy(temp2 , contours+start2,s2);
            
            size_t st ;size_t en ;size_t s ;
            glm::ivec2* between ;

        if(dif>1){
            size_t st = endPts[end1]+1;size_t en=start2-1;size_t s=en-st+1;
            glm::ivec2* between = new glm::ivec2[s];
        }
            pri::memcpy(between,contours+st,s);
            
            size_t t = endPts[end2] - start2 ;
            endPts[end1] = start1 + s2 - 1;
            start2 = endPts[end1]+1; 
            endPts[end2] = start2 + s1 - 1;

            pri::memcpy(contours+start1,temp2,s2);
            pri::memcpy(contours+start2,temp1,s1);
            if(dif>1){
                pri::memcpy(contours+endPts[end1]+1,between ,s)
            }
    };
    void order(){
        bool badtree = false;

        size_t start=0;
        for(size_t i=0;i<numberOfContours;i++){
            size_t curE = endPts[i];
            size_t startn=curE + 1;
            std::vector<uint16> startsizes{curE-start+1};
            for(size_t j=i+1;j<numberOfContours;j++){
                size_t curEn = endPts[j];
                startsizes.push_back(curEn-startn+1);
                if(isInside(contours[curE],startn,curEn)){
                    size_t curEn2 = endPts[j+1];
                    size_t startn2 = curEn+1;
                    size_t k ;
                    std::vector<uint16> endsizes;
                    for( k=j+1;isInside(contours[curE],startn2,curEn2);k++;){
                        curEn2 = endPts[k+1];
                        endsizes.push_back(curEn2 - startn2+1);
                        startn2 = curEn2+1;
                    };
                    curEn2 = endPts[k-1];
                    startn2 = endPts[k-2] + 1;

                    size_t s = curEn2 - startn2 + 1;
                    glm::ivec2 temp = new glm::ivec2[s];
                    pri::memcpy(temp,contours+startn2,s);
                    size_t sc=curE-startn + 1;glm::ivec2 tcur = new glm::ivec2[sc];
                    pri::memcpy(tcur,contours+startn,sc);
                    
                    pri::memcpy(contours+startn,temp,s);
                    pri::memcpy(contours+startn+s,tcur,sc) ;
                    // UpdateEndPts
                    size_t s;
                    for(s=0;s<endsizes.size();s++){endPts[i+s]=endPts[i+s-1]+endsizes[s];}
                    size_t m =s;
                    for(;s<startsizes.size();s++){endPts[i+s]=endPts[i+s-1]+endsizes[s-m];}
                    badtree =true;
                    break;
                }

                startn = curEn + 1;
            };

            start = curE + 1;
        };
        return badtree;
    };
    void sort(){
        for(size_t i=0;i<numberOfContours and !order();i++){}
    };
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
    sort();
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

template <typename charT , typename ty>
struct ftrangeT {
    ty* range;
    charT start,end;
    uint16 size;
    
    uint16 startGlyphID;

    ty* get(charT c){
        if(c>=start and c<=end){return &(glyfft[c-start]);}
        return &(range[0]);
    };
};

template <typename charT>
using ftrange = ftrangeT<charT,glyfft>;

template <typename charT>
using bmrange = ftrangeT<charT,glyfbm>;

#define TAG_MEMBER(x)\
x("avar",avar)\
x("BASE",BASE)\
x("CBDT",CBDT)\
x("CBLC",CBLC)\
x("CFF ",CFF)\
x("CFF2",CFF2)\
x("cmap",cmap)\
x("COLR",COLR)\
x("CPAL",CPAL)\
x("cvar",cvar)\
x("cvt ",cvt)\
x("DSIG",DSIG)\
x("EBDT",EBDT)\
x("EBLC",EBLC)\
x("EBSC",EBSC)\
x("fpgm",fpgm)\
x("fvar",fvar)\
x("gasp",gasp)\
x("GDEF",GDEF)\
x("glyf",glyf)\
x("GPOS",GPOS)\
x("GSUB",GSUB)\
x("gvar",gvar)\
x("hdmx",hdmx)\
x("head",head)\
x("hhea",hhea)\
x("hmtx",hmtx)\
x("HVAR",HVAR)\
x("JSTF",JSTF)\
x("kern",kern)\
x("loca",loca)\
x("LTSH",LTSH)\
x("MATH",MATH)\
x("maxp",maxp)\
x("MERG",MERG)\
x("meta",meta)\
x("MVAR",MVAR)\
x("name",name)\
x("OS/2",os2)\
x("PCLT",PCLT)\
x("post",post)\
x("prep",prep)\
x("sbix",sbix)\
x("STAT",STAT)\
x("SVG ",SVG)\
x("VDMX",VDMX)\
x("vhea",vhea)\
x("vmtx",vmtx)\
x("VORG",VORG)\
x("VVAR",VVAR)\

        #define XTABLES(x) x(avar) x( BASE) x( CBDT) x( CBLC) x( CFF) x( CFF2) x( cmap) x( COLR) x( CPAL) x( cvar) x( cvt) x( DS) x(G) x( EBDT) x( EBLC) x( EBSC) x( fpgm) x( fvar) x( gasp) x( GDEF) x( glyf) x( GPOS) x( GSUB) x( gvar) x( hdmx) x( head) x( hhea) x( hmtx) x( HVAR) x( JSTF) x( kern) x( loca) x( LTSH) x( MATH) x( maxp) x( MERG) x( meta) x( MVAR) x( name) x( os2) x( PCLT) x( post) x( prep) x( sbix) x( STAT) x( SVG) x( VDMX) x( vhea) x( vmtx) x( VORG) x( VVAR)

    #define comma(n) ,n
    typedef char reservedType;

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

typedef pri::variant<reservedType,XTABLES(n) > tableu;

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
    for(int j =0;j<f.tableDirectories[i].numTables;j++){
        switch(f.tableDirectories[i].tableRecords[j].tableTag){
            #define TABLE_RECORD_COL(tag,member) case font_tag(tag):{offone(pri::get<member>(f.tbs[_ftTBI]),f.tableDirectories[i].tableRecords[j].offset);\
                f.tableDirectories[i].tableRecords[j].length=pri::get<member>(f.tbs[_ftTBI])  ;continue;\
            };
            TAG_MEMBER(TABLE_RECORD_COL)
        }
        _ftTBI++;
    }
}
}
USE_ACQRES(TTChead)
typedef TTChead fontcollection ;


TableDirectory td ;
        tableu* table;


#define PTR_MEMB_TABLE(name)  indexTable<name> _name; \

XTABLES(PTR_MEMB_TABLE)        

     template <typename tableTy>
        struct tableTyPtr {
            constexpr tableTy tablue::* ptr =void
        }
        
                template <typename tableTy>
                struct indexTable {
                    int i = -1;
                    operator bool(){return i!=(-1);}
                    tableTy& operator(){return pri::get<tableTy>(table[ind]);}
                };

        constexpr bool wcb = std::is_same<wchar_t,char16_t>::value ; 

        using bcVec = std::vector<bmrange<char>> ;
        using bwcVec = std::vector<bmrange<wchar_t>> ;
        using bc16Vec = std::enable_if< wcb, std::vector<bmrange<char16_t>>>::type  ; 
        using bc32Vec = std::vector<bmrange<char32_t>> ; 

bcVec bcglyfs; 
bwcVec bwcglyf; 
bc16Vec bc16glyf; 
bc32Vec  bc32glyf; 

bool bloaded;
template <typename charT>
struct bvectype {
    using type = void;
    constexpr type font::* ptr  ;
};
template <>
struct bvectype<char> {
    using type = bcVec;
    constexpr type font::* ptr= font::bcglyfs  ;
};
template <>
struct bvectype<wchar_t> {
    using type = bwcVec;
    constexpr type font::* ptr= font::bwcglyfs  ;
};
template <>
struct bvectype<char16_t> {
    using type = bc16Vec;
    constexpr type font::* ptr= font::bc16glyfs  ;
};
template <>
struct bvectype<char32_t> {
    using type = bc32Vec;
    constexpr type font::* ptr= font::bc32glyfs  ;
};

        using cVec = std::vector<ftrange<char>> ;
        using wcVec = std::vector<ftrange<wchar_t>> ;
        using c16Vec = std::enable_if< wcb, std::vector<ftrange<char16_t>>>::type  ; 
        using c32Vec = std::vector<std::vector<char32_t>> ; 

        template <typename charT>
        struct vectype {
            using type = void
            constexpr  type font::* ptr ; 
        }; 

        bool floaded;
        cVec cglyfs ;
        wcVec wcglyf;
        c16Vec c16glyf;
        c32Vec c32glyf;

        template <> struct vectype <char> {
             using type = cVec;
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
        uint16 getGid(charT c){
            vectype<charT>::type& v =this->*(vectype<charT>::ptr); 
            uint16 res=0;
            for(int j=0;i<v.size();j++){
                if(v[j].start<=c and  v[j].end<=c ){
                    return v[j].startGlyphId  + c- v[j].start; 
                }
            }
            return res;
        };
       
    
    template <typename charT>
    glyfft get(charT c,mod::fontPrim::options opts){glyfft res;
        uint16 gid;
        if(_cmap and _loca and _glyf){
            gid=  cmapGlyphId<charT>((&cmap()),c);
            if(_indexToLocFormat==0){
                res.fromtGlyfHead(glyf().loca(loca().f.s.offsets[gid]));
            };
        }  
        if(_hmtx>=0; and _hhea>=0){
            res.advanceWidth=hmtx().hMetrics[gid].advanceWidth;
            res.lisb=hmtx().hMetrics[gid].lsb;
        };
        if(opts.color and _COLR and _CPAL){
            res.colors=COLR().get(gid);
        };
        return res;
    };
    
template <typename charT>
void loadGlyphs(uint16 size, charT* start, charT *end,mod::fontPrim::options opts){

if(_cmap  and _loca and _glyf){
    
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
        }
        
       if(_hmtx_ and _hhea_){
                re.back().advanceWidth=hmtx().hMetrics[r[j]].advanceWidth;
                re.back().lsb=hmtx().hMetrics[r[j]].lsb;}

        ftrange fr ;
        fr.range = re.data();
        fr.start = start[i];re.end=end[i];re.size=s;

        vectype::type& v = this->*(vectpe<charT>::ptr) ;
        v.push_back(fr)
    }
    
    if(opts.color and _COLR and _CPAL){
        for(int i =0 ;i<s;i++){

        }  
    };
    
    
};
};
        
       
        void loadAll(mod::fontPrim::options opts=NULL){
            
            uint16 numRanges;
            uint16* starts, ends;
            cmap().getRanges(&numRanges,starts,ends);
            loadGlyphs(numRanges,starts,ends,opts);
            floaded = true;
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
    
    void setCOLR(mod::ftPrimFull& c){//TODO

    };
    void setLoca(mod::ftPrimFull& c);
    void setCmap(mod::ftPrimFull& c);
    void setGlyf(mod::ftPrimFull& c);

    void set(mod::ftPrimFull& c){

    }

    template <typename Tb>
    void addTable(Tb table,int index){
        
    };



}
    // font* ftcur;
    ACQRES(font){
        ftcur = &f;
        one(f.td);
        int _head_.i=-1;
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
                #define TABLE_RECORD(tag,member) case font_tag(tag):{offone((pri::get<member>(f.table[i])),f.td.tableRecords[i].offset);f.td.tableRecords[i].length=size(pri::get<member>(f.table[i]));f._##member.i=i;};
                case font_tag("EBLC"):{offone(pri::get<EBLC>(f.table[i])),f.td.tableRecords[i].offset;f.td.tableRecords[i].length=size(pri::get<EBLC>(f.table[i]));f._EBLC.i=i;
                    EBLCfound=true;
                };
                case font_tag("EBDT"):{offone(pri::get<EBDT>(f.table[i])),f.td.tableRecords[i].offset;f.td.tableRecords[i].length=size(pri::get<EBDT>(f.table[i]));f._EBDT.i=i;}
                TAG_MEMBER(TABLE_RECORD)          
            }
            _length=f.td.tableRecords[i].length;
        }
        if(_head>=0){
        _head().xMin=xMin;
        _head().yMin=yMin;
        _head().xMax=xMax;
        _head().xMax=xMax;
        }
    }   
    USE_ACQRES(font)


void reduce(font::fontcollection& fc){
    size<TTChead>(fc);
};
font::fontcollection makeCollection(font* f,size_t num){// TODO make it correct
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
font getFont(font::fontcollection* fc,uint tdIndex){
    font f;size_t tableNum;f.td=fc->tableDirectories[tdIndex];
    f.table = new tableu[fc->tableDirectories[tdIndex].numTables];
    for(int i=0;i<fc->tableDirectories[tdIndex].numTables;i++){
        f.table[i]=fc->tbs[fc->tableDirectories[tdIndex].tableRecords[i]];
        f.td.tableRecords[i].index=i;
    };
    return f;
};



};
#endif