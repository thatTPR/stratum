enum ev {
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
_MOTION_NAV=( _up|_down|_left|_right|_forward|_back),
_MOTION_GAME=( _up|_down|_left|_right|_forward|_back|_accup|_accdown|_accleft|_accright|_accforward|_accback),
_MOTION_SIM=( _yawleft|_yawright|_pitchdown|_pitchup|_accyawleft|_accyawright|_accpitchdown|_accpitchup| _rotate2d|_translate2d|_rotate3d|_translate3d|_accrotate2d|_acctranslate2d|_accrotate3d|_acctranslate3d),
_MOTION=( MOTION_NAV|MOTION_GAME| MOTION_SIM  ),
_enter=     228,
_leave=     229,
_focus=     230,
_drag=      231,
_dragstart= 232,
_dragend=   233,
_combo=     236,
_text_in=   237,
_text_edit= 238,
_clipboard= 239,
_play_audio=           252,    
_play_audio_about_to=  253,     // For loading,
_AUDIO= (play_audio |play_audio),
_UI= (_enter|_leave|_focus|_drag|_dragstart|_dragend|_keycombo|_dbclick|_click|_combo|_text_in|_text_edit|_clipboard),

}


using motion = event<vec3,_motion>;
using accmotion = event<vec4,_accmotion>;
using rotate2d = event<vec2,_rotate2d>;
using translate2d = event<vec2,_translate2d>;
using rotate3d = event<vec3,_rotate3d>;
using translate3d = event<vec3,_translate3d>;
using accrotate2d = event<vec2,_accrotate2d>;
using acctranslate2d = event<vec2,_acctranslate2d>;
using accrotate3d = event<vec3,_accrotate3d>;
using acctranslate3d = event<vec3,_acctranslate3d>;


class MOTION : public event_sys<evs::_MOTION>{
    motion last_motion;
    accmotion last_accmotion;
    rotate2d last_rotate2d;
    translate2d last_translate2d;
    rotate3d last_rotate3d;
    translate3d last_translate3d;
    accrotate2d last_accrotate2d;
    acctranslate2d last_acctranslate2d;
    accrotate3d last_accrotate3d;
    acctranslate3d last_acctranslate3d;

    bool motion_cb(vec3 d,int index){this->last_motion=motion(d,index));};                           bool push_motion(vec3 d,int index){this->evmain.push(motion(d,index));};
    bool accmotion_cb(vec4 d,int index){this->last_accmotion=accmotion(d,index));};                  bool push_accmotion(vec4 d,int index){this->evmain.push(accmotion(d,index));};
    bool rotate2d_cb(vec2 d,int index){this->last_rotate2d=rotate2d(d,index));};                     bool push_rotate2d(vec2 d,int index){this->evmain.push(rotate2d(d,index));};
    bool translate2d_cb(vec2 d,int index){this->last_translate2d=translate2d(d,index));};            bool push_translate2d(vec2 d,int index){this->evmain.push(translate2d(d,index));};
    bool rotate3d_cb(vec3 d,int index){this->last_rotate3d=rotate3d(d,index));};                     bool push_rotate3d(vec3 d,int index){this->evmain.push(rotate3d(d,index));};
    bool translate3d_cb(vec3 d,int index){this->last_translate3d=translate3d(d,index));};            bool push_translate3d(vec3 d,int index){this->evmain.push(translate3d(d,index));};
    bool accrotate2d_cb(vec2 d,int index){this->last_accrotate2d=accrotate2d(d,index));};            bool push_accrotate2d(vec2 d,int index){this->evmain.push(accrotate2d(d,index));};
    bool acctranslate2d_cb(vec2 d,int index){this->last_acctranslate2d=acctranslate2d(d,index));};   bool push_acctranslate2d(vec2 d,int index){this->evmain.push(acctranslate2d(d,index));};
    bool accrotate3d_cb(vec3 d,int index){this->last_accrotate3d=accrotate3d(d,index));};            bool push_accrotate3d(vec3 d,int index){this->evmain.push(accrotate3d(d,index));};
    bool acctranslate3d_cb(vec3 d,int index){this->last_acctranslate3d=acctranslate3d(d,index));};   bool push_acctranslate3d(vec3 d,int index){this->evmain.push(acctranslate3d(d,index));};

    bool motion_cb(motion ev){this->last_motion=ev; };                          bool push_motion(motion ev){this->evmain.push(ev);}
    bool accmotion_cb(accmotion ev){this->last_accmotion=ev; };                 bool push_accmotion(accmotion ev){this->evmain.push(ev);}
    bool rotate2d_cb(rotate2d ev){this->last_rotate2d=ev; };                    bool push_rotate2d(rotate2d ev){this->evmain.push(ev);}
    bool translate2d_cb(translate2d ev){this->last_translate2d=ev; };           bool push_translate2d(translate2d ev){this->evmain.push(ev);}
    bool rotate3d_cb(rotate3d ev){this->last_rotate3d=ev; };                    bool push_rotate3d(rotate3d ev){this->evmain.push(ev);}
    bool translate3d_cb(translate3d ev){this->last_translate3d=ev; };           bool push_translate3d(translate3d ev){this->evmain.push(ev);}
    bool accrotate2d_cb(accrotate2d ev){this->last_accrotate2d=ev; };           bool push_accrotate2d(accrotate2d ev){this->evmain.push(ev);}
    bool acctranslate2d_cb(acctranslate2d ev){this->last_acctranslate2d=ev; };  bool push_acctranslate2d(acctranslate2d ev){this->evmain.push(ev);}
    bool accrotate3d_cb(accrotate3d ev){this->last_accrotate3d=ev; };           bool push_accrotate3d(accrotate3d ev){this->evmain.push(ev);}
    bool acctranslate3d_cb(acctranslate3d ev){this->last_acctranslate3d=ev; };  bool push_acctranslate3d(acctranslate3d ev){this->evmain.push(ev);}



};

