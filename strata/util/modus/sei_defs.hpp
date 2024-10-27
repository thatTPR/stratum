#ifdef FP_ALL 
#define FP_LOOP_ALL
#define FP_CONTROL_ALL
#define FP_EVENT_ALL
#endif

#ifdef APP_BAS
#endif

#ifdef APP_ADV
#define EVENT_ALL
#define JOBSYS_ALL
#define SETTINGS_ALL
#define FULLSCREEN_WINDOWBAR 
#define MENUBAR_OPTIONS
#endif
#ifdef GAME_BAS

#endif

#ifdef GAME_ADV

#endif



/*   FLAG TYPES :
SETTINGS Shortcuts, Combos , Chords , Key, mouse , hoy, controller , touch,  Gesture , THREADING
Threaded Modes: SINGLE_THREADED, GAME_SIM ,   
FP : Controlls , Events , loops
Loops : GameLoop , Tick , 
*/ 
// Perhaps special loop for 
#define LOOP_ALL
#ifdef LOOP_ALL
#define GAME_LOOP
#define RENDER_LOOP
#define RESAQ_LOOP
#define EVENT_LOOP
#endif

#ifdef JOBSYS_ALL
#define THREAD_ALL
#define ASYNC_ALL
#endif

#ifdef JOBSYS_GAME
#define THREAD_GAME
#define ASYNC_GAME 
#endif
#ifdef JOBSYS_RENDER
#define THREAD_RENDER
#define ASYNC_RENDER
#endif
#ifdef JOBSYS_RESAQ
#define THREAD_RESAQ
#define ASYNC_RESAQ
#endif
#ifdef JOBSYS_EVENT
#define THREAD_EVENT
#define ASYNC_EVENT
#endif

#ifdef THREAD_ALL
#define THREAD_GAME // Game simulation
#define THREAD_RENDER // Rendering logic
#define THREAD_RESAQ // Resource acquisition
#define THREAD_EVENT // Programmer defined Event system
#endif

#ifdef ASYNC_ALL // Executed with async
#define GAME_ASYNC
#define RENDER_ASYNC
#define COMPUTE_ASYNC
#define RESAQ_ASYNC
#define EVENT_ASYNC
#endif

#ifdef FP_LOOP_ALL
#define FP_GAME_LOOP
#define FP_RENDER_LOOP
#define FP_RESAQ_LOOP
#define FP_EVENT_LOOP
#endif

#ifdef SETTINGS_ALL
#define KEY_SHORTCUTS
#define KEY_CHORDS // Shortcut combos
#define KEY_SETTINGS
#define MOUSE_SETTINGS
#define JOY_SETTINGS
#define CONTROLLER_SETTINGS
#define TOUCH_SETTINGS
#define GESTURE_SETTINGS
#define AUDIO_SETTINGS
#define VIDEO_SETTINGS
#endif

#ifdef KEY_SHORTCUTS
#define SETTINGS_ANY
#ifdef KEY_CHORDS
#define SETTINGS_ANY
#ifdef KEY_SETTINGS
#define SETTINGS_ANY
#ifdef MOUSE_SETTINGS
#define SETTINGS_ANY
#ifdef JOY_SETTINGS
#define SETTINGS_ANY
#ifdef CONTROLLER_SETTINGS
#define SETTINGS_ANY
#ifdef TOUCH_SETTINGS
#define SETTINGS_ANY
#ifdef GESTURE_SETTINGS
#define SETTINGS_ANY
#ifdef AUDIO_SETTINGS
#define SETTINGS_ANY
#ifdef VIDEO_SETTINGS
#define SETTINGS_ANY

#ifdef WINDOWS_ALL
#define MUL_WINDOWS
#define MUL_WINDOWS_DISPLAY_ASK
#endif
// SDL Event macros
#ifdef EVENT_ALL
#define APP_EVENT
#define DISPLAY_EVENT
#define WINDOW_EVENT
#define KEY_EVENT
#define MOUSE_EVENT
#define JOY_STICK_EVENT
#define CONTROLLER_EVENT
#define TOUCH_EVENT
#define GESTURE_EVENT
#define CLIPBOARD_EVENT
#define DROP_EVENT
#define AUDIO_EVENT
#define SENSOR_EVENT
#define RENDER_EVENT
#define POLL_SENTINEL_EVENT
#define USEREVENT
#endif

#ifdef CONTROL_ALL
#define CONTROL_MOUSE_KEYBOARD
#define CONTROL_JOYSTICK
#define CONTROL_CONTROLLER
#define CONTROL_TOUCH
#endif


#ifdef VK_ALL
#define VK_DYN_SHALD // Dyn shader load
#define VK_DYN_RESAQ // Resource aquire
#define VK_VAL_LYR // validation layers
#define VK_DBG_MES // debug messages
#endif

#ifdef VR_ALL
#define VR_HEADSET
#define VR_CONTROLLERS
#endif


