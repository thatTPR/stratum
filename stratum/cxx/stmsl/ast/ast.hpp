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
using nstype = pri::deque<type<temp::inst>>;


template <temp q>
struct param {
    enum ty {
        Typename,Type,Template
    };
    bool pack;
    using typeTypename =  type<q>  ;
    // typedef typeUint = uint;
    using typeFloat = float;
    ty t;//in param<inst> a value of Typename signfies the qualification of dependent type or variable as a type instantiation
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
    param()
};

template <temp q>
using param_list = pri::list<param<q>>;
template <temp q>
struct acc {
    std::string name;
    param_list<q> plist;
    acc(std::string n,param_list<q> p): name(n),plist(p){}
    acc(std::string n): name(n){}

};
template <temp q>
using nsacc =pri::deque<acc<q>> ; 
using typeacc=pri::deque<type<temp::inst>> ; 

template <temp q>
struct type {
    static constexpr temp tempState = q;
    // bool Template ;
    bool depndentType;
    enum ty {constructor=0,expr=1,func=2,Buffer=3,strct=4,arr=5,
        Image2D=6,Image3D=7,Sampler=8,Void=9,Float=10,Int=11,Uint=12,Bool=13,
        Ns,Alias,
        Vec=24,Mat=25,Ivec=26,Imat=27,Uvec=28,Umat=29,Bvec=30,Bmat=31}


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
    type<inst> get(param_list<temp::inst>& plist,nstype& nsnames){

    };
    type<q> get(param<q> p) {}
    type(type::ty _t,std::initializer_list<op::tyop> ops) :t(_t) {arr=ops;tempTy=false;};
    type(type::ty _t,param_list<q> _prms) :t(_t) {prms=_prms;tempTy=true;};
};

enum AttribT {
    LayoutOnly,LayoutExcl,Every,
    ClassMember
};
enum qual {qStatic,qConstExpr,qConst,qin,qinout,qout,qflat,qVirtual,qFinal,qFriend};
template <AttribT atT>
struct AttribS {static constexpr AttribT at = atT;}
template <qual q>
struct _Qual{static constexpr AttribType at;};

template <>struct _Qual<qual::qStatic> : public AttribS<AttribT::ClassMember> {};
template <>struct _Qual<qual::qConstExpr> : public AttribS<AttribT::Every> {};
template <>struct _Qual<qual::qConst> : public AttribS<AttribT::LayoutExcl> {};
template <>struct _Qual<qual::qin> : public AttribS<AttribT::Every> {};
template <>struct _Qual<qual::qinout> : public AttribS<AttribT::Every> {};
template <>struct _Qual<qual::qout> : public AttribS<AttribT::Every> {};
template <>struct _Qual<qual::qflat> : public AttribS<AttribT::LayoutOnly> {};
template <>struct _Qual<qual::qVirtual> : public AttribS<AttribT::ClassMember> {};
template <>struct _Qual<qual::qFinal> : public AttribS<AttribT::ClassMember> {};
template <>struct _Qual<qual::qFriend> : public AttribS<AttribT::ClassMember> {};

template <qual q>
struct Qual {static constexpr qual quality = q; static constexpr AttribT at = _Qual<q>::at; }

using QStatic = Qual<qual::qStatic>
using QConstExpr = Qual<qual::qConstExpr>
using QConst = Qual<qual::qConst>
using QIn  =Qual<qual::qin>
using QInout =Qual<qual::qinout>
using QOut =Qual<qual::qout>
using QFlat =Qual<qual::qflat>
using QVirtual =Qual<qual::qVirtual>
using QFinal =Qual<qual::qFinal>
using QFriend = Qual<qual::qFriend>

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
struct funcType {
    param_list<q> params;
    type<q> retTy;
    pri::deque<decl<q>> args;  
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
    struct funcCall {
        type<q>
    };
    struct constructorCall {

    };
    
    struct varRef{
        type<q>* tptr;
    };
    
