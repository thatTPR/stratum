#include <sei.hpp>


class VulkanApp_FP : VulkanApp {
    
#ifdef APP_EVENT
    bool (*_AppEvent)(SDL_Event *);
    void (*_QUIT)(SDL_QuitEvent *);
    void (*_APP_TERMINATING)();
    void (*_APP_LOWMEMORY)();
    void (*_APP_WILLENTERBACKGROUND)();
    void (*_APP_DIDENTERBACKGROUND)();
    void (*_APP_WILLENTERFOREGROUND)();
    void (*_APP_DIDENTERFOREGROUND)();
    void (*_LOCALECHANGED)();
    void _quit(SDL_QuitEvent *qevent) { this->cleanup() ; }
    void _app_terminating() { exit(EXIT_SUCCESS); }
    void _app_lowmemory(void){};
    void _app_willenterbackground() { return ; /*this->will_sleep();*/ };
    void _app_didenterbackground(){this->sleep();} ;
    void _app_willenterforeground(){this->will_wake() ;} ;
    void _app_didenterforeground() {  return ; /*this->will_wake();*/ };
    void _localechanged(){return ;} 
    bool SDL_AppEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case SDL_QUIT: //           = 0x100, /**< User-requested quit */
        {
            this->_QUIT(event->quit);
            return true;
        };
            /* These application events have special meaning on iOS, see README-ios.md for details */
        case SDL_APP_TERMINATING, /**< The application is being terminated by the OS
                          Called on iOS in applicationWillTerminate()
                          Called on Android in onDestroy()
                     */
        {
            this->_APP_TERMINATING();
          return true;
        };
            case SDL_APP_LOWMEMORY: /**< The application is low on memory, free memory if possible.
                           Called on iOS in applicationDidReceiveMemoryWarning()
                           Called on Android in onLowMemory()
                      */
        {
            this->_APP_LOWMEMORY();
            return true;
        }
        case SDL_APP_WILLENTERBACKGROUND: /**< The application is about to enter the background
                                Called on iOS in applicationWillResignActive()
                                Called on Android in onPause()
                           */
        {
            this->_APP_WILLENTERBACKGROUND();
            return true;
        };
        case SDL_APP_DIDENTERBACKGROUND: /**< The application did enter the background and may not get CPU for some time
                                Called on iOS in applicationDidEnterBackground()
                                Called on Android in onPause()
                           */
        {
            this->_APP_DIDENTERBACKGROUND();
            return true;
        }
        case SDL_APP_WILLENTERFOREGROUND: /**< The application is about to enter the foreground
                                Called on iOS in applicationWillEnterForeground()
                                Called on Android in onResume()
                           */
        {
            this->_APP_WILLENTERFOREGROUND();
            return true;
        }
        case SDL_APP_DIDENTERFOREGROUND: /**< The application is now interactive
                                Called on iOS in applicationDidBecomeActive()
                                Called on Android in onResume()
                           */
        {
            this->_APP_DIDENTERFOREGROUND();
            return true;
        }
        case SDL_LOCALECHANGED: /**< The user's locale preferences have changed. */
        {
            this->_LOCALECHANGED();
            return true;
        }
        }
    }
    void assignDefaultAppEvents()
    {
        this->AppEvent = &(this->SDL_AppEvent);
        this->_QUIT =&(this->_quit);
        this->_APP_TERMINATING =&(this->_app_terminating);
        this->_APP_LOWMEMORY =&(this->_app_lowmemory);
        this->_APP_WILLENTERBACKGROUND =&(this->_app_willenterbackground);
        this->_APP_DIDENTERBACKGROUND =&(this->_app_didenterbackground);
        this->_APP_WILLENTERFOREGROUND =&(this->_app_willenterforeground);
        this->_APP_DIDENTERFOREGROUND =&(this->_app_didenterforeground);
        this->_LOCALECHANGED =&(this->_localechanged);
    };
#endif
#ifdef DISPLAY_EVENT
    bool (*DisplayEvent)(SDL_Event *);
    void (*_DISPLAYCONNECTED)(SDL_DisplayEvent);
    void (*_DISPLAYDISCONNECTED)(SDL_DisplayEvent);
    void (*_DISPLAYORIENTATION)(SDL_DisplayEvent);
    SDL_DisplayEvent _DISPLAYCONNECTED_FLAG = NULL;
    SDL_DisplayEvent _DISPLAYDISCONNECTED_FLAG = NULL;
    SDL_DisplayEvent _DISPLAYORIENTATION_FLAG = NULL;

#ifdef MUL_WINDOWS
    void organiseWindows(SDL_DisplayEvent event) // TODO
    {
        std::map<int, SDL_Rect> displayMap;
        int num = SDL_GetNumVideoDisplays();
        for (int i = 0; i < num; i++)
        {
            displayMap.insert(std::pair<int, SDLRect>)
        };
        for (SDL_Window *window : this->windows)
        {
        };
    };
