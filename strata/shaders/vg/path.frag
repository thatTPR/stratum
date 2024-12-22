#define FEMAGIC 20000
#define _color 1
#define _striate 2
#define _perlin 3
#define _simplex 4
#define _convolve 5
#define _turbulence 6

struct animateMotion {
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int valuesSize;
    glm::dmat4 values; // Values to animate over; // xy: dpos : zw :rotation(size)

};
struct animateTransform {
    double dur=1; // ms
    double begin=0,end=dur; // ms or event;
    int index_size;
    int index;
    int valuesSize;
    glm::dmat4 values; // 
    
};

void feMagic(inout dmat4 p,  int s){
     p.x.w=fract(p.x.w)+((p.x.w)-fract(p.x.w))*FEMAGIC+s;
};
lowp int feMagic(inout dmat4 p){
    double t = p.x.w;
    int s=int(floor(t))/FEMAGIC; t = floor(t)/FEMAGIC +fract(t); p.x.w=t;
    return s;
};
#define PTMAGIC 2000
#define CUBIC 0
#define QUAD 1
#define LINE 2

struct atrib {
    dvec4 stroke;
    double stroke_width; // Relative to size
    dvec4 fill; // rgba 
    dmat4 gradient ; //x:col  y: dir z:
    dmat4 radialGradient; // xy center , zw theta=0
    animateTransform animt;
    animateMotion animm;
    dmat4 fe;
};
dvec2 ptpmagic(inout dvec2 p , lowp int g){  
    
    p.y=fract(s.y)+floor(s.y)*PTMAGIC+g;
    return s;
};
int ptpmagic(inout dvec2 p ){  
         int PT=int(floor(p.y))%PTMAGIC; p.y=floor(p.y)/PTMAGIC+fract(p.y);
    return PT;
};
layout(binding=0 )uniform  ;

layout(binding=1) buffer t {
    
    atrib at;
    dvec2 vgsize; // Size of image in port
    ivec2 imsize;
    dvec2 pts[];
};
layout(location=0) out image2D im;

image2D strokeIm ;
int strokeIsi = t.at.stroke_width*(abs(t.imsize)
for(int i = 0 ; i < strokeIsi ; i++){
for(int j = 0 ; j < strokeIsi ; j++){
    bool b = distance(ivec2(i,j), ivec2(strokeIsi));
    imageStore(strokeIsi , ivec2(i,j),b*t.at.stroke );
} ;
} ;
void stroke(ivec2 pt){
     imageStore(im,ivec2(pt+ivec2(-(at.stroke_width/2))),t.at.stroke );
};
ivec2 imsize = int( double(t.imsize) * t.vgsize ) ;
dvec2 geticoord(dvec2 s){return s*imsize;};
void main(){ // TODO this does a lot of vertex work WRONG!!!
// Shape size in pixels;
    ivec2 bounds[] ; int boundcur = 0;
    dvec2 imsi = dvec2(t.imsize);
    double iter = 1 /imsi.x ;
    for(int i =0 ; i < t.size -1;){
        bounds[boundcur] = geticoord(t.pts[i])
        boundcur++;
        lowp int mag = ptpmagic(t.pts[i])
        lowp int nextmag = ptpmagic(t.pts[i+1]); 
        switch(mag){
            case CUBIC: {
                dvec2 p1 = geticoord(t.pts[i]);
                dvec2 p2 = geticoord(t.pts[i+1]);
                dvec2 p3 = geticoord(t.pts[i+2]);
                dvec2 p4 = geticoord(t.pts[i+3]);

                i+=4;
            };
            case QUAD: {
                dvec2 p1 = geticoord(t.pts[i]);
                dvec2 p2 = geticoord(t.pts[i+1]);
                dvec2 p3 = geticoord(t.pts[i+2]);
                
                for(double j=0 ; j <= 1 ;j+=iter){
                    dvec2 pt =  p1*(1-j) +  p2 *(1 -0.5-i ) + (1 -(1-i))*p3 ;
                    ivec2 p = ivec2(pt*imsi.x);
                    stroke(p);
                };
                i+=3;
            };
            case LINE: {
                i++;
            };
          
        };
        mag=ptmagic(t.pts[1]);
    };

};