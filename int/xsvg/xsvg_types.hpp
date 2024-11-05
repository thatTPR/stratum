// Char types
#include "svg_tags.hpp"
#include <regex>

class number {
    // [+-]?
};

class percentage {
   // Number % 
};

class angle {
// angle ::= number (~"deg" | ~"grad" | ~"rad")?

};
class time {
   // time s, or ms

};

class color {

};

// Binary types
template <typename T>
class _d_bin : _d {
    struct _d_prim_bin {
        using struct _d_prim_pt<T>:: ;

    };
    
    _d_bin match_parse(std::vector<char> , size_t& pos){

    }
};
