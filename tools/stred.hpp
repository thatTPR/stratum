
// Basically worthless
    
 
    
typedef unsigned long int ulint;
template <typename chart >
class b_strng {
    chart* s;
    int size;

    public:
    void resize(int am){this->size+= am;
        chart n[this->size];
        n = s;
        this->s = new chart[this->size];
        this->s = n; 
    };
    b_strng& operator+=(chart n){
        this->resize(1);
        this->s[this->size-1] = n;
    };

    b_strng& operator+=(const chart* s){
        for(int i = 0 ; s[i]!='\0';i++){
            this->s +=s[i];
        };
    };
    int size(){return this->size;};
    void eq(chart& l,chart& r){return l==r;};
    void neq(chart& l,chart& r){return l!=r;};
    
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
    };
    int find_first(b_strng<chart> s, 
    bool (*func)(chart&,chart&),
    int pos ){
        for(int i =pos; i < this->size();i++){
            for(int j = 0;j<s.size();j++){
                if( func(s[j],this->s[i])){return i ;};
            };
        };
        return -1;
    };
    };
   
    int find_first_of(b_strng<chart> s , int pos=0){
        return this->find_first(s,this->eq , pos);         
    };
    int find_first_not(b_strng<chart> s, int pos=0){
        return this->find_first(s,this->neq , pos); 
    };
    

};  
using strng = b_strng<char>;
template <bool words,bool case>
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
    strng find(std::string expr, int* sizepos,int* pos){
        for()
    };
    strng replace(std::string i, std::string o , std::string str){

    };
    strng replace(std::string expr, std::string str){ // Sepparated by ;\n
        
    };
    
};

