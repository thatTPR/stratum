#include <filesystem>
#include <limits.h>
#ifdef _WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif
#include <string>

std::filesystem::path get_CWD(){ char _cwd[PATH_MAX];
    std::filesystem::path pth;
    if (GetCurrentDir(_cwd, sizeof(_cwd)) != nullptr) {
        pth = std::filesystem::path(_cwd);return 
    } else {
        perror("getcwd() error");
    }
    return pth;
};
const std::string help_strng="\
Usage: glslc [options] file...\
\
An input file of - represents standard input.\
\
Options:\
  -CPH Compiled header for .hstmsl files
  -CPHU Use Compiled headers
  -c                Only run preprocess, compile, and assemble steps.\
  -Dmacro[=defn]    Add an implicit macro definition.\
  -E                Outputs only the results of the preprocessing step.\
                    Output defaults to standard output.\
  -fauto-bind-uniforms\
                    Automatically assign bindings to uniform variables that\
                    don't have an explicit 'binding' layout in the shader\
                    source.\
  -fauto-map-locations\
                    Automatically assign locations to uniform variables that\
                    don't have an explicit 'location' layout in the shader\
                    source.\
  -fauto-combined-image-sampler\
                    Removes sampler variables and converts existing textures\
                    to combined image-samplers.\
  -fentry-point=<name>\
                    Specify the entry point name for HLSL compilation, for\
                    all subsequent source files.  Default is \"main\".\
  -fhlsl-16bit-types\
                    Enable 16-bit type support for HLSL.\
  -fhlsl_functionality1, -fhlsl-functionality1\
                    Enable extension SPV_GOOGLE_hlsl_functionality1 for HLSL\
                    compilation.\
  -fhlsl-iomap      Use HLSL IO mappings for bindings.\
  -fhlsl-offsets    Use HLSL offset rules for packing members of blocks.\
                    Affects only GLSL.  HLSL rules are always used for HLSL.\
  -finvert-y        Invert position.Y output in vertex shader.\
  -flimit=<settings>\
                    Specify resource limits. Each limit is specified by a limit\
                    name followed by an integer value.  Tokens should be\
                    separated by whitespace.  If the same limit is specified\
                    several times, only the last setting takes effect.\
  -flimit-file <file>\
                    Set limits as specified in the given file.\
  -fnan-clamp       Generate code for max and min builtins so that, when given\
                    a NaN operand, the other operand is returned. Similarly,\
                    the clamp builtin will favour the non-NaN operands, as if\
                    clamp were implemented as a composition of max and min.\
  -fpreserve-bindings\
                    Preserve all binding declarations, even if those bindings\
                    are not used.\
  -fresource-set-binding [stage] <reg0> <set0> <binding0>\
                        [<reg1> <set1> <binding1>...]\
                    Explicitly sets the descriptor set and binding for\
                    HLSL resources, by register name.  Optionally restrict\
                    it to a single stage.\
  -fcbuffer-binding-base [stage] <value>\
                    Same as -fubo-binding-base.\
  -fimage-binding-base [stage] <value>\
                    Sets the lowest automatically assigned binding number for\
                    images.  Optionally only set it for a single shader stage.\
                    For HLSL, the resource register number is added to this\
                    base.\
  -fsampler-binding-base [stage] <value>\
                    Sets the lowest automatically assigned binding number for\
                    samplers  Optionally only set it for a single shader stage.\
                    For HLSL, the resource register number is added to this\
                    base.\
  -fssbo-binding-base [stage] <value>\
                    Sets the lowest automatically assigned binding number for\
                    shader storage buffer objects (SSBO).  Optionally only set\
                    it for a single shader stage.  Only affects GLSL.\
  -ftexture-binding-base [stage] <value>\
                    Sets the lowest automatically assigned binding number for\
                    textures.  Optionally only set it for a single shader stage.\
                    For HLSL, the resource register number is added to this\
                    base.\
  -fuav-binding-base [stage] <value>\
                    For automatically assigned bindings for unordered access\
                    views (UAV), the register number is added to this base to\
                    determine the binding number.  Optionally only set it for\
                    a single shader stage.  Only affects HLSL.\
  -fubo-binding-base [stage] <value>\
                    Sets the lowest automatically assigned binding number for\
                    uniform buffer objects (UBO).  Optionally only set it for\
                    a single shader stage.\
                    For HLSL, the resource register number is added to this\
                    base.\
  -fshader-stage=<stage>\
                    Treat subsequent input files as having stage <stage>.\
                    Valid stages are vertex, vert, fragment, frag, tesscontrol,\
                    tesc, tesseval, tese, geometry, geom, compute, and comp.\
  -g                Generate source-level debug information.\
  -h                Display available options.\
  --help            Display available options.\
  -I <value>        Add directory to include search path.\
  -mfmt=<format>    Output SPIR-V binary code using the selected format. This\
                    option may be specified only when the compilation output is\
                    in SPIR-V binary code form. Available options are:\
                      bin   - SPIR-V binary words.  This is the default.\
                      c     - Binary words as C initializer list of 32-bit ints\
                      num   - List of comma-separated 32-bit hex integers\
  -M                Generate make dependencies. Implies -E and -w.\
  -MM               An alias for -M.\
  -MD               Generate make dependencies and compile.\
  -MF <file>        Write dependency output to the given file.\
  -MT <target>      Specify the target of the rule emitted by dependency\
                    generation.\
  -O                Optimize the generated SPIR-V code for better performance.\
  -Os               Optimize the generated SPIR-V code for smaller size.\
  -O0               Disable optimization.\
  -o <file>         Write output to <file>.\
                    A file name of '-' represents standard output.\
  -std=<value>      Version and profile for GLSL input files. Possible values\
                    are concatenations of version and profile, e.g. 310es,\
                    450core, etc.  Ignored for HLSL files.\
  -S                Emit SPIR-V assembly instead of binary.\
  --show-limits     Display available limit names and their default values.\
  --target-env=<environment>\
                    Set the target client environment, and the semantics\
                    of warnings and errors.  An optional suffix can specify\
                    the client version.  Values are:\
                        vulkan1.0       # The default\
                        vulkan1.1\
                        vulkan1.2\
                        vulkan1.3\
                        vulkan          # Same as vulkan1.0\
                        opengl4.5\
                        opengl          # Same as opengl4.5\
  --target-spv=<spirv-version>\
                    Set the SPIR-V version to be used for the generated SPIR-V\
                    module.  The default is the highest version of SPIR-V\
                    required to be supported for the target environment.\
                    For example, default for vulkan1.0 is spv1.0, and\
                    the default for vulkan1.1 is spv1.3,\
                    the default for vulkan1.2 is spv1.5.\
                    the default for vulkan1.3 is spv1.6.\
                    Values are:\
                        spv1.0, spv1.1, spv1.2, spv1.3, spv1.4, spv1.5, spv1.6\
  --version         Display compiler version information.\
  -w                Suppresses all warning messages.\
  -Werror           Treat all warnings as errors.\
  //-x <language>     Treat subsequent input files as having type <language>.\
                    Valid languages are: glsl, hlsl.\
                    For files ending in .hlsl the default is hlsl.\
                    Otherwise the default is glsl.\
    --template-eval-depth=<n> template eval depth \
                    \
                    ";


