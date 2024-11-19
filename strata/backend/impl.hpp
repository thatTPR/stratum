#pragma once

#ifdef SIMPL_LINUX
#include "impl_linux.hpp"
#else
#ifdef SIMPL_WINDOWS
#include "impl_win.hpp"
#else
#ifdef SIMPL_ANDROID
#include "impl_android.hpp"
#endif
#ifdef SIMPL_VK
#include "impl_vk.hpp"
#else
#ifdef SIML_DX
#include "impl_dx.hpp"
#else
#ifdef SIMPL_GL
#include "impl_gl.hpp"
#endif


// Scope : 
// gpu Platform info
// cpu Platform info  
// window  
// power management
// input events

// GPU info
// bool hasThing();
// CPU info

// Window
s_init();
s_create_window();
s_del_window