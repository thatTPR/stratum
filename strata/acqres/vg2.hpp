#include <cmath>
#include <stdint.h>
#include <lib/glm/glm.hpp>
#include <acqres/source.hpp>


struct animateMotion : prop{
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int valuesSize;
    glm::dmat4 values; // Values to animate over; // xy: dpos : zw :rotation(size)

};
struct animateTransform : prop{
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int index_size;
    int index;
    int valuesSize;
    glm::dmat4 values; // 
    
};

/*
struct striate : prop{
    glm::dvec2 center;
    float curl ; // means nothin;
    float theta; // Direction of striation 
    bool radial; // Theta now means 
    glm::dvec2 strokeWidths;
    glm::dvec2 straightness;
    

};*/



glm::dvec4 rgba16itorgbaf(glm::uvec4 s){vec4 t = s.xyzw ;t= t/0xFF; };
struct filt {
    glm::dvec4 col;
    float weight;
    float stabilize;
};
enum fe {
    color=1,
    striate=2,
    fibrate=3,
    cybrate=4,
    perlin=5,
    simplex=6,
    convolve=7,
    turbulence=8
};
struct shape_at ;
struct shape_atv { // TODO make fe all one vector and adapt index, also add ats to g and add feRGBA glm::dmat4
    int animateMotionSize;
std::vector< animateMotion> animateMotions;
    int animateTransformSize;
std::vector< animateTransform> animateTransforms;
    glm::dvec4 stroke;
    double stroke_width; // Relative to size
    glm::dvec4 fill; // rgba 
    glm::dmat4 gradient ; //x:col  y: dir z:
    glm::dmat4 radialGradient; // xy center , zw theta=0
    
