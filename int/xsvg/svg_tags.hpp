#pragma once
#include <stdlib.h>
#include <string>
#include <vector>
#include <type_traits>
#include <cwctype>
#include "../format.hpp"


template <  typename T  , parser parser_type  >
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
template <typename type , typename T , typename string_type>
class _elem {
    public:
    static const std::vector<string_type> elems ;
    static const std::vector<string_type> attribs ; // Acceptable attributes
    // Read ; 
    virtual void operator[](size_t pos , string_type& str_ref ) ;
    // Write
    virtual void operator[](string_type& str_ref, size_t pos ) ; 
    
};
 template <typename type  , typename T , typename string_type>
    class _attrib {
        public:
        static const std::vector<string_type> elems ;
        static const std::vector<string_type> attribs ; // Acceptable attributes
        // Read ; 
        virtual void operator[](size_t pos , string_type& str_ref ) ;
        // Write
        virtual void operator[](string_type& str_ref, size_t pos ) ; 
    };
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
    

class elems {
   

/** @} */

// Elements


std::vector<size_t> _elem ; 
// <a> [ ]
class _a_ : _elem {
    using _elem:: ; 
    elem_p_vec[] = {}
};
// <animate> [ ]
// <animateMotion> [ ]
// <animateTransform> [ ]
// <circle> [ ]
// <clipPath> [ ]
// <cursor> Deprecated [ ]
// <defs> [ ]
// <desc> [ ]
// <ellipse> [ ]
// <feBlend> [ ]
// <feColorMatrix> [ ]
// <feComponentTransfer> [ ]
// <feComposite> [ ]
// <feConvolveMatrix> [ ]
// <feDiffuseLighting> [ ]
// <feDisplacementMap> [ ]
// <feDistantLight> [ ]
// <feDropShadow> [ ]
// <feFlood> [ ]
// <feFuncA> [ ]
// <feFuncB> [ ]
// <feFuncG> [ ]
// <feFuncR> [ ]
// <feGaussianBlur> [ ]
// <feImage> [ ]
// <feMerge> [ ]
// <feMergeNode> [ ]
// <feMorphology> [ ]
// <feOffset> [ ]
// <fePointLight> [ ]
// <feSpecularLighting> [ ]
// <feSpotLight> [ ]
// <feTile> [ ]
// <feTurbulence> [ ]
// <filter> [ ]
// <font-face-format> Deprecated [ ]
// <font-face-name> Deprecated [ ]
// <font-face-src> Deprecated [ ]
// <font-face-uri> Deprecated [ ]
// <font-face> Deprecated [ ]
class _font_face_{};
// <font> Deprecated [ ]
// <foreignObject> [ ]
// <g> [ ]
// <glyph> Deprecated [ ]
// <glyphRef> Deprecated [ ]
// <hkern> Deprecated [ ]
// <image> [ ]
// <line> [ ]
// <linearGradient> [ ]
// <marker> [ ]
// <mask> [ ]
// <metadata> [ ]
// <missing-glyph> Deprecated [ ]
// <mpath> [ ]
// <path> [ ]
class _path_ : elem{
    using _elem:: ;
    elem_p_vec  = {} ;
    attrib_p_vec = {&_d , &_path_length};
};
std::vector<_path_> _path ; 
// <pattern> [ ]
// <polygon> [ ]
// <polyline> [ ]
// <radialGradient> [ ]
// <rect> [ ]
// <script> [ ]
// <set> [ ]
// <s_top> [ ]
// <style> [ ]
// <svg> [ ]
class _svg_ {
        elems::_elem* elem_p_vec[] = {&_a, &_clipPath, &_cursor, &_filter, &_font, &_font&_face, &_foreignObject, &_image, &_marker, &_mask, &_pattern, &_script, &_style, &_switch, &_text, &_view} ; // One Instance of each element accepted 
        attribs::_attrib* attrib_p_vec[]={&_baseProfile, &_height, &_preserveAspectRatio, &_version, &_viewBox, &_width, &_x, &_y}; 
};
std::vector<_svg_> _svg ; 
// <switch> [ ]
// <symbol> [ ]
// <text> [ ]
// <textPath> [ ]
// <title> — the SVG accessible name element  [ ]
// <tref> Deprecated [ ]
// <tspan> [ ]
// <use> [ ]
// <view> [ ]
// <vkern> Deprecated [ ]
};
struct index {

};
/**
 *  Attribute // [ ]s
 *  @{
 */


