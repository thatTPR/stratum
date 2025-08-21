#ifndef REFLECT_HPP
#define REFLECT_HPP
#include <stratum/sgui/strata/nodes_editor.hpp>
#include <map>
namespace reflect { // TODO use map and list
    template <typename T>
   struct refl {
    T* ptr;
    std::string type ;
    std::string name ;
   };
    template <typename T>
    struct fullrefl : public refl {
        using ty = T ;
        T* ptr; 
         std::string type ;
         std::string name ;
        fullrefl(std::string _type,std::string _name,T* _ptr) : ptr(_ptr) , type(_type) , name(_name) ;
        fullrefl(T* _ptr,std::string _type,std::string _name) : ptr(_ptr) , type(_type) , name(_name) ;
        // fullrefl(T* _ptr,pinsig _ps, std::string _type,std::string _name) : ptr(_ptr) ,ps(_ps), type(_type) , name(_name), 
    };
    
    template <typename T>
    struct namerefl{
        T* ptr; 
         std::string name; 
    } ;
    template <typename T>
    struct tyrefl {
        auto* prev ; 
        auto* next ;
        T* ptr ;
        alignas(16) std::string type ;
    } ;
    template <template <typename T> Member = fullrefl>
    class itreflect {
        public:
        using iterator = mapit; 
        
        std::string name ;
        


        auto* startPtr = &(this->self);
        auto* endPtr = &(this->self);
        auto* ptr  = &(this->self);

        size_t size= 0 ; 
        


        template <typename T>
        static constexpr void add(T* ptr, std::string ref){
            Member<T> s(ptr,ref) ;s.prev = this->endptr;this->endptr.next=&s;this->endptr=s ; this->ptr=this->endPtr; 
        if(size==0){this->startPtr==this->endPtr};this->size++;
        };
        template <typename T>
        static constexpr void add(T* ptr, std::string type, std::string name){
            Member<T> s(ptr,type,name) ;   s.prev = this->endptr;this->endptr.next=&s;this->endptr=s ; this->ptr=this->endPtr; 
            if(size==0){this->startPtr==this->endPtr};this->size++;
        };
        template <typename T>
        static constexpr void add(T* ptr,pinsig ps, std::string type, std::string name){
            Member<T> s(ptr,ps,type,name) ;   s.prev = this->endptr;this->endptr.next=&s;this->endptr=s ; this->ptr=this->endPtr; 
            if(size==0){this->startPtr==this->endPtr};this->size++;

        };
        
        auto& begin(){return (this->startPtr);} ;
        auto& end(){return   (this->endPtr) ;} ; 
        
        *this operator++(){return this->ptr->next;};
        *this operator--(){return this->ptr->prev;};
        
        void apply_all(void(*fn)(auto)){
            for(const auto& it : *this){
                fn(it) ;
            };
        };

        auto getbyname(std::string name){
            for(const auto it : *this){
                if(it->name == name){return it;};
            };
        };
        std::vector<std::string> gettype(std::string name){
            std::vector<std::string> ret ;
            for(const auto& it : this){
                if(it->name == this->name){ret.push_back(it);};
            };
            return ret ;
        };

        template <typename... args>
        itreflect((Member<args>)... refls){
            for(const auto it : refls ){
                this->endPtr=&it ;
                this->ptr->next = this->endPtr; 
                this->endPtr->prev = this->ptr ;
                this->ptr = this->endPtr; 
            };
        } ;
    };
    class itnamerefl : public itreflect<namerefl> ;
    class ittyrefl : public itreflect<tyrefl> ;

    class itmapreflect : public itreflect<tyreflect> {
        public:
        std::map<std::string,tyreflect> m; 
        
        tyreflect operator[](std::string& a){

        };
        template <typename T>
        static constexpr void add(T* ptr, std::string ref){
            Member<T> s(ptr,ref) ;  s.prev = this->endptr;this->endptr.next=&s;this->endptr=s ; this->ptr=this->endPtr; 
        if(size==0){this->startPtr==this->endPtr};this->size++; m[ref] = s;
            
        };
        template <typename T>
        static constexpr void add(T* ptr, std::string type, std::string name){
            Member<T> s(ptr,type,name) ;   s.prev = this->endptr;this->endptr.next=&s;this->endptr=s ; this->ptr=this->endPtr; 
            if(size==0){this->startPtr==this->endPtr};this->size++;
        };
        template <typename T>
        static constexpr void add(T* ptr,pinsig ps, std::string type, std::string name){
            Member<T> s(ptr,ps,type,name) ;   s.prev = this->endptr;this->endptr.next=&s;this->endptr=s ; this->ptr=this->endPtr; 
            if(size==0){this->startPtr==this->endPtr};this->size++;

        };    } ;


    #define REFLIT_SYS friend itreflect ; itreflect reflsys ;
    #define REFLNAME_SYS friend itnamerefl ; itnamerefl reflsys;
    #define REFLTY_SYS friend ittyrefl ; ittyrefl reflsys ;


    class clss_refl {
        public:
        REFLIT_SYS
        
        public:
        auto& begin(){return this->reflsys.begin()};
        auto& end(){return this->reflsys.end();};
        *this operator++(){this->reflsys++;};
        *this operator--(){this->reflsys--;};
    };

    
    #define REFL_CLASS(name,macro)\
     class ##name_refl  : public clss_refl { \
        #define MEMBER_MACRO_LIST
        private: \
        macro \   
        public:  \
        class name  \
        { \
            public: \
        

    #define ITREFL_STRUCT_END(name,refltype) 
            ##name_refl(){reflsys= refltype(MEMBER_MACRO_LIST)}
}; \
            name strct ; \
            name& get(){return this->strct;};\ 

}; \

#define ITREFL_CLASS(name) REFL_CLASS(name,REFLIT_SYS) 
#define NAREFL_CLASS(name) REFL_CLASS(name,REFLNAME_SYS)
#define TYREFL_SYS(name) REFL_CLASS(name,REFLTY_SYS)



        // #define REFL_USING(var , value) var = value;

        #define REFL_DECL( type,name,value) type name = value ;\
        #define MEMBER_MACRO_LIST MEMBER_MACRO_LIST , {##type,##name,&name} 
        #define MEMBER_TYPES MEMBER_TYPES , type
        // reflsys.add<type>(&(this->name),sign,#type,#name) ;

        
        #define REFL_DECL( type,name,) type name ;\
        reflsys.add<type>(&(this->name),sign,#type,#name) ;



        #define REFL_DECL(name , value) type name = value ;\
        #define MEMBER_MACRO_LIST MEMBER_MACRO_LIST , {##type,##name,&name} 
        reflsys.add<type>(&(this->name),#type,#name) ;

        #define REFL_DECL(type,name) type name  ; \
        reflsys.add<type>(&(this->name),#type,#name) ;


   
};

#endif