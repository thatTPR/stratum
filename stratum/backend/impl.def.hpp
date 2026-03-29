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
_keycombo=               11,
_dbclick=                12,

    _KEY=                    (_keyup|_keydown|_keypress),
_joy_hat  =              13,
_joy_axis=               14,
_joy_up=                 15,
_joy_down=               16,
_joy_press=              17,
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
_wake=        56,
_sleep=       57,
_min=         58,
_max=         59,
_hide=        60,
_move=        61,
_resize=      62,
_fullscreen=  63,
_close=       64,
_display_conn=65,
_display_power=66,
_display_orient=67,
_SYS=( _wake|_sleep|_min|_max|_move|_resize|_fullscreen|_close),
_rec = 256,
_play= 257,
_AUDIO = (_rec | _play),
_gyro   = 120,
_accel  = 121,
_mag    = 122,
_baro   = 123,
_humid  = 124,
_mic    = 125,
_pos    = 126,
_lidar  = 127,
_cam    = 128,
_SENSOR= _gyro|_accel|_mag|_baro|_humid|_mic|_pos|_lidar|_cam
};
    static const std::map<int , std::string> ev_map = {
{evs::_click,"click"},{evs::_mousedown,"mousedown"},{evs::_mouseup,"mouseup"},{evs::_mouseup,"mousepress"}{evs::_mouse_move,"mouse_move"},{evs::_mouse_wheel,"mouse_wheel"},{evs::_MOUSE,"MOUSE"},
{evs::_keyup,"keyup"},{evs::_keydown,"keydown"},{evs::_keypress,"keypress"},{evs::_KEY,"KEY"},
{evs::_joy_axis,"joy_axis"},{evs::_joy_up,"joy_up"},{evs::_joy_down,"joy_down"},{evs::_joy_press,"joy_press"},{evs::_JOY,"JOY"},
{evs::_CONT_axis,"CONT_axis"},{evs::_CONT_up,"CONT_up"},{evs::_CONT_down,"CONT_down"},{evs::_CONT_press,"CONT_press"},{evs::_CONT,"CONT"},
{evs::_touch_move,"touch_move"},{evs::_touch_tap,"touch_tap"},{evs::_touch_gesture,"touch_gesture"},{evs::_touch_zoom,"touch_zoom"},{evs::_TOUCH,"TOUCH"},
{evs::_up,"up"},{evs::_down,"down"},{evs::_left,"left"},{evs::_right,"right"},{evs::_forward,"forward"},{evs::_back,"back"},{evs::_accup,"accup"},{evs::_accdown,"accdown"},{evs::_accleft,"accleft"},{evs::_accright,"accright"},{evs::_accforward,"accforward"},{evs::_accback,"accback"},{evs::_yawleft,"yawleft"},{evs::_yawright,"yawright"},{evs::_pitchdown,"pitchdown"},{evs::_pitchup,"pitchup"},{evs::_accyawleft,"accyawleft"},{evs::_accyawright,"accyawright"},{evs::_accpitchdown,"accpitchdown"},{evs::_accpitchup,"accpitchup"},{evs::_rotate2d,"rotate2d"},{evs::_translate2d,"translate2d"},{evs::_rotate3d,"rotate3d"},{evs::_translate3d,"translate3d"},{evs::_accrotate2d,"accrotate2d"},{evs::_acctranslate2d,"acctranslate2d"},{evs::_accrotate3d,"accrotate3d"},{evs::_acctranslate3d,"acctranslate3d"},{evs::_CONTROL},
{evs::_play_audio,"play_audio"},{evs::_play_audio_about_to,"play_audio_about_to"},{evs::_AUDIO,"AUDIO"},
{evs::_wake,"wake"},{evs::_sleep,"sleep"},{evs::_min,"min"},{evs::_max,"max"},{evs::_hide,"hide"},{evs::_move,"move"},{evs::_resize,"resize"},{evs::_fullscreen,"fullscreen"},{evs::_close,"close"},{evs::_SYS,"SYS"},
{evs::_display_conn,"display_conn"},{evs::_display_power,"display_power"},{{evs::_display_orient,"display_orient"}},{evs::_DISPLAY,"DISPLAY"}

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


};
#define STRATA_CAPABILTY_DISPLAY
#define STRATA_CAPABILTY_KEY