#endif
    bool organiseDisplayHandle(SDL_DisplayEvent event)
    {
#ifdef MUL_WINDOWS
#ifdef MUL_WINDOWS_DISPLAY_ASK
        bool show_dialog;
        ImGui::Window
            ImGui::Begin("Display Event", &show_dialog, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text(" Reorganize Secondary Windows? \n Enter for Yes, ESC for No");
        ImGui::Separator();
        if (ImGui::Button("Yes"))
        {
            organiseWindows(event);
            return true;
        };
        ImGui::Separator();
        if (ImGui::Button("No"))
        {
            return true;
        }
        ImGui::End();
#endif
        organiseWindows();
#endif
        return false;
    }
    void _displayconnected(SDL_DisplayEvent ev)
    {
        SDL_Log("A new display with id %d was connected", ev.display);
        if (this->organiseDisplayHandle(ev))
        {
            this->_DISPLAYCONNECTED_FLAG = NULL;
        }
    };
    void _displaydisconnected(SDL_DisplayEvent ev)
    {
        SDL_Log("The display with id %d was disconnected", ev.display);
        if (this->organiseDisplayHandle(ev))
        {
            this->_DISPLAYDISCONNECTED_FLAG = NULL;
        }
    };
    void _displayorientation(SDL_DisplayEvent ev)
    {
        SDL_Log("The orientation of display with id %d was changed", ev.display);
        if (this->organiseDisplayHandle(ev))
        {
            this->_DISPLAYORIENTATION_FLAG = NULL;
        }
    };
    bool SDL_DisplayEvent(SDL_Event *event)
    {
        if (event->type == SDL_DISPLAYEVENT)
        {
            switch (event->display.event)
            {
            case SDL_DISPLAYEVENT_CONNECTED:
                this->_DISPLAYCONNECTED_ARG = event->display;
                this->_DISPLAYCONNECTED(event->display);
                return 1;
            case SDL_DISPLAYEVENT_DISCONNECTED:
                this->_DISPLAYDISCONNECTED(event->display);
                this->_DISPLAYDISCONNECTED_FLAG = event->display;
                return 1;
            case SDL_DISPLAYEVENT_ORIENTATION:
                this->_DISPLAYORIENTATION(event->display);
                this->_DISPLAYORIENTATION_FLAG = event->display;
                return 1;
            }
        }
        if (this->_DISPLAYCONNECTED_ARG != NULL)
        {
            this->_DISPLAYCONNECTED(this->_DISPLAYCONNECTED_ARG)
        };
        if (this->_DISPLAYDISCONNECTED_ARG != NULL)
        {
            this->_DISPLAYDISCONNECTED(this->_DISPLAYDISCONNECTED_ARG)
        };
        if (this->_DISPLAYORIENTATION_ARG != NULL)
        {
            this->_DISPLAYORIENTATION(this->_DISPLAYORIENTATION_ARG)
        };

    };
    void assignDisplayEvent()
    {
        this->DisplayEvent = &(this->SDL_DisplayEvent);
        this->_DISPLAYCONNECTED = &(this->_displayconnected);
        this->_DISPLAYDISCONNECTED = &(this->_displaydisconnected);
        this->_DISPLAYORIENTATION = &(this->_displayorientation);
    }
#endif
#ifdef WINDOW_EVENT
    bool (*WindowEvent)(SDL_Event *);
    void (*_WINDOWEVENT)(SDL_WindowEvent);
    void (*_SYSWMEVENT)(SDL_SysWMEvent);
    void _windowevent(SDL_WindowEvent ev){

    };
    void _syswmevent(SDL_SysWMEvent ev){

    };
    SDL_WindowEvent _WINDOWEVENT_ARG = NULL;
    SDL_SysWMEvent _SYSWMEVENT_ARG = NULL;
    bool SDL_WindowEvent(SDL_Event *event)
    {
        if (event->type == SDL_WINDOW_EVENT)
        {
            switch (event->type)
            {
            case:
                SDL_WINDOWEVENT
                {
                    this->_WINDOWEVENT(event->window);
                    this->_WINDOWEVENT_ARG = this->window;
                    return true;
                } /**< Window state change */
            case:
                SDL_SYSWMEVENT
                {
                    this->_SYSWMEVENT_ARG = this->window;
                    this->_SYSWMEVENT(event->syswm);
                    return true;
                }
            }
        }


        if (this->_WINDOWEVENT_ARG != NULL)
        {
            this->_WINDOWEVENT(this->_WINDOWEVENT_ARG);
        };
        if (this->_SYSWMEVENT_ARG != NULL)
        {
            this->_SYSWMEVENT(this->_SYSWMEVENT_ARG);
        }
    };
    void assignDefaultWindowEvents()
    {
          this->WindowEvent = &(this->SDL_WindowEvent);
        this->_WINDOWEVENT = &(this->_windowevent);
        this->_SYSWMEVENT = &(this->_syswmevent);
    }
#endif
#ifdef KEY_EVENT
// TODO
    bool (*KeyEvent)(SDL_Event *);
    void (*_KEYDOWN)(SDL_KeyboardEvent);
    void (*_KEYUP)(SDL_KeyboardEvent);
    void (*_TEXTEDITING)(SDL_TextEditingEvent);
    void (*_TEXTINPUT)(SDL_TextInputEvent);
    void (*_KEYMAPCHANGED)();
    void (*_TEXTEDITING_EXT)(SDL_TextEditingExtEvent);
    std::vector<SDL_Keysym>  keys ;

    #ifdef KEY_SHORTCUTS

    #ifdef KEY_COMBOS
    bool possibleCombo ; // Set to true if pressed
    std::array<std::map<std::tuple<SDL_Keycode>, void (*action)() >, int>> combos ; 
    #ifdef PLUGINS
     std::array<std::tuple<SDL_Keycode>, int>> getKeyCombosExt(){
        
    };
    #endif
     std::array<std::tuple<SDL_Keycode>, int>> getKeyCombos(){

    }
    void assignKeyCombos(){
        getKeyCombos(){

        };
    }; 
    
    #ifdef KEY_CHORDS // Supports Ctrl+Key , Key Combo type shortcuts
    std::array<std::array<SDL_Keycode>> chordStarts ;
    std::array<std::tuple<std::array<SDL_Keycode>, std::array<SDL_keycode>>>>
    void shortcutChord(){ // 

    };
    #endif
    #endif
    #ifndef KEY_COMBOS
    
    #endif
    #endif


    void _keydown(SDL_KeyboardEvent ev){ // Detect various shortcuts
        if(ev->repeat > 0 ){
    switch(ev->state){
            case: SDL_PRESSED {
                switch(ev->keysym.sym) {

                }
            };
            case: SDL_RELEASED {

            };
        } 
        };
        switch(ev->state){
            case: SDL_PRESSED {
                switch(ev->keysym.sym) {

                }
            };
            case: SDL_RELEASED {

            };
        } 
    };
    void _keyup(SDL_KeyboardEvent ev){

    };
    void _textediting(SDL_TextEditingEvent ev){

    };
    void _textinput(SDL_TextInputEvent ev);
    void _keymapchanged();
    void _textediting_ext(SDL_TextEditingExtEvent ev);
    bool SDL_KeyEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_KEYDOWN
            {
                this->_KEYDOWN(event->key);
                return true;
            }
        case:
            SDL_KEYUP
            {
                this->_KEYUP(event->key);
                return true;
            }
        case:
            SDL_TEXTEDITING
            {
                this->_TEXTEDITING(event->edit);
                return true;
            }
        case:
            SDL_TEXTINPUT
            {
                this->_TEXTINPUT(event->text);
                return true;
            }
        case:
            SDL_KEYMAPCHANGED
            {
                this->_keymapchanged();
                return true;
            }
        case:
            SDL_TEXTEDITING_EXT
            {
                this->_TEXTEDITING_EXT(event->editExt);
                return true;
            }
        };
    };
    void assignDefaultKeyEvents()
    {
        this->KeyEvent = &(this->SDL_KeyEvent);
        this->_KEYDOWN = &(this->&_keydown);
        this->_KEYUP = &(this->&_keyup);
        this->_TEXTEDITING = &(this->&_textediting);
        this->_TEXTINPUT = &(this->&_textinput);
        this->_KEYMAPCHANGED = &(this->&_keymapchanged);
        this->_TEXTEDITING_EXT = &(this->&_textediting_ext);
    };
