#ifndef IMPL_HPP
#define IMPL_HPP
/*/
Capablities
SYS_MOUSE
SYS_KEY
SYS_JOY
SYS_CONT
SYS
SYS_FSWATCH
SYS_KEYCOMBO
SYS_MOUSECOMBO
SYS_JOY
SYS_COMBO
*/
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "impl.hpp"
#include "implmain.hpp"
#include <stratum/petri/vects.hpp>
#include <stratum/petri/queue.hpp>
#include <stratum/petri/list.hpp>
#include <vector>
#include <memory>
#include <string>
#include <atomic>
#include <future>
#include <cpuid.h>

using namespace std;
#define VEC_MAX 1000


#include <strata/backend/implgl.hpp>
#ifdef STRATA_IMPL_WIN
#include <strata/backend/impl_win.hpp>

#endif
#ifdef STRATA_IMPL_ANDROID
#include <strata/backend/impl_android.hpp>
#ifdef STRATA_IMPL_LINUX
#include <strata/backend/impl_linux.hpp>
#define STRATA_IMPL_WASM
#include <strata/backend/impl_wasm.hpp>
#endif


struct cpu_feat {
    bool pse=false;
// SIMD extensions like
bool SSE=false;bool AVX=false ; //bool AVX2=false; bool AVX_512=false;
bool AES_NI=false;
//Virtualization Support:
bool hypervisor;
bool VT_x=false ;//(Intel) 
bool AMD_V=false;
//Multithreading and Parallelism:
bool HTT=false;
// Cores and logical processors
int cores=1; int logical=1;
// Hardware Capabilities:
//Support for features like 64-bit operation 
bool x64=false;
// TSX (Transactional Synchronization Extensions).
bool TSX=false;
} ;

    struct cpu_feat_ext {
        bool crypto = false;  // Feats:

        // neural net 
        bool nn = false; // Feats:

        // Acceleration
        bool other_accel = false; // Feats:

    };
template <typename shared,typename procinstance>
class strata_env{

    
    public:
    using sharedty= shared; 
    void 
    cpu_feat get_cpu_feat(){
        cpu_feat cpuf;
#if defined(__x86_64__) || defined(__i386__)
     unsigned int eax, ebx, ecx, edx;

    // Query standard function 1 (Processor Info and Feature Bits)
    __cpuid(1, eax, ebx, ecx, edx);
    cpuf.SSE= edx&(1<<25);
    cpuf.AVX= ecx&(1<<28);
    cpuf.pse= eax&(1<<3);
    cpuf.hypervisor=ecx(1<<31);
    
#endif
return cpuf;
    };
     void init(int flags){
        // Get cpu features
        
     }; // System initialization
    #ifdef STRATA_IMPL_VK
    virtual void initVk(win w, VkInstance inst, VKSurfaceKHR* surface, procinstance hInstance);
    #endif
    #ifdef STRATA_IMPL_DX
    virtual void initDx(){std::cerr<<"System has no dx implementation"};
    #endif
    void cpu_info();
    virtual void load_shared(char* p);
    virtual void unload_shared(shared s);  
};
    

namespace impl {
#include "impl.def.hpp"
#define MAXPOLL 10
template<typename T , size_t size>
struct eventq  {
    T d[size];
    int i[size] ;
    size_t pos=0;
    T& operator[](int s){return this->d[s>=0?(size_t)s:sizes+s];}
    T& operator[](size_t s){return this->d[s];}
    void clear(){pos = 0;}
    int lastn(){return d[pos]};)
    void push(T&& s){if(pos==size-1){clear();} d[pos] = s;++pos  ;}
    void push(T&& s,int ind){if(sizes==size-1){clear();return;} d[pos] = s;i[sizes]=ind;++pos  ;}


    void operator+=(T&& s){push(s);};
    bool operator==(T s){for(const T& it  : d){if(it == s){return true;};} return false;};

    eventq() {d.push_back(T()); sizes= 1; pos = d.begin();}
};



template <typename T>
using evq = eventq<T,MAXPOLL>;
#ifdef STRATA_CAP_MOUSE
using click        = int        ;// _click    
using dbclick      = int        ;// _dbclick
using mousedown    = int        ;// _mousedown        
using mouseup      = int        ;// _mouseup      
using mouse_move   = glm::ivec2 ;// _mouse_move
using mouse_wheel  = int        ;// _mouse_wheel       
using mouse_wheelh = int        ;// _mouse_wheelh;
struct MOUSE {  // TODO filters for all
const uint flag=_MOUSE;
    mouse_move  last_location;
    evq<click >       last_click; 
    evq<dbclick >     last_db_click;     
    evq<mousedown >   last_down;          
    evq<mouseup >     last_up;        
    evq<mouse_move>  last_move;           
    evq<mouse_wheel> last_wheel;     
    evq<mouse_wheelh> last_wheelh;     
    uint getlastKey(){return this->last_down.lastn();};
    uint getlastaxis(){mouse_move l = this->last_move.lastn(); return (( (l.x <0) ? (-l.x) : l.x )>((l.y < 0) ? (-l.y) : l.y)) ? 0 : 1; };

