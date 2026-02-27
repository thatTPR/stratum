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
layout(std430, set=0,binding=2) buffer pts{
    uint p[];//[numCon]
}endPts;
layout(std430, set=0,binding=3) buffer ptss{
    uint p[];//[numOnCurves]
}onCurve;
// layout(std430,set=0,binding=4) buffer ps{vec2 pts[];} ;
bool OnCP[MAX_PRIM];
struct glyf {
    ivec2 pos;
    int   xMin;
    int   yMin;
    int   xMax;
    int   yMax;
};
layout(location=0 ) flat out bool gsFill;




layout(triangle_strip, max_vertices = 100) out;


layout (location=1)out glyf glyfInfo; 

const uint tess = 3;



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
    uint tessNum = t-2;
    vec3 centRad = getCenter(pta,ptb,ptOnc);
    float r =centRad.z;
    vec2 center=  vec2(centRad.x,centRad.y);
    for(uint i=0;i<=tessNum;i++){ uint te = i/(tessNum);
        pts[ind+i]= 
        ptOnCircle(pta,ptb,te,center,r);
    }
}

vec3 getCenter(vec2 centLast,vec2 ptLast,vec2 pt1,vec2 pt2){
    vec2 l = line(centLast,ptLast);
    vec2 l1 = line(pt1,pt2);
    vec2 mid = (pt2+pt1)/2;
    vec2 perpp = perpendicular(l1,mid); 
    vec2 center = intersect(perpp,l);
    return vec3(center,distance(pt1,center)); 
}
#define PTSONC_MAX 1000
void arctesselate(uint s,vec2 ptsonc[PTSONC_MAX],uint t,inout vec2 pts[TESSC_MAX]){
uint tessNum = t-2;uint inds=0;
vec2 pta;vec2 ptb;
vec2 ptOnc;vec3 centRad;float r;
vec2 oa;vec2 oonc;
vec2 center;
    for(uint i=0;i<min(s-2 , PTSONC_MAX);i++){
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
            pts[inds] = (to+tb)/2 + center;
            inds++;
        }
    inds++;pts[inds] = ptb;
}

uint binomial(uint n,uint k){
    uint res;
    uint st=1;
    for(uint i=k+1;i<=n;i++){
        res*=i;
        if(st<=n-k){if(i%st == 0){res/=st;st++;}}
    }
    for(uint i=st;st<=n-k;i++){res/=i;}
    return res;
}

void computeTrue(uint s,inout vec2 pts[TESSC_MAX]){
        vec2 cur = pts[0];
        vec2 prev = cur;
        for(uint i=1;i<min(s,TESSC_MAX);i++){
        vec2 mid = (prev + pts[i+1])/2;
            cur = pts[i];
            pts[i] = (cur - mid)*2 + cur;
            prev = cur;
        }
}

void tesselate(uint s,inout vec2 ptsonc[TESSC_MAX],uint stess,inout vec2 pts[TESSC_MAX]){

    computeTrue(s,ptsonc);
    //formula  : B(t) = sum(i,n){ bin(n,i)* (1-t)^(n-i)t^i*Pi }

    uint tessnum = stess+2;uint si = min(s,TESSC_MAX) ;
  for(uint i = 1;i<=tessnum-1;i++){float t = i/tessnum ;
        vec2 r;
        for(uint j =0;j<si;j++){
            r+=binomial(si,j)* pow((1-t),(si-i))*pow(t,j)*ptsonc[j];
        }
        pts[i-1] =r;
    }
}
void tesselate(uint ind,inout uint size ,inout vec2 pts[MAX_CONT]){
    uint curind=0;
    uint start = ind>0?endPts.p[ind-1] : 0;
    uint end = endPts.p[ind];
    uint j=0;
    bool wrap= false  ;vec2 lastPt =pts[end] ;
    if(OnCP[start]==true){wrap=true;}

    for(uint i=start;i<end;i++){
        uint startInd=i;    
        for(;OnCP[i] && (i<end);i++ ){j++;}
        if(i!=startInd){
            uint s=i-startInd + 1;
            vec2 ptsonc[PTSONC_MAX];ptsonc[0]=pspts[end];
            for(uint j=1;j<s;j++){
                ptsonc[j] = pspts[startInd+j];}
            uint tesst = (s+1)*tess ;vec2 ptst[TESSC_MAX];
            arctesselate(s,ptsonc,tesst,ptst);
            for(uint j=0;j<tesst;j++){pts[curind]=ptst[j];curind++;}
        }
        else {pts[curind]=lastPt;curind++;}
        lastPt = pts[i];
    }
    size=curind;
}
uint getSize(uint ind){uint size=0;
    uint start = ind>0?endPts.p[ind-1] : 0;
    uint si = endPts.p[ind] - start+1;uint j=0;
    for(uint i=0;i<si;i++){if(OnCP[start+i]){for(;OnCP[start+i];i++){j++;} continue;} else {size++;}}
    size+=(1+j)*tess; 
    return size;
}

