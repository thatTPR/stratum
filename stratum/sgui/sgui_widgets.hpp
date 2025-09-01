#ifndef SGUI_WIDGETS_HPP
#define SGUI_WIDGETS_HPP


#include <type_traits>
#include <petri/list.hpp>
#include <petri/templates.hpp>
#include <variant>
#include <cstdarg>
#include <type_info>
#include <cstddef>
#include "../petri/vects.hpp"
#include "sgui_internal.hpp"
#include <type_traits>
#include <tuple>
#include <memory>
#include <thread>
#include <int/ansicode.hpp>
#include "./sgui.hpp"
#ifndef uint  
#define uint  unsigned int
#endif
using namespace std ; 

#define STRATA_GLM_NO_SWIZZLE

#define SGUI_DECL static 

#ifndef SGUI_DOCKING
#define SGUI_DOCKING
#endif
#define NO_SIZE 1000000000
#define MAX_WIDGET 500
#define MAX_CHILDS 
namespace sgui {
    using namespace pri;
// Text arrsize()
// Maybe make widget childs so that it has static size defined per widget
    enum align {
        no=           0b0000,
        left=         0b0001,
        left_cen=     0b1101,
        right=        0b0010,
        right_cen=    0b1110,
        top=          0b0100,
        top_cen=      0b0111,
        down=         0b1000,
        down_cen=     0b1011,
        cenh=         0b0011,
        cenv=         0b1100,
        cen=          0b1111
    };

    enum Scroll {
        HORI=  0b01,
        VERTI= 0b10,
        ALL=   0b11
    };
    enum Resize {

        RIGHT =0b0001,
        LEFT  =0b0010,
        UP    =0b0100,
        DOWN  =0b1000,
        SE    =0b1001,
        WSE   =0b1011,
        WS    =0b1010,
        ALL   =0b1111
    };
       
       #define SALIGN_RIGHT  0b001  
       #define SALIGN_LEFT   0b100 
       #define SALIGN_UP     0b011 
       #define SALIGN_DOWN   0b110
       #define SALIGN_CENTER 0b111 
       // Widget Primitives
            
    class sgui_attribute {
        public:
        enum atty {align,scroll,resize,color} ;
        union {
            uint8_t align;
            uint8_t scroll;
            uint8_t resize;
            glm::vec4 color;
        };
        atty t;         
        constexpr attribute operator=(auto c){this->data = c; };
        sgui_attribute operator=(uint8_t s){
            switch(this->t){
                case atty::align :{align = s;};
                case atty::scroll :{scroll = s;};
                case atty::resize :{resize = s;};
            }         
            return *this;   
         };
        sgui_attribute& operator=(glm::vec4 s){
                color = s;return *this;
         };

        sgui_attribute(atty _t){this->t = _t;}
    };

    sgui_attribute color(sgui_attribute::atty::color);
    sgui_attribute align(sgui_attribute::atty::align);
    sgui_attribute scroll(sgui_attribute::atty::scroll);
    sgui_attribute resize(sgui_attribute::atty::resize);
#define WIDGET_EVENT()



template <bool _scroll,bool draggable,bool docking, class... events>
    class widget {
        public:
        constexpr bool scroll = _scroll;
        constexpr bool drag = draggable;
        constexpr bool dock = docking;
        
        using evtup = pri::tuple<events...>;
        evtup unique_events;
        uint8_t align;
        uint8_t scroll;
        uint8_t resize;

        
        glm::ivec4 size;
        glm::ivec4 maxsize;

        glm::ivec4& _size()final{return size;};
        glm::ivec4& _maxsize()final{return maxsize;};
        
        
        virtual void calc(glm::ivec4 parentLeft);
        virtual void update();
        virtual void event();

        
        void close(){delete this;};

//TODO set when widget si active and pushed from backend
        void idev_mouseMove(impl::mouse_move i);
        void idev_mouseDown(impl::mouse_down i);
        void idev_kbDown(impl::key_down i);
        void idev_kbUp(impl::key_up i);
        void idev_kbPress(impl::key_press i);
        void idev_kbCombo(impl::key_combo i);



            
        template <class containerT>
        void setcurPar(){
            for(size_t s  = 0;s<std::variant_size(parent);s++){
                if(std::is_same<*(std::get<s>(parent)) , containerT>::value){
                    curPar = s; return;
                }
            }
        }
        // template <class containerT>
        // void setParent(containerTs* par){parent= par;setcurPar<containerT>();}
        glm::dvec4 color ;
        uint8_t align;
        uint8_t scroll;
        uint8_t resize;

        std::string name ;



        // uint pos; // position in canvas hierarchy
        uint childs_length=0;



        void close()final{std::get<curPar>(parent)->erase_child(this);};

        
        bool is_pt_of(glm::ivec2 pt ){return 
            (pt.x > data.x) and (pt.y<data.y) and (pt.x<data.z) and (pt.y>data.w)  ;}

