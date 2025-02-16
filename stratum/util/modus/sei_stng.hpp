
#include "boost_1_83_0/boost/json.hpp"
#include "stypes/Scontainers/bimap"

#ifndef SEI_SETTINGS
#define SEI_SETTINGS
#endif
#ifdef SEI_SETTINGS_ALL
#define KEY_CHORDS
#define KEY_SHORTCUTS
#define KEY_SETTINGS
#define MOUSE_SETTINGS
#define JOY_SETTINGS
#define CONTROLLER_SETTINGS
#define AUDIO_SETTINGS
#define VIDEO_SETTINGS
#define USER_SETTINGS
#endif
// Operators supported for shortcuts
// + (in order)
// | (shortcuts allow multiple captures)
// 

class sei_shortcuts {

};
class sei_misc {

};
class sei_settings {
    sei_misc misc ; 
    sei_shortcuts shortcuts ; 
};

class stng_vals {
    typedef std::string key ;
    key keyval ;                                     // Token              Operator
    std::array< std::pair<key , std::pair< std::array<std::string> , std::array<char> > > > strings_condition ; \
                                 //         Min    max
    std::array<std::pair<key ,  std::pair<double , double> >>  doubles_condition ; 
                                       //min  max
    std::array<std::pair<key , std::pair<int , int> >>  ints_condition ;

    std::array<key, std::array<key>>  booleans_condition ; 
    std::array<stng_condition> >  arrs_condition ; 
    std::array<stng_condition>>  objs_condition ;

   
    std::stirng strings(std::string key , std::string str ){
        for(const auto &i : strings_condition){
            str.find(i.)
        }
    };
    virtual std::string doubles(std::string key ,double num){

    };
    virtual std::string ints(std::string key , int num){

    };
    virtual std::string booleans(std::string key ,bool boolean){

    };
    virtual std::string arrs(std::string key ){

    };
    virtual std::string obj(std::string key ){

    };

    condition(std::conditional<_strings>)




};
typedef std::pair<std::string , std::array<std::string>>
class arr ;
class obj  {
    std::string name; 
    std::bimap<std::string ,boost::json::value> stored_values ;

    virtual bimap<std::string , std::string> strings;
    virtual bimap<std::string , double> doubles; 
    virtual bimap<std::string , int> ints ;
    virtual bimap<std::string , bool> booleans ;
    virtual bimap<std::string , arr> arrs ;
    virtual bimap<std::string , obj> obj ;

    check(){

    };
    virtual parser(){

    }
    obj(std::string name , ){
        this->name = name ;
    }

};
class arr  {
    std::string name ;
    std::vector<boost::json::value> values ;
    
    virtual std::vector< std::string> strings;
    virtual std::vector< double> doubles; 
    virtual std::vector< int> ints ;
    virtual std::vector< bool> booleans ;
    virtual std::vector< arr> arrs ;
    virtual std::vector< obj> objs ;
}


template <bool key_chords, bool key_shortcuts, bool key_settings, bool mouse_settings, bool joy_settings , bool controller_settings , bool audio_settings, bool video_settings , bool user_settings  >
class sei_settings {
    public: 
    typedef enum STNG {
        STNG_FIRST = 0;
        #ifdef KEY_CHORDS
        STNG_CHORD= 1 ,
        #endif
        #ifdef KEY_SHORTCUTS
        STNG_SHORTCUT=2,
        #endif
        #ifdef KEY_SETTINGS
        STNG_KEY=4,
        #endif
        #ifdef MOUSE_SETTINGS
        STNG_MOUSE_BUTTON=5,
        STNG_MOUSE_AXIS=6,
        STNG_MOUSE_SENSITIVITY=7,
        #endif
        #ifdef JOY_SETTINGS
        STNG_JOY_AXIS=8,
        STNG_JOY_BALL=9,
        STNG_JOY_HAT=10,
        STNG_JOY_BUTTON=11,
        #endif
        #ifdef CONTROLLER_SETTINGS
        STNG_CONTROLLER_AXIS=12,
        STNG_CONTROLLER_BUTTON=13,
        #endif
        #ifdef  AUDIO_SETTINGS
        STNG_AUDIO_VOL=14,
        STNG_AUDIO_3D=15 
        #endif
        #ifdef VIDEO_SETTINGS
        STNG_VIDEO_RES=16
        STNG_VIDEO_MODE=17
        #endif
        #ifdef USER_SETTINGS
        // Values can be null , uint, int , bool , double , arr obj
        STNG_USER_BOOLEAN,
        STNG_USER_DOUBLE,
        STNG_USER_STRING,
        STNG_USER_ARRAY,
        STNG_USER_OBJECT
        #endif
    }STNG;
    typedef std::string cat ;  
    typedef std::pair<std::string, void(*stng)() > stng ;