#endif
#ifdef MOUSE_EVENT
    bool (*MouseEvent)(SDL_Event *);
    void (*_MOUSEMOTION)(SDL_MouseMotionEvent);
    void (*_MOUSEBUTTONDOWN)(SDL_MouseButtonEvent);
    void (*_MOUSEBUTTONUP)(SDL_MouseButtonEvent);
    void (*_MOUSEWHEEL)(SDL_MouseWheelEvent);
    enum MouseState {
#ifdef MOUSE_MOD  
    
#endif
    };
    void _mousemotion(SDL_MouseMotionEvent ev){
        switch(ev->){

        }
        };
    void _mousebuttondown(SDL_MouseButtonEvent ev){};
    void _mousebuttonup(SDL_MouseButtonEvent ev);
    void _mousewheel(SDL_MouseWheelEvent ev);


    getModsExt()

        assignMods()
    {
        getMods()
    }

    bool SDL_MouseEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_MOUSEMOTION
            {
                this->_MOUSEMOTION(event->motion);
                return true;
            }
        case:
            SDL_MOUSEBUTTONDOWN
            {
                this->_MOUSEBUTTONDOWN(event->button);
                return true;
            }
        case:
            SDL_MOUSEBUTTONUP
            {
                this->_MOUSEBUTTONUP(event->button)
                return true;
            }
        case:
            SDL_MOUSEWHEEL
            {
                this->_MOUSEWHEEL(event->wheel);
                return true;
            }
        };
    };
    void assignDefaultMouseEvents()
    {
        this->MouseEvent = this->SDL_MouseEvent;
        this->_MOUSEMOTION = _mousemotion;
        this->_MOUSEBUTTONDOWN = _mousebuttondown;
        this->_MOUSEBUTTONUP = _mousebuttonup;
        this->_MOUSEWHEEL = _mousewheel;
    }
#endif
#ifdef JOY_STICK_EVENT
#ifdef FP_JOY_STICK_EVENT
    bool (*JoyEvent)(SDL_Event *);
    void (*_JOYAXISMOTION)(SDL_JoyAxisEvent);
    void (*_JOYBALLMOTION)(SDL_JoyBallEvent);
    void (*_JOYHATMOTION)(SDL_JoyHatEvent);
    void (*_JOYBUTTONDOWN)(SDL_JoyButtonEvent);
    void (*_JOYBUTTONUP)(SDL_JoyButtonEvent);
    void (*_JOYDEVICEADDED)(SDL_JoyDeviceEvent);
    void (*_JOYDEVICEREMOVED)(SDL_JoyDeviceEvent);
    void (*_JOYBATTERYUPDATED)(SDL_JoyBatteryEvent);