        virtual void drawCmd();
        virtual void update();
       
 
       
        SGUI_DECL void calc_self(){

        }; 
     

        SGUI_DECL void draw_childs(){
            if(childs_calced ){this->calc_childs();};
            for(int i=0 ; i<this->childs_length;i++){
                this->childs[i]->draw();
            };
        };

        virtual SGUI_DELC void draw(){
            this->draw_childs();
        };
        // virtual SGUI_DECL void moveto(widget* parent){
        //     this->parent->move_child(this,parent);
        // };

    
    widget() = default ;
    void attributes(sgui_attribute at,sgui_attribute... ats){
        switch(at.t){
            case sgui_attribute::scroll : {scroll = at.scroll;}
            case sgui_attribute::resize : {resize = at.resize;}
            case sgui_attribute::color : {scroll = at.color;}
            case sgui_attribute::align : {scroll = at.align;}
        };
        attributes(ats...) ;
    };
    widget(sgui_attribute at,sgui_attribute... ats){
        attributes(at,ats...);
    };
    widget(std::string _name,sgui_attribute at,sgui_attribute... ats){
        name = _name;
        attributes(at,ats...);
    };

    };

template <typename event,typename ev,typename... evs>
event& get_event(widget<ev,evs...>& w){
    static_assert(pri::is_one_of<event,ev,evs...>::value,"event is not part of widget event contribution");
    return pri::get<event>(w.unique_events);
};
    
template <typename event,typename ev,typename... evs>
constexpr bool get_event(widget<ev,evs...>& w, event& ref){
    if(pri::is_one_of<event,ev,evs...>::value){
         ref=pri::get<event>(w.unique_events);return true;
    }
    return false;
};

template <typename event,typename widg,typename... widgets>
void events_proc(event::argtup args, widg w,widgets... ws){
    event ev;
    if constexpr (get_event(w,ev)){
        if constexpr(pri::tuple_size<event::argtup>() == 0){
            ev();}
        else {ev(args);}
    };

    events_proc(args,ws...);
};

    template <class widgetT>
    widgetFuncs getWidgetFuncs(widgetT& w){
        return w.wfuncs;
                // return widgetFuncs{w.calc_ptr,w.update_ptr,w.clear_ptr,w.event_ptr,w.module_ptr}    
    };



template <typename widT>
struct less {
    virtual int cmp(widT& lhs,widT& rhs){return 0;};
};
template <typename widgetT,class _cmp = less<widgetT> >
class widlist : public list<widgetT*> {
    int (*cmp)(widgetT& ,widgetT& );

    using iterator = list<widgetT>::iterator;
    void insert(iterator& s,widgetT* ptr){
        insert(s,ptr);
    };
    void insert(widgetT* w) {
         widlist<widgetT>::iter it= this->begin();
        for( ;it;++it ){
            if(cmp(*it , w) <=0){insert(w,it);return;}
        };
        insert(w,it);
    };
    void erase(list<widgetT*>::iter& it){pop(it);}
    void erase(widgetT* ptr){
        for(list<widgetT*>::iter it= begin() ; it;++it){
            if(*it == ptr){pop(it);return;}
        }}

    widlist() cmp(_cmp::cmp() ) { };
};

template <typename cA,typename cB>
    void move_child(cA from,cB to);

    template <bool scroll,bool draggable,bool docking,  class... widgetsTs>
    class container : widget<scroll,draggable,docking>< {
        
        using evtup =typename pri::utupConcats<widgets::evtup...>::type; 
        evtup unique_events;
        
        pri::tuple<widlist<widgetsTs*> ...> childs;

    auto& front(){
        return *pri::get<0>(childs).front();
    }
    auto& back(){
        return *pri::get<pri::tuple_size(childs) -1>(childs).back();}


        template <class... widgetTs>
        class iterator_ {
            public:
            using varty = pri::variantvalue<widlist<widgetTs*>::iterator ...>;
            varty iter;

            
            auto& operator*(){
                return *(pri::get(iter.cur,iter));
            };  
            inline decltype(*this) incr(){
                ++pri::get(iter.cur,iter);
                if(pri::get(iter.cur,iter) == pri::get(iter.cur,childs).end())  {cur++;pri::get(iter.cur,iter) =pri::get<cur>(childs).begin() ; } 
            };
            inline decltype(*this) decr(){
                ++pri::get<cur>(iter);
                if(pri::get<cur>(iter) == pri::get<cur>(childs).rend())  {cur--;pri::get(iter.cur,iter) =pri::get<cur>(childs).rbegin() ; } 
            };
            decltype(*this) operator++(){return incr();}
            decltype(*this) operator--(){return decr();}
            decltype(*this) operator++(int){return incr();}
            decltype(*this) operator--(int){return decr();}
            decltype(*this) operator+=(int a){for(int i=0;i<a;i++){++(*this);};}
            decltype(*this) operator-=(int a){for(int i=0;i<a;i++){--(*this);};}
            
