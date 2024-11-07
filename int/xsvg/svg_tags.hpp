#pragma once
#include <stdlib.h>
#include <string>
#include <vector>
#include <type_traits>
#include <cwctype>
#include "../format.hpp"
#include "xsvg_types.hpp"



template <  typename T  , parser parser_type , typename string_type   >
class irtg_svg_{
    

     typedef enum {
        SVG_LINE,
        SVG_TRIANGLE,
        SVG_SQUARE,
        SVG_RECT,
        SVG_CIRCLE,
        SVG_ELLIPSE,
        SVG_PATH,
        SVG_TEXT
    }POLY_PRIM ; 
    typedef enum {
        SVG_SVG,
        SVG_G,
    }GROUPS;
    typedef enum {

    }TRANSFORM_PRIM;
    typedef enum {

    }ANIM_PRIM;

class _elem {
    public:
    static const std::vector<_elem*> elems ;
    static const std::vector<_attrib*> attribs ; // Acceptable attributes
    static const value_type_variant<>
    // Read ; 
    virtual void operator[](size_t pos , string_type& str_ref ) ;
    // Write
    virtual void operator[](string_type& str_ref, size_t pos ) ; 
    
};
    static const std::vector<string_type , _elem> elem_map;  // Forward declaration

    
template <  bool animatable , typename def_t , typename... value_t >
    class _attrib {
        public:
        string_type = name ; 
        static const std::vector<_elem*> elems ;
        static const std::vector<_attrib*> attribs ; // Acceptable attributes
        
        using t_var = value_t_variant_t<def_t , value_t...> ; 
        using variant  = t_var::variant ;
        using type = t_var::type ;
        static const type value_def ; 
        static const bool anim = animatable  ;
        // Read ; 
        virtual void operator[](size_t pos , string_type& str_ref ) ;
        // Write
        virtual void operator[](string_type& str_ref, size_t pos ) ; 
        virutual _attrib(def_t val) : value_def(val) {};
    };
    static const std::vector<string_type> attrib_map
    struct index {
        std::vector<size_t> elem_index ;  
        std::vector<size_t> elem_pos ; 

        // std::vector<_elem> .... ;
        // or std::vector<>

        std::vector<size_t> attrib_index ;
        std::vector<size_t> attrib_pos ;

        // std::vector<_attrib> ... ; 

        std::vector<size_t>  ref_elem_index ;
        std::vector<size_t>  ref_elem_pos ;
    };
    using ind = struct index ;
    
#include "svg_tags_elems.hpp"
#include "svg_tags_attribs.hpp"
};