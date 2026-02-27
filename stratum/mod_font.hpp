#ifndef MOD_FONT_HPP
#define MOD_FONT_HPP


#include <pair>
#include <stratum/acqres/fontft.hpp>
#include <uchar.h>
#include <string>
#include "mod_util.hpp"
#include "mod_model.hpp"
#include "mod_paint.hpp"
namespace mod {
memoryPool<ttf::font> fontPool;

template <typename T>
    struct contour : std::vector<T> {
        T& operator[](int s){
            int h = s%size();
            return h<0?data()[size()+s]:s ;}
};
template <typename charT>
struct glyfEdit ;
template <typename charT,bool bm>
struct glyfPrim ;




template <typename charT>
struct glyfEdit;

template <typename charT>
struct fontColor {
    
    struct indexE {
        int s;
        size_t num;
    };  
    struct layerE {
        size_t posTup;
        size_t posVec;
        
        layerE(bool h,int _posTup,int _posVec) :layer(h), posTup(_posTup),posVec(_posVec){}
    
        layerE(int _posTup,int _posVec) : posTup(_posTup),posVec(_posVec){layer=false;}
    };
    struct compose{
        layerE src;
        layerE b;
        font::COMPOSITE_MODE mode ;
        compose(layerE& _src,layerE& _b,font::COMPOSITE_MODE m ) : src(_src),b(_b),mode(m){}
        compose(font::COMPOSITE_MODE m ) :mode(m){}
    };

struct SubGlyph {
    glyfEdit<charT>* subglyf; 
    uint16_t gid;
    fontColSubGlyph(uint16_t gi) : gid(gi){};
};
struct ColGlyph {
    glyfEdit<charT>* subglyf; 
    uint16_t gid;
    layerE lyr;
    fontColSubGlyph(uint16_t gi) : gid(gi){};
    fontColSubGlyph(uint16_t gi,layerE _ly) : gid(gi) ,lyr(ly){};
};


    struct paintGlyph {

    };
    template <typename... Paints>
    using tyt = pri::utuple<std::vector<Paints>...> ;
    
    struct subGlyph {
        glyfEdit<charT>* subGlyf;
    };
    using tytup = tyt<SubGlyph,ColGlyph,
compose,paint::solid,paint::var<paint::solid>,
    paint::gradientLinear,paint::var<paint::gradientLinear>,
    paint::gradientSweep, paint::var<paint::gradientSweep>,
    paint::gradientRadial, paint::var<paint::gradientRadial>,
    paint::Affine, paint::var<paint::Affine>,
    paint::rotate, paint::var<paint::rotate>,
    paint::skew, paint::var<paint::skew>,
    paint::rotateAroundCenter, paint::var<paint::rotateAroundCenter>,
    paint::skewAroundCenter, paint::var<paint::skewAroundCenter>,
    paint::translate, paint::var<paint::translate>> ;

    // std::vector<SubGlyph> subglyph;
    // std::vector<ColGlyph> colglyph;
    // std::vector<compose> composePnts;
    
    
    std::vector<layerE> index;
    
    std::vector<indexE> layers; 
    

    tytup tupvec;


fontColor(ttf::colorFT& r){*this = r.get();}
 fontColor(ttf::glyfft& r){*this = r.colors.get();}   
};
template <typename charT>
struct glyfEdit {
    charT c ;
    std::vector<contour<glm::ivec2>> contours;
    std::vector<contour<bool>> onCurve;
    uint16 glyphID;
    ttf::coord pos;
    int16   xMin;
    int16   yMin;
    int16   xMax;
    int16   yMax;
    fontColor colors;
    void set(ttf::glyfft& f){
                size_t endPl = 0;
        for(size_t i=0;i<f.numberOfContours;i++){
            contours.push_back(std::vector<glm::ivec2>(f.endPts[i]-endPl+1));
            onCurve.push_back(std::vector<glm::ivec2>(f.endPts[i]-endPl+1);
            for(size_t j = endPl;j<=f.endPts[i];j++){contours.back()[j-endPl]=f.contours[j]; onCurve.bacl()[j-endPl] = f.onCurve[j];}
            endPl=f.endPts[i] + 1;
        };
        colors = fontColor(f)
    }
    glyfEdit(ttf::glyfft& f){
        glyphID = f.glyphID;
        pos = f.pos;
        xMin = f.xMin;
        yMin = f.yMin;
        xMax = f.xMax;
        yMax = f.yMax;set(f);
    };
};


memoryPool<glyfEdit<char>> glyfEditPool;
memoryPool<glyfEdit<wchar_t>> wglyfEditPool;
memoryPool<glyfEdit<char32_t>> c32glyfEditPool;

template <typename charT>
struct fontBm {
    struct bmPrim {
    uint16 glyphID;
    coord pos;
    int16   xMin;
    int16   yMin;
    int16   xMax;
    int16   yMax;
    glm::uvec4 color;
    float alpha ;
        image2D bm;
    };

