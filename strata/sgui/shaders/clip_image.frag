
in image2D im;
in uvec2 pos;
out image2D canvas; 

void main(){
    imageStore(canvas,pos,im);
};  
