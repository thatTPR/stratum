#version 450

#define MAX_PRIM 10000
#define MAX_CONT 100
// struct prim 
layout(std430, set=0,binding=1) buffer ps{
    ivec2 pos;
    int   xMin;
    int   yMin;
    int   xMax;
    int   yMax;
    uint onCurveMax;
    uint maxSizeCon;
    uint numCon;
    uint numOnCurves;// Make it so that the size tells how many intermeddiatePoints are added / numTess
    uint size ;
    vec2 pspts[];    
};
layout(std430, set=0,binding=2) buffer endPts{
    uint p[];//[numCon]
};
layout(std430, set=0,binding=3) buffer onCurve{
    uint onc[];//[numOnCurves]
};
// layout(std430,set=0,binding=4) buffer ps{vec2 pts[];} ;
bool OnCP[MAX_PRIM];
struct glyf {
    ivec2 pos;
    int   xMin;
    int   yMin;
    int   xMax;
    int   yMax;
};
layout(triangle_strip, max_vertices = 100) out;
layout (location=0)out glyf glyfInfo; 
// layout (std430,location=1)out
//  primOut tessCon; 

uint s;

float slope(vec2 left,vec2 center,vec2 right){
    vec2 x = center - left +(right - center);
    return x.y/x.x; 
}
float slope(vec2 l,vec2 r){ vec2 t = r - l; return t.y/t.x;}
float radvec(vec2 l,vec2 r){
    vec2 t = r-l;return atan(t.y,t.x);}

float winding(uvec2 bound){
    float rad= radvec(pspts[bound.x],pspts[bound.x+1]);
    for(uint i=bound.x+1;i<bound.y;i++){
        rad+=radvec(pspts[i],pspts[i+1]);
    }
    rad+=radvec(pspts[bound.y],pspts[bound.x]);return rad;
}
#define M_PI 3.14159253589
float radadd(float v,float s){
    float r = (v+s);
    while(abs(r)>M_PI*2){r+=sign(r)*(M_PI*2);}
    return r; 
}

vec2 ovec(float t){return vec2(1,t);}
vec2 ovec(mat2x2 i){return i[1] - i[0];}

float der(vec2 o){return o.y/o.x ; }

vec2 line(vec2 l1, vec2 l2){
    vec2 o = ovec(mat2x2(l1,l2));
    float d = der(o);
    vec2 dif = l1 ;
    float y = d*dif.x + dif.y;
    return vec2(d,y);
}
vec2 line(mat2x2 l){
    vec2 o = ovec(l);
    float d = der(o);
    vec2 dif = l[0] ;
    float y = d*dif.x + dif.y;
    return vec2(d,y);
}
vec2 intersect(vec2 li1,vec2 li2){
    float fac =(li2.y - li1.y)/(li1.x - li2.x ) ;    
return vec2(fac, li1.x*(fac)+li1.y );
}
vec2 intersect(mat2x2 l1,mat2x2 l2){return intersect(line(l1),line(l2));}


vec2 line(float slope,vec2 pt){
    float y = pt.y;
    return vec2(slope,slope*pt.x + pt.y);
}
vec2 perpendicular(vec2 li ,vec2 pt){
    float slope = (-1/li.x);
    vec2 line = line(slope,pt);
    return intersect(li,line);
}
vec2 rightAngle(vec2 l1, vec2 pt){    
    vec2 per = perpendicular(l1,pt);
    return intersect(per,l1);
}
vec2 rightAngle(mat2x2 l1, vec2 pt){
    return rightAngle(line(l1),pt);    
}

bool intersectSeg(mat2x2 line , mat2x2 seg){
    vec2 i = intersect(line,seg);
    vec2 o = seg[1] - seg[0];
    vec2 r= i-seg[0];
    return  (length(r) < length(o));
}
bool intersectSegSeg(mat2x2 seg1 , mat2x2 seg){
    vec2 i = intersect(seg1,seg);
    vec2 o = seg[1] - seg[0];
    vec2 os = seg1[1] - seg1[0];
    vec2 r= i-seg[0];
    bool sb = length(r) < length(o);if(!sb){return false;} 
    vec2 r1 = i - seg1[0];
    bool s1b = length(r1)< length(os);
    return s1b;
}

