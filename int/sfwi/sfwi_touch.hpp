#include "../types.hpp"
#include <vector>

typedef struct touch_ev {
    suint numfing ;
    float** pts ; // 0 means fing lifted

}gesture;

typedef struct path {
    enum elem {
         ;

    };
} ; 
typedef struct gesture {
    suint numfing ; 
    path* path   ; 
} ;

class sfwi_touch {
    suint maxfinger; 
    std::vector<gesture> vec_gest ;
    void multiple_dev();

    void gesture();
    void rec_gesture() ;
    void pinch();
    
    sfwitouch(suint Maxfinger) maxfinger(Maxfinger){};
};