    // All in order of application but indexes first make index index // TODO maybe curl
    int feSize;  // TODO mul in fourths according to sparse idmat
std::vector< int> feIndex;
std::vector< glm::mat4> fe;
 shape_atv(shape_at s);
static tinygltf::Value::Object getgltf(shape_at at){
        tinygltf::Value::Object ats;
         if(at.animateMotionSize>0){
            std::vector<tinygltf::Value> animm;
            for(int i = 0 ; i < at.animateMotionSize ; i++){
                animMo["dur"] = tinygltf::Value(at.animateMotion[i].dur) ;
                animMo["begin"] = tinygltf::Value(at.animateMotion[i].begin) ;
                animMo["end"] = tinygltf::Value(at.animateMotion[i].end) ;
                std::vector<tinygltf::Value> vals;
                animMo["values"] =tinygltf::Value(getmatgltfv<glm::dmat4>(at.animateMotion[i].values)) ;
                animm.push_back(tinygltf::Value(animMo));
            };
            ats["animateMotion"] = tinygltf::Value(animm);
        };
        if(at.animateTransformSize>0){
            std::vector<tinygltf::Value> animt;
            for(int i = 0 ; i < at.animateTransformSize ; i++){
                animTr["dur"] = tinygltf::Value(at.animateTransform[i].dur) ;
                animTr["begin"] = tinygltf::Value(at.animateTransform[i].begin) ;
                animTr["end"] = tinygltf::Value(at.animateTransform[i].end) ;
                animTr["index"] = tinygltf::Value(at.animateTransform[i].index);
                animTr["values"] = tinygltf::Value(getmatgltfv<glm::dvec4>(at.animateTransform[i].values));
                animt.push_back(tinygltf::Value(animTr));
            };
            ats["animateTransform"] = tinygltf::Value(animt);
        };
            ats["stroke"] = tinygltf::Value(getvecgltfv<glm::dvec4>(at.stroke));
            ats["strokeWidth"] = tinygltf::Value(at.strokeWidth);
            ats["fill"] = tinygltf::Value(getvecgltfv<glm::dvec4>(at.fill));
            ats["gradient"] = tinygltf::Value(getvecgltfv<glm::dvec4>(at.gradient));
            ats["radialGradient"] = tinygltf::Value(getvecgltfv<glm::dvec4>(at.radialGradient));
            ats["feSize"] = tinygltf::Value(at.feSize);
            std::vector<tinygltf:Value> fei;
            for(int i=0;i<at.feSize;i++){fei.push_back(tinygltf::Value(at.feIndex[i]));};
            ats["feIndex"] = tinygltf::Value(fei);
            fei.clear()
            for(int i=0;i<at.feSize;i++){fei.push_back(getmatgltfv<glm::dmat4>(at.fe[i]));}
            ats["fe"]=tinygltf::Value(fei);
            return ats;          
    };
     static shape_atv getgltf(tinygltf::Value ats) {
        shape_atv s;
        std::vector<tinygltf::Value> animm ; animm = vals["animateMotion"].Get<tinygltf::Value::Array>();int sizem=0;
        for(tinygltf::Value t : animm){ 
            animateMotion i;
            i.dur = t["dur"].GetNumberAsDouble();
            i.begin = t["begin"].GetNumberAsDouble();
            i.end = t["end"].GetNumberAsDouble();
            i.values= getmat<glm::dmat4>(t["values"]) ; 
            s.animateMotions.push_back(i);sizem++;
        };
        delete animm; s.animateMotionSize = sizem;sizem=0
        std::vector<tinygltf::Value> animt ; animt = vals["animateTransform"].Get<tinygltf::Value::Array>();
        for(tinygltf::Value t : animt){  
            animateTransform i;
            i.dur = t["dur"].GetNumberAsDouble();
            i.begin = t["begin"].GetNumberAsDouble();
            i.end = t["end"].GetNumberAsDouble();
            i.index = t["index"].GetNumberAsInt();
            i.values= getmat<glm::dmat4>(t["values"]) ; 
            s.animateTransforms.push_back(i);sizem++;
        };
        s.animateTransformSize=sizem;
        s.stroke   = getvec<glm::dvec4>(ats["stroke"])
        s.strokeWidth   = ats["strokeWidth"].GetNumberAsDouble();
        s.fill   = getvec<glm:dvec4>(ats["fill"]);
        s.gradient   = getvec<glm::dvec4>(ats["gradient"]);
        s.radialGradient   = getvec<glm::dvec4>(ats["radialGradient"]);

        tinygltf::Value::Array fei =ats["feIndex"].Get<tinygltf::Value::Array>() ;sizem=0;
        for(tinygltf::Value v : fei){s.feIndex[sizem] = getmat<glm::dmat4>(v);  sizem++;};
        s.feSize=sizem; 
        s.fe.resize(s.feSize);
        fei = ats["fe"].Get<tinygltf::Value::Array>() ; sizem=0
        for(tinygltf::Value v: fei){s.fe[i] = getmat<glm::dmat4>(fei[sizem]); sizem++;};
        return s;    
    };
    shape_atv(shape_at sat);

};
#ifndef FEMAGIC
#define FEMAGIC 20000
#endif
glm::dmat4 feMagic(glm::dmat4 p, fe s){
    glmd::dmat4 s = p; s.x.w=(s.x.w)%1+((s.x.w)-(s.x.w)%1)*FEMAGIC+s;
    return s;
};
fe feMagic(glm::dmat4 p){
    double t = p.x.w;
    int s = (int)t;
    s = s%FEMAGIC ;
    return (fe)s;
};
struct shapev {
    glm::dvec2 pos;
    shape_atv at;
    tinygltf::Value getgltf(shapev shape){
    #define SHAPEGETGLTFV(name) \
        o["pos"] = getvecgltfv<glm::dvec2>(name.pos);\
        o["at"] = shape_atv::getgltf(name.at);\


    };
    shapev get(tinygltf::Value::Object o){
        #define SHAPEGET(name) \
        name.pos=tinygltf::Value(getvec<glm::dvec2>(o["pos"])); \
        name.at = shape_atv::get(o["at"]); \
        
    };
    

};
struct polyline;
struct polylinev : shapev {
    int ptSize ;
std::vector< glm::dvec2> pts;
    virtual auto& operator[](int index){
        if(index<=0){return this->at(index);
        return this->pts[index-1];
        };
    };

