#ifndef STRATA_CXX
#define STRATA_CXX
#include <type_info>
#include <vector>
#include <string>
#include <filesystem>
#include <system>
#include <strata/command.cpp>
namespace cxx {
    bool comoutput = false;
    void syscom(std::string t){if(comoutput){strata::com<<t};
        system(t.c_str());
    };

typedef struct flag {
    std::string name;
    std::string val;

}flag;
struct cxxBuild {
    const std::string output ="o";
    const std::string Shared = "-shared";
    const std::string incDir = "-I";
    const std::string incLib ="-L";
    const std::string lib = "-l";
    const std::string opre = "-O";
    const std::string oPos1 = "1";
    const std::string oPos2 = "2";
    const std::string oPos3 = "3";
    const std::string oPosfast = "fast";
    const std::string optimPosSize = "s";
    const std::string optimPosSSize = "z";
    const std::string Debug = "-g" ;
    const std::string nostackex = "-Wl -z -noexecstack";
    
    const std::string wall = "-Wall"; //
    const std::string wfatal = "-Wfatal-errors";


    const std::string warndef = "-Wall -Wfatal-errors";
    const std::string no_strict_alias = "-fno-strict-aliasing"; // Hardens pointer casts 
    const std::string except= "-fexceptions";
    
    const std::string libr = "-c";
    // Random addressing

    const std::string pic = "-fPIC -shared"; // Position independent code
    const std::string pie = "-fPIE -pie" // Position independent executable 
    const std::string harddef = 
    const std::string compiler = "gcc";
    public:
    std::string outName; 
    bool library ;
    bool shared = false ;
    bool debug ;
    uint optim ; // 1-3 ;
    bool no_strict_alias;
    bool position_independent;

    std::string input ;
    std::vector<std::string> vflags;
    std::vector<flag> valflags  ;



    std::vector<std::string> incdirs;
    std::vector<std::string> libdirs ;
    std::vector<std::string> libs ; 
    std::vector<std::string> options ;
    std::string outname; 

    std::string outfolder;
    void clear(){this->options.clear();};
    void init(uint Optimize , bool debug, bool lib , bool shared = false   ){
        this->optim = Optimize;
        this->debug=debug;
        this->library = lib;
        this->shared = shared;
    };
    void input(){
            this->
    };
    void incs(){this->options = ;};
    void libs(){;};
    void optim();
    void options();
    void out();
    void opts(){
        
    };
    void comm(){
        std::string com ;
        com+= this->compiler + " " ;
        for(const auto s :this->incdirs){com+=this->incDir+s};
        for(const auto s :this->libdirs){com+=this->libDir+s};
        for(const auto s :this->libs){com+=this->lib+s};
        if(this->library){com+=this->libr;
        if(this->shared){com+=this->Shared;};};
        if{this->debug}{com+=this->Debug;};
        com++ this->out +" "+ this->outfolder+ this->outname;
        syscom(com);
    };
    cxxBuld(std::string outname,std::vector<std::string> incDirvec , std::vector<std::string> libDirvec,std::vector<std::string> libraries; uint sizeOptimize , bool debug, bool lib , bool shared ){
        this->outname = outname;
        this->options.clear();
        this->incdirs = indDirvec;
        this->libdirs = libDirvec;         
        this->libs = libraries;
        init(sizeOptimize , debug,lib,shared)
    };

    decltype(*this) construct_library(std::vector<std::string> libs, std::vector<>){
        decltype(*this)  res  =
    };
    // void make(std::vector<std::string> vFlags, std::vector<std::string> incDirs, std::vector<std::string> options)
    void make(){
        std::vector<std::string> options ; 

    }; 
    cxxBuild()
};
struct cxx_gcc : public cxxBuild {
    static const std::string compiler = "gcc";
    

};
struct cxx_clang : public cxxBuild {
    static const std::string compiler = "clang++";
};
struct cxx_msvc  {
    const std::string shared = "\\LD";
    const std::string incDir = "\\I";
    const std::string incLib ="\\L";
    const std::string lib = "\\l";
    const std::string opre = "\\O";
    const std::string oPos1 = "1";
    const std::string oPos2 = "2";
    const std::string oPos3 = "3";
    const std::string oPosfast = "t";
    const std::string optimPosSize = "s";
    const std::string optimPosSSize = "z";
    const std::string debug = "\\DEBUG" ;
    const std::string nostackex = "-Wl -z -noexecstack";

    static const std::string compiler = "msvc";
};

struct cxx_emcc : public cxxBuild {
    static const std::string compiler = "emcc";

};
std::string projectsDir;
std::string projectPath ; 

static const std::string projectFolder  ;
 buildSource()
// command dispatchers
template <typename builder >
struct CompileBuiler {
    using buildty = builder;
    buildty builder;
    std::string buildpath ;
    std::vector<std::string> flags;
    std::vector<std::string> modules ;  
    void make(std::string buildPath,std::vector<std::string> FLAGS,std::vector<std::string> modules){
    
    };
    CompilerBuilder(buildty b ,std::string buildPath,std::vector<std::string> flags  ) = default{

    } ;
};

struct android_compile : CompilerBuilder<cxx_clang>{
    std::string buildPath = "build/android/";   
}; 
 CompilerBuilder<cxx_msvc>  win_compile;
 CompierBuilder<cxx_emcc>  emcc_compile;
 CompilerBuilder<cxx_msvc>  linux_compile;

};
#endif