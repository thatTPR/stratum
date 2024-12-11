#pragma once
#include "impl.hpp"
#include "implmain.hpp"
#include <strata/petri/vects.hpp>
#include <strata/petri/queue.hpp>
#include <memory>
#include <filesystem>
#include <atomic>
#include <future>
#define fs std::filesystem

#ifdef STA_IMPL_WIN
#define STA_IMPL_VK
#define STA_IML_DX
#endif
#ifdef STA_IMPL_ANDROID
#define STA_IMPL_VK
#endif
#ifdef STA_IMPL_LINUX
#define STA_IMPL_VK
#endif


template<typename device,typename _shader, typename _stage>
class strata_impl {
    using stage = _stage ;


virtual void create_fullscreen();
virtual void get_gpu_info();
virtual _shader load_shader(const uint32_t shader[] );
virtual void shader_bind(_shader shader,auto*... uniforms);
    void descriptor_set();
    void descriptor_pool();
virtual void load_SSBO(_shader shader,auto* buffer);
virtual void load_UBO(_shader shader,auto* buffer);
virtual void draw(_stage ;);
virtual void blend();
virtual void mesh_load();
virtual void texture_load();

};


// Scope : 
// gpu Platform info
// cpu Platform info  
// window  
// power management
// input events

// GPU info
// bool hasThing();
// CPU info

// Window
s_init();
s_create_window();
s_del_window();

template <typename shared,typename procinstance>
class strata_env{
    struct cpu_info {
        std::string name;
        std::string arch;

    };
    public:
    using sharedty= shared; 
   
    virtual void init(int flags); // System initialization
    #ifdef STA_IMPL_VK
    virtual void initVk(win w, VkInstance inst, VKSurfaceKHR* surface, procinstance hInstance);
    #endif
    #ifdef STA_IMPL_DX
    virtual void initDx(){std::cerr<<"System has no dx implementation"};
    #endif
    void cpu_info();
    virtual void load_shared(fs::path p);
    virtual void unload_shared(shared s);
    
    };
    
    

} ;


namespace events {
enum evs {

 _DEFAULT=                0,
_click=                  1,
_mousedown=               2,
_mouseup=                 3,
_mousepress=              4,
_mouse_move=              5,
_mouse_wheel=             6,
    _MOUSE=                   (_click|_mousedown |_mouseup |_mousepress|_mouse_move |_mouse_wheel),                                 ,
_keyup=                   8,
_keydown=                 9,
_keypress=               10,
    _KEY=                    (_keyup|_keydown|_keypress),
_joy_hat  =              12,
_joy_axis=               13,
_joy_up=                 14,
_joy_down=               15,
_joy_press=              16,
    _JOY=                    (_joy_axis|_joy_up|_joy_down|_joy_press),
_CONT_axis=        22,
_CONT_up=          23,
_CONT_down=        24,
_CONT_press=       25,
_CONT_dpad=        26,
_CONT=             ( _CONT_axis|_CONT_up|_CONT_down|_CONT_press),
_touch_move=             30,
_touch_tap=              31,
_touch_gesture=          32,
_touch_zoom=             33,
_TOUCH=                  ( _touch_move|_touch_tap|_touch_gesture|_touch_zoom),
        _IDEV_ALL = _MOUSE | _KEY | _JOY | _CONT | _TOUCH ,
_MOVE=              0x01000000,
_ACC=               0x10000000,
_motion=            0x01000010,
_accmotion=         0x10000010,
_rotate2d=          0x01000100,
_translate2d=       0x01001000,
_rotate3d=          0x01010000,
_translate3d=       0x01100000,
_accrotate2d=       0x10000100,
_acctranslate2d=    0x10001000,
_accrotate3d=       0x10010000,
_acctranslate3d=    0x10100000,
_INT_NAV=( _up|_down|_left|_right|_forward|_back),
_INT_GAME=( _up|_down|_left|_right|_forward|_back|_accup|_accdown|_accleft|_accright|_accforward|_accback),
_INT_SIM=( _yawleft|_yawright|_pitchdown|_pitchup|_accyawleft|_accyawright|_accpitchdown|_accpitchup| _rotate2d|_translate2d|_rotate3d|_translate3d|_accrotate2d|_acctranslate2d|_accrotate3d|_acctranslate3d),
_INT=( INT_NAV|INT_GAME| INT_SIM  ),
_enter=     228,
_leave=     229,
_focus=     230,
_drag=      231,
_dragstart= 232,
_dragend=   233,
_keycombo=  234,
_dbclick=   235,
_combo=     236,
_text_in=   237,
_text_edit= 238,
_clipboard= 239,
_play_audio=           252,    
_play_audio_about_to=  253,     // For loading,
_AUDIO= (play_audio |play_audio),
_UI= (_enter|_leave|_focus|_drag|_dragstart|_dragend|_keycombo|_dbclick|_click|_combo|_text_in|_text_edit|_clipboard),
_wake=        356,
_sleep=       357,
_min=         358,
_max=         359,
_hide=        360,
_move=        361,
_resize=      362,
_fullscreen=  363,
_close=       364,
_display_conn=365,
_display_power=366,
_displat_orient=367,
_SYS=( _wake|_sleep|_min|_max|_move|_resize|_fullscreen|_close),
};