bool isInside(vec2 pt,uint indFirst,uint indLast){
    
    uint count=0;
        vec2 cur = pspts[indLast];
        vec2 next = pspts[indFirst];
        vec2 midPt = (cur + next)/2;

        mat2x2 firstPtSeg = mat2x2(midPt,pt) ;        
    count = 0;
    for(uint i=indFirst;i<indLast;i++){
        cur= pspts[i];
        next= pspts[i+1];
        mat2x2 seg=mat2x2(cur,next);
        if(intersectSeg(firstPtSeg,seg)){count++;}
    }
    
    return (count%2)==1;
}
// vec2 center z: rad
vec3 getCenter(vec2 pta,vec2 ptb,vec2 ptOnc){
    vec2 mid=(pta  + ptb)/2;
    vec2 l1= line(pta,ptOnc);
    vec2 l2= line(ptb,ptOnc);
     
     vec2 mid1 = (pta + ptOnc)/2;
     vec2 mid2 = (ptOnc + ptb)/2;
     
    vec2 ll1 = perpendicular(l1,mid1);
    vec2 ll2 = perpendicular(l2,mid2);
    vec2 center = intersect(ll1,ll2);
    float rad = distance(center,pta);
    return vec3(center,rad ); 
}

vec2 ptOnCircle(vec2 pta,vec2 ptb,float t,vec2 center,float r){
    vec2 oa = pta-center;
    vec2 ob = ptb-center;
    vec2 ta = oa*t;
    vec2 tb = ob*(1-t);
    return ((ta+tb)/2)+center;
}

#define TESSC_MAX 100
void arcTess(vec2 pta,vec2 ptb,vec2 ptOnc, uint tessc,vec2 pts[TESSC_MAX]){
    uint tessNum = tessc-2;
    vec3 centRad = getCenter(pta,ptb,ptOnc);
    float r =centRad.z;
    vec2 center=  vec2(centRad.x,centRad.y);
    for(uint i=0;i<=tessNum;i++){ uint t = i/(tessNum);
        pts[i]= ptOnCircle(pta,ptb,t,center,r);
    }
}
void arcTess(vec2 pta,vec2 ptb,vec2 ptOnc, uint t,inout vec2 pts[TESSC_MAX],uint ind){
    uint tessNum = tessc-2;
    vec3 centRad = getCenter(pta,ptb,ptOnc);
    float r =centRad.z;
    vec2 center=  vec2(centRad.x,centRad.y);
    for(uint i=0;i<=tessNum;i++){ uint te = i/(tessNum);
        pts[ind+i]= 
        
        ptOnCircleBeg(pta,ptb,te,center);
    }
}

vec3 getCenter(vec2 centLast,vec2 ptLast,vec2 pt1,vec2 pt2){
    vec2 l = line(centLast,ptLast);
    vec2 l1 = line(pt1,pt2);
    vec2 mid = (p2+p1)/2;
    vec2 perpp = perpedicular(l1,mid); 
    vec2 center = intersect(perpp,l);
    return vec3(center,rad); 
}

vec2 arctesselate(uint s,vec2 ptsonc[s],uint t,inout vec2 pts[TESSC_MAX]){
    uint tessNum = tessc-2;uint inds=0;
vec2 pta;vec2 ptb;
vec2 ptOnc;vec3 centRad;float r;
vec2 oa;vec2 oonc;

    for(uint i=0;i<s-2;i++){
         pta=ptsonc[i];ptb=ptsonc[i+2];ptOnc=ptsonc[i+1];
         if(i==0){centRad = getCenter(pta,ptb,ptOnc);}
         else {centRad =  getCenter(ptsonc[i],vec2(centRad.x,centRad.y),ptOnc);}
         r =centRad.z;
        center=centRad.xy;
         oa = pta-center;
         oonc = ptOnc - center;
        pts[inds] = pta;
        for(uint j=1;j<tessNum;j++){inds++;float te = j/tessNum;
            vec2 ta = oa*te;
            vec2 to = oonc*(1-te);
            pts[inds] = (ta+to)/2 + center;
            inds++;
        }
    }
    vec2 ob = ptb -center;
        pts[inds] = pta;
        for(uint j=1;j<tessNum;j++){inds++;float te = j/tessNum;
            vec2 tb = ob*(1-te);
            vec2 to = oonc*te;
            pts[inds] = (ta+tb)/2 + center;
            inds++;
        }
    inds++;pts[inds] = ptb;
}

uint binomial(uint n,uint k){
    uint res;
    uint st=1;
    for(uint i=k+1;i<=n;i++){
        res*=i;
        if(st<=n-k){if(i%st == 0){res/=st;st++}}
    }
    for(uint i=st;st<=n-k;i++){res/=i;}
}

