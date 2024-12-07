#pragma once
#include <strata/petri/vects.hpp>
#include <queue>
#include <filesystem>
#include <atomic>
#include <future>
#define fs std::filesystem

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
    virtual void initVk(win w, VkInstance inst, VKSurfaceKHR* surface, procinstance hInstance);
    virtual void initDx(){std::cerr<<"System has no dx implementation"};
    void cpu_info();
    virtual void load_shared(fs::path p);
    virtual void unload_shared(shared s);
    
    };
    
    

} ;


namespace events {
enum
#define _click                    1            
#define _mousedown                2                  
#define _mouseup                  3 
#define _mousepress               4             
#define _mouse_move               5  
#define _mouse_wheel              6
#define _MOUSE                    (_click|_mousedown |_mouseup |_mousepress|_mouse_move |_mouse_wheel)                                     
#define _keyup                    8              
#define _keydown                  9                
#define _keypress                10 
#define _KEY                     (_keyup|_keydown|_keypress)                                      
#define _joy_axis                13
#define _joy_up                  14      
#define _joy_down                15        
#define _joy_press               16
#define _JOY                     (_joy_axis|_joy_up|_joy_down|_joy_press)                               
#define _controller_axis         22                    
#define _controller_button_up    23
#define _controller_button_down  24                              
#define _controller_button_press 25                                
#define _CONTROLLER              ( _controller_axis|_controller_button_up|_controller_button_down|_controller_button_press)
#define _touch_move              30    
#define _touch_tap               31   
#define _touch_gesture           32
#define _touch_zoom              33                  
#define _TOUCH                   ( _touch_move|_touch_tap|_touch_gesture|_touch_zoom)
 
#define IDEV_ALL

#define MOVE                0x01000000              
#define ACC                 0x10000000
#define _motion             0x01000010          
#define _accmotion          0x10000010                          
#define _rotate2d           0x01000100                
#define _translate2d        0x01001000                
#define _rotate3d           0x01010000                
#define _translate3d        0x01100000                
#define _accrotate2d        0x10000100                
#define _acctranslate2d     0x10001000                
#define _accrotate3d        0x10010000                
#define _acctranslate3d     0x10100000                 

#define _CONTROL_NAV ( _up|_down|_left|_right|_forward|_back)
#define _CONTROL_GAME ( _up|_down|_left|_right|_forward|_back|_accup|_accdown|_accleft|_accright|_accforward|_accback)
#define _CONTROL_SIM ( _yawleft|_yawright|_pitchdown|_pitchup|_accyawleft|_accyawright|_accpitchdown|_accpitchup)
#define _CONTROL_EDIT ( _rotate2d|_translate2d|_rotate3d|_translate3d|_accrotate2d|_acctranslate2d|_accrotate3d|_acctranslate3d)
#define _CONTROLL_ALL ( CONTROL_NAV|CONTROL_GAME| CONTROL_SIM | CONTROL_EDIT )

#define _enter      228
#define _leave      229
#define _focus      230
#define _drag       231 
#define _dragstart  232       
#define _dragend    233     
#define _keycombo   234      
#define _dbclick    235
#define _click      236      
#define _combo      236
#define _text_in    237
#define _text_edit  238
#define _clipboard  239


#define play_audio           252    
#define play_audio_about_to  253     // For loading
#define _AUDIO  (play_audio |play_audio)
#define _UI  (_enter|_leave|_focus|_drag|_dragstart|_dragend|_keycombo|_dbclick|_click|_combo|_text_in|_text_edit|_clipboard)

#define _wake         356
#define _sleep        357
#define _min          358
#define _max          359
#define _move         360
#define _resize       361
#define _fullscreen   362
#define _close        363
#define _display_conn 364
#define _display_mode 365
#define _SYS ( _sleep|_min|_max|_move|_resize|_fullscreen|_close)


#define DEFAULT_EVENT_ALL

static const std::map<int , std::string> ev_map = {
{    _click,"click"},{_mousedown,"mousedown"},{_mouseup,"mouseup"},{_mouseup,"mousepress"}{_mouse_move,"mouse_move"},{_mouse_wheel,"mouse_wheel"},{_MOUSE,"MOUSE"},{_keyup,"keyup"},{_keydown,"keydown"},{_keypress,"keypress"},{_KEY,"KEY"},{_joy_axis,"joy_axis"},{_joy_up,"joy_up"},{_joy_down,"joy_down"},{_joy_press,"joy_press"},{_JOY,"JOY"},{_controller_axis,"controller_axis"},{_controller_button_up,"controller_button_up"},{_controller_button_down,"controller_button_down"},{_controller_button_press,"controller_button_press"},{_CONTROLLER,"CONTROLLER"},{_touch_move,"touch_move"},{_touch_tap,"touch_tap"},{_touch_gesture,"touch_gesture"},{_touch_zoom,"touch_zoom"},{_TOUCH,"TOUCH"},{_up,"up"},{_down,"down"},{_left,"left"},{_right,"right"},{_forward,"forward"},{_back,"back"},{_accup,"accup"},{_accdown,"accdown"},{_accleft,"accleft"},{_accright,"accright"},{_accforward,"accforward"},{_accback,"accback"},{_yawleft,"yawleft"},{_yawright,"yawright"},{_pitchdown,"pitchdown"},{_pitchup,"pitchup"},{_accyawleft,"accyawleft"},{_accyawright,"accyawright"},{_accpitchdown,"accpitchdown"},{_accpitchup,"accpitchup"},{_rotate2d,"rotate2d"},{_translate2d,"translate2d"},{_rotate3d,"rotate3d"},{_translate3d,"translate3d"},{_accrotate2d,"accrotate2d"},{_acctranslate2d,"acctranslate2d"},{_accrotate3d,"accrotate3d"},{_acctranslate3d,"acctranslate3d"},{_enter,"enter"},{_leave,"leave"},{_focus,"focus"},{_drag,"drag"},{_dragstart,"dragstart"},{_dragend,"dragend"},{_keycombo,"keycombo"},{_dbclick,"dbclick"},{_click,"click"},{_combo,"combo"},{_text_in,"text_in"},{_text_edit,"text_edit"},{_clipboard,"clipboard"}
};

