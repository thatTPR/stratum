
#include <tuple>
/*
template<>
struct si {
    size_t size = 0;
} ;
template<typename f>
struct si {
    size_t size = 1+si<>;
} ;
template<typename f,typename s>
struct si {
    size_t size = 1 + si<s>;
} ;
template<typename f,typename... args>
struct si {
    size_t size = 1 + si<args>;
} ;

template<typename head>
class tuple : tuple<args>{
    size_t s=0;
};
template<typename head>
class tuple : tuple<args>{
    size_t s=1;
};
template<typename head,typename last>
class tuple : tuple<args>{
    size_t s=2;
};
template<typename Head,typename... Args>
class tuple : tuple<args>{
   public:
    head val;
    const size_t s = si<Head,Args>::size ;
    size_t size(){return this->size;}
    size_t pos=0+posi<prev_pos,>;

    template<size_t ind=0 >
    Head& operator[](size_t ind){
        return this->val;
    };
    
    template<size_t ind >
    auto& operator[](size_t ind){
        return tuple<Args...>[ind-1];
    };
    
    tuple(Head v, Tail... tail) : tuple<Tail...>(tail...), value(v) {}



};  
*/
template<typename T ,T v>
struct integral_constant {
    static constexpr T val = v;
    static constexpr T operator()(){return val;};
};
template <typename fir,typename... k>
class tuple : public tuple<k...>  {
    fir head;
    fir get(integral_constant<size_t s , 0> s){
        return this->head;
    };
    template <size_t Index>
    auto& get(integral_constant<size_t, Index>) {
        return tuple<Tail...>::get(std::integral_constant<size_t, Index - 1>());
    };
    auto& operator[](size_t s){
        return get(integral_constant<size_t , s>);
    };

};
