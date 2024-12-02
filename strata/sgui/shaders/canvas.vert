layout(location=0) in vec4 parent_bounds;
layout(location=1) in int wno;
layout(location=2) in bvec4 aligns[wno]; // left,right,up,down
layout(location=3) in vec4 def_size[wno];
layout(location=4) in mouse_pos;
layout(locaiton=5) out vec4 bounds[wno];
layout(location=6) out uint index_mouse_pos;
layout(location=7) out vec4 bounds_remaining[2]; // left-center right-center
void main(){
    vec4 bleft = parent_bounds;
    for(int i = 0 ; i<widgets.wno;i++){
        bool c_hori=0;
        bool c_verti=0;
        if(aligns[i].x == 1){
            if(aligns[i].y==1){
                c_hori=1;
            }
            else {
                
            }
        }
        if(aligns[i].y==1){
            if(aligns[i].y==1){
                c_hori=1;
            }
            else {

            }
        }
        if(aligns[i].z==1){
            if(aligns[i].w==1){
                c_verti=1;
            }
            else {

            }
        }
        if(aligns[i].w==1){
            if(aligns[i].z==1){
                c_verti=1;
            }
            else {
                
            }
        }
        
    };
};