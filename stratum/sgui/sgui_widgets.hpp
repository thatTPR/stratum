#ifndef SGUI_WIDGETS_HPP
#define SGUI_WIDGETS_HPP


#include <type_traits>
#include <petri/list.hpp>
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
    using namespace ptr;
// Text arrsize()
// Maybe make widget childs so that it has static size defined per widget

       #define align_no           0b0000
       #define align_left         0b0001
       #define align_left_cen     0b1101
       #define align_right        0b0010
       #define align_right_cen    0b1110
       #define align_top          0b0100
       #define align_top_cen      0b0111
       #define align_down         0b1000
       #define align_down_cen     0b1011
       #define align_cenh         0b0011
       #define align_cenv         0b1100
       #define align_cen          0b1111

    
       #define SCROLL_HORI  0b01
       #define SCROLL_VERTI 0b10
       #define SCROLL_ALL   0b11
       #define RESIZE_RIGHT 0b0001
       #define RESIZE_LEFT  0b0010
       #define RESIZE_UP    0b0100
       #define RESIZE_DOWN  0b1000
       #define RESIZE_SE    0b1001
       #define RESIZE_WSE   0b1011
       #define RESIZE_WS    0b1010
       #define RESIZE_ALL   0b1111
       
       #define SALIGN_RIGHT  0b001  
       #define SALIGN_LEFT   0b100 
       #define SALIGN_UP     0b011 
       #define SALIGN_DOWN   0b110
       #define SALIGN_CENTER 0b111 
       // Widget Primitives

        template <class... containerTs>
        class widget ;
        class draggable : widget ; // May be dockable
        template <class... widgetTs>
        class container : widget; 
        
   
    class sgui_attribute {
        public:
        enum atty {
            color=0,
            align=1,
            scroll=2
            parent=3,
            dockable=4,
            leaf=5
        };  
        struct {
            glm::dvec4 color ;
            uint8_t align;
            uint8_t scroll;
            bool dockable;
            widget* parent; 
        }data;
        atty t;         
        constexpr attribute operator=(auto c){this->data = c; };
        constexpr void operator[](widget* w){
            switch(this->t){
                case atty::color :{w->color = this->data.color;};
                case atty::align :{w->align = this->data.align;};
                case atty::scroll :{w->scroll = this->data.scroll;};
                case atty::parent :{w->parent = this->data.parent;};
                case atty::dockable :{w->dockable = this->data.dockable;};
            }            
         };
        sgui_attribute(atty _t){
            this->t = _t ;
        }
    };

    sgui_attribute Color(sgui_attribute::atty::color);
    sgui_attribute Parent(sgui_attribute::atty::align);
    sgui_attribute Align(sgui_attribute::atty::parent);
    sgui_attribute Dockable(sgui_attribute::atty::dockable);
#define WIDGET_EVENT()
        template < class... containerTs>
        class widget {
        public:
         std::variant<containerTs*...> parent ;
        size_t curPar;
    

        void eventProc
        auto parent(){
            return std::get<curPar>(parent);
        };
        template <class containerT>
        void setcurPar(){
            for(size_t s  = 0;s<std::variant_size(parent);s++){
                if(std::is_same<*(std::get<s>(parent)) , containerT>::value){
                    curPar = s; return;
                }
            }
        }
        template <class containerT>
        void setParent(containerTs* par){parent= par;setcurPar<containerT>();}
        struct attrib {
            std::string name ;
            glm::dvec4 color ;
            uint8_t align;
            uint8_t scroll;
            bool leaf;
            bool dockable;         
        } at;



        // uint pos; // position in canvas hierarchy
        uint childs_length=0;
        modules::shaderModule sm ;


        glm::ivec4 data;
        glm::ivec4 max;
        
        void _calc()final{
            glm::ivec4 pard  =std::get<curPar>(parent).data;
        }
        virtual void calc(){

        };
        void close()final{std::get<curPar>(parent)->erase_child(this);};

        
        bool is_pt_of(glm::ivec2 pt ){return 
            (pt.x > data.x) and (pt.y<data.y) and (pt.x<data.z) and (pt.y>data.w)  ;}

        virtual void drawCmd();
        virtual void update();
        bool handle(){
            calc_childs();
            drawCmd();
        };
        void run(){
            for(int i=0 ; i<this->childs_length;i++){
                this->childs[i]->run();
            };
        };
       
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
        virtual SGUI_DECL void moveto(widget* parent){
            this->parent->move_child(this,parent);
        };
    widget(widget* parent,  bool dockable, bool leaf,uint8_t alignment ){
            uint arr_size = sizeof(parent->childs)/sizeof(parent->childs[0]);
            this->parent= parent ;
            this->dockable = dockable;
            this->leaf = leaf;
            this->alignment = alignment;
            this->canvas = current;
            parent->add_child(this);
    };
    widget(widget* parent) = default{
            this->parent= parent ;
            this->canvas=current;
            parent->add_child(this);
        };
    widget(bool dockable, bool leaf, uint8_t alignment){this = new widget(w_cur,dockable,leaf,alignment);};
    widget(){this = new widget(w_cur);};
    
    widget(widget* parent,uint flags  )=default{
        this->flags=flags;
        if(flags & DOCKABLE == DOCKABLE) {this->dockable=true;};
        else {this->dockable=false;};
        if(flags&LEAF == LEAF){this->leaf = true;};
        else {this->leaf = false;};
        this->parent = parent;this->canvas = current;
    };
  
    widget(std::initializer_list<sgui_attribute> ats){
        for(const auto& s : ats){
            s[this];
        };
    }

    };