    typedef uint cati ;
    typedef uint stngi ;

    std::string filePath  ;


    bimap<stng , STNG> stng  ;
// If keys hold object values they are treated as category. We also have an empty category ""
    bimap<cat, bimap< stng, STNG > cat_stng_bimap





    stng get_stng(uint stng_index){
        return stng_arr[stng_index]->first
    };

// Default is press
// syntax is obj.obj.field.PRESS_MODE
 enum PRESS_MODE {
        PRESS=0,
        HOLD=1,
        TOGGLE=2
    };
    bimap<std::string , PRESS_MODE> str_press_mode_bimap = {
        {"press", PRESS_MODE.PRESS},
        {"hold" , PRESS_MODE.HOLD},
        {"toggle",PRESS_MODE.TOGGLE}
    }


#ifdef KEY_SETTINGS    
    bimap<SDL_Keycode , std::pair<stng* , PRESS_MODE> > key_stng  ;
    void keyRecord(stng setting){

    };
    void keyTostr(SDL_KeyCode key){

    };
    void modToStr(SDL_KeyMod mod){

    };
    SDL_KeyCode strToKey(std::string key){

    };
    SDL_Keymod strToMod(std::string mod){

    };
#endif
// Any shortcut must start with a KeyMod 
#ifdef KEY_SHORTCUTS
   
   typedef std::pair<std::vector<SDL_Keymod> , SDL_KeyCode > shortcut ; 
    
    bimap<shortcut, stng*> shortcut_stng ;    
    void shortcutRecord(stng setting){

    };
    bool isValidShortcut(std::array<SDL_KeyCode> key_arr){

    };
    bool IsKeyMod(SDL_KeyCode keyc ){

    }
#endif
#define KEY_CHORD
   
    typedef shortcut chord ;
    bimap<chord, stng> chord_stng ;
    

    void addChordSmall(chord_small ch_sm , stng setting){
        SEI_SETTINGS chord_small_stng.[ch_sm]=setting ;
        SEI_SETTINGS stng_chord_small[*setting]=ch_sm ;
    };
    void addChordBig(chord_big ch_bg , stng setting){
        SEI_SETTINGS chord_big_stngs[ch_bg]=setting ; 
        SEI_SETTINGS stngs_chord_big[&setting] = ch_bg ; 
    };
    std::string submitChordShortcut(){

    }
    bool detectChord(){
        if( ( SDL_GetModState() & SEI_SETTINGS chord_shortcut.first ) && SDL_GetKeyboardState(NULL)[SEI_SETTINGS chord_shortcut.second] ) {
            SEI_SETTINGS chord_start = true ;
        }
        else return false ;
    };
    bool ChordStart(){
        return chord_start ;
    };
    void chordRecord(){

    }
#endif
#ifdef MOUSE_SETTINGS
    bimap<uint32, stng> mouse_button_stng ;
    int sensitivty ;
#ifdef MOUSE_AXIS
    stng x_axis ; bool x_inverted ;
    stng y_axis ; bool y_inverted ;
    
#endif
#endif
#ifdef JOY_SETTINGS
    typedef std::pair<SDL_JoystickID , uint8> joy_axis; 
    typedef std::pair<SDL_JoystickID , uint8> joy_ball;
    typedef std::tuple<SDL_JoystickID , uint8 , uint8> joy_hat; 
    typedef std::pair<SDL_JoystickID , uint8> joy_button;     
    