        font::options opts ;
std::basic_string<charT> text;
    std::vector<bmPrim> prims; 

    void push(font::glyfbm f){
        image2D im(f.width,f.height, image_formats::rgba16ui);
        std::memcpy(im.data,f.bitmap,im.byd * im.imageSize);
        
        bmPrim r{f.glyphID,f.pos,f.xMin,f.yMin,f.xMax,f.yMax,f.color,f.alpha,im} ;

        prims.push_back(r);
    };
    ttf::font* f;

    template <typename charTy>
    using vectype = ttf::font::bvectype<charTy> ;

    void loadAll(ttf::font* f){
        loadAllBm()
    };
    fontBm(ttf::font* _f) : f(_f) {}
};

template <typename charT>
struct fontPrim {
    struct options {
        bool color;
        bool kerning;
        bool curve;
    };
    options opts ;
    std::basic_string<charT> text;
    struct ftPrim {
        struct vert {
            using prty = mod::topology_primitive_vec<DIM::bi,TopologyPrimitive::POINT_LIST,false>; 
            glm::ivec2 pos;
            int   xMin;
            int   yMin;
            int   xMax;
            int   yMax;
            uint onCurveMax;
            uint maxSizeCon;
            uint numCon;
            uint numOnCurves;
            uint s;
            prty::ty* mprim;

            size_t operator sizeof(){return sizeof(uint)*4 +sizeof(int)* + sizeof(s) + sizeof(prty::ty)*s;}
        };

        struct fragSimple {
            glm::vec4 fg;
            glm::vec4 bg;
        }
        using frag = fontColor ;
        vert v;
        uint* endPts;
        uint* OnCurve;
        frag f;
    };
    std::vector<ftPrim> ftprims;
///@region:PrimGen
    void VertProc(ttf::glyfft&  f,ftPrim& r){
        size_t off=0;
        size_t numOnc = 0;
        for(size_t s=0;s<f.sizeContour,s++){
            if(f.onCurve[s]){numOnc++;}
        };
        ftPrim::vert::prty g(f.sizeContour+f.numberOfCountours+numOnc); 
        size_t endPtInd=0;size_t sizeConMax=0;size_t sizeCon=0;size_t OnCurveMax=0;size_t OnCurveN=0;
        size_t numOnCurves=0;
        std::vector<uint> endPtsVec;
        std::vector<uint> onCurveVec;
        for(size_t s=0;s<f.sizeContour,s++){
            sizeCon++;
            if(f.onCurve[s] ){OnCurveN++;
                onCurveVec.push_back(s);
                g[s] =glm::vec2(f.contours[s].x,f.contours[s].y);}
            if(f.endPts[endPtInd]==s){
                OnCurveMax=OnCurveN>onCurveMax? OnCurveN>onCurveMax ;numOnCurves+=OnCurveN;OnCurveN =0;
                endPtsVec.push_back(s);
                endPtInd++;if(sizeCon>=sizeConMax){sizeConMax=sizeCon+1;}
                sizeCon=0;
            }
        };

        r.v.onCurveMax= OnCurveMax; 
        r.v.maxSizeCon=sizeConMax;
        r.v.numCon = f.numberOfContours;
        r.v.numOnCurves= numOnCurves;
        r.v.s = g.size() ;
        r.v.mprim = g.data();
        r.OnCurve = new uint[onCurveVec.size()];
        r.OnCurve = onCurveVec.data();
        r.endPts = new uint[endPtsVec.size()];
        r.OnCurve = endPtsVec.data();
    };
    void FragProc(ttf::glyfft& f,ftPrim& r){
        return;
    } ;
    void Proc(ttf::glyfft& f,ftPrim& r){
        VertProc(f,r);
        FragProc(f,r);
    }
    
/// @endregion:PrimGen

    void push(font::glyfft& f){
        ftPrim::vert s = Proc(f,r);
        ftprims.push_back(s);
    };
    
    glm::ivec2 size;
    ttf::font* f;

    std::basic_string<charT> text;
    // template <typename charTy>
    // void getf(){
    //     // using ty = font::vectype<charTy>::type ;
    //     // ty font::* fontPtr = font::vectype<charTy>::ptr;
    //     // ty s = f->*fontPtr;
    
    // };
    // template <>void getf<char>();
    // template <>void getf<wchar_t>();
    // template <>void getf<char32_t>();

    void get(){
         for(const charT c : text ){
            font::glyfft r = f->get(c,opts);
            push(r);
        };
    } ;


    void insert(size_t pos, std::basic_string<charT> _text){text.insert(_text,pos);};
    void multiInsert(std::vector<size_t> poss,    std::basic_string<charT> _text){
        for(size_t p : poss){insert(p,_text);};
    };

