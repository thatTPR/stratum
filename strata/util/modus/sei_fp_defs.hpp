#ifdef FP_CONTROL_ALL
#define FP_KEY_EVENT
#define FP_MOUSE_EVENT
#define FP_JOY_STICK_EVENT
#define FP_CONTROLLER_EVENT
#endif

#ifdef FP_EVENT_ALL
#ifdef APP_EVENT
#define FP_APP_EVENT
#endif
#ifdef DISPLAY_EVENT
#define FP_DISPLAY_EVENT
#endif
#ifdef WINDOW_EVENT
#define FP_WINDOW_EVENT
#endif
#ifdef KEY_EVENT
#define FP_KEY_EVENT
#endif
#ifdef MOUSE_EVENT
#define FP_MOUSE_EVENT
#endif
#ifdef JOY_STICK_EVENT
#define FP_JOY_STICK_EVENT
#endif
#ifdef CONTROLLER_EVENT
#define FP_CONTROLLER_EVENT
#endif
#ifdef TOUCH_EVENT
#define FP_TOUCH_EVENT
#endif
#ifdef GESTURE_EVENT
#define FP_GESTURE_EVENT
#endif
#ifdef CLIPBOARD_EVENT
#define FP_CLIPBOARD_EVENT
#endif
#ifdef DROP_EVENT
#define FP_DROP_EVENT
#endif
#ifdef AUDIO_EVENT
#define FP_AUDIO_EVENT
#endif
#ifdef SENSOR_EVENT
#define FP_SENSOR_EVENT
#endif
#ifdef RENDER_EVENT
#define FP_RENDER_EVENT
#endif
#ifdef POLL_SENTINEL_EVENT
#define FP_POLL_SENTINEL_EVENT
#endif
#endif
// #define FP_KEY_SHORTCUTS 
#ifdef FP_LOOP
#define FP_MAIN_LOOP
#define FP_GAME_LOOP
#define FP_RENDER_LOOP
#endif


#ifdef UN_FP_EVENT_ALL // Undefine all FUNCTION POINTERS
#undef FP_APP_EVENT
#undef FP_DISPLAY_FEVENT
#undef FP_WINDOW_EVENT
#undef FP_KEY_EVENT
#undef FP_MOUSE_EVENT
#undef FP_JOY_STICK_EVENT
#undef FP_CONTROLLER_EVENT
#undef FP_TOUCH_EVENT
#undef FP_GESTURE_EVENT
#undef FP_CLIPBOARD_EVENT
#undef FP_DROP_EVENT
#undef FP_AUDIO_EVENT
#undef FP_SENSOR_EVENT
#undef FP_RENDER_EVENT
#undef FP_POLL_SENTINERL_EVENT

#undef FP_MAIN
#undef FP_GAME_LOOP
#undef FP_TICK
#endif


#ifdef FP_APP_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_DISPLAY_FEVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_WINDOW_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_KEY_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_MOUSE_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_JOY_STICK_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_CONTROLLER_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_TOUCH_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_GESTURE_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_CLIPBOARD_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_DROP_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_AUDIO_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_SENSOR_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_RENDER_EVENT
#define FP_ANY_EVENT
#endif
#ifdef FP_POLL_SENTINERL_EVENT
#define FP_ANY_EVENT
#endif