#endif
    void _joyaxismotion(SDL_JoyAxisEvent ev);
    void _joyballmotion(SDL_JoyBallEvent ev);
    void _joyhatmotion(SDL_JoyHatEvent ev);
    void _joybuttondown(SDL_JoyButtonEvent ev);
    void _joybuttonup(SDL_JoyButtonEvent ev);
    void _joydeviceadded(SDL_JoyDeviceEvent ev);
    void _joydeviceremoved(SDL_JoyDeviceEvent ev);
    void _joybatteryupdated(SDL_JoyBatteryEvent ev);
    bool SDL_JoyEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_JOYAXISMOTION
            {
                this->_JOYAXISMOTION(event->jaxis);
            return true;
            } /**< Joystick axis motion */
        case:
            SDL_JOYBALLMOTION
            {
                this->_JOYBALLMOTION(event->jball);
            return true;
            } /**< Joystick trackball motion */
        case:
            SDL_JOYHATMOTION
            {
                this->_JOYHATMOTION(event->jhat);
            return true;
            } /**< Joystick hat position change */
        case:
            SDL_JOYBUTTONDOWN
            {
                this->_JOYBUTTONDOWN(event->jbutton);
            return true;
            } /**< Joystick button pressed */
        case:
            SDL_JOYBUTTONUP
            {
                this->_JOYBUTTONUP(event->jbutton);
            return true;
            } /**< Joystick button released */
        case:
            SDL_JOYDEVICEADDED
            {
                this->_JOYDEVICEADDED(event->jdevice);
            return true;
            } /**< A new joystick has been inserted into the system */
        case:
            SDL_JOYDEVICEREMOVED
            {
                this->_JOYDEVICEREMOVED(event->jdevice);
            return true;
            } /**< An opened joystick has been removed */
        case:
            SDL_JOYBATTERYUPDATED
            {
                this->_JOYBATTERYUPDATED(event->jbattery);
            return true;
            } /**< Joystick battery level change */
        }
        return false;
    };
    void assignDefaultJoyEvents()
    {
        this->JoyEvent = this->SDL_JoyEvent;
        _JOYAXISMOTION = _joyaxismotion;
        _JOYBALLMOTION = _joyballmotion;
        _JOYHATMOTION = _joyhatmotion;
        _JOYBUTTONDOWN = _joybuttondown;
        _JOYBUTTONUP = _joybuttonup;
        _JOYDEVICEADDED = _joydeviceadded;
        _JOYDEVICEREMOVED = _joydeviceremoved;
        _JOYBATTERYUPDATED = _joybatteryupdated;
    }
#endif
#ifdef CONTROLLER_EVENT
#ifdef FP_CONTROLLER_EVENT
    bool (*ControllerEvent)(SDL_Event *);
    void (*_CONTROLLERAXISMOTION)(SDL_ContorllerAxisEvent);
    void (*_CONTROLLERBUTTONDOWN)(SDL_ControllerButtonEvent);
    void (*_CONTROLLERBUTTONUP)(SDL_ControllerButtonEvent);
    void (*_CONTROLLERDEVICEADDED)(SDL_ControllerDeviceEvent);
    void (*_CONTROLLERDEVICEREMOVED)(SDL_ControllerDeviceEvent);
    void (*_CONTROLLERDEVICEREMAPPED)(SDL_ControllerDeviceEvent);
    void (*_CONTROLLERTOUCHPADDOWN)(SDL_ControllerTouchpadEvent);
    void (*_CONTROLLERTOUCHPADMOTION)(SDL_ControllerTouchpadEvent);
    void (*_CONTROLLERTOUCHPADUP)(SDL_ControllerTouchpadEvent);
    void (*_CONTROLLERSENSORUPDATE)(SDL_ControllerSensorEvent);
#endif
    void _controlleraxismotion(SDL_ContorllerAxisEvent ev);
    void _controllerbuttondown(SDL_ControllerButtonEvent ev);
    void _controllerbuttonup(SDL_ControllerButtonEvent ev);
    void _controllerdeviceadded(SDL_ControllerDeviceEvent ev);
    void _controllerdeviceremoved(SDL_ControllerDeviceEvent ev);
    void _controllerdeviceremapped(SDL_ControllerDeviceEvent ev);
    void _controllertouchpaddown(SDL_ControllerTouchpadEvent ev);
    void _controllertouchpadmotion(SDL_ControllerTouchpadEvent ev);
    void _controllertouchpadup(SDL_ControllerTouchpadEvent ev);
    void _controllersensorupdate(SDL_ControllerSensorEvent ev);
    bool SDL_ControllerEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_CONTROLLERAXISMOTION
            {
                this->_CONTROLLERAXISMOTION(event->caxis);
                return true;
            }
        case:
            SDL_CONTROLLERBUTTONDOWN
            {
                this->_CONTROLLERBUTTONDOWN(event->cbutton);
                return true;
            } /**< Game controller button pressed */
        case:
            SDL_CONTROLLERBUTTONUP
            {
                this->_CONTROLLERBUTTONUP(event->button);
                return true;
            } /**< Game controller button released */
        case:
            SDL_CONTROLLERDEVICEREMAPPED
            {
                this->_CONTROLLERDEVICEREMAPPED(event->device);
                return true;
            } /**< The controller mapping was updated */
        case:
            SDL_CONTROLLERTOUCHPADDOWN
            {
                this->_CONTROLLERTOUCHPADDOWN(event->ctouchpad);
                return true;
            } /**< Game controller touchpad was touched */
        case:
            SDL_CONTROLLERTOUCHPADMOTION
            {
                this->_CONTROLLERTOUCHPADMOTION(event->ctouchpad);
                return true;
            } /**< Game controller touchpad finger was moved */
        case:
            SDL_CONTROLLERTOUCHPADUP
            {
                this->_controlleraxismotion(event->ctouchpad) ;
                return true;
            } /**< Game controller touchpad finger was lifted */
        case:
            SDL_CONTROLLERSENSORUPDATE
            {
                this->_CONTROLLERSENSORUPDATE(event->csensor);
                return true;
            }
        case:
            SDL_CONTROLLERDEVICEADDED
            {
                this->_CONTROLLERDEVICEADDED(event->cdevice)
                return true;
            } /**< A new Game controller has been inserted into the system */
        case:
            SDL_CONTROLLERDEVICEREMOVED
            {
                this->_CONTROLLERDEVICEREMOVED(event->cdevice);
                return true;
            } /**< An opened Game controller has been removed */
        default: 
            return false 

        }
    };
    void assignDefaultControllerEvents()
    {
        this->ControllerEvent = this->SDL_ControllerEvent;
        _CONTROLLERAXISMOTION = _controlleraxismotion;
        _CONTROLLERBUTTONDOWN = _controllerbuttondown;
        _CONTROLLERBUTTONUP = _controllerbuttonup;
        _CONTROLLERDEVICEADDED = _controllerdeviceadded;
        _CONTROLLERDEVICEREMOVED = _controllerdeviceremoved;
        _CONTROLLERDEVICEREMAPPED = _controllerdeviceremapped;
        _CONTROLLERTOUCHPADDOWN = _controllertouchpaddown;
        _CONTROLLERTOUCHPADMOTION = _controllertouchpadmotion;
        _CONTROLLERTOUCHPADUP = _controllertouchpadup;
        _CONTROLLERSENSORUPDATE = _controllersensorupdate;
    }
