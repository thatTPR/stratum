
class elems {
   
#include "svg_tags_elems.defs"

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
    std::vector<string_type> attribs = {"d", "pathLength"};
    std::vector<string_type> elems ={};
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
        _elem* elem_p_vec[] = {&_a, &_clipPath, &_cursor, &_filter, &_font, &_font&_face, &_foreignObject, &_image, &_marker, &_mask, &_pattern, &_script, &_style, &_switch, &_text, &_view} ; // One Instance of each element accepted 
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

// // Elements