    virtual void cursorHide();
    virtual void cursorShow();
    void clicked(click t){return this->last_click == t;};
    void dbclicked(dbclick t){return this->last_dbclick == t;};
    void down(mousedown t){return this->last_down == t;};
    void up(mouseup t){return this->last_up == t;};
    // void moved_gt(glm::ivec2 s);
    // void move_lt(glm::ivec2 s);
    // void 
    void clear()final{this->last_click.clear();this->last_down.clear();this->last_up.clear();this->last_press.clear();this->last_move.clear();this->last_wheel.clear();}
    bool detect_combo(int* s[2]){
        bool x=false;bool y=false;
            for(int i = 0 ; i < this->last_down.pos();i++){
                if(this->last_down[i]== s[j][0] ){
                    bool cond=false;
                    for(int k = 0 ; k < this->last_up.pos();k++){if(this->last_up[k]==this->last_down[i]){cond=true};break;};
                    if(cond){continue;}
                    else {
                        if(x){y=true}
                        else x = true;
                    };
                }; 
                if(this->last_down[i]== s[j][1] ){
                    bool cond=false;
                    for(int k = 0 ; k < this->last_up.pos();k++){if(this->last_up[k]==this->last_down[i]){cond=true};break;};
                    if(cond){continue;}
                    else {
                        if(x){y=true}
                        else x = true;
                    };
                }; 
                if(x and y){return true};
        };
        return false;
    };
    int detect_combo(uint size_combos ,int* s[2]){

        for(int j = 0 ; j < size_combos){
            if(detect_combo(s[j])){return j};
        };
        return -1;
    };
    void up_check(int i){
        for(int i = 0 ; i<this->last_down.pos() ;i++ ){
            if(i==this->last_down.data();){this->last_down[i].data=-1; break;}
        };
    };
    // glm::vec2 get_pos(){return this->last_move.data()};
    // bool get_state(short int bt){return this->last_press.data==bt};
    

     void dbclick_cb(dbclick_cb ev, int index) final {last_dbclick.push(ev,index);}
     void click_cb(click_cb click,int index) final {last_click.push(click,index);}
     void move_cb(move_cb mv,int index) final {last_move.push(mv,index);};
     void down_cb(down_cb down,int index) final {last_down.push(down,index);};
     void up_cb(up_cb up,int index) final {up_check(up);last_up.push(up,index);};
     void wheel_cb(wheel_cb wheel,int index) final {last_wheel.push(wheel,index);};
     void wheelh_cb(wheelh_cb wheel,int index) final {last_wheelh.push(wheel,index);};
     void dbclick_cb(dbclick ev) final {last_dbclick+=ev;}
     void click_cb(click ev) final {last_click+=ev;}
     void move_cb(mouse_move ev) final {last_move+=ev;};
     void down_cb(mousedown ev) final {last_down+=ev;};
     void up_cb(mouseup ev) final { up_check(ev.data());last_up+=ev;};
     void wheel_cb(mouse_wheel ev) final {last_wheel+=ev;};
     void wheelh_cb(mouse_wheel ev) final {last_wheelh+=ev;};
    
     virtual glm::vec2 Pos(int index=0);
     virtual glm::vec2 WinPos();
    virtual void handle();
    virtual void _handle(){
        this->handle();

    };
    void init()override{
        this->_init();};
};
   

#endif
#ifdef STRATA_CAP_KEY
using keyup = int,        ;// _keyup>; // x button, y index    
using keydown = int,        ;// _keydown>; // x button, y index      
using keypress = int         ;//,_keypress>; // x button, y index       
using keycombo = glm::ivec4   ;//,_keycombo> ; //-1 is 
enum metastate {
    CRTL,
    ALT,
    LALT,
    RALT,
};
struct KEY   {
 public:
    bool meta,lmeta,rmeta;
    bool ctrl, lctrl, rctrl;
    bool alt, lalt, ralt;
    bool shift, lshift, rshift;
    evq<keyup>    last_keyup;
    evq<keydown>  last_keydown;
    evq<keypress> last_keypress;
        uint getlastKey(){return this->last_keydown.lastn();};

    bool up_cb(char key,int index) final {this->last_keyup.push(keyup(key),index);};
    bool down_cb(char key,int index) final {this->last_keydown.push(keydown(key),index);};    
    bool press_cb(char key,int index) final {this->last_keypress.push(keypress(key),index);};    
    bool up_cb(up ev) final {this->last_keyup.push(ev);};
    bool down_cb(down ev) final {this->last_keydown.push(ev);};    
    bool press_cb(press ev) final {this->last_keypress.push(ev);};    
    
    virtual void handlemeta();
    bool check_combo( uint32_t kc){

    };
    virtual bool get_state(int key);
    bool resolve(void ev,evs flag){
        switch(flag){
            case _keyup :{this->last_keyup=(keyup)ev;return true;};
            case _keydown :{this->last_keydown=(keydown)ev;return true;};
            case _keypress :{this->last_keypress=(keypress)ev;return true;};
        };
        return false;
    };
    void clear()final{
        this->last_keyup.clear();
        this->last_keydown.clear();
        this->last_keypress.clear();        
    };
}; // index 
#endif
#ifdef STRATA_CAP_JOY
using joy_hat = int ;        //,_joy_hat>;  
using joy_axis = glm::vec2 ;        // x,y axis 
using joy_up = int ;        //,_joy_up>;    
using joy_down = int ;        //,_joy_down>;      
using joy_press = int ;        //,_joy_press>;     
using joy_rot = float ;
using joy_throt = float;
#define JOY_A
#define JOY_B
#define JOY_X
#define JOY_Y
#define JOY_L1
#define JOY_R1
#define JOY_LTHUMB
#define JOY_RTHUMB
struct  JOY   { // TODO handle multi input by calling multiple
public:
        evq<joy_hat>   last_hat;
        evq<joy_axis>  last_axis;

