in vec4 coords;
in vec2 val;

in vec4 cols[4];

out vec4 color; 
out image2D im ;

int main(){
    vec2 interp = (val - coords.xw)/(coords.zy-coords.xw);
    vec4 vup =mix( cols[0],cols[1], interp.x);
    vec4 vdown = mix(cols[2],cols[3],interp.x);
    color = mix(vup, vdown, interp.y);
    
    if ( distance(gl_FragCoord.xy ,val) <  vec2((coords.z-coords.x), (coords.y-coords.w)) ){
        imageStore(im,gl_FragCoord,color);
    }
    else {
    vec4 cols;
    vec2 vs = vec2( ((gl_FragCoord.x-coords.x) /(coords.z - coord.x)),((gl_FragCoord.y-coords.w)/(coords.y-coords.w)) ) ;
        vup = mix( cols[0],cols[1], vs.x);
        vsown = mix(cols[2],cols[3],vs.x);
        cols = mix(vup,vdown,vs.y);
        imageStore(im,gl_FragCoord,cols);
    }
};