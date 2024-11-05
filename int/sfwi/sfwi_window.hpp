#pragma once
#include "../lib/glm/glm.hpp"
#include "../types.hpp"

typedef enum  {

    Minimized =     0b000000,
    Maximized =     0b000001,
    NoOsTitle =     0b000010,
    Fullscreen =    0b000100,
    Windowed =      0b001000,
    FullSWindow =   0b001100,


    MASK       =    0b1111111
}windowFlags;

typedef enum  {
    AlwaysOnTop =  0b001,
    NoResize =     0b010,
    NoMove   =     0b100,
    MASK =         0b111
}windowOptions;
class sfwiwindow {
    public:
    windowFlags flags;
    windowOptions options;  

    suint xsize , ysize;
    suint xpos,ypos ;
    suint opacity ;
    void setoptions () ; 

    void setOpacity(suint opacity);
    void resize(suint xsize, suint ysize);
    void setWindow(Xsize , Ysize , Xpos , Ypos);
    
    sfwiwindow(suint Xsize ,suint  Ysize , suint flags , suint options ) :xsize(Xsize) , ysize(Ysize)  {};
    sfwiwindow(suint Xsize ,suint  Ysize , suint Xpos , suint Ypos) :xsize(Xsize) , ysize(Ysize) , xpos(Xpos) , ypos(Ypos) {};
    sfwiWindow() = default {} ; 
};