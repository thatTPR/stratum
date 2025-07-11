#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include <type_traits>
#include <utility>


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
                prev = pr ; next = r;
                data = new T(data);
            };
            template <typename U>
            node(node* _prev, U&& value, node* _next=nullptr) :  data((new T(std::forward<U>(value)))) // ✅ construct T from value
             {
                 prev=_prev;next=_next;
             }
           
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


        void init(){
            first =new node();
            last = new node(nullptr,first);
        }
        list() {
            init();
        }
        // list() :Size(0){first = last ;};
        template <typename Ty >
        class iterator {
            public: 
            node* ptr;
            iterator(Ty& f ){
                ptr->data = &f;
            }
            iterator(node* f) {
                ptr = f; 
            };
            iterator(node f){
                ptr = &f; 
            };
            
            iterator<Ty> next(){return iterator<Ty>(ptr->next);};
            iterator<Ty> prev(){return iterator<Ty>(ptr->prev);};
            node* get(){return ptr;};
            Ty* operator->(){return (ptr->data) ;};
            Ty& operator*(){return *(ptr->data);};
            bool operator==(iterator<Ty>& rhs){return ptr == rhs.ptr ;};
            // bool operator==(iterator<Ty> rhs){return ptr == rhs.ptr;};
            // bool operator!=(iterator<Ty>& rhs){return ptr != rhs.ptr ;};
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
            explicit operator bool() const {
                if(ptr){return true;} 
                else return false;};
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
        bool empty() const {return (last->next == first);};
        
        
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
            node* s = new node(at.ptr,val,at.ptr->next) ;
            if(at.ptr->next) at.ptr->next->prev = s; 
            at.ptr->next = s;            
        };
        
       
        // void push_back( T& data){
        //         node* s = new node(last, data);
        //         if(empty()){s->prev = nullptr;
        //             last = s;
        //             first= last;
        //         }
        //         else {
        //             last->next= s;
        //             last = last->next;}
                    
            
        // };
        void push_back(const T& data){
                
                node* s = new node(last, std::move(data));
                if(empty()){s->prev = nullptr;
                    last = s;
                    first= last;
                }
                else {
                    last->next= s;
                    last = last->next;}            
        };
        void push_back(T&& data){

            node* s =new node(last,std::forward<T>(data),nullptr);
                if(empty()){s->prev = nullptr;
                    last = s;
                    first= last;
                }
                else {
                    last->next= s;
                    last = last->next;}            
        };
        
        // void push_back(T* data){
        //     node* s =new node(last,*data,nullptr);
        //         if(empty()){s->prev = nullptr;
        //             last = s;
        //             first= last;
        //         }
        //         else {
        //             last->next= s;
        //             last = last->next;}            
        // };

     
        // void push_back(const T data){push<const T>(data);};
        
        // void push_back(std::initializer_list<auto> s){push_back(T(s));};
        inline void pop(){
            if(first == last){
                delete first;
                init();return;
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
        void erase(iter& at){
            if(at){
                delete at.ptr;
            };
        };
        void pop(iter& at){
            iter prev=at?at-1:at;
            iter next=at?at+1:at;
            erase(at);
            bool p = false; bool n=false;;
            if(prev ){p=true;}
            if(next){n=true;}
            if(p and n){
                prev.ptr->next = next.ptr;
                next.ptr->prev = prev.ptr;
            }
            else if(p){prev.ptr->next = nullptr;
                last = prev.ptr;}
                else if(n){next.ptr->prev = nullptr;
                    first = prev.ptr;}
                    else {init();}            

        };
        void pop(int at){
            pop(iter_at(at));
        };
        
        void erase(iter from , iter to){
            iter c(from);
            iter prev=from?from-1:from;
            iter next=to?to+1:to;
            for(node* n = c.ptr ;c!=next ;c = iter(n)){
                if(n)n=n->next;
                else break;
                erase(c);
            }
            bool p = false; bool n=false;;
            if(prev){p=true;}
            if(next){n=true;}
            if(p and n){
                prev.ptr->next = next.ptr;
                next.ptr->prev = prev.ptr;
            }
            else if(p){prev.ptr->next = nullptr;
                last = prev.ptr;}
            else if(n){next.ptr->prev = nullptr;
                first = next.ptr;}
            else {init();}            
            
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
            clear();
            for(const T& it : l){
                push_back(it);
            };
        };  
        void resize(int s){
            int dif = s - size();
            for(;dif;--dif){push(T());};
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