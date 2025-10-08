#ifndef STMSL_AST
#define STMSL_AST

#include <petri/list.hpp>
#include <petri/stack.hpp>
#include <petri/variant.hpp>
#include "sys.cpp"
#include "lex.hpp"
namespace stmsl{

#include <string>
enum temp {meta,inst};

template <template <typename... T> typename A , template <temp qs> typename... ASTNODES>
using _AST_TEMP = typename A<ASTNODES<q>...>;
template <template<typename... As> typename AS,template <typename... T> typename A , template <temp qs> typename... ASTNODES>
using _AST_TEMPT = typename AS<A<ASTNODES<q>>...>;

struct op {
    enum ty {
        opdot=lex::ty::dot,
        oplus=lex::ty::plus,
        ominus=lex::ty::minus,
        oband=lex::ty::band,
        obor=lex::ty::bor,
        obxor=lex::ty::bxor,
        omul=lex::ty::mul,
        odiv=lex::ty::div,
        olt=lex::ty::ltangle,
        ogt=lex::ty::gtangle,
        opp=lex::ty::pp,
        omm=lex::ty::mm,
        opand=lex::ty::oand,
        opor=lex::ty::oor,
        opcond=lex::ty::cond,
        err,none
    }
    ty oper;
    op(lex::ty tp) {
        case::lex::plus : {oper=ty::oplus;break;}
        case::lex::minus : {oper=ty::ominus;break;}
        case::lex::band : {oper=ty::oband;break;}
        case::lex::bor : {oper=ty::obor;break;}
        case::lex::bxor : {oper=ty::obxor;break;}
        case::lex::mul : {oper=ty::omul;break;}
        case::lex::div : {oper=ty::odiv;break;}
        case::lex::ltangle : {oper=ty::olt;break;}
        case::lex::gtangle : {oper=ty::ogt;break;}
        case::lex::pp : {oper=ty::opp;break;}
        case::lex::mm : {oper=ty::omm;break;}
        case::lex::oand : {oper=ty::opoand;break;}
        case::lex::oor : {oper=ty::opoor;break;}
        default : {oper=ty::err;}
    }
};


template <temp q>
struct ref ;
template <temp q>
struct value ;

template <temp q>
struct param {
    enum pty {
        Bool,Uint,tyname,Template
    }
    pty ty;
    union {
        definition<inst>* def;
        definition<meta>* tdef;
    }u;
    std::string name;
    std::string str(){
        std::string s;
        switch(ty){
            case Bool:{s+="B";break;};case Uint:{s+="Ui";break},case tyname : {s+=ty;break}
            case Template : {s+="Temp";}
        }
        return s;
    }
};
struct varty ;
struct varmetaty;
struct functy;
struct funcmetaty;

template <temp q>
struct type {
    static constexpr temp tempState = q;
    enum ty {expr,func,Buffer,strct,arr,
        Image2D,Image3D,Sampler,Void,Float,Int,Uint,Bool,
        Vec,Mat,Ivec,Imat,Uvec,Umat,Bvec,Bmat}
    template <ty t>
    constexpr bool hasSwizzle(){return false;};
template <>constexpr bool hasSwizzle<Vec>(){return true;};
template <>constexpr bool hasSwizzle<Mat>(){return true;};
template <>constexpr bool hasSwizzle<Ivec>(){return true;};
template <>constexpr bool hasSwizzle<Imat>(){return true;};
template <>constexpr bool hasSwizzle<Uvec>(){return true;};
template <>constexpr bool hasSwizzle<Umat>(){return true;};
template <>constexpr bool hasSwizzle<Bvec>(){return true;};
template <>constexpr bool hasSwizzle<Bmat>(){return true;};


size_t dim;std::vector<size_t> dims;

struct swizzle {
    size_t size;
    std::vector<size_t> s;
    swizzle(std::string s){
        
    } 
};
    op::tyop arr[]= {op::ty::con} 
    
    std::string name ; 
    std::vector<param<q>> prms;bool tempTy=false;
    ty t;
    
