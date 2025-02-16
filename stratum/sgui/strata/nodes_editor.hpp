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

namespace snode {


template< typename T>
struct reftype{
    static constexpr bool ref = std::is_reference_v<T>;
    static constexpr bool ptr = std::is_pointer_v<T>;
    static constexpr bool val = !(ref || ptr);
};

// Stroke, fill, more
uvec4 exec_col={{200,50,25,200},
                    {0,0,200,100} ,
                    {100,20,0,0}};

glm::umat3x4 ev_col={{200,50,25,100}, 
                    {80,80,80,100},
                    {0,0,80,75}};

glm::umat3x4 res_col={{200,50,25,200}, 
                    {0,0,200,100} ,
                    {100,20,20,75}};

glm::umat3x4 mod_com={200,50,25,200}; 


enum pintypes { // Icons for each // Ref,ptr, each
    event=0,//
    res=1, // Resource
    mod=2  // modifier
};
constexpr glm::umat3x4 col_from_pinty(pintypes s=pintypes::res ){return (s==pintypes::event)?ev_col:res_col}
class node : private widget_base ;
template<typename T , bool _expand>
class pin : public widget{
    public:
    constexpr bool expand = _expand; // Controls wheter or not widget can be expanded for editing  
    using ty=T;
    using ref= pin<T,_pintype>;
    using ptr=pin<T,_pintype>; 
    T d;
  glm::ivec4 bounds;
    using arrmeta = arrtype<T>;
    std::string name = typeid(T).name() ;
    
    vectvect<uint> connects; // Nodes and their pins in node
    pintypes pintype =pintypes::res;
    glm::umat3x4 color = col_from_pin(pintypes::res);
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
    glm::umat3x4 color = col_from_pin(pintypes::res) ;
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

#define PIN_CLSS(ty,name,pinty ) { \
class name : pin<ty>  {\
    std::string name = "##name" ; \ 
    pintypes = pintype = pintypes::pinty; \
    glm::umat3x4 color = col_from_pin(pinty) ; \
} ;
class node_canvas : public sgui::wi_canvas {

} ;


// Template parameters are tuples of pins
template <typename in_ev_tup,typename in_res_tup,typename in_mod_tup,
typename out_ev_tup,typename out_res_tup,typename out_mod_tup>
class node : virtual public widget { // Has mainexec 
    private:
    char name[] = "node";
    public:
    ivec4 bounds;
       // Every node defines this;
    typedef void (*func)(void) ;

#ifdef STRATA_NODE_UNDO
    typedef union  {
        float fl ;
    }ty;
    typedef struct {
        pin
    } edit;
    std::vector<edit> node;

#endif 

    using inevtup = in_ev_tup;
    using inrestup = in_res_tup;
    using inmodtup = in_mod_tup;
    using outevtup = in_ev_tup;
    using outrestup = in_res_tup;
    using outmodtup = in_mod_tup;

    in_ev_tup in_event_pins;
    in_res_tup in_res_pins;
    in_mod_tup in_mods_pins;

    const size_t in_ev_size = std::tuple_size(in_ev_tup);
    const size_t in_res_size= std::tuple_size(in_res_tup);
    const size_t in_mod_size= std::tuple_size(in_mod_tup);
   
    template <size_t n>
    auto get_inev(size_t n){return std::get<n>(this->in_event_pins);};
    template <size_t n>
    auto get_inres(size_t n){return std::get<n>(this->in_res_pins);};
    template <size_t n>
    auto get_inmod(size_t n){return std::get<n>(this->in_mods_pins);};    

    auto get_inev(char n[]){for(int i=0;i<in_ev_size;i++;){auto t = std::get<i>(this->in_event_pins);if (t.name == n){return t};};};
    auto get_inres(char n[]){for(int i=0;i<in_res_size;i++;){auto t = std::get<i>(this->in_res_pins);if (t.name == n){return t};};};
    auto get_inmod(char n[]){for(int i=0;i<in_mods_size;i++;){auto t = std::get<i>(this->in_mods_pins);if (t.name == n){return t};};};    

    out_ev_tup out_event_pins;
    out_res_tup out_res_pins;
    out_mod_tup out_mods_pins;
    const size_t out_ev_size = std::tuple_size(out_ev_tup);
    const size_t out_res_size= std::tuple_size(out_res_tup);
    const size_t out_mod_size= std::tuple_size(out_mod_tup);
    std::array<std::string, out_ev_size> out_ev_names;
    std::array<std::string, out_res_size> out_res_names;
    std::array<std::string, out_mod_size> out_mod_names;
    template <size_t n>
    auto get_outev(size_t n){return std::get<n>(this->out_event_pins);}
    template <size_t n>
    auto get_outres(size_t n){return std::get<n>(this->out_res_pins);}
    template <size_t n>
    auto get_outmod(size_t n){return std::get<n>(this->out_mods_pins);}    

