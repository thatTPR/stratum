
#ifndef PTR_TUPLE
#define PTR_TUPLE
#include <type_traits>
#include <utility>
namespace pri {

struct tupleEmpty {using headt = tupleEmpty;using tailtup = tupleEmpty;};  // base case

template <typename empty,typename Head,typename... Tail>
struct tupleAddBack {
        using headt = Head;
    using tailtup = tupleAddBack<empty,Tail...> ;
    headt first;
    tailtup rest;


    tupleAddBack() = default;
   
    tupleAddBack(const Head& h, const Tail&... t)
        : first(h), rest(t...) {}

}
template <typename empty,typename Head>
struct tupleAddBack {
    using headt = Head;
    using tailtip = empty;
    headt  first;
    tailtup rest;
}


template <typename Head,typename... Tail>
using tuple = tupleAddBack<tupleEmpty,Head,Tail...> ;



template <typename T,typename empty,typename Head , typename... Ts>
T& get(tupleAddBack<empty,Head,Ts...>& t){
    if constexpr(std::is_same<Head,T>::value){
        return t.first;
    }
    return get<T,empty,Ts...>(t.rest);
};

template <typename empty,typename Head, typename... Tail>
size_t tuple_size(tupleAddBack<empty,Head,Tail...>& t){
    tuple<Tail...> r;
    return 1 + tuple_size<empty,Tail...>(r);
}
template <typname empty,typename Head>
size_t tuple_size(tupleAddBack<empty,Head>& t){
    if constexpr (std::is_same<empty,tupleEmpty>::value){return 1;}
    else {return 1 + tuple_size(t.rest);}
};

template <typename empty,typename Head, typename Tail>
size_t tuple_size(tuple<empty,Head,Tail>& t){return 2;};

template <typename tupt>
constexpr size_t tuple_size(){    constexpr tupt g;return tuple_size(g);}

template <typename empty,typename Head, typename... Tail>
Head& get(std::integral_constant<size_t, 0>, tupleAddBack<empty,Head, Tail...>& t) {return t.first;}

// Recursive case: peel one element off
template <size_t N, typename Head, typename... Tail>
auto& get(std::integral_constant<size_t, N>, tupleAddBack<empty,Head, Tail...>& t) {
    static_assert(N < sizeof...(Tail) + 1, "Index out of range");
    return get(std::integral_constant<size_t, N - 1>{}, t.rest);}

// User-friendly wrapper
template <size_t N,typename empty, typename... Ts>
auto& get(tupleAddBack<empty,Ts...>& t) {return get(std::integral_constant<size_t, N>{}, t);}

template <typename empty, typename... Ts>
auto& get(size_t N,tupleAddBack<empty,Ts...>& t) {

    if(n==0){return t.first;}
    return get(N-1, t.rest);}

template <typename empty,typename Head, typename... Tail>
Head& getTail(std::integral_constant<size_t, 0>, tupleAddBack<empty,Head, Tail...>& t) {return t.rest;}

// Recursive case: peel one element off
template <size_t N,typename empty, typename Head, typename... Tail>
auto& getTail(std::integral_constant<size_t, N>, tupleAddBack<empty,Head, Tail...>& t) {
    static_assert(N < sizeof...(Tail) + 1, "Index out of range");
    return getTail(std::integral_constant<size_t, N - 1>{}, t.rest);}

// User-friendly wrapper
template <size_t N,typename empty, typename... Ts>
auto& getTail(tupleAddBack<empty,Ts...>& t) {
    return getTail(std::integral_constant<size_t, N>{}, t);
}

template <typename T, typename tup>
struct addfronttup {
    using headt = T;
    using tailtup = tup;
    headt first;
    tailtup  rest;
      addFront() = default;
   
