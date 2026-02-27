#ifndef MOD_UTIL_HPP
#define MOD_UTIL_HPP
#ifndef NSC
#define NSC pri::
#endif
#include <petri/macros.hpp>
#include <petri/vector>
#include <cstddef>
#include <ifstream>
#include <math.h>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <lib/glm/glm.hpp>
#include <cstring>
#include <math.h>
#include <petri\list.hpp>
#include <stratum/backend/impl.hpp>
#include "mod_quality.hpp"
namespace mod {
struct app_info {
    char*  name;
    uint32_t  ver;
    char*  engname;
    char*  engver;
};

#define NAME_FALSE false
#define NAME_TRUE true

template <typename T, template <typename T> class container >
struct pool {
    using type = T;
    using iterator = container<T>::iterator;
    virtual void updateReference(T* d);
    virtual void updateReference(T* d)
};



template <typename T>
struct named {
    std::string name;
    T data;
    named<T>& operator=(T& d){data=d;}
    named(std::string n, T& d) :name(n),data(d)  {};
} ;

/// Maybe change pools so that the referrence everything through pointers
template <tpename T, template <typename A> class container = NSC vector>
struct memoryPool {
   container <T> d;
   container <named<T*>> named;
    void addNamed(name<T> m){
        d.push_back(m.data);
        named<T*>(m.name,&d.back());return;
    }
    void add(T m){d.push_back(m);}
    container<T> get(){return d;}
    container<named<T*>> getNamed(){return named;}
};

template < template <DIM > typename T , template <typename A> container = NSC list>
struct  dmemoryPool  {
   container<named<T<DIM::Bi>*>> named2;
   container<named<T<DIM::Tri>*>> named3;
   container<T<DIM::Bi>> d2;
   container<T<DIM::Tri>> d3;

    template <DIM d>
    void add(T<d> m){
            if constexpr (d==DIM::Tri){d3.push_back(m);}
            else {d2=push_back(m);}
    };

    
    template <DIM d>
    void addNamed(named<T<d>> m){
            if constexpr (d==DIM::bi){d2.push_back(m.data);named2.push_back(named<T<2>*>(m.name,&d2.back()));;}
            else {d3.push_back(m.data);named3.push_back(named<T<2>*>(m.name,&d3.back()));;}
    };


    template<DIM d>
   container<named<T<d>*> getNamed(){
        if constexpr (d==dim::Bi){return named2;}
        else return named3;
   }
    template<DIM d>
   container<named<T<d>*> get{
        if constexpr (d==dim::Bi){return d2;}
        else return d3;
    };



};

#define QUALITIES_ENUM 0, 1, 2, 3, 4, 5, 6, 7

template < template <quality::QUALITY> typename T, template <typename A>class container , quality::QUALITIES... qs >
struct _qmemoryPool {

    pri::tuple<container<named<T<qs>*>...> named; 
    pri::tuple<container<T<qs>...>> d;

    template <quality::QUALITY q>
    void add(T<d>& m){
        pri::get<T<q>>(d).push_back(m);
    }
    template <quality::QUALITY q>
    void addNamed(named<T<q>>& m){   pri::get<named<T<q>>>(named).push_back(&m);};

    template <quality::QUALITY q>
   container<T<q>>& get(){ return pri::get<continer<T<q>>>(d);  }
    template <quality::QUALITY q>
   container <named<T<q>>>& getNamed(named<T<q>> m){
        return pri::get<container<named<T<q>>>>(named);
    }    
};
template < template <quality::QUALITY> typename T , template <typename A> container = NSC list>
using  qmemoryPool =  _qmemoryPool<T, container ,QUALITIES_ENUM>;

template < template <DIM , quality::QUALITY > typename T,template <typename A >class container, quality::QUALITY... qs>
struct  _qdmemoryPool  : dim_t<d>{
        pri::tuple<container <named<T<DIM::Bi,qs>*>>... > named2;
        pri::tuple<container <named<T<DIM::Tri,qs>*>>... > named3;
        pri::tuple<container <T<DIM::Bi,qs>>...> d2;
        pri::tuple<container <T<DIM::Tri,qs>>...> d3;
    
    template <DIM d,quality::QUALITY q>
    void add(T<d,q> m){
        if constexpr(d==2){
            pri::get<list<T<DIM::Bi,q>(d2).push_back(m);return;
        } 
            pri::get<list<T<DIM::Tri,q>(d3).push_back(m); 
    }
    template <DIM d,quality::QUALITY q>
    void addNamed(named<T<d,q>> m){
        if constexpr(d==2){
            pri::get<list<named<T<DIM::Bi,q>>(named2).push_back(m);return;
        } 
            pri::get<list<named<T<DIM::Tri,q>>(named3).push_back(m); 
    }

    template <DIM d,quality::QUALITY q>
   container<T<d,q>>& get(){
    if constexpr (d == DIM::Bi){return pri::get<conainer<T<DIM::Bi,q>>>(d2);}
    else pri::get<container<T<DIM::Tri,q>>>(d3);
   };

    template <DIM d,quality::QUALITY q>
   container<named<T<d,q>>>& getNamed(){
    if constexpr (d == DIM::Bi){return pri::get<container<named<T<DIM::Bi,q>>>>(d2);}
    else pri::get<container<named<T<DIM::Tri,q>>>>(d3);
   };

};

template < template <DIM , quality::QUALITY > typename T,tempate <typename A> class container= NSC list >
using qdmemoryPool = _qdmemoryPool<T,QUALITIES_ENUM> ; 


};
#endif