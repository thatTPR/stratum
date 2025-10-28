#ifndef STMSL_AST
#define STMSL_AST
#include <initializer_list>
#include <petri/list.hpp>
#include <petri/stack.hpp>
#include <petri/variant.hpp>
#include "sys.cpp"
#include "lex.hpp"
#include "intrinsics.hpp"
namespace stmsl{

#include <string>
enum struct temp {meta,inst};

struct op {
    enum struct ty {
        opNew,opDelete,
        opbnot=lex::ty::bnot,
        oparrow=lex::ty::arrow,
        opdot=lex::ty::dot,oppack=lex::ty::pack,
        opthree=lex::ty::three,
        opeq = lex::ty::eq,
        
        oppeq=lex::ty::peq,opxoreq=lex::ty::xoreq,opmeq=lex::ty::meq,opandeq=lex::ty::andeq,oporeq=lex::ty::oreq,opNoteq=lex::ty::Noteq,opmuleq=lex::ty::muleq,opdiveq=lex::ty::diveq,
        opNot=lex::ty::Not,
        oplus=lex::ty::plus,
        opmod=lex::ty::mod,
        opmodeq=lex::ty::modeq,
        ominus=lex::ty::minus,
        oband=lex::ty::band,
        obor=lex::ty::bor,
        obxor=lex::ty::bxor,
        omul=lex::ty::mul,
        odiv=lex::ty::div,
        olt=lex::ty::ltangle,olteq=lex::ty::lteq,
        ogt=lex::ty::gtangle,ogteq=lex::ty::gteq,
        opp=lex::ty::pp,
        omm=lex::ty::mm,
        opand=lex::ty::oand,
        opor=lex::ty::oor,
        opxor = lex::ty::bxor,opoxoreq=lex::ty::xoreq,
        opcond=lex::ty::cond,opcolon=lex::ty::colon,
        oindex=lex::ty::lbrack,
        ocall = lex::ty::lparen,
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
template <temp q>
std::string getName(type<q>& ty);
using nstype = pri::deque<type<temp::inst>>;
template <temp q>
using type_list<q> = pri::deque<type<q>> ;



template <temp q>
struct param_list : public pri::deque<param<q>>;

template <template <temp> typename T>
T<temp::inst> getNode(T<temp::meta>& n);
// TODO mabe specialize separately;
template <temp q>
struct param {
    enum ty {Typename,Type,PtrToMember,Template};
    bool pack=false;
    ty t;//in param<inst> a value of Typename signfies the qualification of dependent type 
    type<q>* arg;
    value<q> val;// For ty::Type
    bool value_def;std::enable_if<q==temp::meta,param<temp::inst>>::type valdef; 
    using tyMeta=pri::variant<Enum,type<q>,value<q>> ;
    using tyInst=pri::variant<value<q>,expr<q>,type<q>>;
    std::conditional<q==temp::meta,tyMeta,tyInst>::type varg;
    std::string name;
    std::string str(){
        switch(t){
            case ty::Typename : {return return std::string("Type");}
            case ty::Type : {return std::string("Type") }
            case ty::Template {return std::string("template")}
            case ty::PtrToMember {return std::string("memberPtr")}
        }
    };
static constexpr temp other_q = q==temp::meta?temp::inst:temp::meta;
    bool operator==(param<other_q>& rhs){ if(t==ty::Type){ return (t==rhs.t)and (rhs.val<=pri::get<type<temp::inst>(rhs.arg)) and (pack==t.pack);}
        return t==rhs.t and (pack==t.pack) };
    bool operator==(param<q>& rhs){
        if(t==ty::Type){ return (t==rhs.t)and (pri::get<type<temp::inst>>(arg)==pri::get<type<temp::inst>(rhs.arg)) and (pack==t.pack);}
        return t==rhs.t and (pack==t.pack) };
    
    void operator=(expr<q>& r ){
        if constexpr(q==temp::inst){if(t==ty::Type){pri::get<expr<q>>(varg)=r;return;}}
        std::string str="Expr not assignable for"+str()+ "parameter";
         throw ValueError(str);
    };
    param(type<q>& _Ty) {ptr=&_Ty;if(q==temp::meta){
        if(ty.Template){t=ty::Template;}
        else{t=ty::Type;}}
        else{t=ty::Type;}}
    param(std::string str,ty _t) :name(str) t(_t) ;
    template <temp Q>
    param(std::string str,type<Q>& tp) : name(str) { pri::get<type<Q>>(arg)=tp;};
    template <temp Q>
    param(type<Q>& tp) : name(str) { pri::get<type<Q>>(arg)=tp;name=getName<Q>(tp);};


param(uint ref) {*this=param(_UInt);construct_type(&_UInt,ref);}
param(int ref) {*this=param(_Float);construct_type(&_Float,ref);}
param(float ref) {*this=param(_Int);construct_type(&_Int,ref);}
param(bool ref) {*this=param(_Bool);construct_type(&_Bool,ref);}
param() = default ;
};


template <temp q>
struct param_list : public pri::deque<param<q>> {
    param<q>& findByName(std::string name){for(param<q>& it : *this){if(name==it.name){return it}}
    throw MemberNotFound<param_list<q>>("In Param List");
}  
} ;
template <temp q>
struct other_q {static constexpr temp other = q==temp::meta?temp::inst:temp::meta;}
template <temp q>
bool operator==(param_list<q>& lhs , param_list<other_q<q>::other>& rhs){
    param_list::iter itr = rhs.begin();
    param_list::iter itl = lhs.begin();
    for(;itl!=lhs.end() and (itr!=rhs.end());++itl){
        if( *it!=*itr){return false;};
        ++itr;
    };
    if(itr==rhs.end() and (itl==lhs.end())){return true;}
    if constexpr (q==temp::meta){
        if(itr==rhs.end()){return false;}
        if(lhs.back().pack){
            for(;itr;++itr){if(*itr!=lhs.back()){return false}}
        }
    }
    else {
        if(itl==lhs.end()){return false;}
        if(rhs.back().pack){
            for(;itl;++itl){if(*itl!=rhs.back()){return false}}
        }
    }
    return true;
};
template <temp q>
struct stmt ;
template <temp q>
accSpec getAcc(stmt<q>& st);

template < template <temp > typename Tt>
Tt<temp::inst> getInstance(Tt<temp::meta>& f,param_list<q> plist={});


    class TypeError : public std::exception {
    std::string msg;param::ty t;
public:
    explicit TypeError(const param::ty t, const std::string& message) : msg(message) {}