void computeTrue(uint s,inout vec2 pts[s]){
        vec2 cur = pts[0];
        vec2 prev = cur;
        for(uint i=1;i<s;i++){
        vec2 mid = (prev + pts[i+1])/2;
            cur = pts[i];
            pts[i] = (cur - mid)*2 + cur;
            prev = cur;
        }
}
// uint stess=  s*tess;
// n = stess
void tesselate(uint s,inout vec2 ptsonc[TESSC_MAX],uint stess,inout vec2 pts[TESSC_MAX]){

    computeTrue(s,ptsonc);
    vec2 hpt = (ptprev + ptnext)/2;
    vec2 p1 = (ptc - hpt)*2 + hpt ;

    //formula  : B(t) = sum(i,n){ bin(n,i)* (1-t)^(n-i)t^i*Pi }

    uint tessnum = stess+2;
  for(uint i = 1;i<=tessnum-1;i++){float t = i/tessnum ;
        vec2 r;
        for(uint j =0;j<s;j++){
            r+=binomial(n,j)* pow((1-t),(n-i))*pow(t,j)*ptsonc[j];
        }
        pts[i-1] =r;
    }
}
void tesselate(uint ind,inout uint size ,inout vec2 pts[MAX_CONT]){
    uint curind=0;
    uint start = ind>0?endPts.p[ind-1] : 0;
    uint end = endPts.pt[ind];
    uint j=0;
    bool wrap=0 ;vec2 lastPt =pts[end] ;
    if(OnCP[start]==true){wrap=1;}

    for(uint i=start;i<end;i++){
        uint startInd=i;    
        for(OnCP[i] && i<end;i++ ){j++}
        if(i!=startInd){
            uint s=i-startInd + 1;
            uint ptsonc[s];ptsonc[0]=lastPt;
            for(uint j=1;j<s;j++){
                ptsonc[j] = pspts[startInd+j];}
            uint tesst = (s+1)*tess ;vec2 ptst[tesst];
            arctesselate(s,ptsonc,tesst,ptst);
            for(uint j=0;j<tesst;j++){pts[curInd]=ptst[j];curInd++;}
        }
        else {pts[curInd]=lastPt;curInd++}
        lastPt = p.Pts[i];
    }
    size=curInd;
}
uint getSize(uint ind){uint size=0;
    uint start = ind>0?endPts.p[ind-1] : 0;
    uint si = endPts.p[ind] - start+1;uint j=0;
    for(uint i=0;i<si;i++){if(ONcP[start+i]){for(;OnCP[start+i];i++){j++;} continue;} else {size++;}}
    size+=(1+j)*tess; return size;
}

#define MAX_DIR 1000
uint close( vec2 p, uint s,inout vec2 c2[MAX_DIR],uvec2 lim){
    uint m = lim.x;   
    for(uint j=lim.x;j<=lim.y;j++){
        vec2 pp = c2[j];
        if(distance(pp,p)<distance(p,c2[m]) ){m= j;}}
    return m;
}
uint close( uint s,inout vec2 c2[MAX_DIR],inout uint si ,inout uint t[MAX_DIR],uint s0 ,uvec2 lim1){
    for(uint j=s0;j<si+s0;j++){
        vec2 pp = c2[j];
        t[j-s0] = close(pp,s,c2,s1,e1); 
    }
}
uvec2 close( uint s,inout vec2 c2[MAX_DIR], uint uvec2 lim0,uvec2 lim1){
    uvec2 pm;
    for(uint j=lim.x;j<=lim.y;j++){
        vec2 pp = c2[j];
        uint c = close(pp,s,c2,lim1);
        if(distance(pp,c2[c]) < distance(pm[c2.y],pm[c2.x] )) { pm = {j , c}} 
    }
    return pm;
}
uint close(uint s,inout vec2 ps[MAX_DIR],uint p,uvec2 lim){
uint cls=  lim.x; float d= distance(ps[p],ps[lim.x]);

    for(uint i=lim.x+1;i<=lim.y;i++){
        float ds = distance(ps[i],ps[p])
        if(ds < d){d=ds;cls=i;}
    }
    return i;
}