// cliopts
#include <petri/templates.hpp>
template <pri::Str S>
struct hs {
    static constexpr auto value = S;
    static std::string name() { return std::string(value.data.data()); }
};

template <pri::Str s,bool takesArgs>
struct opt {
    static constexpr args = takesArgs;
    static std::string n(){return s.name();} ; 
    std::string val;
    bool check(std::string s){
        size_t p = s.find(n());
        if(s.find(n())!=std::string::npos){
            val = s.substr(n().length());
            return true;}
    };
     void proc(int argc,char* argv[],int& i);
     void proc();
}
#define OPTS_MACROS

#define OPTS_MACROS OPTS_MACROS , name


struct opt_CPH : opt<"-CPH",false>{
void proc(){stmsl::CPH=true;}
};
struct opt_CPHU : opt<"-CPHU",false>{
void proc(){stmsl::CPHU=true;};
};
struct opt_c  : opt<"-c",false>{
void proc(){stmsl::preprocAndCompileOnly=true;};
};
struct opt_D  : opt<"-D",false>{
void proc(){
    size_t pos= this->val.find("=");
    if(pos!=std::string::npos){
        std::string n=val.substr(0,pos);
        std::string v = val.substr(pos+1);
        stmsl::macros.push(macro(n,v));
    }
    else {stmsl::macros.push(macro(val,std::string()));}    
};
};
struct opt_E : opt<"-E",false>{
void proc(){stmsl::preprocOnly=true;};
};
struct opt_fauto_bind_uniforms : opt<"-fauto-bind-uniforms",false>{
void proc(){stmsl::fauto_bind_uniforms=true;};
};
struct opt_fauto_map_locations : opt<"-fauto-map-locations",false>{
void proc(){stmsl::fauto_map_locations=true;};
};
struct opt_fauto_combined_image_sampler : opt<"-fauto-combined-image-sampler",false>{
void proc(){stmsl::fauto_combined_image_sampler=true;};
};
struct opt_fentry_point : opt<"-fentry-point",true>{
void proc(int argc,char* argv[],int& i){
    stmsl::entry_pt = std::string(argv[i]);   
};  
};

