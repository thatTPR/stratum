#include "sgui_internal.hpp" 
#include "sgui_widgets.hpp"
#include <backend/impl.hpp>
#include <vector>
#define NSC std::


namespace sgui {

    

    template <typename... widgetTs>
    struct window : sgui::compound<0 ,inherEvs<drag,dragend,dragleave,dragstart,dragenter> ,widgetTs...> {
        void init(glm::ivec2 size = {1024,1000}, glm::ivec2 pos ={10024,1000}){sys.createWin(size,pos);}
        NSC vector<wsys*> ws;
        template <class widgetT >
        void add(widgetT& w){ws.push_back(&w._wsys);w._wsys.parent=_wsys;};
        template <class widgetT >
        void rem(widgetT& w){for(NSC vector<wsys*>::iterator it=ws.begin();it!=ws.end() ;++it){if(*it==&w._wsys){ws.erase(it);}}};
        
        void proc(){
            evsys.events()
        }
    };

}
