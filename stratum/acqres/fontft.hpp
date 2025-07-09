#ifndef STRATA_FONT_HPP
#define STRATA_FONT_HPP
#include <cstdint>
#include <stdexcept>
#include <string>
namespace ttf {

typedef uint8_t[3] uint24_t ;
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
    // typedef uint24_t Offset24 ;
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
   
#include <stratum/acqres/acqres.hpp>

#include <stratum/acqres/ft/avar.hpp> //[x]
#include <stratum/acqres/ft/base.hpp> //[x]
#include <stratum/acqres/ft/cbdt.hpp> //[]
#include <stratum/acqres/ft/cblc.hpp> //[]
#include <stratum/acqres/ft/cff.hpp> //[]
#include <stratum/acqres/ft/cff2.hpp> //[]
#include <stratum/acqres/ft/cmap.hpp> //[x]
#include <stratum/acqres/ft/colr.hpp> //[x]
#include <stratum/acqres/ft/cpal.hpp> //[x]
#include <stratum/acqres/ft/cvar.hpp> //[x]
#include <stratum/acqres/ft/cvt.hpp> //[x]
#include <stratum/acqres/ft/dsig.hpp> //[x]
#include <stratum/acqres/ft/ebdt.hpp> //[x]
#include <stratum/acqres/ft/eblc.hpp> //[x]
#include <stratum/acqres/ft/ebsc.hpp> //[x]
#include <stratum/acqres/ft/fpgm.hpp> //[x]
#include <stratum/acqres/ft/fvar.hpp> //[x]
#include <stratum/acqres/ft/gasp.hpp> //[x]
#include <stratum/acqres/ft/gdef.hpp> //[x]
#include <stratum/acqres/ft/glyf.hpp> //[x]
#include <stratum/acqres/ft/gpos.hpp> //[x]
#include <stratum/acqres/ft/gsub.hpp> //[x]
#include <stratum/acqres/ft/gvar.hpp> //[x]
#include <stratum/acqres/ft/hdmx.hpp> //[x]
#include <stratum/acqres/ft/head.hpp> //[x]
#include <stratum/acqres/ft/hhea.hpp> //[x]
#include <stratum/acqres/ft/hmtx.hpp> //[x]
#include <stratum/acqres/ft/hvar.hpp> //[x]
// #include <stratum/acqres/ft/ibmfc.hpp> //[]
#include <stratum/acqres/ft/jstf.hpp> //[x]
#include <stratum/acqres/ft/kern.hpp> //[x]
#include <stratum/acqres/ft/loca.hpp> //[x]
#include <stratum/acqres/ft/ltsh.hpp> //[x]
#include <stratum/acqres/ft/math.hpp> //[x]
#include <stratum/acqres/ft/maxp.hpp> //[x]
#include <stratum/acqres/ft/merg.hpp> //[x]
#include <stratum/acqres/ft/meta.hpp> //[x]
#include <stratum/acqres/ft/mvar.hpp> //[x]
#include <stratum/acqres/ft/name.hpp> //[x]
#include <stratum/acqres/ft/ompl.hpp> //[y]
#include <stratum/acqres/ft/os2.hpp> //[x]
#include <stratum/acqres/ft/pclt.hpp> //[x]
#include <stratum/acqres/ft/post.hpp> //[x]
#include <stratum/acqres/ft/prep.hpp> //[x]
#include <stratum/acqres/ft/sbix.hpp> //[x]
#include <stratum/acqres/ft/stat.hpp> //[x]
#include <stratum/acqres/ft/svg.hpp> //[x]
#include <stratum/acqres/ft/vdmx.hpp> //[x]
#include <stratum/acqres/ft/vhea.hpp> //[x]
#include <stratum/acqres/ft/vmtx.hpp> //[x]
#include <stratum/acqres/ft/vorg.hpp> //[x]
#include <stratum/acqres/ft/vvar.hpp> //[x]
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


uint16 _ftTBI;// Table Inex
/// @brief otff //[]
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


typedef struct {
    Tag   ttcTag;
uint16   majorVersion;
uint16   minorVersion;
uint32   numFonts;
Offset32*   tableDirectoryOffsets;//[numFonts]
    //
    TTCHeader2 f2;
    TableDirectory* tableDirectories;//[numFonts]

    tableu* tbs ;//[ td.numTables]

 
}TTChead;
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



struct colorFT  {
    enum flags {
        var=0x10,//second value in values[i] ;
        
