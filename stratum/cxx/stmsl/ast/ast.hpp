#ifndef STMSL_AST
#define STMSL_AST

#include <petri/list.hpp>
#include <petri/stack.hpp>
#include <petri/variant.hpp>

namespace stmsl{
/* Expressions : 
rvalue
lvalue

*/

/**Vartypes
inout
in 
out

*/

/* Prims
image2D
image3D
sampler
buffer
float
int
uint
bool

vec
matn
matnxm
ivec
imatn
imatnxm
uvec
umatn
umatnxm
bvec
bmatn
bmatnxm

*/

/*Qualifier
flat
const

typename 


*/

/// 
// temp
#include <string>
enum temp {meta,inst};


template <template <typename... T> typename A , template <temp qs> typename... ASTNODES>
using _AST_TEMP = typename A<ASTNODES<q>...>;
template <template<typename... As> typename AS,template <typename... T> typename A , template <temp qs> typename... ASTNODES>
using _AST_TEMPT = typename AS<A<ASTNODES<q>>...>;



template <temp q>
class decl ;


template <temp q>
class variable {
    std::string name; 
    typei* t;
};


class reference {

};

template <temp q>
class definition;
template <temp q>
class stmt;
template <temp q>
struct expr;

// template <temp q>
// class astNode {
//     enum variant {
//         decl,
//         def,
//         stmt,
//         expr
//     }
//     variant nty;
//     enum type {
//         func,var,constructor
//     }
//     type ty;
//     enum q {
//         cnst,flat,in,out,inout
//     }
//     q tempifier;
//     std::string name;
// };


template <temp q>
struct ref ;
template <temp q>
struct value ;


struct param {
    enum pty {
        Bool,Uint,tyname,Template
    }
    pty type;
    union {
        definition<inst>* def;
        definition<meta>* tdef;
    }u;
};


template <temp q>
struct type {
    enum ty {
        Buffer,strct,arr
    };
    ty t;
    
    enum qual {const,in,inout,out,flat};
    std::vector<qual> qual;
    size_t dim;std::vector<size_t> dims;
    private:
    pri::list<type> ts;
};

struct primtype : type<inst>  {
    enum ty {
        Image2D,Image3D,Sampler,Void,Float,Int,Uint,Bool,
        Vec,Mat,Ivec,Imat,Uvec,Umat,Bvec,Bmat}
    size_t dimx;size_t dimy;

   
    std::string name ;
    std::enable_if<q==meta,pri::list<param>>::type params;
};


template <temp q>
struct expr {
    enum valuet {
        
        prvalue // operator expressions
        xvalue, // member.access,swizzle,arr[]
        lvalue, // variable name , function call,literal
        rvalue, // prvalue or xvalue
        glvalue,// xvalue or lvalue

        literal
    };    
    type ty;
    
    bool isConst;
    valuet value;
    pri::list<expr<q>> exprs;
    operator bool(){
        if(value==valuet::literal and value){return bliteral; }
    }
    bool isConstExpr(){
        if(value==ty::literal){return true;}
        if(value==lvalue){
            for(expr<q> it : exprs){
                if(!it.isConstExpr()){return false;}
            }

        }

    }
    // LiteralConstructors:
    expr(type _t) : ty(_t);
    expr(bool s) : type(ty::literal) , bliteral(s){}
    // template <typename T>
    // expr(T s) : type(ty::literal) {if(s){bliteral=true}else{bliteral=false}}
};



template <temp q>
struct stmt {
    struct block {
        pri::list<stmt> stmts;
    };
    struct argList {
        pri::list<stmt> stmts;
    };
    struct parList {
        pri::list<stmt> stmts;
    }
    enum stmtty {
        While,For,ForRange,
        Switch,If,funcdecl,funcdef
        Vardecl,
        Vardef,
        typeNaming,usingDecl
        expr
    };
    stmtty s;
    pri::list<expr> exprs;
};

template <temp q>
struct varDecl  {
    
};
template <temp q>
struct varDef :varDecl<q> {
    varDef(varDef<meta>& vd){
        if constexpr (q==temp::inst){
            
        }
        else {*this = vd;}
    };
};


template <temp q>
struct funcBlock : stmt<q>::block {  
    pri::list<stmt<q>> stmts;
};

template <temp q>
struct funcDecl  {
    std::string name ;

    pri::list<varDecl<q>> args;

};
template <temp q>
struct funcDef : funcDecl<q>  {

};

template <temp q>
struct While : funcDef<q> ;

template <temp q>
struct For : funcDef<q> ;

template <temp q>
struct ForRange : For<q> ;

template <temp q>
struct If : funcDef<q> {
    bool ConstExpr ;
} ;

template <temp q>
struct Switch : funcDef<q> {
    bool ConstExpr ;
};


#define AST_NODES funcDecl,funcDef,varDecl,varDef; 



template <template <typename... T> typename A >
using AST_TEMP = typename _AST_TEMP<A,AST_NODES>;
template <template<typename... As> typename AS,template <typename... T> typename A >
using AST_TEMPT = typename _AST_TEMPT<AS,A,AST_NODES>;


using AST_variant= AST_TEMP<pri::variant> ;

template <temp q>
using AST_tup_list= AST_TEMPT<pri::tuple,pri::list> ;




template <temp q>
class tu {
    expr<q> condition;

    template <typename... astNds>
    using list_tup = pri::tuple<pri::list<astNds>...>;
    list_tup tup;
    enum types {

    };
    template <typename astNd>
    types get(){

    };

    struct index {
        size_t ind;
        types ty;
    };
    pri::list<index> ind;
    class iter {
        pri::list<index>::iter ; 
    };


    template <typename astNd>
    void push(astNd& s){pri::get<pri::list<astNd>>(tup).push_back(s);};
    template <typename astNd>
    void push_back(iter& it,astNd& s ){
        ind.push_back
    };

    void include(ast<q> s){}//TODO

    tu(ast<meta>& q){


    };
    tu(expr<q>& e) : condition(e){}

};
template <temp q>
using ast =pri::list<tu<q>> ;

pri::stack<ast<meta>> ast_stack;
ast<meta> curAst(){return ast_stack.back();};

}
#endif