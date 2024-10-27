// Binary file format representing strata project strucutre
// Defines plugin dependencies ( and the specific modules )
// Defines local module dependencies
// Assets and atlases
// Scene Files
// Canvases
// 
#include <string>
#include "../util/syscanvas.cpp"
struct sproj {
    std::vector<std::string> plugins;
    std::vector<levels> levels ;
    std::vector<canvas> canvases ;
    std::vector<>
};

class sprojParser {

};

class project {
    std::string path; // Name should be the same
    sproj proj;   
}