#endif
#ifdef TOUCH_EVENT
#ifdef FP_TOUCH_EVENT
    bool (*TouchEvent)(SDL_Event *);
    void (*_FINGERDOWN)(SDL_TouchFingerEvent);
    void (*_FINGERUP)(SDL_TouchFingerEvent);
    void (*_FINGERMOTION)(SDL_TouchFingerEvent);
    void _fingerdown(SDL_TouchFingerEvent ev);
    void _fingerup(SDL_TouchFingerEvent ev);
    void _fingermotion(SDL_TouchFingerEvent ev);
    bool SDL_TouchEvent(SDL_Event *event)
    {
            switch (event->type)
            {
            case:
                SDL_FINGERDOWN
                {
                    this->_FINGERDOWN(event->tfinger);
                    return true;
                }
            case:
                SDL_FINGERUP
                {
                   this->_FINGERUP(event->tfinger);
                    return true;
                }
            case:
                SDL_FINGERMOTION
                {
                    this->_FINGERMOTION(event->tfinger);
                    return true;
                }
            default:
                return false ;
            };
       
    }
    void assignDefaultTouchEvents()
    {
        this->TouchEvent = this->SDL_TouchEvent;
        _FINGERDOWN = _fingerdown;
        _FINGERUP = _fingerup;
        _FINGERMOTION = _fingermotion;
    };
#endif
#ifdef GESTURE_EVENT
    bool (*GestureEvent)(SDL_Event *);
    void (*_DOLLARGESTURE)(SDL_DollarGesture);
    void (*_DOLLARRECORD)(SDL_DollarGesture);
    void (*_MULTIGESTURE)(SDL_MultiGestureEvent);
    void _dollargesture(SDL_DollarGesture ev){};
    void _dollarrecord(SDL_DollarGesture ev){};
    void _multigesture(SDL_MultiGestureEvent ev){};
    SDL_DollarGesture _DOLLARGESTURE_ARG = NULL;
    SDL_DollarGesture _DOLLARRECORD_ARG = NULL;
    SDL_MultiGestureEvent _MULTIGESTURE_ARG = NULL;
    bool SDL_GestureEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case SDL_MULTIGESTURE {
            this->_MULTIGESTURE(event->mgesture); return true;
        };
            case:
            SDL_DOLLARGESTURE
            {

                this->_DOLLARGESTURE(event->dgesture);
                return true;
            };
        case:
            SDL_DOLLARRECORD
            {
                this->_DOLLARGESTURE(event->dgesture);
                return true;
            };
        }
        if (this->_DOLLARGESTURE_ARG != NULL)
        {
            this->_DOLLARGESTURE(this->_DOLLARGESTURE_ARG);
        };
        if (this->_DOLLARRECORD_ARG != NULL)
        {
            this->_DOLLARRECORD(this->_DOLLARRECORD_ARG);
        };
        if (this->_MULTIGESTURE_ARG != NULL)
        {
            this->_MULTIGESTURE(this->_MULTIGESTURE_ARG);
        };
    };
    void assignGestureEvent()
    {
        this->GestureEvent = this->SDL_GestureEvent;
        _DOLLARGESTURE = _dollargesture;
        _DOLLARRECORD = _dollarrecord;
        _MULTIGESTURE = _multigesture;
    }
#endif
#ifdef CLIPBOARD_EVENT
    bool (*ClipBoardEvent)(SDL_Event *);
    void (*_CLIPBOARDUPDATE)();
    void _clipboardupdate(){return };
    bool SDL_ClipBoardEvent(SDL_Event *event)
    {
        if (event->type == SDL_CLIPBOARDUPDATE)
        {
            this->_CLIPBARODUPDATE();
            return true;
        };
        return false;
    };
    void assignDefaultClipBoardEvents()
    {
        this->ClipBoardEvent = this->SDL_ClipBoardEvent;
        this->_CLIPBOARDUPDATE = this->_clipboardupdate;
    };
