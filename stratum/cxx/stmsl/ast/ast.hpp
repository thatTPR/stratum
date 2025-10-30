#ifndef STMSL_AST
#define STMSL_AST
#include <initializer_list>
#include <petri/list.hpp>
#include <petri/stack.hpp>
#include <petri/variant.hpp>
#include "sys.cpp"
#include "lex.hpp"
#include "intrinsics.hpp"
#include <functional>
namespace stmsl{

#include <string>
enum struct temp {meta,inst};

struct op {
    enum struct ty {
        opNew,opDelete,opNoExcept,
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
    param_list<q> pl;
    bool value_def;std::enable_if<q==temp::meta,param<temp::inst>>::type valdef; 
    using tyInst=pri::variant<value<temp::meta>,value<temp::inst>,expr<temp::meta>,type<temp::meta>,type<temp::inst>>;bool Expr;
    tyInst varg;
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
}

template <temp q>
struct expr;

struct integralT {
    enum ty {flt,Int,Double,Ch,Ty};ty t;
    enum len{Short,Long,LongLong};
    len l;sign s;
    enum sign{Signed,Unsigned};
    template <typename T>
    using mSigned=signed T;
    template <typename T>
    using mUnSigned=unsigned T;
    value<temp::meta> mt;
    bool is(type<temp::meta>& ref){};
    // integralT(type<temp::meta>)
};
struct enmember {
    std::string name;
    expr<temp::meta> cexprval;  
    enmember(std::string str) : name(str){}
};
struct EnumT : public pri::deque<enmember> {
    bool enclass=false;attrib_list ats;
    integralT intt; bool SpeqSeq=false;
    expr<temp::meta> findMember(std::string name){
        for(enmember& it : *this){if(it.name==name){return it.val_literal;}}
        throw MemberNotFound<EnumT>("Enum Member Not Found");
    };
    operator bool (){return isDependent;}
} ;
#include "stmt.hpp"

struct attrib{
    using argList = pri::deque<lex>;
    std::string name;std::string nsacc;bool Ns=false;
    argList args;
    attrib(std::string str) : name(str){};
};
struct attrib_list : public pri::deque<attrib>{
    std::string nsUse;bool useNs;
};
template <temp q>
struct lambda ;
template <temp q>
struct value {
    enum ty {anyvalue,
        prvalue=0b100 // operator expressions
        xvalue=0b01,member,ptrmember,swizzle,arr // member.access,swizzle,arr[]
        lvalue=0b10,varRef,thisRef,funcCall,literal, // variable name , function call,literal
        rvalue, // prvalue or xvalue
        glvalue=0b11,// xvalue or lvalue
        typeValue,lambdav
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
    ty t=ty::anyvalue;
    
    type<q>* tp;
    int ref;
    bool isPtr(){return ref>0;} 
    struct funcCall {
        param_list<q> prms;
        pri::deque<expr<q>> args;
        stmt<q>::StmtFuncDecl* funcDecl;
    };
    using variable =stmt<q>::StmtVarDecl*;
    struct literal {
        pri::variant<float,uint,int> lit;enum ty{FltLit,UintLit,IntLit};ty t;
        literal(float num):t(ty::FltLit) {pri::get<float>(lit)=num;} 
        literal(uint num):t(ty::UintLit) {pri::get<uint>(lit)=num;}
        literal(int num):t(ty::IntLit) {pri::get<int>(lit)=num;}
    };
    struct accMember {
        bool temp;param_list<q> plist;
        std::string name;type<q>* it;
        accMember(std::string str){name=str;}
        accMember(type<q>* _a){it=_a;}
    };
    template <temp Q>
    using accMember_list = pri::deque<value<Q>::accMember> ;
    
    using ptrMember =std::string ;
    
    #ifdef CXX_C
    using ty = pri::variant<bool,int,uint,float,std::string,char>;
    #elif
    using ty = pri::variant<bool,int,uint,float,std::string,char>;
    #endif
    pri::variant<ptrMember,variable,funcCall,literal,accMember_list<q>,lambda<q>> val;


    bool operator=(value<q>& vl){

    };
    operator bool(){};
    operator int(){};
    template <ty tp>void set(){t=tp;};
    param<temp::inst> get_prm(){
        param<temp::inst> res;res.
    }
    template <typename T>
    value(T& v,ty p){pri::get<T>(val)=v;}
    value(type<q>& _tp){tp=&_tp;}
    value(type<q>& _tp,ty _t){tp=&_tp;t=_t;}
    template <typename T>
    value(T v){t=literal;
        if constexpr (std::is_same<T,float>::value){tp=&_Float;}
        if constexpr (std::is_same<T,uint>::value){tp=&_UInt;}
        if constexpr (std::is_same<T,bool>::value){tp=&_Bool;}
        if constexpr (std::is_same<T,char>::value){tp=&Float;}
        if constexpr (std::is_same<T,std::string>::value){tp=&Float;}
    }
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
    template <typename T>
    expr(T val){tree.val=value<q>(val);}
    value<q>& val(){return tree.val;}
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
    template <typename >
    void pushLiteral(T val){emplace_expr(val);}
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
struct lambda {

