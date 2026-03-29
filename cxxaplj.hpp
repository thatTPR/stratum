#include <cstddef>
#include <type_traits>
/*
    arrexpr operator<<(T& arg);
    arrexpr operator>>(T& arg);
    arrexpr operator<(T& arg);
    arrexpr operator>(T& arg);
    arrexpr operator<=(T& arg);
    arrexpr operator>=(T& arg);
    arrexpr operator--(T& arg);
    arrexpr operator++(T& arg);
    arrexpr operator-=(T& arg);
    arrexpr operator=+(T& arg);
    arrexpr operator=-(T& arg);
    arrexpr operator=+(T& arg);
    arrexpr operator+(T& arg);
    arrexpr operator-(T& arg);
    arrexpr operator/(T& arg);
    arrexpr operator*(T& arg);
    arrexpr operator->(T& arg);
    arrexpr operator[](T& arg);
    arrexpr operator()(T& arg);
*/


// Digraphs
class digraph {
    
};
class arrexpr {
    enum type {
        Monadic=0,
        Dyadic=1
    };

    size_t exprvec_size;
    arrexpr* exprvec;

    template <typename T>
    arrexpr operator<<(T arg){

    };
    template <typename T>
    arrexpr operator>>(T& arg);
    template <typename T>
    arrexpr operator<(T& arg);
    template <typename T>
    arrexpr operator>(T& arg);
    template <typename T>
    arrexpr operator<=(T& arg);
    template <typename T>
    arrexpr operator>=(T& arg);
    template <typename T>
    arrexpr operator--(T& arg);
    template <typename T>
    arrexpr operator++(T& arg);
    template <typename T>
    arrexpr operator-=(T& arg);
    template <typename T>
    arrexpr operator=+(T& arg);
    template <typename T>
    arrexpr operator=-(T& arg);
    template <typename T>
    arrexpr operator=+(T& arg);
    template <typename T>
    arrexpr operator+(T& arg);
    template <typename T>
    arrexpr operator-(T& arg);
    template <typename T>
    arrexpr operator/(T& arg);
    template <typename T>
    arrexpr operator*(T& arg);
    template <typename T>
    arrexpr operator->(T& arg);
    template <typename T>
    arrexpr operator[](T& arg);
    template <typename T>
    arrexpr operator()(T& arg);


    constexpr void eval() {

    };
};

class M{
    template <typename T>
    arrexpr type(T& arg){
        if constexpr(std::is_integral<T>::value){

        }
        else {

        };
        if constexpr(std::is_array<T,>::value){

        };
        else {
            if constexpr(std::<>)
        };
    };
    template <typename T>
    arrexrp operator<<(T& arg){
    } ;
    template <typename T>
    arrexrp operator>>();
    template <typename T>
    arrexrp operator<();
    template <typename T>
    arrexrp operator>();
    template <typename T>
    arrexrp operator<=();
    template <typename T>
    arrexrp operator>=();
    
    template <typename T>
    arrexrp operator--();
    template <typename T>
    arrexrp operator++();
    
    template <typename T>
    arrexrp operator-=();
    template <typename T>
    arrexrp operator+=();
    
    
    template <typename T>
    arrexrp operator=-();
    template <typename T>
    arrexrp operator=+();

    template <typename T>
    arrexrp operator+()
    template <typename T>
    arrexrp operator-()
    template <typename T>
    arrexrp operator/()
    template <typename T>
    arrexrp operator*()
    operator->()


    arrexpr operator()(arrexpr expr ){

    };
    arrexpr operator[](arrexpr expr ){

    };
    
} ; 
class D {

} ;