uvec2 closest(uint si , vec2 c1[MAX_DIR], uint s,inout vec2 c2[MAX_DIR],uvec2 lim){
    uvec2 clMin ;
    for(uint i=0;i<si;i++){
        uvec2 cl= {c1[i],c2[lim.x]}
        vec2 p = c1[i];
        uint t = close(p,s,c2,lim);
        if(distance(p,c2[lim.x+t]) < distance(c1[clMin.x] , s2[lim.x+clMin.y]) ){clMin={i,t}}
    }
    return clMin;
}
bool selfIntersect(uint si, inout vec2 c[MAX_DIR], uint pt, vec2 p){
    vec2 p = c[pt];
    for(uint i=pt+2; i<si ;i++){
        vec2 p1= c[i]; vec2 p2 = c[i-1];if(intersectSegSeg({p1,p2},{p,p})){return 1;}
    }
    for(uint i=pt-2; i>=0 ;i--){
        vec2 p1= c[i]; vec2 p2 = c[i-1];if(intersectSegSeg({p1,p2},{p,p})){return 1;}
    }
return 0;
}
bool selfInter(uint si,inout vec2 c[MAX_DIR],uint p1,uint p2,uvec2 lim){
    uint j=lim.x;
    vec2 mid = (c[p1] + c[p2]) /2;
    uint count = 0;
    vec2 midC = (lim.x+ lim.x+1)/2; 
    mat2x2 seg = {mid,midC}
    for(uint i=lim.x+1;i<=lim.y;i++){if(intersectSegSeg({c[j],c[i]},{c[p1],c[p2]})){return 1;}
        j=i;
        mat2x2 segc = {c[i],c[i-1]}
        if(intersectSeg(seg,segc)) {count++;}
    }
    return 0;
}
bool selfInter(uint si,inout vec2 c[MAX_DIR],uint p1,vec2 p2,uvec2 lim){
    uint j=lim.x;
    for(uint i=lim.x+1;i<=lim.y;i++){if(intersectSegSeg({c[j],c[i]},{c[p1],p2})){return 1;}
        j=i;}
    return 0;
}
bool angleGood(uint s,inout vec2 pts[MAX_DIR],uint pa,uint pb,uint cur_a,uint cur){
    return !intersectSeg(mat2x2(pts[pa],pts[pb]),mat2x2(pts[cur_a],pts[cur])) ;}


bool angleGood(uint s,inout vec2 pts[MAX_DIR],uint pa,uint pb,uint cur_a,vec2 p){
    return !intersectSeg(mat2x2(pts[pa],pts[pb]),mat2x2(pts[cur_a],p)) ;}

void vemit(vec2 p){gl_Position = vec4(p,0,0);EmitVertex();}
void incr(inout uint i ,uvec2 lim,int incr ){
    i+=incr;
    if(i<lim.x){i=lim.y}
    if(i>lim.y){i=lim.x}
}

void incri(inout uint i ,uvec2 lim,uvec2 bound,int incr ){
    if(incr == -1){if(i==bound.x){i=bound.y;return;}
    if(i==lim.x){i=lim.y;return;}}
    if(incr == 1){if(i==bound.y){i=bound.x}return;
    if(i==lim.y){i=lim.x;return}}
    i+=incr;
}
ivec2 Mindif(uvec2 lim,uint i1,uint i2){
    uint i=i1;int incr=1;
    int d=0;
    for(;i!=i1;incr(i,lim,incr);d+=incr){}
    int dm=0 ;i=i1;incr=-1;
    for(;i!=i1;incr(i,lim,incr);d+=incr){}
    return abs(d)<abs(dm)?{d,1}:{dm,-1}
}



void tip(uint s,inout vec2 pts[MAX_DIR] ,uvec2 ps, uvec2 l ){
    vemit(pts[ps.x]);vemit(pts[ps.y]);
    uint indy = lim.y;uint prev=lim.x;bool start=1;uint i=lim.x;incr(i,l,1)
    float xa;float xb ;
    uint prev_ap = lim.x;uint prev_bp = lim.y;
    while(i<=indy){
            if( start && angleGood(s,pts,pts[prev_bp],pts[indy],pts[prev_ap],pts[i]) && !selfInter(s,pts,prev_bp,i,lim)  ){
                vemit(pts[i]);prev_ap = i; incr(i,l,1);start=0;}
            else {start=1;
                if(angleGood(s,pts,pts[prev_ap],pts[i],pts[prev_bp],pts[indy]) && !selfInter(s,pts,prev_ap,indy,lim)){
                    vemit(pts[indy]);prev_bp=indy;start=1; incr(indy,l,-1);}
                else {uint ind = indy-1 ;for(;selfInter(s,pts,prev_ap,ind,lim);incr(ind,l,-1)){}
                    vemit(pts[ind]);
                    EndPrimitive();tip(s,pts,uvec2(ind,indy));
                    prev=last;last=ind;                
                    vemit(pts[ind]);
                }}
    }
    EndPrimitive();
}

