

struct prim {
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
    vec2 pts[size];    
}




layout(std430, set=0,binding=1) buffer prim p;
layout(std430, set=0,binding=2) buffer endPts{
    uint p[];//[numCon]
};
layout(std430, set=0,binding=2) buffer onCurve{
    uint p[];//[numOnCurves]
};


#define MAX_SIZE 10000
struct primOut {
    uint size;
    // uint ends[p.numCon];
    // bool fill[p.numCon]
    vec2 pts[MAX_SIZE] ;
    // vec2 pts[p.size + tessNum * p.numOnCurves] ;
};

primOut tessCon; 

layout(binding=2) buffer primOut triangles  ;
layout(binding=3) buffer ends {
    uint p[];
}
layout(binding=4) buffer fillOut {
    uint p[];
}



float slope(vec2 left,vec2 center,vec2 right){
    vec2 x = center - left +(right - center);
    return x.y/x.x; 
}
vec2 ovec(float t){
    return vec2(1,t);
};
vec2 ovec(mat2x2 i){
    vec2 r = i.y - i.x;
    return r; 
};

float der(vec2 o){return o.y/o.x }


bool intersect(mat2x2 line , mat2x2 seg){
    vec2 ol = ovec(line) ;
    mat2x2 os = mat2x2(seg.x - line.x,seg.y -line.x)  ;

    float dx = der(os.x);
    float dy = der(os.y);

    float dl = der(ol);

    return dx<dl ? dl<dy : ((dy<dl) ? true : false);
};
bool isInside(vec2 pt,uint indFirst,uint indLast){
    
    uint count=0;
        vec2 cur = curved.pts[indLast];
        vec2 next = curved.pts[indFirst];
        vec2 midPt = (cur + next)/2;

        mat2x2 firstPtSeg = mat2x2(midPt,pt) ;        
    count = 1;
    for(uint i=indFirst;i<indLast;i++){
        cur= curved.pts[i];
        next= curved.pts[i+1];
        mat2x2 seg(cur,next) ;
        if(intersect(firstPtSeg,seg)){count++;};
    }
    
    return count%2? true :  false;
};


bool[p.numCon] getInsides(uint first,uint last,inout uint indsFirst[p.numCon]){
    uint inds[p.numCon];
    for(uint i=0;i<p.numCon;i++){
        if(isInside(tessCon.pts[indsFirst[i]],first,last )){
        inds[i]=true;
        }
        else {ins[i]=false;}
    };
    return inds;
};


void swap(uint ind,uint s1,uint s2,inout uint inds[p.numCon][p.numCon] ){
    uint temp = inds[ind][s1] ;
    inds[ind][s1] = inds[ind][s2];
    inds[ind][s2] =temp; 
}
void swap(uint s1,uint s2,inout uint inds[p.numCon] ){
    uint temp = inds[s1] ;
    inds[s1] = inds[s2];
    inds[s2] =temp; 
}


bool contains(uint ind,inout uint conts[p.numCon]){
    for(uint i=1;i<conts[0];i++){
        if(ind==conts[i]){return true;}
    }
};

bool[p.numCon] getFill(bool inds[p.numCon][p.numCon]){
    bool fill[p.numCon];for(uint i=0;i<p.numCon;i++){fill[i]=false;}
    bool lpass[p.numCon] = fill;
    uint level[p.numCon];
    uint levMax=0;uint numLevMax;
    uint levs[p.numCon];for(uint i=0;i<p.numCon;i++){levs[i]=0;}
    uint levsPs[p.numCon][p.numCon];
    for(uint i=0;i<p.numCon;i++){
        
        if(lpass[i]){continue;}
        uint numContained=0;
        for(uint j=0;i<p.numCon;j++){
            if(inds[j][i] ){numContained++;}
        }
        if(numContained>levMax){levMax=numContained;}
        lpass[i]=true;
        level[i]=numContained;
        levsPs[level[i]][levs[level[i]]] = i;
        levs[level[i]]++;
    }
    // Triangles
    fillOut = fill;

// 


// TODO mabe for tri strips  

    // uint dirMax=0;
    // uint dirsSize[p.numCon];
    // uint dirs[p.numCon][levs[levMax]] ;
    // for(uint i=0;i<p.numCon;i++){

    // };

   
}  

void getTris(primOut tessc){
    uint curTri ;
    uint indsFirst[p.numCon];
    uint ind = 1;uint curInd = 1;  
    indsFirst[0] = 0;
    for(uint i=0;i<p.numCon;i++){
        while(tessCon.pts[ind]!=endPt){ind++;}
        ind++;
        indsFirst[curInd] = tessCon.pts[ind];
        curInd++;
    }   ;
    bool indsCurInside[p.numCon][p.numCon] ;
    for(uint i=0;i<p.numCon-1;i++){
        indsCurInside[i] = getInsides(indsFirst[i],indsFirst[i+1]-1,indsFirst);
    }
    indsCurInside[p.numCon-1] = getInsides(indsFirst[p.numCon],p.size-1,indsFirst);
    getFill(indsCurInside) ;
}