            iterator(size_t cur,varty ti) iter(ti) {iter.cur=cur;}
        };
        using iterator = iterator_<WidgetsTs...> ;
        using const_iterator = iterator_<(const WidgetsTs)...> ;
        iterator begin(){iterator::varty it;pri::get<0>(it.iter)=pri::get<0>(childs).begin();
            return iterator(0, it );
        }
        iterator end(){
            iterator::varty it;pri::get< pri::tuple_size<childs>()-1>(it)=pri::get< pri::tuple_size<childs>()-1>childs.end();
            return iterator( s,it);}
    
        const_iterator cbegin(){const_iterator::varty it;pri::get<0>(it)=pri::get<0>childs.begin();
            return const_iterator(0, it );
        }
        const_iterator cend(){
            const_iterator::varty it;pri::get< pri::tuple_size<childs>()-1>(it)=pri::get< pri::tuple_size<childs>()-1>childs.end();
            return const_iterator( s,it);}
    
        

    template <typename... Wts>
    class reverse_iterator_ : public iterator_<Wts...> {
        decltype(*this) operator++(){return decr();}
        decltype(*this) operator--(){return incr();}
        decltype(*this) operator++(int){return decr();}
        decltype(*this) operator--(int){return incr();}
    } ;
    using reverse_iterator = reverse_iterator_<WidgetsTs...> ;
    using rconst_iterator = reverse_iterator_<(const WidgetsTs)...> ;
    



    reverse_iterator rbegin(){reverse_iterator::varty it; pri::get<pri::variant_size<reverse_iterator::varty>()-1>(it.iter) = pri::get<reverse_iterator::varty()-1>(childs).rbegin(); 
            return reverse_iterator(pri::variant_size<reverse_iterator::varty>()-1, it );
        }
        reverse_iterator rend(){
           reverse_iterator::varty it; pri::get<0>(it.iter) = pri::get<0>(childs).rend(); 
            return reverse_iterator(0, it );}
    


    rconst_iterator rbegin(){rconst_iterator::varty it; pri::get<pri::variant_size<rconst_iterator::varty>()-1>(it.iter) = pri::get<rconst_iterator::varty()-1>(childs).rbegin(); 
            return iterator(pri::variant_size<rconst_iterator::varty>()-1, it );
        }
        rconst_iterator rend(){
           rconst_iterator::varty it; pri::get<0>(it.iter) = pri::get<0>(childs).rend(); 
            return rconst_iterator(0, it );}
    

    iterator active;
    list<iterator> selected;
    void addNextToSelected(){iterator it = selected.back();++it;selected.push_back(it);}
    void addPrevToSelected(){iterator it = selected.front();--it;selected.push_front(it);}
    void clearSelected(){selected.clear();}

        void prevActive(){active--;}
        void nextActive(){active++;}
        void drawCmd()final{
            for(const auto& t : *this){
                t->drawCmd();
            } ;
        }
        void update()final{
            for(const auto& t : *this){
                t->update();
            } ;
        }

        
    
        template <class widgetT>
        void insert_child(widgetT& w){
            for(size_t s = 0; ; s++){
                if  (pri::is_same<widgetT,decltype(*(pri::get(s,childs).front()))>::value){
                    pri::get<s>(childs).insert(w);return;
                }   ;
            } 
        };
        
        template <class widgetT>
        void erase_child(widgetT* ptr){
            for(iterator& it=begin() ; it ;it++){
                if  (pri::is_same<widgetT,decltype(*(pri::get(it.iter.cur,childs).front()))>::value){
                    pri::get(it.iter.cur,childs).erase(ptr);return;}
                }
            };
          
        template <class widgetT>
        void insert_child(iterator it,widgetT* ptr){
            auto& r = pri::get(it.iter.cur,childs)
            decltype(std::remove_reference<decltype(r)>::type)::iterator iter =  pri::get(it.iter.cur,it.iter)  ;
            r.insert(iter,ptr);  
        };
        void erase_child(iterator it){
             pri::get(it.iter.cur,childs).erase(pri::get(it.iter.cur,it.iter));};    
    

        void erase_selected(){
            for(iterator& it : selected){erase_child(it);}
        };
        
        auto move_from(iterator& it){
            auto ret = *it;
            erase_child(it);
        };
        
        auto move_here(auto* child){
            insert_child<decltype(child)>(child);
        };
        using widget<draggable,docking>::widget ;
    };
    template <typename cA,typename cB>
    void move_child(cA from,cB to){
        to.move_here(from.move_from(from.active));
    };



