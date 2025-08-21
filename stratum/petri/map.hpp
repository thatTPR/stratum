#ifndef PETRI_MAP_HPP
#define PETRI_MAP_HPP



template <typename K, typename V >
class map {
    struct node {
        node* first
        
    };

    node* root ;


    bool exists(K key){

    }
    bool get(K key, V& res){return true }
    V& operator[](K key){
        V& res;
        if(get(key,res)){
            return res;
        }
    };
    
};

#include "pair.hpp"
template <typename K,typename V>
class iterMap :  map<K,V> {

    using iterVal = std::pair<K&,V&> ;
    std::vector<iterVal> vecs;

    V& operator[](K s){

    };
    void insert(std::pair<){

    };


    iterVal front(){vecs.front();}
    iterVal back(){vecs.back();}
};
#endif