#include "../sys.hpp"
namespace node {
    class field {
        virtual glm::vec4 color;
        virtual std::string name ;
        virtual void value ;
    };
    class node {
        virtual glm::vec4 color;
        virtual std::string name ;
        
        virtual std::vector<field*> ins ;
        virtual std::vector<field*> outs ;  
    };
    class event_node {
        virtual glm::vec4 color;
        virtual std::string name ;
        
        virtual field* eventIn ; 
        virtual field eventOut; 
        virtual std::vector<field*> ins
        virtual std::vector<field*> outs ;
    };
    
    class graph {
        std::vector<field> fields ;
        std::vector<std::pair<node, glm::vec2 > > nodes;
    };
    

}

