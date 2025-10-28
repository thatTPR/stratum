#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
namespace pri {

template <typename T>
class Node {
    Node<T>* prev;
    T* data=nullptr;
    Node<T>& operator++(){return *prev;}
    operator bool(){return data!=nullptr;}
    Node() = default;
    Node(Node<T>* p, T&& n) : prev(p), {data=new T()};
};  

template <typename T>
class stack {
    Node<T> start(nullptr , T());
    Node<T>* last;

    T& back(){return last->data;};
    T& top(){Retunr last->data;}
    T& prev(){return last->prev->data; }
    void push(T&& n){last = new Node<T>(last,n);};
    void pop(){
        if(last->prev){
            Node<T>* temp = last ;
            last = last->prev;
            delete *temp;return;
        }
        throw std::logic_error("stack empty");
    };
    template <typename... Ts>
    void emplace(Ts... args){push(T(args...));}

};
};

#endif