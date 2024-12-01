in vec4 bounds; // nw se
in float element_size ; // Zoom (text height)

out vec4 widget_box ; // Where 

in vec2 mouse_pos;
in vec2 mouse_move; // Get mouse motion

in vec2 lastval;
out vec2 newval;

in vec4 normalval; // Norm range nw se
in vec2 val_in;
out vec2 val_out;


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