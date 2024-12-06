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

template <typename win,typename shared,typename procinstance>
class strata_env{
    struct cpu_info {
        std::string name;
        std::string arch;

    };
    public:
    using winty = win;
    using sharedty= shared; 
    vect<win> wins;
    int curr_index;
    using MIN = 0b0001;
    using MAX = 0b0010;
    using HIDE = 0b0100;
    using NORMAL = 0b1000;
    virtual void init(int flags); // System initialization
    virtual void initVk(win w, VkInstance inst, VKSurfaceKHR* surface, procinstance hInstance)
    virtual void initDx(){std::cerr<<"System has no dx implementation"};
    virtual win create_win(ivec2 size,ivec2 pos,HWND parent=NULL,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    virtual ivec2 get_pos(win w);
    virtual ivec2 get_size(win w);
    virtual ivec4 get_all(win w);
    virtual void resize_win(win w,ivec2 addsize);
    virtual void move_win(win w,ivec2 addpos);
    virtual bool is_min(win w)
    virtual bool is_hidden(win w)
    virtual bool is_normal(win w)
    virtual bool is_max(win w)
    virtual void set_win_opacity(float opacity);
    virtual void set_win_fullscreen();

    void cpu_info();


    virtual void load_shared(fs::path p);
    virtual void unload_shared(shared s);
    win create_child_cur (ivec2 size,ivec2 pos,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL){
            return this->create_win (ivec2 size,ivec2 pos,this->wins[curr_index],bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) ;
    } ;
    };
    
    

} ;

class strata_gr {
    
};

