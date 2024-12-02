#pragma once

#include "sgui.cpp"
#include <cstdarg>
#include <type_info>
#include "../petri/vects.hpp"
#include "sgui_internal.hpp"
#include <memory>
#include <thread>
#include "../../../../int/ansicode.hpp"
#include "./shaders/shaders.hpp"
#ifndef uint 
#define uint unsigned int
#endif
using namespace std ; 
#define SGUI_DECL static 

#ifndef SGUI_DOCKING
#define SGUI_DOCKING
#endif
#define NO_SIZE 1000000000
#define MAX_WIDGET 500
#define MAX_CHILDS 

namespace sgui {
// Text arrsize()
    
    SGUI_DECL void canvas::update();
    SGUI_DECL void canvas::update_move();
    SGUI_DECL void canvas::update_insert();
    class widget_base {
        
        public:
        static const char name[30] ; 
        char* shader_bin ;
        size_t shader_bin_size;
        short int alignment=0;
        bool dockable = true; // Means a widget can be moved to a different widget, including an auto-constructed new canvas outside the current window; 
        bool leaf = false; // Leafs can't move child widgets
        constexpr int alignment(){return this->alignment}; 
        constexpr bool is_leaf(){return this->leaf;}
        constexpr bool is_dockable(){return this->dockable;};
       
        uint coord[4];
        uint width,height;
        bool bounds_check(uint x[2]){
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
        widget* bounds_get(uint x[2]){
            widget* cur = this;
            for(int i =0; i<this->childs_size;i++ ){
                if(this->childs[i]->bounds_check(x)){
                    cur = this->childs[i];
                    widget* s = this;
                    s= this->childs[i]->bounds_get(uint x[2]);
                    if(s!= this){
                        cur= s;
                    }
                    
                };
            };
            return cur;
        };
        widget_base();
    };  
   /*
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
    */
   class widget: public wiget_base;
   class canvas : public widget ;
    class widget : public widget_base{
        public:
        bool calced;
        bool childs_calced = false;
        size_t canvas_pos;
        widget* parent ; size_t parent_pos;
        // size_t pos; // position in canvas hierarchy
        size_t childs_length=0;
        canvas* canvas; 
        static struct d {
            uint coord[4]; //nw->se
            uint wh_size[2];
            
        } data;
        
        bool is_pt_of(uint pt[2] ){return (pt[0] > coord[0]) and (pt[0]<coord[3]) and (pt[1]<coord[1]) and (pt[2]>coord[4])  ;}
        std::shared_ptr<vect<widget*>> childs;
        
        SGUI_DECL void _push_child(widget* w){
                // this->childs.store(this->childs.load()->push(w));
                this->childs->push(w);
        };
        
