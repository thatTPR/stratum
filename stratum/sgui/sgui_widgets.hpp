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
#include "sgui.hpp"
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


    float textSize = 11;
    uint8_t clickSpeed = 100 ; // ms
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
    glm::mat2x2& (*size)();
    glm::vec2& (*maxsize)();
    glm::vec2& (*minsize)();
    uint8_t (*align)();
    void (*calc)(glm::vec4& parent_rest);
    void (*draw)();
    bool (*is_pt_of)(glm::ivec2 p);
    wsys* parent;
};

template <typename cA,typename cB, typename widT>
void move_child(cA from,cB to,widT& w);



template <class... evs>
using if_click =  std::enable_if<inherEvent<evs...>::has_event<click >, inherEvent<mousedown,mouseup> >::type , 




template <uint16_t watr, class... events>
class widget : if_click<events...>  ,   events... {
    public:
    using inher_event_type = inherInhEvent<inherEvent<events...> , if_click<events...>>;
    uint16_t att=watr ;


        std::enable_if<inher_event_type::has_event<dbclick> , impl::SYS::time_type>::type lastclick;


        bool scrollable(){return _scroll & att;}  ;
        bool draggable(){return _draggable & att;}  ;
        bool dockable(){return _docking & att;}  ;

        uint16_t attr(){return watr};
        glm::vec2 sizewh;
        glm::mat2x2 pos; glm::imat2x2& _size(){return size; };
        glm::vec2 maxsize; glm::ivec2&  _maxsize(){return maxsize; };
        glm::vec2 minsize; glm::ivec2&  _maxsize(){return minsize; };
     
                wsys _wsys;
                glm::ivec4& _size()final{return size;};
                glm::ivec4& _maxsize()final{return maxsize;};
                
                std::enable_if_t<pri::one_of<resize,events...> , void > resize(glm::vec2 r) {size.zw=r;};
                
                virtual void draw();
                
                void event();
                
                void calc(glm::mat2x2& parent_rest){
                    pos[0]=parent_rest.x;pos[1]=pos.x+sizewh;
                    sizewh = maxsize;
                    parent_rest.x=pos[1];
                };
                void close(){delete this;};
                
                
                // template <class containerT>
                // void setParent(containerTs* par){parent= par;setcurPar<containerT>();}
                glm::dvec4 color ;
          
                std::string name ;
          
        bool is_pt_of(glm::vec2 pt ){return pt>pos[0] and ( pt< pos[1])  ;}
          
                void wsys_init(wsys* parent = nullptr){_wsys = {attr,_size,_maxsize,_minsize,get_align,calc,draw,is_pt_of ,parent};}


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

        std::enable_if<inher_event_type::has_event<mouseup> , void>::type ev_mouseup(){
            if constexpr (inher_event_type::has_event<mouseup>){ if(resizing){resize_end();};}
        };

        virtual void bind(){};

    ~widget() {}
    widget() {events()... ;} ;
    void attributes(sgui_attribute at,sgui_attribute... ats){
        switch(at.t){
            case sgui_attribute::scroll : {scroll = at.scroll;}
            case sgui_attribute::resize : {resize = at.resize;}
            case sgui_attribute::color : {scroll = at.color;}
            case sgui_attribute::align : {scroll = at.align;}
        };
        attributes(ats...) ;
    };
    widget(sgui_attribute at,sgui_attribute... ats){ ; attributes(at,ats...);wsys_init();};
    widget(std::string _name,sgui_attribute at,sgui_attribute... ats){
        name = _name;
        attributes(at,ats...);wsys_init();
    };

    widget(wsys& parent,sgui_attribute at,sgui_attribute... ats){ ; attributes(at,ats...);wsys_init(&parent);};
    widget(wsys& parent,std::string _name,sgui_attribute at,sgui_attribute... ats){
        name = _name;
        attributes(at,ats...);wsys_init(&parent);
    };

    };

template <typename widT,typename widB=widT>
bool less(widT& lhs,widB& rhs) {return 0;}

template <typename widgetT,class _cmp = less<widgetT> >
class widlist : public NSC list<widgetT*> {
    int (*cmp)(widgetT& ,widgetT& );

    using type = widgetT;
    using iterator = NSC list<widgetT>::iterator;
    using const_iterator =  NSC list<widgetT>::const_iterator ;
    
    using reverse_iterator = NSC list<widgetT>::reverse_iterator;
    using const_reverse_iterator =  NSC list<widgetT>::const_reverse_iterator;
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
class compound : widget<ats> , inherEvs {
    using inher_events_type = inherEvs;
    using widgetTY =  widget<ats,inherInhEvent<widgetTs::inher_event_type...> ;
    NSC tuple<widgets> ws;
    NSC tuple<bool > enabled;

