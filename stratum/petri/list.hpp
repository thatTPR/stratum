#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include <type_traits>
#include <utility>

namespace pri {


template <typename T>
    class list {
        
        public:

        struct node {
            
            node* prev;
            node* next;
            T* data; 

            // template <typename... Args>
            // node(Args... V){data= new T(Args...);};
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
        template <typename Ty>
        class iterator {
            public: 
            node* Ptr;
            iterator(Ty& f ){Ptr->data = &f;}
            iterator(node* f) {Ptr = f; };
            iterator(node f){Ptr = &f; };
            
            iterator next(){return iterator<Ty>(Ptr->next);};
            iterator prev(){return iterator<Ty>(Ptr->prev);};
            node* get(){return Ptr;};
            Ty* operator->(){return (Ptr->data) ;};
            Ty& operator*(){return *(Ptr->data);};
            bool operator==(iterator& rhs){return Ptr == rhs.Ptr ;};
            // bool operator==(iterator rhs){return Ptr == rhs.Ptr;};
            // bool operator!=(iterator& rhs){return Ptr != rhs.Ptr ;};
            bool operator!=(iterator& rhs){return Ptr != rhs.Ptr ;};
            // bool operator!=(iterator<Ty> rhs){return Ptr != rhs.Ptr ;};
            void operator++(){Ptr=Ptr->next;};
            void operator--(){Ptr=Ptr->prev;};
            iterator& operator++(int){Ptr=Ptr->next;return *this;};
            iterator& operator--(int){Ptr=Ptr->prev;return *this;};
            
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
                if(Ptr){return true;} 
                else return false;};
            // operator delete(){
            //     delete Ptr;
            // };
           
            iterator(iterator& f) : Ptr(f.Ptr) {};
        };
        using iter = iterator<T> ;
        using const_iter = iterator<const T> ;
        
        T& back(){return  *(last->data);};
        T& front(){return *(first->data);};
        


        node* node_at(int s){
            node* cur = first;
            for(int j = 1 ; j <= s ; j++){cur=first.next;            }
            return cur;
        };

        T& value(node* n){return n->data;};

        
        iter rend() {return rev(first)--;};
        iter rbegin() { return rev(last);}
        iter end(){ return iter(last)++ ;};
        iter begin(){ return iter(first);};
        iter tail(){ return iter(last) ;};
        iter head(){ return iter(first)--;};
        
        bool empty() const {return (last->next == first);};
        
        
        // iterator::operator bool() const {return this->Ptr != last;};

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
            node* s = new node(at.Ptr,val,at.Ptr->next) ;
            if(at.Ptr->next) at.Ptr->next->prev = s; 
            at.Ptr->next = s;            
        };

        T& operator[](size_t s){return *(node_at(s)->data);}
        
       void insert(T& val, int at ){
        insert(val,iter_at(at));   };
        
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
        void _push_back_(node* s){
                if(empty()){s->prev = nullptr;
                    last = s;
                    first= last;
                }
                else {
                    last->next= s;
                    last = last->next;}            

        }
        void push_back(const T& data){
                
                node* s = new node(last, std::move(data));
                _push_back_(s);
        };
        void push_back(T&& data){

            node* s =new node(last,std::forward<T>(data),nullptr);
              _push_back_(s);  
        }; // };
        void _push_front_(node* s){
                        if(empty()){s->next = nullptr;
                    last = s;
                    first= last;
                }
                else {
                    first->prev= s;
                    first = first->prev;}          

        }
        void push_front(const T& data){                
            node* s = new node(std::move(data),first);
            _push_front_(s);
        };
        void push_front(T&& data) {
        node* s = new node(nullptr,std::forward<T>(data),first);
        _push_front_(s);
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
                delete at.Ptr;
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
                prev.Ptr->next = next.Ptr;
                next.Ptr->prev = prev.Ptr;
            }
            else if(p){prev.Ptr->next = nullptr;
                last = prev.Ptr;}
                else if(n){next.Ptr->prev = nullptr;
                    first = prev.Ptr;}
                    else {init();}            

        };
        void pop(int at){
            pop(iter_at(at));
        };
        
        void erase(iter from , iter to){
            iter c(from);
            iter prev=from?from-1:from;
            iter next=to?to+1:to;
            for(node* n = c.Ptr ;c!=next ;c = iter(n)){
                if(n)n=n->next;
                else break;
                erase(c);
            }
            bool p = false; bool n=false;;
            if(prev){p=true;}
            if(next){n=true;}
            if(p and n){
                prev.Ptr->next = next.Ptr;
                next.Ptr->prev = prev.Ptr;
            }
            else if(p){prev.Ptr->next = nullptr;
                last = prev.Ptr;}
            else if(n){next.Ptr->prev = nullptr;
                first = next.Ptr;}
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

            // list::iterator::operator bool() const {return this->Ptr != last;};
};
#include "reverse_iterator.hpp"
#endif