#ifndef STMSL_KW
#define STMSL_KW
#include "ast.hpp"

namespace stmsl{
enum pcntxt {
    turoot=        0b0000000000001,
    global=        0b0000000000010,
    funcblock=     0b0000000000100,
    funcargqual=   0b0000000001000,
    parameterlist= 0b0000000010000,
    declType=      0b0000000100000,
    layoutArgs=    0b0000001000000,
    layoutDef=     0b0000010000000,
    funcret=       0b0000100000000,
    stexpr=        0b0001000000000,
    swblock=       0b0010000000000,
    stmtDecl   =   0b0100000000000,
    macroExpr =    0b1000000000000
};


enum kwty {
    macro,
    qualifier,
    stmt,tempstmt,prim,layout_at,layout_qual,layout_Stmt
    accessSpec,
    funcStmt,
    loopStmt
};


template <kwty k>
struct contxt_kw{
    static constexpr size_t pc ;
    // static constexpr pcntxt pcs[] = {} ;
};

template <>struct contxt_kw<kwty::macro>{
    static constexpr size_t s =turoot ;};

template <>struct contxt_kw<kwty::name_attrib>{static constexpr size_t s =global|funcblock|stmtDecl|macroExpr ;};
template <>struct contxt_kw<kwty::stmt>{
    static constexpr size_t s =global|funcblock|macroExpr ;};
template <>struct contxt_kw<kwty::prim>{
    static constexpr size_t s =global|funcblock|macroExpr ;};
template <>struct contxt_kw<kwty::layout_at>{
    static constexpr size_t s = layoutArgs|macroExpr ;};
template <>struct contxt_kw<kwty::layout_qual>{
    static constexpr size_t s =layoutDef|funcargqual|macroExpr ;};
template <>struct contxt_kw<kwty::builtinFunc>{
    static constexpr size_t s = global|funcblock|macroExpr ;};
template <>struct contxt_kw<kwty::builtinVar>{
    static constexpr size_t s = global|funcblock|stexpr|macroExpr ;};
template <>struct contxt_kw<kwty::funcStmt>{
    static constexpr size_t s = funcblock|stexpr ;};

template <kwty k>
struct context_tuple {
    static constexpr size_t kwCntxt = contxt_kw<k>::s;
    // struct iter {
    //     size_t s;
    //     pcntxt operator*(){return s<=size?pcs[s]:pcs[0];}
    //     decltype(*this) operator++(){s++;return *this;}
    //     iter(size_t _s): s(_s){}
    // };
    // constexpr iter begin(){return iter(0);}
    // constexpr iter end(){return iter(size+1);}
    // bool operator==(iter& i){return s==i.s;}
    // constexpr pcntxt operator[](size_t i){return pcs[i];}
    template <pcntxt p>
    bool hasCntxt(){return kwCntxt&p;};
};



template <pri::Str s,typename KW,kwty kTY>
struct kw : hs<s>/*,context_tuple<kTY>*/ {
    using type = KW;
    static constexpr kwty KT= kTY;
    static std::string name() {return s.get();}
    // bool _check(parser& p,std::string s){ 
    //     for(pcntxt it : *this){
    //         if(it==p.cntxt){return true;}
    //     };
    //     return false;
    // }
    bool check(std::string str){
        if(str!= name()){return false;}
        return true;};
    template <kwty kT>
    void _proc(parser& p){p.putKWt<type>;};
    template <>void _proc<kwty::macro>(parser& p){p.getMacro<KW>();};
    template <>void _proc<kwty::qualifier>(parser& p){p.putQualifier<KW>();};
    template <>void _proc<kwty::layout_Stmt>(parser& p){p.LayoutNew<KW>();};
    template <>void _proc<kwty::layout_at>(parser& p){p.putLayout<KW>();};
    template <>void _proc<kwty::layout_qual>(p.putLayoutQual<KW>());
    template <>void _proc<kwty::funcStmt>(parser& p){p.Stmt();}
    template <>void _porc<kwty::stmt>(parser& p){p.getStmt<KW>();}

