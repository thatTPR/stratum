#include <freetype.h>
#include "sgui_widgets.hpp"

// events modeled after svg events
enum events {
onabort,
onactivate,
onbegin,
oncancel,
oncanplay,
oncanplaythrough,
onchange,
onclick,
onclose,
oncuechange,
ondblclick,
ondrag,
ondragend,
ondragenter,
ondragleave,
ondragover,
ondragstart,
ondrop,
ondurationchange,
onemptied,
onend,
onended,
onerror,
onerror,
onfocus,
onfocusin,
onfocusout,
oninput,
oninvalid,
onkeydown,
onkeypress,
onkeyup,
onload,
onloadeddata,
onloadedmetadata,
onloadstart,
onmousedown,
onmouseenter,
onmouseleave,
onmousemove,
onmouseout,
onmouseover,
onmouseup,
onmousewheel,
onpause,
onplay,
onplaying,
onprogress,
onratechange,
onrepeat,
onreset,
onresize,
onresize,
onscroll,
onscroll,
onseeked,
onseeking,
onselect,
onshow,
onstalled,
onsubmit,
onsuspend,
ontimeupdate,
ontoggle,
onunload,
onvolumechange,
onwaiting
};



class event {
    virtual void trigger() ;
    virtual void behaviour() ;
    event();
};

// Svg compatile events ; 

class onabort : event {
    
};
class onactivate : event {

};
class onbegin : event {

};
class oncancel : event {

};
class oncanplay : event {

};
class oncanplaythrough : event {

};
class onchange : event {

};
class onclick : event {
    void trigger(){

    };
    void baheviour(){

    };
};
class onclose : event {

};
class oncuechange : event {

};
class ondblclick : event {

};
class ondrag : event {

};
class ondragend : event {

};
class ondragenter : event {

};
class ondragleave : event {

};
class ondragover : event {

};
class ondragstart : event {

};
class ondrop : event {

};
class ondurationchange : event {

};
class onemptied : event {

};
class onend : event {

};
class onended : event {

};
class onerror : event {

};
class onerror : event {

};
class onfocus : event {

};
class onfocusin : event {

};
class onfocusout : event {

};
class oninput : event {

};
class oninvalid : event {

};
class onkeydown : event {

};
class onkeypress : event {

};
class onkeyup : event {

};
class onload : event {

};
class onloadeddata : event {

};
class onloadedmetadata : event {

};
class onloadstart : event {

};
class onmousedown : event {

};
class onmouseenter : event {

};
class onmouseleave : event {

};
class onmousemove : event {

};
class onmouseout : event {

};
class onmouseover : event {

};
class onmouseup : event {

};
class onmousewheel : event {

};
class onpause : event {

};
class onplay : event {

};
class onplaying : event {

};
class onprogress : event {

};
class onratechange : event {

};
class onrepeat : event {

};
class onreset : event {

};
class onresize : event {

};
class onresize : event {

};
class onscroll : event {

};
class onscroll : event {

};
class onseeked : event {

};
class onseeking : event {

};
class onselect : event {

};
class onshow : event {

};
class onstalled : event {

};
class onsubmit : event {

};
class onsuspend : event {

};
class ontimeupdate : event {

};
class ontoggle : event {

};
class onunload : event {

};
class onvolumechange : event {

};
class onwaiting : event {

};


// Other events

class onwindowresize : event {

};

class onenterbackground : event {

} ;
class onminimized : event {

};

class
