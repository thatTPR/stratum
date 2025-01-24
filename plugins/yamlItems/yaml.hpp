#include <string>
#include <map>
#include <vector>
namespace yaml {
    struct value {
        typedef std::map<std::string,value> obj;
        typedef std::vector<value> list;
        typedef int Int;
        typedef float Float;
        std::string name;

        template <typename T>
        T Get();

        obj Get<obj>(){return this->o;};
        Int Get<Int>(){return this->numInt;};
        Float Get<Float>(return this->numFloat;);
        std::string Get<std::string>(){return this->str};
    };
    struct loader {
        void fromString(std::string str){

        };

        void fromFile(std::string path){
            if(str.find_str("[", pos);); // List
            if(str.find_str(":")) decl;
            if(list_open < )
            if(str.find_str("&", pos);); // anchor
            if(str.find_str("*", pos);); // Ref to anchor
            if(str.find_str(">", pos);); // Wrapped text
            if(str.find_str("|", pos);); // NewLines text
            if(str.find_str("!!" , pos)){
                if(str.find_str("binary"))
                if(str.find_str("float"))
                if(str.find_str("int"))
                if(str.find_str("str"))
            };// Explicit type
            
        };
    };  
};