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

template <typename T>
void NULLt();

template <typename T, 
template <typename> typename One  ,
template <typename> typename Arr  ,
template <typename> typename OffOne  ,
template <typename> typename OffArr  ,
template <typename> typename OffMany  >
size_t acqresf(T& f, size_t* s, FOne one ,FArr arr,FOffOne offone,FOffArr offarr,FOffMany Offmany  ) ;

// Function
// 
/*

#define ACQRES(type)\
void acqresf_##type \
(type* f,std::function<void(auto type::*) one ,
std::function<void(auto type::*, auto size) arr,
std::function<void(auto type::* , auto offset) offone,
std::function<void(auto type::*, auto offset, auto size) offarr,
std::function<void(auto type::*, auto offset, auto size, auto* offset) offmany)

template <typename T,
std::function<void(T,std::function<void(auto type::*)  ,
std::function<void(auto type::*, auto size) ,
std::function<void(auto type::* , auto offset) ,
std::function<void(auto type::*, auto offset, auto size) ,
std::function<void(auto type::*, auto offset, auto size, auto* offset) )>>
struct acqres {

};
*/

template <typename T>
void acqres(T f,std::function<void(T)> one,std::function<void(T,size_t)> arr,std::function<void(T,)>offone,offarr,offmany,set)

#define ACQRES(type)\
template <  \
template <typename> typename FOne , \
template <typename> typename FArr , \
template <typename> typename FOffOne , \
template <typename> typename FOffArr , \
template < typename> typename FOffMany,\
template <typename> typename FSet > \
void acqresf_##type \
(type f, FOne one ,FArr arr,FOffOne offone,FOffArr offarr ,FOffMany, FSet set) 
    /*
    
       return 
       Func(&(f->sizeMember)) ;
        Func(&(f->memberTwo),f->sizeMember);
        OffF(&(f->memberThree),f->offset);
        OffF(&(f->memberArr),sizeMember,f->offset) 
        ; 
        
    };
  
*/
/*
template <template <typename> typename Func>\
size_t acqres<Type,Func>(Type* f);
*/






    size_t size(auto& s){return sizeof(s);};

    
    
    template< typename T,
template <
template < template <typename> typename FOne , 
template < template <typename> typename FArr , 
template < template <typename> typename FOffOne , 
template < template <typename> typename FOffArr , 
template < template <typename> typename FOffMany,
template <template <typename> typename set> typename Function>
     size_t sizeacqres(Function fn,T& f){
        size_t ss = 0;    
    size_t s = 0;
    auto* Set ;
    auto sset = [&s,&ss,&Set]<typename A>(auto* Start){Set =  Start;ss=s;};
    auto sone = [&s]<typename A>(A& g) {s+=size(g); };
    auto sarr = [&s]<typename A>(A& g,size_t size) {for(int i = 0 ; i < size ; i++){s+= size(g[i]);};};
    
    auto soffone = [&s,&offset]<typename A>(A& g,  auto& Offset ) {
        size_t curs=size(g);
        if(Set)Offset = s-ss;
        else Offset = s;
        s+= curs;
    };
    auto soffarr = [&s,&offset]<typename A>(A& g, auto& Offset,size_t size) {
        size_t curs = s;
        for(int i = 0 ; i < size ; i++){
            curs += size(g[i]);
        };
        if(Set )Offset= s -ss ;
        else Offset= s ;
        s+=curs;
    }; 
       
    auto soffmany = [&s,&offset]<typename A>(A& g, auto& OFfset, size_t size){
        for(int i=0;i<size;i++){soffone(g[i],Offset[i]);}
    };
        fn(f,sone,sarr,soffone,soffarr,soffmany,sset);
        return s;
    }

    

    template< typename T,
    template <
    template < template <typename> typename FOne , 
    template < template <typename> typename FArr , 
    template < template <typename> typename FOffOne , 
    template < template <typename> typename FOffArr , 
    template < template <typename> typename FOffMany,
template <template <typename> typename set> typename Function>
void ldacqres(Function fn,T& f, std::ifstream* fi){
    size_t size =0;

        size_t start = fi->seekg();
        auto ldone = [&fi]<typename A>(A& g) {ld(g,fi) };
        auto ldarr = [&fi]<typename A>(A& g,auto& size) {ld(g,size,fi) ;};
        auto ldOffone = [&fi,&start]<typename A>(A& g,auto& offset, auto& s){ld<A>(g,start,offset,s,fi);}
        auto ldOffarr = [&fi,&start]<typename A*>(A g,auto& offset, auto& s){ld(g,start,offset,s,fi) ;};
        auto lfOffMany = [&fi,&start]<typename A*,typename B*>(A* g,B* Offset, size_t s ){
            if(!g){g = new A[s];}
            for(int i=0;i<s;i++){ldOffone(g[i],Offset[i]);}
        }
        auto ldset = [&fi,&start]<typename A>(A& set){};
        fn(f,ldone,ldarr,ldOffone,ldOffarr,ldOffmany,ldset) ;
    };

   
    template< typename T,
    template <
    template < template <typename> typename FOne , 
    template < template <typename> typename FArr , 
template < template <typename> typename FOffOne , 
template < template <typename> typename FOffArr , 
template < template <typename> typename FOffMany,
template <template <typename> typename set> typename Function>
void wracqres(Function fn,T& f, std::ofstream* fi){
       size_t start ;
       size(f) ;
       start = fi->seekp();
       auto wrset = []<typename A>(A& g){};
       auto wrone = [&fi]<typename A>(A& g,) {wr(g,fi) };
       auto wrarr = [&fi]<typename A,typename S>(A& g,S& size) {wr(g,size,fi) ;};
       auto wrOffone = [&fi,&start]<typename A>(A& g,auto& offset,auto& s =1){wr<A>(g,start,offset,s,fi);}
       auto wrOffarr = [&fi,&start]<typename A*>(A* g,auto& offset, auto& s=1){wr<A>(g,start,offset,s,fi) ;};
       auto wrOffmany =[&fi,&start]<typename A*,typename B*>(A* g,B* Offset, auto& s ){
            for(int i=0;i<s;i++){wrOffone(g[i],Offset[i]);}
       }
       auto wrset = [&fi,&start]<typename A>(A& g ){}; 
        fn(f,wrone,wrarr,wrOffone,wrOffarr,wrOffmany,wrset) ;
    };
    
    




#define MEMBER_ACQRES(type) \
void ld(type* f, std::ifstream* fi){acqres<type,acqresf_##type>::ld<type>(f,fi);}; \
void ld(type* f, std::ifstream* fi,size_t s){acqres<type,acqresf_##type>::ld<type>(f,fi,s);}; \
void wr(type* f,std::ofstream* fi){acqres<type,acqresf_##type>::wr<type>(f,fi);}; \
void size(type* f){acqres<type,acqresf_##type>::size<type>(f);}; 


#define USE_ACQRES(type) \
acqres<type,acqresf_##type> acqres_##type; \
template <>void ld<type>(type* f,std::ifstream fi){ ldacqres(acqresf_##type,f,fi);}; \
template <>void wr<type>(type* f,std::ofstream fi){ wracqres(acqresf_##type,f,fi);}; \
template <>size_t size<type>(type* f){return sizeacqres(acqresf_##type,f);};


template <typename T>
struct data ;
template <typename T >
data<T> build(T& t );
template <typename T>
T parse(data<T>* );

#endif