    bimap<joy_axis, stng> joy_axis_stng ;
    bimap<joy_ball, stng> joy_ball_stng ;
    bimap<joy_hat, stng> joy_hat_stng ;
    bimap<joy_button, stng> joy_button_stng ;
#endif
#ifdef CONTROLLER_SETTINGS
    typedef std::pair<SDL_JoystickID, uint8> controller_axis ; 
    typedef std::pair<SDL_JoystickID, uint8> controller_button ;
    bimap<controller_axis, stng> controller_axis_stng;
    bimap<controller_button, stng> controller_button_stng ;
    void JoyAxisRecord(stng setting){

    };
#endif


#ifdef TOUCH_SETTINGS
#endif
// TODO Gesture settings
#ifdef GESTURE_SETTINGS
#endif
#ifdef DGEST_SETTINGS
// TODO Dollar gesture
#endif
#ifdef AUDIO_SETTINGS
    uint volume ;
    void set_volume(uint vol){
        SEI_SETTINGS volume = vol ; 
    };
#endif
#define VIDEO_SETTINGS
#ifdef VIDEO_SETTINGS
    int xres ; int yres ;
    enum DisplayMode{
    DM_Windowed=0,
    DM_FullScreenWindowed=1,
    DM_FullScreen=2
};
    DisplayMode displayMode  ; 
    void get_video_mode(DisplayMode mode){
         switch(mode){
            case: DM_Windowed {
                return 0; 
            }
            case: DM_FullScreenWindowed {
                return SDL_WINDOW_FULLSCREEN_DESKTOP
            }
            case: DM_FullScreen {
               return  SDL_WINDOW_FULLSCREEN
            };
        }
    }
    void set_video_mode(SDL_Window* window, DisplayMode m ){
        SEI_SETTINGS displayMode = m ;
        SDL_SetWindowFullscreen(window , get_video_mode(m));
    };
    void set_video_res(int xres,  int yres , SDL_Window* window){
        SEI_SETTINGS xres = xres ; SEI_SETTINGS yres = yres ; 
        SDL_SetWindowSize(window, xres,yres);
    };
    void change_video_settings(int xres, int yres , SDL_Window* window, DisplayMode mode){
        set_video_mode(window , mode);
        set_video_res(xres,yres); 
    }
   
#endif
#ifdef USER_SETTINGS
    bimap<std::string , bool > booleans;
    bimap<std::string , int> ints ; 
    bimap<std::string , double> doubles;
    bimap<std::string , std::string> strings ;  
#endif

    union trigger {

    };



    #define ENUM_MAP(n) {#n, ##n},
    #define STRINGIZE(n) #n 
    #define SDL_APPEND(n) SDL_##n
    #define SDLK_APPEND(n) SDLK_##n
   
    #ifdef KEY_SETTINGS
    bool kmod_any = false ; // Flag to control whether to accept any modifier key in setting
    
    const bimap<SDL_KeyCode , SDL_KeyCode> kp_key = {
        {SDLK_KP_LEFTPAREN, SDLK_LEFTPAREN },
        {SDLK_KP_RIGHTPAREN, SDLK_RIGHTPAREN },
        {SDLK_KP_TAB, SDLK_TAB },
        {SDLK_KP_BACKSPACE, SDLK_BACKSPACE },
        {SDLK_KP_PERCENT, SDLK_PERCENT },
        {SDLK_KP_LESS, SDLK_LESS },
        {SDLK_KP_GREATER, SDLK_GREATER },
        {SDLK_KP_AMPERSAND, SDLK_AMPERSAND },
        {SDLK_KP_COLON, SDLK_COLON },
        {SDLK_KP_HASH, SDLK_HASH },
        {SDLK_KP_SPACE, SDLK_SPACE },
        {SDLK_KP_AT, SDLK_AT },
        {SDLK_KP_EXCLAIM, SDLK_EXCLAIM },
        {SDLK_KP_CLEAR, SDLK_CLEAR },
        {SDLK_KP_LEFTPAREN, SDLK_LEFTPAREN },
        {SDLK_KP_RIGHTPAREN, SDLK_RIGHTPAREN },
        {SDLK_KP_TAB, SDLK_TAB },
        {SDLK_KP_BACKSPACE, SDLK_BACKSPACE },
        {SDLK_KP_POWER, SDLK_POWER },
        {SDLK_KP_PERCENT, SDLK_PERCENT },
        {SDLK_KP_LESS, SDLK_LESS },
        {SDLK_KP_GREATER, SDLK_GREATER },
        {SDLK_KP_AMPERSAND, SDLK_AMPERSAND },
        {SDLK_KP_COLON, SDLK_COLON },
        {SDLK_KP_HASH, SDLK_HASH },
        {SDLK_KP_SPACE, SDLK_SPACE },
        {SDLK_KP_AT, SDLK_AT },
        {SDLK_KP_EXCLAM, SDLK_EXCLAM },
    };
    bool kp_same = true ; // Flag to control whether or not to accept keypad codes as same as any other
    #define STR_MAP_SDLK(n) { #n , SDLK_##n},
  
