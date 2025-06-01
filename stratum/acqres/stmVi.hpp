#include <cstddef>

struct version {
    int8_t verno; 
    
};

struct animateMotion {
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int8_t valuesSize;
    enum values {
        mat4,
        double,
    };
    int8_t valty; 
    union {
        glm::mat4 kern ;
        double v ;
    }* values ;
};
struct animateTransform {
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int8_t index_size;
    int8_t valuesSize;
    glm::dmat4 values; // 
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
struct filt {
    glm::dvec4 col;
    float weight;
    float random ;
    float stabilize;
    int8_t kernSize;
    union filt {
        glm::imat3 kern3;
        glm::imat4 kern4 ;
        int16_t kern5[25];
        int16_t kern6[36];
        int16_t kern8[64] ;
        int16_t kern10[100];
    }

};


struct attribute {
     // TODO make fe all one vector and adapt index, also add ats to g and add feRGBA glm::dmat4
        int8_t animateMotionSize;
        int16_t animateMotionIndex;
        animateMotion* animateMotions;
    
        int8_t animateTransformSize;
        int16_t animateTransformIndex;    
        animateTransform* animateTransforms;
        glm::dvec4 stroke;
        double stroke_width; // Relative to size
        glm::dvec4 fill; // rgba 
        glm::dmat4 gradient ; //x:col  y: dir z:
        glm::dmat4 radialGradient; // xy center , zw theta=0
        
        // All in order of application but indexes first make index index // TODO maybe curl
        int8_t feSize;  // TODO mul in fourths according to sparse idmat
        int8_t* feIndex;
        glm::mat4* fe; 

        double rotation=0;
        double sizex=1;
        double sizey=1;

        auto* getIndex(){

        };
};
struct elem {
    int8_t attributes ; 
    int8_t* ats ; 
    struct attribute ats ;

    glm::dvec4 stroke;
    double stroke_width; // Relative to size
    glm::dvec4 fill; // rgba 
    glm::dmat4 gradient ; //x:col  y: dir z:
    glm::dmat4 radialGradient; // xy center , zw theta=0
        
        // All in order of application but indexes first make index index // TODO maybe curl
    int8_t feSize;  // TODO mul in fourths according to sparse idmat
    
};

struct polyLine {
    int8_t size; 
    glm::dvec2* pts;
};
struct path {
    int8_t
};
struct textPath {

};
struct circle {

};
struct triangle {

};
struct rect {

};


void loadBitMapPng();
void loadBitMapBmp();

class stmVi {
    const std::string extension = "StmVi" ;
}