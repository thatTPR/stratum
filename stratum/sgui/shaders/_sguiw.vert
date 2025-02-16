#version 450
layout(std430 binding=0) buffer widget {
vec4 parent_bounds;
ivec2 mouse_pos;
int element_size ;
bvec4 align; // left,up,right,down ( false means nothing )
};
layout(rgba32f, binding = 1) uniform image2D im ; // Image of the widget


layout(location=0)in ivec4 widget_box  ;
layout(location=1)in ivec4 childs_bounds ; 
layout(location=2)in ivec4 prev_bounds;

layout(location=0)out ivec4 _widget_box ; // Where 
layout(location=1)out ivec4 _childs_bounds; // Where children can be rendered
layout(location=2)out ivec4 next_boounds;




void main(){
    bool verti_center = widget.aligns.y && widget.aligns.w ;
    bool hori_center = widget.aligns.x && widget.aligns.y ;
    
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