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
        opNot=lex::ty::Not,
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
struct type;

struct constructor {

};
template <temp q>
struct param {
    enum ty {Template,tyname,ClassTy,Ty}
    ty t;
    struct NaType {};
    struct TempType {};
    struct AnyType{};
    template <ty T>
    struct typeOf {using ty = NaType;};
    template <>struct typeOf<Template>{using ty =TempType;}
    template <>struct typeOf<tyname>{using ty=AnyType;}
    template <>struct typeOf<ClassTy>{using ty=AnyType;}
    template <>struct typeOf<Ty>{using ty =void;}
    std::conditional<q==temp::meta,std::string,type<q>>::type arg;
    
    std::string str(){
        std::string s;
        switch(ty){
            case Bool:{s+="B";break;};case Uint:{s+="Ui";break},case tyname : {s+=ty;break}
            case Template : {s+="Temp";}
        }
        return s;
    };
    param(std::string n){if constexpr (q==temp::meta){arg=n;}}
};
template <temp q>
using param_list = pri::list<param<q>>;
template <temp q>
using arg_list = pri::list<type<q>>;
template <temp q>
struct type {
    static constexpr temp tempState = q;
    // bool Template ;
    enum ty {constructor=0,expr=1,func=2,Buffer=3,strct=4,arr=5,
        Image2D=6,Image3D=7,Sampler=8,Void=9,Float=10,Int=11,Uint=12,Bool=13,
        Vec=14,Mat=15,Ivec=16,Imat=1,Uvec=18,Umat=19,Bvec=20,Bmat=21}
//     template <ty t>
//     constexpr bool hasSwizzle(){return false;};
// template <>constexpr bool hasSwizzle<Vec>(){return true;};
// template <>constexpr bool hasSwizzle<Mat>(){return true;};
// template <>constexpr bool hasSwizzle<Ivec>(){return true;};
// template <>constexpr bool hasSwizzle<Imat>(){return true;};
// template <>constexpr bool hasSwizzle<Uvec>(){return true;};
// template <>constexpr bool hasSwizzle<Umat>(){return true;};
// template <>constexpr bool hasSwizzle<Bvec>(){return true;};
// template <>constexpr bool hasSwizzle<Bmat>(){return true;};

        template <typename T> constexpr bool hasSwizzle(){return false;}

struct baseTy ;
struct Image2DTy;
struct Image3DTy;
struct SamplerTy;
struct FloatTy;
struct IntTy;
struct UintTy;
struct BoolTy;
struct vecT;
size_t dim;std::vector<size_t> dims;

    op::tyop arr[]= {op::ty::con} 
    std::string name ; 
    std::vector<param<q>> prms;
    std::enable_if<q==temp::meta,bool>::type tempTy;
    ty t;
    accSpec acc=accSpec::public;
    std::vector<type<q>> ts;
    std::vector<type<q>> methods;
    std::vector<type<q>> constructors;
    size_t alignment;

    
    
    struct swizzle {
    enum c {
        x= 0,y= 1,z= 2,w= 3,
        r= 0,g= 1,b= 2,a= 3,
        u= 0,v= 1,
        s= 0,t= 1,p= 2,q= 3,
    };
    //xyzw,rgba,
    static const size_t swiz_err=100;
    size_t swizz(char c) {
        switch(c){
case 'x' :{return 0;};
case 'y' :{return 1;};
case 'z' :{return 2;};
case 'w' :{return 3;};
case 'r' :{return 0;};
case 'g' :{return 1;};
case 'b' :{return 2;};
case 'a' :{return 3;};
case 'u' :{return 0;};
case 'v' :{return 1;};
case 's' :{return 0;};
case 't' :{return 1;};
case 'p' :{return 2;};
case 'q' :{return 3;};
        }
        return swize_err;
    };
    size_t size;
    std::vector<size_t > swi;
    bool operator==(type<inst>& f){
        if(s.size()<=f.dim)
    };
     
    swizzleTy(std::string s,type<inst>& i){
        for(char c : s){
            size_t h = siwzz(c);
            if(h!=swiz_err){
                if(h<=i.dim){swi.push_back(h);}
                else{syserr.err<err::t::swizzle_fortype>()}
            }
            else{syserr.err<err::t::swizzle_notexist>()}
        };
    };

};