class attribs {
// accent-height Deprecated // [ ]
// accumulate   // [ ]
// additive // [ ]
// alignment-baseline   // [ ]
// alphabetic Deprecated    // [ ]
// amplitude    // [ ]
// arabic-form Deprecated   // [ ]
// ascent Deprecated    // [ ]
// AttributeName // // [ ]
// AttributeType Deprecated  // [ ]
// azimuth  // [ ]
// baseFrequency    // [ ]
// baseline-shift   // [ ]
// baseProfile Deprecated   // [ ]
// bbox Deprecated  // [ ]
// begin    // [ ]
// bias // [ ]
// by   // [ ]
// calcMode // [ ]
// cap-height Deprecated    // [ ]
// class    // [ ]
// clip Deprecated  // [ ]
// clip-path    // [ ]
// clip-rule    // [ ]
// clipPathUnits    // [ ]
// color    // [ ]
// color-interpolation  // [ ]
// color-interpolation-filters  // [ ]
// cursor   // [ ]
// cx   // [ ]
// cy   // [ ]
// d Attribute // [x] 
/** 
 * @brief d attrib
 * capital abs , lower dx,dy
 * Move_to: M, m
 * Line_to: L, l, H, h, V, v
 * Cubic Bézier curve: C, c, S, s
 * Quadratic Bézier curve: Q, q, T, t
 * Elliptical arc curve: A, a
 * ClosePath: Z, z
 * @{
 */


class _d_ : elems::elem{
    
    template <typename T>
    struct d_prim{
        std::vector<T> pts ; // some pts are one dimensional so just numbers
                                       //      ind size             
        std::vector<size_t> move_to_M; //       0  2
        std::vector<size_t> move_to_m; //       1  2 
        std::vector<size_t> line_to_L; //       2  2 
        std::vector<size_t> line_to_l; //       3  2
        std::vector<size_t> line_to_H; //       4  1    
        std::vector<size_t> line_to_h; //       5  1   
        std::vector<size_t> line_to_V; //       6  1 
        std::vector<size_t> line_to_v; //       7  1  
        std::vector<size_t> cubic_bez_C; //     8  6 
        std::vector<size_t> cubic_bez_c; //     9  6
        std::vector<size_t> cubic_bez_S; //     10 4
        std::vector<size_t> cubic_bez_s; //     11 4
        std::vector<size_t> quad_bez_Q; //      12 4
        std::vector<size_t> quad_bez_q; //      13 4
        std::vector<size_t> quad_bez_T; //      14 2
        std::vector<size_t> quad_bez_t; //      15 2
        std::vector<size_t> elliptical_arc_A; //16 7
        std::vector<size_t> elliptical_arc_a; //17 7
        bool close_path ;
       // Close path is last element
        // same size :
        std::vector<size_t> index_i; // index of each point , 
        std::vector<size_t> index_pt; // pos in respective index indexed by index_i
        
    } ;
    
    d_prim<T> data;
  
    class _dAttribBase   {
        public:
        d_prim<T> d; 
        std::vector<T>* pts ;
        std::vector<size_t>* index_i ; // Index of each no
        std::vector<size_t>* index_pt;  // pos in respective index
        size_t s  ;
        virtual void operator[](std::string& str, size_t& pos , std::vector<size_t>* where, size_t numbers, size_t where_ind){
            pos++ ; T no = 0 ;      
            size_t n_no = 0 ;      
            do {
                if(iswdigit(str[pos])){
                    no = no*10 + (str[pos] - '0') ;
                    continue ;
                };
                if(str[pos]=='.'){
                    int digit_ord = 1; 
                        pos++ ;
                    while(iswdigit(str[pos])){
                        no = no*10 + (str[pos] - '0'); digit_ord=10*digit_ord;
                    };
                    no = no / digit_ord; 
                    size_t s = this->pts->size() ;
                
                        n_no++ ;
                       this->pts->push_back(no);
                        if(n_no ==1){ // This could work without as well but differently
                            where->push_back(s);
                            this->index_pt->push_back(this->index_i->size() );
                            this->index_i->push_back(where_ind);
                        };
                        if(n_no == numbers){n_no = 0;};
                    
                    no=0;
                    continue ;
                };
                pos++ ; 
            }while(!iswalpha(str[pos]) );  
            
        }; 
        _dAttribBase(_d& d_ref):d(*d_ref.data), pts(*d_ref.data.pts) index_i(*d_ref.data.index_i)  , index_pt(*d_ref.data.index_pt) {}; 
    };
    class move_to {
        // Everything after correspondent Line_to
        static const char _M = "M" ; // (x,y)+ L
        static const char _m = "m" ; // (dx,dy) + l
        s = 2 ;
        using _dAttribBase:: ;
    };
    move_to _move_to(*this) ; 
    class line_to {
        static const char _L = "L"; // (x, y)+
        static const char _l = "l"; // (dx, dy)+
        static const char _H = "H"; // (x)+
        static const char _h = "h"; // (dx)+
        static const char _V = "V"; // (y)+
        static const char _v = "v"; // (dy)+
        