    // override what() to return description
    const char* what() const noexcept override {return msg.c_str();}
};
template <temp q>
type<q> getName(std::string name,param_list<q>& plist){
    for(param<q> it : plist){if(it.name==name){
        if(it.t=param::type::Typename){
            return pri:get<type<temp::inst>(it.arg);
        }
        else {
            throw TypeError(it.t,"TypeError"); 
        }   
    }
};

template <temp q>
struct expr;


struct enmember {
    std::string name;
    expr<temp::meta> val_literal;  
};
struct Enum : public pri::deque<enmember> {
    bool isDependent;
    expr<temp::meta> findMember(std::string name){
        for(enmember& it : *this){if(it.name==name){return it.val_literal;}}
        throw MemberNotFound<Enum>("Enum Member Not Found");
    };
    operator bool (){return isDependent;}
} ;


enum AttribT {
    LayoutOnly,LayoutExcl,Every,
    ClassMember,Func,Method
};
enum qual {qStatic,qConstExpr,qConst,qin,qinout,qout,qflat,qVirtual,qOverride,qExplicit,qFinal,qFriend,qNoexcept};
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
template <>struct _Qual<qual::qExplicit> : public AttribS<AttribT::ClassMember> {};
template <>struct _Qual<qual::qVirtual> : public AttribS<AttribT::Method> {};
template <>struct _Qual<qual::qOverride> : public AttribS<AttribT::Method> {};
template <>struct _Qual<qual::qFinal> : public AttribS<AttribT::Method> {};
template <>struct _Qual<qual::qFriend> : public AttribS<AttribT::ClassMember> {};
template <>struct _Qual<qual::qNoexcept> : public AttribS<AttribT::Func> {};

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
using QOverride =Qual<qual::qOverride>
using QExplicit =Qual<qual::qExplict>
using QFinal =Qual<qual::qFinal>
using QFriend = Qual<qual::qFriend>
using QNoexcept = QUal<qual::qNoecept>
template <temp q>
struct value {
    enum ty {
        prvalue=0b100 // operator expressions
        xvalue=0b01,member,ptrmember,swizzle,arr // member.access,swizzle,arr[]
        lvalue=0b10,varRef,thisRef,funcCall,literal, // variable name , function call,literal
        rvalue, // prvalue or xvalue
        glvalue=0b11,// xvalue or lvalue
        typeValue,
    };    
    ty generalTy(ty y){
        switch(){
case ty::member : {return ty::xvalue;}
case ty::swizzle : {return ty::xvalue;}
case ty::arr : {return ty::xvalue;}
case ty::varRef : {return ty::lvalue;}
case ty::funcCall : {return ty::lvalue;}
case ty::literal : {return ty::lvalue;}
default: {return y;}
        }
    };
    ty t;
    
    type<q>* tp;
    int ref;
    bool isPtr(){return ref>0;} 
    struct funcCall {
        param_list<q> prms;
        pri::deque<expr<q>> args;
        stmt<q>* funcDecl;
    };
    using variable =stmt<q>;// Decl
    struct literal {
        pri::variant<float,uint,int> lit;enum ty{FltLit,UintLit,IntLit};ty t;
        literal(float num):t(ty::FltLit) {pri::get<float>(lit)=num;} 
        literal(uint num):t(ty::UintLit) {pri::get<uint>(lit)=num;}
        literal(int num):t(ty::IntLit) {pri::get<int>(lit)=num;}
    };
    struct accMember {
        bool temp;param_list<q> plist;
        std::string name;type<q>* it;bool resolved;
        accMember(std::string str){name=str;}
    };
    template <temp Q>
    using memberAcc = pri::deque<value<Q>::accMember> ;
    
    struct ptrMember {type<q>* tp;std::string name;}

    
    pri::variant<ptrMember,variable,funcCall,literal,memberAcc<q>> val;

    type<q>* getTp(){}//TODO
    operator bool(){

    };
    template <ty tp>void set(){t=tp;};

    template <typename T>
    value(T& v,ty p){pri::get<T>(val)=v;}
    value(type<q>& _tp){tp=&_tp;}
    value(type<q>& _tp,ty _t){tp=&_tp;t=_t;}
};


template <temp q>
struct expr {
    struct node {
        enum ConstVal {ConstExpr,Const,no,value,unknown};
        ConstVal cval=ConstVal::unknown;
        bool isConstExpr(){return cval==ConstVal::ConstExpr;}
        bool isConst(){return cval==ConstVal::Const;}
        op::ty o=op::ty::none;
        enum opty {prefixUnary,postfixUnary,binary,ternary};
        opty  opT;
        value<q> val;        
        node* lhs=nullptr;node* rhs=nullptr;
        void clear(){delete lhs;delete rhs;lhs=nullptr;rhs=nullptr;}
        operator delete(){clear();delete this;};
        bool cexpr(){
            if(cval==ConstExpr ){return true;}
            bool lC=false;bool rC=false;
            if(this->lhs!=nullptr){if((this->lhs.cval==node::ConstVal::ConstExpr){lC=true;}}
            else{if(it.opT==node::opty::prefixUnary){lC=true;}}
            if(this->rhs!=nullptr){if(this->rhs.cval==node::ConstVal::ConstExpr){rC=true;}}
            else{if(it.opT==node::opty::prefixUnary){rC=true;}}
            if(lC and rC){cval=ConstVal::ConstExpr;return true};
            else{cval=no;return false;}
        };
        
        struct bfs_iter {
            pri::stack<node*> nds; 
            node& operator*(){return *(nds.back());}
            node* operator->(){return nds.back();}
            
            decltype(*this) operator--(){nds.pop();return *this;};
            decltype(*this) operator++(){
                if(nds.back()->lhs!=nullptr){nds.push(nds.back()->lhs);}
                else if(nds.back()->rhs!=nullptr){nds.push(nds.back()->rhs);}
                else{
                        while(nds.back()->rhs==nullptr){
                            if(nds.back() == nds.prev()->lhs){
                                nds.pop();
                                if(nds.back()->rhs){nds.push(nds.back().rhs);break;}
                            }
                            else {nds.pop();}
                        }
                    }
                return *this;
            };
            decltype(*this) operator++(int){
                while(--(*this);nds.back()->rhs==nullptr;--(*this);){}
                nds.push(nds.back()->rhs);
                return *this;
            };
            decltpye(*this) operator--(int){++(*this);return *this;};

            bfs_iter(node* l){nds.push(l);}
            bfs_iter();
        };
        bfs_iter begin(){return bfs_iter(this);}
        bfs_iter end(){return bfs_iter();}
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
        node(node& arg) {*this=arg;}
        node(value<temp::meta>&& vt) : val(vt){o=op::ty::none}; 
        node(expr<q>& e)  {*this=e.tree;};
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
    node* ptr;
    value<q> val(){return tree.val;}
    void Alt(){tree.lhs=new node(tree);&ptr=tree.rhs;}
    void Start(){Alt();};
    void Close(){Alt();};
    template <node::opty cur>void _push(){tree.opT=cur;};
    template <>void _push<node::opty::prefixUnary>(){tree.opT=cur;};
    template <>void _push<node::opty::postfixUnary>(){tree.opT=cur;};
    template <>void _push<node::opty::binary>(){tree.opT=cur;};
    template <>void _push<node::opty::ternary>(){tree.opT=cur;};

        template <op::ty OpT,node::opty cur=node::opty::binary>
        void push(){_push<cur>();tree.o=OpT;};


        void pushThis(){};
        void pushExpr(expr<q>&& ref){
            if(tree.lhs==nullptr){tree.lhs=new node(ref);return;}
            tree.rhs=new node(ref);tree.lhs=new node(tree);tree.o=op::ty::none;};
            
    template <typename... T >
    void emplaceExpr(T... args){pushExpr(expr<q>(args...));}
    void addFuncCall(){
        node n ;
        n.lhs new node(tree);
        n.rhs
    };
    type<q> getType(){return tree.val.getType()};
    operator type<q>(){return getType();}
    expr<q> Not(){
        expr<q> res;
        res.tree.opT=node::opty::prefixUnary;
        res.tree.o=op::ty::opNot;
        res.tree.rhs=new node(tree);
        return res;
    };


    void validateConstExpr(){
        for(node::bfs_iter& it=tree.begin();it!=tree.end();++it){
            if(it->cexpr()){
                while(it->cexpr()){--it;};
                it.nds.push(nds.back()->rhs);continue;
            }
            if(tree.cexpr()){return ;}
        };
    };
    bool nodeIsConstExpr(node& n){
        validateConstExpr();
        if(tree.cexpr()){return true;}
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
    expr(bool s) : type(ty::literal) {bvalue=s;}
    expr(uint s) : type(ty::literal) {};
    expr(float flt) : type(ty::literal) {};
    expr(int s) : type(ty::litreal) {};
};

template <temp q>
struct stmt {
    using param_list=param_list<q>;
    enum stmtty {
        Block,NS,
        DeclOperator,DefOperator
        DeclType,DefType,
        //DeclUnion,DefUnion,
        Expr,
        Do,
        While,For,ForRange,
        Switch,Case,Default,
        If,Else,ElseIf,
        Return,Continue,
        FuncDecl,FuncDef,
        VarDecl,
        Using,TypeDef,
        Layout,SEnum,
        Try,Catch,Throw
        
    };
    stmtty t;
using  block = blck<q>;
struct StmtNS;
struct OperatorDecl;
struct OperatorDef;
struct StmtDeclType;
struct StmtDefType ;
#ifdef CXX_C
struct StmtDeclUnion ;
struct StmtDefUnion;
#endif

using StmtExpr = expr<q>;
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
struct StmtFuncDef ;
struct StmtVarDecl;
struct StmtUsing;
struct StmtTypeDef;
struct StmtLayout;
using  StmtEnum = Enum ;
struct StmtTry;
struct StmtCatch ;
struct StmtThrow;
    struct StmtNS {
        std::string name;

        pri::deque<StmtNS> usingNS;
        pri::deque<StmtNS> nss; 

        // std::enable_if<q==temp::inst,type<q> >::type types;// TODO make correct
        pri::deque<StmtVarDecl> vars;
        pri::deque<StmtFuncDecl> funcs;
        pri::deque<StmtTypeDecl> types;
     // pri::deque<StmtUnionDecl> unions; 
        pri::deque<StmtUsing> usings;
        pri::deque<StmtTypeDef> tdefs;
        block body;
        
        StmtNS& includeNS(std::string name){
            for(const StmtNS& it : nss){
                if(it.name==name){return it;};
            };
            nss.push_back(StmtNS());
            return nss.back();
        };
        type<q> findName(std::string s){
            for(stmt<q>& it:body){
                if(it.t==stmtty::DefType){
                    StmtDefType& ref=pri::get<StmtDefType>(it.var);
                    if(s==ref.name){return ref.t;}
                };
            };
        };
        StmtFuncDecl& findFunc(std::string s,pri::deque<value<q>> args){
            for(StmtFuncDecl& f : funcs){}
        };
        
        operator std::string(){return this->name;}
        
    };
    using tyty = typename std::conditional<temp::meta==q,value<q> , type<temp::inst>*>::type;
    
    struct StmtVarDecl {
        bool Const=false;;bool Static=false;bool Constexpr=false;bool in=false;bool out=false;
        tyty tp;std::string name;int ref;
        bool memberPtr;value<q> vl;
        bool Default;expr<q> DefaultValue;
        bool isPtr(){return ref>0;}
        StmtVarDecl() = default;
        StmtVarDecl(type<q>& _tp){*this=StmtVarDecl();}
    };
    
    struct arg_list : public pri::deque<StmtVarDecl>{bool pack;};

    struct Spec {
        param_list<temp::meta> plist;
        param_list<temp::inst> specplist;
    };
    template <typename SpecT>
    struct specTree {
            template <temp Q>
            struct specN {
                SpecT t;
                param<Q> prm;
                specN<temp::meta>* Metas;
                pri::deque<specN<temp::inst>> Insts;
                SpecT& get(){return t;}
                bool operator==(param<temp::inst>& p){return prm==p;}
                ~specN(){delete Metas;Insts.clear();}
            };
        specN<temp::meta> tree;
        param_list<prms> plist;
    struct ptrSpec{
        private:
        bool Meta;
        pri::variant<specN<temp::meta>*,specN<temp::inst>*> ptr; 
        public:
        
        template <temp Qt>
        using retty=typename std::conditional<Qt==temp::meta,specN<temp::meta>,pri::deque<specN,temp::inst>>::type; 
        SpecT& getSpec(){
            if(Meta){return pri::get<specN<temp::meta>*>(ptr)->t;}
            return pri::get<specN<temp::inst>*>(ptr)->t;
        };
        template <temp Qt>
        retty<Qt>& get(){
                    if(Meta){return &pri::get<specN<Qt>*>(ptr)->Metas;}
                      else {return pri::get<specN<Qt>*>(ptr)->Insts};}
        template <temp Qt>
        void update(specN<Qt>* p){if(Qt==temp::meta){Meta=true;>}else{Meta=false;}
            pri::get<specN<Qt>*>(ptr)=p;
            }
        }
    
        void insert(SpecT& ref){// TODO pack support
            ptrSpec cur;cur.update(&tree); 
            bool pM =false;
            auto proc = [&](){
                if(cur.Meta){pri::get<specN<temp::meta>*>(cur.ptr)=pri::get<specN<temp::meta>*>(cur.ptr)->Metas;}
                else {pri::get<specN<temp::meta>*>(cur.ptr)=pri::get<specN<temp::inst>*>(cur.ptr)->Metas;}
            };
            for(param<temp::inst>& p : ref.specplist){
                pM=false;
                for(param<temp::meta>& r: ref.plist){if(r==p){proc();pM=true;break;};}
                if(!pM){
                    for(specN<temp::inst>& r : cur.get<temp::inst>() ){
                        if(ref==r){cur.update(&cur.get<temp::inst>());break;}
                    };
                };
            };
            cur.getSpec()=ref;
        };
        void push(param_list<temp::meta>& ptemp,param_list<temp::inst>&& plist)
        void get( param_list<temp::inst>&& plist){
            for(param<temp::inst>& it : plist) {

            };
        };
        SpecT& getFirst(){return t;};
        delete specTree();
        specTree() = default; 
        specTree(param_list& plt) {plist=plt;};
    };
    template <typename T>
    struct SpecTreeIncl {
        bool Template;
        specTree<T> specs;
        T& get(param_list<temp::inst> plist={}){
            if(!Template){return specs.getFirst();}

        }  ;
    };

    struct StmtOperatorDef  {
        arg_list<temp::inst> args;
        block body;
    };
    struct StmtOperatorDecl : public SpecTreeIncl<StmtOperatorDef> {
        bool typeConv;
        pri::variant<type<q>,op::ty > op;
        using tType =typename std::conditional<temp::meta==q,pri::deque<StmtOperatorDef>,StmtOperatorDef>::type ;
        arg_list<temp::inst> args;
        tType defs;
        tyty rett; 
    };


    struct StmtDefType { 
        type<q> t;
        void addType(type<q>& argt){t.variables.push_back(argt);};
        type<q>& findName(std::string s){
            for(type<q>& it : t.dependnents){if(it.name==s){return it;}};
            for(type<q>& it : t.variables){if(it.name==s){return it;}};
            for(type<q>& it : t.methods){if(it.name==s){return it;}};
            for(type<q>& it : t.constructors){if(it.name==s){return it;}};
            throw  NameNotFound();
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
        }
    };
        
    struct StmtDeclType :public SpecTreeIncl<StmtDefType> {
        std::string name;
        specTree<StmtDefType> specs;
    };
        struct StmtWhile{StmtExpr condition;block body;}
        struct StmtFor {StmtExpr init; StmtExpr condition;StmtExpr incr;
            block body;
    };
    struct StmtForRange {
        StmtVarDecl vardecl;
        StmtExpr ref;
        block body; 

    };
    struct StmtDo {
        pri::variant<StmttFor,StmtWhile,StmtForRange> loop;      
    };
    struct StmtCase {expr<q> ConstExpr;block body;};
    
    struct StmtSwitch {
        bool ConstExpr=false;
        bool assign;value<temp::inst> vl;
        expr<q> condition; 
        block body;
    } ;
    struct StmtIf { 
        bool ConstExpr;
        StmtExpr condition;
        block body;
        StmtIf(expr<q> e) : condition(e) {}
    };
    struct StmtElse {
        pri::variant<StmtIf*,StmtElseIf*> IfS;bool elIf;
        block body;

        StmtElse(StmtIf& If) : elIf(false) {pri::get<StmtIf*>(Ifs)=&If;}
        StmtElse(StmtElseIf& If) : elIf(true) {pri::get<StmtElseIf*>(Ifs)=&If;}
    };
    struct StmtElseIf : public StmtElse   {
        bool ConstExpr;
        bool assign;expr<q> condition;
        StmtElseIf(StmtIf& If) : elIf(false) {pri::get<StmtIf*>(Ifs)=&If;}
        StmtElseIf(StmtElseIf& If) : elIf(true) {pri::get<StmtElseIf*>(Ifs)=&If;}
    };

    struct StmtFuncDecl : public SpecTreeIncl<StmtFuncDef> {
        bool ConstExpr=false;bool Virtual=false;bool Final=false;bool Static=false;
        bool Friend=false;
        std::string name
        param_list<q> prms;
        type<q>* ret;
        arg_list args;
        operator StmtFuncDef(){
            StmtFuncDef d;d.prms=prms;d.ret = ret;d.args=args;
            return d;
        };
        bool operator==(pri::deque<type<q>*> argts){
            if(args.size()!=args.size()){return false;}
            auto it = args.begin();
            for(type<q>*&  ite : argts){
                if(*ite!=it->tp){return false;}
                ++it;
            };
            return true;
        };
        varDecl<q> searchArg(sdt::string n){
            for(varDecl<q> it : args){
                if(it.name)
            }
        };
    };
    struct StmtFuncDef{
        arg_list args;block body;
    };
    struct StmtUsing {
        bool Typename;bool Namespace;
        param_list prms;
        std::string name ;
        tyty expr;
        type<q> get(){};
    };

    struct StmtTypeDef {
        tyty tp;
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
        stand st;
        ty t;
        tyT vart;
        size_t loc;bool in=false;bool out=false;
        bool uniform;bool flat;
        pri::variant<StmtVarDecl,StmtTypeDef> data;bool in=false,bool out=false;
        StmtLayout() = default;
    };
    struct StmtTry{
        block<q> body;
        pri::deque<StmtCatch> catches;
    };
    struct StmtCatch {
    SttmVarDecl var;
    block<q> body;
    };
    struct  StmtThrow {
        expr<q> val;
        StmtThrow(expr<q>&& _val)  {val=_val;}
    };

    
        
    accSpec acc=accSpec::Public;
    using allvar =pri::variant<block,StmtLayout,StmtNS,StmtFuncDecl,StmtFuncDef,StmtVarDecl,StmtUsing,StmtTypeDef,StmtEnum,StmtDeclType,StmtDefType,StmtExpr,StmtWhile,StmtFor,StmtDo,StmtForRange,StmtSwitch,StmtCase,StmtDefault,
    StmtIf,StmtElse,StmtElseIf,StmtReturn,StmtTry,StmtCatch,StmtThrow>;
    allvar var;
    using funcvar = pri::variant<StmtExpr,StmtWhile,StmtFor,StmtDo,StmtForRange,StmtSwitch,StmtCase,StmtDefault,StmtIf,StmtElse,StmtElseIf,StmtReturn,StmtTry,StmtCatch,StmtThrow>;
    using nsvar =  pri::variant<StmtLayout,StmtNS,StmtFuncDecl,StmtFuncDef,StmtVarDecl,StmtUsing,StmtTypeDef,StmtEnum,StmtDeclType,StmtDefType,StmtExpr,StmtWhile,StmtFor,StmtDo,StmtForRange,StmtSwitch,StmtCase,StmtDefault,
    StmtIf,StmtElse,StmtElseIf>;
    template <stmtty ty,stmtty... tys>
    bool isOneOf(stmtty st){if(st==ty){return true;}else {return isOneOf<tys...>(st);}};
    template <stmtty ty>
    bool isOneOf(stmtty st){if(st==ty){return true;}else {return false;}};
    
    template <qual ql>
    bool eval();
    template <> bool eval<qual::qStatic>(){if(!isOneOf<VarDecl>(t)){return false;}else{Static=true;;return true;}};
    template <> bool eval<qual::qConstExpr>(){if(!isOneOf<stmtty::VarDecl,stmtty::If,smtty::ElseIf,stmtty::Switch>(t);){return false;}else{ConstExpr=true;;return true;}};
    template <> bool eval<qual::qConst>(){Const=true;;return true;};
    template <> bool eval<qual::qin>(){if(!isOneOf<stmtty::VarDecl,stmtty::Layout>(t)){return false;}else{in=true;return true;}};
    template <> bool eval<qual::qinout>(){if(!isOneOf<stmtty::VarDecl,stmtty::Layout>(t)){return false;}else{in=true;out=true;return true;}};
    template <> bool eval<qual::qout>(){if(!isOneOf<stmtty::VarDecl,stmtty::Layout>(t)){return false;}else{out=true;return true;}};
    template <> bool eval<qual::qflat>(){if(!isOneOf<stmtty::Layout>(t)){return false;}else{in=true;return true;}};
    template <> bool eval<qual::qFriend>(){if(!isOneOf<stmtty::FuncDef,stmtty::TypeDecl>(t)){return false;}else{return true;}};
    template <> bool eval<qual::qExplicit>(){if(!isOneOf<stmtty::FuncDef>(t)){return false;}else{return true;}};
    template <> bool eval<qual::qVirtual>(){if(!isOneOf<stmtty::FuncDef>(t)){return false;}else{return true;}};
    template <> bool eval<qual::qFinal>(){if(!isOneOf<stmtty::FuncDef,OperatorDecl>()){return false;}else{;return true;}};
    template <> bool eval<qual::qNoexcept>(){if(!isOneOf<stmtty::FuncDecl,OperatorDecl>()){return false;}else{return true;}}
    bool push_qual(qual ql){
        switch(ql){
case qual::qStatic :{return eval<qual::qStatic>();}
case qual::qConstExpr :{return eval<qual::qConstExpr>();}
case qual::qConst :{return eval<qual::qConst>();}
case qual::qin :{return eval<qualq::in>();}
case qual::qinout :{return eval<qual::qinout>();}
case qual::qout :{return eval<qual::qout>();}
case qual::qflat :{return eval<qual::qflat>();}
case qual::qExplicit:{return eval<qual::qExplicit>();}
case qual::qFriend :{return eval<qual::qFriend>();} 
case qual::qVirtual :{return eval<qual::qVirtual>();} 
case qual::qFinal :{return eval<qual::qFinal>();} 
        }
        return false;
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
    stmt(StmtT&& s) : acc(accSpec::public){
        pri::get<StmtT>(var)=s;
        set<StmtT>();
    };
    stmt() = default ;
};


template <temp q>
struct type {
    static constexpr temp tempState = q;
    bool Template ;
    bool dependentType;//Set if type is dependent of superType
    enum ty {//constructor=0,expr=1,
        vec=0,
        func=2,Buffer=3,strct=4,arr=5,
        Image2D=6,Image3D=7,Sampler=8,
        Param,Ns,Alias,enum,
        // Vec=24,Mat=25,Ivec=26,Imat=27,Uvec=28,Umat=29,Bvec=30,Bmat=31
    }
    enum prim {Void=9,Float=10,Int=11,Uint=12,Bool=13}

    template <prim PrimT>struct primType {using type =void;}
    template <>struct primType<prim::Float> {using type =float;};
    template <>struct primType<prim::Int> {using type =int;};
    template <>struct primType<prim::Uint> {using type =uint;};
    template <>struct primType<prim::Bool> {using type =bool;};

        

    op::tyop arr[] ;
    std::string name ; 
    param_list<q> prms;
    std::enable_if<q==temp::meta,bool>::type tempTy;
    std::enable_if<q==temp::meta,pri::deque<type<temp::inst>>::type insts;
    ty t;
    // prim pt;
    // accSpec acc=accSpec::public;
    struct spec {
        type<q> q;
        param_list<temp::meta> plist;
        param_list<temp::inst> specl;
        bool operator==(param_list<temp::inst>& pl);
        bool operator<=(param_list<temp::inst>& pl);
        bool isCloser(spec& ot,param_list<temp::inst>& pl){
            size_t sot=0;
            for(param<temp::inst> it : ot.specl){
                for(param<temp::meta> ite : ot.plist){
                    if(specl)
                };
            };

        };
    };
    bool isTemplate=false;
    bool isUnion=false;
    // enum TYPE {compound,pod,member}
    // TYPE varType;
    bool compound;
    struct inher {
        accSpec acc;type<q>* t;
    };
            
        pri::deque<inher> inherits;
        pri::deque<spec> specs;
        pri::deque<stmt<q>::StmtTypeDecl> frndsClasss;// DeclType
        pri::deque<stmt<q>::StmtFuncDecl> frndsFunctions; // DeclFunction
        pri::deque<stmt<q>::StmtOperatorDecl> frndsFunctions; // DeclFunction
    
        pri::deque<stmt<q>::StmtUsing> using;// Usings stmts
        pri::deque<stmt<q>> tdefs;// Usings TypeDef
        pri::deque<Enum> Enums; pri::deque<Enum> EnumClss;
        
        pri::deque<stmt<q>> variables;// Has type variableDecl
        pri::deque<stmt<q>> methods;// Has type FuncDecl
        pri::deque<stmt<q>> operators;// Has type StmtOperatorDecl
        
        pri::deque<stmt<q>> constructors;//Has Type FuncDecl 
        pri::dequq<stmt<q>> destructors;//Has Type FuncDecl

        pri::variant<type<q>,Compound> data;

    size_t alignment=1;size_t size;
    void calcAlignment(){alignment=1;
        for(type<q> it : ts  ){it.calcAlignment();if(it.alignment>alignment){alignment=it.alignment;}}};
    void calcSize(){size=0;
        for(type<q> it : ts  ){it.calcAlignment();size+=it.size;}};};


    template <temp Qr,temp Qs>
    type<Qr> get(parameter_list<Qs>& plist){
        for(spec& it : this->specs){
            if(it==plist){return it;}
        };
        for(spec& it : this->specs){
            if(it<=plist){return it;}
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

    bool valid_param(param_list<temp::inst>& plist){
        param_list<q>::iter titer= prms.begin(); 
        for(const auto& it : plist){
            if(it.t!=titer->t){return false;}
            ++titer;
        };
        for(;titer;++titer){
            if(!titer->value_default){return false;}
        }
        return true;
    };
    template <temp Qt,temp Qp>
    type<Qt> get(param_list<Qp>& plist){
        
        if(Qp==temp::meta){
            if(Qp==temp::meta)
            type<Qt> h ;h.prms=plist;
        }
        else {
            if(!this->valid_param(plist)){throw std::logic_error("Param List Invalid");}
            if(Qt==temp::inst){ // Replace Params
                size_t =0;
                for(param<Qp>& it : plist){
                    
                };
            }
            else {

            }
        };
    };
   
    
    type(std::string str, prim _tp) : name(str) , pt(_tp)  {}
    type(std::string str, ty _tp) : name(str) , t(tp)  {}


    type(type<q> __ty,pri::deque<size_t> _dims){*this=__ty;dims=_dims;}

    type(std::string _name,prim _ty,param_list<q> _prms) :t(_t) {prms=_prms;tempTy=true;pt=_ty;};
    type(std::string _name,ty _ty,param_list<q> _prms) :t(_t) {prms=_prms;tempTy=true;t=_ty;};  

    template <temp Qt,temp Qp>
    type(std::string _name,type<Qt> _t,param_list<Qp> _prms) :t(_t) {*this=_t.get(_prms);name=_name;};


size_t dim;pri::deque<size_t> dims;

    bool hasSwizzle(){if(t==ty::vec or(t==ty::mat)){return true;}else return false;}
    bool isCompound(){return compound;}
    
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
        return swiz_err;
    };
  
    std::vector<size_t> swizz(std::string sw){
        if(sw.size()>dim){throw SwizzleError("Swizzle ")};
        std::vector<size_t> res;
        for(char c : sw){res.push_back(swizz(c));}
        return res;
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
    template <size_t s, size_t... Ss>
    void pushSize(size_t s,size_t... Ss){
        dims.push_back(s);
        if(sizeof...(Ss)>0){pushSize(Ss);}
    }

    type(std::string str,size_t size) : t(ty::vec) name(str)  {dim=size;}
    template <size_t... Ss> 
    type(std::string str,type<temp::meta>& arrtemp,type<temp::inst>* ty,size_t ss,size_t... Ss) :t(ty::vec) dim(arrtemp=dim)  {*this=*ty;pushSize(ss,Ss...);}
    type(std::string str,size_t ss) : dim(ss) t(ty::vec) {name=str;dim=ss;}
};

template <temp Q>
std::string getName(type<Q>& tp){return tp.name;}


stmt<temp::inst>::tyty getTy(stmt<temp::meta>::tyty& r){

};


stmt<temp::inst>::block getBlock(stmt<temp::meta>::block& r){
    stmt<temp::inst>::block res;
    for(stmt<temp::meta>& rhs: r){res.push_back(getNode(rhs));}
    return res;
};
template <> stmt<temp::inst> getNode<stmt>(stmt<temp::meta>& l){
    switch(l.t){

    };
};


template <temp q>
bool operator==(stmt<q>::arg_list& argsl, pri::deque<expr<q>>& argsr){
    stmt<q>::arg_list::iter itl = argsl.begin();
    pri::deque<expr<q>>::iter itr= argsr.begin();
    for(;itl!=argsl.end() and (itr!=argsr.end);++itl){
        if(*itr!=*itl){return false;}
        ++itr;
    };
} ;
template <temp q>
accSpec getAcc(stmt<q>&  st){return st.acc;}


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
   
template <temp q,bool CEXPR>
bool ConstructorAvail(type<q> lhs,value<temp::inst>& vl,stmt<q>::StmtFuncDecl* res=nullptr){// Checks if there is a constructor for value
    for(stmt<q>& pr : lhs.constructors ) {
        stmt<q>::StmtFuncDecl& ref = pri::get<stmt<q>::StmtFuncDecl>(pr.var);
        if(CEXPR and ref.ConstExpr or !CEXPR){
            if (ref.args.size()==1 and (vl.ty==ref.args.front().tp)){
                res=&ref;return true;}
        };
    }
    return false;
};
template <temp q>
bool operator<(type<q>& lhs,value<temp::inst>& vl){// Checks if there is a constructor for value
    return ConstructorAvail<q,false>(lhs,vl);};
bool operator<=(type<q>& lhs,value<temp::inst>& vl){// Same as < but with constexpr
    return ConstructorAvail<q,true>(lhs,vl);};


    template <temp q>
    StmtVarDecl& findVarName(stmt<q>::block& b,std::string name){
        for(stmt<q>& it : b){
            if(it.t==stmtty::VarDecl){return it;}
        };
    };
struct mStmtVersion;

    enum class result {rType,rNs,rFunc,rMethod,rEnum,rVar,rValue,rErr};
    template <temp q>
    using resty = pri::variant<stmt<q>::StmtNS*,stmt<q>::StmtFuncDecl*,stmt<q>::StmtEnum*,stmt<q>::StmtVarDecl*,type<q>*,value<q>>;
    template <temp q>
    bool isPtr(result* r,resty* res){
        switch(*r){
            case result::rValue : {return pri::get<value<q>>(*res).isPtr();}
            case result::rVar : {return pri::get<stmt<q>::StmtVarDecl*>(*res)->isPtr()}
            default :{return false;}
        }
    };
    template <temp q>
    bool isCompound(result* r,resty* res){
        switch(*r){
            case result::rValue : {return pri::get<value<q>>(*res).tp->isCompound();}
            case result::rVar : {return pri::get<stmt<q>::StmtVarDecl*>(*res)->tp->isCompound()}
            case result::rType : {return pri::get<type<q>*>(*res)->isCompound();}
            default :{return false;}
        }

    };
    template <temp q>
    bool isPtrCompound(result* r,resty* res){return isPtr<q>(r,res) && isCompound<q>(r,res)};
    template <temp q>
    bool hasSwizzle(result* r,resty* res){
        switch(*r){
            case result::rValue : {return pri::get<value<q>>(*res).tp->hasSwizzle();}
            case result::rVar : {return pri::get<stmt<q>::StmtVarDecl*>(*res)->tp->hasSwizzle()}
            default :{return false;}
        }
    };
    template <temp q>
    bool hasMember(result* r,resty* res){return isCompound<q>(r,res) || hasSwizzle<q>(r,res);};
template <temp q>
struct ast   {
    uint version;
    pri::deque<stmt<q>::StmtLayout> layouts;
    stmt<q>::StmtNS global;
    
    
    
    pri::list<type<q>> Types;
    pri::list<stmt<q>::StmtFuncDecl> Funcs;
    
    struct bl {enum ty{other,Template,ns};
        stmt<q>::block* bl;
        param_list<q>* pl;
        ty t;
        bl(stmt<q>::block* _bl) t(ty::other),bl(_bl);
        bl(stmt<q>::block* _bl,param_list<q>* _pl ) t(ty::Template),bl(_bl),pl(_pl);
    };

    bool nsblck=true;bool fblck;bool swBlock;bool IfChain;
    pri::deque<bl> curBl;
    pri::deque<stmt<q>::StmtNS*> nss;
    pri::deque<stmt<q>::StmtDefType*> strcts;
    pri::deque<param_list<q>*> curtemp;
    pri::stack<stmt<q>::StmtTry*> tries;
    stmt<q>::block& curBlock(){return *(curBl.back()->bl);};
    param_list<q>& curParams(){return *(curBl.back()->pl);};

    
    



    bool pushNS(std::string name){
        if(curBl.t!=ns){return false;}
        curBl.push_back(nss.back()->includeNS(ns).body);
        return true;
    };
    
    void pushbl(stmt<q>::block& bl){curBl.emplace(&bl);}
    void pushbl(stmt<q>::block& bl,param_list<q>& pl){curBl.emplace(&bl,&pl)}
    void popbl(){
        if(curBl.back().bl==&strcts.back().body){strcts.pop_back();}
        if(curBl.back().ty==bl::ty::Template){curtemp.pop_back();}
        if(curBl.back().ty==bl::ty::ns){nss.pop_back();}
        curBl.pop();
    };

    template <typename StmtTy>void _pushStmt(StmtTy&& st ){return;};// Review
    template <>void _pushStmt<stmt<q>::StmtUsing>(stmt<q>::StmtUsing&& st ){if(nsblck){nss.back().usings.push_back(st)};};
    template <>void _pushStmt<stmt<q>::StmtDefType>(stmt<q>::StmtDefType&& st ){if(nsblck){nss.back().tdefs.push_back(st);}else{strcts.back().tdefs.push_back(st);} ;};
    template <>void _pushStmt<stmt<q>::StmtFuncDef>(stmt<q>::StmtFuncDef&& st ){if(nsblck){nss.back().funcs.push_back(st);}else{strcts.back().methods.push_back(st);};
    template <>void _pushStmt<stmt<q>::StmtIf>(stmt<q>::StmtIf&& st )            {pushbl(pri::get<stmt<q>::StmtIf>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtElse>(stmt<q>::StmtElse&& st )        {pushbl(pri::get<stmt<q>::StmtElse>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtElseIf>(stmt<q>::StmtElseIf&& st )    {pushbl(pri::get<stmt<q>::StmtElseIf>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtSwitch>(stmt<q>::StmtSwitch&& st )    {pushbl(pri::get<stmt<q>::StmtSwitch>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtCase>(stmt<q>::StmtCase&& st )        {pushbl(pri::get<stmt<q>::StmtCase>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtFor>(stmt<q>::StmtFor&& st )          {pushbl(pri::get<stmt<q>::StmtFor>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtWhile>(stmt<q>::StmtWhile&& st )      {pushbl(pri::get<stmt<q>::StmtWhile>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtForRange>(stmt<q>::StmtForRange&& st ){pushbl(pri::get<stmt<q>::StmtForRange>(curBl().back().var).body);};
    template <>void _pushStmt<stmt<q>::StmtDo>(stmt<q>::StmtDo&& st )            {pushbl(pri::get<stmt<q>::StmtDo>(curBl().back().var).body);};

    struct  {
        stmt<q>::StmtVarDecl* vd;
        stmt<q>::StmtDefType* dt;
    }ptr;
stmt<q>::StmtVarDecl& getVarDecl(){return *(ptr.vd);};
stmt<q>::StmtDefType& getDefType(){return *(ptr.dt);};
    stmt<q>& lastStmt(){return curBlock().back();}
    template <typename T>
    T last(){
        if(curBlNS){return }
    }

    template <typename StmtTy>
    void pushStmt(StmtTy&& st ){_pushStmt<StmtTy>(st);};
    template <> pushStmt(stmt<q>::StmtLayout&& ly){laoyuts.push_back(l);}
    template <qual Q,qual... Qs>
    bool pushQual(){curBlock().back().push_qual(Q);pushQual<Qs...>()};
    template <qual Q>
    bool pushQual(){curBlock().back().push_qual(Q);};

    template <typename StmtTy>
    StmtTy& curStmt(){
        pri::get<StmtTy>(curBlock().back());
    };
    bool pushQual(qual ql){return curBlock().back().push_qual(t);};
    template <typename astNd>
    pri::list<astNd>& get(){pri::get<pri::list<astNd>>(tup);};

    type<temp::inst> getTp(type<temp::meta>* t, stmt<temp::inst>::param_list pl={}){
        return t->get<temp::inst,temp::inst>(pl);
    };



    stmt<q>::StmtNS& findNs(std::string name){
        for(stmt<q>::StmtNS* it : pri::reverse(nss)){
            if(it->name == name){return *it;} 
        };
    };
    
    resty findNameFromNs(stmt<q>::StmtNS* ns,std::string name, result* rt){*rt=result::rErr;
        resty res;
        for(stmt<q>::StmtNS& it : ns->nss){
            if(it.name ==name){*rt=result::rNs;pri::get<stmt<q>::StmtNS*>(res)=&it;return res;}
        };
            for(stmt<q>& ite : it.body){
                if(ite.t==stmt<q>::VarDecl){
                    stmt<q>::StmtVarDecl* ref=pri::get<stmt<q>::StmtVarDecl*>(ite.var);
                    if(ref.name==name){*rt=result::rVar;pri::get<stmt<q>::StmtVarDecl*>(res)=ref;return res;}}
                else if(ite.t==stmt<q>::DeclType){
                    stmt<q>::StmtDeclType& ref=pri::get<stmt<q>::StmtDeclType>(ite.var)
                    if(ref.tp.name==name){*rt=result::rType;pri::get<type<q>*>(res)=&ref.tp;return res;}}
                else if(ite.t==stmt<q>::stmtty::DeclFunc){
                    stmt<q>::StmtFuncDecl& ref=pri::get<stmt<q>::StmtFuncDecl>(ite.var);
                    if(ref.tp.name==name){*rt=result::rFunc;pri::get<stmt<q>::StmtFuncDecl*>(res)=&ref;return res;}}
                else if(ite.t==stmt<q>::stmtty::SEnum){
                    stmt<q>::StmtEnum& ref=pri::get<stmt<q>::StmtEnum>(ite.var);
                    if(ref.tp.name==name){*rt=result::rEnum;pri::get<stmt<q>::StmtEnum*>(res)=&ref;return res;}}
            };        
        throw NameNotFound("FromNs");
    };
    stmt<q>::StmtFuncDecl findVariable(type<q>* typ,std::string name ,result* rt){        *rt= result::rErr;
        for(stmt<q>& it : tp->variables){
            if(it.t==stmt<q>::stmtty::VarDecl){
                if(pri::get<stmt<q>::StmtVarDecl>(it).name==name){*rt= result::rVar;pri::get<stmt<q>::StmtVarDecl>(res)= pri::get<stmt<q>::StmtVarDecl>(it);return res;}
            }
        };
        throw NameNotFound("FromVariable");
    };

    resty findNameFromTp(type<q>* tp,std::string name,result* rt){
        resty res;
        for(stmt<q>& it : tp->dependents) {
            if(it.t==stmt<q>::stmtty::TypeDef){
                *rt= result::rType;
                if(pri::get<stmt<q>::StmtTypeDef>(it).name==name){pri::get<type<q>*>(res)= &pri::get<stmt<q>::StmtTypeDef>(it).tp;return res;}
            }
            else if(it.t==stmt<q>::stmtty::Using){
                *rt= result::rType;
                if(pri::get<stmt<q>::StmtUsing>(it).name==name){pri::get<value<q>>(res)= pri::get<stmt<q>::StmtUsing>(it).expr;return res;}
            }
        };
        findVariable(tp,name,rt);
        *rt=result::rMethod;
        for(stmt<q>& it : tp->methods){
            if(it.t==stmt<q>::stmtty::FuncDecl){
                *rt= result::rVar;
                if(pri::get<stmt<q>::StmtFuncDecl>(it).name==name){pri::get<stmt<q>::StmtFuncDecl*>(res)= &pri::get<stmt<q>::StmtFuncDecl>(it);return res;}
            }
        };
        throw MemberNotFound<type<q>>("FromTp");
    };
    stmt<q>::StmtFuncDecl* findConstructor(type<q>* typ,pri::deque<type<q>*> args){
        for(stmt<q>& it : typ->constructors) {
            if(it.t==stmt<q>::stmtty::FuncDecl){
                stmt<q>::StmtFuncDecl& ref = pri::get<stmt<q>::StmtFuncDecl>(it);
                if(ref == args) {return &ref};
            }
        };
        throw MemberNotFound<type<q>>("Error");
    };
    stmt<q>::StmtFuncDecl* findMethod(type<q>* tp,std::string name,pri::deque<type<q>*> args){
        for(stmt<q>& it : typ->methods) {
            if(it.t==stmt<q>::stmtty::FuncDecl){
                stmt<q>::StmtFuncDecl& ref = pri::get<stmt<q>::StmtFuncDecl>(it);
                if((ref.name=name) and (ref == args) ) {return &ref};
            }
        };
        throw MemberNotFound<type<q>>("NSFunction");
    };
    stmt<q>::StmtFuncDecl* findFunction(stmt<q>::StmtNS* ns,std::string name,pri::deque<type<q>*> args){
        for(stmt<q>& it : ns->block) {
            if(it.t==stmt<q>::stmtty::FuncDecl){
                stmt<q>::StmtFuncDecl& ref = pri::get<stmt<q>::StmtFuncDecl>(it);
                if((ref.name=name) and (ref == args) ) {return &ref};
            }
        };
        throw MemberNotFound<stmt<q>::StmtNS>("NSFunction");
    };
    resty findName(std::string name,result* r){
        resty res;
        for(param_list<q>* it : pri::reverse(curtemp)){
            bool found=true;param<q> rs;
            try { rs=it->findByName(name);}
            catch (const MemberNotFound<param_list<q>>& e) {found=false;}
            if(found){
                if(rs.t==param<q>::ty::Type){*r=result::rValue;pri::get<value<q>>(res)=rs->val;return res}
                *r =result::rType ;pri::get<type<q>>(res)=rs.arg;return res;}
        };
        if(!strcts.empty())  {bool found=false;
                for(stmt<q>::StmtDefType& it : pri::reverse(strcts)){found=true;
                    try {res=findNameFromTp(it,name,r);}catch(const MemberNotFound& exc){found=false};
                    if(found){return res; }
                };
        };
        bool found=false;

                for(stmt<q>::StmtNS*& it : pri::reverse(nss)){found=true;
                    try {res=findNameFromNs(it,name,r);}}catch(const MemberNotFound& exc){found=false};
                    if(found){return res; }
                }
            
        
        throw NameNotFound<resty>("Global");
    };
    bool find(std::string name,resty* res, result* r){
        switch(*r){
            case result::rType : {try{*res=findNameFromTp(pri::get<type<q>>(*res),name,r);}
                catch(const MemberNotFound& e){return false;};return true;};
            case result::rNs : {{try*res=findNameFromNs(pri::get<stmt<q>::StmtNS>(n),name,r);}
                            catch(const MemberNotFound& e){return false;};return true;};
            case result::rEnum : {
                try {*res=pri::get<Enum>(n).findMember(name);}
                catch(const MemberNotFound<Enum>& exc){ return false;syserr.err(*this,exc);}
                return true;};
            case result::rErr :{try{*res=findName(name,r)}catch(const NameNotFound& e){return false};return true;}
                default : {return false;};
                // case result::rVar : {};
        }
    };
    bool find(std::string name,resty* res,result* r,lex::ty acc){

    };
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


    ast() {nss.push_back(&global);};
};

#endif