    template <typename T , uint _type =0>
    class event {
        public:
        using ty = T;
        const uint type = _type;
        T d;
        uint32 ms;
        int index; // device index
        static const std::string name = ev_map[type];  
        operator bool() const {return *(this->data);}
        bool operator<=>(event& lhs, event& rhs){return lhs::ty == rhs::ty};
        bool ev_is_in(event& lhs){
            for(int i=0;i < this->evs->size();i++){if(decltype(*(this->evs[i])) == decltype(lhs)){
                return true;
            } ;};
        }
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
        event(event<T,type> s) = default {this = s;}
        event(T data){this->d = data;}
        event(T data, int index);{this->d = data;this->index=index;}
    };
    template <typname d>
    class ev_filter {
        public:
        event<d>* ev;
        vect<event<d>> filters;
        inline bool operator<=(event<d>& lhs,event<d>& rhs){return lhs<=rhs};
        inline bool operator>=(event<d>& lhs,event<d>& rhs){return lhs>=rhs};
        inline bool operator<(event<d>& lhs,event<d>& rhs){return lhs>=rhs};
        inline bool operator>(event<d>& lhs,event<d>& rhs){return lhs>=rhs};
        inline bool operator==(event<d>& lhs,event<d>& rhs){return lhs>=rhs};
        inline bool operator!=(event<d>& lhs,event<d>& rhs){return lhs>=rhs};
        inline bool operator<=>(event<d>& lhs,event<d>& rhs){return lhs>=rhs};
        virtual void filter(event<d>& lhs,event<d>& rhs){
            return lhs>rhs
        }
        void filter(event<d>& lhs){
            for(int i = 0; i<this->filters.size();i++){
                this->filter(this->ev,lhs);
            };
        };


    };
    template <uint ty=0>
    class event_sys : public event<void,ty>{
        public:
        virtual void init(); // Initialize the subsystem
        virtual event* resolve();
        virtual event* handle();
        virtual void listen();// Checks if there was an event;
        virtual event filter(event* ev);
    };
template <size_t max=8192>
class event_main {
    public:
    vect<flags>;
    vect<event*> events;
    vect<event*> during;
    void resolve_flags(){

    };
    
