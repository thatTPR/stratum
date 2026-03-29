// Header only serialization and deserialization library.
#include <fstream>
#include <type_traits>


template<class T>
class ser {
    T obj  ;
};
template<class T>
class des {
    T operator() ; 

};

template <class T>
class serdes : ser<T> , des<T> {

}