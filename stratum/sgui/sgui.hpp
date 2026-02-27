#include <sgui/sgui_widgets.hpp>
#include <sgui/engine_widgets.hpp>
#include <backend/impl.hpp>
#include <vector>
#define NSC std::
namespace sgui {

    struct window : widget {
        void init(glm::ivec2 size = {1024,1000}, glm::ivec2 pos ={10024,1000}){sys.createWin(size,pos);}
        NSC vector<wsys*> ws;
        template <class widgetT >
        void add(widgetT& w){ws.push_back(&w._wsys);w._wsys.parent=_wsys;};
        template <class widgetT >
        void rem(widgetT& w){for(NSC vector<wsys*>::iterator it=ws.begin();it!=ws.end() ;++it){if(*it==&w._wsys){ws.erase(it);}}};
        
        void start();
    };

}
