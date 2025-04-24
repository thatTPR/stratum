#include <cstddef>
// TODO

struct animateMotion {
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int8_t valuesSize;
    glm::dmat4 values; // Values to animate over; // xy: dpos : zw :rotation(size)
};
struct animateTransform {
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int8_t index_size;
    int8_t index;
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
    glm::dmat4 filt ;

};


struct attribute {
     // TODO make fe all one vector and adapt index, also add ats to g and add feRGBA glm::dmat4
        int8_t animateMotionSize;
        animateMotion* animateMotions;
        int8_t animateTransformSize;
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
};
struct elem {
    int8_t attributes ; 
    int8_t* ats ; 
    struct attribute ats ;

    int8_t animateMotionSize;
    animateMotion* animateMotions;
    int8_t animateTransformSize;
    animateTransform* animateTransforms;
    glm::dvec4 stroke;
    double stroke_width; // Relative to size
    glm::dvec4 fill; // rgba 
    glm::dmat4 gradient ; //x:col  y: dir z:
    glm::dmat4 radialGradient; // xy center , zw theta=0
        
        // All in order of application but indexes first make index index // TODO maybe curl
    int8_t feSize;  // TODO mul in fourths according to sparse idmat
    
};



class stmVi {
    const std::string extension = "StmVi" ;
}