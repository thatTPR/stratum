#ifndef FTJSTF_HPP
#define FTJSTF_HPP
#include "gpos.hpp"
#include "gsub.hpp"

typedef struct {
uint16   glyphCount;
uint16*   extenderGlyphs;//[glyphCount]
}ExtenderGlyph;
ACQRES(ExtenderGlyph){
one(f.glyphCount);
arr(f.extenderGlyphs, f.glyphCount);
};
USE_ACQRES(ExtenderGlyph)

typedef struct {
uint16   lookupCount;
Offset16*   lookupOffsets;//[lookupCount]
}JstfMax;
ACQRES(JstfMax){
one(f.lookupCount);
arr(f.lookupOffsets, f.lookupCount);
 };
USE_ACQRES(JstfMax)

typedef struct {
Offset16   gsubShrinkageEnableOffset;
Offset16   gsubShrinkageDisableOffset;
Offset16   gposShrinkageEnableOffset;
Offset16   gposShrinkageDisableOffset;
Offset16   shrinkageJstfMaxOffset;
Offset16   gsubExtensionEnableOffset;
Offset16   gsubExtensionDisableOffset;
Offset16   gposExtensionEnableOffset;
Offset16   gposExtensionDisableOffset;
Offset16   extensionJstfMaxOffset; 

JstfModList gsubShrinkageEnable;
JstfModList gsubShrinkageDisable;
JstfModList gposShrinkageEnable;
JstfModList gposShrinkageDisable;
JstfMax shrinkageJstfMax;
JstfModList gsubExtensionEnable;
JstfModList gsubExtensionDisable;
JstfModList gposExtensionEnable;
JstfModList gposExtensionDisable;
JStfMax extensionJstfMax;
}JstfPriority;
ACQRES(JstfPriority){
    one(f.gsubShrinkageEnableOffset);
    one(f.gsubShrinkageDisableOffset);
    one(f.gposShrinkageEnableOffset);
    one(f.gposShrinkageDisableOffset);
    one(f.shrinkageJstfMaxOffset);
    one(f.gsubExtensionEnableOffset);
    one(f.gsubExtensionDisableOffset);
    one(f.gposExtensionEnableOffset);
    one(f.gposExtensionDisableOffset);
    one(f.extensionJstfMaxOffset);

    offone(f.gsubShrinkageEnable,f.gsubShrinkageEnableOffset);
    offone(f.gsubShrinkageDisable,f.gsubShrinkageDisableOffset);
    offone(f.gposShrinkageEnable,f.gposShrinkageEnableOffset);
    offone(f.gposShrinkageDisable,f.gposShrinkageDisableOffset);
    offone(f.shrinkageJstfMax,f.shrinkageJstfMaxOffset);
    offone(f.gsubExtensionEnable,f.gsubExtensionEnableOffset);
    offone(f.gsubExtensionDisable,f.gsubExtensionDisableOffset);
    offone(f.gposExtensionEnable,f.gposExtensionEnableOffset);
    offone(f.gposExtensionDisable,f.gposExtensionDisableOffset);
    offone(f.extensionJstfMax,f.extensionJstfMaxOffset);
}
USE_ACQRES(JstfPriority)

typedef struct {
uint16   jstfPriorityCount;
Offset16*   jstfPriorityOffsets;//[jstfPriorityCount]
JstfPriority* jstfPriority;
}JstfLangSys;
ACQRES(JstfLangSys){
one(f.jstfPriorityCount);
arr(f.jstfPriorityOffsets, f.jstfPriorityCount);
offmany(f.jstfPriority,f.jstfPriorityOffsets,f.jstfPriorityCount);
};
USE_ACQRES(JstfLangSys)
typedef struct {
Tag   jstfLangSysTag;
Offset16   jstfLangSysOffset;

JstfLangSys jstfLangSys;
}JstfLangSysRecord;
ACQRES(JstfLangSysRecord){
    one(f.jstfLangSysTag);
    one(f.jstfLangSysOffset);
    offone(f.jstfLangSys,f.jstfLangSysOffset);
}
USE_ACQRES(JstfLangSysRecord)
typedef struct {
Offset16   extenderGlyphOffset;
Offset16   defJstfLangSysOffset;
uint16   jstfLangSysCount;

JstfLangSysRecord*   jstfLangSysRecords;//[jstfLangSysCount]
/// @brief
ExtenderGlyph extenderGlyph;
JstfLangSys jstfLangSys;
}JstfScript;
ACQRES(JstfScript){
one((f.extenderGlyphOffset));
one((f.defJstfLangSysOffset));
one((f.jstfLangSysCount));
arr(f.jstfLangSysRecords, f.jstfLangSysCount);
offone(f.extenderGlyph,f.extenderGlyphOffset);
offone(f.jstfLangSys,f.defJstfLangSysOffset); 
};
USE_ACQRES(JstfScript)
typedef struct {
uint16   lookupCount;
uint16*   lookupIndices;//[lookupCount]
}JstfModList;
ACQRES(JstfModList){
one((f.lookupCount));
arr(f.lookupIndices, f.lookupCount);
 };
USE_ACQRES(JstfModList)

typedef struct {
Tag   jstfScriptTag;
Offset16   jstfScriptOffset; 
}JstfScriptRecord;

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   jstfScriptCount;
JstfScriptRecord*   jstfScriptRecords;//[jstfScriptCount]
JstfScript* jstfScript ;
}JSTF;
ACQRES(JSTF){
one(f.majorVersion);
one(f.minorVersion);
one(f.jstfScriptCount);
arr(f.jstfScriptRecords, f.jstfScriptCount);
if(!f.jstfScript){f.jstfScript=new JstfScript[f.jstfScriptCount];};
for(int i=0;i<f.jstfScriptCount;i++){offone(f.jstfScript[i],f.jstfScriptRecords[i].jstfScriptOffset);} 
};
USE_ACQRES(JSTF)

#endif