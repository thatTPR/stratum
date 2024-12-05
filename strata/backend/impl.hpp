#pragma once
#include "../petri/vects.hpp"
#ifdef STA_IMPL_LINUX
#include "impl_linux.hpp"
#else
#ifdef STA_IMPL_WINDOWS
#include "impl_win.hpp"
#else
#ifdef STA_IMPL_ANDROID
#include "impl_android.hpp"
#endif
#ifdef STA_IMPL_VK
#include "impl_vk.hpp"
#else
#ifdef STA_IML_DX
#include "impl_dx.hpp"
#else
#ifdef STA_IMPL_GL
#include "impl_gl.hpp"
#endif

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


template<typename _shader>
class strata_impl {
virtual create_window(ivec2 size,ivec2 pos,bool custom_tabbar=true, bool resizable=true,float opacity=1,bool always_on_top=true);
virtual resize_window(ivec2 addsize);
virtual set_win_opacity(float opacity);
void set_win_opacity();
virtual void win_fullscreen(); 
virtual _shader create_shader_stage(std::vector<const uint32_t*> shader );
virtual void shader_bind(_shader shader,auto*... uniforms);
virtual void load_SSBO(_shader shader,auto* buffer);
virtual void load_UBO(_shader shader,auto* buffer);
virtual void draw();
virtual void blend();
virtual void mesh_load();
virtual void texture_load();
virtual void obj_generate();
}

namespace events {
    
    
    template <typename d >
    class event {
        public:
        using ty = d;
        d data;
        uint32 ms;
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
        void add_event(event ev){this->evs.push(ev)};
        void add_event_front(event* ev){this->evs.insert(0,ev);}
        d get(){return this->data};
        event(d data,uint32 ms){
            this->data = data; this->ms = ms;
        };

    };
    template <typname d>
    class ev_filtere {
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

   