        SGUI_DECL void _insert_child(size_t pos,widget* w ){w->parent = this;this->childs->insert(pos,w); };
        SGUI_DECL void _erase_child(size_t pos){
            this->childs->erase(pos);
        };
        SGUI_DECL void _move_push_child(size_t pos, widget* parent_dest){
            parent_dest->push((this->childs->get(pos));
            this->childs->erase(pos);
        };
        SGUI_DECL void _move_insert_child(size_t possrc, size_t dest, widget* parent_dest){
            parent_dest->_insert_child(dest,this->childs->get(possrc));
            this->childs->erase(possrc);
        };
        SGUI_DECL void _move_push(widget* parent){
            this->parent= parent;
            parent->_add_child(this);

        };
        SGUI_DECL void _move_insert(size_t pos,widget* parent ){
            this->parent= parent;
            parent->_insert_child(pos,this);
        };
        SGUI_DECL void _move_canvas_push(widget* parent, canvas* c){
            this->parent = parent;
            this->canvas = c;
            this->parent->push(this);
        };
        SGUI_DECL void _move_push(widget* parent){
            parent->_push_child(this);
        };
        SGUI_DECL void _move_insert(size_t pos,widget* parent){
            parent->_insert_child(pos,this);
        };
        // SGUI_DECL void _copy_push(widget* parent);
        // SGUI_DECL void _copy_insert(widget* parent);
        SGUI_DECL void _move_canvas_insert(size_t pos, widget* parent, canvas* c){
            this->parent = parent;
            this->canvas = c;
            this->parent->insert(pos,this);
        };

#ifdef SGUI_CANVAS_MAT
        SGUI_DECL void _add_child(widget* w){
            this->canvas->mat[this->canvas_pos]->push(w);
        };
        SGUI_DECL void _insert_child(size_t pos,widget* w){
            this->canvas->mat[this->canvas_pos]->insert(pos,w);
        };  
        SGUI_DECL void _erase_child(size_t pos){
            this->canvas->mat[this->canvas_pos]->erase(pos);
        };
        SGUI_DECL void _move(size_t parent_pos){
            this->parent = this->canvas->parent()
        };
        SGUI_DECL void _move_canvas_push(size_t canvas_pos, size_t widget_pos);
        SGUI_DECL void _move_canvas_insert(size_t canvas_pos, size_t widget_pos, size_t pos);
        SGUI_DECL void _move_push_child(size_t pos, size_t parent_pos){
            this->canvas->mat[parent_pos]->push( (*(this->canvas->mat[this->canvas_pos]))[pos]);
        
            this->erase_child(pos);
        };
        SGUI_DECL void _move_insert_child( size_t dest, size_t pos){

        };
#endif

        widget* get_child(size_t pos){
            return this->childs->get(pos);
        };
        size_t get_child(widget* w){
            for(size_t i = 0 ; i < this->childs->size(); i++){
                if(w==this->childs[i]){
                    return i;
                }
            };
        };
        
        
        SGUI_DECL void move_child(widget* w, widget* parent_dest){
            this->_move_child(w, parent_dest);
          
        };
        SGUI_DECL void move_insert_child(widget* w, size_t dstpos ,widget* dest ){
            this->_move_insert_child(w,dstpos,dest);
        };
        SGUI_DECL void move_push_child(widget* w, size_t dstpos ,widget* dest ){
            this->_move_push_child(w,dest);
        };
        
        SGUI_DECL void add_child(widget* w, uint[4] coord){
            this->_add_child(w);
        };
        SGUI_DECL void insert_child(widget* w, size_t pos,uint[4] coord){
            w->coord = coord ;
            insert_child(w,pos);
        };


        virtual SGUI_DECL void _draw(){ 
        };
        SGUI_DECL void move(widget* _parent_dest){
            this->parent->move_child(this,_parent_dest) ;                
        };
        protected:
        SGUI_DECL void set_size(uint width,uint height ){this->data.wh_sizee[0] =;this->data.wh_sizee[1]=width;}
        SGUI_DECL void set_coord(uint _x,uint _y){this->data.coord[0] = _x ; this->data.coord[1]  = _y;this->data.coord[2] =this->data.coord[0]+ this->data.wh_size[0]; this->data.coord[3] =this->data.coord[1]+ this->data.wh_size[1]}
        widget(size_t child_arrsize){
            
            this->childs = new widget*[child_arr_size];
        };
        SGUI_DECL void set_coord(uint _x , uint _y , uint )
        virtual SGUI_DECL void calc_from_parent(){

        };
        void load_buffer(){
            
        };
        SGUI_DECL void calc_self(){

        }; 
        SGUI_DECL virtual void calc_childs(){ // TODO + gpu
            for(int i = 0  ; i<this->size_childs ; i++){
                this->childs[i]->calc();
            };
            this->childs_calced = true;
        };
        private:
        SGUI_DECL void draw_childs(){
            if(childs_calced ){this->calc_childs();};
            for(int i=0 ; i<this->childs_length;i++){
                this->childs[i]->draw();
            };
        };
        public:
        virtual SGUI_DELC void draw(){
            this->draw_childs();
        };
         
        virtual SGUI_DECL void moveto(widget* parent){
            this->parent->move_child(this,parent);
        };
        bool handle(){
            this->calc_childs();
            this->draw();
        };
        void run(){
            for(int i=0 ; i<this->childs_length;i++){
                this->childs[i]->run();
            };
        };
        bool ret();
        
    };
    class canvas : public widget_base {
        public:
        font f;
        widget** childs ; size_t sizechils;
        int* opened; // Currently opened widget so that begin() and close() makes sense
        widget* w_cur;
        vect<vect<<widget*>*> mat; // 0 is canvas direct children
        size_t get_pos_from_widget(widget* w){
            for(size_t i = 0 ; i < this->mat.size(); i++){
                if(w==(*(this->mat[0]))[0]){
                    return i;
                };
            };
        };
        void _add_widget(size_t paren_pos ,widget* w){
            this->mat[0]->push(w);
        };
        void _insert_widget(size_t paren_pos,size_t pos, widget* w){
            this->mat[paren_pos]->insert(pos,w);
        };

        struct ext {
            uint bg_col[3];
            uint fg_col[3];
        } ext ;
        SGUI_DECL void begin(widget* w){
            this->last_opened = w; 
        };
        SGUI_DECL void end(widget* w){
            this->opened =  this->last_opened;
        };
        
