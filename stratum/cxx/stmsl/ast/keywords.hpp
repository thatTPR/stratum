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
    name_attrib,qualifier,
    stmt,prim,layout_at,layout_qual
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
template <kwty kTY>
struct kw : context_tuple<kTY> {
    static constexpr kwty KT= kTY;
    const std::string name;
    bool _check(parser& p,std::string s){ 
        for(pcntxt it : *this){
            if(it==p.cntxt){return true;}
        };
        return false;
    }
    bool check(parser& p,std::string s){
        if(s!= name){return false;}
        return _check();}
    void proc(parser& p);
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

struct kw_version :  kw_mat<kwty::macro> {
static const std::string name = #version;
void proc(parser& p){    p.setVersion(p.getNum(p.untilEOL()));}

};



struct kw_Incl : kw<kwty::macro> {
    static const std::string name = "#include";
    void proc(parser& p){
        std::string s=p.untilEOL();
        std::string name;
        for(i=0;i<s.length() and s[i]==' ';i++){}
        for(i=0;i<s.length() and s[i]!=' ';i++){name+=line[i];}
        std::string str = name.substr(1,name.length()-2);
        if(name[0]=='<'){if(name[name.length()-1]=='>'){
            std::filesystem::path pth;
                if(p.pushRel(str,&pth)){
                    ast<meta> Ast;
                    ast<meta>& curTU = ast_stack.back();
                    if(CPHU && cph(pth,&Ast)){curTU.include(Ast);}
                    else {cphAst = p.include(pth);curTU.include(Ast);}
                }
                else {syserr<err::t::include_closing_angle_bracket>(p);}}
                else{ if(name[name.length()-1]=='\"'){
                    p.pushRelcwd(str);}
                    else {syserr<err::t::include_closing_dq>(p);}}
        }
    };
};
#define KW_LIST kw_Incl 


struct kw_Define :  kw<kwty::macro> ; 



struct kw_if :  kw<kwty::macro> ;
struct kw_else :  kw<kwty::macro> ;
struct kw_elif :  kw<kwty::macro> ;
struct kw_elifdef :  kw<kwty::macro> ;
struct kw_endif :  kw<kwty::macro> ;
struct kw_ifndef :  kw<kwty::macro> ;


struct kw_Define :  kw<kwty::macro> {
static const std::string name = "#define";
void proc(parser& p){
    std::string s=p.untilEOL();
    std::string name ;std::string value;size_t i;
    for(i=0;i<s.length() and s[i]==' ' ;i++){}
    for(i=0;i<s.length() and s[i]!=' ';i++){name+=line[i];}
    for(i=0;i<s.length() ;i++){value+=line[i];}
    macros.push(macro(name,value));
};
};

struct kw_if :  kw<kwty::macro> {
static const std::string name = "#if";
void proc(parser& p){
    expr<meta> Ex = p.parse(p.untilEOL());
    ex.
    p.cast.push_back(tu<meta>(Ex));
};
};
struct kw_else :  kw<kwty::macro> {
static const std::string name = "#else";
void proc(parser& p){ 
    expr<meta> Ex = p.parse(p.untilEOL());
    p.cast.push_back(tu<meta>(Ex));
};
};
    struct kw_elif :  kw<kwty::macro> {
static const std::string name = "#elif";
void proc(parser& p){ 
    expr<meta> Ex = p.parse(p.untilEOL());
    p.cast.push_back(tu<meta>(Ex));
};
};
    struct kw_elifdef :  kw<kwty::macro> {
static const std::string name = "#elifdef";
void proc(parser& p){};
};
    struct kw_endif :  kw<kwty::macro> {
static const std::string name = "#endif";
void proc(parser& p){};
};
    struct kw_ifndef :  kw<kwty::macro> {
static const std::string name = "#ifndef";
void proc(parser& p){ 
    std::string str=p.untilEOL();
    std::string s;for(size_t i=0;i<str.length();i++){
        if(str[i]!=' '){size_t p=str.find_first_of(" ");
            if(p!=std::string::npos){s=str.substr(i,p-i+1);break;};
            else {s.str.substr(i);}
        }
    } ;
    bool found=false;
    for(macro mit : macros.mlist){
        if(mit.name==s){found=true;break;}
    };
    if(found){
        p.cast.push_back(tu<meta>(expr<meta>(true)))
    }
    else {p.untilKWs<kw_else,kw_elif,kw_elifdef,kw_endif>();}
};
};
struct kw_ifdef :  kw<kwty::macro> {
static const std::string name = "#ifdef";
void proc(parser& p){ 
    
};
};
struct kw_Layout :  kw<kwty::stmt> {
static const std::string name = "layout";
void proc(parser& p){ 
    
};
};
struct kw_Location :  kw<kwty::layout_at> {
static const std::string name = "location";
void proc(parser& p){
};
};
struct kw_Binding :  kw<kwty::layout_at> {
static const std::string name = "binding";
void proc(parser& p){
};
};
struct kw_uniform :  kw<kwty::qualifier> {
static const std::string name = "uniform";
void proc(parser& p){
};
};
struct kw_in :  kw<kwty::qualifier> {
static const std::string name = "in";
void proc(parser& p){
};
};
struct kw_out :  kw<kwty::qualifier> {
static const std::string name = "out";
void proc(parser& p){
};
};
struct kw_inout :  kw<kwty::qualifier> {
static const std::string name = "inout";
void proc(parser& p){ 
    
};
};
struct kw_Return :  kw<kwty::funcStmt> {
static const std::string name = "return";
void proc(parser& p){ 
    expr<q> ex=p.untilSemiColon(); 
};
};
#define KW_LIST
struct kw_Buffer :  kw<kwty::prim> {
static const std::string name = "buffer";
void proc(parser& p){
};
};
#define KW_LIST

struct kw_Image2D :  kw<kwty::prim> {
static const std::string name = "image2D";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Image3D :  kw<kwty::prim> {
static const std::string name = "image3D";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Sampler :  kw<kwty::prim> {
static const std::string name = "sampler";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Void :  kw<kwty::prim> {
static const std::string name = "void";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Float :  kw<kwty::prim> {
static const std::string name = "float";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Int :  kw<kwty::prim> {
static const std::string name = "int";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Uint :  kw<kwty::prim> {
static const std::string name = "uint";
void proc(parser& p){
};
};
#define KW_LIST
struct kw_Bool :  kw<kwty::prim> {
static const std::string name = "bool";
void proc(parser& p){
};
};
#define KW_LIST




template <kwty kTY,pcntxt pc,pcntxt... pcs>
struct kw_vec : kw<kTY,pc,pcs...> {    size_t d;
    bool check(parser& p,std::string s){
        if(s.substr(0,this->name.length()) != this->name){return false;}
        else if(!isdigit(s[this->name.length()])){return false;}
        size_t d = this->name[this->name.length()-1] - '0' ;if(d<2 or d>4){return false;}

        return true;}
    void proc(parser& p){
        
    };
};

template <kwty kTY,pcntxt pc,pcntxt... pcs>
struct kw_mat : kw<kTY,pc,pcs...> {
    size_t dx,dy;
    bool check(parser& p,std::string s){
        if(s.substr(0,this->name.length()) != this->name){return false;}
        else if(!isdigit(s[this->name.length()])){return false;}
        dy=s[this->name.length()] - '0';if(dy<2 or dy>4){return false;}
        if(s[this->name.length()+1] !='x'){return false;}
        if(!isdigit(s[this->name.length()+2] )){return false;}
        dx=s[this->name.length()+2] - '0';if(dx<2 or dx>4){return false;}
        return true;}
    void proc(parser& p){

    };
};
#define KW_VEC(name,sname,KWTY) struct name : kw_vec<KWTY> {const std::string name = sname;}; \
#define KW_LIST KW_LIST, name
#define KW_MAT(name,sname,KWTY) struct name : kw_mat<KWTY> {const std::string name = sname;}; \
#define KW_LIST KW_LIST, name

struct kw_Vec :  kw_vec<      kwty::prim> {
static const std::string name =       "vec";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Vec
struct kw_Mat :  kw_mat<      kwty::prim> {
static const std::string name =       "mat";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Mat
struct kw_Ivec :  kw_vec<     kwty::prim> {
static const std::string name =      "ivec";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Ivec
struct kw_Imat :  kw_mat<     kwty::prim> {
static const std::string name =      "imat";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Imat
struct kw_Uvec :  kw_vec<     kwty::prim> {
static const std::string name =      "uvec";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Uvec
struct kw_Umat :  kw_mat<     kwty::prim> {
static const std::string name =      "umat";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Umat
struct kw_Bvec :  kw_vec<     kwty::prim> {
static const std::string name =      "bvec";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Bvec
struct kw_Bmat :  kw_mat<     kwty::prim> {
static const std::string name =      "bmat";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Bmat
struct kw_Flat :  kw_mat<     kwty::qualifier> {
static const std::string name =      "flat";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Flat
struct kw_Const :  kw_mat<    kwty::qualifier> {
static const std::string name =     "const";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Const
struct kw_Template :  kw_mat< kwty::name_attrib> {
static const std::string name =  "template";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST,  kw_Template
struct kw_Typename :  kw_mat< kwty::name_attrib> {
static const std::string name =  "typename";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Typename
struct kw_Constexpr :  kw<kwty::qualifier> {
static const std::string name = "constexpr";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Constexpr 
struct kw_Do :  kw_mat<       kwty::funcStmt> {
static const std::string name =        "do";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Do 
struct kw_While :  kw_mat<    kwty::funcStmt> {
static const std::string name =     "while";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST,  kw_While
struct kw_For :  kw_mat<      kwty::funcStmt> {
static const std::string name =       "for";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_For 
struct kw_If :  kw_mat<       kwty::funcStmt> {
static const std::string name =        "if";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_If  
struct kw_Else :  kw_mat<     kwty::funcStmt> {
static const std::string name =      "else";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Else  
struct kw_Switch :  kw_mat<   kwty::funcStmt> {
static const std::string name =    "switch";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Switch
struct kw_Case :  kw_mat<   kwty::funcStmt> {
static const std::string name =      "switch";
void proc(parser& p){
};
};
#define KW_LIST KW_LIST, kw_Case
kw_Case::proc(parser& p){

};


template <temp q,typename kw>
struct stmt_kw_ty{using type = stmt<q>::stmtExpr;};

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
struct stmt_kw_ty<q,kw_else>{using type = macroStmt::mStmtElse;
    using clsty = macroStmt;
};
template <temp q>
struct stmt_kw_ty<q,kw_>{using type = macroStmt::mStmtElse;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_While>{using type = Stmt::StmtWhile;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_For>{using type = Stmt::StmtFor;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_If>{using type = Stmt::StmtIf;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_Else>{using type = Stmt::StmtElse;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_Switch>{using type = Stmt::StmtSwitch;
    using clsty = Stmt;};

template <temp q>
struct stmt_kw_ty<q,kw_Case>{using type = Stmt::StmtCase;
    using clsty = Stmt;};
template <temp q>
struct stmt_kw_ty<q,kw_Do>{using type = Stmt::block;
    using clsty = Stmt;};



}
#endif