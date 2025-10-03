#ifndef STMSL_SYS_CPP
#define STMSL_SYS_CPP
#include <petri/list.hpp>
#include <petri/stack.hpp>
#include "parser.cpp"

namespace stmsl
{

    

struct macro {
    std::string name ,val;
    macro(std::string _name,std::string _val) : name(_name) : val(_val) {}
}

struct macrosl {
    pri::list<macro> mlist ;
    void push(macro m ){
        for(macro mit : mlist){
            if(m.name == mit.name){
                mit.val=m.val;return;
            };
        }
        mlist.push_back(m);
    }
};
macrosl macros;
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


struct _errs{
    parser& p;
    enum sys{
        template_instance,
    };
    void operator(sys s){

    };

};
_errs syserr;


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
    syserr _errs;errs.p = prsr;prsr.syserr=syserr;
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