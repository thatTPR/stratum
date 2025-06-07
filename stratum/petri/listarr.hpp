#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include <list>
template <typename T>
    class listarr {
        
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
        size_t size , curSize; 
        node** arr; 


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
            bool operator==(iterator<Ty> rhs){return ptr == rhs.ptr;};
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
        template <typename Ty>
        class reverse_iterator : public iterator<Ty> {
            
            void operator++(reverse_iterator<Ty>& rhs){this->ptr=this->ptr->prev;};
            void operator--(reverse_iterator<Ty>& rhs){this->ptr=this->ptr->next;};
            size_t operator-(reverse_iterator<Ty>& rhs){
                size_t i = 0 ; 
                for(;*this!=rhs;--(*this)){i++;};return i;
            };
        };
        using rev = reverse_iterator<T>;
        using const_rev = reverse_iterator<const T> ;

        bool empty(){return last->next == first;};
        node* node_at(int s){
            node* cur = first;
            for(int j = 1 ; j <= s ; j++){cur=first.next;            }
            return cur;
        };
        T& value(node* n){return n->cur;};
        void grow(int s=1){
            curSize+=s;
            if(curSize>=size) {
                size +=2+size/2 ; 
                node* a = arr ;
                arr = new node*[size];
                for(int i =0  ; i < curSize -1 ; i++ ){
                    arr[i] = a[i]; 
                } ;
            }
        };
        void shrink(int s=1){
            curSize-=s;
            if(curSize<=size/2) {
                size = size/2 ;
                size += size%2!=0?3:2; 
                node* a = arr ;
                arr = new[size] node*[size];
                for(int i =0  ; i < curSize -1 ; i++ ){
                    arr[i] = a[i]; 
                } ;
            }
        };

        template <typename Tyo>
        void push(Tyo f){
            grow();
            ast->next = new node(data,last);
            last = (last->next);
            arr[curSize-1]  = last ;
        };
        void push_back( T& data){
            push(data);
        };
        void push_back(const T& data){
            push(data);    
        };

        inline void pop(){
            shrink();
            delete last;
            last = last->prev;
        };
        void pop_back(){
            // if(empty()) {return ;};
            pop() ;
        };
        const_iter reverse() const {return const_iter(last);};
        const_iter end()const {return const_iter(last)+1;};
        const_iter begin()const {return const_iter(first);};
        iter reverse() {return iter(last);};
        iter end(){return (iter(last)+1);};
        iter begin(){return iter(first);};
        // iterator::operator bool() const {return this->ptr != last;};

        inline iter iter_at(size_t s){
            return iter(arr[s]);
        };
        void insert(T& val, iter at ){
            node* s = new node(val,at.get()) ;
            s->next = at->next ;
            at->next->prev = s ;
            s->prev = at.get() ;
            at.get()->next = s;
        };
        void insert(T& val , size_t at){
            iter_at(val,iter_at(at));
        };
        void pop(iter& at){
            // if(empty()){return;};
            
            if(at == end()){return;};
            delete at.ptr->prev->next ;
        };
        void pop(int at){
           pop(iter_at(at));
        };
        void tailMove(iter& from ,iter& to){ // Rewrite iterators for this to work
            int j = 0;
            for(iter i = from ;to+j != end(); ++i){j++;
                *from = *(to+j); 
            };
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