    stmt<q>::arg_list args;
    struct  capture {
        bool byRef;
        value<q> vl;
        capture(bool br,value<q>& value) : byRef(br), vl(value);
    } ;
    struct captureList : public pri::deque<value<q>>{bool byCopy=false;
        void push(bool byr,value<q>& vl){
            for(const auto it : *this){
                if(it.vl==vl){throw CaptureRepeated();}
            };
            emplace_back(byr,vl);
        }
    };
    bool Template=false;
    attrib_list front_ats;
    attrib_list back_ats;
    bool Noexcept=false;
    param_list<q> plist;
    using argList = stmt<q>::arg_list;
    using tyty= std::conditional<temp::meta==q,value<q>,type<q>>::type
    tyty rettp;bool trailing=false;
    attrib_list attribs;
    stmt<q>::block body;
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
        accSpec acc;
        using tyty  = typename std::conditional<temp::meta==q,value<q>,type<q>*>::type;
        tyty t;
        inher(accSpec spc) : acc(spc);
        inher(tyty r) : t(r){} 
    };
        using inher_list=pri::deque<inher>;      
        pri::deque<inher> inherits;
        stmt<q>::specTree<type<q>> specs;
        pri::deque<stmt<q>::StmtTypeDecl*> frndsClasss;// DeclType
        pri::deque<stmt<q>::StmtFuncDecl*> frndsFunctions; // DeclFunction
        pri::deque<stmt<q>::StmtOperatorDecl*> frndsOperators; // DeclFunction
    
        pri::deque<stmt<q>::StmtUsing> usings;// Usings stmts
        pri::deque<stmt<q>::StmtTypeDecl> tdefs;// Usings TypeDef
        pri::deque<stmt<q>::Enum> Enums; 
        
        pri::deque<stmt<q>::StmtVarDecl> variables;
        pri::deque<stmt<q>::StmtFuncDecl> methods;// Has type FuncDecl
        pri::deque<stmt<q>::StmtOperatorDecl> operators;// Has type StmtOperatorDecl
        
        pri::deque<stmt<q>::StmtFuncDecl> constructors;//Has Type FuncDecl 
        pri::dequq<stmt<q>::StmtFuncDecl> destructors;//Has Type FuncDecl

        pri::variant<type<q>> data;

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
                else{err::e<err::t::swizzle_fortype>()}
            }
            else{err::e<err::t::swizzle_notexist>()}
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
    bool isMember(result* r,resty* res){return *r==result::rMethod ||*r==result::rVar;};
    template <temp q>
    bool isMemberPtr(result* r,resty* res){return isPtr(r,res) && isMember(r,res);};
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
    
    bool nsblck=true;bool fblck;bool swBlock;bool IfChain;
    pri::deque<stmt<q>::block*> curBl;
    pri::deque<stmt<q>::StmtNS*> nss;
    pri::deque<stmt<q>::StmtDeclType*> strcts;
    pri::deque<param_list<q>*> curtemp;
    pri::stack<stmt<q>::StmtTry*> tries;
    stmt<q>::FuncDef* fdef;
    stmt<q>::block& curBlock(){return *(curBl.back());};
    param_list<q>& curParams(){return *(curtemp.back());};

    stmt<q>::TypeDef& getTypeDef(){if(nsblck){nss.back().tdefs.back()}else{strcts.back()->tdefs.back()};}
    stmt<q>::TypeDef& getUsing(){if(nsblck){nss.back().usings.back()}else{strcts.back()->usings.back()};}
    stmt<q>* getStmt(){return curBl.back().back();}
    stmt<q>::VarDecl* getRef(std::string name){
        for(stmt<q>::VarDecl& it :  fdef->args){
            if(it.name==name){return it;}
        };
        for(stmt<q>::VarDecl& it :  fdef->args){
            if(it.name==name){return it;}
        };

    };

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

    template <typename StmtTy>void pushAttrs(){}

    template <typename StmtTy> StmtTy* _pushStmt(StmtTy&& st ){curBlock().back()->push_back(stmt<q>(st));return &pri::get<StmtTy>(curBl().back().var;);};// Review

    template <>stmt<q>::Case* _pushStmt<stmt<q>::Case>(stmt<q>::Case&& st ){curBl.back()->push_back(stmt<q>(st));return &pri::get<stmt<q>::block>(curBlock.back());};
    template <>stmt<q>::Default* _pushStmt<stmt<q>::Default>(stmt<q>::Default&& st ){curBl.back()->push_back(stmt<q>(st));return &pri::get<stmt<q>::block>(curBlock.back());};