        canvas(font f, uint x, uint y, uint width , uint height){
            this->f = f; this->d.coord[0] =x; this->d.coord[1] = y; this->d.coord[2] = x+width;this->d.coord[3] = y+height ;
            this->d.wh_size[0] = width; this->d.wh_size[1] = height;
        };
        canvas(font f,uint x, uint y, uint xsec,uint ysec){
            this=new canvas(f,x,y,xsec-x,ysec-y);
        };
    };
    #ifndef CANVAS_LIMIT
    #define CANVAS_LIMIT 10
    #endif
    canvas* canvas_arr[CANVAS_LIMIT];
    int c_cur=0;
    widget* w_cur;
    int add_canvas(canvas* c){cavas_arr[c_cur+1] = c; c_cur++; w_cur = c;};
    canvas::canvas(font f, uint x, uint y, uint xs , uint ys){
        this->f = f; this->c[0]=x;this->c[1]=y;this->c[2]=xs;this->c[3]=ys;
        c_cur = this;
    };

    widget::widget(widget* parent,  bool dockable, bool leaf,short int alignment ){
            size_t arr_size = sizeof(parent->childs)/sizeof(parent->childs[0]);
            this->parent= parent ;
            this->dockable = dockable;
            this->leaf = leaf;
            this->alignment = alignment;
            this->canvas = current;
            parent->add_child(this);
        };
    widget::widget(widget* parent) = default{
            this->parent= parent ;
            this->canvas=current;
            parent->add_child(this);
        };
    widget::widget(bool dockable, bool leaf, short int alignment){
        this = new widget(w_cur,dockable,leaf,alignment);
    };
    widget::widget(){
        this = new widget(w_cur);
    };
    widget::widget(bool dockable, bool leaf, short int alignment, widget* childs...){
        this = new widget(w_cur,dockable,leaf,alignment);
         std::va_list args;
        va_start(args, childs);
        for (int i = 0; i<childs;i++)
            this->add_child(va_args(args,widget*));
        va_end(args);

    };
    
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
    
    class hlist : public widget { // Th
    public:
        bool resize_borders = true ;
        hlist left = NULL; 
        hlist center = NULL ; 
        hlist right = NULL; 
        uint size ; 
        uint true_size;
        void add_left(hlist* w){if(this->left == NULL){this->left = new hlist;}this->left->add_child(w);};
        void add_right(hlist* w){if(this->right == NULL){this->right = new hlist;}this->right->add_child(w);};
        void add_center(hlist* w){if(this->center == NULL){this->center = new hlist;}this->center->add_child(w);};
        void insert_left(hlist* w,uint pos){this->left->insert_child(w,pos);};
        void insert_right(hlist* w,uint pos){this->right->insert_child(w,pos);};
        void insert_center(hlist* w,uint pos){this->center->insert_child(w,pos);};
        void normalize_childs(int index){
            remainder=0; uint rem = this->width%this->childs_length;
            for(int i = 0 ; i<this->childs_length; i++){
                this->childs[i]=this->width/this->childs_length;   
            }
         }
        virtual SGUI_DECL void calc_childs override(){
            uint width_sum=0;
            for(int i=0 ; i<this->childs_length ; i++){
                width_sum+= this->childs[i]->width; 
                if(width_sum>this->width){
                    width_sum-= this->childs[i]->width;
                    if(this->childs[i]->width> this->width){this->childs[i]->width=this->width / this->childs_lenght;};
                    width_sum+=this->childs[i]->width;
                    if(width_sum>this->width){
                    this->normalize_childs(i);
                    return;
                    };
                }
            };
        };
        
        hlist(hlist* left, hlist* right , hlist* center){

        };
        hlist(hlist* left, hlist* right){

        };
        hlist(hlist* left){

        };
        hlist(hlist* parent , uint alignment){
            switch(alignment ){
                case SALIGN_RIGHT : {
                parent->add_right();break;
                };
                case SALIGN_CENTER : {
                parent->add_center();break;
                };
                parent->add_left();break;

            }


        }        
        hlist(hlist left, hlist right , hlist center){

        };
        hlist(hlist left, hlist right){

        };
        hlist(hlist left){

        };
        

    };
    
    class sw_vlist : public widget {
        bool resizable_borders = true;

    };
    
    // class sw_full : widget {

    // };
    
    
    class w_text : widget {
        char* text;
        void draw(){

        };
    };
    class w_text_input : w_text {
        void handle(){

        };
    };
    class w_code : widget_leaf{
        
    };
    class w_code : widget_leaf {

    };
    class hori_bar : public  widget {
        public:
        using widget_node::widget_node ;
        bool align_top;
        uint height ;
        uint text_size ;
         uint height ; 
        uint text_size ;
        SGUI_DECL void draw_with_children(uint height, uint text_size);
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
    using slider_uint = slider_no<uint>;
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