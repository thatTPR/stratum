#pragma once
#include <strata/petri/vects.hpp>
#include <memory>
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
#define _controller_up    23
#define _controller_down  24                              
#define _controller_press 25
#define _controller_dpad         26                                
#define _CONTROLLER              ( _controller_axis|_controller_up|_controller_down|_controller_press)
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
#define _hide         360
#define _move         361
#define _resize       362
#define _fullscreen   363
#define _close        364
#define _display_conn 365
#define _display_mode 366
#define _SYS ( _sleep|_min|_max|_move|_resize|_fullscreen|_close)


#define DEFAULT_EVENT_ALL

static const std::map<int , std::string> ev_map = {
{    _click,"click"},{_mousedown,"mousedown"},{_mouseup,"mouseup"},{_mouseup,"mousepress"}{_mouse_move,"mouse_move"},{_mouse_wheel,"mouse_wheel"},{_MOUSE,"MOUSE"},{_keyup,"keyup"},{_keydown,"keydown"},{_keypress,"keypress"},{_KEY,"KEY"},{_joy_axis,"joy_axis"},{_joy_up,"joy_up"},{_joy_down,"joy_down"},{_joy_press,"joy_press"},{_JOY,"JOY"},{_controller_axis,"controller_axis"},{_controller_up,"controller_up"},{_controller_down,"controller_down"},{_controller_press,"controller_press"},{_CONTROLLER,"CONTROLLER"},{_touch_move,"touch_move"},{_touch_tap,"touch_tap"},{_touch_gesture,"touch_gesture"},{_touch_zoom,"touch_zoom"},{_TOUCH,"TOUCH"},{_up,"up"},{_down,"down"},{_left,"left"},{_right,"right"},{_forward,"forward"},{_back,"back"},{_accup,"accup"},{_accdown,"accdown"},{_accleft,"accleft"},{_accright,"accright"},{_accforward,"accforward"},{_accback,"accback"},{_yawleft,"yawleft"},{_yawright,"yawright"},{_pitchdown,"pitchdown"},{_pitchup,"pitchup"},{_accyawleft,"accyawleft"},{_accyawright,"accyawright"},{_accpitchdown,"accpitchdown"},{_accpitchup,"accpitchup"},{_rotate2d,"rotate2d"},{_translate2d,"translate2d"},{_rotate3d,"rotate3d"},{_translate3d,"translate3d"},{_accrotate2d,"accrotate2d"},{_acctranslate2d,"acctranslate2d"},{_accrotate3d,"accrotate3d"},{_acctranslate3d,"acctranslate3d"},{_enter,"enter"},{_leave,"leave"},{_focus,"focus"},{_drag,"drag"},{_dragstart,"dragstart"},{_dragend,"dragend"},{_keycombo,"keycombo"},{_dbclick,"dbclick"},{_click,"click"},{_combo,"combo"},{_text_in,"text_in"},{_text_edit,"text_edit"},{_clipboard,"clipboard"}
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
    template <typename d>
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
        using flag=ty
        void _init(); // Initialize the subsystem
        void init() {this->_init()}; 
        virtual event* resolve();
        virtual event* handle();
        virtual void listen();// Checks if there was an event;
        virtual event filter(event* ev);
    };
template <bool events=true >
class event_main {
    public:
    using ev_sys=events;
    vect<int> flags;
    vect<event*> events;
    vect<event*> during;

    vect<shared_ptr<event_sys>> evsys; // Priority
    void resolve_flags(){

    };
    
