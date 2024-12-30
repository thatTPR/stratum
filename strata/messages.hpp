

#ifndef MESSAGES_H
#define MESSAGS_H
#include <sgui/sgui_widgets.hpp>
// Logging

class log : widget{
    public:
    widget parent ;//TODO = canvas;
    sgui::text s ;
    log();
    log operator<<(std::string& s){
        this->s+=s;
    };
    log operator<<(widget& w)
};

// Messages
class message : log {
    message();
    std::vector<widget> childs;
};

#endif