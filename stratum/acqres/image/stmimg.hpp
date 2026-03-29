#ifndef STMIMG_HPP


struct stmimg {
    struct header {
        uint32_t w;
        uint32_t h;
        uint8_t bych;// Byte perChannel
        uint8_t inf;
        uint32_t cmapSize;
        uint8_t imgByd;// eq to bych*chCount for non cmap;
        uint32_t imgsize;
        bool alpha(){return inf &(1<<7);};
        bool gamma(){return ing &(1<<6);};
        bool cmap(){return inf &(1<<5);};
        bool rle(){return inf & (1<<4);};
        void chCount(return inf & 0b1111;) // Including alpha
    };  
    header head;
    uint32_t gamma ; // Stored as gamma * 100000
    uint8_t *cmap;

    uint8_t *color;
    void gamma(){return gamma/100000;};


    void ld(std::ifstream& fi){
        ld(head,fi);
        if(head.gamma()){ld(gamma,fi);}
        if(head.cmap){ld(cmap,head.chCount()*head.bych*head.w*head.h);
            ld(img.byd)
        };
        
    }

}
#define STMIMG_HPP