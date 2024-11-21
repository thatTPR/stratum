#pragma once
#include "sgui.cpp"
#include <cstdarg>
#ifndef uint 
#define uint unsigned int
#endif
using namespace std ; 
#define SGUI_DECL static 

#ifndef SGUI_DOCKING
#define SGUI_DOCKING
#endif
#define NO_SIZE 1000000000
#define MAX_WIDGET_CHILDS 500
// [SECTION] Forward Declarations
// [SECTION] Widgets: Text, etc.
// [SECTION] Widgets: Main (Button, Image, Checkbox, RadioButton, ProgressBar, Bullet, etc.)
// [SECTION] Widgets: Low-level Layout helpers (Spacing, Dummy, NewLine, Separator, )
// [SECTION] Widgets: ComboBox
// [SECTION] Data Type and Data Formatting Helpers
// [SECTION] Widgets: DragScalar, DragFloat, DragInt, etc.
// [SECTION] Widgets: SliderScalar, SliderFloat, SliderInt, etc.
// [SECTION] Widgets: InputScalar, InputFloat, InputInt, etc. // TODO 
// [SECTION] Widgets: InputText, InputTextMultiline // TODO
// [SECTION] Widgets: ColorEdit, ColorPicker, ColorButton, etc. // TODO
// [SECTION] Widgets: TreeNode, CollapsingHeader, etc.
// [SECTION] Widgets: Selectable
// [SECTION] Widgets: Typing-Select support
// [SECTION] Widgets: Multi-Select support
// [SECTION] Widgets: ListBox
// [SECTION] Widgets: PlotLines, PlotHistogram
// [SECTION] Widgets: Value helpers
// [SECTION] Widgets: MenuItem, BeginMenu, EndMenu, etc.
// [SECTION] Widgets: BeginTabBar, EndTabBar, etc.
// [SECTION] Widgets: BeginTabItem, EndTabItem, etc.
// [SECTION] Widgets: Columns, BeginColumns, EndColumns, etc.
namespace sgui {
// Text arrsize()
    class canvas;
    SGUI_DECL void canvas::update();
    SGUI_DECL void canvas::update_move();
    SGUI_DECL void canvas::update_insert();
    class widget_base {
        
        public:
        static const char[] name = ""; 
        static const int[] shader_bin = {};
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
    class widget : public widget_base{
        public:
        bool calced;
        bool childs_calced = false;
        widget* parent ;
        widget** childs;
        static auto* canvas; 
        size_t childs_length=0;
        static struct d {
            uint coord[4];
            uint wh_size[2];
            
        } data;
        
        SGUI_DECL void _add_child(widget* w){
            if(this->childs_length < sizeof(this->nodes)/sizeof(this->nodes[0]) ){
            this->childs[this->childs_length] = n; return;
            };
            this->childs_length++;
            node** s = new node*[this->childs_length ] ;
            for(int i =0 ; i < this->childs_length-- ;i++ ){
                s[i] = this->childs[i];
            };
            s[this->childs_length] = n;
            return s;
        };
        
        SGUI_DECL void _insert_child(widget* w , size_t pos){
            this->childs_length++;
            widget* chi[this->childs_length] ;
            for(int i=0 ; i<pos;i++){
                chi[i] = this->childs[o]    
            };
            chi[pos] = w;
            for(int i = pos+1;i<this->childs_length; i++){
                chi[i] = this->childs[i-1];
            };
            this->childs = chi;
        };
        SGUI_DECL void _erase_child(size_t pos){
            this->childs_length-- ;
            for(int i = dynamic_cast<int>(pos); i<this->childs_length ; i++){   
                this->childs[i] = this->childs[i+1]; 
            };
        };
        SGUI_DECL void _move_push_child(size_t pos, widget* parent_dest){
            if constexpr(this->leaf == false){return;};
            this->childs[i]; size_t ns = sizeof(parent_dest->childs)/sizeof(parent_dest->childs[0]);
            widget** n= new widget*[ns+1];
            parent_dest->childs[]=;
        };
        SGUI_DECL void _move_insert_child(size_t possrc, size_t dest, widget* parent_dest){
            if constexpr(this->leaf == false){return;};
            _parent_dest->insert_child(this->childs[possrc],dest);
            this->_erase_child(possrc);
        };
        
        widget* get_child(size_t pos){
            return this->childs[pos];
        };
        size_t get_child(widget* w){
            for(int i = 0 ; i < sizeof(this->childs)/sizeof(this->childs[0])){
                if(w==this->childs[i]){
                    return dynamic_cast<size_t>(i);
                }
            };
        };
        
        
        SGUI_DECL void move_child(widget* w, widget* parent_dest){
            this->_move_child(w, parent_dest);
            this->canvas->update(parent_src,parent_dest,this);
        };
        SGUI_DECL void move_insert_child(widget* w, size_t dstpos ,widget* dest ){
            this->_move_insert_child(w,dstpos,dest);
            this->canvas->update(this,parent_dest,this);
        };
        SGUI_DECL void move_push_child(widget* w, size_t dstpos ,widget* dest ){
            this->_move_push_child(w,dest);
            this->canvas->update(parent_src,parent_dest,this);
        };
        
        SGUI_DECL void add_child(widget* w, uint[2] coord){
            this->_add_child(w);
            this->canvas->update_add(this, w);
        };
        SGUI_DECL void insert_child(widget* w, size_t pos,uint[4] coord){
            w->coord = coord ;
            insert_child(w,pos);
            this->canvas->update();
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
                this->childs[i]->calc()
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
    /*
    class widget_leaf : public widget_base{ // Even though sgui::widget supports leaf behaviour this interface is better for widgets with truly no children 
        public:
        static const bool leaf = false ;
        constexpr bool is_leaf(){return this->leaf;}        
        widget* parent ;
        SGUI_DECL void draw();
        SGUI_DECL void handle(){
            this->draw();
        };
    };*/
    template <typename font>
    class canvas : public widget {
        public:
        font f;
        uint c[4];
        // widget* last_opened;//TODO
        widget* childs[MAX_WIDGETS]; // Direct children
        int opened[MAX_WIDGETS]; // Currently opened widget so that begin() and close() makes sense
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
        
        canvas(){
        canvas(font f, uint x, uint y, uint x_size , uint y_size);
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
    
    
    class w_text : widget_leaf {
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
    class tree {

    };
    class text : widget {
        static const char[] name = "text_widget"
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
    class slider_calar : widget {
      
    };
    template <typename no>
    class slider_no : widget {
        no val ;
        virtual SGUI_DECL void normalize();
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

};
};
// How is usage : Widget(args);
                //   Widget(args);