#define MAX_DIR 1000
uint close( vec2 p, uint s,inout vec2 c2[MAX_DIR],uvec2 lim){
    uint m = lim.x;   
    for(uint j=lim.x;j<=lim.y;j++){
        vec2 pp = c2[j];
        if(distance(pp,p)<distance(p,c2[m]) ){m=j;}};
    return m;
}
void close( uint s,inout vec2 c2[MAX_DIR],inout uint si ,inout uint t[MAX_DIR],uint s0 ,uvec2 lim1){
    for(uint j=s0;j<si+s0;j++){
        vec2 pp = c2[j];
        t[j-s0] = close(pp,s,c2,lim1); 
    }
}

uvec2 close( uint s,inout vec2 c2[MAX_DIR], uvec2 lim0,uvec2 lim1){
    uvec2 pm=uvec2(lim0.x,lim0.y);
    for(uint j=lim0.x;j<=lim1.y;j++){
        vec2 pp = c2[j];
        uint c = close(pp,s,c2,lim1);
        if(distance(pp,c2[c]) < 
        distance(c2[pm.y],c2[pm.x] ) ){ pm = uvec2(j , c);} 
    }
    return pm;
}
uint close(uint s,inout vec2 ps[MAX_DIR],uint p,uvec2 lim){
uint cls=  lim.x; float d= distance(ps[p],ps[lim.x]);
    uint i;
    for( i=lim.x+1;i<=lim.y;i++){
        float ds = distance(ps[i],ps[p]);
        if(ds < d){d=ds;cls=i;}
    }
    return i;
}


uvec2 closest(uint si , vec2 c1[MAX_DIR], uint s,inout vec2 c2[MAX_DIR],uvec2 lim){
    uvec2 clMin ;
    for(uint i=0;i<si;i++){
        // uvec2 cl= {c1[i],c2[lim.x]}
        vec2 p = c1[i];
        uint t = close(p,s,c2,lim);
        if(distance(p,c2[lim.x+t]) < distance(c1[clMin.x] , c2[lim.x+clMin.y]) ){clMin=uvec2(i,t);}
    }
    return clMin;
}
bool selfIntersect(uint si, inout vec2 c[MAX_DIR], uint pt, vec2 p){
    vec2 pp = c[pt];
    for(uint i=pt+2; i<si ;i++){
        vec2 p1= c[i]; vec2 p2 = c[i-1];if(intersectSegSeg(mat2x2(p1,p2),mat2x2(p,pp)) == true){return true;}
    }
    for(uint i=pt-2; i>=0 ;i--){
        vec2 p1= c[i]; vec2 p2 = c[i-1];if(intersectSegSeg(mat2x2(p1,p2),mat2x2(p,pp)) == true){return true;}
    }
return false;
}
bool selfInter(uint si,inout vec2 c[MAX_DIR],uint p1,uint p2,uvec2 lim){
    uint j=lim.x;
    vec2 mid = (c[p1] + c[p2]) /2;
    uint count = 0;
    vec2 midC = (c[lim.x]+ c[lim.x+1])/2; 
    mat2x2 seg = {mid,midC} ;
    for(uint i=lim.x+1;i<=lim.y;i++){if(intersectSegSeg(mat2x2(c[j],c[i]),mat2x2(c[p1],c[p2])) == true){return true;}
        j=i;
        mat2x2 segc = {c[i],c[i-1]} ;
        if(intersectSeg(seg,segc)) {count++;}
    }
    return false;
}
bool selfInter(uint si,inout vec2 c[MAX_DIR],uint p1,vec2 p2,uvec2 lim){
    uint j=lim.x;
    for(uint i=lim.x+1;i<=lim.y;i++){if(intersectSegSeg(mat2x2(c[j],c[i]),mat2x2(c[p1],p2)) == true){return true;}
        j=i;}
    return false;
}
bool angleGood(uint s,inout vec2 pts[MAX_DIR],uint pa,uint pb,uint cur_a,uint cur){
    return !intersectSeg(mat2x2(pts[pa],pts[pb]),mat2x2(pts[cur_a],pts[cur])) ;}


bool angleGood(uint s,inout vec2 pts[MAX_DIR],uint pa,uint pb,uint cur_a,vec2 p){
    return !intersectSeg(mat2x2(pts[pa],pts[pb]),mat2x2(pts[cur_a],p)) ;}

void vemit(vec2 p){gl_Position = vec4(p,1,1);EmitVertex();}

void incr(inout uint i ,uvec2 lim,int incr ){
    if(incr>0){if(i==lim.y){i=lim.x;return;}}
    if(incr<0){if(i==lim.x){i=lim.y;return;}}
    i+=incr;
}

void incri(inout uint i ,uvec2 lim,uvec2 bound,int incr ){
    if(incr == -1){if(i==bound.x){i=bound.y;return;}
    if(i==lim.x){i=lim.y;return;}}
    if(incr == 1){if(i==bound.y){i=bound.x;return;}
    if(i==lim.y){i=lim.x;return;}}
    i+=incr;
}
ivec2 Mindif(uvec2 lim,uint i1,uint i2){
    uint i=i1;int inc=1;
    int d=0;
    for(;i!=i1;incr(i,lim,inc),d+=inc){}
    int dm=0 ;i=i1;inc=-1;
    for(;i!=i1;incr(i,lim,inc),d+=inc){}
    return abs(d)<abs(dm)?ivec2(d,1):ivec2(dm,-1) ;
}

