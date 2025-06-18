typedef struct {
uint16   majorVersion;
uint16   minorVersion;
uint16   (reserved);
uint16   valueRecordSize;
uint16   valueRecordCount;
Offset16   itemVariationStoreOffset;
ValueRecord*   valueRecords;//[valueRecordCount]
}Metrics/* variations table:*/;
ACQRES(Metrics/* variations table:*/){
one(majorVersion);
one(minorVersion);
one((reserved));
one(valueRecordSize);
one(valueRecordCount);
one(itemVariationStoreOffset);
arr(valueRecords, valueRecordCount);
 };
USE_ACQRES(Metrics/* variations table:*/)

typedef struct {
Tag   valueTag;
uint16   deltaSetOuterIndex;
uint16   deltaSetInnerIndex;
}ValueRecord:;
typedef struct {
''hasc'   horizontal ascender;
''hdsc'   horizontal descender;
''hlgp'   horizontal line gap;
''hcla'   horizontal clipping ascent;
''hcld'   horizontal clipping descent;
''vasc'   vertical ascender;
''vdsc'   vertical descender;
''vlgp'   vertical line gap;
''hcrs'   horizontal caret rise;
''hcrn'   horizontal caret run;
''hcof'   horizontal caret offset;
''vcrs'   vertical caret rise;
''vcrn'   vertical caret run;
''vcof'   vertical caret offset;
''xhgt'   x height;
''cpht'   cap height;
''sbxs'   subscript em x size;
''sbys'   subscript em y size;
''sbxo'   subscript em x offset;
''sbyo'   subscript em y offset;
''spxs'   superscript em x size;
''spys'   superscript em y size;
''spxo'   superscript em x offset;
''spyo'   superscript em y offset;
''strs'   strikeout size;
''stro'   strikeout offset;
''unds'   underline size;
''undo'   underline offset;
''gsp0'*   gaspRange;//[0]
''gsp1'*   gaspRange;//[1]
''gsp2'*   gaspRange;//[2]
''gsp3'*   gaspRange;//[3]
''gsp4'*   gaspRange;//[4]
''gsp5'*   gaspRange;//[5]
''gsp6'*   gaspRange;//[6]
''gsp7'*   gaspRange;//[7]
''gsp8'*   gaspRange;//[8]
''gsp9'*   gaspRange;//[9]
}Value/* tags, ordered by logical groupings:*/;
ACQRES(Value/* tags, ordered by logical groupings:*/){
one(horizontal ascender);
one(horizontal descender);
one(horizontal line gap);
one(horizontal clipping ascent);
one(horizontal clipping descent);
one(vertical ascender);
one(vertical descender);
one(vertical line gap);
one(horizontal caret rise);
one(horizontal caret run);
one(horizontal caret offset);
one(vertical caret rise);
one(vertical caret run);
one(vertical caret offset);
one(x height);
one(cap height);
one(subscript em x size);
one(subscript em y size);
one(subscript em x offset);
one(subscript em y offset);
one(superscript em x size);
one(superscript em y size);
one(superscript em x offset);
one(superscript em y offset);
one(strikeout size);
one(strikeout offset);
one(underline size);
one(underline offset);
arr(gaspRange, 0);
 arr(gaspRange, 1);
 arr(gaspRange, 2);
 arr(gaspRange, 3);
 arr(gaspRange, 4);
 arr(gaspRange, 5);
 arr(gaspRange, 6);
 arr(gaspRange, 7);
 arr(gaspRange, 8);
 arr(gaspRange, 9);
 };
USE_ACQRES(Value/* tags, ordered by logical groupings:*/)

typedef struct {
''cpht'   cap height;
''gsp0'*   gaspRange;//[0]
''gsp1'*   gaspRange;//[1]
''gsp2'*   gaspRange;//[2]
''gsp3'*   gaspRange;//[3]
''gsp4'*   gaspRange;//[4]
''gsp5'*   gaspRange;//[5]
''gsp6'*   gaspRange;//[6]
''gsp7'*   gaspRange;//[7]
''gsp8'*   gaspRange;//[8]
''gsp9'*   gaspRange;//[9]
''hasc'   horizontal ascender;
''hcla'   horizontal clipping ascent;
''hcld'   horizontal clipping descent;
''hcof'   horizontal caret offset;
''hcrn'   horizontal caret run;
''hcrs'   horizontal caret rise;
''hdsc'   horizontal descender;
''hlgp'   horizontal line gap;
''sbxo'   subscript em x offset;
''sbxs'   subscript em x size;
''sbyo'   subscript em y offset;
''sbys'   subscript em y size;
''spxo'   superscript em x offset;
''spxs'   superscript em x size;
''spyo'   superscript em y offset;
''spys'   superscript em y size;
''stro'   strikeout offset;
''strs'   strikeout size;
''undo'   underline offset;
''unds'   underline size;
''vasc'   vertical ascender;
''vcof'   vertical caret offset;
''vcrn'   vertical caret run;
''vcrs'   vertical caret rise;
''vdsc'   vertical descender;
''vlgp'   vertical line gap;
''xhgt'   x height;
}Value/* tags, in alphabetical order of tags:*/;
ACQRES(Value/* tags, in alphabetical order of tags:*/){
one(cap height);
arr(gaspRange, 0);
 arr(gaspRange, 1);
 arr(gaspRange, 2);
 arr(gaspRange, 3);
 arr(gaspRange, 4);
 arr(gaspRange, 5);
 arr(gaspRange, 6);
 arr(gaspRange, 7);
 arr(gaspRange, 8);
 arr(gaspRange, 9);
 one(horizontal ascender);
one(horizontal clipping ascent);
one(horizontal clipping descent);
one(horizontal caret offset);
one(horizontal caret run);
one(horizontal caret rise);
one(horizontal descender);
one(horizontal line gap);
one(subscript em x offset);
one(subscript em x size);
one(subscript em y offset);
one(subscript em y size);
one(superscript em x offset);
one(superscript em x size);
one(superscript em y offset);
one(superscript em y size);
one(strikeout offset);
one(strikeout size);
one(underline offset);
one(underline size);
one(vertical ascender);
one(vertical caret offset);
one(vertical caret run);
one(vertical caret rise);
one(vertical descender);
one(vertical line gap);
one(x height);
};
USE_ACQRES(Value/* tags, in alphabetical order of tags:*/)

