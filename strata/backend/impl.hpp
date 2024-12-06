#pragma once
#include <strata/petri/vects.hpp>
#include <queue>
#include <filesystem>
#include <functional>
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
    
#define _click                    0            
#define _mousedown                1                  
#define _mouseup                  2 
#define _mousepress               3             
#define _mouse_move               4  
#define _mouse_wheel              5
#define _MOUSE                    6                 
#define _keyup                    7              
#define _keydown                  8                
#define _keypress                 9
#define _KEY                     10                 
#define _joy_axis                11
#define _joy_up                  12      
#define _joy_down                13        
#define _joy_press               14
#define _JOY                     15                               
#define _controller_axis         16                    
#define _controller_button_up    17
#define _controller_button_down  18                               
#define _controller_button_press 19                                
#define _CONTROLLER              20
#define _touch_move              21      
#define _touch_tap               22     
#define _touch_gesture           23
#define _touch_zoom              25                    
#define _TOUCH                   26 
 
#define IDEV_ALL

#define ACC               
#define MOVE              
#define _up              30 
#define _down            31   
#define _left            32  
#define _right           33   
#define _forward         34      
#define _back            35   
#define _accup           36
#define _accdown         37  
#define _accleft         38      
#define _accright        39            
#define _accforward      40
#define _accback         41  
#define _yawleft         42  
#define _yawright        43   
#define _pitchdown       44  
#define _pitchup         45
#define _accyawleft      46  
#define _accyawright     47  
#define _accpitchdown    48
#define _accpitchup      49 
#define _rotate2d        50
#define _translate2d     51
#define _rotate3d        52
#define _translate3d     53
#define _accrotate2d     54
#define _acctranslate2d  55
#define _accrotate3d     56
#define _acctranslate3d  57 

#define CONTROLL_ALL

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

#define UI_ALL
#define DEFAULT_EVENT_ALL

