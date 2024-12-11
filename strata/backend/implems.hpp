
#include "impl.hpp"
#ifdef STA_IMPL_VK
#include "impl_vk.hpp"
using impl = vk_impl;
#endif
#ifdef STA_IML_DX
#define D3D12
#include "impl_dx.hpp"
#endif
#ifdef
#ifdef STA_IMPL_GL
#include "impl_gl.hpp"
#endif