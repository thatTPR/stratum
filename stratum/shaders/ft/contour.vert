struct contour {
    bool invert;
    vec2 coord;
    int size;
    vec2 contour[size];
};


layout(location=0) out 

const vec2 endContour = {0,0} ;
const vec2 followCurvecPt = {1,1};

struct contours {
    int  xMin;
    int  yMin;
    int  xMax;
    int  yMax;
    vec2 coord;
    uint size;
    vec2 contour[size] ;
};

struct contour {
    bool invert;
    vec2 coord;
    int size;
    vec2 contour[size];
};

layout ( location=0) in vec4 fg;
layout ( location=1) in vec4 bg;

layout ( location=1) in contour con;  




void main(){
    
      
};