void tip(uint s,inout vec2 pts[MAX_CONT] ,uvec2 ps ,bool ins){
    vemit(pts[ps.x]);vemit(pts[ps.y]);
    uvec2 lim = {0,s-1};
    uint indy = lim.y;uint prev=lim.x;bool start=1;uint i=lim.x;incr(i,lim,1);
    float xa;float xb ;
    uint prev_ap = lim.x;uint prev_bp = lim.y;
    while(i<=indy){
            if( start && angleGood(s,pts,pts[prev_bp],pts[indy],pts[prev_ap],pts[i]) && !selfInter(s,pts,prev_bp,i,lim)  ){
                vemit(pts[i]);prev_ap = i; incr(i,l,1);start=0;}
            else {start=1;
                if(angleGood(s,pts,pts[prev_ap],pts[i],pts[prev_bp],pts[indy]) && !selfInter(s,pts,prev_ap,indy,lim)){
                    vemit(pts[indy]);prev_bp=indy;start=1; incr(indy,l,-1);}
                else {uint ind = indy-1 ;for(;selfInter(s,pts,prev_ap,ind,lim);incr(ind,lim,-1)){}
                    vemit(pts[ind]);
                    EndPrimitive();tip(s,pts,uvec2(ind,indy),lim,ins);
                    prev=ind;                
                    vemit(pts[ind]);
                }}
    }
    gsFill = !ins;
    EndPrimitive();
}

void normBound(inout uvec2 b){b = b.x<b.y? b : b.yx;}

bool isInside(uint s,inout vec2 pts[MAX_CONT],vec2 p){
    
    uint count=0;
        vec2 cur = pts[s-1];
        vec2 next = pts[0];
        vec2 midPt = (cur + next)/2;

        mat2x2 firstPtSeg = mat2x2(midPt,p) ;        
    count = 0;
    for(uint i=0;i<s;i++){
        cur= pspts[i];
        next= pspts[i+1];
        mat2x2 seg=mat2x2(cur,next);
        if(intersectSeg(firstPtSeg,seg)){count++;}
    }
    
    return (count%2)==1;
}
uvec2 PerpInter(uint s,inout vec2 pts[MAX_CONT],uint ind,inout vec2 p){
    vec2 prev=ind>0?pts[ind-1]:pts[s-1];
    vec2 next=ind<(s-1)?pts[ind+1]:pts[0];
    mat2 line = mat2(pts[ind],(prev+next)/2); 
    mat2 seg = mat2(pts[0],pts[s]);
    vec2 ps  ; uvec2 ret={0,1};
    for(uint i=0;i<s-1;i++){
        mat2 seg = mat2(seg[1],pts[i]);
        if(intersectSeg(line,seg)){
            ps = intersect(line,seg);
            vec2 mid = (ps + pts[ind])/2;
            if(isInside(s,pts,mid)){
                if(distance(pts[ind],ps)<distance(pts[ind],p)){p = ps;ret=uvec2(i,i+1);}
            }
        }
    }
    if(ret.x==s-1){ret.y=0;}
    return ret;
};
/*
void _Contour(uint s,inout vec2 pts[MAX_CONT]){

    vec2 p[MAX_CONT];
    uvec2 inds[MAX_CONT];
    for(uint i=0;i<s;i++){inds[i] = PerpInter(s,pts,i,p[i]);};
    vemit(pts[s-1]);
    for(uint j=0;j<s-1;j++){
        vemit(pts[j]);
        vemit(p);
    }
    EndPrimitive();
}
*/

void Contour(uint s,inout vec2 pts[MAX_CONT],bool ins){tip(s,pts,uvec2(0,s-1),ins);};

void primOut(uint ind,uint inds[MAX_CONT] , uint size){
    uint smax=0;
    uint scont = getSize(ind);
    vec2 cont[MAX_CONT]; tesselate(ind,scont,cont) ;Contour(scont,cont,false);
    uint fullSize=0;

    uvec2 lims[MAX_CONT] ;for(uint i=0;i<size;i++){lims[i]=uvec2(fullSize+1,0);fullSize+=getSize(inds[i]);endPs[i].y=fullSize;} 
    uint endPs[MAX_CONT];for(uint i=0;i<size;i++){fullSize+=getSize(inds[i]);endPs[i]=fullSize;}
    vec2 conts[MAX_DIR];
    
    for(uint i=0;i<size;i++){
        uint start =(i==0 ? 0 : endPs[i-1]) + 1;
        uint si = endPs[i] - start+1;
        vec2 pts[MAX_CONT];
        tesselate(inds[i],si,pts);
        Contour(si,pts,true);
    }
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
    uvec2 bound={0,endPts.p[0]};
    float rad = winding(bound);
    for(uint i=0;i<p.numCon;i++){
        bound = uvec2(bound.y+1,endPts.p[i]);
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