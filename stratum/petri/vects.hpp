#pragma once
#include <assert>
#include <memory>
#include <initializer_list>
namespace ptr {

template<typename T, size_t sizearr>
class arr {
    public:
    
    T data[s];
    size_t size=sizearr;
    size_t pos=0 ;
    T data(){return this->data;}
    T& data(){return this->data;}
    T* data(){return &(this->data);}

    size_t pos(){return this->pos;};
    void clear(){this->pos=0;};
    operator+=(T n){if(this->pos==(this->size-1)){this->clear};this->data[pos]= n; this->pos++;};
    T& get(size_t pos){return this->data[pos];};
     T& operator[](size_t pos){
        assert(pos<size, "pos bigger than array size")
        return this->data[pos];
    };
    arr<T&,sizearr> operator=(T* s){
        arr<T&,sizearr> res;
        for(int i=0;i<sizearr;i++){
            res[i]=s[i];
        };
        return res;
    };
    void clear(){this->data = new T[size];this->pos=0;};
    void swap(size_t pos1 ,size_t pos2){
        T temp = this->data[pos1];
        this->data[pos1] = this->data[pos2] ;
        this->data[pos2] = temp;
        delete temp;
    };
    void copy(size_t pos1 , size_t pos2){
        this->data[pos2] = this->data[pos1];
        this->swap(pos1,pos2); int add=0;};
        arr<T,sizearr>& operator=(std::initializer_list<T> list){
        assert(list.size()==this->size)
        int i = 0 ;
        for(T val : list) {
            this->data[i] = val; i++;
        };
        return *this;
    };

    arr(std::initializer_list<T> list){
        assert(list.size()!=this->size);
        int i = 0 ;
        for(T val : list) {
            this->data[i] = val; i++;
        };
    };
    arr() = default ;
};
    #ifdef SWIZZLE_ARR
    using dim =sizearr ;
    #include "swizzle.def"
    #endif



template <typename T,size_t r=0, size_t c =0>
class mat {
    public:
    T data[r][c];
    size_t row = r ; size_t col = c;
    T data(){return this->data;}
    T& data(){return this->data;}
    T* data(){return &(this->data);}

    arr<T&,c> operator[](size_t pos){
     assert(pos<r);
    arr<T,c> res = this->data[pos];
    return res;
    };
    void swap(size_t r1,size_t c1 ,size_t r2, size_t c2){
        T temp = this->data[r1][c1];
        this->data[r1][c1] = this->data[r2][c2] ;
        this->data[r2][c2] = temp;
        delete temp;
    };
    mat<T,r,c>& operator=(std::initializer_list<T> s){
        assert(s.size()==r*c);
        int it=0;
        for(T i : s){
            this->data[it/c][it%c] = i;it++;
        };
        return *this;
    };
    mat<T,r,c>& operator=(std::initializer_list<std::initializer_list<T>> s){
        assert(s.size()==this->row);
        int it=0;
        for(std::initializer_list<T> i : s){
            assert(i.size()==this->col);
            int jt=0;
            for(T j : s){
            this->data[it][jt] = j;jt++;
            }
            it++;
        };
        return *this;
    };
    mat(std::initializer_list<T> s){this = s;}
   
   mat(std::initializer_list<std::initializer_list<T>> s){this= s; }
   mat() =default;

   #ifdef SWIZZLE_ARR
   using dim =r  ;
   #include "swizzle.def"
   #endif

};

 template <typename T >
 struct arrdepth {
     using _ty = std::remove_extent_t<T>;
    static constexpr int depth = std::is_array_v<_ty>?(arrdepth<_ty>::depth+1):0;
    static constexpr size_t size= size>arrdepth<_ty>::size?arrdepth<_ty>::size:sizeof(T[0]); 
 
 };
template <typename T>
struct arrtype {
    static constexpr bool vec = std::is_array_v<T>;
    static constexpr bool mat = std::is_array_v<T> && std::is_array_v<std::remove_extent_t<T>>;
    static constexpr bool depth = arr_depth<T>::depth;
    static constexpr bool sizeprim = arr_depth<T>::size;
    static constexpr bool arrd = depth==1; 
    static constexpr size_t size_prime=sizeof(T[0][0])/sizeof(T[0]);
    static constexpr bool arrvec = depth==2?((sizeof(T[0])>(sizeprim*4))?true:false):false;
    static constexpr bool matd = depth==2?(sizeof(T[0])>(sizeprim*4))?true:false):false;
    static constexpr bool matvec = mat and (depth == 3) ? true : false ;
    static constexpr bool matmat = mat and (depth == 4) ? true : false ;
};

template <typename T,size_t r=0, size_t c=0>
struct arrc {
    using d=std::conditional<c==0,T[r],T[r][c]>::type;
    static constexpr size_t row = r;
    static constexpr size_t col = c ;
    static bool mat=c>0; 
};


template <typename T , size_t size_buffer=0b1000 >
class vect {
    private:
    size_t size_buf = size_buffer;
    size_t tsize=size_buf;
    T* data;
    size_t s;// Current size
    public:
    T* get_data(){
        return this->data;
    };
    size_t size(){return this->s;};
    
