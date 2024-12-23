#include <strata/backend/impl.hpp>
#include <windows.h>
#ifdef STRATA_IMPL_VK
#include <vk/vulkan.h>
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#ifdef STRATA_IMPL_DX
#ifdef D3D12
#include <d3d12.h>
#elifdef D3D11
#include <d3d11.h>
#endif
#include <dxgi.h>
#endif
#ifdef STRATA_IMPL_GL
#include <gl/gl.h>
#endif

namespace win_events {
    // using events::event;
    // using events::event_filter;
    // using events::event_main;
    #ifdef STRATA_CAPABILTY_MOUSE
    class MOUSE                   :public events::MOUSE                   { 
        virtual bool get_state(short int bt){
            return 
        };
        void _handleMulti( WPARAM wParam, LPARAM lParam){
            UINT dataSize;
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dataSize, sizeof(RAWINPUTHEADER));

            if (dataSize > 0) {
                RAWINPUT* raw = (RAWINPUT*)malloc(dataSize);
                int id = get_dev_index(raw->header.hDevice);
                if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, raw, &dataSize, sizeof(RAWINPUTHEADER)) == dataSize) {
                    if (raw->header.dwType == RIM_TYPEMOUSE) {
                        glm::ivec2 s;
                    s.x= (int)raw->data.mouse.lLastX;s.y= (int)raw->data.mouse.lLastY;
                    this->move_cb(mouse_move( s ,id); 
                    RAWMOUSE mouse = raw->data.mouse;
                        if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {int wheel = static_cast<int>(mouse.usButtonData); this->wheel_cb(wheel,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_HWHEEL) {int wheel = static_cast<int>(mouse.usButtonData); this->wheelh_cb(wheel,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {this->down_cb(0,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) {this->up_cb(0,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN){this->down_cb(1,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) {this->up_cb(1,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN){this->down_cb(2,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) {this->up_cb(2,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN){this->down_cb(4,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_BUTTON_4_UP){this->up_cb(4,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) {this->down_cb(5,id);}
                        if (mouse.usButtonFlags & RI_MOUSE_BUTTON_5_UP){this->up_cb(5,id);}
                    int bt=(int)raw->data.mouse.ul;;
                    };
                };
                free(raw);
                return true;
            }; return false;
        };
        bool handleMulti( UINT mMsg, WPARAM wParam, LPARAM lParam ){
            switch (mMsg) {
                case WM_INPUT: {return this->_handleMulti(wParam, lParam) ; }
                return false;
    
        };
        bool handle(UINT mMsg, WPARAM wParam, LPARAM lParam ){
             switch (mMsg) {
              
            return 0;
        };
        case WM_LBUTTONDOWN   :{this->down_cb(mouse_down(0));return;};
        case WM_LBUTTONUP     :{this->up_cb(mouse_up(0));return;}
        case WM_LBUTTONDBLCLK :{this->dbclick_cb(db_click(0));};
        case WM_RBUTTONDOWN   :{this->down_cb(mouse_down(1));return;};
        case WM_RBUTTONUP     :{this->down_cb(mouse_up(1));return;}
        case WM_RBUTTONDBLCLK :{this->dbclick_cb(dbclick(1));return 1};
        case WM_MBUTTONDOWN   :{this->down_cb(mouse_down(3));return 1};
        case WM_MBUTTONUP     :{this->down_cb(mouse_up(3));return 1};
        case WM_MBUTTONDBLCLK :{this->down_cb(dbclick(3));return 1};
        case WM_XBUTTONUP: {
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) {this->up_cb(4);            }
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2) {this->up_cb(5);}
            return;
        };
        case WM_XBUTTONDOWN: {
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) {this->down_cb(4);};
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2) {this->down_cb(5);};
            return;
        };
        
        case WM_MOUSEMOVE: {
            this->move_cb( mouse_move((int)GET_X_LPARAM(lParam),(int)GET_Y_LPARAM(lParam)) );
            return;
        };
       case WM_MOUSEWHEEL: {
            int delta = GET_WHEEL_DELTA_WPARAM(wParam); // Motion delta
            this->wheel_cb( mouse_wheel(delta)); return;};
          case WM_INPUT: {return this->_handleMulti( WPARAM wParam, LPARAM lParam)}
            };
    };
    return -1;
    };
        virtual void _init(){
            
        };
        glm::vec2 Pos()(){
            POINT cursorPos;
            GetCursorPos(&cursorPos); glm::vec2(cursorPos.x,cursorPos.y);
        };
        glm::vec2 WinPos() override{

        };
    };      
    #endif
    #ifdef STRATA_CAPABILTY_KEY   
    class KEY                     :public events::KEY                     {
        virtual void init(){return;};  CALLBACK
        bool handle( UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_KEYDOWN: {int key = (int)wParam;this->down_cb(key);return true;};
        case WM_KEYUP : {int key = (int)wParam; this->up_cb(key);return true;};
        };
        return false;
    };
};
    };
    #endif
    // #include <dinput.h> // TODO maybe
    // #include <xinput.h>
#ifdef STRATA_CAPABILITY_JOY
#include <joystickapi.h>
    class JOY                     :public events::JOY                     {

    virtual void init();
    virtual int num(){this->num=joyGetNumDevs();return this->num;};

  /*  joycap getCap(int index){
  LPJOYCAPS pj;      
        joyGetDevCaps(index,&pj,sizeof(pj))};
*/
     virtual int get_btn_state(int btn=-1 , int index=0;);
    virtual int get_axis_state(int axis=-1 , int index=0;);
    virtual int get_state(int key=-1 , int index=0;);
    virtual int get_hat_state(int hatpos=-1 , int index=0;); // usually 8 starting n;

    void init(HWND hwnd){
        this->num();
      for(int i=0; i <this->num;i++){
      joySetCapture( hwnd,  i,this->period,  true);
      };
    };
    void end(){
        for(int i=0;i<this->num;i++){
            joyReleaseCapture(i);
        };
    };  

    bool handle(){
    for(int i = 0 ;i < this->num;i++){
        if (joyGetPos(JOYSTICKID1, &joyInfo) == JOYERR_NOERROR) {
                           this->axis_cb(glm::ivec2(joyInfo.wXpos,joyInfo.wYpos);
                            for(int j =0 ;j<maxbtn ; j++)
                                if(joyInfo.wButtons &( j<<1 )){
                                    this->press_cb( j ,i);};
                           };};
    };
    
    };
    #endif
    #ifdef STRATA_CAPABILITY_CONT
    #ifndef XINPUT
    #include <Xinput.h>
    #endif
    class CONT                  : public events::CONT {
        void num(){

        };
        void init(){

        };
        bool handle(int index=0){
 XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // Get the state of the controller
    DWORD result = XInputGetState(index, &state);
    if (result == ERROR_SUCCESS) {
        this->trig_cb(CONT_trig( (int)state.Gamepad.bLeftTrigger,(int)state.Gamepad.bRightTrigger) , index);
             WORD buttons = state.Gamepad.wButtons;
             if(buttons & XINPUT_GAMEPAD_DPAD_UP)       {this->dpad_cb(0,index);}
             if(buttons & XINPUT_GAMEPAD_DPAD_DOWN)     {this->dpad_cb(1,index);}
             if(buttons & XINPUT_GAMEPAD_DPAD_LEFT)     {this->dpad_cb(2,index);}
             if(buttons & XINPUT_GAMEPAD_DPAD_RIGHT)    {this->dpad_cb(3,index);}
             if(buttons & XINPUT_GAMEPAD_A)             {this->press_cb(0,index)}
             if(buttons & XINPUT_GAMEPAD_B)             {this->press_cb(1,index)}
             if(buttons & XINPUT_GAMEPAD_X)             {this->press_cb(2,index)}
             if(buttons & XINPUT_GAMEPAD_Y)             {this->press_cb(3,index)}
             if(buttons & XINPUT_GAMEPAD_LEFT_THUMB)    {this->press_sb(4,index)}
             if(buttons & XINPUT_GAMEPAD_RIGHT_THUMB)   {this->press_sb(5,index)}
             if(buttons & XINPUT_GAMEPAD_LEFT_SHOULDER) {this->press_sb(6,index)}
             if(buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER){this->press_sb(7,index)}
             if(buttons & XINPUT_GAMEPAD_START)         {this->press_cb(8,index)}
             if(buttons & XINPUT_GAMEPAD_BACK)          {this->press_cb(9,index)}
        // Read thumbstick positions
         this->laxis_cb(CONT_axis(state.Gamepad.sThumbLX,state.Gamepad.sThumbLY)); 
         this->raxis_cb(CONT_axis(state.Gamepad.sThumbRX,state.Gamepad.sThumbRY)); 
         return true;        
        };
    };
    class TOUCH                   :public events::TOUCH                   {
         
         void init(HWND hwnd){RegisterTouchWindow(hwnd, TWF_WANTPALM);};
         void end(HWND hwnd){UnregisterTouchWindow (hwnd);};
         void handle( UINT uMsg, WPARAM wParam, LPARAM lParam){
         switch (uMsg) {
            case WM_TOUCH: {
            UINT cInputs = LOWORD(wParam);
            TOUCHINPUT touchInputs[10]; // Support up to 10 simultaneous touches

            if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, touchInputs, sizeof(TOUCHINPUT))) {
                for (UINT i = 0; i < cInputs; i++) {
                    TOUCHINPUT ti = touchInputs[i];
                    if (ti.dwFlags & TOUCHEVENTF_DOWN) {
                        down_cb(touch_tap(ti.x,ti.y));
                    } else if (ti.dwFlags & TOUCHEVENTF_UP) {
                        up_cb(touch_tap(ti.x,ti.y));
                    } else if (ti.dwFlags & TOUCHEVENTF_MOVE) {
                        move_cb(touch_tap(ti.x,ti.y));
                    };
                 CloseTouchInputHandle((HTOUCHINPUT)lParam);   
                }
            };

            return 0;
        }
         };
         
     }         
   
    class DISPLAY   : public events::UI {
        bool gotten;
//         typedef struct _DISPLAY_DEVICEW {
//     DWORD  cb;
//     WCHAR  DeviceName[32];
//     WCHAR  DeviceString[128];
//     DWORD  StateFlags;
//     WCHAR  DeviceID[128];
//     WCHAR  DeviceKey[128];
// } DISPLAY_DEVICEW, *PDISPLAY_DEVICEW, *LPDISPLAY_DEVICEW;
    glm::ivec3 get_display_data(uint pos=0)final {
        DISPLAY_DEVICE displayDevice;
        displayDevice.cb = sizeof(DISPLAY_DEVICE);
        glm::ivec3 res;
    // Enumerate the monitor by index
        if (EnumDisplayDevices(NULL, monitorIndex, &displayDevice, 0)) {
        DEVMODE devMode;
        devMode.dmSize = sizeof(DEVMODE);
        // Get the current display settings for this monitor
        if (EnumDisplaySettings(displayDevice.DeviceName, ENUM_CURRENT_SETTINGS, &devMode)) {
             res.x = devMode.dmPelsWidht;
             res.y = devMode.dmPelsHeight;
             res.z=devMode.dmDisplayFrequency ; this->disp[pos] = res; return res;
        } else {
            std::cerr << "  Failed to retrieve display settings." << std::endl;
        }
        } else {
        std::cerr << "Monitor index " << monitorIndex << " is invalid." << std::endl;
    }
        
    }
        glm::ivec3 get_monitor_data(uint pos=0) final {
 MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFOEX);

    if (GetMonitorInfo(hMonitor, &monitorInfo)) {
        // Get device context for the monitor
        HDC hdcMonitor = CreateDC(NULL, monitorInfo.szDevice, NULL, NULL);

        // Get physical width and height in millimeters
        int widthMM = GetDeviceCaps(hdcMonitor, HORZSIZE);
        int heightMM = GetDeviceCaps(hdcMonitor, VERTSIZE);
        int hz = GetDeviceCaps(hdcMonitor,VREFRESH);
        return glm::ivec4(widthMM,heightMM);
        DeleteDC(hdcMonitor);
        this->mon[pos] = glm::ivec3(widthMM,heightMM,hz);
        return this->mon[pos];
    };
    else std::cerr<<"Could not get_monitor_data(uint pos= "<<pos<<")"; 
    delete monitorInfo;
    };
    int Num(){this->num = GetSystemMonitors(SMCMONITORS);};
    void get_all(){
        this->get_num_monitors();
        this->disp.clear();
        this->mon.clear();
        for(uint i =0; i <this->nummon;i++){
            this->get_display_data(i);
            this->get_monitor_data(i);
        };
    };
    void handle();
    bool handle(UINT uMsg, WPARAM wParam, LPARAM lParam){
        switch (uMsg) {
        case WM_DISPLAYCHANGE: {
            this->change_cb(LOWORD(lParam),HIWORD(lParam),(int)wParam);return true;
        };
        case WM_DEVICECHANGE: {
            if (wParam == DBT_DEVICEARRIVAL) {this->conn_cb(0);
            } else if (wParam == DBT_DEVICEREMOVECOMPLETE) {
                this->conn_cb(0,false)
            }
            return true;
        };
        case WM_SETTINGCHANGE: {
            if (lParam) {
                std::wstring settingName(reinterpret_cast<LPCWSTR>(lParam));
                std::wcout << L"System setting changed: " << settingName << std::endl;
            }
            return true;
        };
    };
    
    void init()final{
        this->get_all();
    // Set callback to new monitor
    };
    };

    }
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
    HWND win;
    std::vector<HWND> wins ;
    vect<glm::ivec4> wind;
    vect<int> state; 
    
    LRESULT void handle_win(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
        if (this->wins[this->cur_win_index]!=hwnd){
            for(int i = 0; i< this->wins.size();i++){if(this->wins[this->cur_win_index]==hwnd){this->cur_win_index=i;break};};
        };
        switch (uMsg) {
        case WM_MOVE: {
            int xPos = LOWORD(lParam); // Horizontal position
            int yPos = HIWORD(lParam); // Vertical position
            this->wind[this->cur_win_index][0]=xPos;
            this->wind[this->cur_win_index][1]=yPos;
            this->move_callback();
            break;
        }
        case WM_RESIZE: {
            int width= LOWORD(lParam);
            int height=HIWORD(lParam);
            this->wind[this->cur_win_index][2]=width;
            this->wind[this->cur_win_index][3]=height;
            this->resize_callback();
        break;
        };
        case WM_MINIMIZE : {this->min_callback();break;};
        case WM_MAXIMIZE : {this->max_callback();break;};
        case WM_RESTORE : {this->restore_callback();break;};
        case WM_HIDE :{this->hide_callback();break;};
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    };
    return 0;
    };
    evq<long , MAXPOLL> last;
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT mMsg, WPARAM wParam, LPARAM lParam ){
        // If WM_INPUT(0) then go thorugh rest
#ifdef STRATA_CAPABILTY_MOUSE
if(sMOUSE.handle( mMsg, wParam,  lParam )!=0){this->last.push(2);return 2;};
#endif
#ifdef STRATA_CAPABILTY_KEY
if(s.KEY.handle( mMsg, wParam,  lParam )!=0){this->last.push(3);return 3;};
#endif        
#ifdef STRATA_CAPABILTY_JOY
if(s.JOY.handle()!=0){this->last.push(4);return 4;};
#endif
        #ifdef STRATA_CAPABILTY_CONT
if(s.CONT.handle()!=0){this->last.push(5);return 5;};
#endif
        #ifdef STRATA_CAPABILTY_TOUCH
if(s.TOUCH.handle( mMsg, wParam,  lParam )!=0){this->last.push(6);return 6;};
#endif
        #ifdef STRATA_CAPABILTY_SENSOR
if(s.SENSOR.handle( mMsg, wParam,  lParam )!=0){this->last.push(7);return 7;};
#endif
        #ifdef STRATA_CAPABILTY_AUDIO
if(s.AUDIO.handle( mMsg, wParam,  lParam )!=0){this->last.push(8);return 8;}; 
#endif
if(this->handle_win(hwnd, mMsg, wParam,  lParam)!=0{this->last.push(1) ;return 1;};
    };
    LRESULT CALLBACK KeyProc(HWND hwnd, UINT mMsg, WPARAM wParam, LPARAM lParam ){
        // If WM_INPUT(0) then go thorugh rest
#ifdef STRATA_CAPABILTY_KEY
if(s.KEY.handle( mMsg, wParam,  lParam )!=0){this->last.push(3);return 3;};
#endif        
#ifdef STRATA_CAPABILTY_MOUSE
if(sMOUSE.handle( mMsg, wParam,  lParam )!=0){this->last.push(2);return 2;};
#endif
#ifdef STRATA_CAPABILTY_JOY
if(s.JOY.handle()!=0){this->last.push(4);return 4;};
#endif
        #ifdef STRATA_CAPABILTY_CONT
if(s.CONT.handle()!=0){this->last.push(5);return 5;};
#endif
        #ifdef STRATA_CAPABILTY_TOUCH
if(s.TOUCH.handle( mMsg, wParam,  lParam )!=0){this->last.push(6);return 6;};
#endif
        #ifdef STRATA_CAPABILTY_SENSOR
if(s.SENSOR.handle( mMsg, wParam,  lParam )!=0){this->last.push(7);return 7;};
#endif
        #ifdef STRATA_CAPABILTY_AUDIO
if(s.AUDIO.handle( mMsg, wParam,  lParam )!=0){this->last.push(8);return 8;}; 
#endif
if(this->handle_win(hwnd, mMsg, wParam,  lParam)!=0{this->last.push(1) ;return 1;};
    };

    LRESULT CALLBACK JoyProc(HWND hwnd, UINT mMsg, WPARAM wParam, LPARAM lParam ){
        // If WM_INPUT(0) then go thorugh rest
#ifdef STRATA_CAPABILTY_JOY
if(s.JOY.handle()!=0){this->last.push(4);return 4;};
#endif
#ifdef STRATA_CAPABILTY_KEY
if(s.KEY.handle( mMsg, wParam,  lParam )!=0){this->last.push(3);return 3;};
#endif        
#ifdef STRATA_CAPABILTY_MOUSE
if(sMOUSE.handle( mMsg, wParam,  lParam )!=0){this->last.push(2);return 2;};
#endif
        #ifdef STRATA_CAPABILTY_CONT
if(s.CONT.handle()!=0){this->last.push(5);return 5;};
#endif
        #ifdef STRATA_CAPABILTY_TOUCH
if(s.TOUCH.handle( mMsg, wParam,  lParam )!=0){this->last.push(6);return 6;};
#endif
        #ifdef STRATA_CAPABILTY_SENSOR
if(s.SENSOR.handle( mMsg, wParam,  lParam )!=0){this->last.push(7);return 7;};
#endif
        #ifdef STRATA_CAPABILTY_AUDIO
if(s.AUDIO.handle( mMsg, wParam,  lParam )!=0){this->last.push(8);return 8;}; 
#endif
if(this->handle_win(hwnd, mMsg, wParam,  lParam)!=0{this->last.push(1) ;return 1;};
    };

    LRESULT CALLBACK ContProc(HWND hwnd, UINT mMsg, WPARAM wParam, LPARAM lParam ){
        // If WM_INPUT(0) then go thorugh rest
        #ifdef STRATA_CAPABILTY_CONT
if(s.CONT.handle()!=0){this->last.push(5);return 5;};
#endif
#ifdef STRATA_CAPABILTY_KEY
if(s.KEY.handle( mMsg, wParam,  lParam )!=0){this->last.push(3);return 3;};
#endif        
#ifdef STRATA_CAPABILTY_MOUSE
if(sMOUSE.handle( mMsg, wParam,  lParam )!=0){this->last.push(2);return 2;};
#endif
#ifdef STRATA_CAPABILTY_JOY
if(s.JOY.handle()!=0){this->last.push(4);return 4;};
#endif
        #ifdef STRATA_CAPABILTY_TOUCH
if(s.TOUCH.handle( mMsg, wParam,  lParam )!=0){this->last.push(6);return 6;};
#endif
        #ifdef STRATA_CAPABILTY_SENSOR
if(s.SENSOR.handle( mMsg, wParam,  lParam )!=0){this->last.push(7);return 7;};
#endif
        #ifdef STRATA_CAPABILTY_AUDIO
if(s.AUDIO.handle( mMsg, wParam,  lParam )!=0){this->last.push(8);return 8;}; 
#endif
if(this->handle_win(hwnd, mMsg, wParam,  lParam)!=0{this->last.push(1) ;return 1;};
    };
     LRESULT CALLBACK TouchProc(HWND hwnd, UINT mMsg, WPARAM wParam, LPARAM lParam ){
        // If WM_INPUT(0) then go thorugh rest
        #ifdef STRATA_CAPABILTY_TOUCH
if(s.TOUCH.handle( mMsg, wParam,  lParam )!=0){this->last.push(6);return 6;};
#endif
#ifdef STRATA_CAPABILTY_KEY
if(s.KEY.handle( mMsg, wParam,  lParam )!=0){this->last.push(3);return 3;};
#endif        
#ifdef STRATA_CAPABILTY_MOUSE
if(sMOUSE.handle( mMsg, wParam,  lParam )!=0){this->last.push(2);return 2;};
#endif
#ifdef STRATA_CAPABILTY_JOY
if(s.JOY.handle()!=0){this->last.push(4);return 4;};
#endif
        #ifdef STRATA_CAPABILTY_CONT
if(s.CONT.handle()!=0){this->last.push(5);return 5;};
#endif
        #ifdef STRATA_CAPABILTY_SENSOR
if(s.SENSOR.handle( mMsg, wParam,  lParam )!=0){this->last.push(7);return 7;};
#endif
        #ifdef STRATA_CAPABILTY_AUDIO
if(s.AUDIO.handle( mMsg, wParam,  lParam )!=0){this->last.push(8);return 8;}; 
#endif
if(this->handle_win(hwnd, mMsg, wParam,  lParam)!=0{this->last.push(1) ;return 1;};
    };
   
    MSG msg ;
    bool _handle() 
        while(GetMessage(&(this->msg), nullptr, 0, 0)) {
        TranslateMessage(&(this->msg));
        DispatchMessage(&(this->msg));
    };
    };
    void changeCb(HWND hwnd , LRESULT CALLBACK (*WindowProc)(HWND hwnd, UINT mMsg, WPARAM wParam, LPARAM lParam )){SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc );};
    void changePrMouse(uint pos=0){this->changCb(this->wins[0],this->WindowProc;)};
    void changePrKey(uint pos=0){this->changCb(this->wins[0],this->KeyProc;)};
    void changePrCont(uint pos=0){this->changCb(this->wins[0],this->ContProc;)};
    void changePrJoy(uint pos=0){this->changCb(this->wins[0],this->JoyProc;)};
    void changePrTouch(uint pos=0){this->changCb(this->wins[0],this->TouchProc;)};
    void create_win (glm::ivec2 size,glm::ivec2 pos,HWND parent=NULL,char CLASS_NAME[]="DefaultName" ,std::string text=NULL,int8_t flag) override {
        // Register class

    WNDCLASS wc = {};
    wc.lpfnWndProc = this->handle;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc)) {
        std::cerr << "Failed to register window class!" << std::endl;
        return -1;
    };
        DWORD style = (flag&_transparent?WS_EX_TRANSPARENT:0) | (flag&_always_on_top?WS_EX_TOPMOST:0)|  (flag&_tool?WS_EX_TOOLWINDOW:0) | (flag&_custom_tabbar?0:WS_CAPTION) ; 
        HWND winh = CreateWindowEx(
            style,CLASS_NAME,text,WS_OVERLAPPEDWINDOW,// Size and position
            pox.x!=0?pos.x:CW_USEDEFAULT, pos.y!=0?pos.y:CW_USEDEFAULT,size.x!=0?size.y:CW_USEDEFAULT, size.x!=0?size.y:CW_USEDEFAULT,

            parent,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );
        this->wins.push_back(winh);
        
    };
    
     glm::ivec2 winpos(uint pos){WINDOWPLACEMENT wp={ sizeof(WINDOWPLACEMENT) };GetWindowPlacement(this->wins[pos],&wp); return glm::ivec2(wp.rcNormalPosition.left,wp.rcNormalPosition.top)};
     glm::ivec2 winsize(uint pos){WINDOWPLACEMENT wp={ sizeof(WINDOWPLACEMENT) };GetWindowPlacement(this->wins[pos],&wp);return glm::ivec2(wp.rcNormalPosition.right-wp.rcNormalPosition.left ,wp.rcNormalPosition.top -wp.rcNormalPosition.bottom); };
     glm::ivec4 wininfo(uint pos){WINDOWPLACEMENT wp={ sizeof(WINDOWPLACEMENT) };GetWindowPlacement(this->wins[pos],&wp);this->wind[pos]= glm::ivec4(wp.rcNormalPosition.left,wp.rcNormalPosition.top, wp.rcNormalPosition.right-wp.rcNormalPosition.left ,wp.rcNormalPosition.top -wp.rcNormalPosition.bottom);return this->wind[pos];};
     void winresize(uint pos,glm::ivec2 addpos){ glm::ivec4 s = get_all(); BOOL MoveWindow(this->wins[pos],s.x,s.y,s.z+addsize[0],s.w+addsize[1],false); };
     void winmove(uint pos,glm::ivec2 addsize){glm::ivec4 s = get_all(); BOOL MoveWindow(this->wins[pos],s.x+addpos.x,s.y+addpos.y,s.z,s.w,false); };
     void winminimize(uint pos)final{ChangeWindowState(this->wind[pos], SW_MINIMIZE);};
     void winmaximize{uint pos}final{ChangeWindowState(this->wind[pos], SW_MAXIMIZE);};
     void winrestore{uint pos}final{ChangeWindowState(this->wind[pos], SW_RESTORE);};
     void winhide(uint pos)final{ChangeWIndowState(this->wind[pos],SW_HIDE);};

     bool is_min(uint pos){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd&(SW_MINIMIZE |SW_SHOWMINIMIZED))?true:false;};
     bool is_hidden(uint pos){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd==SW_HIDE)?true:false;};
     bool is_normal(uint pos){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd&(SW_RESTORE|SW_SHOW)?true:false;};
     bool is_max(uint pos){WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT); GetWindowPlacement(w,wp); return (wp.showCmd&SW_SHOWMAXIMIZED)?true:false;};
     bool setWindow(HWND w, vec4 pos_w_h, int state){
    WINDOWPLACEMENT wp=sizeof(WINDOWPLACEMENT);
     wp.rcNormaplPosition.left=pos_w_h[0]; wp.rcNormaplPosition.top=pos_w_h[1];
     wp.rcNormaplPosition.right=pos_w_h[2];wp.rcNormaplPosition.bottom=pos_w_h[3];
     wp.showCmd =  ((state&MIN)?SW_SHOWMINIMIZED:0)|((state&MAX)?SW_SHOWMAXIMIZED:0)|((state&HIDDEN)?SW_HIDE:0)|((state&NORMAL)?SW_SHOW:0);
    return  SetWindowPlacement(w,const WINDOWPLACEMENT *wp);
    };
    void closeWin(HWND hwnd){SendMessage(hwnd, WM_CLOSE, 0, 0);};
    void close_win(uint pos){ SendMessage(this->wins[pos], WM_CLOSE, 0, 0);this->wins.erase(pos);this->wins.shrink_to_fit(); ;};
    void close_app(){for(HWND hwnd : this->wins){this->closeWin(hwnd)}};
    void sleep(int mstime=2000){Sleep(mstime);}
    virtual void _init(){return;}

    
    #ifdef STRATA_IMPL_VK
    void initVk(HWND win, VkInstance inst, VKSurfaceKHR* surface, HINSTANCE hInstance=GetModuleHandle(NULL)){ 
    VkWin32SurfaceCreateInfoKHR info;
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.hinstance = hInstance;
    info.hwnd = win;
         if (vkCreateWin32SurfaceKHR(vkInstance, &info, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan surface.");
    }
    #endif
    };
    #ifdef STRATA_IMPL_DX
     #include 
     void initDx(){

    };
    #endif
    #ifdef STRATA_IMPL_GL
    void initGl(){

    };
    #endif
    void load_shared(fs::path p){HMODULE s= LoadLibrary(p.name(););};
    void unload_shared(HMODULE m){FreeLibrary(m);};
    func get_func(const char* funcname; HMODULE m){return (func)GetProcAddress(m,name); };
// #define WATCH_DIR_TREE true
// // #include <fileapi.h>

//      fswatch(std::wstring dir);
//     void fswatch(std::vector<std::wstring> dirs , std::shared_ptr<std::vector<std::wstring>> changes;){ 
//         std::vector<HANDLE> dirhwnds;
//         for(std::wstring t : dirs){
//             HANDLE  dir = FindFirstChangeNotification(
//             directory.c_str(),
//             WATCH_DIR_TREE ,
//             FILE_NOTIFIY_CHANGE_LAST_WRITE
//     );
//     if (dir == INVALID_HANDLE_VALUE) {std::cerr << "Failed to open fs_watch " << GetLastError() << std::endl;return;}
//             else dirhwnds->push_back(dir);
//         };
        

//     char buffer[1024];
//     DWORD bytesReturned;

//     while (true) {
//         if (ReadDirectoryChangesW(
//                 dir,
//                 buffer,
//                 sizeof(buffer),
//                 TRUE,
//                 FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
//                 FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_SIZE |
//                 FILE_NOTIFY_CHANGE_LAST_WRITE,
//                 &bytesReturned,
//                 nullptr,
//                 nullptr)) {

//             FILE_NOTIFY_INFORMATION* info = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);

//             do {
//                 std::wcout << L"File changed: " << std::wstring(info->FileName, info->FileNameLength / sizeof(wchar_t)) << std::endl;
//                 info = info->NextEntryOffset ? reinterpret_cast<FILE_NOTIFY_INFORMATION*>(
//                         reinterpret_cast<BYTE*>(info) + info->NextEntryOffset) : nullptr;
//             } while (info);
//         }
//     }

    // CloseHandle(dir);
    // };
  

};

    