        using _dAttribBase:: ;
    };
    line_to _line_to(*this) ; 
    class cubic_bez {
        static const char _C  "C"; // (x1,y1, x2,y2, x,y)+
        static const char _c  "c"; //(dx1,dy1, dx2,dy2, dx,dy)+
        static const char _S  "S"; // (x2,y2, x,y)+
        static const char _s  "s"; // (dx2,dy2, dx,dy)+
        using _dAttribBase:: ;
    };
    cubic_bez _cubic_bez(*this) ;
    class quad_bez {
            static const char _Q = "Q" ; //  (x1,y1, x,y)+
            static const char _q = "q" ; // (dx1,dy1, dx,dy)
            static const char _T = "T" ; // (x,y)+
            static const char _t = "t" ; // (dx,dy)+
        using _dAttribBase:: ;
    };
    quad_bez _quad_bez(*this);
    class elliptical_arc {
        /** angle in degrees
        *  large-arc-flag allows a choice of large arc (1) or small arc (0),
        *  sweep-flag allows a choice of a clockwise arc (1) or counterclockwise arc (0)
        */
        static const char _A = "A";   //(rx ry angle large-arc-flag sweep-flag x y)+
        static const char _a = "a";   //(rx ry angle large-arc-flag sweep-flag dx dy)+
        using _dAttribBase:: ;
    };
    elliptical_arc _elliptical_arc(*this);
    class close_path {
        static const char _Z = "Z";
        static const char _z = "z"; 
       void operator[](){};
    };
    close_path _close_path(*this) ; 
    d_prim<T>& match_parse(std::string& ref, size_t& pos){
        while (ref[pos]!="\""){

            switch(c){
                case move_to::_M       :{_move_to[ref       , pos , this->data.move_to_M       ,2, 0]; break;};//0 2 
                case move_to::_m       :{_move_to[ref       , pos , this->data.move_to_m       ,2, 1]; break;};//1 2 
                case line_to::_L       :{_line_to[ref       , pos , this->data.line_to_L       ,2, 2]; break;};//2 2 
                case line_to::_l       :{_line_to[ref       , pos , this->data.line_to_l       ,2, 3]; break;};//3 2 
                case line_to::_H       :{_line_to[ref       , pos , this->data.line_to_H       ,1, 4]; break;};//4 1 
                case line_to::_h       :{_line_to[ref       , pos , this->data.line_to_h       ,1, 5]; break;};//5 1 
                case line_to::_V       :{_line_to[ref       , pos , this->data.line_to_V       ,1, 6]; break;};//6 1 
                case line_to::_v       :{_line_to[ref       , pos , this->data.line_to_v       ,1, 7]; break;};//7 1 
                case cubic_bez::_C     :{_cubic_bez[ref     , pos , this->data.cubic_bez_C     ,6, 8]; break;};//8 6 
                case cubic_bez::_c     :{_cubic_bez[ref     , pos , this->data.cubic_bez_c     ,6, 9]; break;};//9 6 
                case cubic_bez::_S     :{_cubic_bez[ref     , pos , this->data.cubic_bez_S     ,4, 10]; break;};//10 4
                case cubic_bez::_s     :{_cubic_bez[ref     , pos , this->data.cubic_bez_s     ,4, 11]; break;};//11 4
                case quadBez::_Q       :{_quadBez[ref       , pos , this->data.quadBez_Q       ,4, 12]; break;};//12 4
                case quadBez::_q       :{_quadBez[ref       , pos , this->data.quadBez_q       ,4, 13]; break;};//13 4
                case quadBez::_T       :{_quadBez[ref       , pos , this->data.quadBez_T       ,2, 14]; break;};//14 2
                case quadBez::_t       :{_quadBez[ref       , pos , this->data.quadBez_t       ,2, 15]; break;};//15 2
                case elliptical_arc::_A:{_elliptical_arc[ref, pos , this->data.elliptical_arc_A,7, 16]; break;};//16 7
                case elliptical_arc::_a:{_elliptical_arc[ref, pos , this->data.elliptical_arc_a,7, 17]; break;};//17 7
                case closePath::_Z     :{this->data.close_path  = true ; break;};//18 0
                case closePath::_z     :{this->data.close_path  = true ; break;};//19 0
            };

        };
        pos++ ;
        return this->data; 
    };
    // enum _d_error {
    //     index_size_difference,
    //      index_incorrect
    // };
    //  check_correct(){
    //     // TODO
    // };
    // Read
    _d_ operator[](size_t pos ,std::string& s){

    };
    // Write
    void operator[](std::string& s, size_t pos){
        for(const T : this->data.pts){

        };
    };
    _d_ operator<<(std::string& s);
   