    template <bool Name>
    bool approxEq(type<q>& s){
        if(t != s.t){return false;}
        if(t>=14){if(dims!=s.dims){return false;}}
        if constexpr(Name){
            if(s.name != name){return false;}
        };
        return true;
    };
    bool tyEq(type<q>& s){
            if(ts.size()!= s.ts.size()){return false;}
        pri::list<type<q>>::iter tit = ts.begin();
        pri::list<type<q>>::iter sit = s.ts.begin();
        while(tit!=ts.end() and sit != s.ts.end() ){
            if(*tit != *sit){return false;}
            ++tit;++sit;
        };
        return true;
    };    
    bool operator<=(type<q>& s){return approxEq<true>(s)}
    bool operator<(type<q>& s){
        if(!approxEq<true>(s)){return false;}
        return ts.size()<s.ts.size();
    };
    bool operator>=(type<q>& s){return approxEq<false>(s)}
    bool operator>(type<q>& s){
        if(!approxEq<false>(s)){return false;}
        return ts.size()<s.ts.size();
    };
    bool operator==(type<q>& s){
        if(!approxEq<true>(s)){return false;}
        return tyEq(s);
    };
    bool operator!=(type<q>& s){
        if(!approxEq<false>(s)){return false;}
        return tyEq(s);        
    };
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
    lex ltok; 
    size_t fpos;size_t ln,col;
    decl(lex l ) : name(l.u.name),fpos(l.filePos),ln(l.ln) ,col(l.col) :
} ;


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
    struct funcCall {

    };
    struct varRef{

    };
    
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
    size_t fpos,ln,col;
    value(lex l) name(l.u.name),fpos(l.filePos),ln(l.ln),col(l.col) {}

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
        op::ty o;
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
    template <op::ty tyOp,node::opty Op>
    node::opty getOpTy(){
        switch constexpr (Op){
            case node::opty::prefixUnary :{
                switch constexpr (tyOp){
                    case op::ty::opp :{return true;}
                    case op::ty::omm :{return true;}
                    case op::ty::opNot :{return true;}
                };
                return false;
            };
            case node::opty::postfixUnary :{
                                switch constexpr (tyOp){
                    case op::ty::opp :{return true;}
                    case op::ty::omm :{return true;}
                };
                return false;
            };
            case node::opty::binary :{
                switch constexpr (tyOp){
                    case op::ty::opp :{return false;}
                    case op::ty::omm :{return false;}
                    case op::ty::opNot :{return false;}
                };
                return true;
            };
        }
    };
    node tree;
    expr cond;
    expr<q> Not(){
        expr<q> res;
        res.tree.opT=node::opty::prefixUnary;
        res.tree.o=op::ty::opNot;
        res.tree.rhs=&tree;
        return res;
    };

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
    expr(bool s) : type(ty::literal) {bvalue=s;}
    
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
        Switch,SwitchCase,SwitchDefault,
        If,Else,ElseIf,
        Return,
        funcdecl,funcdef
        Vardecl,
        Using,TypeDef,
        DeclType,DefType,
        Layout,
        Expr
    };
    stmtty s;
    
    using  block = pri::list<stmt<q>>;
    
struct StmtDeclType {
    std::string name;
    pri::list<type<q>> inherits;
    pri::list<param<temp::meta>> params;
};
struct StmtDefType  {
    StmtDeclType decl;
    block body;