    long unsigned int ms;
    long unsigned int sec;
    size_t cur_pos;
    void tick ()final{this->ms++;}
    void tick (short int timems)final{this->ms+=timems;};
    void sec ()final{this->sec++;}
    void sec (short int times)final{this->sec+=times;};
    long int sec_ms(){return this->ms/1000;};
    virtual long unsigned int _get_time_ms();
    int get_time_ms(){this->ms= ; return this->ms;};
    void push(event* ev) final {if constexpr(ev_sys) {ev->ms = this->get_time_ms(); this->events.push(ev);};};
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
using click = event<int,_click>;    
using mousedown = event<int,_mousedown>;        
using mouseup = event<int,_mouseup>;      
using mouse_press = event<int,_mousepress>; // 0 left 1 right 2 wheel, 3 forward ,4 back
using mouse_move = event<vec2,_mouse_move>;//xy
using mouse_wheel = event<float,_mouse_wheel>; //x       
   
class MOUSE                  :public event_sys<_MOUSE>{
    event_main* evmain;
    virtual vec2 get_pos();
    virtual bool get_state(short int bt);
     void move_cb(vec2 mv,int index=0) final {this->ev_main.push(mouse_move(mv,index));};
     void press_cb(int press,int index=0) final {this->ev_main.push(mouse_press(press,index));};
     void down_cb(int down,int index=0) final {this->ev_main.push(mouse_down(down,index));};
     void up_cb(int up,int index=0) final {this->ev_main.push(mouse_up(up,index));};
     void wheel_cb(float wheel,int index=0) final {this->ev_main.push(mouse_wheel(wheel,index));};
    virtual void init();
    void init()override{this->_init();};
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
using keyup = event<int,_keyup>; // x button, y index    
using keydown = event<int,_keydown>; // x button, y index      
using keypress = event<int,_keypress>; // x button, y index       
class KEY                    :public event_sys<_KEY>{
    
    void up_cb(int key,int index) final {this->evmain.push(keyup(key,index));};
    void down_cb(int key,int index) final {this->evmain.push(keydown(key,index));};    
    void press_cb(int key,int index) final {this->evmain.push(keypress(key,index));};    
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
using joy_axis = event<int16,_joy_axis>; // x axis y index       
using joy_up = event<int,_joy_up>;    
using joy_down = event<int,_joy_down>;      
using joy_press = event<int,_joy_press>;       
class JOY                    :public event_sys<_JOY>{
    void up_cb(int btn,int index) final {this->evmain.push(joy_up(btn,index));};
    void down_cb(int btn,int index) final {this->evmain.push(joy_down(btn,index));};    
    void press_cb(int btn,int index) final {this->evmain.push(joy_press(btn,index));};    
    void axis_cb(int16 axis,int index) final {this->evmain.push(joy_axis(axis,index));};    

    virtual bool get_btn_state(int btn);
    virtual bool get_axis_state(int axis);
    virtual bool get_state(int key);
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
class controller_press:public event<int,_controller_press>;                    
using controller_down = event<int,_controller_down>; 
using controller_up = event<int,_controller_up>; 
using controller_dpad = event<int,_controller_dpad>;
using controller_axis = event<float,_controller_axis>; 
class CONTROLLER             :public event_sys<_CONTROLLER>{

