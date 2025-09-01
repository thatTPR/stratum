#include <stratum/acqres/fontft.hpp>
#include <uchar.h>
#ifndef MOD_FONT_HPP
#define MOD_FONT_HPP
#include "mod_util.hpp"
namespace mod {
memoryPool<ttf::font> fontPool;

template <typename T>
    struct contour : std::vector<T> {
        T& operator[](int s){
            int h = s%size();
            return h<0?data()[size()+s]:s ;}
};

struct fontColorEdit {

};
struct fontEdit {
    std::vector<contour<glm::ivec2>> contours;
    std::vector<contour<bool>> onCurve;
    uint16 glyphID;
    ttf::coord pos;
    int16   xMin;
    int16   yMin;
    int16   xMax;
    int16   yMax;
    fontColorEdit colors;
    void set(ttf::glyfft& f){
                size_t endPl = 0;
        for(size_t i=0;i<f.numberOfContours;i++){
            contours.push_back(std::vector<glm::ivec2>(f.endPts[i]-endPl+1));
            onCurve.push_back(std::vector<glm::ivec2>(f.endPts[i]-endPl+1);
            for(size_t j = endPl;j<=f.endPts[i];j++){contours.back()[j-endPl]=f.contours[j]; onCurve.bacl()[j-endPl] = f.onCurve[j];}
            endPl=f.endPts[i] + 1;
        };
    }
    fontEdit(ttf::glyfft& f){
        glyphID = f.glyphID;
        pos = f.pos;
        xMin = f.xMin;
        yMin = f.yMin;
        xMax = f.xMax;
        yMax = f.yMax;set();
    }
};
template <typename charT, bool bm>
struct fontPrim {

    font::options opts ;
    std::basic_string<charT> text;
    struct ftPrim {
        struct vert {
            using prty = topology_primitive_vec<DIM::bi,TopologyPrimitive::TRIANGLE_STRIP,false>; 
            struct oncurved {
                bool onCurve;
                glm::vec2 pt;
            }
            struct invertBool {
                bool inverted;
                prty contour;
                struct data {
                    bool inverted;
                    size_t s;
                    prty::vertty* data ;
                }
                data get(){return {inverted,contour.size(),contour.data()};}
            };
            using oncty = std::vector<oncurved>; 
                glm::ivec2 pos;
                int16   xMin;
                int16   yMin;
                int16   xMax;
                int16   yMax;

            pri::list<prty> mprim;
        };
        struct frag {
            glm::uvec4 bg;
            glm::uvec4 fg;
            float alpha;
        };
        vert v;
        frag f;
    };
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

    std::vector<ftPrim> ftprims;
    std::vector<bmPrim>> bmprims; 
    uint8_t tesc = 0;
    
