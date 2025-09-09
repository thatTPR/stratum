struct glyfInfo {
   
    ivec2 rowCol;
    int xMin;
    int yMin;
    int xMax;
    int yMax;
    int horiBearing;
    int vertiBearing;

    uvec2 row_col; 
    vec2 offset; 
#define MAX_SIZE 10000
    uint size;
    vec2 pts[MAX_SIZE] ;
    // vec2 pts[p.size + tessNum * p.numOnCurves] ;
}

layout(binding=0)uniform bool kerning ;
layout(binding=1)uniform bool location;
layout(binding=1)buffer glyyfInfo gi ;



layout(location=0) 
layout(location=1) 

void main(){
    
    gl_Position

};