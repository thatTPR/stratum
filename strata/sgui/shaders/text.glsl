#define BOLD
#define ITALIC
#define CROSSED
#define UNDERLINE
#define CLEAR

#ifdef 

#endif

struct plist {
    vec2[20] lines;
    vec2[20] control; // If set to 0,0 than line is normal
};
struct glyph_k {
    plist[20] letter; // Represents a glyph bezier point
    float h;
    float w;
    float horibearx;
    float horibeary;
};

struct font {
    fmat
};

struct text {
    fmat4x4
};
layout(location=1) in text {
    int size;
    
};
layout(location=2 ) in