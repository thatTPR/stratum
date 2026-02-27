#ifndef PTR_TEMPLATES
#define PTR_TEMPLATES
#include <type_traits>
#include <stratum/petri/tuple.hpp>
template <typename T,typename...Ts>
constexpr size_t sizeOf(){return sizeof(T)+sizeOf<Ts...>();}
template <typename T>
constexpr size_t sizeOf(){return sizeof(T);}

#include <cstring>
namespace pri {

    /*
    template <typename T>
    struct CleverEnumType {
        using ty = void ;// Must Implement;

    } ;

    #define CEVAL_DEFc constexpr
    #define CEVAL_DEFe constexpr
    template <typename T, T... es>
    struct CleverEnum {
        static CEVAL_DEFc T arr[] = {es...};
        struct iter {
            constexpr size_t si = s;
            constexpr T& operator*(){return arr[si];}
            constexpr iter<s+1> operator++(){++si;}
            constexpr iter<s-1> operator--(){--si;}
            iter() = default;
        };
        constexpr iter<0>& begin(){return iter<0>();}
        constexpr iter<sizeof...(es)>& end(){return iter<sizeof...(es)>();}


    };


    #define CENUM_START(name,t) \
    #define CENUM_START_T t
    #define CENUM_NAME name
    #define CENUM_STACK\
    enum name {\

        #define ENUM_MEM(name) name ,\
        #define CENUM_STACK CENUM_STACK,name
        
        #define ENUM_MEMEQ(name,val) name=val,\
        #define CENUM_STACK CENUM_STACK,name



    #define END_CENUM COUNT\
    };\
    static constexpr CleverEnum<CENUM_START_T,CENUM_STACK> CENUM_NAME##clever;

    */


        template <typename T,T a,Ts... args>
        bool OneOf(T l){
            if(l==a){return true;}
            if constexpr (sizeof...(args)>0){return OneOf<args...>(l);}
            return false;
        };
    
template <size_t N>
struct Str {
    std::array<char, N> data;

    constexpr Str(const char (&s)[N]) {
        std::copy_n(s, N, data.begin());
    }

    static std::string str()  { return std::string(data.data()); }
};



template <Str h>
struct CEStr {
    std::string str(){return h.str();}
};

    template <typename T>
    void memcpy(T* dest,T* src,size_t s){std::memcpy(dest,src,s*sizeof(T));}

    template <typename T>
    int memcmp(T* dest,T* src,size_t s){std::memcmp(dest,src,sizeof(T));}


template <bool& b , pri::Str s,pri::Str... syns >
struct opt {
    std::string str(){return s.str();}
    virtual void operator++(int);
    bool check(int& i,int argc,char* argv[]){
        if(s==std::string(argv[i])){b=true ; return true;}
        else if constexpr (sizeof...(syns)>0){return opt<syns>().check(str);}
        return false;
    };
};




template <typename eq,eq& e,pri::Str s,pri::Str... syns>
struct opeq{
eq operator[](std::string& str){return proc_tlit<eq>(str);};
eq operator[](std::string&& str){return proc_tlit<eq>(str);};
    virtual void operator<<(eq es){e =es; }
    bool check(int& i, int argc, char* argv[]){
        size_t p  =s.str().find(std::string(argv[i]));
        if( p==0){
            if (s.str().size()==(std::string(argv[i]).size())) {i++;(*this)<<(*this)[argv[i]];return true;}
            else if(s.str()[std::string(argv[i]).size()] == '=' ){p=1;}
        (*this)<<(*this)[s.str().substr(std::string(argv[i]).size() + p)] ;return true;
        }
        else if constexpr (sizeof...(syns)>0){return opeq<syns...>().check(i,argc,argv);}
        return false;
    };
    bool check(int& i,int argc,char* argv[]){
        size_t p  =s.str().find(std::string(argv[i]));
        if(s.str().find(std::string(i,argc,argv))!=std::string::npos){return true;}
        else if constexpr (sizeof...(syns)>0){return opeq<syns...>().check(i,argc,argv);}
        return false;
    };
};


template <class t,class... ts>
struct eqts {
    template <t& r,ts&... refs>
    struct refer : eqts<ts...>::refer<refs...> {
        using ty = t;
        static constexpr t& ref= r;
        virtual void operator<<(t _r){ref=_r;}
        using eqts<ts...>::refer<refs...>::operator<<;
    };
    
};
template <class eqsrefs,pri::Str s,pri::Str... syns>
struct opeqs  : eqsrefs, opeq<eqsref::ty, eqsref::ref,s,syns> {
    using eqsrefs::operator<< ;
};


    template < template <size_t > typename T,size_t s>
struct Tcase {
    static bool operator()(size_t is){
        if(is==s){T<is>();return true;}
        else {Tcase<T,sS...>()}
    };
};


template < template <size_t > typename T>
struct Tcase {
    static bool operator()(size_t is){
        if(is==s){T<is>();return true;}
        else {return false;}
    };
};




    template <typename T, typename A , typename... Ts>
    struct is_one_of {static  constexpr bool value = std::is_same<T,A>::value || is_one_of<T,Ts...>::value ; };
   
     template <typename T ,template <typename As,typename... Tss>typename Template,typename A,typename...Ts>
    constexpr bool is_one_of(Template<A,Ts...> r){return is_one_of<T,A,Ts...>::value;};

    

    template <typename T, typename A>
    struct is_one_of<T,A> {static  constexpr bool value = std::is_same<T,A>::value; };
    template <typename T, T val, T vone,T... vals> 
    struct eqs_one_of{
        static constexpr bool value = (val == vone) || eqs_one_of<T,val,vals...>::value ;
    };
    template <typename T, T val, T vone> 
    struct eqs_one_of<T,val,vone>{
        static constexpr bool value = (val == vone) ;
    };

    template <typename T, T val, T vone,T... vals> 
    struct eqs_all_of{
        static constexpr bool value = (val == vone) && eqs_one_of<T,val,vals...>::value ;
    };
    template <typename T, T val, T vone> 
    struct eqs_all_of<T,val,vone>{
        static constexpr bool value = (val == vone) ;
    };
    


template <typename... T>
struct EnumTs{
    static constexpr size_t size = sizeof...(T);
    using tup = pri::tuple<T...>;

    template <typename T,typename tupleEmpty,size_t s>
    constexpr size_t get(){
        return s;
    }
    template <typename T,typename subTup,size_t s>
    constexpr size_t get(){
        if constexpr(std::is_same<T,subTup::headt>::value){return s;}
        else return get<T,subTup::tailt,s+1>()
    }

    template <typename T>
    constexpr size_t get(){
        if constexpr(std::is_same<T,tup::headt>::value){return s;}
        else return get<T,tup::tailt,1>();
    }


    template <size_t s,typename A,typename... B>
    struct gett{
        using type =typename  std::conditional<s==0,A,gett<s-1,B...>>::type;
    }
    template <size_t s>
    gett<s,T...>::type get(tup& t){
        return get<gett<s,T...>::type>(t);
    };

};
 
template <typename Arg,template <typename> typename func,typename tp,typename... tps>
        bool BoolFunc(Arg& arg){
            if(func<tp>(arg)){return true;}
            else{return BoolFunc<Arg,func,tps...>(arg);}
        };

    // template <typename... S>
    // using cases_type = pri::tuple<S...> ; 
    // template <typename casesTy ,casesTy val,bool Bool,bool... Booleans>
    // struct sw_type {
    //     casesTy valueTy = v ;

    // };
}
#endif