    template <typename T , evs _type =evs::_DEFAULT>
    class event {
        public:
        using ty = T;
        const uint type = _type;
        T data;
        uint32 ms;
        int index; // device index
        static const std::string name = ev_map[type];  
        operator bool() const {return *(this->data);}

        inline bool operator<=(event& lhs,event& rhs){return lhs.data==rhs.data;};
        inline bool operator>=(event& lhs,event& rhs){return lhs.data==rhs.data;};
        inline bool operator<(event<d>& lhs,event<d>& rhs){return lhs.data<rhs.data};
        inline bool operator>(event<d>& lhs,event<d>& rhs){return lhs.data>rhs.data};
        inline bool operator==(event<d>& lhs,event<d>& rhs){return lhs.data==rhs.data};
        inline bool operator!=(event<d>& lhs,event<d>& rhs){return lhs.data!=rhs.data};
        inline bool operator<=>(event<d>& lhs,event<d>& rhs){return lhs.data<=>rhs.data};
        std::string parser_cls_inst(){
            std::string ret;
            ret+=map[ty]+"("+ ;
        };
        d get(){return this->data;};
        int get_index(){return this->index;};
        uint32 get_time(){return this->ms;};
        event(d data,uint32 ms){
            this=default;
            this->data = data; this->ms = ms;
        };
        event() = default ;
        event(event<T,type> s) = default {this = s;}
        event(T data){this->data = data;}
        event(T data, int index);{this->data = data;this->index=index;}
        event(T data, int index,uint32 ms);{this->data = data;this->index=index;this->ms=ms;}
        
    };
    // template <>
    // class event<void,_DEFAULT>{
    
    //     template<typename t,uint _ty>
    //     event<t,_ty> operator=(event<t,_ty> s){ return s;};
    // };
    // using ev_default = event<void,_DEFAULT>;
    


    class event_union {

    };
    template <typename T,evs type=evs::_DEFAULT>
    class ev_filter : public event<T,type> {
        public:
        virtual void cb(event<T,type>& lhs); // Callback to call
        virtual bool filter(event<T,type>& lhs){
            return lhs>this;
        };      
    };

    class ev_filters {
        public:
        arr<ev_filter<void, _DEFAULT>*> filters;
        void filter(event<d>& lhs){
            for(int i=0; i<this->filters.size();i++){this->filters->filter(lhs);};
        };
    };
    class event_main ;
    template <uint flag>
    class event_sys : public event<void,ty>{
        public:
        const uint flag=ty;
        event_main* evmain;
        event_sys<evs::_SYS>* sys;
        void _init(); // Initialize the subsystem
        void init() {this->_init()}; 
        virtual event* resolve();
        virtual event* handle();
        virtual void listen();// Checks if there was an event;
        virtual event filter(event* ev);
        event_sys(event_sys<evs::_SYS> sys, event_main* evm){this->sys=sys;this->evmain=evm;};
    };



    template<>
    class event_sys<evs::_DEFAULT>{
        public:
        template<uint flag>
        event_sys<flag> operator=(event_sys<flag> s){
            return s<flag>();
        };
    };
    using evsys_default=event_sys<evs::_DEFAULT>;




using click = event<int,_click>;    
using mousedown = event<int,_mousedown>;        
using mouseup = event<int,_mouseup>;      
using mouse_press = event<int,_mousepress>; // 0 left 1 right 2 wheel, 3 forward ,4 back
using mouse_move = event<vec2,_mouse_move>;//xy
using mouse_wheel = event<float,_mouse_wheel>; //x       
   
class  event_sys<evs::_MOUSE> {
 public:
 
 const uint flag=_MOUSE;
    click       last_click;      
    mousedown   last_down;          
    mouseup     last_up;        
    mouse_press last_press;            
    mouse_move  last_move;           
    mouse_wheel last_wheel;            


    virtual vec2 get_pos();
    virtual bool get_state(short int bt);
     void push_cl(int click,int index=0) final {this->ev_main.push(mouse_move(click,index));}
     void push_move(vec2 mv,int index=0) final {this->ev_main.push(mouse_move(mv,index));};
     void push_press(int press,int index=0) final {this->ev_main.push(mouse_press(press,index));};
     void push_down(int down,int index=0) final {this->ev_main.push(mouse_down(down,index));};
     void push_up(int up,int index=0) final {this->ev_main.push(mouse_up(up,index));};
     void push_wheel(float wheel,int index=0) final {this->ev_main.push(mouse_wheel(wheel,index));};
     void push_click(click ev) final {this->ev_main.push(ev);}
     void push_move(move_cb ev) final {this->ev_main.push(ev);};
     void push_press(press_cb ev) final {this->ev_main.push(ev);};
     void push_down(down_cb ev) final {this->ev_main.push(ev);};
     void push_up(up_cb ev) final {this->ev_main.push(ev);};
     void push_wheel(wheel_cb ev) final {this->ev_main.push(ev);};

