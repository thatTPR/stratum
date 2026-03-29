#include <string>
#include <fstream>

enum json_types {
    json_string
    json_number , // i+.i+e[+-]iii
    json_boolean , 
    json_array,
    json_obj , 
    json_null,
};


class json_parser {
    

    void r(std::fstream& fstr);
    void w(std::fstream& fstr);
    void r(std::string& str, size_t& pos);
    void w(std::string& str, size_t& pos);

    json_parser(std::fstream& fstr) = default ;
    json_parser(std::string& str, size_t& pos) = default;

};