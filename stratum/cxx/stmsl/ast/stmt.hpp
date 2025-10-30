#ifndef STMSL_STMT
#define STMSL_STMT
#include "ast.hpp"

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
struct stmt {
    using param_list=param_list<q>;
    enum stmtty {
eBlock,eNS,
eDeclOperator,eDefOperator,
eDeclType,eDefType,
//eDeclUnion,eDefUnion,
eExpr,
eDo,
eWhile,eFor,eForRange,
eSwitch,eCase,eDefault,
eIf,eElse,eElseIf,
eReturn,eContinue,
eFuncDecl,eFuncDef,
eVarDecl,
eUsing,eTypeDef,
eLayout,eSEnum,
eTry,eCatch,Throw
        
    };
    stmtty t;
struct NS;
struct OperatorDecl;
struct OperatorDef;
struct DeclType;
struct DefType ;
#ifdef CXX_C
struct DeclUnion ;
struct DefUnion;
#endif

using Expr = expr<q>;
struct While;
struct For;
struct Do;
struct ForRange;
struct Switch;
struct Case;
struct Default;
struct If;
struct Else;
struct ElseIf;
using Return = Expr;
struct FuncDecl;
struct FuncDef ;
struct VarDecl;
struct Using;
struct TypeDef;
struct Layout;
using Enum=EnumT
struct Try;
struct Catch ;
struct Throw;
using  block =pri::deque<funcvar>;
    using funcvar = pri::variant<Expr,While,For,Do,ForRange,Switch,Case,Default,If,Else,ElseIf,Return,Try,Catch,Throw,block>;


    struct NS {
        std::string name;
        pri::deque<NS*> usingNS;
        pri::deque<NS*> inlineNS;

        pri::deque<NS> nss; 
        pri::deque<NS> inline_nss;
        // std::enable_if<q==temp::inst,type<q> >::type types;// TODO make correct
        pri::deque<VarDecl> vars;
        pri::deque<FuncDecl> funcs;
        pri::deque<OperatorDecl> operators;
        pri::deque<TypeDecl> types;
#ifdef CXX_C
         pri::deque<UnionDecl> unions; 
#endif
        pri::deque<Using> usings;
        pri::deque<TypeDef> tdefs;


        NS& includeNS(std::string name){
            for(const NS& it : nss){
                if(it.name==name){return it;};
            };
            nss.push_back(NS());
            return nss.back();
        };
        type<q> findName(std::string s){
            for(stmt<q>& it:body){
                if(it.t==stmtty::DefType){
                    DefType& ref=pri::get<DefType>(it.var);
                    if(s==ref.name){return ref.t;}
                };
            };
        };
        FuncDecl& findFunc(std::string s,pri::deque<value<q>> args){
            for(FuncDecl& f : funcs){}
        };
        
        operator std::string(){return this->name;}
        
    };
    using tyty = typename std::conditional<temp::meta==q,value<q> , type<temp::inst>*>::type;
    
    struct VarDecl {
        bool Const=false;;bool Static=false;bool Constexpr=false;bool in=false;bool out=false;
        tyty tp;std::string name;int ref;bool Auto;
        bool memberPtr;value<q> vl;
        bool Default;expr<q> DefaultValue;
        bool isPtr(){return ref>0;}
        VarDecl() = default;
        VarDecl(type<q>& _tp){*this=VarDecl();}
    };
    
    struct arg_list : public pri::deque<VarDecl>{bool pack;};

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

    struct OperatorDef  {
        arg_list<temp::inst> args;
        block body;
    };
    struct OperatorDecl : public SpecTreeIncl<OperatorDef> {
        bool typeConv;
        pri::variant<type<q>,op::ty > op;
        using tType =typename std::conditional<temp::meta==q,pri::deque<OperatorDef>,OperatorDef>::type ;
        arg_list<temp::inst> args;
        tType defs;
        tyty rett; 
    };


    struct DefType { 
        type<q> t;
        
