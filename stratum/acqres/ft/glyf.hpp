
	
enum SimpleGlyphFlags{
ON_CURVE_POINT=0x01,//Bit 0: If set, the point is on the curve; otherwise, it is off the curve.
X_SHORT_VECTOR=0x02,//Bit 1: If set, the corresponding x-coordinate is 1 byte long, and the sign is determined by the X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR flag. If not set, its interpretation depends on the X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR flag: If that other flag is set, the x-coordinate is the same as the previous x-coordinate, and no element is added to the xCoordinates array. If both flags are not set, the corresponding element in the xCoordinates array is two bytes and interpreted as a signed integer. See the description of the X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR flag for additional information.
Y_SHORT_VECTOR=0x04,//	Bit 2: If set, the corresponding y-coordinate is 1 byte long, and the sign is determined by the Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR flag. If not set, its interpretation depends on the Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR flag: If that other flag is set, the y-coordinate is the same as the previous y-coordinate, and no element is added to the yCoordinates array. If both flags are not set, the corresponding element in the yCoordinates array is two bytes and interpreted as a signed integer. See the description of the Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR flag for additional information.
REPEAT_FLAG=0x08,//	Bit 3: If set, the next byte (read as unsigned) specifies the number of additional times this flag byte is to be repeated in the logical flags array — that is, the number of additional logical flag entries inserted after this entry. (In the expanded logical array, this bit is ignored.) In this way, the number of flags listed can be smaller than the number of points in the glyph description.
X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR=0x10,//	Bit 4: This flag has two meanings, depending on how the X_SHORT_VECTOR flag is set. If X_SHORT_VECTOR is set, this bit describes the sign of the value, with 1 equaling positive and 0 negative. If X_SHORT_VECTOR is not set and this bit is set, then the current x-coordinate is the same as the previous x-coordinate. If X_SHORT_VECTOR is not set and this bit is also not set, the current x-coordinate is a signed 16-bit delta vector.
Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR=0x20,//	Bit 5: This flag has two meanings, depending on how the Y_SHORT_VECTOR flag is set. If Y_SHORT_VECTOR is set, this bit describes the sign of the value, with 1 equaling positive and 0 negative. If Y_SHORT_VECTOR is not set and this bit is set, then the current y-coordinate is the same as the previous y-coordinate. If Y_SHORT_VECTOR is not set and this bit is also not set, the current y-coordinate is a signed 16-bit delta vector.	
OVERLAP_SIMPLE=0x40,//Bit 6: If set, contours in the glyph description could overlap. Use of this flag is not required — that is, contours may overlap without having this flag set. When used, it must be set on the first flag byte for the glyph. See additional details below.
Reserved=0x80
};
int16 _numberOfContours ;
typedef struct {
uint16*   endPtsOfContours;//[numberOfContours]
uint16   instructionLength;
uint8*   instructions;//[instructionLength]
uint8*   flags;// [variable]

/*uint16 or*/ int8   *xCoordinates;
/*uint16 or*/ int8   *yCoordinates;
// No ldwr
uint16 flagNum;
uint16 xCoordNum;
uint16 yCoordNum;

}SimpleGlyph;
size_t size<SimpleGlyph>(SimpleGlyph& f){
   size_t s = _numberOfCountours * sizeof(f.endPtsOfContours[0]);
   s+= sizeof(f.instructionsLength);
   s+= sizeof(f.instructions[0])* f.instructionLength;
   s+=sizeof(f.flags[0])* f.flagNum;
   s+=sizeof(f.xCoordinates[0])* f.xCoordNum;
   s+=sizeof(f.yCoordinates[0])* f.yCoordNum;
   return s;
};
void ld<SimpleGlyph>(SimpleGlyph& f,std::ifstream* fi){
ld(f.endPtsOfCountours,_numberOfCountours,fi);
ld(f.instructionLength,fi);
ld(f.instructions,f.instructionLength,fi);
int lastEndPt = f.endPtsOfContours[_numberOfCountours-1];
f.flags = new uint8[lastEndPt];
f.flagNum = 0;
f.xCoordNum = 0;f.yCoordNum = 0;
for(int i=0;i<lastEndPt;i++){
   ld(f.flags[i],fi);   
   if(f.flags[i] & X_SHORT_VECTOR){ f.xCoordNum++; } 
   else {if(lastFlag & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR){};
   else {f.xCoordNum+=2}; }
   if(f.flags[i] & Y_SHORT_VECTOR) {f.yCoordNum++; }
   else {if(lastFlag & Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR){};
   else{f.yCoordNum+=2};}
   if(f.flags[i] & OVERLAP_SIMPLE) {}
   if(f.flags[i] & REPEAT_FLAG){
      i++;
      if(i>=lastEndPt){throw std::runtime_error("Font Read error: SimpleGlyph flags array too big");}
      ld(f.flags[i],fi);   
      };
   f.flagNum++;
   }
   f.xCoordinates = new int8[f.xCoordNum] ;uint fit=0;
for(int i =0 ; i<f.xCoordNum;i++){
   
   if(f.flags[fit] & X_SHORT_VECTOR){ 
      if(f.flags[fit] & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR) {} 
    else {f.xCoordinates[i]= -f.xCoordinates[i];}}
    else {if(f.flags[fit] & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR){f.xCoordinates[i]=f.xCoordinates.[i-1];}
         else{ld(f.xCoordinates[i],fi);
            ld(f.xCoordinates[i],fi)
         }}
         fit++;
}
   fit=0;
   for(int i=0;i<f.yCoordNum;i++){
      if(f.flags[fit] & Y_SHORT_VECTOR){ ld(f.yCoordinates[i],fi);
      if(f.flags[fit] & Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR) {} 
    else {f.yCoordinates[i]= -f.yCoordinates[i];}}
    else {if(f.flags[fit] & Y_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR){f.yCoordinates[i]=f.yCoordinates.[i-1];}
         else{ld(f.yCoordinates[i],fi);
            ld(f.yCoordinates[i],fi)
         }}
         fit++;
   }

};
template<> void wr<SimpleGlyph>(SimpleGlyph& f, std::ofstream* fi){
   wr(f.endPtsOfCountours,_numberOfCountours,fi);
   wr(f.instructionLength,fi);
   wr(f.instructions,f.instructionLength,fi);
   wr(f.flags,f.flagNum);
   uint16 x,y;x=0;y=0;
   for(int i =0 ; i<f.flagNum;i++){wr(f.flags[i],fi);}
   for(int i=0 ; i< f.xCoordNum;i++){wr(f.xCoordinates[i],fi);}
   for(int i=0 ; i< f.yCoordNum;i++){wr(f.yCoordinates[i],fi);}
};
enum ComponentGlyphflags {
   ARG_1_AND_2_ARE_WORDS = 0x0001,    // Bit 0: If this is set, the arguments are 16-bit (uint16 or int16); otherwise, they are bytes (uint8 or int8).
   ARGS_ARE_XY_VALUES = 0x0002,       // Bit 1: If this is set, the arguments are signed xy values; otherwise, they are unsigned point numbers.
   ROUND_XY_TO_GRID = 0x0004,         // Bit 2: If set and ARGS_ARE_XY_VALUES is also set, the xy values are rounded to the nearest grid line. Ignored if ARGS_ARE_XY_VALUES is not set.
   WE_HAVE_A_SCALE = 0x0008,          // Bit 3: This indicates that there is a simple scale for the component. Otherwise, scale = 1.0.
   MORE_COMPONENTS = 0x0020,          // Bit 5: Indicates at least one more glyph after this one.
   WE_HAVE_AN_X_AND_Y_SCALE = 0x0040, // Bit 6: The x direction will use a different scale from the y direction.
   WE_HAVE_A_TWO_BY_TWO = 0x0080,     // Bit 7: There is a 2 by 2 transformation that will be used to scale the component.
   WE_HAVE_INSTRUCTIONS = 0x0100,     // Bit 8: Following the last component are instructions for the composite glyph.
   USE_MY_METRICS = 0x0200,           // Bit 9: If set, this forces the aw and lsb (and rsb) for the composite to be equal to those from this component glyph. This works for hinted and unhinted glyphs.
   OVERLAP_COMPOUND = 0x0400,         // Bit 10: If set, the components of the compound glyph overlap. Use of this flag is not required — that is, component glyphs may overlap without having this flag set. When used, it must be set on the flag word for the first component. Some rasterizer implementations may require fonts to use this flag to obtain correct behavior — see additional remarks, above, for the similar OVERLAP_SIMPLE flag used in simple-glyph descriptions.
   SCALED_COMPONENT_OFFSET = 0x0800,  // Bit 11: The composite is designed to have the component offset scaled. Ignored if ARGS_ARE_XY_VALUES is not set.
   UNSCALED_COMPONENT_OFFSET = 0x1000,// Bit 12: The composite is designed not to have the component offset scaled. Ignored if ARGS_ARE_XY_VALUES is not set.
   Reserved = 0xE010	                 // Bits 4, 13, 14 and 15 are reserved: set to 0.
  };