    auto get_outev(char n[]){for(int i=0;i<out_ev_size;i++;){auto t = std::get<i>(this->out_event_pins);if (t.name == n){return t};};};
    auto get_outres(char n[]){for(int i=0;i<out_res_size;i++;){auto t = std::get<i>(this->out_res_pins);if (t.name == n){return t};};};
    auto get_outmod(char n[]){for(int i=0;i<out_mods_size;i++;){auto t = std::get<i>(this->out_mods_pins);if (t.name == n){return t};};};    

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

template <typename Node , typename node>
using node_cnat = node<std::tuple_cat<Node::inevtup,node::inevtup>,std::tuple_cat<Node::inrestup,node::inrestup>,std::tuple_cat<Node::inmodtup,node::inmodtup>,
std::tuple_cat<Node::outevtup,node::outevtup>,std::tuple_cat<Node::outrestup,node::outrestup>,std::tuple_cat<Node::outmodtup,node::outmodtup>> ;

template <typename Node , typename node>
node_cnat<Node,node> node_cnat_copy(Node a,node b){node_cnat<Node,node> temp;
    int i,j;
    for( i = 0;i<std::tuple_size<Node::inevtup>;i++){std::get<i>(temp.in_event_pins)=std::get<i>(a.in_event_pins);}; j =i;
    for(;i<std::tuple_size<node::inevtup>+j;i++){std::get<i>(temp.in_event_pins)=std::get<i-j>(a.in_event_pins);};

    for( i = 0;i<std::tuple_size<Node::inrestup>;i++){std::get<i>(temp.in_res_pins)=std::get<i>(a.in_res_pins);}; j =i;
    for(;i<std::tuple_size<node::inrestup>+j;i++){std::get<i>(temp.in_res_pins)=std::get<i-j>(a.in_res_pins);};

    for( i = 0;i<std::tuple_size<Node::inmodup>;i++){std::get<i>(temp.in_mod_pins)=std::get<i>(a.in_mod_pins);}; j =i;
    for(;i<std::tuple_size<node::inmodup>+j;i++){std::get<i>(temp.in_mod_pins)=std::get<i-j>(a.in_mod_pins);};

    for( i = 0;i<std::tuple_size<Node::outevtup>;i++){std::get<i>(temp.out_event_pins)=std::get<i>(a.out_event_pins);}; j =i;
    for(;i<std::tuple_size<node::outevtup>+j;i++){std::get<i>(temp.out_event_pins)=std::get<i-j>(a.out_event_pins);};

    for( i = 0;i<std::tuple_size<Node::outevtup>;i++){std::get<i>(temp.out_event_pins)=std::get<i>(a.out_event_pins);}; j =i;
    for(;i<std::tuple_size<node::outevtup>+j;i++){std::get<i>(temp.out_event_pins)=std::get<i-j>(a.out_event_pins);};

    for( i = 0;i<std::tuple_size<Node::outevtup>;i++){std::get<i>(temp.out_event_pins)=std::get<i>(a.out_event_pins);}; j =i;
    for(;i<std::tuple_size<node::outevtup>+j;i++){std::get<i>(temp.out_event_pins)=std::get<i-j>(a.out_event_pins);};
return temp;

};


// Has only resources and modifiers and one out
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_mods_tup >
class node_geom : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup> ;

template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class geom : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class tesc : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class tese : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class comp : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class task : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class mesh : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class rgen : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class rint : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class rahit : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class rchit : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class rmiss : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;
template <typename in_res_tup,typename  in_mods_tup , typename out_res_tup, typename out_res_tup,typename out_mods_tup >
class rcall : public node<NULL,in_res_tup,in_mods_tup,NULL,out_res_tup,out_mods_tup>;


template <typename inpins>
class nodeFromPins {
    node
};
class node_instance : public  node  {

