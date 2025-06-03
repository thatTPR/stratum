#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include <list>
template <typename T>
    class list {
        
        public:

        struct node {
            
            node* prev;
            node* next;
            T* cur; 
            node(){};
            node(node* n)  {
                *this = *n ;
            };
            node(node* l, node* r){
                node();
                prev = new node(l);
                next = new node(r);
            };

            node(node* l, T& data, node* r){
                node(l,r) ;
                cur = new T(data);
            };

            node(T& data, node* pr) {
                prev = new node(*pr);
                prev->next = new node(this);
                cur=new T(data);};
            node(const T& data, node* pr) {
                node(const_cast<T&>(data), pr);};
           
            ~node(){
                prev->next = new node(next) ;
                next->prev = new node(prev);
                delete cur;
                delete prev;
                delete next;
            };
        };  

        // int Size ;
        node* first;
        node* last ;

        list() {
            first =new node(first,first);
            last = new node(first);
        }
        T& back(){return *(last->cur);};
        T& front(){return *(first->cur);};
        // list() :Size(0){first = last ;};
        template <typename Ty >
        class iterator {
            public: 
            node* ptr;
            iterator(node* f) : ptr(f){};
            node* get(){return ptr;};
            Ty* operator->(){return (ptr->cur) ;};
            Ty& operator*(){return *(ptr->cur);};
            bool operator==(iterator<Ty>& rhs){return ptr == rhs.ptr ;};
            bool operator!=(iterator<Ty>& rhs){return ptr != rhs.ptr ;};
            void operator++(){ptr=ptr->next;};
            void operator--(){ptr=ptr->prev;};
            size_t operator-(iterator<Ty>& rhs ){
                size_t i = 0 ;
                for(;*this!= rhs;--(*this) ){i++;};
                return i ;
            };
            iterator<Ty> operator-(int s){
                for(int h=s ; h ; h--){--(*this);}
                return *this;   
            };
            iterator<Ty> operator+(int s){
                for(int h=s ; h ; h--){++(*this);} 
                return *this;  
            };
            explicit operator bool() const {return ptr != nullptr;};
            // operator delete(){
            //     delete ptr;
            // };
           
            iterator(iterator<Ty>& f) : ptr(f.ptr) {};
        };
        using iter = iterator<T> ;
        using const_iter = iterator<const T> ;

        bool empty(){return last->next == first;};
        node* node_at(int s){
            node* cur = first;
            for(int j = 1 ; j <= s ; j++){cur=first.next;            }
            return cur;
        };
        T& value(node* n){return n->cur;};

        
        void push_back( T& data){
           last->next = new node(data,last);
            last = (last->next);
        };
        void push_back(const T& data){
            last->next = new node(data,last);
            last = (last->next);
        };

        inline void pop(){
            delete last->cur;
            last = last->prev;
        };
        void pop_back(){
            // if(empty()) {return ;};
            pop() ;
        };
        
        const_iter end()const {return const_iter(last)+1;};
        const_iter begin()const {return const_iter(first);};
        iter end(){return (iter(last)+1);};
        iter begin(){return iter(first);};
        // iterator::operator bool() const {return this->ptr != last;};

        inline iter iter_at(int s){
            int a = s;
             for(iter it= begin() ; it!=end() ; ++it){
                a-- ;if(!a){;return it;};
            };
        };
        void insert(T& val, iter& at ){
            node* s = new node(val,at.get()) ;
            s->next = at->next ;
            at->next->prev = s ;
            s->prev = at.get() ;
            at.get()->next = s;
            
        };
        void pop(iter& at){
            // if(empty()){return;};
            delete at.ptr->prev->next ;
        };
        void pop(int at){
           pop(iter_at(at));
        };
        void erase(iter from , iter to){
            iter c(from);
            iter prev = from-1;
            for(;c!=to;++c){pop(c);}
            pop(from);
        };
        void clear(){
            erase(begin(),iter(last));
            list();
        };

        T& operator[](int i){
            int j = i-1;iter f = begin();
            for(; f and (j) ; ++f  ){j--;};
            return *f;
        };

        inline size_t SIZE() const {
            size_t i=-1;
            for(const T& it : *this){i++;};
            return i;
        };
        inline size_t Size() const {
            const_iter e = end() ;
            const_iter b = begin() ;
           return e - b ;
        };
        size_t size() const {
            return Size();    
        };
        void operator=(std::initializer_list<T> l){
            list() ;
            for(const T& it : l){
                push_back(it);
            };
        };
        list(std::initializer_list<T> l){
            *this = l;
        };  
        list(const list<T>& v)  {
            list() ;
            for(const auto& it : v){
                this->push_back(it);
            };
        };
    };

            // list::iterator::operator bool() const {return this->ptr != last;};

    #endif