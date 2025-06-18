typedef struct {
uint16   majorVersion;
uint16   minorVersion;
int16   defaultVertOriginY;
uint16   numVertOriginYMetrics;
VertOriginYMetrics*   vertOriginYMetrics;//[numVertOriginYMetrics]
}VerticalOrigin/* table*/;
ACQRES(VerticalOrigin/* table*/){
one(majorVersion);
one(minorVersion);
one(defaultVertOriginY);
one(numVertOriginYMetrics);
arr(vertOriginYMetrics, numVertOriginYMetrics);
 };
USE_ACQRES(VerticalOrigin/* table*/)

typedef struct {
uint16   glyphIndex;
int16   vertOriginY;
}VertOriginYMetrics/* record*/;
