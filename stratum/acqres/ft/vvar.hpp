#ifndef FTVVAR_HPP
#define FTVVAR_HPP
#include "_fontVarCommon.hpp"

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset32   itemVariationStoreOffset;
Offset32   advanceHeightMappingOffset;
Offset32   tsbMappingOffset;
Offset32   bsbMappingOffset;
Offset32   vOrgMappingOffset;
/// @brief Offsets;
ItemVariationStore itemVariationStore;
DeltaSetIndexMap advanceHeightMapping;
DeltaSetIndexMap tsbMapping;
DeltaSetIndexMap bsbMapping;
DeltaSetIndexMap vOrgMapping;
}VVAR;
ACQRES(VVAR){
one(f.majorVersion);
one(f.minorVersion);
one(f.itemVariationStoreOffset);
one(f.advanceHeightMappingOffset);
one(f.tsbMappingOffset);
one(f.bsbMappingOffset);
one(f.vOrgMappingOffset);
offone(f.itemVariationStore,f.itemVariationStoreOffset);
offone(f.advanceHeightMapping,f.advanceHeightMappingOffset);
offone(f.tsbMapping,f.tsbMappingOffset);
offone(f.bsbMapping,f.bsbMappingOffset);
offone(f.vOrgMapping,f.vOrgMappingOffset);
}
USE_ACQRES(VVAR)
#endif