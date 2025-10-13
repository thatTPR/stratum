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
using nstype = pri::list<type<temp::inst>>;

template <temp q>
struct param {
    enum ty {
        Typename,Type,Template
    };
    using typeTypename =  type<q>  ;
    // typedef typeUint = uint;
    using typeFloat = float;
    ty t;
    std::conditional<q==temp::meta,pri::variant<type<q>,pri::list<param<q>>>,type<q>>::type d; 
    std::string name;
    template<temp Q>
    tpye<q> getTy();
    type<q> getTy(){

    };
    std::string str(){
        switch(t){
            case ty::Typename : {return return std::string("ty");}
            case ty::Type : {return }
            case ty::Template {}
        }
    };
};

template <temp q>
using param_list = pri::list<param<q>>;

template <temp q>
struct type {
    static constexpr temp tempState = q;
    // bool Template ;

    enum ty {constructor=0,expr=1,func=2,Buffer=3,strct=4,arr=5,
        Image2D=6,Image3D=7,Sampler=8,Void=9,Float=10,Int=11,Uint=12,Bool=13,
        Ns,
        Vec=24,Mat=25,Ivec=26,Imat=27,Uvec=28,Umat=29,Bvec=30,Bmat=31}
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
        if(t>=24){if(dims!=s.dims){return false;}}
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
        type<q>* t;
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
        value<q> val;        
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
    type<q> getType(){return gettree.val.getType()};
    operator type<q>(){return getType();}
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

struct tyTemplate {

};



template <temp q>
struct stmt {
    using param_list=param_list<q>;
    enum stmtty {
        Block,NS,
        DeclType,DefType,
        Expr,Assign,
        Do,
        While,For,ForRange,
        Switch,Case,Default,
        If,Else,ElseIf,
        Return,
        FuncDecl,FuncDef,
        Vardecl,
        Using,TypeDef,
        Layout,
        
    };
    stmtty t;
using  block = pri::list<stmt<q>>;
struct StmtNS;
struct StmtDeclType;
struct StmtDefType : public StmtDeclType;
using StmtExpr = expr<q>;
struct StmtAssign;
struct StmtWhile;
struct StmtFor;
struct StmtDo;
struct StmtForRange;
struct StmtSwitch;
struct StmtCase;
struct StmtDefault;
struct StmtIf;
struct StmtElse;
struct StmtElseIf;
using StmtReturn = StmtExpr;
struct StmtFuncDecl;
struct StmtFuncDef : public StmtFuncDecl;
struct StmtVardecl;
struct StmtUsing;
struct StmtTypeDef;
struct StmtLayout;

    struct StmtNS {
        std::string name;
        block body;
        type<q> findName(std::string s){

        };
        
        operator std::string(){return this->name;}
        
    };
    struct StmtDeclType {
        std::string name;
        pri::list<type<q>> inherits;
        pri::list<param<temp::meta>> params;
    };
    struct StmtDefType : public StmtDeclType{ 
        bool Const,Static,ConstExpr;
        param_list prms;
        std::string name ;
        block body;
        type<q> t;
        type<q> findName(std::string s,stmt<temp::inst>::param_list& pl=param_list()){
            for(stmt<q>& it : body){
                if(it.t==stmtty::DefType){
                    StmtDefType& ref= pri::get<StmtDefType>(it);
                    if(ref.name==s){
                        if(pl.empty()and ref.prms.empty()){
                            return ref.t;
                        }
                        else {

                        }
                    }
                }
            };
        };
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
 
    };


    struct StmtAssign {expr<q> lhs;expr<q> rhs;

    };
    struct StmtWhile{stmt<q> condition;}// Can be Assign
    struct StmtFor {stmt<q> init; stmt<q> condition;stmt<q> incr;
        block body;
    };
    struct StmtForRange {
        stmt<q> stmVarDecl;
        expr<q> ref;
        block body; 

    };
    struct StmtDo {
        pri::variant<StmttFor,StmtWhile,StmtForRange> loop;
        block body;
    };
    
    struct StmtCase {expr<q> ConstExpr;block body;};
    
    struct StmtSwitch {bool ConstExpr;
        bool assign;value<temp::inst> vl;
        expr<q> condition; 
        block body;
    } ;
    struct StmtIf { bool ConstExpr
        bool assign;value<temp::inst> vl;
        expr<q> condition;
        block body;
    };
    struct StmtElse { bool ConstExpr;
        pri::variant<StmtIf*,StmtElseIf*> IfS;bool elIf;
        block body;

