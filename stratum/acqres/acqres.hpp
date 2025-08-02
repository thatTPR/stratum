#ifndef ACQRES_HPP
#define ACQRES_HPP
// #include <type_traits>
// template <typename T, size_t si>
// void ld(T& s,std::ifstream* fi){
//     if constexpr(std::is_pointer<T>::value){
//         fi->read(reinterpret_cast<char*>(s) , sizeof(s[0])* si)
//     }
//     else {
//         fi->read(reinterpret_cast<char*>(s) , sizeof(s) )
//     }
// };

#include <cstddef>
#include <fstream>
#include <vector>
#include <functional>

template <typename T>
size_t size(T& s){
    return sizeof(*s);
};
template <typename T>
size_t size(T& s, size_t si){
    return size(s) * si ;
};
template <typename T>
size_t size(T& s, auto& offset){
    offset = size(s);
};


template <typename T>
inline void ld(T& f, std::ifstream* fi){ // One
    fi->read(reinterpret_cast<char*>(&f), sizeof(f));
};
template <typename T>
inline void ld(T& f, size_t s,std::ifstream* fi){ // Arr
    f = new T[s];
    fi->read(reinterpret_cast<char*>(&f),sizeof(f[0])*s);
};
template <typename T>
inline void ld( T& f,size_t start ,size_t Offset, std::ifstream* fi){ //  OffOne
    fi->seekg(start + offset);
    ld(f,fi);
};

template <typename T>
inline void ld( T& f,size_t start ,size_t Offset,size_t si, std::ifstream* fi){ // OffArr
    fi->seekg(start + offset);
    ld(f,fi,si);
};
template <typename T>
inline void ld( T& f,size_t start ,size_t Offsize , size_t* Offset,size_t si, std::ifstream* fi){ // OffMany
    for(int i = 0 ; i < Offsize ;i++){
        fi->seekg(start + Offset[i]);
        ld(&(f[i]),fi,si);
    };
};

template <typename T>
inline void wr(T& f, size_t s, std::ofstream* fi){
    fi->write(reinterpret_cast<char*>(f),sizeof(f[0])*s);
};
template <typename T>
inline void wr(T& f, std::ofstream* fi){
    fi->write(reinterpret_cast<char*>(f), sizeof(f));
};



template <typename T>
inline void wr(T& f,pos_t start ,pos_t Offset, std::ofstream* fi){
    fi->seekp(start + offset);
    wr(f,fi);
};
template <typename T>
inline void wr(T& f,pos_t start ,pos_t Offset,size_t si, std::ofstream* fi){
    fi->seekp(start + offset);
    wr(f,si,fi);
};
template <typename T>
inline void wr( T& f,auto& start ,size_t Offsize , auto* Offset, std::ofstream* fi){
    for(int i = 0 ; i < Offsize ;i++){
        fi->seekp(start + Offset[i]);
        wr(&(f[i]),si,fi);
    };
};



#define ACQRES(type) \
strstruct acqresb_##type : acqres_base {}; \
struct acqres_##type_ld : acqresSize , acqresb_##type {} ; \
struct acqres_##type_wr : acqresLd , acqresb_##type {}; \
struct acqres_##type_si : acqresWr , acqresb_##type {}; \
void acqresb_##type::function()

#define USE_ACQRES(type) \
template <> ld(std::ifstream& fi){acqres_##type_ld obj(fi);obj.func();} \
template <> wr(std::ofstream& fi){acqres_##type_wr obj(fi);obj.func();} \
template <> size(){acqres_##type_ld obj;obj.func();} \


struct acqres_base {
    //  template <typename A>
    // void set (auto* Start);
    // template <typename A>
    // void one (A& g) ;
    // template <typename A>
    // void arr (A& g,size_t size);
    // template <typename A>
    // void offone (A& g,  auto& Offset );
    // template <typename A>
    // void offarr (A& g, auto& Offset,size_t size); 
    // template <typename A>
    // void offmany (A& g, auto& OFfset, size_t size);
    void init(){};
    void function();

}






    
struct acqresSize : acqres_base  {
    size_t ss = 0;    
    size_t s = 0;
    void* Set ;
    template <typename A>
    void set (auto* Start){Set =  Start;ss=s;};
    template <typename A>
    void one (A& g) {s+=size(g); };
    template <typename A>
    void arr (A& g,size_t size) {for(int i = 0 ; i < size ; i++){s+= size(g[i]);};};
    template <typename A>
    void offone (A& g,  auto& Offset ) {
        size_t curs=size(g);
        if(Set)Offset = s-ss;
        else Offset = s;
        s+= curs;
    };
    template <typename A>
    void offarr (A& g, auto& Offset,size_t size) {
        size_t curs = s;
        for(int i = 0 ; i < size ; i++){
            curs += size(g[i]);
        };
        if(Set )Offset= s -ss ;
        else Offset= s ;
        s+=curs;
    }; 
    template <typename A>
    void offmany (A& g, auto& OFfset, size_t size){
        for(int i=0;i<size;i++){soffone(g[i],Offset[i]);}
    };
    void init(){ss=0;s=0;};
    void func(){function();};

    
};


struct acqresLd : acqres_base{
    std::ifstream& fi;
     size_t size ;    size_t start ; 
        template <typename A>
        void one(A& g) {ld(g,fi) };
        template <typename A>
        void arr(A& g,auto& size) {ld(g,size,fi) ;};
        template <typename A>
        void offone (A& g,auto& offset, auto& s){ld<A>(g,start,offset,s,fi);}
        template <typename A*>
        void offarr (A g,auto& offset, auto& s){ld(g,start,offset,s,fi) ;};
        template <typename A* ,typename B*>
        void offmany (A* g,B* Offset, size_t s ){
            if(!g){g = new A[s];}
            for(int i=0;i<s;i++){ldOffone(g[i],Offset[i]);}
        }
        template <typename A>
        void set (A& set){};
        void init(){size =0; start = fi->seekg();}
        void func(){function();} ;
        acqresLd(std::ifstream& f){fi=f;}
}

struct acqresWr : acqres_base{
        std::ofstream& fi;
    size_t start ;
        template <typename A>
        void set(A& g){};
        template <typename A>
       auto one (A& g,) {wr(g,fi) };
        template <typename A,typename S>
        auto arr (A& g,S& size) {wr(g,size,fi) ;};
       template <typename A>
       auto offone (A& g,auto& offset,auto& s =1){wr<A>(g,start,offset,s,fi);}
       template <typename A*>
       auto offarr(A* g,auto& offset, auto& s=1){wr<A>(g,start,offset,s,fi) ;};
       template <typename A*,typename B*>
       void offmany(A* g,B* Offset, auto& s ){
            for(int i=0;i<s;i++){wrOffone(g[i],Offset[i]);}
       }
       template<typename A>
       void wrset (A& g ){}; 
    void init(){size(f) ;start = fi->seekp();} 
    void func(){function();}
    acqresWr(std::ofstream& f){fi=f;}

}



#endif