struct opt_fhlsl_16bit_types : opt<  "-fhlsl-16bit-types",false>{
void proc(){stmsl::opt_fhlsl_16bit_types=true;};
};
struct opt_fhlsl_functionality1 : opt<"-fhlsl_functionality1",false>{
void proc(){stmsl::opt_fhlsl_functionality1=true;};
};
struct opt_fhlsl_iomap : opt<"-fhlsl-iomap",false>{
void proc(){stmsl::fhlsl_iomap=true;};
};
struct opt_fhlsl_offsets : opt<"-fhlsl-offsets",false>{
void proc(){stmsl::fhlsl_offsets=true;};
};
struct opt_finvert_y : opt<"-finvert-y",false>{
void proc(){stmsl::finvert_y=true;};
};
struct opt_flimit : opt<"-flimit",true>{
void proc(int argc,char* argv[],int& i){}//TODO
};



//   "-flimit-file"
struct opt_fnan_clamp : opt<"-fnan-clamp",false>{
void proc(){stmsl::fnan_clamp=true;};
};
struct opt_fpreserve_bindings : opt<"-fpreserve-bindings",false>{
void proc(){stmsl::fpreserve_bindings=true;};
};


struct opt_fresource_set_binding : opt<"-fresource-set-binding",false>{
void proc(){stmsl::fresource_set_binding=true;};
};
struct opt_fcbuffer_binding_base : opt<"-fcbuffer-binding-base",false>{
void proc(){stmsl::fcbuffer_binding_base=true;};
};
struct opt_fimage_binding_base : opt<"-fimage-binding-base",false>{
void proc(){stmsl::fimage_binding_base=true;};
};
struct opt_fsampler_binding_base : opt<"-fsampler-binding-base",false>{
void proc(){stmsl::fsampler_binding_base=true;};
};
struct opt_fssbo_binding_base : opt<"-fssbo-binding-base",false>{
void proc(){stmsl::fssbo_binding_base=true;};
};
struct opt_ftexture_binding_base : opt<"-ftexture-binding-base",false>{
void proc(){stmsl::ftexture_binding_base=true;};
};
struct opt_fuav_binding_base : opt<"-fuav-binding-base",false>{};

void opt_fuav_binding_base::proc(){stmsl::fuav_binding_base=true;}
struct opt_fubo_binding_base : opt<"-fubo-binding-base",false>{
void proc(){stmsl::fubo_binding_base=true;};
};
  
struct opt_fshader_stage : opt<"-fshader-stage",false>{
void proc(){stmsl::fshader_stage=this->val;};
};
struct opt_g : opt<"-g",false>{
void proc(){stmsl::debug=true;};
};
struct opt_h : opt<"-h",false>{
void proc(){std::cout<<help_strng;};
};
struct opt_help : opt<"--help",false>{
void proc(){std::cout<<help_strng;};
};
struct opt_I : opt<"-I",false>{
void proc(){stmsl::dirs.push(this->val);};
};
struct opt_mfmt : opt<"-mfmt",false>{
void proc(){stmsl::mfmt=this->val;};
};

// struct opt_MD : opt<"-MD",true>{};
#define OPTS_MACROS OPTS_MACROS,opt_MD
 
// void opt_MD::proc(){generate_make_deps=true;}
// struct opt_MF : opt<"-MD",true>{};
#define OPTS_MACROS OPTS_MACROS,opt_M