#endif
#ifdef DROP_EVENT
    bool (*DropEvent)(SDL_Event *);
    void (*_DROPFILE)(SDL_DropEvent);
    void (*_DROPTEXT)(SDL_DropEvent);
    void (*_DROPBEGIN)(SDL_DropEvent);
    void (*_DROPCOMPLETE)(SDL_DropEvent);
    void _dropfile(SDL_DropEvent ev){};
    void _droptext(SDL_DropEvent ev){};
    void _dropbegin(SDL_DropEvent ev){};
    void _dropcomplete(SDL_DropEvent ev){};
    bool SDL_DropEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_DROPFILE
            {
                _DROPFILE(event->drop);
                return true;
            }; /**< The system requests a file open */
        case:
            SDL_DROPTEXT
            {
                _DROPTEXT(event->drop);
                return true;

            }; /**< text/plain drag-and-drop event */
        case:
            SDL_DROPBEGIN
            {
                _DROPBEGIN(event->drop);
                return true;
            }; /**< A new set of drops is beginning (NULL filename) */
        case:
            SDL_DROPCOMPLETE
            {
                _DROPCOMPLETE(event->drop);
                return true;
            };
        }
    };
    void assignDropEvent()
    {
        this->DropEvent = this->SDL_DropEvent;
        _DROPFILE = _dropfile;
        _DROPTEXT = _droptext;
        _DROPBEGIN = _dropbegin;
        _DROPCOMPLETE = _dropcomplete;
    };
#endif
#ifdef AUDIO_EVENT
    bool (*AudioEvent)(SDL_Event *);
    void (*_AUDIODEVICEADDED)(SDL_AudioDeviceEvent);
    void (*_AUDIODEVICEREMOVED)(SDL_AudioDeviceEvent);
    void _audiodeviceadded(SDL_AudioDeviceEvent);
    void _audiodeviceremoved(SDL_AudioDeviceEvent);
    SDL_AudioDeviceEvent _AUDIODEVICEADDED_ARG = NULL;
    SDL_AudioDeviceEvent _AUDIODEVICEREMOVED_ARG = NULL;
    bool SDL_AudioEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_AUDIODEVICEADDED
            {
                _AUDIODEVICEADDED(event->adevice);

            }
        case:
            SDL_AUDIODEVICEREMOVED
            {
                _AUDIODEVICEREMOVED(event->adevice);
            }
        }
    };
    void assignAudioEvent()
    {
        this->AudioEvent = this->SDL_AudioEvent;
        _AUDIODEVICEADDED = _audiodeviceadded;
        _AUDIODEVICEREMOVED = _audiodeviceremoved;
    }
#endif
#ifdef SENSOR_EVENT
    bool (*SensorEvent)(SDL_Event *);
    void (*_SENSORUPDATE)(SDL_SensorEvent);
    void _sensorupdate(SDL_SensorEvent ev){};

    bool SDL_SensorEvent(SDL_Event *event)
    {
        if (event->type == SDL_SENSORUPDATE)
        {
            _SENSOR_UPDATE(event->sensor);
            return true;
        }
    };
    void assignSensorEvent()
    {
        this->SensorEvent = this->SDL_SensorEvent;
        this->_SENSORUPDATE = this->_sensorupdate;
    }
#endif
#ifdef RENDER_EVENT
    bool (*RenderEvent)(SDL_Event *);
    void (*_RENDER_TARGETS_RESET)();
    void (*_RENDER_DEVICE_RESET)();
    void _render_targets_reset() {}
    void _render_device_reset(){};
    bool SDL_RenderEvent(SDL_Event *event)
    {
        switch (event->type)
        {
        case:
            SDL_RENDER_TARGETS_RESET
            {
                this->_RENDER_TARGETS_RESET();
                return true;

            } /**< The render targets have been reset and their contents need to be updated */
        case:
            SDL_RENDER_DEVICE_RESET
            {
                this->_RENDER_DEVICE_RESET();
                return true;
            };
        }
        return false ;
    };
    void assignDefaultRenderEvents()
    {
        this->RenderEvent = this->SDL_RenderEvent;
        this->_RENDER_TARGETS_RESET = this->_render_targets_reset;
        this->_RENDER_DEVICE_RESET = this->_render_device_reset;
    }
#endif
#ifdef POLL_SENTINEL_EVENT
    bool (*PollSentinelEvent)(SDL_Event *);
    void (*_POLLSENTIINEL)();
    void _pollsentinel(){     return;   };
    bool SDL_PollSentinelEvent()
    {
        if (event->type == SDL_POLLSENTINEL)
        {
            this->_POLLSENTINELEVENT(t);
            return true;
        }
        return false;
    };
    void assignPollSentinelEvent()
    {
        this->PollSentinelEvent = this->SDL_PollSentinelEvent;
        this->_POLLSENTIINEL = this->_pollsentinel;
    }
        #endif
#endif
    void setEventFunctionPointers(
        bool (*_AppEvent)(SDL_Event *),
        bool (*_DisplayEvent)(SDL_Event *),
        bool (*_WindowEvent)(SDL_Event *),
        bool (*_KeyEvent)(SDL_Event *),
        bool (*_MouseEvent)(SDL_Event *),
        bool (*_JoyStickEvent)(SDL_Event *),
        bool (*_ControllerEvent)(SDL_Event *),
        bool (*_TouchEvent)(SDL_Event *),
        bool (*_GestureEvent)(SDL_Event *),
        bool (*_ClipBoardEvent)(SDL_Event *),
        bool (*_DropEvent)(SDL_Event *),
        bool (*_AudioEvent)(SDL_Event *),
        bool (*_SensorEvent)(SDL_Event *),
        bool (*_RenderEvent)(SDL_Event *),
        bool (*_PollSentinelEvent)(SDL_Event *)
    )
    {
        this->AppEvent = _AppEvent;
        this->DisplayEvent = _DisplayEvent;
        this->WindowEvent = _WindowEvent;
        this->KeyEvent = _KeyEvent;
        this->MouseEvent = _MouseEvent;
        this->JoyStickEvent = _JoyStickEvent;
        this->ControllerEvent = _ControllerEvent ;
        this->TouchEvent = _TouchEvent;
        this->GestureEvent = _GestureEvent;
        this->ClipBoardEvent = _ClipBoardEvent;
        this->DropEvent = _DropEvent;
        this->AudioEvent = _AudioEvent;
        this->SensorEvent = _SensorEvent;
        this->RenderEvent = _RenderEvent;
        this->PollSentinelEvent = _PollSentinelEvent;
    }
    void assignEventFunctionPointers()
    {

        this->assignAppEvent();
        this->assignDisplayEvent();
        this->assignWindowEvent();
        this->assignKeyEvent();
        this->assignMouseEvent();
        this->assignJoyEvent();
        this->assignControllerEvent();
        this->assignTouchEvent();
        this->assignGestureEvent();
        this->assignClipBoardEvent();
        this->assignDropEvent();
        this->assignAudioEvent();
        this->assignSensorEvent();
        this->assignRenderEvent();
        this->assignPollSentinelEvent();
}
#endif

    void setLoopFp(
        void (*_render_loop)() ,
        void (*_game_loop)() ,
        void (*_resaq_loop)(), 
        void (*_events_loop)()
    ){
        this->fp_render_loop = _render_loop ; 
        this->fp_game_loop = _game_loop ; 
        this->fp_resaq_loop = _resaq_loop ;  
        this->fp_events_loop = _events_loop 
    };
    void asignLoopFp(){
        this->fp_render_loop = render_loop ; 
        this->fp_game_loop = game_loop ; 
        this->fp_resaq_loop = resaq_loop ;  
        this->fp_events_loop = events_loop 
    }