    void up_cb(int btn,int index) final {this->evmain.push(controller_up(btn,index));};
    void down_cb(int btn,int index) final {this->evmain.push(controller_down(btn,index));};    
    void press_cb(int btn,int index) final {this->evmain.push(controller_press(btn,index));};    
    void axis_cb(int16 axis,int index) final {this->evmain.push(controller_axis(axis,index));};    
    void dpad_cb(int16 axis,int index) final {this->evmain.push(controller_dpad(axis,index));};    
    virtual bool get_btn(int btn,  int index=0);
    virtual int get_axis(int axis,  int index=0 );
    virtual int get_dpad(int index =0);
    virtual void _init();
    void init(){event_sys::init();};
    bool filter(short int type_flag){
        switch(type_flag){
            case _controller_press: {return true;};
            case _controller_down: {return true;};
            case _controller_up: {return true;};
            case _controller_axis: {return true;};
        };
        return false;
    };


};  // index        
using touch_move = event<vect<vec4>,_touch_move>; //xy last zw move
using class touch_tap              :public =  event<vect<vec2>,_touch_tap>;// tap
using touch_zoom =  event<mat<vec2>,_touch_gesture>; // xy move,z rotate,w zoom
using touch_gesture =  event<vect<vec4>,_touch_zoom>; // rotate
class TOUCH                  :public event_sys<_TOUCH>{
    suvec2 get_pos();
    vect<suvec2> get_multi_pos();
    void move_cb(vect<vec4> mv);
    void tap_cb(vect<vec4> mv);
    void zoom_cb(vect<vec4> mv);
    void gesture_cb(vect<vec4> mv);

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
float mouse_move::get_theta()final{return (this->d[0])/(this->d[1]);}
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

class CONTROL_NAV : public event_sys<_CONTROL_NAV>;
class CONTROL_GAME : public event_sys<_CONTROL_GAME>;
class CONTROL_SIM : public event_sys<_CONTROL_SIM>;
class CONTROL_EDIT : public event_sys<_CONTROL_EDIT>;
class CONTROL : public event_sys<_CONTROL_ALL>{

};
typedef struct text_edit {
    ivec2 range; // ln,col
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
using click = event<int,_click> ;
using combo = event<imat2x4,_combo> ; //r0 keys, r1 mouse
using textedit = event<text_edit,_textedit>;
class UI        :public event_sys<_UI>{
    public: 
    
    virtual void get_db_click_ms(int per);
    int get_ms(int _ms=200) final{this->ms=_ms}; int16 ms_cur;}
};

class  wake         : public wake<bool,_wake>;
class  sleep        : public event<bool,_sleep>;        
class  min          : public event<bool,_min>;      
class  max          : public event<bool,_max>;      
class  hide          : public event<bool,_max>;
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
using display_mode = event<bool,_display_mode>{
    public:
    bool landscape(){this->d==true;};
    bool portrait(){this->d==false;};
    virtual bool _get_landscape();
    virtual bool _get_portrait();
    bool get_landscape()final{this->d=_get_landscape();};
    bool get_portrait()final{this->d=_get_portrait();};
};  
class DISPLAY : public event_sys<_DISPLAY>{
    vect<ivec3> disp; // xy=wh ; z=hz;
    vect<ivec3> mon;
    size_t nummon;
    vec2 get_data(size_t pos=0){return this->disp[pos];}; // hw(pixels) ,hw(cm)
    int get_width(size_t pos=0){return this->disp[pos][0];};
    int get_height(size_t pos=0){return this->disp[pos][1];};
    int get_index(size_t pos=0){return this->disp[pos][2];};
    ivec3 get_monitor_data(size_t pos=0); // w,h,hz
    ivec3 get_display_data(size_t pos=0); // w,h,hz
    size_t get_num_monitors();
    size_t get_monitor_display(size_t pos=0);
    virtual vec2 get_data(size_t pos=0){this->_get_data this->disp[pos];}; // hw(pixels) ,hw(cm)
    virtual int get_width(size_t pos=0){this->_get_width this->disp[pos][0];};
    virtual int get_height(size_t pos=0){this->_get_height this->disp[pos][1];};
    virtual int get_index(size_t pos=0){this->_get_index this->disp[pos][2];};
 

    bool conn_callback(bool val = true){this->evmain->push(display_conn::display_conn(val);)};
    bool mode_callback(bool val = true){this->evmain->push(display_mode::display_mode(val);)};
    virtual void handle();
    virtual void _init();
    void init(){this->_init();};
    virtual void close();
    virtual bool _get_mode();
    void get_mode(){
        bool res=_get
    }; // 
};

template <typename win,typename command_sys>
class SYS : public event_sys<_SYS>{
    public:
    command_sys* commsys;
    event_main evmain;
    vect<event_sys*> eventsys;
    public:
    using winty = win;
    vect<win> wins;
    vect<ivec4> wind;
    int curr_win_index=0;

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
        for(int i =0; i<this->eventsys.size();i++){this->eventsys.handle();};
    };
    void set_close(void (*const close_app)() = this->def_close){this->close_app_win_func= close_app;};
    virtual void _init();// Set callbacks
    void init(void (*const close_app)() ){set_close(close_app);this->_init();for(int i=0;i<this->eventsys.size();i++){this->eventsys[i].init();};
    void set_priority(int place,int flag){
        for(int i = 0;i<this->eventsys.size();i++){
            if(this->eventsys[i].flag==flag){
                this->eventsys.swap(i,place);
                int s = ((place-i)>0)?1:-1;
                for(int j = place ; j != i ; j+=s){
                    this->eventsys.swap(place,place+s);
                };
            };
        };
    };
    void set_priority(vect<ivec2> flag_place){
        for(int i=0;i<flag_place.size();i++){
            for(int j = 0 ; j <this->eventsys.size();j++){
                if(this->eventsys[j].flag==flag_place[i][0]){
                    this->eventsys.swap(g,flag_place[1]);
                    break;
                }
            };
        }
    };
    void push(event_sys* first){this->eventsys.push(first);};
    void push(event_sys* first,event_sys* second){this->push(first);this->push(second);};
    void push(event_sys* first,event_sys* s...){
        this->push(first);
        this->push(s...);
    };
    SYS(eventsys* first, eventsys* args...){
        this->eventsys.push(first) ; this->push(args...)
        
    };
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