    type<q>& getType() {return *t;}
    struct VarValueRef {
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
        DeclType,DefType,DefTypeSpec
        Expr,Assign,
        Do,
        While,For,ForRange,
        Switch,Case,Default,
        If,Else,ElseIf,
        Return,
        FuncDecl,FuncDef,FuncDefSpec
        VarDecl,
        Using,TypeDef,
        Layout,
        
    };
    stmtty t;
using  block = pri::list<stmt<q>>;
struct StmtNS;
struct StmtDeclType;
struct StmtDefType : public StmtDeclType;
struct StmtDefTypeSpec : public StmtDefType;
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
struct StmtFuncDefSpec : public StmtFuncDef;
struct StmtVarDecl;
struct StmtUsing;
struct StmtTypeDef;
struct StmtLayout;

    struct StmtNS {
        std::string name;
        pri::deque<StmtNS> nss; 
        block body;
        void includeNS(StmtNS& ns);
        bool existstNS(StmtNS& ns ){
            for(StmtNS  it : nss ){
                if(it.name==ns.name){it.includeNs(ns);return true;}
            };
            return false;
        };
        void includeNS(StmtNS& ns){
            for(const StmtNS& it : ns.nss){
                if(!existsNS(it.name)){nss.push_back(it);};
            };
        };
        type<q> findName(std::string s){
            for(stmt<q>& it:body){
                if(it.t==stmtty::DefType){
                    StmtDefType& ref=pri::get<StmtDefType>(it.var);
                    if(s==ref.name){return ref.t;}
                };
            };
        };
        
        operator std::string(){return this->name;}
        
    };
    struct StmtDeclType {
        std::string name;
        pri::list<type<q>> inherits;
        pri::list<param<temp::meta>> params;
    };
    struct StmtDefType : public StmtDeclType{ 
        param_list prms;
        std::string name;
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
    struct StmtDefTypeSpec : public StmtDefType {
        param_list prmsSpec;
        StmtDefTypeSpec(StmtDefType& dt) :prms(dt.prms),name(dt.name),body(dt.body),t(dt.t){}}
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
    
    struct StmtSwitch {
        bool assign;value<temp::inst> vl;
        expr<q> condition; 
        block body;
    } ;
    struct StmtIf { 
        bool assign;value<temp::inst> vl;
        expr<q> condition;
        block body;
    };
    struct StmtElse {
        pri::variant<StmtIf*,StmtElseIf*> IfS;bool elIf;
        block body;

        StmtElse(StmtIf& If) : elIf(false) {pri::get<StmtIf*>(Ifs)=&If;}
        StmtElse(StmtElseIf& If) : elIf(true) {pri::get<StmtElseIf*>(Ifs)=&If;}
    };
    struct StmtElseIf : public StmtElse   {
        bool assign;value<temp::inst> vl;expr<q> condition;
        StmtElseIf(StmtIf& If) : elIf(false) {pri::get<StmtIf*>(Ifs)=&If;}
        StmtElseIf(StmtElseIf& If) : elIf(true) {pri::get<StmtElseIf*>(Ifs)=&If;}
    };

    using arg_list = pri::list<StmtVarDecl>;
    struct StmtFuncDecl {
        param_list<q> prms;
        type<q>* ret;
        pri::list<StmtVarDecl> args;
        operator StmtFuncDef(){
            StmtFuncDef d;d.prms=prms;d.ret = ret;d.args=args;
            return d;
        };
        varDecl<q> searchArg(sdt::string n){
            for(varDecl<q> it : args){
                if(it.name)
            }
        };
    };
    struct StmtFuncDef : public StmtFuncDecl  {
        block body;

    };
    struct StmtFuncDefSpec : public StmtFuncDef {

