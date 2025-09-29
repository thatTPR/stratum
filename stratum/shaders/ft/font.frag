#version 450
#define MAX_SIZE_TS = 100

    #define EXTEND_PAD 0
    #define EXTEND_REPEAT 1
    #define EXTEND_REFL 2
#define LAYER 0

#define GRAD_LINEAR 1;
struct gradientLinear{
        vec2 p0;
        vec2 p1;
        vec2 rotation;
    };
#define GRAD_SWEEP 2;
    struct gradientSweep{
        vec2 center;
        float startAngle;
        float endAngle;
    };
#define GRAD_RADIAL 3;

struct gradientRadial{
    vec2 startCenter;
    float rad1;
    vec2 endCenter;
    float rad2;
};


#define AFFINE 4
    struct Affine{
        mat2 basis;
        vec2 dxdy;
    };
    // Transforms
    
#define SCALE_AROUND_CENTER 5
    struct scaleAroundCenter {
        vec2 d; 
        vec2 center;
    };

#define ROTATE_AROUND_CENTER 
    struct rotateAroundCenter {
        float d;
        vec2 center;
    };
#define SKEW_AROUND_CENTER 7
    struct skewAroundCenter{
        vec2 d;
        vec2 center;
    };

#define TRANSLATE 8
struct translate {
    vec2 d;
};

#define SOLID_FILL 9


#define COMPOSITE 10
struct composite {
    uint mode;
} ;
// #define COMPOSITE



// TODO #define VAR 40



#ifndef MAX_SIZE 
#define MAX_SIZE 10000
#endif

layout(std430,binding=0) buffer paint{
    uint size;
    uint TsNum;
    vec4 fg;vec4 bg;
    uint valueTs[100];
    float values[MAX_SIZE] ;
};



struct glyf {
    ivec2 pos;
    int   xMin;
    int   yMin;
    int   xMax;
    int   yMax;
};

layout(location=0) flat in uint gsFill; 
layout (location=1)flat in glyf glyfInfo; 

layout (location=0)out vec4 outColor; 


float getFlt(inout uint pos){float p=values[pos];pos++;return p;}

vec2 getvec2(inout uint pos){
    vec2 p={values[pos],values[pos+1]};pos+=2;return p;
}

vec4 getvec4(inout uint pos){
    vec4 p={values[pos],values[pos+1],values[pos+2],values[pos+3]};pos+=4;return p;
}
#define MAX_LINE 20
vec4[MAX_LINE] getColorStop(inout uint pos,uint size ){
    vec4 o[MAX_LINE];
    for(uint i=0;i<size;i++){
        o[i]=getvec4(pos);
    };
    return o;
}

struct colorLine {
    uint si;
    vec4 line[MAX_LINE];
    uint extend;
};
translate get_translate(inout uint pos){translate l ;l.d=getvec2(pos);return l;}
colorLine get_colorLine(inout uint pos,inout uint ts){
    colorLine l;
     ts++;l.si=valueTs[ts];l.line=getColorStop(pos,l.si);
    ts++;l.extend= valueTs[ts];return l;ts++;
}
gradientLinear get_gradientLinear(inout uint pos){
gradientLinear l ;l.p0= getvec2(pos);l.p1=getvec2(pos);l.rotation=getvec2(pos);return l;
}
gradientSweep get_gradientSweep(inout uint pos){
gradientSweep l ;l.center= getvec2(pos);l.startAngle=getFlt(pos);l.endAngle=getFlt(pos);return l;
}
gradientRadial get_gradientRadial(inout uint pos){
gradientRadial l ;l.startCenter= getvec2(pos);l.rad1=getFlt(pos);l.endCenter=getvec2(pos);l.rad2=getFlt(pos);return l;
}
Affine get_Affine(inout uint pos){
    Affine l ; 
    l.basis[0]=getvec2(pos);l.basis[1]=getvec2(pos);l.dxdy=getvec2(pos);return l;}

scaleAroundCenter get_scaleAroundCenter(inout uint pos){scaleAroundCenter l ; 
l.d = getvec2(pos);l.center = getvec2(pos);
return l;
}
rotateAroundCenter get_rotateAroundCenter(inout uint pos){
    rotateAroundCenter l ; l.d=getFlt(pos) ; l.center=getvec2(pos);return l;}

