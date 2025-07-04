#ifndef FTMVAR_HPP
#define FTMVAR_HPP
#include "_fontVarCommon.hpp"
/// @brief  
const Tag hasc=Tag("hasc");//  horizontal ascender;
const Tag hdsc=Tag("hdsc");//  horizontal descender;
const Tag hlgp=Tag("hlgp");//  horizontal line gap;
const Tag hcla=Tag("hcla");//  horizontal clipping ascent;
const Tag hcld=Tag("hcld");//  horizontal clipping descent;
const Tag vasc=Tag("vasc");//  vertical ascender;
const Tag vdsc=Tag("vdsc");//  vertical descender;
const Tag vlgp=Tag("vlgp");//  vertical line gap;
const Tag hcrs=Tag("hcrs");//  horizontal caret rise;
const Tag hcrn=Tag("hcrn");//  horizontal caret run;
const Tag hcof=Tag("hcof");//  horizontal caret offset;
const Tag vcrs=Tag("vcrs");//  vertical caret rise;
const Tag vcrn=Tag("vcrn");//  vertical caret run;
const Tag vcof=Tag("vcof");//  vertical caret offset;
const Tag xhgt=Tag("xhgt");//  x height;
const Tag cpht=Tag("cpht");//  cap height;
const Tag sbxs=Tag("sbxs");//  subscript em x size;
const Tag sbys=Tag("sbys");//  subscript em y size;
const Tag sbxo=Tag("sbxo");//  subscript em x offset;
const Tag sbyo=Tag("sbyo");//  subscript em y offset;
const Tag spxs=Tag("spxs");//  superscript em x size;
const Tag spys=Tag("spys");//  superscript em y size;
const Tag spxo=Tag("spxo");//  superscript em x offset;
const Tag spyo=Tag("spyo");//  superscript em y offset;
const Tag strs=Tag("strs");//  strikeout size;
const Tag stro=Tag("stro");//  strikeout offset;
const Tag unds=Tag("unds");//  underline size;
const Tag undo=Tag("undo");//  underline offset;
const Tag gsp0=Tag("gsp0");//   gaspRange;//[0]
const Tag gsp1=Tag("gsp1");//   gaspRange;//[1]
const Tag gsp2=Tag("gsp2");//   gaspRange;//[2]
const Tag gsp3=Tag("gsp3");//   gaspRange;//[3]
const Tag gsp4=Tag("gsp4");//   gaspRange;//[4]
const Tag gsp5=Tag("gsp5");//   gaspRange;//[5]
const Tag gsp6=Tag("gsp6");//   gaspRange;//[6]
const Tag gsp7=Tag("gsp7");//   gaspRange;//[7]
const Tag gsp8=Tag("gsp8");//   gaspRange;//[8]
const Tag gsp9=Tag("gsp9");//   gaspRange;//[9]


typedef struct {
Tag   valueTag;
uint16   deltaSetOuterIndex;
uint16   deltaSetInnerIndex;
}ValueRecord:;

typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   reserved;
uint16   valueRecordSize;
uint16   valueRecordCount;
Offset16   itemVariationStoreOffset;
ValueRecord*   valueRecords;//[valueRecordCount]

ItemVariationStore varStore ;
}MVAR;
ACQRES(MVAR){
one(f.majorVersion);
one(f.minorVersion);
one(f.reserved);
one(f.valueRecordSize);
one(f.valueRecordCount);
one(f.itemVariationStoreOffset);
arr(f.valueRecords, f.valueRecordCount);
offone(f.varStore, itemVariationStoreOffset);
 };
USE_ACQRES(MVAR)
#endif