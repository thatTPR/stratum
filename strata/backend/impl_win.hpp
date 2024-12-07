#include <strata/backend/impl.hpp>
#include <Windows.h>
#ifdef STA_IMPL_VK
#define VK_USE_PLATFORM_WIN32_KHR
#include <vk/vulkan.h>
#endif
#ifdef STA_IMPL_DX
#ifdef D3D12
#include <d3d12.h>
#elifdef D3D11
#include <d3d11.h>
#endif
#include <dxgi.h>
#endif
namespace win_events {
    using events::event;
    using events::event_filter;
    class MOUSE                   :public events::MOUSE                   { 
        virtual void init();
    };         
    class KEY                     :public events::KEY                     {
        virtual void init();
    };
    class JOY                     :public events::JOY                     {
    virtual void init();
    }
    class CONTROLLER              :public events::CONTROLLER              {
    virtual void init();
    }              
    class TOUCH                   :public events::TOUCH                   { }         

    class SYS : public events::SYS{
        /*   
using OVERLAPPED= WS_OVERLAPPED; 
using POPUP= WS_POPUP; 
using CHILD= WS_CHILD; 
using MINIMIZE= WS_MINIMIZE; 
using VISIBLE= WS_VISIBLE; 
using DISABLED= WS_DISABLED; 
using CLIPSIBLINGS= WS_CLIPSIBLINGS; 
using CLIPCHILDREN= WS_CLIPCHILDREN; 
using MAXIMIZE= WS_MAXIMIZE; 
using CAPTION= WS_CAPTION; 
using BORDER= WS_BORDER; 
using DLGFRAME= WS_DLGFRAME; 
using VSCROLL= WS_VSCROLL; 
using HSCROLL= WS_HSCROLL; 
using SYSMENU= WS_SYSMENU; 
using THICKFRAME= WS_THICKFRAME; 
using GROUP= WS_GROUP; 
using TABSTOP= WS_TABSTOP; 
using MINIMIZEBOX= WS_MINIMIZEBOX; 
using MAXIMIZEBOX= WS_MAXIMIZEBOX; 
using TILED= WS_TILED; 
using ICONIC= WS_ICONIC; 
using SIZEBOX= WS_SIZEBOX; 
using TILEDWINDOW= WS_TILEDWINDOW; 

 using OVERLAPPEDWINDOW =(OVERLAPPED | CAPTION | SYSMENU | THICKFRAME | MINIMIZEBOX | MAXIMIZEBOX)
 using POPUPWINDOW =(POPUP | BORDER | SYSMENU)
 using CHILDWINDOW =(CHILD)

using DLGMODALFRAME = WS_EX_DLGMODALFRAME ;  
using NOPARENTNOTIFY = WS_EX_NOPARENTNOTIFY ;  
using TOPMOST = WS_EX_TOPMOST ;  
using ACCEPTFILES = WS_EX_ACCEPTFILES ;  
using TRANSPARENT = WS_EX_TRANSPARENT ;  
using MDICHILD = WS_EX_MDICHILD ;  
using TOOLWINDOW = WS_EX_TOOLWINDOW ;  
using WINDOWEDGE = WS_EX_WINDOWEDGE ;  
using CLIENTEDGE = WS_EX_CLIENTEDGE ;  
using CONTEXTHELP = WS_EX_CONTEXTHELP ;  
using RIGHT = WS_EX_RIGHT ;  
using LEFT = WS_EX_LEFT ;  
using RTLREADING = WS_EX_RTLREADING ;  
using LTRREADING = WS_EX_LTRREADING ;  
using LEFTSCROLLBAR = WS_EX_LEFTSCROLLBAR ;  
using RIGHTSCROLLBAR = WS_EX_RIGHTSCROLLBAR ;  
using CONTROLPARENT = WS_EX_CONTROLPARENT ;  
using STATICEDGE = WS_EX_STATICEDGE ;  
using APPWINDOW = WS_EX_APPWINDOW ;  */

