// Node editor 
#include <typeinfo>
#include "../sgui_widgets.hpp"
#include "../backend/impl.hpp"
#include <glm/common.hpp>
#include <cstring>
#include <petri/vecs.hpp>
#include <petri/vects.hpp>
// #include <petri/tuple.hpp>
#include <type_traits>
#include <memory>
using namespace events;


template< typename T>
struct reftype{
    static constexpr bool ref = std::is_reference_v<T>;
    static constexpr bool ptr = std::is_pointer_v<T>;
    static constexpr bool val = !(ref || ptr);
};

// Stroke, fill, more
uvec4 exec_col_mat={{200,50,25,200},
                    {0,0,200,100} ,
                    {100,20,0,0}};

umat3x4 ev_col_mat={{200,50,25,100}, 
                    {80,80,80,100},
                    {0,0,80,75}};

umat3x4 res_col_mat={{200,50,25,200}, 
                    {0,0,200,100} ,
                    {100,20,20,75}};

umat3x4 mod_com_mat={200,50,25,200}; 


enum pintypes { // Icons for each // Ref,ptr, each
    event=0,//
    res=1, // Resource
    mod=2  // modifier
};
constexpr umat3x4 col_from_pinty(pintypes s=pintypes::res ){return (s==pintypes::event)?ev_col_mat:res_col_mat}
class node : private widget_base ;
template<typename T >
class pin : public widget{
    public:
    using ty=T;
    using ref= pin<T,_pintype>;
    using ptr=pin<T,_pintype>; 
    T d;
  glm::ivec4 bounds;
    using arrmeta = arrtype<T>;
    std::string name = typeid(T).name() ;
    
    vectvect<uint> connects; // Nodes and their pins in node
    pintypes pintype =pintypes::res;
    umat3x4 color = col_from_pin(pintypes::res);
    ivec4 data ; // h,w,pintype,pinned;
    int32_t[0] pixel_shader_ptr;
    virtual T& data_ref(){return (this->d);};
    virtual T* data_ptr(){return *(this->d);};
    virtual T data(){return this->d;};


    virtual void handle(){return this->d;};
    virtual void _set_ref(pin* p){
        this->ref = p;};
    pin(pintypes pt,std::string name, T data,)  {this->pintype=pt;this->name =name;this->d =data;}
    pin(std::string _name, T data) = default {this->name =_name;this->d =data;}
    pin(std::string _name, T& data) = default {this->name =_name;this->d =data;}
    pin(std::string _name, T* data)= default {this->name = _name ; this->d = *(data);};
    pin(std::string _name, T& data){this = new pin(_name,&data);};
    pin(std::string _name, T data){this->d = data;this->name =  _name; };
    pin(T data) = default{this->d = data;};
    pin(std::string _name){this->name = _name;};

    
};
template <typename T>
class pinres : pin<T>{
    pintypes pintype = pintypes::res ;
    umat3x4 color = col_from_pin(pintypes::res) ;
};
template <typename T, typename lhs>
class pinmod: public pin<T> {
    
    template <typename T>
     void handle(T* resourced); // eg: resourced->field + this->d;
};
template <typename T>
class pinevent : public pin<T>{
        template <typename T>
    void handle(T* modd);    // Eg : modd->field + this->d;
    
};

#define PIN_CLSS(ty,name)
class ##name : pin<ty>  {\
    std::string name = "##name" ; \ 
} ;\

#define PIN_CLSS(ty,name,pinty ) {
class name : pin<ty>  {\
    std::string name = "##name" ; \ 
    pintypes = pintype = pintypes::pinty;
    umat3x4 color = col_from_pin(pinty) ;
} ;
class node_canvas : public sgui::wi_canvas {

} ;


template <typename in_ev_tup,typename in_res_tup,typename in_mod_tup,
typename out_ev_tup,typename out_res_tup,typename out_mod_tup>
class node : virtual public widget,virtual public pin<T> { // Has mainexec
    private:
    char name[] = "node";
    public:
    ivec4 bounds;
       // Every node defines this;
    typedef void (*func)(void) ;

    vect<node*> left_nodes_link;
    vect<node*> right_nodes_link;
    vect<node*> exec_left, exec_right;
    
    in_ev_tup in_event_pins;
    in_res_tup in_res_pins;
    in_mod_tup in_mods_pins;
    const size_t in_ev_size = std::tuple_size(in_ev_tup);
    const size_t in_res_size= std::tuple_size(in_res_tup);
    const size_t in_mod_size= std::tuple_size(in_mod_tup);
    template <size_t n>
    void get_inev(){return std::get<n>(this->in_event_pins);}
    template <size_t n>
    void get_inres(){return std::get<n>(this->in_res_pins);}
    template <size_t n>
    void get_inmod(){return std::get<n>(this->in_mods_pins);}    