    size_t tsize(){return this->tsize;};
    T& get(size_t pos){return this->data[pos];}
    void resize(size_t a){ // Resizes tsize to a + size_buf and vect to a;
        T* n = new T[a+size_buf];
        if(a<this->s){
            for(int i = 0 ; i< a;i++){n[i] = this->data[i];};
        }
        else{
            for(int i=0 ; i < this->s ; i++ ){
                n[i] = this->data[i]; 
            };
        };
        this->data= new T[a+size_buf] ;this->data=n;
        this->s= a;
    };
    void reserve(size_t n){
        this->tsize=this->tsize+n;
        T* n = new T[this->tsize];
        for(int i=0 ; i < this->s ; i++ ){
            n[i] = this->data[i]; 
        };
        this->data= new T[this->tsize] ;this->data=n;
    };
    void insert(size_t pos, T elem){
        if(!(this->s+1 < this->tsize)){
        this->resize(this->s+1);};
        T cur; 
        cur = this->data[pos];
        this->data[pos] = elem;
        for(int i = pos+1 ; i < this->s;i++){
            T current = this->data[i];
            this->data[i]=cur;
            cur= current;
    };
    void erase(size_t pos){
        this->s--;
        for (int i = pos ; i < this->s ; i++){
            this->data[i] = this->data[i+1];
        };     
    };

    #ifdef CXX23
    vect operator[](size_t a, size_t b){
        vect<T> res ;
        for(int i =a ; i<=b ; i++){
            res[i-a] = this->data[i];
        };
        return res;
    };
    #endif
    
    T& operator[](size_t pos){
        if(pos >= this->s){
            this->resize(pos+1);
            return this->data[pos];
        };
        return this->data[pos];
    };
    vect& operator=(std::initializer_list<T> list){
        T* n = new T[list.size()];
        int i = 0 ;
        for(T val : list) {
            n[i] = val; i++;
        };
        this->data=n;
        this->s = list.size();
    };
     void push(T& elem){
        if (this->s < this->tsize){
            this->data[s]= elem;
            this->s++; return;
        };
        this->resize(this->tsize);
        this->data[this->s] = elem;
        this->s++;
    };
    void clear(){
        this->s=0;
        this->tsize=sizebuf;
        this->data = new T[sizebuf];
    };
    void swap(size_t pos1 ,size_t pos2){
        T temp = this->data[pos1];
        this->data[pos1] = this->data[pos2] ;
        this->data[pos2] = temp;
        delete temp;
    };
    void move(size_t pos1 , size_t pos2){
        this->swap(pos1,pos2); int add=0;
        if(pos1<pos2){add=1;}
        else {add=-1}
        for( int i = pos1 + add ; i != pos2 ; i+=add )
            this->swap(i-add,i);
        };
    };
    vect(size_t size){
        this->s = size; 
        this->tsize = size+size_buf;
        this->data = new T[this->tsize];
    };  
    vect(){vect(0);}
    vect(size_t s, size_t tsize){
        this->s = s; this->tsize = tsize ; this->data= new T[this->tsize];
    };

};
template <typename T,size_t sb=0b100,>
using vectvect= vect<<vect<T,sb>,sb>> ;

#ifdef TENSOR_MAT
template <typename T,size_t first>
class ten {
    using ty =T[first]
    using next = NULL;
    using order = 1;
    static constexpr bool sizes[] = {first};
    using type = 
};
template <typename T ,size_t first, size_t... s>
class ten{
    using ty=vec<T,first>::ty;
    using next = ten<ty,s...>
    using order = 1+ next::order;
    static constexpr bool sizes[] = {first}+next::sizes;    
    using type = next::ty;
    type data;
    ten& operator[](size_t pos){
        return this->data[pos];
    };
    ten& operator+=(ten& n ){
        
    };
    ten& operator*=(ten& n){

    };
    ten& operator*=(ten& n){

    };
    ten& operator-=(ten& n){

    };
    ten& operator*(ten& n){if}
    ten& operator+(ten& n){if}
    ten& operator-(ten& n){if}
    ten& operator/(ten& n){if}
    ten& operator%(ten& n){if}
    
   
    T operator[](size_t last){
        ten<T,sizes[order-1]> res = this[last];
    };
    T operator[](size_t First,size_t... arg){
        assert(sizeof...(arg) + sizeof(First) > sizeof(sizes)/sizeof(first) );
        assert(sizeof...(arg) + sizeof(First) < sizeof(sizes)/sizeof(first) );
        T ret = this->data[First].operator[](arg...);
        return ret;
    };
    ten get_ten_index(size_t no , size_t last,){

    };
    ten get_ten_index(size_t no, size_t midF , size_t... args){

    };
    ten get_ten_ind(size_t no, size_t last){
        size_t ncur = no+1;
        for(int i = no ; i < size_t )
         this->data[last]
    };
    ten get_ten_ind(size_t no,size_t First, size_t... arg){
        assert(sizeof...(arg) + sizeof(First) > sizeof(sizes)/sizeof(first) );//, "To many parameters");
        size_t ncur = no+1;
        ten<First,arg...> tens = this->data[First]->get_ten_ind_cur(ncur,arg...)
        
    };

    ten operator[](size_t First,size_t... s){
        return this->get_ten_ind(0,First,arg...);
    };
    ten();
};
};
#endif
