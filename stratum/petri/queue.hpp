#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <initializer_list>
namespace pri {


    template <typename T>
    struct qnode {
        T* data;
        node<T>* next;
        node(T& d) { data = new T(d);}   
        template <typename... Ts>
        node(Ts... d) { data = new T(d...);}   
    };


    template <typename T>
    struct dqnode {
        T* data;
        node<T>* next;
        node<T>* prev;
        node(T& d) { data = new T(d);}   
        template <typename... Ts>
        node(Ts... d) { data = new T(d...);}   
    };

template <typename T,template <typename Ty> typename node>
class _queue {
   
    node<T>* first;
    node<T>* last;

    bool empty() const {
        if(first){return false;}
        if(last){return false;}
        return true;
    };
    T& front(){return *(first->data);}
    T& back(){return *(last->data);}

    template <typename... Ts>
    void emplace(Ts... v){last->next=new node<T>(v...);delete cur;}
    void push_back(T& d){last->next=new node<T>(d);last=last->next;};
    void pop(){node<T>* cur = first;first=first->next;delete cur;}
        _queue(){last->next=first;}
    size_t  size(){
        size_t s=0;
        node<qnode>* it=first;if(first){s++;}
        for(;it;it=it->next){s++;}
        return s;
    };

    _queue(std::initializer_list<T>&& list){for(const T& it : list){push_back(it);}};
    _queue(_queue<T>& q){*this=q;};
};
template <typename T>
using queue= _queue<T,qnode>;
template <typename T>
struct deque : public _queue<T,dqnode>{
    using node=dqnode<T>;
        class iterator {
            public: 
            node* ptr;
            iterator(Ty& f ){
                ptr->data = &f;
            }
            iterator(node<T>* f) {
                ptr = f; 
            };
            iterator(node<T> f){
                ptr = &f; 
            };
            
            iterator next(){return iterator<Ty>(ptr->next);};
            iterator prev(){return iterator<Ty>(ptr->prev);};
            node* get(){return ptr;};
            Ty* operator->(){return (ptr->data) ;};
            Ty& operator*(){return *(ptr->data);};
            bool operator==(iterator& rhs){return ptr == rhs.ptr ;};
            // bool operator==(iterator rhs){return ptr == rhs.ptr;};
            bool operator!=(iterator& rhs){return ptr != rhs.ptr ;};
            // bool operator!=(iterator<Ty> rhs){return ptr != rhs.ptr ;};
            void operator++(){ptr=ptr->next;};
            void operator--(){ptr=ptr->prev;};
            iterator& operator++(int){ptr=ptr->next;return *this;};
            iterator& operator--(int){ptr=ptr->prev;return *this;};
            
            size_t operator-(iterator& rhs ){
                size_t i = 0 ;
                iterator<Ty>* t = this ;
                for(;*t!= rhs;--(*t) ){i++;};
                return i ;
            };

            iterator operator-(int s){
                int h = s ; 
                for(int h=s ; h ; h--){--(*this);}
                return *this;   
            };
            iterator operator+(int s){
                for(int h=s ; h ; h--){++(*this);} 
                return *this;  
            };
            explicit operator bool() const {
                if(ptr){return true;} 
                else return false;};
            // operator delete(){
            //     delete ptr;
            // };
           
            iterator(iterator& f) : ptr(f.ptr) {};
        };
        
        using iter = iterator<T> ;
        using const_iter = iterator<const T> ;
        const_iter end() const {return const_iter(last)++ ;};
        const_iter begin() const {return const_iter(first);};

        iter end(){ return iter(last)++ ;};
        iter begin(){ return iter(first);};
        iter tail(){return iter(last);}
        iter head(){return --begin();}
        iter rend(){return head();}
        iter rbegin(){return tail();}
        void pop_front(){pop();}
        void pop_back(){node<T>* cur=last;last=last->prev;delete cur;}
        void push_front(T& d){first->prev=new node<T>(d);first=first->prev;}


        void eraseFromEnd(iter& it){
            while(tail()!=it){pop_back();}
            pop_back();
        };
        decltype(*this) operator+=(deque<T>& d){
            for(T it:d){this->push_back(it);}
            return *this;
        };
        void erase(){while(!empty()){pop();}}
        template <typename... Ts>
        void emplace_back(Ts... v){emplace(v...);}

        template <typename... Ts>
        void emplace_front(Ts... d){first->prev=new node<T>(d...);first=first->prev;}

        void concat(deque<T>&& d){this->last->next=d.first;
            d.first->prec=this->last;
        };

    } ;
};
#include "reverse_iterator.hpp"
#endif