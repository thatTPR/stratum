#version 450
#ifdef MULTI_CURSOR
#define CURSOR
#endif
precision mediump float;
#ifdef ANSICODE
#define BEL	  7 //       | 007   |  0x07      \a	^G	Terminal bell ,
#define BS	  8 //       | 010   |  0x08      \b	^H	Backspace ,
#define HT	  9 //       | 011   |  0x09      \t	^I	Horizontal TAB ,
#define LF	  10 //      | 012   |  0x0A      \n	^J	Linefeed (newline) ,
#define VT	  11 //      | 013   |  0x0B      \v	^K	Vertical TAB ,
#define FF	  12 //      | 014   |  0x0C      \f	^L	Formfeed (also: New page NP) ,
#define CR	  13 //      | 015   |  0x0D      \r	^M	Carriage return ,
#define ESC	  27 //      | 033   |  0x1B      \e*	^[	Escape character ,
#define DEL   127 //     | 0177   |  0x7F      <none>	<none>	Delete character 

#define CARET 94

#define _BEL 71
#define _BS 72
#define _HT 73
#define _LF 74
#define _VT 75
#define _FF 76
#define _CR 77
#define _ESC 91

    #define cursor_up "A",//	Cursor Up	(n=1)	Move cursor up by n
    #define cursor_down "B", //	Cursor Down	(n=1)	Move cursor down by n
    #define cursor_forward "C", //	Cursor Forward	(n=1)	Move cursor forward by n
    #define cursor_back "D", //	Cursor Back	(n=1)	Move cursor back by n
    #define cursor_next_line "E", //	Cursor Next Line	(n=1)	Move cursor to the beginning of the line n lines down
    #define cursor_prev_line "F", //	Cursor Previous Line	(n=1)	Move cursor to the beginning of the line n lines up
    #define cursor_horizontal_abs "G", //	Cursor Horizontal Absolute	(n=1)	Move cursor to the the column n within the current row
    #define cursor_pos "H", //	Cursor Position	(n=1, m=1)	Move cursor to row n, column m, counting from the top left corner
    #define erase_in_disp "J", /*	Erase in Display	(n=0)	Clear part of the screen. 0, 1, 2, and 3 have various specific functions
     0 ( same as missing) erase unitl end of screen
     1 erase until beggining of screen
     2 erase entire screen
     3 erase saved line */
    #define erase_in_line "K", /*	Erase in Line	
    
    0 (same as missing )	erase from cursor to end of line
    1 	erase start of line to the cursor
    2 	erase the entire line
    
    */
    #define scroll_up "S", //	Scroll Up	(n=1)	Scroll window up by n lines
    #define scroll_down "T", //	Scroll Down	(n=1)	Scroll window down by n lines
    #define cursor_save "s", //	Save Cursor Position	()	Save current cursor position for use with u
    #define cursor_restore "u", //	Restore Cursor Position	()	Set cursor back to position last saved by s
    #define cursor_save_dec 7//	Save Cursor Position	()	Save current cursor position for use with u
    #define cursor_restore_dec 8//	Restore Cursor Position	()	Set cursor back to position last saved by s
    #define cursor_horizontal_abso "f", //	…	…	(same as G)
    #define SGR "m", //	SGR	(*)	Set graphics mode. More below