skewAroundCenter get_skewAroundCenter(inout uint pos){
    skewAroundCenter l ; l.d=getvec2(pos) ; l.center=getvec2(pos);return l;}


float distancePointLine(vec2 A, vec2 B, vec2 P) {
    vec2 AB = B - A;
    vec2 AP = P - A;
    return abs(AB.x * AP.y - AB.y * AP.x) / length(AB);
}
vec2 perpIntersect(mat2 l,vec2 p){
      vec2 AB = l[1] - l[0];
    float t = dot(p - l[0], AB) / dot(AB, AB);
    return l[0] + t * AB; 
}
float sizegl(gradientLinear gl){
    mat2 l = mat2(gl.p0,gl.rotation);
    vec2 p = gl.p1;
    return distancePointLine(l[0],l[1],p);
}
float dist(gradientLinear gl,vec2 pt){
    return distancePointLine(gl.p0,gl.rotation,pt);
}
bool segInter(vec2 P1,vec2 P2, vec2 Q1,vec2 Q2){
    vec2 r = P2 - P1;
vec2 s = Q2 - Q1;
float denom = r.x * s.y - r.y * s.x;
if (abs(denom) < 1e-6) return false; // parallel

float u = ((Q1.x - P1.x) * r.y - (Q1.y - P1.y) * r.x) / denom;
float t = ((Q1.x - P1.x) * s.y - (Q1.y - P1.y) * s.x) / denom;

return (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0);
}


uint perpToLine_pad(gradientLinear gl, vec2 point,inout float v,colorLine cl){uint si= cl.si;
float s = sizegl(gl);
    float dist = dist(gl,point);
    float c = s/si;
    uint num = uint(dist/c) ;
    int sig = !segInter(point,gl.p1,gl.p0,gl.rotation)?1:-1;
    v = dist-(num*c); 
    if(sig<0){v = 0;num = 0;}
    else {
        if(dist>s){v=1;num=si-1;}
    }
    return num; 
}

uint perpToLine_repeat(gradientLinear gl, vec2 point,inout float v,colorLine cl){uint si= cl.si;
float s = sizegl(gl);
    float dist = dist(gl,point);
    float c = s/si;
    uint num = uint(dist/c) ;
    int sig = !segInter(point,gl.p1,gl.p0,gl.rotation)?1:-1;
    v = dist-(num*c); 
    if(sig<0){v = 1-v;num = si-num-1;}
    return num; 

}
uint perpToLine_refl(gradientLinear gl, vec2 point,inout float v,colorLine cl){uint si= cl.si;
    float s = sizegl(gl);
    float dist = dist(gl,point);
    float c = s/si;
    uint num = uint(dist/c) ;
    v = dist-(num*c); num = num%si;
    return num; 
}
vec4 linearGradient_pad(vec2 p,gradientLinear g,colorLine cl){
    float val;uint pinterval = perpToLine_pad(g,p,val,cl);
    return mix(cl.line[pinterval],cl.line[pinterval+1],val);
}
vec4 linearGradient_repeat(vec2 p,gradientLinear g,colorLine cl){
    float val;uint pinterval = perpToLine_repeat(g,p,val,cl);
    return mix(cl.line[pinterval],cl.line[pinterval+1],val);
}
vec4 linearGradient_refl(vec2 p,gradientLinear g,colorLine cl){
    float val;uint pinterval = perpToLine_refl(g,p,val,cl);
    return mix(cl.line[pinterval],cl.line[pinterval+1],val);
}
vec4 linearGradient(gradientLinear g,colorLine cl){
    switch(cl.extend) {
    case EXTEND_PAD : {return linearGradient_pad(gl_FragCoord.xy,g,cl);} 
    case EXTEND_REPEAT : {return linearGradient_repeat(gl_FragCoord.xy,g,cl);} 
    case EXTEND_REFL : {return linearGradient_refl(gl_FragCoord.xy,g,cl);} 
    }
} 