    template <>stmt<q>::block* _pushStmt<stmt<q>::block>(stmt<q>::block&& st ){curBl.back()->push_back(stmt<q>(st));return &pri::get<stmt<q>::block>(curBlock.back());};
    template <>stmt<q>::Using* _pushStmt<stmt<q>::Using>(stmt<q>::Using&& st ){if(nsblck){nss.back().usings.push_back(st);return &nss.back().usings.back();}else{strcts.back().usings.push_back(st);return &strcts.back().usings.back();};};
    template <>stmt<q>::DefType* _pushStmt<stmt<q>::DefType>(stmt<q>::DefType&& st ){if(nsblck){nss.back().tdefs.push_back(st);return &(nss.back().tdefs.back());}else{strcts.back().tdefs.push_back(st);return &(strcts.back().tdefs.back());} ;};
    template <>stmt<q>::FuncDef* _pushStmt<stmt<q>::FuncDecl>(stmt<q>::FuncDef&& st ){
        if(nsblck){nss.back().funcs.push_back(st);return &(nss.back().funcs.back());}
        else{strcts.back().methods.push_back(st);return &(strcts.back().methods.back());};
    }
    template <>stmt<q>::FuncDef* _pushStmt<stmt<q>::OperatorDecl>(stmt<q>::OperatorDecl&& st ){
        if(nsblck){nss.back().funcs.push_back(st);return &(nss.back().funcs.back());}
        else{strcts.back().methods.push_back(st);return &(strcts.back().operators.back());};
    }    
    

    // template <>stmt<q>::Expr* _pushStmt<stmt<q>::Expr>(stmt<q>::Expr&& st )           {pushbl(pri::get<stmt<q>::Expr>(curBl().back().var).body);return pri::get<stmt<q>::Expr>(curBl().back().var;) ;};
    // template <>stmt<q>::If* _pushStmt<stmt<q>::If>(stmt<q>::If&& st )                 {pushbl(pri::get<stmt<q>::If>(curBl().back().var).body);return pri::get<stmt<q>::If>(curBl().back().var;) ;};
    // template <>stmt<q>::Else* _pushStmt<stmt<q>::Else>(stmt<q>::Else&& st )           {pushbl(pri::get<stmt<q>::Else>(curBl().back().var).body);return pri::get<stmt<q>::Else>(curBl().back().var;) ;};
    // template <>stmt<q>::ElseIf* _pushStmt<stmt<q>::ElseIf>(stmt<q>::ElseIf&& st )     {pushbl(pri::get<stmt<q>::ElseIf>(curBl().back().var).body);return pri::get<stmt<q>::ElseIf>(curBl().back().var;) ;};
    // template <>stmt<q>::Switch* _pushStmt<stmt<q>::Switch>(stmt<q>::Switch&& st )     {pushbl(pri::get<stmt<q>::Switch>(curBl().back().var).body);return pri::get<stmt<q>::Switch>(curBl().back().var;) ;};
    // template <>stmt<q>::Case* _pushStmt<stmt<q>::Case>(stmt<q>::Case&& st )           {pushbl(pri::get<stmt<q>::Case>(curBl().back().var).body);return pri::get<stmt<q>::Case>(curBl().back().var;) ;};
    // template <>stmt<q>::For* _pushStmt<stmt<q>::For>(stmt<q>::For&& st )              {pushbl(pri::get<stmt<q>::For>(curBl().back().var).body);return pri::get<stmt<q>::For>(curBl().back().var;) ;};
    // template <>stmt<q>::While* _pushStmt<stmt<q>::While>(stmt<q>::While&& st )        {pushbl(pri::get<stmt<q>::While>(curBl().back().var).body);return pri::get<stmt<q>::While>(curBl().back().var;) ;};
    // template <>stmt<q>::ForRange* _pushStmt<stmt<q>::ForRange>(stmt<q>::ForRange&& st){pushbl(pri::get<stmt<q>::ForRange>(curBl().back().var).body);return pri::get<stmt<q>::ForRange>(curBl().back().var;) ;};
    // template <>stmt<q>::Do* _pushStmt<stmt<q>::Do>(stmt<q>::Do&& st )                 {pushbl(pri::get<stmt<q>::Do>(curBl().back().var).body);return pri::get<stmt<q>::Do>(curBl().back().var;) ;};
    // template <>stmt<q>::Return* _pushStmt<stmt<q>::Expr>(stmt<q>::Expr&& st )           {pushbl(pri::get<stmt<q>::Return>(curBl().back().var).body);return pri::get<stmt<q>::Return>(curBl().back().var;) ;};


