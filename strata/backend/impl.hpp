#pragma once
#include "impl.hpp"
#include "implmain.hpp"
#include <strata/petri/vects.hpp>
#include <strata/petri/queue.hpp>
#include <memory>
#include <filesystem>
#include <atomic>
#include <future>
#include <cpuid.h>
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


struct gpu_info {

    bool robustBufferAccess       ,  //Ensures bounds-checking for buffer accesses.
    bool fullDrawIndexUint32      ,  //Allows 32-bit indices for drawing.
    bool geometryShader           ,  //Supports geometry shaders.
    bool tessellationShader       ,  //Supports tessellation shaders.
    bool multiDrawIndirect        ,  //Allows multiple draw calls in a single command.
    bool wideLines                ,  //Enables rendering wide lines.
    bool largePoints              ,  //Enables rendering large points.
    bool textureCompressionETC2   ,  //ETC2 texture compression support.
    bool sparseBinding            ,  //Supports sparse resources (like sparse textures).


    bool ray_tracing_pipeline; /*
Adds support for ray tracing features.
Features structure: VkPhysicalDeviceRayTracingPipelineFeaturesKHR.
    */
    bool descriptor_indexing;/*
Adds support for descriptor indexing.
Features structure: VkPhysicalDeviceDescriptorIndexingFeatures.
    */    
    bool multiview;
/*
Adds support for rendering to multiple views (e.g., for VR).
Features structure: VkPhysicalDeviceMultiviewFeatures.
*/
    bool sampler_filter_minmax;

Adds support for min/max filtering.
Features structure: VkPhysicalDeviceSamplerFilterMinmaxFeaturesEXT.
    bool 
};
template <typename winsurface, typename Pipeline,   > 
class strata_impl {
    vect<Pipeline> pipelines;
    vect<winsurface> winsurfaces;
virtual void create_fullscreen();
virtual void get_gpu_info(gpu_info gpinfo);
virtual _shader load_shader(const uint32_t shader[] );
virtual void shader_bind(_shader shader,auto*... uniforms);
void descriptor_set();
void descriptor_pool();
void create_swapchain();
virtual void load_SSBO(_shader shader,auto* buffer);
virtual void load_UBO(_shader shader,auto* buffer);
virtual void draw(_stage ;);
virtual void blend();

void exec(shader_module module) final{};
void pipeline_create(size_t shad_size , shader_module* modules )final{
    for(int i =0; i<shad_size;i++){
        this->
    };
};
virtual void init(){

} ; // Gets platform info

};
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
    

namespace events {
#include "impl.def.hpp"

using click = event<int,_click>;    
using dbclick = event<int,_dbclick>;
using mousedown = event<int,_mousedown>;        
using mouseup = event<int,_mouseup>;      
using mouse_move = event<ivec2,_mouse_move>;//xy
using mouse_wheel = event<int,_mouse_wheel>; //x       
using mouse_wheelh = event<int,_mouse_wheelh>;
class MOUSE: public  event_sys<evs::_MOUSE> {
 public:
    