    _d_() = default ;
  


};
std::vector<_d_> _d ;
std::vector<size_t> _d_ind  ; // points to _elem_ind
// data-* Attribute // [ ]
// decoding Attribute // [ ]
// descent Deprecated Attribute // [ ]
// diffuseConstant Attribute // [ ]
// direction Attribute // [ ]
// display Attribute // [ ]
// divisor Attribute // [ ]
// dominant-baseline Attribute // [ ]
// dur Attribute // [ ]
// dx Attribute // [ ]
// dy Attribute // [ ]
// edgeMode Attribute // [ ]
// elevation Attribute // [ ]
// end Attribute // [ ]
// exponent Attribute // [ ]
// fill Attribute // [ ]
// fill-opacity Attribute // [ ]
// fill-rule Attribute // [ ]
// filter Attribute // [ ]
// filterUnits Attribute // [ ]
// flood-color Attribute // [ ]
// flood-opacity Attribute // [ ]
// font-family Attribute // [ ]
// font-size Attribute // [ ]
// font-size-adjust Attribute // [ ]
// font-stretch Attribute // [ ]
// font-style Attribute // [ ]
// font-variant Attribute // [ ]
// font-weight Attribute // [ ]
// fr Attribute // [ ]
// from Attribute // [ ]
// fx Attribute // [ ]
// fy Attribute // [ ]
// g1 Deprecated Attribute // [ ]
// g2 Deprecated Attribute // [ ]
// glyph-name Deprecated Attribute // [ ]
// glyph-orientation-horizontal Deprecated Attribute // [ ]
// glyph-orientation-vertical Deprecated Attribute // [ ]
// gradientTransform Attribute // [ ]
// gradientUnits Attribute // [ ]
// hanging Deprecated Attribute // [ ]
// height Attribute // [ ]
// horiz-adv-x Deprecated Attribute // [ ]
// horiz-origin-x Deprecated Attribute // [ ]
// horiz-origin-y Deprecated Attribute // [ ]
// href Attribute // [ ]
// id Attribute // [ ]
// ideographic Deprecated Attribute // [ ]
// image-rendering Attribute // [ ]
// in Attribute // [ ]
// in2 Attribute // [ ]
// intercept Attribute // [ ]
// k Deprecated Attribute // [ ]
// k1 Attribute // [ ]
// k2 Attribute // [ ]
// k3 Attribute // [ ]
// k4 Attribute // [ ]
// kernelMatrix Attribute // [ ]
// kernelUnitLength Attribute // [ ]
// keyPoints Attribute // [ ]
// keySplines Attribute // [ ]
// keyTimes Attribute // [ ]
// lang Attribute // [ ]
// lengthAdjust Attribute // [ ]
// letter-spacing Attribute // [ ]
// lighting-color Attribute // [ ]
// limitingConeAngle Attribute // [ ]
// marker-end Attribute // [ ]
// marker-mid Attribute // [ ]
// marker-start Attribute // [ ]
// markerHeight Attribute // [ ]
// markerUnits Attribute // [ ]
// markerWidth Attribute // [ ]
// mask Attribute // [ ]
// maskContentUnits Attribute // [ ]
// maskUnits Attribute // [ ]
// mathematical Deprecated Attribute // [ ]
// max Attribute // [ ]
// media Attribute // [ ]
// methodExperimental Attribute // [ ]
// min Attribute // [ ]
// mode Attribute // [ ]
// name Deprecated Attribute // [ ]
// numOctaves Attribute // [ ]
// opacity Attribute // [ ]
// opera_tor Attribute // [ ]
// order Attribute // [ ]
// orient Attribute // [ ]
// orientation Deprecated Attribute // [ ]
// origin Attribute // [ ]
// overflow Attribute // [ ]
// overline-position Attribute // [ ]
// overline-thickness Attribute // [ ]
// paint-order Attribute // [ ]
// panose-1 Deprecated Attribute // [ ]
// path Attribute // [ ]
// pathLength Attribute // [ ]
// patternContentUnits Attribute // [ ]
// patternTransform Attribute // [ ]
// patternUnits Attribute // [ ]
// pointer-events Attribute // [ ]
// points Attribute // [ ]
// pointsAtX Attribute // [ ]
// pointsAtY Attribute // [ ]
// pointsAtZ Attribute // [ ]
// preserveAlpha Attribute // [ ]
// preserveAspectRatio Attribute // [ ]
// primitiveUnits Attribute // [ ]
// r Attribute // [ ]
// radius Attribute // [ ]
// refX Attribute // [ ]
// refY Attribute // [ ]
// repeatCount Attribute // [ ]
// repeatDur Attribute // [ ]
// requiredFeatures Deprecated Attribute // [ ]
// restart Attribute // [ ]
// result Attribute // [ ]
// rotateExperimental Attribute // [ ]
// rx Attribute // [ ]
// ry Attribute // [ ]
// scale Attribute // [ ]
// seed Attribute // [ ]
// shape-rendering Attribute // [ ]
// sideExperimental Attribute // [ ]
// slope Attribute // [ ]
// spacing Attribute // [ ]
// specularConstant Attribute // [ ]
// specularExponent Attribute // [ ]
// spreadMethod Attribute // [ ]
// star_toffset Attribute // [ ]
// stdDeviation Attribute // [ ]
// stemh Deprecated Attribute // [ ]
// stemv Deprecated Attribute // [ ]
// stitchTiles Attribute // [ ]
// s_top-color Attribute // [ ]
// s_top-opacity Attribute // [ ]
// strikethrough-position Attribute // [ ]
// strikethrough-thickness Attribute // [ ]
// string Deprecated Attribute // [ ]
// stroke Attribute // [ ]
// stroke-dasharray Attribute // [ ]
// stroke-dashoffset Attribute // [ ]
// stroke-linecap Attribute // [ ]
// stroke-linejoin Attribute // [ ]
// stroke-miterlimit Attribute // [ ]
// stroke-opacity Attribute // [ ]
// stroke-width Attribute // [ ]
// style Attribute // [ ]
// surfaceScale Attribute // [ ]
// SVG Attribute // [ ]: crossorigin Attribute // [ ]
// systemLanguage Attribute // [ ]
// tabindex Attribute // [ ]
// tableValues Attribute // [ ]
// target Attribute // [ ]
// targetX Attribute // [ ]
// targetY Attribute // [ ]
// text-anchor Attribute // [ ]
// text-decoration Attribute // [ ]
// text-rendering Attribute // [ ]
// textLength Attribute // [ ]
// _to Attribute // [ ]
// transform Attribute // [ ]
// transform-origin Attribute // [ ]
// type Attribute // [ ]
// u1 Deprecated Attribute // [ ]
// u2 Deprecated Attribute // [ ]
// underline-position Attribute // [ ]
// underline-thickness Attribute // [ ]
// unicode Deprecated Attribute // [ ]
// unicode-bidi Attribute // [ ]
// unicode-range Deprecated Attribute // [ ]
// units-per-em Deprecated Attribute // [ ]
// v-alphabetic Deprecated Attribute // [ ]
// v-hanging Deprecated Attribute // [ ]
// v-ideographic Deprecated Attribute // [ ]
// v-mathematical Deprecated Attribute // [ ]
// values Attribute // [ ]
// vec_tor-effect Attribute // [ ]
// version Deprecated Attribute // [ ]
// vert-adv-y Deprecated Attribute // [ ]
// vert-origin-x Deprecated Attribute // [ ]
// vert-origin-y Deprecated Attribute // [ ]
// viewBox Attribute // [ ]
// visibility Attribute // [ ]
// width Attribute // [ ]
// widths Deprecated Attribute // [ ]
// word-spacing Attribute // [ ]
// writing-mode Attribute // [ ]
// x Attribute // [ ]
// x-height Deprecated Attribute // [ ]
// x1 Attribute // [ ]
// x2 Attribute // [ ]
// xChannelSelec_tor Attribute // [ ]
// xlink:arcrole Deprecated Attribute // [ ]
// xlink:href Deprecated Attribute // [ ]
// xlink:show Deprecated Attribute // [ ]
// xlink:title Deprecated Attribute // [ ]
// xlink:type Deprecated Attribute // [ ]
// xml:lang Deprecated Attribute // [ ]
// xml:space Deprecated Attribute // [ ]
// y Attribute // [ ]
// y1 Attribute // [ ]
// y2 Attribute // [ ]
// yChannelSelec_tor Attribute // [ ]
// z Attribute // [ ]
// zoomAndPan Deprecated Attribute // [ ]


/** @} */

};