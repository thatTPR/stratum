#version 450

in bvec2 state;
in uvec4 stroke; // Last one is width
in uvec4 fill;
in uvec4 more;
in vec2 icoCoord;
in vec2 icoVert
out vec4 outColor;


#ifdef EVENT 
// Square    
vec2 pin_event(bool connected, bool triggered){
    uvec4 st[p][p] ;
        
    
    
    if(connected){
        stroke.zw += more;
        fill.zw += more;
    };
    if(triggered) {
        stroke.zw += more;
        fill.zw += more
    };

    for(int i=0 ; i<p ; i++){
        for(int t = 0 ; t<stroke_width;t++){
            st[i+t][i] = stroke;
            st[i][i+t] = stroke ;
            st[p-1-i-t][i] = stroke;
            st[i][p-1-i-t] = stroke;
        };
    };
    for(int j = stroke_width ; j<p-stroke_width ; j++){
        for(int h = stroke_width ; h<p-stroke_width ; h++){
            st[h][j] = fill ;
        };
    };


}; 
#endif
#ifdef RES
// circle
vec2 pin_res(bool connected, bool triggered , uvec4 stroke, uvec4 fill, uvec4 more ){ 
        uvec4 st[p][p] ;
    // Fill
    if(connected){
        stroke.xyzw += more;
        fill.xyzw += more;
    };
    if(triggered) {
        stroke.xyzw += more;
        fill.xyzw += more
    };
    int size =  p - stroke_width  ;
    bool size_even = (size%2) ==0
    int r = size/2;
    uint pt = size/2 + size_even; 
    uint half_rad = pt/2 ;
    
    int d = 1-r;
    uint cx = stroke_width+pt;
    uint cy = stroke_width/2 ;
    uint x = 0 ;
    uint y = r;
    do{ 
        int nx = cx + x;
        int ny = cy + r -y;
        for (int i =pt; i < nx ; i++ ){
            st[cx][i] = fill;
            st[cx][i-(i-pt)] = fill;
        };
        // st[x][y] = stroke;
        for(int t = - stroke_width/2 ; t< stroke_width/2;t++){
            st[nx+t][ny+t]   = stroke;
            st[nx+t][p-ny+t] = stroke;
            st[p-nx][ny+t]   = stroke;
            st[p-nx][p-ny+t] = stroke;
        };
        if(d<0){
            d=d+2x+3;
            x++;  
        }
        else {
            x++ ; yii ;
            d = d + 2x -2y +5;
        };

    }while(x>y);
    if(!twice){
        twice = false;
    };
}; 
#endif 
#ifdef FUNC
#ifdef exec
// triangle
uvec4[p][p] pin_func(bool connected, bool triggered){
        uvec4 st[p][p] ;
    // Fill
    uvec4 stroke={200,50,25,200}; ;
    uvec4 fill = {0,0,200,100} ;
    uvec2 more = {100,20};
    if(connected){
        stroke.zw += more;
        fill.zw += more;
    };
    if(triggered) {
        stroke.zw += more;
        fill.zw += more
    };
    bool swheven = (stroke_width%2)==1?false:true;
    int swh = stroke_width/2;
    int sih = p/2;
    for(int i=swh; i< p-swh; i++){
        for(int j = 0 ; j<=i ; j++){
            st[i][sih+i] = fill;
            st[i][sih-i] = fill;

        };
    };
   for(int i=0 ; i<p ; i++){
        for(int t = 0 ; t<stroke_width;t++){
            st[i+t][i] = stroke;
            st[i][i+t] = stroke ;
            st[p-1-i-t][i] = stroke;
            st[i][p-1-i-t] = stroke;
        };
        for(int t = 0 ; t<stroke_width;t++){

        };
    };
}; 
#endif
//cube
uvec4[p][p] pin_func(bool connected, bool triggered){
        uvec4 st[p][p] ;
    // Fill
    uvec4 stroke={200,50,25,200}; ;
    uvec4 fill = {0,0,200,100} ;
    uvec2 more = {100,20};
    if(connected){
        stroke.zw += more;
        fill.zw += more;
    };
    if(triggered) {
        stroke.zw += more;
        fill.zw += more
    };
    int h = p/2 ;
       for(int i=0 ; i<p ; i++){
        for(int t = 0 ; t<stroke_width;t++){
            st[i+t][i] = stroke;
            st[i][i+t] = stroke ;
            st[p-1-i-t][i] = stroke;
            st[i][p-1-i-t] = stroke;
        };
    };
    for(int j = stroke_width ; j<p-stroke_width ; j++){
        for(int h = stroke_width ; h<p-stroke_width ; h++){
            st[h][j] = fill ;
        };
    };
}; 
#endif 
uint ps = resx/(monptx/(PT_SIZE));
uint stroke_width = STROKE_WIDTH * ps ; 

uint p= ps * textSizept;
int p_pix = 
bool handle_state(bool connected , bool triggered){

};





void main(){
    outColor = 
};