     pri::list<ftPrim::vert::prty> tesselate(fontEdit& fe){
        pri::list<ftPrim::vert::prty> ret;
        for(size_t s =0 ; s<fe.contours.size();s++){        ret.push_back(ftPrim::vert::prty());       

            for(size_t j =0 ; j<fe.contours[s].size();j++){
                size_t offs = 0; size_t loffs=0
                if(fe.onCurve[s][j]){
                    bool prevC = fe.onCurve[s][j-1];
                    bool nextC = fe.onCurve[s][j+1];
                    
                    std::vector<glm::vec2> pts(tesc);
                    glm::ivec2 cur =fe.contours[s][j+offs];
                    glm::ivec2 prevc =fe.contours[s][j+offs-loffs];
                    glm::ivec2 nextc =fe.contours[s][j+offs+1];
                    bool onCurvPrev =fe.onCurve[s][j-1];
                    glm::vec2 hpt = (prevc + nextc)/2;
                    glm::vec2 p1 = (cur - hpt)*2 + hpt ;
                    //formula  : B(t) = (1-t)^2 * prevc + 2*(1-t)*t*p1 + t^2 *next

                    for(size_t i = 0;i<tesc;i++){float t = i/tesc ;
                        glm::vec2 pt =pts[i] = powf((1-t),2) * prevc + 2*(1-t)*t*p1 + pow(t,2) *nextc;
                        ret.back().push_back(pt);
                    };
                    ret.push_back(pts);
                    fe.contours[s].insert( fe.contours[s].begin()+j+offs, pts.begin(),pts.begin()+ tesc-1 )
                    offs+=tesc;
                    loffs = tesc;
                };
                else {
                    glm::vec2 pt = fe.contours[s][j+offs];
                    ret.back().push_back(pt);
                    tesc=0;}
        };
    };
    return ret;
}
    bool intersect(glm::vec2 A1 ,glm::vec2 A2 , glm::vec2 SEG1 , glm::vec2 SEG2  ){
        glm::vec2 a1= A1 ;glm::vec2 a2 =A2 ; glm::vec2 seg1=SEG2 , glm::vec2 seg2 = SEG2;
        a2 = a2 - a1;seg1 = seg1 - a1 ; seg2 = seg2 - a1;  
        float a , s1,s2;
        a = slope(a2);s1 = slope(seg1); s2 = slope(seg2);
        if(s1 - a>0){
            if(s2 - a>0){return false;}
            return true;
        }
        if(a - s2>0 ){return false;}
        return true;
    };
    bool isInside(glm::vec2 is , ftPrim::vert::prty& cmp){
        glm::vec2 first = cmp[0];
        glm::vec2 dif=is-first;
        glm::vec2 last = cmp[1];
        size_t intersects = 1;
        for(size_t s = 2 ; s< cmp.size();s++){
            if(intersects(first,is,last,cmp[s])){intersects++;} ;
            last = cmp[s];
        };
        if(intersects%2==0){return true;}
        return false;
    };
    bool segIntersect(glm::vec2 sa1,glm::vec2 sa2,glm::vec2 sb1,glm::vec2 sb2, glm::vec2* res){
        sa2-=sa1;
        sb1-=sa1;sb2-=sa1;
        float ssa = sa2.y/sa2.x;

        float ssb1 = sb1.y/sb1.x;float ssb2 = sb2.y/sb2.x;
        glm::vec2 difb = sb2 - sb1 ;
        float ratio = (ssb2 - sa) /(ssb2-ssb1) ;
        difb*= ratio;
        glm::vec2 pt = sb1 + difb   ;
        *res = sa1 + pt;
        if(glm::length(pt) < glm::length(sa2) ){
            if(glm::sign(pt.x) == glm::sign(sa2.x) and (glm::sign(pt.y) and glm::sign(sa2.y))){
                return true;
            }
        }
        return false;
    };
    glm::vec2 getIntersect(glm::vec2 seg1 ,glm::vec2 seg2 ,ftPrim::vert::prty& cmp,size_t* s1,size_t* s2 ){
        glm::vec2 last = cmp[0];
        for(size_t i=1;i<cmp.size();i++){
            glm::vec2 pt;
            if(segIntersect(seg1,seg2,cmp[i],last,&pt)){
                *s1 = i-1;*s2=i ;
                return pt;
            }
            last = cmp[i] ;
        }
    };
    
    // PointLess: Don't use
    enum IsInsideEn {
        False = 0,
        True = 1,
        Kinda = 2,
    };
    IsInsideEn checkInside(ftPrim::vert::prty& is,ftPrim::vert::prty& cmp,std::vector<ftPrim::vert::prty>* res ){
        IsInside ret=IsInsideEn::True;
        res->push_back(ftPrim::vert::prty());
        glm::vec2 last ;
        size_t s1,s2,b1,b2;
        glm::vec2 p = is[0];last = p;
        bool startInside = false;
        if(isInside(p,cmp)){startInside=true;ret=IsInsideEn::True;}
        auto first = [&](size_t* sone,size_t* stwo){
            ret = IsInsideEn::Kinda;
                    glm::vec2 pt = getIntersect(last,p,cmp,sone,stwo);
 res->push_back(ftPrim::vert::prty());res->back().push_back(pt);res->back().push_back(p);
        }
        for(size_t s = 1; s< is.size();s++ ){p= is[s];
            if(startInside){ // TODO make it so it adds to res when appropiate
                if(!isInside(p,cmp)){
                    if(ret==IsInsideEn::True){first(&s1,&s2);}
                    else {res->back().push_back(p);}
                }
                else {
                    if(ret == IsInsideEn::True){last=p;continue;}
                    if(ret =IsInsideEn::Kinda){
                        first(&b1,&b2);
                        if(b2<s1){for(;b2<=s1;b2++){res->back().push_back(cmp[b2]);}}
                        if (s2<b1){for(;s2<=b1;s2++){res->back().push_back(cmp[s2]);}}
                        ret = IsInsideEn::True;
                    }
                };
            }
            else {
                if(isInside(p,cmp)){
                    if(ret==IsInsideEn::True){first(&s1,&s2);}
                    else {res->back().push_back(p);}
                }
                else {
                    if(ret == IsInsideEn::True){last=p;continue;}
                    if(ret =IsInsideEn::Kinda){
                        first(&b1,&b2);
                        if(b2<s1){for(;b2<=s1;b2++){res->back().push_back(cmp[b2]);}}
                        if (s2<b1){for(;s2<=b1;s2++){res->back().push_back(cmp[s2]);}}
                        ret = IsInsideEn::True;
                    }
                };

            }
            last = p;
        }
      return res->size()>0?IsInsideEn::Kinda : startInside?IsInsideEn::True:isInside::False;        
    };

