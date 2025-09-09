#ifndef MOD_UTIL_HPP
#define MOD_UTIL_HPP

#include <petri/macros.hpp>
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


template <typename T>
struct named {
    std::string name;
    T data;
    named<T>& operator=(T& d){data=d;}
    named(std::string n, T& d) :name(n),data(d)  {};
} ;

/// Maybe change pools so that the referrence everything through pointers
template <tpename T>
struct memoryPool {
    list<T> d;
    list<named<T*>> named;
    void addNamed(name<T> m){
        d.push_back(m.data);
        named<T*>(m.name,&d.back());return;
    }
    void add(T m){d.push_back(m);}
    pri::list<T> get(){return d;}
    pri::list<named<T*>> getNamed(){return named;}
}

template < template <DIM > typename T>
struct  dmemoryPool  : dim_t<d>{
    list<named<T<DIM::Bi>*>> named2;
    list<named<T<DIM::Tri>*>> named3;
    list<T<DIM::Bi>> d2;
    list<T<DIM::Tri>> d3;

    template <DIM d>
    void add(T<d> m);

    
    template <>
    void add<DIM::Bi>(T<DIM::Bi> m){
d2.push_back(m);}

    template <>
    void add<DIM::Tri>(T<DIM::Tri> m){d3.push_back(m);}
    
    template <DIM d>
    void addNamed(named<T<d>> m);

        template <>
    void addNamed<DIM::Bi>(named<T<DIM::Bi>> m){
    d2.push_back(m.data);named2.push_back(named<T<2>*>(m.name,&d2.back()));;}

        template <>
    void addNamed<DIM::Tri>(named<T<DIM::Tri>> m){
d3.push_back(m.data);named3.push_back(named<T<DIM::Tri>*>(m.name,&d3.back());return;}


    template<DIM d>
    list<named<T<d>*> getNamed();
    template <> list<named<T<DIM::bi>*> getNamed<DIM::Bi>(){return d2;}
    template <> list<named<T<DIM::Tri>*> getNamed<DIM::Tri>(){return d3; }
};

#define QUALITIES_ENUM 0, 1, 2, 3, 4, 5, 6, 7

template < template <quality::QUALITY> typename T,quality::QUALITIES... qs>
struct _qmemoryPool {

    pri::tuple< list<named<T<qs>*>...> named; 
    list<T<qs>...> d;

    template <quality::QUALITY q>
    void add(T<d>& m){
        pri::get<T<q>>(d).push_back(m);
    }
    template <quality::QUALITY q>
    void addNamed(named<T<q>> m){
        pri::get<named<T<q>>>(named).push_back(m);
    }

    template <quality::QUALITY q>
    list<T<q>>& get(){
        return pri::get<T<q>>(d);
        
    }
    template <quality::QUALITY q>
    list<named<T<q>*>> getNamed(named<T<q>> m){
        return pri::get<named<T<q>>>(named);
    }    
};
template < template <quality::QUALITY> typename T>
using  qmemoryPool =  _qmemoryPool<T,QUALITIES_ENUM>;




template < template <DIM , quality::QUALITY > typename T, quality::QUALITY... qs>
struct  _qdmemoryPool  : dim_t<d>{
        pri::tuple<list<named<T<DIM::Bi,qs>*>>... > named2;
        pri::tuple<list<named<T<DIM::Tri,qs>*>>... > named3;
        pri::tuple<list<T<DIM::Bi,qs>>...> d2;
        pri::tuple<list<T<DIM::Tri,qs>>...> d3;
    
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
    list<T<d,q>>& get();
    template <quality::QUALITY q>
    list<T<DIM::Bi,q>>& get<DIM::Bi,q>(){ return pri::get<list<T<DIM::Bi,q>>(d2);}    
    
    template <quality::QUALITY q>
    list<T<DIM::Tri,q>>& get<DIM::Tri,q>(){return pri::get<list<T<DIM::Tri,q>>(d3);}    
    
    template <DIM d,quality::QUALITY q>
    list<named<T<d,q>>>& getNamed();
    
    template <quality::QUALITY q>
    list<named<T<DIM::Bi,q>>>& getNamed(){return return pri::get<list<named<T<DIM::Bi,q>>>(d2);};
    
    
    template <quality::QUALITY q>
    list<named<T<DIM::Tri,q>>>& getNamed(){return return pri::get<list<named<T<DIM::Tri,q>>>(d3);};
    
};

template < template <DIM , quality::QUALITY > typename T, quality::QUALITY... qs>
using qdmemoryPool = _qdmemoryPool<T,QUALITIES_ENUM> ; 
}
#endif