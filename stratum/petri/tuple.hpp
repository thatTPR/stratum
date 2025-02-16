
template <typename f> 
struct tuples {
    using ty =f;
    using size = 1;
    f d ;
    auto tup<next> ;

};
template <typename first, typename... next>
struct tuples  {
      first d; 
      tupleMulti<next> n ; 
};

template <typename first, typename... next>
struct tuple {
  first d ;
  using next = tuples<next> ;
  next n ;
};
template <size_t s>
auto& get(tuple& tp){
  if(s ==0 )return tp.d;
  else return get<s-1>(tp.n) ;
} ;

template <typenmme s>
void add(tuples& g ){

};
template <typename s>
void add(tuple& tp){
    get<size(tp)>(tp).; 
};