#define _cursor_up 65
#define _cursor_down 66
#define _cursor_forward 67
#define _cursor_back 68
#define _cursor_next_line 69
#define _cursor_prev_line 70
#define _cursor_horizontal_abs 71
#define _cursor_pos 72
#define _erase_in_disp 74
#define _erase_in_line 75
#define _scroll_up  83
#define _scroll_down 84
#define _cursor_save 115
#define _cursor_restore 117
#define _cursor_horizontal_abso 102 
#define _SGR 109

    #define TABLE 5
    #define RGB 2

    #define FG_BLACK 30
    #define FG_RED 31
    #define FG_GREEN 32
    #define FG_YELLOW 33
    #define FG_BLUE 34
    #define FG_MAGENTA 35
    #define FG_CYAN 36
    #define FG_WHITE 37
    #define FG_fg_color 38 //	Set foreground color	Next arguments are 5;<n> or 2;<r>;<g>;<b>
    #define FG_fg_off 39 //	Default foreground color	implementation defined (according to standard)
    //AIXTERM NON STANDARD
    #define FG_BRIGHT_BLACK 90
    #define FG_BRIGHT_RED 91
    #define FG_BRIGHT_GREEN 92
    #define FG_BRIGHT_YELLOW 93
    #define FG_BRIGHT_BLUE 94
    #define FG_BRIGHT_MAGENTA 95
    #define FG_BRIGHT_CYAN 96
    #define FG_BRIGHT_WHITE 97

    #define BG_BLACK 40
    #define BG_RED 41
    #define BG_GREEN 42
    #define BG_YELLOW 43
    #define BG_BLUE 44
    #define BG_MAGENTA 45
    #define BG_CYAN 46
    #define BG_WHITE 47
    #define BG_color 48 //	Set background color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, 
    #define BG_off 49 //	Default background color	implementation defined (according to standard)
    // AIXTERMnon standard
    #define BG_BRIGHT_BLACK 100
    #define BG_BRIGHT_RED 101
    #define BG_BRIGHT_GREEN 102
    #define BG_BRIGHT_YELLOW 103
    #define BG_BRIGHT_BLUE 104
    #define BG_BRIGHT_MAGENTA 105
    #define BG_BRIGHT_CYAN 106
    #define BG_BRIGHT_WHITE 107

    int fg(int s){return s-10; };

 
#define SG_reset 0 //	Reset / Normal	all attributes off
#define SG_bold 1 //	Bold or increased intensity	
#define SG_faint 2 //	Faint (decreased intensity)	Not widely supported.
#define SG_italic 3 //	Italic	Not widely supported. Sometimes treated as inverse.
#define SG_underline 4 //	Underline	
#define SG_slow_blink 5 //	Slow Blink	less than 150 per minute
#define SG_rapid_blink 6 //	Rapid Blink	MS-DOS ANSI.SYS; 150+ per minute; not widely supported
#define SG_reverse 7 //	[[reverse video]]	swap foreground and background colors
#define SG_conceal 8 //	Conceal	Not widely supported.
#define SG_crossed 9 //	Crossed-out	Characters legible, but marked for deletion. Not widely supported.
#define SG_primary 10 //	Primary(default) font	
#define SG_font_1 11
#define SG_font_2 12
#define SG_font_3 13
#define SG_font_4 14
#define SG_font_5 15
#define SG_font_6 16
#define SG_font_7 17
#define SG_font_8 18
#define SG_font_9 19 //	Alternate font	Select alternate font n-10
#define SG_fraktur 20 //	Fraktur	hardly ever supported
#define SG_bold_off 21 //	Bold off or Double Underline	Bold off not widely supported; double underline hardly ever supported.
#define SG_normal_intensity 22 //	Normal color or intensity	Neither bold nor faint
#define SG_italic_off 23 //	Not italic, not Fraktur	
#define SG_underline_off 24 //	Underline off	Not singly or doubly underlined
#define SG_blink_off 25 //	Blink off	
#define SG_reverse_off 27 //	reverse off	
#define SG_reveal 28 //	Reveal	conceal off
#define SG_not_crossed 29 //	Not crossed out	
 //30–39	Set foreground color	See color table above

 //40–49,	Set background color	See color table above

#define SG_framed 51  //	Framed	
#define SG_encircled 52  //	Encircled	
#define SG_overlined 53  //	Overlined	
#define SG_framed_off 54  //	Not framed or encircled	
#define SG_overlined_off 55  //	Not overlined	
#define SG_ideogram_underline 60  //	ideogram underline	hardly ever supported
#define SG_ideogram_double_underline 61  //	ideogram double underline	hardly ever supported
#define SG_ideogram_overline 62  //	ideogram overline	hardly ever supported
#define SG_ideogram_double_overline 63  //	ideogram double overline	hardly ever supported
#define SG_ideogram_stress 64  //	ideogram stress marking	hardly ever supported
#define SG_ideogram_off 65  //	ideogram attributes off	reset the effects of all of 60-64

