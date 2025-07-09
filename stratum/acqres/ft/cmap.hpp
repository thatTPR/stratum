#ifndef TFCMAP_HPP
#define TFCMAP_HPP

#include <math.h>
#include <string>
template <typename charT,typename InT,typename cmapT>
void cmapnglyphId(cmapT& p,charT start,charT end,size_t* s, InT* res ,InT(*ptr)(cmapT,charT )){
    *s=end-start+1;
    res = new uint8[*s];
    for(InT i=start;i<=end;i++){res[i-start]=ptr(p,c[i]);}
};
typedef struct {
    uint16   firstCode;
    uint16   entryCount;
    int16   idDelta;
uint16   idRangeOffset;
/// @brief noldwr;
uint16 idIndex;
}SubHeader;
typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint8   glyphIdArray[256];//[256]
uint16 getRangeNum(){return 1;  };
}cmapSubFormat0;

uint8 cmap0glyphId(cmapSubFormat0& p,char c){return p.glyphIdArray[c];};
void cmap0glyphIds(cmapSubFormat0& p,char start,char end,size_t* s, uint8* res ){
    cmapnglyphId<char,uint8,cmapSubFormat0>(p,start,end,s,res,&cmap0glyphId);
};
typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint16   subHeaderKeys[256];//[256]Array that maps high bytes into the subHeaders array: value is subHeaders index × 8.
SubHeader*   subHeaders;//[ ]
uint16*   glyphIdArray;//[ ]

/// @brief noldwr
uint16 mshk;
uint16 numSub;
uint16 ngid;
uint16 maxSubHeaderKeys(){uint16 m=0;for(int i=0;i<256;i++){if(m<subHeaderKeys[i])m=subHeaderKeys[i];};};
uint16 getRangeNum(){uint16 n=0;
    for(int i=0;i<numSub;i++){
        n+=subHeaders[i].entryCount;
    };
    return n;
  };
}cmapSubFormat2;

template <typename charT>
uint16 cmap2glyphId(cmapSubFormat2& f,charT c){
     for(int i=0;i<f.numSub;i++){
        if(f.subHeaders[i].firstCode<c ){
            uint16 dif = c= f.subHeaders.firstCode - c;
            if(dif<f.subHeaders[i].entryCount){
                uint16 res =  f.glyphIdArray[f.subHeaders[i].idIndex+dif];
                if(res!=0){res+=f.f.subHeaders[i].idDelta;}
                if(res<0){res+=65536;};
                return res;
            } 
        }
    }
};
template <typename charT>
void cmap2glyphIds(cmapSubFormat2& p,charT start,charT end,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat2>(p,start,end,start,end,res,&cmap2glyphId);
};
ACQRES(cmapSubFormat2){
// one((f.format));
one(f.length);
one(f.language);
arr(f.subHeaderKeys, 256);
uint16 f.mshk = = f.maxSubHeaderKeys(); 
uint16 f.numSub = 1+mshk/8;
 
 arr(f.subHeaders,numSub  );
 uint16 ngid=0;
 for(int i =0 ; i < numSub;i++){
    #define SIZE_GlyphID sizeof(uint16)
    uint16 ec = f.subHeaders[i].entryCount;
    uint16 off =  f.subHeaders[i].idRangeOffset;
    f.subHeaders[i].idIndex = (off-(numsub-1-i)*sizeof(SubHeader)) /SIZE_GlyphID ;
    ngid = ngid<(f.subHeaders[i].idIndex+ec-1)?(f.subHeaders[i].idIndex+ec-1):ngid;
}
 f.ngid=ngid;
 if(!f.glyphIdArray){f.glyphIdArray=new uint16[f.ngid];}

 for(int i =0 ; i < numSub;i++){
    set(f.subHeaders[i].idRangeOffset);
    offone(f.glyphIdArray[i], f.subHeaders[i].idRangeOffset );
    d.subHeaders[i].idIndex=i;
 }
 };