     void click_cb(int click,int index=0) final {this->last_click=mouse_move(click,index);}
     void move_cb(vec2 mv,int index=0) final {this->last_move=mouse_move(mv,index);};
     void press_cb(int press,int index=0) final {this->last_press=mouse_press(press,index);};
     void down_cb(int down,int index=0) final {this->last_down=mouse_down(down,index);};
     void up_cb(int up,int index=0) final {this->last_up=mouse_up(up,index);};
     void wheel_cb(float wheel,int index=0) final {this->last_wheel=mouse_wheel(wheel,index);};
     void click_cb(click ev) final {this->last_click=ev;}
     void move_cb(move_cb ev) final {this->last_move=ev;};
     void press_cb(press_cb ev) final {this->last_press=ev;};
     void down_cb(down_cb ev) final {this->last_down=ev;};
     void up_cb(up_cb ev) final {this->last_up=ev;};
     void wheel_cb(wheel_cb ev) final {this->last_wheel=ev;};
   
    void init()override{
        this->_init();};
    };
   
}; 
using MOUSE=event_sys<evs::_MOUSE>;
using keyup = event<int,_keyup>; // x button, y index    
using keydown = event<int,_keydown>; // x button, y index      
using keypress = event<int,_keypress>; // x button, y index       
class event_sys<evs::_KEY> {
 public:
  keyup    last_keyup;
  keydown  last_keydown;
  keypress last_keypress;
    
    bool push_up(int key,int index) final {this->evmain.push(keyup(key,index));};
    bool push_down(int key,int index) final {this->evmain.push(keydown(key,index));};    
    bool push_press(int key,int index) final {this->evmain.push(keypress(key,index));};    
    bool push_up(up ev) final {this->evmain.push(ev);};
    bool push_down(down ev) final {this->evmain.push(ev);};    
    bool push_press(press ev) final {this->evmain.push(ev);};    

    bool up_cb(int key,int index) final {this->last_keyup=push(keyup(key,index));};
    bool down_cb(int key,int index) final {this->last_keydown=push(keydown(key,index));};    
    bool press_cb(int key,int index) final {this->last_keypress=push(keypress(key,index));};    
    bool up_cb(up ev) final {this->last_keyup.push(ev);};
    bool down_cb(down ev) final {this->last_keydown.push(ev);};    
    bool press_cb(press ev) final {this->last_keypress.push(ev);};    

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
using KEY = event_sys<evs::_KEY>
using joy_hat = event<int,_joy_hat>;  
using joy_axis = event<ivec2,_joy_axis>; // x axis y index       
using joy_up = event<int,_joy_up>;    
using joy_down = event<int,_joy_down>;      
using joy_press = event<int,_joy_press>;     
class  event_sys<evs::_JOY> {
 public:
        joy_hat   last_hat;
        joy_axis  last_axis;    
        joy_up    last_up;  
        joy_down  last_down;    
        joy_press last_press;     
void hat_cb(joy_hat ev) final {this->last_hat=ev;};void push_up(joy_hat ev) final {this->evmain.push(ev);};
void up_cb(joy_up ev) final {this->last_up=ev;};void push_up(joy_up ev) final {this->evmain.push(ev);};
void down_cb(joy_down ev) final {this->last_down=ev;};void push_down(joy_down ev) final {this->evmain.push(ev);};
void press_cb(joy_press ev) final {this->last_press=ev;};void push_press(joy_press ev) final {this->evmain.push(ev);};
void axis_cb(joy_axis ev) final {this->last_axis=ev;};void push_axis(joy_axis ev) final {this->evmain.push(ev);};
void hat_cb(int btn,int index) final {this->last_hat=joy_hat(btn,index);};void push_up(int btn,int index) final {this->evmain.push(joy_hat(btn,index));};
void up_cb(int btn,int index) final {this->last_up=joy_up(btn,index);};void push_up(int btn,int index) final {this->evmain.push(joy_up(btn,index));};
void down_cb(int btn,int index) final {this->last_down=joy_down(btn,index);};void push_docb(int btn,int index) final {this->evmain.push(joy_down(btn,index));};    
void press_cb(int btn,int index) final {this->last_press=joy_press(btn,index);};void push_pr_cb(int btn,int index) final {this->evmain.push(joy_press(btn,index));};    
void axis_cb(int16 axis,int index) final {this->last_axis=joy_axis(axis,index);};void push_axcb(int16 axis,int index) final {this->evmain.push(joy_axis(axis,index));};    

