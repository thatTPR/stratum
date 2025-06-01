// Tables
#include <glm/fwd.hpp>
#include <cstdint>
struct model {
    //primitives
    enum vertexTypes {
        pt,
        splineC,
        splinex,
        spliney,
        splineS,

    };
    enum primitves {
        triangleStrip,
        lineStrip,
        fan,
        QuadFanSpline, // Triabgle with pt insideish, and fan around it
        triFanSplineStrip,// StartsFromPreviousVertexPt  
        lineSpline,// 2 lines connected to one CurvePointLine
        lineSplineCubic,//
    };
    struct texture {
        int8_t pathSize; 
        char* path;
        int8_t nameSize; 
        char* name ;
        bool loaded;
        void loadSector(glm::uvec4 s){
            
        };
    };



};
struct sgen { // Surface generation table
    enum noise {
        perlin,
        simplex,
    };
    int8_t noiseMode;
    lowp_int Seed[255] =  ;

    

};