    static  tinygltf::Value getgltf( polyline PolyLine){
            tinygltf::Value::Object  o;
            SHAPEGETGLTFV(PolyLine)

            o["pos"] = tinyglf::Value(getvecgltfv<glm::dvec2>(PolyLine.pos));
        if(PolyLine.ptSize>0) {
                std::vector<tinygltf::Value> v;
            for(int i = 0 ; i<PolyLine.ptsize;i++){
                v.push(tinygltf::Value(tinygltf::Value(getvecgltfv<glm::dvec2>(PolyLine.pts[i])));
            };
            o["pts"] = tinygltf::Value(v); tinygltf::Value;
            o["attributes"] = tinygltf::Value(shape_atv::getgltfv(PolyLine.at));
            return tinylgtf::Value(o);
        };
    };
    static polylinev get(tinygltf::Value o){
        polylinev pl;
        SHAPEGET(pl)
        pl.ptSize=tinygltf::Value(o["ptSize"]);
        for(tinygltf::Value a : o["pts"].Get<tinygltf::Value::Array>()){
            pl.pts.push_back(getvec<glm::dvec2>(a));
        };
        return pl;
    };
    polylinev(polyline s);
};
struct ellipse
struct ellipsev : shapev {
    double r; int8_t size;
    glm::dmat4x2 foci; // radi
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);}
        switch(index)
        case 1 : {return rads.x ;};
        case 2 : {return rads.y ;};
        case 3 : {return rads.z ;};
        case 4 : {return rads.w ;};
    }; 
     static tinygltf::Value writeEllipse( ellipse Ellipse){
        tinygltf::Value::Object  o;
        SHAPEGETGLTFV(Ellipse)
        o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Ellipse.pos.x),tinygltf::Value(Ellipse.pos.y)});
        o["attributes"] = tinygltf::Value(shape_atv::getgltfv(Ellipse.at));
        o["size"] = tinygltf::Value(Ellipse.size);
        o["foci"] = tinyglf::Value(getmatgltfv<glm::dmat4>(Ellipse.foci));
        o["r"] = tinyglf::Value(Ellipse.r);
        return tinygltf::Value(o)
    };
    static ellipsev get(tinygltf::Value o){
        ellipsev e;
        SHAPEGET(e)

        e.size=o{"size"}.GetNumberAsInt();
        e.r = o["r"].GetNumberAsDouble();
        e.foci = getvec<glm::dmat4x2>(o["foci"]); return e;
    };
    ellipsev(ellipse s);
};
struct rect;
struct rectv : shapev {
    glm::dvec2 d; // (w,h<center>)
    float rx; // corner radius;(0-1<0 means normal 1 means rect is circle>)
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);
        switch(index){
        case 1 : {return d.x };
        case 2 : {return d.y };
        case 3 : {return rx };
        };
        };
    
    static tinygltf::Value getgltf( rect Rect){
            tinygltf::Value::Object  o;
            SHAPEGETGLTFV(Rect)
            o["d"] = tinygltf::Value(getvecgltfv<glm::dvec2>(Rect.d));
            o["rx"] = tinygltf::Value(Rect.rx);
            return tinygltf::Value(o);
    };
    static rectv get(tinygltf::Value o){
        rectv r;
        SHAPEGET(r)
        r.rx = tinygltf::Value(o["rx"]);
        r.d = tinygltf::Value(getvec<glm::dvec2>(o["d"]));
        return r;
    };
    rectv(rect s);
};
struct path;
struct pathv :shapev {// Absolute values;