        repeat=0x20,
        subGlyph=0x30
        center=0x40,//First value in values[i] unless var is set then
        solid_fill=0x1,
        linear_gradient=0x2,
        radial_gradient=0x4,
        sweep_gradient=0x7,
        affine=0x8,// Takes two values
        // Must be at end
        translate=0xA,
        rotate=0xB,
        scale=0xC,
        scale_uniform=0xD,
        skew=0xE,
        composite=0xF // If this flags is on the first value in value[i] is the sourceIndex and second is backdropIndex;
    };
    glm::uvec4 color;

    uint16 alpha;
    uint16 sizeColr;

    uint16 sizeSubGlyphs;
    uint16* subGlyphIDS;
    uint32* flags;
    glm::uvec4* values;
    
};
enum PTflags {
    onCurve=0x1,
    delta=0x2,
    signX=0x4,
    signY=0x8,
    overlap=0x10
};
typedef struct{
    uint16 glyphID;
    coord pos;
    int16   numberOfContours;
    int16   xMin;
    int16   yMin;
    int16   xMax;
    int16   yMax;
    colorFT colors;
    uint8* endPts ;// [numberOfContours]
    uint16 advanceWidth ;
    int16 lsb;
    uint16 sizeContour;
    glm::uvec2* contours;/// [sizeContour]
    PTflags* flags;//[sizeContour] 
    righSideBearing(font* f){return advanceWidth - (lsb + f->head().xMax - f->head().xMin);}
}glyfft;
struct glyffftprim {
    coord pos;
    int16 nStrips;
    int16 nFans;
    
    colorFT* colors;//[nstrips]


    void glyfft();
};  

template <typename charT>
struct ftrange {
    glyfft* range;
    charT* start,end;
    uint16 size;
    
    uint16 startGlyphID;
};


     struct font {
        TableDirectory td ;
        tableu* table;

        std::vector<ftrange<char>> cglyfs ;
        std::vector<ftrange<wchar_t>> wcglyf;
        
        template <typename charT>
        uint16 getGid(charT c){
            uint16 res=0;
            for(int j=0;i<f->cglyfs.size();j++){
                if(f->cglyfs[j].start<=fstr.c and f->cglyfs[j].start>=fstr.c ){
                    left = f->cglyfs[j].range[fstr.c -f->cglyfs[j].start]; 
                }
            }
            if(!left){
            for(int j=0;i<f->wcglyfs.size();j++){
                if(f->wcglyfs[j].start<=fstr.c and f->wcglyfs[j].start>=fstr.c ){
                    left = f->wcglyfs[j].range[fstr.c -f->wcglyfs[j].start]; 
                }
            };
            }
            return res;
        };

        int avarI, BASEI, CBDTI, CBLCI, CFFI, CFF2I, cmapI, COLRI, CPALI, cvarI, cvtI, DSIGI, EBDTI, EBLCI, EBSCI, fpgmI, fvarI, gaspI, GDEFI, glyfI, GPOSI, GSUBI, gvarI, hdmxI, headI, hheaI, hmtxI, HVARI, JSTFI, kernI, locaI, LTSHI, MATHI, maxpI, MERGI, metaI, MVARI, nameI, os2I, PCLTI, postI, prepI, sbixI, STATI, SVGI, VDMXI, vheaI, vmtxI, VORGI, VVAR;
        avarI=-1;BASEI=-1;CBDTI=-1;CBLCI=-1;CFFI=-1;CFF2I=-1;cmapI=-1;COLRI=-1;CPALI=-1;cvarI=-1;cvtI=-1;DSIGI=-1;EBDTI=-1;EBLCI=-1;EBSCI=-1;fpgmI=-1;fvarI=-1;gaspI=-1;GDEFI=-1;glyfI=-1;GPOSI=-1;GSUBI=-1;gvarI=-1;hdmxI=-1;headI=-1;hheaI=-1;hmtxI=-1;HVARI=-1;JSTFI=-1;kernI=-1;locaI=-1;LTSHI=-1;MATHI=-1;maxpI=-1;MERGI=-1;metaI=-1;MVARI=-1;nameI=-1;os2I=-1;PCLTI=-1;postI=-1;prepI=-1;sbixI=-1;STATI=-1;SVGI=-1;VDMXI=-1;vheaI=-1;vmtxI=-1;VORGI=-1;VVARI=-1;cmap& cmap(){return table[cmapI]._cmap; }
    
