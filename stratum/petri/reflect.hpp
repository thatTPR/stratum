namespace reflect {

    template <typename T>
    struct fullrefl{
        T* ptr; 
        std::string type ;
        std::string name ;
        auto* prev ; 
        auto* next ;
        size_t cmp(fullrefl& lhs, fullrefl& rhs){
            if(lhs.type<rhs.type) {return 2;};
            if(lhs.type>rhs.type) {return -2;};
            if(lhs.type==rhs.type){
                if(lhs.name<rhs.name){return 1;};
                if(lhs.name>rhs.name){return -1;};
                if(lhs.name==rhs.name){return 0;};
            }
        };
        tynamenname(T* _ptr,std::string _type,std::string _name) : ptr(_ptr) , type(_type) , name(_name) ;
    };
    template <typename T>
    struct namerefl{
        T* ptr; std::string name; 
    } ;
    template <typename T>
    struct tyrefl {
        T* ptr ;
        std::string type ;
    } ;
    template <typename Member=fullrefl>
    class itreflect {
        public:
        using iterator = mapit; 
        
        std::string name ;
        fullrefl<itreflect<fullrefl>(this,"itreflect","reflsys")> self;


        auto* startPtr = &(this->self);
        auto* endPtr = &(this->self);
        void* ptr  = &(this->self);
        bool init = true ; 
        template <typename T>
        static constexpr void add(T* ptr){
            
        };
        
        auto& begin(){return *(this->startPtr);} ;
        auto& end(){return   *(this->endPtr) ;} ; 
        
        itreflect operator++(){return this->ptr; }
        
    };

    class itnamerefl : public itreflect<namerefl> ;
    class ittyrefl : public itreflect<tyrefl> ;
    
    class reflectable  {
        itreflect reflsys ; 

        template <typename T>
        void decl(){

        } ;
        auto getbyname(std::string name){
            for(const auto& it : this){

            };
        };
        std::string gettype(std::string name){
            for(const auto& it : this){

            };
        };

    };

    #define ITREFL_STRUCT_DEF(name)\
     struct name : public reflactable { \ 
       
        
        void getByName(std::string name){}
        

    #define ITREFL_STRUCT_END( name) \ }; 
    
    #define ITTYREFL_STRUCT_DEF_START(name)
    #define ITTYREFL_STRUCT_DEF_END(name)
    
    #define ITTY_STRUCT_DEF_START(name) struct { 
        #define ITTY_STRUCT_DEF_END( name) }name; 
        
        
        
        #define MEMBER_DECL(type,name) type name  ; 
        #define ITREFL_FUNC(funcptrtype , name) funcptrtpye   ;
        

    #define TPYE_REFLECT(type) #type ; 
    #define TYPE_REFLECT_MEMBER(type, name) 
    #define REFLECT_MEMBER(type, name)

};