    int ptlistSize;// total number of pts
    std::vector<pathpt> index;
    std::vector< glm::dvec2> ptlist; //xy is pt 
    auto& operator[](glm::uvec2 index){ 
        if(index.x<=0){return this->at(index);}
        switch(index.x){
            case 1 : return this->cubic[index.y];
            case 2 : return this->cubic[index.y];
            case 3 : return this->cubic[index.y];
            case 4 : return this->cubic[index.y];
        };
    }; 
    auto& operator[](glm::ivec2 index){ 
        if(index.x<=0){return this->at(index);}
    return this->operator[](glm::uvec2(glm::abs(index.xy)));
    }; 
    static tinygltf::Value getgltf( path Path){ // TODO fix
        tinygltf::Value::Object  o;
        SHAPEGETGLTFV(Rect)
        o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Ellipse.pos.x),tinygltf::Value(Ellipse.pos.y)});
        o["text"] = tinygltf::Value(Path.text)
        o["attributes"] = tinygltf::Value(shape_atv::getgltfv(Path.at));
        std::vector<tinygltf::Value> plist,index;
        for(int i =0 ; i< Path.ptlistSize ; i++)
        {
                ptlist.push_back(tinygltf::Value(getvecgltfv<glm::dvec2>(Path.ptlist[i])));
                index.push_back(tinygltf::Value(Path.index[i]));
        };
        o["ptlist"]=tinygltf::Value(ptlist);
        o["index"]=tinygltf::Value(index);
        return tinygltf::Value(o);
        ;};
    static pathv get(tinygltf::Value o){
        pathv p;
        SHAPEGET(p)
        p.pos=getvec<glm::dvec2>(o["pos"]);
        p.at =shape_atv::getgltfv(o["attributes"]);
        for(tinygltf::value s : o["ptlist"]){
            p.ptlist.push_back(getvec<glm::dvec2>(s));
        };
        return p;
    };
    pathv(path s);
   
};
#define PTMAGIC 2000
#define CUBIC 0,
#define QUAD 1,
#define LINE 2,
double fract(double s){return s - std::floor(s);};  
glm::dvec2 ptpmagic(glm::dvec2 p , int8_t g){ // Stays at 
    glm::dvec2 s = p;
    s.y=(fract(s.y))+std::floor(s.y)*PTMAGIC+g;
    return s;
};
int8_t ptpmagic(glm::dvec2 p ){ // Stays at 
    int8_t PT;    glm::dvec2 s = p;
         int PT=int(std::floor(s.y))%PTMAGIC;
    return PT;
};
void ptmagic(glm::dvec2& p){
    p.y = std::floor(p.y)/PTMAGIC + fract(p.y);
};
struct textpath;
struct textpathv : shapev {
    uint8_t font;
    std::string text;
    pathv p ;
     
    static tinygltf::Value getgltf( textpath TextPath){
        tinygltf::Value::Object  o;
        SHAPEGETGLTFV(TextPath)
        o["font"] = tinygltf::Value(TextPath.font);
        o["text"] = tinygltf::Value(TextPath.text);
        o["path"] =  tinygltf::Value(pathv::getgltf(TextPath.p););return tinygltf::Value(o);
    static textpathv get(tinygltf::Value o){
        textpathv tp;
        SHAEGET(tp)
        tp.font  =o{"font"}.GetNumberAsInt();
        tp.text = o["text"].Get<std::string>();
        tp.p = pathv::get(o["path"]);return tp;};
   textpathv(textpath s);
};
struct g;
struct gv : shapev , prop {
    int size;
std::vector< glm::uvec2> index;
 static tinygltf::Value getgltf(g el){
        tinygltf::Value::Object o ;
        SHAPEGETGLTFV(el)
              o["size"]=tinygltf::Value(el.size);
              o["index"]=(std::vector<tinygltf>({tinygltf::Value( el.index[i].x) , tinygltf::Value( el.index[i].y)}));
            return tinygltf::Value(o);
        
    static gv read_g(tinygltf::Value::Object o){
        gv gr;
        SHAPEGET(gr)
        gr.size = o["size"].getNumberAsInt();
        std::vector<tinygltf::Value> array = o["index"].Get<tinygltf::Value::Array>();;
        for(tinygltf::Value a : array){
            glm::uvec2 ind  = getvec<glm::uvec2>(a) ;
            gr.index.push_back(ind)
        };
        return gr;
    };
    gv(g s);
};
struct vg;
struct vgv : shapev , prop { // Size is 1,1 for 
    std::string name;
    int gsize; 
std::vector< gv> gs;

