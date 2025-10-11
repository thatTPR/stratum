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
    builtinFunc,builtinVar,
    accessSpec,
    funcStmt,
    loopStmt
};


template <kwty k>
struct contxt_kw{
    static constexpr size_t pc ;
    // static constexpr pcntxt pcs[] = {} ;
};
/*
template <>struct contxt_kw<kwty::macro>{
    static constexpr size_t s = 1 ;
    static constexpr pcntxt pcs[] = {turoot} ;
};

template <>struct contxt_kw<kwty::name_attrib>{
    static constexpr size_t s = 2 ;
    static constexpr pcntxt pcs[] = {global,funcblock} ;
};
template <>struct contxt_kw<kwty::stmt>{
    static constexpr size_t s = 2 ;
    static constexpr pcntxt pcs[] = {global,funcblock} ;
};
template <>struct contxt_kw<kwty::prim>{
    static constexpr pcntxt pcs[] = {global,funcblock} ;
};
template <>struct contxt_kw<kwty::layout_at>{
    static constexpr size_t s = 1 ;
    static constexpr pcntxt pcs[] = {layoutArgs} ;
};
template <>struct contxt_kw<kwty::layout_qual>{
    static constexpr size_t s = 2 ;
    static constexpr pcntxt pcs[] = {layoutDef,funcargqual} ;
};
template <>struct contxt_kw<kwty::builtinFunc>{
    static constexpr size_t s = 2 ;
    static constexpr pcntxt pcs[] = {global,funcblock} ;
};
template <>struct contxt_kw<kwty::builtinVar>{
    static constexpr size_t s = 2 ;
    static constexpr pcntxt pcs[] = {global,funcblock} ;
};

template <>struct contxt_kw<kwty::funcStmt>{
    static constexpr size_t s = 2 ;
    static constexpr pcntxt pcs[] = {funcblock} ;
};
*/
template <>struct contxt_kw<kwty::macro>{
    static constexpr size_t s =turoot ;
};

template <>struct contxt_kw<kwty::name_attrib>{
    static constexpr size_t s =global|funcblock|stmtDecl|macroExpr ;
};
template <>struct contxt_kw<kwty::stmt>{
    static constexpr size_t s =global|funcblock|macroExpr ;
};
template <>struct contxt_kw<kwty::prim>{
    static constexpr size_t s =global|funcblock|macroExpr ;};
template <>struct contxt_kw<kwty::layout_at>{
    static constexpr size_t s = layoutArgs|macroExpr ;
};
template <>struct contxt_kw<kwty::layout_qual>{
    static constexpr size_t s =layoutDef|funcargqual|macroExpr ;
};
template <>struct contxt_kw<kwty::builtinFunc>{
    static constexpr size_t s = global|funcblock|macroExpr ;
};
template <>struct contxt_kw<kwty::builtinVar>{
    static constexpr size_t s = global|funcblock|stexpr|macroExpr ;
};

template <>struct contxt_kw<kwty::funcStmt>{
    static constexpr size_t s = funcblock|stexpr ;
};

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


template <size_t N>
struct Str {
    std::array<char, N> data;

    constexpr Str(const char (&s)[N]) {
        std::copy_n(s, N, data.begin());
    }

    std::string get() const { return std::string(data.data()); }
};

// Now Str is literal → usable as NTTP
template <Str S>
struct hs {
    static constexpr auto value = S;
    static std::string name() { return std::string(value.data.data()); }
};