namespace events {
    
#define _click                    1            
#define _mousedown                2                  
#define _mouseup                  3 
#define _mousepress               4             
#define _mouse_move               5  
#define _mouse_wheel              6
#define _MOUSE                    _click|_mousedown |_mouseup |_mousepress|_mouse_move |_mouse_wheel                                     
#define _keyup                    8              
#define _keydown                  9                
#define _keypress                10 
#define _KEY                     _keyup|_keydown|_keypress                                      
#define _joy_axis                13
#define _joy_up                  14      
#define _joy_down                15        
#define _joy_press               16
#define _JOY                     _joy_axis|_joy_up|_joy_down|_joy_press                               
#define _controller_axis         22                    
#define _controller_button_up    23
#define _controller_button_down  24                              
#define _controller_button_press 25                                
#define _CONTROLLER               _controller_axis|_controller_button_up|_controller_button_down|_controller_button_press
#define _touch_move              30    
#define _touch_tap               31   
#define _touch_gesture           32
#define _touch_zoom              33                  
#define _TOUCH                    _touch_move|_touch_tap|_touch_gesture|_touch_zoom
 
#define IDEV_ALL

#define MOVE                0x0100000000000000              
#define ACC                 0x1000000000000000
#define _up                 0x0000000000000001                 
#define _down               0x0000000000000010                   
#define _left               0x0000000000000100                  
#define _right              0x0000000000001000                   
#define _forward            0x0000000000010000                      
#define _back               0x0000000000100000                   
#define _accup              0x1000000000000001                
#define _accdown            0x1000000000000010                  
#define _accleft            0x1000000000000100                      
#define _accright           0x1000000000001000                            
#define _accforward         0x1000000000010000                
#define _accback            0x1000000000100000                  
#define _yawleft            0x0100000001000000                  
#define _yawright           0x0100000010000000                   
#define _pitchdown          0x0100000100000000                  
#define _pitchup            0x0100001000000000                
#define _accyawleft         0x1000000001000000                  
#define _accyawright        0x1000000010000000                  
#define _accpitchdown       0x1000000100000000                
#define _accpitchup         0x1000001000000000                 
#define _rotate2d           0x0100010000000000                
#define _translate2d        0x0100100000000000                
#define _rotate3d           0x0101000000000000                
#define _translate3d        0x0110000000000000                
#define _accrotate2d        0x1000010000000000                
#define _acctranslate2d     0x1000100000000000                
#define _accrotate3d        0x1001000000000000                
#define _acctranslate3d     0x1010000000000000                 

#define CONTROL_NAV _up|_down|_left|_right|_forward|_back
#define CONTROL_GAME _up|_down|_left|_right|_forward|_back|_accup|_accdown|_accleft|_accright|_accforward|_accback
#define CONTROL_SIM _yawleft|_yawright|_pitchdown|_pitchup|_accyawleft|_accyawright|_accpitchdown|_accpitchup
#define CONTROL_EDIT _rotate2d|_translate2d|_rotate3d|_translate3d|_accrotate2d|_acctranslate2d|_accrotate3d|_acctranslate3d
#define CONTROLL_ALL CONTROL_NAV|CONTROL_GAME| CONTROL_SIM | CONTROL_EDIT 

#define _enter      61
#define _leave      62
#define _focus      63
#define _drag       64  
#define _dragstart  65       
#define _dragend    66     
#define _keycombo   67      
#define _dbclick    68
#define _click      69      
#define _combo      70
#define _text_in    71
#define _text_edit  72
#define _clipboard  73

#define UI_ALL  _enter|_leave|_focus|_drag|_dragstart|_dragend|_keycombo|_dbclick|_click|_combo|_text_in|_text_edit|_clipboard

#define POWER_DOWN 128
#define POWER_UP   129
#define SLEEP      130
#define MINIMIZE   131
#define MAXIMIZE   132
#define FULLSCREEN 133
#define CLOSE      134

#define SYS_EV POWER_DOWN|POWER_UP|SLEEP|MIN|MAX|FULLSCREEN|CLOSE

#define CONTROLL_ALL
#define IDEV_ALL
#define MOUSE
#define JOY
#define CON
#define TOUCH

#define DEFAULT_EVENT_ALL

static const std::map<int , std::string> ev_map = {
{    _click,"click"},{_mousedown,"mousedown"},{_mouseup,"mouseup"},{_mouseup,"mousepress"}{_mouse_move,"mouse_move"},{_mouse_wheel,"mouse_wheel"},{_MOUSE,"MOUSE"},{_keyup,"keyup"},{_keydown,"keydown"},{_keypress,"keypress"},{_KEY,"KEY"},{_joy_axis,"joy_axis"},{_joy_up,"joy_up"},{_joy_down,"joy_down"},{_joy_press,"joy_press"},{_JOY,"JOY"},{_controller_axis,"controller_axis"},{_controller_button_up,"controller_button_up"},{_controller_button_down,"controller_button_down"},{_controller_button_press,"controller_button_press"},{_CONTROLLER,"CONTROLLER"},{_touch_move,"touch_move"},{_touch_tap,"touch_tap"},{_touch_gesture,"touch_gesture"},{_touch_zoom,"touch_zoom"},{_TOUCH,"TOUCH"},{_up,"up"},{_down,"down"},{_left,"left"},{_right,"right"},{_forward,"forward"},{_back,"back"},{_accup,"accup"},{_accdown,"accdown"},{_accleft,"accleft"},{_accright,"accright"},{_accforward,"accforward"},{_accback,"accback"},{_yawleft,"yawleft"},{_yawright,"yawright"},{_pitchdown,"pitchdown"},{_pitchup,"pitchup"},{_accyawleft,"accyawleft"},{_accyawright,"accyawright"},{_accpitchdown,"accpitchdown"},{_accpitchup,"accpitchup"},{_rotate2d,"rotate2d"},{_translate2d,"translate2d"},{_rotate3d,"rotate3d"},{_translate3d,"translate3d"},{_accrotate2d,"accrotate2d"},{_acctranslate2d,"acctranslate2d"},{_accrotate3d,"accrotate3d"},{_acctranslate3d,"acctranslate3d"},{_enter,"enter"},{_leave,"leave"},{_focus,"focus"},{_drag,"drag"},{_dragstart,"dragstart"},{_dragend,"dragend"},{_keycombo,"keycombo"},{_dbclick,"dbclick"},{_click,"click"},{_combo,"combo"},{_text_in,"text_in"},{_text_edit,"text_edit"},{_clipboard,"clipboard"}
};
    class event_main;
    event& event_main::poll();
    template <typename T , uint type =0>
    class event {
        public:
        const uint ty = T;
        T d;
        uint32 ms;
        uint index;
        using ty = type;
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
        virtual void init();
        virtual short int resolve();
        virtual bool filter();
    };
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
class MOUSE                  :public event{
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
class KEY                    :public event<vect<short unsigned int>,_KEY>{
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
class JOY                    :public event<void,_JOY>{
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
class CONTROLLER             :public event<void,_CONTROLLER>{
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
class TOUCH                  :public event<void,_TOUCH>{
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
class up                     :public event<float,_up>;
class down                   :public event<float,_down>;
class left                   :public event<float,_left>;
class right                  :public event<float,_right>;
class forward                :public event<float,_forward>;
class back                   :public event<float,_back>;
class accup                  :public event<float,_accup>;
class accdown                :public event<float,_accdown>;
class accleft                :public event<float,_accleft>;
class accright               :public event<float,_accright>;
class accforward             :public event<float,_accforward>;
class accback                :public event<float,_accback>;
class yawleft                :public event<float,_yawleft>;
class yawright               :public event<float,_yawright>;
class pitchdown              :public event<float,_pitchdown>;
class pitchup                :public event<float,_pitchup>;
class accyawleft             :public event<float,_accyawleft>;
class accyawright            :public event<float,_accyawright>;
class accpitchdown           :public event<float,_accpitchdown>;
class accpitchup             :public event<float,_accpitchup>;
class rotate2d               :public event<vec2,_rotate2d>;
class translate2d            :public event<vec2,_translate2d>;
class rotate3d               :public event<vec3,_rotate3d>;
class translate3d            :public event<vec3,_translate3d>;
class accrotate2d            :public event<vec2,_accrotate2d>;
class acctranslate2d         :public event<vec2,_acctranslate2d>;
class accrotate3d            :public event<vec3,_accrotate3d>;
class acctranslate3d         :public event<vec3,_acctranslate3d>;

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

class display   :public event<sivec2,_display>;
class audio     :public event<sivec2,_audio>;

class events  : public vect<event*>{
    vect<event*> event_ptrs;
    short int index_plugins;


};

template <size_t max=8192>
class event_main {
    public:
    int flags;
    vect<event*> events;
    vect<event*> during;
    void resolve_flags(){

    };
    ev_q<event*> events;
    int evs;
    
    long int ms;
    long int sec;
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
    bool operator^(event* e){return this->peep(0).ty ^ e.ty ;}
    operator bool () const {return this->poll()};
    this& operator=(vect<event*> evs){
        events_main s;
        for(int i=0;i<evs.size();i++){
            s.evs.push(evs[i]);
        };
        this&=s;
    };
    event resolve(int flag);
    events_main(int flags){
        
    };
    
    };
};
#define MAIN_DEF(ev_m) ev_m main; 
#define NS_USE(ns) using namespace ns;


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
using env = win_env;
using evns = win_events;
#elifdef STA_IMPL_ANDROID
#include "impl_android.hpp"
using namespace android_events;
using env = android_env;
using evns = android_events;
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


