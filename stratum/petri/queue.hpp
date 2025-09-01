#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace pri {


template <typename T>
class queue {
   
    struct node {
        T* data;
        node<T>* next;
        node(T& d) { data = new T(d);}   
    }

    node* first;
    node* last;


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
        const_iter end() const {return const_iter(last)++ ;};
        const_iter begin() const {return const_iter(first);};

        iter end(){ return iter(last)++ ;};
        iter begin(){ return iter(first);};
        bool empty() const {return (last->next == first);};

    T& front(){return *(first->data);}
    T& back(){return *(last->data);}

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
    void push(T& d){last->next=new node(d)};
    void pop(){node* cur = first;first=first->next;delete cur;}

};
};
#endif