    avar& avar(){return table[avarI]._avar;};
    BASE& BASE(){return table[BASEI]._BASE;};
    CBDT& CBDT(){return table[CBDTI]._CBDT;};
    CBLC& CBLC(){return table[CBLCI]._CBLC;};
    CFF& CFF(){return table[CFFI]._CFF;};
    CFF2& CFF2(){return table[CFF2I]._CFF2;};
    cmap& cmap(){return table[cmapI]._cmap;};
    COLR& COLR(){return table[COLRI]._COLR;};
    CPAL& CPAL(){return table[CPALI]._CPAL;};
    cvar& cvar(){return table[cvarI]._cvar;};
    cvt&  cvt() {return table[cvtI]._cvt;};
    DSIG& DSIG(){return table[DSIGI]._DSIG;};
    EBDT& EBDT(){return table[EBDTI]._EBDT;};
    EBLC& EBLC(){return table[EBLCI]._EBLC;};
    EBSC& EBSC(){return table[EBSCI]._EBSC;};
    fpgm& fpgm(){return table[fpgmI]._fpgm;};
    fvar& fvar(){return table[fvarI]._fvar;};
    gasp& gasp(){return table[gaspI]._gasp;};
    GDEF& GDEF(){return table[GDEFI]._GDEF;};
    glyf& glyf(){return table[glyfI]._glyf;};
    GPOS& GPOS(){return table[GPOSI]._GPOS;};
    GSUB& GSUB(){return table[GSUBI]._GSUB;};
    gvar& gvar(){return table[gvarI]._gvar;};
    hdmx& hdmx(){return table[hdmxI]._hdmx;};
    head& head(){return table[headI]._head;};
    hhea& hhea(){return table[hheaI]._hhea;};
    hmtx& hmtx(){return table[hmtxI]._hmtx;};
    HVAR& HVAR(){return table[HVARI]._HVAR;};
    JSTF& JSTF(){return table[JSTFI]._JSTF;};
    kern& kern(){return table[kernI]._kern;};
    loca& loca(){return table[locaI]._loca;};
    LTSH& LTSH(){return table[LTSHI]._LTSH;};
    MATH& MATH(){return table[MATHI]._MATH;};
    maxp& maxp(){return table[maxpI]._maxp;};
    MERG& MERG(){return table[MERGI]._MERG;};
    meta& meta(){return table[metaI]._meta;};
    MVAR& MVAR(){return table[MVARI]._MVAR;};
    name& name(){return table[nameI]._name;};
    os2& os2(){return table[os2I]._os2;};
    PCLT& PCLT(){return table[PCLTI]._PCLT;};
    post& post(){return table[postI]._post;};
    prep& prep(){return table[prepI]._prep;};
    sbix& sbix(){return table[sbixI]._sbix;};
    STAT& STAT(){return table[STATI]._STAT;};
    SVG& SVG(){return table[SVGI]._SVG;};
    VDMX& VDMX(){return table[VDMXI]._VDMX;};
    vhea& vhea(){return table[vheaI]._vhea;};
    vmtx& vmtx(){return table[vmtxI]._vmtx;};
    VORG& VORG(){return table[VORGI]._VORG;};
    VVAR& VVAR(){return table[VVARI]._VVAR;};
    
