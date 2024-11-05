#include <string>


class xml_type {
    string,
    name,
};


template <typename stream>
class xml_parser {

        
    void virtual start_tag(pos);
    void virtual end_tag();
    void virtual open_tag();
    void virtual close_tag()
    
    xml_parse();        
};