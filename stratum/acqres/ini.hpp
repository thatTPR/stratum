
#include <fstream>
#include <string>
#include <cstddef>
#include <map>

std::string strip(std::string s){
    std::string res;
    for(const auto& i : s){
        if(i = ' '){continue;}
        res = res+ i; 
    };
    return res;
};
class ini {
    public:
    class section {
        public:
        std::string name ;
        std::map<std::string,std::string> entries ;
    };
    std::vector<section> data ;
    void load(std::string path){
        std::ifstream f(path);
        std::string c; 
        while(getline(f,c)){
            if(c[0] == '['){
                this->data.push_back(new section) ;
                size_t pos = c.find(']');
                std::string substr = c.substr(1,pos-2);
                this->data.end().name = substr ;  
            }
            else {
                size_t eq = c.find('=')
                std::string key = c.substr(0,eq);
                std::string val = c.substr(eq+1,c.size()-(eq+1));
                key= strip(key) ; val = strip(val) ;
                this->data.end().entries[key] = val ;
            }
        };
        f.close();
    };
    void write(std::string path){
        ofstream f(path) ;
        for(const auto& it : this->data){
            std::string section = "["+it.name+"]";
            f<<section<<std::endl;
            for(const auto& [key,val] : it.entries) {
                f<<key<<"="<<val<<std::endl;
            };
        };
        f.close() ;
    };
};