    float slope(size_t i,ftPrim::vert::prty& cont){
            glm::vec2 f=cont[i] - cont[i-1] +  (cont[i+1] - cont[i] )  ; return f.y/f.x ;
        };
    pri::list<ftPrim::vert::prty> triStrips(ftPrim::vert::prty& out,std::vector<ftPrim::vert::prty>& in){
        pri::list<ftPrim::vert::prty> res;

        // Get outside tip ranges 
        // Get inside tip range
        // TOOD
        pri::list<std::pair<size_t,size_t>> outs; 
        pri::list<std::pair<size_t,size_t>> ins;
        
        int j=0;int s;
       
        auto passed = [&](glm::vec2& si, size_t& sprev, size_t& snext){
            float n = slope(s,out);
            float norm = - 1/n;
            size_t sj =j;
            for(;sj;sj++){
                bool beneath = (in[sj] - out[s]) 
                if()
            };
        };
        glm::vec2 out_startsi = glm::sign(out[1] - out[-1]) ;
        glm::vec2 out_cursi = out_startsi;

        
        int minInd = j; float minDist = glm::distance(in[j],out[0]) ; 
        for (j=1;j<in.size();j++){
            float dist = glm::distance(in[j],out[0]); 
            if( dist < minDist ){minDist = dist;minInd = j ;}
        };
        glm::vec2 in_startsi = glm::sign(in[minInd+1] - in[minInd-1]) ;
        glm::vec2 in_cursi = in_startsi;
        
        
        for( s=0;s<out.size();s++){

        };


    };
    pri::list<ftPrim::vert::prty> triStrips(ftPrim::vert::prty& out){
        std::vector<glm::vec2> v(out.size());

        std::vector<glm::vec2> tips;
        contour<float> slopes(out.size())  ; ;
        for(int s=0;s<out.size();s++){slopes.push_back(slope(s,out));};
        std::vector<float> betas(out.size());
        for(int s=0;s<out.size();s++){betas.push_back(slopes[s+1]-slopes[s-1]);};

        float avgBeta =0; size_t smallest = 0;size_t s=0;
        for(float& f : betas){avgBeta+=f;smallest = betas[s]<betas[smallest]?s:smallest;s++;}avgBeta/=betas.size();

        std::vector<bool> ltavg(betas.size());
        for(size_t s=0;s<betas.size();s++){ltavg=betas[s]<avgBeta?true:false;}
        /// Betas get local maximums
        


    }


    void VertProc(ttf::glyfft&  f,ftPrim& r) {
        fontEdit fe;fe.set(f) ;
         pri::list<ftPrim::vert::prty> ret = tesselate(fe);
         std::vector<size_t> inside(ret.size());
         std::vector<size_t> outside(ret.size());
         std::vector<bool> inverted(ret.size()) ;
         std::vector<bool> hasInside(ret.size());
          
         ftPrim::vert::prty& last = ret[0];
         for(size_t s=1;s<ret.size();s++){ftPrim::vert::prty& it=ret[s];
            inverted[s] = false;hasInside[s]=false;
            for(size_t ss = 0 ; ss<s;ss++){
                if(IsInside(it[0],ret[ss])){
                    inverted[s] = !inverted[s];
                    hasInside[ss] = hasInside[ss]|inverted[s] ;
                    inside[s] = ss;
                    outside[ss] = s;
                }   
            }
            last = it;
        }
        std:::vector<ftPrim::vert::prty> s;
// Detect tips and add pts as appropiate on line regions to have a clean triangle strip
    size_t lastP=1;        
for(size_t s=0;s<ret.size() and lastP < ret.size();s++){

        };
        
        r.v =  {f.pos,xMin,yMin,xMax,yMax,s};
        
    }

    void FragProc(ttf::glyfft&  f,ftPrim& r) {
        
    }
    void Proc(ttf::glyfft&  f,ftPrim& r){
         VertProc(f,r);
         FragProc(f,r)
    };
    
    void push(font::glyfft& f){
        
        ftPrim::vert s = Proc(f,r);
        ftprims.push_back(s);
    };
    
    
    void push(font::glyfbm f){
        image2D im(f.width,f.height, image_formats::rgba16ui);
        std::memcpy(im.data,f.bitmap,im.byd * im.imageSize);
        
        bmPrim r {f.glyphID,f.pos,f.xMin,f.yMin,f.xMax,f.yMax,f.color,f.alpha,im} ;

        bmprims.push_back(r);
    };
    glm::ivec2 size;
    
    font* f;

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


    void insert(size_t pos,std::string text){
        text.insert(text,pos);
    };
    void multiInsert(std::vector<size_t> poss,std::string text){
        for(size_t p : poss){insert(p,text);};
    };
}



memoryPool<fontPrim<char>> fontPrimPool;
memoryPool<fontPrim<wchar_t>> wcfontPrimPool;
memoryPool<fontPrim<char32_t>> c32fontPrimPool;

}
#endif