    // template <>void _proc<kwty::accessSpec>(parser& p){p.accessSpec<access::>}
    // template <>void _proc<kwty::
    // template <>void _proc<kwty::builtinFunc>();
    // template <>void _proc<kwty::builtinVar>();
    template <>void _proc<kwty::loopStmt>(parser& p){p.putLoop<type>();};  
    static void proc(parser& p){_proc<kTY>(p);};
    // void lex(parser& p);
};

template <typename T,typename... Ts>
struct context_join {
    static constexpr size_t s = T::kwCntxt | context_join<Ts...>::s;
};

template <typename T>
struct context_join {
    static constexpr size_t s = T::kwCntxt | context_join<Ts...>::s;
};


#define KW_LIST 
#define KW_LISTKW
#define KW_PRIM
#define KW_LISTPRIM
#define KW_LISTLYT
#define KW_LISTQ
#define KW_LISTM
#define KWLYTQ
#define KW_ACCS
#define KW_N(name,sname,KWTY) struct name : kw<KWTY> {static const std::string name = sname;void proc(smtsl_parser& p) ;}; \
#define KW_LIST KW_LIST, name


using kw_version =  kw<"#version",macroStmt::mStmtVersion,kwty::macro> ;
// void kw_version::proc(parser& p){    p.setVersion(p.getNum(p.untilEOL()));}

using kw_Incl = kw<"#include",macroStmt::mStmtInclude,kwty::macro> ;
using kw_Define =  kw<"#define",macroStmt::mStmtDefine,kwty::macro> ;
using kw_if =  kw<"#if",macroStmt::mStmtIf,kwty::macro> ;
using kw_else =  kw<"#else",macroStmt::mStmtElse,kwty::macro>;
using kw_elif =  kw<"#elif",macroStmt::mStmtElif,kwty::macro> ;
using kw_elifdef =  kw<"#elifdef",macroStmt::mStmtElifdef,kwty::macro> ;
using kw_elifndef =  kw<"#elifndef",macroStmt::mStmtElifndef,kwty::macro> ;
using kw_endif =  kw<"#endif",macroStmt::mStmtEndIf,kwty::macro> ;
using kw_ifndef =  kw<"#ifndef",macroStmt::mStmtIfndef,kwty::macro> ;
using kw_ifdef =  kw<"#ifdef",macroStmt::mStmtIfdef,kwty::macro> ;
using kw_Layout =  kw<"layout",stmt<meta>::StmtLayout,kwty::layout_Stmt> ;
#define KW_LISTM kw_version, kw_Incl, , kw_Define , kw_if , kw_elif , kw_elif , kw_elifdef , kw_elifndef , kw_endif , kw_ifndef , kw_ifdef , kw_Layout 
#define KW_LIST KW_LISTM
template <pri::Str s,stmt<temp::meta>::StmtLayout::ty TY>
struct kw_lyt : kw<s,stmt<meta>::StmtLayout,kwty::layout_at> {
    static constexpr stmt<temp::meta>::StmtLayout::ty typeLyt=TY;
} ; 

using kw_Location =  kw_lyt<"location",stmt<temp::meta>::StmtLayout::ty::location> ;
using kw_Binding =  kw_lyt<"binding",stmt<temp::meta>::StmtLayout::ty::binding> ;

#define KW_LISTLYT KW_LISTLYT kw_Location, kw_Binding 

using kw_uniform =  kw<"uniform",stmt<meta>::StmtLayout,kwty::layout_qual> ;
#define KW_LISTLYT KW_LISTLYT, kw_uniform 
struct kw_Buffer :  kw<"buffer",kwty::layout_qual>{
    void proc(parser& p){
        p.curAcc.push(accSpec::Public);
        p.getStmt<stmt<temp::meta>::StmtDefType>();
    };
} ;
#define KW_LISTLYT KW_LISTLYT,kw_Buffer
  


#define KW_LYTQ
using kw_Const =  kw<"const",QConst,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW, kw_Const
using kw_Flat =  kw<"flat",QFlat,kwty::qualifier> ;
using kw_in =  kw<"in",QIn,kwty::qualifier> ;
using kw_out =  kw<"out",QOut,kwty::qualifier> ;
using kw_inout =  kw<"inout",QInout,kwty::qualifier> ;
#define KW_LYTQ  kw_Flat , kw_in , kw_out , kw_inout 
#define KW_LISTKW KW_LISTKW, KWLYTQ


enum accSpec{Public,Private,Protected};
struct kw_Struct : public kw<"struct",type<temp::meta> ,kwty::Struct>{
    void proc(parser& p){
        p.accessPush<accSpec::Public>();
        p.getStmt<stmt<temp::meta>::StmtDeclType>();
    };
};

struct kw_Class : public kw<"class",type<temp::meta>,kwty::Struct>{
    void proc(parser& p){
        p.accessPush<accSpec::Private>();
        p.getStmt<stmt<temp::meta>::StmtDeclType>();
    };
};
struct kw_Union : public kw<"union",type<temp::meta>,kwty::Struct>{
    void proc(parser& p){p.getStmt<stmt<temp::meta>::StmtDeclUnion>();};
}

using kw_Enum = kw<"enum",Enum , kwty::stmt>;
#define KW_TYPEKW kw_Enum, kw_Struct,kw_Class ,

using kw_New = kw<"new",value<temp::meta>,kwty::prim>
using kw_Delete = kw<"delete",value<temp::meta>,kwty::prim>
using kw_Nullptr = kw<"nullptr",value<temp::meta>,kwty::prim>;
using kw_Null = kw<"NULL",value<temp::meta>,kwty::prim>;

using kw_This =kw<"this",type<temp::meta>,kwty::qualifier>; 
template <Str s,typename QQt>
struct kw_Qual : public kw<s,QQt,kwty::qualifier>{
    void proc(parser& p){p.cast->pushQual(QQt::quality);}
};
using kw_Virtual =  kw_Qual<"virtual",QVirtual,kwty::qualifier>;
using kw_Override =  kw_Qual<"override",QOverride,kwty::qualifier> ;
using kw_Explicit =  kw_Qual<"explicit",QExplicit,kwty::qualifier> ;
using kw_Final =  kw_Qual<"final",QFinal,kwty::qualifier>;
using kw_Noexcept = kw_Qual<"noexcept",QNoexcept,kwty::qualifier>;

#define KW_PRIM kw_New,kw_Delete,kw_Nullptr,kw_Null
#define KW_QUAL  kw_Virtual,kw_Override,kw_Explicit,kw_Final,kw_Noexcept
#define KW_LISTKW KW_LISTKW,kw_This, KW_QUAL ,
#ifdef CXX_C 
#define KW_LISTKW KW_LISTKW, KW_Union ,KW_PRIM
#endif

struct kw_Template :public  kw<"template",void,kwty::Tempstmt>{
    void proc(parser& p){p.getTemplate();};
} ;
using kw_Typename =  kw<"typename",void,kwty::stmt> ;
using kw_Constexpr =  kw<"constexpr",QConstExpr,kwty::qualifier> ;
using kw_Static =  kw<"static",QStatic,kwty::qualifier> ;
using kw_Friend = kw<"friend",QFriend,kwty::qualifier>;
using kw_Operator = kw<"operator",stmt<temp::meta>::StmtOperatorDecl,kwty::stmt>;
using kw_Decltype = kw<"decltype",stmt<temp::meta>::StmtFuncDecl,kwrt::stmt>;
#define KW_LISTKW KW_LISTKW,kw_Template,kw_Typename,kw_Constexpr,kw_Static ,kw_Friend,kw_Operator,kw_Decltype
template <pri::Str s,accSpec asT>
struct kw_as : public kw<s,void,kwty::accessSpec> {
    void proc(parser& p){
        p.until<lex::ty::colon>();
        p.erase();
        p.access<asT>();
    };
};
using kw_Public = kw_as<"public",accSpec::Public>;
using kw_Private = kw_as<"private",accSpec::Private>;
using kw_Protected = kw_as<"protected",accSpec::Protected>;
#define KW_ACCS kw_Public , kw_Private , kw_Protected 
struct kw_Namespace : public  kw<"namespace",stmt<temp::meta>::StmtNS,kwty::stmt>{
    void proc(parser& p){
        p.Fromuntil<lex::ty::lbrace>();}
};
using kw_If =  kw<"if",stmt<temp::meta>::StmtIf,kwty::funcStmt> ;
using kw_Else =  kw<"else",stmt<temp::meta>::StmtElse,kwty::funcStmt> ;
using kw_Switch =  kw<"switch",stmt<meta>::StmtSwitch,kwty::funcStmt> ;
using kw_Case =  kw<"case",stmt<temp::meta>::StmtCase,kwty::funcStmt> ;
using kw_Default = kw<"default",stmt<temp::meta>::StmtCase,kwty::funcStmt>;
using kw_While =  kw<"while",stmt<temp::meta>::StmtWhile,kwty::loopStmt> ;
using kw_For =  kw<"for",stmt<temp::meta>::StmtFor,kwty::loopStmt> ;
using kw_Try = kw<"try",stmt<temp::meta>::StmtTry,kwty::funcStmt>;
using kw_Catch = kw<"catch",stmt<temp::meta>::StmtCatch,kwty::funcStmt>;
using kw_Throw = kw<"throw",stmt<temp::meta>::StmtThrow,kwty::funcStmt>;
struct kw_Do : public  kw<"do",void,kwty::funcStmt> {
void proc(parser& p){
        p.until<lex::ty::lbrace>();p.getBlock<>();
        p.untilKW<true,kw_For,kw_While>();
    };
};

using kw_Return =  kw<"return",stmt<temp::meta>::StmtReturn,kwty::funcStmt> ;
using kw_Break =  kw<"break",stmt<temp::meta>::StmtBreak,kwty::stmtStmt> ;
using kw_Continue =  kw<"continue",stmt<temp::meta>::StmtContinue,kwty::stmtStmt> ;

#define KW_LISTSTMT kw_If  , kw_Else  , kw_Switch, kw_Case, kw_Default,  kw_While, kw_For,kw_Do ,kw_Try ,kw_Catch ,kw_Throw, kw_Return , kw_Break , kw_Continue 

#define KW_LISTKW KW_LISTKW,KW_LISTSTMT
#ifdef CXX_20
using kw_export = public kw<"export",void,kwty::stmt>;
using kw_import = public kw<"import",void ,kwty::stmt>;
#define KW_LISTKW KW_LISTKW, kw_export,kw_import 
#endif

#define KW_LIST KW_LISTKW ,KW_LISTLYT,KW_LISTPRIM

}
#endif