template <Str s,typename KW,kwty kTY>
struct kw : hs<s>,context_tuple<kTY> {
    using type = KW;
    static constexpr kwty KT= kTY;
    static std::string name() {return s.name();}
    // bool _check(parser& p,std::string s){ 
    //     for(pcntxt it : *this){
    //         if(it==p.cntxt){return true;}
    //     };
    //     return false;
    // }
    bool check(parser& p,std::string s){
        if(s!= name()){return false;}
        return true;
    };
    template <kwty kT>
    void _proc(parser& p){p.putKWt<type>;};
    template <>void _proc<kwty::macro>(parser& p){p.getMacro<KW>();};
    template <>void _proc<kwty::qualifier>(parser& p){p.putQualifier<KW>();};
    template <>void _proc<kwty::layout_Stmt>(parser& p){p.LayoutNew<KW>();};
    template <>void _proc<kwty::layout_at>(parser& p){p.putLayout<KW>();};
    template <>void _proc<kwty::layout_qual>(p.putLayoutQual<KW>());
    template <>void _proc<kwty::funcStmt>(parser& p){p.Stmt();}
    // template <>void _proc<kwty::accessSpec>(parser& p){p.accessSpec<access::>}
    // template <>void _proc<kwty::
    // template <>void _proc<kwty::builtinFunc>();
    // template <>void _proc<kwty::builtinVar>();
    template <>void _proc<kwty::loopStmt>(parser& p){p.putLoop<type>();};  
    void proc(parser& p){_proc<kTY>(p);};
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
#define KW_LISTPRIM
#define KW_LISTLYT
#define KW_N(name,sname,KWTY) struct name : kw<KWTY> {static const std::string name = sname;void proc(smtsl_parser& p) ;}; \
#define KW_LIST KW_LIST, name


using kw_version =  kw<"version",macroStmt::mStmtVersion,kwty::macro> ;
// void kw_version::proc(parser& p){    p.setVersion(p.getNum(p.untilEOL()));}
#define KW_LISTKW kw_version,

using kw_Incl = kw<"#include",macroStmt::mStmtInclude,kwty::macro> ;
#define KW_LISTKW KW_LISTKW kw_Incl, 

using kw_Define =  kw<"#define",macroStmt::mStmtDefine,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_Define 

using kw_if =  kw<"#if",macroStmt::mStmtIf,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_if 
using kw_else =  kw<"#else",macroStmt::mStmtElse,kwty::macro>;
#define KW_LISTKW KW_LISTKW, kw_elif 

using kw_elif =  kw<"#elif",macroStmt::mStmtElif,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_elif 

using kw_elifdef =  kw<"#elifdef",macroStmt::mStmtElifdef,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_elifdef 
using kw_elifndef =  kw<"#elifndef",macroStmt::mStmtElifndef,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_elifndef 

using kw_endif =  kw<"#endif",macroStmt::mStmtEndIf,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_endif 

using kw_ifndef =  kw<"#ifndef",macroStmt::mStmtIfndef,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_ifndef 

using kw_ifdef =  kw<"#ifdef",macroStmt::mStmtIfdef,kwty::macro> ;
#define KW_LISTKW KW_LISTKW, kw_ifdef 

using kw_Layout =  kw<"layout",stmt<meta>::StmtLayout,kwty::layout_Stmt> ;
#define KW_LISTKW KW_LISTKW, kw_Layout 

using kw_Location =  kw<"location",stmt<meta>::Location,kwty::layout_at> ;
#define KW_LISTLYT KW_LISTLYT kw_Location 

using kw_Binding =  kw<"binding",stmt<meta>::Binding,kwty::layout_at> ;
#define KW_LISTLYT KW_LISTLYT, kw_Binding 

using kw_uniform =  kw<"uniform",stmt<meta>::StmtLayout,kwty::layout_qual> ;
#define KW_LISTLYT KW_LISTLYT, kw_uniform 
using kw_Buffer =  kw<"buffer",kwty::layout_qual> ;
#define KW_LISTLYT KW_LISTLYT,kw_Buffer


using kw_Const =  kw_mat<"const",atConst,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW, kw_Const
using kw_Flat =  kw_mat<"flat",atFlat,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW, kw_Flat 
using kw_in =  kw<"in",atIn,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW, kw_in 
using kw_out =  kw<"out",atOut,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW, kw_out 
using kw_inout =  kw<"inout",atInout,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW, kw_inout 

using kw_Return =  kw<"return",stmt<temp::meta>::StmtReturn,kwty::funcStmt> ;
#define KW_LISTKW KW_LISTKW, kw_Return 
using kw_Break =  kw<"break",stmt<temp::meta>::StmtBreak,kwty::stmtStmt> ;
#define KW_LISTKW KW_LISTKW, kw_Break 
using kw_Continue =  kw<"continue",stmt<temp::meta>::StmtContinue,kwty::stmtStmt> ;
#define KW_LISTKW KW_LISTKW, kw_Break 




template <Str s, typename T>
struct kw_prim  : kw<s,T,kwty::prim> {
    void proc(parser& p){
        if constexpr (pcs == pcntxt::stexpr){pushConstructor<T>(d);}
        else pushDecl<T>(d);
    };
};
using kw_Image2D =  kw_prim<"image2D",type<meta>::Image2DTy> ;
using kw_Image3D =  kw_prim<"image3D",type<meta>::Image3DTy> ;
using kw_Sampler =  kw_prim<"sampler",type<meta>::SamplerTy> ;
using kw_Void =  kw<"void",kwty::prim> ;
using kw_Float =  kw_prim<"float",type<meta>::FloatTy> ;
using kw_Int =  kw_prim<"int",type<meta>::IntTy> ;
using kw_Uint =  kw_prim<"uint",type<meta>::UintTy> ;
using kw_Bool =  kw_prim<"bool",type<meta>::BoolTy> ;
#define KW_LISTPRIM KW_LISTPRIM,kw_Image2D,kw_Image3D,kw_Sampler,kw_Void,kw_Float,kw_Int,kw_Uint,kw_Bool

template <Str s,typename T>
struct kw_vec : kw<s,T,kwty::prim> {    size_t d;
    bool check(parser& p,std::string s){
        if(s.substr(0,this->name().length()) != this->name()){return false;}
        else if(!isdigit(s[this->name().length()])){return false;}
         d = this->name()[this->name().length()-1] - '0' ;if(d<2 or d>4){return false;}
        return true;}
    
