template <typename T>
class queue_el {
    public:
    T el;
    size_t pos;
    std::shared_ptr<queue_el<T>> next;
    std::shared_ptr<queue_el<T>> prev;
    // operator delete(this){
    //     ::operator delete(this->el) ;
    //     ::operator delete(*this) ;
    // };

    queue_el(T n,queue_el<T>* next,queue_el<T>* prev){
        this->el = n; this->next=next; this->prev=prev;
    };
};
template <typename T>
class queue {
    public:
    std::shared_ptr<queue_el<T>> first (NULL,nullptr,nullptr); 
    std::shared_ptr<queue_el<T>> last  ;
    size_t pos=0;
    queue_el<T>* cur;
    size_t size=0;
    void operator++(){
        this->pos++;this->cur=this->cur.next;
    }; 
    void operator--(){
        this->pos--;this->cur=this->cur.prev;
    }; 
    void set()
    queue_el* get(size_t pos){
        assert(pos<size); size_t it = this->pos;
        queue_el<T>* current;
        if(pos>this->pos){for(current = this->cur;it!=pos;it++){current=current.next;};}
        else             {for(current = this->cur;it!=pos;it--){current=current.prev;};};
        else {return this->cur;};
        return current;
    } ;
    T& operator[](size_t pos) {
        return this->get(pos).el;
    }; 
    queue_el<T>* peek(int pos){
        assert((pos+this->pos<this->size));
        assert((pos+this->pos>=0));

        size_t c = pos;queue_el<T>* cur=this->cur;
        if(pos>0){for(;c!=0;c--){cur=cur.next;};}
        else     {for(;c!=0;c++){cur=cur.prev;};};
        else return this->cur;
        return cur;
    };
    T& operator()(int pos){return this->peek(pos).el;} ;
    void insert(size_t pos, T n){
        queue_el<T>* te= this->get(pos);
        queue_el<T>* el=queue_el<T>(n,te.prev,te)
        te->prev=el ; el->prev->next=te;
        this->size++;this->pos+=pos>pos?1:0;
    };
    void insert(T n){this->insert(this->pos,n);};
    void pop(size_t pos){
        queue_el<T>* te= this->get(pos);
        te->prev=te->next ; te->next=te->prev;
        delete *te;
        this->size--;this->pos-=pos>pos?1:0;
    };
    void pop(){this->pop(this->pos)};
    void push_begin(T n){
        this->first= &(queue_el<T>(n,this->first,nullptr));this->size++;
        this->first->next->prev=this->first;
    };
    void push_end(T n){
        this->last= &(queue_el<T>(n,nullptr,this->last));this->size++;
        this->last->prev->next=this->last;
    };
    void pop_begin(){
        queue_el<T> tem = this->first;
        this->first=this->first->next;
        this->first->prev=nullptr;
        delete *tem; this->size--;
    };
    void pop_end(){
        queue_el<T> tem = this->last;
        this->last=this->last->prev;
        this->last->next=nullptr;
        delete *tem; this->size--;
    };
    void swap(size_t pos1,size_t pos2){
        assert(pos1< this->size);
        assert(pos2< this->size);
        size_t f,s;
        if(pos1>pos2){f = pos2;s=pos1}
        else {f=pos1;s = pos2;};
        queue_el<T>* el= this->first;queue_el<T>* fir;
        for(size_t cur=0;;cur!=s;cur++){
            if(cur==f){fir=el;};
            if(cur==s){
                fir->next->prev=el ;
                fir->prev->next=el;
                el->next->prev=fir;
                el->prev->next=fir;
                queue_el<T>* oneprev;queue_el<T>* onenext;
                onenext=fir->next;oneprev=fir->prev;
                fir->next=el->next;fir->prev=el->prev;
                el->next= onenext;el->prev=oneprev;
                return;
            };
            el=el.next();
        };
    };
    void swap(size_t pos1){
        this->swap(pos1,this->pos);
        this->pos=pos1;
    };
    void operator delete(){
        while(this->size>=0){
            this->pop_begin();
        };
    };
    queue() = default;
};