    virtual int get_btn_state(int btn=-1 , int index=0;);
    virtual int get_axis_state(int axis=-1 , int index=0;);
    virtual int get_state(int key=-1 , int index=0;);
    virtual int get_hat_state(int hatpos=-1 , int index=0;); // usually 8 starting n;
    virtual void _init()
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
};
using JOY = event_sys<evs::_JOY>;
using CONT_press= event<int,_CONT_press>;                    
using CONT_down = event<int,_CONT_down>; 
using CONT_up = event<int,_CONT_up>; 
using CONT_dpad = event<int,_CONT_dpad>;
using CONT_axis = event<ivec2,_CONT_axis>;  // Axis index;
class event_sys<evs::_CONT> {
 public:
    CONT_press last_press;      
    CONT_down  last_down;     
    CONT_up    last_up;   
    CONT_dpad  last_dpad;     
    CONT_axis  last_axis;     

    bool up_cb(int btn,int index) final {this->last_up=CONT_up(btn,index);};        bool push_up(int btn,int index) final {this->evmain.push(CONT_up(btn,index));};
    bool down_cb(int btn,int index) final {this->last_down=CONT_down(btn,index);};        bool push_down(int btn,int index) final {this->evmain.push(CONT_down(btn,index));};    
    bool press_cb(int btn,int index) final {this->last_press=CONT_press(btn,index);};        bool push_press(int btn,int index) final {this->evmain.push(CONT_press(btn,index));};    
    bool axis_cb(ivec2 axis,int index) final {this->last_axis=CONT_axis(axis,index);};        bool push_axis(ivec2 axis,int index) final {this->evmain.push(CONT_axis(axis,index));};    
    bool dpad_cb(int axis,int index) final {this->last_dpad=CONT_dpad(axis,index);};        bool push_dpad(int axis,int index) final {this->evmain.push(CONT_dpad(axis,index));};    
    
    bool up_cb(up ev) final {this->last_up = ev;};            bool push_up(up ev) final {this->evmain.push(ev);};             
    bool down_cb(down ev) final {this->last_down = ev;};            bool push_down(down ev) final {this->evmain.push(ev);};                 
    bool press_cb(press ev) final {this->last_press = ev;};            bool push_press(press ev) final {this->evmain.push(ev));};                
    bool axis_cb(axis ev) final {this->last_axis = ev;};            bool push_axis(axis ev) final {this->evmain.push(ev));};                
    bool dpad_cb(dpad ev) final {this->last_dpad = ev;};            bool push_dpad(dpad ev) final {this->evmain.push(ev));};                

    
    virtual int get_btn(int btn=-1,  int index=0); // If negative then means get all pressed
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
using CONT= event_sys<evs::_CONT>;
using touch_move = event<vect<vec4>,_touch_move>; //xy last zw move
using touch_tap  =  event<vect<vec2>,_touch_tap>;// tap
using touch_zoom =  event<mat<vec2>,_touch_gesture>; // xy move,z rotate,w zoom
using touch_gesture =event<vect<vec4>,_touch_zoom>; // rotate


class event_sys<evs::_TOUCH> { 
 public:
touch_move last_move;
touch_tap last_tap;
touch_zoom last_zoom;
touch_gesture last_gesture;
    
        bool move_cb(vect<vec4> d,int index){this->last_move=move_cb(d,index);}      bool push_touch_move(vect<vec4> d,int index){this->evmain.push(move_cb(d,index));}
        bool tap_cb(vect<vec2> d,int index){this->last_tap=tap_cb(d,index);}      bool push_touch_tap(vect<vec2> d,int index){this->evmain.push(tap_cb(d,index));}
        bool zoom_cb(mat<vec2> d,int index){this->last_zoom=zoom_cb(d,index);}      bool push_touch_zoom(mat<vec2> d,int index){this->evmain.push(zoom_cb(d,index));}
        bool gesture_cb(vect<vec4> d,int index){this->last_gesture=gesture_cb(d,index);}      bool push_touch_gesture(vect<vec4> d,int index){this->evmain.push(gesture_cb(d,index));}
    suvec2 get_pos();
    vect<suvec2> get_multi_pos();
    void move_cb(touch_move ev){this->last_move_cb=ev;};           void push_move(touch_move ev){this->evmain.push(ev);};
    void tap_cb(touch_tap ev){this->last_tap_cb=ev;};              void push_tap(touch_tap ev){this->evmain.push(ev);};
    void zoom_cb(touch_zoom ev){this->last_zoom_cb=ev;};           void push_zoom(touch_zoom ev){this->evmain.push(ev);};
    void gesture_cb(touch_gesture ev){this->last_gesture_cb=ev;};  void push_gesture(touch_gesture ev){this->evmain.push(ev);};