static const std::map<int , std::string> ev_map = {
{    _click,"click"},{_mousedown,"mousedown"},{_mouseup,"mouseup"},{_mouseup,"mousepress"}{_mouse_move,"mouse_move"},{_mouse_wheel,"mouse_wheel"},{_MOUSE,"MOUSE"},{_keyup,"keyup"},{_keydown,"keydown"},{_keypress,"keypress"},{_KEY,"KEY"},{_joy_axis,"joy_axis"},{_joy_up,"joy_up"},{_joy_down,"joy_down"},{_joy_press,"joy_press"},{_JOY,"JOY"},{_controller_axis,"controller_axis"},{_controller_button_up,"controller_button_up"},{_controller_button_down,"controller_button_down"},{_controller_button_press,"controller_button_press"},{_CONTROLLER,"CONTROLLER"},{_touch_move,"touch_move"},{_touch_tap,"touch_tap"},{_touch_gesture,"touch_gesture"},{_touch_zoom,"touch_zoom"},{_TOUCH,"TOUCH"},{_up,"up"},{_down,"down"},{_left,"left"},{_right,"right"},{_forward,"forward"},{_back,"back"},{_accup,"accup"},{_accdown,"accdown"},{_accleft,"accleft"},{_accright,"accright"},{_accforward,"accforward"},{_accback,"accback"},{_yawleft,"yawleft"},{_yawright,"yawright"},{_pitchdown,"pitchdown"},{_pitchup,"pitchup"},{_accyawleft,"accyawleft"},{_accyawright,"accyawright"},{_accpitchdown,"accpitchdown"},{_accpitchup,"accpitchup"},{_rotate2d,"rotate2d"},{_translate2d,"translate2d"},{_rotate3d,"rotate3d"},{_translate3d,"translate3d"},{_accrotate2d,"accrotate2d"},{_acctranslate2d,"acctranslate2d"},{_accrotate3d,"accrotate3d"},{_acctranslate3d,"acctranslate3d"},{_enter,"enter"},{_leave,"leave"},{_focus,"focus"},{_drag,"drag"},{_dragstart,"dragstart"},{_dragend,"dragend"},{_keycombo,"keycombo"},{_dbclick,"dbclick"},{_click,"click"},{_combo,"combo"},{_text_in,"text_in"},{_text_edit,"text_edit"},{_clipboard,"clipboard"}
};
    
    template <typename T , uint32 type =0>
    class event {
        public:
        using ty = T;
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
class MOUSE                  :public event<mat2x4,_MOUSE>; // 0:xy pos, zw last_pos,1:x theta,y abs,z press,w wheel 
class keyup                  :public event<int,_keyup>; // x button, y index    
class keydown                :public event<int,_keydown>; // x button, y index      
class keypress               :public event<int,_keypress>; // x button, y index       
class KEY                    :public event<void,_KEY>; // index 
class joy_axis               :public event<int16,_joy_axis>; // x axis y index       
class joy_up                 :public event<int,_joy_up>;    
class joy_down               :public event<int,_joy_down>;      
class joy_press              :public event<int,_joy_press>;       
class controller_button_press:public event<int,_controller_button_press>;                    
class controller_button_down :public event<int,_controller_button_down>; 
class controller_button_up   :public event<int,_controller_button_up>; 
class controller_axis        :public event<float,_controller_axis>; 
class CONTROLLER             :public event<void,_CONTROLLER>;  // index        
class touch_move             :public event<vect<vec4>,_touch_move>; //xy last zw move
class touch_tap              :public event<vect<vec2>,_touch_tap>;// tap
class touch_zoom             :public event<mat<vec2>,_touch_gesture>; // xy move,z rotate,w zoom
class touch_gesture          :public event<vec4,_touch_zoom>; // rotate
class TOUCH                  :public event<void,_TOUCH>{
    virtual 
    virtual TOUCH::record(){}
};
float mouse_move::get_theta()final{return (this->d[0])/(this->d[1]);}
class up                     :public event<float,_up>;
class down                   :public event<float,_down>;
class accup                  :public event<float,_accup>;
class accdown                :public event<float,_accdown>;
class left                   :public event<float,_left>;
class right                  :public event<float,_right>;
class forward                :public event<float,_forward>;
class back                   :public event<float,_back>;
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
class dbclick   :public event<ivec2,_dbclick> ;
class click     :public event<int,_click> ;
class combo     :public event<imat2x4,_combo> ; //r0 keys, r1 mouse
class textedit  :public event<text_edit,_textedit>;

class display   :public event<sivec2,_display>;
class audio     :public event<sivec2,_audio>;

class events  : public vect<event*>{
    vect<event*> event_ptrs;
    short int index_plugins;


};
class events_main {
    public:
    std::queue<event*> events;
    vect<event*> evs;
    public:
    void push_event(event* ev) final {this->events.push(ev)};
    event* poll_event(event* ev) final {event* res = this->events.first();this->events.pop();return res;};
    void clear_events() final {while(!(this->events.empty())){this->events.pop();};};
    void resolve(event* ev){

            if(*(ev)<=>clicktypeid)                   {return _click}           
            if(*(ev)<=>mousedown)              {return _mousedown}               
            if(*(ev)<=>mouseup)                {return _mouseup}             
            if(*(ev)<=>mouse_move)             {return _mouse_move}                
            if(*(ev)<=>mouse_wheel)            {return _mouse_wheel}                 
            if(*(ev)<=>MOUSE)                  {return _MOUSE}           
            if(*(ev)<=>keyup)                  {return _keyup}           
            if(*(ev)<=>keydown)                {return _keydown}             
            if(*(ev)<=>keypress)               {return _keypress}              
            if(*(ev)<=>KEY)                    {return _KEY}         
            if(*(ev)<=>joy_axis)               {return _joy_axis}              
            if(*(ev)<=>joy_up)                 {return _joy_up}            
            if(*(ev)<=>joy_down)               {return _joy_down}              
            if(*(ev)<=>joy_press)              {return _joy_press}               
            if(*(ev)<=>controller_button_press){return _controller_button_press}                             
            if(*(ev)<=>controller_button_down) {return _controller_button_down}                            
            if(*(ev)<=>controller_button_up)   {return _controller_button_up}                          
            if(*(ev)<=>controller_axis)        {return _controller_axis}                     
            if(*(ev)<=>CONTROLLER)             {return _CONTROLLER}                
        };
    };
    virtual event* peep_event(int s);
    this& operator=(vect<event*> evs){
        events_main s;
        for(int i=0;i<evs.size();i++){
            s.evs.push(evs[i]);
        };
        this&=s;
    }
    event resolve(int flag)
    events_main(vect<event*> evs){
        this=evs;
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