uint pad(gradientSweep g,vec2 p,colorLine cl,inout float val){uint si= cl.si;
    vec2 v = p-g.center;
    float angle = degrees(atan(v.y,v.x));
    if(angle<g.startAngle){val=0;return 0;}
    if(angle>g.endAngle){val=si-1;return 1;}
   float s = g.endAngle - g.startAngle;
   float ter = s/si;
   float dif = angle- g.startAngle;
   uint num = uint(dif / ter);
   val= (dif-  num* ter )/ter ;
    return num;


}
uint repeat(gradientSweep g,vec2 p,colorLine cl,inout float val){uint si= cl.si;
    vec2 v = p-g.center;
    float angle = degrees(atan(v.y,v.x));
   float s = g.endAngle - g.startAngle;
   float ter = s/si;
   for(;angle<g.startAngle;){angle+=s;}
   for(;angle>g.endAngle;){angle-=s;}

   float dif = angle- g.startAngle;
   uint num =uint(dif / ter);
   val =  (dif-  num* ter )/ter ;
return num;
}
uint refl(gradientSweep g,vec2 p,colorLine cl,inout float val){uint si= cl.si;
    vec2 v = p-g.center;
    float angle = degrees(atan(v.y,v.x));
   float s = g.endAngle - g.startAngle;
   float ter = s/si;

   float dif = angle- g.startAngle;
   float fac = dif / s;
   uint num = uint(dif / ter);
   val =  (dif-  num* ter )/ter ;num=num%si;
return num;
}

vec4 pad_gradientSweep(vec2 p,gradientSweep g,colorLine cl){
    float val;uint pint = pad(g,p,cl,val);
    return mix(cl.line[pint],cl.line[pint+1],val);
}
vec4 repeat_gradientSweep(vec2 p,gradientSweep g,colorLine cl){
        float val;uint pint = repeat(g,p,cl,val);
    return mix(cl.line[pint],cl.line[pint+1],val);

}
vec4 refl_gradientSweep(vec2 p,gradientSweep g,colorLine cl){
    float val;uint pint = refl(g,p,cl,val);
    return mix(cl.line[pint],cl.line[pint+1],val);
}

