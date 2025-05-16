#ifndef ACQRES_HPP
#define ACQRES_HPP
// #include <type_traits>
// template <typename T, size_t si>
// void ld(T* s,std::ifstream* fi){
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

template <typename T>
size_t size(T* s){
    return sizeof(*s);
};
template <typename T>
size_t size(T* s, size_t si){
    return size(s) * si ;
};

template <typename T>
inline void ld(T* f, std::ifstream* fi){ // One
    fi->read(reinterpret_cast<char*>(f), sizeof(*f));
};
template <typename T>
inline void ld(T* f, size_t s,std::ifstream* fi){ // Arr
    *f = new T[s];
    fi->read(reinterpret_cast<char*>(f),sizeof(*f[0])*s);
};
template <typename T>
inline void ld( T* f,pos_t start ,pos_t Offset, std::ifstream* fi){ //  OffOne
    fi->seekg(start + offset);
    ld(f,fi);
};

template <typename T>
inline void ld( T* f,pos_t start ,pos_t Offset,size_t si, std::ifstream* fi){ // OffArr
    fi->seekg(start + offset);
    ld(f,fi,si);
};
template <typename T>
inline void ld( T* f,pos_t start ,size_t Offsize , pos_t* Offset,size_t si, std::ifstream* fi){ // OffMany
    for(int i = 0 ; i < Offsize ;i++){
        fi->seekg(start + Offset[i]);
        ld(&(f[i]),fi,si);
    };
};

template <typename T>
inline void wr(T* f, size_t s, std::ofstream* fi){
    fi->write(reinterpret_cast<char*>(f),sizeof(*f[0])*s);
};
template <typename T>
inline void wr(T* f, std::ofstream* fi){
    fi->write(reinterpret_cast<char*>(f), sizeof(*f));
};



template <typename T>
inline void wr(T* f,pos_t start ,pos_t Offset, std::ofstream* fi){
    fi->seekp(start + offset);
    wr(f,fi);
};
template <typename T>
inline void wr(T* f,pos_t start ,pos_t Offset,size_t si, std::ofstream* fi){
    fi->seekp(start + offset);
    wr(f,si,fi);
};
template <typename T>
inline void wr( T* f,auto& start ,size_t Offsize , auto* Offset, std::ofstream* fi){
    for(int i = 0 ; i < Offsize ;i++){
        fi->seekp(start + Offset[i]);
        wr(&(f[i]),si,fi);
    };
};

template <typename T>
void NULLt();

template <typename T, 
template <typename> typename One  ,
template <typename> typename Arr  ,
template <typename> typename OffOne  ,
template <typename> typename OffArr  ,
template <typename> typename OffMany  >
size_t acqresf(T* f, size_t* s, FOne one ,FArr arr,FOffOne offone,FOffArr offarr,FOffMany Offmany  ) ;

// Function
// 

#define ACQRES(type)\
template <  \
template <typename> typename FOne , \
template <typename> typename FArr , \
template <typename> typename FOffOne , \
template <typename> typename FOffArr , \
template <typename> typename FOffMany > \
void acqresf_##type \
(type f, size_t* s,FOne one ,FArr arr,FOffOne offone,FOffArr offarr,FOffMany offmany  ) \
    /*
    
       return 
       Func(&(f->sizeMember)) +
        Func(&(f->memberTwo),f->sizeMember)+
        OffF(&(f->memberThree),f->offset);
        OffF(&(f->memberArr),sizeMember,f->offset) 
        ; 
        
    };
  
*/
/*
template <template <typename> typename Func>\
size_t acqres<Type,Func>(Type* f);
*/