void normBound(inout uvec2 b){b = b.x<b.y? b : b.yx;}
uvec2 findTip(uint s,inout vec2 pts[MAX_DIR],uvec2 lim,uint i,int incr,vec2 pt){
    uint ii = i;
    for(;selfInter(s,pts,ii,pt,lim) ;incr(ii,lim,incr)){}
    return uvec2(ii,i);
}

bool insideN(uint p1,uint p2, uint s,inout vec2 pts[MAX_DIR],uvec2 lim1, uvec2 bound1, uint incr1){
    uint i=p1;
    incr(i,bound1, incr1);
    uint last = i; 
    for(incr(i,bound1,incr1);i!=p1;incr(i,bound1,incr1)){
        if(intersectSeg(mat2x2(pts[last],pts[i]),mat2x2(pts[p1],pts[p2]))){return 0;}
    }
    return 1;
}
bool inside(uint p1,uint p2, uint s,inout vec2 pts[MAX_DIR],uvec2 lim1,uvec2 lim2, uvec2 bound1,uvec2 bound2, uint incr1,uint incr2){
    if(insideN(p1,p2,s,pts,lim1,bound1,incr1)){
        return insideN(p1,p2,s,pts,lim2,bound2,incr2)
    }
    return 0;
}


void pass(uint s,inout vec2 pts[MAX_DIR],uint start1,uint start2,uvec2 lim1,uvec2 lim2;uvec2 bound1,uvec2 bound2,int incr1,int incr2){
    uint i1,ind1,i2,ind2;
    i1=start1;i2=start2;
    uint end1=bound1.x != start1?bound1.y :bound1.x ;uint end2=bound2.x!=start2?bound2.y:bound2.x; 
    vemit(pts[i1]);vemit(pts[i2]);ind1 = i1;ind2=i2;incr(ind1,lim1,bound1,incr1);incr(ind2,lim2,bound2,incr2);
    for(;ind1!=lim1.y && ind2 != ;incr(ind1,bound1,incr1)){
            if(start) {if (angleGood(s,pts,i2,i1,ind2,ind1)){
                vemit(pts[ind1]);i1 = ind1;incr(ind1,bound1,incr1);start=0;continue;}
                else {if(!stop){start=0;stop=1;continue;}}
            }  
            else {
                if( angleGood(s,pts,i1,i2,ind1,ind2)){
                    vemit(pts[ind2]);i2 = ind2;incr(ind2,bound2,incr2);start=1;}
                else {if(!stop){start=0;stop=1;continue;}}
            }
            if(stop){
                if(inside(ind1,ind2,s,pts,bound1,bound2,lim1,lim2,incr1,incr2) ){
                    vec2 mid= (pts[ind1] + pts[ind2])/2;
            if(start){
                                    vemit(mid);vemit(pts[i1]) ; 
                                    vemit(pts[ind1]);i1=ind1;incr(ind1,bound1,incr1);vemit(pts[ind2]);
                                    incr(ind1,bound1,incr1);start=0;}
            else {
                                    vemit(mid);vemit(pts[i2]) ; 
                                    vemit(pts[ind2]);i2=ind2;incr(ind2,bound2,incr2);vemit(pts[ind1]);
                                    incr(ind2,bound2,incr2);start=1;}                   
            }}
            else {
            if(start){
                vec2 mids[sb1] ;uint ss = 0;mids[ss] = (pts[ind1] + pts[i1])/2;
                for(mids[ss]=( mids[ss-1] + pts[i1])/2;!angleGood(s,pts,i2,i1,ind2,mids[ss]) && ss!=sb1;ss++){
                    mids[ss]=( mids[ss-1] + pts[i1])/2;}
                if(ss==sb1){
                    uvec2 tip = findTip(s,pts,bound1,incr1);
                    tip(s,pts,tip);                 
                }
                else {for(uint i=ss;i>=0;i++){vemit(mids[i]);vemit(pts[i2]);}}              
                }
            else {
                 vec2 mids[sb2] ;uint ss = 0;mids[ss] = (pts[ind2] + pts[i2])/2;
                for(mids[ss]=( mids[ss-1] + pts[i2])/2;!angleGood(s,pts,i1,i2,ind1,mids[ss]);ss++){
                    mids[ss]=( mids[ss-1] + pts[i2])/2;}
                if(ss==sb2){uvec2 tip = findTip(s,pts,bound2,incr2);
                    tip(s,pts,tip);                 
                }
                else {for(uint i=ss;i>=0;i++){vemit(mids[i]);vemit(pts[i1]);}}              
                }
            }
    }
}