    mat2x2 size_rest;


    template <typename T>
    void cb(T& p){};

    std::enable_if<inherEvs::has_event<mousemove> , void>::type ev_mousemove(mousemove::dtype& d) {
        if(is_pt_of(d)){if(!mouseon){     
            if constexpr (inherEvs::has_event<mouseenter>) {mouseenter::cb();};
            if constexpr (inherEvs::has_event<mouseover>) {mouseover::cb();};
            if constexpr (inherEvs::has_event<dragenter>) {dragenter::cb();};

            mouseon=true;}; 
        };
    };


    template <size_t s>
    void _update()  {if constexpr (s<sizeof...(widgets)) {NSC get<s>(ws).update();_update<s+1>();};};
    void update() override {_update<0>()};  
    void _calc()  {if constexpr (s<sizeof...(widgets)) {NSC get<s>(ws).calc(size_rest);_calc<s+1>();};};
    void calc(mat2x2& parent)  { widgetTY::calc(parent) ; _update<0>(); };  

};


// TODO 
/*
// Unofficial , incomplete
#if __cplusplus > 202903L
    template <uint16_t ats ,typename inherEvs, class widgetT, class... widgetsTs >
    class container : widget<ats>  {
        glm::vec2 leftSize;

        using inher_event_type = typename inherEvs;

        NSC tuple<widlist<widgetT> ,widlist<widgetsTs>...>> childs;

        using iterval = size_t ;
        static constexpr size_t wno = sizeof...(widgetsTs) ;  
        template <iterval v>
        constexpr auto& getfunc(){return NSC get<v>(childs);}

    auto& front(){return *pri::get<0>(childs).front();};
    auto& back(){return *pri::get<pri::tuple_size(childs) -1>(childs).back();}

    // using vartype = NSC variantvalue<widlist<widgetTs*>::iterator ...>; 
    using vartype = NSC variant<widlist<widgetT>::iterator,widlist<widgetTs*>::iterator ...>; 
        template <size_t s>
        struct _iterator : decltype(NSC get<s>(childs))::iterator {};
        template <size_t s>
        struct _const_iterator : decltype(NSC get<s>(childs))::const_iterator {};
        
        template <size_t s>
        struct _reverse_iterator : decltype(NSC get<s>(childs))::reverse_iterator {};
        template <size_t s>
        struct _const_reverse_iterator : decltype(NSC get<s>(childs))::const_reverse_iterator {};
        

        template <size_t s>
        _iterator<s> _begin(){return NSC get<s>( childs).begin();}
        template <size_t s>
        _iterator<s> _end(){return NSC get<s>( childs).end();}
        template <size_t s>
        _const_iterator<s> _cbegin(){return NSC get<s>( childs).cbegin();}
        template <size_t s>
        _const_iterator<s> _cend(){return NSC get<s>( childs).cend();}
        
        template <size_t s>
        _reverse_iterator<s> _rbegin(){return NSC get<s>(childs).rbegin();}
        template <size_t s>
        _reverse_iterator _rend(){return NSC get<s>(childs).rend();}
        template <size_t s>
        _const_reverse_iterator<s> _crbegin(){return NSC get<s>(childs).crbegin();};
        template <size_t s>
        _const_reverse_iterator<s> _crend(){return NSC get<s>(childs).crend();};
        
        template <size_t s> 
        struct iterator : _iterator<s>  {
            using type = typename NSC variant<widlist<widgetT>::iterator ,widlist<widgetTs >::iterator...> ;
            type itvar; 
            size_t const p = s;
            auto operator++(){_iterator<s>::operator++(); if(it==_end<s>()){ if constexpr (s<wno){return _begin<s+1>();} ;} ;}
            auto operator--(){_iterator<s>::operator--(); if(*it==nullptr){ if constexpr (s>0){return _begin<s-1>()+ ( -1 +NSC get<s-1>().size() ) ;} ;}}
            constexpr iterator(size_t s){}
        };

        iterator<0> begin(){return _begin<0>();}
        iterator<wno> end(){return _end<wno-1>();}
        cbegin()
        cend()
        rbegin()
        rend()
        crbegin()
        crend()


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

        template <size_t s,template <typename T> typename A>
        void _apply_all(){
            auto& w  = NSC get<s>(childs);
            if constexpr (s<=sizoef...(widgetTs)){std::for_each(w.begin(),w.end(),A<decltype(w)::type>()  ) ; _apply_all(s+1,A);}
            else return;
        };


          template <template <typename T> typename A>
        void apply_all(){_apply_all<0,A>()};


        auto move_from(iterator& it){
            auto ret = *it;
            erase_child(it);
        };
        template <typename T>
        auto move_here(T* child){insert_child<decltype(child)>(child);};
     
            void calc(mat2x2& parent) override { widgetTY::calc(parent) ; std::for_each(begin(),end(),<>[&leftSize](){}; };  

        
    };

#endif
*/


