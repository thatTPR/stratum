struct widget{
uvec4 bounds; // nw se
image2D sample;

};

in widget ws[] ;
in ivec element_size ; // Zoom 

out ivec4 widget_box ; // Where 
out ivec4 childs_bounds; // Where children can be rendered


// lower
void main(){
    vec2 lower = bounds.zw + vec2(0,-5);
    childs_bounds.xyzw = vec4(vec2(bounds.xy ,lower);
};