    struct  {
        stmt<q>::StmtVarDecl* vd;
        stmt<q>::StmtDefType* dt;
    }ptr;
stmt<q>::StmtVarDecl& getVarDecl(){return *(ptr.vd);};
stmt<q>::StmtDefType& getDefType(){return *(ptr.dt);};
    stmt<q>& lastStmt(){return curBlock().back();}

    template <typename StmtTy>
    StmtTy* pushStmt(StmtTy&& st ){return _pushStmt<StmtTy>(st);};
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
    
    resty<q> findNameFromNs(stmt<q>::StmtNS* ns,std::string name, result* rt){*rt=result::rErr;
        resty<q> res;
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
    
    stmt<q>::VarDecl& findVariable(type<q>* typ,std::string name ,result* rt){        *rt= result::rErr;
        for(stmt<q>::VarDecl& it : tp->variables){
            if(it.name==name){return res;}
        };
        throw NameNotFound("FromVariable");
    };
    stmt<q>::VarDecl& findVariable(stmt<q>::StmtNS* ns,std::string name ,result* rt){        *rt= result::rErr;
        for(stmt<q>& it : ns->body){
            if(it.t==stmt<q>::eVarDecl){ if(pri::get<stmt<q>::VarDecl>(it).name==name){return pri::get<stmt<q>::VarDecl>(it);}}
        };
        throw NameNotFound("FromVariable");
    };


  
    resty<q> findNameFromTp(type<q>* tp,std::string name,result* rt){
        resty<q> res;
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
        for(stmt<q>FuncDecl& it : typ->methods) {
                if((it.name=name) and (it == args) ) {return &it};
        };
        throw MemberNotFound<type<q>>("NSFunction");
    };
    stmt<q>::StmtFuncDecl* findFunction(stmt<q>::StmtNS* ns,std::string name,pri::deque<type<q>*> args){
        for(stmt<q>::FuncDecl& it : ns->funcs) {
                if((it.name=name) and (it == args) ) {return &it};}
        };
        throw MemberNotFound<stmt<q>::StmtNS>("NSFunction");
    };
    stmt<q>::TypeDecl* findTp(std::string name){//TODO
        if(!nsblck){
            for(stmt<q>::TypeDecl* ns : pri::reverse(strcts)){
                if(ns->name==name){return ns;}
                for(stmt<q>::TypeDef& it : ns->tdefs ){
                    if(it.name==name){return &it.get();}
                };
                for(stmt<q>::Using& it : ns->usings ){
                    if(it.name==name){return &it.get();}
                }
                for(stmt<q>::TypeDecl& it : ns->types ){
                if(it.name==name){return &it;}
            };
            };
        }
            for(stmt<q>::NS* ns : pri::reverse(nss)){
                for(stmt<q>::TypeDecl& it : ns->tdefs ){
                    if(it.name==name){return &it.get();}
                };
                for(stmt<q>::Using& it : ns->usings ){
                    if(it.name==name){return &it.get();}
                }
                for(stmt<q>::TypeDecl& it : ns->types ){
                if(it.name==name){return &it;}
            };
        };
            throw TypeNotFound();
    };
    stmt<q>::TypeDecl* findTpDecl(std::string name){
        if(!nsblck){
            for(stmt<q>::TypeDecl* ns : pri::reverse(strcts)){
                if(ns->name==name){return ns;}
                for(stmt<q>::TypeDecl* it : ns->types ){
                    if(it.name==name){return it.get();}
                };
            };
            };
            for(stmt<q>::NS* ns : pri::reverse(nss)){
                for(stmt<q>::TypeDecl& it : ns->types ){
                if(it.name==name){return &it;}
            };
        };
            throw TypeNotFound();
    };
    resty<q> findName(std::string name,result* r){
        resty<q> res;
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
        
        throw NameNotFound<resty<q>>("Global");
    };
    bool find(std::string name,resty<q>* res, result* r){
        switch(*r){
            case result::rType : {try{*res=findNameFromTp(pri::get<type<q>>(*res),name,r);}
                catch(const MemberNotFound& e){return false;};return true;};
            case result::rNs : {{try*res=findNameFromNs(pri::get<stmt<q>::StmtNS>(n),name,r);}
                            catch(const MemberNotFound& e){return false;};return true;};
            case result::rEnum : {
                try {*res=pri::get<Enum>(n).findMember(name);}
                catch(const MemberNotFound<Enum>& exc){ return false;err::e(*this,exc);}
                return true;};
            case result::rErr :{try{*res=findName(name,r)}catch(const NameNotFound& e){return false};return true;}
                default : {return false;};
                // case result::rVar : {};
        }
    };
    bool find(std::string name,resty<q>* res,result* r,lex::ty acc){

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