template <typename data,class ...containerTs>
class Widget : widget<containerTs...> {
    data d ; 
    pipelineContrib* pipeContrib;
    void drawCmd(){
        
    };
    void update(){

    };
} ;
template <typename widgetT>
class widlist : public list<widgetT*> {
    int (*cmp)(widgetT& ,widgetT& );

    void insert(widgetT* w) {
         widlist<widgetT>::iter it= this->begin();
        for( ;it;++it ){
            if(cmp(*it , w) <0){insert(w,it);return;}
        };
        insert(w,it);
    };
    void erase(list<widgetT*>::iter& it){pop(it);}
    widlist(int (*_cmp)(widgetT& ,widgetT& )) {cmp(_cmp); };
};

  using containerw = container<container,draggable,widget> ;
    using containercd = container<container,draggable> ;


    class drcontainer :  public dragable , public container<container,draggable> ;

    template <class... widgetsTs>
    class container : widget<container<widgetsTs...>> {
        std::tuple<widlist<widgets> ...> tupvecs;


        template <class widgetT>
        constexpr widlist<widgetT*>& get(){
            for(size_t s=0;s<std::tuple_size(tupvecs);s++){
                if constexpr (std::is_same<widgetT,decltype(*(std::get<s>(tupvecs).data()))>::value){
                    return std::get<s>(tupvecs);
                }
            }
            return std::get<0>(tupvecs) ;
        }

        constexpr bool has_containers(){
            return std::is_same<container,decltype(*(std::get<0>(tupvecs).data()))>::value ;
        }
    decltype (std::get<0>(tupvecs).front()) front(){
        return *std::get<0>(tupvecs).front();
    }
    decltype (*std::get<std::tuple_size(tupvecs) -1>(tupvecs).back()) back(){
        return std::get<std::tuple_size(tupvecs) -1>(tupvecs).back();}


        class iterator {
            public:
            using varty = std::variant<list<widgets*>::iterator ...>;
            varty iter;

            size_t cur=0;
            decltype(*(std::get<cur>(iter))) operator*(){
                return *(std::get<cur>(iter));
            };  
            decltype(*this) incr(){
                ++std::get<cur>(iter);
                if(std::get<cur>(iter) == std::get<cur>(tupvecs).end())  {cur++;std::get<cur>(iter) =std::get<cur>(tupvecs).begin() ; } 
            };
            decltype(*this) decr(){
                ++std::get<cur>(iter);
                if(std::get<cur>(iter) == std::get<cur>(tupvecs).rend())  {cur--;std::get<cur>(iter) =std::get<cur>(tupvecs).rbegin() ; } 
            };
            decltype(*this) operator++(){return incr();}
            decltype(*this) operator--(){return decr();}
            decltype(*this) operator--(int){return operator--();}
            decltype(*this) operator++(int){return operator++();}
            decltype(*this) operator+=(int a){for(int i=0;i<a;i++){++(*this);};}
            decltype(*this) operator-=(int a){for(int i=0;i<a;i++){-=(*this);};}
            
            iterator(size_t cur)
        };


    decltype (std::get<0>(tupvecs).front()) front(){
        return *std::get<0>(tupvecs).front();
    }
    decltype (*std::get<std::tuple_size(tupvecs) -1>(tupvecs).back()) back(){
        return std::get<std::tuple_size(tupvecs) -1>(tupvecs).back();}


    iterator begin(){iterator::varty it;std::get<0>(it)=std::get<0>tupvecs.begin();
        return iterator(0, it );
    }
    iterator end(){size_t s = std::tuple_size<tupvecs>()-1;
        iterator::varty it;std::get<s>(it)=std::get<s>tupvecs.begin();
        return iterator( s,it);}


    iterator active;
    list<iterator> selected;
    void addNextToSelected(iterator it = selected.back();++it;selected.push_back(it);)
    void addPrevToSelected(iterator it = selected.front();--it;selected.push_front(it);)
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

         virtual void posEmpty();
        
        void update(){
            
        };
        template <class widgetTs>
        void insert_child(widgetTs& w){
            for(size_t s = 0; ; ){
                if constexpr (std::is_same<widgetTs,decltype(*(std::get<s>(tupvecs).data()))>::value){
                    std::get<s>(tupvecs).insert(w);return;
                }   ;
            } 
        };
        
        template <class widgetTs>
        void erase_child(widgetTs* ptr){
            for(iterator& it=begin() ; it ;it++){
                if(ptr == t){std::get<it.cur>(tupvecs).erase(it);return;}
            };
        };     

    container(bool dockable, bool leaf, uint8_t alignment, widget* childs...){
        this = new widget(w_cur,dockable,leaf,alignment);
         std::va_list args;
        va_start(args, childs);
        for (int i = 0; i<childs;i++)
            this->add_child(va_args(args,widget*));
        va_end(args);
    };
    container(* parent, uint8_t flags, widget* childs...){
        this = new widget(parent , flags);
         std::va_list args;
        va_start(args, childs);
        for (int i = 0; i<childs;i++)
            this->add_child(va_args(args,widget*));
        va_end(args);
    };

    };
    template <class... containerTs>
    class dragable : widget<containerTs...> {
         bool dragging=true;
        glm::ivec2 dragpos;
       void dragend(){this->dragging=false;};
        void drop(glm::ivec2 pos){
            data.x = pos.x;data.y=pos.y; 
            // Find first common root
            container* cur=parent;
            container* next=parent;
            for(;next->is_pt_of(pos);next=next->parent){
                cur=next;
            }
            
            if(cur.has_containers()){
                for(container* ref : std::get<0>(cur->tupvecs)){
                    if(ref->is_pt_of(pos)){

                    }
                };
            };
        };
        void drag(glm::ivec2 move){
        // Check if needs new window and if so make one which would be appropiate
            uint8_t pos = canv.size();
            canv.newwin(/* sizedata here*/ );
            
            #ifdef STRATA_CAP_DOCKING
          
        };
       void dragstart(){this->dragging=true;};
        glm::ivec4 s;
        uint  width,height;
        bool bounds_check(uint  x[2]){
            if(x[0]>this->c[0]){
                if(x[0]<this->c[2]){
                    if(x[1]>this->c[1]){
                        if(x[1]<this->c[3]){
                            return true;
                        }
                    }
                }
            }
            return false;
        };
    };

    template <typename data,class containerT>
    class button : Widget<data,containerT> {
    
        void (*press)(decltype(this));

    };
  

    template <class... widgetTs> 
    class hlist : public container<widgetTs...> { // Th
                
    };