        const bimap<std::string, SDL_KeyCode> str_key {
    STR_MAP_SDLK(UNKNOWN)
    STR_MAP_SDLK(RETURN)
    STR_MAP_SDLK(ESCAPE)
    STR_MAP_SDLK(BACKSPACE)
    STR_MAP_SDLK(TAB)
    STR_MAP_SDLK(SPACE)
    STR_MAP_SDLK(EXCLAIM)
    STR_MAP_SDLK(QUOTEDBL)
    STR_MAP_SDLK(HASH)
    STR_MAP_SDLK(PERCENT)
    STR_MAP_SDLK(DOLLAR)⌈
    STR_MAP_SDLK(AMPERSAND)
    STR_MAP_SDLK(QUOTE)
    STR_MAP_SDLK(LEFTPAREN)
    STR_MAP_SDLK(RIGHTPAREN)
    STR_MAP_SDLK(ASTERISK)
    STR_MAP_SDLK(PLUS)
    STR_MAP_SDLK(COMMA)
    STR_MAP_SDLK(MINUS)
    STR_MAP_SDLK(PERIOD)
    STR_MAP_SDLK(SLASH)
    STR_MAP_SDLK(0)
    STR_MAP_SDLK(1)
    STR_MAP_SDLK(2)
    STR_MAP_SDLK(3)
    STR_MAP_SDLK(4)
    STR_MAP_SDLK(5)
    STR_MAP_SDLK(6)
    STR_MAP_SDLK(7)
    STR_MAP_SDLK(8)
    STR_MAP_SDLK(9)
    STR_MAP_SDLK(COLON)
    STR_MAP_SDLK(SEMICOLON)
    STR_MAP_SDLK(LESS)
    STR_MAP_SDLK(EQUALS)
    STR_MAP_SDLK(GREATER)
    STR_MAP_SDLK(QUESTION)
    STR_MAP_SDLK(AT)
    STR_MAP_SDLK(LEFTBRACKET)
    STR_MAP_SDLK(BACKSLASH)
    STR_MAP_SDLK(RIGHTBRACKET)
    STR_MAP_SDLK(CARET)
    STR_MAP_SDLK(UNDERSCORE)
    STR_MAP_SDLK(BACKQUOTE)
    STR_MAP_SDLK(a)
    STR_MAP_SDLK(b)
    STR_MAP_SDLK(c)
    STR_MAP_SDLK(d)
    STR_MAP_SDLK(e)
    STR_MAP_SDLK(f)
    STR_MAP_SDLK(g)
    STR_MAP_SDLK(h)
    STR_MAP_SDLK(i)
    STR_MAP_SDLK(j)
    STR_MAP_SDLK(k)
    STR_MAP_SDLK(l)
    STR_MAP_SDLK(m)
    STR_MAP_SDLK(n)
    STR_MAP_SDLK(o)
    STR_MAP_SDLK(p)
    STR_MAP_SDLK(q)
    STR_MAP_SDLK(r)
    STR_MAP_SDLK(s)
    STR_MAP_SDLK(t)
    STR_MAP_SDLK(u)
    STR_MAP_SDLK(v)
    STR_MAP_SDLK(w)
    STR_MAP_SDLK(x)
    STR_MAP_SDLK(y)
    STR_MAP_SDLK(z)
    STR_MAP_SDLK(CAPSLOCK)
    STR_MAP_SDLK(F1)
    STR_MAP_SDLK(F2)
    STR_MAP_SDLK(F3)
    STR_MAP_SDLK(F4)
    STR_MAP_SDLK(F5)
    STR_MAP_SDLK(F6)
    STR_MAP_SDLK(F7)
    STR_MAP_SDLK(F8)
    STR_MAP_SDLK(F9)
    STR_MAP_SDLK(F10)
    STR_MAP_SDLK(F11)
    STR_MAP_SDLK(F12)
    STR_MAP_SDLK(PRINTSCREEN)
    STR_MAP_SDLK(SCROLLLOCK)
    STR_MAP_SDLK(PAUSE)
    STR_MAP_SDLK(INSERT)
    STR_MAP_SDLK(HOME)
    STR_MAP_SDLK(PAGEUP)
    STR_MAP_SDLK(DELETE)
    STR_MAP_SDLK(END)
    STR_MAP_SDLK(PAGEDOWN)
    STR_MAP_SDLK(RIGHT)
    STR_MAP_SDLK(LEFT)
    STR_MAP_SDLK(DOWN)
    STR_MAP_SDLK(UP)
    STR_MAP_SDLK(NUMLOCKCLEAR)
    STR_MAP_SDLK(KP_DIVIDE)
    STR_MAP_SDLK(KP_MULTIPLY)
    STR_MAP_SDLK(KP_MINUS)
    STR_MAP_SDLK(KP_PLUS)
    STR_MAP_SDLK(KP_ENTER)
    STR_MAP_SDLK(KP_1)
    STR_MAP_SDLK(KP_2)
    STR_MAP_SDLK(KP_3)
    STR_MAP_SDLK(KP_4)
    STR_MAP_SDLK(KP_5)
    STR_MAP_SDLK(KP_6)
    STR_MAP_SDLK(KP_7)
    STR_MAP_SDLK(KP_8)
    STR_MAP_SDLK(KP_9)
    STR_MAP_SDLK(KP_0)
    STR_MAP_SDLK(KP_PERIOD)
    STR_MAP_SDLK(APPLICATION)
    STR_MAP_SDLK(POWER)
    STR_MAP_SDLK(KP_EQUALS)
    STR_MAP_SDLK(F13)
    STR_MAP_SDLK(F14)
    STR_MAP_SDLK(F15)
    STR_MAP_SDLK(F16)
    STR_MAP_SDLK(F17)
    STR_MAP_SDLK(F18)
    STR_MAP_SDLK(F19)
    STR_MAP_SDLK(F20)
    STR_MAP_SDLK(F21)
    STR_MAP_SDLK(F22)
    STR_MAP_SDLK(F23)
    STR_MAP_SDLK(F24)
    STR_MAP_SDLK(EXECUTE)
    STR_MAP_SDLK(HELP)
    STR_MAP_SDLK(MENU)
    STR_MAP_SDLK(SELECT)
    STR_MAP_SDLK(STOP)
    STR_MAP_SDLK(AGAIN)
    STR_MAP_SDLK(UNDO)
    STR_MAP_SDLK(CUT)
    STR_MAP_SDLK(COPY)
    STR_MAP_SDLK(PASTE)
    STR_MAP_SDLK(FIND)
    STR_MAP_SDLK(MUTE)
    STR_MAP_SDLK(VOLUMEUP)
    STR_MAP_SDLK(VOLUMEDOWN)
    STR_MAP_SDLK(KP_COMMA)
    STR_MAP_SDLK(KP_EQUALSAS400)
    STR_MAP_SDLK(ALTERASE)
    STR_MAP_SDLK(SYSREQ)
    STR_MAP_SDLK(CANCEL)
    STR_MAP_SDLK(CLEAR)
    STR_MAP_SDLK(PRIOR)
    STR_MAP_SDLK(RETURN2)
    STR_MAP_SDLK(SEPARATOR)
    STR_MAP_SDLK(OUT)
    STR_MAP_SDLK(OPER)
    STR_MAP_SDLK(CLEARAGAIN)
    STR_MAP_SDLK(CRSEL)
    STR_MAP_SDLK(EXSEL)
    STR_MAP_SDLK(KP_00)
    STR_MAP_SDLK(KP_000)
    STR_MAP_SDLK(THOUSANDSSEPARATOR)
    STR_MAP_SDLK(DECIMALSEPARATOR)
    STR_MAP_SDLK(CURRENCYUNIT)
    STR_MAP_SDLK(CURRENCYSUBUNIT)
    STR_MAP_SDLK(KP_LEFTPAREN)
    STR_MAP_SDLK(KP_RIGHTPAREN)
    STR_MAP_SDLK(KP_LEFTBRACE)
    STR_MAP_SDLK(KP_RIGHTBRACE)
    STR_MAP_SDLK(KP_TAB)
    STR_MAP_SDLK(KP_BACKSPACE)
    STR_MAP_SDLK(KP_A)
    STR_MAP_SDLK(KP_B)
    STR_MAP_SDLK(KP_C)
    STR_MAP_SDLK(KP_D)
    STR_MAP_SDLK(KP_E)
    STR_MAP_SDLK(KP_F)
    STR_MAP_SDLK(KP_XOR)
    STR_MAP_SDLK(KP_POWER)
    STR_MAP_SDLK(KP_PERCENT)
    STR_MAP_SDLK(KP_LESS)
    STR_MAP_SDLK(KP_GREATER)
    STR_MAP_SDLK(KP_AMPERSAND)
    STR_MAP_SDLK(KP_DBLAMPERSAND)
    STR_MAP_SDLK(KP_VERTICALBAR)
    STR_MAP_SDLK(KP_DBLVERTICALBAR)
    STR_MAP_SDLK(KP_COLON)
    STR_MAP_SDLK(KP_HASH)
    STR_MAP_SDLK(KP_SPACE)
    STR_MAP_SDLK(KP_AT)
    STR_MAP_SDLK(KP_EXCLAM)
    STR_MAP_SDLK(KP_MEMSTORE)
    STR_MAP_SDLK(KP_MEMRECALL)
    STR_MAP_SDLK(KP_MEMCLEAR)
    STR_MAP_SDLK(KP_MEMADD)
    STR_MAP_SDLK(KP_MEMSUBTRACT)
    STR_MAP_SDLK(KP_MEMMULTIPLY)
    STR_MAP_SDLK(KP_MEMDIVIDE)
    STR_MAP_SDLK(KP_PLUSMINUS)
    STR_MAP_SDLK(KP_CLEAR)
    STR_MAP_SDLK(KP_CLEARENTRY)
    STR_MAP_SDLK(KP_BINARY)
    STR_MAP_SDLK(KP_OCTAL)
    STR_MAP_SDLK(KP_DECIMAL)
    STR_MAP_SDLK(KP_HEXADECIMAL)
    STR_MAP_SDLK(LCTRL)
    STR_MAP_SDLK(LSHIFT)
    STR_MAP_SDLK(LALT)
    STR_MAP_SDLK(LGUI)
    STR_MAP_SDLK(RCTRL)
    STR_MAP_SDLK(RSHIFT)
    STR_MAP_SDLK(RALT)
    STR_MAP_SDLK(RGUI)
    STR_MAP_SDLK(MODE)
    STR_MAP_SDLK(AUDIONEXT)
    STR_MAP_SDLK(AUDIOPREV)
    STR_MAP_SDLK(AUDIOSTOP)
    STR_MAP_SDLK(AUDIOPLAY)
    STR_MAP_SDLK(AUDIOMUTE)
    STR_MAP_SDLK(MEDIASELECT)
    STR_MAP_SDLK(WWW)
    STR_MAP_SDLK(MAIL)
    STR_MAP_SDLK(CALCULATOR)
    STR_MAP_SDLK(COMPUTER)
    STR_MAP_SDLK(AC_SEARCH)
    STR_MAP_SDLK(AC_HOME)
    STR_MAP_SDLK(AC_BACK)
    STR_MAP_SDLK(AC_FORWARD)
    STR_MAP_SDLK(AC_STOP)
    STR_MAP_SDLK(AC_REFRESH)
    STR_MAP_SDLK(AC_BOOKMARKS)
    STR_MAP_SDLK(BRIGHTNESSDOWN)
    STR_MAP_SDLK(BRIGHTNESSUP)
    STR_MAP_SDLK(DISPLAYSWITCH)
    STR_MAP_SDLK(KBDILLUMTOGGLE)
    STR_MAP_SDLK(KBDILLUMDOWN)
    STR_MAP_SDLK(KBDILLUMUP)
    STR_MAP_SDLK(EJECT)
    STR_MAP_SDLK(SLEEP)
    STR_MAP_SDLK(APP1)
    STR_MAP_SDLK(APP2)
    STR_MAP_SDLK(AUDIOREWIND)
    STR_MAP_SDLK(AUDIOFASTFORWARD)
    STR_MAP_SDLK(SOFTLEFT)
    STR_MAP_SDLK(SOFTRIGHT)
    STR_MAP_SDLK(CALL)
    STR_MAP_SDLK(ENDCALL)
    };
    
   
    const std::bimap<SDL_KeyCode , SDL_KeyMod> key_mod = {
        {SDLK_LSHIFT ,KMOD_LSHIFT} ,
        {SDLK_RSHIFT ,KMOD_RSHIFT} ,
        {SDLK_LCTRL ,KMOD_LCTRL} ,⌈
        {SDLK_RCTRL ,KMOD_RCTRL} ,
        {SDLK_LALT ,KMOD_LALT} ,
        {SDLK_RALT ,KMOD_RALT} ,
        {SDLK_LGUI ,KMOD_LGUI} ,
        {SDLK_RGUI ,KMOD_RGUI} ,
        {SDLK_NUMLOCKCLEAR ,KMOD_NUM} ,
        {SDLK_CAPSLOCK ,KMOD_CAPS} ,
        {SDLK_MODE ,KMOD_MODE} ,
        {SDLK_SCROLLLOCK ,KMOD_SCROLL} ,
    } ;
  
