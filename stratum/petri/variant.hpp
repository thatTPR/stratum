#ifndef PTR_VARIANT
#define PTR_VARIANT
#include "templates.hpp"
#include <cstddef>
#include <type_traits>
#include <typeinfo>
namespace pri {

struct emptyVariant {
    using head = emptyVariant;
    using tail = emptyVariant;
};

template <typename T,typename... Ts>
struct variant {
    using head = T;
    using tail = variant<Ts...>  ;
    union {
        head first;
        tail rest;
    };
    variant () {};
};

template <typename T>
struct variant<T> {
    using head = T;
    using tail = emptyVariant  ;
    head first;
        variant () {} ;

};
template <typename Head, typename... Tail>
size_t variant_size(variant<Head,Tail...>& t){
    variant<Tail...> r;
    return 1 + variant_size<Tail...>(r);
}

template <typename Head, typename Tail>
size_t variant_size(variant<Head,Tail>& t){
    return 2;
}

template <typename Head>
size_t variant_size(variant<Head>& t){
    return 1;
}


template <typename tupt>
constexpr size_t variant_size(){
    tupt g;
    return variant_size(g);
}

template <typename Head, typename... Tail>
Head& get(std::integral_constant<size_t, 0>, variant<Head, Tail...>& t) {
    return t.first;
}

template < typename Head, typename... Tail>
auto& get(size_t N, variant<Head, Tail...>& t) {
    static_assert(N < sizeof...(Tail) + 1, "Index out of range");
    if(n==0){return t.first;}
    return get(N-1, t.rest);
}

// Recursive case: peel one element off
template <size_t N, typename Head, typename... Tail>
auto& get(std::integral_constant<size_t, N>, variant<Head, Tail...>& t) {
    static_assert(N < sizeof...(Tail) + 1, "Index out of range");
    return get(std::integral_constant<size_t, N - 1>{}, t.rest);
}

// User-friendly wrapper
template <size_t N, typename... Ts>
auto& get(variant<Ts...>& t) {
    return get(std::integral_constant<size_t, N>{}, t);
}

template <typename T,typename A>
[[nodiscard]] T& get(variant<A>& v) noexcept{
    if constexpr (std::is_same<T,typename variant<A>::head>::value){return v.first;}
    throw std::logic_error("No type of id:in variant" ) ;

};
template <typename T,typename A,typename... S>
T& get(variant<A,S...>& v){
    if constexpr (std::is_same<T,typename variant<A,S...>::head>::value){return v.first;}
    return get<T,S...>(v.rest);
};
template <typename T,typename A,typename... S>
T& gets(variant<A,S...>& v){
    static_assert(pri::is_one_of<T,A,S...>::value, "Index out of range");
    if constexpr (std::is_same<T,typename variant<A,S...>::head>::value){return v.first;}
    return get<T,S...>(v.rest);
};
template <typename T,typename Vart>
T& get(Vart& v){
    return gets<T>(v);
    
};



template <typename... Ts> 
struct variantvalue  {
    using varty = variant<Ts...>;
    variant<Ts...> var; 
    static constexpr size_t size = sizeof...(Ts) ;
    size_t cur =0;
    constexpr size_t getpos(){return cur;}
    variantvalue() {} ;
    // variantvalue(){} ;
};

template <typename T, typename A,typename... Ts >
T& getvt(variant<A,Ts...>& v,size_t& s ){
    if constexpr(std::is_same<T,A>::value){return v.first;}
    s++;
    return getvt<T,Ts...>(v.rest,s);
};
template <typename T, typename A >
T& getvt(variant<A>& v,size_t& s ){
    if constexpr(std::is_same<T,A>::value){return v.first;}
    else {throw std::logic_error("No type of id in variantvalue" );} ;
}

template <typename T, typename... Ts>
T& get(variantvalue<Ts...>& vt){
    size_t s=0;
    T& res =  getvt<T,Ts...>(vt.var, s) ;
    vt.cur = s;return res;
};



template <size_t s , typename... Ts>
auto& get(variantvalue<Ts...>& vt){
    vt.cur = s;
    return get<s>(vt.var) ; 
};



template <typename T,typename... Ts>
struct Pack_Enum {
    template <size_t h>
    struct get{using type =typename  std::conditional<h==0,T,Pack_Enum<Ts...>::get<h-1>::type>::type;}
    template <typename g,size_t ssin> 
    struct geten{static constexpr size_t result= std::is_same<g,T>::value?ssin:Pack_Enum<Ts...>::geten<g,ssin+1>::result ;}
};

template <typename T>
struct Pack_Enum {
    template <size_t h>
    struct get{using type =typename  std::conditional<h==0,T,void>::type;}
    template <typename g,size_t ssin> 
    struct geten{static constexpr size_t result= std::is_same<g,T>::value?ssin:NULL ;}
};

template <typename T,typename... Ts>
struct option {
    variant<T,Ts...> var;
    using _enumty = Pack_Enum<T,Ts...> ;
    template <typename TT,template <typename> typename FuncTy,typename... As> // requires hasOperator()
    void apply(){FuncTy<pri::get<TT>(var)>(As... args);}

    template <size_t h,template <typename> typename FuncTy,typename... As> // requires hasOperator()
    void applyEn(){FuncTy<pri::get<TT>(var)>(As... args);}

};

}
#endif