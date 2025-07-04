#ifndef STRATA_FONT_HPP
#define STRATA_FONT_HPP
#include <cstdint>
#include <stdexcept>
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
#include <stratum/acqres/ft/cblc.hpp> //[x]
#include <stratum/acqres/ft/cff.hpp> //[x]
#include <stratum/acqres/ft/cff2.hpp> //[x]
#include <stratum/acqres/ft/cmap.hpp> //[x]
#include <stratum/acqres/ft/colr.hpp> //[x]
#include <stratum/acqres/ft/cpal.hpp> //[x]
#include <stratum/acqres/ft/cvar.hpp> //[x]
#include <stratum/acqres/ft/cvt.hpp> //[x]
#include <stratum/acqres/ft/dsig.hpp> //[x]
#include <stratum/acqres/ft/ebdt.hpp> //[]
#include <stratum/acqres/ft/eblc.hpp> //[]
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
        // fpgm _fpgm;
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
macro("avar",_avar)\
macro("BASE",_BASE)\
macro("CBDT",_CBDT)\
macro("CBLC",_CBLC)\
macro("CFF ",_CFF)\
macro("CFF2",_CFF2)\
macro("cmap",_cmap)\
macro("COLR",_COLR)\
macro("CPAL",_CPAL)\
macro("cvar",_cvar)\
macro("cvt ",_cvt)\
macro("DSIG",_DSIG)\
macro("EBDT",_EBDT)\
macro("EBLC",_EBLC)\
macro("EBSC",_EBSC)\
macro("fvar",_fvar)\
macro("gasp",_gasp)\
macro("GDEF",_GDEF)\
macro("glyf",_glyf)\
macro("GPOS",_GPOS)\
macro("GSUB",_GSUB)\
macro("gvar",_gvar)\
macro("hdmx",_hdmx)\
macro("head",_head)\
macro("hhea",_hhea)\
macro("hmtx",_hmtx)\
macro("HVAR",_HVAR)\
macro("JSTF",_JSTF)\
macro("kern",_kern)\
macro("loca",_loca)\
macro("LTSH",_LTSH)\
macro("MATH",_MATH)\
macro("maxp",_maxp)\
macro("MERG",_MERG)\
macro("meta",_meta)\
macro("MVAR",_MVAR)\
macro("name",_name)\
macro("OS/2",_os2)\
macro("PCLT",_PCLT)\
macro("post",_post)\
macro("prep",_prep)\
macro("sbix",_sbix)\
macro("STAT",_STAT)\
macro("SVG ",_SVG)\
macro("VDMX",_VDMX)\
macro("vhea",_vhea)\
macro("vmtx",_vmtx)\
macro("VORG",_VORG)\
macro("VVAR",_VVAR)\

/// @brief otff //[]
uint32 _length ;
typedef struct {
Tag   tableTag;
uint32   checksum;
Offset32   offset;
uint32   length;
}TableRecord;
ACQRES(TableRecord){
    one(f);
    _length = f.length;
};
USE_ACQRES(TableRecord);
   typedef struct {
uint32   sfntVersion;
uint16   numTables;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
TableRecord*   tableRecords;//[numTables]
}TableDirectory:;
ACQRES(TableDirectory){
one((f.sfntVersion));
one((f.numTables));
one((f.searchRange));
one((f.entrySelector));
one((f.rangeShift));
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
one((f.numFonts));
arr(f.tableDirectoryOffsets, f.numFonts);
 one((f.dsigTag));
one((f.dsigLength));
one((f.dsigOffset));
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

    tableu* tbs ;

 
}TTChead;
ACQRES(TTChead){
one(f.ttcTag);
one(f.majorVersion);
one(f.minorVersion);
one(f.numFonts)
switch(f.majorVersion){
    case 2 : {one(f.f2);}
};
if(!f.tableDirectories){f.tableDirectories = new TableDirectory[f.numFonts];};
for(int i=0;i<f.numFonts;i++){offone(f.tableDirectories[i],f.tableDirectoryOffsets[i]);};
size_t s=0;
for(int i=0;i<f.numFonts;i++){s+=f.tableDirectories.numTables;};
if(!f.tbs){f.tbs=new tableu[s];};
int tbi=0;
for(int i=0;i<f.numFonts;i++){
    for(int j =0;j<f.tableDirectories[i].numTables){
        switch(f.tableDirectories[i].tableRecords[j].tableTag){
            #define TABLE_RECORD_COL(tag,member) case font_tag(tag):{offone((f.tbs[tbi].##member),f.tableDirectories[i].tableRecords[j].offset);};
            TAG_MEMBER(TABLE_RECORD_COL)
        }
        tbi++;
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
    typedef struct {
        TableDirectory td ;
        tableu* table;

    }font;
    ACQRES(font){
        one(f.td);
        if(!f.table){f.table = new tableu[f.td.numTables];};
        for(int i =0 ; i <f.td.numTables){
            switch(f.td.tableRecords[i].tableTag){
                #define TABLE_RECORD(tag,member) case font_tag(tag):{offone((f.table[i].##member),f.td.tableRecords[i].offset);};
            TAG_MEMBER(TABLE_RECORD)          
            }
            
        }
    }

   
};
#endif