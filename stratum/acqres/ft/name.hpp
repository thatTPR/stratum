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
uint8* variable ;
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
uint8* variable ; 
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