#include <sgui_widgets.hpp>
#include <petri/templates.hpp>
namespace sgui {
#define NSC pri::
    template <typename T>
    class port {
        using reference = T&;
        using ptr=  T*;
        using type = T;
        T* ptr;
        virtual void render(glm::vec2 coord); 
    };


    template <class T , template <typename T> class portty> // PinType for widget
    struct Pin : widget<0,click,input,dbclick> {
        portty<T> port;


    };
    template <class... Pin>
    class PinIn { // Given a list of pindefines each of which may be collapsible
        
    };
    template <class... Node>
    class PinOut {
        
    };

    struct node : widget<scroll|drag,input,mouseover> {
        static constexpr std::string name ;
        using PinGroup = NSC vector<Pin> ;   
        PinGroup pinins;
        struct PinGroupCollapsible {std::string name;bool collapsed;PinGroup pg;};
        PinGroup pinouts;
        void update(glm::vec4 rest){size =  };
        struct range {NSC list<NSC vector<Pin>::iterator> start,end;}
        struct InputSide {
            NSC list<range> joins; 
            NSC list<range> collapsible
        }
    };
    
    
    template <class... nodes>
    struct nodeCanvas : widget<scroll,input,mouseover> ;
    
    template <class... nodes>
    struct nodeCanvasNode {
        nodeCanvas<nodes...> data;
    };
    
    template < class... nodes>
    struct nodeCanvas : widget<scroll,input,mouseover> {
        PinOut* ingroup ; 
        PinOut outgroup;
            

    };
    
}