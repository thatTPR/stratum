
#ifndef PTR_TUPLE
#define PTR_TUPLE
#include <type_traits>
#include <utility>
namespace ptr {

struct tupleEmpty {using headt = void;};  // base case

// Recursive tuple
template <typename Head, typename... Tail>
struct tuple : tupleEmpty{

    using headt = Head;
    using tailtup = tuple<Tail...> ;

    template <typename Head_,typename... Tail_>
    using conc = tuple<Head,Tail...,Head_,Tail...>;
    headt first;
    tailtup rest;


    tuple() = default;
   
    tuple(const Head& h, const Tail&... t)
        : first(h), rest(t...) {}
};

// Base case specialization
template <typename T>
struct tuple<T>{
    using tailtup = tupleEmpty;
    using headt = T;
    T first;};




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


// TODO nesteds gener
template <typname TupA,typename... Tups>
struct nestedTup : tuple<tupA,Tups...>{
    using tuple<tupA,Tups...>::
};




template <size_t s, typename tupT>
struct tupGet {
    using head = std::conditional<s==0,typename tupT::headt,tupGet<s-1,typename tupT::tailtup>::type>::type;
    using tail = std::conditional<s==0,typename tupT::tailtup,tupGet<s-1,typename tupT::tailtup>::type>::type;
    using trueVal = std::conditional<s==0 , true_type , false_type >::type; 
}




template <size_t s,typename TupA,typename TupB>
struct tupconc {
    using head =  typename tupA::conc<tupGet<s,TupB>::head> ;
    using type = std::conditional<s==tuple_size<TupB>()-1,head,
    typename tupconc<s+1,head,tupGet<s+1,TupB>::head>::type>::type ;
};



template <size_t s,typename nestedTup>
struct tupconcnest {
    using head =  typename tupGet<s,nestedTup>::head ;
    using next = typename nestedTup::tailtup::headt ;
    using type = std::conditional<s==tuple_size<nestedTup>()-1,head,
      tupconc<0,head,tupconcnest<0,next>::type>::type>::type ;
};

template <typename... Tupts>
using tupnestt = tupconcnest<0,nestedTup<Tupts>>::type;

    template <typename tup,typename Head_,typename... Tail_>
    typename tup::conc<Head_,Tail_...> tuple_concat(tup& a,tuple<Head_,Tail_...>& b){
        tup::conc<Head_,Tail_...> res ;
        size_t s=0;
        for(;s<tuple_size<tupA>();s++){
            get<s>(res) = get<s>(a);
        };
        size_t ss = s;
        for(;s-ss<tuple_size<tupB>();s++){
            get<s>(res) = get<s-ss>(b);
        }
        return res;
    };
    template <typename tupA,typename tubB>
    tupconc<0,tupA,tupB>::type tuple_concat(tupA& a,tupB& b){
        tupconc<tupA,tupB> res;
        size_t s=0;
        for(;s<tuple_size<tupA>();s++){
            get<s>(res) = get<s>(a);
        };
        size_t ss = s;
        for(;s-ss<tuple_size<tupB>();s++){
            get<s>(res) = get<s-ss>(b);
        }
        return res;
    };



template <size_t s,typename tupT, typename... Tupts>
size_t set_tup(tupnestt<Tupts...>& ref,tupT& r){
    size_t si = s;
    for(;si-s<=tuple_size<tupT>();si++){
        std::get<si>(ref) = std::get<si-s>(r);
    }
    return si;
};
template <typename... Tupts>
tupnestt<Tupts...> concat_tuples(Tupts&... tups){    
    tupnestt<Tupts...> res;
    size_t s = 0;
    (s=set_tup<s,decltype(tups),Tupts...>(res,tups))...;
    return res;
};


}
#endif