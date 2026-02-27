#ifndef SGUI_WIDGETS_HPP
#define SGUI_WIDGETS_HPP

#pragma once
#include <modules.hpp>
#include <map>
#include <vector>
#include <mode_pipeline.hpp>
#include <glm/glm.hpp>
#include <cstddef>
using namespace std; 
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

#define NSC std::

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
        left_center=     0b1101,
        right=        0b0010,
        right_center=    0b1110,
        top=          0b0100,
        top_center=      0b0111,
        down=         0b1000,
        down_center=     0b1011,
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
    enum class Align {
        _RIGHT=0b001,
        _LEFT=0b100,
        _UP=0b011,
        _DOWN=0b110,
        _CENTER=0b111,
    }
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

enum widgetAttribute {_scroll=0b00010000, draggable=0b00100000, docking=0b01000000,RESIZE=0b10000000,alignleft=0x0b1000 ,alignright=0b0100,alignup=0b0010,aligndown=0b0001};

// #define events

struct wsys  {
    uint16_t (*attr)() ;
    glm::vec4& (*size)();
    glm::vec4& (*maxsize)();
    uint8_t (*align)();
    void (*calc)(glm::vec4& parent_rest);
    void (*draw)();
    bool (*is_pt_of)(glm::ivec2 p);
    wsys* parent;
};

template <typename cA,typename cB, typename widT>
void move_child(cA from,cB to,widT& w);

