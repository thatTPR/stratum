#ifndef FTOS2_HPP
#define FTOS2_HPP

typedef struct {
// uint16	version;//	0x0005
FWORD	xAvgCharWidth;//	
uint16	usWeightClass;//	
uint16	usWidthClass;//	
uint16	fsType;//	
FWORD	ySubscriptXSize;//	
FWORD	ySubscriptYSize;//	
FWORD	ySubscriptXOffset;//	
FWORD	ySubscriptYOffset;//	
FWORD	ySuperscriptXSize;//	
FWORD	ySuperscriptYSize;//	
FWORD	ySuperscriptXOffset;//	
FWORD	ySuperscriptYOffset;//	
FWORD	yStrikeoutSize;//	
FWORD	yStrikeoutPosition;//	
int16	sFamilyClass;//	
uint8	panose[10];//	
uint32	ulUnicodeRange1;//	Bits 0 – 31
uint32	ulUnicodeRange2;//	Bits 32 – 63
uint32	ulUnicodeRange3;//	Bits 64 – 95
uint32	ulUnicodeRange4;//	Bits 96 – 127
Tag	achVendID;//	
uint16	fsSelection;//	
uint16	usFirstCharIndex;//	
uint16	usLastCharIndex;//	
FWORD	sTypoAscender;//	
FWORD	sTypoDescender;//	
FWORD	sTypoLineGap;//	
UFWORD	usWinAscent;//	
UFWORD	usWinDescent;//	
uint32	ulCodePageRange1;//	Bits 0 – 31
uint32	ulCodePageRange2;//	Bits 32 – 63
FWORD	sxHeight;//	
FWORD	sCapHeight;//	
uint16	usDefaultChar;//	
uint16	usBreakChar;//	
uint16	usMaxContext;//	
uint16	usLowerOpticalPointSize;//	
uint16	usUpperOpticalPointSize;//
}os25;
typedef struct {
// uint16	version
FWORD	xAvgCharWidth;
uint16	usWeightClass;
uint16	usWidthClass;
uint16	fsType;
FWORD	ySubscriptXSize;
FWORD	ySubscriptYSize;
FWORD	ySubscriptXOffset;
FWORD	ySubscriptYOffset;
FWORD	ySuperscriptXSize;
FWORD	ySuperscriptYSize;
FWORD	ySuperscriptXOffset;
FWORD	ySuperscriptYOffset;
FWORD	yStrikeoutSize;
FWORD	yStrikeoutPosition;
int16	sFamilyClass;
uint8	panose[10];
uint32	ulUnicodeRange1;
uint32	ulUnicodeRange2;
uint32	ulUnicodeRange3;
uint32	ulUnicodeRange4;
Tag	achVendID;
uint16	fsSelection;
uint16	usFirstCharIndex;
uint16	usLastCharIndex;
FWORD	sTypoAscender;
FWORD	sTypoDescender;
FWORD	sTypoLineGap;
UFWORD	usWinAscent;
UFWORD	usWinDescent;
uint32	ulCodePageRange1;
uint32	ulCodePageRange2;
FWORD	sxHeight;
FWORD	sCapHeight;
uint16	usDefaultChar;
uint16	usBreakChar;
uint16	usMaxContext;
}os24;
typedef os24 os22;
typedef os24 os23;

typedef struct {
// uint16	version
FWORD	xAvgCharWidth;
uint16	usWeightClass;
uint16	usWidthClass;
uint16	fsType;
FWORD	ySubscriptXSize;
FWORD	ySubscriptYSize;
FWORD	ySubscriptXOffset;
FWORD	ySubscriptYOffset;
FWORD	ySuperscriptXSize;
FWORD	ySuperscriptYSize;
FWORD	ySuperscriptXOffset;
FWORD	ySuperscriptYOffset;
FWORD	yStrikeoutSize;
FWORD	yStrikeoutPosition;
int16	sFamilyClass;
uint8	panose[10];
uint32	ulUnicodeRange1;
uint32	ulUnicodeRange2;
uint32	ulUnicodeRange3;
uint32	ulUnicodeRange4;
Tag	achVendID;
uint16	fsSelection;
uint16	usFirstCharIndex;
uint16	usLastCharIndex;
FWORD	sTypoAscender;
FWORD	sTypoDescender;
FWORD	sTypoLineGap;
UFWORD	usWinAscent;
UFWORD	usWinDescent;
uint32	ulCodePageRange1;
uint32	ulCodePageRange2;
}os21;
typedef struct {
// uint16	version;//
FWORD	xAvgCharWidth;//
uint16	usWeightClass;//
uint16	usWidthClass;//
uint16	fsType;//
FWORD	ySubscriptXSize;//
FWORD	ySubscriptYSize;//
FWORD	ySubscriptXOffset;//
FWORD	ySubscriptYOffset;//
FWORD	ySuperscriptXSize;//
FWORD	ySuperscriptYSize;//
FWORD	ySuperscriptXOffset;//
FWORD	ySuperscriptYOffset;//
FWORD	yStrikeoutSize;//
FWORD	yStrikeoutPosition;//
int16	sFamilyClass;//
uint8	panose[10];//
uint32	ulUnicodeRange1;//
uint32	ulUnicodeRange2;//
uint32	ulUnicodeRange3;//
uint32	ulUnicodeRange4;//
Tag	achVendID;//
uint16	fsSelection;//
uint16	usFirstCharIndex;//
uint16	usLastCharIndex;//
FWORD	sTypoAscender;//
FWORD	sTypoDescender;//
FWORD	sTypoLineGap;//
UFWORD	usWinAscent;//
UFWORD	usWinDescent;//
}os20;

typedef struct {
uint16	version;
union {
    os20 f0;
    os21 f1;
    os22 f2;
    os23 f3;
    os24 f4;
    os25 f5;
}f;
}os2;
ACQRES(os2){
    one(f.version);
    switch (f.version)
    {
    case 0:{one(f.f.f0);};
    case 1:{one(f.f.f1);};
    case 2:{one(f.f.f2);};
    case 3:{one(f.f.f3);};
    case 4:{one(f.f.f4);};
    case 5:{one(f.f.f5);};
}
#endif