    std::vector<type<q>> ts;
    size_t alignment;
    bool operator==(type<q>& s){
        if(t != s.t){return false;}
        switch(t){
            case Ty::Vec {if(dims!=s.dims){return false;}}
            case Ty::Mat {if(dims!=s.dims){return false;}}
            case Ty::IVec {if(dims!=s.dims){return false;}}
            case Ty::IMat {if(dims!=s.dims){return false;}}
            case Ty::UVec {if(dims!=s.dims){return false;}}
            case Ty::UMat {if(dims!=s.dims){return false;}}
            case Ty::BVec {if(dims!=s.dims){return false;}}
            case Ty::BMat {if(dims!=s.dims){return false;}}
        }
        if(s.name != name){return false;}
        if(ts.size()!= s.ts.size()){return false;}
        
        pri::list<type<q>>::iter tit = ts.begin();
        pri::list<type<q>>::iter sit = s.ts.begin();
        while(tit!=ts.end() and sit != s.ts.end() ){
            if(*tit != *sit){return false;}
            ++tit;++sit;
        };
        return true;
    }
    void calc_alignment(){size_t biggest=1;
        for(const type it : ts){
            if(it.alignment>biggest){biggest=it.alignment;}
        }
        alignment =biggest;
    };
};
    type<inst> get(){};
    type(type::ty _t,std::initializer_list<op::tyop> ops) :t(_t) {arr=ops;tempTy=false;};
    type(type::ty _t,std::initializer_list<param<q>> _prms) :t(_t) {prms=_prms;tempTy=true;};
};

enum AttribType {
    LayoutOnly,LayoutExcl,Every
};
enum qual {Const,in,inout,out,flat};
template <AttribType at,qual q>
struct Attrib{using ats=at;using qualty = q;};
using atConst = Attrib<AttribType::LayoutExcl,qual::Const>;
using atIn  =Attrib<AttribType::Every,qual::In>;
using atInout =Attrib<AttribType::Every,qual::Inout>;
using atOut =Attrib<AttribType::Every,qual::Out>;
using atFlat =Attrib<AttribType::LayoutOnly,qual::Flat>;
template <temp q>
struct decl {
    enum ty {func,memberFunc,constructor,strct,varDecl}
    std::vector<qual> qualifies;
    ty dty;
    type t;    
std::string TypeID(){std::string n;
    if constexpr(t.tempState == temp::meta){
        n+="<";
        for(param<q> it : t.prms){
            n+=it.str();n+=",";        }
        n[n.length()-1]=">";
    }
    switch(t.t){
case type<q>::ty::Buffer : {n="Buffer_";n+=name;
    for(type it : t.ts){n+=TypeID(it);}
}
case type<q>::ty::strct : {n="Strct_";n+=name;
    for(type it : t.ts){n+=TypeID(it);}
}
case type<q>::ty::arr : {n="Arr";n+=name;
    n+=dims[0];
    for(size_t i=1;i<n.dim;i++){n+="x";n+=dims[i];}
    break;
}
case type<q>::ty::Image2D : {n="Image2D";break;}
case type<q>::ty::Image3D : {n="Image3D";break;}
case type<q>::ty::Sampler : {n="Sampler";break;}
case type<q>::ty::Void : {n="Void";break;}
case type<q>::ty::Float : {n="Float";break;}
case type<q>::ty::Int : {n="Int";break;}
case type<q>::ty::Uint : {n="Uint";break;}
case type<q>::ty::Bool : {n="Bool";break;}
case type<q>::ty::Vec : {n="Vec";n+=dims[0];break;}
case type<q>::ty::Mat : {n="Mat";n+=dims[0];n+=dims[1];break;}
case type<q>::ty::Imat : {n="Imat";n+=dims[0];break;}
case type<q>::ty::Ivec : {n="Ivec";n+=dims[0];n+=dims[1];break;}
case type<q>::ty::Uvec : {n="Uvec";n+=dims[0];break;}
case type<q>::ty::Umat : {n="Umat";n+=dims[0];n+=dims[1];break;}
case type<q>::ty::Bvec : {n="Bvec";n+=dims[0];break;}
case type<q>::ty::Bmat : {n="Bmat";n+=dims[0];n+=dims[1];break;}
}
return n;
}
    std::string name;
} ;



template <temp q>
struct def : decl<q>{
    enum defty {specialization,fulldef };
};



template <temp q>
struct typeDecl {

};
template <temp q>
struct typeDef : typeDecl<q> {

};

