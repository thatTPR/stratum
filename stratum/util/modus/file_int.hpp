#include <array>
#include <vector>
#include <conditional>
#include <string>
#include <filesystem>
#include <fstream>
#include <boost_1_84_0/boost/serialization/access.hpp>
using namespace std ;
class parser {
    std::string ext ;
    std::map<std::string , parser > ext_to_dep ; 
    std::path filePath;
    void read() ;


    virtual void getNum();
    
    void parser final (std::path filePath , std::tuple<parser>  ){

    } ;
};

typedef struct index {
            size_t start ;
            size_t end ; 
            index* 
            uint pos ;  // Position in table ; Which element it is ;
}index;   

template<typename T>
concept arr_vec = std::is_same_v<T, std::array> || std::is_same_v<T, std::vector>;

class someIndex {
    public :
    virtual size_t start ;
    virtual size_t end ;
    virtual uint pos ;
} 

class staticIndex : someIndex {
    public:
    

    size_t start ;
    size_t end ;
    uint pos ;
    std::array<index , size_t > indexes ; // Indexes containes withing this range


    virtual size_t size ;
    virtual size_t size();
    virtual size_t max_size();
    virtual void emplace();
    virtual void 
    staticIndex();

};

class dynIndex : someIndex {
    public:
    size_t start ;
    size_t end ;
    uint pos ;
    std::vector<index> indexes ;
    add();
    insert();
    emplace();
    dynIndex();
}