    #endif
    inline std::string appendNum(sdt::string name, uint no){
        std::string n = name ;
        return n + std::to_string(no) ;
    };
    #ifdef MOUSE_SETTINGS 
    const std::string MouseButton_name = "Mouse"; // TO be appended with button eg: "Mouse1"
    const std::string MouseX_name = "MouseX";
    const std::string MouseY_name = "MouseY";
    #endif
    #ifdef JOY_SETTINGS
    // All to be appended with number
    const std::string JoyButton_name = "Joy";
    const std::string JoyBall_name = "Ball";
    const std::string JoyHat_name = "Hat" ;
    const std::string Hat_CENTERED_name = "CENTERED";
    const std::string Hat_UP_name  = "UP"; 
    const std::string Hat_RIGHT_name = "RIGHT"; 
    const std::string Hat_DOWN_name = "DOWN"; 
    const std::string Hat_LEFT_name = "LEFT"; 
    const std::string Hat_RIGHTUP_name = "RIGHTUP"; 
    const std::string Hat_RIGHTDOWN_name = "RIGHTDOWN"; 
    const std::string Hat_LEFTUP_name = "LEFTUP"; 
    const std::string Hat_LEFTDOWN_name  = "LEFTDOWN"; 
    const std::string JoyAxis_name=  "JoyAxis";

