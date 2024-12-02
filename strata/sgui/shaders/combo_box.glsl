layout(location=0)uniform ivec4 bounds;
layout(locaiton=1)uniform vec4 linesep_color;
layout(location=2)uniform vec4 col_add; // Add color
layout(location=3)uniform int combo_size ;
layout(location=4)uniform int no_hovered ;
layout(location=5)uniform int scroll;
layout(location=6)uniform ivec2 mouse_pos;

layout(location=0)in image2D text;
layout(location=1)in ivec4 text_size; // w,h,space,line Space between 
layout(location=0)out ivec4 _bounds;
layout(location=1)out image2D combo;


int scroll_phi=int(float(scroll)/float(float(text_size.h)+float(text_size.w)));

vec2 cur_pos=vec2(0,imageSize(text).y-int(scroll_phi));
void add_combo_border(){
    int spot=int(cur_pos.y-(text_size.w/2));
    for(int i =0 ; i<imageSize(text).x;i++){
        imageStore(combo,ivec2(i,spot) , linesep_color );
    }
    for(int i=cur_pos.y; i<height_size;i--){
        imageStore(combo,ivec2(0,i),linesp_color);
        imageStore(combo,ivec2(int(bounds.z),i),linesp_color);
    };
    cur_pos.xy= {cur_pos.x,(cur_pos.y-(text_size.w + text_size.h)};
    
};
void draw_hover(int n){
    vec2 pos = (cur_pos)+vec2(0.0,(-scroll_phi-n*(text_size.h + text_size.w));
    for(int i = ceil.bounds)
    imageAdd()
};
void main(){
    float no = (floor(scroll)/(scroll -floor(scroll)))/(text_size.h+text_size.line);
    float no_end = no + (bounds.y-bounds.w - (scroll-floor(scroll)))/(text_size.h+text_size.w);
    if((no<no_hovered) && (no_hovered<no_end) ){
        draw_hover(no - no_hovered);
    };
    imageStore(combo,vec2(0,(bounds.y-bounds.w)),text);    
    for(int i = no  ; i<=no_end<; i++){
            add_combo_border();     
    };
    if((mouse_pos.y < bounds.y) &&  (mouse_pos.y > bounds.w) && (mouse_pos.x < bounds.x) && (mouse_pos.x > bounds.z)){
        vec4 pos_bounds=vec4(bounds.x ,bounds.y+(no_end-no)
    };
    _bounds=bounds;
};