typedef struct {
uint16   flags;
uint16   glyphIndex;
/*uint8, int8 , uint16 or */int16   argument1;
/*uint8, int8 , uint16 or */int16   argument2;
// [transform data]   ;
}ComponentGlyphg;
ACQRES(CGlyph){
one(f.flags);
      one(f.glyphIndex);
      if(f.flags & ARG_1_AND_2_ARE_WORDS){if(f.flags & ARGS_ARE_XY_VALUES){one(f.argument1),one(f.argument2);}
                                          else {uint16 arg1= f.argument1; uint16 arg2=f.argument1;one(arg1);one(arg2);f.argument1=arg1;f.argument2=arg2;};}
      else {if(f.flags & ARGS_ARE_XY_VALUES){
         int8 arg1=f.argument1 ;int8 arg2=f.argument2;one(arg1),one(arg2);f.argument1 = arg1;f.argument2=arg2;};
         else {uint8 arg1=f.argument1 ;uint8 arg2=f.argument2;one(arg1),one(arg2);f.argument1 = arg1;f.argument2=arg2;}
      }
}
USE_ACQRES(CGlyph)
typedef struct {
   CGlyph* var;
   uint16 numInstr;
   uint8* instr; //[numInstr]
}ComponentGlyph;
ACQRES(ComponentGlyph){
   int index=0;
   do {
      one(f.var[i]);
      index++;
   }while(f.flags & MORE_COMPONENTS);
   if(f.flags& WE_HAVE_INSTRUCTIONS){
      one(f.numInstr);
      arr(f.instr,f.numInstr);
   }
}
USE_ACQRES(ComponentGlyph)
typedef struct {
int16   numberOfContours;
int16   xMin;
int16   yMin;
int16   xMax;
int16   yMax;
union {
   ComponentGlyph cg;
   SimpleGlyph sg;
}glyff;

}glyf;
ACQRES(glyf){
   one(f.numberOfCountours);
   _numberOfCountours = f.numberOfContours;
   one(f.glyphIndex);
   one(f.xMin);
   one(f.yMin);
   one(f.xMax);
   one(f.yMax);

   if(numberOfContours<0){one(f.glyff.cg);};
   else {one(f.glyff.sg);};
};
USE_ACQRES(glyf)