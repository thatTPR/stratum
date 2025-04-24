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


enum pintype { // Icons for each // Ref,ptr, each
    event=0,//
    res=1, // Resource
    mod=2  // modifier
};
enum pinsig {
    in=0,
    out=1,
    inout=2,
}
constexpr glm::umat3x4 col_from_pinty(pintypes s=pintypes::res ){return (s==pintypes::event)?ev_col:res_col;};


class node : private widget_base ;

template<typename T , pinsig ps,pintype pt,>
class pin : public widget{
    public:
    pinsig sig = ps ;
    pintype type = pt ;
    bool expanded ; // Controls wheter or not widget can be expanded for editing  
    using ty=T;
    using ref= pin<T,ps,pt>;
    using ptr=pin<T,ps,pt>; 
    T d;
  glm::ivec4 bounds;
    using arrmeta = arrtype<T>;
    std::string name = typeid(T).name() ;
    
    std::vector<uint> connects; // Nodes and their pins in node
    glm::umat3x4 color = col_from_pin(pintypes::res);
    ivec4 data ; // h,w,pintype,pinned;
    
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
template <typename T,pinsig ps>
class pinres : pin<T,ps,pintype::res>{
    
    glm::umat3x4 color = col_from_pin(pintypes::res) ;
};
template <typename T,pinsig ps>
class pinmod: public pin<T,ps,pintype::mod> {
    
    template <typename T>
     void handle(T* resourced); // eg: resourced->field + this->d;
};
template <typename T,pinsig ps>
class pinevent : public pin<T,ps,pintype::event>{
        template <typename T>
    void handle(T* modd);    // Eg : modd->field + this->d;
    
};


class node_canvas : public sgui::wi_canvas {

} ;

struct emptyNode {using empty = 0 ;};
// Template parameters are tuples of pins


#include <stratum/petri/reflect.hpp>

class variables {
    std::vector<reflect::refl> event ;
    std::vector<reflect::refl> res ;
    std::vector<reflect::refl> mod ; 

    [[__noreturn]] void addRes(reflect::refl rd){
        this->res.push_back(rd) ;
    };
    [[__noreturn]] void addEvent(reflect::refl rd){
        this->event.push_back(rd) ;
    };
    [[__noreturn]] void addMod(reflect::refl rd){
        this->mod.push_back(rd) ;
    };

};


variables vars ;


class reflnode : virtual public node {
    std::string name = "node" ;
    
    clss_refl reflcls ;
    void (*fp)(reflcls::strct) ;
     ShaderModule module ;
    

    itreflect in ;
    itreflect out ;

    bool exec; 
    std::vector<bool> incon;
    std::vector<bool> outcon;

    glm::vec2 inExec,outExec; 
    std::vector<glm::vec2> inpos; 
    std::vector<glm::vec2> outpos; 
    void execute(){
        fp(this->reflcls.strct);
    };
    void init(){
        for(const auto& r : reflcls){
            if(r.ps == pinsig::inout){
                in.add<r::ty>(r.ptr,r.ps,r.type,r.name);
                out.add<r::ty>(r.ptr,r.ps,r.type,r.name);
            };
            if(r.ps == pinsig::in){
                in.add<r::ty>(r.ptr,r.ps,r.type,r.name);
            };
            if(r.ps == pinsig::out){
                in.add<r::ty>(r.ptr,r.ps,r.type,r.name);
            };
        };
    };


    node(clss_refl _reflcls , void (*_fp)(reflcls::strct) ) : reflcls(_reflcls) , fp(_fp){this->init()}; 

};


class compNode {

    std::string name = "Composite node" ;

    std::vector<clss_refl> refclsvec;

    itreflect in ;
    itreflect out ;


    auto getIn(size_t n){
        for(const auto& i : this->in ){
            if(!n){return i;};n--;
        } ;
    };
    auto getOut(size_t n){
        for(const auto& i : this->out ){
            if(!n){return i;};n--;
        } ;
    };
    
    void execute(){
        for(const auto& s : this->refclsvec){
            a.fp(a.refcls.strct);
        };
    };
    void init(){
        for(const auto& refcls : refclsvec){
        
        for(const auto& r : reflcls){
            if(r.ps == pinsig::inout){
                in.add<r::ty>(r.ptr,r.ps,r.type,r.name);
                out.add<r::ty>(r.ptr,r.ps,r.type,r.name);
            };
            if(r.ps == pinsig::in){
                in.add<r::ty>(r.ptr,r.ps,r.type,r.name);
            };
            if(r.ps == pinsig::out){
                in.add<r::ty>(r.ptr,r.ps,r.type,r.name);
            };
        };
        };
    };
    compNode(reflnode a, reflnode b): refclsvec({a.reflcls,b.reflcls}){
        this->init();
    };
    compNode(compnode a, reflnode b) {
        this->refclsvec = a.refclsvec ;
        this->refclsvec.push_back(b.refcls);
        this->init();
    };
    compnode(compnode a, compnode b){
        this->refclsvec = a.refclsvec ;
        for(const auto & s : b.refclsvec){
            this->refclsvec.push_back(s);
        };
        this->init();
    };
    
};



class node : virtual public widget { // Nodes 
    private:
    std::string name = "node";
    public:
    ivec4 bounds;
       // Every node defines this;
    


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
   
    virtual void execute(); // Executes
    virtual void eventHandle();
    
 
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
    struct node_uni nodeUni ;
    void draw()final {
        for(int i = 0 ; i<this->nodeUni.left_size;)
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
    };





class nodeFromPins {
    node
};
class node_instance : public  node  {

    void process;
    
};

class pNode { // PluginNode
    void execute();
};  

class nodeCanvas : private canvas{
    std::vector<node*> childs ;
    string file_path;
    string global_namespace;
    string* includes;
    enum fence_type {
        class=0,struct=1,namespace=2,function=3,;
    };
    typedef std::vector<node*> selection ;
// */
    class fence : NodeEditorwidget {
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