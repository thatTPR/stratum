#pragma once
#include "nodes_editor.hpp"
#include <acqres/vg2.hpp>

#define MEMBER(type,member) STRCT_MEMBER(type,member) STRCT_REF(type,member)
#define NODE(type )
#define NODE(type, members, ...) NODE(type, ) NODE(member) ONE(NODE,__VA_ARGS__)  // TODO make work for all maybe 
class node_vg {
       // Every node defines this;
    typedef vgv (*func)(glm::dvec2 ,shape_at , std::string name,g,polyline,rect,ellipse,path,textpath,uvec2) ;

};
class node_expression : public dyn_node, public w_code {
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