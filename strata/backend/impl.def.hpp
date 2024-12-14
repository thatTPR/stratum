    enum evs {

 _DEFAULT=                0,
_click=                  1,
_mousedown=               2,
_mouseup=                 3,
_mousepress=              4,
_mouse_move=              5,
_mouse_wheel=             6,
_mouse_wheelh=            7,
    _MOUSE=                   (_click|_mousedown |_mouseup |_mousepress|_mouse_move |_mouse_wheel),                                 ,
_keyup=                   8,
_keydown=                 9,
_keypress=               10,
    _KEY=                    (_keyup|_keydown|_keypress),
_joy_hat  =              12,
_joy_axis=               13,
_joy_up=                 14,
_joy_down=               15,
_joy_press=              16,
    _JOY=                    (_joy_axis|_joy_up|_joy_down|_joy_press),
_CONT_axis=        22,
_CONT_up=          23,
_CONT_down=        24,
_CONT_press=       25,
_CONT_dpad=        26,
_CONT=             ( _CONT_axis|_CONT_up|_CONT_down|_CONT_press),
_touch_move=             30,
_touch_tap=              31,
_touch_gesture=          32,
_touch_zoom=             33,
_TOUCH=                  ( _touch_move|_touch_tap|_touch_gesture|_touch_zoom),
        _IDEV_ALL = _MOUSE | _KEY | _JOY | _CONT | _TOUCH ,
_MOVE=              0x01000000,
_ACC=               0x10000000,
_motion=            0x01000010,
_accmotion=         0x10000010,
_rotate2d=          0x01000100,
_translate2d=       0x01001000,
_rotate3d=          0x01010000,
_translate3d=       0x01100000,
_accrotate2d=       0x10000100,
_acctranslate2d=    0x10001000,
_accrotate3d=       0x10010000,
_acctranslate3d=    0x10100000,
_INT_NAV=( _up|_down|_left|_right|_forward|_back),
_INT_GAME=( _up|_down|_left|_right|_forward|_back|_accup|_accdown|_accleft|_accright|_accforward|_accback),
_INT_SIM=( _yawleft|_yawright|_pitchdown|_pitchup|_accyawleft|_accyawright|_accpitchdown|_accpitchup| _rotate2d|_translate2d|_rotate3d|_translate3d|_accrotate2d|_acctranslate2d|_accrotate3d|_acctranslate3d),
_INT=( INT_NAV|INT_GAME| INT_SIM  ),
_enter=     228,
_leave=     229,
_focus=     230,
_drag=      231,
_dragstart= 232,
_dragend=   233,
_keycombo=  234,
_dbclick=   235,
_combo=     236,
_text_in=   237,
_text_edit= 238,
_clipboard= 239,
_play_audio=           252,    
_play_audio_about_to=  253,     // For loading,
_AUDIO= (play_audio |play_audio),
_UI= (_enter|_leave|_focus|_drag|_dragstart|_dragend|_keycombo|_dbclick|_click|_combo|_text_in|_text_edit|_clipboard),
_wake=        356,
_sleep=       357,
_min=         358,
_max=         359,
_hide=        360,
_move=        361,
_resize=      362,
_fullscreen=  363,
_close=       364,
_display_conn=365,
_display_power=366,
_display_orient=367,
_SYS=( _wake|_sleep|_min|_max|_move|_resize|_fullscreen|_close),
_gyro   = 510,
_accel  = 511,
_mag    = 512,
_baro   = 513,
_humid  = 514,
_mic    = 515,
_pos    = 516,
_lidar  = 517,
_cam    = 518,
_SENSOR= _gyro|_accel|_mag|_baro|_humid|_mic|_pos|_lidar|_cam
};


    template <typename T , evs _type =evs::_DEFAULT>
    class event {
        public:
        using ty = T;
        const uint type = _type;
        T data;
        uint32 ms;
        int index; // device index
        static const std::string name = ev_map[type];  
        operator bool() const {return *(this->data);}

        inline bool operator<=(event& lhs,event& rhs){return lhs.data==rhs.data;};
        inline bool operator>=(event& lhs,event& rhs){return lhs.data==rhs.data;};
        inline bool operator<(event<d>& lhs,event<d>& rhs){return lhs.data<rhs.data};
        inline bool operator>(event<d>& lhs,event<d>& rhs){return lhs.data>rhs.data};
        inline bool operator==(event<d>& lhs,event<d>& rhs){return lhs.data==rhs.data};
        inline bool operator!=(event<d>& lhs,event<d>& rhs){return lhs.data!=rhs.data};
        inline bool operator<=>(event<d>& lhs,event<d>& rhs){return lhs.data<=>rhs.data};
        std::string parser_cls_inst(){
            std::string ret;
            ret+=map[ty]+"("+ ;
        };
        d get(){return this->data;};
        int get_index(){return this->index;};
        uint32 get_time(){return this->ms;};
        event(d data,uint32 ms){
            this=default;
            this->data = data; this->ms = ms;
        };
        event() = default ;
        event(event<T,type> s) = default {this = s;}
        event(T data){this->data = data;}
        event(T data, int index);{this->data = data;this->index=index;}
        event(T data, int index,uint32 ms);{this->data = data;this->index=index;this->ms=ms;}
        
    };
    // template <>
    // class event<void,_DEFAULT>{
    
    //     template<typename t,uint _ty>
    //     event<t,_ty> operator=(event<t,_ty> s){ return s;};
    // };
    // using ev_default = event<void,_DEFAULT>;
    


    template <typename T,evs type=evs::_DEFAULT>
    class ev_filter : public event<T,type> {
        public:
        virtual void cb(event<T,type>& lhs); // Callback to call
        virtual bool filter(event<T,type>& lhs){
            return lhs>this;
        };      
    };

    class ev_filters {
        public:
        arr<ev_filter<void, _DEFAULT>*> filters;
        void filter(event<d>& lhs){
            for(int i=0; i<this->filters.size();i++){this->filters->filter(lhs);};
        };
    };
    class event_main ;
    template <uint flag>
    class event_sys : public event<void,ty>{
        public:
        const uint flag=ty;
        event_main* evmain;
        event_sys<evs::_SYS>* sys;
        void _init(); // Initialize the subsystem
        void init() {this->_init()}; 
        virtual event* resolve();
        virtual event* handle();
        virtual void listen();// Checks if there was an event;
        virtual event filter(event* ev);
        event_sys(event_sys<evs::_SYS> sys, event_main* evm){this->sys=sys;this->evmain=evm;};
    };



    template<>
    class event_sys<evs::_DEFAULT>{
        public:
        template<uint flag>
        event_sys<flag> operator=(event_sys<flag> s){
            return s<flag>();
        };
    };
    using evsys_default=event_sys<evs::_DEFAULT>;


using gyro  =  event<vec3,_gyro>;     
using accel  = event<vec3,_accel>;      
using mag  =   event<float,_mag>;    
using baro  =  event<float,_baro>;     
using humid  = event<float,_humid>;      
using pos  =   event<float,_pos>;   
using mic  =   event<vec<int>,_mic>;    
using lidar  = event<mat<int> >,_lidar>;      
using cam  =   event<,_cam>;    
class SENSOR : event_sys<evs::_SENSOR> {
    
};
