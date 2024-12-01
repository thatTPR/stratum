#version 450
layout(location=0)in vec4 bounds; // nw se
layout(location=1)in float element_size ; // Zoom (text height)

layout(location=2)out vec4 widget_box ; // Where 

layout(location=3)in vec2 mouse_pos;
layout(location=4)in vec2 mouse_move; // Get mouse motion

layout(location=5)in float lastval;
layout(location=6)out float newval;

#ifdef FLOAT
layout(location=7)in vec2 normalval; // Norm range
layout(location=8)in float val_in;
layout(location=9)out float val_out;
float get(float v ){
    if( v>normalval.y) {return normalval.y;};
    if( v<normalval.x) {return normalval.x;};
    return v;
}
#endif 

#ifdef INT

layout(location=7)in ivec2 normalval; // Norm range
layout(location=8)in int val_in;
layout(location=9)out int val_out;
int get(int v ){
    if( v>normalval.y) {return normalval.y;};
    if( v<normalval.x) {return normalval.x;};
    return v;
}

#endif

#ifdef UNSIGNED
layout(location=7)in uvec2 normalval; // Norm range
layout(location=8)in uint val_in;
layout(location=9)out uint val_out;
uint get(uint v ){
    if( v>normalval.y) {return normalval.y;};
    if( v<normalval.x) {return normalval.x;};
    return v;
}
#endif

#ifdef HORI 
vec4 get_bounds(){
    float height = element_size;
    if ((bounds.y - bounds.w) > height ){
        height = bounds.y-height;
    }
    else height=  bounds.y -bounds.w;
    vec4 res = vec4(bounds.xy,bounds.z,height);
    return res;
}
#endif
#ifdef VERTI
vec4 get_bounds(){
    float height = element_size;
    if ((bounds.y - bounds.w) > height ){
        height = bounds.y-height;
    }
    else height=  bounds.y -bounds.w;
    vec4 res = vec4(bounds.xy,bounds.z,height);
    return res;
}
#endif


void main(){
 widget_box = get_bounds();
    #ifdef HORI
    float bsize = (bounds.y-(bounds.y-bounds.w)/2);
    float size = widget_box.x - widget_box.z ;
    #endif
    #ifdef VERTI
    float size = widget_box.y - widget_box.w;
    float bsize = (bounds.x-(bounds.x-bounds.z)/2);
    #endif
    if( distance((mouse_pos - mouse_move), vec2(lastval,bsize)) < element_size){
        #ifdef HORI
        float _newval= lastval+mouse_move.x ;
        _newval = _newval<bounds.x ? normalval.x : (_newval > bounds.z ?  normalval.y : _newval );
        #endif
        #ifdef VERTI 
        float _newval= lastval+mouse_move.y ;
        _newval = _newval>bounds.y ? normalval.y : (_newval < bounds.w ?  normalval.x : _newval );
        #endif
        float _outval = val_in + ((_newval-lastval) / size)* (normalval.y-normalval.x);
        #ifdef FLOAT
        val_out = get(_outval);
        #else
        int _out= (fract(_outval) > 0.5) ? int(_outval+1) : int(_outval);
        #endif
        #ifdef UNSIGNED
        if(_outval < 0){_out = 0;}
        val_out = get(_out);
        #endif
        #ifdef INT
        val_out = get(_out);
        #endif
        #ifdef HORI
        newval = normalval.x + (val_out - normalval.x) / (normalval.y - normalval.x);
        #endif
        #ifdef VERTI
        newval = normalval.x + (val_out - normalval.x) / (normalval.y - normalval.x);
        #endif
    } 
    else {
        newval = lastval; val_out=val_in;

    }
    
}