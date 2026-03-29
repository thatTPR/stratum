#include "svg.hpp"
#include <math.h>
#include "../mod_font.hpp"
#include "../mod_font_extra.hpp"
#include "../mod_image.hpp"

#include <variant>
#include <vector>
#include <stexcept>
#include <templates.hpp>
#include <type_traits>
#include <utilty>
#define NSC std::


namespace svg{

struct svgPl {
    
    // template <typename T

    // template <typename... Ts>
    // using tuplevec = typename NSC tuple<std::vector<Ts>... > refs;

    // tuplevec<SVGARELS> refs;
    
    Number height;float pixWidth; // = / height
    Number width; float pixHeight;
    float UserSpaceUnits ;

    struct Vertex {
        glm::vec2 pt;
        uint32_t colr;

    };
    std::vector<Vertex> vs;

    struct range {size_t s, e;}

    std::vector<range> ranges;
    
        struct animMotion {
            dType pth; std::vector<range> rngs;
        };
        struct animTransform {
            transformmType:: type t;
            std::vector<float> from;
            std::vector<float> to;
            std::vector<range> ranges;
        };
        
    struct filt {
        struct feBlend {
            std::vector<range> in;
            std::vector<range> in2;
            blendMode::ty t;
            std::vector<range> ranges;
        };
        struct feBlend {};
        struct feColorMatrix {};
        struct feComponentTransfer {};
        struct feComposite {};
        struct feConvolveMatrix {};
        struct feDiffuseLighting {};
        struct feDisplacementMap {};
        struct feDropShadow {};
        struct feFlood {};
        struct feFuncA {};
        struct feFuncB {};
        struct feFuncG {};
        struct feFuncR {};
        struct feGaussianBlur {};
        struct feImage {};
        struct feMerge {};
        struct feMergeNode {};
        struct feMorphology {};
        struct feOffset {};
        struct feSpecularLighting {};
        struct feTile {};
        struct feTurbulence {};
        struct linearGradient {vec2 s,e;uint32_t colorS,uint32_t colorE;};
        struct radialGradient {
            glm::vec2 c ,f;float r,fr;spreadMetho::ty t;
            std::vector<range> ranges;
            radialGradient(radialGradient& r)
        };

        filt operator<<(std::vector<Vertex>& vr){};
        template <typename T>
        void push(T&& s){}
    void psh(feBlendVar& b,std::vector<range>& rng){push(feBlend(feBlendVar,rng));};
    void psh(feColorMatrixTag& b,std::vector<range>& rng){push(feColorMatrix(feColorMatrixTag,rng));};
    void psh(feComponentTransferTag& b,std::vector<range>& rng){push(feComponentTransfer(feComponentTransferTag,rng));};
    void psh(feCompositeTag& b,std::vector<range>& rng){push(feComposite(feCompositeTag,rng));};
    void psh(feConvolveMatrixTag& b,std::vector<range>& rng){push(feConvolveMatrix(feConvolveMatrixTag,rng));};
    void psh(feDiffuseLightingTag& b,std::vector<range>& rng){push(feDiffuseLighting(feDiffuseLightingTag,rng));};
    void psh(feDisplacementMapTag& b,std::vector<range>& rng){push(feDisplacementMap(feDisplacementMapTag,rng));};
    void psh(feDropShadowTag& b,std::vector<range>& rng){push(feDropShadow(feDropShadowTag,rng));};
    void psh(feFloodVar& b,std::vector<range>& rng){push(feFlood(feFloodVar,rng));};
    void psh(feFuncATag& b,std::vector<range>& rng){push(feFuncA(feFuncATag,rng));};
    void psh(feFuncBTag& b,std::vector<range>& rng){push(feFuncB(feFuncBTag,rng));};
    void psh(feFuncGTag& b,std::vector<range>& rng){push(feFuncG(feFuncGTag,rng));};
    void psh(feFuncRTag& b,std::vector<range>& rng){push(feFuncR(feFuncRTag,rng));};
    void psh(feGaussianBlurTag& b,std::vector<range>& rng){push(feGaussianBlur(feGaussianBlurTag,rng));};
    void psh(feImageTag& b,std::vector<range>& rng){push(feImage(feImageTag,rng));};
    void psh(feMergeTag& b,std::vector<range>& rng){push(feMerge(feMergeTag,rng));};
    void psh(feMergeNodeTag& b,std::vector<range>& rng){push(feMergeNode(feMergeNodeTag,rng));};
    void psh(feMorphologyTag& b,std::vector<range>& rng){push(feMorphology(feMorphologyTag,rng));};
    void psh(feOffsetTag& b,std::vector<range>& rng){push(feOffset(feOffsetTag,rng));};
    void psh(feSpecularLightingTag& b,std::vector<range>& rng){push(feSpecularLighting(feSpecularLightingTag,rng));};
    void psh(feTileTag& b,std::vector<range>& rng){push(feTile(feTileTag,rng));};
    void psh(feTurbulenceTag& b,std::vector<range>& rng){push(feTurbulence(feTurbulenceTag,rng));};
    void psh(radialGradientTag& b,std::vector<range>& rng){push(radialGradient(radialGradientTag,rng));};
    void psh(linearGradientTag& b,std::vector<range>& rng){push(linearGradient(linearGradientTag,rng));};
    void psh(radialGradientTag& b,std::vector<range>& rng){push(radialGradient(radialGradientTag,rng));};
    };