        evq<joy_up>    last_up;  
        evq<joy_down>  last_down;    
        evq<joy_press> last_press;   
        evq<joy_throt> last_throt;   
        evq<joy_rot> last_rot;   
    uint getlastKey(){ this->last_down.lastn();};
    uint getlastaxis(){joy_axis l = this->last_axis.lastn(); return (( (l.x <0) ? (-l.x) : l.x )>((l.y < 0) ? (-l.y) : l.y)) ? 0 : 1;};

        
        uint num =1;
        uint period = 100;
        // int maxbtn;
        #ifndef no_maxbtn
        #define maxbtn 16
        #endif
        virtual int _numJoys();
        void clear(){this->last_hat.clear();this->last_axis.clear();this->last_up.clear();this->last_down.clear();this->last_press.clear();};
        joycap getCap(int index);
        void setperiod(uint ms) {this->period=ms;};
        int numJoys(){ this->numJoys(); return this->num;}

void hat_cb(joy_hat ev) final {this->last_hat+=ev;};      //void push_up(joy_hat ev) final {this->evmain.push(ev);};
void up_cb(joy_up ev) final {this->last_up+=ev;};         //void push_up(joy_up ev) final {this->evmain.push(ev);};
void down_cb(joy_down ev) final {this->last_down+=ev;};   //void push_down(joy_down ev) final {this->evmain.push(ev);};
void press_cb(joy_press ev) final {this->last_press+=ev;};//void push_press(joy_press ev) final {this->evmain.push(ev);};
void axis_cb(joy_axis ev) final {this->last_axis+=ev;};   //void push_axis(joy_axis ev) final {this->evmain.push(ev);};
void hat_cb(int btn,int index) final {this->last_hat+=joy_hat(btn,index);};           //void push_up(int btn,int index) final {this->evmain.push(joy_hat(btn,index));};
void up_cb(int btn,int index) final {this->last_up+=joy_up(btn,index);};              //void push_up(int btn,int index) final {this->evmain.push(joy_up(btn,index));};
void down_cb(int btn,int index) final {this->last_down+=joy_down(btn,index);};        //void push_docb(int btn,int index) final {this->evmain.push(joy_down(btn,index));};    
void press_cb(int btn,int index) final {this->last_press+=joy_press(btn,index);};     //void push_pr_cb(int btn,int index) final {this->evmain.push(joy_press(btn,index));};    
void axis_cb(int16 axis,int index) final {this->last_axis+=joy_axis(axis,index);};    //void push_axcb(int16 axis,int index) final {this->evmain.push(joy_axis(axis,index));};    
void throt_cb(joy_throt ev){this->last_throt+=ev;};
void rotate_cb(joy_rot  ev){this->last_rot+=ev;};
    virtual int get_btn_state(int btn=-1 , int index=0;);
    virtual int get_axis_state(int axis=-1 , int index=0;);
    virtual int get_state(int key=-1 , int index=0;);
    virtual int get_hat_state(int hatpos=-1 , int index=0;); // usually 8 starting n;


    int connected_no ;
    virtual void _init()
    void connected_cb();
    virtual void init(){this->_init();};
      bool filter(short int type_flag){
        switch(type_flag){
            case _joy_axis: {return true;};
            case _joy_up: {return true;};
            case _joy_down: {return true;};
            case _joy_press: {return true;};
        };
        return false;
    };
    JOY() =default{};
};
#endif
#ifdef STRATA_CAP_CONT
using CONT_press= int;//        _CONT_press>;                    
using CONT_down = int;//        _CONT_down>; 
using CONT_up =   int;//        _CONT_up>; 
using CONT_dpad = int;//        _CONT_dpad>;
using CONT_axis = glm::vec2;//        _CONT_axis>;  // Axis index;
using CONT_trig = float;
struct CONT  {
public:
    evq<CONT_press> last_press;      
    evq<CONT_down>  last_down;     
    evq<CONT_up>    last_up;   
    evq<CONT_dpad>  last_dpad;     
    evq<CONT_axis>  last_laxis;     
    evq<CONT_axis>  last_raxis;
    evq<CONT_trigger> last_ltr;
    evq<CONT_trigger> last_rtr;
      uint getlastKey(){ this->last_down.lastn();};
    uint getlastaxis(){CONT_axis l ; this->last_laxis.lastn();CONT_axis r; this->last_raxis.lastn(); return (glm::abs(l)>glm::abs(r)) ? 0 : 1; };