struct varDecl {
    decl<inst>* obj;
    std::string name;
};
struct varDef : varDecl {
    std::vector<param<q>> ps;
    type<inst> get(){
        if constexpr (q==temp::meta){
            if(obj->t.tempTy){
                if(ps.size()!=obj->t.prms.size()){syserr.err<err::t::template_param_list_incomplete>()}
                auto t = ps.begin();
                auto temp = obj->t.prms.begin();
                for(;t!=ps.end() and (temp!=obj->t.prms.begin())){
                    if(t->ty!=temp->ty){
                        syserr.err<err::t::template_param_mismatch>();
                        
                        return;}
                    
                    ++t;++temp;
                };
            }
            else return (*this);
        }
        else {return *this;}
    }
};
template <temp q>
struct value {
    enum valuet {
        prvalue // operator expressions
        xvalue, // member.access,swizzle,arr[]
        lvalue, // variable name , function call,literal
        rvalue, // prvalue or xvalue
        glvalue,// xvalue or lvalue
        literal
    };    
    valuet vt;
    type<q>* t;
    // type<inst> val;
    
    type<q>& getType() {return *t;}
    struct dataVarVal {
        type<q>* ptr;

    };
    struct dataVar {
        std::string name;
        type<q>* ptr;
        
    };
    struct dataVarRef{
        dataVar ref;
        
    };
    struct dataMemberRef : dataVarRef {
        dataVarRef* parent;
    };
    pri::tuple<dataVarVal,dataVarRef,dataMemberRef> val;
    std::string name;

};



template <temp q>
class stmt;
template <temp q>
struct expr;

template <temp q>
struct expr {

    // type<q> ty;
    
    struct node {
        enum ConstVal {
            ConstExpr,Const,no,unknown
        };
        ConstVal cval=ConstVal::unknown;
        bool isConstExpr(){return cval==ConstVal::ConstExpr;}
        bool isConst(){return cval==ConstVal::Const;}
        op o;
        enum opty {prefixUnary,postfixUnary,binary};
        opty  opT;
        value val;        
        node* lhs;node* rhs;

        struct bfs_iter {
            pri::stack<node*> nds; 
            node& operator*(){return *(nds.back());}
            node* operator->(){return nds.back();}
            decltype(*this) operator++(){
                if(nds.back()->lhs){nds.push(nds.back()->lhs);}
                else {
                    if(nds.back()->rhs){nds.push(nds.back()->rhs);}
                    else{
                        while(nds.back()->rhs){
                            if(nds.back() == nds.prev()->lhs){
                                nds.pop();
                                if(nds.back()->rhs){nds.push(nds.back(rhs));break;}
                            }
                            else {nds.pop();}
                        }
                    }
                }
    
                return *this;
            };
            decltype(*this) operator--(){
                nds.pop();return *this;
            };


        };
        bool getConstVal(){
            // for(decltype(*this) it : *this){
                if(val.vt==valuet::literal){cval=ConstVal::Const;return true;}
                if(isConst==ConstVal::unknown){bool clhs=false;bool crhs=false;
                    if(lhs){lhs->getConstVal();
                        if(lhs->isConst() || lhs->isConstExpr()){clhs=true;}
                    }
                    else {clhs=true;}
                    if(rhs){rhs->getConstVal();
                        if(rhs->isConst() || rhs->isConstExpr()){crhs=true;}
                    }
                    else {crhs=true;}
                    if(clhs && crhs){cval=ConstVal::ConstExpr;return true;}
                }
        };
        
        node() = default;


    };
    node tree;
    expr cond;

    template <typename retTy>
    retTy parseTree(retTy(*ptr)(node& n)){
        for( : )
    };
    
    bool nodeIsConstExpr(node& n){
        if(it.isConst==node::ConstVal::unknown){n.getConstVal();}
        if(it.isConst==node::ConstVal::no){return false;}
        return true;
        
    };
    bool isConstExpr(){return nodeIsConstExpr(tree);};
        expr<inst> get(){
        if constexpr (q==temp::meta){

        }
        else return *this;
    };
    void valid(){
        if(ty.t==type::ty::expr){
            for(operand)
        }
        else {

        }
    };
    operator bool(){
        if(tree.vt==valuet::literal and (tree.ty.t==type::ty::Bool) ){return bliteral; }
    }
    bool isConstExpr(){return tree.getConstVal();}


    // LiteralConstructors:
    // expr() = default ;
    // expr(pri::deque<lex> stripped){}; 
    // expr(type _t) : ty(_t);
    // expr(bool s) : type(ty::literal) , bliteral(s){}
    