USE_ACQRES(cmapSubFormat2)

typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint16   segCountX2;
uint16   searchRange;
uint16   entrySelector;
uint16   rangeShift;
uint16*   endCode;//[segCount]
uint16   reservedPad;
uint16*   startCode;//[segCount]
int16*   idDelta;//[segCount]
uint16*   idRangeOffset;//[segCount]
uint16*   glyphIdArray;//[ ]
    uint16 searchRange(uint16 segCount){return pow(2,floor(log2(segCount)));}
    uint16 entrySelector(uint16 segCount){return floor(log2(segCount));} //log2(searchRange/2)
    uint16 rangeShift(uint16 segCount){return segCount*2 - searchRange(segCount);}
    uint16 glyphId(int8 c){ *(idRangeOffset[i]/2
            + (c - startCode[i])
            + idRangeOffset[i])};

    uint16 getRangeNum(){
        uint16 n=0;
        for(int i=0;i<segCountX2/2;i++){
            n+=endCode[i]-startCode[i]+1;
        }
        return n;
      };

}cmapSubFormat4;
ACQRES(cmapSubFormat4){
// one((f.format));
one(f.length);
one(f.language);
one(f.segCountX2);
one(f.searchRange);
one(f.entrySelector);
one(f.rangeShift);
uint16 segCount=f.segCountX2/2;
arr(f.endCode, segCount);
one(f.reservedPad);
arr(f.startCode, segCount);
arr(f.idDelta, segCount);
arr(f.idRangeOffset, segCount);
uint16 numgid=0;
for(int i=0;i<segCount;i++){numgid+=f.endCode[i]-f.startCode[i]+1;};
if(!f.glyphIdArray){f.glyphIdArray=new uint16[numgid];}
 for(int i =0 ; i < numgid;){
    for(int j=0;j<segCount;j++){
        if(f.idRangeOffset[j]>0){set(f.idRangeOffset[j]);
           offone(f.glyphIdArray[i], f.idRangeOffset[j] ); };
        i++;
    }
 };
 f.length=8*2+ 2*(segCount)*4+2*numgid;
}
USE_ACQRES(cmapSubFormat4)

template <typename charT>
uint16 cmap4glyphId(cmapSubFormat4& p, charT c){
    uint16 segcount=f.segCountX2/2;
    for(int i=0;i<segcount;i++){
        if(f.endCode[i]>=c and(f.startCode[i]<=c)) {
            if(idRangeOffset[i]==0){uint16 ind=f.idDelta[i]+c; 
                if(ind<0){ind+=65536};return f.glyphIdArray[ind];};
            uint16 glyphId= *(idRangeOffset[i]/2
            + (c - startCode[i])
            + &idRangeOffset[i]);
            if(glyphId!=){glyphId+=f.idDelta[i];return glyphId>0?glyphId:glyphId+65536; }
        };
    }
};

template <typename charT>
void cmap4glyphIds(cmapSubFormat4& p,charT start,charT end,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat4>(p,start,end,s,res,&cmap4glyphId);
};

typedef struct {
// uint16   format;
uint16   length;
uint16   language;
uint16   firstCode;
uint16   entryCount;
uint16*   glyphIdArray;//[entryCount]
uint16 getRangeNum(){return entryCount;  };

}cmapSubFormat6;
template <typename charT>
ACQRES(cmapSubFormat6){
    // one((f.format));
    one(f.length);
    one(f.language);
    one(f.firstCode);
    one(f.entryCount);
    arr(f.glyphIdArray, f.entryCount);
    f.length= 5*2 + 2*f.entryCount;
};
USE_ACQRES(cmapSubFormat6)
uint16 cmap6glyphId(cmapSubFormat6& p, charT c){
    int16 s=c-f.firstCode;
    if(s>=0 and s<f.entryCount){
        return f.glyphIdArray[c-f.firstCode];
    };
    return 0;
};
template <typename charT>
void cmap6glyphIds(cmapSubFormat6& p,charT start,charT end,,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat6>(p,start,end,s,res,&cmap6glyphId);
};


typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   startGlyphID;
}SequentialMapGroup;

typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint8*   is32;//[8192]
uint32   numGroups;
SequentialMapGroup*   groups;//[numGroups]
uint16 getRangeNum(){uint16 n=0;
    for (int i = 0; i < numGroups; i++)
    {
        n+=groups[i].endCharCode-groups[i].startCharCode+1;
    }
    return n;
    
  };

}cmapSubFormat8;
ACQRES(cmapSubFormat8){
// one((f.format));
one(f.reserved);
one(f.length);
one(f.language);
_8192=8192;
arr(f.is32, _8192);
 one(f.numGroups);
arr(f.groups, f.numGroups);
f.length=2*6+8192+sizeof(SequentialMapGroup)*f.numGroups;
 };
USE_ACQRES(cmapSubFormat8)
uint32 cmap8glyphId(cmapSubFormat8& p, charT c){
    for(int i=0;i<f.numGroups;i++){
        if(f.groups[i].startCharCode <= c and(f.groups[i].endCharCode <= c)){
            uint32 cc = c-f.groups[i].startCharCode;
            return cc+f.groups[i].startGlyphId;
            // if(f.is32[c/8] & 1<<(8-c%8)){// TODO

        }
    }
    return 0;
};
template <typename charT>
void cmap8glyphIds(cmapSubFormat8& p,charT start,charT end,,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat8>(p,start,end,s,res,&cmap8glyphId);
};

typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   startCharCode;
uint32   numChars;
uint16*   glyphIdArray;//[numChars]
uint16 getRangeNum(){return numChars;}

}cmapSubFormat10;
ACQRES(cmapSubFormat10){
    one(f.reserved);
    one(f.length);
    one(f.language);
    one(f.startCharCode);
    one(f.numChars);
    arr(f.glyphIdArray,f.numChars);
    f.length=4+4*4+2*f.numChars;
}
uint32 cmap10glyphId(cmapSubFormat10& p, charT c){
    if(c>=f.startCharCode ){
        uint32 dif = c-f.startCharCode ;
        if(dif<numChars)return f.glyphIdArray[dif];
    };
    return 0;
};
template <typename charT>
void cmap10glyphIds(cmapSubFormat10& p,charT start,charT end,,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat10>(p,start,end,s,res,&cmap10glyphId);
};


typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   numGroups;
SequentialMapGroup*   groups;//[numGroups]
uint16 getRangeNum(){uint16 n=0;
    for (int i = 0; i <numGroups; i++)
    {
        n+=groups[i].endCharCode-groups[i].startCharCode+1;
    }
    return n;
}

}cmapSubFormat12;
ACQRES(cmapSubFormat12){
// one((f.format));
one(f.reserved);
one(f.length);
one(f.language);
one(f.numGroups);
arr(f.groups, f.numGroups);
f.length=4+3*4+sizeof(SequentialMapGroup)*f.numGroups;
 };
USE_ACQRES(cmapSubFormat12)
uint32 cmap12glyphId(cmapSubFormat12& p, charT c){
    for(int i=0;i<f.numGroups;i++){
        if(f.groups[i].startCharCode <= c and(f.groups[i].endCharCode <= c)){
            uint32 cc = c-f.groups[i].startCharCode;
            return cc+f.groups[i].startGlyphId;
        }
    }
    return 0;
};
template <typename charT>
void cmap12glyphIds(cmapSubFormat12& p,charT start,charT end,,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat12>(p,start,end,s,res,&cmap13glyphId);
};

