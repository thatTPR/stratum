#ifndef SGUI_INTERNAL
#define SGUI_INTERNAL
#include <glm/glm.hpp>
#include <backend/impl.hpp>
#include "sgui_widgets.hpp"
#include <functional>
#include <type_traits>
#include <petri/tuple>
#include <array>
#include <time>

#define NSC std::
namespace sgui{


template <typename T>
struct stng : NSC array<std::function<void(T)>,0xFF> {
    bool exists(size_t s) {T t();
        try {(*this)[s](t)} catch (const std::bad_function_call& e){return false;}
        return true;
    };
};


template <typename T>
struct multi_stng : NSC array<stng<T>,5> {};



    #ifndef EXTENDMACRO  
    #define EVMACRO_ALL(x) x(abort) x(activate) x(begin) x(cancel) x(canplay) x(canplaythrough) x(change) x(click) x(close) x(cuechange) x(dblclick) x(drag) x(dragend) x(dragenter) x(dragleave) x(dragover) x(dragstart) x(drop) x(durationchange) x(emptied) x(end) x(ended) x(error) x(focus) x(focusin) x(focusout) x(input) x(invalid) x(keydown) x(keypress) x(keyup) x(load) x(loadeddata) x(loadedmetadata) x(loadstart) x(mousedown) x(mouseenter) x(mouseleave) x(mousemove) x(mouseout) x(mouseover) x(mouseup) x(mousewheel) x(mousewheelh) x(pause) x(play) x(playing) x(progress) x(ratechange) x(repeat) x(reset) x(resize) x(scroll) x(seeked) x(seeking) x(select) x(show) x(stalled) x(submit) x(suspend) x(timeupdate) x(toggle) x(unload) x(volumechange) x(waiting)


enum even {
    even_first,
    #define SGUIEVEN(ev) _ev_##ev,
    EVMACRO_ALL(SGUIEVEN)
_ev_joy_axis,
_ev_joy_hat,
_ev_joy_button,
_ev_joy_up,
_ev_joy_down,
_ev_joy_press,
_ev_joy_rot,
_ev_joy_throt,


_ev_CONT_press,
_ev_CONT_down,
_ev_CONT_up,
_ev_CONT_dpad,
_ev_CONT_axis,
_ev_CONT_trig,

_ev_touch_move,
_ev_touch_tap,
_ev_touch_zoom,
_ev_touch_gesture,

move,