    decltype(*this) operator[](charT c){
        return ftprims[c];
    };

    template <typename charTy>
    using vectype = ttf::font::vectype<charTy> ;


    fontPrim(ttf::font* _f) : f(_f) {}
    fontPrim(ttf::font* _f, ttf::ftrange<charT>& r) : f(_f) {
        text.clear();
        text.resize(r.size);
        text[0] = r.start;
        ftprims.clear();
            push(r.range[0]);
        for(size_t s = 1; s<r.size;s++){
            text[s] = text[s-1] + 1;
            push(r.range[s]);
        }
    }
}


struct fontProc : mod::shaderModule{
    
};
template <typename charT , template <typename charTy> typename fPrimT >
struct fontPool {
    font* f;
    using type= fPrimT<charT>;
    
struct rangeE {
    charT first;
    size_t num;
    rangeE(charT f,size_t n) : first(f) , num(_n) {}

};

     std::vector<type> ranges;

    std::vector<rangeE> index;


    type& get(charT c){
        size_t ind = 0;
        for(const rangeE& it : index){
            if(c>=it.first){
                if( c-it.first < it.num) {
                    return ranges[ind][c-it.first] ;
                };
            }
            ind++;}
    };
    type& operator[](charT c){return get(c);}


    template <typename charTy>
    using vectype = fPrimT<charTy>::vectype ;

    struct iterator {
        size_t indexPt;
        size_t pt;
        iterator& operator++(){
            if(pt<index[indexPt].num -1){++pt;}
            else {++indexPt;pt=0;}
            return *this;
        };
        iterator& operator--(){
            if(pt>0){--pt;}
            else {--indexPt;pt=index[indexPt].num-1;}
            return *this;
        };
        iterator& operator++(int){
            if(pt<index[indexPt].num -1){pt++;}
            else {indexPt++;pt=0;}
            return *this;
        };
        iterator& operator--(int){
            if(pt>0){pt--;}
            else {indexPt--;pt=index[indexPt].num-1;}
            return *this;
        };
        bool operator==(iterator& r){return indexPt == r.indexPt and (r.pt==pt);};
        bool operator!=(iterator& r){return !(operator==(r));};
        operator bool(){
            return cond
        }
        fPrimT<charT>& operator*(){return ranges[index[indexPt]][pt];        };
        iterator(size_t ind,size_t _pt): indexPt(ind) , pt(_pt){}
    };
    void begin(){return iterator(0,0);}
    void end(){return iterator(index.size()-1,index[index.size()-1].num); }

    void rbegin(){return iterator(index.size()-1,index[index.size()-1].num-1);}
    void rend(){return iterator(0,size_t(0) - 1); }
    

    void front(){return *begin();}
    void back(){return *rbegin();}

    void loadAll(ttf::font* f){
        vectype<charT>::type vecs = f->*(vectype<charT>::ptr) ; 
        for(const auto& it : vecs){
            fPrimT<charT> r(f,it);
            ranges.push_back(ranges);
            index.push_back(it.start,it.size);
        };
    };  
    fontPool(ttf::font* _f) : f(_f) {};
};

template <typename charT>
using ftPrim = fontPool<charT,fontPrim> ;

template <typename charT>
using bmPrim = fontPool<charT,fontBm> ;


template <template <typename charT> typename T>
struct primFull {

    T<char> c_prim;
    T<wchar_t> wc_prim;
    T<char32_t> c32_prim;

    primFull(font* f){
        if(f->floaded){
            c_prim = T<char>(f); 
            wc_prim = T<wchar_t>(f); 
            c32_prim = T<char32_t>(f); 
            c_prim.loadAll(f);
            wc_prim.loadAll(f);
            c32_prim.loadAll(f);
        };
    };

}

using ftprimFull = primFull<ftPrim> ;
using bmprimFull = bmimFull<bmPprim> ;

struct PrimFull {
    bmprimFull bms;
    ftprimFull fts; 

    // void makeAllBm(){
    //     bmprimFull res;
    //     for(ftprimFull::type& it  : fts){

    //     };
    // }

    PrimFull(ttf::font* f){
        bms = bmprimFull(f);
        fts = ftprimFull(f);
    }
};


memoryPool<ftprimFull> ftPrimPool;
memoryPool<bmprimFull> ftPrimPool;

template <typename charT,tempate <typename charTy> typename fnPrim>
struct PrimText  {
    std::basic_string<charT> text;

    fnPrim<charT>* font;
    std::vector<fnPrim::type> textPrims;
    ftPrimText(std::basic_string<charT> _text,fnPrim<charT>* _font) : text(_text),font(_font){
        for(const charT& c : text){
            font->get(c).push_back(textPrims);
        };
    };
};

template <typename charT>
using ftPrimText = PrimText<charT,ftPrim>;

template <typename charT>
using bmPrimText = PrimText<charT,bmPrim>;




}
#endif