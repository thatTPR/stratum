#include "../sys_graph.hpp"

namespace graph {

    
    // template <glm::length_t C, glm::length_t R, typename T , glm::qualifier Q>
    // class dataPinbase {
    //     private:
    //     const std::string name ; 
    //     bool c_bool = C==1 ;
    //     bool r = R==1 ;
    //     public: 
    //     std::string data = NULL; // In case of logical expression()
    //     using type = typename std::conditional<C==1 , glm::vec<R,T,Q>,  glm::mat<C,R,T,Q>   >  ;
    //     execPin* exec ;
    //     std::vector< type> vec ;
    //     dataPin(const std::string& Name) : name(Name) {};
    //     dataPin(const std::string& Name, const std::string& Data ) : name(Name), data(Data) {};
    //     dataPin(const std::string& Name, const std::string& Data , vector<type>& Vec  ) : name(Name), data(Data), vec(Vec) {};
    //     dataPin() = default;
    // };
    
    // // Derived class that uses the common base implementation
    // template <glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
    // class dataPin : public dataPinBase<C, R, T, Q> {
    // public:
    //     using dataPinBase<C, R, T, Q>::dataPinBase;  
    // };

    // // Partial specialization for `C = 1`, reuses the base class
    // template <glm::length_t S, typename T, glm::qualifier Q>
    // class dataPin<1, S, T, Q> : public dataPinBase<1, S, T, Q> {
    // public:
    //     using dataPinBase<1, S, T, Q>::dataPinBase; 
    };
    
    class static_image : Snode {

    };
    class dynamic_image {

    };
};