    reserved
};

template <even _E, typename T=void>
struct ev  {
    using dtype = T;
    static constexpr even evty = _E; 
    void cb(dtype& p){};
    ev() = default ;
};  
struct impl_drag :   event_impl<glm::mat2x2 , impl::mouse_move,impl::touch_move>{};
struct impl_drop :   event_impl<glm::vec2 , impl::mouse_up,impl::touch_up>{};
struct impl_input :  event_impl<impl::keypress,impl::keypress>{};
struct impl_scroll : event_impl<glm::vec2,impl::mouse_wheel,impl::mouse_wheelh,impl::touch_move>{};
struct impl_resize : event_impl<glm::vec2 , impl::mouse_move,impl::touch_move>{};

struct abort          :ev<even::_ev_abort          ,void>{void ev_abort(); void cb(dtype& dt){ev_abort();};};
struct activate       :ev<even::_ev_activate       ,void>{void ev_activate(); void cb(dtype& dt){ev_activate();};};
struct begin          :ev<even::_ev_begin          ,void>{void ev_begin(); void cb(dtype& dt){ev_begin();};};
struct cancel         :ev<even::_ev_cancel         ,void>{void ev_cancel(); void cb(dtype& dt){ev_cancel();};};
struct canplay        :ev<even::_ev_canplay        ,void>{void ev_canplay(); void cb(dtype& dt){ev_canplay();};};
struct canplaythrough :ev<even::_ev_canplaythrough ,void>{void ev_canplaythrough(); void cb(dtype& dt){ev_canplaythrough();};};
struct change         :ev<even::_ev_change         ,void>{void ev_change(); void cb(dtype& dt){ev_change();};};
struct click          :ev<even::_ev_click          ,impl::click>{ ;void ev_click();void cb(dtype& dt){ev_click();};};
struct rclick         :ev<even::_ev_click          ,impl::click>{void ev_rclick();void cb(dtype& dt){ev_rclick();};};
struct close          :ev<even::_ev_close          ,void>{void ev_close();;};
struct cuechange      :ev<even::_ev_cuechange      ,void>{void ev_cuechange();;};
struct dblclick       :ev<even::_ev_dblclick       ,impl::dbclick>{void ev_dblclick();void cb(dtype& dt){ev_dbclick();};};
struct drag           :ev<even::_ev_drag           ,impl_drag>{void ev_drag();void cb(dtype& dt){ev_drag();};};
struct dragend        :ev<even::_ev_dragend        ,impl_drag>{void ev_dragend();void cb(dtype& dt){ev_dragend();};};
struct dragenter      :ev<even::_ev_dragenter      ,impl_drag>{void ev_dragenter();void cb(dtype& dt){ev_dragenter();};};
struct dragleave      :ev<even::_ev_dragleave      ,impl_drag>{void ev_dragleave();void cb(dtype& dt){ev_dragleave();};};
struct dragover       :ev<even::_ev_dragover       ,impl_drag>{void ev_dragover();void cb(dtype& dt){ev_dragover();};};
struct dragstart      :ev<even::_ev_dragstart      ,impl_drag>{void ev_dragstart();void cb(dtype& dt){ev_dragstart();};};
struct drop           :ev<even::_ev_drop           ,impl_drop>{void ev_drop();void cb(dtype& dt){ev_drop();};};
struct durationchange :ev<even::_ev_durationchange ,void>{void ev_durationchange();void cb(dtype& dt){ev_durationchange();};};
struct emptied        :ev<even::_ev_emptied        ,void>{void ev_emptied();void cb(dtype& dt){ev_emptied();};};
struct end            :ev<even::_ev_end            ,void>{void ev_end();void cb(dtype& dt){ev_end();};};
struct ended          :ev<even::_ev_ended          ,void>{void ev_ended();void cb(dtype& dt){ev_ended();};};
struct error          :ev<even::_ev_error          ,std::runtime_error>{void ev_error();void cb(dtype& dt){ev_error();};};
struct focus          :ev<even::_ev_focus          ,void>{void ev_focus();void cb(dtype& dt){ev_focus();};};
struct focusin        :ev<even::_ev_focusin        ,void>{void ev_focusin();void cb(dtype& dt){ev_focusin();};};
struct focusout       :ev<even::_ev_focusout       ,void>{void ev_focusout();void cb(dtype& dt){ev_focusout();};};
struct input          :ev<even::_ev_input          ,impl_input>{void ev_input();void cb(dtype& dt){ev_input();};};
struct invalid        :ev<even::_ev_invalid        ,void>{void ev_invalid();void cb(dtype& dt){ev_invalid();};};
struct keydown        :ev<even::_ev_keydown        ,impl::keydown>{void ev_keydown();void cb(dtype& dt){ev_keydown();};};
struct keypress       :ev<even::_ev_keypress       ,impl::keypress>{void ev_keypress();void cb(dtype& dt){ev_keypress();};};
struct keyup          :ev<even::_ev_keyup          ,int>{void ev_keyup();void cb(dtype& dt){ev_keyup();};};
struct load           :ev<even::_ev_load           ,void>{void ev_load();void cb(dtype& dt){ev_load();};};
struct loadeddata     :ev<even::_ev_loadeddata     ,void>{void ev_loadeddata();void cb(dtype& dt){ev_loadeddata();};};
struct loadedmetadata :ev<even::_ev_loadedmetadata ,void>{void ev_loadedmetadata();void cb(dtype& dt){ev_loadedmetadata();};};
struct loadstart      :ev<even::_ev_loadstart      ,void>{void ev_loadstart();void cb(dtype& dt){ev_loadstart();};};
struct mousedown      :ev<even::_ev_mousedown      ,impl::mousedown>{void ev_mousedown();void cb(dtype& dt){ev_mousedown();};};
struct mouseenter     :ev<even::_ev_mouseenter     ,impl::mouse_move>{void ev_mouseenter();void cb(dtype& dt){ev_mouseenter();};};
struct mouseleave     :ev<even::_ev_mouseleave     ,impl::mouse_move>{void ev_mouseleave();void cb(dtype& dt){ev_mouseleave();};};
struct mousemove      :ev<even::_ev_mousemove      ,impl::mouse_move>{void ev_mousemove();void cb(dtype& dt){ev_mousemove();};};
struct mouseout       :ev<even::_ev_mouseout       ,impl::mouse_move>{void ev_mouseout();void cb(dtype& dt){ev_mouseout();};};
struct mouseover      :ev<even::_ev_mouseover      ,impl::mouse_move>{void ev_mouseover();void cb(dtype& dt){ev_mouseover();};};
struct mouseup        :ev<even::_ev_mouseup        ,impl::mouseup>{void ev_mouseup();void cb(dtype& dt){ev_mouseup();};};
struct mousewheel     :ev<even::_ev_mousewheel     ,impl::mouse_wheel>{void ev_mousewheel();void cb(dtype& dt){ev_mousewheel();};};
struct mousewheelh    :ev<even::_ev_mousewheelh,   ,impl::mouse_wheelh>{void ev_mousewheelh();void cb(dtype& dt){ev_mousewheelh();};};
struct pause          :ev<even::_ev_pause          ,void>{void ev_pause();void cb(dtype& dt){ev_pause();};};
struct play           :ev<even::_ev_play           ,void>{void ev_play();void cb(dtype& dt){ev_play();};};
struct playing        :ev<even::_ev_playing        ,std::time_t>{void ev_playing();void cb(dtype& dt){ev_playing();};};
struct progress       :ev<even::_ev_progress       ,unsigned short> {void ev_progress();void cb(dtype& dt){ev_progress();};};
struct ratechange     :ev<even::_ev_ratechange     ,float>{void ev_ratechange();void cb(dtype& dt){ev_ratechange();};};
struct repeat         :ev<even::_ev_repeat         ,void>{void ev_repeat();void cb(dtype& dt){ev_repeat();};};
struct reset          :ev<even::_ev_reset          ,void>{void ev_reset();void cb(dtype& dt){ev_reset();};};
struct resize         :ev<even::_ev_resize         ,impl_resize>{void ev_resize();void cb(dtype& dt){ev_resize();};};
struct scroll         :ev<even::_ev_scroll         ,impl_scroll>{void void ev_scroll(); impl_scroll scroll={0,0} ;void cb(dtype& v){scroll.x=v;ev_scroll();}};
// struct scroll         :ev<even::_ev_scroll,impl_scroll>, ev<even::_ev_scroll2 ,impl_scroll>{void scroll() ;void cb(dtype& v){scroll.y=v;}};
struct seeked         :ev<even::_ev_seeked         ,unsigned long>{void ev_seeked(); dtype seek; void cb(dtype& v ){seek=v;ev_seeked()}};
struct seeking        :ev<even::_ev_seeking        ,unsigned long>{void ev_seeking(); dtype seek; void cb(dtype& v ){seek=v;ev_seeking()}};
struct select         :ev<even::_ev_select         ,unsigned short>{void ev_select(); dtype select; void cb(dtype& v ){seek=v;ev_select()}};
struct show           :ev<even::_ev_show           ,void>{void ev_show(); void cb(dtype& t){ev_show();} };
struct stalled        :ev<even::_ev_stalled        ,void>{void ev_stalled(); void cb(dtype& t){ev_stalled();} };
struct submit         :ev<even::_ev_submit         ,void>{void ev_submit(); void cb(dtype& t){ev_submit();} };
struct suspend        :ev<even::_ev_suspend        ,void>{void ev_suspend(); void cb(dtype& t){ev_suspend();} };
struct timeupdate     :ev<even::_ev_timeupdate     ,time_t>{void ev_timeupdate(); void cb(dtype& t){ev_timeupdate();} };
struct toggle         :ev<even::_ev_toggle         ,bool> {void ev_toggle(); bool toggle=false;void cb(bool& p){toggle=p;ev_toggle();};};
struct unload         :ev<even::_ev_unload         ,void>{void ev_unload(); void cb(dtype& p){ev_unload();} };
struct volumechange   :ev<even::_ev_volumechange   ,impl::volume_change>{void ev_volumechange(); impl::volume_change volume;void cb(impl::volume_change& v){volume=v;ev_volume_change();}};
struct waiting        :ev<even::_ev_waiting        ,void>{void ev_waiting(); void cb(dtype& p){ev_waiting();}};

#define SVG_EVS abort,activate,begin,cancl,canplay,canplaythrough,change,click,rclick,close,cuechange,dblclick,drag,dragend,dragenter,dragleave,dragover,dragstart,drop,durationchange,emptied,end,ended,error,focus,focusin,focusout,input,invalid,keydown,keypress,keyup,load,loadeddata,loadedmetadata,loadstart,mousedown,mouseenter,mouseleave,mousemove,mouseout,mouseover,mouseup,mousewheel,mousewheelh,pause,play,playing,progress,ratechange,repeat,reset,resize,scroll,scroll,seeked,seeking,select,show,stalled,submit,suspend,timeupdate,toggle,unload,volumechange,waiting
enum move_ {up,down,left,right,forward,back}

struct mouse_axis  : event_impl<evne::_ev_mouse_move, impl_mouse_move> {void ev_mouse_axis(dtype& p);void cb(){ev_mouse_axis(dtype& v){ev_mouse_axis(v);};}};
struct move        : ev<even::move, move_>{void ev_move(dtype& p);void cb(){ev_move(dtype& v);}};
struct move2       : ev<even::move, glm::vec2>{void ev_move2(dtype& p);void cb(){ev_move2(dtype& v);}};
struct move3       : ev<even::move, glm::vec3>{void ev_move3(dtype& p);void cb(){ev_move3(dtype& v);}};
struct rotate2     : ev<even::move, float>{void ev_rotate2(dtype& p);void cb(){ev_rotate2(dtype& v);}};
struct rotate3     : ev<even::move, glm::vec3>{void ev_rotate3(dtype& p);void cb(){ev_rotate3(dtype& v);}};
struct translate2  : ev<event::move,glm::vec2>{void ev_translate2(dtype& p);void cb(){ev_translate2(dtype& v);}};
struct translate3  : ev<event::move,glm::vec3>{void ev_translate3(dtype& p);void cb(){ev_translate3(dtype& v);}};
struct acc2        : ev<even::move,glm::vec2>{void ev_acc2(dtype& p);void cb(){ev_acc2(dtype& v);}};
struct acc3        : ev<even::move,glm::vec3>{void ev_acc3(dtype& p);void cb(){ev_acc3(dtype& v);}};
#define MOTION_EVS move,move2,move3,rotate2,rotate3,translate2,translate3,acc2,acc3

// Joy 
#define JOY_EVS
#ifdef SYS_JOY
stng <impl::joy_axis> impl_joy; 

struct joy_axis  :  ev<even::ev_joy_axis,impl::joy_axis>     {void ev_joy_axis(dtype& p);   void cb(dtype& p){ev_joy_axis(p);}};
struct joy_hat  :   ev<even::ev_joy_hat,impl::joy_hat>       {void ev_joy_hat(dtype& p);    void cb(dtype& p){ev_joy_hat(p);}};
struct joy_button  :ev<even::ev_joy_button,impl::joy_button> {void ev_joy_button(dtype& p); void cb(dtype& p){ev_joy_button(p);}};
struct joy_up  :    ev<even::ev_joy_up,impl::joy_up>         {void ev_joy_up(dtype& p);     void cb(dtype& p){ev_joy_up(p);}};
struct joy_down  :  ev<even::ev_joy_down,impl::joy_down>     {void ev_joy_down(dtype& p);   void cb(dtype& p){ev_joy_down(p);}};
struct joy_press  : ev<even::ev_joy_press,impl::joy_press>   {void ev_joy_press(dtype& p);  void cb(dtype& p){ev_joy_press(p);}};
struct joy_rot  :   ev<even::ev_joy_rot,impl::joy_rot>       {void ev_joy_rot(dtype& p);    void cb(dtype& p){ev_joy_rot(p);}};
struct joy_throt  : ev<even::ev_joy_throt,impl::joy_throt>   {void ev_joy_throt(dtype& p);  void cb(dtype& p){ev_joy_throt(p);}};

#define JOY_EVS joy_axis,joy_hat,joy_button,joy_up,joy_down,joy_press,joy_rot,joy_throt
#endif 
// Controller
#define CONT_EVS 
#ifdef SYS_CONT
struct CONT_press: ev<even::_ev_CONT_press,impl::CONT_press> {void ev_CONT_press(dtype& v);void cb(dtype& p){ev_CONT_press(v);}};
struct CONT_down : ev<even::_ev_CONT_down, impl::CONT_down> {void ev_CONT_down(dtype& v);void cb(dtype& p){ev_CONT_down(v);}};
struct CONT_up   : ev<even::_ev_CONT_up,   impl::CONT_up> {void ev_CONT_up(dtype& v);void cb(dtype& p){ev_CONT_up(v);}};
struct CONT_dpad : ev<even::_ev_CONT_dpad, impl::CONT_dpad> {void ev_CONT_dpad(dtype& v);void cb(dtype& p){ev_CONT_dpad(v);}};
struct CONT_axis : ev<even::_ev_CONT_axis, impl::CONT_axis> {void ev_CONT_axis(dtype& v);void cb(dtype& p){ev_CONT_axis(v);}};
struct CONT_trig : ev<even::_ev_CONT_trig, impl::CONT_trig> {void ev_CONT_trig(dtype& v);void cb(dtype& p){ev_CONT_trig(v);}};
#define CONT_EVS CONT_press,CONT_down,CONT_up,CONT_dpad,CONT_axis,CONT_trig
#endif 
#define TOUCH_EVS 
#ifdef SYS_TOUCH
struct touch_move : ev<even::_ev_touch_move,impl::touch_move>{void ev_touch_move(dtype& v);void cb(dtype& v){ev_touch_move(v);}};
struct touch_tap : ev<even::_ev_touch_tap,impl::touch_tap>{void ev_touch_tap(dtype& v);void cb(dtype& v){ev_touch_tap(v);}};
struct touch_zoom : ev<even::_ev_touch_zoom,impl::touch_zoom>{void ev_touch_zoom(dtype& v);void cb(dtype& v){ev_touch_zoom(v);}};
struct touch_gesture : ev<even::_ev_touch_gesture,impl::touch_gesture>{void ev_touch_gesture(dtype& v);void cb(dtype& v){ev_touch_gesture(v);}};
#define TOUCH_EVS touch_move,touch_tap,touch_zoom,touch_gesture
#endif 

#include <petri/templates.hpp>

template <class... ev>
struct oneOfEv {
    template <class... es>
inline constexpr bool is = (pri::is_one_of<es,ev>::value | ... ) ;   
};

template <class... evs >
struct inherEvent: virtual evs...{
    template <ev _enevt>
    inline constexpr bool has_event =  (_enevt == evs::evty ) || ... ;
};  


template <class T>
using inhInputOnly = typename std::conditional<evs::isInEv,T,void>::type ;
template <class... evs >
struct inherOnlyInput : inhInputOnly<evs>... {};


template <class InherT , class... InherTs>
struct inherInhEvent : InherT ,InherTs... {
    temlate <ev enevt>
    inline bool has_event = InherT::has_event<enevt> || (InherTs::has_event<enevt> || ... ) ; 

    using tupty = pri::utupConcats<typename inherT::tupty, typename InherTs >::type... ;
    
};


#if __cplusplus >= 202003L

template <typename T>
concept Event  = std::is_base_of<T,evbase>::value;

template <Event Et>
#else 
template <class Et>
#endif 
struct evinh {
     //
};





struct evsrt :  {


};




};
