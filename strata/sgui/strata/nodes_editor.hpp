// Node editor 
#include "../sgui_widgets.hpp"
enum pintypes { // Icons for each // Ref,ptr, each
    event,
    function,
    res, 
    mainexec,
}
class node : private widget_base ;
template<typename type>
class pin : public code{
    public:
    T data;
    pin* ref ;
    node* parent;
    uint color[4];
    char* pixel_shader_ptr;
    void draw();
    void calc();
    virtual void _set_ref(pin* p){
        this->ref = p;
    };
   
    
};
class function_pin : public pin{

};
class res_pin : public pin {

};

class node_widget : public widget {
    node_widget(pin* left[], pin* right[]){
        this->left = left; this->right= right;
    }
} ;


class node :public widget {
    private:
    static constexpr const char* name = "node";
    public:
    pin** left_pins;
    pin** right_pins;

    virtual void exec(){

    };
    node(node_canvas* c,pin left[] , pin right[]){

    };
    
};
class node_expression : public node, public w_code {
    #define MAX_EXPR_SIZE 256
    char expr[MAX_EXPR_SIZE] ;
   
    virtual void exec(){

    };
    virtual void draw(){

    };
};

class node_canvas : private canvas{
    node** childs ;
    string path;
    string* dep_paths;
    SGUI_DECL void add_child(widget* w, uint[2] coord){
            w->coord=coord;
            this->_add_child(w);
            this->canvas->update_add(this, w);
    };    
    SGUI_DECL void insert_child(widget* w, size_t pos,uint[4] coord){
        w->coord = coord ;
        insert_child(w,pos);
        this->canvas->update();
    };
    
    node_canvas(){

    };
};


class branch : public node {
    bool s;

    void exec(){

    } ;
};
