#version 450
layout(location=0)in widget ws[] ;
layout(location=1)in ivec element_size ; // Zoom 

layout(location=0)out ivec4 widget_box ; // Where 
layout(location=1)out ivec4 childs_bounds; // Where children can be rendered


// lower
void main(){
    vec2 lower = bounds.zw + vec2(0,-5);
    childs_bounds.xyzw = vec4(vec2(bounds.xy ,lower);
};