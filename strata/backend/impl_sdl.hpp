#pragma once
#include "impl.hpp"
#include "SDL2/SDL.h"
void SGUIloadWidget();
void SGUIDrawWidget();



SDL_AddEventWatch
SDL_EventEnabled
SDL_FilterEvents
SDL_FlushEvent
SDL_FlushEvents
SDL_GetEventFilter
SDL_GetWindowFromEvent
SDL_HasEvent
SDL_HasEvents
SDL_PeepEvents
SDL_PollEvent
SDL_PumpEvents
SDL_PushEvent
SDL_RegisterEvents
SDL_RemoveEventWatch
SDL_SetEventEnabled
SDL_SetEventFilter
SDL_WaitEvent
SDL_WaitEventTimeout
//Datatypes
SDL_EventFilter
// Structs
SDL_AudioDeviceEvent
SDL_CameraDeviceEvent
SDL_ClipboardEvent
SDL_CommonEvent
SDL_DisplayEvent
SDL_DropEvent
SDL_Event
SDL_GamepadAxisEvent
SDL_GamepadButtonEvent
SDL_GamepadDeviceEvent
SDL_GamepadSensorEvent
SDL_GamepadTouchpadEvent
SDL_JoyAxisEvent
SDL_JoyBallEvent
SDL_JoyBatteryEvent
SDL_JoyButtonEvent
SDL_JoyDeviceEvent
SDL_JoyHatEvent
SDL_KeyboardDeviceEvent
SDL_KeyboardEvent
SDL_MouseButtonEvent
SDL_MouseDeviceEvent
SDL_MouseMotionEvent
SDL_MouseWheelEvent
SDL_PenAxisEvent
SDL_PenButtonEvent
SDL_PenMotionEvent
SDL_PenProximityEvent
SDL_PenTouchEvent
SDL_QuitEvent
SDL_SensorEvent
SDL_TextEditingCandidatesEvent
SDL_TextEditingEvent
SDL_TextInputEvent
SDL_TouchFingerEvent
SDL_UserEvent
SDL_WindowEvent




using sgui_sdl_vk = sgui<sgui_sdl,sgui_sdl_vk> ;
using sgui_sdl_sdl = sgui<sgui_sdl,sgui_sdl_sdl>;

namespace SDL_events {
    class event : public events::event {
        
    }
class click: public events::click , SDL_MouseButtonEvent {
    void get(){
        
    }
};
class mousedown: public events::mousedown , SDL_MouseButtonEvent{

};
class mouseup: public events::mouseup , SDL_MouseButtonEvent{

};
class mouse_move: public events::mouse_move , SDL_MouseMotionEvent{

};
class mouse_wheel: public events::mouse_wheel, SDL_MouseWheelEvent {

};
class MOUSE: public events::event{
    virtual void get_mouse_state(){
        SDL_GetMouseState()
    };
    virtual window get_mouse_focus(){
        return window::get(SDL_GetMouseFocus());
    };
    void handle(){

    }; 
};
class keyup: public events::keyup{

};
class keydown: public events::event{

};
class keypress: public events::event{

};
class KEY: public events::event{

};
class joy_axis: public events::event{

};
class joy_up: public events::event{

};
class joy_down: public events::event{

};
class joy_press: public events::event{

};
class controller_button_press: public events::event{

};
class controller_button_down: public events::event{

};
class controller_button_up: public events::event{

};
class controller_axis: public events::event{

};
class CONTROLLER: public events::event{

};
class ev_filter : public SDL_EventFilter{

};
class events_main : public events::events_main{
    virtual void get_time (int* ms) override ;
    virtual event* poll_event() override {
        SDL_Event* ev;
        SDL_PollEvent(ev);
        return event(ev);
    };
    virtual void push_event(event* ev){
        SDL_PushEvent(ev.get_ptr();)
    };  
    SDL_PushEvent
    SDL_PeepEvents
    SDL_PumpEvents
    
SDL_AddEventWatch
SDL_EventEnabled
SDL_FilterEvents
SDL_FlushEvent
SDL_FlushEvents
SDL_GetEventFilter
SDL_GetWindowFromEvent
SDL_HasEvent
SDL_HasEvents
SDL_RegisterEvents
SDL_RemoveEventWatch
SDL_SetEventEnabled
SDL_SetEventFilter
SDL_WaitEvent
SDL_WaitEventTimeout
//Datatypes
};  

}