    virtual void get_touch();
    void init(){event_sys::init();};
    virtual touch_gesture record_gesture(){}
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
using TOUCH = event_sys<evs::_TOUCH>;

using motion = event<vec3,_motion>;
using accmotion = event<vec4,_accmotion>;
using rotate2d = event<vec2,_rotate2d>;
using translate2d = event<vec2,_translate2d>;
using rotate3d = event<vec3,_rotate3d>;
using translate3d = event<vec3,_translate3d>;
using accrotate2d = event<vec2,_accrotate2d>;
using acctranslate2d = event<vec2,_acctranslate2d>;
using accrotate3d = event<vec3,_accrotate3d>;
using acctranslate3d = event<vec3,_acctranslate3d>;


class event_sys<evs::_CONTROL>{
    motion last_motion;
    accmotion last_accmotion;
    rotate2d last_rotate2d;
    translate2d last_translate2d;
    rotate3d last_rotate3d;
    translate3d last_translate3d;
    accrotate2d last_accrotate2d;
    acctranslate2d last_acctranslate2d;
    accrotate3d last_accrotate3d;
    acctranslate3d last_acctranslate3d;

    bool motion_cb(vec3 d,int index){this->last_motion=motion(d,index));};                           bool push_motion(vec3 d,int index){this->evmain.push(motion(d,index));};
    bool accmotion_cb(vec4 d,int index){this->last_accmotion=accmotion(d,index));};                  bool push_accmotion(vec4 d,int index){this->evmain.push(accmotion(d,index));};
    bool rotate2d_cb(vec2 d,int index){this->last_rotate2d=rotate2d(d,index));};                     bool push_rotate2d(vec2 d,int index){this->evmain.push(rotate2d(d,index));};
    bool translate2d_cb(vec2 d,int index){this->last_translate2d=translate2d(d,index));};            bool push_translate2d(vec2 d,int index){this->evmain.push(translate2d(d,index));};
    bool rotate3d_cb(vec3 d,int index){this->last_rotate3d=rotate3d(d,index));};                     bool push_rotate3d(vec3 d,int index){this->evmain.push(rotate3d(d,index));};
    bool translate3d_cb(vec3 d,int index){this->last_translate3d=translate3d(d,index));};            bool push_translate3d(vec3 d,int index){this->evmain.push(translate3d(d,index));};
    bool accrotate2d_cb(vec2 d,int index){this->last_accrotate2d=accrotate2d(d,index));};            bool push_accrotate2d(vec2 d,int index){this->evmain.push(accrotate2d(d,index));};
    bool acctranslate2d_cb(vec2 d,int index){this->last_acctranslate2d=acctranslate2d(d,index));};   bool push_acctranslate2d(vec2 d,int index){this->evmain.push(acctranslate2d(d,index));};
    bool accrotate3d_cb(vec3 d,int index){this->last_accrotate3d=accrotate3d(d,index));};            bool push_accrotate3d(vec3 d,int index){this->evmain.push(accrotate3d(d,index));};
    bool acctranslate3d_cb(vec3 d,int index){this->last_acctranslate3d=acctranslate3d(d,index));};   bool push_acctranslate3d(vec3 d,int index){this->evmain.push(acctranslate3d(d,index));};

    bool motion_cb(motion ev){this->last_motion=ev; };                          bool push_motion(motion ev){this->evmain.push(ev);}
    bool accmotion_cb(accmotion ev){this->last_accmotion=ev; };                 bool push_accmotion(accmotion ev){this->evmain.push(ev);}
    bool rotate2d_cb(rotate2d ev){this->last_rotate2d=ev; };                    bool push_rotate2d(rotate2d ev){this->evmain.push(ev);}
    bool translate2d_cb(translate2d ev){this->last_translate2d=ev; };           bool push_translate2d(translate2d ev){this->evmain.push(ev);}
    bool rotate3d_cb(rotate3d ev){this->last_rotate3d=ev; };                    bool push_rotate3d(rotate3d ev){this->evmain.push(ev);}
    bool translate3d_cb(translate3d ev){this->last_translate3d=ev; };           bool push_translate3d(translate3d ev){this->evmain.push(ev);}
    bool accrotate2d_cb(accrotate2d ev){this->last_accrotate2d=ev; };           bool push_accrotate2d(accrotate2d ev){this->evmain.push(ev);}
    bool acctranslate2d_cb(acctranslate2d ev){this->last_acctranslate2d=ev; };  bool push_acctranslate2d(acctranslate2d ev){this->evmain.push(ev);}
    bool accrotate3d_cb(accrotate3d ev){this->last_accrotate3d=ev; };           bool push_accrotate3d(accrotate3d ev){this->evmain.push(ev);}
    bool acctranslate3d_cb(acctranslate3d ev){this->last_acctranslate3d=ev; };  bool push_acctranslate3d(acctranslate3d ev){this->evmain.push(ev);}



};
using INT = event_sys<evs::_INT>;

