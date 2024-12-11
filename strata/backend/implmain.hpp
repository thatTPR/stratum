#pragma once
#include "impl.hpp"
union event_union {    // union mouse {
click           click_ev;             
mousedown       mousedown_ev;                 
mouseup         mouseup_ev;               
mouse_press     mouse_press_ev;                   
mouse_move      mouse_move_ev;                  
mouse_wheel     mouse_wheel_ev;                   
keyup           keyup_ev;             
keydown         keydown_ev;               
keypress        keypress_ev;            // union joy {
joy_hat         joy_hat_ev;               
joy_axis        joy_axis_ev;                
joy_up          joy_up_ev;              
joy_down        joy_down_ev;                
joy_press       joy_press_ev;// union cont {
CONT_press      CONT_press_ev;                  
CONT_down       CONT_down_ev;                 
CONT_up         CONT_up_ev;               
CONT_dpad       CONT_dpad_ev;                 
CONT_axis       CONT_axis_ev;   // union touch {
touch_move      touch_move_ev;                  
touch_tap       touch_tap_ev;                 
touch_zoom      touch_zoom_ev;                  
touch_gesture   touch_gesture_ev;                     // union control{
motion          motion_ev;              
accmotion       accmotion_ev;                 
rotate2d        rotate2d_ev;                
translate2d     translate2d_ev;                   
rotate3d        rotate3d_ev;                
translate3d     translate3d_ev;                   
accrotate2d     accrotate2d_ev;                   
acctranslate2d  acctranslate2d_ev;                      
accrotate3d     accrotate3d_ev;                   
acctranslate3d  acctranslate3d_ev;// union ui
enter           enter_ev;             
leave           leave_ev;             
focus           focus_ev;             
drag            drag_ev;            
dragstart       dragstart_ev;                 
dragend         dragend_ev;               
keycombo        keycombo_ev;                
dbclick         dbclick_ev;               
combo           combo_ev;             
textedit        textedit_ev;                // union sys
wake            wake_ev;            
sleep           sleep_ev;             
min             min_ev;           
max             max_ev;           
hide            hide_ev;            
resize          resize_ev;              
move            move_ev;            
fullscreen      fullscreen_ev;                  
};

