#ifndef SGUI_INTERNAL
#define SGUI_INTERNAL
#include <stratum/backend/impl.hpp>
#include "sgui_widgets.hpp"
#include <functional>
#include <type_traits>
#include <stratum/petri/tuple.hpp>
namespace sgui{
    #ifndef EXTENDMACRO  
    #define EVMACRO_ALL(x) x(abort) x(activate) x(begin) x(cancel) x(canplay) x(canplaythrough) x(change) x(click) x(close) x(cuechange) x(dblclick) x(drag) x(dragend) x(dragenter) x(dragleave) x(dragover) x(dragstart) x(drop) x(durationchange) x(emptied) x(end) x(ended) x(error) x(focus) x(focusin) x(focusout) x(input) x(invalid) x(keydown) x(keypress) x(keyup) x(load) x(loadeddata) x(loadedmetadata) x(loadstart) x(mousedown) x(mouseenter) x(mouseleave) x(mousemove) x(mouseout) x(mouseover) x(mouseup) x(mousewheel) x(pause) x(play) x(playing) x(progress) x(ratechange) x(repeat) x(reset) x(resize) x(scroll) x(seeked) x(seeking) x(select) x(show) x(stalled) x(submit) x(suspend) x(timeupdate) x(toggle) x(unload) x(volumechange) x(waiting


enum even {
    #define SGUIEVEN(ev) _ev_##ev,
    EVMACRO_ALL(SGUIEVEN)

_ev_joy_axis,
_ev_joy_axis,
_ev_joy_axis,
_ev_joy_axis,
_ev_joy_axis,
_ev_joy_axis,
_ev_joy_axis,
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

