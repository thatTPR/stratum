#pragma once

#include <system>
#include <filesystem>
#include <sstream>
#include <vector>



#ifdef __ANDROID__
#define PLATFORM_ANDROID
#endif

#if defined(_WIN64)
#define PLATFORM_WINDOWS
#elif defined(_WIN32)
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#else
#error "Unsupported platform"
#endif

#ifdef PLATFORM_WINDOWS
#include <windows.h>
void appendVar(std::filesystem path, std::string var)
{
    // Get the current value of the environment variable
    size_t bufferSize = GetEnvironmentVariable(variableName, nullptr, 0);
    if (bufferSize == 0)
    {
        std::cerr << "Error getting environment variable." << std::endl;
        return 1;
    };
    char *currentValue = new char[bufferSize];
    GetEnvironmentVariable(var, currentValue, bufferSize);

    // Append the new path to the current value
    std::string newValue = currentValue + std::string(";") + path;

    if (!SetEnvironmentVariable(variableName, newValue.c_str()))
    {
        std::cerr << "Error setting environment variable." << std::endl;
        delete[] currentValue;
        return 1;
    };
};
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#include <cstdlib>

void appendVar(std::filesystem path, std::string var)
{

    char *currentValue;
    currentValue getenv(var);

    // Append the new path to the current value
    std::string newValue = currentValue + std::string(";") + path;

    system("export " + var + "=" + newValue);
}
#endif

void setPythonIncludeVariable(std::filesystem::path path){
    appendVar("PYTHONPATH", path)};
void setClangIncludeVariable(std::filesysytem::path path)
{
    appendVar("CPATH", path);
};
std:: : string getcHeaderInclude(std::array<std::string> paths)
{
    std::string str = "";
    for (auto const &i : paths)
    {
        str.append("-L " + *i + " ");
    };
}

std::string getcLibraryIncldues(std::array<std::string> IncludePaths, std::array<std::string> libraries)
{
    std::string str = "";
    for (auto const &i : IncludePaths)
    {
        str.append("-L " + *i + " ");
    };
    for (auto const &i : libraries)
    {
        str.append("-l " + *i + " ");
    };
    return str ;
};
// -sysroot


// TODO triple interface better and .lib on windows insure for fll
const triple_x86_linux_pc = "-target x86_64-pc-linux-gnu" ;
const triple_android = "-target arm-linux-androideabi-21" ;
const triple_window = "-target x86_64-pc-windows-msvc" ; 
void stripExtension(std::string path){
    size_t lastDotPos = path.find_last_of('.');
        // Remove the extension by taking a substring up to the last dot
        return  path.substr(0, lastDotPos);
};

std::string getlibCompile(std::string path){
    return "llvm-lib "+path+" -o "+stripExtension(path)+".lib";
};


// CPU FPU ABI


//
std::string getSharedWin(std::string path ){
    std::string str = "";
    
    return "-shared -o "+stripExtension(path)+".dll"
};

std::string getSharedLin(std::string path  ){
    std::string str = "";
    
    return "-shared -o "+stripExtension(path)+".so "+path
};
std::vector<std::pair<std::string, std::string>> executeCommandAndSplit(const char* cmd) {
    std::vector<std::pair<std::string, std::string>> result;

    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        std::cerr << "Error opening pipe." << std::endl;
        return result;
    }


    std::string buffer;
   
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::istringstream lineStream(buffer);
        std::string arch, desc;
        lineStream >> arch >> std::ws;
        std::getline(lineStream, desc);
        result.emplace_back(arch, desc);
    };
    
    pclose(pipe);
    return result;
};

std::vector<std::pair<std::string, std::string>> getCxxTargets(){
        return executeCommandAndSplit("clang++ -print-targets");
};

std::vector<std::string> getVendors(){ // 
    // TODO filesystem 
};

#define DEBUG_FLAG "-g"
#define NO_OPTIM "-O0"
#define O1_OPTIM "-O1"
#define O2_OPTIM "-O2"
#define O3_OPTIM "-O3"
#define FAST_OPTIM "-Ofast"
#define SIZE_OPTIM "-Os"
#define SUPER_SIZE_OPTIM "-Oz"



#define DEFAULT_OPT O3_OPTIM
#define BEST_OPT FAST_OPTIM
/*
-O0 means "no optimization": this level compiles the fastest and generates the most debuggable code. It enable -mrelax-all option.
-O1 somewhere between -O0 and -O2.
-O2 moderate level of optimization which enables most optimizations.
-O3 is like -O2 except that it enables optimizations that take longer to perform or that may generate larger code (in an attempt to make the program run faster).
-Ofast enable -O3, with other aggressive optimizations that may violate strict compliance with language standards. It speedup math calculations.
-Os is like -O2 with extra optimizations to reduce code size.
-Oz is like -Os, but try to minimise even more the code size.
*/