;
typedef struct text_edit {
    ivec4 range; // ln,col
    std::string text;
}text_edit; 
using enter = event<bool,_enter> ;
using leave = event<bool,_leave> ;
using focus = event<bool,_focus> ;
using drag = event<bool,_drag> ;
using dragstart = event<bool,_dragstart> ;
using dragend = event<bool,_dragend> ;
using keycombo = event<ivec4,_keycombo> ; //-1 is 
using dbclick = event<ivec2,_dbclick> ;
using combo = event<imat2x4,_combo> ; //r0 keys, r1 mouse
using textedit = event<text_edit,_textedit>;
class event_sys<evs::_UI> {
 public:
    // Lasts
    enter     last_enter;  
    leave     last_leave;  
    focus     last_focus;  
    drag      last_drag; 
    dragstart last_dragstart;      
    dragend   last_dragend;    
    keycombo  last_keycombo;     
    dbclick   last_dbclick;    
    click     last_click;  
    combo     last_combo;  
    textedit  last_textedit;     

    

 const uint flag=_UI;
    public: 
    
    virtual void get_db_click_ms(int per);
    int get_ms(int _ms=200) final{this->ms=_ms}; int16 ms_cur;}
};
using UI =  event_sys<evs::_UI>; 

using wake        = event<bool,_wake>;
using sleep       = event<bool,_sleep>;        
using min         = event<bool,_min>;      
using max         = event<bool,_max>;      
using hide        = event<bool,_max>;
using resize      = event<ivec2,_resize>;
using move        = event<ivec2,_move>;         
using fullscreen  = event<bool,_fullscreen>;             
using close       = event<bool,_close>;                  
using display_conn =event<bool,_display_conn>;  
using display_orient =event<int,_display_orient>;
using display_power=event<int ,_display_power>;
class event_sys<evs::_DISPLAY> {
 public:
    vect<ivec3> disp; // xy=wh ; z=hz;
    vect<ivec3> mon;
    size_t nummon;
    void _init(); // Initialize the subsystem
    void init() {this->_init()}; 
    virtual event* resolve();
    virtual event* handle();
    virtual void listen();// Checks if there was an event;
    virtual event filter(event* ev);

    vec2 get_data(size_t pos=0){return this->disp[pos];}; // hw(pixels) ,hw(cm)
    int get_width(size_t pos=0){return this->disp[pos][0];};
    int get_height(size_t pos=0){return this->disp[pos][1];};
    int get_index(size_t pos=0){return this->disp[pos][2];};
    ivec3 get_monitor_data(size_t pos=0); // w,h,hz
    ivec3 get_display_data(size_t pos=0); // w,h,hz
    bool is_portrait(size_t pos){return (this->disp[pos][0]<this->disp[pos][1]);};
    size_t get_num_monitors();
    size_t get_monitor_display(size_t pos=0);
    virtual vec2 get_data(size_t pos=0){this->_get_data this->disp[pos];}; // hw(pixels) ,hw(cm)
    virtual int get_width(size_t pos=0){this->_get_width this->disp[pos][0];};
    virtual int get_height(size_t pos=0){this->_get_height this->disp[pos][1];};
    virtual int get_index(size_t pos=0){this->_get_index this->disp[pos][2];};
 