void pass(uint s, inout vec2 pts[MAX_DIR],uvec2 bound1,uvec2 bound2,  uvec2 lim1,uvec2 lim2){
    uint si1=lim1.y-lim1.x+1;uint si2=lim2.y-lim2.x+1;
    uint sb1 = bound1.y>bound1.x? bound1.y- bound1.x+1 :(lim1.x- bound1.x) + bound1.y + 2;
    uint sb2 = bound2.y>bound2.x? bound2.y- bound2.x+1 :(lim2.x- bound2.x) + bound2.y + 2;
    bool rev = 0;
    if(distance(pts[lim1.x] , pts[lim2.x]) > distance(pts[lim1.x] , pts[lim2.y])){rev=1;}
    int incr2;uint e2; 
    if(rev){incr2=-1;e2 = lim2.y;}
    else {incr2=1;e2=lim2.x;}
    int incr1 = 1;
    uint ind2 = lim2.y;
    uint ind1=lim1.x;
    pass(s,pts,sb1,sb2,lim1,lim2,bound1,bound2,incr1,incr2); 
}
uvec2 findPass(uint s,inout vec2 pts[MAX_DIR],uint b1,uint b2,uvec2 lim1,uvec2 lim2){
    uint incr1=1;uint incr2 = -1;
    uint r1=b1;r2=b2;
    for(incr(r1,lim1,incr1);r1!=b1 ;incr(r1,lim1,incr1)){
        if(selfInter(s,pts,r1,r2,lim1)){
            for(incr(r1,lim1,incr1);!selfInter(s,pts,r1,r2,lim1) ;incr(r1,lim1,incr1) ){}
        }
        
        for(;selfInter(s,pts,r1,r2,lim2) ; incr(r2,lim2,incr2) ){} 
        }
    return {r1,r2}
}
uvec2 tipInter(uint s,inout vec2 pts[MAX_DIR],uvec2 lim,uint ptcur,uint lastPt){

}
void getPass(uint s ,inout vec2 pts[MAX_DIR],uvec2 lim1,uvec2 lim2,inout uvec2 bound1,inout uvec2 bound2, uint si,uint MaxSi,uvec2 cls[MAX_CONT][MAX_CONT],uvec2 curPair){
    uvec2 clssL={curPair.y,bound2.x} uint t=0;uint j;bool brk=0;
    for(j=bound1.y;j!=bound1.x ;incr(j,lim1,1)){
        uvec2 clss=cls[curPair.x][t];
        if(clss.x != curCls.x){break;}
        ivec2 dif =Mindif(lim2,clss.y , clssL.y) ;
            for(uint ind = clssL.y; ;incr(ind,lim2,-1)){
                if(selfInter(s,pts,ind,j,lim1)){
                    uint indi=j;
                    while(selfInter(s,pts,ind,j,lim1) && j!=bound1.x){incr(j,lim1,1);}
                    if(j!=bound1.x){tip(s,pts,{indi,j},lim1);}
                    else {brk=1;break;}
                }
                else if(selfInter(s,pts,ind,j,lim2)){
                    uint indi=ind;
                    for(;selfInter(s,pts,ind,j,lim2) && ind!=bound1.y;){incr(ind,lim2,-1);}
                    if(ind!=bound1.y){tip(s,pts,{indi,j},lim2);}
                    else {brk=1;break;}

                    tip(s,pts,{indi,ind},lim2);
                }
                else {vemit(pts[ind]);vemit(pts[j]);}
                if(ind!=clss.y){break;}
            }   
        if(brk){break;}
        t++;clssL = clss;
    }
    bound1.x = bound1.y ; bound1.y= j;
    bound2.x=bound2.y;bound2.y=clssL.y;
}
bool coveredAll(uint si,uvec2 lims[MAX_CONT],uvec2 bounds[MAX_CONT]){
    for(uint i=0;i<si;i++){if(bounds.y!=bounds.x){return 0;}}
    return 1;
}
void insides(uint s, inout vec2 pts[s],uint si,inout uvec2 lims[MAX_CONT],inout uvec2 bounds[MAX_CONT] ,uint sip,inout uint pairs[MAX_CONT]  ){
    
    
    uint MaxSi=0 ;uint sibs[MAX_CONT];
    for(uint i=0;i<si;i++){uint s=bounds[i].y -bounds[i].x+1;sibs[i]=s; if(s>MaxSi){MaxSi=s;}}

    uvec2 cls[MAX_CONT][MAX_CONT];
    for(uint i=0;i<si;i++){uint it=0;
        for(uint k=bounds[i].x;k<=bounds[i].y;incr(k,lims[i],1);){
            uvec2 clMin; float dMin;
            for(uint j=0;j<si;j++){if(j==i){continue;}
                uint cl = close(s,pts,j,lims[j]);
                float d= distance(pts[k],cl);
                if(d<dMin){dMin=d;clMin={j,cl}}
            }
            cls[i][it]=clMin;it++;
        }
    }

    for(;!coveredAll(si,lims,bounds);){
        uvec2 curPair={pairs[si-1],pairs[0]}
        getPass(s,pts,lims[curPair.x],lims[curPair.y],bounds[curPair.x],bounds[curPair.y],si,MaxSi,cls,curPair);
        for(uint i=0;i<psize-1;i++){
            curPair={pairs[i],pairs[i+1]}
            getPass(s,pts,lims[curPair.x],lims[curPair.y],bounds[curPair.x],bounds[curPair.y],si,MaxSi,cls,curPair);
        }
        uint pairs1[si] ; uint sizeInner=0; 
        uvec2 lastCls=cls[pairs[0]][0];
        for(uint i=0;i<psize-1;i++){
            lastCls=cls[pairs[i]][0];
                uint lastJ=bounds[pairs[i]].x;
                for(uint j=bounds[pairs[i]].x;j!=bounds[pairs[i]].y;incr(j,lim[pairs[i]],1)){
                uvec2 curCls=cls[pairs[i]][j]; 
                if(curCls.x != lastCls.x){pairs1[sizeInner] = curCls.x;sizeInner++;
                    for(;!selfInter(s,pts,lastJ,lastCls.y,lims[lastCls.x]); incr(lastCls.y,lims[lastCls.x],1)){
                        vemit(pts[lastJ]);vemit(pts[lastCls.y]);}
                    uint curCl = curCls.y;
                    for(;!selfInter(s,pts,j,curCl,lims[curCls[x]]);incr(curCl,lims[curCls[x]],-1)){}
                    for(;curCl!=curCls.y;incr(curCl,lims[curCls[x]]),1){vemit(pts[j]);vemit(pts[curCl]);}
                    vemit(pts[j]);vemit(pts[curCls.y]);}
                else {
                    uint lastPt=lastCls.y;
                    if(!selfInter(s,pts,lastCls.y,j,lims[lastCls.x])){
                        vemit(pts[j]);
                    }
                    for(uint x = lastCls.y;;incr(x,lims[curCls.x],1)){
                        if(!selfInter(s,pts,x,j,lims[lastCls.x])){
                            vemit(pts[j]);vemit(pts[x]);                             
                        }else {uint xx = x;
                            for(;selfInter(s,pts,x,j,lims[lastCls.x]); incr(x,lims[curCls.x],1)){}
                            tip(s,pts,{xx,x},lims[curCls.x]);
                            vemit(pts[j]);vemit(pts[x]);
                        }
                        
                        if(x==curCls.y){break;}
                    }
                }
                lastCls=curCls;lastJ = j;
            }
        }
        for(uint i=0;i<sizeInner;i++){pairs[i]=pairs1[i];psize=sizeInner+1;}
    }
}