    void clear(){
        this->last_press.clear();
        this->last_down.clear();
        this->last_up.clear();
        this->last_dpad.clear();
        this->last_laxis.clear();
        this->last_raxis.clear();
        this->last_tr.clear();
    };
    int num =0 ; 
    virtual void num();
    void clear()final{this->last_press.clear();this->last_down.clear();this->last_up.clear();this->last_dpad.clear();this->last_laxis.clear();this->last_raxis.clear();this->last_tr.clear();};
    bool trig_cb(CONT_trig ev,int index=0) final {this->last_tr+=ev;}
    bool up_cb(int btn,int index=0) final {this->last_up=CONT_up(btn,index);};                   //bool push_up(int btn,int index) final {this->evmain.push(CONT_up(btn,index));};
    bool down_cb(int btn,int index=0) final {this->last_down=CONT_down(btn,index);};             //bool push_down(int btn,int index) final {this->evmain.push(CONT_down(btn,index));};    
    bool press_cb(int btn,int index=0) final {this->last_press=CONT_press(btn,index);};          //bool push_press(int btn,int index) final {this->evmain.push(CONT_press(btn,index));};    
    bool laxis_cb(glm::ivec2 axis,int index=0) final {this->last_laxis=CONT_axis(axis,index);};  //bool push_laxis(glm::ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool raxis_cb(glm::ivec2 axis,int index=0) final {this->last_raxis=CONT_axis(axis,index);};  //bool push_raxis(glm::ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool dpad_cb(int axis,int index) final {this->last_dpad=CONT_dpad(axis,index);};         //bool push_dpad(int axis,int index) final {this->evmain.push(CONT_dpad(axis,index));};    
    
    bool trig_cb(CONT_trig ev) final {this->last_tr+=ev;}
    bool up_cb(CONT_up ev) final {this->last_up+= ev;};           // bool push_up(up ev) final {this->evmain.push(ev);};             
    bool down_cb(CONT_down ev) final {this->last_down+= ev;};     //       bool push_down(down ev) final {this->evmain.push(ev);};                 
    bool press_cb(CONT_press ev) final {this->last_press+= ev;};  //          bool push_press(press ev) final {this->evmain.push(ev));};                
    bool axis_cb(CONT_axis ev) final {this->last_axis+= ev;};     //       bool push_axis(axis ev) final {this->evmain.push(ev));};                
    bool dpad_cb(dpad ev) final {this->last_dpad+= ev;};          //  bool push_dpad(dpad ev) final {this->evmain.push(ev));};                

    
    virtual bool handle(int index=0);
    virtual bool mhandle();
     int get_state(int btn=-1,  int index=0); // If negative then means get all pressed
     int get_axis(int axis=-1,  int index=0 );
     int get_dpad(int index =0);


    void init();
    bool filter(short int type_flag){
        switch(type_flag){
            case _CONT_press: {return true;};
            case _CONT_down: {return true;};
            case _CONT_up: {return true;};
            case _CONT_axis: {return true;};
        };
        return false;
    };


};  // index
#endif
#ifdef STRATA_CAP_TOUCH
using touch_move =glm::vec4; ///,_touch_move>; //xy last zw move // glm::ivec4
using touch_tap  = glm::vec4; ///,_touch_tap sizex sizey
using touch_zoom = glm::vec4; ///,_touch_gesture>; // xy move,z rotate,w zoom
using touch_gesture = evq<glm::vec4*>; ///,_touch_zoom>; // rotate

struct TOUCH  { 
 public:
     evq<touch_tap> last_tap;
     evq<touch_tap> last_up;
     evq<touch_tap> last_down;
     evq<touch_move> last_move;
     evq<touch_zoom> last_zoom;
       uint getlastaxis(){touch_move l =this->last_move.lastn(); return (( (l.x <0) ? (-l.x) : l.x )>((l.y < 0) ? (-l.y) : l.y)) ? 0 : 1; };

     void clear(){
        this->last_tap.clear();
        this->last_up.clear();
        this->last_down.clear();
        this->last_move.clear();
        this->last_zoom.clear();
     };
    std::vector<touch_gesture> last_gesture;

    std::vector<touch_gesture> gestures ;
    std::vector<>
    bool rec_gest;
    void clearGest()final {this->gestures.clear();};
    void _clear()final {this->last_move.clear();this->last_tap.clear();this->last_zoom.clear();};
    void clear()final {this->_clear();if(!(this->rec_gest)){this->clearGest();};};
    glm::uvec2 get_pos();
    vect<glm::uvec2> get_multi_pos();
    virtual void get_touch();
    vect<touch_move> s;
        bool move_cb(vect<glm::vec4> d,int index){this->last_move+=touch_move(d,index);}       //bool push_touch_move(vect<glm::vec4> d,int index){this->evmain.push(move_cb(d,index));}
        bool tap_cb(vect<glm::vec2> d,int index){this->last_tap+=touc_tap(d,index);}       //bool push_touch_tap(vect<glm::vec2> d,int index){this->evmain.push(tap_cb(d,index));}
        bool zoom_cb(mat<glm::vec2> d,int index){this->last_zoom+=touch_zoom(d,index);}       //bool push_touch_zoom(mat<glm::vec2> d,int index){this->evmain.push(zoom_cb(d,index));}
        bool gesture_cb(vect<glm::vec4> d,int index){this->last_gesture+=touch_gesture(d,index);}       //bool push_touch_gesture(vect<glm::vec4> d,int index){this->evmain.push(gesture_cb(d,index));}
    void move_cb(touch_move ev){this->last_move_cb+=ev;};         //  void push_move(touch_move ev){this->evmain.push(ev);};
    void tap_cb(touch_tap ev){this->last_tap_cb+=ev;};            //  void push_tap(touch_tap ev){this->evmain.push(ev);};
    void zoom_cb(touch_zoom ev){this->last_zoom_cb+=ev;};         //  void push_zoom(touch_zoom ev){this->evmain.push(ev);};
    void gesture_cb(touch_gesture ev){this->last_gesture_cb+=ev;};//  void push_gesture(touch_gesture ev){this->evmain.push(ev);};
     void down_cb(mousedown ev) final {this->last_down+=ev;};
     void up_cb(mouseup ev) final { up_check(ev.data());this->last_up+=ev;};