    // expr(stmsl::parser& prs,std::string s){

    // };
    // expr(ast<q> ,  std::string s){

    // };
    // template <typename T>
    // expr(T s) : type(ty::literal) {if(s){bliteral=true}else{bliteral=false}}
};


template <temp q>
struct parameterType {
    enum ty {
        Typename,uint,float,
    };
    using typeTypename =  type<q>  ;
    // typedef typeUint = uint;
    using typeFloat = float;

    pri::variant<>
};


template <temp q>
struct stmt {
    struct argList {
        struct arg {

        };
        pri::list<stmt<q>> stmts;
    };
    struct parameterList {
    struct arg {
        type<q> ty;
        std::string name; 
    };
    pri::deque<arg> args;
    };

    enum stmtty {
        Block,
        Assign,
        Do,DoWhile,DoFor,
        While,For,ForRange,
        Switch,SwitchCase,
        If,Else,ElseIf,
        Return,
        funcdecl,funcdef
        Vardecl,
        Using,DefType,TypeDef,
        Layout,
        Expr
    };
    stmtty s;

    struct block {
        pri::list<stmt<q>> stmts;
        block(pri::list<stmt<qt>> _stmts) :stmts(_stmts) {}
    };
    struct StmtAssign {expr<q> lhs;expr<q> rhs;};
    struct StmtWhile {
        expr<q> condition;
        block body;
};
    struct StmtFor {stmt<q> init; expr<q> condition;stmt<q> incr;
        block body;
    };
    struct StmtForRange {
        stmt<q> stmVarDecl;
        expr<q> ref;
        block body; 
    };
    struct StmtCase {expr<q> ConstExpr;block body;};
    struct StmtSwitch {
        expr<q> ConstExpr;
        block body;
    } ;
    struct StmtIf {
        expr<q> condition; block body;
    };
    struct StmtElse {
        StmtIf* Ifptr; block body;
    };
    struct StmtElseIf : StmtElse  {
        expr<q> condition;
    };


    struct StmtFuncDecl {
       
        std::vector<param<q>> prms;
        type<q>* return;
        argList args;
    };
    struct StmtFuncDef : StmtFuncDecl {block body;};
    struct StmtVardecl {
        enum qualif {
            Const,in,inout,out
        };
        uint qualifiers;
        type<q>* t;std::string name;
        bool Default;expr<q> DefaultValue;
    };
    struct StmtUsing {
        std::vector<param<q>> ty;
        std::string name ;
        expr<q> expr;
        type<q> get(){};
    };
    struct StmtDefType {
        param<q> prms;
        std::string name ;
        type<q> t;
        type<q> get(){};        
    };
    struct StmtTypeDef {
        type<q> t;
        std::string name ;
        type<q> get(){};        
    };
    // template <>
    // struct StmtLayoutTy
    struct Location ;
    struct Binding
    struct StmtLayout {
        enum stand {std430,std140};
        enum ty {location,binding};
        enum tyT { buffer,var,uniform}
        stand st;
        ty t;
        size_t loc;
        bool uniform;bool flat;
        pri::variant<StmtVardecl,StmtDefType> data;
    };
    struct StmtExpr {
        expr<q> ex;
        type<q> get(){return ex.tree.val.getType();};        
    };
// struct StmtReturn : StmtExpr;
    
        
    pri::variant<StmtAssign ,StmtWhile ,StmtFor ,StmtForRange ,StmtSwitch ,StmtIf,StmtFuncDecl,StmFuncDef,StmtVardecl,StmtUsing,StmtDefType> var;
    stmt<temp::inst> get(ast<q>& st){
        if constexpr(q==temp::meta){

        }
        else return *this;
    };
    template <stmtty Ty>
    struct getTy {
using ty = typename ty ;}
template <>struct getTy<stmtty::Assign>{using ty =StmtAssign; };  
template <>struct getTy<stmtty::DoWhile>{using ty =StmtFor; };  
template <>struct getTy<stmtty::DoFor>{using ty =StmtWhile; };  

template <>struct getTy<stmtty::For>{using ty =StmtFor; };  
template <>struct getTy<stmtty::ForRange>{using ty =StmtForRange; };  
template <>struct getTy<stmtty::Switch>{using ty =StmtSwitch; };  
template <>struct getTy<stmtty::SwitchCase>{using ty =StmtSwitchCase; };  
template <>struct getTy<stmtty::If>{using ty =StmtIf; };  
template <>struct getTy<stmtty::funcdecl>{using ty =Stmtfuncdecl; };  
template <>struct getTy<stmtty::funcdef>{using ty =Stmtfuncdef; };  
template <>struct getTy<stmtty::Vardecl>{using ty =StmtVardecl; };  
template <>struct getTy<stmtty::Using>{using ty =StmtUsing; };  
template <>struct getTy<stmtty::DefType>{using ty =StmtDefType; };  
template <>struct getTy<stmtty::TypeDef>{using ty =StmtTypeDef; };  
template <>struct getTy<stmtty::Expr>{using ty =StmtExpr; };  