    #endif
    #ifdef CONTROLLER_SETTINGS // TODO presets
    const std::string ControllerButton_mame = "Controller" ;
    const std::string ControllerAxis_name = "ControllerAxis"
    #endif

   
    void settingsReadResolve(stng setting, STNG type, boost::json::value val){
        switch(type) {
            #ifdef KEY_CHORDS
            case: STNG_CHORD {
                setting
            }
            #endif
            #ifdef KEY_SHORTCUTS
            case: STNG_SHORTCUT {
                setting
            }
            #endif
            #ifdef KEY_SETTINGS
            case: STNG_KEY {
                setting
            }
            #endif
            #ifdef MOUSE_SETTINGS
            case: STNG_MOUSE_BUTTON {
                setting
            }
            case: STNG_MOUSE_AXIS {
                setting
            }
            case: STNG_MOUSE_SENSITIVITY {
                setting
            }
            #endif
            #ifdef JOY_SETTINGS
            case: STNG_JOY_AXIS {
                setting
            }
            case: STNG_JOY_BALL {
                setting
            }
            case: STNG_JOY_HAT, {
                setting
            }
            case: STNG_JOY_BUTTON, {
                setting
            }
            #endif
            #ifdef CONTROLLER_SETTINGS
            case: STNG_CONTROLLER_AXIS {
                setting
            }
            case: STNG_CONTROLLER_BUTTON {
                setting
            }
            #endif
            #ifdef  AUDIO_SETTINGS
            case: STNG_AUDIO_VOL {
                setting
            }
            case: STNG_AUDIO_3D  {
                setting
            }
            #endif
            #ifdef VIDEO_SETTINGS
            case: STNG_VIDEO_RES {
                setting
            }
            case: STNG_VIDEO_MODE {
                setting
            }
            #endif
            #ifdef USER_SETTINGS
            case: STNG_USER_BOOLEAN {
                setting
            }
            case: STNG_USER_INT {
                setting
            }
            case: STNG_USER_DOUBLE {
                setting
            }
            case: STNG_USER_STRING {
                setting
            }
            #endif
        }
    }
    
