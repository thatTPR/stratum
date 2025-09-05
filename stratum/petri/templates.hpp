#ifndef PTR_TEMPLATES
#define PTR_TEMPLATES
#include <type_traits>
#include <stratum/petri/tuple.hpp>
template <typename T,typename...Ts>
constexpr size_t sizeOf(){return sizeof(T)+sizeOf<Ts...>();}
template <typename T>
constexpr size_t sizeOf(){return sizeof(T);}


namespace pri {

    template < template <size_t > typename T,size_t s>
struct Tcase {
    static bool operator()(size_t is){
        if(is==s){T<is>();return true;}
        else {Tcase<T,sS...>()}
    };
};


template < template <size_t > typename T>
struct Tcase {
    static bool operator()(size_t is){
        if(is==s){T<is>();return true;}
        else {return false;}
    };
};




    template <typename T, typename A , typename... Ts>
    struct is_one_of {
        static  constexpr bool value = std::is_same<T,A>::value || is_one_of<T,Ts...>::value ; 
    };
    template <typename T ,template <typename As,typename... Tss>typename Template,typename A,typename...Ts>
    constexpr bool is_one_of(Template <A,Ts...> r){return is_one_of<T,A,Ts...>::value;};

    
    template <typename T, typename A>
    struct is_one_of<T,A> {
        static  constexpr bool value = std::is_same<T,A>::value; 
    };
    template <typename T, T val, T vone,T... vals> 
    struct eqs_one_of{
        static constexpr bool value = (val == vone) || eqs_one_of<T,val,vals...>::value ;
    };
    template <typename T, T val, T vone> 
    struct eqs_one_of<T,val,vone>{
        static constexpr bool value = (val == vone) ;
    };

    template <typename T, T val, T vone,T... vals> 
    struct eqs_all_of{
        static constexpr bool value = (val == vone) && eqs_one_of<T,val,vals...>::value ;
    };
    template <typename T, T val, T vone> 
    struct eqs_all_of<T,val,vone>{
        static constexpr bool value = (val == vone) ;
    };
    

    // template <typename... S>
    // using cases_type = pri::tuple<S...> ; 
    // template <typename casesTy ,casesTy val,bool Bool,bool... Booleans>
    // struct sw_type {
    //     casesTy valueTy = v ;

    // };
}
#endif