// 90–97, //	Set bright foreground color	aixterm (not in standard)
// 100–107, //	Set bright background color	aixterm (not in standard)

#define SEMICOLON 59
#define zero 48

bool _bold = 0 ;
bool _faint = 0 ;
bool _italic = 0;
bool _underline = 0;
bool _slow_blink = 0;
bool _rapid_blink = 0;
bool _reverse = 0;
bool _conceal = 0;
bool _crossed = 0;
int _font = 0;
bool _fraktur = 0;
uvec4 fg_col;
uvec4 bg_col;

#endif
 struct glyf {
	uint numberOfContours;
	int xMin;
	int yMin;
	int xMax;
	int yMax;
	// uint instructionLength;
	// uint instructions[];
	int size;
	ivec2 coords[];
	int endPtsOfContours[numberOfContours];
};
struct glyph {
    uint numberOfContours;
	int xMin;
	int yMin;
	int xMax;
	int yMax;
	int size;
	vec2 coords[];
	int endPtsOfContours[numberOfContours];

    
    float h;
    float w;
    float horibearingx;
    float horibearingy;
    float horiadvance;
    #ifdef VERTI_BEARING
    float vertibearingx;
    float vertibearingy;
    float vertiadvance;
    #endif  VERTI_BEARING
};

layout(location=0) uniform bool word_wrap;
layout(location=1) uniform bvec4 options; // scrollable,kerning,word,wrap
layout(location=2) uniform glyph range[n];
layout(location=3) uniform int text_length;
layout(location=4) uniform int text[text_length];
layout(location=5) uniform ivec4 text_size ; // w,h,space,line;
layout(location=6) uniform ivec2 bounds;
layout(location=7) uniform int scroll;
layout(location=0) out image2D im ;
layout(location=1) out text_s;
#define LOC  8
#ifdef ANSICODE
layout(location=LOC) uniform ivec4 fg_bg_col[2];
#define LOC  LOC +1 
#endif
#ifdef CURSOR

#ifdef MULTI_CURSOR
layout(location=LOC) uniform uint size;
#define LOC LOC+1
layout(location=LOC) uniform vec2 cursor[size]; //line col;
#define LOC  LOC +1 
#else
#define (location=LOC) uniform vec2 cursor;
#endif
layout(location=1) out image2D index; // position of each glyph xy pos; zw state;
#define LOC  LOC +1 
#endif

int i;
vec2 pos_cur;
int space;
image2D qbspline_rast(vec2 p1,vec2 p2,vec2 p3){
    image2D s;
    for(int i=0;i < text_size.x ;i++){
        if(p2)
        if(p1)
    };
};
bool check_pt_in_contour(vec2 p, uint contourSize,vec2 contour[contourSize]){
    int windingNumber = 0;

    for (int i = 0; i < contourSize; ++i) {
        vec2 a = contour[i];
        vec2 b = contour[(i + 1) % contourSize]; // Next vertex (loop back at end)

        if (a.y <= point.y) {
            if (b.y > point.y && crossProduct(b - a, point - a) > 0.0) {
                windingNumber += 1;
            }
        } else {
            if (b.y <= point.y && crossProduct(b - a, point - a) < 0.0) {
                windingNumber -= 1;
            }
        }
    }

    return windingNumber != 0; // Non-zero means inside
};
// vec2 check_segment_in_contour(float axis,uint contour_size,vec2[contour_size]){

// };
// bool check_bounding_in_contour(vec4 axis,uint contour_size,vec2[contour_size]){