    void process;
    
};


class node_canvas : private canvas{
    std::vector<node*> childs ;
    string file_path;
    string global_namespace;
    string* includes;
    enum fence_type {
        class=0,struct=1,namespace=2,function=3,;
    };
    // /* Breaks the cpu most likely :
    #ifdef STRATA_CAP_ENG_DYNAMIC_NODES
    template <typename T>
    void add_inevToNode(int pos){
         node< std::tuple_cat<this->childs[pos]::inevtup,std::tuple<T>>,this->childs[pos]::inrestup,this->childs[pos]::inmodtup,>,
        this->childs[pos]::outevtup,this->childs[pos]::outrestup,this->childs[pos]::outmodtup > temp;
        for(uint i=0;i<std::tuple_size<this->childs[pos]::inevtup>();i++){
            std::get<i>(temp.in_event_pins) = std::get<i>(*this->childs[pos].in_event_pins) ;
        };
        temp.in_res_pins = (*this->childs[pos]).in_res_pins;
        temp.in_mod_pins = (*this->childs[pos]).in_mod_pins;
        temp.out_event_pins = (*this->childs[pos]).out_event_pins;
        temp.out_res_pins = (*this->childs[pos]).out_res_pins;
        temp.out_mod_pins = (*this->childs[pos]).out_mod_pins;
        this->childs[pos] = &temp;
    };
    template <typename T>
    void add_inresToNode(int pos){
        node< this->childs[pos]::inevtup,std::tuple_cat<this->childs[pos]::inrestup, std::tuple<T>>,this->childs[pos]::inmodtup,
        this->childs[pos]::outevtup,this->childs[pos]::outrestup,this->childs[pos]::outmodtup > temp;
        for(uint i=0;i<std::tuple_size<this->childs[pos]::inrestup>();i++){
            std::get<i>(temp.in_res_pins) = std::get<i>(*this->childs[pos].in_res_pins) ;
        };
        temp.in_event_pins = (*this->childs[pos]).in_event_pins;
        temp.in_mod_pins = (*this->childs[pos]).in_mod_pins;
        temp.out_event_pins = (*this->childs[pos]).out_event_pins;
        temp.out_res_pins = (*this->childs[pos]).out_res_pins;
        temp.out_mod_pins = (*this->childs[pos]).out_mod_pins;
        this->childs[pos] = &temp;

    };
    template <typename T>
    void add_inmodToNode(int pos){
 node< this->childs[pos]::inevtup,this->childs[pos]::inrestup,std::tuple_cat<this->childs[pos]::inmodtup,std::tuple<T>>,
        this->childs[pos]::outevtup,this->childs[pos]::outrestup,this->childs[pos]::outmodtup > temp;
        for(uint i=0;i<std::tuple_size<this->childs[pos]::inmodtup>();i++){
            std::get<i>(temp.in_mod_pins) = std::get<i>(*this->childs[pos].in_mod_pins) ;
        };
        temp.in_event_pins = (*this->childs[pos]).in_event_pins;
        temp.in_res_pins = (*this->childs[pos]).in_res_pins;
        temp.out_event_pins = (*this->childs[pos]).out_event_pins;
        temp.out_res_pins = (*this->childs[pos]).out_res_pins;
        temp.out_mod_pins = (*this->childs[pos]).out_mod_pins;
        this->childs[pos] = &temp;
    };
    template <typename T>
    void add_outresToNode(int pos){
  node< this->childs[pos]::inevtup,this->childs[pos]::inrestup,this->childs[pos]::inmodtup,>,
        std::tuple_cat<this->childs[pos]::outevtup,std::tuple<T>,this->childs[pos]::outrestup,this->childs[pos]::outmodtup > temp;
        for(uint i=0;i<std::tuple_size<this->childs[pos]::outevtup>();i++){
            std::get<i>(temp.out_event_pins) = std::get<i>(*this->childs[pos].out_event_pins) ;
        };
        temp.in_event_pins = (*this->childs[pos]).in_event_pins;
        temp.in_res_pins = (*this->childs[pos]).in_res_pins;
        temp.in_mod_pins = (*this->childs[pos]).in_mod_pins;
        temp.out_res_pins = (*this->childs[pos]).out_res_pins;
        temp.out_mod_pins = (*this->childs[pos]).out_mod_pins;
        this->childs[pos] = &temp;
    };
    template <typename T>
    void add_outmodToNode(int pos){
         node< this->childs[pos]::inevtup,this->childs[pos]::inrestup,this->childs[pos]::inmodtup,
        this->childs[pos]::outevtup,std::tuple_cat<this->childs[pos]::outrestup, std::tuple<T>>,this->childs[pos]::outmodtup > temp;
        for(uint i=0;i<std::tuple_size<this->childs[pos]::outrestup>();i++){
            std::get<i>(temp.out_res_pins) = std::get<i>(*this->childs[pos].out_res_pins) ;
        };
        temp.in_event_pins = (*this->childs[pos]).in_event_pins;
        temp.in_res_pins = (*this->childs[pos]).in_res_pins;
        temp.in_mod_pins = (*this->childs[pos]).in_mod_pins;
        temp.out_event_pins = (*this->childs[pos]).out_event_pins;
        temp.out_mod_pins = (*this->childs[pos]).out_mod_pins;
        this->childs[pos] = &temp;
    };
    template <typename T>
    void add_outevToNode(int pos){
         node< this->childs[pos]::inevtup,this->childs[pos]::inrestup,this->childs[pos]::inmodtup,
        this->childs[pos]::outevtup,this->childs[pos]::outrestup,std::tuple_cat<this->childs[pos]::outmodtup,std::tuple<T>> > temp;
        for(uint i=0;i<std::tuple_size<this->childs[pos]::outmodtup>();i++){
            std::get<i>(temp.out_mod_pins) = std::get<i>(*this->childs[pos].out_mod_pins) ;
        };
        temp.in_event_pins = (*this->childs[pos]).in_event_pins;
        temp.in_res_pins = (*this->childs[pos]).in_res_pins;
        temp.in_mod_pins = (*this->childs[pos]).in_mod_pins;
        temp.out_event_pins = (*this->childs[pos]).out_event_pins;
        temp.out_res_pins = (*this->childs[pos]).out_res_pins;
        this->childs[pos] = &temp;
    };
    #endif
// */
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

};