    type<temp::meta> get(){
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
    };
    type<q>::compound get(pri::list<param<temp::inst>> prms){

    };
};
using StmtExpr = expr<q>; 

    struct StmtAssign {expr<q> lhs;expr<q> rhs;};
    struct StmtWhile{stmt<q> condition;}
    struct StmtFor {stmt<q> init; stmt<q> condition;stmt<q> incr;
        block body;
    };
    struct StmtForRange {
        stmt<q> stmVarDecl;
        expr<q> ref;
        block body; 
    };
    struct StmtDo {
        pri::variant<StmttFor,StmtWhile> loop;
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
        bool ConstExpr;bool Virtual=false;bool Final=false;bool Static=false;
        std::vector<param<q>> prms;
        type<q>* return;
        pri::list<varDecl<q>> args;
        varDecl<q> searchArg(sdt::string n){
            for(varDecl<q> it : args){
                if(it.name)
            }
        };
    };
    struct StmtFuncDef  {
        StmtFuncDecl decl;
        block body;
        void search
    };
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
        bool Const,Static,ConstExpr;
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
    
    bool ConstExpr;
    pri::variant<StmtExpr,StmtAssign ,StmtDo,StmtWhile ,StmtFor ,StmtForRange ,StmtSwitch ,StmtIf,StmtFuncDecl,StmtFuncDef,StmtVardecl,StmtUsing,StmtDefType> var;
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

struct mStmtInclude {};
struct mStmtIf {};
struct mStmtElif {};
struct mStmtElifdef {};
struct mStmtElifndef {};
struct mStmtIfdef {};
struct mStmtIfndef {};
struct mStmtElse {};
struct mStmtEndIf{}
struct mStmtDefine {
    enum ty{            _include,_define,_if,_ifdef,_ifndef,_elif,_elifdef,_else};
    struct vart {
        using var=pri::variant<mStmtInclude,mStmtIf,mStmtDefine,mStmtElif,mStmtElifdef,mStmtElifndef,mStmtIfdef,mStmtIfndef,mStmtElse,mStmtEndIf> ;
        var vart;
        ty mty;
    };
    struct mstmt {
        pri::variant<stmt<temp::meta> ,vart> p;
        bool macro;
    };
    pri::list<mstmt> data;
};
struct mStmtVersion;

struct macroStmt {

    ty mty;
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
    bool evalCondTrue(){

    };
    using list_tup = AST_tup_list<q> ;
    list_tup tup;

    
    pri::list<type<q>> Types;
    pri::list<stmt<q>::StmtFuncDef*> Funcs;

    stmt<q>::block stmts;
    pri::stack<stmt<q>::block*> curBl;
    pri::stack<stmt<q>::stmt<q>::
    stmt<q>::block& curBlock(){return *(curBl.back());};

    template <typename astNd>
    pri::list<astNd>& get(){pri::get<pri::list<astNd>>(tup);};

    varDecl<q> findVarDecl(std::string name){

    };
    
    type<q> findTypeDecl(std::string name){

    };
    type<q> findTypeDecl(std::string name,pri::list<param<q>> ps){

    };  
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


    tu(ast<meta>& q) : {curBl.push(stmts);};
    tu(expr<q>& e) : condition(e){curBl.push(stmts);}
    tu(bool b) : condition(expr<q>(true)) {curBl.push(stmts);}
};
template <temp q>
struct ast   {
    std::filesystem::path pth;
    uint version;
    pri::deque<stmt<q>::StmtLayout> layouts;

    
pri::list<ast*> asts;

    expr<q> condition;
    bool evalCondition(){}
    // pri::list<tu> tus;

    struct metaSpace {
        type<temp::meta>* ty;
        std::vector<type<temp::inst>> insts; 
    };
    // pri::list<type<temp::meta>*, type<temp::inst>> metaSpaces;
    pri::list<metaSpace> metaSpaces;

    typeDecl<temp::meta> searchTypeDecl();
    varDecl<temp::inst> searchVarDecl();
    void add(tu u){tus.push_back(u);};
    void include(ast s){
        for(stmt<q>::StmtLayout& lyt : s.layouts){
            layouts.push_back(lyt);
            };
            for(macro& mcr : s.macros.mlist){macros.push(mcr);};
            for(tu t : s.tus){tus.push_back(t);}
    };
    void include(ast* s){
        asts->push_back(s);
    };

    tu<q> back(){return tus.back();}
    tu<q> front(){return tus.front();}
    ast(std::filesystem::path _pth) : pth(_pth){};
};


pri::list<ast<temp::meta>> asts;

void emplace_ast(std::filesystem::path pth){
    asts.emplace_back(pth);
};
// TODO
ast<temp::inst> getAst(ast<temp::meta> m){
    
};
#endif