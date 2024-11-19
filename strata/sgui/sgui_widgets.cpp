#include "sgui.cpp"

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
// [SECTION] Widgets: InputScalar, InputFloat, InputInt, etc.
// [SECTION] Widgets: InputText, InputTextMultiline
// [SECTION] Widgets: ColorEdit, ColorPicker, ColorButton, etc.
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
        private:
        static const char[] name = "widget"; 
        static const char[] shader_bin = ""; 
        public:
       
        uint c[4];
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
    
    
    class widget : public widget_base{
        public:
        bool dockable = true;
        bool leaf = false; // Leafs can't move child widgets
        constexpr bool is_lead(){return this->leaf;}
        constexpr bool is_dockable(){return this->dockable;};
        bool calced;
        bool childs_calced = false;
        widget* parent ;
        widget** childs;
        static auto* canvas; 
        size_t childs_length=0;
        uint coord[4];
        uint width,height;
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
        SGUI_DECL void set_size(uint xsi,uint ysi){this->x_size=xsi;this->y_size=ysi;}
        SGUI_DECL void set_coord(uint _x,uint _y){this->x = _x ; this->y  = _y;}
        widget(size_t child_arrsize){
            
            this->childs = new widget*[child_arr_size];
        };
        SGUI_DECL void set_coord(uint _x , uint _y , uint )
        virtual SGUI_DECL void calc_from_parent(){

        };
        void load_buffer(){
            
        };
        SGUI_DECL void calc_childs(){ // TODO + gpu
            for(int i = 0  ; i<this->size_childs ; i++){
                this->childs[i]->calc()
            };
            this->childs_calced = true;
        };
        SGUI_DECL void draw_childs(){
            if(childs_calced ){this->calc_childs();};
            for(widget* w : childs){
                w
            };
        };
        virtual SGUI_DECL void draw(){
            
        };
         
        virtual SGUI_DECL void moveto(widget* parent){
            this->parent->move_child(this,parent);
        };
        
        
        auto handle();
        bool ret();
        
    };
    class widget_leaf : public widget_base{ // Even though sgui::widget supports leaf behaviour this interface is better for widgets with truly no children 
        public:
        static const bool leaf = false ;
        constexpr bool is_leaf(){return this->leaf;}        
        widget* parent ;
        SGUI_DECL void draw();
        SGUI_DECL void handle(){
            this->draw();
        };
    };
    template <typename font>
    class canvas : widget {
        public:
        font f;
        uint c[4];
        // widget* last_opened;//TODO
        widget* childs[MAX_WIDGETS]; // Direct children
        int opened[MAX_WIDGETS]; // Currently opened widget so that begin() and close() makes sense
        SGUI_DECL void begin(widget* w){
            this->last_opened = w; 
        };
        SGUI_DECL void end(widget* w){
            this->opened =  this->last_opened;
        };
        
        canvas(){
        canvas(font f, uint x, uint y, uint x_size , uint y_size);
    };
    canvas* current;
    widget* w_cur;
    canvas::canvas(font f, uint x, uint y, uint xs , uint ys){
        this->f = f; this->c[0]=x;this->c[1]=y;this->c[2]=xs;this->c[3]=ys;
        current = this;
    };

    widget::widget(widget* parent,  bool dockable, bool leaf ){
            size_t arr_size = sizeof(parent->childs)/sizeof(parent->childs[0]);
            this->parent= parent ;
            this->dockable = dockable;
            this->leaf = leaf;
            this->canvas = current;
            parent->add_child(this);
        };
    widget::widget(widget* parent) = default{
            this->parent= parent ;
            this->canvas=current;
            parent->add_child(this);
        };
    widget::widget(bool dockable, bool leaf){
        this = new widget(w_cur,dockable,leaf);
        this->parent = w_cur; this->dockable = dockable;
    };
    widget::widget(){
        this = new widget(w_cur);
    };
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
    class SliderScalar : widget {
        SliderScalar()
    };
    template <typename no>
    class slider_no : widget {
        no val ;
        virtual SGUI_DECL void normalize();
    };
    class SliderInt {

        SliderIntNormalised(int min , int max , )
    };

};
};
// How is usage : Widget(args);
                //   Widget(args);