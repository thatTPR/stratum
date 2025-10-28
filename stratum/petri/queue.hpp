#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace pri {


    template <typename Ty>
    struct qiter {
       Ty* Ptr;
  qiter<Ty>* next=nullptr; 
                 qiter<Ty>& next(){return *next;};
            void operator++(){this=next;};
            qiter<Ty>& operator++(int){this=next;return *this;};
            qiter<Ty> operator+(int s){
                for(int h=s ; h ; h--){++(*this);} 
                return *this;  
            };
       Ty* operator->(){return Ptr ;};
            Ty& operator*(){return *Ptr;};
            bool operator==(qiter<Ty>& rhs){return Ptr == rhs.Ptr ;};
            // bool operator==(qiter rhs){return Ptr == rhs.Ptr;};
            // bool operator!=(qiter& rhs){return Ptr != rhs.Ptr ;};
            bool operator!=(qiter<Ty>& rhs){return Ptr != rhs.Ptr ;};
            // bool operator!=(qiter<Ty> rhs){return Ptr != rhs.Ptr ;};
            operator bool() {return(Ptr!=nullptr);};
            bool operator!{return !bool(*this);}
            operator delete(){delete Ptr;};
            qiter(qiter<Ty>* l, qiter<Ty>* r = nullptr){
                prev = l;
                next = r;
            };

           dqiter(qiter<Ty>* l, T& d){
                prev = l ;
                next=  r;
                data = new T(data);
            };
            
            dqiter( qiter<Ty>* pr,const T& d) {
                prev = pr ; next = r;
                data = new T(data);
            };
            template <typename U>
            qiter(qiter<Ty>* _prev, U&& value,qiter<Ty>* _next=nullptr) :  data((new Ty(std::forward<U>(value)))) 
             {
                 prev=_prev;next=_next;
             }
             template <typename... Ts>
             qiter(qiter<Ty><Ty* prev,Ts... args){qiter<Ty>(prev,Ty(args...));}
             qiter() = default;
             qiter(qiter<Ty>& f)  {*this=f;};
             qiter(qiter<Ty>* f)  {this=f;};
             qiter(Ty data) {Ptr=new Ty(data);}
    };


    template <typename Ty>
    struct dqiter : public qiter<Ty>{
            dqiter<Ty>* prev=nullptr;
        dqiter<Ty>& prev(){return *prev;};
        void operator--(){this=prev;};
        dqider<Ty>& operator--(int){this=prev;return *this;};
        operator delete(){delete Ptr;}
        size_t operator-(dqiter<Ty>& rhs ){
                size_t i = 0 ;
                dqiter<Ty>* t = this ;
                for(;*t!= rhs and (*t);--(*t) ){i++;};
                return i ;
            };
        dqiter<Ty> operator-(int s){
                int h = s ; 
                for(int h=s ; h ; h--){--(*this);}
                return *this;   
            };
             dqiter(dqiter<Ty>* l, T& d, dqiter<Ty>* r = nullptr){
                prev = l ;
                next=  r;
                data = new T(data);
            };
      
            dqiter( dqiter<Ty>* pr,const T& d, dqiter<Ty>* r = nullptr) {
                prev = pr ; next = r;
                data = new T(data);
            };
            dqiter( dqiter<Ty>* pr, dqiter<Ty>* r ,const T& d) {
                prev = pr ; next = r;
                data = new T(data);
            };
            template <typename... Ts>
            dqiter(dqiter<Ty>* prev,dqiter<Ty>* next,Ts... args){dqiter<Ty>(prev,next,Ty(args...));}


    };

template <typename T,template <typename Ty> typename Iter>
class _queue {
   
    
    Iter<T>* first;
    Iter<T>* last;
    void init(){first=new Iter<T>();last=new Iter<T>();}
    bool empty() const {
        if(first){return false;}
        if(last){return false;}
        return true;
    };

    T& back(){return last->Ptr;}
    T& front(){return first->Ptr;}
    template <typename... Ts>
    void emplace(Ts... v){last->next=new Iter<T>(last,v...);}
    void push_back(T& d){last->next=new Iter<T>(d);last=last->next;};
    void pop(){
        if(*first){
            Iter<T>* cur =first;
            ++(*first);
            delete cur ;
        }
    };
    void clear(){while(!empty()){pop();};}

        using iter = Iter<T> ;
        using const_iter = Iter<const T> ;
        const_iter end() const {return const_iter(last)++ ;};
        const_iter begin() const {return const_iter(first);};

        iter end(){ return iter(last)++ ;};
        iter begin(){ return iter(first);};
        iter tail(){return iter(last);}
        iter rend(){return head();}
        iter rbegin(){return tail();}
        
    _queue() = default;
    size_t  size(){
        size_t s=0;
        Iter<T>* it=first;if(first){s++;}
        for(;it;it=it->next){s++;}
        return s;
    };

    _queue(std::initializer_list<T>&& list){for(const T& it : list){push_back(it);}};
    _queue(_queue<T>& q){*this=q;};
};
template <typename T>
using queue= _queue<T,qiter>;
template <typename T>
struct deque : public _queue<T,dqiter>{
    using node=dqnode<T>;
    using iter = dqiter<T>;
        iter head(){return --begin();}
        void pop_front(){pop();}
        void pop_back(){
            if(last->prev){
                iter* cur=last;last=last->prev;delete cur;}
            else {
                delete last;
                init();}
        }
        void push_front(T& d){first->prev=new iter(d);first=first->prev;}
        void eraseFromEnd(iter& it){
            while(tail()!=it){pop_back();}
            pop_back();
        };
                
        void concat(deque<T>&& d){
            if(!empty()){
                this->last->next=d.first;
                this->last->next->prev=this->last;
                last=d.last;
            }
            else {*this = d;}
        };

        decltype(*this) operator+=(deque<T>& d){
            concat(d);return *this;
        };
        void erase(){while(!empty()){pop();}}
        template <typename... Ts>
        void emplace_back(Ts... v){emplace(v...);}
        
        template <typename... Ts>
        void emplace_front(Ts... d){first->prev=new node<T>(d...);first=first->prev;}

        T& operator[](size_t s){size_t ss=0
            for( T& : *this){s++;if(s==s){return s;}}
            throw std::out_of_range; 
        };  

    } ;
};
#include "reverse_iterator.hpp"
#endif