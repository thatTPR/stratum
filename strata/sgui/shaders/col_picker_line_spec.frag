in vec4 coords;
in float val;

in vec4 mincol;
in vec4 midpoint
in vec4 maxcol;

out vec4 color; 
out image2D im ;

int main(){
    
    float v =  (val - coords.x) / (coords.z - coord.x);
        if(v<0.5){
            color = mix(mincol, midpoint, mincol + (maxcol-mincol) * vec4(v,v,v,v));
        }
        else{
            color = mix( midpoint, maxcol, mincol + (maxcol-mincol) * vec4(v,v,v,v))
        };
    if ( distance(gl_FragCoord.x ,val) <  min(coords.x-coords.z,coords.y-coords.w) ){
        imageStore(im,gl_FragCoord,color);
    }
    else {
    vec4 cols;
    float vs = (gl_FragCoord.x-coords.x) /(coords.z - coord.x);
        if(v<0.5){
            cols = mix(mincol, midpoint, mincol + (maxcol-mincol) * vec4(vs,vs,vs,vs));
        }
        else{
            cols = mix( midpoint, maxcol, mincol + (maxcol-mincol) * vec4(vs,vs,vs,vs));
        };
        imageStore(im,gl_FragCoord,cols);
    } 
}