        param_list<q> specPrms;
        StmtFuncDefSpec(StmtFuncDef& fdef){
            prms=fdef.prms;ret=fdef.ret;args=fdef.args;body=fdef.body;            
        };
    };
    struct StmtVarDecl {
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
        pri::variant<StmtVarDecl,StmtDefType> data;
    };
    
        bool Const=false;bool in=false;bool inout=false;bool out=false;
        bool ConstExpr=false;bool Virtual=false;bool Final=false;bool Static=false;
        bool Friend=false;;

    pri::variant<block,StmtNS,StmtDeclType,StmtDefType,StmtExpr,StmtAssign,StmtWhile,StmtFor,StmtDo,StmtForRange,StmtSwitch,StmtCase,StmtDefault,StmtIf,StmtElse,StmtElseIf,StmtReturn,StmtFuncDecl,StmtFuncDef,StmtVarDecl,StmtUsing,StmtTypeDef,StmtLayout> var;
    template <stmtty ty,stmtty... tys>
    bool isOneOf(stmtty st){if(st==ty){return true;}else {return isOneOf<tys...>(st);}};
    template <stmtty ty>
    bool isOneOf(stmtty st){if(st==ty){return true;}else {return false;}};
    
    template <qual ql>
    bool eval();
    template <> bool eval<qual::qStatic>(){if(t!=stmtty::DefType){return false;}else{Static=true;;return true;}};
    template <> bool eval<qual::qConstExpr>(){if(!isOneOf<stmtty::VarDecl,stmtty::If,smtty::ElseIf,stmtty::Switch>(t);){return false;}else{ConstExpr=true;;return true;}};
    template <> bool eval<qual::qConst>(){Const=true;;return true;};
    template <> bool eval<qual::qin>(){if(!isOneOf<stmtty::VarDecl,stmtty::Layout>(t)){return false;}else{in=true;return true;}};
    template <> bool eval<qual::qinout>(){if(!isOneOf<stmtty::VarDecl,stmtty::Layout>(t)){return false;}else{inout=true;return true;}};
    template <> bool eval<qual::qout>(){if(!isOneOf<stmtty::VarDecl,stmtty::Layout>(t)){return false;}else{out=true;return true;}};
    template <> bool eval<qual::qflat>(){if(!isOneOf<stmtty::Layout>(t)){return false;}else{in=true;return true;}};
    template <> bool eval<qual::qFriend>(){if(!isOneOf<stmtty::FuncDef>(t)){return false;}else{Static=true;;return true;}};
    template <> bool eval<qual::qVirtual>(){if(!isOneOf<stmtty::FuncDef>(t)){return false;}else{Static=true;;return true;}};
    template <> bool eval<qual::qFinal>(){if(!isOneOf<stmtty::FuncDef>()){return false;}else{Static=true;;return true;}};
    bool push_qual(qual ql){
        switch(ql){
case qual::qStatic :{return eval<qual::qStatic>();}
case qual::qConstExpr :{return eval<qual::qConstExpr>();}
case qual::qConst :{return eval<qual::qConst>();}
case qual::qin :{return eval<qualq::in>();}
case qual::qinout :{return eval<qual::qinout>();}
case qual::qout :{return eval<qual::qout>();}
case qual::qflat :{return eval<qual::qflat>();}
case qual::qFriend :{return eval<qual::qFriend>();} 
case qual::qVirtual :{return eval<qual::qVirtual>();} 
case qual::qFinal :{return eval<qual::qFinal>();} 
        }
        return false;
    };
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
template<>struct getTy<stmtty::DefTypeSpec>{using ty=StmtDefTypeSpec;}
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
template<>struct getTy<stmtty::FuncDefSpec>{using ty=StmtFuncDefSpec;}
template<>struct getTy<stmtty::VarDecl>{using ty=StmtVarDecl;}
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
template<> void getTy<StmtDefTypeSpec>(){return stmtty::DefTypeSpec;}
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
template<> void getTy<StmtFuncDefSpec>(){return stmtty::FuncDefSpec;}
template<> void getTy<StmtVarDecl>(){return stmtty::VarDecl;}
template<> void getTy<StmtUsing>(){return stmtty::Using;}
template<> void getTy<StmtTypeDef>(){return stmtty::TypeDef;}
template<> void getTy<StmtLayout>(){return stmtty::Layout;}

template <typename StmtT> set(){t=getTy<StntT>();};

