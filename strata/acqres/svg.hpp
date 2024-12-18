#include <lib/gltf.h>
#include <stdint.h>
#include <lib/glm/glm.hpp>



struct animateMotionv{
    int dur=1; // ms
    dbl begin=0,end=dur; // ms or event;
    size_t valuesSize;
std::vector<glm::dvec4> values; // Values to animate over; // xy: dpos : zw :rotation(size)

};
struct animateTransformv {
    dbl begin,end,dur; // ms
    size_t index_size;
    int index;
    size_t valuesSize;
std::vector< glm::dvec2> values; // 
};


glm::vec4 rgba16itorgbaf(glm::uvec4 s){vec4 t = s.xyzw ;t= t/0xFF; };

struct shape_atv {
    size_t animateMotionSize;
std::vector< animateMotion> animateMotions;
    size_t animateTransformSize;
std::vector< animateTransform> animateTransforms;
    glm::vec4 stroke;
    double stroke_width; // Relative to size
    glm::vec4 fill; // rgba 
    glm::vec4 gradient ; // xy zw coords
    glm::vec4 radialGradient; // xy center , zw theta=0
    
    // All in order of application but indexes first make index index // TODO maybe curl
    size_t feColorSize;  // TODO mul in fourths according to sparse idmat
std::vector< int> feColorIndex;
std::vector< glm::mat4> feColor;
    int feStriateSize;
std::vector< int> feStriateIndex;
std::vector< glm::mat4> feStriate; //x: xy center , z theta ,w dens,  , y: xy foc1, zwfoc2 ,  z: xy strokewidths, zw straightness, w :  colvariation 
    int feNoiseSize;
std::vector< int> FeNoiseIndex;
std::vector< glm::mat4> feNoise; // These are all perlin funcs;
    size_t feConvolveSize;
std::vector< glm::ivec2> feConvolveIndex; //  xIndex , y order 
std::vector< glm::mat4> feConvolve;
    size_t feTurbulenceSize;  
std::vector< int> feTurbulenceIndex;
    std::vector<glm::mat4> feTurbulence;
};
      
struct shapev {
    glm::dvec2 pos;
    shape_at atrib;
    uint32_t at(int index=-1 ){return this->atrib.stroke ;};
    uint32_t at(int index=-2){return this->atrib.fill;};
    double& at(int index=-3) {return this->atrib.stroke_width;};    
    glm::vec4& at(int index){return this->atrib.gradient[index]}
    auto& at(int index){
        switch(index) {
          case  0 :{return this->atrib.pos};
          case -1 :{return this->atrib.stroke };
          case -2 :{return this->atrib.fill;};
          case -3 :{return this->atrib.stroke_width;};
          case -4 :{return this->atrib.radialGradient;};
          case -5 :{return this->atrib.gradient;}
        };        
    };
    
    virtual auto& operator[](int index);
};

struct polylinev : shapev {
    size_t ptSize ;
std::vector< glm::dvec2> pts;
    virtual auto& operator[](int index){
        if(index<=0){return this->at(index);
        return this->pts[index-1];
        };
    };
};
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
struct circlev : shapev {
    double r; //  rad
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);
        switch(index){
        case 1 : {return this->d ;};
        };
};
struct ellipsev {
    double r;
    glm::dvec4 foci; // radi
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);}
        switch(index)
        case 1 : {return rads.x ;};
        case 2 : {return rads.y ;};
        case 3 : {return rads.z ;};
        case 4 : {return rads.w ;};
    }; 
};
struct pathv :shapev {// Absolute values;
    size_t cubicSize;
std::vector< glm::dvec2> cubic;
    size_t quadSize;
std::vector< glm::dvec2> quad;
    size_t lineSize;
std::vector< glm::dvec2> line;
    size_t arcSize;
std::vector<glm::dvec2>  arc;
    size_t ptlistSize;// total number of pts
std::vector< glm::uvec2> ptlist; //x is list,y is point in list
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

};
struct textpathv : shapev {
    uint8_t font;
    std::string text;
    path p ;
    
};
struct gv {
    size_t size;
std::vector< glm::uvec2> index;
};
struct svgv  { // Size is 1,1 for 
    size_t gsize; 
std::vector< g> g;