    long int ms;
    long int sec;
    size_t cur_pos;
    void tick ()final{this->ms++;}
    void tick (short int timems)final{this->ms+=timems;};
    void sec ()final{this->sec++;}
    void sec (short int times)final{this->sec+=times;};
    long int sec_ms(){return this->ms/1000;};
    void push(event* ev) final {this->events.push(ev)};
    bool poll(event* e) final {this->during.cur_pos++; e= &(this->events.first);};
    event* peep(size_t s) final{return this->events[s];};
    void clear_events() final {while(!(this->events.empty())){this->events.pop();};};
    void during_add(event* e)final{this->during.push(e);};
    void during_end() final { 
    this->events.pop(cur_pos); cur_pos=0; ;this->events.push(during); std::async(this->during.clear());};
    void operator bool(){
        this->during();
    };
    bool _during = true;
    void during_loop() final {
        while(_during){
            get_event();
        };
        this->during_end();
    };

    vect<event_sys*> evs_sys;
        void handle()final{
            for(int i=0;i<this->evs_sys.size();i++){
                evs_sys().handle();
            };
        };
        void init()final{
            for(int i=0;i<this->evs_sys.size();i++){
                evs_sys[i].init();
            };
        };
    bool operator==(event* e){return this->peep(cur_pos).ty == e.ty ;}
    operator bool () const {return this->poll()};
    this& operator=(vect<event*> evs){
        events_main s;
        for(int i=0;i<evs.size();i++){
            s.evs.push(evs[i]);
        };
        this&=s;
    };
    event_main(int flag){this->flags.push(flag);};
    events_main(int first_flag,int flags...){
        this->flags.push(first);
    };
    
    };
    event_main evmain;