typedef struct {
uint32   startCharCode;
uint32   endCharCode;
uint32   glyphID;
}ConstantMapGroup;
typedef struct {
// uint16   format;
uint16   reserved;
uint32   length;
uint32   language;
uint32   numGroups;
ConstantMapGroup*   groups;//[numGroups]
uint16 getRangeNum(){return numGroups;}

}cmapSubFormat13;
ACQRES(cmapSubFormat13){
// one((f.format));
one(f.reserved);
one(f.length);
one(f.language);
one(f.numGroups);
arr(f.groups, f.numGroups);
f.length=4+4*3+sizeof(ConstantMapGroup)*f.numGroups;
 };
USE_ACQRES(cmapSubFormat13)
uint32 cmap13glyphId(cmapSubFormat13& p, charT c){
    for(int i=0;i<f.numGroups;i++){
        if(f.groups[i].startCharCode <= c and(f.groups[i].endCharCode <= c)){
            return f.groups[i].glyphID;
        }
    }
    return 0;
};
template <typename charT>
void cmap13glyphIds(cmapSubFormat13& p,charT start,charT end,,size_t* s, uint16* res){
    cmapnglyphId<charT,uint16,cmapSubFormat13>(p,start,end,s,res,&cmap13glyphId);
};
typedef struct {
uint24   unicodeValue;
uint16   glyphID;
}UVSMapping;
typedef struct {
uint32   numUVSMappings;
UVSMapping*   uvsMappings;//[numUVSMappings]
}NonDefaultUVS;
ACQRES(NonDefaultUVS){
one(f.numUVSMappings);
arr(f.uvsMappings, f.numUVSMappings);
 };
USE_ACQRES(NonDefaultUVS)

typedef struct {
uint24   startUnicodeValue;
uint8   additionalCount;
}UnicodeRange;
typedef struct {
uint32   numUnicodeValueRanges;
UnicodeRange*   ranges;//[numUnicodeValueRanges]
}DefaultUVS;
ACQRES(DefaultUVS){
one(f.numUnicodeValueRanges);
arr(f.ranges, f.numUnicodeValueRanges);
 };