    size_t polyLineSize;
std::vector< polyline> polylines;
    size_t circlesSize;
std::vector< circle> circles ;
    size_t rectsSize;
std::vector< rect> rects;
    size_t ellipsesSize;
std::vector< ellipse> ellipses;
    size_t pathsSize;
std::vector< path> paths;
    size_t textpathsSize;
std::vector< textpath> textpaths;
    size_t indexSize;
std::vector< glm::uvec2> index; // x shape, y pos; // Starting from 1 0 being groups
};
/***
 * 
 * 
 */

// TODO create vector equivalent of these
struct animateMotion{
    int dur=1; // ms
    dbl begin=0,end=dur; // ms or event;
    size_t valuesSize;
    glm::dvec4* values; // Values to animate over; // xy: dpos : zw :rotation(size)

};
struct animateTransform {
    dbl begin,end,dur; // ms
    size_t index_size;
    int index;
    size_t valuesSize;
    glm::dvec2* values; // 
};


glm::vec4 rgba16itorgbaf(glm::uvec4 s){vec4 t = s.xyzw ;t= t/0xFF; };

struct shape_at {
    size_t animateMotionSize;
    animateMotion* animateMotions;
    size_t animateTransformSize;
    animateTransform* animateTransforms;
    glm::vec4 stroke;
    double stroke_width; // Relative to size
    glm::vec4 fill; // rgba 
    glm::vec4 gradient ; // xy zw coords
    glm::vec4 radialGradient; // xy center , zw theta=0
    
    // All in order of application but indexes first make index index // TODO maybe curl
    size_t feColorSize;  // TODO mul in fourths according to sparse idmat
    int* feColorIndex;
    glm::mat4* feColors;
    int feStriateSize;
    int* feStriateIndex;
    glm::mat4* feStriates; //x: xy center , z theta ,w dens,  , y: xy foc1, zwfoc2 ,  z: xy strokewidths, zw straightness, w :  colvariation 
    int feNoiseSize;
    int* FeNoiseIndex;
    glm::mat4* feNoises; // These are all perlin funcs;
    size_t feConvolveSize;
    glm::ivec2* feConvolveIndex; //  xIndex , y order 
    glm::mat4* feConvolves;
    size_t feTurbulenceSize;  
    int* feTurbulenceIndex;
    glm::mat4* feTurbulences;
};
      