    void init(){event_sys::init();};
    void record_gesture(){this->rec_gest=true;};
    vect<touch_move> finish_gesture(){this->reg_get=false;return this->s};
    //  bool handle();
    bool filter(short int type_flag){
        switch(type_flag){
            case _touch_move: {return true;};
            case _touch_tap: {return true;};
            case _touch_gesture: {return true;};
            case _touch_zoom: {return true;};
        };
        return false;
    };

};
#endif
#ifdef STRATA_CAP_AUDIO
#define MONO
#define WAVE_1M08  0b000001       //	11.025 kHz, mono, 8-bit
#define WAVE_1M16  0b000010      //	11.025 kHz, mono, 16-bit
#define WAVE_2M08  0b000101      //	22.05 kHz, mono, 8-bit
#define WAVE_2M16  0b000110      //	22.05 kHz, mono, 16-bit
#define WAVE_4M08  0b001001      //	44.1 kHz, mono, 8-bit
#define WAVE_4M16  0b001010      //	44.1 kHz, mono, 16-bit
#define WAVE_96M08 0b010001      // 96 kHz, mono, 8-bit
#define WAVE_96M16 0b010010      // 96 kHz, mono, 16-bit

#define WAVE_1S08  0b100001        //	11.025 kHz, stereo, 8-bit
#define WAVE_1S16  0b100010       //	11.025 kHz, stereo, 16-bit
#define WAVE_2S08  0b100101       //	22.05 kHz, stereo, 8-bit
#define WAVE_2S16  0b100110       //	22.05 kHz, stereo, 16-bit
#define WAVE_4S08  0b101001       //	44.1 kHz, stereo, 8-bit
#define WAVE_4S16  0b101010       //	44.1 kHz, stereo, 16-bit
#define WAVE_96S08 0b110001        //	96 kHz, stereo, 8-bit
#define WAVE_96S16 0b110010        //	96 kHz, stereo, 16-bit
typedef struct devcap{
    std::string name;
    uint channels;
    uint flags;
    devcap(std::string _name, uint _channels,uint _flags) {this->name=_name;this->channels=_channels,this->flags=_flags;}; 
}devcap;
using dcaps = devcap;
#include <strata/acqres/wav.hpp>
struct AUDIO  {
public:
    uint num = 0;
    const bool direction;
    std::vector<dcaps> audioCaps; 
    uint set =0 ; // device
    virtual uint GetNum();
    void clear()final {this->audioCaps.clear();};
    void init(){this->GetNum();};
    virtual void getCaps();
    void open(uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz,uint index);    
    void open(uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz )final{this->open(byterate , bitspersampple,bitrate, channels, hz,0);};

    void open(uint hz, uint channels);
    virtual void open();
    
    virtual void _play_wav(wavh header,std::vector<uint8_t> data);
 void playWav(std::string path,double start,double end) final{
    wavh header;
    std::vector<uint8_t> pcmdata;
    readwavfile(path.cstr(),&header,pcmdata,start,end);
    this->_play_wav(header,data);
 };

    virtual void close(uint index);
    void close()final{this->close(this->set);};
    void play(uint sizedata, char* data, uint byterate,uint bitspersapmple,uint channels, uint hz ,uint index   )final{
        this->open(byterate,bitspersample,channels,hz,index);
        this->play(sizedata,data,index);
        this->close(index);
    };
    void play(uint sizedata, char* data, uint byterate,uint bitspersapmple,uint channels, uint hz ,)final{this->play(sizedata, char* data,  byterate, bitspersapmple, channels, hz ,0);};
    //  void play(std::string wavfile , );
    //  play(uint sizedata, char* data);
    void play(uint sizedata, char* data)final{this->play(uint sizedata, char* data,0);};
    virtual void setVol(uint index, uint vol); 
    void setVol(uint vol)final{this->setVol(this->set,vol);};
    virtual void stopPlay(uint index);
    void stopPlay()final{this->stopPlay(this->set);};
    #ifdef STRATA_CAPABILITY_MIC
    uint nummic=0;
    std::vector<scas> mcaps ;

    void clearmic();
    virtual void getMicVaps();
    virtual uint GetNumMic();
    virtual void openMic(uint index);
    void openMic()final{this->openMic(0);};
    void clearMic(){this->micd.clear()}
    virtual void openmic(uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz,uint index);    
    void openmic(uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz )final{this->open(byterate , bitspersampple,bitrate, channels, hz,0);};
 virtual void closemic(uint index);
    void closemic()final{this->close(0);};
 void rec(uint sizedata, char* data, uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz,uint index)final{
        this->openMic(byterate ,  bitspersampple, bitrate, channels,  hz,index);
        this->rec(sizedata, data,index);
        this->closeMic(index);
    };
 void rec(uint sizedata, char* data, uint byterate , uint bitspersampple,uint bitrate,uint channels, uint hz)final{this->rec(sizedata, char* data,  byterate, bitspersapmple, channels, hz ,0);};
 virtual void stoprec(uint index);
  uint stoprec()final{this->stoprec(0);};
#endif
};
#endif

