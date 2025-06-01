// xml file format representing strata project strucutre
// Defines plugin dependencies ( and the specific modules )
// Defines local module dependencies
// Assets and atlases
// Scene Files
// Canvases
// 
#include <string>
#include <xml.cpp>
#include "../util/syscanvas.cpp"


namespace StmProject {
    class plugin {
        enum type {
            Shared ,
            Script
        };
        type t ;
        std::string codePath ;
        std::string configJson;
        void parse(){
            xmlParser p = p.parse()
        };
        void init(std::string config){
            
        };     
    };



    template <typename T>
    class element {
        std::string uri ;// MayBe filePath
    static auto getter;
    T data;
    virtual get(){
        
    }
};
class lib {
    std::string name ;

};
struct StmProj {
    

    std::vector<plugin> plugins;  
    std::vector<asset> assets ; 
    std::vector<lib> libs ;
    StmProj(std::string path){
        
    };
};

class sprojParser {

};

class project {
    std::string path; // Name should be the same
    sproj proj;   
};
};