/*
void striate(glm::vec2 foc0 ,glm::vec2 foc1, glm::vec2 strokew, glm::vec2 strokevar, glm::vec2 straghtness, glm::vec2 variation){

};
void app_striate(glm::mat4 feStriate, uint8_t* noms , glm::uvec4[1024][1024] ){
    glm::vec2 c , foc1 ,foc2 , strokewidth_outAndIn , strokew_variation,straigtness, straightness_variation;
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
    shape_at atrib;
    uint32_t at(int index=-1 ){return this->atrib.stroke ;};
    uint32_t at(int index=-2){return this->atrib.fill;};
    double& at(int index=-3) {return this->atrib.stroke_width;};    
    glm::vec4& at(int index){return this->atrib.gradient[index]}
    auto& at(int index){
        switch(index) {
          case  0 :{return this->atrib.pos};
          case -1 :{return this->atrib.stroke };
          case -2 :{return this->atrib.fill;};
          case -3 :{return this->atrib.stroke_width;};
          case -4 :{return this->atrib.radialGradient;};
          case -5 :{return this->atrib.gradient;}
        };        
    };
    
    virtual auto& operator[](int index);
};

struct polyline : shape {
    size_t ptSize ;
    glm::dvec2* pts;
    virtual auto& operator[](int index){
        if(index<=0){return this->at(index);
        return this->pts[index-1];
        };
    };
};
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
  

};
struct circle : shape {
    double r; //  rad
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);
        switch(index){
        case 1 : {return this->d ;};
        };
};
struct ellipse {
    double r;
    glm::dvec4 foci; // radi
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);}
        switch(index)
        case 1 : {return rads.x ;};
        case 2 : {return rads.y ;};
        case 3 : {return rads.z ;};
        case 4 : {return rads.w ;};
    }; 
};
struct path :shape {// Absolute values;
    size_t cubicSize;
    glm::dvec2* cubic;
    size_t quadSize;
    glm::dvec2* quad;
    size_t lineSize;
    glm::dvec2* line;
    size_t arcSize;
    glm::dvec2  arc;
    size_t ptlistSize;// total number of pts
    glm::uvec2* ptlist; //x is list,y is point in list
    auto& operator[](int index){ 
        if(index<=0){return this->at(index);}

    };

};
pathv get_pathv(path p){
    pathv pv;
pv.cubicSize = p.cubicSize;pv.cubic.resize(pv.cubicSize); pv.cubic.data()= p.cubic;
pv.quadSize = p.quadSize ; pv.quad.resize(pv.quadSize); pv.quad.data()=p.quad; 
pv.lineSize =p.lineSize; pv.line.resize(pv.lineSize); pv.line.data()=p.line ;
pv.arcSize = p.arcSize;pv.arc.resize(pv.arcSize);pv.arc.data() =p.arc; 
pv.ptlistSize = p.ptlistSize;pv.ptlist.resize(pv.ptlistSize);pv.ptlist.data() = p.ptlist; 
};
path get_pathv(pathv pv){
    path p;
p.cubicSize=pv.cubicSize;p.cubic=new glm::dvec2[p.cubicSize];p.cubic=pv.cubic.data(); 
p.quadSize=pv.quadSize;p.quad=new glm::dvec2[p.quadSize];p.quad=pv.quad.data();  
p.lineSize=pv.lineSize;p.line=new glm::dvec2[p.lineSize];p.line=pv.line.data();  
p.arcSize=pv.arcSize;p.arc=new glm::dvec2[p.arcSize];p.arc=pv.arc.data();  
p.ptlistSize=pv.ptlistSize;p.ptlist=new glm::dvec2[p.ptlistSize];p.ptlist=pv.ptlist.data();  
};

struct textpath : shape {
    uint8_t font;
    std::string text;
    path p ;
    
};
struct textpathi : shape {
    uint8_t font;
    int* text;
    path p;
    textpathi(textpath tp){     this->font = tp.font;this->text=new int[tp.text.size();];for(int i =0 ;i<tp.text.size();i++){this->text[i] = static_cast<int>(tp.text[i]);}this->p = tp.p;}
};
struct g {
    size_t size;
    glm::uvec2* index;
};
struct svg  { // Size is 1,1 for 
    size_t gsize; 
    g* g;

    size_t polyLineSize;
    polyline* polylines;
    size_t circlesSize;
    circle* circles ;
    size_t rectsSize;
    rect* rects;
    size_t ellipsesSize;
    ellipse* ellipses;
    size_t pathsSize;
    path* paths;
    size_t textpathsSize;
    textpath* textpaths;
    size_t indexSize;
    glm::uvec2* index; // x shape, y pos; // Starting from 1 0 being groups
};
textpathi textPath_int_text(textPath tp){
};
// Todo finish conversion funcs;
shape_at at_from(shape_atv satv){
    shape_at sat ;
sat.animateMotionSize=satv.animateMotions.size();sat.animateMotions=new animateMotion[satv.animateMotionSize] ; sat.animateMotion = satv.animateMotion.data();
sat.animateTransformSize = satv.animateTransform.size();sat.animateTransforms = new animateTrasform[sat.animateTrasformSize] ; sat.animateTrasforms = satv.animateTrasform.size();
sat.stroke = satv.stroke;
sat.stroke_width = satv.stroke_width;
sat.fill = satv.fill;
sat.gradient = satv.gradient;
sat.radialGradient= satv.radialGradient
sat.feColorSize=satv.feColor.size();sat.feColorIndex=new int[sat.feColorSize];sat.feColors=new glm::mat4[sat.feColorSize];sat.feColorIndex=satv.feColorIndex.data(); sat.feColors = satv.feColors.data();
sat.feStriateSize=satv.feStriate.size();sat.feStriateIndex=new int[sat.feStriateSize];sat.feStriates=new glm::mat4[sat.feStriateSize];sat.feStriateIndex=satv.feStriateIndex.data(); sat.feStriates = satv.feStriates.data();
sat.feNoiseSize=satv.feNoise.size();sat.feNoiseIndex=new int[sat.feNoiseSize];sat.feNoises=new glm::mat4[sat.feNoiseSize];sat.feNoiseIndex=satv.feNoiseIndex.data(); sat.feNoises = satv.feNoises.data();
sat.feConvolveSize=satv.feConvolve.size();sat.feConvolveIndex=new glm::ivec2[sat.feConvolveSize];sat.feConvolves=new glm::mat4[sat.feConvolveSize];sat.feConvolveIndex=satv.feConvolveIndex.data(); sat.feConvolves = satv.feConvolves.data();
sat.feTurbulenceSize=satv.feTurbulence.size();sat.feTurbulenceIndex=new int[sat.feTurbulenceSize];sat.feTurbulence=new glm::mat4[sat.feTurbulenceSize];sat.feTurbulenceIndex=satv.feTurbulenceIndex.data(); sat.feTurbulences = satv.feTurbulences.data();
return sat;
};
shape_atv atv_from(shape_at sat){
    shape_atv satv
satv.animateMotionSize = sat.animateMotionSize;satv.animateMotions.resize(sat.animateMotionSize);satv.animateMotions.data()=sat.animateMotions;
satv.animateTransformSize = sat.animateTransformSize;satv.animateTransforms.resize(sat.animateTransformSize);satv.animateTransforms.data()=sat.animateTransforms;
satv.stroke = sat.stroke;
satv.stroke_width = sat.stroke_width;
satv.fill = sat.fill;
satv.gradient = sat.gradient;
satv.radialGradient = sat.radialGradient;
satv.feColorSize = sat.feColorSize;satv.feColors.resize(sat.feColorSize);satv.feColors.data()=sat.feColors;
satv.feStriateSize = sat.feStriateSize;satv.feStriates.resize(sat.feStriateSize);satv.feStriates.data()=sat.feStriates;
satv.feNoiseSize = sat.feNoiseSize;satv.feNoises.resize(sat.feNoiseSize);satv.feNoises.data()=sat.feNoises;
satv.feConvolveSize = sat.feConvolveSize;satv.feConvolves.resize(sat.feConvolveSize);satv.feConvolves.data()=sat.feConvolves;
satv.feTurbulenceSize = sat.feTurbulenceSize;satv.feTurbulences.resize(sat.feTurbulenceSize);satv.feTurbulences.data()=sat.feTurbulences;
};
svg svg_from(svgv sv){
    svg s;
    // 
    s.gsize=sv.g.size();s.g = new g[s.gsize]; s.g=sv.g.data();
    // 
    s.polyLineSize = sv.polylines.size();s.polylines = new polyline[s.polyLineSize]; s.polylines = sv.polylines.data();
    s.circlesSize = sv.circles.size(); s.circles = new circle[s.circlesSize] ; s.circles = sv.circles.data();
    s.rectsSize = sv.rects.size(); s.rects = new rects[s.rectsSize];s.rects = sv.rects.data();
    s.ellipsesSize = sv.ellipses.size(); s.ellipses = new ellipses[s.ellipsesSize];s.ellipses = sv.ellipses.data();
    s.pathsSize = sv.paths.size(); s.paths = new paths[s.pathsSize];s.paths = sv.paths.data();
    s.textpathsSize = sv.textpaths.size(); s.textpaths = new textpaths[s.textpathsSize];s.textpaths = sv.textpaths.data();
    s.indexSize = sv.index.size(); s.index = new index[s.indexSize];s.index = sv.index.data();  
    return s;
};

svgv svgv_from(svg sv){
    svgv s;
    s.gsize= sv.gsize ; s.g.resize(s.gsize); s.g.data() ; sv.g;                
    s.polyLineSize = sv.polyLinesize; s.polyLine.resize(s.polyLineSize);s.polyLine.data() = sv.polyLine;                
    s.circlesSize = sv.circlessize; s.circles.resize(s.circlesSize);s.circles.data() = sv.circles;                 
    s.rectsSize = sv.rectssize; s.rects.resize(s.rectsSize);s.rects.data() = sv.rects;                
    s.ellipsesSize = sv.ellipsessize; s.ellipses.resize(s.ellipsesSize);s.ellipses.data() = sv.ellipses;                
    s.pathsSize = sv.pathssize; s.paths.resize(s.pathsSize);s.paths.data() = sv.paths;                
    s.textpathsSize = sv.textpathssize; s.textpaths.resize(s.textpathsSize);s.textpaths.data() = sv.textpaths;                
    s.indexSize = sv.indexsize; s.index.resize(s.indexSize);s.index.data() = sv.index;                
    return s;
};
class svg_prop : public extension_prop {
    const char extensionName[] = "strata_svg_extension" ;

    
    svg parse(tinygltf::TinyGLTF& loader){
        
    };
    
    static tinygltf::Value::Object getAt(shape_at at){
        tinygltf::Value::Object ats;
        if(at.animateMotionSize>0){
            std::vector<tinygltf::Value> animm;
            for(int i = 0 ; i < at.animateMotionSize ; i++){
                animMo["dur"] = tinygltf::Value(at.animateMotion[i].dur) ;
                animMo["begin"] = tinygltf::Value(at.animateMotion[i].begin) ;
                animMo["end"] = tinygltf::Value(at.animateMotion[i].end) ;
                std::vector<tinygltf::Value> vals;
                for(int j = 0 ; j < at.animateMotion[i].valuesSize ; j++){
                    std::vector<tinygltf::Value> val = {
                    tinygltf::Value(at.animateMotion[i].values[j].x) ,
                    tinygltf::Value(at.animateMotion[i].values[j].y) ,
                    tinygltf::Value(at.animateMotion[i].values[j].z) ,
                    tinygltf::Value(at.animateMotion[i].values[j].w) ,
                    } ;
                    vals.push_back(val);
                };
                animMo["values"] = tinygltf::Value(vals);
                animm.push_back(animMo);
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
                std::vector<tinygltf::Value> vals;
                for(int j = 0 ; j < at.animateTransform[i].valuesSize ; j++){
                    std::vector<tinygltf::Value> val = {
                    tinygltf::Value(at.animateTransform[i].values[j].x) ,
                    tinygltf::Value(at.animateTransform[i].values[j].y) ,
                    tinygltf::Value(at.animateTransform[i].values[j].z) ,
                    tinygltf::Value(at.animateTransform[i].values[j].w) ,
                    } ;
                    vals.push_back(val);
                };
                animTr["values"] = tinygltf::Value(vals);
                animt.push_back(animMo);
            };
            ats["animateTransform"] = tinygltf::Value(animt);
        };
            std::vector<tinygltf::Value> stro = {
                tinygltf::Value(at.stroke.x),
                tinygltf::Value(at.stroke.y),
                tinygltf::Value(at.stroke.z),
                tinygltf::Value(at.stroke.w)
            };
            ats["stroke"] = tinygltf::Value(stro);
            ats["strokeWidth"] = tinygltf::Value(at.strokeWidth);
            std::vector<tinygltf::Value> fill = {
                tinygltf::Value(at.fill.x),
                tinygltf::Value(at.fill.y),
                tinygltf::Value(at.fill.z),
                tinygltf::Value(at.fill.w)
            };
            ats["fill"] = tinygltf::Value(fill);

            ats["gradient"] = tinygltf::Value(std::vector<tinygltf::Value>({
                tinygltf::Value(at.gradient.x),
                tinygltf::Value(at.gradient.y),
                tinygltf::Value(at.gradient.z),
                tinygltf::Value(at.gradient.w)
            }));
            ats["radialGradient"] = tinygltf::Value(std::vector<tinygltf::Value>({
                tinygltf::Value(at.radialGradient.x),
                tinygltf::Value(at.radialGradient.y),
                tinygltf::Value(at.radialGradient.z),
                tinygltf::Value(at.radialGradient.w)
            }));            
            if(at.feColorSize>0){
                std::vector<tinygltf::Value> colind;
                std::vector<tinygltf::Value> col ;
            for(int i = 0 ; i < at.feColorSize ; i++){
                std::vector<tinygltf::Value> vals;
                colind.push_back(tinygltf::Value(at.feColorIndex[i]));
                col.push_back(tinygltf::Value(std::vector<tinygltf::Value>({tinygltf::value(at.feColor[i].x),tinygltf::value(at.feColor[i].y),tinygltf::value(at.feColor[i].z),tinygltf::value(at.feColor[i].w)})));
            };
            ats["feColorIndex"] = tinygltf::Value(colind);
            ats["feColor"] = tinygltf::Value(col);
            };
            if(at.feStriateSize>0){
                std::vector<tinygltf::Value> strind;
                std::vector<tinygltf::Value> str ;
            for(int i = 0 ; i < at.feStriateSize ; i++){
                std::vector<tinygltf::Value> vals;
                strind.push_back(tinygltf::Value(at.feStriateIndex[i]));
                str.push_back(tinygltf::Value(std::vector<tinygltf::Value>({tinygltf::value(at.feStriate[i].x),tinygltf::value(at.feStriate[i].y),tinygltf::value(at.feStriate[i].z),tinygltf::value(at.feStriate[i].w)})));
            };
            ats["feStriateIndex"] = tinygltf::Value(strind);
            ats["feStriate"] = tinygltf::Value(str);
            };
            if(at.feNoiseSize>0){
                std::vector<tinygltf::Value> noiind;
                std::vector<tinygltf::Value> noi ;
            for(int i = 0 ; i < at.feNoiseSize ; i++){
                std::vector<tinygltf::Value> vals;
                noiind.push_back(tinygltf::Value(at.feNoiseIndex[i]));
                noi.push_back(tinygltf::Value(std::vector<tinygltf::Value>({tinygltf::value(at.feNoise[i].x),tinygltf::value(at.feNoise[i].y),tinygltf::value(at.feNoise[i].z),tinygltf::value(at.feNoise[i].w)})));
            };
            ats["feNoiseIndex"] = tinygltf::Value(noiind);
            ats["feNoise"] = tinygltf::Value(noi);
            };
            if(at.feConvolveSize>0){
                std::vector<tinygltf::Value> conind;
                std::vector<tinygltf::Value> con ;
            for(int i = 0 ; i < at.feConvolveSize ; i++){
                std::vector<tinygltf::Value> vals;
                conind.push_back(tinygltf::Value(at.feConvolveIndex[i]));
                con.push_back(tinygltf::Value(std::vector<tinygltf::Value>({tinygltf::value(at.feConvolve[i].x),tinygltf::value(at.feConvolve[i].y),tinygltf::value(at.feConvolve[i].z),tinygltf::value(at.feConvolve[i].w)})));
            };
            ats["feConvolveIndex"] = tinygltf::Value(noiind);
            ats["feConvolve"] =      tinygltf::Value(noi);
            };
            if(at.feTurbulenceSize>0){
                std::vector<tinygltf::Value> turind;
                std::vector<tinygltf::Value> tur ;
            for(int i = 0 ; i < at.feConvolveSize ; i++){
                std::vector<tinygltf::Value> vals;
                turind.push_back(tinygltf::Value(at.feTurbulenceIndex[i]));
                tur.push_back(tinygltf::Value(std::vector<tinygltf::Value>({tinygltf::value(at.feTurbulence[i].x),tinygltf::value(at.feTurbulence[i].y),tinygltf::value(at.feTurbulence[i].z),tinygltf::value(at.feTurbulence[i].w)})));
            };
            ats["feTurbulenceIndex"] = tinygltf::Value(turind);
            ats["feTurbulence"] =      tinygltf::Value(tur);
            };
            return ats;          
            
    };
    static void writePolyLine( polyline PolyLine, tinygltf::Value::Object* ob){
            tinygltf::Value::Object  o;
            o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(PolyLine.pos.x),tinygltf::Value(PolyLine.pos.y)});
        if(PolyLine.ptSize>0) {
                std::vector<tinygltf::Value> v;
            for(int i = 0 ; i<PolyLine.ptsize;i++){
                v.push(tinygltf::Value(std::vector<tinygltf::Value>({tinygltf::Value(PolyLine.pts[i].x),tinygltf::Value(PolyLine.pts[i].y)})));
            };
            o["pts"] = tinygltf::Value(v); tinygltf::Value;
            o["attributes"] = tinygltf::Value(this->getAt(PolyLine.at));
            (*ob)["polyline"] = tinygltf::Value(o); 
        };
    };
    static void writeRect( rect Rect,   tinygltf::Value::Object* ob){
            tinygltf::Value::Object  o;
            o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(PolyLine.pos.x),tinygltf::Value(PolyLine.pos.y)});
            o["rx"] = tinygltf::Value(Rect.rx);
            o["attributes"] = tinygltf::Value(this->get(Rect.at));
            (*ob)["rect"] = tinygltf::Value(o);
    };
    static void writeCircle( circle Circle, tinygltf::Value::Object* ob){
        tinygltf::Value::Object  o;
        o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Circle.pos.x),tinygltf::Value(Cirlce.pos.y)});
        o["r"] = tinyglf::Value(Circle.r);
        o["attributes"] = tinygltf::Value(this->get(Circle.at));
        (*ob)["circle"] = tinygltf::Value(o);
};
    static void writeEllipse( ellipse Ellipse, tinygltf::Value::Object* ob){
        tinygltf::Value::Object  o;
        o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Ellipse.pos.x),tinygltf::Value(Ellipse.pos.y)});
        o["foci"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Ellipse.foci.x),tinygltf::Value(Ellipse.foci.y),tinygltf::Value(Ellipse.foci.z),tinygltf::Value(Ellipse.foci.w)});
        o["r"] = tinyglf::Value(Ellipse.r);
        o["attributes"] = tinygltf::Value(this->get(Ellipse.at));
        (*ob)["ellipse"] = tinygltf::Value(o);
    };
    static void writePath( path Path,tinygltf::Value::Object* ob){
        tinygltf::Value::Object  o;
        o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Ellipse.pos.x),tinygltf::Value(Ellipse.pos.y)});
        o["text"] = tinygltf::Value(Path.text)
        o["attributes"] = tinygltf::Value(this->get(Path.at));
        std::vector<tinygltf::Value> cubic,quad,line,arc;
        for(int i =0 ; i< Path.ptlistSize ; i++){
            switch(Path.ptlist[i].x){
                case 0: {cubic.push_back(tinygltf::Value(std::vector<tinygltf::value>({tinygltf::Value(Path.cubic[Path.ptlist[i].y].x),tinygltf::Value(Path.cubic[Path.ptlist[i].y].y)} ) )) ;};
                case 1: { quad.push_back(tinygltf::Value(std::vector<tinygltf::value>({tinygltf::Value( Path.quad[Path.ptlist[i].y].x),tinygltf::Value( Path.quad[Path.ptlist[i].y].y)} ) )) ;};
                case 3: { line.push_back(tinygltf::Value(std::vector<tinygltf::value>({tinygltf::Value( Path.line[Path.ptlist[i].y].x),tinygltf::Value( Path.line[Path.ptlist[i].y].y)} ) )) ;};
                case 4: {  arc.push_back(tinygltf::Value(std::vector<tinygltf::value>({tinygltf::Value(  Path.arc[Path.ptlist[i].y].x),tinygltf::Value(  Path.arc[Path.ptlist[i].y].y)} ) )) ;};
            };
        };
        o["cubic"] = tinygltf::Value(cubic);
        o["quad"] = tinygltf::Value(quad);
        o["line"] = tinygltf::Value(line);
        o["arc"] = tinygltf::Value(arc);
        (*ob)["path"] = tinygltf::Value(o);
        ;};
    static void writeTextPath( textpath TextPath,tinygltf::Value::Object* ob){
        tinygltf::Value::Object  o;
        o["pos"] = tinyglf::Value(std::vector<tinygltf::Value>({tinygltf::Value(Ellipse.pos.x),tinygltf::Value(Ellipse.pos.y)});
        o["font"] = tinygltf::Value(Path.font);
        o["text"] = tinygltf::Value(Path.text);
        o["attributes"] = tinygltf::Value(this->get(TextPath.at));
                    tinygltf::Value::Object  pat;
                    void writePath(TextPath.path,&pat);
        o["path"] = tinygltf::Value(pat);
        (*ob)["textpath"] = tinygltf::Value(o);        
    ;};
    
    static void write_g(g el, tinygltf::Value::Object* ob){
        std::vector<tinygltf::Value> o ;
        for(int i = 0 ; i< el.size;i++){
              o.push_back(std::vector<tinygltf>({tinygltf::Value( el.index[i].x) , tinygltf::Value( el.index[i].y)}));
            };
        };
        (*ob)["index"] = tinygltf::Value(o);
        (*ob)["size"] = el.size;
    };
    template<typename s>
    inline void svg_el_write(tinygltf::Value::Object* ob, void (*write_func)(s , tinygltf::Value::Object* ob) , size_t s , s* arr , std::string name ) {
        if(s>0){
            std::vector<tinygltf::Value> pls;
          for(int i =0 ; i <s;i++){
                tinygltf::Value::Object o;   
                write_func(Svg.arr[i],&o);
                pls.push_back(tinygltf::Value(o));
          };
         (*ob)[name]=tinygltf::Value(pls);};
    };
    void write(svg Svg, tinygltf::Value::Object* ob ){
        inline this->svg_el_write<g>       (ob,this->write_g       ,Svg.gsize     ,Svg.gs,"gs");
        inline this->svg_el_write<polyline>(ob,this->writePolyLine ,Svg.polylines ,Svg.polyLinesize,"polylines");
        inline this->svg_el_write<circle>  (ob,this->writeCircle   ,Svg.circles   ,Svg.gsize,"circles");
        inline this->svg_el_write<rect>    (ob,this->writeRect     ,Svg.rects     ,Svg.rectsSize,"rects");
        inline this->svg_el_write<ellipse> (ob,this->writeEllipse  ,Svg.ellipses  ,Svg.ellipsesSize,"ellipses");
        inline this->svg_el_write<path>    (ob,this->writePath     ,Svg.paths     ,Svg.pathsSize,"paths");
        inline this->svg_el_write<textpath>(ob,this->writeTextPath ,Svg.textPaths ,Svg.textPathsSize,"textpaths");
        // TODO index
        std::vector<tinygltf::Value> ind;
        for(int i = 0; i<Svg.indexSize;i++){
            ind.push_back(tinygltf::value(Svg.index[i];););
        };
        (*ob)["index"] = tinygltf::Value(ind);
        };
    };
    tinygltf::value::Object getSvgObj(svg Svg){ 
        tinygltf::Value::Object obj;
        this->write(Svg,&obj);
        return obj;
    };
    tinygltf::Value::Object get_ext(){
        tingtlf::Value::Object o;
        o["version"] = tinygltf::Value(100);
        return o;
    };
    tinygltf::Node get_node(){ // TODO make buffer view insted
        tinygltf::BufferView
        node.name="svg";
        node.extensions["strata_svg_ext"]=tinygltf::Value(this->get_ext());
        return node ; 
    };
    void toModel(tinygltf::Model* model,svg Svg){
        tinygltf::Node node;
        node.extras=tinygltf::Value(this->getSvgObj(Svg));

    };
    void write_to_file(std::string path, svg Svg ){
        tinygltf::Value::Object obj;
        tinygltf::Model mod;
        this->toModel(&mod,Svg);
        tinygltf::TinyGLTF::WriteGltfSceneToFile(mod,path);
    };
    getSvgObj(tinygltf::Node svgnode){

    } ;
    Svgv Svgvecfromfile(std::string path){
        tiny
    };
    
};

void contributeSvgExtension(tinygltf::Model& model,tinygltf::TinyGLTF& loader){
    
    // Create a new node
    tinygltf::Image node;
    node.name = "svg";

    // Define custom extension data
    // Add custom extension to the node
    node.extensions["strata_svg_extension"] = tinygltf::Value(customExtensionData);

    // Add the node to the model
    model.nodes.push_back(node);

    // Add the custom extension to the extensionsUsed and extensionsRequired arrays
    model.extensionsUsed.push_back("strata_svg_extension");
    model.extensionsRequired.push_back("strata_svg_extension");

    // Save the modified glTF file
    std::string error, warning;
    bool success = loader.WriteGltfSceneToFile(&model, "example_with_extension.gltf", true, true, true, &error, &warning);

    if (!success) {
        std::cerr << "Failed to save glTF file: " << error << std::endl;
    } else {
        std::cout << "Custom extension added successfully!" << std::endl;
    }

    return 0;
}
};
tinygltf::model load(){

};
void read_svg(){
    tinygltf::Node
};
void write_svg(std::string path){
    tinygltf::TinyGLTF loader;
std::string err, warn;
bool success = loader.WriteGltfSceneToFile(&model,path, true, true, true, true, true, false);
};

class svg {
};