vec4 gradientSweep_f(gradientSweep g,colorLine cl){
    switch(cl.extend) {
    case EXTEND_PAD : {return pad_gradientSweep(gl_FragCoord.xy,g,cl);} 
    case EXTEND_REPEAT : {return repeat_gradientSweep(gl_FragCoord.xy,g,cl);} 
    case EXTEND_REFL : {return refl_gradientSweep(gl_FragCoord.xy,g,cl);} 
    }
} 
struct Tangents {
    mat2 t1;
    mat2 t2;
};
Tangents getTangent(vec2 c1, float r1, vec2 c2, float r2 ) {
    vec2 d = c2 - c1;
    float dist = length(d);
    vec2 dir = d / dist;

    // float r = external ? (r2 - r1) : -(r2 + r1);
    float r =r2 - r1;
    float ang = acos(r / dist);
    float base = atan(d.y, d.x);

    float theta1 = base + ang;
    float theta2 =  base-ang;
    vec2 v1 = vec2(cos(theta1), sin(theta1));
    vec2 v2 = vec2(cos(theta2), sin(theta2));

    Tangents t;
    t.t1=mat2(vec2(c1 + v1 * r1) , vec2(c2 + v1 * r2));
    t.t2=mat2(vec2(c1 + v2 * r1) ,  vec2(c2 + v2 * r2));
    return t;
}
vec2 intersect(mat2 l1,mat2 l2){
 vec2 r = l1[1] - l1[0];
    vec2 s = l2[1] - l1[0];

    float denom = r.x * s.y - r.y * s.x; // cross(r, s)

    vec2 qp = l1[1] - l2[1];
    float t = (qp.x * s.y - qp.y * s.x) / denom;

    return l2[1] + t * r; // intersection point
}
bool inAngle(Tangents t,vec2 p){
    vec2 o =  intersect(t.t1,t.t2);
  vec2 v = normalize(p - o);

    float c1 = t.t1[0].x * v.y - t.t1[0].y * v.x;  // cross(d1, v)
    float c2 = v.x * t.t2[0].y - v.y * t.t2[0].x;  // cross(v, d2)

    return (c1 >= 0.0 && c2 >= 0.0); // inside sector d1→d2
}
uint pad(gradientRadial g,vec2 p,colorLine cl,inout float val){uint si= cl.si;
    float dis0=distance(p, g.startCenter);
    float dis1=distance(p, g.endCenter);
    bool i0 = dis0 < g.rad1;
    bool i1 = dis1 < g.rad2;
    bool iside0 = distance(g.startCenter,g.endCenter) + g.rad2<g.rad1;       
    bool iside1 = distance(g.endCenter,g.startCenter)+ g.rad1<g.rad2;
float d0;
float d1;
float rat;
    if(iside0){
            if(i0){val=0;return 0;}
    else if(!i1){val=1;return si-1;}

             d0 = dis0 - g.rad1;
             d1 = g.rad2 - dis1;
             rat = d0 / (d0+d1);
    }
    else if(iside1){        
    if(!i0){val=0;return 0;}
    else if(i1){val=1;return si-1;}
             d0 = g.rad1-dis0 ;
             d1 = dis1-g.rad2  ;
             rat = d1 / (d1+d0);
    }
    else { 
        Tangents ts = getTangent(g.startCenter,g.rad1,g.endCenter,g.rad2);
        // if(inAngle(ts,p)){
             d0 = dis0-g.rad1;
             d1 = dis1-g.rad2 ;
             rat = d0 / (d0+d1);
        // }
        
    }                
            uint num = uint(rat*float(si));
            float n0 = float(num)*(1/float(si));
            val = clamp(0,1,rat-n0);return clamp(0,si-1,num);
}
uint repeat(gradientRadial g,vec2 p,colorLine cl,inout float val){uint si= cl.si;
    float dis0=distance(p, g.startCenter);
    float dis1=distance(p, g.endCenter);
    bool i0 = dis0 < g.rad1;
    bool i1 = dis1 < g.rad2;
    bool iside0 = distance(g.startCenter,g.endCenter) + g.rad2<g.rad1;       
    bool iside1 = distance(g.endCenter,g.startCenter)+ g.rad1<g.rad2;
float d0;
float d1;
float rat;
    if(iside0){
             d0 = dis0 - g.rad1;
             d1 = g.rad2 - dis1;
             rat = d0 / (d0+d1);
    }
    else if(iside1){        
             d0 = g.rad1-dis0 ;
             d1 = dis1-g.rad2  ;
             rat = d1 / (d1+d0);
    }
    else { 
        Tangents ts = getTangent(g.startCenter,g.rad1,g.endCenter,g.rad2);
        // if(inAngle(ts,p)){
             d0 = dis0-g.rad1;
             d1 = dis1-g.rad2 ;
             rat = d0 / (d0+d1);
        // }
        
    }                
            int num = int(rat*float(si));uint numn=sign(num)>0?uint(num)%si:(si -uint(-num)%si -1);
            float n0 = float(numn)*(1/float(si));
            val = rat-n0;return numn;
}
uint refl(gradientRadial g,vec2 p,colorLine cl,inout float val){uint si= cl.si;
    float dis0=distance(p, g.startCenter);
    float dis1=distance(p, g.endCenter);
    bool i0 = dis0 < g.rad1;
    bool i1 = dis1 < g.rad2;
    bool iside0 = distance(g.startCenter,g.endCenter) + g.rad2<g.rad1;       
    bool iside1 = distance(g.endCenter,g.startCenter)+ g.rad1<g.rad2;
float d0;
float d1;
float rat;
    if(iside0){
             d0 = float(dis0) - g.rad1;
             d1 = g.rad2 - float(dis1);
             rat = d0 / (d0+d1);
    }
    else if(iside1){        
             d0 = g.rad1-float(dis0) ;
             d1 = float(dis1)-g.rad2  ;
             rat = d1 / (d1+d0);
    }
    else { 
        Tangents ts = getTangent(g.startCenter,g.rad1,g.endCenter,g.rad2);
        // if(inAngle(ts,p)){
             d0 = float(dis0)-g.rad1;
             d1 = float(dis1)-g.rad2 ;
             rat = d0 / (d0+d1);
        // }
        
    }                
            int num = int(rat*float(si));uint numn=sign(num)>0? uint(num)%si : uint(-num)%si;
            float n0 = float(numn)*(1/float(si));
            val = rat-n0;return numn;
}

