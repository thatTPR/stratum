#include <cstdlib>
#include <ifstream>
using namespace std;
#include <filesytem>
#define fs std::filesystem
#include <cxx>
template <>
class make

class makeWin {
    std::string libdirname;
    virtual incDir();
    virtual libDir(); 
};

class makeAndroid {
    std::string libdirname="android";
    std::string incDir;
    std::string LibDir;
    std::string triple;
    std::string androidSysRootUser;
    std::string incDir(){return this->androidSysRootUser+"include"}
    std::string libDir(std::string triple){return this->androidSysRootUser+"lib/"+}

virtual bool build(project proj)
void createManifest();

virtual bool makeDebug(project proj , std::string options ){
    return makeAndroidProject( , proj.name, proj.capabilites);
    fs::path project_and = fs::path(proj.path+"/build/android/");
    fs::path project_b = fs::path(proj.path+"/build");
    bool projp = fs::exists(project_and);
    bool projand = fs::exists(project_b);
    fs::path existing ;
    if(projand){
        existiing = project_and;
    }
    else(projp){
    existing = project_b;
    };

};

};

class makeWindows {
    std::string libdirname="windows";
    
};
class makeLinux {

};
class makeWasm {

};
