#ifndef FTHVAR_HPP
#define FTHVAR_HPP
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset32   itemVariationStoreOffset;
Offset32   advanceWidthMappingOffset;
Offset32   lsbMappingOffset;
Offset32   rsbMappingOffset;
}hvar;
#endif