void primOut(uint ind,uint inds[MAX_CONT] , uint size){
    uint smax=0;
    uint scont = getSize(ind);
    vec2 cont[MAX_CONT]; tesselate(ind,scont,cont) ;
    uint fullSize=0;

    uvec2 lims[MAX_CONT] ;for(uint i=0;i<size;i++){lims[i]=uvec2(fullSize+1,0);fullSize+=getSize(inds[i]);endPs[i].y=fullSize;} 
    uint endPs[MAX_CONT];for(uint i=0;i<size;i++){fullSize+=getSize(inds[i]);endPs[i]=fullSize;}
    vec2 conts[MAX_DIR];
    
    if(fullSize == 0){tip(scont,cont,uvec2(0,scont-1)); return ;}

    for(uint i=0;i<size;i++){
        uint start =(i==0 ? 0 : endPs[i-1]) + 1;
        uint si = endPs[i] - start+1;
        vec2 pts[si];
        tesselate(inds[i],si,pts);
        for(uint j=0;j<si;j++){conts[start+j]=pts[j];}
    }
    uvec2 cls[scont];for(uint i=0;i<scont;i++){cls[i]={-1,-1}}
    for(uint i=0;i<scont;i++){
        uvec2 clMin={0,0}vec2 p = cont[i];
        for(uint j=0;j<size;j++){
            uvec2 lim = lims[j];
            uint cl = close(p,fullSize,conts,lim);
            if(distance(cont[i] ,conts[clMin]) <
               distance(cont[i] , conts[cl[0]] ) && selfIntersect(scont,cont,i,conts[cl])){clMin = {j,cl;}}
        }
        cls[i]=clMin;
    }
   
    uvec2 bounds[MAX_CONT];bounds=lims;

    uint pairs[MAX_CONT] ;
    uvec2 lim = uvec2(0,scont-1); 
    uint sizeInners=1;uvec2 close = cls[0];pairs[0]=close.x; uint sizeInner;
    for(uint i=0;i<scont;i++){
        if(cls[i].x != close.x){
            close = cls[i];pairs[sizeInners]=close.x;sizeInners++;
            bounds[close.x] = {close.y,close.y}
            }
        else {
            uint dif = close.y- cls[i].y ;
            if(dif>1){ i--;
                for(uint j=0;i<dif;j++){
                    if(!selfIntersect(fullsize,conts,cls[i+j].y,cont[i])){
                        vemit(conts[cls[i+j]]);}
                    else {i++; }
                }
            }
            else { 
                if(!selfIntersect(scont,cont,i,conts[cls[i].y])){vemit(conts[cls[i].y]);vemit(cont[i]);}
                else {
                    EndPrimitive();
                    uvec2 tipB = findTip(scont,cont,uvec2(0,scont-1),i,conts[cls[i].y] );tip(scont,cont,tipB);
                    vemit(conts[cls[i-1].y]);vemit(cont[tipB.x]);vemit(cont[tipB.x]);
                    vemit(conts[cls[i-1].y]);
                    vemit(conts[cls[i].y]);vemit(cont[tipB.x]);
            }    
            for(uint i=0;i<dif;i++){incr(bounds[close.x].y,lims[close.x],1); }
        }
    }
    }
    for(uint i=0;i<sizeInners){bounds[i]={bounds[i].y,bounds[i].x}}
    uint prs[MAX_CONT];for(uint i=0;i<sizeInners;i++){prs[i]=pairs[i];}
    insides(fullSize, conts,size,lims,bounds,sizeInner,prs);
}