// Need to track changees

/*This configuration contains symbols for debugging.
 *This configuration builds both engine and game code in debug configuration. It also
 */

std::string getCxxDebugAll(std::string ){
    return "clang++ "+DEBUG_FLAG+" "+DEFAULT_OPT+
};
std::string getCxxDebugGame();
std::string getCxxDevelop();
std::string getCxxTesting();
std::string getCxxRel();



// General Cross-Compilation Options in Clang
// Target Triple
// The basic option is to define the target architecture. For that, use -target <triple>. If you don’t specify the target, CPU names won’t match (since Clang assumes the host triple), and the compilation will go ahead, creating code for the host platform, which will break later on when assembling or linking.

// The triple has the general format <arch><sub>-<vendor>-<sys>-<env>, where:
// arch = x86_64, i386, arm, thumb, mips, etc.

// sub = for ex. on ARM: v5, v6m, v7a, v7m, etc.

// vendor = pc, apple, nvidia, ibm, etc.

// sys = none, linux, win32, darwin, cuda, etc.

// env = eabi, gnu, android, macho, elf, etc.

// The sub-architecture options are available for their own architectures, of course, so “x86v7a” doesn’t make sense. The vendor needs to be specified only if there’s a relevant change, for instance between PC and Apple. Most of the time it can be omitted (and Unknown) will be assumed, which sets the defaults for the specified architecture. The system name is generally the OS (linux, darwin), but could be special like the bare-metal “none”.

// When a parameter is not important, it can be omitted, or you can choose unknown and the defaults will be used. If you choose a parameter that Clang doesn’t know, like blerg, it’ll ignore and assume unknown, which is not always desired, so be careful.

// Finally, the env (environment) option is something that will pick default CPU/FPU, define the specific behaviour of your code (PCS, extensions), and also choose the correct library calls, etc.

// CPU, FPU, ABI
// Once your target is specified, it’s time to pick the hardware you’ll be compiling to. For every architecture, a default set of CPU/FPU/ABI will be chosen, so you’ll almost always have to change it via flags.

// Typical flags include:
// -mcpu=<cpu-name>, like x86-64, swift, cortex-a15

// -mfpu=<fpu-name>, like SSE3, NEON, controlling the FP unit available

// -mfloat-abi=<fabi>, like soft, hard, controlling which registers to use for floating-point

// The default is normally the common denominator, so that Clang doesn’t generate code that breaks. But that also means you won’t get the best code for your specific hardware, which may mean orders of magnitude slower than you expect.

// For example, if your target is arm-none-eabi, the default CPU will be arm7tdmi using soft float, which is extremely slow on modern cores, whereas if your triple is armv7a-none-eabi, it’ll be Cortex-A8 with NEON, but still using soft-float, which is much better, but still not great.

// Toolchain Options
// There are three main options to control access to your cross-compiler: --sysroot, -I, and -L. The two last ones are well known, but they’re particularly important for additional libraries and headers that are specific to your target.

// There are two main ways to have a cross-compiler:

// When you have extracted your cross-compiler from a zip file into a directory, you have to use --sysroot=<path>. The path is the root directory where you have unpacked your file, and Clang will look for the directories bin, lib, include in there.

// In this case, your setup should be pretty much done (if no additional headers or libraries are needed), as Clang will find all binaries it needs (assembler, linker, etc) in there.

// When you have installed via a package manager (modern Linux distributions have cross-compiler packages available), make sure the target triple you set is also the prefix of your cross-compiler toolchain.

// In this case, Clang will find the other binaries (assembler, linker), but not always where the target headers and libraries are. People add system-specific clues to Clang often, but as things change, it’s more likely that it won’t find than the other way around.

// So, here, you’ll be a lot safer if you specify the include/library directories manually (via -I and -L).

// Target-Specific Libraries


namespace platform
{

    enum ShaderTarget
    {
        wgsl = 0b00,
        spv = 0b01,

    };
    enum ShadersSource
    {
        hlsl = 0,
        glsl = 1,
        wgsl = 2,
        sshl = 3, // Strata shading language l  // TODO
    };

    namespace cxx
    {
        enum cxxArch
        {
            x86_64,
            i386,
            arm,
            thumb,
            mips
        };
        std::map<std::string, cxxArch> str_arch = {
            {"x86_64", cxxArch.x86_64},
            {"i386", cxxArch.i386},
            {""},
            {},
            {},

        };

        enum cxxVendor
        {
            pc,
            apple,
            nvidia,
            ibm
        };
        enum cxxSys
        {
            none,
            linux,
            win32,
            darwin,
            cuda
        };
        enum cxxEnv
        {
            eabi,
            gnu,
            andorid,
            macho,
            elf
        };
        class config
        {
            cxxArch arch;
            cxxVendor vendor;
            cxxSys sys;
            cxxEnv env;
            cxx
        };