    using MIN = strate_env::MIN; 
    using MAX = strate_env::MAX; 
    using HIDE = strate_env::HIDE; 
    using NORMAL = strate_env::NORMAL;
    vect<HWND> wins ;
    void init(){

    };
    HWND create_win (ivec2 size,ivec2 pos,HWND parent=NULL,bool tool=false,bool custom_tabbar=true, bool resizable=true,bool transparent=false,bool always_on_top=true,std::string CLASS_NAME=NULL ,std::string text=NULL) override {
        DWORD style = (transparent?WS_EX_TRANSPARENT:0) | (always_on_top?WS_EX_TOPMOST:0)|  (tool?WS_EX_TOOLWINDOW:0) | (custom_tabbar?0:WS_CAPTION) ; 
        HWND winh = CreateWindowEx(
            style,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            text,    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            pox[0]!=0?pos[0]:CW_USEDEFAULT, pos[1]!=0?pos[1]:CW_USEDEFAULT,size[0]!=0?size[1]:CW_USEDEFAULT, size[0]!=0?size[1]:CW_USEDEFAULT,

            parent,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );
        this->wins.push(winh);
        return winh;
    };
     ivec2 get_pos(hwnd w){WINDOWPLACEMENT wp={ sizeof(WINDOWPLACEMENT) };GetWindowPlacement(w,&wp);ivec2 s ; s[0] =wp.rcNormalPosition.left;s[1] =wp.rcNormalPosition.top;};
     ivec2 get_size(hwnd w){WINDOWPLACEMENT wp={ sizeof(WINDOWPLACEMENT) };GetWindowPlacement(w,&wp);ivec2 s ; s[0] =wp.rcNormalPosition.right-wp.rcNormalPosition.left;s[1] =wp.rcNormalPosition.top -wp.rcNormalPosition.bottom; return s;};
     ivec4 get_all(hwnd w){WINDOWPLACEMENT wp={ sizeof(WINDOWPLACEMENT) };GetWindowPlacement(w,&wp);ivec4 s ;s[0] =wp.rcNormalPosition.left;s[1] =wp.rcNormalPosition.top; s[2] =wp.rcNormalPosition.right-wp.rcNormalPosition.left;s[3] =wp.rcNormalPosition.top -wp.rcNormalPosition.bottom;return s;};
     ivec2 get_window(){}
     void resize_win(HWND w,ivec2 addpos){ ivec4 s = get_all(); BOOL MoveWindow(w,s[0],s[1],s[2]+addsize[0],s[3]+addsize[1],false); };
     void move_win(HWND w,ivec2 addsize){ivec4 s = get_all(); BOOL MoveWindow(w,s[0]+addpos[0],s[1]+addpos[1],s[2],s[3],false); };
     bool is_min(HWND w){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd&(SW_MINIMIZE |SW_SHOWMINIMIZED))?true:false;};
     bool is_hidden(HWND w){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd==SW_HIDE)?true:false;};
     bool is_normal(HWND w){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd&(SW_RESTORE|SW_SHOW)?true:false;};
     bool is_max(HWND w){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd&SW_SHOWMAXIMIZED)?true:false;};
     bool setWindow(HWND w, vec4 pos_w_h, int state){
    WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT);
     wp.rcNormaplPosition.left=pos_w_h[0]; wp.rcNormaplPosition.top=pos_w_h[1];
     wp.rcNormaplPosition.right=pos_w_h[2];wp.rcNormaplPosition.bottom=pos_w_h[3];
     wp.showCmd =  ((state&MIN)?SW_SHOWMINIMIZED:0)|((state&MAX)?SW_SHOWMAXIMIZED:0)|((state&HIDDEN)?SW_HIDE:0)|((state&NORMAL)?SW_SHOW:0);
    return  SetWindowPlacement(w,const WINDOWPLACEMENT *wp);
    };
    void sleep(int mstime=2000){Sleep(mstime);}

};

class win_env : public strata_env<HMODULE,HINSTANCE>{
 
    public:
    
    void init(int flags){

    };
    void initVk(HWND win, VkInstance inst, VKSurfaceKHR* surface, HINSTANCE hInstance=GetModuleHandle(NULL)){ 
        #ifdef STA_IMPL_VK
    VkWin32SurfaceCreateInfoKHR info;
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.hinstance = hInstance;
    info.hwnd = win;
         if (vkCreateWin32SurfaceKHR(vkInstance, &info, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan surface.");
    }
        #endif
    };
     void initDx(){
        #ifdef STA_IMPL_DX
    };

     void load_shared(fs::path p){HMODULE LoadLibrary(p.name(););};
    
    template <typename func>
    func get_func(const char* funcname; HMODULE m){return (func)GetProcAddress(m,name); };
    void unload_shared(HMODULE m){FreeLibrary(m);};
};