void strips(uint ind,uint endSel){
   
/// Get directs;
uint start= ind==0?0:endPts.p[ind-1]+1;
uint end;
for(uint j=ind;j<=endSel;j++){
uint end= endPts.p[j];

    uint sizeDirs=0;
    uint dirs[p.numCon];

    uint start2 = end+1;
    uint end2= endPts.p[j+1]  ;uint k; uint endInsides=0;
    for(k = j+1;k<=endSel && isInside(pspts[end2],start,end);){
        end2 = endPts.p[k];
        dirs[sizeDirs]=pspts[end2];sizeDirs++;uint h;
    for(k=k+1;k<endSel && isInside(pspts[end2],start2,end2);k++){
        end2  = endPts.p[k];
        start2 = end2+1;}
        j=k-1;
    for(;k<=endSel && !isInside(pspts[end2],start,end);k++){
        end2 = endPts.p[k];
        start2 = end2+1;}
        start2 = end2+1;
    }
    primOut(j,dirs,sizeDirs);
    for(uint i=0;i<sizeDirs;i++){
        if(isInside(pspts[i+1],endPts.p[dirs[i]-1 ]+1,endPts.p[dirs[i]])){
            strips(i+1,j);
        }
    }
    start = end+1;
}
       
}


void main(){
    s=p.size;
    for(uint i=0;i<p.size;i++){OnCP[i]=0;}
    for(uint i=0;i<p.numOnCurves;i++){OnCP[onCurve.p[i]] = 1;}
    uvec2 bound={0,endPts.p[0]}
    float rad = winding(bound);
    for(uint i=0;i<p.numCon;i++){
        bound = {bound.y+1,endPts.p[i]}
        float r = winding(bound);
        if(sign(r)!=sign(rad)){uint k=0;uint size = bound.y-bound.x+1;
            uint k=bound.y;
            for(uint j = bound.x;j<=bound.y-size/2;j++){
                vec2 t = pspts[j];pspts[j]=pspts[k];pspts[k] = t;
                k--;
            }
        }
    }
    strips(0,p.numCon-1);
} 