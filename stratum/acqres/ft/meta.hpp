typedef struct {
uint32   version;
uint32   flags;
uint32   (reserved);
uint32   dataMapsCount;
DataMap*   dataMaps;//[dataMapsCount]
}MetaHeader;
ACQRES(MetaHeader){
one(version);
one(flags);
one((reserved));
one(dataMapsCount);
arr(dataMaps, dataMapsCount);
 };
USE_ACQRES(MetaHeader)

typedef struct {
Tag   tag;
Offset32   dataOffset;
uint32   dataLength;
}DataMap/* record*/;