    glyfft fromGlyfHead(glyfHead& gh){
    glyfft res;
    res.numberOfContours = gh.numberOfContours;
    res.xMin = gh.xMin;
    res.yMin = gh.yMin;
    res.xMax = gh.xMax;
    res.yMax = gh.yMax;
    res.sizeContour= gh.f.sg.xCoordNum>gh.f.sg.yCoordNum?gh.f.sg.xCoordNum:gh.f.sg.yCoordNum;
    if(gh.numberOfContours>=0){
        res.endPts=uint8[res.numberOfContours];
        for(int i=0;i<gh.f.sg.flagNum;i++){
            if(gh.f.sg.flag[i] &( X_SHORT_VECTOR | X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR ) ){res.sizeContour++;continue;}
            if(gh.f.sg.flag[i] &( Y_SHORT_VECTOR | Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR ) ){res.sizeContour++;};
        };
        res.contours = new coord[res.sizeContour]; int x,y;x=0;y=0;
        for(int i=1;i<res.sizeContour;i++){
            res.endPts[i] = gh.f.sg.endPtsOfContours[0]; int fn=0;
            for(int j =0;j<res.xCoordNum;j++){
                if(gh.f.sg.flag[fn] & ( X_SHORT_VECTOR | X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR )){
                --j;}
                res.contours[j].x =gh.f.sg.xCoordinates[j];
                ++fn;
            }
            fn=0;
            for(int j =0;j<res.yCoordNum;j++){
                if(gh.f.sg.flag[fn] & ( Y_SHORT_VECTOR | Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR )){
                --j;}
                res.contours[j].y =gh.f.sg.yCoordinates[j];
                ++fn;
            }
            res.flags = new PTflags[res.sizeContour;]  ;
            for(int j=0;j<res.sizeContour;j++){
                res.flags[j] =0;
                res.flags[j]|=(gh.f.sg.flag[j] & ON_CURVE)?onCurve:0;
                
                
            };
        };
    }
    else {
        
    }
}
template <typename charT>
void loadGlyphs(uint16 size, charT* start, charT *end,options opts){

if(cmapI>=0 and locaI>=0 and glyfI>=0){
    
    for(int i=0;i<s;i++){uint32* r;size_t s;
        std::vector<glyfft> re; 
        cmapGlyphIds<charT>(&(table[cmapI]._cmap),start,end,&s,r);
        // Loca                
        if(_indexToLocFormat==0){ // Loca
            for(int j=0 ; j <s;j++ ){
                glyfHead gh = glyf().loca(loca().f.s.offsets[r[j]]);
                re.push_back(fromGlyfHead(gh));re.back().glyphID = r[j];
                re.back().advanceWidth=hmtx().hMetrics[r[j]].advanceWidth;
                re.back().lsb=hmtx().hMetrics[r[j]].lsb;
            }
            else {
                for(int j=0;j<s;j++){
                    glyfHead gh = glyf().loca(loca().f.s.offsets[r[j]]);
                    re.push_back(fromGlyfHead(gh),r[j]);re.back().glyphID = r[j];   
                }
            };            
        }
        ftrange fr ;
        fr.range = re.data();
        fr.start = start[i];re.end=end[i];re.size=s;
        if constexpr( std::is_same<charT,char>::value){cglyphs.push_back(fr);} 
        if( constexpr (std::is_same<charT,whcar_t>::value)){wcglyphs.push_back(fr);}
    }
    res.size=s;
    if(opts.color and COLRI and CPALI){
        for(int i =0 ;i<s;i++){
            // TODO
        }  
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
    font* ftcur;
    ACQRES(font){
        ftcur = &f;
        one(f.td);
        int headI=-1;
        int16 xMin,yMin,xMax,yMax;xMin=-8192;yMin=-8192;xMax=8192;yMax=8192;
        if(!f.table){f.table = new tableu[f.td.numTables];};
        for(_ftTBI  =0 ; i <f.td.numTables){
            if(f.td.tableRecords[i].tableTag== Tag("glyf")){
               #define GLYF_TABLE f.table[f.td.tableRecords[i].index]._glyf
               if(GLYF_TABLE.xMin<xMin){xMin=GLYF_TABLE.xMin;}   
               if(GLYF_TABLE.yMin<yMin){yMin=GLYF_TABLE.yMin;}   
               if(GLYF_TABLE.xMax>xMax){xMax=GLYF_TABLE.xMax;}   
               if(GLYF_TABLE.yMax>xMax){xMax=GLYF_TABLE.yMax;}   
            }
            if(f.td.tableRecords[i].tableTag== Tag("head")){headI=f.td.tableRecords[i].index;};
            switch(f.td.tableRecords[i].tableTag){
                #define TABLE_RECORD(tag,member) case font_tag(tag):{offone((f.table[i]._##member),f.td.tableRecords[i].offset);f.td.tableRecords[i].length=size(f.table[i]._##member);f.##memberI=i;};
            TAG_MEMBER(TABLE_RECORD)          
            }
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
#include <algorithm>

typedef struct {
    uint16 em; // Size of space
    bool kern; // shrink spaces between faces
    bool color;
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
    res.range[0].coord = glm::uvec2(0,0);
    if(f->hmtxI and f->hheaI){
        for(int i=1;i<fstr.str.size();i++){
            uint16 left=f->getGid(str[i-1]);
            uint16 right=f->getGid(str[i]);
        if(opts.kerning){
                int16 k = kern().getPair(left,right);
                res.line[i].pos =res.range[i-1].pos+ f->hmtx().hMetrics[left].advanceWidth +f->hmtx().hMetrics[right].lsb + k ;
        }
        else {
            for(int i=1;i<fstr.str.size();i++){
                // Make sure all characters are 1 em in width
                res.range[i].pos =res.range[i-1].coord+em ;
            };
        }
        }
    };

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