    out_ev_tup out_event_pins;
    out_res_tup out_res_pins;
    out_mod_tup out_mods_pins;
    const size_t out_ev_size = std::tuple_size(out_ev_tup);
    const size_t out_res_size= std::tuple_size(out_res_tup);
    const size_t out_mod_size= std::tuple_size(out_mod_tup);
    template <size_t n>
    void get_outev(){return std::get<n>(this->out_event_pins);}
    template <size_t n>
    void get_outres(){return std::get<n>(this->out_res_pins);}
    template <size_t n>
    void get_outmod(){return std::get<n>(this->out_mods_pins);}    


    bool exec;
    uint left_pin_index[20] ;  // Points to nodes;
    

    uint right_pin_index[20];
    size_t right_size=0;
    const uint32_t shader[] = {1,2,3} ; 
    void shader_init()final {
        impl.
    };
    void shader_exec() final {

    };
    
    void _handle(){
        for(int i = 0 ; i <this->in_ev_size ;i++){
        for(int k = 0 ; i <this->in_mod_size;k++){
            this->get_inev<i>().handle(&(this->get_in_mod<i>().d));
        for(int j = 0 ; j <this->in_res_size;j++){
            this->get_inmods<i>().handle(&(this->get_inres<i>().d);};
        };};
        this->shader_exec();
        for(int i = 0 ; i <this->out_ev_size ;i++){this->get_outev<i>().handle(); };
        for(int i = 0 ; i <this->out_res_size;i++){this->get_outres<i>().handle();};
        for(int i = 0 ; i <this->out_mod_size;i++){this->get_outmods<i>().handle();};

        
    };
    void handle()final{
        this->_handle();
    };
    struct node_uni {
        ivec4 text_size;//h,w,space,line
        bool exec;
        ivec4 bounds;
        ivec4 bounds_top;// top_bar_exec_pin
        uint left_size;
        ivec4 pin_left[left_size];// h,w,type,(pinned) 
        uint right_size;
        ivec4 pin_right[right_size];// h,w,type,pinned
        
    };
    void draw()final {
        for(int i = 0 ; i<left.size;)
    };
    private:
    virtual  calc_bounds(ivec2 pos){
        ivec4 bounds ;bounds[3]=pos[0] +this->w ;bounds[4]=pos[2] - this->w;
    };
    void exec() {
        this->handle();
        for(int i = 0; i <this->exec_right->size() ; i++ ){
            (*(this->exec_right[i]))->exec();
        };
    };
    protected:
    static void _push_pin_left( pin* s){this->left->push(s);};
    static void _push_pin_right(pin* s){this->right->push(s);};
    static void _insert_pin_left(size_t pos, pin* s){this->left->insert(pos,s);};
    static void _insert_pin_right(size_t pos, pin* s){this->right->insert(pos,s);};
public:
    node(){
        // Set events

        // 
    }
    node(node_canvas* c,vect<pin*> left, vect<pin*> right){
        this = new node();
        this->node_canvas = c;
        this->left = std::make_shared<vect<pin*>> left ;
        this->right = std::make_shared<vect<pin*>> right ;
    };
    node(node_canvas* c,ivec4 bounds);
    node(node_canvas* c,ivec2 pos){
        this = new node(c,pos,/*canvas,left,right*/);
    };
};

    struct pinVoid {
    std::string name,tyname;
    void* data;
    void cast(std::string name,std::string tyname,auto s){
        this->name=name;
        this->tyname=tyname;
        decltype(s) r;
        this->data = reinterpret_cast<void*>(s);
        r = reinterpret_cast<decltype(s)>(this->data);
        std::cout<<r;
    };
} ;
template <typename T>
class dyn_node : public node { // Like regular node but pins can be added;
    std::vector<> s;
    void addPin(auto pin){

    };

};
// Has only resources and modifiers and one out
template <typename res_tup,typename  mods_tup>
class node_geom : public node_base {
    pinres<T> out ;
    res_tup res;
    mods_tup mods;
    virtual pinres<T> to_res(){

    }
};


class node_instance : public  node  {

    void process;
    
};


class node_canvas : private canvas{
    node** childs ;
    string file_path;
    string global_namespace;
    string* includes;
    enum fence_type {
        class=0,struct=1,namespace=2,function=3,;
    };
    class fence : widget {
        public:
        uint coord[4];
        node** nodes;
        size_t nodes_count;
        fence_type type;
        std::string name ;
        void resize_fit(){
            uint mindist[4]={10,10,10,10};
            
            for(int i=0; i < nodes_cound; i++){
                mindist[0]=mindist[0]< this->nodes[i]->coord[0]-this->coord
            };
        };
        fence(std::string name, uint coord[4] ){

        };
    };

    fence* fences;
    size_t fence_size;
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

class object_fence : public canvas, public node,widget {

};

class branch : public node {
    bool s;

    void exec(){

    } ;
};
/***
 *  One canvas , each object fence may be a class or struct depeneding on requirements . 
 *  @translate_unit 
 */
class translate_unit { 

};