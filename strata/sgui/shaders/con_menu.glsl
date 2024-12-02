layout(location=0)in vec4 bounds;
layout(location=1)in float height_size;
layout(location=2)in image2D text;
layout(location=3)in vec4 hover_col_add; // Add color
layout(location=)in int combo_size ;
layout(location=)in vec2 mouse_pos ;
layout(location=)in float scroll;
layout(location=)out int entryind;

void add_combo_border(){
    spot=cur_pos.y-(text_size.z/2);
    for(int i =0 ; i<bounds.x;i++){
        imageStore(im,vec2(spot,i) , fg_col);
    };
};
void main(){
    int nl = 0;
    line_height = (bounds.y-bounds.w)/text_size;
    while(nl<scroll){
        if(text[i] == LF){
            nl++;
        };
        
    };
    
    pos_cur = bounds.xy - vec2(0,text_size);
    space++;
    for(i =0 ; i<text_length; i++){
        if(text[i] == LF){
            add_combo_border();
        };
        pro_ind();      
    };
    if((mouse_pos.y < bounds.y) &&  (mouse_pos.y > bounds.w) && (mouse_pos.x < bounds.x) && (mouse_pos.x > bounds.z)){

        float pos=(mouse_pos.y-bounds.y) / (bounds.y-bounds.w);
        float ipos = scroll + (pos-pos%1); 
        entryind= scroll  + (pos-pos%1)

            for(int i = ipos*(text_size.y * );i< (bounds.z-bounds.x);i++){
                for(int j = 0 ; j < bonds.y-bounds.w;j++){

                };
            };
        };
    };
    
};