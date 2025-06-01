#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>

template <typename T>
    class list {
        
        public:

        struct node {
            
            T cur; 
            node* prev;
            node* next;
            node(node* n) : cur(n->cur) , prev(n->prev) , next(n->next) {};
            node(node* l,node* r) : prev(l),next(r){};
            node(T& ref, node* pr) : cur(ref),prev(pr){};
            node(T ref, node* pr) : cur(ref),prev(pr){};
        };  

        int Size ;
        node* first;
        node* last ;

        list() :Size(0){first = last ;};
        template <typename Ty>
        class iterator {
            public: 
            node* ptr;
            Ty& operator*(){return (ptr->cur);};
            bool operator==(iterator& rhs){return ptr == rhs.ptr ;};
            bool operator!=(iterator& rhs){return !(ptr == rhs.ptr) ;};
            void operator++(){ptr = ptr->next;};
            void operator--(){ptr= ptr->prev;};
            iterator operator+(int size){
                for(int i = 0 ; i <size; i++){ptr = ptr->next;};
                return *this;
            };
            iterator operator-(int size){
                for(int i = 0 ; i <size; i++){ptr = ptr->prev;};
                return *this;
            };
            iterator(node* f) : ptr(f){};
            iterator(iterator& f) : ptr(f.ptr) {};
        };
        using iter = iterator<T> ;
        using const_iter = iterator<const T> ;
        
        T& operator[](int i){
            node* cur = last;
            for(int j = Size ; j>=0; j--){
                    if(j==i){return cur->cur;};
                    cur = cur->next;
                }
            return first->cur;
        };
        node* node_at(int s){
            node* cur = first;
            for(int j = 1 ; j <= s ; j++){cur=first.next;            }
            return cur;
        };
        T& value(node* n){return n->cur;};

        T& back(){return last->cur;};
        T& front(){return first->cur;};
        inline void push(const T& ref){
            last->next = new node(ref,last);
            last = (last->next);
        };
        void push_back(const T& ref){
            push(ref);
            Size++;
        };
        inline void pop(){
                node* l = last;
                delete last;
                last= l->prev;
                delete l;
        };
        void pop_back(){
            if(last == first){return;};
            pop();
            Size--;
        };
        const_iter end()const {return const_iter(last)+1;};
        const_iter begin()const {return const_iter(first);};
        iter end(){return (iter(last)+1);};
        iter begin(){return iter(first);};
        void pop(iter& at){
            at.ptr->prev->next = at.ptr->next;
            at.ptr->next->prev = at.ptr->prev;
            delete at.ptr ;
        };
        void erase(iter from , iter to){
            iter c(from);
            do{
                c.ptr->prev->next = c.ptr->next;
                node* p = c.ptr->next;
                delete c.ptr ;
                c.ptr = p;
            }while(c!=to);
            c.ptr->prev->next = c.ptr->next;
            node* p = c.ptr->next;
            delete c.ptr ;
        };
        int SIZE(){
            int i=0;
            for(const T& it : *this){i++;};
            return i;
        };
        int size(){return Size;};
        list(std::initializer_list<T> l){
            for(const T& it : l){
                push_back(it);
            };
        };  
        list(const list<T>& v) : Size(v.Size) {
            for(const auto& it : v){
                this->push_back(it);
            };
        };
    };
    #endif