;
typedef struct text_edit {
    ivec4 range; // ln,col
    std::string text;
}text_edit; 
using enter = event<bool,_enter> ;
using leave = event<bool,_leave> ;
using focus = event<bool,_focus> ;
using drag = event<bool,_drag> ;
using dragstart = event<bool,_dragstart> ;
using dragend = event<bool,_dragend> ;
using dbclick = event<ivec2,_dbclick> ;
using combo = event<imat2x4,_combo> ; //r0 keys, r1 mouse
using textedit = event<text_edit,_textedit>;
class UI :public event_sys<evs::_UI> {
 public:
    // Lasts
    enter     last_enter;       
    leave     last_leave;       
    focus     last_focus;       
    drag      last_drag;      
    dragstart last_dragstart;           
    dragend   last_dragend;         
    dbclick   last_dbclick;         
    combo     last_combo;       
    textedit  last_textedit;     

    bool enter_cb(bool d,int index){this->last_enter=last_enter(d,index);};
    bool leave_cb(bool d,int index){this->last_leave=last_leave(d,index);};
    bool focus_cb(bool d,int index){this->last_focus=last_focus(d,index);};
    bool drag_cb(bool d,int index){this->last_drag=last_drag(d,index);};
    bool dragstart_cb(bool d,int index){this->last_dragstart=last_dragstart(d,index);};
    bool dragend_cb(bool d,int index){this->last_dragend=last_dragend(d,index);};
    bool keycombo_cb(ivec4 d,int index){this->last_keycombo=last_keycombo(d,index);};
    bool dbclick_cb(ivec2 d,int index){this->last_dbclick=last_dbclick(d,index);};
    bool combo_cb(imat2x4 d,int index){this->last_combo=last_combo(d,index);};
    bool textedit_cb(text_edit d,int index){this->last_textedit=last_textedit(d,index);};


    bool enter_cb(enter ev){this->last_enter=ev;};
    bool leave_cb(leave ev){this->last_leave=ev;};
    bool focus_cb(focus ev){this->last_focus=ev;};
    bool drag_cb(drag ev){this->last_drag=ev;};
    bool dragstart_cb(dragstart ev){this->last_dragstart=ev;};
    bool dragend_cb(dragend ev){this->last_dragend=ev;};
    bool keycombo_cb(keycombo ev){this->last_keycombo=ev;};
    bool dbclick_cb(dbclick ev){this->last_dbclick=ev;};
    bool combo_cb(combo ev){this->last_combo=ev;};
    bool textedit_cb(textedit ev){this->last_textedit=ev;};

 const uint flag=_UI;
    public: 
    
    virtual void get_db_click_ms(int per);
    int get_ms(int _ms=200) final{this->ms=_ms}; int16 ms_cur;}
};