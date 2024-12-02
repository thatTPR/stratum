
layout(location=0)in image2D im;
layout(location=1)in uvec2 pos;
layout(location=2)out image2D canvas; 

void main(){
    imageStore(canvas,pos,im);
};  