        void addType(type<q>& argt){t.variables.push_back(argt);};
        type<q>& findName(std::string s){
            for(type<q>& it : t.dependnents){if(it.name==s){return it;}};
            for(type<q>& it : t.variables){if(it.name==s){return it;}};
            for(type<q>& it : t.methods){if(it.name==s){return it;}};
            for(type<q>& it : t.constructors){if(it.name==s){return it;}};
            throw  NameNotFound();
        };
        type<q>& get(){
            if constexpr (q==temp::meta){
            if(obj->t.tempTy){
                if(ps.size()!=obj->t.prms.size()){err::err<err::t::template_param_list_incomplete>()}
                auto t = ps.begin();
                auto temp = obj->t.prms.begin();
                for(;t!=ps.end() and (temp!=obj->t.prms.begin())){
                    if(t->ty!=temp->ty){
                        err::err<err::t::template_param_mismatch>();
                        
                        return;}
                    
                    ++t;++temp;
                };
            }
            else return *this;
        }
        else {return *this;}
        }
    };
        
    struct DeclType :public SpecTreeIncl<DefType> {
        std::string name;
        specTree<DefType> specs;
        
    };
        struct While{Expr condition;block body;}
        struct For {Expr init; Expr condition;Expr incr;
            block body;
    };
    struct ForRange {
        VarDecl vardecl;
        Expr ref;
        block body; 
        decltype(*this) operator=(For& rhs){vardecl=rhs.init;return *this;}
    };
    struct Do : public While{bool Do;};
    struct Case {expr<q> ConstExpr;block body;};
    
    struct Switch {
        bool ConstExpr=false;
        bool assign;value<temp::inst> vl;
        expr<q> condition; 
        block body;
    } ;
    struct If { 
        bool ConstExpr;
        Expr condition;
        block body;
        If(expr<q> e) : condition(e) {}
    };
    struct Else {
        pri::variant<If*,ElseIf*> IfS;bool elIf;
        block body;

        Else(If& If) : elIf(false) {pri::get<If*>(Ifs)=&If;}
        Else(ElseIf& If) : elIf(true) {pri::get<ElseIf*>(Ifs)=&If;}
    };
    struct ElseIf : public Else   {
        bool ConstExpr;
        bool assign;expr<q> condition;
        ElseIf(If& If) : elIf(false) {pri::get<If*>(Ifs)=&If;}
        ElseIf(ElseIf& If) : elIf(true) {pri::get<ElseIf*>(Ifs)=&If;}
    };