    int polyLineSize;
std::vector< polylinev> polylines;
    int rectsSize;
std::vector< rectv> rects;
    int ellipsesSize;
std::vector< ellipsev> ellipses;
    int pathsSize;
std::vector< pathv> paths;
    int textpathsSize;
std::vector< textpathv> textpaths;
    int indexSize;
std::vector< glm::uvec2> index; // x shape, y pos; // Starting from 1 0 being groups
    tinygltf::Value getgltf(vg Vg  ){// TODOdo better
        tinygltf::Value::Object o;
        SHAPEGETGLTFV(Vg)

        o["name"]=tinygltf::Value(Vg.name);

        int size;
        #define GETVGELTF(name,type,size) \
        tinygltf::Value::Array arr ; size =0\
        for( type s: Vg.name  ){ \
            arr.push_back(type::getgltf(s));size++;\
        }; \
        b[#name] = arr;o[#size]=tinygltf::Value(size); \

        GETVGLTF(gs,gv,gsize)
        GETVGLTF(polylines, polylinev, polyLineSize)  
        GETVGLTF(rects, rectv, rectsSize)  
        GETVGLTF(ellipses, ellipsev, ellipsesSize)  
        GETVGLTF(paths, pathv, pathsSize)  
        GETVGLTF(textPaths, textPathv, textPathsSize)  
       
        std::vector<tinygltf::Value> ind; size=0;
        for(int i = 0; i<Vg.indexSize;i++){
            ind.push_back(tinygltf::value(Vg.index[i];););size++;
        }; ;b["index"] = tinygltf::Value(ind);o["indexSize"]=tinygltf::Value(size);return ob;
        };
    vgv read(tinygltf::Value::Object ob){
        vgv o;
        SHAPEGET(o)

        o.name = ob["name"].Get<std::string>();
        o.gsize = ob["gsize"].GetNumberAsInt();

        #define GETGVGLTF(name,type,size)
        o.##size=ob[#size].GetNumberAsInt(); \
        tintgltf::Value::Array arr; \
        for(type s : ob.name){arr.push_back(type::get(s));};\

        GETGVGLTF(gs,gv,gsize)
        GETGVGLTF(polylines, polylinev, polyLineSize)  
        GETGVGLTF(rects, rectv, rectsSize)  
        GETGVGLTF(ellipses, ellipsev, ellipsesSize)  
        GETGVGLTF(paths, pathv, pathsSize)  
        GETGVGLTF(textPaths, textPathv, textPathsSize)  

       
        o.indexSize = ob["indexSize"].GetNumberAsInt();
        tinygltf::Value::Array arr=tinygltf::Value( o["index"]));        
        for(tinygltf::Value::Object s : arr){
         o.index.push_back(getvec<glm::uvec2>(s));
        } ;
        return o;
    };  
    vgv(vg sv);
};


/***
 * 
 * 
 */
glm::dvec4 rgba16itorgbaf(glm::uvec4 s){vec4 t = s.xyzw ;t= t/0xFF; };



struct shape_at {
    int animateMotionSize;
    animateMotion* animMotions;
    int animateTransformSize;
    animateTransform* animTransforms;
    glm::dvec4 stroke;
    double stroke_width; // Relative to size
    glm::dvec4 fill; // rgba 
    glm::dvec4 gradient ; // xy zw coords
    glm::dvec4 radialGradient; // xy center , zw theta=0
    