#ifdef EVENT_LOOP
void (*fp_event_loop)(event);
#endif
typedef struct event{

}event ;
bool processEvent(event ev) {

};
std::vector<event> events ;
void event_loop(event event){
    #ifdef THREAD_EVENT
    bool quit_event_thread 
    while(quit_event_thread){
    #endif
    for( event i : events){
        #ifdef EVENT_ASYNC
        std::async(std::launch::async, &this->processEvent, i);
        #endif
        #ifndef EVENT_ASYNC
        this->processEvent(i) ;
        #endif
    };
    #ifdef THREAD_EVENT
    };
    #endif
}

void (*fp_resaq_loop)() ;
#ifdef THREAD_RESAQ

bool  quit_resaq_thread = false ;
#endif

inline void load(){ // Function that loads any assets supplied to it to be consumed by another process
    
};
void resaq_loop(){
#ifdef THREAD_RESAQ
    while (!this->quit_resaq_thread){
#endif




#ifdef THREAD_RESAQ
    };
#endif
};
#endif

#ifdef RENDER_LOOP
#ifdef FP_RENDER_LOOP
void (*fp_render_loop)() ; 
#endif
#ifdef THREAD_RENDER
bool quit_render_loop = false ;
#endif
void render_loop(){ 
        
    #ifdef THREAD_RENDER
    while(!this->quit_render_thread)
    #endif
    {

        ImGui::
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
    }
    
}
#endif

#ifdef GAME_LOOP
#ifdef GAME_LOOP_PRIORITY
enum GameLoopPriority
{
#ifdef CONTROL_MOUSE_KEYBOARD
    GAMECONTROLMODE_MOUSE_KEYBAORD = 0,
#endif
#ifdef CONTROL_JOYSTICK //
    GAMECONTROLMODE_JOYSTICK = 1,
#endif
#ifdef CONTROL_CONTROLLER
    GAMECONTROLMODE_CONTROLLER = 2,
#endif
#ifdef CONTROL_TOUCH
    GAMECONTROLMODE_TOUCH = 3
#endif
};
#endif
#ifdef FP_GAME_LOOP
void (*fp_game_loop)();
#endif
bool quit_game_loop = false ; 


void game_loop()  // In this loop all entity updates are handled
{
 #ifdef THREAD_GAME
    while(!this->quit_game_loop){
 #endif
   
 #ifdef THREAD_GAME
    };
#endif
};
#endif

