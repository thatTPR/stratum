#ifndef REFLECT_HPP
#define REFLECT_HPP
#include <stratum/sgui/strata/nodes_editor.hpp>
#include <type_traits>
#include <map>
#include <pair>
#include <tuple>

namespace pri {

namespace reflect { 
    


    #define REFLIT_SYS friend itreflect ; itreflect reflsys ;
    #define REFLNAME_SYS friend itnamerefl ; itnamerefl reflsys;
    #define REFLTY_SYS friend ittyrefl ; ittyrefl reflsys ;


    #define REFL_CLASS(name,macro)
  
    template <typename... type>
    class refliterator {
        std::tuple<type*...> iters;
        size_t cur=0;
        decltype(*std::get<cur>(iters)) operator*(){
            return *(std::get<cur>(iters)) ;
        };
        decltype(*this) operator++(){cur++;}
        decltype(*this) operator--(){cur--;}

        decltype(*this) operator++(int){++cur;}
        decltype(*this) operator--(int){--cur;}


        bool operator bool(){
            if(cur>= std::tuple_size(iters)){return false;}
            else return true;
        }
        refliterator(type*... ts) : iters(ts...) {};  
        refliterator(size_t _s, type*... ts) : iters(ts...){s=_s;} ;
    };
    template <typename meta, class...type>
    class namedrefliterator : refliterator<type...> {
        std::vector<meta> ms;
        std::pair<decltype(*std::get<cur>(iters)),std::string> operator*(){
            return std::pair<decltype(*std::get<cur>(iters)), meta>(*(std::get<cur>(iters)), ms[cur]) ;
        };

    };
    template < class...type>
    using namedrefliter = namedrefliterator<std::string,type...> ;
    template < class...type>
    using typednamerefliter = namedrefliterator<std::pair<std::string,std::string>,type...> ;
    

#define REFL_START(name)  \
 #define MEMBER_MACRO_LIST \
 #define MEBER_TYPES   \
 #define MEMBERNO 0


        // #define REFL_USING(var , value) var = value;

        #define REFL_DECL( type,name,value) type name = value ;\
        #define MEMBER_PTRS MEMBER_MACRO_LIST , &name  \
        #define MEMBER_TYPES MEMBER_TYPES , type  \
        #define MEMBERNO + 1
        // reflsys.add<type>(&(this->name),sign,#type,#name) ;

        

        #define REFL_END(name) \
        public:\
        using refliter = refliterator<MEMBER_TYPES> ;\
        using namedreflit = namedrefliter<MEMBER_TYPES> ;\
        using typednamed = typednamerefliter<MEMBER_TYPES>; \
        refliter begin(){return refliter(MEMBER_PTRS);} \
        refliter end(){ refliter(MEMBERNO,MEMBER_PTRS)+;}\
        refliter namedbegin(){return refliter(MEMBER_PTRS);} \
        refliter namedend(){ refliter(MEMBERNO,MEMBER_PTRS)+;}\
        refliter typednamedbegin(){return refliter(MEMBER_PTRS);} \
        refliter typednamedend(){ refliter(MEMBERNO,MEMBER_PTRS)+;}\

        template <typename reflected>
        reflected::namedreflit namediter(reflected& refl){refl.namedbegin();}
        template <typename reflected>
        reflected::typednamed typednamediter(reflected& refl){refl.typednamedbegin();}
   
};
}
#endif