USE_ACQRES(DefaultUVS)
typedef struct {
uint24   varSelector;
Offset32   defaultUVSOffset;
Offset32   nonDefaultUVSOffset;
uint16 defaultUvsI;
uint16 nonDefaultUvsI;
}VariationSelector;
ACQRES(VariationSelector){
one(varSelector);
one(defaultUVSOffset);
one(nonDefaultUVSOffset);

}
USE_ACQRES(VariationSelector)
typedef struct {
// uint16   format;
uint32   length;
uint32   numVarSelectorRecords;
VariationSelector*   varSelector;//[numVarSelectorRecords]
/// @brief noldwr;
uint16 numDUVS,numNDUVS;
DefaultUVS* defaultUVS; 
NonDefaultUVS* nonDefaultUVS; 
}cmapSubFormat14;
ACQRES(cmapSubFormat14){
// one((f.format));
one(f.length);
one(f.numVarSelectorRecords);
arr(f.varSelector, f.numVarSelectorRecords);
f.length=2+4*2+sizeof(VariationSelector)*f.numVarSelectorRecords;
f.numNDUVS=0;f.numDUVS=0;
for(int i=0;i< f.numVarSelectorRecords;i++){
    if(f.varSelector[i].defaultUvsOffset!=0){f.varSelector[i].defaultUvsI=f.numDUVS;f.numDUVS++;};
    if(f.varSelector[i].nonDefaultUvsOffset!=0){f.varSelector[i].nonDefaultUvsI=f.numNDUVS;f.numNDUVS++;};
};
if(!f.defaultUVS){f.defaultUVS=DefaultUVS[numVarSelectorRecords];}
if(!f.nonDefaultUVS){f.nonDefaultUVS=NonDefaultUVS[numVarSelectorRecords];}
for(int i=0;i<f.numVarSelectorRecords;i++){
if(f.varSelector[i].defaultUVSOffset!=0){
offone(f.defaultUVS[f.varSelector[i].defaultUVSI],f.varSelector[i].defaultUVSOffset);}
if(f.varSelector[i].nonDefaultUVSOffset!=0){
offone(f.nonDefaultUVS[f.varSelector[i].nonDefaultUVSI],f.varSelector[i].nonDefaultUVSOffset);}
};};
USE_ACQRES(cmapSubFormat14)
template <typename charT>
void cmap14glyphIds(cmapSubFormat14& p,charT start,charT end,,size_t* s, uint16* res){
    
    std::vector<uint16> ret;
    #define DEFUVS(i) f.varSelector[i].defualtUVS
    #define NDEFUVS(i) f.varSelector[i].nonDefaultUVS
    for(int i=0;i<f.numVarSelectorRecords;i++){
        for(int k=0;k<c.length();k++){

            if(DEFUVS(i)Offset!=0){
                for(int j=0;j<f.defaultUVS[DEFUVS(i)I].numUnicodeRanges,j++){
                    if(f.defaultUVS[DEFUVS(i)I].ranges[j].startUnicodeValue<c[k] ){
                    uint32 dif =c[k]-f.defaultUVS[DEFUVS(i)I].ranges[j].startUnicodeValue;
                    if(dif<=f.defaultUVS[DEFUVS(i)I].ranges[j].additionalCount)
                    {ret.push_back(f.defaultUVS[DEFUVS(i)I].ranges[j].startUnicodeValue+dif);}
                };
            }
        }
        if(NDEFUVS(I)Offset!=0){
            for(int j=0;j<f.nonDefaultUVS[NDEFUVS(i)I].numUVSMappings;j++){
                if(f.nonDefultUVS[NDEFUVS(i)I].ivsMappings[j].unicodeValue == c[k]){
                    ret.push_back(f.nonDefultUVS[NDEFUVS(i)I].ivsMappings[j].glyphID);
                }
            }
        }
    }
    }
    *s = ret.size();
    res=ret.data();
};
uint32 cmap14glyphId(cmapSubFormat14& p, charT c){
    std::basic_string<c> s =std::string(c);size_t s; uint16* res;
    cmap14glyphIds<charT>(p,s,&s,res);
    if(s>0){return res[0];};
};


typedef struct {
    uint16   format;
    union {
    cmapSubFormat0 f0;
    cmapSubFormat2 f2;
    cmapSubFormat4 f4;
    cmapSubFormat6 f6;
    cmapSubFormat8 f8;
    cmapSubFormat10 f10;
    cmapSubFormat12 f12;
    cmapSubFormat13 f13;
    cmapSubFormat14 f14 ;
} f;
}cmapSubFormat;
ACQRES(cmapSubFormat){
    one(f.format);
    switch(f.format){
        case 0 : {one(f.f.f0);};
        case 2 : {one(f.f.f2);};
        case 4 : {one(f.f.f4);};
        case 6 : {one(f.f.f6);};
        case 8 : {one(f.f.f8);};
        case 10 : {one(f.f.f10);};
        case 12 : {one(f.f.f12);};
        case 13 : {one(f.f.f13);};
        case 14 : {one(f.f.f14);};
    }
};
enum PlatformID {
        Unicode=0,
        Macntosh=1,
        ISO=2,
        Windows=3,
        Custom=4
    };
    // enum UnicodeID{
    //     0	Unicode 1.0 semantics—deprecated
    //     1	Unicode 1.1 semantics—deprecated
    //     2	ISO/IEC 10646 semantics—deprecated
    //     3	Unicode 2.0 and onwards semantics, Unicode BMP only
    //     4	Unicode 2.0 and onwards semantics, Unicode full repertoire
    //     5	Unicode variation sequences—for use with subtable format 14
    //     6	Unicode full repertoire—for use with subtable format 13
    // };
typedef struct {
uint16   platformID;
uint16   encodingID;
Offset32   subtableOffset;
}EncodingRecord;
typedef struct {
uint16   version;
uint16   numTables;
EncodingRecord*   encodingRecords;//[numTables]
}cmapHeader;
ACQRES(cmapHeader){
one(f.version);
one(f.numTables);
arr(f.encodingRecords, f.numTables);
 };