    addFront(const Head& h, const Tail&... t)
        : first(h), rest(t...) {}
};

template <typename tupBack,typename Head,typename... Tail>
using tupaddBack = tupleAddBack<tupBack,Head,Tail...>;


template <typename T,typename Head,typename... Tail>
struct tupConcat<T,tupleAddBack<tupleEmpty,Head,Tail> {
    using type = tupleAddBack<T,Head,Tail...>;
} ;

#include "templates.hpp" 



template <typename tupA,typename tupB,typename... tups>
struct tupConcats {
    using type = tupConcat<tupA,tupConcats<tupB,tups...>::type>::type  ;
} ;

template <typename tupA,typename tupB>
struct tupConcats {
    using type = tupConcat<tupA,tupB>::type  ;
} ;


template <typename T,typename Head,typename... Tail>
struct utupAddBack<T,tupleAddBack<tupleEmpty,Head,Tail...>> {
    constexpr bool isin = pri::is_one_of<T,Head,Tail...>::value
    using type = typename std::conditional<isin,tupleAddBack<tupleEmpty,Head,Tail...>,tupleAddBack<tuple<T>,Head,Tail...>::type;
};

template <typename tup,typename Head,typename... Tail>
struct utupConcat<tup,tupleAddBack<tupleEmpty,Head,Tail...> {
    using type = typename utupConcat<tup::tailt,typename utupAddBack<tup::headt,Head,Tail...>::type>::type
};


template <typename tup ,typename Head,typename... Tail>
struct utupConcat<tuple<T>,tupleAddBack<tupleEmpty,Head,Tail...> {
    using type = typename utupAddBack<tuple<T>,Head,Tail...>::type ;
};



template <typename tup,typename tupB,typename... tups>
struct utupConcats {
    using type = typename utupConcats<typename utupConcat<tup,tupB>::type , tups...>::type ;
};

template <typename tup,typename tupB>
struct utupConcats {
    using type = typename utupConcat<tup,tupB>::type ;
};

template <typename T , typename... Ts>
using utuple =  typename std::conditional<pri::is_one_of<T,Ts...>::value,tupleAddBack<utuple<Ts...>,T> , utuple<Ts...>>::type;

template <typename T,typename Head,typename... Ts>
constexpr size_t _get_size<>(){
    if constexpr (std::is_same<T,Head>::value){
        return 0;    
    }
    else {return 1 + get_size<T,Ts...>();}
};


template <typename T,typename Head>
constexpr size_t _get_size<>(){
    return 2;
};

template <typename T,typename utupty>
constexpr size_t get_size<>(){
    if constexpr (std::is_same<T,utupty::headt>::value){
        return 0;    
    }
    else {return 1 + get_size<T,utupty::tailtup>();}
};

template <typename T>
constexpr size_t get_size<T,tupleEmpty>(){
return 1;
};


template <template <typename T> typename Func ,typename Head,typename... Tail>
void applyAll(tupleAddBack<tupleEmpty,Head,Tail...>& s){
    func<Head>(s.first);
    applyAll<Func,Tail...>(s.rest);
};



template <typename tupBack,typename Head,typename... Tail>
tupleAddBack<tupBack,Head,Tail...> concat_tuples(tupleAddBack<tupleEmpty,Head,Tail...>& tup , tupBack& back){
    tupleAddBack<tupBack,Head,Tail...> set; 
    size_t s=0;
    for(;s<tuple_size<tuple<Head,Tail>();s++){
        get(s,set)= get(s,tup);  
    }
    size_t ss = s;
    for(;s-ss < tuple_size<tupBack>();s++){
        get(s,set) = get(s-ss,back); 
    }
    return set;
};
}


template <template <typename A>typename T, typname Head,typename... Tail>
void for_each_tup(tuple<Head,Tail>& r){
    T<tuple<Head,Tail>::headt>(r.first);
    for_each_tup<T,Tail...>(r.rest);
};
template <template <typename A>typename T, typname Head>
void for_each_tup<T,Head>(tuple<Head>& r){
    T<tuple<Head,Tail>::headt>(r.first);
};


#endif