// };
image2D fill_contour(image2D glif; vec4 colour,int size,vec2 cont[size]){
    int xmax;
    int ymax;
    int xmin;
    int ymin;
    image2D glim = glif;
    for(int i=0; i < size;i++){
        if(cont[i].x < m.x){xmin=i;continue;};
        if(cont[i].y < m.y){ymin=i;continue;};
        if(cont[i].x > m.z){xmax=i;continue;};
        if(cont[i].y > m.w){ymax=i;continue;};
    };
    for(int i=ymax;i>=ymin;y++){
        for(int j = xmax; j >= xmin;j++){
            vec2 p = vec2(i,j);
            if(check_pt_in_contour(p,size,cont)){
                imageStore(glim,p,colour);
            };

        };
        
    };
    return glim;
};
void process(){
    
    glyph cur =range[text[i]]; 
    if(kerning){   pos_cur.x =pos_cur.x- cur.horibearingx;    }
       

    int j =0;
    for(; j< cur.size ;j++){
        contours[curendptcont][j-0]
        if(j==cur.endPtsOfContours[curendptcont]){
            contourSize[curendptcont]=j;
            curendptcont++;break;
        };
    };
    for(; j< cur.size ; j<;j++){
        contours[curendptcont][j-cur.endPtsOfContours[curendptcont-1]];
        if(j==cur.endPtsOfContours[curendptcont]){
            contourSize[curendptcont]=j-contourSize[curendptcont-1];
            curendptcont++;
        };
    };  
    vec2 pt = pos_cur.xy+vec2(0.0,text_size.y);
    image2D glyfim;
    for(int i = 0; i <text_size.w;i++){
        for(int j = 0 ; j<text_size.h;j++){
            imageStore(glyfim, vec2(i,j),bg_col);
        };
    } ;

    for(int i = 0 ; i<cur.numberOfContours ; i++;)
    {
            uint contSize;int lastend ;
            if(i==0){
                contSize = cur.endPtsofContours[i];
                lastend = 0;
            }
            else {lastend=cur.endPtsofContours[i-1];contSize = cur.endPtsOfContours[i]-lastend;}
            vec2 v[contsize];

            for(int j = lastend+1 ; j <= cur.endPtsOfContours[i];j++){
                v[j-(lastend+1)]=cur.coords[j];
            };
            glyfim=fill_contour(glyfim,fg_col,contsize,v);
        for(int h = 0 ; h<=cur.numberOfContours;h++ ){
            if(h==i){continue;};
            uint cons; int laste;
            if(i==0){
                cons = cur.endPtsofContours[i];
                laste = 0;
            }
            else {laste=cur.endPtsofContours[i-1];cons = cur.endPtsOfContours[i]-laste;}
            vec2 ve[contsize];

            for(int k = laste+1 ; k <= cur.endPtsOfContours[i];k++){
                ve[k-(laste+1)]=cur.coords[k];
            };
            if (check_pt_in_contour(ve[0],contSize,v)){glyfim = fill_contour(glyfim,bg_col,cons,ve);};    
            
        };
    };
    if(kerning){pos_cur.x =pos_cur.x + cur.w ;}
    else {pos_cur.x = pos_cur.x +cur.advance + text_size.z;};
    pos_cur.x += cur.w;
    imageStore(im,pt,glyfim);
};
#ifdef ANSICODE
void new_line(int s=1){pos_cur.xy=vec2( (bounds.x + text_size.z),(pos_cur.y-(text_size.y+text_size.w));};
void space(int s=1){pos_cur.x+= s*(text_size.x);};
uvec3 color128(){
    vec3 col;i++; int ansiCode ; int size=0;
    for(;i<text_length;i++){
        if(text[i]=SEMICOLON){
            break;
        }
        else {size++;
            ansiCode = ansiCode *10+text[i]-zero;
        };
    };
    
      if (ansiCode >= 0 && ansiCode <= 15) {
        // Standard colors (adjust as per your terminal's palette)
        uvec3 standardColors[16] = {
            {0, 0, 0}, {205, 0, 0}, {0, 205, 0}, {205, 205, 0},
            {0, 0, 238}, {205, 0, 205}, {0, 205, 205}, {229, 229, 229},
            {127, 127, 127}, {255, 0, 0}, {0, 255, 0}, {255, 255, 0},
            {92, 92, 255}, {255, 0, 255}, {0, 255, 255}, {255, 255, 255}
        };
        return standardColors[ansiCode];
    } else if (ansiCode >= 16 && ansiCode <= 231) {
        // return ansiToRgbCube(ansiCode);
    int levels[6] = {0, 95, 135, 175, 215, 255};
    int index = ansiCode - 16;
    int red = levels[(index / 36) % 6];
    int green = levels[(index / 6) % 6];
    int blue = levels[index % 6];
    return uvec3(red, green, blue);

    } else if (ansiCode >= 232 && ansiCode <= 255) {
        // return ansiToGrayscale(ansiCode);
        // Grayscale
         int gray = 8 + (ansiCode - 232) * 10;
    return uvec3(gray, gray, gray);
    } 
else return uvec3(100,0,0);
    
};
uvec3 colorrgb(){
    int no=-1;
    int num; 
    vec3 col;
    for(; i <text_length ;i++){
        if(text[i]=SEMICOLON){
            if(no==0){col.x=num;}
            if(no==1){col.y=num;}
            if(no==2){col.z=num; return col;}
            no++;num=0;
        };
        else {
            num = num*10+text[i]-zero;
        };
    };
};
void escape(){
    bool cond;
    for (; (i<text_length) && cond;i++ ){
    switch(text[i]){
        case _cursor_up:             {};
        case _cursor_down:           {};
        case _cursor_forward:        {};
        case _cursor_back:           {};
        case _cursor_next_line:      {};
        case _cursor_prev_line:      {};
        case _cursor_horizontal_abs: {};
        case _cursor_pos:            {};
        case _erase_in_disp:         {};
        case _erase_in_line:         {};
        case _scroll_up:             {};
        case _scroll_down:           {};
        case _cursor_save:           {};
        case _cursor_restore:        {};
        case _cursor_horizontal_abso:{};
        case _SGR:   
                        {
        i++;
            switch(text[i]){
            case FG_BLACK         :{fg_col=uvec3(0, 0, 0);}; 
            case FG_RED           :{fg_col=uvec3(205, 0, 0);};
            case FG_GREEN         :{fg_col=uvec3(0, 205, 0);};
            case FG_YELLOW        :{fg_col=uvec3(205, 205, 0);};
            case FG_BLUE          :{fg_col=uvec3(0, 0, 238);};
            case FG_MAGENTA       :{fg_col=uvec3(205, 0, 205);};
            case FG_CYAN          :{fg_col=uvec3(0, 205, 205);};
            case FG_WHITE         :{fg_col=uvec3(229, 229, 229);};
            case FG_fg_color      :{if(text[i+1]==TABLE-zero) ;fg_col=color128(i++;);
                                    else {i++;fg_col=colorrgb();}    };
            case FG_fg_off        :{fg_col=uvec3(229,229,229);};
            case FG_BRIGHT_BLACK  :{fg_col=uvec3(127, 127, 127);};
            case FG_BRIGHT_RED    :{fg_col=uvec3(255, 0, 0);};
            case FG_BRIGHT_GREEN  :{fg_col=uvec3(0, 255, 0);};
            case FG_BRIGHT_YELLOW :{fg_col=uvec3(255, 255, 0);};
            case FG_BRIGHT_BLUE   :{fg_col=uvec3(92, 92, 255);};
            case FG_BRIGHT_MAGENTA:{fg_col=uvec3(255, 0, 255);};
            case FG_BRIGHT_CYAN   :{fg_col=uvec3(0, 255, 255);};
            case FG_BRIGHT_WHITE  :{fg_col=uvec3(255, 255, 255);};
            case BG_BLACK         :{bg_col=uvec3(0, 0, 0);}; 
            case BG_RED           :{bg_col=uvec3(205, 0, 0);};
            case BG_GREEN         :{bg_col=uvec3(0, 205, 0);};
            case BG_YELLOW        :{bg_col=uvec3(205, 205, 0);};
            case BG_BLUE          :{bg_col=uvec3(0, 0, 238);};
            case BG_MAGENTA       :{bg_col=uvec3(205, 0, 205);};
            case BG_CYAN          :{bg_col=uvec3(0, 205, 205);};
            case BG_WHITE         :{bg_col=uvec3(229, 229, 229);};
            case BG_fg_color      :{if(text[i+1]==TABLE-zero) ;bg_col=color128(i++;);
                                    else {i++;bg_col=colorrgb();}    };
            case BG_fg_off        :{bg_col=uvec3(0,0,0);};
            case BG_BRIGHT_BLACK  :{bg_col=uvec3(127, 127, 127);};
            case BG_BRIGHT_RED    :{bg_col=uvec3(255, 0, 0);};
            case BG_BRIGHT_GREEN  :{bg_col=uvec3(0, 255, 0);};
            case BG_BRIGHT_YELLOW :{bg_col=uvec3(255, 255, 0);};
            case BG_BRIGHT_BLUE   :{bg_col=uvec3(92, 92, 255);};
            case BG_BRIGHT_MAGENTA:{bg_col=uvec3(255, 0, 255);};
            case BG_BRIGHT_CYAN   :{bg_col=uvec3(0, 255, 255);};
            case BG_BRIGHT_WHITE  :{bg_col=uvec3(255, 255, 255);};
            case SG_reset :           {_bold=0;_faint=0;_italic=0;_underline=0;_slow_blink=0;_rapid_blink=0;_reverse=0;_conceal=0;_crossed=0;font=0;_fraktur=0;};
            case SG_bold :            {_bold=1};
            case SG_faint :           {_faint=1};
            case SG_italic :          {_italic};
            case SG_underline :       {_underline=1};
            case SG_slow_blink :      {_slow_blink=1};
            case SG_rapid_blink :     {_rapid_blink=1};
            case SG_reverse :         {_reverse=1};
            case SG_conceal :         {_conceal=1};
            case SG_crossed :         {_crossed=1};
            case SG_primary :         {_font=0};
            case SG_font_1 :          {_font=1};
            case SG_font_2 :          {_font=2};
            case SG_font_3 :          {_font=3};
            case SG_font_4 :          {_font=4};
            case SG_font_5 :          {_font=5};
            case SG_font_6 :          {_font=6};
            case SG_font_7 :          {_font=7};
            case SG_font_8 :          {_font=8};
            case SG_font_9 :          {_font=9};
            case SG_fraktur :         {_fraktur=1};
            case SG_bold_off :        {_bold=0};
            case SG_normal_intensity :{_faint=0};
            case SG_italic_off :      {_italic=0};
            case SG_underline_off :   {_underline=0};
            case SG_blink_off :       {_blink=0};
            case SG_reverse_off :     {_reverse=0};
            case SG_reveal :          {_reveal=0};
            case SG_not_crossed :     {_crossed=0};
            }
        };
    };
    cond=0;
};
};
#endif
void pro_ind(){
    int prev = i-1;
        #ifdef ANSICODE
        if(text[i-1] != 92){        
        switch(text[i]){
            case (CARET)  {
                i++;
                switch text[i] {
                    case : _BEL {} ;
                    case : _BS {};
                    case : _HT {space(4);};
                    case : _LF {new_line(1);};
                    case : _VT {new_line(4);};
                    case : _FF {};
                    case : _CR {};
                    case : _ESC {i++;escape();};
                };
            };
            case BEL : {};
            case BS : {};
            case HT : {space(4);};
            case LF : {new_line(1);};
            case VT : {new_line(4);};
            case FF : {};
            case CR : {};
            case ESC :{escape(i+1);};
            case DEL :{}; 
        };};
        #endif
        process(text[i]);
};
#ifndef NO_MAIN
void main(){
    text_s = text_size;
    pos_cur = bounds.xy - vec2(-text_size.z,(text_size.y+text_size.w));
    line_height = (bounds.y-bounds.w)/text_size;
    space++;
    for(i =0 ; i<text_length; i++){
        pro_ind();      
    };
};
#endif