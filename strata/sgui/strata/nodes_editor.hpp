// Node editor 
#include "../sgui_widgets.hpp"
#include "../../../lib/glm/common.hpp"
#include <cstring>
#include "../../petri/all.hpp"
#include <type_traits>
#include <memory>
template< typename T>
struct reftype{
    static constexpr bool ref = std::is_reference_v<T>;
    static constexpr bool ptr = std::is_pointer_v<T>;
    static constexpr bool val = !(ref || ptr);
};

enum pintypes { // Icons for each // Ref,ptr, each
    event=1,
    function=2,
    res=3, 
    exec=4,
}
class node : private widget_base ;
template<typename T >
class pin : public widget,public code{
    public:
    T type;
    
    using arrmeta = arrtype<T>;
    char* name ; size_t namesize;
    uint color[4];
    unsigned short int o; // order of array
    unsigned short int o2; // order of data
    
    int pintype;
    int* pixel_shader_ptr;
    virtual T& get_data_ref(){return *(this->data);};
    virtual T* get_data_ptr(){return *(this->data);};
    virtual T get_data(){return this->data;};
    virtual void handle();
    void draw();
    void calc();
    virtual void _set_ref(pin* p){
        this->ref = p;
    pin(char* name, T* data){
        this->name = name ; this->namesize = sizeof(name)/sizeof(name[0]);
    };
    pin(char* name, T& data){
        this = new pin(name,&data);
    };
    pin(char* name, T data){
        this->data = data;this->name =  name; this->namesize = sizeof(name);
    };
    pin(T data){
        this->data = data;
    };
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

class event_pin = pin<events::event> {
    public:
    virtual void handle(){

    };
} ;

class event_pinptr :public pinptr<events::event>{

} ;
class event_pinref : public pinptr<events::event>;

template <typename T>
class function_pin : public pin<T>{

};
template <typename T>
using func_pinptr = pin<T*> ;
template <typename T> 
using func_pinref = pin<T&>;

template <typeame T>
class res_pin : public pin<T> {

};
template <typename T>
using res_pinptr = pin<T*> ;
template <typename T> 
using res_pinref = pin<T&>;

using rt_pin = pin<void>;
using rt_pinref = pinref<void>;
using rt_pinptr = pinptr<void>;
class node_widget : public widget {
    node_widget(pin* left[], pin* right[]){
        this->left = left; this->right= right;
    }
} ;

class node :public widget_base,public pin { // Has mainexec
    private:
    static constexpr const char* name = "node";
    public:
    node* nodes;
    pin** left;  size_t left_size=0;
    uint left_pin_index[20] ;  // Points to nodes;
    pin** right; size_t right_size=0;
    uint right_pin_index[20];
    size_t right_size=0;
    virtual void exec(){

    };
    protected:
    static inline void _add_pin(pin*** member, size_t* member_s, pin& s){
        pin** p = *(member);
        *member = new pin*[*(member_s)+1];
        for(int i = 0 ;i<*(member_s);i++){
            (*member)[i] = p[i];  
        };
        (*member)[*(member_s)] = new pin(s);
        *(member_s)++;
        delete s;
    };
    static inline void _insert_pin(pin*** member, size_t* member_s,size_t pos, pin& s){
        pin** p = *(member);
        *member = new pin*[*(member_s)+1];
        for(int i =0; i <pos ; i++){
            (*member)[i] = p[i];
        };
        *member_s++;
        (*member)[pos] = new pin(s);
        for(int i = pos+1 ;i<*(member_s);i++){
            (*member)[i] = p[i-1];  
        };
        delete s;
    };
public:
    void add_pin_left(pin& s){
        this->_add_pin(&(this->left),&(this->left_size),s);
    };

    void add_pin_right(pin& s){
        this->_add_pin(&(this->right),&(this->right_size),s);
    };
    node(node_canvas* c,pin left[] , pin right[]){
        
    };
    
};
class node_expression : public node, public w_code {
    public:
    #define MAX_EXPR_SIZE 256
    char name = "expression";
    char expr[MAX_EXPR_SIZE] ;
    
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