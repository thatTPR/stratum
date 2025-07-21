#ifndef FTNAME_HPP
#define FTNAME_HPP
enum nameId {
    copyright=0
    fontFamily=1,
    fontSubFamily=2,
    uniqueFontID=3,
    fullNameIdentifier=4,
    version=5,
    postScriptName=7,
    Trademark=8,
    manufacturerName=9,
    Designer=10,
    Description=11,
    URLVendor=12,
    URLDesigner=13,
    LicenseInfo=14,
    Reserved=15,
    TypographicFamily=16,
    TypographicSubFamily=17,
    CompatibleFull=18,// MacintoshOnly
    SampleText=19,
    PostScriptCID=20,
    WWSFamily=21,
    WWSSubFamily=22,
    LightBackgroundPalette=23,
    DarkBackgroundPalette=24,
    VariationsPostScriptNamePrefix =25
};
typedef struct {
uint16	platformID ;//	Platform ID.
uint16	encodingID ;//	Platform-specific encoding ID.
uint16	languageID ;//	Language ID.
uint16	nameID ;//	Name ID.
uint16	length ;//	String length (in bytes).
Offset16	stringOffset ;//	String offset from start of storage area (in bytes).
   
}NameRecord;

typedef struct {
uint16	length ;//	Language-tag string length (in bytes).
Offset16	langTagOffset ;//	Language-tag string offset from start of storage area (in bytes).
}LangTagRecord;
typedef struct {
uint16	version ;//	Table version number (=0).
uint16	count ;//	Number of name records.
Offset16	storageOffset ;//	Offset to start of string storage (from start of table).
NameRecord*	nameRecord;//[count]	The name records where count is the number of records.

// (Variable)		Storage for the actual string data.
// uint8* variable ;
char* variable;
}name0;
ACQRES(name0){
    one(f.version);
    one(f.count);
    one(f.storageOffset);
    arr(f.nameRecord,f.count);
    size_t str=0 ;
    for(int i=0;i<f.count;i++){str+=f.nameRecord[i].length;};
    if(!f.variable){f.variable = new int8_t[str];}
    offarr(f.variable,f.storageOffset,str);
}
USE_ACQRES(name0)
typedef struct {
uint16	version;//	Table version number (=1).
uint16	count;//	Number of name records.
Offset16	storageOffset;//	Offset to start of string storage (from start of table).
NameRecord*	nameRecord;//[count]	The name records where count is the number of records.
uint16	langTagCount;//	Number of language-tag records.
LangTagRecord*	langTagRecord;//[langTagCount]	The language-tag records where langTagCount is the number of records.

//(Variable)		Storage for the actual string data.
char* variable ; 
}name1;
ACQRES(name1){
    one(f.version);
    one(f.count);
    one(f.storageOffset);
    arr(f.nameRecord,f.count);
    one(f.langTagCount);
    arr(f.langTagRecord,f.langTagCount);
    size_t str=0 ;
    for(int i=0;i<f.count;i++){str+=f.nameRecord[i].length;};
    if(!f.variable){f.variable = new int8_t[str];}
    offarr(f.variable,f.storageOffset,str);    
}
USE_ACQRES(name1)

typedef struct {
uint16 version;
union {
    name0 f0;
    name1 f1;
}f;
     char* getName(uint nameId,,uint16* len){
        switch(version){
            case 0 : {int i;
                for(i=0;i<f.f0.count;i++){
                    if(f.f0.nameRecord[i].nameID==nameId){break;}
                }
                *len = f.f0.nameRecord[i].length; 
            return &(name()+f.f0.nameRecord[i].stringOffset);

            }
            case 1 : {int i;
                for(i=0;i<f.f1.count;i++){
                    if(f.f1.nameRecord[i].nameID==nameId){break;}
                }
                *len = f.f1.nameRecord[i].length; 
            return &(name()+f.f0.nameRecord[i].stringOffset);
            }
        }
    }
}name; 
ACQRES(name){
    one(f.version);
    switch (f.version)
    {
    case 0:{one(f.f.f0);};
    case 1:{one(f.f.f1);};
    }
}
USE_ACQRES(name)
#endif