#pragma once
/*
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
#include <glm.hpp>
#include "impl.hpp"
#include "implmain.hpp"
#include <strata/petri/vects.hpp>
#include <strata/petri/queue.hpp>
#include <vector>
#include <memory>
#include <filesystem>
#include <atomic>
#include <future>
#include <cpuid.h>
#define fs std::filesystem


#include <strata/backend/implgl.hpp>
#ifdef STRATA_IMPL_WIN
// #define STRATA_IMPL_VK
// #define STRATA_IML_DX
#endif
#ifdef STRATA_IMPL_ANDROID
#define STRATA_IMPL_VK
#endif
#ifdef STRATA_IMPL_LINUX
#define STRATA_IMPL_VK
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
    virtual void load_shared(fs::path p);
    virtual void unload_shared(shared s);  
};
    

namespace events {
#include "impl.def.hpp"
#define MAXPOLL 10
template<typename T , int size>
struct evq {
    T[size] d;
    int pos ;
    int pos(){return this->pos;};
    void clear(){this->pos=0;};
    void push(T s){}
    void operator+=(T s){if(pos==size-1){this->clear();return;};this->d[pos]=s;this->pos++;};
    evq() {

    };
};

using click        = int        ;//,           _click   >;    
using dbclick      = int        ;//,   _dbclick>;
using mousedown    = int        ;//,   _mousedown>;        
using mouseup      = int        ;//,   _mouseup>;      
using mouse_move   = glm::ivec2 ;//,   _mouse_move>;//xy
using mouse_wheel  = int        ;//,   _mouse_wheel>; //x       
using mouse_wheelh = int        ;//,   _mouse_wheelh>;
class MOUSE: public  event_sys<evs::_MOUSE> {
 public:
    
 const uint flag=_MOUSE;
    evq<click ,MAXPOLL>       last_click; 
    evq<dbclick ,MAXPOLL>     last_db_click;     
    evq<mousedown ,MAXPOLL>   last_down;          
    evq<mouseup ,MAXPOLL>     last_up;        
    evq<mouse_move,MAXPOLL>  last_move;           
    evq<mouse_wheel,MAXPOLL> last_wheel;     
    evq<mouse_wheelh,MAXPOLL> last_wheelh;     
    void clear()final{this->last_click.clear();this->last_down.clear();this->last_up.clear();this->last_press.clear();this->last_move.clear();this->last_wheel.clear();}
    bool detect_combo(glm::ivec2* s){
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
    int detect_combo(uint size_combos ,glm::ivec2* s){

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
    virtual glm::vec2 get_pos(){return this->last_move.data()};
    virtual bool get_state(short int bt){return this->last_press.data==bt};
     void push_click(int click,int index=0) final {this->ev_main.push(mouse_move(click,index));}
     void push_move(glm::vec2 mv,int index=0) final {this->ev_main.push(mouse_move(mv,index));};
     void push_down(int down,int index=0) final {this->ev_main.push(mouse_down(down,index));};
     void push_up(int up,int index=0) final {this->ev_main.push(mouse_up(up,index));};
     void push_wheel(float wheel,int index=0) final {this->ev_main.push(mouse_wheel(wheel,index));};
     void push_wheelh(float wheel,int index=0) final {this->ev_main.push(mouse_wheelh(wheel,index));};
     void push_click(click ev) final {this->ev_main.push(ev);}
     void push_move(move ev) final {this->ev_main.push(ev);};
     void push_down(down ev) final {this->ev_main.push(ev);};
     void push_up(up ev) final {this->ev_main.push(ev);};
     void push_wheel(wheel ev) final {this->ev_main.push(ev);};
     void push_wheelh(wheelh ev) final {this->ev_main.push(ev);};

     void click_cb(int click,int index=0) final {this->last_click+=mouse_move(click,index);}
     void move_cb(glm::vec2 mv,int index=0) final {this->last_move+=mouse_move(mv,index);};
     void down_cb(int down,int index=0) final {this->last_down+=mouse_down(down,index);};
     void up_cb(int up,int index=0) final {up_check(up);this->last_up+=mouse_up(up,index);};
     void wheel_cb(float wheel,int index=0) final {this->last_wheel+=mouse_wheel(wheel,index);};
     void wheelh_cb(float wheel,int index=0) final {this->last_wheelh+=mouse_wheelh(wheel,index);};
     void dbclick_cb(dbclick ev) final {this->last_dbclick+=ev;}
     void click_cb(click ev) final {this->last_click+=ev;}
     void move_cb(mouse_move ev) final {this->last_move+=ev;};
     void down_cb(mousedown ev) final {this->last_down+=ev;};
     void up_cb(mouseup ev) final { up_check(ev.data());this->last_up+=ev;};
     void wheel_cb(mouse_wheel ev) final {this->last_wheel+=ev;};
     void wheelh_cb(mouse_wheel ev) final {this->last_wheelh+=ev;};
    
     glm::vec2 Pos(int index=0);
     glm::vec2 WinPos();
    virtual void handle();
    virtual void _handle(){
        this->handle();

    };
    void init()override{
        this->_init();};
    };
   
}; 
using keyup = int,        ;// _keyup>; // x button, y index    
using keydown = int,        ;// _keydown>; // x button, y index      
using keypress = int         ;//,_keypress>; // x button, y index       
using keycombo = glm::ivec4   ;//,_keycombo> ; //-1 is 
class KEY : public event_sys<evs::_KEY> {
 public:
    evq<keyup,MAXPOLL>    last_keyup;
    evq<keydown,MAXPOLL>  last_keydown;
    evq<keypress,MAXPOLL> last_keypress;
    evq<keycombo,MAXPOLL>  last_keycombo;          

    
    bool push_up(char key,int index) final {this->evmain.push(keyup(key,index));};
    bool push_down(char key,int index) final {this->evmain.push(keydown(key,index));};    
    bool push_press(char key,int index) final {this->evmain.push(keypress(key,index));};    
    bool push_up(up ev) final {this->evmain.push(ev);};
    bool push_down(down ev) final {this->evmain.push(ev);};    
    bool push_press(press ev) final {this->evmain.push(ev);};    

    bool up_cb(char key,int index) final {this->last_keyup.push(keyup(key,index));};
    bool down_cb(char key,int index) final {this->last_keydown.push(keydown(key,index));};    
    bool press_cb(char key,int index) final {this->last_keypress.push(keypress(key,index));};    
    bool up_cb(up ev) final {this->last_keyup.push(ev);};
    bool down_cb(down ev) final {this->last_keydown.push(ev);};    
    bool press_cb(press ev) final {this->last_keypress.push(ev);};    
    
    struct keyComboCom {
        glm::ivec4 combo ;
        void (*func)();
    };  
    std::vector<keycomboCom>  s ;
    void clearKeyCombo(){

    };
    void addKeyCombo(){

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
}; // index 
using joy_hat = int ;        //,_joy_hat>;  
using joy_axis = glm::ivec3 ;        //,_joy_axis>; // x axis y index       
using joy_up = int ;        //,_joy_up>;    
using joy_down = int ;        //,_joy_down>;      
using joy_press = int ;        //,_joy_press>;     
struct joycap {

};
class  JOY : public event_sys<evs::_JOY> { // TODO handle multi input by calling multiple
 public:
        evq<joy_hat,MAXPOLL>   last_hat;
        evq<joy_axis,MAXPOLL>  last_axis;    
        evq<joy_up,MAXPOLL>    last_up;  
        evq<joy_down,MAXPOLL>  last_down;    
        evq<joy_press,MAXPOLL> last_press;   
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

void hat_cb(joy_hat ev) final {this->last_hat=ev;};      //void push_up(joy_hat ev) final {this->evmain.push(ev);};
void up_cb(joy_up ev) final {this->last_up=ev;};         //void push_up(joy_up ev) final {this->evmain.push(ev);};
void down_cb(joy_down ev) final {this->last_down=ev;};   //void push_down(joy_down ev) final {this->evmain.push(ev);};
void press_cb(joy_press ev) final {this->last_press=ev;};//void push_press(joy_press ev) final {this->evmain.push(ev);};
void axis_cb(joy_axis ev) final {this->last_axis=ev;};   //void push_axis(joy_axis ev) final {this->evmain.push(ev);};
void hat_cb(int btn,int index) final {this->last_hat=joy_hat(btn,index);};           //void push_up(int btn,int index) final {this->evmain.push(joy_hat(btn,index));};
void up_cb(int btn,int index) final {this->last_up=joy_up(btn,index);};              //void push_up(int btn,int index) final {this->evmain.push(joy_up(btn,index));};
void down_cb(int btn,int index) final {this->last_down=joy_down(btn,index);};        //void push_docb(int btn,int index) final {this->evmain.push(joy_down(btn,index));};    
void press_cb(int btn,int index) final {this->last_press=joy_press(btn,index);};     //void push_pr_cb(int btn,int index) final {this->evmain.push(joy_press(btn,index));};    
void axis_cb(int16 axis,int index) final {this->last_axis=joy_axis(axis,index);};    //void push_axcb(int16 axis,int index) final {this->evmain.push(joy_axis(axis,index));};    

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
using CONT_press= int;//        _CONT_press>;                    
using CONT_down = int;//        _CONT_down>; 
using CONT_up =   int;//        _CONT_up>; 
using CONT_dpad = int;//        _CONT_dpad>;
using CONT_axis = glm::ivec2;//        _CONT_axis>;  // Axis index;
using CONT_trig = glm::ivec2;
class CONT: public event_sys<evs::_CONT> {
 public:
    evq<CONT_press,MAXPOLL> last_press;      
    evq<CONT_down,MAXPOLL>  last_down;     
    evq<CONT_up,MAXPOLL>    last_up;   
    evq<CONT_dpad,MAXPOLL>  last_dpad;     
    evq<CONT_axis,MAXPOLL>  last_laxis;     
    evq<CONT_axis,MAXPOLL>  last_raxis;
    evq<CONT_trigger,MAXPOLL> last_tr;
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

    
    virtual void handle(int index=0);
    virtual handleMulti(){

    };
    virtual int get_state(int btn=-1,  int index=0); // If negative then means get all pressed
    
    virtual int get_axis(int axis=-1,  int index=0 );
    virtual int get_dpad(int index =0);


    virtual void _init();
    void init(){event_sys::init();};
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

using touch_move =glm::vec4; ///,_touch_move>; //xy last zw move
using touch_tap  = glm::vec2; ///,_touch_tap>;// tap
using touch_zoom = glm::vec4; ///,_touch_gesture>; // xy move,z rotate,w zoom
using touch_gesture = evq<glm::vec4,MAXPOLL*MAXPOLL>; ///,_touch_zoom>; // rotate


class TOUCH: public event_sys<evs::_TOUCH> { 
 public:
     evq<touch_tap,MAXPOLL> last_tap;
     evq<touch_tap,MAXPOLL> last_up;
     evq<touch_tap,MAXPOLL> last_down;
     evq<touch_move,MAXPOLL> last_move;
     evq<touch_zoom,MAXPOLL> last_zoom;
    std::vector<touch_gesture,MAXPOLL> last_gesture;

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
        bool move_cb(vect<glm::vec4> d,int index){this->last_move=move(d,index);}      bool push_touch_move(vect<glm::vec4> d,int index){this->evmain.push(move_cb(d,index));}
        bool tap_cb(vect<glm::vec2> d,int index){this->last_tap=tap(d,index);}      bool push_touch_tap(vect<glm::vec2> d,int index){this->evmain.push(tap_cb(d,index));}
        bool zoom_cb(mat<glm::vec2> d,int index){this->last_zoom=zoom(d,index);}      bool push_touch_zoom(mat<glm::vec2> d,int index){this->evmain.push(zoom_cb(d,index));}
        bool gesture_cb(vect<glm::vec4> d,int index){this->last_gesture=gesture(d,index);}      bool push_touch_gesture(vect<glm::vec4> d,int index){this->evmain.push(gesture_cb(d,index));}
    void move_cb(touch_move ev){this->last_move_cb=ev;};           void push_move(touch_move ev){this->evmain.push(ev);};
    void tap_cb(touch_tap ev){this->last_tap_cb=ev;};              void push_tap(touch_tap ev){this->evmain.push(ev);};
    void zoom_cb(touch_zoom ev){this->last_zoom_cb=ev;};           void push_zoom(touch_zoom ev){this->evmain.push(ev);};
    void gesture_cb(touch_gesture ev){this->last_gesture_cb=ev;};  void push_gesture(touch_gesture ev){this->evmain.push(ev);};
     void down_cb(mousedown ev) final {this->last_down+=ev;};
     void up_cb(mouseup ev) final { up_check(ev.data());this->last_up+=ev;};

    void init(){event_sys::init();};
    void record_gesture(){this->rec_gest=true;};
    vect<touch_move> finish_gesture(){this->reg_get=false;return this->s};
    void priority(){



        // gesture
        if(rec_gest){this->s.push(this->last_move);};
    };
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
class DISPLAY : event_sys<evs::_DISPLAY> {
 public:
    vect<glm::ivec3> disp; // xy=wh ; z=hz;
    vect<glm::ivec3> mon;
    uint num;
    void _init(); // Initialize the subsystem
    void init() {this->_init()}; 
    virtual event* resolve();
    virtual event* handle();
    virtual void listen();// Checks if there was an event;
    virtual event filter(event* ev);

    vec2 get_data(uint pos=0){return this->disp[pos];}; // hw(pixels) ,hw(cm)
    int get_width(uint pos=0){return this->disp[pos][0];};
    int get_height(uint pos=0){return this->disp[pos][1];};
    int get_index(uint pos=0){return this->disp[pos][2];};
    glm::ivec3 get_monitor_data(uint pos=0); // w,h,hz
    glm::ivec3 get_display_data(uint pos=0); // w,h,hz
    bool is_portrait(uint pos){return (this->disp[pos][0]<this->disp[pos][1]);};
    int Num();
    int get_monitor_display(uint pos=0);
    virtual vec2 get_data(uint pos=0){this->_get_data this->disp[pos];}; // hw(pixels) ,hw(cm)
    virtual int get_width(uint pos=0){this->_get_width this->disp[pos][0];};
    virtual int get_height(uint pos=0){this->_get_height this->disp[pos][1];};
    virtual int get_index(uint pos=0){this->_get_index this->disp[pos][2];};
 
    void change_cb()
    void conn_cb(uint index,bool val = true){this->evmain->push(display_conn::display_conn(index,val);)};
    void discon_cb()
    void power_cb(uint index,bool val = true){this->evmain->push(display_power::display_power(index,val);)};
    void orient_cb(uint index,bool val = true){this->evmain->push(display_power::display_orient(index,val);)};
    virtual void handle();
    virtual void init();
    virtual void close();
    virtual bool _get_mode();
    void get_mode(){
        bool res=_get
    }; // 
};
#ifdef STRATA_CAPABILTY_AUDIO
class AUDIO : event_sys<evs::_AUDIO> {

};
#endif
#ifdef STRATA_CAPABILTY_SENSOR
using gyro  =  glm::vec3//_gyro>;     
using accel  = glm::vec3//_accel>;      
using mag  =   float //,_mag>;    
using baro  =  float //,_baro>;     
using humid  = float //,_humid>;      
using pos  =   float //,_pos>;   
using mic  =   int** //,_mic>;    
using lidar = double** //,_lidar>;      
using cam  =  double** //,_cam>;    
class SENSOR : event_sys<evs::_SENSOR> {
    evq<gyro, MAXPOLL >   last_gyro;
    evq<accel, MAXPOLL >  last_accel;
    evq<mag, MAXPOLL >    last_mag;
    evq<baro, MAXPOLL >   last_baro;
    evq<humid, MAXPOLL >  last_humid;
    evq<pos, MAXPOLL >    last_pos;
    evq<mic, MAXPOLL >    last_mic;
    evq<lidar, MAXPOLL >  last_lidar;
    evq<cam, MAXPOLL >    last_cam;  
};
#endif
template <typename win>
class SYS : public event_sys<evs::_SYS> { 
    public:

  uint flag=_SYS;
    // event_main evmain;
    
#ifdef STRATA_CAPABILITY_MOUSE 
MOUSE      sMOUSE;
#endif    
#ifdef STRATA_CAPABILITY_KEY
KEY        sKEY;
#endif
#ifdef STRATA_CAPABILITY_JOY 
JOY        sJOY;
#endif
#ifdef STRATA_CAPABILITY_CONT 
CONT       sCONT;
#endif
#ifdef STRATA_CAPABILITY_TOUCH 
TOUCH      sTOUCH;
#endif
#ifdef STRATA_CAPABILITY_DISPLAY 
DISPLAY    sDISPLAY;
#endif
#ifdef STRATA_CAPABILITY_AUDIO 
AUDIO      sAUDIO;
#endif
#ifdef STRATA_CAPABILITY_SENSOR 
SENSOR     sSENSOR;
#endif



    void initMouse();
    void initKey();
    void initJoy();
    void initCont();
    void initTouch();
    void initInt();
    void initUi();
    void initAudio();
    void initSensor();
    
    virtual bool wake(wake ev);
    virtual bool sleep(sleep ev);
    virtual bool min(min ev);
    virtual bool max(max ev);
    virtual bool hide(hide ev);
    virtual bool resize(resize ev);
    virtual bool move(move ev);
    virtual bool fullscreen(fullscreen ev);
    virtual bool close(close ev)final{return this->fullscreen(ev);};
    virtual bool display_conn(display_conn ev);
    virtual bool display_orient(display_orient ev);
    virtual bool display_power(display_power ev);
    bool wake(evun ev)final{return this->wake(ev.wake)};
    bool sleep(evun ev)final{return this->sleep(ev.sleep)};
    bool min(evun ev)final{return this->min(ev.min)};
    bool max(evun ev)final{return this->max(ev.max)};
    bool hide(evun ev)final{return this->hide(ev.hide)};
    bool resize(evun ev)final{return this->resize(ev.resize)};
    bool move(evun ev)final{return this->move(ev.move)};
    bool fullscreen(evun ev)final{return this->fullscreen(ev.fullscreen)};
    bool close(evun ev)final{return this->fullscreen(ev.close)};
    bool display_conn(evun ev){return this-> display_conn(ev.display_conn)};
    bool display_orient(evun ev){return this-> display_orient(ev.display_orient)};
    bool display_power(evun ev){return this-> display_power(ev.display_power)};
    
    
   
    using winty = win;
    vect<win> wins;
    vect<glm::ivec4> wind;
    int curr_win_index=0;
    void _init(); // Initialize the subsystem
    virtual event* resolve();
    virtual event* handle();
     void listen(){
        for(int i=0;i<this->evsys.size();i++){this->evsys[i].listen();};
     };// Checks if there was an event;
    event filter(event* ev){ev};
    virtual void handle();
   
    void init() {        
        this->_init()}; 
    void init_evsys(uint flags){
        if( (flags & MOUSE::flag)==MOUSE::flag)       {this->sMOUSE.init();};
        if( (flags & KEY::flag)==KEY::flag)           {this->sKEY.init();};
        if( (flags & JOY::flag)==JOY::flag)           {this->sJOY.init();};
        if( (flags & CON::flag)==CON::flag)           {this->sCON.init();};
        if( (flags & TOUCH::flag)==TOUCH::flag)       {this->sTOUCH.init();};
        if( (flags & AUDIO::flag)==AUDIO::flag)       {this->sAUDIO.init();};
        if( (flags & SENSOR::flag)==SENSOR::flag)     {this->sSENSOR.init();};
    };
    using MIN = 0b0001;
    using MAX = 0b0010;
    using HIDE = 0b0100;
    using NORMAL = 0b1000;
    void selfclose(){delete this;};
    void sleep_callback()final{this->evmain->push(sleep::sleep(this->cur_win_index,true));};;
    void wake_callback()final{this->evmain->push(wake::wake(this->cur_win_index,true));};
    void min_callback()final{this->evmain->push(min::min(this->cur_win_index,true));}
    void max_callback()final{this->evmain->push(max::max(this->cur_win_index,true));}
    void restore_callback()final{this->evmain->push(restore::restore(this->cur_win_index,true));};
    void hide_callback()final{this->evmain->push(hide::hide(this->cur_win_index,true));};
    void resize_callback()final{this->evmain->push(resize::resize(this->curr_win_index,glm::ivec2(this->wind[this->cur_win_index][2],this->wind[this->cur_win_index][3]));};;
    void move_callback()final{this->evmain->push(move::move(this->curr_win_index,glm::ivec2(this->wind[this->cur_win_index][0],this->wind[this->cur_win_index][1])));};;
    void fullscreen_callback(bool val=true)final{this->evmain->push(fullscreen::fullscreen(this->cur_win_index,val));};
    void close_callback()final{this->evmain->push(close::close(true));this->close_app_win_func();}
    #define _custom_tabbar 0b00001
    #define _resizable     0b00010
    #define _transparent   0b00100
    #define _always_on_top 0b01000
    #define _tool          0b10000
    #define _default       0b00011
    virtual win create_win(glm::ivec2 size,glm::ivec2 pos,win parent=NULL,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    win create_child_cur (glm::ivec2 size,glm::ivec2 pos,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) final{
            return this->create_win (glm::ivec2 size,glm::ivec2 pos,this->wins[this->curr_win_index].w,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    } ;
    virtual glm::ivec2 winpos(win w=this->wins[0]);
    virtual glm::ivec2 winsize(win w=this->wins[0]);
    virtual glm::ivec4 wininfo(win w=this->wins[0]);
    virtual void winresize(win w=this->wins[0],glm::ivec2 addsize);
    virtual void winmove(win w=this->wins[0],glm::ivec2 addpos);
    virtual void winminimize(uint pos);
    virtual void winmaximize{uint pos};
    virtual void winrestore{uint pos};
    virtual void winhide(uint pos);
    
    virtual bool is_min(win w=this->wins[0])
    virtual bool is_hidden(win w=this->wins[0])
    virtual bool is_normal(win w=this->wins[0])
    virtual bool is_max(win w=this->wins[0])
    virtual void set_win_opacity(uint index,float opacity);
    virtual void set_win_fullscreen(uint index);
    virtual void close_win();
    virtual void sleep(int mstime=2000);
    virtual void _handle(); // Called during the event loop
    void handle() final{
        this->_handle();
        for(int i =0; i<this->evsyspriority.size();i++){this->evsyspriority.handle();};
    };
    void set_close(void (*const close_app)() = this->def_close){this->close_app_win_func= close_app;};
    virtual void _init();// Set callbacks
    void init(void (*const close_app)() ){set_close(close_app);this->_init();for(int i=0;i<this->evsyspriority.size();i++){this->evsyspriority[i].init();};
    SYS(uint flags)=default{this->flag=flags;this->init_evsys(flags);}
};

};


#define MAIN_DEF(ev_m) ev_m main; 
#define NS_USE(ns) using namespace ns;

event_main evmain;
#ifdef STRATA_IMPL_SDL
#include "impl_sdl.hpp"
using namespace SDL_events;
#endif
#ifdef STRATA_IMPL_LINUX
#include "impl_linux.hpp"
using namespace linux_events;
using env = linux_env;
using evns = linux_events;
#elifdef STRATA_IMPL_WINDOWS
#include "impl_win.hpp"
using namespace win_events;

#elifdef STRATA_IMPL_ANDROID
#include "impl_android.hpp"
using namespace android_events;
#elifdef
#endif


