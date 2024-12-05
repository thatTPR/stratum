// Node editor 
#include <typeinfo>
#include "../sgui_widgets.hpp"
#include "../../../lib/glm/common.hpp"
#include <cstring>
#include "../../petri/all.hpp"
#include <type_traits>
#include <memory>
#include "../backend/impl.hpp"
using namespace events;
template< typename T>
struct reftype{
    static constexpr bool ref = std::is_reference_v<T>;
    static constexpr bool ptr = std::is_pointer_v<T>;
    static constexpr bool val = !(ref || ptr);
};
uvec4 exec_stroke={200,50,25,200}; ;
uvec4 exec_fill = {0,0,200,100} ;
uvec2 exec_more = {100,20};

uvec4 event_stroke={200,50,25,100}; ;
uvec4 event_fill = {80,80,80,100} ;
ivec2 event_more = {0,0,80,75};

uvec4 res_stroke={200,50,25,200}; ;
uvec4 res_fill = {0,0,200,100} ;
uvec2 res_more = {100,20};

uvec4 func_stroke={200,50,25,200}; ;
uvec4 func_fill = {0,0,200,100} ;
uvec2 func_more = {100,20};

enum pintypes { // Icons for each // Ref,ptr, each
    event=1,
    res=3, 
};
class node : private widget_base ;
template<typename T , int _pintype>
class pin : public widget{
    public:
    T d;
    ivec4 bounds;
    using arrmeta = arrtype<T>;
    std::string name = typeid(T).name() ; 
    uint color[4];
    vect<uint> connects;
    const int pintype = _pintype;
    ivec4 data ; // h,w,pintype,pinned;
    int32_t[0] pixel_shader_ptr;
    virtual T& get_data_ref(){return *(this->d);};
    virtual T* get_data_ptr(){return *(this->d);};
    virtual T get_data(){return this->d;};

    virtual void handle(){return this->d;};
    virtual void _set_ref(pin* p){
        this->ref = p;
    pin(std::string name, T data)  {this->name =name;this->d =data;}
    pin(std::string name, T* data) {
        this->name = name ; this->d = *(data);
    };
    pin(std::string name, T& data){
        this = new pin(name,&data);
    };
    pin(std::string name, T data){
        this->data = data;this->name =  name; 
    };
    pin(T data): default{
        this->data = data;
    };
    pin(std::string name){this->name = name;};

    };
};

template <typename T >
class pinptr :public pin<T*> {
    virtual T& get_data_ref() override {return this->data;};
    virtual T* get_data_ptr() override {return this->data;};
    virtual T get_data() override  {return *(this->data);};
    virtual void handle() override {inline pin::handle();};
};
template <typename T> 
class pinref : public pin<T&>{
    virtual  T& get_data_ref() override {return this->data;};
    virtual T* get_data_ptr() override {return *(this->data);};
    virtual T get_data() override {T s = this->data; return s;};
};

class event_pin : public pin<events::event,pintype::res> {
    public:
    virtual void handle(){

    };
} ;

class event_pinptr :public pinptr<events::event,pintype::event>{

} ;
class event_pinref : public pinref<events::event,pintype::event>;


template <typeame T>
class res_pin : public pin<T,pintype::res> ;
template <typename T>
using res_pinptr = res_pin<T*,pintype::res> ;
template <typename T> 
using res_pinref = res_pin<T&,pintype::res>;
#define res(T,name) \
  using ##name_ptr res_pin_ptr<T>; \
  using ##name_rer res_pin_ref<T>; \
  using ##name res_pin<T> ; \

#define ev(T,name) \
  using ##name_ptr =event_pin_ptr<T>; \
  using ##name_ref =event_pin_ref<T>; \
  using ##name =event_pin<T> ; \

#define ptr(name) ##name_ptr
#define ref(name) ##name_ref


