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
    
    template <typename stream_type>
    void r(stream_type& stream);
    template <typename stream_type>
    void w(stream_type& stream);
    
    void r(std::fstream& fstr);
    void w(std::fstream& fstr);
    xml r(std::string& str, size_t& pos){
    };
    void w(std::string& str, size_t& pos);
};
