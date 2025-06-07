#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include <type_traits>
#include <iterator>
template <typename T>
    class list {
        
        public:

        struct node {
            
            node* prev;
            node* next;
            T* data; 
            node(){};
            node(node* l, node* r = nullptr){
                prev = l;
                next = r;
            };

            node(node* l, T& d, node* r = nullptr){
                prev = l ;
                next=  r;
                data = new T(data);
            };
            node( node* pr,const T& d, node* r = nullptr) {
                node(pr,const_cast<T&>(d),r);};
            ~node(){
                if(data){delete data;};
            };
            // if(data){delete data;};
            // // if(prev ) prev->next = next;
            // // if(next) 
           
        };  

        // int Size ;
        node* first;
        node* last ;


        list() {
            first =new node();
            last = new node(nullptr,first);
            
        }
        // list() :Size(0){first = last ;};
        template <typename Ty >
        class iterator {
            public: 
            node* ptr;
            iterator(node* f) {
                if(f){ptr = f; }
            };
            iterator(node f){
                ptr = &f; 
            };
           
            node* get(){return ptr;};
            Ty* operator->(){return (ptr->data) ;};
            Ty& operator*(){return *(ptr->data);};
            bool operator==(iterator<Ty>& rhs){return ptr == rhs.ptr ;};
            // bool operator==(iterator<Ty> rhs){return ptr == rhs.ptr;};
            bool operator!=(iterator<Ty>& rhs){return ptr != rhs.ptr ;};
            // bool operator!=(iterator<Ty> rhs){return ptr != rhs.ptr ;};
            void operator++(){ptr=ptr->next;};
            void operator--(){ptr=ptr->prev;};
            
            iterator<Ty>& operator++(int){ptr=ptr->next;return *this;};
            iterator<Ty>& operator--(int){ptr=ptr->prev;return *this;};
            size_t operator-(iterator<Ty>& rhs ){
                size_t i = 0 ;
                iterator<Ty>* t = this ;
                for(;*t!= rhs;--(*t) ){i++;};
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

        bool empty() const {return last->next == first;};
        T& back(){return  *(last->data);};
        T& front(){return *(first->data);};
        


        node* node_at(int s){
            node* cur = first;
            for(int j = 1 ; j <= s ; j++){cur=first.next;            }
            return cur;
        };
        T& value(node* n){return n->data;};

        const_iter rend() const  {return const_iter(first)--;};
        const_iter rbegin() const  {return const_iter(last); };
        const_iter end() const {return const_iter(last)++ ;};
        const_iter begin() const {return const_iter(first);};
        
        iter rend() {return iter(first)--;};
        iter rbegin() { return iter(last);}
        iter end(){ return iter(last)++ ;};
        iter begin(){ return iter(first);};
        
        
        // iterator::operator bool() const {return this->ptr != last;};

         inline size_t SIZE() const {
            // if(empty()){return 0;};
            size_t i=0;
            for(const T& it : *this){i++;};
            return i;
        };
        inline size_t Size() const {
            if(empty()){return 0;};
            const_iter e = rbegin() ;
            const_iter b = rend() ;
           return e - b ;
        };
        size_t size() const {
            return SIZE();
        };

        inline iter iter_at(int s){
            int a = s;
             for(iter it= begin() ; it!=end() ; ++it){
                a-- ;if(!a){;return it;};
            };
        };
        void insert(T& val, iter& at ){
            node* s = new node(at.get(),val,at.get()->next) ;
            if(at->get()->next) at->get->next->prev = s; 
            at->get()->next = s;            
        };
        template <typename Tyo>
        void push(Tyo data){
            if constexpr ( std::is_reference<Tyo>::value and std::is_pointer<typename std::remove_reference<Tyo>::type>::value ){
                typename std::remove_reference<Tyo>::type d = data ;
                 node* s = new node(last,*d);
                if(empty()){s->prev = nullptr;
                last = s;
                first= last;
                }
                else {
                last->next= s;
                last = last->next;}
                return;
            };
            node* s = new node(last, data);
            if(empty()){s->prev = nullptr;
                last = s;
                first= last;
            }
            else {
                last->next= s;
                last = last->next;}

            
        };

        // void push_back( T data){push<T>(data);};
        void push_back( T& data){push<T&>(data);};
        void push_back(const T& data){push<const T&>(data);};
        
        // void push_back(std::initializer_list<auto> s){push_back(T(s));};
        inline void pop(){
            if(last == first){
                delete first;
                list();return;
            }
            else 
            {
                last = last->prev;
                delete last->next;
                return;
            }
                  
        };
        void pop_back(){
            // if(empty()) {return ;};
            pop() ;
        };
        void pop(iter& at){
            iter en = end();
            if(at == en){return;};
            iter b =begin();
            if(at!=b){
                at.ptr->prev->next = at.ptr->next ;
            };
            iter r = rend() ;
            if(at!=r){
                at.ptr->next->prev = at.ptr->prev;
            }
            delete at.ptr ;
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
            if(!empty()){erase(begin(),end());};
            this = list();
        };

        T& operator[](int i){
            int j = i-1;iter f = begin();
            for(; f and (j) ; ++f  ){j--;};
            return *f;
        };

        list(std::initializer_list<T> l){
            clear();
            for(const T& it : l){
                push_back(it);
            };
        };  
        
        void operator=(std::initializer_list<T>& inl){
            list(l);
        };
        ~list(){
            clear();
        };
        list(const list<T>& v)  {
            list() ;
            for(const T& it : v){
                push_back(it);
            };
        };
    };

            // list::iterator::operator bool() const {return this->ptr != last;};

    #endif