class node_canvas : public sgui::wi_canvas {

} ;
template <typename T>
class node :public widget,public pin<T> { // Has mainexec
    private:
    char name[] = "node";
    public:
    ivec4 bounds;
    vect<node*> left_nodes_link;
    vect<node*> right_nodes_link;
    vect<node*> exec_left, exec_right;
    bool exec;
    uint left_pin_index[20] ;  // Points to nodes;
    vect<pin*> left; 
    vect<pin*> right;
    uint right_pin_index[20];
    size_t right_size=0;
    virtual void handle(){

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

    void exec() {
        this->handle();
        for(int i = 0; i <this->exec_right->size() ; i++ ){
            (*(this->exec_right[i]))->exec();
        };
    };
    protected:
    static inline void _push_pin_left( pin* s){this->left->push(s);};
    static inline void _push_pin_right(pin* s){this->right->push(s);};
    static inline void _insert_pin_left(size_t pos, pin* s){this->left->insert(pos,s);};
    static inline void _insert_pin_right(size_t pos, pin* s){this->right->insert(pos,s);};
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
    node(ivec2 pos){
        this = new node(/*canvas,left,right*/);
    };
};

class node_expression : public node, public w_code {
    public:
    #define MAX_EXPR_SIZE 256
    char name = "expression";
    char expr[MAX_EXPR_SIZE] ;
    virtual void handle(){

    };
    static bool get_pin_from_name(char* name, pin* left_right, pin* p  ){
        size_t t;
        if(this->left == left_right){t= this->left_size;}
        else {t= this->right_size;};
        for ( int i=0 ; i<t ; i++ ){
            if(strcmp(left_right[i]->name, name){
                p = left_right[i];
                return true; 
            }
        };
        return false;
        
    };
    struct expr {
        pin* pins[20];int pinsize;
        int iop[48][2];int opsize;  // op name
         // dot.nxyzw n is index to name 
        int iparen[20][3];int parensize; int pmax;// begin close depth
    };
    expr expression;
    
    enum operators {
            plus=1,
            minus=2,
            multiply=3,//*
            power=4,// ^
            divide=5,// /
            mod =6, // %
            root=7,// /%
            dot=8, // .
            comma=9, // ,
            eq=10 , // =
            lt=11, // <
            gt=12, // >
            question=14,
            colon=15,
            semicolon=16,
    }; // support swizzle
    static bool eval_expr(struct expr x){
        auto val ;

        
        int par[pmax][20];int pars[20]; 
        for(int i =0 ; i<20 ; i++){
            leafpars[i] = 0;
        };
        /*
        int depth=0; 
        bool cond; 
            for(int i = 0 ; i < x.parensize ; i++){
                if(x.iparen[i][1]< x.iparen[i+1][1]  ) {
                    leafpar[depth][leafpars[depth]] = i;leafpars[depth]++;
                };
            };
        int i=0;
        for(depth = 1 ; cond ; depth++) {
            for(int j = depth ; j > 0  ; j-- ){
                for (int k=0 ; k<leafpars[j] ; k++){
                    bool c = false;
                    for(int m = 0 ; i < leafpars[j-1] ; m++){
                        if(leafpar[j][k] == leafpar[j-1][m]){
                            c = true;
                        };
                    };
                    if(c){leafpar[j][leafpars[j]] = x.iparen[i];leafpars[j]++;
                    }
                };
            };
            int sum =0 ;
            for(int i =0; i<=depth;i++){
                sum+=leafpars[i];
            } ;
            if(sum == x.parensize){
                cond==false ;break;
            };
            i++;
            if(i>=20){i=0;depth++}
        };*/
        
        for (int i = 0 ; i < x.parensize ; i++){
            par[x.iparen[i][2]][pars[x.iparen[i][2]]] = i;
            pars[x.iparen[i][2]]++;
        }; // x.pins[x.iparen[leafpar[0,1]]]

        int opit=0 ;int dotit=0;int parenit = 0;
        for (int i = pmax-1 ; i>=0 ; i--){
        for(int j = 0 ; j <leafpars[i];j++){
            if(x.pins[par[i][j]] == nullptr){return false;};
            
            bool condition = true;
            while (condition){
                if(iop[opit][1]==i){
                    switch(iop[opit][1]){
                        case operators::plus :{
                            if(iop[opit][1] == iop[opit+1][1]) {
                                switch (iop[opit+1][1]){
                                    case operators::plus: {++};
                                    case operators::eq: {+=};
                                }
                            };
                        };
                        case operators::power :{
                            ^
                        };
                        case operators::gt :{
                            if(iop[opit][1] == iop[opit+1][1]) {
                                if (iop[opit+1][1] == operators::eq){
                                    >=;
                                }
                            }
                            else >
                            
                        };
                        case operators::lt :{
                            if(iop[opit][1] == iop[opit+1][1]) {
                                if (iop[opit+1][1] == operators::eq){
                                    <=;
                                }
                            }
                            else <
                        };
                        case operators::multiply :{
                            if(iop[opit][1] == iop[opit+1][1]) {
                                if (iop[opit+1][1] == operators::eq){
                                    *=;
                                }
                            };
                            else {*}
                        };
                        case operators::divide :{
                            if(iop[opit][1] == iop[opit+1][1]) {
                                if (iop[opit+1][1] == operators::eq){
                                    /=;
                                };
                                
                            };
                        };
                        case operators::question :{
                            ?;
                        };
                        case operators::colon :{
                            : 
                        };
                        case operators::power :{
                            ^
                        };
                    };

                   
                    condition = false;}
                if(idot[opit][0]==i){condition = false;};
                if(condition == false) {}

                if(iop[opit]<i){opit++;};
                if(iop[opit]>i){opit--;};
                
            };
        };
        };
    };
    static void parse_expr(){
        enum token {
            name ,
            number,
            values,
            operator
        };
        // #define OP 0  // Operation
        // #define OPI 1 
        // #define DOTI 2 
        // #define DOTX 3 // Swizzle:
        // #define DOTY 4
        // #define DOTZ 5
        // #define DOTW 6 
        // #define PARB 7 // Begin
        // #define PARC 8 // Close
        // #define PARD 9 // Depth
        // int ast[MAX_EXPR_SIZE/20][10] ;
        pin* pins[MAX_EXPR_SIZE/9]; // names_s
        char names[MAX_EXPR_SIZE/9][20] ; int names_s=0;
        int iop[48][2]; int indop=0; // op name
        int idot[48][5]; int inddot; // .nxyzw or nv   n:index of ptr, v: pointer value of member
        int iparen[20][3]; int indparen=0; int pmax = 0// begin close depth

        bool space =false;int popen[20]; int popit=0 ;
        char c[20] ncur; size_t ncur = 0; 
        pin* name_handle(){
            if(pins[names_s] != nullptr ){return pins[names_s];}
            for(int j =0 ; j < ncur ; j++){
                names[names_s][j] = c[j];
            };
                bool yes = true; pin* res;
            for(int k = 0 ; k <this->left_size ; i++){
                for(int  = 0 ; m < 20; i++ ){
                    if(names[names_s][j] != this->left[k][m] ) {yes = false;continue;}
                } ;
                if(yes == true){res = this->left[k] break;}
            };
            names_s++ ; ncur=0;
            if(yes == false){return nullptr;}
            return res;
        };
        for( int i = 0 ; i <sizeof(this->expr) / sizeof(this->expr[0]) ; i++){  
            if(isalpha(this->expr[i]) ){
                if(space == true){
                    space = false;
                if(dot){
                    bool con = true;int it = 0;
                    while(con){
                        switch(this->expr[i]){
                        case 'x':{idot[inddot][it]=1;it++;i++;continue;};
                        case 'y':{idot[inddot][it]=2;it++;i++;continue;};
                        case 'z':{idot[inddot][it]=3;it++;i++;continue;};
                        case 'w':{idot[inddot][it]=4;it++;i++;continue;};
                        con = false; 
                        };
                    };
                    i-- ; continue;
                }
                else c[ncur] = this->expr[i];ncur++;
                continue;
                } ;
            }   ;         
            if(isspace(this->expr[i])){
                if(is_space ==false){
                    pins[names_s] = name_handle();
                };
                space = true; dot = false;

                continue;
            };
            
            switch(this->expr[i]){ 
                case '(':{iparen[indparen][0]=names_s+1 ;popen[popit] = indparen;indparen++;popit++ ; pmax = popit>pmax?popit:pmax; }
                case ')':{popit-- ;  iparen[popen[popit]][1]=names_s ; iparen[popen[popit]][2] = popit;  }
                case '.':{idot[inddot][0]=names_s; inddot++;dot = true; pins[names_s] = name_handle(); continue; };
                case '=':{iop[indop][0]=operators::eq;       iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} 
                case '+':{iop[indop][0]=operators::plus;     iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case '-':{iop[indop][0]=operators::power;    iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case '>':{iop[indop][0]=operators::gt;       iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ; 
                case '<':{iop[indop][0]=operators::lt;       iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ; 
                case '*':{iop[indop][0]=operators::multiply; iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case '/':{iop[indop][0]=operators::divide;   iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case '?':{iop[indop][0]=operators::question; iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case ':':{iop[indop][0]=operators::colon;    iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case '^':{iop[indop][0]=operators::power;    iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
                case '%':{iop[indop][0]=operators::mod;      iop[indop][1]=names_s ;iop[indop][2]=indparen; indop++; pins[names_s] = name_handle(); continue;} ;
            };
        };
        this->expression = {pins,names_s,iop,indop,iparen,indparen};
    };

    virtual void exec(){

    };
    virtual void draw(){

    };
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