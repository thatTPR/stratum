#ifndef SGUI_INTERNAL
#define SGUI_INTERNAL
#include <stratum/backend/impl.hpp>
#include <freetype.h>
#include "sgui_widgets.hpp"
#include <functional>
#include <petri/macros.hpp>
// events modeled after svg events
#include <type_traits>
namespace sgui{
    #define EVMACRO_ALL abort,activate,begin,cancel,canplay,canplaythrough,change,click,close,cuechange,dblclick,drag,dragend,dragenter,dragleave,dragover,dragstart,drop,durationchange,emptied,end,ended,error,focus,focusin,focusout,input,invalid,keydown,keypress,keyup,load,loadeddata,loadedmetadata,loadstart,mousedown,mouseenter,mouseleave,mousemove,mouseout,mouseover,mouseup,mousewheel,pause,play,playing,progress,ratechange,repeat,reset,resize,scroll,seeked,seeking,select,show,stalled,submit,suspend,timeupdate,toggle,unload,volumechange,waiting

enum even {
    #define SGUIEVEN(ev) _ev_##ev,

    REPEAT(SGUIEVEN,EVMACRO_ALL)

    reserved
}

template <even en,typename func>
struct ev {
    const even e = en;
    using evt = func;
    // func ptr;
    void operator()(){ptr();}
    void operator=(func){ptr=func;}
}
using ev_abort =ev<even::_ev_abort, std::function<void()> >;
using ev_activate =ev<even::_ev_activate, std::function<void()>>;
using ev_begin =ev<even::_ev_begin, std::function<void()>>;
using ev_cancel =ev<even::_ev_cancel, std::function<void()>>;
using ev_canplay =ev<even::_ev_canplay, std::function<void()>>;
using ev_canplaythrough =ev<even::_ev_canplaythrough, std::function<void()>>;
using ev_change =ev<even::_ev_change, std::function<void()>>;
using ev_click =ev<even::_ev_click, std::function<void(click)>>;
using ev_close =ev<even::_ev_close, std::function<void()>>;
using ev_cuechange =ev<even::_ev_cuechange, std::function<void()>>;
using ev_dblclick =ev<even::_ev_dblclick, std::function<void(click)>>;
using ev_drag =ev<even::_ev_drag, std::function<void()>>;
using ev_dragend =ev<even::_ev_dragend, std::function<void()>>;
using ev_dragenter =ev<even::_ev_dragenter, std::function<void()>>;
using ev_dragleave =ev<even::_ev_dragleave, std::function<void()>>;
using ev_dragover =ev<even::_ev_dragover, std::function<void()>>;
using ev_dragstart =ev<even::_ev_dragstart, std::function<void()>>;
using ev_drop =ev<even::_ev_drop, std::function<void()>>;
using ev_durationchange =ev<even::_ev_durationchange, std::function<void()>>;
using ev_emptied =ev<even::_ev_emptied, std::function<void()>>;
using ev_end =ev<even::_ev_end, std::function<void()>>;
using ev_ended =ev<even::_ev_ended, std::function<void()>>;
using ev_error =ev<even::_ev_error, std::function<void(uint32_t)>>;
using ev_focus =ev<even::_ev_focus, std::function<void()>>;
using ev_focusin =ev<even::_ev_focusin, std::function<void()>>;
using ev_focusout =ev<even::_ev_focusout, std::function<void()>>;
using ev_input =ev<even::_ev_input, std::function<void()>>;
using ev_invalid =ev<even::_ev_invalid, std::function<void()>>;
using ev_keydown =ev<even::_ev_keydown, std::function<void(keydown)>>;
using ev_keypress =ev<even::_ev_keypress, std::function<void(keypress)>>;
using ev_keyup =ev<even::_ev_keyup, std::function<void(int)>>;
using ev_load =ev<even::_ev_load, std::function<void()>>;
using ev_loadeddata =ev<even::_ev_loadeddata, std::function<void()>>;
using ev_loadedmetadata =ev<even::_ev_loadedmetadata, std::function<void()>>;
using ev_loadstart =ev<even::_ev_loadstart, std::function<void()>>;
using ev_mousedown =ev<even::_ev_mousedown, std::function<void(mousedown)>>;
using ev_mouseenter =ev<even::_ev_mouseenter, std::function<void()>>;
using ev_mouseleave =ev<even::_ev_mouseleave, std::function<void()>>;
using ev_mousemove =ev<even::_ev_mousemove, std::function<void()>>;
using ev_mouseout =ev<even::_ev_mouseout, std::function<void()>>;
using ev_mouseover =ev<even::_ev_mouseover, std::function<void()>>;
using ev_mouseup =ev<even::_ev_mouseup, std::function<void()>>;
using ev_mousewheel =ev<even::_ev_mousewheel, std::function<void(mousewheel)>>;
using ev_pause =ev<even::_ev_pause, std::function<void()>>;
using ev_play =ev<even::_ev_play, std::function<void()>>;
using ev_playing =ev<even::_ev_playing, std::function<void()>>;
using ev_progress =ev<even::_ev_progress, std::function<void()>>;
using ev_ratechange =ev<even::_ev_ratechange, std::function<void()>>;
using ev_repeat =ev<even::_ev_repeat, std::function<void()>>;
using ev_reset =ev<even::_ev_reset, std::function<void()>>;
using ev_resize =ev<even::_ev_resize, std::function<void(resize)>>;
using ev_scroll =ev<even::_ev_scroll, std::function<void(int32_t)>>;
using ev_seeked =ev<even::_ev_seeked, std::function<void()>>;
using ev_seeking =ev<even::_ev_seeking, std::function<void()>>;
using ev_select =ev<even::_ev_select, std::function<void()>>;
using ev_show =ev<even::_ev_show, std::function<void()>>;
using ev_stalled =ev<even::_ev_stalled, std::function<void()>>;
using ev_submit =ev<even::_ev_submit, std::function<void()>>;
using ev_suspend =ev<even::_ev_suspend, std::function<void()>>;
using ev_timeupdate =ev<even::_ev_timeupdate, std::function<void()>>;
using ev_toggle =ev<even::_ev_toggle, std::function<void()>>;
using ev_unload =ev<even::_ev_unload, std::function<void()>>;
using ev_volumechange =ev<even::_ev_volumechange, std::function<void(int8_t)>>;
using ev_waiting =ev<even::_ev_waiting, std::function<void()>>;


template <typename evft>
struct weven_ {
    #define WEVENT_MACRO(event) constexpr bool b##event=evft::e==even::_ev_##event ;std::enable_if<b##event,evft::evt>::type event_ ; 
    REPEAT(WEVENT_MACRO,EVMACRO_ALL)
}
template <even e, typename weve>
struct memberis {
    constexpr bool Boolean = [](){
        #define EVENT_CASE(ev) case ev : {return weve::b##ev;}
        switch constexpr (e){
            REPEAT(EVENT_CASE,EVMACRO_ALL)
        }
    };

    
    auto weve::* get(weve& f){
        switch constexpr(e){
            #define GETEV_PTR(event) case e::b##event : {return &f.event_;}
}} 
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




