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
#include <stratum/petri/queue>
#include <stratum/petri/list>
#include <vector>
#include <memory>
#include <string>
#include <atomic>
#include <future>
#include <cpuid.h>

using namespace std;
#define VEC_MAX 1000



#ifdef STRATA_CAP_MOUSE 
constexpr bool CAPMOUSE = true ;
#else 
constexpr bool CAPMOUSE = false ;
#endif    
#ifdef STRATA_CAP_KEY
constexpr bool CAPMOUSE = true ;
#else 
constexpr bool CAPMOUSE = false ;
#endif
#ifdef STRATA_CAP_JOY
constexpr bool CAPJOY =true;
#else
constexpr bool CAPJOY = false ;
#endif
#ifdef STRATA_CAP_CONT
constexpr bool CAPCONT =true;
#else
constexpr bool CAPCONT = false ;
#endif
#ifdef STRATA_CAP_TOUCH
constexpr bool CAPTOUCH =true;
#else
constexpr bool CAPTOUCH = false ;
#endif
#ifdef STRATA_CAP_DISPLAY
constexpr bool CAPDISPLAY =true;
#else
constexpr bool CAPDISPLAY = false ;
#endif
#ifdef STRATA_CAP_AUDIO
constexpr bool CAPAUDIO =true;
#else
constexpr bool CAPAUDIO = false ;
#endif
#ifdef STRATA_CAP_SENSOR
constexpr bool CAPSENSOR =true;
#else
constexpr bool CAPSENSOR = false ;
#endif