    bool conn_callback(uint index,bool val = true){this->evmain->push(display_conn::display_conn(index,val);)};
    bool power_callback(uint index,bool val = true){this->evmain->push(display_power::display_power(index,val);)};
    bool orient_callback(uint index,bool val = true){this->evmain->push(display_power::display_orient(index,val);)};
    virtual void handle();
    virtual void _init();
    void init(){this->_init();};
    virtual void close();
    virtual bool _get_mode();
    void get_mode(){
        bool res=_get
    }; // 
};
using DISPLAY=event_sys<evs::_DISPLAY>;

    static const std::map<int , std::string> ev_map = {
{evs::_click,"click"},{evs::_mousedown,"mousedown"},{evs::_mouseup,"mouseup"},{evs::_mouseup,"mousepress"}{evs::_mouse_move,"mouse_move"},{evs::_mouse_wheel,"mouse_wheel"},{evs::_MOUSE,"MOUSE"},
{evs::_keyup,"keyup"},{evs::_keydown,"keydown"},{evs::_keypress,"keypress"},{evs::_KEY,"KEY"},
{evs::_joy_axis,"joy_axis"},{evs::_joy_up,"joy_up"},{evs::_joy_down,"joy_down"},{evs::_joy_press,"joy_press"},{evs::_JOY,"JOY"},
{evs::_CONT_axis,"CONT_axis"},{evs::_CONT_up,"CONT_up"},{evs::_CONT_down,"CONT_down"},{evs::_CONT_press,"CONT_press"},{evs::_CONT,"CONT"},
{evs::_touch_move,"touch_move"},{evs::_touch_tap,"touch_tap"},{evs::_touch_gesture,"touch_gesture"},{evs::_touch_zoom,"touch_zoom"},{evs::_TOUCH,"TOUCH"},
{evs::_up,"up"},{evs::_down,"down"},{evs::_left,"left"},{evs::_right,"right"},{evs::_forward,"forward"},{evs::_back,"back"},{evs::_accup,"accup"},{evs::_accdown,"accdown"},{evs::_accleft,"accleft"},{evs::_accright,"accright"},{evs::_accforward,"accforward"},{evs::_accback,"accback"},{evs::_yawleft,"yawleft"},{evs::_yawright,"yawright"},{evs::_pitchdown,"pitchdown"},{evs::_pitchup,"pitchup"},{evs::_accyawleft,"accyawleft"},{evs::_accyawright,"accyawright"},{evs::_accpitchdown,"accpitchdown"},{evs::_accpitchup,"accpitchup"},{evs::_rotate2d,"rotate2d"},{evs::_translate2d,"translate2d"},{evs::_rotate3d,"rotate3d"},{evs::_translate3d,"translate3d"},{evs::_accrotate2d,"accrotate2d"},{evs::_acctranslate2d,"acctranslate2d"},{evs::_accrotate3d,"accrotate3d"},{evs::_acctranslate3d,"acctranslate3d"},{evs::_CONTROL},
{evs::_INT_NAV,"_INT_NAV"},{evs::_INT_GAME,"_INT_GAME"},{evs::_INT_SIM,"_INT_SIM"},{evs::_INT_EDIT,"_INT_EDIT"},{evs::_INT_ALL,"_INT_ALL"},
{evs::_enter,"enter"},{evs::_leave,"leave"},{evs::_focus,"focus"},{evs::_drag,"drag"},{evs::_dragstart,"dragstart"},{evs::_dragend,"dragend"},{evs::_keycombo,"keycombo"},{evs::_dbclick,"dbclick"},{evs::_click,"click"},{evs::_combo,"combo"},{evs::_text_in,"text_in"},{evs::_text_edit,"text_edit"},{evs::_clipboard,"clipboard"},{evs::_UI,"UI"}
{evs::_play_audio,"play_audio"},{evs::_play_audio_about_to,"play_audio_about_to"},{evs::_AUDIO,"AUDIO"},
{evs::_wake,"wake"},{evs::_sleep,"sleep"},{evs::_min,"min"},{evs::_max,"max"},{evs::_hide,"hide"},{evs::_move,"move"},{evs::_resize,"resize"},{evs::_fullscreen,"fullscreen"},{evs::_close,"close"},{evs::_SYS,"SYS"},
{evs::_display_conn,"display_conn"},{evs::_display_power,"display_power"},{{evs::_display_orient,"display_orient"}},{evs::_DISPLAY,"DISPLAY"}

};

template <typename command_sys,typename win, int flags...>
class SYS :  event_sys<evs::_SYS> { 
    public:

 const uint flag=_SYS;
    command_sys* comms;
    event_main evmain;
    MOUSE     sMOUSE;           
    KEY       sKEY;         
    JOY       sJOY;         
    CONT      sCONT;                
    TOUCH     sTOUCH;           
    INT   sINT;                  
    UI        sUI;        
    AUDIO     sAUDIO;           
    INT  sINT ;




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
    
    
    
    void prioirty(){
        
    };
    vect<event_sys<_DEFAULT>*> evsys;
    using winty = win;
    vect<win> wins;
    vect<ivec4> wind;
    int curr_win_index=0;
    void _init(); // Initialize the subsystem
    virtual event* resolve();
    virtual event* handle();
     void listen(){
        for(int i=0;i<this->evsys.size();i++){this->evsys[i].listen();};
     };// Checks if there was an event;
    event filter(event* ev){ev};

   
    void init() {
        
        this->_init()}; 
    void init_evsys(uint flags){
        if( (flags & MOUSE::flag)==MOUSE::flag)       {this->evsys.push(&MOUSE());   this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & KEY::flag)==KEY::flag)           {this->evsys.push(&KEY());     this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & JOY::flag)==JOY::flag)           {this->evsys.push(&JOY());     this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & CON::flag)==CON::flag)           {this->evsys.push(&CON());     this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & TOUCH::flag)==TOUCH::flag)       {this->evsys.push(&TOUCH());   this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & UI::flag)==UI::flag)             {this->evsys.push(&UI());      this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & AUDIO::flag)==AUDIO::flag)       {this->evsys.push(&AUDIO());   this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & INT_ALL::flag)==INT_ALL::flag)   {this->evsys.push(&INT_ALL()); this->evsys[this->evsys.size()-1]0->init();return;};
        if( (flags & INT_NAV::flag)==INT_NAV::flag)   {this->evsys.push(&INT_NAV()); this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & INT_SIM::flag)==INT_SIM::flag)   {this->evsys.push(&INT_SIM()); this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & INT_GAME::flag)==INT_GAME::flag) {this->evsys.push(&INT_GAME());this->evsys[this->evsys.size()-1]0->init();};
        if( (flags & INT_EDIT::flag)==INT_EDIT::flag) {this->evsys.push(&INT_EDIT());this->evsys[this->evsys.size()-1]0->init();};
    };
    using MIN = 0b0001;
    using MAX = 0b0010;
    using HIDE = 0b0100;
    using NORMAL = 0b1000;
