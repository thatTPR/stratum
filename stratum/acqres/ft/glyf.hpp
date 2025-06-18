typedef struct {
int16   numberOfContours;
int16   xMin;
int16   yMin;
int16   xMax;
int16   yMax;
}Glyph/* Header*/;
typedef struct {
uint16*   endPtsOfContours;//[numberOfContours]
uint16   instructionLength;
uint8*   instructions;//[instructionLength]
uint8   flags;
uint8 or int16   xCoordinates;
uint8 or int16   yCoordinates;
}Simple/* Glyph table*/;
ACQRES(Simple/* Glyph table*/){
arr(endPtsOfContours, numberOfContours);
 one(instructionLength);
arr(instructions, instructionLength);
 one(flags);
one(xCoordinates);
one(yCoordinates);
};
USE_ACQRES(Simple/* Glyph table*/)

typedef struct {
0x01   ON_CURVE_POINT;
0x02   X_SHORT_VECTOR;
0x04   Y_SHORT_VECTOR;
0x08   REPEAT_FLAG;
0x10   X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR;
0x20   Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR;
0x40   OVERLAP_SIMPLE;
0x80   Reserved;
}Simple/* Glyph flags*/;
typedef struct {
uint16   flags;
uint16   glyphIndex;
uint8, int8, uint16 or int16   argument1;
uint8, int8, uint16 or int16   argument2;
[transform data]   ;
}Component/* Glyph record*/;
typedef struct {
0x0001   ARG_1_AND_2_ARE_WORDS;
0x0002   ARGS_ARE_XY_VALUES;
0x0004   ROUND_XY_TO_GRID;
0x0008   WE_HAVE_A_SCALE;
0x0020   MORE_COMPONENTS;
0x0040   WE_HAVE_AN_X_AND_Y_SCALE;
0x0080   WE_HAVE_A_TWO_BY_TWO;
0x0100   WE_HAVE_INSTRUCTIONS;
0x0200   USE_MY_METRICS;
0x0400   OVERLAP_COMPOUND;
0x0800   SCALED_COMPONENT_OFFSET;
0x1000   UNSCALED_COMPONENT_OFFSET;
0xE010   Reserved;
}Component/* Glyph flags*/;