vec4 pad(vec2 p,gradientRadial g,colorLine cl){
    float val;uint pint = pad(g,p,cl,val);
    return mix(cl.line[pint],cl.line[pint+1],val);
}
vec4 repeat(vec2 p,gradientRadial g,colorLine cl){
    float val;uint pint = repeat(g,p,cl,val);
    return mix(cl.line[pint],cl.line[pint+1],val);
}
vec4 refl(vec2 p,gradientRadial g,colorLine cl){
    float val;uint pint = refl(g,p,cl,val);
    return mix(cl.line[pint],cl.line[pint+1],val);
}
vec4 gradientRadial_f(gradientRadial g,colorLine cl, vec2 fragCoord){
    switch(cl.extend) {
    case EXTEND_PAD : {return pad(fragCoord,g,cl);} 
    case EXTEND_REPEAT : {return repeat(fragCoord,g,cl);} 
    case EXTEND_REFL : {return refl(fragCoord,g,cl);} 
    }
    return pad(fragCoord,g,cl);
} 

vec2 transform(Affine a,vec2 p){
    return a.basis * p + a.dxdy;
}
vec2 transform(scaleAroundCenter a,vec2 p){
    vec2 o=p-a.center;
    return a.d * o + a.center;}

#define M_PI 3.141592653689
vec2 transform(rotateAroundCenter a,vec2 p){
    vec2 v = p-a.center;
    float rad= (a.d)/M_PI;
float c = cos(rad);
    float s = sin(rad);
    return vec2(c * p.x - s * p.y,
                s * p.x + c * p.y);}

vec2 transform(skewAroundCenter a,vec2 p){
    vec2 v = p-a.center;
    mat2 sk = mat2(1.0,a.d.x,
                   a.d.y,1.0);
    return a.center+v*sk;
}
vec2 transform(translate l,vec2 p){return p+l.d;}

vec4 fill(inout uint pos,inout uint ts,inout vec2 fragCoord){
    switch(ts){case SOLID_FILL :  {ts++;return getvec4(pos);}
    case GRAD_LINEAR : {
            gradientLinear l = get_gradientLinear(pos);
            colorLine cl = get_colorLine(pos,ts);
            ts++;return linearGradient(l,cl,fragCoord);}
        case GRAD_SWEEP : {gradientSweep l=get_gradientSweep(pos);
            colorLine cl = get(pos,ts);ts++;return gradientSweep_f(l,cl);}
        case GRAD_RADIAL : {gradientRadial l=get_gradientRadial(pos);colorLine cl = get_colorLine(pos,ts);ts++;return gradientRadial_f(l,cl,fragCoord);}
        case AFFINE : {Affine l=get(pos);ts++;fragCoord = transform(l,fragCoord);return fill(pos,ts,fragCoord);}
        case SCALE_AROUND_CENTER : {scaleAroundCenter l =get_scaleAroundCenter(pos);ts++;fragCood= transform(l,fragCoord);return fill(pos,ts,fragCoord);}
        case ROTATE_AROUND_CENTER : {rotateAroundCenter l = get_rotateAroundCenter(pos);ts++;fragCood= transform(l,fragCoord);return fill(pos,ts,fragCoord);}
        case SKEW_AROUND_CENTER : {skewAroundCenter l = get_skewAroundCenter(pos);ts++;fragCood= transform(l,fragCoord);return fill(pos,ts,fragCoord);}
        case TRANSLATE : {translate l = get_translate(pos);ts++;fragCood= transform(l,fragCoord);return fill(pos,ts,fragCoord);}
        case LAYER : {ts++;uint si=valueTs[ts];ts++;uint mode= valueTs[ts];
            uint tss = ts;
            vec4 s=fill(pos,ts,frag);ts++;
            for(uint i=tss-ts;i<ts;i++){tss=ts;s= (s+fill(pos,ts,frag))/2;ts++;i+=ts-tss;}
            return s;
        }
    }

    if(ts>= COMPOSITE ){
        switch(ts){

        }
    }
}

// #ifdef VERTS_INS
void main(){
    if(gsFill==1){
    uint pos=0;
    for(uint i=0;i<TsNum;i++){
        outColor = fill(pos,valueTs[i],gl_FragCoord.xy);
    }
    }
    else {
        outColor=bg;
    }
}
// #else

// #endif