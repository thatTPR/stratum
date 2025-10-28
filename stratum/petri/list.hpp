#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>
#include <initializer_list>
#include <type_traits>
#include <utility>

namespace pri {


template <typename T>
    class list {
        public:

      
        template <typename Ty>
        class iterator {
            public: 
            Ty* Ptr;
            iterator<Ty>* prev=nullptr;
            iterator<Ty>* next=nullptr; 
            iterator(Ty& f ){Ptr->data = &f;}
            iterator(node* f) {Ptr = f; };
            iterator(node f){Ptr = &f; };
            
            iterator<Ty>& next(){return *next;};
            iterator<Ty>& prev(){return *prev;};
            Ty* operator->(){return Ptr ;};
            Ty& operator*(){return *Ptr;};
            bool operator==(iterator& rhs){return Ptr == rhs.Ptr ;};
            // bool operator==(iterator rhs){return Ptr == rhs.Ptr;};
            // bool operator!=(iterator& rhs){return Ptr != rhs.Ptr ;};
            bool operator!=(iterator& rhs){return Ptr != rhs.Ptr ;};
            // bool operator!=(iterator<Ty> rhs){return Ptr != rhs.Ptr ;};
            void operator++(){this=next;};
            void operator--(){this=prev;};
            iterator<Ty>& operator++(int){this=next;return *this;};
            iterator<Ty>& operator--(int){this=prev;return *this;};
            operator delete(){delete Ptr;}
            size_t operator-(iterator& rhs ){
                size_t i = 0 ;
                iterator<Ty>* t = this ;
                for(;*t!= rhs and (*t);--(*t) ){i++;};
                return i ;
            };

            iterator<Ty> operator-(int s){
                int h = s ; 
                for(int h=s ; h ; h--){--(*this);}
                return *this;   
            };
            iterator<Ty> operator+(int s){
                for(int h=s ; h ; h--){++(*this);} 
                return *this;  
            };
            operator bool() {return(Ptr!=nullptr);};
            bool operator!{return !bool(*this);}
            operator delete(){delete Ptr;};
            iterator(iterator* l, iterator* r = nullptr){
                prev = l;
                next = r;
            };

            iterator(iterator* l, T& d, iterator* r = nullptr){
                prev = l ;
                next=  r;
                data = new T(data);
            };
            
            iterator( iterator* pr,const T& d, iterator* r = nullptr) {
                prev = pr ; next = r;
                data = new T(data);
            };
            template <typename U>
            iterator(iterator* _prev, U&& value,iterator* _next=nullptr) :  data((new T(std::forward<U>(value)))) // ✅ construct T from value
             {
                 prev=_prev;next=_next;
             }
             iterator() = default;
             iterator(iterator& f)  {*this=f;};
        };
        iterator first = iterator();
        iterator last = iterator() ;
        list() =default ;
        using iter = iterator<T> ;
        using const_iter = iterator<const T> ;
        
        T& back(){return  *(last->data);};
        T& front(){return *(first->data);};
        


        iterator& iter_at(int s){
            iterator cur = first;
            for(int j = 0 ; j < s ; j++){cur=first.next;            }
            return cur;
        };

        T& value(iterator n){return n->data;};

        iter rend() {return rev(first)--;};
        iter rbegin() { return rev(last);}
        iter end(){ return iter(last)++ ;};
        iter begin(){ return iter(first);};
        iter tail(){ return iter(last) ;};
        iter head(){ return iter(first)--;};
        
        bool empty()  {return ((last==nullptr) and (nullptr=first));};
        
        
        // iterator::operator bool() const {return this->Ptr != last;};

         inline size_t SIZE() const {
            size_t i=0;
            for(const T& it : *this){i++;};
            return i;
        };
        size_t size() const {
            if(empty()){return 0;};
            return SIZE();
        };

        inline iter iter_at(int s){
            int a = s;
             for(iter it= begin() ; it!=end() ; ++it){
                a-- ;if(!a){;return it;};
            };
        };
        void insert(T& val, iter& at ){
            if(!iter) {throw std::logic_error("iter \"at\" invalid");}
            if((*at.next)){
                at.next=new iterator(*(at.prev)? first :at.prev.next,&at,val);}
            else {at.next=new node(at.next->prev,val,at.next);}
        };

        T& operator[](size_t s){return *(iter_at(s)->data);}
        
       void insert(T& val, int at ){insert(val,iter_at(at));   };
        
        void push_back(const T& data){
            if(!empty()){last.next=new iterator(last, std::move(data));}
            else {last= iterator(last,std::move(data));first=last;}
        };
        void push_back(T&& data){
            if(!empty()){last.next=new iterator(&last, std::forward<T>(data),nullptr);}
            else {last= iterator(&last,std::forward<T>(data),nullptr);first=last;}
        }; // };
        void push_front(const T& data){                
            if(!empty()){first.prev=new iterator(nullptr, std::move(data),&first);}
            else {first= iterator(nullptr,std::move(data),&first);last=first;}
        };
        void push_front(T&& data) {
            if(!empty()){first.prev=new iterator(nullptr,std::forward<T>(data),&first);}
            else {                last= iterator(nullptr,std::forward<T>(data),&first);first=last;}
        };
        template <typename... Args>
        void emplace_back(Args&&... args){
            push_back(T(args...));
        };
        template <typename... Args>
        void emplace_front(Args&&... args){
            push_front(T(args...));
        };
        template <typename... Args>
        void emplace_insert(iter& at,Args&& ... args){
            insert(T(args...),at);
        };
        
        template <typename... Args>
        void emplace_insert(int at,Args&& ... args){
            insert(T(args...),at);
        };
        
        void init(){first.Ptr=nullptr;last.Ptr=nullptr;}
        inline void pop(){
            if(first == last){
                delete first.Ptr;
                init();
            }
            else 
            {
                last = last->prev;
                delete last->next;
                return;
            }
        };
        void pop_back(){// if(empty()) {return ;};
            pop() ;
        };
        void erase(iter& at){
            if(at){delete at.Ptr;};
        };
        void pop(iter& at){
            delete at;
        };
        void pop(int at){
            pop(iter_at(at));
        };
        
        void erase(iter from , iter to){
            if(!to){throw std::logic_error("iter from invalid");return;}
            if(!from){throw std::logic_error("iter to invalid");return;}
            iter c=from+1;
            for(erase(from);c!=to and c ;++c){erase(*(c.prev));};
            erase(to);
        };
        void clear(){
            if(!empty()){erase(begin(),end());};
            init();
        };

        T& operator[](int i){
            int j = i-1;iter f = begin();
            for(; f and (j) ; ++f  ){j--;};
            return *f;
        };

        list(std::initializer_list<T> l){
            for(const T& it : l){
                push_back(it);
            };
        };  
        void operator=(std::initializer_list<T>& inl){
            list(l);
        };
        ~list(){clear();};
        list(const list<T>& v)  {
            init() ;
            for(const T& it : v){push_back(it);};
        };
    };

            // list::iterator::operator bool() const {return this->Ptr != last;};
};
#include "reverse_iterator.hpp"
#endif