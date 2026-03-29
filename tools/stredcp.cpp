#include <iostream>
using namespace std;
template<typename chart>
 bool eq(chart& l,chart& r){return l==r;};
template<typename chart>
bool neq(chart& l,chart& r){return l!=r;};
template <typename chart >
class b_strng {
    public:
    chart* s;
    int _size;

    int size(){return this->_size;};
    
    void resize(int am){this->size+= am;
        chart n[this->size];
        n = s;
        this->s = new chart[this->size];
        this->s = n; 
    };
    chart& operator[](int am){
        if(am<this->size()){return this->s[am]; };
        return this->s[this->size()-1];

    };
    b_strng& operator+=(chart n){
        this->resize(1);
        this->s[this->size-1] = n;
        return *this;
    };

    b_strng& operator+=(const chart* s){
        for(int i = 0 ; s[i]!='\0';i++){
            this->s +=s[i];
        };
        return *this;
    };
    
    b_strng& operator=(const chart* s){
        for(int i = 0 ; s[i]!='\0';i++){
            this->s[i] =s[i];
            std::cout<<s[i];
        };
        return *this;
    };

  
    
    int find(b_strng<chart> s, int pos=0){
        for(int i =pos; i < this->size();i++){
            if(this->s[i]==s[0]){
                bool b =true;
                for(int j = 1 ; j < s.size();j++){
                    if(this->s[i+j]!=s[j]){b = false;}
                };
                if(b){return i;}
                return -1;
            };
    };};
    int find_first(b_strng<chart> s, 
    bool (*func)(chart&,chart&),
    int pos )
    {
        for(int i =pos; i < this->size();i++){
            for(int j = 0;j<s.size();j++){
                if( func(s[j],this->s[i])){return i ;};
            };
        };
        return -1;
    };
    
   
    int find_first_of(b_strng<chart> s , int pos=0){
        bool (*st)(chart&, chart&);
        st= eq<chart>;
        return this->find_first(s,st , pos);         
    };
    int find_first_not(b_strng<chart> s, int pos=0){
        bool (*st)(chart&, chart&);
        st = neq<chart>;

        return this->find_first(s,st , pos); 
    };
    b_strng() = default;

};  
using strng = b_strng<char>;
/*
template <bool words >
class stred {
    // Captures    
    #define BRACKBEG "["
    #define BRACKEND "]" 
    #define BRACEBEG "{"
    #define BRACEEND "}"
    #define PARENBEG "("
    #define PARENEND ")"

    // 
    // Escapes 
    strng find(strng expr, int* sizepos,int* pos){
        for()
    };
    strng replace(strng i, strng o , strng str){

    };
    strng replace(strng expr, strng str){ // Sepparated by ;\n
        
    };
    
};*/
int main(){
    strng s ;
    s = "read";
    strng t ;t= "res" ;
    std::cout<< t.s[0];

    std::cout<<s.find_first_of(t);
};