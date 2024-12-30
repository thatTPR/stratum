#include <type_traits>
template <typename , typenme = std::void_t<>>
struct has_value_type : std::false_type {};
template <typename T>
struct has_value_type<T, T::value_type> : std::true_type {};

template <typename , typenme = std::void_t<>>
struct has_bool_type : std::false_type {};
template <typename T>
struct has_bool_type<T, T::value_type> : std::true_type {};



template <typename , typenme = std::void_t<>>
struct has_col : std::false_type {};
template <typename T>
struct has_col<T, T::col_type> : std::true_type {};

template <typename T> 
struct is_glmvec{
    constexpr bool value = has_value_type<T>::value && has_bool_type::value ;
} ;
template <typename T> 
struct is_glmmat{
    constexpr bool value =is_glmvec<T>::value &&has_col<T>::value ;
} ;