    struct FuncDecl : public SpecTreeIncl<FuncDef> {
        bool ConstExpr=false;bool Virtual=false;bool Final=false;bool Static=false;
        bool Friend=false;
        std::string name
        param_list<q> prms;
        type<q>* ret;
        arg_list args;
        operator FuncDef(){
            FuncDef d;d.prms=prms;d.ret = ret;d.args=args;
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
    struct FuncDef{
        arg_list args;block body;
    };
    struct Using {
        bool Typename;bool Namespace;
        param_list prms;
        std::string name ;
        tyty expr;
        type<q> get(){};
    };

    struct TypeDef {
        tyty tp;
        std::string name ;
        type<q> get(){};        
        TypeDef(type<temp::inst> ty,std::string n) : t(ty),name(n) {}
    };
    // template <>
    // struct LayoutTy
    struct Layout {
        enum stand {std430,std140};
        enum ty {location,binding};
        enum tyT { buffer,var,uniform};
        stand st;
        ty t;
        tyT vart;
        size_t loc;bool in=false;bool out=false;
        bool uniform;bool flat;
        pri::variant<VarDecl,TypeDef> data;bool in=false,bool out=false;
        Layout() = default;
    };
    struct Try{
        block<q> body;
        pri::deque<Catch> catches;
    };
    struct Catch {
    VarDecl var;
    block<q> body;
    };
    struct  Throw {
        expr<q> val;
        Throw(expr<q>&& _val)  {val=_val;}
    };

    
        
    accSpec acc=accSpec::Public;
    using allvar =pri::variant<block,Layout,NS,FuncDecl,FuncDef,VarDecl,Using,TypeDef,Enum,DeclType,DefType,Expr,While,For,Do,ForRange,Switch,Case,Default,
    If,Else,ElseIf,Return,Try,Catch,Throw>;
    allvar var;
    using nsvar =  pri::variant<Layout,NS,FuncDecl,FuncDef,VarDecl,Using,TypeDef,Enum,DeclType,DefType,Expr,While,For,Do,ForRange,Switch,Case,Default,
    If,Else,ElseIf>;
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
template<>struct getTy<stmtty::eBlock>{using ty=block;}
template<>struct getTy<stmtty::eNS>{using ty=NS;}
template<>struct getTy<stmtty::eDeclType>{using ty=DeclType;}
template<>struct getTy<stmtty::eDefType>{using ty=DefType;}
template<>struct getTy<stmtty::eDefTypeSpec>{using ty=DefTypeSpec;}
template<>struct getTy<stmtty::eExpr>{using ty=Expr;}
template<>struct getTy<stmtty::eAssign>{using ty=Assign;}
template<>struct getTy<stmtty::eDo>{using ty=Do;}
template<>struct getTy<stmtty::eWhile>{using ty=While;}
template<>struct getTy<stmtty::eFor>{using ty=For;}
template<>struct getTy<stmtty::eForRange>{using ty=ForRange;}
template<>struct getTy<stmtty::eSwitch>{using ty=Switch;}
template<>struct getTy<stmtty::eCase>{using ty=Case;}
template<>struct getTy<stmtty::eDefault>{using ty=Default;}
template<>struct getTy<stmtty::eIf>{using ty=If;}
template<>struct getTy<stmtty::eElse>{using ty=Else;}
template<>struct getTy<stmtty::eElseIf>{using ty=ElseIf;}
template<>struct getTy<stmtty::eReturn>{using ty=Return;}
template<>struct getTy<stmtty::eFuncDecl>{using ty=FuncDecl;}
template<>struct getTy<stmtty::eFuncDef>{using ty=FuncDef;}
template<>struct getTy<stmtty::eFuncDefSpec>{using ty=FuncDefSpec;}
template<>struct getTy<stmtty::eVarDecl>{using ty=VarDecl;}
template<>struct getTy<stmtty::eUsing>{using ty=Using;}
template<>struct getTy<stmtty::eTypeDef>{using ty=TypeDef;}
template<>struct getTy<stmtty::eLayout>{using ty=Layout;}

        
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
template<> void getTy<NS>(){return stmtty::NS;}
template<> void getTy<DeclType>(){return stmtty::DeclType;}
template<> void getTy<DefType>(){return stmtty::DefType;}
template<> void getTy<DefTypeSpec>(){return stmtty::DefTypeSpec;}
template<> void getTy<Expr>(){return stmtty::Expr;}
template<> void getTy<Assign>(){return stmtty::Assign;}
template<> void getTy<While>(){return stmtty::While;}
template<> void getTy<For>(){return stmtty::For;}
template<> void getTy<ForRange>(){return stmtty::ForRange;}
template<> void getTy<Do>(){return stmtty::Do;}
template<> void getTy<Switch>(){return stmtty::Switch;}
template<> void getTy<Case>(){return stmtty::Case;}
template<> void getTy<Default>(){return stmtty::Default;}
template<> void getTy<If>(){return stmtty::If;}
template<> void getTy<Else>(){return stmtty::Else;}
template<> void getTy<ElseIf>(){return stmtty::ElseIf;}
template<> void getTy<Return>(){return stmtty::Return;}
template<> void getTy<FuncDecl>(){return stmtty::FuncDecl;}
template<> void getTy<FuncDef>(){return stmtty::FuncDef;}
template<> void getTy<FuncDefSpec>(){return stmtty::FuncDefSpec;}
template<> void getTy<VarDecl>(){return stmtty::VarDecl;}
template<> void getTy<Using>(){return stmtty::Using;}
template<> void getTy<TypeDef>(){return stmtty::TypeDef;}
template<> void getTy<Layout>(){return stmtty::Layout;}

template <typename StmtT> set(){t=getTy<StmtT>();};

    template <typename StmtT>
    stmt(StmtT&& s) : acc(accSpec::public){
        pri::get<StmtT>(var)=s;
        set<StmtT>();
    };
    stmt() = default ;
};

#endif