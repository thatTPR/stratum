#ifndef STACK_HPP
#define STACK_HPP
namespace pri {

template <typename T>
class Node {
    Node<T>* prev;
    T data;
    Node(Node<T>* p, T n) : prev(p), data(n) {};
};  

template <typename T>
class stack {
    Node<T> start(nullptr , T());
    Node<T>* last;

    T& back(){return last->data;};
    T& top(){Retunr last->data;}
    T& prev(){return last->prev->data; }
    void push(T n){last = new Node<T>(last,n);};
    void pop(){
        if(last->prev != nullptr){
            Node<T>* temp = last ;
            last = last->prev;
            delete *temp;
        }
    };

};
};

#endif