    typedef struct joy_axis {
        float pos;
        uint16 axis_no;
        bool operator<(joy_axis& lhs, joy_axis& rhs){return lhs.pos<rhs.pos;}
        bool operator>(joy_axis& lhs, joy_axis& rhs){return lhs.pos<rhs.pos;}

     }joy_axis;
class click                  :public event<int,_click>;    
class mousedown              :public event<int,_mousedown>;        
class mouseup                :public event<int,_mouseup>;      
class mouse_press            :public event<int,_mousepress>; // 0 left 1 right 2 wheel, 3 forward ,4 back
class mouse_move             :public event<vec2,_mouse_move>;//xy
class mouse_wheel            :public event<float,_mouse_wheel>; //x          
class MOUSE                  :public event_sys<_MOUSE>{
    virtual vec2 get_pos();
    virtual bool get_state(short int bt);
    virtual 
    virtual short int resolve(event ev) {
        return ev::ty;
    };
    bool filter(short int type_flag){
        switch(type_flag){
            case _click :{return true;};
            case _mousedown :{return true;};
            case _mouseup :{return true;};
            case _mousepress :{return true;};
            case _mouse_move :{return true;};
            case _mouse_wheel :{return true;};
        }
        return false;
    };
}; 
class keyup                  :public event<int,_keyup>; // x button, y index    
class keydown                :public event<int,_keydown>; // x button, y index      
class keypress               :public event<int,_keypress>; // x button, y index       
class KEY                    :public event_sys<_KEY>{
    virtual bool get_state(int key);
      bool filter(short int type_flag){
        switch(type_flag){
            case _keyup :{return true;};
            case _keydown :{return true;};
            case _keypress :{return true;};
        };
        return false;
    };
}; // index 
class joy_axis               :public event<int16,_joy_axis>; // x axis y index       
class joy_up                 :public event<int,_joy_up>;    
class joy_down               :public event<int,_joy_down>;      
class joy_press              :public event<int,_joy_press>;       
class JOY                    :public event_sys<_JOY>{
    virtual bool get_btn_state(int btn);
    virtual bool get_axis_state(int axis);
    virtual bool get_state(int key);
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
class controller_button_press:public event<int,_controller_button_press>;                    
class controller_button_down :public event<int,_controller_button_down>; 
class controller_button_up   :public event<int,_controller_button_up>; 
class controller_axis        :public event<float,_controller_axis>; 
class CONTROLLER             :public event_sys<_CONTROLLER>{
    virtual bool get_btn_state(int btn);
    virtual int get_axis_state(int axis );
    virtual bool get_dpad_up();
    virtual bool get_dpad_down();
    virtual bool get_dpad_left();
    virtual bool get_dpad_right();
    bool filter(short int type_flag){
        switch(type_flag){
            case _controller_button_press: {return true;};
            case _controller_button_down: {return true;};
            case _controller_button_up: {return true;};
            case _controller_axis: {return true;};
        };
        return false;
    };


};  // index        
class touch_move             :public event<vect<vec4>,_touch_move>; //xy last zw move
class touch_tap              :public event<vect<vec2>,_touch_tap>;// tap
class touch_zoom             :public event<mat<vec2>,_touch_gesture>; // xy move,z rotate,w zoom
class touch_gesture          :public event<vect<vec4>,_touch_zoom>{ // rotate
    void clear() final {this->d.clear();};
    private:
    bool exit=false;
    public: 
    void exit(){this->exit=true;};  
    touch_gesture record(){
        // Wait for tap
        this->exit=false;
        touch_tap tc_tp;
        while(!tc_tp^event_main){
            if(exit ){return NULL;}
        };
        while(touch[event_main])
    };
};
class TOUCH                  :public event_sys<_TOUCH>{
    suvec2 get_pos();
    vect<suvec2> get_multi_pos();
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
float mouse_move::get_theta()final{return (this->d[0])/(this->d[1]);}
class motion                     :public event<vec3,_motion>;
class accmotion                  :public event<vec4,_accmotion>;
class rotate2d               :public event<vec2,_rotate2d>;
class translate2d            :public event<vec2,_translate2d>;
class rotate3d               :public event<vec3,_rotate3d>;
class translate3d            :public event<vec3,_translate3d>;
class accrotate2d            :public event<vec2,_accrotate2d>;
class acctranslate2d         :public event<vec2,_acctranslate2d>;
class accrotate3d            :public event<vec3,_accrotate3d>;
class acctranslate3d         :public event<vec3,_acctranslate3d>;

class CONTROL_NAV : public event_sys<_CONTROL_NAV>;
class CONTROL_GAME : public event_sys<_CONTROL_GAME>;
class CONTROL_SIM : public event_sys<_CONTROL_SIM>;
class CONTROL_EDIT : public event_sys<_CONTROL_EDIT>;
class CONTROL_ALL : public event_sys<_CONTROL_ALL>;
typedef struct text_edit {
    ivec2 range; // ln,col
    std::string text;
}text_edit; 
class enter     :public event<bool,_enter> ;
class leave     :public event<bool,_leave> ;
class focus     :public event<bool,_focus> ;
class drag      :public event<bool,_drag> ;
class dragstart :public event<bool,_dragstart> ;
class dragend   :public event<bool,_dragend> ;
class keycombo  :public event<ivec4,_keycombo> ; //-1 is 
class dbclick   :public event<ivec2,_dbclick>{public: virtual int get_ms(int _ms=200){this->ms=_ms}; int16 ms_cur;} ;
class click     :public event<int,_click> ;
class combo     :public event<imat2x4,_combo> ; //r0 keys, r1 mouse
class textedit  :public event<text_edit,_textedit>;
class UI        :public event_sys<_UI>;

class  wake         : public wake<bool,_wake>;
class  sleep        : public event<bool,_sleep>;        
class  min          : public event<bool,_min>;      
class  max          : public event<bool,_max>;      
class  resize       : public event<ivec2,_resize>;
class  move         : public event<ivec2,_move>;         
class  fullscreen   : public event<bool,_fullscreen>;             
class  close        : public event<bool,_close>{    void handle(){}};                  
class  display_conn : public event<bool,_display_conn>{
    public:
    bool connected(){this->d==true;};
    bool disconnected(){this->d==false;};

