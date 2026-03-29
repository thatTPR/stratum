
#ifdef STRATA_IMPL_WIN
#undef STRATA_CAP_SENSOR
#endif
#include <impl.hpp>
// #define MAIN_DEF(ev_m) ev_m main; 
// #define NS_USE(ns) using namespace ns;

// #ifdef STRATA_IMPL_SDL
// #include "impl_sdl.hpp"
// using namespace SDL_events;
// #endif
#ifdef STRATA_IMPL_LINUX
#include "impl_linux.hpp"
using namespace impl_linux;
using env = linux_env;
using evns = linux_events;
#elifdef STRATA_IMPL_WIN
#include "impl_win.hpp"
using namespace impl_win;

#elifdef STRATA_IMPL_ANDROID
#include "impl_android.hpp"
using namespace impl_android;
#elifdef
#endif

