#include <cstdef>
#include <iostream>

typedef struct  {
    uint xres;
    uint yres;  

    float64_t** im ;

}image ;


typedef struct  {
    uint xres;
    uint yres;
    uint length;
    uint period;
    uint frameRate;
    float64_t*** im ;
}GIF;

typedef struct {
    glm::uvec2 coord ;
    uint index ; 
}UV;
  

typedef struct {
    image s; 
    uint8_t vertnum;
    UV* verts ;
}UVIM;


typedef struct {
    GIF s;
    uint8_t vertnum;
    UV* verts ;
}UVGIF;
void load_gif(FILE* f , )
void load_png(FILE f) ;
void load_bmp(FILE f) ;

void write_gif(char* path);
void write_png(char* path);
void write_bmp(char* path);

struct atlas {
    struct uvim* images;
};
void loadAtlas(char* path, struct atlas* atl){
    
} ;
void writeAtlas(char* path , struct atlas* atl){

};
void load_image(char* path ){
    FILE* inFIle = fopen(path,"r");
};