USE_ACQRES(cmapHeader)

typedef struct {
    cmapHeader head;
    cmapSubFormat* tables;
    void getRanges(uint16* s,uint16* starts,uint16* ends){
        int n=0;
        for(int i=0;i<head.numTables;i++){
            switch(tables[i].format){
                case 0 : {n+=getRangeNum();break;}
                case 2 : {n+=getRangeNum();break;}
                case 4 : {n+=getRangeNum();break;}
                case 6 : {n+=getRangeNum();break;}
                case 8 : {n+=getRangeNum();break;}
                case 10 : {n+=getRangeNum();break;}
                case 12 : {n+=getRangeNum();break;}
                case 13 : {n+=getRangeNum();break;}
                case 14 : {n+=getRangeNum();break;}
            }
        }
        *s=n;

    };
}cmap;
ACQRES(cmap){
    one(f.head);
    if(!f.cmapSubFormat){f.cmapSubFormat= new cmapSubFormat[f.head.numTables];};
    for(int i = 0; i <f.head.numTables;i++){
        offone(f.tables[i],f.head.encodingRecords[i].subtableOffset);
    };
}
USE_ACQRES(cmap)
template <typename charT>
uint32 cmapSubGlyphId(cmapSubFormat& f,charT c){
    switch(f.format){
case 0 :  {return cmap0GlyphId(f.f.f0,c);};
case 2 :  {return cmap2GlyphId(f.f.f2,c);};
case 4 :  {return cmap4GlyphId(f.f.f4,c);};
case 6 :  {return cmap6GlyphId(f.f.f6,c);};
case 8 :  {return cmap8GlyphId(f.f.f8,c);};
case 10 : {return cmap10GlyphId(f.f.f10,c);};
case 12 : {return cmap12GlyphId(f.f.f12,c);};
case 13 : {return cmap13GlyphId(f.f.f13,c);};
case 14 : {return cmap14GlyphId(f.f.f14,c);};
    }
};
template <typename charT, typename uintT>
 cmapSubGlyphIds(cmapSubFormat& f,charT start ,charT end,uintT* r,size_t* s){
    switch(f.format){
case 0 :  {return cmap0GlyphIds(f.f.f0,c,s,s,r);};
case 2 :  {return cmap2GlyphIds(f.f.f2,c,s,s,r);};
case 4 :  {return cmap4GlyphIds(f.f.f4,c,s,s,r);};
case 6 :  {return cmap6GlyphIds(f.f.f6,c,s,s,r);};
case 8 :  {return cmap8GlyphIds(f.f.f8,c,s,s,r);};
case 10 : {return cmap10GlyphIds(f.f.f10,c,s,s,r);};
case 12 : {return cmap12GlyphIds(f.f.f12,c,s,s,r);};
case 13 : {return cmap13GlyphIds(f.f.f13,c,s,s,r);};
case 14 : {return cmap14GlyphIds(f.f.f14,c,s,s,r);};
    }
};

template <typename charT, typename uintT>
uintT cmapGlyphId(cmap* cm, charT c  ){
    for(int i=0;i<numTables;i++){
       uintT res = cmapSubGlyphId(cm->tables[i]);
        if(res!=0){return res;};
    }
};

template <typename charT>
void cmapGlyphIds(cmap* cm,charT start,charT end,  size_t* s,uint32* r   ){
    *s=0;
    for(int i=0;i<numTables;i++){
        
        cmapSubGlyphIds(cm->tables[i],o,s,r);
        if(s>=0){return ;};
    };
};

template <typename charT>
uint32 cmapGlyphIds(cmap* cm, size_t numRanges,charT *rangeStarts,charT *rangeEnd   ){
    for(int i=0;i<numTables;i++){

    };
};

#endif