    struct joy_axis_ [
        float pos;
        uint16 axis_no;
        uint16 dev_no;
    ]
class click                  :public event<int>;    
class mousedown              :public event<int>;        
class mouseup                :public event<int>;      
class mouse_move             :public event<vec2>;
class mouse_wheel            :public event<float>;         
class MOUSE                  :public event<int>;    // index
class keyup                  :public event<ivec2>; // x button, y index    
class keydown                :public event<ivec2>; // x button, y index      
class keypress               :public event<ivec2>; // x button, y index       
class KEY                    :public event<int>; // index 
class joy_axis               :public event<joy_axis_>; // x axis y index       
class joy_up                 :public event<ivec2>; // x button , y conindex   
class joy_down               :public event<ivec2>; // x button , y conindex     
class joy_press              :public event<ivec2>; // x button , y conindex      
class controller_button_press:public event<ivec2>; // x button , y conindex                   
class controller_button_down :public event<ivec2>; // x button , y conindex
class controller_button_up   :public event<ivec2>; // x button , y conindex
class controller_axis        :public event<ivec2>; // x axis z index      
class CONTROLLER             :public event<int>;  // index        

class up             : public event<event<float>>;
class down           : public event<event<float>>;
class accup          : public event<event<float>>;
class accdown        : public event<event<float>>;
class left           : public event<event<float>>;
class right          : public event<event<float>>;
class forward        : public event<event<float>>;
class back           : public event<event<float>>;
class accforward     : public event<event<float>>;
class accback        : public event<event<float>>;
class yawleft        : public event<event<float>>;
class yawright       : public event<event<float>>;
class pitchdown      : public event<event<float>>;
class pitchup        : public event<event<float>>;
class accyawleft     : public event<event<float>>;
class accyawright    : public event<event<float>>;
class accpitchdown   : public event<event<float>>;
class accpitchup     : public event<event<float>>;
class rotate2d       : public event<event<vec2>>;
class translate2d    : public event<event<vec2>>;
class rotate3d       : public event<event<vec3>>;
class translate3d    : public event<event<vec3>>;
class accrotate2d    : public event<event<vec2>>;
class acctranslate2d : public event<event<vec2>>;
class accrotate3d    : public event<event<vec3>>;
class acctranslate3d : public event<event<vec3>>;

typedef struct text_edit {
    ivec2 range; // ln,col
    std::string text;
}text_edit; 
class enter     :public event<bool> ;
class leave     :public event<bool> ;
class focus     :public event<bool> ;
class drag      :public event<bool> ;
class dragstart :public event<bool> ;
class dragend   :public event<bool> ;
class keycombo  :public event<ivec4> ; //-1 is 
class dbclick   :public event<ivec2> ;
class click     :public event<int> ;
class combo     :public event<imat2x4> ; //r0 keys, r1 mouse
class textedit  :public event<text_edit>;
#define _click                   0b00000000010001             
#define _mousedown               0b00000000010010                  
#define _mouseup                 0b00000000010100                
#define _mouse_move              0b00000000011000  
#define _mouse_wheel             0b00000000011001
#define _MOUSE                   0b00000000010000                 
#define _keyup                   0b00000100100000              
#define _keydown                 0b00000101000000                
#define _keypress                0b00000110000000
#define _KEY                     0b00000100000000                 
#define _joy_axis                0b01000100000000
#define _joy_up                  0b01001000000000      
#define _joy_down                0b01010000000000        
#define _joy_press               0b01100000000000                               
#define _controller_button_press 0b10001000000000                                
#define _controller_button_down  0b10010000000000                               
#define _controller_button_up    0b10100000000000
#define _controller_axis         0b11000000000000                    
#define _CONTROLLER              0b10000000000000
uint32 CONTROL_EXT(uint32 s){
                       return s*0b100000000000000
}
#define IDEV_ALL

#define ACC               0b1000000000000000
#define MOVE              0b0100000000000000
#define _up               0b0100000000000001 
#define _down             0b0100000000000010   
#define _left             0b0100000000000100  
#define _right            0b0100000000001000   
#define _forward          0b0100000000010000      
#define _back             0b0100000000100000   
#define _accup            0b1000000000000001
#define _accdown          0b1000000000000010  
#define _accleft          0b1000000000000100      
#define _accright         0b1000000000001000            
#define _accforward       0b1000000000010000
#define _accback          0b1000000000100000  
#define _yawleft          0b0100000001000000  
#define _yawright         0b0100000010000000   
#define _pitchdown        0b0100000100000000  
#define _pitchup          0b0100001000000000
#define _accyawleft       0b1000000001000000  
#define _accyawright      0b1000000010000000  
#define _accpitchdown     0b1000000100000000
#define _accpitchup       0b1000001000000000 
#define _rotate2d         0b0100010000000000
#define _translate2d      0b0100100000000000
#define _rotate3d         0b0101000000000000
#define _translate3d      0b0110000000000000
#define _accrotate2d      0b1000010000000000
#define _acctranslate2d   0b1000100000000000
#define _accrotate3d      0b1001000000000000
#define _acctranslate3d   0b1010000000000000

#define MOVE_ALL          0b0111111111111111
#define ACC_ALL           0b1011111111111111


uint32 CONTROL_EXT(uint32 s) 
{return               s*(0b10000000000000000);} 
#define CONTROLL_ALL

#define _enter      0b00000000000001
#define _leave      0b00000000000010
#define _focus      0b00000000000100
#define _drag       0b00000000010000  
#define _dragstart  0b00000000110000       
#define _dragend    0b00000001010000     
#define _keycombo   0b00000010000000      
#define _dbclick    0b00000100000000
#define _click      0b00001000000000
#define _combo      0b00010000000000  
#define _text_in    0b00100000000000
#define _text_edit  0b01000000000000
#define _clipboard  0b10000000000000
  int32 UI_EXT(int32 s){
          return s*0b100000000000000} 
#define UI_ALL
#define DEFAULT_EVENT_ALL

class events  : public vect<event*>{
    vect<event*> event_ptrs;
    short int index_plugins;


};
class events_main {
    public:
    events evs;
    virtual void push_event(event* evs){};
    virtual event* poll_event();
    virtual void resolve(event* ev){
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
    operator=(vect<event*> evs){
        events_main s;
        for(int i=0;i<evs.size();i++){
            s.push(evs[i]);
        };
        return s;
    }
    event resolve(int flag)
    events_main(vect<event*> evs){
        this=evs;
    };
    
    };
};
#define MAIN_DEF(ev_m) ev_m main; 
#define NS_USE(ns) using namespace ns;

#define RES_CLASS_DEF(n) ; 
#ifdef STA_IMPL_SDL
#include "impl_sdl.hpp"
using namespace SDL_events;
#endif
using namespace events ;