    template <uint16_t ats ,typename inherEvs, class widgetT ,class containerT=widlist>
    class container : widget<ats,resize,mousedown,mouseup>  {
        public:
        using inher_event_type = typename inherEvs;
        
        using type = container<ats,inherEvs,widgetT,containerT> ; 
        glm::vec4 size; 
        glm::mat2x2 size_rest;

        containerT<widgetT> childs;

        widgetT& front(){return childs.front();};
        widgetT& back(){return childs.back();}

        using iterator = containerT<widgetT>::iterator ;
        using const_iterator = containerT<widgetT>::iterator::const_iterator ;
        iterator begin(){return childs.begin();}
        iterator end(){return childs.end();}
    
        const_iterator cbegin(){childs.cbegin();}
        const_iterator cend(){childs.cend();}
    
        

    using reverse_iterator =  containerT<widgetT>::reverse_iterator ;
    using const_reverse_iterator =  containerT<widgetT>::const_reverse_iterator ;
    



    reverse_iterator rbegin(){return childs.rbegin();}
    reverse_iterator rend(){return childs.rend();}
    
    const_reverse_iterator crbegin(){return childs.crbegin();}
        const_reverse_iterator crend(){return childs.crend();}
    

    iterator active;
    list<iterator> selected;
    void addNextToSelected(){iterator it = selected.back();++it;selected.push_back(it);}
    void addPrevToSelected(){iterator it = selected.front();--it;selected.push_front(it);}
    void clearSelected(){selected.clear();}       

        void ev_load()final{for(const auto& t : *this){t->ev_load();} ;}
        void update()final{for(const auto& t : *this){t->update();} ;}
        template <typename wt>
        void _calc(wt& w){w.calc(rest_size);}
        void update_calc() {for(const auto& t : *this){_calc(t);};}
        void calc(mat2x2& p)final{widget<ats>::calc(p) ; update_calc();}


        widgetT* firstResize;widgetT* nextResize;
        bool in_boundary(vec2& pt){
            for(iterator i = begin(); i!=end() ; ++i ){
                if(i->pos[0].x < pt.x and ( pt.x <i->pos[1].x ) and ( glm::abs(pty - i->pos[1].y ) <10  ) {
                    firstResize = &(*i) ;  ++i; nextResize = &(*i) ;return true;
                }
            }
            return false;
        };



        
        std::enable_if<inher_event_type::has_event<rclick> , void >::type ev_rclick(impl::mousepos pt){
            if constexpr (widgetT::inher_event_type::has_event<rclick>){for(auto& i : *this){if(i.is_pt_of(pt)){i.ev_rclick(m,pt);return;};};}
        };
        
        std::enable_if<inher_event_type::has_event<dbclick> , void >::type ev_dbclick(impl::mousepos pt){
            if constexpr (widgetT::inher_event_type::has_event<dbclick>){for(auto& i : *this){if(i.is_pt_of(pt)){i.ev_dbclick(pt);return;};  };};
        };
        
        std::enable_if<inher_event_type::has_event<click> , void >::type ev_click(impl::mousepos& pt){
            if constexpr (widgetT::inher_event_type::has_event<click>){
                  for(auto& i : *this){if(i.is_pt_of(pt)){i.ev_click(m,pt);return;};}
            };
            if constexpr(inher_event_type::has_event<dbclick>){
                if(impl::sys.time() - lastclick < clickSpeed){ev_dbclick(pt);}
            };  
        };
         
        void ev_mousedown(impl::mousedown m,impl::mousepos pt){
            if constexpr (widgetT::inher_event_type::has_event<resize>) {if((m == 0)and in_boundary(pt)){ resize();return;} }
            if constexpr (widgetT::inher_event_type::has_event<mousedown>){  for(auto& i : *this){if(is_pt_of(pt)){i.ev_mousedown(m,pt);};return;};};
            
        };    
        void ev_mouseup(impl::mouseup m,impl::mousepos pt){
            if( (m==0) and resizingb ){resize_end(); }
            if constexpr (widgetT::inher_event_type::has_event<mouseup>){  for(auto& i : *this){if(i.is_pt_of(pt)){i.ev_mousedown(m,pt);return;};};}
            if constexpr (inher_event_type::has_event<click>) {ev_click(pt);}
        };

   
        void ev_mousemove(impl::mouse_move& m){if(resizingb){resizing(m);}; };
        
        virtual void _resizing(impl::mouse_move& m) {};
        void resizing(impl::mouse_move& m){if constexpr (inher_event_type::has_event<resize>){_resizing(m);};}

        void insert_child(widgetT& w){childs.insert(&w); };
        
        void erase_child(widgetT* ptr){for(auto it = begin();it!=end();++it){if(*it=ptr){childs.erase(it);};}};
        void erase_child(iterator& it){childs.erase(it);};
          
        void insert_child(iterator it,iterator& at){ childs.insert(*it,at);  };
        void insert_child(widgetT* it,iterator& at){ childs.insert(it,at);  };
        void erase_child(iterator it){childs.erase(it);};    
    
        void erase_selected(){for(iterator& it : selected){erase_child(it);}    };
        
        void move_from(iterator& from ,type& fromC, iterator& at){
            insert_child(from , at);
            fromC.erase(at);
        };
        void move_to(iterator& it, type& toC,iterator& to){toC.move_from(it,toC,to);};
        void push(widgetT& w){insert_child(w,end());};

        iterator begin(){childs.begin();}
        iterator end(){childs.end();}
        const_iterator cbegin(){childs.cbegin();}
        const_iterator cend(){childs.cend();}
      
        reverse_iterator rbegin(){childs.rbegin();}
        reverse_iterator rend(){childs.rend();}
        const_reverse_iterator crbegin(){childs.crbegin();}
        const_reverse_iterator crend(){childs.crend();}
      

    };

