#ifndef FTBASE_HPP
#define FTBASE_HPP
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   horizAxisOffset;
Offset16   vertAxisOffset;
}BASE10/* Header, version 1.0*/;
typedef struct {
uint16   majorVersion;
uint16   minorVersion;
Offset16   horizAxisOffset;
Offset16   vertAxisOffset;
Offset32   itemVarStoreOffset;
}BASE11/* Header, version 1.1*/;

typedef struct {
        base10 b10;
        Offset32   itemVarStoreOffset;
         
}basehead;
ACQRES(basehead){
    one((f.b10));
    switch(f.b10.minorVersion){
        case 1 : {one((f.iterVarStoreOffset));};
    };
}
typedef struct {
Offset16   baseTagListOffset;
Offset16   baseScriptListOffset;
}Axis/* table*/;
typedef struct {
uint16   baseTagCount;
Tag*   baselineTags;//[baseTagCount]
}BaseTagList/* table*/;
ACQRES(BaseTagList/* table*/){
one((f.baseTagCount));
arr(f.baselineTags, f.baseTagCount);
 };
USE_ACQRES(BaseTagList/* table*/)

typedef struct {
uint16   baseScriptCount;
BaseScriptRecord*   baseScriptRecords;//[baseScriptCount]
}BaseScriptList/* table*/;
ACQRES(BaseScriptList/* table*/){
one((f.baseScriptCount));
arr(f.baseScriptRecords, f.baseScriptCount);
 };
USE_ACQRES(BaseScriptList/* table*/)

typedef struct {
Tag   baseScriptTag;
Offset16   baseScriptOffset;
}BaseScriptRecord;
typedef struct {
Tag   baseLangSysTag;
Offset16   minMaxOffset;
}BaseLangSys /*record*/;
typedef struct {
Offset16   baseValuesOffset;
Offset16   defaultMinMaxOffset;
uint16   baseLangSysCount;
BaseLangSys*   baseLangSysRecords;//[baseLangSysCount]
}BaseScript ;///*table*/;
ACQRES(BaseScript/* table*/){
one((f.baseValuesOffset));
one((f.defaultMinMaxOffset));
one((f.baseLangSysCount));
arr(f.baseLangSysRecords, f.baseLangSysCount);
 };
USE_ACQRES(BaseScript /*table*/)


typedef struct {
uint16   defaultBaselineIndex;
uint16   baseCoordCount;
Offset16*   baseCoordOffsets;//[baseCoordCount]
}BaseValues /*table*/;
ACQRES(BaseValues/* table*/){
one((f.defaultBaselineIndex));
one((f.baseCoordCount));
arr(f.baseCoordOffsets, f.baseCoordCount);
 };
USE_ACQRES(BaseValues/* table*/)


typedef struct {
Tag   featureTag;
Offset16   minCoordOffset;
Offset16   maxCoordOffset;
}FeatMinMax/* record*/;
typedef struct {
uint16   format;
int16   coordinate;
}BaseCoordFormat1/* table: Design units only*/;
typedef struct {
uint16   format;
int16   coordinate;
uint16   referenceGlyph;
uint16   baseCoordPoint;
}BaseCoordFormat2/* table: Design units plus contour point*/;
typedef struct {
uint16   format;
int16   coordinate;
Offset16   deviceOffset;
}BaseCoordFormat3/* table: Design units plus Device or VariationIndex table*/;

typedef struct  {
        BaseCoordFormat1 f1;
        uint16 referenceGlyph;
        uint16 baseCoordPoint;
        Offset16   deviceOffset;
        BaseCoordFormat2 to2(){BaseCoordFormat2 f; f.format = f1.format;f.coordinate=f1.coordinate;f.referenceGlyph =referenceGlyph;f.baseCoordPoint =baseCoordPoint;return f;  };
        BaseCoordFormat2 to3(){BaseCoordFormat3 f; f.format = f1.format;f.coordinate=f1.coordinate;f.deviceOffset = deviceOffset;return f;};
        
}BaseCoordFormat;
ACQRES(BaseCoordFormat) {
one(f.f1);
switch(f.f1.format){
case 2 : {
    
    one((f.referenceGlypth));
    one((f.baseCoordPoint));
};
case 3 : {
    one((f.deviceOffset));
    };
} ;
};
USE_ACQRES(BaseCoordFormat)

typedef struct {
Offset16   minCoordOffset;
Offset16   maxCoordOffset;
uint16   featMinMaxCount;
FeatMinMax*   featMinMaxRecords;//[featMinMaxCount]
}MinMax/* table*/;
ACQRES(MinMax/* table*/){
one((f.minCoordOffset));
one((f.maxCoordOffset));
one((f.featMinMaxCount));
arr(f.featMinMaxRecords, f.featMinMaxCount);
 };
USE_ACQRES(MinMax/* table*/)


 typedef struct {
        MinMax d;
        BaseCoordFormat min;
        BaseCoordFormat max;
        BaseCoordFormat* Mincoord ;
        BaseCoordFormat* Maxcoord ;
    }MinMaxBox;
    ACQRES(MinMaxBox) {
        one((f.d)) ;
        offone((f.min) ,f.d.minCoordOffset) ; 
        offone((f.max) ,f.d.maxCoordOffset) ;
        arr(f.Mincoord,f.d.featMinMaxCount);
        arr(f.Maxcoord,f.d.featMinMaxCount);
        for(int i = 0 ; i < f.d.featMinMaxCount){
            offone((f.Mincoord[i]),f.d.featMinMaxRecords[i].minCoordOffset);
            offone((f.Maxcoord[i]),f.d.featMinMaxRecords[i].maxCoordOffset);
        };
    };


typedef struct {
        BaseScript baseScript ;
        BaseValues baseValues;
        BaseCoordFormat* baseCoordValues;
        MinMaxBox* minMax;
    }BaseScriptBox;
    ACQRES(BaseScriptBox) {
        one((f.baseScript));
        offone((f.baseValues),f.baseScript.baseValuesOffset);
        for(int i = 0 ; i < f.baseValues.baseCoordCount){
            offone((f.baseCoordValues[i]),f.baseScript.baseValuesOffset + f.baseValues.baseCoordOffsets[i]);
        };
        for(int i = 0 ; i < f.baseScript.baseLangSysCount;i++){
            one((f.minMax[i]))
        };
    };
    USE_ACQRES(BaseScriptBox)
    typedef struct  {
        Axis ax;
        BaseTagList baseTagList;
        BaseScriptList baseScriptList;
        BaseScriptBox* baseScript ; 
        
    }AxisBox;
    ACQRES(AxisBox) {
        one((f.ax));
        if(f.ax.baseTagListOffset != NULL){
            offone((f.baseTagList),f.ax.baseTagListOffset);
        };
        offone((f.baseScriptList),f.ax.baseScriptListOffset);
        for(int i =0 ; i < f.baseScriptList.baseScriptCount;i++){
            offone((f.baseScript[i]),f.baseScriptList.baseScriptRecords[i].baseScriptOffset);
        };
    }
    USE_ACQRES(AxisBox) 
    typedef struct {
        basehead head;
        AxisBox hori ;    
        AxisBox verti ;

    }BASE;
    ACQRES(BASE) {
        one((f.head));
        if(f.head.b10.minorVersion == 1){
            one((f.head.b11.itemVarStoreOffset));
        };
        offone((f.hori),f.head.horiAxisOffset);
        offone((f.hori),f.head.vertAxisOffset);
    };
    USE_ACQRES(BASE)

    #endif