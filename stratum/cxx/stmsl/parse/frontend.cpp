#include <filesystem>
#include <limits.h>
#ifdef _WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif
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
                    Otherwise the default is glsl.";

// cliopts

#include <string>

template <bool takesArgs>
struct opt {
    static constexpr args = takesArgs;
    const std::string n ; 
    std::string val;
    bool check(std::string s){
        size_t p = s.find(n);
        if(s.find(n)!=std::string::npos){
            val = s.substr(sizeof(n));
            return true;}
    };
     void proc(int argc,char* argv[],int& i);
     void proc();
}
#define OPTS_MACROS

#define OPTS_N(name,nname,bflag) struct name : opt<bflag> {const std::string n = nname;} ;\
#define OPTS_MACROS OPTS_MACROS , name


OPTS_N(opt_CPH,"-CPH",false)
void opt_CPH::proc(){stmsl::CPH=true;}
OPTS_N(opt_CPHU,"-CPHU",false)
void opt_CPHU::proc(){stmsl::CPHU=true;}
OPTS_N(opt_c ,"-c",false)
void opt_c::proc(){stmsl::preprocAndCompileOnly=true;}
OPTS_N(opt_D ,"-D",false)
void opt_D::proc(){
    size_t pos= this->val.find("=");
    if(pos!=std::string::npos){
        std::string n=val.substr(0,pos);
        std::string v = val.substr(pos+1);
        stmsl::macros.push(macro(n,v));
    }
    else {stmsl::macros.push(macro(val,std::string()));}    
}
OPTS_N(opt_E,"-E",false)
void opt_E::proc(){stmsl::preprocOnly=true;}
OPTS_N(opt_fauto_bind_uniforms,"-fauto-bind-uniforms",false)
void opt_fauto_bind_uniforms::proc(){stmsl::fauto_bind_uniforms=true;}
OPTS_N(opt_fauto_map_locations,"-fauto-map-locations",false)
void opt_fauto_map_locations::proc(){stmsl::fauto_map_locations=true;}
OPTS_N(opt_fauto_combined_image_sampler,"-fauto-combined-image-sampler",false)
void opt_fauto_combined_image_sampler::proc(){stmsl::fauto_combined_image_sampler=true;}
OPTS_N(opt_fentry_point,"-fentry-point",true) 
void opt_fentry_point::proc(int argc,char* argv[],int& i){
    stmsl::entry_pt = this->value;   
}  

OPTS_N(opt_fhlsl_16bit_types,  "-fhlsl-16bit-types",false)
void opt_fhlsl_16bit_types::proc(){stmsl::opt_fhlsl_16bit_types=true;}
OPTS_N(opt_fhlsl_functionality1,"-fhlsl_functionality1",false)
void opt_fhlsl_functionality1::proc(){stmsl::opt_fhlsl_functionality1=true;}
OPTS_N(opt_fhlsl_iomap,"-fhlsl-iomap",false)
void opt_fhlsl_iomap::proc(){stmsl::fhlsl_iomap=true;}
OPTS_N(opt_fhlsl_offsets,"-fhlsl-offsets",false)
void opt_fhlsl_offsets::proc(){stmsl::fhlsl_offsets=true;}
OPTS_N(opt_finvert_y,"-finvert-y",false)
void opt_finvert_y::proc(){stmsl::finvert_y=true;}
OPTS_N(opt_flimit,"-flimit",true) 
void opt_flimit::proc(int argc,char* argv[],int& i){}//TODO



//   "-flimit-file"
OPTS_N(opt_fnan_clamp,"-fnan-clamp",false)
void opt_fnan_clamp::proc(){stmsl::fnan_clamp=true;}
OPTS_N(opt_fpreserve_bindings,"-fpreserve-bindings",false)
void opt_fpreserve_bindings::proc(){stmsl::fpreserve_bindings=true;}

