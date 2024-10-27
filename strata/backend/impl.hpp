#pragma once 



class senv_c {


    std::vector<uint> displays  ;

    std::vector<SDL_Window*> windows ; 
    
    virtual enum INIT_FLAGS {
        TIMER,
        VIDEO,
        AUDIO,
        JOYSTICK,
        HAPTIC,
        CONTROLLER,
        EVENTS,
        EVERYTHING,
    };
    class window {

    };
    
    void init(){};
    virtual void newWindow(window* w, char title , int x, int y, int w , int h ){};
    virtual void destroyWindow(window* w){SDL_DestroyWindow(this->displays[ind]);};
    virtual void getNumDisplays();
    
};
template <senv_c c>
class sren_c {
    c env; 
    void init(){

    };
    void text(std::string text ){

    };
    void std::string()

};