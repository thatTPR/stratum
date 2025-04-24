#include "vects.hpp"

template <typename f,typename s>
class pair {    
    public:
    f fel ; s sel;
    f first(){return this->fel;};
    s second(){return this->sel;};
  
    pair(f elf,s els) : f(elf) , s(els){}
};

template <typename T> 
class less {
    size_t dif ;
    less(T a, T b){
        
    };
};

template <typename k,typename v, class cmp = >
class map {    
    public:
    vect<k,size_buf> keys;
    vect<v,size_buf> vals;
    size_t size=0 ;
    v& operator[](k key){
        for(int i =0 ; i < this->size;i++ ){
            if(key==this->keys->size){return this->vals[i];};
        };
        this->keys.push(key);
        v n;
        this->vals.push(n);
        this->size++;
    };
    k posk(size_t s){return this->keys[s] ;}
    ClassA(std::initializer_list<pair<k,v>> initList)   {
        this->keys.resize(initList.size())
        this->vals.resize(initList.size())
        for(pair<k,v>& val: initList){
            this->keys=val.first();
            this->vals=val.second();
        };
    };
    map()=default;

};  