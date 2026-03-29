#ifndef FTVORG_HPP
#define FTVORG_HPP

typedef struct {
    uint16   glyphIndex;
int16   vertOriginY;
}VertOriginYMetrics;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
int16   defaultVertOriginY;
uint16   numVertOriginYMetrics;
VertOriginYMetrics*   vertOriginYMetrics;//[numVertOriginYMetrics]
}VORG;
ACQRES(VORG){
one(f.majorVersion);
one(f.minorVersion);
one(f.defaultVertOriginY);
one(f.numVertOriginYMetrics);
arr(f.vertOriginYMetrics, f.numVertOriginYMetrics);
};
USE_ACQRES(VORG)
#endif