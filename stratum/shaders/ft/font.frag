#ifdef PAINT
#define MAX_SIZE_TS = 100
struct paint {
    uint size;
    uint TsNum;
    uint valueTs[100];
    float values[size] ;
}

#define GRAD_LINEAR 0;

struct gradientLinear{
        vec2 p1;
        vec2 p2;
        vec2 rotation;
    };
#define GRAD_SWEEP 1;
    struct gradientSweep{
        vec2 center;
        float startAngle;
        float endAngle;
    };
#define GRAD_RADIAL 2;

    struct gradientRadial{
        vec2 startCenter;
        float rad1;
        vec2 endCenter;
        float rad2;

    };

#define AFFINE 3;

    struct Affine{
        vec2 xbasis;
        vec2 ybasis;
        vec2 dxdy;
    };
    // Transforms
    
#define SCALE_AROUND_CENTER 4
    struct scaleAroundCenter {
        vec2 d; 
        vec2 center;
    };

#define ROTATE_AROUND_CENTER 5
    struct rotateAroundCenter {
        float d;
        vec2 center;
    };
#define SKEW_AROUND_CENTER 5
    struct skewAroundCenter{
        vec2 d;
        vec2 center;
    };
    

layout(binding=2) buffer paint p;



#endif