    void saveSettings(){
        
        std::ofstream f.open(SEI_SETTINGS file);
        boost::json::object obj ;
        // Convert to json object
        for (const auto &cat : SEI_SETTINGS cat_bimap ){
                for(const auto &setting : cat ){
                    switch(setting.second){
                        #ifdef KEY_CHORDS
                        case: STNG_CHORD {
                            
                        }l
                        #endif
                        #ifdef KEY_SHORTCUTS
                        case: STNG_SHORTCUT {
                            
                        }
                        #endif
                        #ifdef KEY_SETTINGS
                        case: STNG_KEY {
                            
                        }
                        #endif
                        #ifdef MOUSE_SETTINGS
                        case: STNG_MOUSE_BUTTON {
                            
                        }
                        case: STNG_MOUSE_AXIS {
                            
                        }
                        case: STNG_MOUSE_SENSITIVITY {
                            
                        }
                        #endif
                        #ifdef JOY_SETTINGS
                        case: STNG_JOY_AXIS {
                            
                        }
                        case: STNG_JOY_BALL {
                            
                        }
                        case: STNG_JOY_HAT {
                            
                        };
                        case: STNG_JOY_BUTTON {
                            
                        };
                        #endif
                        #ifdef CONTROLLER_SETTINGS
                        case: STNG_CONTROLLER_AXIS {
                            
                        };
                        case: STNG_CONTROLLER_BUTTON {
                            
                        };
                        #endif
                        #ifdef  AUDIO_SETTINGS
                        case: STNG_AUDIO_VOL {
                            
                        };
                        case: STNG_AUDIO_3D {
                            
                        } 
                        #endif
                        #ifdef VIDEO_SETTINGS
                        case: STNG_VIDEO_RES {
                            
                        }
                        case: STNG_VIDEO_MODE {
                            
                        }
                        #endif
                        #ifdef USER_SETTINGS
                        case: STNG_USER_BOOLEAN {
                            
                        }
                        case: STNG_USER_INT {
                            
                        }
                        case: STNG_USER_DOUBLE {
                            
                        }
                        case: STNG_USER_STRING {
                            
                        }                     
                        #endif
                    }

                }

        };
    };


