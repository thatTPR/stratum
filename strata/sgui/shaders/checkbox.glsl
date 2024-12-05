layout(location=0) uniform ivec4 bounds;
layout(location=1) uniform fg_col;
layout(location=2) uniform bg_col;
layout(location=3) uniform bool set;
layout(std432,binding=0) out  image2D im;
void drawBox(){
    int size= bounds.z-bounds.x;
    int si_fg_im = int(size/10);
    vec4 fg_im[2][si_fg_im] ;
    ivec2 cur_pos=bounds.xw;
    for(int i = 1 ; i <si_fg_im-1 ;i++){fg_im[0][i]=fg_col;fg_im[1][i]=fg_col;}
    for(int i = int(cur_pos.y); i < cur_pos.y + size ; i++){
    for(int j = int(cur_pos.x); i < cur_pos.x + size ; i++){
        imageStore(im,ivec2(i,j),bg_col);
    }
        imageStore(im,vec2(cur_pos.x,i),fg_col);
        imageStore(im,vec2(cur_pos.x+size,i),fg_col);
        imageStore(im,vec2(cur_pos.x +(i-cur_pos.x) ,cur_pos.y),fg_col);
        imageStore(im,vec2(cur_pos.x +(i-cur_pos.x) ,cur_pos.y+size),fg_col);
        if(set){
            if(i<(cur_pos.y + size /2)){
                imageStore(im, vec2(cur_pos.x + i -( i-cur_pos.y)) ,( cur_pos.y+(bounds.y-bounds.w)/2-i/2  ), fg_im );
            }
            else {
                imageStore(im, vec2(cur_pos.x + i -( i-cur_pos.y)) ,( cur_pos.y+(i-(bounds.y-bounds.w)/2)*2   ),fg_im);
            }
        }
    }
}


void main(){
    drawBox();
}