    // All in order of application but indexes first make index index // TODO maybe curl
    int* feIndex;
    int feSize;
    glm::mat4* fe; /*
    int feColorSize;  // TODO mul in fourths according to sparse idmat
    int feStriateSize;
    glm::mat4* feStriates; //x: xy center , z theta ,w dens,  , y: xy foc1, zwfoc2 ,  z: xy strokewidths, zw straightness, w :  colvariation 
    int fePerlinSize;
    glm::mat4* fePerlins; // These are all perlin funcs;
    int feSimplexSize;
    glm::mat4* feSimplexs; // These are all perlin funcs;
    int feConvolveSize;
    glm::mat4* feConvolves;
    int feTurbulenceSize;  
    glm::mat4* feTurbulences;*/
shape_at(shape_atv satv){
this->animateMotionSize=satv.animateMotions.size();this->animateMotions=new animateMotion[satv.animateMotionSize] ; this->animateMotion = satv.animateMotion.data();
this->animateTransformSize = satv.animateTransform.size();this->animateTransforms = new animateTrasform[this->animateTrasformSize] ; this->animateTrasforms = satv.animateTrasform.size();
this->stroke = satv.stroke;
this->stroke_width = satv.stroke_width;
this->fill = satv.fill;
this->gradient = satv.gradient;
this->radialGradient= satv.radialGradient; 
this->feSize=satv.feSize;this->feIndex=new int[satv.feSize];this->feIndex=satv.feIndex.data(); this->fe=satv.fe.size();this->fe=new glm::mat4[this->feSize]; this->fe = satv.fe.data();
};
};
shape_atv::shape_atv(shape_at sat){
this->animateMotionSize = sat.animateMotionSize;this->animateMotions.resize(sat.animateMotionSize);this->animateMotions.data()=sat.animateMotions;
this->animateTransformSize = sat.animateTransformSize;this->animateTransforms.resize(sat.animateTransformSize);this->animateTransforms.data()=sat.animateTransforms;
this->stroke = sat.stroke;
this->stroke_width = sat.stroke_width;
this->fill = sat.fill;
this->gradient = sat.gradient;
this->radialGradient = sat.radialGradient;
this->feSize = sat.feSize;this->feIndex.resize(sat.feSize);this->feIndex.data()=this->feIndex;this->fe.resize(sat.feSize);this->fe.data()=sat.fe;
};

/*
void striate(glm::dvec2 foc0 ,glm::dvec2 foc1, glm::dvec2 strokew, glm::dvec2 strokevar, glm::dvec2 straghtness, glm::dvec2 variation){

};
void app_striate(glm::mat4 feStriate, uint8_t* noms , glm::uvec4[1024][1024] ){
    glm::dvec2 c , foc1 ,foc2 , strokewidth_outAndIn , strokew_variation,straigtness, straightness_variation;
    float theta,dens,strokeOuter;
    theta = feStriate.x.z;
    dens = feStriate.x.w;
    c = feStriate.x.xy;
    foc1 = feStriate.y.xy;
    foc2 = feStriate.y.zw;
    strokeOuter=feStriate.z.x; outerVar=feStriate.z.z; 
    strokeInner=feStriate.z.y; innerVar = feStriate.z.w; 

    // ptxy = 
};
void convolve4(order,glm::mat4 kernelmatrix, float divisor, float  bias){ 
    // targetx targety = floor(orderxy/2) 
    const int targetx= 2; const int targety = 2;
};
void convolve3(order,glm::mat3 kernelmatrix, float divisor, float  bias){ 
    // targetx targety = floor(orderxy/2) 
    const int targetx= 1; const int targety = 1;
};
void convolve2(order,glm::mat2 kernelmatrix, float divisor, float  bias){ 
    // targetx targety = floor(orderxy/2) 
    const int targetx= 1; const int targety = 1;
};
void turbulence();
*/
struct shape {
    glm::dvec2 pos;
    shape_at at;   
    static shapev to_shapev(){
        #define TOSHAPEV res.pos=this->pos;res.at=new shape_atv(this->at);
        shapev res; TOSHAPEV  
        return res;
    };
    shape(shapev s){
        #define TOSHAPE(s) this->pos=s.pos;this->at=new shape_at(s.at);
        TOSHAPE(s)
    };
};
shapev::shapev(shape s){
    TOSHAPEV(s) this.pos=s->pos;this->at=atv_from(s->at);
};
sshape::sshape(shapev s){
#define TOSSHAPE(s) this->pos=s.pos;this->at= s.at[0];
TOSSHAPE(S)
};

struct polyline : shape {
    int ptSize ;
    glm::dvec2* pts;
  