void (*const close_app_win_func)();
    void def_close(){delete this;};
    void sleep_callback()final{this->evmain->push(sleep::sleep(this->cur_win_index,true));};;
    void wake_callback()final{this->evmain->push(wake::wake(this->cur_win_index,true));};
    void min_callback()final{this->evmain->push(min::min(this->cur_win_index,true));}
    void max_callback()final{this->evmain->push(max::max(this->cur_win_index,true));}
    void restore_callback()final{this->evmain->push(restore::restore(this->cur_win_index,true));};
    void hide_callback()final{this->evmain->push(hide::hide(this->cur_win_index,true));};
    void resize_callback()final{this->evmain->push(resize::resize(this->curr_win_index,ivec2(this->wind[this->cur_win_index][2],this->wind[this->cur_win_index][3]));};;
    void move_callback()final{this->evmain->push(move::move(this->curr_win_index,ivec2(this->wind[this->cur_win_index][0],this->wind[this->cur_win_index][1])));};;
    void fullscreen_callback(bool val=true)final{this->evmain->push(fullscreen::fullscreen(this->cur_win_index,val));};
    void close_callback()final{this->evmain->push(close::close(true));this->close_app_win_func();}
    
    virtual win create_win(ivec2 size,ivec2 pos,win parent=NULL,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    win create_child_cur (ivec2 size,ivec2 pos,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) final{
            return this->create_win (ivec2 size,ivec2 pos,this->wins[this->curr_win_index].w,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    } ;
    virtual ivec2 get_pos(win w=this->wins[0]);
    virtual ivec2 get_size(win w=this->wins[0]);
    virtual ivec4 get_data_all(win w=this->wins[0]);
    virtual void resize_win(win w=this->wins[0],ivec2 addsize);
    virtual void move_win(win w=this->wins[0],ivec2 addpos);
    virtual void minimize_win(size_t pos);
    virtual void maximize_win{size_t pos};
    virtual void restore_win{size_t pos};
    virtual void hide_win(size_t pos);
    
    virtual bool is_min(win w=this->wins[0])
    virtual bool is_hidden(win w=this->wins[0])
    virtual bool is_normal(win w=this->wins[0])
    virtual bool is_max(win w=this->wins[0])
    virtual void set_win_opacity(size_t index,float opacity);
    virtual void set_win_fullscreen(size_t index);
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
    void set_priority(int place,int flag){
        for(int i = 0;i<this->evsyspriority.size();i++){
            if(this->evsyspriority[i].flag==flag){
                this->evsyspriority.swap(i,place);
                int s = ((place-i)>0)?1:-1;
                for(int j = place ; j != i ; j+=s){
                    this->evsyspriority.swap(place,place+s);
                };
            };
        };
    };
    void set_priority(vect<ivec2> flag_place){
        for(int i=0;i<flag_place.size();i++){
            for(int j = 0 ; j <this->evsyspriority.size();j++){
                if(this->evsyspriority[j].flag==flag_place[i][0]){
                    this->evsyspriority.swap(g,flag_place[1]);
                    break;
                }
            };
        }
    };
    SYS(uint flags){this->init_evsys(flags);}
};

};


#define MAIN_DEF(ev_m) ev_m main; 
#define NS_USE(ns) using namespace ns;

event_main evmain;
#ifdef STA_IMPL_SDL
#include "impl_sdl.hpp"
using namespace SDL_events;
#endif
#ifdef STA_IMPL_LINUX
#include "impl_linux.hpp"
using namespace linux_events;
using env = linux_env;
using evns = linux_events;
#elifdef STA_IMPL_WINDOWS
#include "impl_win.hpp"
using namespace win_events;
void init_win(){

};
#elifdef STA_IMPL_ANDROID
#include "impl_android.hpp"
using namespace android_events;
#elifdef
#endif
#ifdef STA_IMPL_VK
#include "impl_vk.hpp"
using impl = vk_impl;
#else
#ifdef STA_IML_DX
#define D3D12
#include "impl_dx.hpp"
using impl = dx_impl;
#else
#ifdef STA_IMPL_GL
#include "impl_gl.hpp"
using impl = gl_impl;
#endif
#ifdef STA_IMPL_WASM
#include "impl_wasm.hpp"
using env = wasm_env;  
using impl = wasm_impl ;
#endif