    // Return tokens sepparated by +
    std::array<std::string> tokenizeSTNG(std::string expr){
        std::string temp; 
        std::vector<std::string> arr ;
        for(const auto i : expr){
            if(i == "+"){
                arr.push_back(temp) ;
                continue ;
            }
            temp.append(i) ;
        };
        return arr ;
    };
    shortcut TokenizedToShortCut(std::array<std::string> arr){
        std::array<std::SDL_KeyCode> keys ;
        for(const auto &i : arr){
            SDL_KeyCode temp ;
            if( temp = SEI_SETTINGS str_to_key[i] != NULL ){
                if(SEI_SETTINGS key_to_mod[])
            }
        } 
    }
    std::array<std::string> tokenize(std::string str )

    std::pair<STNG, stng>  processStng(stng setting , boost::json::value val ){
        switch(val.kind)
        {
        case boost::json::kind::string:
            processTokenized(  setting::tokenize(val.to_string()));
            break;
        case boost::json::kind::int64 || boost::json::kind::uint64 ||  boost::json::kind::double_:
            return {setting}
            break;
        case boost::json::kind::bool_:
            std::cout << "Type: Boolean" << std::endl;
            break;
        case boost::json::kind::null:
            std::cout << "Type: Null" << std::endl;
            break;
        default:
            std::cout << "Type: Unknown" << std::endl;
            break;
        }
    }
    
    constexpr std::string setDefaults(){
        return ""; 
    };
     // As we read we want to know if any errors come up
    void ReportErr(uint ln , uint col , std::string line ;  std::string error ;) {
        #ifdef SETTINGS_SFWGUI_PROMPT
        SfwGui::OpenPopup("Error");

        if (SfwGui::BeginPopupModal("Error", NULL, SfwGuiWindowFlags_AlwaysAutoResize)) {
            std::string str = <"Error on ln: "+ ln + ", col: " + col + "of settings.json"
        SfwGui::Text(str);
        SfwGui::Separator();
        SfwGui::Text(line) ;
        SfwGui::Separator();
        SfwGui::Text(error);
        SfwGui::Separator();

            SfwGui::Text("Choose an option:");
         SfwGui::PushStyleColor(SfwGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 7.0f));
        if (SfwGui::Button("Load Defaults and save them later ")) {

            SfwGui::CloseCurrentPopup();
        }
        SfwGui::PopStyleColor();
        SfwGui::Separator();

        if (SfwGui::Button("Try Again ")) {
            selectedOption = 2;
            SfwGui::CloseCurrentPopup();
        }

        SfwGui::EndPopup();
    }
        #else
        std::cout<<"Error on ln: "<<ln <<", col: "<<col <<"of settings.json" << std::endl ;
        
        std::cout<<line<<endl;
        std::cout<<Error
        #endif

    };
    
    size_t readSettings(){ // And deposit everything
        std::ifstream f(SEI_SETTINGS file);
        if(!f.is_open()){
            constexpr std::string jsonString(SEI_SETTINGS setDefaults );
        }
        else {
            std::string jsonString((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

        }
        f.close() ;
        try {
        
        json::value jv = json::parse(jsonString);
        delete jsonString ;
        if (jv.is_object()) {
            json::object jsonObj = jv.as_object();
            for (const auto &cat : jsonObj){
                    for(const auto &setting : cat.second() ){ // TODO
                        std::pair<STNG > = processStng(setting.first, setting.second)
                        stng st = {setting.first, SEI_SETTINGS stngs_map[setting.first] };
                        SEI_SETTINGS cat_bimap[cat.first][cat.second]=settingType ; 
                }
            }
        } 
        catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
        }
        }
    }
    
    void reload(){
        SEI_SETTINGS readSettings();
    };
    settings(std::string fileName, std::map<category,std::map<stng,STNG>> map){

        SEI_SETTINGS file = fileName; 
        SEI_SETTINGS cat_bimap = map ; 
        
        SEI_SETTINGS readSettings();
        std::vector<std::pair<*stng,  *category>> stng_vec ;
        size_t n= 0
        for( auto &cat : SEI_SETTINGS cat_bimap){
                for(auto &set : cat.second){
                    stng_vec[n].first = set ;
                    stng_vec[n].second = cat ;
                    n++ ;
                }
        }
        std::array<std::pair<*stng, *category > , n> arr ;
        SEI_SETTINGS stng_arr = arr; 
    };

    sei_settings(std::string file){
        SEI_SETTINGS size = SEI_SETTINGS readSettings();
    }
}