template <uint16_t watr, class... events>
    class widget : events... {
        public:
        using inher_event_type = inherEvent<events...>;
        uint16_t att ;

        bool scrollable(){return _scroll & att;}  ;
        bool draggable(){return _draggable & att;}  ;
        bool dockable(){return _docking & att;}  ;

        uint16_t attr(){return watr};

        glm::vec4 size; glm::vec4& _size(){return size; };
        glm::vec4 maxsize; glm::vec4&  _maxsize(){return maxsize; };
     
                wsys _wsys;
                glm::ivec4& _size()final{return size;};
                glm::ivec4& _maxsize()final{return maxsize;};
                
                std::enable_if_t<pri::one_of<resize,events...> , void > resize(glm::vec2 r) {size.zw=r;};
                
                virtual void update(glm::vec4 update){};
                virtual void draw();
                
                void event();
                
                void calc(glm::vec4 parent_rest){update(parent_rest);};
                void close(){delete this;};
                
                
                // template <class containerT>
                // void setParent(containerTs* par){parent= par;setcurPar<containerT>();}
                glm::dvec4 color ;
          
                std::string name ;
          
        bool is_pt_of(glm::ivec2 pt ){return 
            (pt.x > size.x) and (pt.y<size.y) and (pt.x<size.z) and (pt.y>size.w)  ;}

    
          
                void wsys_init(wsys* parent = nullptr){_wsys = {attr,_size,_maxsize,get_align,calc,draw,is_pt_of ,parent};}


        // uint pos; // position in canvas hierarchy
        uint childs_length=0;

    template <typename evT ,typename T>
    bool _cb(T& v) {
        if constexpr (inherEvent<events...>::has_event<e>){        
            assert(std::is_same<evT::dtype,T>::value,"Value for evT not correct") ;
            evT::cb(v);return true;}
            return false;
    };
    
    template <typename T,typename evT,typename... evTs> void __cb(T& r){
            if(_cb<evT,T>(r)){return;};
            else if constexpr (sizeof...(evTs)){__cb<T,evTs...>(r);}
        };


    template <typename evT& e>
    void cb(e::dtype& v){__cb<e::dtype,events...>(v);};


        void close()final{std::get<curPar>(parent)->erase_child(this);};

        virtual void draw();
        virtual void update();
       
        SGUI_DECL void calc_self(glm::vec4 bound){}; 
     
        sgui_attribute sattr;

        // virtual SGUI_DECL void moveto(widget* parent){
        //     this->parent->move_child(this,parent);
        // };

    ~widget() {}
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


template <class wT,typename evT>
void evcb(evT::dtype& dt ,wT& ws);

template <class wT>void evcb<wT,click>(click::dtype& dt,wT& ws){if (ws.is_pt_of(dt)){ws.cb<click>(dt);}};

template <typename event,uint8_t attr,typename ev,typename... evs>
event& get_event(widget<attr,ev,evs...>& w){
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



template <typename widT,typename widB=widT>
bool less(widT& lhs,widB& rhs) {return 0;}


template <typename widgetT,class _cmp = less<widgetT> >
class widlist : public NSC list<widgetT*> {
    int (*cmp)(widgetT& ,widgetT& );

    using iterator = list<widgetT>::iterator;
    void insert(iterator& s,widgetT* ptr){insert(s,ptr);};
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

template <uint16_t ats,typename inherEvs, class... widgets>
class compound : widget<ats,inherEvents> {
    using inher_events_type = inherEvs;
    using widgetTY =  widget<ats,inherInhEvent<widgetTs::inher_event_type...> ;
    NSC tuple<widgets> ws;

    template <size_t s>
    void _update()  {if constexpr (s<sizeof...(widgets)) {NSC get<s>(ws).update();_update<s+1>();};};
    void update() override {_update<0>()};  
    void _calc()  {if constexpr (s<sizeof...(widgets)) {NSC get<s>(ws).calc();_calc<s+1>();};};
    void calc() override {_update<0>();};  
    
};


    template <uint16_t ats ,typename inherEvs,class... widgetsTs >
    class container : widget<ats>,  inherInhEvent<widgetTs::inher_event_type...>  {
        using inher_event_type = typename inherEvs;

        pri::tuple<widlist<widgetsTs*> ...> childs;

        
        template <typename Event,typename Widget> 
        void callEv(Event::ty v , Widget& w){

            if constexpr (pri::has_type<Event,>(w.event_tup)) {pri::get<Event>(w.event_tup);}
        };
        template <typename Event> 
        void callEv(Event::ty v,int ind) {

        };
        
        template <widget W, template <typename Wt> Func>
        void callEvList(widlist<W>& wl){for(W& i : wl){Func(i);}};
        
        void applyCallEv(){pri::applyAll(childs,callEvList)} ;




    auto& front(){return *pri::get<0>(childs).front();};
    auto& back(){return *pri::get<pri::tuple_size(childs) -1>(childs).back();}

        template 
        class iterator{
            public:
            using varty = pri::variantvalue<widlist<widgetTs*>::iterator ...>;
            varty iter;
           
            auto& operator*(){return *(pri::get(iter.cur,iter));};  
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
    using const_reverse_iterator = reverse_iterator_<(const WidgetsTs)...> ;
    



    reverse_iterator rbegin(){reverse_iterator::varty it; pri::get<pri::variant_size<reverse_iterator::varty>()-1>(it.iter) = pri::get<reverse_iterator::varty()-1>(childs).rbegin(); 
            return reverse_iterator(pri::variant_size<reverse_iterator::varty>()-1, it );
        }
        reverse_iterator rend(){
           reverse_iterator::varty it; pri::get<0>(it.iter) = pri::get<0>(childs).rend(); 
            return reverse_iterator(0, it );}
    


    const_reverse_iterator crbegin(){rconst_iterator::varty it; pri::get<pri::variant_size<rconst_iterator::varty>()-1>(it.iter) = pri::get<rconst_iterator::varty()-1>(childs).rbegin(); 
            return iterator(pri::variant_size<rconst_iterator::varty>()-1, it );
        }
        const_reverse_iterator crend(){
           rconst_iterator::varty it; pri::get<0>(it.iter) = pri::get<0>(childs).rend(); 
            return rconst_iterator(0, it );}
    

    iterator active;
    list<iterator> selected;
    void addNextToSelected(){iterator it = selected.back();++it;selected.push_back(it);}
    void addPrevToSelected(){iterator it = selected.front();--it;selected.push_front(it);}
    void clearSelected(){selected.clear();}

        void left(){active--;}
        void right(){active++;}
        void up(){active-=()};
        void down(){};

        

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
            static_assert(pri::one_of<widgetT , widgetTs...>::value,"Widget not compatible with container");
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
        template <typename T>
        auto move_here(T* child){insert_child<decltype(child)>(child);};
     
        
    };

    template <typename cA,typename cB, typename widT>
    void move_child(cA from,cB to,widT& w){to.move_here(from.move_from(from.active));};

    template <uint16_t ats,typename... widgetTs> 
    struct hlist : container<ats,widgetTs...> { 
        
    };
    template <uint16_t ats,typename... widgetTs> 
    struct vlist : container<ats,widgetTs...> { // Th
                
    };
    template <uint16_t ats,typename... widgetTs> 
    struct table : container<ats,widgetTs...> { // Th
                
    };


    

    template <typename T,uint16_t ats,typename... widgetTs> 
    struct tree : container<ats,widgetTs...> { // Th Vertical
        
    };

template <typename lineCon,uint16_t,class... events>
class Widget : widget<ats,events...> {
    lineCon SMcont; 
    pipelineContrib* pipeContrib;    

    void update();
    void draw();
} ;

    template <typename lineCon,uint16_t=0,class... events>
    class button : Widget<lineCon,ats,mousedown,keypress> {
        
    };
    template <typename lineCon,uint16_t=0,class... events>
    class toggle_button : button<lineCon,ats, toggle,events...> {

    };
  
    template <typename charT>
    struct textD {
        fontPrim<charT>& fprim;
        bool kerning;
        bool multiLine;
        uint16_t lineWidth;
        textD(std::basic_string<charT> str) : fprim(str);
    };
    
    tempate <typename charT,uint16_t = 0,class... events>
    class text : Widget<textD<charT>,scroll|draggable| docking,events...>{
        
        size_t getInputPos(glm::vec2 pos){
            
        };

    } ;

    tempate <typename charT,uint16_t,class... events>
    struct scrolltext = text<charT,_scroll|ats,scroll,mousewheel,events...> ;


    tempate <typename charT,uint16_t = 0,class... events>
    struct textinput : text<charT,ats,mousedown,keydown,input,events...> ;
    
    tempate <typename charT,uint16_t = 0,class... events>
    struct code : textinput<charT,ats,mousedown,keydown,events...> { 
        size_t ln;size_t col;
        struct pos {uint ln,col;} p;
        
       
    };
    template <uint16_t,class... events>
    struct 2Dgraph : widget<ats,events...> {
        std::vector<float> pts;
        glm::vec2 maxc;
        float gridSize ; 
        void setPt(glm::vec2& coords) {};
        void set(glm::vec2& coords, glm::vec2 pts)

    };
    template <typename T>
    struct inputType : input<T> {T& t;    
    
    };

    template <typename T>
    struct vecList {
        using type = T::value_type;
        static constexpr size_t size = T::length(); 
        std::array<>
    };
    template <typename T>
    struct matList  {
        using type = T::value_type;
        static constexpr size_t cols = T::length(); 
        static constexpr size_t rows = T::col_type::length(); 
    
    
    };


    tempate <uint16_t ats,class... events>    
    struct image : widget<image2D,ats,events...> {
        
    };
    template <uint16_t ats,class... events>
    struct Widget<image2D,ats,events> : image<ats,events>{}

    // template <uint16_t = 0 , class ... events>
    // struct svgImage : Widget<image2D,ats,events> {
            
    //     constexpr svgImage(std::string& svgImage)
    // }


    tempate <typename charT,uint16_t = 0,class... events>    
    struct textIco :Widget<textIcoD,ats,events...>  {
        text<charT,ats,events...> Text;
        image<ats,events...> image;
        
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


    template <typename charT>
    struct tooltip : text<charT,0,_activate,_close>  {
        tooltip(std::string name)
    };
    

    template <typename charT , >
    struct image_tooltip : image<0,_mouseover> {
                
        tooltip toolTip ;
        void update
        void mouseover(impl::mouse_over& r){toolTip.activate();};//
        void mouseout(){toolTip.close();};
        image_tooltip(std::string name,image2D im ) : image(im) ,  toolTip(name,) {}

    };

    using tool = image_tooltip ;
    struct tooltab : vert_bar<align_left|resize,,image_tooltip> {

    }; 



    template <typename T,pri::Str s>
    struct factorWidget {

    };

    template <typename... T>
    struct factorTab {

    };


    template <uint16_t ats , class... events>
    struct windowBar : hori_bar<ats,events>{
        
    };
   
    template <charT>
    struct text : widget {
        std::basic_string<charT> text= "text_widget";
        canvas* _canvas
        std::string name ;
    };
    struct drag_quad : public widget {
        void calc(vec2 mouse_pos, vec2 mouse_move){

        }
    };
    
    struct input_text : widget<_scroll ,input,mousedown,mouseover> {

        void mouseover(){}
        void mousedown(){}
        void 
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
struct gizmo {
    
};

struct view : private widget{ // Gizmos
    gizmos* gs; 
};
struct combo_box : widget {
};
struct container {
    enum t {List,Grid,Row};
    std::vector<wsys>  widgets; 
    void render(); 
}
template <clsss gizmo>
class gizmoContext {
    template <class viewEntity> 

    };
    template <class inherEvent  , ,  class... gizmoContext>
    struct viewPort : widget<ats,events...>{

    };




};
// How is usage : Widget(args);
                //   Widget(args);



#endif