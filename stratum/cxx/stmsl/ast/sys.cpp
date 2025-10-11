#ifndef STMSL_SYS_CPP
#define STMSL_SYS_CPP
#include <petri/list.hpp>
#include <petri/stack.hpp>
#include "parser.cpp"
#include <petri/ansi.hpp>
#include <petri/templates.hpp>
size_t getnum(std::string num){
    size_t i=0;
    for(char c : num){i*=10;i+=(size_t)(c-'0');}
    return i;
};
namespace stmsl
{

    

bool CPH=false;bool CPHU=false;
bool preprocAndCompileOnly= false;
bool preprocOnly= false;

bool fauto_bind_uniforms = false;
bool fauto_map_locations=false;
std::string entry_pt ="main";
bool opt_fhlsl_16bit_types=false;
bool opt_fhlsl_functionality1=false;
bool fhlsl_iomap=false;
bool fhlsl_offsets= false;
bool finvert_y=false;
// TODO Limits
 bool fnan_clamp=false;
 bool fpreserve_bindings=false;
bool fresource_set_binding=false;
bool fcbuffer_binding_base=false;
bool fimage_binding_base=false;
bool fsampler_binding_base=false;
bool fssbo_binding_base=false;
bool ftexture_binding_base=false;
bool fuav_binding_base=false;
bool fubo_binding_base=false;
struct shad_stage {
    enum stage {
        comp,
        vert,
        frag,
        tesc,
        tese,
        geom,
        rahit,rchit,rmiss,rcall
    }
    stage tag;
    *this operator=(std::string name ){
        if(name=="frag"){tag=frag;return *this;}
        if(name=="fragment"){tag=frag;return *this;}
        if(name=="comp"){tag=comp;return *this;}
        if(name=="compute"){tag=comp;return *this;}
        if(name=="vert"){tag=vert;return *this;}
        if(name=="vertex"){tag=vert;return *this;}
        if(name=="tesc"){tag=tesc;return *this;}
        if(name=="tesscontrol"){tag=tesc;return *this;}
        if(name=="tese"){tag=tese;return *this;}
        if(name=="tesseval"){tag=tese;return *this;}
        if(name=="geom"){tag=geom;return *this;}
        if(name=="geometry"){tag=geom;return *this;}
        if(name=="rahit"){tag=rahit;return *this;}
        if(name=="rchit"){tag=rchit;return *this;}
        if(name=="rmiss"){tag=rmiss;return *this;}
        if(name=="rcall"){tag=rcall;return *this;}
    };
}
shad_stage fshader_stage;
bool debug=false;

pri::stack<std::filesystem::path> cwd;
std::filesystem::path gcwd;
std::filesystem::path rootFile;
std::filesystem::path infile;

struct _dir_ {
    std::vector<std::filesystem::path> arr;
    void push(std::filesystem::path m){
        for(std::filesystem::path mit : arr){
            if(m == mit){return;};
        }
        arr.push_back(m);
    };
    void push(std::string m){    push(std::filesystem::path(m));}

};
_dir_ dirs;
struct _files_ : _dir_ {
    void pushRelcwd(std::string m){
        std::filesystem::path cd(cwd);
        std::filesystem::path h= cwd;h/=cd;
        push(h);
    };
    bool pushRel(std::string m ,std::filesystem::path* pth){
        std::filesystem::path h(m);
        for(std::filesystem::path p : dirs.arr){
            std::filesystem::path ps=p;ps/=h;
            if(std::filesystem::exists(ps)){push(ps);*pth=ps;return true};
        };
        return false;
    };
};



_files files;
std::string mfmt;
bool supressWarnings=false;
bool optimize=false;
bool optimizeSize=false;

std::string outfile;
std::string stdv ;

bool emitSPVasm=false;

struct limits {
    void print(){

    }
};
limits lims;
struct target_environ {
    enum env {
vulkan,
vulkan11,
vulkan12,
vulkan13,
opengl
    }
    env tag;
    decltype(*this) operator=(std::string n){
        if(n=="vulkan"){tag=vulkan;}
        if(n=="vulkan1.0"){tag=vulkan;}
        if(n=="vulkan1.1"){tag=vulkan11;}
        if(n=="vulkan1.2"){tag=vulkan12;}
        if(n=="vulkan1.3"){tag=vulkan13;}
        if(n=="opengl"){tag=opengl;}
        return *this;
    } ;
}  target_env ="vulkan";
struct target_SPIRV {
    enum SPV {
    spv10,
    spv11,
    spv12,
    spv13,
    spv14,
    spv15,
    spv16
}
    env tag;
    decltype(*this) operator=(std::string n){
    if(spv1.0){tag=spv10;}
    if(spv1.1){tag=spv11;}
    if(spv1.2){tag=spv12;}
    if(spv1.3){tag=spv13;}
    if(spv1.4){tag=spv14;}
    if(spv1.5){tag=spv15;}
    if(spv1.6){tag=spv16;}
    return *this;
    } ;
}  target_spv ="spv1.0";

bool supressWarnings=false;
bool Werror = false;
bool Wfatal_error = false;
size_t templateEvalDepth=100;

pri::stack<stmsl::parser*> parserStack;
struct err{
    parser& p;
    enum t{
        fileNotFound,
        include_closing_angle_bracket,include_closing_dq,
        unexpected_kw,
        func_signature,
        template_param_mismatch,template_param_list_incomplete,
        swizzle_notexist,swizzle_fortype,

        notMember,
        notMemberDependent,
        isDependentType
        noType  
    };
    