    template <stmtty Ty>
    getTy<Ty>::ty get(){return pri::get<getTy<Ty>::ty>(var);};
    template <typename T>
    void apply(void (*ptr)(T&)){ptr(pri::get<T>(var));}

    block get(std::string s){

    };
    struct fileRange {
        size_t filePos;
        size_t linestart,lineend;
        std::filesystem::path pathFile;
        fileRange(size_t s,size_t e,std::filesystem::path pth) : linestart(s) , lineend(e) pathFile(path) {}  
    };
    std::enable_if<q==temp::meta,fileRange>::type range;
    std::enable_if<q==temp::meta,parList>::type paramters;

     

    stmt(stmsl::parser& p,std::string s){
        range.linestart=fileRange(p.linecur,p.linecurnext,p.curFilePath);
    };

};

struct macroStmt {
    enum ty{            _include,_define,_if,_ifdef,_ifndef,_elif,_elifdef,_else};
    struct mStmtVersion;
struct mStmtInclude {

};
struct mStmtIf {};
struct mStmtDefine {};
struct mStmtElif {};
struct mStmtElifdef {};
struct mStmtIfdef {};
struct mStmtIfndef {};
struct mStmtElse {};
struct mStmtEndIf{}

};



#define AST_NODES funcDecl,funcDef,typeDecl,typeDef,varDecl,varDef; 



template <template <typename... T> typename A >
using AST_TEMP = typename _AST_TEMP<A,AST_NODES>;
template <template<typename... As> typename AS,template <typename... T> typename A >
using AST_TEMPT = typename _AST_TEMPT<AS,A,AST_NODES>;


using AST_variant= AST_TEMP<pri::variant> ;

template <temp q>
using AST_tup_list= AST_TEMPT<pri::tuple,pri::list> ;


template <temp q>
struct tu {
    expr<q> condition;
    bool evalTrue(){

    };
    using list_tup = AST_tup_list<q> ;
    list_tup tup;



    template <typename astNd>
    pri::list<astNd>& get(){pri::get<pri::list<astNd>>(tup);};

    varDecl<q> findVarDecl(std::string name){

    };
    void findTypeDecl(std::string name){

    }
    void findTypeDef(std::string name)
    void findTemptyDecl(std::string name)
    void findTemptyDefAll(std::string name)
    void findTemptyDefPartial(std::string name,pri::list<param<q>> ps){};
    

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
struct ast   {
    uint version;
    pri::deque<stmt<q>::StmtLayout> layouts;

    
struct macro {
    std::string name ,val;
    std::vector<std::string> args;
    macro(std::string _name,std::string _val) : name(_name) : val(_val) {}
    macro(std::string _name,std::string _val,std::vector<std::string> arg) : name(_name) , val(_val) , args(arg) {}
};

struct macrosl {
    pri::list<macro> mlist ;
    void push(macro m ){
        for(macro mit : mlist){
            if(m.name == mit.name){
                mit.val=m.val;return;
            };
        }
        mlist.push_back(m);
    }
};
macrosl macros;
    pri::list<tu<q>> lst;

    struct metaSpace {
        type<temp::meta>* ty;
        std::vector<type<temp::inst>> insts; 
    };
    // pri::list<type<temp::meta>*, type<temp::inst>> metaSpaces;
    pri::list<metaSpace> metaSpaces;


    void getTu(){}
    tu<q> back(){return lst.back();}
    tu<q> front(){return lst.front();}
    
}

pri::stack<ast<meta>> ast_stack;
ast<meta> curAst(){return ast_stack.back();};


#endif