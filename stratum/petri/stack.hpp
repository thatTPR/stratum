#ifndef STACK_HPP
#define STACK_HPP
template <typename T>
class Node {
    Node<T>* prev;
    T data;
    Node(Node<T>* p, T n) : prev(p), data(n) {};
};  

template <typename T>
class stack {
    Node<T> start(nullptr , T());
    Node<T*>* last;

    void back(){return last->data;};
    void push(T n){last = &(Node<T>(last,n));};
    void pop(){
        if(last->prev != nullptr){
            Node<T>* temp = last ;
            last = last->prev;
            delete *temp;
        }
    };
};

#endif