    void proc(parser& p){
        if constexpr (pcs == pcntxt::stexpr){pushVecConstructor(d);}
        else pushVecDecl(d);
    };

};

template <Str s,typename T>
struct kw_mat : kw<s,T,kwty::prim> {
    size_t dx,dy;
    bool check(parser& p,std::string s){
        if(s != this->name().substr(0,s.length())){return false;}
        else if(!isdigit(s[this->name().length()])){return false;}
        dy=s[this->name().length()-1] - '0';if(dy<2 or dy>4){return false;}
        if(s.length() == (1+this->name().length())){dx=dy;return true};

        if(s[this->name().length()+1] !='x'){return false;}
        if(!isdigit(s[this->name().length()+2] )){return false;}
        dx=s[this->name().length()+2] - '0';if(dx<2 or dx>4){return false;}      
        return true;}
    void proc(parser& p){
        if constexpr (pcs == pcntxt::stexpr){pushMatConstructor(d);}
        else pushMatDecl(d);
    };
};

using kw_Vec =kw_vec<"vec",primVec,kwty::prim> ;
using kw_Mat =kw_mat<"mat",primMat,kwty::prim> ;
using kw_Ivec =kw_Ivec<"ivec",primiVec,kwty::prim> ;
using kw_Imat =kw_Imat<"imat",primiMat,kwty::prim> ;
using kw_Uvec =kw_Uvec<"uvec",primuVec,kwty::prim> ;
using kw_Umat =kw_Umat<"umat",primuMat,kwty::prim> ;
using kw_Bvec =kw_Bvec<"bvec",primbVec,kwty::prim> ;
using kw_Bmat =kw_Bmat<"bmat",primbMat,kwty::prim> ;
#define KW_LISTPRIM KW_LISTPRIM, kw_vec,kw_mat, kw_Ivec, kw_Imat, kw_Uvec, kw_Umat, kw_Bvec, kw_Bmat
enum accSpec{Public,Private,Protected};
struct kw_Struct : kw<"struct",type<temp::meta> ,kwty::Struct>{
    void proc(parser& p){
        p.accessPush<accSpec::Public>();
        p.getStruct();
    };
};
struct kw_Class : kw<"class",type<temp::meta>,kwty::Struct>{
    void proc(parser& p){
        p.accessPush<accSpec::Private>();
        p.getStruct();
    };
};
struct kw_Virtual : kw<"virtual",type<temp::meta>,kwty::qualifier>{
    void proc(parser& p){

    };

};
struct kw_Final : kw<"final",type<temp::meta>,kwty::qualifier>{
    void proc(parser& p){
        if(!p.isContextMethodDeclAfterArgList()){
            syserr.err<err::t::unexpected_kw>()
        }
    };
};


using kw_This= kw<"this",type<temp::meta>,kwty::Struct ;
#define KW_LISTKW KW_LISTKW, kw_Struct,kw_Class ,kw_This,kw_Virtual,kw_Final


using kw_Enum = kw<"enum",Enum , kwty::Enum>;
using kw_Template =  kw<"template",void,kwty::Tempstmt> ;
using kw_Typename =  kw<"typename",void,kwty::stmt> ;
using kw_Constexpr =  kw<"constexpr",void,kwty::qualifier> ;
using kw_Static =  kw<"static",void,kwty::qualifier> ;
#define KW_LISTKW KW_LISTKW,kw_Enum,kw_Template,kw_Typename,kw_Constexpr,kw_Static 
template <Str s,accSpec asT>
struct kw_as : kw<s,void,kwty::accessSpec> {
    void proc(parser& p){
        p.until<lex::ty::colon>();
        p.erase();
        p.access<asT>();
    };
};
using kw_Public = kw_as<"public",accSpec::Public>
using kw_Private = kw_as<"private",accSpec::Private>
using kw_Protected = kw_as<"protected",accSpec::Protected>
#define KW_ACCS kw_Public , kw_Private , kw_Protected 
using kw_If =  kw<"if",stmt<temp::meta>::StmtIf,kwty::funcStmt> ;
using kw_Else =  kw<"else",stmt<temp::meta>::StmtElse,kwty::funcStmt> ;
using kw_Switch =  kw<"switch",stmt<meta>::StmtSwitch,kwty::funcStmt> ;
using kw_Case =  kw<"case",stmt<temp::meta>::StmtCase,kwty::funcStmt> ;
using kw_Default = kw<"default",stmt<temp::meta>::StmtCase,kwty::funcStmt>;
using kw_While =  kw<"while",stmt<temp::meta>::StmtWhile,kwty::loopStmt> ;
using kw_For =  kw<"for",stmt<temp::meta>::StmtFor,kwty::loopStmt> ;
#define KW_LISTKW KW_LISTKW, kw_If  , kw_Else  , kw_Switch, kw_Case, kw_Default,  kw_While, kw_For 
struct kw_Do :  kw<"do",kwty::funcStmt> {
     void proc(parser& p){
        p.until<lex::ty::lbrace>();
        p.getBlock<>();
        p.untilKW<true,kw_For,kw_While>();
    };
} ;
#define KW_LISTKW KW_LISTKW, kw_Do 

#define KW_LIST KW_LISTKW ,KW_LISTLYT,KW_LISTPRIM

}
#endif