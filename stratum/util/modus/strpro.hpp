// str
#include <array>
#include <fstream>
#include <string>
#include <variant>
using namespace std ;

// This either returns an ast  or something else 
namespace strpro {
    class type  {
        
            typedef enum types {
                t_double, 
                t_integer,
                t_str,
                t_ch,
                t_boolean,
                t_obj,
                
            }types ;
        
        types match_double(std::string s){

        };
        types match_string(std::string s) {

        };

        types match_(std::string s)
        virtual types match(std::string& s ){
            
        };

    };

    // Used to be able to parse specific operations and expressions eg: 
    // CTRL+K shortcut. We define  a input class object  with the function input operator+()
    class lex { 
        type t;
       

        typedef type operator+(type& lhs , type& rhs)
        virtual type operator+(type& lhs , type& rhs){};
        virtual type operator-(type& lhs , type& rhs){};
        virtual type operator|(type& lhs , type& rhs){};
        virtual type operator/(type& lhs , type& rhs){};
        virtual type operator*(type& lhs , type& rhs){};
        virtual type operator&(type& lhs , type& rhs){};
        virtual type map(char c , std::string lhs , std::string rhs ){
            switch c {
                case "+" : {
                    
                }
            };
        }

    };
    struct ast {
        char key ;
        ast l; // May be null
        ast r ; // May be null 
    };
    
    class strpro {
    
        std::array<char> keychars ; // Returns as expr ; // In order of operations
        std::array<matcher> matchers ;  // to match strings after expr parsing ; 
        std::array 
        std::array<> clear; 

        virtual ast line(std::string s) ; 
        
        };
        std::string file(std::path file){
            std::ifstream f ;
            f.open(file) ;
            std::string s;
            std::string out ; 
            while(f >> s){
                out += "\n" this->line(s)  ;
            };

        } ;

        strpo(std::array<char> formatChars , std::array<char> keychars, std::variant<>);

    };

    class strproAST {

    };

};