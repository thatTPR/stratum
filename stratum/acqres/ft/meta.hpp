#ifndef FTMETA_HPP
#define FTMETA_HPP

const Tag appl = Tag("appl");//	(reserved)		Reserved — used by Apple.
const Tag bild = Tag("bild");//	(reserved)		Reserved — used by Apple.
const Tag dlng = Tag("dlng");//	Design languages	Text, using only Basic Latin (ASCII) characters.	Indicates languages and/or scripts for the user audiences that the font was primarily designed for. Only one instance is used. See below for additional details.
const Tag slng = Tag("slng");//	Supported languages	Text, using only Basic Latin (ASCII) characters.	Indicates languages and/or scripts that the font is declared to be capable of supporting. Only one instance is used. See below for additional details.
bool meta_Tag(Tag t){
    switch(t){
        case appl :{return true;};
        case bild :{return true;};
        case dlng :{return true;};
        case slng :{return true;};
    };
    return false;
};
typedef union {
    uint8* bytes;
} metaData;
typedef struct {
Tag   tag;
Offset32   dataOffset;
uint32   dataLength;
}DataMap;
typedef struct {
uint32   version;
uint32   flags;
uint32   reserved;
uint32   dataMapsCount;
DataMap*   dataMaps;//[dataMapsCount]

metaData* u;//[dataMapsCount]
}meta;
ACQRES(meta){
one(f.version);
one(f.flags);
one(f.reserved);
one(f.dataMapsCount);
arr(f.dataMaps, f.dataMapsCount);
if(!f.u){f.u=new metaData[f.dataMapsCount];};
for(int i=0;i<f.dataMapsCount;i++){
    offarr(f.u[i].bytes,f.dataMaps[i].dataOffset,f.dataMaps[i].dataLength);
}
 };
USE_ACQRES(meta)


#endif