// This sections does not have include flag guard since it is meant to possibly be redefined
#if defined(STRATA_CAP_SENSOR) || defined(STRATA_CAP_CAMERA) || defined(STRATA_CAP_LOCATION) 
using gyro  =  glm::vec3//_gyro>;   
using loc = glm::dvec4;// long,lat,sealev,
using light = float;
using gravity = glm::vec3; 
using proximity = double;
using temp = double;
using accel  = glm::vec3;//_accel>;      
using magnet  =  glm::vec3; //,_mag>;    
using baro  =  float; //,_baro>;     
using humid  = float; //,_humid>;      
using pos  =   float; //,_pos>;   
using motion = bool;
using rotation = glm::vec3;
using heading = glm::vec2;
struct SENSOR   {
public:
gyro        last_gyro;
loc         last_loc;
light       last_light;
gravity     last_gravity;
proximity last_proximity;
temperature last_temperature; 
accel last_accel;
magnet last_magnet;

baro last_baro;
humid last_humid;
pos last_pos;
lidar last_lidar;
// motion last_motion;
// motion last_stationary;
rotation last_rotation;
rotation last_game_rotation;

virtual temp        gettemp();
virtual gyro        getgyro();
virtual loc         getloc();         
virtual light       getlight();       
virtual gravity     getgravity();     
virtual proximity   getproximity(); 
virtual accel       getaccel(); 
virtual mag         getmag(); 
virtual baro        getbaro(); 
virtual humid       gethumid(); 
virtual pos         getpos(); 
virtual lidar       getlidar(); 
// virtual motion      getmotion(); 
// virtual motion      getstationary(); 
virtual rotation    getrotation(); 
virtual rotation    getgamerotation(); 



virtual void init();
virtual bool inittemp(uint pollrateus=1000000);virtual void closetemp();
virtual bool initgyro(uint pollrateus=1000000);virtual void closegyro();
virtual bool initlight(uint pollrateus=1000000);virtual void closelight();
virtual bool initgravity(uint pollrateus=1000000);virtual void closegravity();
virtual bool initproximity(uint pollrateus=1000000);virtual void closeproximity();
virtual bool initaccel(uint pollrateus=1000000);virtual void closeaccel();
virtual bool initmag(uint pollrateus=1000000);virtual void closemag();
virtual bool initbaro(uint pollrateus=1000000);virtual void closebaro();
virtual bool inithumid(uint pollrateus=1000000);virtual void closehumid();
virtual bool initmotion(uint pollrateus=1000000);virtual void closemotion();
virtual bool initstationary(uint pollrateus=1000000);virtual void closestationary();
virtual bool initrotation(uint pollrateus=1000000);virtual void closerotation();
virtual bool initgamerotation(uint pollrateus=1000000);virtual void closegamerotation();
void initAll(){init();initgyro();initloc();initlight();initgravity();initproximity();initaccel();initmag();initbaro();inithumid();initpos();initlidar();initmotion();initmotion();initrotation();initgamerotation();
void closeAll(){closegyro();closelight();closegravity();closeproximity();closeaccel();closemag();closebaro();closehumid();closemotion();closestationary();closerotation();closegamerotation();};
#endif



};


// uint numGyro =1;
// uint numloc =1;
// uint numaccel =1;
// uint nummag =1;
// uint numbaro =1;
// uint numhumid =1;
// uint numpos =1;
// uint numlidar =1;
// uint numcam =1;
    virtual void getSensorPermisisons();

    virtual uint getNumgyro();
    virtual uint getNumaccel();
    virtual uint getNummag();
    virtual uint getNumbaro();
    virtual uint getNumhumid();
    virtual uint getNumpos();
    virtual uint getNumlidar();
    virtual uint getNumcam();
    virtual uint getNumloc();
    void getnums()final {this->getNumgyro();this->getNumaccel();this->getNummag();this->getNumbaro();this->getNumhumid();this->getNumpos();this->getNumlidar();this->getNumcam();this->getNumloc();};

    virtual gyro getgyro();
    virtual accel getaccel();
    virtual mag getmag();
    virtual baro getbaro();
    virtual humid gethumid();
};

#ifdef STRATA_CAP_CAM
using lidar = double**; //,_lidar>;      
using cam  =  glm::dvec4**; //,_cam>;    
struct CAM {
    virtual pos getpos();
    evq<cam>    last_cam;
    evq<lidar>      last_lidar;

    uint indexFront;
    uint indexBack;

virtual cam         getcam(uint index=0);
virtual initCam();     
virtual numCams();
    virtual lidar getlidar();
    virtual cam getcam();
    virtual loc getloc();

};
#endif
#ifdef STRATA_CAP_NET

#define CREATE_FAIL VEC_MAX
#include <int/net.hpp>
struct NET {
    std::vector<char*> sockaddrs;
virtual auto inetaddr(const char dotstr[]);
void char* inettoa(long  ad){return intnet::inettoa(ad)};
void gethostname(char* name, uint size);
int getaddrinfo(char* dns);
enum res{
SUCCESS=0
NOINIT=1,
NETDOWN=2,
ADRINUSE=3,
ADRNAVAIL=4,
INVALARG=5,
FAILDEF=6
} ;

