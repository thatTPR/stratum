
namespace tree{

    template <typename T>
    class treeallocator {
        typedef size_t size_type;
        typedef T* pointer;
        typedef const T* const_pointer;

        pointer arr;
                template<typename _Tp1>
                struct rebind
                {
                        typedef allocator<_Tp1> other;
                };
                    
                pointer allocate(size_type n, const void *hint=0)
                {
                    
                    
                    return treeallocator<T>::allocate(n, hint);
                }
                
                void deallocate(pointer p, size_type n)
                {
                       p->~T();
                }
};



template <typename T, class Allocator alloc = eltreeAlocator>
class eltree {
    public:
    
    T d;
    eltree<T>* parent;
    eltree<T>* children;
    
    size_t childrenSize;
    
    eltree<T>& get(size_t i){return children[i];};    
    size_t size(){return childrenSize};
    eltree<T>& front(){

    }
    eltree<T>& back(){

    };
    void resize(size_t s)
    void push_back(eltree<T> el){
        
    };
    void dfs(void (*func)(eltree<T>&) ){
        func(*this);
        for(int i = 0 ; i < childSize ; i++){
            children[i].dfs(func);
        };
    };


    void bfs(void (*func)(eltree<T>&) ){
        int* index = [childrenSize];
        int i =0;
        func(*this);
        auto cur = this;
        for(index[i] ; index[i]<cur->childrenSize ){

        };
    };
    
};
};