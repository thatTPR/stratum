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