        StmtElse(StmtIf& If) : elIf(false) {pri::get<StmtIf*>(Ifs)=&If;}
        StmtElse(StmtElseIf& If) : elIf(true) {pri::get<StmtElseIf*>(Ifs)=&If;}
    };
    struct StmtElseIf : public StmtElse   {bool ConstExpr;
        bool assign;value<temp::inst> vl;expr<q> condition;
        StmtElseIf(StmtIf& If) : elIf(false) {pri::get<StmtIf*>(Ifs)=&If;}
        StmtElseIf(StmtElseIf& If) : elIf(true) {pri::get<StmtElseIf*>(Ifs)=&If;}
    };

    using arg_list = pri::list<StmtVarDecl>;
    struct StmtFuncDecl {
        bool ConstExpr;bool Virtual=false;bool Final=false;bool Static=false;
        
        param_list<q> prms;
        type<q>* return;
        pri::list<StmtVardecl> args;
        varDecl<q> searchArg(sdt::string n){
            for(varDecl<q> it : args){
                if(it.name)
            }
        };
    };
    struct StmtFuncDef : public StmtFuncDecl  {
        block body;
        StmtFuncDef(StmtFuncDecl& decl){*this=dynamic_cast<StmtFuncDef>(decl);}

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
        param_list prms;
        std::string name ;
        expr<q> expr;
        type<q> get(){};
    };
    struct StmtTypeDef {
        type<q> t;
        std::string name ;
        type<q> get(){};        
        StmtTypeDef(type<temp::inst> ty,std::string n) : t(ty),name(n) {}
    };
    // template <>
    // struct StmtLayoutTy
    struct StmtLayout {
        enum stand {std430,std140};
        enum ty {location,binding};
        enum tyT { buffer,var,uniform};
        using bufferDef = DefType;
        stand st;
        ty t;
        size_t loc;
        bool uniform;bool flat;
        pri::variant<StmtVardecl,StmtDefType> data;
    };
    
    bool ConstExpr;
    pri::variant<block,StmtNS,StmtDeclType,StmtDefType,StmtExpr,StmtAssign,StmtWhile,StmtFor,StmtDo,StmtForRange,StmtSwitch,StmtCase,StmtDefault,StmtIf,StmtElse,StmtElseIf,StmtReturn,StmtFuncDecl,StmtFuncDef,StmtVardecl,StmtUsing,StmtTypeDef,StmtLayout> var;
    stmt<temp::inst> get(ast<q>& st){
        if constexpr(q==temp::meta){

        }
        else return *this;
    };
    template <stmtty Ty>
    struct getTy {using ty = typename ty ;}
template<>struct getTy<stmtty::Block>{using ty=block;}
template<>struct getTy<stmtty::NS>{using ty=StmtNS;}
template<>struct getTy<stmtty::DeclType>{using ty=StmtDeclType;}
template<>struct getTy<stmtty::DefType>{using ty=StmtDefType;}
template<>struct getTy<stmtty::Expr>{using ty=StmtExpr;}
template<>struct getTy<stmtty::Assign>{using ty=StmtAssign;}
template<>struct getTy<stmtty::Do>{using ty=StmtDo;}
template<>struct getTy<stmtty::While>{using ty=StmtWhile;}
template<>struct getTy<stmtty::For>{using ty=StmtFor;}
template<>struct getTy<stmtty::ForRange>{using ty=StmtForRange;}
template<>struct getTy<stmtty::Switch>{using ty=StmtSwitch;}
template<>struct getTy<stmtty::Case>{using ty=StmtCase;}
template<>struct getTy<stmtty::Default>{using ty=StmtDefault;}
template<>struct getTy<stmtty::If>{using ty=StmtIf;}
template<>struct getTy<stmtty::Else>{using ty=StmtElse;}
template<>struct getTy<stmtty::ElseIf>{using ty=StmtElseIf;}
template<>struct getTy<stmtty::Return>{using ty=StmtReturn;}
template<>struct getTy<stmtty::FuncDecl>{using ty=StmtFuncDecl;}
template<>struct getTy<stmtty::FuncDef>{using ty=StmtFuncDef;}
template<>struct getTy<stmtty::Vardecl>{using ty=StmtVardecl;}
template<>struct getTy<stmtty::Using>{using ty=StmtUsing;}
template<>struct getTy<stmtty::TypeDef>{using ty=StmtTypeDef;}
template<>struct getTy<stmtty::Layout>{using ty=StmtLayout;}

        
    template <stmtty Ty>
    getTy<Ty>::ty get(){return pri::get<getTy<Ty>::ty>(var);};
  
