#include "../sys.hpp"
#include "../../sgui/strata/nodes_editor.hpp"
namespace node {
  
    class event: public node {
        virtual glm::vec4 color;
        virtual std::string name ;
        
        virtual field* eventIn ; 
        virtual field eventOut; 
        virtual std::vector<field*> ins
        virtual std::vector<field*> outs ;
        event()
    };
    
    class graph {
        std::vector<field> fields ;
        std::vector<std::pair<node, glm::vec2 > > nodes;
    };
    

}

