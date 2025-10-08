#ifndef STMSL_KW
#define STMSL_KW
#include "ast.hpp"

namespace stmsl{
enum pcntxt {
    turoot=        0b0000000001,
    global=        0b0000000010,
    funcblock=     0b0000000100,
    funcargqual=   0b0000001000,
    parameterlist= 0b0000010000,
    declType=      0b0000100000,
    layoutArgs=    0b0001000000,
    layoutDef=     0b0010000000,
    funcret=       0b0100000000,
    stexpr=        0b1000000000,
};


enum kwty {
    macro,
    qualifier,
    stmt,tempstmt,prim,layout_at,layout_qual,layout_Stmt
    builtinFunc,builtinVar,
    funcStmt
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
    static constexpr size_t s =global|funcblock ;
};
template <>struct contxt_kw<kwty::stmt>{
    static constexpr size_t s =global|funcblock ;
};
template <>struct contxt_kw<kwty::prim>{
    static constexpr size_t s =global|funcblock ;};
template <>struct contxt_kw<kwty::layout_at>{
    static constexpr size_t s = layoutArgs ;
};
template <>struct contxt_kw<kwty::layout_qual>{
    static constexpr size_t s =layoutDef|funcargqual ;
};
template <>struct contxt_kw<kwty::builtinFunc>{
    static constexpr size_t s = global|funcblock ;
};
template <>struct contxt_kw<kwty::builtinVar>{
    static constexpr size_t s = global|funcblock|stexpr ;
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

#define KW_LIST 

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

template <typename KW>
struct kwordMeta {
    static constexpr bool macro;
    static constexpr bool
};

template <Str s,typename KW,kwty kTY>
struct kw : hs<S>,context_tuple<kTY> {
    using type = KW;
    static constexpr kwty KT= kTY;
    static std::string name() {return S.name();}
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
    void _proc(parser& p);
    template <>void _proc<kwty::macro>(parser& p){p.getMacro(p.getMacro()<KW>());};
    template <>void _proc<kwty::qualifier>(parser& p){p.putQualifier<KW>();};
    template <>void _proc<kwty::layout_Stmt>(parser& p){p.LayoutNew<KW>();};
    template <>void _proc<kwty::layout_at>(parser& p){p.putLayout<KW>();};
    template <>void _proc<kwty::layout_qual>();
    template <>void _proc<kwty::builtinFunc>();
    template <>void _proc<kwty::builtinVar>();
    template <>void _proc<kwty::funcStmt>();  
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
#define KW_N(name,sname,KWTY) struct name : kw<KWTY> {static const std::string name = sname;void proc(smtsl_parser& p) ;}; \
#define KW_LIST KW_LIST, name

#define KW_NDECL(name,sname,KWTY) struct name : kw<KWTY> ;

using kw_version =  kw<"version",macroStmt::mStmtVersion,kwty::macro> ;
// void kw_version::proc(parser& p){    p.setVersion(p.getNum(p.untilEOL()));}

#define KW_LIST kw_version,

using kw_Incl = kw<"#include",macroStmt::mStmtInclude,kwty::macro> ;
#define KW_LIST KW_LIST kw_Incl, 

using kw_Define =  kw<"#define",macroStmt::mStmtDefine,kwty::macro> ;
#define KW_LIST KW_LIST, kw_Define 

using kw_if =  kw<"#if",macroStmt::mStmtIf,kwty::macro> ;
#define KW_LIST KW_LIST, kw_if 
using kw_else =  kw<"#else",macroStmt::mStmtElse,kwty::macro>;
#define KW_LIST KW_LIST, kw_elif 

using kw_elif =  kw<"#elif",macroStmt::mStmtElif,kwty::macro> ;
#define KW_LIST KW_LIST, kw_elif 

using kw_elifdef =  kw<"#elifdef",macroStmt::mStmtElifdef,kwty::macro> ;
#define KW_LIST KW_LIST, kw_elifdef 

using kw_endif =  kw<"#endif",macroStmt::mStmtEndIf,kwty::macro> ;
#define KW_LIST KW_LIST, kw_endif 

    using kw_ifndef =  kw<"#ifndef",macroStmt::mStmtIfndef,kwty::macro> ;
#define KW_LIST KW_LIST, kw_ifndef 

using kw_ifdef =  kw<"#ifdef",macroStmt::mStmtIfdef,kwty::macro> ;
#define KW_LIST KW_LIST, kw_ifdef 

using kw_Layout =  kw<"layout",stmt<meta>::StmtLayout,kwty::layout_Stmt> ;
#define KW_LIST KW_LIST, kw_Layout 

using kw_Location =  kw<"location",stmt<meta>::Location,kwty::layout_at> ;
#define KW_LIST KW_LIST, kw_Location 

using kw_Binding =  kw<"binding",stmt<meta>::Binding,kwty::layout_at> ;
#define KW_LIST KW_LIST, kw_Binding 

using kw_uniform =  kw<"uniform",stmt<meta>::StmtLayout,kwty::layout_qual> ;
#define KW_LIST KW_LIST, kw_uniform 
using kw_Buffer =  kw<"buffer",kwty::layout_qual> ;
#define KW_LIST KW_LIST,kw_Buffer


using kw_Const =  kw_mat<"const",atConst,kwty::qualifier> ;
#define KW_LIST KW_LIST, kw_Const
using kw_Flat =  kw_mat<"flat",atFlat,kwty::qualifier> ;
#define KW_LIST KW_LIST, kw_Flat 
using kw_in =  kw<"in",atIn,kwty::qualifier> ;
#define KW_LIST KW_LIST, kw_in 
using kw_out =  kw<"out",atOut,kwty::qualifier> ;
#define KW_LIST KW_LIST, kw_out 
using kw_inout =  kw<"inout",atInout,kwty::qualifier> ;
#define KW_LIST KW_LIST, kw_inout 

using kw_Return =  kw<"return",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_Return 
using kw_Image2D =  kw<"image2D",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Image2D
using kw_Image3D =  kw<"image3D",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Image3D
using kw_Sampler =  kw<"sampler",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Sampler
using kw_Void =  kw<"void",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Void
using kw_Float =  kw<"float",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Float
using kw_Int =  kw<"int",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Int
using kw_Uint =  kw<"uint",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Uint
using kw_Bool =  kw<"bool",kwty::prim> ;
#define KW_LIST KW_LIST,kw_Bool

template <Str s,typename T>
struct kw_vec : kw<s,T,kwty::builtinVar> {    size_t d;
    bool check(parser& p,std::string s){
        if(s.substr(0,this->name().length()) != this->name){return false;}
        else if(!isdigit(s[this->name().length()])){return false;}
        size_t d = this->name()[this->name().length()-1] - '0' ;if(d<2 or d>4){return false;}

        return true;}
    void proc(parser& p){
        
    };
};

template <Str s,typename T>
struct kw_mat : kw<s,T,kwty::builtinVar> {
    size_t dx,dy;
    bool check(parser& p,std::string s){
        if(s.substr(0,this->name().length()) != this->name){return false;}
        else if(!isdigit(s[this->name().length()])){return false;}
        dy=s[this->name().length()] - '0';if(dy<2 or dy>4){return false;}
        if(s[this->name().length()+1] !='x'){return false;}
        if(!isdigit(s[this->name().length()+2] )){return false;}
        dx=s[this->name().length()+2] - '0';if(dx<2 or dx>4){return false;}
        return true;}
    void proc(parser& p){

    };
};

using kw_Vec =kw_vec<"vec",primVec,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Vec
using kw_Mat =kw_mat<"mat",primMat,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Mat
using kw_Ivec =kw_vec<"ivec",primiVec,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Ivec
using kw_Imat =kw_mat<"imat",primiMat,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Imat
using kw_Uvec =kw_vec<"uvec",primuVec,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Uvec
using kw_Umat =kw_mat<"umat",primuMat,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Umat
using kw_Bvec =kw_vec<"bvec",primbVec,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Bvec
using kw_Bmat =kw_mat<"bmat",primbMat,kwty::prim> ;
#define KW_LIST KW_LIST, kw_Bmat

using kw_Template =  kw<"template",kwty::Tempstmt> ;
#define KW_LIST KW_LIST,  kw_Template
using kw_Typename =  kw<"typename",kwty::stmt> ;
#define KW_LIST KW_LIST, kw_Typename
using kw_Constexpr =  kw<"constexpr",kwty::qualifier> ;
#define KW_LIST KW_LIST, kw_Constexpr 
using kw_Do =  kw<"do",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_Do 
using kw_While =  kw<"while",kwty::funcStmt> ;
#define KW_LIST KW_LIST,  kw_While
using kw_For =  kw<"for",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_For 
using kw_If =  kw<"if",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_If  
using kw_Else =  kw<"else",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_Else  
using kw_Switch =  kw<"switch",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_Switch
using kw_Case =  kw<"switch",kwty::funcStmt> ;
#define KW_LIST KW_LIST, kw_Case


template <temp q,typename kw>
struct stmt_kw_ty{using type = stmt<q>::stmtVarDecl;};
template <temp q>
struct stmt_kw_ty<q,kw_Incl>{using type = macroStmt::mStmtInclude;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_Define>{using type = macroStmt::mStmtDefine;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_if>{using type = macroStmt::mStmtIf;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_elif>{using type = macroStmt::mStmtElif;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_elifdef>{using type = macroStmt::mStmtElifdef;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_else>{using type = macroStmt::mStmtElse;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_else>{using type = stmt<q>::StmtElse;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_Layout>{using type = stmt<q>::StmtLayout;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Location>{using type = stmt<q>::StmtLayout;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Binding>{using type = stmt<q>::StmtLayout;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Uniform>{using type = stmt<q>::StmtLayout;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Flat>{using type = stmt<q>::StmtLayout;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_in>{using type = stmt<q>::StmtVardecl;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_inout>{using type = stmt<q>::StmtVardecl;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_out>{using type = stmt<q>::StmtVardecl;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Return>{using type = stmt<q>::StmtFuncDef;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Buffer>{using type = stmt<q>::StmtLayout;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Image2D>{using type = stmt<q>::StmtVardecl;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_While>{using type = stmt<q>::StmtWhile;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_For>{using type = stmt<q>::StmtFor;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_If>{using type = stmt<q>::StmtIf;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_Else>{using type = stmt<q>::StmtElse;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_Switch>{using type = stmt<q>::StmtSwitch;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_Case>{using type = stmt<q>::StmtCase;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Do>{using type = stmt<q>::block;
    using clsty = Stmt;};



}
#endif