titleBar(){

}
void main_loop() // In this loop all events are handled input or otherwise
{

    // Custom 
#ifdef THREAD_GAME
std::thread game(
#ifdef FP_GAME_LOOP
    fp_game_loop,
#endif
#ifndef FP_GAME_LOOP
    game_loop,    
#endif
    void ) ;
#endif
#ifdef THREAD_EVENT
std::thread render(
    #ifdef FP_EVENT_LOOP
    fp_render_loop,
    #endif
    #ifndef FP_EVENT_LOOP
    render_loop,
    #endif
    void );
#endif
#ifdef THREAD_RESAQ
std::thread render(
    #ifdef FP_RESAQ_LOOP
    fp_render_loop,
    #endif
    #ifndef FP_RESAQ_LOOP
    render_loop,
    #endif
    void );
#endif
#ifdef THREAD_RENDER
std::thread render(
    #ifdef FP_RENDER_LOOP
    fp_render_loop,
    #endif
    #ifndef FP_RENDER_LOOP
    render_loop,
    #endif
    void );
#endif
SDL_Event event;
    bool quit = false;
    bool gui_priority = true; 
    bool gui_active = true ;
    while (SDL_PollEvent(&event) != 0) 
    {
     
        if(gui_active){
            if(ImGui_ImplSDL2_ProcessEvent(&event)){
                continue ;
            };
        }
        if(event < SDL_DISPLAYEVENT ){
            #ifdef APP_EVENT
            #ifdef FP_APP_EVENT
            this->AppEvent(&event);
            #endif
            #ifndef FP_APP_EVENT
            inline this->AppEvent(&event);
            #endif
        }
        else(event < SDL_WINDOWEVENT){
        #ifdef DISPLAY_EVENT
        #ifdef FP_DISPLAY_EVENT
        this->DisplayEvent(&event);
        #endif
        #ifndef FP_DISPLAY_EVENT
        inline this->DisplayEvent(&event);
        #endif
        }
        else(event < SDL_KEYDOWN){
        #ifdef WINDOW_EVENT
        #ifdef FP_WINDOW_EVENT
        this->WindowEvent(&event);
        #endif
        #ifndef FP_WINDOW_EVENT
        inline this->WindowEvent(&event);
        #endif
        }
        else (event < SDL_MOUSEMOTION) {
        #ifdef KEY_EVENT
        #ifdef FP_KEY_EVENT
        this->KeyEvent(&event);
        #endif
        #ifndef FP_KEY_EVENT
        inline this->KeyEvent(&event);
        #endif
        }
        else (event < SDL_JOYAXISMOTION ){
        #ifdef MOUSE_EVENT
        #ifdef FP_MOUSE_EVENT
        this->MouseEvent(&event);
        #endif
        #ifndef FP_MOUSE_EVENT
        inline this->MouseEvent(&event);
        #endif
        } 
        else (event < SDL_CONTROLLERAXISMOTION){
        #ifdef JOY_STICK_EVENT
        #ifdef FP_JOY_STICK_EVENT
        this->JoyEvent(&event);
        #endif
        #ifndef FP_JOY_STICK_EVENT
        inline this->JoyEvent(&event);
        #endif
        }
        else (event < SDL_FINGERDOWN){
        #ifdef CONTROLLER_EVENT
        #ifdef FP_CONTROLLER_EVENT
        this->ControllerEvent(&event);
        #endif
        #ifndef FP_CONTROLLER_EVENT
        inline this->ControllerEvent(&event);
        #endif
        }
        else (event < SDL_DOLLARGESTURE){
        #ifdef TOUCH_EVENT
        #ifdef FP_TOUCH_EVENT
        this->TouchEvent(&event);
        #endif
        #ifndef FP_TOUCH_EVENT
        inline this->TouchEvent(&event);
        #endif
        }
        else (event < SDL_CLIPBOARDUPDATE){
        #ifdef GESTURE_EVENT
        #ifdef FP_GESTURE_EVENT
        this->GestureEvent(&event);
        #endif
        #ifndef FP_GESTURE_EVENT
        inline this->GestureEvent(&event);
        #endif
        }
        else (event < SDL_DROPFILE){
        #ifdef CLIPBOARD_EVENT
        #ifdef FP_CLIPBOARD_EVENT
        this->ClipboardEvent(&event);
        #endif
        #ifndef FP_CLIPBOARD_EVENT
        inline this->ClipboardEvent(&event);
        #endif
        }
        else (event < SDL_AUDIODEVICEADDED){
        #ifdef DROP_EVENT
        #ifdef FP_DROP_EVENT
        this->DropEvent(&event);
        #endif
        #ifndef FP_DROP_EVENT
        inline this->DropEvent(&event);
        #endif
        }
        else (event < SDL_SENSORUPDATE){
        #ifdef AUDIO_EVENT
        #ifdef FP_AUDIO_EVENT
        this->AudioEvent(&event);
        #endif
        #ifndef FP_AUDIO_EVENT
        inline this->AudioEvent(&event);
        #endif
        }
        else (event < SDL_RENDER_TARGETS_RESET) {
        #ifdef SENSOR_EVENT
        #ifdef FP_SENSOR_EVENT
        this->SensorEvent(&event);
        #endif
        #ifndef FP_SENSOR_EVENT
        inline this->SensorEvent(&event);
        #endif
        }
        if(event < SDL_POLLSENTINEL){
        #ifdef RENDER_EVENT
        #ifdef FP_RENDER_EVENT
        this->RenderEvent(&event);
        #endif
        #ifndef FP_RENDER_EVENT
        inline this->RenderEvent(&event);
        #endif
        }
        if(event < SDL_USEREVENT){
        #ifdef POLL_SENTINEL_EVENT
        #ifdef FP_POLL_SENTINEL_EVENT
        this->PollSentinelEvent(&event);
        #endif
        #ifndef FP_POLL_SENTINEL_EVENT
        inline this->PollSentinelEvent(&event);
        #endif
        #endif
        }
#ifndef THREAD_GAME
#ifdef FP_GAME_LOOP
        this->fp_game_loop(&event);
#endif
#ifndef FP_GAME_LOOP
        inline this->game_loop(&event);
#endif
#endif
#ifndef THREAD_RESAQ
#ifdef FP_RESAQ_LOOP
        this->fp_resaq_loop(&event);
#endif
#ifndef FP_RENDER_LOOP
        inline this->resaq_loop(&event);
#endif
#endif
#ifndef THREAD_EVENT
#ifdef FP_EVENT_LOOP
        this->fp_event_loop(&event);
#endif
#ifndef FP_RENDER_LOOP
        inline this->event_loop(&event);
#endif
#endif
#ifndef THREAD_RENDER
#ifdef FP_RENDER_LOOP
        this->fp_render_loop(&event);
#endif
#ifndef FP_RENDER_LOOP
        inline this->render_loop(&event);
#endif
#endif
        if (event.type == SDL_QUIT)
        {
            quit = true;
            continue;
        }
        if (this->SDL_AppEvent(&event))
        {
            continue;
        }
    };
}
   
    VulkanApp(
#ifdef FP_GAME
        void (*game_loop)()
#endif
    )
    {
#ifdef FP_GAME
        this->fp_game_loop = gameLoop;
#endif
    };
    VulkanApp()
    {
        #ifdef FP_GAME
        this->fp_game_loop = &this->game_loop;
        #endif
    };

}