template< typename T,
template <
template < template <typename> typename FOne , 
template < template <typename> typename FArr , 
template < template <typename> typename FOffOne , 
template < template <typename> typename FOffArr , 
template < template <typename> typename FOffMany > typename Function>
struct acqres{    
    template<> size_t size<T>(T* s){
        size_t s = 0;
        std::vector<auto*> offset;
        auto one = [&s]<typename A>(A* g,) {s+=size(g); };
        auto arr = [&s]<typename A>(A* g,size_t size) {
            for(int i = 0 ; i < size ; i++){
                s+= size(g[i]);};
            };
        };
        auto offone = [&s,&offset]<typename A>(A* g, auto& start, auto& Offset  ) {
            size_t curs=size(g);
            Offset = curs;
            s+= size(Offset);offset.push_back(&Offset);
        };
        auto offarr = [&s,&offset]<typename A>(A* g,auto& start, auto& Offset,size_t size) {
            size_t curs = 0;
            for(int i = 0 ; i < size ; i++){
                curs += size(g[i]);
            };
            Offset= curs ;
            s+=size(Offset);
            offset.push_back(&Offset);

        }; 
        
            
        auto offmany = [&s,&offset]<typename A>(A* g,auto& start, size_t Offsize, auto* Offset) {
            for(int i = 0 ; i<Offsize ; i++){
                size_t curs = size(g);
                Offset[i]=curs;
                s+=size(Offset);
                offset.push_back(&(Offset[i]));
            };
        }

         Function(s,one,arr,offone,offarr,offmany);
         size_t tot = s; 
         for(int i = 0 ; i < offset.length() - 1 ; i++  ){
            
            *offset[i]+=tot - *offset[i]; 
            tot += *offset[i] ; 
        };
        return tot ;
   
    };
    

    template<> void ld<T>(T* f, std::ifstream* fi){
        size_t size =0;
        pos_t start = fi->seekg();
        auto one = [&fi]<typename A>(A* g,) {ld(g,fi) };
        auto arr = [&fi]<typename A>(A* g,size_t size) {ld(g,size,fi) ;};
        auto Offone = [&fi,&start]<typename A>(A* g,pos_t offset, size_t s =1){ld<A>(g,start,offset,s,fi);return 1;}
        auto Offarr = [&fi,&start]<typename A>(A* g,pos_t offset, size_t s=1){ld(g,start,offset,s,fi) ;};
        auto Offmany = [&fi,&start]<typename A>(A* g,pos_t Offsize,pos_t* Offset, size_t s=1){ld(g,start,Offsize,offset,s,fi) ;};
        Function(f,one,arr,Offone,Offarr,Offmany) ;
    };

    template<> void ld<T>(T* f, std::ifstream* fi, size_t s){
        f = new T[s];
        for(int i = 0 ; i < s ;i++){
            ld(&(f[i]),fi) ;
        };
    };
   
    template<> void wr<T>(T* f, std::ofstream* fi){
        size(f) ;
        size_t start = fi->seekp();
        auto one = [&fi]<typename A>(A* g,) {wr(g,fi) };
        auto arr = [&fi]<typename A>(A* g,size_t size) {wr(g,size,fi) ;};
        auto Offone = [&fi,&start]<typename A>(A* g,pos_t offset, size_t s =1){wr<A>(g,start,offset,s,fi);return 1;}
        auto Offarr = [&fi,&start]<typename A>(A* g,pos_t offset, size_t s=1){wr<A>(g,start,offset,s,fi) ;};
        auto Offmany = [&fi,&start]<typename A>(A* g,pos_t Offsize,pos_t* Offset, size_t s=1){wr(g,start,Offsize,offset,s,fi) ;};
        Function(f,one,arr,Offone,Offarr,Offmany) ;
    };
    
    template<> void wr<T>(T* f, std::ofstream* fi , size_t s){
        for(int i = 0 ; i < s ;i++){
            wr(&(f[i]),fi);
        };
    };   
};





#define USE_ACQRES(type) \
using acqres<type,acqresf_##type>::ld<type>; \
using acqres<type,acqresf_##type>::wr<type>; \
using acqres<type,acqresf_##type>::size<type>;


template <typename T>
struct data ;
template <typename T >
data<T> build(T* t );
template <typename T>
T parse(data<T>* );

#endif