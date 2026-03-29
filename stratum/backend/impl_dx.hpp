#if !defined(D3D12) && !defined(D3D11)
#define D3D11 

#ifdef D3D12
#include <d3d12.h>
#include 
#elifdef D3D11
#include <d3d11.h>
#include <dxgi.h>
#endif