    struct values {
        Number strw ; 
        color fill ; 
        color stroke ; 
        uint8_t strokeA;
        uint8_t fillA;

        template <typename T>
        values(T& t)  {
        strokeA=  (uint8_t)(t.ats.getStr<"stroke-opacity">() * 0xFF);
        fillA =  (uint8_t)(t.ats.getStr<"fill-opacity">() * 0xFF);
        strw = t.ats.getStr<"stroke-width">(); 
        fill  =t.ats.getStr<"fill">();
        stroke  =t.ats.getStr<"stroke">();
        };
    };
    uint8_t colorSize = mod::bitd(image_formats::rgba8ui)/8;


    using pt = mod::image2D::pt;
    using line = mod::image2D::line;  
    

    uint32_t  timems;

    void rast(circleTag& t ){
        values v(*(t.r)) ;
        uint32_t fill = v.fill<<8 + v.fillA;
        uint32_t stroke = v.stroke<<8+v.strokeA;
  
        uint32_t size = t.dim.x*UserSpaceUnits;
 
        
        
        Number r= t.ats.getStr<"r">() ;
        Number cx= t.ats.getStr<"cx">() ;
        Number cy= t.ats.getStr<"cy">() ;
        float _cx = cx*UserSpaceUnits;
        float _cy = cy*UserSpaceUnits;
        float _r= r*UserSpaceUnits;

        t.im.circle(fill,stroke,strkw,_r,_cx,_cy);
        
    };
    void rast(ellipseTag& t ){
        values v(*(t.r)) ;
        uint32_t fill = v.fill<<8 + v.fillA;
        uint32_t stroke = v.stroke<<8+v.strokeA;
  
        uint32_t size = t.dim.x*UserSpaceUnits;
 
        
        
        Number rx= t.ats.getStr<"rx">() ;
        Number ry= t.ats.getStr<"ty">() ;
        Number cx= t.ats.getStr<"cx">() ;
        Number cy= t.ats.getStr<"cy">() ;

        float _cx = cx*UserSpaceUnits;
        float _cy = cy*UserSpaceUnits;
        float _rx= rx*UserSpaceUnits;
        float _ry= ry*UserSpaceUnits;

        t.im.ellipse(fill,stroke,strkw,_rx,_ry,_cx,_cy);
        
    };    
    void rast(lineTag& t ){
        uint32_t colr = t.ats.getStr<"color">()<<8 + ((uint8_t)(t.ats.getStr<"stroke-opacity">() * 0xFF)) ;
        float strw = t.ags.getStr<"stroke-width">();
        pt a{t.ats.getStr<"x1">(),t.ats.getStr<"y1">()};
        pt b{t.ats.getStr<"x2">(),t.ats.getStr<"y2">()};
        t.im.line(colr,strw,line(a,b));
    };
    mod::image2D& imRef;
    void rast_line(dType& t, uint32_t colr, float strkw,line l){imRef.line(colr,strkw,l)}
    void rast_quad(dType& t, bool fstart,uint32_t colr, float strkw,pt x, pt y ,pt z){imRef.quad(fstart,colr,strkw,x,y,z);}
    void rast_cubic(dType& t, bool fstart,uint32_t colr, float strkw,pt x,pt y ,pt z ,pt w){imRef.quad(fstart,colr,strkw,x,y,z,w);}
    void rast_arc(dType& t, uint32_t colr, float strkw,pt s,pt r, float angle , pt flag,pt xy){imRef.arc(colr,strkw,s,r,angle,flag,xy);;}

    
    void pathHandle(dType& t, uint32_t colr,float strw,
                    void (*line)(dType&,uint32_t colr, float strkw,line& l),
                    void (*quad)(dType&,bool fstart,uint32_t colr, float strkw, pt x, pt y ,pt z),
                    void (*cubic)(dType&,bool fstart,uint32_t colr, float strkw,pt x,pt y ,pt z ,pt w),
                    void (*arc)(dType&,uint32_t colr, float strkw ,pt s, pt r, foat angle , pt flag,pt xy) ){
     
        pt cur,c;
          for(size_t i=0;i<dt.offs.size();i++){
            switch(dt.t[i]){
                case dType::ty::M : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=2){cur.x=dt.p[j];cur.y=dt.p[j+1]; }; continue;};
                case dType::ty::m : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=2){cur.x+=dt.p[j];cur.y+=dt.p[j+1]; }; continue;};
                case dType::ty::L : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=2){ c=cur; cur.x=dt.p[j];cur.y=dt.p[j+1];   }; break;};
                case dType::ty::l : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=2){ c=cur; cur.x+=dt.p[j];cur.y+=dt.p[j+1]; }; break;};
                case dType::ty::H : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j++){ c=cur; cur.x=dt.p[j];  }; break;};
                case dType::ty::h : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j++){ c=cur; cur.x+=dt.p[j];  };break;};
                case dType::ty::V : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j++){ c=cur; cur.y=dt.p[j];  }; break;};
                case dType::ty::v : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j++){ c=cur; cur.y+=dt.p[j];  };break;};
                case dType::ty::C : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=3){ 
                    pt x(cur),y(dt.p[j]),z(p[j+1]),w(p[j+2]);
                    cubic(t,colr,strw,x,y,z,w);cur = w;c=z; }; continue;};
                case dType::ty::c : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=3){
                    pt x(cur),y(x+dt.p[j]),z(y+p[j+1]),w(z+p[j+2]);
                    cubic(t,colr,strw,x,y,z,w );cur=w;c=z; };continue;};
                case dType::ty::S : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=3){ 
                    pt x(c),y(cur),z(p[j]),w(p[j+1]);
                    cubic(t,colr,strw,x,y,z,w );cur=w;c=z;}continue;
                };
                case dType::ty::s : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=3){ 
                    pt x(c),y(cur),z(y+p[j]),w(z+p[j+1]);cubic(t,colr,strw,x,y,z,w );cur=w;c=z;}continue;
                };
                case dType::ty::Q : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=2){ 
                    pt x(cur),y(dt.p[j]),z(p[j+1]);
                                        qudratic(t,colr,strw,x,y,z,w);cur=z;c=y; }; continue;};
                case dType::ty::q : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=2){
                    pt x(cur),y(x+dt.p[j]),z(y+p[j+1]),w(z+p[j+2]);
                    qudratic(t,colr,strw,x,y,z,w );cur=z;c=y; };continue;};
                case dType::ty::T : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j++){ 
                    pt x(c),y(cur),z(p[j]);
                    qudratic(t,colr,strw,x,y,z );cur=z;c=y;}continue;
                };
                case dType::ty::t : {for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j++){ 
                    pt x(c),y(cur),z(y+p[j]);quadratic(t,colr,strw,x,y,z );cur=z;c=y;}continue;
                };
                case dType::ty::A : {
                    bool of=false;
                    for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=3) {
                        if(of){
                            float angle(dt[j+1].y) ;
                            pt r(dt[j].y,dt[j+1].x), flag(dt[j+2]) , xy(dt[j+3]) ;
                            arc(t,colr,strw,cur,r,angle,flag,xy);
                        cur = xy;
                        }
                        else {
                            float angle(dt[j+1].x) ;
                            pt r(dt[j]), flag(dt[j+1].y,dt[j+2].x) , xy(dt[j+2].y,dt[j+3].x)
                            arc(t,colr,strw,cur,r,angle,flag,xy);
                        cur = xy;
                        }
                        of!=of;
                        continue;
                    }
                };
                case dType::ty::a : {
                     bool of=false;
                    for(size_t j = dt.offs[dt.offs[i]] ;j< dt.offs[dt.offs[i+1]] ;j+=3) {
                        if(of){
                            float angle(dt[j+1].y) ;
                            pt r(dt[j].y,dt[j+1].x), flag(dt[j+2]) , xy(cur+dt[j+3]) ;
                            arc(t,colr,strw,cur,r,angle,flag,xy);
                            cur=xy;
                        }
                        else {
                            float angle(dt[j+1].x) ;
                            pt r(dt[j]), flag(dt[j+1].y,dt[j+2].x) , xy(cur.x+dt[j+2].y,cur.y+dt[j+3].x)
                            arc(t,colr,strw,cur,r,angle,flag,xy);
                            cur=xy;
                        }
                        of!=of;
                    }
                    cur=continue;
                };
                case dType::ty::Z : {if(cur!=dt.p[0] ){line(t,colr,strw,mod::image2D::line(cur,dt.p[o])) ;}};
                case dType::ty::z : {if(cur!=dt.p[0] ){line(t,colr,strw,mod::image2D::line(cur,dt.p[o])) ;}};
            }
            line(t,colr,strw,line(c,cur););
        };
    };
    float plen=0;;

    void len_plus(pt x){plen+=sqrt(x.x*x.x + x.y*x.y)};
    void len_line(dType& t, uint32_t colr, float strkw,line l){ pt x(l.e - l.s) ; plus(x);}
    void len_quad(dType& t,bool fstart, uint32_t colr, float strkw,pt x, pt y ,pt z){ if(!fstart){plus(y-x);} ;plus (z-y);}    
    void len_cubic(dType& t,bool fstart, uint32_t colr, float strkw,pt x,pt y ,pt z ,pt w ){if(!fstart){plus(y-x);};  plus(z-y) ; plus(w-z)a);}
    void len_arc(dType& t, uint32_t colr, float strkw,pr s,pt r, float angle , pt flag,pt xy){plen+=M_PI*r.x;}


    float lazypathLen(dType& dt ){plen=0;pathHandle(dt,0,0,dt,len_line,len_quad,len_cubic,len_arc);};
    void rast(pathTag& t) {
        uint32_t colr = t.ats.getStr<"color">()<<8 + ((uint8_t)(t.ats.getStr<"stroke-opacity">() * 0xFF)) ;
        float strw = t.ags.getStr<"stroke-width">();
        dType dt = t.ats.getStr<"d">();imRef=t.im ;
        pathHandle(dt,colr,strw,,rast_line,rast_quad,rast_cubic,rast_arc) ;
    };
   
    void rast(polygonTag& t) {
        uint32_t colr = t.ats.getStr<"color">()<<8 + ((uint8_t)(t.ats.getStr<"stroke-opacity">() * 0xFF)) ;
        float strw = t.ags.getStr<"stroke-width">();
        auto pts = t.ats.getStr<"points">();
        t.im.line(colr,strw,mod::image2D::line(pts[pts.size()-1], pts[0])) ;
        for(size_t i=1;i<pts.length();i++){t.im.line(colr,strw,mod::image2D::line(pts[i-1], pts[i])) ;}
    };
    void rast(polylineTag& t) {        
        uint32_t colr = t.ats.getStr<"color">()<<8 + ((uint8_t)(t.ats.getStr<"stroke-opacity">() * 0xFF)) ;
        float strw = t.ags.getStr<"stroke-width">();
        auto pts = t.ats.getStr<"points">();
        for(size_t i=1;i<pts.length();i++){t.im.line(colr,strw,mod::image2D::line(pts[i-1], pts[i])) ;}
    };
    void rast(rectTag& t) {
        uint32_t colr = t.ats.getStr<"color">()<<8 + ((uint8_t)(t.ats.getStr<"stroke-opacity">() * 0xFF)) ;
        float strw = t.ags.getStr<"stroke-width">();
        mod::image2D::pt a{t.ats.getStr<"x">(),t.ats.getStr<"y">()};
        mod::image2D::pt b{t.ats.getStr<"width">(),t.ats.getStr<"height">()};
        mod::image2D::pt r{t.ats.getStr<"rx">(),t.ats.getStr<"ry">()}
       
           line _a(pt(a.x+r.x,a.y) ,pt(a.x -r.x+b.x,a.y));
        t.im.line(colr,strw, atan(a.y,a.x),a);
           line _b(pt(a.x+r.x,a.y+b.y) ,pt(a.x -r.x+b.x,a.y+b.y));
        t.im.line(colr,strw, atan(b.y,b.x),b);
           line _c(pt(a.x,a.y+r.y) ,pt(a.x ,a.y+b.y-r.y)))
        t.im.line(colr,strw, atan(c.y,c.x),c);
           line _d(pt(a.x+b.x,a.y+r.y) ,pt(a.x+b.x ,a.y+b.y-r.y));)
        t.im.line(colr,strw, atan(d.y,d.x),d);
        t.im.ellipseArc(colr,strw,r.x,r.y,pt(a.x+r.x,a.y+r.y),M_PI_2,M_PI);
        t.im.ellipseArc(colr,strw,r.x,r.y,pt(a.x+r.x,a.y-r.y+b.x),M_PI,M_PI_2 *3);
        t.im.ellipseArc(colr,strw,r.x,r.y,pt(a.x-r.x+b.x,a.y+b.y-r.y),M_PI_2*3,M_PI_2*5);
        t.im.ellipseArc(colr,strw,r.x,r.y,pt(a.x-r.x+b.x,a.y+r.y),M_PI_2*5,M_PI_2);
        t.im.scan(colr);
    };
    ttf::font* f;

 uint32_t binomial(uint8_t n , uint8_t k){
        uint32_t res=1;
        for(uint32_t i =k+1;i<=n;i++){res*=i;};
        for(uint32_t i =1;i<=k;i++){res*=i;};
        return res;
    };
    

    std::vector<pt > pts;size_t pcur=0;
    float distpth;

    template <size_t ps>
    void bezier(bool fstart,clrFr colr ,float strkw, pt p[ps] ){
        float step =1 ;
        float ls = plus(p[0]-p[1]);
        float len =ls;
        for(size_t i=1;i<ps-1;i++){len+=plus(p[i+1]-p[i] ); }

        float step = 1 / len ;
        float lssteps = ls/len;
        pt last;
        if(fstart){
            float lssteps = ls/len;
            sit+=lssteps;
            last=p[1];
        };
        else {last=p[0];}
        for(;sit<1;sit+=step){
            pt h;
            for(uint8_t i=0 ;i<ps;i++  ){
                h+=(float)binomial(ps-1,i) * pow ( (1-sit) ,((float)ps-1-(float)i) )*pow(sit,(float)i) * p[i] ; 
            }
            pcur++;pts.push_back(h);
            last =h;
        };
    };

     void ellipseArc(  float rx,float ry,float cx,float cy, float phi ,float alpha,float rotation=0){

        float stepLen = 1/ (M_PI*(rx+ry))  ;
        float stepRad = 2*M_PI * stepLen;
        float a = 2*rx;
        float b= 2*ry;
        auto lam = [&](float ang)->pt{return pt(cx+a*cos(ang+rotation),cy+ b* sin(ang+rotation))};
        pt prev=lam(0);
        for(float i=stepRad;i<M_2_PI;i+=stepRad){
            pt p = lam(i);pcur++;
            pts.push_back(p);
        };
    };

    void tplus(pt x){plen+=sqrt(x.x*x.x + x.y*x.y);};
    void tpth_line(dType& t, uint32_t colr, float strkw,line l){pts.push_back(l.e);pcur++;};

    void tpth_quad(dType& t,bool fstart, uint32_t colr, float strkw,pt x, pt y ,pt z){ bezier(fstart,colr,strkw,{x,y,z});}    ;
    void tpth_cubic(dType& t,bool fstart, uint32_t colr, float strkw,pt x,pt y ,pt z ,pt w ){bezier(fstart,colr,strkw,{x,y,z,w});};
    void tpth_arc(dType& t, uint32_t colr, float strkw,pr s,pt r, float angle , pt flag,pt xy){
         bool smallArc = flag.x==0;
        bool clockWise = flag.y==0;
        // Tangent at point
        float tgs = 
        float len = M_PI * plus(xy-s);
        pt center;
        
        float st,et;
        float d=  sqrt(pow(e.x-s.x,2) + pow(e.y-s.y , 2) ) ;
        float a=pow(r.x,2) -pow(r.y,2) + d*d;
        float h=sqrt(r.x*r.x-a*a);
        pt pp(s.x+a*((e.x-s.x)/d) , s.y+a*((e.y-s.y)/d));
        
        pt c1(pp.x+(h*(e.y-s.y)/d) , pp.y-(h*(e.x-s.x)/d)) ;
        pt c2(pp.x-(h*(e.y-s.y)/d) , pp.y+(h*(e.x-s.x)/d)) ;
        pt c=c1;

        if (!clockWise){c = c2; } ;
        pt cs=s-c ;pt ce=e-c; 
        float phi = atan(cs.y,cs.x);float alpha=atan(ce.y,ce.x);
        if(smallArc){float t=phi;phi = alpha ; alpha =phi }  ;
        if(phi>alpha){alpha+=M_PI} ;
        ellipseArc(colr, 0,r.x,r.y,c.x,c.y,phi,alpha,angle );
    }

    void rast(textPathTag& t) {pcur=0;
        uint32_t colr = t.getStr<"stroke">();
        Number textLength(t.ats.getStr<"textLength">()) ;
        dType t = t.r.ats.getStr<"path">();
        lazeypathLen(dt);float pl=plen;
        float textSize=t.r.data.size();

        pathHandle(t,0,0,tpth_line,tpth_quad,tpth_cubic,tpth_arc) ;
        size_t i=0;
        float offs=0;
        pt h;pts[i+1]-pts[i];
        float alpha;
        auto lam=[&](){if(i<pts.size()-2){ h= pts[i+1]-pts[i]; alpha=atan(h.y,h.x);i++;};}
        for(char c : t.data) {
            font::glyfft r =  f->get(c,opts);
            lam();            
            im.glyf<uint32_t,true>(stroke,size,pts[i],r,alpha);
        };
  
    };
    void rast(textTag& t) {
        uint32_t colr = t.getStr<"stroke">();
        Number textLength(t.ats.getStr<"textLength">()) ;
        Number x(t.ats.getStr<"x">()),y(t.ats.getStr<"y">()),dx(t.ats.getStr<"dx">()),dy(t.ats.getStr<"dy">()),rotate(t.ats.getStr<"rotate">());
        float size = textLength/t.data.size();
        pt p(x+dx,y+dy);
        pt plus(cos(rotate)*size,sin(rotate)*size);
        mod::options opts;opts.color=true;opts.kering=true;opts.curve=true;
        for(char c : t.data) {
            font::glyfft r =  f->get(c,opts);
            im.glyf(stroke,size,p,r,rotate);
            p=p+plus;
        };
    };
    void rast(tspanTag& t) {
           uint32_t colr = t.getStr<"stroke">();
        Number textLength(t.ats.getStr<"textLength">()) ;
        Number x(t.ats.getStr<"x">()),y(t.ats.getStr<"y">()),dx(t.ats.getStr<"dx">()),dy(t.ats.getStr<"dy">()),rotate(t.ats.getStr<"rotate">());
        float size = textLength/t.data.size();
        pt p(x,y);
        pt plus(cos(rotate)*size,sin(rotate)*size);
        mod::options opts;opts.color=true;opts.kering=true;opts.curve=true;
        for(char c : t.data) {
            font::glyfft r =  f->get(c,opts);
            im.glyf(stroke,ptsize,p,r,rotate);
            p=p+plus;
        };
    };
    filtt reff ;
    void filt(feBlendVar& b){};
    void filt(feColorMatrixTag& b){};
    void filt(feComponentTransferTag& b){};
    void filt(feCompositeTag& b){};
    void filt(feConvolveMatrixTag& b){};
    void filt(feDiffuseLightingTag& b){};
    void filt(feDisplacementMapTag& b){};
    void filt(feDropShadowTag& b){};
    void filt(feFloodVar& b){};
    void filt(feFuncATag& b){};
    void filt(feFuncBTag& b){};
    void filt(feFuncGTag& b){};
    void filt(feFuncRTag& b){};
    void filt(feGaussianBlurTag& b){};
    void filt(feImageTag& b){};
    void filt(feMergeTag& b){};
    void filt(feMergeNodeTag& b){};
    void filt(feMorphologyTag& b){};
    void filt(feOffsetTag& b){};
    void filt(feSpecularLightingTag& b){};
    void filt(feTileTag& b){};
    void filt(feTurbulenceTag& b){};

    void filt(radialGradientTag& b){};
    void filt(linearGradientTag& b){};
    void filt(radialGradientTag& b){};

    template <typename T>
    void procSub(T& t){
        if constexpr (pri::is_one_of<T,FILTERPRIMITIVEELS>::value){filt(t);}
        if constexpr (pri::is_one_of<T,ANIMATIONELS>::value){filt(t);}
        if constexpr (pri::is_one_of<T,GRADIENTELS>::value){filt(t);}
    };

    template <typename T>
    void procSubs(T& t){
        reff = t.filt;
        t.subs.apply<procSub>()
    };
    template <typename T>
    void _rast(T& t ) {
        if (pri::is_one_of<T,SHAPEELS,TEXTCONTENTELS>::value){rast(t);}
        

    };

    template <typename T>
    void _rast(T& t ){
        t.setImage(UserSpaceUnits);
        if (pri::is_one_of<T,FILTERPRIMITIVEELS>::value){}

        t.apply<__rast>();
        __rast(t);
    };
template <class imFFormat>
    void save(std::string path ){imFFormat r;r.wr(ref.im,path);};
    svgRast(svgTag& v){rast(v,pt(0,0)) ; };
};



};