    // struct fileRange  {
    //     size_t filePos;
    //     size_t linestart,lineend;
    //     std::filesystem::path pathFile;
    //     fileRange(size_t s,size_t e,std::filesystem::path pth) : linestart(s) , lineend(e) pathFile(path) {}  
    // };
    // std::enable_if<q==temp::meta,fileRange>::type range;
    std::enable_if<q==temp::meta,parList>::type paramters;

    template <typename StmtT>stmtty getTy();
template<> void getTy<block>(){return stmtty::Block;}
template<> void getTy<StmtNS>(){return stmtty::NS;}
template<> void getTy<StmtDeclType>(){return stmtty::DeclType;}
template<> void getTy<StmtDefType>(){return stmtty::DefType;}
template<> void getTy<StmtExpr>(){return stmtty::Expr;}
template<> void getTy<StmtAssign>(){return stmtty::Assign;}
template<> void getTy<StmtWhile>(){return stmtty::While;}
template<> void getTy<StmtFor>(){return stmtty::For;}
template<> void getTy<StmtForRange>(){return stmtty::ForRange;}
template<> void getTy<StmtDo>(){return stmtty::Do;}
template<> void getTy<StmtSwitch>(){return stmtty::Switch;}
template<> void getTy<StmtCase>(){return stmtty::Case;}
template<> void getTy<StmtDefault>(){return stmtty::Default;}
template<> void getTy<StmtIf>(){return stmtty::If;}
template<> void getTy<StmtElse>(){return stmtty::Else;}
template<> void getTy<StmtElseIf>(){return stmtty::ElseIf;}
template<> void getTy<StmtReturn>(){return stmtty::Return;}
template<> void getTy<StmtFuncDecl>(){return stmtty::FuncDecl;}
template<> void getTy<StmtFuncDef>(){return stmtty::FuncDef;}
template<> void getTy<StmtVardecl>(){return stmtty::Vardecl;}
template<> void getTy<StmtUsing>(){return stmtty::Using;}
template<> void getTy<StmtTypeDef>(){return stmtty::TypeDef;}
template<> void getTy<StmtLayout>(){return stmtty::Layout;}

template <typename StmtT> set(){t=getTy<StntT>();};

    template <typename StmtT>
    stmt(StmtT& s){
        pri::get<StmtT>(var)=s;
        set<StmtT>();
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
struct mStmtDefine {};
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

// #define AST_NODES funcDecl,funcDef,typeDecl,typeDef,varDecl,varDef; 

// template <template <typename... T> typename A >
// using AST_TEMP = typename _AST_TEMP<A,AST_NODES>;
// template <template<typename... As> typename AS,template <typename... T> typename A >
// using AST_TEMPT = typename _AST_TEMPT<AS,A,AST_NODES>;


// using AST_variant= AST_TEMP<pri::variant> ;

// template <temp q>
// using AST_tup_list= AST_TEMPT<pri::tuple,pri::list> ;


template <temp q>
struct ast   {
    std::filesystem::path pth;
    uint version;
    pri::deque<stmt<q>::StmtLayout> layouts;

    stmt<q>::StmtNS global;
    pri::list<ast*> asts;


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

 
    pri::list<type<q>> Types;
    pri::list<stmt<q>::StmtFuncDef> Funcs;

    stmt<q>::block stmts;
    pri::stack<stmt<q>::block*> curBl;
    stmt<q>::block& curBlock(){return *(curBl.back());};

    template <typename astNd>
    pri::list<astNd>& get(){pri::get<pri::list<astNd>>(tup);};

    varDecl<q> findVarDecl(nstype name){

    };
    
    type<q> findTypeDecl(nstype name){

    };
    type<q> findTypeDecl(nstype name,pri::list<param<q>> ps){

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
    template <typename StmtT>
    void push_back(StmtT&& St){curBl.back()->push_back(St);}
    template <typename StmtT,typename... Ts>
    void emplace_back(Ts... args){push_back(StmtT(args...));};


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