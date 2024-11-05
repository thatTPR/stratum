
#include <istream>
#include <string>
std::basic_string std::iostream::operator[](size_t pos, size_t size){
    this->seekg(pos);
    return this->get(size);
};

std::basic_string std::iostream::operator[](size_t off, std::istream::seekdir dir , size_t size){
    this.seekg(off,dir);
    return this->get(size);
};

std::basic_string& std::string::operator[](size_t pos,size_t off){

};
std::basic_string* std::string::operator[](size_t pos,size_t off){
    return this->copy(*t,pos,off);
};