 const uint flag=_MOUSE;
    arr<click, MAX_POLL>       last_click; 
    arr<dbclick, MAX_POLL>     last_db_click;     
    arr<mousedown, MAX_POLL>   last_down;          
    arr<mouseup, MAX_POLL>     last_up;        
    arr<mouse_move,MAX_POLL>  last_move;           
    arr<mouse_wheel,MAX_POLL> last_wheel;     
    arr<mouse_wheelh,MAX_POLL> last_wheelh;     
    bool detect_combo(ivec2* s){
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
    int detect_combo(size_t size_combos ,ivec2* s){

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
    void clear()final{this->last_click.clear();this->last_down.clear();this->last_up.clear();this->last_press.clear();this->last_move.clear();this->last_wheel.clear();}
    virtual vec2 get_pos(){return this->last_move.data()};
    virtual bool get_state(short int bt){return this->last_press.data==bt};
     void push_click(int click,int index=0) final {this->ev_main.push(mouse_move(click,index));}
     void push_move(vec2 mv,int index=0) final {this->ev_main.push(mouse_move(mv,index));};
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
     void move_cb(vec2 mv,int index=0) final {this->last_move+=mouse_move(mv,index);};
     void down_cb(int down,int index=0) final {this->last_down+=mouse_down(down,index);};
     void up_cb(int up,int index=0) final {up_check(up);this->last_up+=mouse_up(up,index);};
     void wheel_cb(float wheel,int index=0) final {this->last_wheel+=mouse_wheel(wheel,index);};
     void wheelh_cb(float wheel,int index=0) final {this->last_wheelh+=mouse_wheelh(wheel,index);};
     void dbclick_cb(click ev) final {this->last_dbclick+=ev;}
     void click_cb(click ev) final {this->last_click+=ev;}
     void move_cb(mouse_move ev) final {this->last_move+=ev;};
     void down_cb(mousedown ev) final {this->last_down+=ev;};
     void up_cb(mouseup ev) final { up_check(ev.data());this->last_up+=ev;};
     void wheel_cb(mouse_wheel ev) final {this->last_wheel+=ev;};
     void wheelh_cb(mouse_wheel ev) final {this->last_wheelh+=ev;};
   
    virtual void handle();
    virtual void _handle(){
        this->handle();

    };
    void init()override{
        this->_init();};
    };
   
}; 
using keyup = event<int,_keyup>; // x button, y index    
using keydown = event<int,_keydown>; // x button, y index      
using keypress = event<int,_keypress>; // x button, y index       
class KEY : public event_sys<evs::_KEY> {
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
using joy_hat = event<int,_joy_hat>;  
using joy_axis = event<ivec2,_joy_axis>; // x axis y index       
using joy_up = event<int,_joy_up>;    
using joy_down = event<int,_joy_down>;      
using joy_press = event<int,_joy_press>;     
class  JOY : public event_sys<evs::_JOY> {
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
using CONT_press= event<int,_CONT_press>;                    
using CONT_down = event<int,_CONT_down>; 
using CONT_up = event<int,_CONT_up>; 
using CONT_dpad = event<int,_CONT_dpad>;
using CONT_axis = event<ivec2,_CONT_axis>;  // Axis index;
class CONT: public event_sys<evs::_CONT> {
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
using touch_move = event<vect<vec4>,_touch_move>; //xy last zw move
using touch_tap  =  event<vect<vec2>,_touch_tap>;// tap
using touch_zoom =  event<mat<vec2>,_touch_gesture>; // xy move,z rotate,w zoom
using touch_gesture =event<vect<vec4>,_touch_zoom>; // rotate


class TOUCH: public event_sys<evs::_TOUCH> { 
 public:
touch_move last_move;
touch_tap last_tap;
touch_zoom last_zoom;
touch_gesture last_gesture;
    
    bool rec_gest;
    suvec2 get_pos();
    vect<suvec2> get_multi_pos();
    virtual void get_touch();
    vect<touch_move> s;
        bool move_cb(vect<vec4> d,int index){this->last_move=move(d,index);}      bool push_touch_move(vect<vec4> d,int index){this->evmain.push(move_cb(d,index));}
        bool tap_cb(vect<vec2> d,int index){this->last_tap=tap(d,index);}      bool push_touch_tap(vect<vec2> d,int index){this->evmain.push(tap_cb(d,index));}
        bool zoom_cb(mat<vec2> d,int index){this->last_zoom=zoom(d,index);}      bool push_touch_zoom(mat<vec2> d,int index){this->evmain.push(zoom_cb(d,index));}
        bool gesture_cb(vect<vec4> d,int index){this->last_gesture=gesture(d,index);}      bool push_touch_gesture(vect<vec4> d,int index){this->evmain.push(gesture_cb(d,index));}
    void move_cb(touch_move ev){this->last_move_cb=ev;};           void push_move(touch_move ev){this->evmain.push(ev);};
    void tap_cb(touch_tap ev){this->last_tap_cb=ev;};              void push_tap(touch_tap ev){this->evmain.push(ev);};
    void zoom_cb(touch_zoom ev){this->last_zoom_cb=ev;};           void push_zoom(touch_zoom ev){this->evmain.push(ev);};
    void gesture_cb(touch_gesture ev){this->last_gesture_cb=ev;};  void push_gesture(touch_gesture ev){this->evmain.push(ev);};

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


class INT : public event_sys<evs::_INT>{
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
class UI :public event_sys<evs::_UI> {
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
    combo     last_combo;       
    textedit  last_textedit;     