struct evun{
    union event_union;
    evs flag;
};
class pr {
    evs flag;
    bool (*cb)(evun);
    void operator=(bool (*f)(evun)){this->cb=f;}
};
class event_main { 
    public:
    using ev_sys=events;
    vect<int> flags;
    SYS* s;
    queue<ev_union*> events;
    vect<ev_filter*> evfilters;
    pr __click
    pr __mousedown;
    pr __mouseup;
    pr __mouse_press;
    pr __mouse_move;
    pr __mouse_wheel;
    pr __keyup;
    pr __keydown;
    pr __keypress;
    pr __joy_hat;
    pr __joy_axis;
    pr __joy_up;
    pr __joy_down;
    pr __joy_press;
    pr __CONT_press;
    pr __CONT_down;
    pr __CONT_up;
    pr __CONT_dpad;
    pr __CONT_axis;
    pr __touch_move;
    pr __touch_tap;
    pr __touch_zoom;
    pr __touch_gesture;
    pr __motion;
    pr __accmotion;
    pr __rotate2d;
    pr __translate2d;
    pr __rotate3d;
    pr __translate3d;
    pr __accrotate2d;
    pr __acctranslate2d;
    pr __accrotate3d;
    pr __acctranslate3d;
    pr __enter;
    pr __leave;
    pr __focus;
    pr __drag;
    pr __dragstart;
    pr __dragend;
    pr __keycombo;
    pr __dbclick;
    pr __combo;
    pr __textedit;
    pr __wake;
    pr __sleep;
    pr __min;
    pr __max;
    pr __hide;
    pr __resize;
    pr __move;
    pr __fullscreen;
    pr __close;
    pr __display_conn;
    pr __display_orient;
    pr __display_power;
    );
    vect<pr> evsyspr; // Priority

    void set_pr(vect<evs> pr_evs){
        for(int i = 0 ; i<pr_evs.size();i++){
            int j;
            for(int j = i ; this->evsyspr[j].flag!=pr_evs[i];j++ );
            if(j==i){continue;};
            this->evsyspr.swap(i,j);
        };
    };
    void set_click(bool (*f)(evun))final{this->__click = f;};
    void set_mousedown(bool (*f)(evun))final{this->__mousedown = f;};
    void set_mouseup(bool (*f)(evun))final{this->__mouseup = f;};
    void set_mouse_press(bool (*f)(evun))final{this->__mouse_press = f;};
    void set_mouse_move(bool (*f)(evun))final{this->__mouse_move = f;};
    void set_mouse_wheel(bool (*f)(evun))final{this->__mouse_wheel = f;};
    void set_keyup(bool (*f)(evun))final{this->__keyup = f;};
    void set_keydown(bool (*f)(evun))final{this->__keydown = f;};
    void set_keypress(bool (*f)(evun))final{this->__keypress = f;};
    void set_joy_hat(bool (*f)(evun))final{this->__joy_hat = f;};
    void set_joy_axis(bool (*f)(evun))final{this->__joy_axis = f;};
    void set_joy_up(bool (*f)(evun))final{this->__joy_up = f;};
    void set_joy_down(bool (*f)(evun))final{this->__joy_down = f;};
    void set_joy_press(bool (*f)(evun))final{this->__joy_press = f;};
    void set_CONT_press(bool (*f)(evun))final{this->__CONT_press = f;};
    void set_CONT_down(bool (*f)(evun))final{this->__CONT_down = f;};
    void set_CONT_up(bool (*f)(evun))final{this->__CONT_up = f;};
    void set_CONT_dpad(bool (*f)(evun))final{this->__CONT_dpad = f;};
    void set_CONT_axis(bool (*f)(evun))final{this->__CONT_axis = f;};
    void set_touch_move(bool (*f)(evun))final{this->__touch_move = f;};
    void set_touch_tap(bool (*f)(evun))final{this->__touch_tap = f;};
    void set_touch_zoom(bool (*f)(evun))final{this->__touch_zoom = f;};
    void set_touch_gesture(bool (*f)(evun))final{this->__touch_gesture = f;};
    void set_motion(bool (*f)(evun))final{this->__motion = f;};
    void set_accmotion(bool (*f)(evun))final{this->__accmotion = f;};
    void set_rotate2d(bool (*f)(evun))final{this->__rotate2d = f;};
    void set_translate2d(bool (*f)(evun))final{this->__translate2d = f;};
    void set_rotate3d(bool (*f)(evun))final{this->__rotate3d = f;};
    void set_translate3d(bool (*f)(evun))final{this->__translate3d = f;};
    void set_accrotate2d(bool (*f)(evun))final{this->__accrotate2d = f;};
    void set_acctranslate2d(bool (*f)(evun))final{this->__acctranslate2d = f;};
    void set_accrotate3d(bool (*f)(evun))final{this->__accrotate3d = f;};
    void set_acctranslate3d(bool (*f)(evun))final{this->__acctranslate3d = f;};
    void set_enter(bool (*f)(evun))final{this->__enter = f;};
    void set_leave(bool (*f)(evun))final{this->__leave = f;};
    void set_focus(bool (*f)(evun))final{this->__focus = f;};
    void set_drag(bool (*f)(evun))final{this->__drag = f;};
    void set_dragstart(bool (*f)(evun))final{this->__dragstart = f;};
    void set_dragend(bool (*f)(evun))final{this->__dragend = f;};
    void set_keycombo(bool (*f)(evun))final{this->__keycombo = f;};
    void set_dbclick(bool (*f)(evun))final{this->__dbclick = f;};
    void set_combo(bool (*f)(evun))final{this->__combo = f;};
    void set_textedit(bool (*f)(evun))final{this->__textedit = f;};
    void set_wake(bool (*f)(evun))final{this->__wake = f;};
    void set_sleep(bool (*f)(evun))final{this->__sleep = f;};
    void set_min(bool (*f)(evun))final{this->__min = f;};
    void set_max(bool (*f)(evun))final{this->__max = f;};
    void set_hide(bool (*f)(evun))final{this->__hide = f;};
    void set_resize(bool (*f)(evun))final{this->__resize = f;};
    void set_move(bool (*f)(evun))final{this->__move = f;};
    void set_fullscreen(bool (*f)(evun))final{this->__fullscreen = f;};
    void close(bool (*f)(evun))final{this->__close=f;};
    void display_conn(bool (*f)(evun))final{this->__display_conn=f;};
    void display_orient(bool (*f)(evun))final{this->__display_orient=f;};
    void display_power(bool (*f)(evun))final{this->__display_power=f;};
    void resolve(evun e)  {
        for(int i = 0;i<this->evsyspr.size();i++){
            if(e.flag==this->evsyspr[i].flag){
                this->evsyspr[i].cb(ev);
            };

        };
    };
    void init(
        bool (*click)(evun),
        bool (*mousedown)(evun),
        bool (*mouseup)(evun),
        bool (*mouse_press)(evun),
        bool (*mouse_move)(evun),
        bool (*mouse_wheel)(evun),
        bool (*keyup)(evun),
        bool (*keydown)(evun),
        bool (*keypress)(evun),
        bool (*joy_hat)(evun),
        bool (*joy_axis)(evun),
        bool (*joy_up)(evun),
        bool (*joy_down)(evun),
        bool (*joy_press)(evun),
        bool (*CONT_press)(evun),
        bool (*CONT_down)(evun),
        bool (*CONT_up)(evun),
        bool (*CONT_dpad)(evun),
        bool (*CONT_axis)(evun),
        bool (*touch_move)(evun),
        bool (*touch_tap)(evun),
        bool (*touch_zoom)(evun),
        bool (*touch_gesture)(evun),
        bool (*motion)(evun),
        bool (*accmotion)(evun),
        bool (*rotate2d)(evun),
        bool (*translate2d)(evun),
        bool (*rotate3d)(evun),
        bool (*translate3d)(evun),
        bool (*accrotate2d)(evun),
        bool (*acctranslate2d)(evun),
        bool (*accrotate3d)(evun),
        bool (*acctranslate3d)(evun),
        bool (*enter)(evun),
        bool (*leave)(evun),
        bool (*focus)(evun),
        bool (*drag)(evun),
        bool (*dragstart)(evun),
        bool (*dragend)(evun),
        bool (*keycombo)(evun),
        bool (*dbclick)(evun),
        bool (*combo)(evun),
        bool (*textedit)(evun),
        bool (*wake)(evun),
        bool (*sleep)(evun),
        bool (*min)(evun),
        bool (*max)(evun),
        bool (*hide)(evun),
        bool (*resize)(evun),
        bool (*move)(evun),
        bool (*fullscreen)(evun),
        bool (*close)(evun),
        bool (*display_conn)(evun),
        bool (*display_orient)(evun),
        bool (*display_power)(evun)
    ){
        set_click(click);
        set_mousedown(mousedown);
        set_mouseup(mouseup);
        set_mouse_press(mouse_press);
        set_mouse_move(mouse_move);
        set_mouse_wheel(mouse_wheel);
        set_keyup(keyup);
        set_keydown(keydown);
        set_keypress(keypress);
        set_joy_hat(joy_hat);
        set_joy_axis(joy_axis);
        set_joy_up(joy_up);
        set_joy_down(joy_down);
        set_joy_press(joy_press);
        set_CONT_press(CONT_press);
        set_CONT_down(CONT_down);
        set_CONT_up(CONT_up);
        set_CONT_dpad(CONT_dpad);
        set_CONT_axis(CONT_axis);
        set_touch_move(touch_move);
        set_touch_tap(touch_tap);
        set_touch_zoom(touch_zoom);
        set_touch_gesture(touch_gesture);
        set_motion(motion);
        set_accmotion(accmotion);
        set_rotate2d(rotate2d);
        set_translate2d(translate2d);
        set_rotate3d(rotate3d);
        set_translate3d(translate3d);
        set_accrotate2d(accrotate2d);
        set_acctranslate2d(acctranslate2d);
        set_accrotate3d(accrotate3d);
        set_acctranslate3d(acctranslate3d);
        set_enter(enter);
        set_leave(leave);
        set_focus(focus);
        set_drag(drag);
        set_dragstart(dragstart);
        set_dragend(dragend);
        set_keycombo(keycombo);
        set_dbclick(dbclick);
        set_combo(combo);
        set_textedit(textedit);
        set_wake(wake);
        set_sleep(sleep);
        set_min(min);
        set_max(max);
        set_hide(hide);
        set_resize(resize);
        set_move(move);
        set_fullscreen(fullscreen);
        set_close(close);
        set_display_conn(display_conn);
        set_display_orient(display_orient);
        set_display_power(display_power);

    };
    void init(SYS s){
        void init(
        s.sMOUSE.click,
        s.sMOUSE.mousedown,
        s.sMOUSE.mouseup,
        s.sMOUSE.mouse_press,
        s.sMOUSE.mouse_move,
        s.sMOUSE.mouse_wheel,
        s.sKEY.keyup,
        s.sKEY.keydown,
        s.sKEY.keypress,
        s.sJOY.joy_hat,
        s.sJOY.joy_axis,
        s.sJOY.joy_up,
        s.sJOY.joy_down,
        s.sJOY.joy_press,
        s.sCONT.CONT_press,
        s.sCONT.CONT_down,
        s.sCONT.CONT_up,
        s.sCONT.CONT_dpad,
        s.sCONT.CONT_axis,
        s.sCONT.touch_move,
        s.sTOUCH.touch_tap,
        s.sTOUCH.touch_zoom,
        s.sTOUCH.touch_gesture,
        s.sINT.motion,
        s.sINT.accmotion,
        s.sINT.rotate2d,
        s.sINT.translate2d,
        s.sINT.rotate3d,
        s.sINT.translate3d,
        s.sINT.accrotate2d,
        s.sINT.acctranslate2d,
        s.sINT.accrotate3d,
        s.sINT.acctranslate3d,
        s.sUI.enter,
        s.sUI.leave,
        s.sUI.focus,
        s.sUI.drag,
        s.sUI.dragstart,
        s.sUI.dragend,
        s.sUI.keycombo,
        s.sUI.dbclick,
        s.sUI.combo,
        s.sUI.textedit,
        s.wake,
        s.sleep,
        s.min,
        s.max,
        s.hide,
        s.resize,
        s.move,
        s.fullscreen,
        s.close,
        s.display_conn,
        s.display_orient,
        s.display_power);
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
