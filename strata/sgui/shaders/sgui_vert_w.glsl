struct widget {
    uvec4 coord;
    uvec2 size; 
    vec2 svg[40];
    vec3 svg_ind[20];  
};
struct w_col {
uvec3 bg;
    uvec4 fg;
}
layout(location = 0 ) uniform int widget_no;
layout(location = 1 ) uniform widget w[widget_no];
layout(location = widget_no* ) uniform w_col ;
    
layout() in text {
    uvec2 size;
    vec3 text[10][40];

};

void main(){
    
};