    template <bool scroll,bool draggable,bool docking,typename... widgetTs> 
    struct hlist :  container<scroll,draggable,docking,widgetTs...> { // Th
                
    };
    template <bool scroll,bool draggable,bool docking,typename... widgetTs> 
    struct vlist :  container<scroll,draggable,docking,widgetTs...> { // Th
                
    };
    template <bool scroll,bool draggable,bool docking,typename... widgetTs> 
    struct table :  container<scroll,draggable,docking,widgetTs...> { // Th
                
    };

    template <bool scroll,bool draggable,bool docking,typename... widgetTs> 
    struct tree :  container<scroll,draggable,docking,widgetTs...> { // Th
         
    };

    template <bool scroll,bool draggable,bool docking,typename... widgetTs> 
    struct vtree : public tree<scroll,draggable, docking,widgetTs...> {

    };

    template <bool scroll,bool draggable,bool docking,typename... widgetTs> 
    struct htree : public tree<scroll,draggable, docking,widgetTs...> {}




template <typename lineCon,bool scroll=false,bool draggable=false,bool docking=false,class... events>
class Widget : widget<scroll,draggable,docking,events...> {
    lineCon d; 
    pipelineContrib* pipeContrib;

    
} ;

    template <typename lineCon,bool scroll=false,bool draggable=false,bool docking=false>
    class button : Widget<lineCon,scroll,draggable,docking,ev_mousedown> {

        void (*press)(decltype(this));
    };
    
  
    template <typename charT>
    struct textD {
        fontPrim<charT>& fprim;
        bool kerning;
        bool multiLine;
        uint16_t lineWidth;
    };
    
    tempate <typename charT,bool scroll=false,bool draggable=false,bool docking=false,class... events>
    class text : Widget<textD<charT>,scroll,draggable, docking,events...>{
        
        size_t getInputPos(glm::vec2 pos){
            
        };

    } ;

    tempate <typename charT,bool draggable=false,bool docking=false>
    using scrolltext = text<charT,true,draggable, docking,ev_scroll,ev_mousewheel> ;


    tempate <typename charT,bool scroll=false,bool draggable=false,bool docking=false,class... events>
    struct textinput : text<charT,scroll,draggable, docking,ev_mousedown,ev_keydown,events...> ;
    
    tempate <typename charT,bool scroll=false,bool draggable=false,bool docking=false,class... events>    
    struct code : textinput<charT,scroll,draggable,docking,ev_mousedown,ev_keydown,events...> { 
        size_t ln;size_t col;
        
    };
    
    tempate <bool scroll=false,bool draggable=false,bool docking=false,class... events>    
    struct image : Widget<image2D,scroll, draggable, docking,events...> {
    
    };




    tempate <typename charT,bool scroll=false,bool draggable=false,bool docking=false,class... events>    
    struct textIco :Widget<textIcoD,scroll,draggable,docking,events...>  {
        text<charT,false,false,false,events...> Text;
        image<false,false,draggable,,
        
    }
    struct fileD {
        decltype(modules::fontPrimPool)::iter path;
        decltype(modules::fontPrimPool)::iter name;
    };
    template <struct fileTab>
    struct fileTabButton : textIco, button<fileD,fileTab>; 
    
    struct fileTabBar : hlist<fileTabButton<fileTabBar>> ; 

    struct fileTabButton : textIco {
        
    } ;

    struct hori_bar : public  widget {
        public:
        using widget_node::widget_node ;
        bool align_top;
        uint  height ;
        uint  text_size ;
         uint  height ; 
        uint  text_size ;
        SGUI_DECL void draw_with_children(uint  height, uint  text_size);
        SGUI_DECL void draw();
    };
    struct verti_bar : public widget {
       using widget::widget;
        bool align_left;
        SGUI_DECL void to_other(){
            side_bar_right n(this);
            this = n; 
        };

    };
   

    struct text : widget {
        static const char[] name = "text_widget";
        canvas* _canvas
        std::string name ;
        

    };
    struct drag_quad : public widget {
        void calc(vec2 mouse_pos, vec2 mouse_move){

        }
    };
    struct input_text : widget {
        bool widget() override {

        };
    };
    struct button : widget{

    };
    struct toggle_button : widget{

    };
    
    template <typename no>
    struct slider_no : widget {
        public:
        no val ;
        no min;
        no max;
    };
    using slider_int = slider_no<int>;
    using slider_uint  = slider_no<uint >;
    using slider_float = slider_no<float>;
    using slider_ufloat = slider_float<unsigned float>;


    struct gizmo : public widget_leaf{
        bool active ;
        
    };

    struct view : private widget{ // Gizmos
        gizmos* gs; 
    };

    struct combo_box : widget {

    }
};
// How is usage : Widget(args);
                //   Widget(args);



#endif