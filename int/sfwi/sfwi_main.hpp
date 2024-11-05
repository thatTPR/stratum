#include "sfwi_window.hpp"
#include "sfwi_mkb"
#include "sfwi_controller.hpp"
#include "sfwi_joystick.hpp"
#include "sfwi_touch.hpp"
#include "sfwi_os.hpp"
#include "sfwi_events.hpp"
#include "sfwi_cursor.hpp"

#include "idev.hpp"
enum SFWI_SUBSYS {
    SFWI_EVENTS   =  0b000000001        ,    
    SFWI_WINDOW   =  0b000000011        ,
    SFWI_KB       =  0b000000101        ,
    SFWI_MOUSE    =  0b000001001        ,
    SFWI_MKB      =  0b000011001        ,
    SFWI_JOYS     =  0b000100001        ,
    SFWI_CONT     =  0b001100001        ,
    SFWI_TOUCH    =  0b010000001        ,
    SFWI_INPUT_ALL=  0b011111111        ,
    SFWI_OS       =  0b100000001        ,
    SFWI_ALL      =  0b111111111        

};

class sfwi_subsys {

};

class sfwi {
    public:
    sfwi_cursor cursor =  ; 
    enum SFWI_SUBSYS flags = SFWI_ALL ; 
    
    sfwi_window win = NULL ;
    sfwi_os os = NULL ;
    sfwi_events ev  = NULL ;
    
      sfwi_kb kb = NULL   ;
      sfwi_mouse m = NULL ;
      sfwi_controller con = NULL  ;
      sfwi_touch  t = NULL;

    void (s*)()[3];
    void set_event_priority();
    void events();

    void init_ev(){  this->ev    = new sfwi_events();    this->flags = this->flags | SFWI_EVENTS  };
    void init_win(){ this->win   = new sfwi_window();    this->flags = this->flags | SFWI_WINDOW  };
    void init_kb(){  this->kb    = new sfwi_kb();        this->flags = this->flags | SFWI_KB  };
    void init_m(){   this->m     = new sfwi_mouse;       this->flags = this->flags | SFWI_MOUSE  };
    void init_con(){ this->con   = new sfwi_controller();this->flags = this->flags | SFWI_CONT  };
    void init_t(){   this->t     = new sfwi_touch;       this->flags = this->flags | SFWI_TOUCH  };
    void init_os(){  this->os    = new sfwi_os();        this->flags = this->flags | SFWI_OS  };

    void init_input_all(){
        inline init_ev();
        inline init_win();
        inline init_kb();
        inline init_m();
        inline init_con();
        inline init_t();
    };
    void init_all(){
        inline init_input_all();
        inline init_os();
    };
    void init(enum SFWI_SUBSYS FLAGS){
        this->flags= FLAGS ;
        if(FLAGS & SFWI_ALL = SFWI_ALL )
        if(FLAGS & SFWI_WINDOW    = SFWI_WINDOW    ){inline init_win();     };
        if(FLAGS & SFWI_KB        = SFWI_KB        ){inline init_kb() ;         };
        if(FLAGS & SFWI_MOUSE     = SFWI_MOUSE     ){inline init_m()  ;    };
        if(FLAGS & SFWI_CONT      = SFWI_CONT      ){inline init_con() ;};
        if(FLAGS & SFWI_TOUCH     = SFWI_TOUCH     ){inline init_t()  ;    };
        if(FLAGS & SFWI_OS        = SFWI_OS        ){inline init_os();         };
        if(FLAGS & SFWI_EVENTS    = SFWI_EVENTS    ){inline init_ev();     };
                
    };
    sfwi(enum SFWI_SUBSYS flags, sfwi_kb keyb , sfwi_mouse mo , sfwi_controller cont , sfwi_touch touc) :  kb(keyb) , m(mo) , con(cont) , t(touc){};
    sfwi() = default {} ;
    sfwi(enum SFWI_SUBSYS FLAGS) = default {
        inline init(FLAGS)
    };

};

typedef sfwi<1,0,0,0> sfwi_kb ;
typedef sfwi<0,1,0,0> sfwi_m ;
typedef sfwi<0,0,1,0> sfwi_c ;
typedef sfwi<0,0,0,1> sfwi_t ;
typedef sfwi<0,0,1,1> sfwi_ct ;
typedef sfwi<0,1,0,1> sfwi_mt ;
typedef sfwi<1,0,0,1> sfwi_kbt ;
typedef sfwi<1,1,0,0> sfwi_kbm ;
typedef sfwi<1,0,1,0> sfwi_kbc ;
typedef sfwi<1,1,1,0> sfwi_kbmc ;
typedef sfwi<1,1,0,1> sfwi_kbmt ;
typedef sfwi<0,1,1,1> sfwi_mct ;
typedef sfwi<1,0,1,1> sfwi_kbct ;

typedef sfwi<1,1,1,1> sfwi_kbmct ;