#include "implgl.hpp"
#ifdef STRATA_IMPL_WIN
#include "impl_win.hpp"
#endif
#ifdef STRATA_IMPL_ANDROID
#include "impl_android.hpp"
#ifdef STRATA_IMPL_LINUX
#include "impl_linux.hpp"
#define STRATA_IMPL_WASM
#include "impl_wasm.hpp"
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
    int i[size];
    size_t pos=0;
    size_t ps;

    void (*cb_root)(T);
    void (*cb_rooti)(T,int);

    T& operator[](int s){return this->d[s>=0?(size_t)s:sizes+s];}
    T& operator[](size_t s){return this->d[s];}
    void clear(){pos = 0;}
    void erase(){for(int i=0;i<size;i++){d[i]=T();};pos=0;};
    int lastn(){return d[pos]};)
    std::pair<T,i> lastEv(){return {d[pos],i[pos]};}
    void push(T&& s){if(pos==size-1){clear();} d[pos] = s;++pos  ;}
    void push(T&& s,int ind){if(sizes==size-1){clear();return;} d[pos] = s;i[sizes]=ind;++pos  ;}


    void operator+=(T&& s){push(s);};
    bool operator==(T s){for(const T& it  : d){if(it == s){return true;};} return false;};

    void cb(T v,int index){push(v,index); };
    void cb(T v){push(v);};

    T* begin(){return d[0];};
    T* end(){return d[pos];};


    eventq() {d.push_back(T()); sizes= 1; pos = d.begin();}
};
struct SYS ;
template <typename T>
bool getEvent(T* res,SYS& s );




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
    evq<click >       _click; 
    evq<dbclick >     _dbclick;     
    evq<mousedown >   _mousedown;          
    evq<mouseup >     _mouseup;        
    evq<mouse_move>  _mouse_move;           
    evq<mouse_wheel> _mouse_wheel;     
    evq<mouse_wheelh> _mouse_wheelh;     
    uint getlastKey(){return this->_down.lastn();};
    uint getlastaxis(){mouse_move l = this->_move.lastn(); return (( (l.x <0) ? (-l.x) : l.x )>((l.y < 0) ? (-l.y) : l.y)) ? 0 : 1; };

    virtual void cursorHide();
    virtual void cursorShow();
    void clicked(click t){return this->_click == t;};
    void dbclicked(dbclick t){return this->_dbclick == t;};
    void down(mousedown t){return this->_down == t;};
    void up(mouseup t){return this->_up == t;};
    // void moved_gt(glm::ivec2 s);
    // void move_lt(glm::ivec2 s);
    // void 
    void clear()final{this->_click.clear();this->_down.clear();this->_up.clear();this->_press.clear();this->_move.clear();this->_wheel.clear();}
    bool detect_combo(int* s[2]){
        bool x=false;bool y=false;
            for(int i = 0 ; i < this->_down.pos();i++){
                if(this->_down[i]== s[j][0] ){
                    bool cond=false;
                    for(int k = 0 ; k < this->_up.pos();k++){if(this->_up[k]==this->_down[i]){cond=true};break;};
                    if(cond){continue;}
                    else {
                        if(x){y=true}
                        else x = true;
                    };
                }; 
                if(this->_down[i]== s[j][1] ){
                    bool cond=false;
                    for(int k = 0 ; k < this->_up.pos();k++){if(this->_up[k]==this->_down[i]){cond=true};break;};
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
        for(int i = 0 ; i<this->_down.pos() ;i++ ){
            if(i==this->_down.data();){this->_down[i].data=-1; break;}
        };
    };
    
     virtual glm::vec2 Pos(int index=0);
     virtual glm::vec2 WinPos();
    virtual void handle();
    virtual void _handle(){
        this->handle();

    };
    void init()override{
        this->_init();};
};
   
template <> bool getEvent<click>(click* e,SYS& s){ if (s.mouse) };
template <> bool getEvent<dbclick>(dbclick* e,SYS& s){ if (s.mouse) };
template <> bool getEvent<mousedown>(mousedown* e,SYS& s){ if (s.mouse) };
template <> bool getEvent<mouseup>(mouseup* e,SYS& s){ if (s.mouse) };
template <> bool getEvent<mouse_move>(mouse_move* e,SYS& s){ if (s.mouse) };
template <> bool getEvent<mouse_wheel>(mouse_wheel* e,SYS& s){ if (s.mouse) };
template <> bool getEvent<mouse_wheelh>(mouse_wheelh* e,SYS& s){ if (s.mouse) };


#endif
#ifdef STRATA_CAP_KEY
using keyup = int,        ;// _keyup>; // x button, y index    
using keydown = int,        ;// _keydown>; // x button, y index      
using keypress = int         ;//,_keypress>; // x button, y index       
using keycombo = glm::ivec4   ;//,_keycombo> ; //-1 is
#ifndef MAX_KEYS
#define MAX_KEYS 0xFF
#endif  
struct KEY   {
    enum key_state {up=0,down=1,press=1};
    evq<keyup>    _keyup;
    evq<keydown>  _keydown;
    evq<keypress> _keypress;
    

    int keyState[MAX_KEYS];
    uint getlastKey(){return this->_keydown.lastn();};

    bool up_cb(char key,int index) final {this->_keyup.push(keyup(key),index);this->keyState[(int)key]=key_state::up;};
    bool down_cb(char key,int index) final {this->_keydown.push(keydown(key),index);this->keyState[(int)key]=key_state::down;};    
    bool press_cb(char key,int index) final {this->_keypress.push(keypress(key),index);this->keyState[(int)key]=key_state::press;};    
    bool up_cb(up ev) final {this->_keyup.push(ev);};
    bool down_cb(down ev) final {this->_keydown.push(ev);};    
    bool press_cb(press ev) final {this->_keypress.push(ev);};    
    
    virtual void handlemeta();
    bool check_combo( uint32_t kc){

    };
    
    virtual bool get_state(int key);
    bool resolve(void ev,evs flag){
        switch(flag){
            case _keyup :{this->_keyup=(keyup)ev;return true;};
            case _keydown :{this->_keydown=(keydown)ev;return true;};
            case _keypress :{this->_keypress=(keypress)ev;return true;};
        };
        return false;
    };
    void clear()final{
        this->_keyup.clear();
        this->_keydown.clear();
        this->_keypress.clear();        
    };
}; // index 
#endif
#ifdef STRATA_CAP_JOY
using joy_hat = int ;        //,_joy_hat>;  
struct  joy_axis {long val,index;}  ;        // x,y axis 
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
        evq<joy_hat>   _hat;
        evq<joy_axis>  _axis;

        evq<joy_up>    _up;  
        evq<joy_down>  _down;    
        evq<joy_press> _press;   
        evq<joy_throt> _throt;   
        evq<joy_rot> _rot;   
    uint getlastKey(){ this->_down.lastn();};
    uint getlastaxis(){joy_axis l = this->_axis.lastn(); return (( (l.x <0) ? (-l.x) : l.x )>((l.y < 0) ? (-l.y) : l.y)) ? 0 : 1;};

        
        uint num =1;
        uint period = 100;
        // int maxbtn;
        #ifndef no_maxbtn
        #define maxbtn 16
        #endif
        virtual int _numJoys();
        void clear(){this->_hat.clear();this->_axis.clear();this->_up.clear();this->_down.clear();this->_press.clear();};
        joycap getCap(int index);
        void setperiod(uint ms) {this->period=ms;};
        int numJoys(){ this->numJoys(); return this->num;}

      //void push_up(joy_hat ev) final {this->evmain.push(ev);};
         //void push_up(joy_up ev) final {this->evmain.push(ev);};
   //void push_down(joy_down ev) final {this->evmain.push(ev);};
//void push_press(joy_press ev) final {this->evmain.push(ev);};
   //void push_axis(joy_axis ev) final {this->evmain.push(ev);};
           //void push_up(int btn,int index) final {this->evmain.push(joy_hat(btn,index));};
              //void push_up(int btn,int index) final {this->evmain.push(joy_up(btn,index));};
        //void push_docb(int btn,int index) final {this->evmain.push(joy_down(btn,index));};    
     //    
    //void push_axcb(int16 axis,int index) final {this->evmain.push(joy_axis(axis,index));};    


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
using CONT_press= long;//        _CONT_press>;                    
using CONT_down = long;//        _CONT_down>; 
using CONT_up =   long;//        _CONT_up>; 
using CONT_dpad = long;//        _CONT_dpad>;
struct CONT_axis {long val,short index;};//        _CONT_axis>;  // Axis index;
struct CONT_trig {long val,short index; };
struct CONT  {
public:
    evq<CONT_press> _press;      
    evq<CONT_down>  _down;     
    evq<CONT_up>    _up;   
    evq<CONT_dpad>  _dpad;     
    evq<CONT_axis>  _laxis;     
    evq<CONT_axis>  _raxis;
    evq<CONT_trigger> _trig;
      uint getlastKey(){ this->_down.lastn();};
    uint getlastaxis(){CONT_axis l ; this->_laxis.lastn();CONT_axis r; this->_raxis.lastn(); return (glm::abs(l)>glm::abs(r)) ? 0 : 1; };

    void clear(){
        this->_press.clear();
        this->_down.clear();
        this->_up.clear();
        this->_dpad.clear();
        this->_laxis.clear();
        this->_raxis.clear();
        this->_tr.clear();
    };
    int num =0 ; 
    virtual void num();
    void clear()final{this->_press.clear();this->_down.clear();this->_up.clear();this->_dpad.clear();this->_laxis.clear();this->_raxis.clear();this->_tr.clear();};
 
 
    bool trig_cb(CONT_trig ev,int index=0) final {_trig.push(ev,index);}
    bool up_cb(CONT_up btn,int index=0) final {_up.push(btn,index);};                   //bool push_up(int btn,int index) final {this->evmain.push(CONT_up(btn,index));};
    bool down_cb(CONT_down btn,int index=0) final {_down.push(btn,index);};             //bool push_down(int btn,int index) final {this->evmain.push(CONT_down(btn,index));};    
    bool press_cb(CONT_press btn,int index=0) final {_press.push(btn,index);};          //bool push_press(int btn,int index) final {this->evmain.push(CONT_press(btn,index));};    
    bool laxis_cb(glm::ivec2 axis,int index=0) final {_laxis.push(axis,index);};    //bool push_laxis(glm::ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool raxis_cb(glm::ivec2 axis,int index=0) final {_raxis.push(axis,index);};    //bool push_raxis(glm::ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool dpad_cb(CONT_dpad,int index=0) final {_dpa.push(axis,index);};              //bool push_dpad(int axis,int index) final {this->evmain.push(CONT_dpad(axis,index));};    
    
    
    bool trig_cb(CONT_trig ev,int index=0) final {_trig.push(ev);}
    bool up_cb(CONT_up btn,int index=0) final {_up.push(btn);};                   //bool push_up(int btn,int index) final {this->evmain.push(CONT_up(btn,index));};
    bool down_cb(CONT_down btn,int index=0) final {_down.push(btn);};             //bool push_down(int btn,int index) final {this->evmain.push(CONT_down(btn,index));};    
    bool press_cb(CONT_press btn,int index=0) final {_press.push(btn);};          //bool push_press(int btn,int index) final {this->evmain.push(CONT_press(btn,index));};    
    bool laxis_cb(glm::ivec2 axis,int index=0) final {_laxis.push(axis);};    //bool push_laxis(glm::ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool raxis_cb(glm::ivec2 axis,int index=0) final {_raxis.push(axis);};    //bool push_raxis(glm::ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool dpad_cb(CONT_dpad,int index=0) final {_dpa.push(axis);};              //bool push_dpad(int axis,int index) final {this->evmain.push(CONT_dpad(axis,index));};    
    
 
    
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
     evq<touch_tap> _tap;
     evq<touch_tap> _up;
     evq<touch_tap> _down;
     evq<touch_move> _move;
     evq<touch_zoom> _zoom;
       uint getlastaxis(){touch_move l =this->_move.lastn(); return (( (l.x <0) ? (-l.x) : l.x )>((l.y < 0) ? (-l.y) : l.y)) ? 0 : 1; };

     void clear(){
        this->_tap.clear();
        this->_up.clear();
        this->_down.clear();
        this->_move.clear();
        this->_zoom.clear();
     };
    std::vector<touch_gesture> _gesture;

    std::vector<touch_gesture> gestures ;
    bool rec_gest;
    void clearGest()final {this->gestures.clear();};
    void _clear()final {this->_move.clear();this->_tap.clear();this->_zoom.clear();};
    void clear()final {this->_clear();if(!(this->rec_gest)){this->clearGest();};};
    glm::uvec2 get_pos();
    vect<glm::uvec2> get_multi_pos();
    virtual void get_touch();
    vect<touch_move> s;

    
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
using volume_change = long;
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
gyro        _gyro;
loc         _loc;
light       _light;
gravity     _gravity;
proximity _proximity;
temperature _temperature; 
accel _accel;
magnet _magnet;

baro _baro;
humid _humid;
pos _pos;
lidar _lidar;
// motion _motion;
// motion _stationary;
rotation _rotation;
rotation _game_rotation;

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
    evq<cam>    _cam;
    evq<lidar>      _lidar;

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


template <typename T>
struct getEventT {using type = void;  };

template <typename T,typename InhT>
struct getEventInh {using type = typename getEventT<T>::type; static constexpr evq<T> getEventT<T>::type::* ptrm=getEventT<T>::ptrm; static constexpr SYS::type::* ps = getEventT<T>::ps; }

tempate <typename T, typename inhSys>
evq<T>* getEvq(inhSys& s ){s.*getEventInh<T,inhSys>::ps.*(getEventT::ptrm);};


#ifdef STRATA_CAP_CLI 

struct clisys {
    using tyMouseCoord = struct {short X,Y};
    virtual bool mouseMove();
    virtual bool click();
    virtual bool dclick();
    virtual bool mouseEvent();
    virtual bool keyEvent();
    virtual bool isPressedLCTRL();
    virtual bool isPressedRCTRL();
    virtual bool isPressedLALT();
    virtual bool isPressedRALT();
    virtual bool isPressedLSHIFT();
    virtual bool isPressedRSHIFT();
    void event(){}

    clisys() = default {GetConsoleMode(hInput, &prev_mode);SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);}
};  
#endif
struct SYS   { 
private:
    // event_main evmain;
    
#ifdef STRATA_CAPABILITY_MOUSE 
MOUSEt     mouse;
    void initMouse();
#endif    
#ifdef STRATA_CAPABILITY_KEY
KEYt        key;
    void initKey();
#endif
#ifdef STRATA_CAPABILITY_JOY 
JOYt        joy;
    void initJoy();
#endif
#ifdef STRATA_CAPABILITY_CONT 
CONTt       cont;
    void initCont();
#endif
#ifdef STRATA_CAPABILITY_TOUCH 
TOUCHt      touch;
    void initTouch();
#endif
#ifdef STRATA_CAPABILITY_DISPLAY 
DISPLAYt    display;
    void initDisplay();
#endif
#ifdef STRATA_CAPABILITY_AUDIO 
AUDIOt      audio;
    void initAudio();
#endif
#ifdef STRATA_CAPABILITY_SENSOR 
SENSORt     sensor;
    void initSensor();
#endif
#ifdef STRATA_CAP_CAM
CAMt cam;
#endif
#ifdef STRATA_CAP_NET
NETt net;
#endif
public:

template <typename T>
T getEvnt(){return getEvq<T>(*this)->lastn();};


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
   uint _dev ;
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
template <>getEventT<dbclick         > {using type = MOUSE  ;static constexpr evq<dbclick       > type::* ptrm=&type::_dbclick       ;static constexpr type SYS::* ps =&SYS::mouse;  };
template <>getEventT<mousedown       > {using type = MOUSE  ;static constexpr evq<mousedown     > type::* ptrm=&type::_mousedown     ;static constexpr type SYS::* ps =&SYS::mouse;  };
template <>getEventT<mouseup         > {using type = MOUSE  ;static constexpr evq<mouseup       > type::* ptrm=&type::_mouseup       ;static constexpr type SYS::* ps =&SYS::mouse;  };
template <>getEventT<mouse_move      > {using type = MOUSE  ;static constexpr evq<mouse_move    > type::* ptrm=&type::_mouse_move    ;static constexpr type SYS::* ps =&SYS::mouse;  };
template <>getEventT<mouse_wheel     > {using type = MOUSE  ;static constexpr evq<mouse_wheel   > type::* ptrm=&type::_mouse_wheel   ;static constexpr type SYS::* ps =&SYS::mouse;  };
template <>getEventT<mouse_wheelh    > {using type = MOUSE  ;static constexpr evq<mouse_wheelh  > type::* ptrm=&type::_mouse_wheelh  ;static constexpr type SYS::* ps =&SYS::mouse;  };
template <>getEventT<keyup           > {using type = KEY    ;static constexpr evq<keyup         > type::* ptrm=&type::_keyup         ;static constexpr type SYS::* ps =&SYS::key;  };
template <>getEventT<keydown         > {using type = KEY    ;static constexpr evq<keydown       > type::* ptrm=&type::_keydown       ;static constexpr type SYS::* ps =&SYS::key;  };
template <>getEventT<keypress        > {using type = KEY    ;static constexpr evq<keypress      > type::* ptrm=&type::_keypress      ;static constexpr type SYS::* ps =&SYS::key;  };
template <>getEventT<keycombo        > {using type = KEY    ;static constexpr evq<keycombo      > type::* ptrm=&type::_keycombo      ;static constexpr type SYS::* ps =&SYS::key;  };
template <>getEventT<joy_hat         > {using type = JOY    ;static constexpr evq<joy_hat       > type::* ptrm=&type::_joy_hat       ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<joy_axis        > {using type = JOY    ;static constexpr evq<joy_axis      > type::* ptrm=&type::_joy_axis      ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<joy_up          > {using type = JOY    ;static constexpr evq<joy_up        > type::* ptrm=&type::_joy_up        ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<joy_down        > {using type = JOY    ;static constexpr evq<joy_down      > type::* ptrm=&type::_joy_down      ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<joy_press       > {using type = JOY    ;static constexpr evq<joy_press     > type::* ptrm=&type::_joy_press     ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<joy_rot         > {using type = JOY    ;static constexpr evq<joy_rot       > type::* ptrm=&type::_joy_rot       ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<joy_throt       > {using type = JOY    ;static constexpr evq<joy_throt     > type::* ptrm=&type::_joy_throt     ;static constexpr type SYS::* ps =&SYS::joy;  };
template <>getEventT<CONT_press      > {using type = CONT   ;static constexpr evq<CONT_press    > type::* ptrm=&type::_press         ;static constexpr type SYS::* ps =&SYS::cont;  };
template <>getEventT<CONT_down       > {using type = CONT   ;static constexpr evq<CONT_down     > type::* ptrm=&type::_down          ;static constexpr type SYS::* ps =&SYS::cont;  };
template <>getEventT<CONT_up         > {using type = CONT   ;static constexpr evq<CONT_up       > type::* ptrm=&type::_up            ;static constexpr type SYS::* ps =&SYS::cont;  };
template <>getEventT<CONT_dpad       > {using type = CONT   ;static constexpr evq<CONT_dpad     > type::* ptrm=&type::_dpad          ;static constexpr type SYS::* ps =&SYS::cont;  };
template <>getEventT<CONT_axis       > {using type = CONT   ;static constexpr evq<CONT_axis     > type::* ptrm=&type::_axis          ;static constexpr type SYS::* ps =&SYS::cont;  };
template <>getEventT<CONT_trig       > {using type = CONT   ;static constexpr evq<CONT_trig     > type::* ptrm=&type::_trig          ;static constexpr type SYS::* ps =&SYS::cont;  };
template <>getEventT<touch_move      > {using type = TOUCH  ;static constexpr evq<touch_move    > type::* ptrm=&type::_touch_move    ;static constexpr type SYS::* ps =&SYS::touch;  };
template <>getEventT<touch_tap       > {using type = TOUCH  ;static constexpr evq<touch_tap     > type::* ptrm=&type::_touch_tap     ;static constexpr type SYS::* ps =&SYS::touch;  };
template <>getEventT<touch_zoom      > {using type = TOUCH  ;static constexpr evq<touch_zoom    > type::* ptrm=&type::_touch_zoom    ;static constexpr type SYS::* ps =&SYS::touch;  };
template <>getEventT<touch_gesture   > {using type = TOUCH  ;static constexpr evq<touch_gesture > type::* ptrm=&type::_touch_gesture ;static constexpr type SYS::* ps =&SYS::touch;  };
template <>getEventT<gyro            > {using type = SENSOR ;static constexpr evq<gyro          > type::* ptrm=&type::_gyro          ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<loc             > {using type = SENSOR ;static constexpr evq<loc           > type::* ptrm=&type::_loc           ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<light           > {using type = SENSOR ;static constexpr evq<light         > type::* ptrm=&type::_light         ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<gravity         > {using type = SENSOR ;static constexpr evq<gravity       > type::* ptrm=&type::_gravity       ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<proximity       > {using type = SENSOR ;static constexpr evq<proximity     > type::* ptrm=&type::_proximity     ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<temp            > {using type = SENSOR ;static constexpr evq<temp          > type::* ptrm=&type::_temp          ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<accel           > {using type = SENSOR ;static constexpr evq<accel         > type::* ptrm=&type::_accel         ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<magnet          > {using type = SENSOR ;static constexpr evq<magnet        > type::* ptrm=&type::_magnet        ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<baro            > {using type = SENSOR ;static constexpr evq<baro          > type::* ptrm=&type::_baro          ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<humid           > {using type = SENSOR ;static constexpr evq<humid         > type::* ptrm=&type::_humid         ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<pos             > {using type = SENSOR ;static constexpr evq<pos           > type::* ptrm=&type::_pos           ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<motion          > {using type = SENSOR ;static constexpr evq<motion        > type::* ptrm=&type::_motion        ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<rotation        > {using type = SENSOR ;static constexpr evq<rotation      > type::* ptrm=&type::_rotation      ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<heading         > {using type = SENSOR ;static constexpr evq<heading       > type::* ptrm=&type::_heading       ;static constexpr type SYS::* ps =&SYS::sensor;  };
template <>getEventT<wake            > {using type = DISPLAY;static constexpr evq<wake          > type::* ptrm=&type::_wake          ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<sleep           > {using type = DISPLAY;static constexpr evq<sleep         > type::* ptrm=&type::_sleep         ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<min             > {using type = DISPLAY;static constexpr evq<min           > type::* ptrm=&type::_min           ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<max             > {using type = DISPLAY;static constexpr evq<max           > type::* ptrm=&type::_max           ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<hide            > {using type = DISPLAY;static constexpr evq<hide          > type::* ptrm=&type::_hide          ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<resize          > {using type = DISPLAY;static constexpr evq<resize        > type::* ptrm=&type::_resize        ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<move            > {using type = DISPLAY;static constexpr evq<move          > type::* ptrm=&type::_move          ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<fullscreen      > {using type = DISPLAY;static constexpr evq<fullscreen    > type::* ptrm=&type::_fullscreen    ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<close           > {using type = DISPLAY;static constexpr evq<close         > type::* ptrm=&type::_close         ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<display_conn    > {using type = DISPLAY;static constexpr evq<display_conn  > type::* ptrm=&type::_display_conn  ;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<display_orient  > {using type = DISPLAY;static constexpr evq<display_orient> type::* ptrm=&type::_display_orient;static constexpr type SYS::* ps =&SYS::display;  };
template <>getEventT<display_power   > {using type = DISPLAY;static constexpr evq<display_power > type::* ptrm=&type::_display_power ;static constexpr type SYS::* ps =&SYS::display;  };




}


#endif