// TODO
OPTS_N(opt_fresource_set_binding,"-fresource-set-binding",false)
void opt_fresource_set_binding::proc(){stmsl::fresource_set_binding=true;}
OPTS_N(opt_fcbuffer_binding_base,"-fcbuffer-binding-base",false)
void opt_fcbuffer_binding_base::proc(){stmsl::fcbuffer_binding_base=true;}
OPTS_N(opt_fimage_binding_base,"-fimage-binding-base",false)
void opt_fimage_binding_base::proc(){stmsl::fimage_binding_base=true;}
OPTS_N(opt_fsampler_binding_base,"-fsampler-binding-base",false)
void opt_fsampler_binding_base::proc(){stmsl::fsampler_binding_base=true;}
OPTS_N(opt_fssbo_binding_base,"-fssbo-binding-base",false)
void opt_fssbo_binding_base::proc(){stmsl::fssbo_binding_base=true;}
OPTS_N(opt_ftexture_binding_base,"-ftexture-binding-base",false)
void opt_ftexture_binding_base::proc(){stmsl::ftexture_binding_base=true;}
OPTS_N(opt_fuav_binding_base,"-fuav-binding-base",false)
void opt_fuav_binding_base::proc(){stmsl::fuav_binding_base=true;}
OPTS_N(opt_fubo_binding_base,"-fubo-binding-base",false)
void opt_fubo_binding_base::proc(){stmsl::fubo_binding_base=true;}
  
OPTS_N(opt_fshader_stage,"-fshader-stage",false)
void opt_fshader_stage::proc(){stmsl::fshader_stage=this->val;}
OPTS_N(opt_g,"-g",false)
void opt_g::proc(){stmsl::debug=true;}
OPTS_N(opt_h,"-h",false)
void opt_h::proc(){std::cout<<help_strng;}
OPTS_N(opt_help,"--help",false)
void opt_help::proc(){std::cout<<help_strng;}
OPTS_N(opt_I,"-I",false)
void opt_I::proc(){stmsl::dirs.push(this->val);}
OPTS_N(opt_mfmt,"-mfmt",false)
void opt_mfmt::proc(){stmsl::mfmt=this->val;}

// OPTS_N(opt_MD,"-MD",true) 
// void opt_MD::proc(){generate_make_deps=true;}
// OPTS_N(opt_MF,"-MD",true) 
// void opt_MF::proc(){generate_make_deps=true;}

// "-MF"
// "-MT"
// OPTS_N(opt_M,"-M",true) 
// void opt_M::proc(){generate_make_deps=true;preprocOnly=true;}
OPTS_N(opt_O,"-O",false)
void opt_O::proc(){stmsl::optimize=true;}
OPTS_N(opt_Os,"-O",false)
void opt_Os::proc(){stmsl::optimizeSize=true;}
OPTS_N(opt_O0,"-O0",false)
void opt_O0::proc(){stmsl::optimizeSize=false;stmsl::optimize=false;}
OPTS_N(opt_o,"-o",false)
void opt_O0::proc(){i++;stmsl::outfile=argv[i];}
OPTS_N(opt_std,"-std",false)
void opt_std::proc(){stmsl::stdv=this->val;}
OPTS_N(opt_S,"-S",false)
void opt_S::proc(){stmsl::emitSPVasm=true;}
OPTS_N(opt_show_limits,"--show-limits",false)
void opt_show_limits::proc(){stmsl::lims.print();}
OPTS_N(opt_target_env,"--target-env",false)
void opt_target_env::proc(){stmsl::target_env=this->val;}
OPTS_N(opt_target_spv,"--target-env",false)
void opt_target_spv::proc(){stmsl::target_spv=this->val;}
OPTS_N(opt_version,"--version",false)
void opt_version::proc(){std::cout<<"version: 1.0";}
OPTS_N(opt_w,"-w",false)
void opt_w::proc(){stmsl::supressWarnings=true;}

OPTS_N(opt_Werror,"-Werror",false)
void opt_Werror::proc(){stmsl::Werror=true;}
OPTS_N(opt_W_fatal_errors,"-Wfatal-errors",false)
void opt_Werror::proc(){stmsl::Wfatal_error=true;}

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