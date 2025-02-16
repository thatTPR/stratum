#include <ifstream>
#include <string>

strata::strct_info  reflect(struct) 

#define ptr_to_member(name , member) name->member
#define member(name , member) name.member
#define MEMBERFUNC( member) decltype(this->data.member)  ret##member(){return name.member;};\
#define MEMBERFUNCCALL(member) ret##member();



#define NODE(strctname,...) \
struct name : node { \
    strctname data ; \
    ONE(memberfunc,__VA_ARGS__)
};
 
#define NODE(name,align) \
void create_ssbo(){

};
void parse_line(std::string s){

};
void get_strct_file(std::string path, std::string name){
    ifstream in(path); size_t pos;
    std::vector<std::string> members;
    bool cond=true;std::string line;size_t pos;
    while(cond){
        in>>line;
        size_t pos = line.find(name);
        if(pos!=line.npos){
            
        };
    };
};

// Function here to take node and canvas json object and generate cpp from it

// take node and canvas and generate runtime node for it;