    reserved
}

template <even en,typename... T>
struct ev {
    constexpr even e = en;
    using functy = std::function<void(T...)>;
    using argtup = pri::tuple<T...>;
    using functytup = typename std::conditional<sizeof...(T) ==0,std::function<void()> ,std::function<void(argtup)>::type;
    // functy function;
    functytup func;
    // void operator()(T... args){ function(args...);}
    void operator()(argtup args){ func(args);}
    void operator()(T... args){ 
        if constexpr(sizeof...(T) == 0){func();return}
        func(argtup(args...));}
    ev<en,func>& operator=(func ptr){function=ptr;return *this;}

}

using ev_abort           =ev<even::_ev_abort          >;
using ev_activate        =ev<even::_ev_activate       >;
using ev_begin           =ev<even::_ev_begin          >;
using ev_cancel          =ev<even::_ev_cancel         >;
using ev_canplay         =ev<even::_ev_canplay        >;
using ev_canplaythrough  =ev<even::_ev_canplaythrough >;
using ev_change          =ev<even::_ev_change         >;
using ev_click           =ev<even::_ev_click         , impl::click>;
using ev_close           =ev<even::_ev_close          >;
using ev_cuechange       =ev<even::_ev_cuechange      >;
using ev_dblclick        =ev<even::_ev_dblclick      , click>;
using ev_drag            =ev<even::_ev_drag           >;
using ev_dragend         =ev<even::_ev_dragend        >;
using ev_dragenter       =ev<even::_ev_dragenter      >;
using ev_dragleave       =ev<even::_ev_dragleave      >;
using ev_dragover        =ev<even::_ev_dragover       >;
using ev_dragstart       =ev<even::_ev_dragstart      >;
using ev_drop            =ev<even::_ev_drop           >;
using ev_durationchange  =ev<even::_ev_durationchange >;
using ev_emptied         =ev<even::_ev_emptied        >;
using ev_end             =ev<even::_ev_end            >;
using ev_ended           =ev<even::_ev_ended          >;
using ev_error           =ev<even::_ev_error         , uint32_t>;
using ev_focus           =ev<even::_ev_focus          >;
using ev_focusin         =ev<even::_ev_focusin        >;
using ev_focusout        =ev<even::_ev_focusout       >;
using ev_input           =ev<even::_ev_input          >;
using ev_invalid         =ev<even::_ev_invalid        >;
using ev_keydown         =ev<even::_ev_keydown       , impl::keydown>;
using ev_keypress        =ev<even::_ev_keypress      , impl::keypress>;
using ev_keyup           =ev<even::_ev_keyup         , int>;
using ev_load            =ev<even::_ev_load           >;
using ev_loadeddata      =ev<even::_ev_loadeddata     >;
using ev_loadedmetadata  =ev<even::_ev_loadedmetadata >;
using ev_loadstart       =ev<even::_ev_loadstart      >;
using ev_mousedown       =ev<even::_ev_mousedown     , impl::mousedown>;
using ev_mouseenter      =ev<even::_ev_mouseenter     >;
using ev_mouseleave      =ev<even::_ev_mouseleave     >;
using ev_mousemove       =ev<even::_ev_mousemove      >;
using ev_mouseout        =ev<even::_ev_mouseout       >;
using ev_mouseover       =ev<even::_ev_mouseover      >;
using ev_mouseup         =ev<even::_ev_mouseup        >;
using ev_mousewheel      =ev<even::_ev_mousewheel    , impl::mousewheel>;
using ev_pause           =ev<even::_ev_pause          >;
using ev_play            =ev<even::_ev_play           >;
using ev_playing         =ev<even::_ev_playing        >;
using ev_progress        =ev<even::_ev_progress       >;
using ev_ratechange      =ev<even::_ev_ratechange     >;
using ev_repeat          =ev<even::_ev_repeat         >;
using ev_reset           =ev<even::_ev_reset          >;
using ev_resize          =ev<even::_ev_resize        , glm::ivec2,sgui::Resize>;
using ev_scroll          =ev<even::_ev_scroll        , int32_t>;
using ev_seeked          =ev<even::_ev_seeked         >;
using ev_seeking         =ev<even::_ev_seeking        >;
using ev_select          =ev<even::_ev_select         >;
using ev_show            =ev<even::_ev_show           >;
using ev_stalled         =ev<even::_ev_stalled        >;
using ev_submit          =ev<even::_ev_submit         >;
using ev_suspend         =ev<even::_ev_suspend        >;
using ev_timeupdate      =ev<even::_ev_timeupdate     >;
using ev_toggle          =ev<even::_ev_toggle         >;
using ev_unload          =ev<even::_ev_unload         >;
using ev_volumechange    =ev<even::_ev_volumechange  , int8_t>;
using ev_waiting         =ev<even::_ev_waiting       >;


// Joy 
using ev_joy_hat = ev<even::_ev_joy_axis,size_t,impl::joy_hat>;
using ev_joy_button = ev<even::_ev_joy_axis,size_t,impl::joy_axis>;
using ev_joy_up = ev<even::_ev_joy_axis,size_t,impl::joy_up>;
using ev_joy_down = ev<even::_ev_joy_axis,size_t,impl::joy_down>;
using ev_joy_press = ev<even::_ev_joy_axis,size_t,impl::joy_press>;
using ev_joy_rot = ev<even::_ev_joy_axis,size_t,impl::joy_rot>;
using ev_joy_throt = ev<even::_ev_joy_axis,size_t,impl::joy_throt>;
// Controller

using ev_CONT_press = ev<even::_ev_CONT_press,size_t,impl::CONT_press> ;
using ev_CONT_down = ev<even::_ev_CONT_down,size_t,impl::CONT_down> ;
using ev_CONT_up = ev<even::_ev_CONT_up,size_t,impl::CONT_up> ;
using ev_CONT_dpad = ev<even::_ev_CONT_dpad,size_t,impl::CONT_dpad> ;
using ev_CONT_axis = ev<even::_ev_CONT_axis,size_t,impl::CONT_axis> ;
using ev_CONT_trig = ev<even::_ev_CONT_trig,size_t,impl::CONT_trig> ;


using ev_touch_move = ev<even::_ev_touch_move,impl::touch_move>;
using ev_touch_tap = ev<even::_ev_touch_tap,impl::touch_tap>;
using ev_touch_zoom = ev<even::_ev_touch_zoom,impl::touch_zoom>;
using ev_touch_gesture = ev<even::_ev_touch_gesture,impl::touch_gesture>;



template <typename evft>
struct weven_ {
    #define WEVENT_MACRO(event) constexpr bool b##event=evft::e==even::_ev_##event ;std::enable_if<b##event,evft::evt>::type event_ ; 
    EVMACRO_ALL(WEVENT_MACRO)
}
template <even e, typename weve>
struct memberis {
    constexpr bool Boolean = [](){
        #define EVENT_CASE(ev) case ev : {return weve::b##ev;}
        switch constexpr (e){
            EVMACRO_ALL(EVENT_CASE)
        }
    };

    
    auto weve::* get(weve& f){
        switch constexpr(e){
            #define GETEV_PTR(event) case e::b##event : {return &f.event_;}}} 
}   
template <typename evft,typename... evfts>
struct wevent {
    wevent_<evft> first;
    wevent<evfts> lasts;
} ;

template <even e,typename weventT>
auto& get(weventT& r){
    if constexpr(memberis<e,decltype(wevenT::first)>::Boolean){return *memberis<e,wevenT>::get(r.first)}
    return get<e,decltype<weventT::lasts>>(r.lasts);
};
template <even e>
size_t wevent_size(wevent& r){
    return 1 + wevent_size(r.lasts);
} 






};




