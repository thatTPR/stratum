typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint32   numSizes;
BitmapScale*   strikes;//[numSizes]
}EBSC/* table*/;
ACQRES(EBSC/* table*/){
one(majorVersion);
one(minorVersion);
one(numSizes);
arr(strikes, numSizes);
 };
USE_ACQRES(EBSC/* table*/)

typedef struct {
SbitLineMetrics   hori;
SbitLineMetrics   vert;
uint8   ppemX;
uint8   ppemY;
uint8   substitutePpemX;
uint8   substitutePpemY;
}BitmapScale/* record*/;
