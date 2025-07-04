#ifndef FTPCLT_HPP
#define FTPCLT_HPP
enum fontNumber {
AdobeSystems='A',	
BitstreamInc='B',	    
AgfaCorporation='C',	    
BigelowANDHolmes='H',	    
LinotypeCompany='L',	    
MonotypeTypographyLtd='M'
};
enum styleStructure {
    //Structure (bits 5 – 9)
Solid=0,	 //(normal, black)
Outline=1,	 //(hollow)
Inline=2,	 //(incised, engraved)
Contour=3,	//, edged (antique, distressed)
Solidwithshadow=4,	
Outlinewithshadow=5,	
Inlinewithshadow=6,	
Contourshadow=7,	
Pattern=8,	 
Pattern1=9,	 //(when more than one pattern)
Pattern2=10,	 //(when more than two patterns)
Pattern3=11,	 //(when more than three patterns)
Patternshadow=12,	
Patternshadow1=13,	// (when more than one pattern or shadow)
Patternshadow2=14,	// (when more than two patterns or shadows)
Patternshadow3=15,	// (when more than three patterns or shadows)
Inverse=16,	
Inversewithborder=17,	
reserved=18,	
reserved=31
};


enum styleWidth{// (bits 2 – 4)
normal=0,	
condensed=1,	
compressed=2,	
extracompressed=3,	
ultracompressed=4,	
reserved=5,	
expanded=6,	
extraexpanded=7	
};
enum stylePosture{\\ (bits 0 – 1)

0	upright
1	oblique, italic
2	alternate italic (backslanted, cursive, swash)
3	(reserved)
};
enum typeFamily{   
reserved=0,
AgfaCorporation=1,
BitstreamInc=2,
LinotypeCompany=3,
MonotypeTypography=4,
AdobeSystems=5,
fontrepackagers=6,
vendorsofuniquetypefaces=7,
reserved=8 , 
reserved=15 
}
enum CharacterComplement{
	ASCII=31,
	Latin1extensions=30,
	Latin2extensions=29,
	Latin5extensions=28,
	DesktopPublishingExtensions=27,
	AccentExtensions=26,
	PCLExtensions=25,
	MacintoshExtensions=24,
	PostScriptExtensions=23,
	CodePageExtensions=22,
};
enum FileName {
Text='R',
Italic='I',
Bold='B',
BoldItalic='J',
Demibold='D',
DemiboldItalic='E',
Black='K',
BlackItalic='G',
Light='L',
LightItalic='P',
Condensed='C',
CondensedItalic='A',
BoldCondensed='F',
BoldCondensedItalic='H',
Semibold='S',
SemiboldItalic='T'
}
enum StrokeWeight{
UltraThin=-7,	
ExtraThin=-6,	
Thin=-5,	
ExtraLight=-4,	
Light=-3,	
Demilight=-2,	
Semilight=-1,	
regular=0,	
Semibold=1,	
Demibold=2,	
Bold=3,	
ExtraBold=4,	
Black=5,	
ExtraBlack=6,	
UltraBlack=7	
}
enum widthType {
Ultra_Compressed=-5,	
Extra_Compressed=-4,	    
Compressed=-3,	    
Condensed=-2,	    
Normal=0,	    
Expanded=2,	    
Extra_Expanded=3    
}
enum SerifStyle {
Sans_Serif_Square=0,	    
Sans_Serif_Round=1,	    
Serif_Line=2,	    
Serif_Triangle=3,	    
Serif_Swath=4,	    
Serif_Block=5,	    
Serif_Bracket=6,	    
Rounded_Bracket=7,	    
Flair_Serif=8,	    
Script_Nonconnecting=9,	    
Script_Joining=1,0	    
Script_Calligraphic=1,1	    
Script_Broken_Letter=1,2	    
}
typedef struct{
uint16	majorVersion;
uint16	minorVersion;
uint32	fontNumber;
uint16	pitch;// as defd by unitsPerEm field of the 'head' 
uint16	xHeight;
uint16	style;
uint16	typeFamily;
uint16	capHeight;
uint16	symbolSet;
int8	typeface[16];
int8	characterComplement[8];
int8	fileName[6];
int8	strokeWeight;
int8	widthType;
uint8	serifStyle;
uint8	reserved;
}pclt;

#endif