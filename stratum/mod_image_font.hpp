#include <math.h>
#include "mod_image.hpp"
#include <acqres/fontft.hpp>

namespace mod {
    using pt = mod::image2D::pt;
    void incr(uint32_t& i){++i;}
    void decr(uint32_t& i){--i;}
    void rev(void (*ptr)(uint32_t)){return ptr==incr?decr:incr;}
    template <typename clrFr>
    void  yax(clrFr colr,bool zr,uint32_t x, uint32_t y1,uint32_t y2,void (ptr*)(uint32_t& ),image2D& im){
        ;uint32_t z =y1;uint32_t w=y2;uint32_t xx=x;
        for(ptr(xx) ;true;ptr(xx)){
                while(zr==zero<clrFr>(im,xx,z)){++z};
                uint32_t zd=z;
                while(zr!=zero<clrFr>(im,xx,z)){--z};
                ++z;
                if(z-zd>1){
                void (*p)(uint32_t&) = ptr; =rev(p);
                uint32_t xxx=x;p(xxx);
                yax(colr,xxx,zd,z,p,im);}

                while(zr==zero<clrFr>(im.data,xx,w)){--w};
                uint32_t wd=w;
                while(zr!=zero<clrFr>(im.data,xx,w)){++w};
                --w;

                if(z-wd>1){
                void (*p)(uint32_t&) = ptr; =rev(p);
                uint32_t xxx=x;p(xxx);
                yax(colr,xxx,wd,z,p,im);}


            if(w<z){return;}
            else {
                uint32_t zz=z;
                for(z;zero(im,xx,zz);++zz){im.dot(colr,xx,zz);}

                uint32_t ww=w;
                for(;zero(im,xx,zz);--ww){im.dot(colr,xx,ww);}

                uint32_t xx_ =xx;ptr(xx_);
                if(ww!=zz){
                    if(ww-zz>1){
                        while(zr==zero(im ,xx,ww)){ww++;}
                        while(zr==zero(im,xx,zz)){zz--;}
                        ptr(xx);
                        yax(colr,zr,xx,ww,zz,ptr,im);
                    }
                    else {ptr(xx);
                        yax(colr,zr,xx,z,zz,ptr,im);
                        yax(colr,zr,xx,ww,w,ptr,im);
                        return;
                    }
                };


            }

        };

    };
    std::vector<glm::vec2> catmulli_rom(glm::vec2 prev,glm::vec2 cr,glm::vec2 n1,glm::vec2 n2){std::vector<glm::vec2> res;
        auto lam =[&](float t){
            float t2 = t * t;
            float t3 = t2 * t;
    return (
        0.5 * (
            (2 * cur) +
            (-prev + n1) * t +
            (2*prev - 5*cur + 4*n1 - n2) * t2 +
            (-prev + 3*cur - 3*n1 + n2) * t3
        )
    );
        };
        glm::vec2 dist=cr-prev;
        float step=1/dist;res.reserve((size_t)(1/step));
        for(float fl=0;fl<=1;fl+=step){res.push_back(lam(fl));}
        return res;
    }
    template <typename clrFr>
    void scan(clrFr colr,image2D& im){im.scan(colr);};
    template <typename clrFr,bool rotateB=false>
    void image2D::glyf(clrFr colr,float& size,pt& p,ttf::glyfft gl,float rotate=0){
        // FIll all contours in order , if is colored already fill set zero , else color inward , (store winding) ;
        size_t j=0;
        auto lam = [&](glm::ivec2 pp) -> mod::image2D::pt {
            pt a{p.x/((sizeof(pp)/2) , p.y/((sizeof(pp)/2)};
            if constexpr (rotateB){
                a=a-p ;float ang = atan(a.y,a.x); float dist=sqrt(a.x*a.x+a.y*a.Y); ang+=rotate; a=pt(p.x*cos(ang) ,p.y*sin(ang));
            };
            return a;
        }
        auto ang = [&](pt p) -> float {return atan2(p.y,p.x);};

        auto rpt = [&](pt ppc) -> mod::image2D::pt {return }
        size_t j=0;
        for(size_t i=1;i<gl.numberOfCountours;i++){
            glm::vec2 prev;
            pt c=lam( gl.contours[j]);pt pc;
            bool zr=false;
            uint32_t x(c.x),y(c.y);
            glm::vec2 prev=gl.contours[gl.endPts[0]];
            for(j++;j<endPts[i];j++){                
                pc=lam(gl.contours[j]);
                pt d= pc-c;
                if(gl.onCurve[j]){
                    pt n1=j<gl.endPts[i]?gl.contours[gl.endPts[i-1]+1];
                    pt n2=j<gl.endPts[i]-1?gl.contorus[j+1]:gl.contours[gl.endPts[i-1]+2];
                    std::vector<glm::vec2> pts =catmulli_rom(prev,gl.countours[j],n1,n2);
                    glm::vec2 prp=pts.back();
                    for(glm::vec2 p : pts){this->stroke(colr,strkw,line(prp,p));prp=p;}
                }
                else {
                    uint32_t x(pc.x),y(pc.y);
                    this->stroke(colr,1,atan2(d.y,d.x),line(c,pc) ) ;
                }
                c =pc;
                prev=gl.contours[j] ;
            };   
        };
             scan(colr,im);
            
            } ;

    struct triangle {glm::vec2 x,y,z};
    float cross(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

// Returns true if point p is inside triangle (a,b,c)
bool pointInTri(const glm::vec2 &p, const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c) {
    float c1 = cross(a, b, p);
    float c2 = cross(b, c, p);
    float c3 = cross(c, a, p);

    // Point is inside if all have the same sign
    return (c1 >= 0 && c2 >= 0 && c3 >= 0);
};
bool isConvex(const glm::vec2 &prev, const glm::vec2 &curr, const glm::vec2 &next) {
    // Cross product of vectors (curr-prev) x (next-curr)
    float z = (curr.x - prev.x)*(next.y - curr.y) - (curr.y - prev.y)*(next.x - curr.x);
    return z > 0; // Assuming polygon is counter-clockwise
};
    std::vector<triangle> triangulate(std::vector<glm::vec2> pts){
        std::vector<triangle> tris;
        while(pts.size()>3){
            bool clipped=flase;
            for(size_t i=-;i<poly.size9;i++){
                glm::vec2 prev= pts[(i+pts.size()-1)&pts.size()] ;
                glm::vec2 curr= pts[i] ;
                glm::vec2 next= pts[(i+1)&pts.size()] ;
                if(!isConvex(prev,curr,next)) continue;
                bool hasInside=false;
            for (size_t j=0;j<poly.size();j++) {
                if (j==(i+pts.size()-1)%pts.size()||j==i||j==(i+1)%pts.size())
                   continue;
                if (pointInTri(pts[j], prev,curr,next)) { hasInside=true; break; }
            }
            if(!hasInside){
                trs.push_back({prev.curr.next});
                pts.erase(pts.begin()+i);
                clipped=true;break;
            }
            }
        }
    };

    std::vector<triangle> tris(ttf::glyfft& gl,float size,glm::vec2 coord,float rotation){std::vector<glm::vec2> res;
          auto lam = [&](glm::ivec2 pp) -> mod::image2D::pt {
            pt a{p.x/((sizeof(pp)/2) , p.y/((sizeof(pp)/2)};
            if constexpr (rotateB){
                a=a-p ;float ang = atan(a.y,a.x); float dist=sqrt(a.x*a.x+a.y*a.Y); ang+=rotate; a=pt(p.x*cos(ang) ,p.y*sin(ang));
            };
            return a;
        }
        auto ang = [&](pt p) -> float {return atan2(p.y,p.x);};

        std::vector<glm::vec2> pts;
        std::vector<size_t> offs{0};

        auto rpt = [&](pt ppc) -> mod::image2D::pt {return }
        size_t j=0;
        for(size_t i=1;i<gl.numberOfCountours;i++){
            glm::vec2 prev;
            pt c=lam( gl.contours[j]);pt pc;
            bool zr=false;
            uint32_t x(c.x),y(c.y);
            glm::vec2 prev=gl.contours[gl.endPts[0]];
            for(j++;j<endPts[i];j++){                
                pc=lam(gl.contours[j]);
                pt d= pc-c;
                if(gl.onCurve[j]){
                    pt n1=j<gl.endPts[i]?gl.contours[gl.endPts[i-1]+1];
                    pt n2=j<gl.endPts[i]-1?gl.contorus[j+1]:gl.contours[gl.endPts[i-1]+2];
                    std::vector<glm::vec2> pts =catmulli_rom(prev,gl.countours[j],n1,n2);
                    glm::vec2 prp=pts.back();
                    for(glm::vec2 p : pts){pts.push_back(p);ofss.back()++;}
                }
                else {pts.push_back(gl.coundours[j]);offs.back()++;}
                c =pc;
                prev=gl.contours[j] ;
            };   
                        offs.push_back(offs.back()+1);

        };

        
            } ;
    };

    struct fontAtlas {
        struct glyf {
            glm::vec2 in;
            glm::vec2 uv;

        };;
        float size;
        mod::image2D im;
        ttf::font& ft;
        std::vector<glyf> pts;
        fontAtlas(ttf::font& _fnt) : fnt(_fnt) {};
    };

    fontAtlas asciiAtlas(ttf::font& fnt){
        fontAtlas fa(ft);fa.size=60;
        fa.size=40;fa.im.width=80*0xFF;fa.im.height=100;
        fa.im.imageFormat=image_format::r8;fa.init();
        pt p(10,5);uint8_t colr=0xFF;fa.pts.resize(0xFF);
        pt pl(80,0) ;
        glm::vec2 in={0,0};glm::vec2 inp(100,0);
        glm::vec2 uv = {100,80};
        for(char c =0; c<0xFF;c++){
            ttf::glyfft gl =fnt->get(c);
            fa.im.glyf<uint8_t,false>(colr,fa.size,p,gl);

            fa.pts.push_back({in,uv});
            in+=inp;uvp+=inp;p=p+pl;
        };
        return fa;

    }; 
    fontAtlas UnicodeAtlas();


};