    bool enter_cb(bool d,int index){this->last_enter=last_enter(d,index);};
    bool leave_cb(bool d,int index){this->last_leave=last_leave(d,index);};
    bool focus_cb(bool d,int index){this->last_focus=last_focus(d,index);};
    bool drag_cb(bool d,int index){this->last_drag=last_drag(d,index);};
    bool dragstart_cb(bool d,int index){this->last_dragstart=last_dragstart(d,index);};
    bool dragend_cb(bool d,int index){this->last_dragend=last_dragend(d,index);};
    bool keycombo_cb(ivec4 d,int index){this->last_keycombo=last_keycombo(d,index);};
    bool dbclick_cb(ivec2 d,int index){this->last_dbclick=last_dbclick(d,index);};
    bool combo_cb(imat2x4 d,int index){this->last_combo=last_combo(d,index);};
    bool textedit_cb(text_edit d,int index){this->last_textedit=last_textedit(d,index);};


    bool enter_cb(enter ev){this->last_enter=ev;};
    bool leave_cb(leave ev){this->last_leave=ev;};
    bool focus_cb(focus ev){this->last_focus=ev;};
    bool drag_cb(drag ev){this->last_drag=ev;};
    bool dragstart_cb(dragstart ev){this->last_dragstart=ev;};
    bool dragend_cb(dragend ev){this->last_dragend=ev;};
    bool keycombo_cb(keycombo ev){this->last_keycombo=ev;};
    bool dbclick_cb(dbclick ev){this->last_dbclick=ev;};
    bool combo_cb(combo ev){this->last_combo=ev;};
    bool textedit_cb(textedit ev){this->last_textedit=ev;};

 const uint flag=_UI;
    public: 
    
    virtual void get_db_click_ms(int per);
    int get_ms(int _ms=200) final{this->ms=_ms}; int16 ms_cur;}
};

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
class DISPLAY : event_sys<evs::_DISPLAY> {
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

template <typename win>
class SYS : public event_sys<evs::_SYS> { 
    public:

 const uint flag=_SYS;
    event_main evmain;
    MOUSE      sMOUSE;           
    KEY        sKEY;         
    JOY        sJOY;         
    CONT       sCONT;                
    TOUCH      sTOUCH;           
    INT        sINT;                  
    UI         sUI;        
    AUDIO      sAUDIO;         
    SENSOR     sSENSOR;  
  
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
    
    
    template<typename... subsys>
    void prioirty(subsys... s){// TODO Priority remplating.
        ((s.priority())...);
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
    virtual void handle();
   
    void init() {        
        this->_init()}; 
    void init_evsys(uint flags){
        if( (flags & MOUSE::flag)==MOUSE::flag)       {this->sMOUSE.init();};
        if( (flags & KEY::flag)==KEY::flag)           {this->sKEY.init();};
        if( (flags & JOY::flag)==JOY::flag)           {this->sJOY.init();};
        if( (flags & CON::flag)==CON::flag)           {this->sCON.init();};
        if( (flags & TOUCH::flag)==TOUCH::flag)       {this->sTOUCH.init();};
        if( (flags & UI::flag)==UI::flag)             {this->sUI.init();};
        if( (flags & AUDIO::flag)==AUDIO::flag)       {this->sAUDIO.init();};
        if( (flags & INT::flag)==INT::flag)           {this->sINT_ALL.init();};
        if( (flags & SENSOR::flag)==SENSOR::flag)     {this->sSENSOR.init();};
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
    SYS(uint flags)=default{this->init_evsys(flags);}
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


