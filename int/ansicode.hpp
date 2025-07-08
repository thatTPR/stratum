

#define BEL	0x07,  //  7       | 007   |  0x07      \a	^G	Terminal bell ,
#define BS	0x08,  //  8       | 010   |  0x08      \b	^H	Backspace ,
#define HT	0x09,  //  9       | 011   |  0x09      \t	^I	Horizontal TAB ,
#define LF	0x0A,  //  10      | 012   |  0x0A      \n	^J	Linefeed (newline) ,
#define VT	0x0B,  //  11      | 013   |  0x0B      \v	^K	Vertical TAB ,
#define FF	0x0C,  //  12      | 014   |  0x0C      \f	^L	Formfeed (also: New page NP) ,
#define CR	0x0D,  //  13      | 015   |  0x0D      \r	^M	Carriage return ,
#define ESC	0x1B,  //  27      | 033   |  0x1B      \e*	^[	Escape character ,
#define DEL 0x7F,  //  127     | 0177   |  0x7F      <none>	<none>	Delete character 
#define STR_BEL "\a*"
#define STR_BS  "\b*"
#define STR_HT  "\t*"
#define STR_LF  "\n*"
#define STR_VT  "\v*"
#define STR_FF  "\f*"
#define STR_CR  "\r*"
#define STR_ESC "\e*"
#define STR_DEL NULL

#define HEX_C_BEL "\x07"
#define HEX_C_BS  "\x08"
#define HEX_C_HT  "\x09"
#define HEX_C_LF  "\x0A"
#define HEX_C_VT  "\x0B"
#define HEX_C_FF  "\x0C"
#define HEX_C_CR  "\x0D"
#define HEX_C_ESC "\x1B"
#define HEX_C_DEL "\x7F"

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
    #define FG_color 38 //	Set foreground color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, see above
    #define FG_off 39 //	Default foreground color	implementation defined (according to standard)
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
    #define BG_color 48 //	Set background color	Next arguments are 5;<n> or 2;<r>;<g>;<b>, see below
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
