loyout(location=0)uniform ivec4 bounds; // nw se
loyout(location=1)uniform int element_size ; // Zoom (text height)


layout(location=2)uniform vec2 mouse_pos;
layout(location=3)uniform vec2 mouse_move; // Get mouse motion

layout(location=4)uniform ivec2 lastval;
layout(location=5)uniform vec4 normalval; // Norm range nw se
layout(location=6)uniform vec2 val_in;
layout(location=0)out ivec4 widget_box ; // Where 
layout(location=1)out ivec2 newval;
layout(location=2)out ivec2 val_out;



void main(){
    size = ((bounds.x-bounds.z) > (bounds.y - bounds.w)) ? (bounds.y - bounds.w) : (bounds.x - bounds.z);
    widget_box = vec4(bounds.x , bounds.y ,bounds.x - size , bounds.y -size  ) ;
    
    if(distance(mouse_pos-mouse_move , lastval) < element_size ){
        float x ;
        if(mouse_pos.x < widget_box.x  ){x = normalval.x;}
        else if(mouse_pos.x > widget_box.z){x = normalval.z;}
        else {x = (( mouse_pos.x  - widget_box.z) / (widget_box.x - widget_box.z) ) * (normalval.x - normalval.z) ;  }
        if(mouse_pos.y > widget_box.y){y=normalval.y;}
        else if(mouse_pos.y < widget_box.w){y=normalval.w;};
        else {y =  (( mouse_pos.y  - widget_box.w) / (widget_box.y - widget_box.w) ) * (normalval.y - normalval.w) ; }
        val_out = vec2(x,y);
        newval = mouse_pos.xy;
    }
    else {
        val_out = val_in;
        newval = lastval;
    }
    

} ;