    bool get_connected()final{this->d=_get_connected();};
    bool get_disconnected()final{this->d=_get_disconnected();};
};  
class display_mode   :public event<bool,_display_mode>{
    public:
    bool landscape(){this->d==true;};
    bool portrait(){this->d==false;};
    virtual bool _get_landscape();
    virtual bool _get_portrait();
    bool get_landscape()final{this->d=_get_landscape();};
    bool get_portrait()final{this->d=_get_portrait();};
};  
class DISPLAY : public event_sys<_DISPLAY>{
    vect<ivec3> disp; // xy=wh ; z=index;
    void get_data(size_t pos=0){return this->disp[pos];};
    void get_width(size_t pos=0){return this->disp[pos][0];};
    void get_height(size_t pos=0){return this->disp[pos][1];};
    void get_index(size_t pos=0){return this->disp[pos][2];};
    virtual display_conn _get_connected(int* index);
    bool push_connected(){
        bool res=_get_connected(int* index);
        evmain.push(display_conn(res,*(index));
    };
    virtual bool _get_mode();
    void get_mode(){
        bool res=_get
    }; // 
};

template <typename win>
class SYS : public event_sys<_SYS>{
    public:
    event_main evmain;
    public:
    using winty = win;
    vect<win> wins;
    int curr_win_index;
    using MIN = 0b0001;
    using MAX = 0b0010;
    using HIDE = 0b0100;
    using NORMAL = 0b1000;
void (*const close_app_win_func)();
    void sleep_callback()final{this->evmain->push(sleep::sleep()};;
    void wake_callback()final{this->evmain->push(wake::wake()};;
    void min_callback()final{this->evmain->push(min::min(true));}
    void max_callback()final{this->evmain->push(max::max(true));}
    void resize_callback()final{this->evmain->push(resize::resize(this->curr_win_index,ivec2(this->wins[this->cur_win_index].second[2],this->wins[this->cur_win_index].second[3]));};;
    void move_callback()final{this->evmain->push(move::move(this->curr_win_index,ivec2(this->wins[this->cur_win_index].second[0],this->wins[this->cur_win_index].second[1])));};;
    void fullscreen_callback(bool val=true)final{this->evmain->push(fullscreen::fullscreen(val));};
    void close_callback()final{this->evmain->push(close::close(true));this->close_app_win_func();}
    
    virtual void init(){

    };
    void set_close(void (*const close_app)()){this->close_app_win_func= close_app;};
    virtual void _init()
    void init(void (*const close_app)() ){set_close(close_app);this->_init();};// Set callbacks
    virtual win create_win(ivec2 size,ivec2 pos,win parent=NULL,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    win create_child_cur (ivec2 size,ivec2 pos,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) final{
            return this->create_win (ivec2 size,ivec2 pos,this->wins[this->curr_win_index].w,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    } ;
    virtual ivec2 get_pos(win w=this->wins[0]);
    virtual ivec2 get_size(win w=this->wins[0]);
    virtual ivec4 get_all(win w=this->wins[0]);
    virtual void resize_win(win w=this->wins[0],ivec2 addsize);
    virtual void move_win(win w=this->wins[0],ivec2 addpos);
    virtual bool is_min(win w=this->wins[0])
    virtual bool is_hidden(win w=this->wins[0])
    virtual bool is_normal(win w=this->wins[0])
    virtual bool is_max(win w=this->wins[0])
    virtual void set_win_opacity(float opacity);
    virtual void set_win_fullscreen();
    virtual void close();
    virtual void sleep(int mstime=2000);
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