    template <typename StmtT>
    stmt(StmtT&& s){
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


    struct metaSpace {
        type<temp::meta>* ty;
        std::vector<type<temp::inst>> insts; 
    };
    // pri::list<type<temp::meta>*, type<temp::inst>> metaSpaces;
    pri::list<metaSpace> metaSpaces;

template <temp q>
struct ast   {
    uint version;
    pri::deque<stmt<q>::StmtLayout> layouts;
    pri::deque<stmt<q>::StmtNS> asts;
    stmt<q>::StmtNS global;
    
    
    
    typeDecl<temp::meta> searchTypeDecl();
    varDecl<temp::inst> searchVarDecl();
    void add(tu u){tus.push_back(u);};
    
    
    pri::list<type<q>> Types;
    pri::list<stmt<q>::StmtFuncDef> Funcs;
    
    stmt<q>::block stmts;
    struct bl {enum ty{other,Template,ns};
        stmt<q>::block* bl;
        param_list<q>* pl;
        ty t;
        bl(stmt<q>::block* _bl) t(ty::other),bl(_bl);
        bl(stmt<q>::block* _bl,param_list<q>* _pl ) t(ty::Template),bl(_bl),pl(_pl);
    };
    pri::stack<bl> curBl;
    pri::stack<stmt<q>::StmtNS> nss;
    pri::stack<stmt<q>::StmtDefType> strcts;
    pri::deque<param_list<q>*> curtemp;
    stmt<q>::block& curBlock(){return *(curBl.back()->bl);};
    param_list<q>& curParams(){return *(curBl.back()->pl);};
    bool pushNS(stmt<q>::StmtNS& ns){
        if(curBl.t!=ns){return false;}
        nss.back().includeNS(ns);
        nss.push_back(ns);
    };
    
    void pushbl(stmt<q>::block& bl){curBl.emplace(&bl);}
    void pushbl(stmt<q>::block& bl,param_list<q>& pl){curBl.emplace(&bl,&pl)}
    void popbl(){
        if(curBl.back().bl==&strcts.back().body){strcts.pop();}
        if(curBl.back().ty==bl::ty::Template){curtemp.pop_back();}
        if(curBl.back().ty==bl::ty::ns){nss.pop();}
        curBl.pop();
    };
    template <typename StmtTy>
    void pushStmt(StmtTy&& st){
        curBlock().push_back(st);
    };
    template <typename StmtTy>
    StmtTy& curStmt(){
        pri::get<StmtTy>(curBlock().back());
    };
    bool pushQual(qual ql){return curBlock().back().push_qual(t);};
    template <typename astNd>
    pri::list<astNd>& get(){pri::get<pri::list<astNd>>(tup);};

    type<q> findVarDecl(nstype name){

    };
    
    type<q> getType(nsacc ns){

    };
    
    void findTypeDef(std::string name)
    void findTemptyDecl(std::string name)
    void findTemptyDefAll(std::string name)
    void findTemptyDefPartial(std::string name,pri::list<param<q>> ps){};
    
    bool include(ast&& s){
        if(!s.curBl.empty()){return false;}
        this->layouts.concat(s.layouts);
        global.includeNs(s.global);
    };


    template <typename astNd>
    void push(astNd& s){pri::get<pri::list<astNd>>(tup).push_back(s);};
    template <typename StmtT>
    void push_back(StmtT&& St){curBl.back()->push_back(St);}
    template <typename StmtT,typename... Ts>
    void emplace_back(Ts... args){push_back(StmtT(args...));};


    ast() {nss.push_back(global);};
};

#endif