 uint result(int result);

enum sockcrtt {
    STREAM,
    DGRAM,
    // RAW,
    // MCAST,
    // SEQPACKET
};
enum proto {
    TCP=0,
    UDP=1,
    PGM=2
};
uint sockcreate(char* addr, sockt ty,sockcrt crtty);// Returns pos
bindres sockbind(uint pos,sockt ty,char* addr);
bindres sockbind(impl::NET::sockt ty, char addr[14]){return this->sockbind(0,ty,addr);};
uint sockclose(uint pos=0);// 

virtual int nsend(uint pos, uint bufsize, char* buf,char* to, int tolen);
int nsend(uint bufsize, char* buf){this->send(0,bufsize,buf)};
int nrecvfrom(uint pos,uint bufsize, char* buf,char* from, int fromlen);
int nrecvfrom(uint pos,uint bufsize, char* buf,uint pos){this->nrecvfrom(pos,bufsize,buf,this->sockaddrs[posa],sizeof(this->sockaddrs[posa]));};
int nrecvfrom(uint bufsize, char* buf,uint pos){this->recvfrom(0,bufsize,buf,pos);};
int nrecv(uint pos,uint sizelim);
int naccept(uint pos, char* addr,int *adrlen);




void naccept()
void nrecv()final{this->recv(this->sockaddrs[pos]);};

virtual bool close();
virtual int init();
};
#endif
#define STRATA_CAP_DISPLAY
#ifdef STRATA_CAP_DISPLAY
using wake        =  bool      ; //         ,_wake>;
using sleep       =  bool      ; //         ,_sleep>;        
using min         =  bool      ; //         ,_min>;      
using max         =  bool      ; //         ,_max>;      
using hide        =  bool      ; //         ,_max>;
using resize      =  glm::ivec2; //               ,_resize>;
using move        =  glm::ivec2; //               ,_move>;         
using fullscreen  =  bool      ; //         ,_fullscreen>;             
using close       =  bool      ; //         ,_close>;                  
using display_conn = bool      ; //         ,_display_conn>;  
using display_orient = int     ; //          ,_display_orient>;
using display_power  = int       ; //         ,_display_power>;

struct DISPLAY  {
 public:
    vect<glm::ivec3> disp; // xy=wh ; z=hz;
    vect<glm::ivec3> mon;
    uint num;
    void _init(); // Initialize the subsystem
    void init() {this->_init()}; 
   

    vec2 get_data(uint pos=0){return this->disp[pos];}; // hw(pixels) ,hw(cm)
    int get_width(uint pos=0){return this->disp[pos][0];};
    int get_height(uint pos=0){return this->disp[pos][1];};
    int get_index(uint pos=0){return this->disp[pos][2];};
    glm::ivec3 get_monitor_data(uint pos=0); // w,h,hz
    glm::ivec3 get_display_data(uint pos=0); // w,h,hz
    bool is_portrait(uint pos){return (this->disp[pos][0]<this->disp[pos][1]);};
    int Num();
    int get_monitor_display(uint pos=0);
    virtual vec2 get_data(uint pos=0){this->_get_data() ; this->disp[pos];}; // hw(pixels) ,hw(cm)
    virtual int get_width(uint pos=0){this->_get_width() ; this->disp[pos][0];};
    virtual int get_height(uint pos=0){this->_get_height() ; this->disp[pos][1];};
    virtual int get_index(uint pos=0){;};
 
    void change_cb()
    void conn_cb(uint index,bool val = true){this->evmain->push(display_conn::display_conn(index,val);)};
    void discon_cb()
    void power_cb(uint index,bool val = true){this->evmain->push(display_power::display_power(index,val);)};
    void orient_cb(uint index,bool val = true){this->evmain->push(display_power::display_orient(index,val);)};
    virtual void handle();
    virtual void init();
    virtual void close(){delete this;};
};
#endif
#ifdef STRATA_WININFOSTRCT
struct winstrct {
glm::ivec2 size;
glm::ivec2 pos;
uint8_t parent=-1;
bool tool=false;
bool custom_tabbar=true;
 bool resizable=true;
bool transparent=false;
bool always_on_top=true;
char CLASS_NAME[]=NULL ;
char text[]=NULL;
};
#endif
template <typename win>
struct SYS   { 
private:
    // event_main evmain;
    
#ifdef STRATA_CAPABILITY_MOUSE 
MOUSE      mouse;
    void initMouse();
#endif    
#ifdef STRATA_CAPABILITY_KEY
KEY        key;
    void initKey();
#endif
#ifdef STRATA_CAPABILITY_JOY 
JOY        joy;
    void initJoy();
#endif
#ifdef STRATA_CAPABILITY_CONT 
CONT       cont;
    void initCont();
#endif
#ifdef STRATA_CAPABILITY_TOUCH 
TOUCH      touch;
    void initTouch();
#endif
#ifdef STRATA_CAPABILITY_DISPLAY 
DISPLAY    display;
    void initDisplay();
#endif
#ifdef STRATA_CAPABILITY_AUDIO 
AUDIO      audio;
    void initAudio();
#endif
#ifdef STRATA_CAPABILITY_SENSOR 
SENSOR     sensor;
    void initSensor();
#endif
#ifdef STRATA_CAP_CAM
CAM cam;
#endif
#ifdef STRATA_CAP_NET
NET net;
#endif
public:

enum dev {
    Mouse=1,
    Key=2,
    Joy=3,
    Cont=4,
    Touch=5
    Mkb=7,
};

// virtual void handlemkb();
// virtual void handleCont();
// virtual void handleJoy();
// virtual void
uint8_t main ; 
   uint last_dev ;
    using keyrecord = glm::ivec2 ; // X is index impl::
    static const keyrecord idlekrec = keyrecord(-1,-1); 
    keyrecord keyrec = idlekrec; 
    keyrecord axisrec = idlekrec;
    void resetrec(){this->keyrec=idlekrec;this->axisrec=idlekrec;};
    bool rec = false ;
    private :
    virtual void recordKey(); 
    virtual void recordAxis();
    virtual void stoprecordKey();
    virtual void stoprecordAxis();
    public:

    void stop_record_key()final{this->rec=false ; this->stoprecordKey();};
    void stop_record_axis()final{this->rec=false ; this->stoprecordAxis();};
    void record_key()final{this->rec = true;recordKey();};
    void record_axis()final{this->rec = true;recordAxis();};


     
    using winty = win;
    // vect<win> wins;
    std::vector<glm::ivec4> wind;
    int curr_win_index=0;
    void listen(){
        for(int i=0;i<this->evsys.size();i++){this->evsys[i].listen();};
     };// Checks if there was an event;
    event filter(event* ev){ev};
    virtual void handle();
   
    void init() {        
        this->_init()}; 
 

    virtual void changePrMouse(uint pos=0);
    virtual void changePrKey(uint pos=0);
    virtual void changePrCont(uint pos=0);
    virtual void changePrJoy(uint pos=0);
    virtual void changePrTouch(uint pos=0);
    using MIN = 0b0001;
    using MAX = 0b0010;
    using HIDE = 0b0100;
    using NORMAL = 0b1000;
    void selfclose()final{delete this;};
    void sleep_callback()final{return;};
    void wake_callback()final{return;};
    void min_callback()final{return;};
    void max_callback()final{return;};
    void restore_callback()final{return;};
    void hide_callback()final{return;};
    void resize_callback()final{return;};
    void move_callback()final{return;};
    void fullscreen_callback(bool val=true)final{return};
    void close_callback()final{this->evmain->push(close::close(true));this->close_app_win_func();}
    #define _custom_tabbar 0b00001
    #define _resizable     0b00010
    #define _transparent   0b00100
    #define _always_on_top 0b01000
    #define _tool          0b10000
    #define _permeable    0b100000
    #define _default       0b00011
    void createWin(glm::ivec2 size,glm::ivec2 pos,uint8_t parent=-1,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,char CLASS_NAME[]=NULL ,char text[]=NULL) ;
    void createWin(){
        #ifdef STRATA_WININFOSTRCT
        this->createWin(winstrct.size,winstrct.pos,winstrct.parent,winstrct.tool,winstrct.custom_tab,winstrct.resizable,winstrct.transparent,winstrc.always_on_top,winstrc.CLASS_NAME,winstrct.text);
        #endif
    };
    void create_child_cur (glm::ivec2 size,glm::ivec2 pos,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) final{
            return this->create_win (glm::ivec2 size,glm::ivec2 pos,this->wins[this->curr_win_index].w,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    } ;
    virtual glm::ivec2 winpos(win w=this->wins[0]);
    virtual glm::ivec2 winsize(win w=this->wins[0]);
    virtual glm::ivec4 wininfo(win w=this->wins[0]);
    virtual void resize(win w=this->wins[0],glm::ivec2 addsize);
    virtual void move(win w=this->wins[0],glm::ivec2 addpos);
    virtual void minimize(uint pos);
    virtual void maximize{uint pos};
    virtual void restore{uint pos};
    virtual void hide(uint pos);
    
    virtual bool ismin(uint index=0)
    virtual bool ishidden(uint index=0)
    virtual bool isnormal(uint index=0)
    virtual bool ismax(uint index=0)
    virtual void setopacity(uint index,float opacity);
    virtual void setfullscreen(uint index);
    virtual void closeWin();
    virtual void recreateWin(uint index,glm::ivec2 size,glm::ivec2 pos,int8_t flag=_custom_tabbar,uint8_t parent=NULL,char CLASS_NAME[]="DefaultName" ,char text[]=NULL) {

    virtual void sleep(int mstime=2000);
    virtual int handle(); // Called during the event loop
    void clear(){
#ifdef STRATA_CAP_MOUSE
this->mouse.clear();
#endif
#ifdef STRATA_CAP_KEY
this->key.clear();
#endif
#ifdef STRATA_CAP_JOY
this->key.clear();
#endif
#ifdef STRATA_CAP_CONT
this->cont.clear();
#endif
    };
    virtual void handle();
    void run(){this->handle(); this->handle();this->clear();};
    void mkb(){this->handle(); this->mouse.handle();this->clear();};
    void cont(){this->handle(); this-> ;};
    void set_mkb();
    void set_cont();
    virtual void _init();// Set callbacks
    SYS(uint flags)=default{this->flag=flags;this->init_evsys(flags);}
};


}
}


#endif