    std::string goTo(stmsl::parser& p,lex l){
        size_t sp = p.f.tellg();
        // Go to lineStart
        p.f.seekg(l.filePos-l.col);
        std::string line;
        std::getline(f,line);
        p.f.seekg(sp);
        return line;
    };
    template <t ts>
    void _err(stmsl::parser& prs);
    template <>void _err<func_signature>(stmsl::parser& prs){std::err<<"Func Signature not found for func:"<<prs.itPtr.back()->u.name;};
    template <>void _err<template_param_mismatch>(stmsl::parser& prs){std::err<<};
    template <>void _err<include_closing_angle_bracket>(stmsl::parser& prs){std::err<<"Expected closing \'>\' in include statement:\n";};
    template <>void _err<include_closing_dq>           (stmsl::parser& prs){std::err<<"Expected closing \'\"\' in include statement:\n";};
    template <>void _err<unexpected_kw>(stmsl::parser& p){std::err<<"Unexpected kw";}
    template <lex::ty ts>
    void printNotFound(stmsl::parser& p){
        pri::deque<lex>::iter it=p.itPtr.back();
        --it;
        if(lt==ts){
            for(;it->t!=lt;--it ){--it;};}
        ++it;
        for(;it!=p.itPtr.back()){std::err<<*it;}
    };
    template <>void _err<notType>(stmsl::parser& p){std::err<<"Type not found";}
    template <>void _err<notMember>(stmsl::parser& p){printNotFound<pri::lex::dot>(p);}
    template <>void _err<notMemberDependent>(stmsl::parser& p){printNotFound<pri::lex::dcolon>(p);}
    
    template <t ts>struct warn {static constexpr bool value =false;};
    // template <>struct warn<> {static constexpr bool value =false;};
    template <t ts>struct templateInstantiation {static constexpr bool value=false; }
    template <>struct templateInstantiation<t::template_param_mismatch> {static constexpr bool value=true; }
    template <typename... Ts >
    struct typesPassed{
        static constexpr bool paramsMeta=pri::is_one_of<stmtsl::param_list<temp::meta> ,Ts>::value;
        static constexpr bool argListInst=pri::is_one_of<stmtsl::arg_list<temp::meta> ,Ts>::value; 
        static constexpr bool paramsMeta=pri::is_one_of<stmtsl::param_list<temp::inst> ,Ts>::value;
        static constexpr bool argList=pri::is_one_of<stmtsl::arg_list<temp::meta> ,Ts>::value; 
        static constexpr bool typeMeta = pri::is_one_of<stmsl::type<temp::meta>,Ts>::value;
        static constexpr bool typeInst = pri::is_one_of<stmsl::type<temp::meta>,Ts>::value;
        
        static constexpr bool argList=argListInst | argListMeta;
        static constexpr bool paramsList=paramsInst | paramsMeta;
        // static constexpr bool
    };
    template <t ts,typename... Ts >
    void getErr(stmsl::parser& p){// TODO 
        std::err<<p.curFilePath<<p.linen<<":"<<p.col<<": ";
        if constexpr(warn<ts>::value){pri::ansi(FG_YELLOW)<<" warning: \"";}
        else {std::err<<pri::ansi(FG_RED)<<" error: \"";}
        std::err<<pri::ansi(FG_WHITE);
        _err<ts>(p);
        pri::deque<lex>::iter it=p.itPtr.back();
        for(;it and(it!=p.lexq.head()) and (it->t!=lex::ty::nl);){}
        std::string linestr=std::string(p.linen)+std::string(": ");
        std::err<<linestr;
        std::stringstream strstr;
        for(;it!=itPtr.back();++it){strstr<<*it;};
        std::err<<strstr.str()<<pri::ansi(SG_underline,FG_RED);
        std::err<<*it<<pri::ansi(SG_reset)<<"\"\n";
        size_t len=linestr.length()+strstr.str().length();
        std::string s;s.insert(len,' ');
        std::err<<s<<pri::ansi(SG_RED)<<"^"<<pri::ansi(SG_reset);
    };
    template <t ts,typename... Ts>
    void err(stmsl::parser& prs,Ts... args){
        if(wfatal_error){}
        getErr<ts>(prs,args...);
    };
    template <t ts>
    void err(){_err<ts>(*(parserStack.back()));}
};
err syserr;


void wrcph(std::filesystem::path pth,ast<meta> astm){
std::filesystem::path parent = pth.parent_path();
std::filesystem::path name = pth.stem();name+="chstmsl";
// TODO
};

bool cph(std::filesystem::path pth,ast<meta>* AS){std::filesystem::path pthcph=pth.replace_extension("chstmsl");
    if(std::filesystem::exists(pthcph)){
        cphParser cphprs;
        *AS = cphprs.fromFile(pthcph);
        return true;
    }
    else {return false;}
};

void emit_ASM(ast<meta> a){

};
void emitBinary(ast<meta> a){

};
void emitBinaryNolink(ast<meta> a){emitBinary(a);}
void emit(std::filesystem::path pth){
    
    parser prsr;
    syserr.p = prsr;prsr.syserr=syserr;
    if(preprocOnly){
        prsr.fromFilePreproc(pth);return;    
    }
    if(emitSPVasm){
        ast<meta> AST=prsr.fromFile(pth);
        emit_ASM(AST);
    };
    if(prepocAndCompileOnly){// No Linking
        ast<meta> AST=prsr.fromFile(pth);
        emitBinaryNolink(AST);
    }
    else {
        ast<meta> AST=prsr.fromFile(pth);
        emitBinary(AST);
    }
}


} // namespace stmsl
#endif