    polyline(polylinev s) {
        TOSHAPE(s)
        this->ptSize = s.ptSize;this->pts=new glm::dvec2[s.ptSize] ; this->pts= s.pts.data();
    };
    virtual auto& operator[](int index){
        if(index<=0){return this->at(index);
        return this->pts[index-1];
        };
    };
};
polylinev::polylinev(polyline s){TOSHAPEV(s) this->ptSize=s.ptSize; this->pts.resize(this->ptSize) ; this->pts.data()=s.pts;};
spolyline::polylinev(polylinev s){TOSSHAPE(s) this->ptSize = s.ptSize; this->pts = new glm::dvec2[s.ptSize];this->pts = s.pts.data();};
struct rect : shape {
    glm::dvec2 d; // (w,h<center>)
    float rx; // corner radius;(0-1<0 means normal 1 means rect is circle>)
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);
        switch(index){
        case 1 : {return d.x };
        case 2 : {return d.y };
        case 3 : {return rx };
        };
    rect(rectv s) {
        TOSHAPE(S) this->d = s.d;this->rx=s.rx;
    }

};
srect::srect(rectv s){
    TOSSHAPE(s) this->d= s.d; this->rx=s.rx;
};
struct ellipse {
    double r; int8_t size;
    glm::dmat4x2 foci; // radi
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);}
        switch(index)
        case 1 : {return rads.x ;};
        case 2 : {return rads.y ;};
        case 3 : {return rads.z ;};
        case 4 : {return rads.w ;};
    }; 
    ellipse(ellipsev s)  {
        TOSHAPE(s) this->r = s.r; this->foci = s.foci;
    };
};
ellipsev::ellipsev(ellipse s)  {
    TOSHAPE(s) this->r = s.r ; this->foci = s.foci;
};

struct path :shape {// Absolute values;

    int ptlistSize;// total number of pts
    pathpt* index;
    glm::dvec2* ptlist; //xy is pt, z is pathpt
    auto& operator[](double index){ 
        if(index<=0){return this->at(index);}

    };
    path(pathv s)  {
        TOSHAPE(s) this->ptlistSize = s.ptlistSize;this->index = new pathpt[s.ptlistSize];this->index=s.index.data();this->ptlist=new glm::dvec2[s.ptlistSize] ; this->index=s.index.data();this->ptlist=s.ptlist.data();};
    };
};
pathv::pathv(path s){ TOSHAPEV(S) this->ptlistSize = s.ptlistSize;this->index.resize(s.ptlistSize);this->index.data()=s.index;this->ptlist.resize(s.ptlistSize);this->ptlist.data()=s.ptlist;};

struct textpath : shape {
    uint8_t font;
    std::string text;
    path p ;
    textpath(textpathv s) { TOSHAPE(S) this->font =s.font;this->text=text;this->p = new path(s.p);} ;
};
textpathv::textpathv(textpath s)  { SHAPE(s) this->font = font  ; this->text = text; this->p= new pathv(s.p) ; };
struct textpathi : shape {
    uint8_t font;
    int* text;
    path p;
    textpath to_textpath(){
        textpath res;res.font=this->font;res.p = this->p;
    };
    textpathi(textpath tp){     this->font = tp.font;this->text=new int[tp.text.size();];for(int i =0 ;i<tp.text.size();i++){this->text[i] = static_cast<int>(tp.text[i]);}this->p = tp.p;}
};
struct g : shape {
    int size;
    glm::uvec2* index;
    g(gv s)  {TOSHAPE(s) this->siz = s.size; this->index = new glm::uvec2[s.size] ; this->index = s.index.data();};
};
gv::gv(g s) {TOSHAPEV(S) this->size=s.size;this->index.resize(s.size);this->index.data()=s.index; };
struct vg : shape { // Size is 1,1 for 
    std::string name;
    int gsize; 
    g* g;
    int polyLineSize;
    polyline* polylines;
    int rectsSize;
    rect* rects;
    int ellipsesSize;
    ellipse* ellipses;
    int pathsSize;
    path* paths;
    int textpathsSize;
    textpath* textpaths;
    int indexSize;
    glm::uvec2* index; // x shape, y pos; // Starting from 1 0 being groups

vg(vgv sv){ this->name=sv.name;
    this->gsize=sv.g.size();this->g = new g[this->gsize]; this->g=sv.g.data();
    this->polyLineSize = sv.polylines.size();this->polylines = new polyline[s.polyLineSize];this->polylines = sv.polylines.data();
   this->rectsSize = sv.rects.size();this->rects = new rects[s.rectsSize];this->rects = sv.rects.data();
   this->ellipsesSize = sv.ellipses.size();this->ellipses = new ellipses[s.ellipsesSize];this->ellipses = sv.ellipses.data();
   this->pathsSize = sv.paths.size();this->paths = new paths[s.pathsSize];this->paths = sv.paths.data();
   this->textpathsSize = sv.textpaths.size();this->textpaths = new textpaths[s.textpathsSize];this->textpaths = sv.textpaths.data();
   this->indexSize = sv.index.size();this->index = new index[s.indexSize];this->index = sv.index.data();  
};
};
vgv::vgv(vg sv){this->name=sv.name;
   this->gsize= sv.gsize;this->g.resize(s.gsize);this->g.data()= sv.g;                
   this->polyLineSize = sv.polyLinesize;this->polyLine.resize(s.polyLineSize);this->polyLine.data() = sv.polylines;                
   this->rectsSize = sv.rectssize;this->rects.resize(s.rectsSize);this->rects.data() = sv.rects;                
   this->ellipsesSize = sv.ellipsessize;this->ellipses.resize(s.ellipsesSize);this->ellipses.data() = sv.ellipses;                
   this->pathsSize = sv.pathssize;this->paths.resize(s.pathsSize);this->paths.data() = sv.paths;                
   this->textpathsSize = sv.textpathssize;this->textpaths.resize(s.textpathsSize);this->textpaths.data() = sv.textpaths;                
   this->indexSize = sv.indexsize;this->index.resize(s.indexSize);this->index.data() = sv.index;               
};
struct vgv_aq : vgv , aqres_prop {
        std::vector<std::string> extensions={"strata_vg_extension"};
    template<typename s>
    inline void vg_el_write(tinygltf::Value::Object* ob, void (*write_func)(s , tinygltf::Value::Object* ) , int size , s* arr , std::string name ) {
        if(s>0){
            std::vector<tinygltf::Value> pls;
          for(int i =0 ; i <size;i++){
                tinygltf::Value::Object o;   
                write_func(Vg.arr[i],&o);
                pls.push_back(tinygltf::Value(o));
          };
         (*ob)[name]=tinygltf::Value(pls);};
    };
   
