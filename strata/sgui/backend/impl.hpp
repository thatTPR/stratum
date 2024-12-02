// Text
#include "../sgui_widgets.hpp"
void text(
bool word_wrap
 bvec4* options, // scrollable,kerning,word,wrap
 glyph* range[n],
 int* text_length,
 int* text[text_length],
 vec4* text_size, // w,h,space,line;
 vec2* bounds,
  image2D* im 
);
void text_ansi(
 bool word_wrap;
 bvec4* options, // scrollable,kerning,word,wrap
 glyph* range[n],
 int* text_length,
 int* text[text_length],
 vec4* text_size, // w,h,space,line;
 vec2* bounds,
 image2D* im ,
 ivec4* fg_bg_col[2];

);
void text_cursor(
  bool word_wrap
 bvec4* options, // scrollable,kerning,word,wrap
 glyph* range[n],
 int* text_length,
 int* text[text_length],
 vec4* text_size, // w,h,space,line;
 vec2* bounds,
  image2D* im ,
  vec2* cursor
);
void text_multi_cursor(
bool word_wrap
 bvec4* options, // scrollable,kerning,word,wrap
 glyph* range[n],
 int* text_length,
 int* text[text_length],
 vec4* text_size, // w,h,space,line;
 vec2* bounds,
  image2D* im ,
 uint* cursor_size,
 vec2* cursor;
);
void text_ansi_cursor(
        /*in*/   bvec4 options,  // scrollable,kerning,word,wrap
 /*in */ bvec4* options, // scrollable,kerning,word,wrap
 /*in */ glyph* range[n],
 /*in */ int* text_length,
 /*in */ int* text[text_length],
 /*in */ vec4* text_size, // w,h,space,line;
 /*in */ vec2* bounds,
 /*out*/ image2D* im ,
 /*in*/ ivec4* fg_bg_col; // Default color
 /*in*/ vec2* cursor;

);
void text_ansi_multi_cursor(
    /*in*/   bvec4 options,  // scrollable,kerning,word,wrap
 /*in */ bvec4* options, // scrollable,kerning,word,wrap
 /*in */ glyph* range[n],
 /*in */ int* text_length,
 /*in */ int* text[text_length],
 /*in */ vec4* text_size, // w,h,space,line;
 /*in */ vec2* bounds,
 /*out*/ image2D* im ,
 /*in*/ ivec4* fg_bg_col
 /*in*/ uint* cursor_size,
 /*in*/ vec2* cursor[cursor_size];
);
void combo_box(){
 ivec4 bounds,
 vec4 linesep_color,
 vec4 col_add; // Add colo,
 int combo_size ,
 int no_hovered ,
 int scroll,
 ivec2 mouse_pos
};
void 