void tesselate(vec2 ptc,vec2 ptprev,vec2 ptnext, inout vec2 pts[tessNum]){
    vec2 hpt = (ptprev + ptnext)/2;
    vec2 p1 = (ptc - hpt)*2 + hpt ;

    //formula  : B(t) = (1-t)^2 * prevc + 2*(1-t)*t*p1 + t^2 *next

  for(size_t i = 1;i<tessNum+1;i++){float t = i/tessNum ;
     pts[i-1] = pow((1-t),2) * ptprev + 2*(1-t)*t*p1 + pow(t,2) *ptnext;
    };
};

uint binomial(uint n,uint k){
    uint res;
    for(uint i=k+1;i<=n;i++){
        res*=i;
    };
    for(uint i=k+1;i<=n;i++){
        res/=(i-k);
    };
};
void computeTrue(uint s,inout vec2 pts[s]){
        vec2 cur = pts[0];
        vec2 prev = cur;
        for(uint i=1;i<s;i++){
        vec2 mid = (prev + pts[i+1])/2;
            cur = pts[i];
            pts[i] = (cur - mid)*2 + cur;
            prev = cur;
        };
};
// uint stess=  s*tess;
// n = stess
void tesselate(uint s,inout vec2 ptsonc[s],uint stess,inout vec2 pts[stess]){

    computeTrue(s,ptsonc);
    vec2 hpt = (ptprev + ptnext)/2;
    vec2 p1 = (ptc - hpt)*2 + hpt ;

    //formula  : B(t) = sum(i,n){ bin(n,i)* (1-t)^(n-i)t^i*Pi }

  for(size_t i = 0;i<=stess-1;i++){float t = i/stess ;
        vec2 r;
        for(uint j =0;j<s;j++){
            r+=binomial(n,j)* pow((1-t),(n-i))*pow(t,j)*ptsonc[j];
        };
        pts[i] =r;
    };
};

struct Contour {
    vec2 size;
    bool inverted;
    vec2 cont[size] ;
}
layout ( location=0) out Contour c ;

void wrapHandle(uint i,inout uint numOnc ,uint sizeStart,inout uint icon,uint ind) {
    vec2 pts[numOnc+sizeStart+2];
    pts[numOnc+1] = p.pts[i];
    uint offset=0 ; uint indexOff=0;
    pts[numOnc] = p.pts[i-offset];
    for(;offset<numOnc;offset++){
      pts[ numOnc-offset ] = p.pts[i-offset];
    };

    offset = icon+ (numOnc+sizeStart ); 
    for(uint j =0;j<sizeStart,j++){
        pts[numOnc+2+j] = p.pts[i-offset + j  ] ;
    };
    numOnc +=sizeStart;
    uint stess = numOnc*tess;
    vec2 pt[stess];
    tesselate(numOnc,pts,stess,pt);

    for()

}

void numOncHandle(uint i,inout uint numOnc,inout uint icon,uint ind){
  vec2 pts[numOnc+2];

        pts[numOnc+1] = p.pts[i];
  uint offset=0 ; uint indexOff=0;
  pts[numOnc] = p.pts[i-offset];
  for(;offset<numOnc;offset++){
      pts[numOnc-offset ] = p.pts[i-offset];
  };
    putPts(numOnc,icon,ind);
}

void main(){

    // vec2 tessCon.pts[p.numCon][maxSizeCon];
    cp = p ;
    uint icon=0;uint ind=0;uint curCon=0;
    vec2 lastPt;
    uint offs=0;

    vec2 firstPt ; uint numOnc=0;
    uint curCurveCount=0; bool wrap;
    uint curOnCurve;
    for(uint i=0;i<p.size;i++){
        if(i == endPts.p[curCon]){
            if(numOnc!=0){
                if(wrap){wrapHandle(i,numOnc,curCurveCount,icon,ind);};};

            curCurveCount=0;
            curCon++;ind+=icon;icon=0;
        continue; }
        if(i == onCurve.p[curOnCurve]){curOnCurve++;
            if(icon==0){wrap=true;}
            numOnc++;}
        else {
            if(wrap==true && (curCurveCount == 0)){curCurveCount=numOnc;numOnc =0;}
            if(numOnc!=0){
               numOncHandle(i,numOnc,icon,ind);
            };
            else {tessCon.pts[ind+icon] = p.pts[i] ;icon++;}; 
        }
    };

    tessCon.size = p.size + tessNum * p.numOnCurves ;

// TODO make triStrip

} 