#define OPTS_MACROS OPTS_MACROS,opt_MF
// void opt_MF::proc(){generate_make_deps=true;};
//};
// "-MF"
// "-MT"
// struct opt_M : opt<"-M",true>{};
 
// void opt_M::proc(){generate_make_deps=true;preprocOnly=true;}
struct opt_O : opt<"-O",false>{
void proc(){stmsl::optimize=true;};
};
struct opt_Os : opt<"-Os",false>{
void proc(){stmsl::optimizeSize=true;};
};
struct opt_O0 : opt<"-O0",false>{
void proc(){stmsl::optimizeSize=false;stmsl::optimize=false;};
};

// struct opt_o : opt<"-o",false>{};

struct opt_std : opt<"-std",false>{
void proc(){stmsl::stdv=this->val;}
struct opt_S : opt<"-S",false>{
void proc(){stmsl::emitSPVasm=true;};
};
struct opt_show_limits : opt<"--show-limits",false>{
void proc(){stmsl::lims.print();};
};
struct opt_target_env : opt<"--target-env",false>{
void proc(){stmsl::target_env=this->val;};
};
struct opt_target_spv : opt<"--target-env",false>{
void proc(){stmsl::target_spv=this->val;};
};
struct opt_version : opt<"--version",false>{
void proc(){std::cout<<"version: 1.0";};
};

struct opt_w : opt<"-w",false>{
void proc(){stmsl::supressWarnings=true;};
};

struct opt_Werror : opt<"-Werror",false>{
void proc(){stmsl::Werror=true;}
}

struct opt_W_fatal_errors : opt<"-Wfatal-errors",false>{void proc(){stmsl::Wfatal_error=true;}};
struct :opt<"--template-eval-depth",true>{void proc(int argc,char* argv[],int& i){
    templateEvalDepth=getnum(val);
};};


#define OPTS_MACROS OPTS_MACROS,opt_Werror,opt_W_fatal_errors,opt_CPH,opt_CPHU,opt_c ,opt_D ,opt_E,opt_fauto_bind_uniforms,opt_fauto_map_locations,opt_fauto_combined_image_sampler,opt_fentry_point,opt_fhlsl_16bit_types,opt_fhlsl_functionality1,opt_fhlsl_iomap,opt_fhlsl_offsets,opt_finvert_y,opt_flimit,opt_fnan_clamp,opt_fpreserve_bindings,opt_fresource_set_binding,opt_fcbuffer_binding_base,opt_fimage_binding_base,opt_fsampler_binding_base,opt_fssbo_binding_base,opt_ftexture_binding_base,opt_fuav_binding_base,opt_fubo_binding_base,opt_fshader_stage,opt_g,opt_h,opt_help,opt_I,opt_mfmt,opt_O,opt_Os,opt_O0,opt_o,opt_std,opt_S,opt_show_limits,opt_target_env,opt_target_spv,opt_version,opt_w

  template <typename opt>
  bool proc(int argc,char* argv[],int& i){opt h;
    std::string s=argv[i];
    if(h.check(s)){
        if(h.args){
            h.proc( argc, argv, i);
        }
        else {h.proc();}
        return true   
    }
    else return false;
)}
  template <typename opt,typename... opts>
  bool proc(int argc,char* argv[],int& i){
    opt h ;
    std::string s = argv[i];
    if(h.check(s)){
        if constexpr (h.args){h.proc( argc, argv, i);}
        else {h.proc();}
        return true   
    }
    else {proc<opts>(argc,argv,i);}
}

void main(int argc, char* argv[] ){std::string s;
    for(int i=0;i<argc;i++ ){    
        if(!proc<OPTS_MACROS>(argc,argv,i)){
            s=argv[i];
        }    
    }

    std::filesystem::path pth(s);
    if(std::filesystem::path::is_absolute(pth)){
        gcwd = pth.parent_path();
        rootFile=pth;
    }
    else {
        std::filesystem::path CWD = get_CWD() ;
        if(std::filesystem::is_relative(pth)){
            std::filesystem::path pCWD = CWD;
            CWD/=pth.parent_path();
            gcwd=CWD;
            pCWD/=pth;
            rootFile = pCWD; 
        }
     }
    
     emit(pth);

}