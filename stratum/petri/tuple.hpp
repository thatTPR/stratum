
#ifndef PTR_TUPLE
#define PTR_TUPLE
#include <type_traits>
#include <utility>
namespace ptr {

struct tupleEmpty {};  // base case

// Recursive tuple
template <typename Head, typename... Tail>
struct tuple {
    Head first;
    tuple<Tail...> rest;

    // decltype(*this)& operator=(tuple<Head,Tail....>& rhs){
    //     first = rhs.first;
    //     rest=rhs.rest;
    // };
    // tuple<Head,Tail....>& operator==(tuple<Head,Tail....>& rhs){
    //     retrun first == rhs.first and ( rest==rhs.rest);
    // };
    
    tuple() = default;

    tuple(const Head& h, const Tail&... t)
        : first(h), rest(t...) {}
};

// Base case specialization
template <typename T>
struct tuple<T>{T first;};

// ---------------------- get implementation ----------------------

// Overload for index 0


template <typename Head, typename... Tail>
size_t tuple_size(tuple<Head,Tail...>& t){
    tuple<Tail...> r;
    return 1 + tuple_size<Tail...>(r);
}

template <typename Head, typename Tail>
size_t tuple_size(tuple<Head,Tail>& t){
    return 2;
}


template <typename tupt>
constexpr size_t tuple_size(){
    tupt g;
    return tuple_size(g);
}

template <typename Head, typename... Tail>
Head& get(std::integral_constant<size_t, 0>, tuple<Head, Tail...>& t) {
    return t.first;
}

// Recursive case: peel one element off
template <size_t N, typename Head, typename... Tail>
auto& get(std::integral_constant<size_t, N>, tuple<Head, Tail...>& t) {
    static_assert(N < sizeof...(Tail) + 1, "Index out of range");
    return get(std::integral_constant<size_t, N - 1>{}, t.rest);
}

// User-friendly wrapper
template <size_t N, typename... Ts>
auto& get(tuple<Ts...>& t) {
    return get(std::integral_constant<size_t, N>{}, t);
}


}
#endif