template <class... widgetTs>     
    class vlist : public container<widgetTs...> {

    };
template <class... widgetTs> 
    class table : public container<widgetTs...> {
        size_t hsize;  
        size_t vsize;

    };
    
    template <typename charT>
    struct textD {
        fontPrim<charT>& fprim;
        bool kerning;
        bool multiLine;
        uint16_t lineWidth;
    };
    
    tempate <typename charT,class ... containerTs>
    class text : Widget<textD<charT>,containerTs...>{
        
        size_t getInputPos(glm::vec2 pos){
            
        };

    } ;

    template <typename charT>
    class scrollableText : Widget<textD<charT>> {

    };
    class textInput : scrollableText<charT> {
        size_t pos;
        void setCursor(glm::vec2 pos){
            pos=getInputPos(pos);
        }
    };

    class code : textInput { 
        size_t ln;size_t col;
        
    };
    class button : widget {

        void (*onclick)() ;
        void click(){onclick();}
        void click(glm::vec2 pos){
            if(is_pt_of(pos)){
                onclick() ;
            }
        };
        
        button(void(*_onclick)()) : onclick(_onclick){}
    };

    struct textIcoD {
        image2D& im ;
        fontPrim& prim ;
    }
    using textIco = Widget<textIcoD> 

    struct fileD {
        modules::fontPrim& path;
        modules::fontPrim& name;
    };
    template <class fileTab>
    class fileTabButton : textIco, button<fileD,fileTab>; 
    
    class fileTabBar : hlist<fileTabButton<fileTabBar>> ; 

    class fileTabButton : textIco {
        
    } ;

    class hori_bar : public  widget {
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
    class verti_bar : public widget {
       using widget::widget;
        bool align_left;
        SGUI_DECL void to_other(){
            side_bar_right n(this);
            this = n; 
        };

    };
    class scroll : public widget {
        public:
       
        };
    };
    class tree : public widget {

    };
    class text : widget {
        static const char[] name = "text_widget";
        canvas* _canvas
        std::string name ;
        

    };
    class drag_quad : public widget {
        void calc(vec2 mouse_pos, vec2 mouse_move){

        }
    };
    class input_text : widget {
        bool widget() override {

        };
    };
    class button : widget{

    };
    class toggle_button : widget{

    };
    
    template <typename no>
    class slider_no : widget {
        public:
        no val ;
        no min;
        no max;
    };
    using slider_int = slider_no<int>;
    using slider_uint  = slider_no<uint >;
    using slider_float = slider_no<float>;
    using slider_ufloat = slider_float<unsigned float>;


    class gizmo : public widget_leaf{
        bool active ;
        
    };

    class view : private widget{ // Gizmos
        gizmos* gs; 
    };

    class combo_box : widget {

    }
};
// How is usage : Widget(args);
                //   Widget(args);



#endif