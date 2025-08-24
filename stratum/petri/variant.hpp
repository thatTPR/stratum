#ifndef PTR_VARIANT
#define PTR_VARIANT
#include <cstddef>
#include <type_traits>
namespace ptr {

template <typename T,typename... Ts>
struct variant {
    using ty = T;
    using varl = std::conditional<sizeof...(Ts)>1 ,variant<Ts...> ,varhelp<Ts>> ;
    union {
        T first;
        variant<Ts...> tail;
    } d ;
};

template <typename T>
struct variant<T> {
    T tail;
}
template <typename Head, typename... Tail>
size_t variant_size(variant<Head,Tail...>& t){
    variant<Tail...> r;
    return 1 + variant_size<Tail...>(r);
}

template <typename Head, typename Tail>
size_t variant_size(variant<Head,Tail>& t){
    return 2;
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

template <typename T,typename A,typename... S>
T& get(variant<S...>& v){
    if constexpr (std::is_same<T,typename variant<A,S...>::ty>::value){return v.first;}
    return get<T,S>(v.tail);
};


template <typename T,typename A>
T& get(T& v){
    static_assert(std::is_same<T,A>::value,"type not found in variant");
    return v;
    
};
}
#endif