    tinygltf::value::Object getVgObj(vg Vg){ 
        tinygltf::Value::Object obj;
        this->write(Vg,&obj);
        return obj;
    };
    tinygltf::Value::Object get_ext(){
        tingtlf::Value::Object o;
        o["version"] = tinygltf::Value(100);
        return o;
    };
    void toModel(tinygltf::Model* model,vg Vg){     
            model->extras = tinygltf::Value(this->getVgObj(Vg));
    };
    void toModel(tinygltf::Model* model,vgv Vg){this->toModel(model, new vg(Vg));};

    std::string mimeType="STRATAvg_mime";
    tinygltf::Image makeImage(std::string uri,std::string name=""){
        tinygltf::Image s;s.uri=uri;
        s.mimeType=this->mimeType;
    };
    std::string version = "100"
  std::string generator = "STRATA_ENGINE";
  std::string minVersion = "100";
  std::string copyright =  "";
    void write_file(std::string path, vg Vg ){
        tinygltf::Value::Object obj;
        tinygltf::Model mod;

        this->toModel(&mod,Vg);
        mod.extensionsUsed.push_back(this->extensions[0]);
        mod.extensionsRequired.push_back(this->extensions[0]);
        mod.Asset.version=this->version;
        mod.Asset.generator=this->generator;
        mod.Asset.minVersion=this->minVersion;
        mod.Asset.copyright=this->copyright;
        tinygltf::TinyGltf loader;
        std::string error, warning;
    bool success = loader.WriteGltfSceneToFile(&mod, path, true, true, true, &error, &warning);
    if (!success) {
        std::cerr << "Failed to save glTF file: " << error << std::endl;
    } else {
        std::cout << "Custom extension added successfully!" << std::endl;
    }

    };
    
    vgv read_file(std::string path){
        tinygltf::TinyGltf loader;
        tinygltf::Model m;
        tinygltf::Image
        bool is_s =true;
        std::string err,warn;
        bool success = loader.LoadASCIIFromFile(&m, &err, &warn, path);
        tinygltf::Value::Object ob = m.extras;
        return (this->read(ob));
    };

};


};