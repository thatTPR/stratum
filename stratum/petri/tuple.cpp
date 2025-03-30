
#include <string>
#include <iostream>
#include <cstddef>
#include <type_traits>



template <typename...>
struct tuple;

struct empty {} ;
template <typename T>
struct tuple<T> {
    public:
    using cur = T ;
    using tprest = empty ;
    // static const size_t size = 0 ;
    T data;
};

template <typename T, typename ...Ts >
struct tuple<T,Ts...> {
    public:
    // static const size_t size = 1;
    using tycur = T ;
    using tyrest = ...Ts ;
    using tprest = tuple<Ts...>;
    T data;
    tprest rest;    
   
   
};
template <typename T>
using singtp = tuple<T>;
template <typename T, typename ...Ts>
using multtp = tuple<T,Ts...>  ;

template <typename tp>
constexpr size_t tpsize();

// template <size_t s , typename tp>
// auto& gets(tp tps) {

// };
template <size_t s, typename T , template <typename >class tp >
auto& get(tp<T>& tps){
    return tps.data ;
};
template <size_t s , typename T>
auto& get(T& trest){
    // static_assert(std::is_same<tuple<typename... > , T>::value)
        return get<s,T,T::tycur,T::tyrest>() ;    
};
 template <size_t s , template <typename , typename...> class tp , typename T , typename... Ts>
auto& get(tp<T,Ts...>& tps){
    using trest = tp<T,Ts...>::tprest ;
    if(s==0){return tps.data;} ;
    return gets<s-1,trest>(tps.rest) ;    
    
};

// template <singtp tp>
// constexpr size_t tpsize(){return 1 ; };
// template <typename tp>
// constexpr size_t tpsize_t(){return 1 + tpsize_t<tp::tprest> }

template <typename tp>
 constexpr size_t tpsize(){
    using trest = tp::tprest ;
    if(std::is_same<trest , void>::value ){
        return 1; 
    }
    else return 1 + tpsize<tp::tprest> ; 
        
};
// template <size_t s , typename... ts>
// auto& get(tuple<ts...>& tp){
//     if(s==0){return tp.data;}
//     return get<s-1>(tp.rest);
// };
void tuple_concat(){

};

int main()
{
    using typs = tuple<int,float,double> ;
    typs tps ;
    std::cout<<tpsize<typs>();
    get<2,typs>(tps) = 2;
    std::cout<<get<2>(tps);
    
}