    template <uint16_t ats,typename widgetT> 
    struct hlist : container<ats,widgetT> { 

        void _resizing(impl::mouse_move p) override {firstResize->pos[1].x+=p.x;nextResize->pos[0].x+=p.x;};
        template <typename wt>
        void _calc(wt& w){w.pos=glm::mat2x2(leftsize[0].xy,vec2(leftsize[0].x+w.size.x,leftsize[1].y));leftsize[1].x=w.pos[1].x;}      
    };
    template <uint16_t ats,typename widgetT> 
    struct vlist : container<ats,widgetT> { 
        void _resizing(impl::mouse_move p)override {firstResize->pos[1].y+=p.y;nextResize->pos[0].y+=p.y;};
        template <typename wt>
        void _calc(wt& w){w.pos=glm::mat2x2(leftsize[0].xy,vec2(leftsize[0].x,leftsize[1].y+w.size.y));leftsize[1].y=w.pos[1].y;}      
    };
    template <uint16_t ats,typename widgetT> 
    struct table : container<ats, widgetT> { // Th
        size_t nocol;glm::ivec2 entry_size; 
        template <typename wt>
        void _calc(wt& w){w.size=glm::ivec4(leftsize.x,leftsize.y+w.size.h,leftsize.zw);leftsize.y=w.size.w;}          
        void calc(){
            entry_size = 
            container<ats,widgetTs...>::calc();
        }
    };


    

    template <typename T,uint16_t ats,typename widgetT> 
    struct tree : container<ats,widgetT> { // Th Vertical
        
    };

template <typename plContrib,uint16_t ats,class... events>
class Widget : widget<ats,events...> {
    lineCon SMcont; 
    pipelineContrib* pipeContrib;   
    lineCon::iterator it; 
    void bind() final {SMcont.bind(pipeContrib);}
    void update() final {SMcont.update(p)};
    void draw() final {} ;
} ;


    Tag vgbutton(svgTag::ATSTY("",1,"xMinYMin",1,{10,0,1,0,0,1,1,1}, 1,0,0),svgTag::SUBTY(rectTag(0,0,1,1,0.1,0.1,NULL),)) ;

            
            svgWidget(svgTag&& tag) {tg=bTag<svgTag>(tag);tg.events();};
        };

    template <uint16_t ats,class... events>
    class button : public Widget<lineCon,ats,click> {
        bool* bl;    
        void ev_click(impl::mousepos& pt){if(is_pt_of(pt)){*bl=true;};}
    };
    template <typename lineCon,uint16_t ats,class... events>
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
        
        size_t getInputPos(impl::mousepos pos){
            
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
    struct _2Dgraph : widget<ats,events...> {
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