#ifndef FTCOLR_HPP
#define FTCOLR_HPP
#include "_fontVarCommon.hpp"
#include "cpal.hpp"

float alphaval(F2DOT14 f){
   const float mask = 0b11111111111111;
   float r = f & mask;
   r = r/(1<<14) + (f & (0b11<<14))>>14 ;
   return r;
};



struct ClipBoxFormat1 {
// uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
};

DeltaSetIndexMap* dsim;

struct varIndBase : uint32;

struct varValueBase {
   uint32 mapCount;
   uint8* mapValue;
   varValueBase(varIndBase& r,size_t s){
      mapValue = (*dsim)[r] ;
      mapCount = s;
   };
    varValueBase(varIndBase& r){
      mapValue = (*dsim)[r] ;
      mapCount = dsim->getSize();
   };
};
struct varIndBase : uint32 {
   varValueBase get(){
      return varValueBase(*this);
   }
};

template <template <typename VarIndex> typename T>
T<varIndBase> getVarInd(T<varIndBase>& s,DeltaSetIndexMap& dmap){
   T<varIndBase> res; 
   size_t s = (sizeof(s) - sizeof(varIndBase)) / sizeof(FWORD)   ;
   for(size_t i=0;i<s;i++){
      std::memcpy(&res + sizeof(FWORD)*i,dmap[s.varIndexBase+i],sizeof(FWORD)*i) ;
   };
   return res;
};

 
template <typename VarIndex>
struct ClipBoxFormat2 {
// uint8   format;
FWORD   xMin;
FWORD   yMin;
FWORD   xMax;
FWORD   yMax;
VarIndex   varIndexBase;
};
template <typename VarIndex>
struct ClipBoxFormat {
   uint8 format;
   union {
      ClipBoxFormat1 f1;
      ClipBoxFormat2<varIndBase> f2;
   }f;

};
template <>
ClipBoxFormat<varIndBase> getVarInd<ClipBoxFormat>(ClipBoxFormat<varIndBase>& s,DeltaSetIndexMap& dmap){
   ClipBoxFormat<varIndBase> res; 
   res.f.f2 =  getVarInd<ClipBoxFormat2>(s.f.f2,dmap);
   return res;
};


ACQRES(ClipBoxFormat){
   one(f.format);
   switch(f.format){
      case 1 :{one(f.f1);}
      case 2 :{one(f.f2);}
   }
}
USE_ACQRES(ClipBoxFormat)
template <typename VarIndex>
struct Clip {
uint16   startGlyphID;
uint16   endGlyphID;
Offset24   clipBoxOffset;
//
ClipBoxFormat<VarIndex> clipBox;
};
ACQRES(Clip<varIndBase>){
   one(f.startGlyphID);
   one(f.endGlyphID);
   one(f.clipBoxOffset);
   offone(f.clipBox,f.clipBoxOffset)
}
USE_ACQRES(Clip<varIndBase>)

typedef struct {
uint8   format;
uint32   numClips;
Clip*   clips;//[numClips]
}ClipList;
ACQRES(ClipList){
one(f.format);
one(f.numClips);
arr(f.clips, f.numClips);
 };
USE_ACQRES(ClipList)
#define COND_IS_VARIND(t1,t1) std::conditional<std::is_same<VarIndex,varIndBase>::value,t1,t2>::type

template <typename varIndexBase>
struct ColorStop {
F2DOT14   stopOffset;
COND_IS_VARIND(uint16,glm::uvec4)   paletteIndex;
F2DOT14   alpha;
mod::paint::colorStop getPaint(){
   if constexpr (std::is_same<varIndexBase,varIndBase>::value){
      return mod::paint::colorStop{CPAL().get(paletteIndex),alphaval(alpha);};
   }
   return  mod::paint::colorStop{paletteIndex,alphaval(alpha)};}
};

template <typename VarIndex>
struct VarColorStop {
F2DOT14   stopOffset;
COND_IS_VARIND(uint16,glm::uvec4)   paletteIndex;
COND_IS_VARIND(F2DOT14,float)   alpha;
VarIndex   varIndexBase;
};
mod::paint::var<mod::paint::colorStop> VarColorStop<varValueBase>::getPaint(){
   std::vector<mod::paint::colorStop> r;
   r.data.col=this->paletteIndex;r.data.alpha=alphaval(this->alpha);
   size_t s = this->varIndexBase.mapCount/sizeof(mod::paint::colorStop);
   r.vars.resize(s);
   std::memcpy(r.vars.data(),this->varIndexBase.mapValues,this->varIndexBase.mapCount)
   return r;
}; 

struct ColorLine {
uint8   extend;
uint16   numStops;
ColorStop*   colorStops;//[numStops]
mod::paint::colorLine getPaint(){
   mod::paint::colorLine h(numStops);
   for(size_t s=0;s<numStops;s++){
      h[s] = colorStops[s].getPaint();
   };
   return h;
}
};
ACQRES(ColorLine){
one(f.extend);
one(f.numStops);
if(f.colorStops){for(int i=0;i<numStops;i++){f.colorStops[i].stopOffset=sizeof(ColorStop)*i+3;}}
arr(f.colorStops, f.numStops);
 };
USE_ACQRES(ColorLine)
template <typename VarIndex>
struct VarColorLine {
uint8   extend;
uint16   numStops;
VarColorStop<varIndBase>*   colorStops;//[numStops]
   mod::paint::var<mod::paint::colorLine> getPaint(){
      mod::paint::var<mod::paint::colorLine> r;
      r.data.resize();
      r.vars.resize(numStops);
      for(size_t s=0;s<numStops;s++){
         r.vars[s] = colorStops[s].getPaint();
      };
   };
   return r;
};
ACQRES(VarColorLine<varIndBase>){
one(f.extend);
one(f.numStops);
if(f.colorStops){for(int i=0;i<numStops;i++){f.colorStops[i].stopOffset=sizeof(VarColorStop<varIndBase>)*i+3;}}
arr(f.colorStops, f.numStops);
 };
USE_ACQRES(VarColorLine<varIndBase>)


template <>
VarColorLine<varIndBase> getVarInd<VarColorLine>(VarColorLine<varIndBase>& s,DeltaSetIndexMap& dmap){
   VarColorLine<varIndBase> res;res.numStops=s.numStops;
   res.colorStops= new VarColorStops<varIndBase>[res.numStops];
   for(size_t s=0;s<s.numStops){
      res.colorStops[s] = getVarInd(s.colorStops[s],dmap);
   }
} 

enum Extend {
EXTEND_PAD=0,
EXTEND_REPEAT=1,
EXTEND_REFLECT=2
};
template <typename T>
void getCpal(T* colf, colorFT* cf){
   ColorRecord cr = CPAL().get(colrf->paletteIndex);
   cf->color= glm::uvec4(cr.red,cr.green,cr.blue,cr.alpha);
   cf->alpha=colf->alpha;
};
template <typename VarIndex>
union colrfu;

template <typename VarIndex,size_t s>
struct colrff_base ;
template <size_t s>
struct colrff_base<varValueBase,s> {

   // colrff<varIndBase ,s> getVar(varValueBase colrff<varValueBase,s>::* ptr ){
   //    colrff<varIndBase,s> res; 
   //    size_t s = (sizeof(s) - sizeof(varIndBase)) / sizeof(FWORD)   ;
   //    for(size_t i=0;i<s;i++){
   //       std::memcpy(&res + sizeof(FWORD)*i,this->*ptr.mapValue + sizeof(FWORD)*i,sizeof(FWORD)) ;
   //    };
   //    return res;
   // };
};



template <size_t s>
struct ptype {
   using ty ;
};
template <> struct ptype<1>{using ty = mod::fontColor::layerty; }
template <> struct ptype<2>{using ty = mod::paint::solid; }
template <> struct ptype<3>{using ty = mod::paint::var<mod::paint::solid>; }
template <> struct ptype<4>{using ty = mod::paint::gradientLinear; }
template <> struct ptype<5>{using ty = mod::paint::ColorLine<mod::paint::var<mod::paint::gradientLinear>>; }
template <> struct ptype<6>{using ty = mod::paint::gradientRadial; }
template <> struct ptype<7>{using ty = mod::paint::var<mod::paint::gradientRadial>; }
template <> struct ptype<8>{using ty = mod::paint::ColorLine<mod::paint::gradientSweep>; }
template <> struct ptype<9>{using ty = mod::paint::VarColorLine<mod::paint::var<mod::paint::gradientSweep>>; }

// template <>struct ptype<10>{using ty=  mod::font::fontColSubGlyph<char> ;}
// template <>struct ptype<11>{using ty = mod::font::fontColSubGlyph<char> ;}

template <> struct ptype<12>{using ty = mod::paint::Affine; }
template <> struct ptype<13>{using ty = mod::paint::var<mod::paint::Affine>; }
template <> struct ptype<14>{using ty = mod::paint::translate; }
template <> struct ptype<15>{using ty = mod::paint::var<mod::paint::translate>; }
template <> struct ptype<16>{using ty = mod::paint::scale; }
template <> struct ptype<17>{using ty = mod::paint::var<mod::paint::scale>; }
template <> struct ptype<18>{using ty = mod::paint::scaleAroundCenter; }
template <> struct ptype<19>{using ty = mod::paint::var<mod::paint::scaleAroundCenter>; }
template <> struct ptype<20>{using ty = mod::paint::scale; }
template <> struct ptype<21>{using ty = mod::paint::var<mod::paint::scale>; }
template <> struct ptype<22>{using ty = mod::paint::scaleAroundCenter; }
template <> struct ptype<23>{using ty = mod::paint::var<mod::paint::scaleAroundCenter>; }
template <> struct ptype<24>{using ty = mod::paint::rotate; }
template <> struct ptype<25>{using ty = mod::paint::var<mod::paint::rotate>; }
template <> struct ptype<26>{using ty = mod::paint::rotateAroundCenter; }
template <> struct ptype<27>{using ty = mod::paint::var<mod::paint::rotateAroundCenter>; }
template <> struct ptype<28>{using ty = mod::paint::rotateAroundCenter; }
template <> struct ptype<29>{using ty = mod::paint::var<mod::paint::rotateAroundCenter>; }
template <> struct ptype<30>{using ty = mod::paint::skewAroundCenter; }
template <> struct ptype<31>{using ty = mod::paint::var<mod::paint::skewAroundCenter>; }
template <> struct ptype<32>{using ty = mod::fontColor::compose;}

template <typename VarIndex,size_t s>
struct colrff : colrff_base<VarIndex,s>{
   static constexpr bool bValue = std::is_same<VarIndex,varValueBase>::value; 
};
template <size_t s>
struct colrff<varIndexBase,s> {
   colrff<varValueBase,s> get();
};
template <size_t s>
struct colrff<varValueBase,s> {
   ptype<s>::ty getPaint();
};



template <typename VarIndex>
 struct colrff<VarIndex,1>{///PaintColrLayers
// uint8   format;   
uint8   numLayers;
uint32   firstLayerIndex;

};template<typename VarIndex> using colrff1=colrff<VarIndex,1> ; //PaintColrLayers

colrff<varValueBase,1> colrff<varIndexBase,1>::get(){
   colrff<varValueBase,1> g{this->numLayers,this->firstLayerIndex} ;return g;
};



template <typename VarIndex>
 struct colrff<VarIndex,2>{//PaintSolid
// uint8   format;
COND_IS_VARIND(uint16,glm::uvec4)   paletteIndex;
COND_IS_VARIND(F2DOT14,float)   alpha;
  
};template<typename VarIndex> using colrff2=colrff<VarIndex,2> ; //PaintSolid table ;

 colrff<varValueBase,2> colrff<varIndexBase,2>::get(){
   corlff<varValueBase,2> r;r.paletteIndex=CPAL().get(this->paletteIndex).get();r.alpha=alphaval(this->alpha);      
   return r;
};
 ptype<2>::ty colrff<varValueBase,2>::getPaint(){
      ptype<2>::ty r;
         r.col = paletteIndex;
         r.alpha = alpha;
      return r;
   }; 

template <typename VarIndex> // Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,3>{//, PaintVarSolid
// uint8   format;
COND_IS_VARIND(uint16,glm::uvec4)  paletteIndex;
F2DOT14   alpha;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff3=colrff<VarIndex,3> ; //PaintVarSolid;
   colrff<varValueBase,3> colrff<varIndexBase,3>::get(){
colrff<varValueBase,3>  r;r.paletteIndex=CPAL().get(paletteIndex).get();r.alpha=alphaval(alpha);return r;}
   ptype<3>::ty colrff<varValueBase,3>::getPaint(){
      ptype<3>::ty r;
         r.data.col = paletteIndex;
         r.data.alpha = alpha;
         r.vars.resize(varIndexBase.mapCount/sizeof(ptype<3>::ty::ty))
         std::memcpy(r.vars.data(),varIndexBase.mapValue,varIndexBase.mapCount);
      
      return r;
   }; 



template <typename VarIndex>
using colrLineOffTy  = std::conditional<std::is_same<VarIndex,varIndBase>::value,Offset24,size_t>::type;

template <typename VarIndex>
using varcolrLineOffTy  = std::conditional<std::is_same<VarIndex,varIndBase>::value,Offset24,VarColorLine<varIndValueBase>>::type;



template <typename VarIndex>
 struct colrff<VarIndex,4>{//PaintLinearGradient
// uint8   format;
colrLineOffTy <VarIndex> colorLineOffset;
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
ColorLine colorLine;
 
// 
};template<typename VarIndex> using colrff4=colrff<VarIndex,4> ; //PaintLinearGradient;

colrff<varValueBase,4> colrff<varIndexBase,4>::get(){
      colrff<varValueBase,4> g;
      g.x0 = this->x0;g.y0 = this->y0;g.x1 = this->x1;g.y1 = this->y1;g.x2 = this->x2;g.y2 = this->y2;g.colorLine = this->colorLine;
      return g;
   }
 ptype<4>::ty colrff<varValueBase,4>::getPaint(){
      ptype<4>::ty r;
         r.p1.x = x0;
         r.p1.y = y0;
         r.p1.x = x1;
         r.p1.y = y1;
         r.rotation = glm::vec2(x2,y2);
      return r;
   };

ACQRES(colrff<varIndBase,4>){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.x1);
   one(f.y1);
   one(f.x2);
   one(f.y2);
   offone(f.colorLine,f.colorLineOffset);
};
USE_ACQRES(colrff<varValueBase,4>)
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,5>{//PaintVarLinearGradient
// uint8   format;
colrLineOffTy <VarIndex> colorLineOffset; 
FWORD   x0;
FWORD   y0;
FWORD   x1;
FWORD   y1;
FWORD   x2;
FWORD   y2;
VarIndex   varIndexBase;
VarColorLine<VarIndex> colorLine;


CORLF_GET(5,x0,y0,x1,y1,x2,y2)
};template<typename VarIndex> using colrff5=colrff<VarIndex,5> ; //PaintVarLinearGradient;

colrff<varValueBase,5> colrff<varIndexBase,5>::get(){
   colrff<varValueBase,5> g;
   g.colorLineOffset = this->colorLineOffset.get();
   g.x0 = this->x0;
   g.y0 = this->y0;
   g.x1 = this->x1;
   g.y1 = this->y1;
   g.x2 = this->x2;
   g.y2 = this->y2;
   g.varIndexBase = this->varIndexBase.get();
   g.colorLine = this->colorLine.get();return g;
};
 ptype<5>::ty colrff<varValueBase,5>::getPaint(){
      ptype<5>::ty r;
         r..data.data.p1.x = x0;
         r..data.data.p1.y = y0;
         r..data.data.p1.x = x1;
         r..data.data.p1.y = y1;
         r..data.data.rotation = glm::vec2(x2,y2);
         r..data.vars.resize(varIndexBase.mapCount/sizeof(ptype<5>::ty::ty))
         std::memcpy(r.vars.data(),varIndexBase.mapValue,varIndexBase.mapCount);
         r.cl = this->colorLine.getPaint() ;
      return r;
   };

ACQRES(colrff<varIndBase,5>){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.x1);
   one(f.y1);
   one(f.x2);
   one(f.y2);
   one(f.varIndexBase);
   offone(f.colorLine,f.colorLineOffset);
};
USE_ACQRES(colrff<varIndBase,5>)




template <typename VarIndex>
struct colrff<VarIndex,6>{//PaintRadialGradient
\\uint8   format;
colrLineOffTy <VarIndex> colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
ColorLine colorLine;
};template<typename VarIndex> using colrff6=colrff<VarIndex,6> ; //PaintRadialGradient:*/;
colrff<varValueBase,6> colrff<varIndexBase,6>::get(){
   colrff<varValueBase,5> g;
   g.colorLineOffset = this->colorLineOffset.get();
   g.x0 = this->x0;
   g.y0 = this->y0;
   g.radius0 = this->radius0;
   g.x1 = this->x1;
   g.y1 = this->y1;
   g.radius1 = this->radius1;
   g.colorLine = this->colorLine;
};
 ptype<6>::ty colrff<varValueBase,6>::getPaint(){
   ptype<6>::ty r;r.startCenter=glm::vec2(this->x0,this->y0);
   ptype<6>::ty r;r.endCenter=glm::vec2(this->x1,this->y1);
   r.rad1 = this->radius0; r.rad2=this->radius1;
   r.cs = this->colorLine.getPaint();
   return r;
}
ACQRES(colrff<varIndBase,6>){
   one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.radius0);
   one(f.x1);
   one(f.y1);
   one(f.radius1);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrff<varIndBase,6>)
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,7>{//, PaintVarRadialGradient
\\uint8   format;
colrLineOffTy <VarIndex>   colorLineOffset;
FWORD   x0;
FWORD   y0;
UFWORD   radius0;
FWORD   x1;
FWORD   y1;
UFWORD   radius1;
VarIndex   varIndexBase;
VarColorLine<VarIndex> colorLine;

};template<typename VarIndex> using colrff7=colrff<VarIndex,7> ; //PaintVarRadialGradient:*/;
colrff<varValueBase,7> colrff<varIndexBase,7>::get(){
   colrff<varValueBase,7> g;
   g.colorLineOffset = this->colorLineOffset.get();
   g.x0 = this->x0;
   g.y0 = this->y0;
   g.radius0 = this->radius0;
   g.x1 = this->x1;
   g.y1 = this->y1;
   g.radius1 = this->radius1;
   g.varIndexBase = this->varIndexBase;
   g.colorLine = this->colorLine.get();return g;
}
 ptype<7>::ty colrff<varValueBase,7>::getPaint(){
   ptype<7>::ty r ; r.data.startCenter=glm::vec2(this->x0,this->y0);
   ptype<7>::ty r ; r.data.endCenter=glm::vec2(this->x1,this->y1);
   r.data.vars.resize(varIndexBase.mapCount/sizeof(ptype<7>::ty))
   std::memcpy(r.vars.data(),varIndexBase.mapValue,varIndexBase.mapCount);
   r.cs = colorLine.getPaint();
   return r;
}

ACQRES(colrff<varIndBase,7>){
      one(f.colorLineOffset);
   one(f.x0);
   one(f.y0);
   one(f.radius0);
   one(f.x1);
   one(f.y1);
   one(f.radius1);
   one(f.varIndexBase);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrff<varIndBase,7>)
template <typename VarIndex>
struct colrff<VarIndex,8>{//PaintSweepGradient, 
\\uint8   format;
colrLineOffTy <VarIndex> colorLineOffset;
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
ColorLine colorLine;

};template<typename VarIndex> using colrff8=colrff<VarIndex,8> ; //PaintSweepGradient:*/;
colrff<varValueBase,8> colrff<varIndexBase,8>::get(){
   colrff<varValueBase,8> g;
   g.colorLineOffset=this->colorLineOffset;
   g.centerX=this->centerX;
   g.centerY=this->centerY;
   g.startAngle=this->startAngle;
   g.endAngle=this->endAngle;
   g.colorLine=this->colorLine;return g;
};
 ptype<8>::ty colrff<varValueBase,8>::getPaint(){
   ptype<8>::ty r;
   r.data.center = glm::vec2(this->centerX,this->centerY);
   r.data.startAngle = this->startAngle;
   r.data.endAngle =this->endAngle;
   r.cl = this->colorLine.getPaint();
}
ACQRES(colrff<varIndBase,8>){
   one(f.colorLineOffset);
   one(f.centerX);
   one(f.centerY);
   one(f.startAngle);
   one(f.endAngle);
   offone(f.colorLine,f.colorLineOffset);
}
USE_ACQRES(colrff<varIndBase,8>)
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,9>{//PaintVarSweepGradient
\\uint8   format;
colrLineOffTy <VarIndex> colorLineOffset;

FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
VarIndex   varIndexBase;
VarColorLine<VarIndex> colorLine;

};template<typename VarIndex> using colrff9=colrff<VarIndex,9> ; //PaintVarSweepGradient:*/;
colrff<varValueBase,9> colrff<varIndexBase,9>::get(){
   colrff<varValueBase,9> g;g.centerX=this->centerX;
   g.centerY=this->centerY;
   g.startAngle=this->startAngle;
   g.endAngle=this->endAngle;
   g.varIndexBase=this->varIndexBase;
   g.colorLine=this->colorLine.get();return g;
};
 ptype<9>::ty colrff<varValueBase,9>::getPaint(){
      ptype<8>::ty r;
   r.data.data.center = glm::vec2(this->centerX,this->centerY);
   r.data.data.startAngle = alphaval(this->startAngle);
   r.data.data.endAngle =alphaval(this->endAngle);
   size_t s = this->varIndexBase.mapCount /sizeOf<FWORD,FWORD,F2DOT14,F2DOT14>();
   struct {
FWORD   centerX;
FWORD   centerY;
F2DOT14   startAngle;
F2DOT14   endAngle;
   } *arr;
   arr = new decltype(*arr)[s]; 
   std::memcpy(arr,this->varIndexBase.mapValues,this->varIndexBase.mapCount )
   for(size_t i =0;i<s;i++){
r.data.vars[i].center=glm::vec2(arr[i].centerX,arr[i].centerY);
r.data.vars[i].startAngle=alphaval(arr[i].startAngle);
r.data.vars[i].endAngle=alphaval(arr[i].endAngle);
   }
   r.cl = this->colorLine.getPaint();
}
ACQRES(colrff<varIndBase,9>){
one(f.colorLineOffset);
one(f.centerX);
one(f.centerY);
one(f.startAngle);
one(f.endAngle);
one(f.varIndexBase);
offone(f.colorLine,colorLineOffset);
}
USE_ACQRES(colrff<varIndBase,9>)

template <typename VarIndex>
using PAINT_OFFSET = typename std::conditional<std::is_same<VarIndex,varIndBase>::value ,  Offset24 , size_t>::type;


template <typename VarIndex>
 struct colrff<VarIndex,10>{//PaintGlyph
\\uint8   format;
PAINT_OFFSET<VarIndex> paintOffset;
uint16   glyphID;
// SpecialHandle
template <typename charT>
mod::fontColor<charT>::SubGlyph getPaint(){return mod::fontColor<charT>::SubGlyph(glyhID);};
colrfu* get(colrf<varIndBase>* start,uint16 index){return (&start[index]+paintOffset);};
};template<typename VarIndex> using colrff10=colrff<VarIndex,10> ; //PaintGlyph:*/;
colrff<varValueBase,10> colrff<varIndexBase,10>::get(){colrff<varValueBase,10> g;
g.glyphID=this->glyphID;
   return g ;}
//  ptype<10>::ty colrff<varValueBase,10>::getPaint(){}
template <typename VarIndex>
struct colrff<VarIndex,11>{//PainColorGlyph
\\uint8   format;
uint16   glyphID; // BaseGlyphList Glyph ID
};template<typename VarIndex> using colrff11=colrff<VarIndex,11> ; //PaintColrGlyph:*/;
colrff<varValueBase,11> colrff<varIndexBase,11>::get(){colrff<varValueBase,11> g;return g ;}
//  ptype<11>::ty colrff<varValueBase,11>::getPaint(){}
 struct Affine2x3  {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
   mod::paint::Affine getPaint(){mod::paint::Affine s{glm::vec2(xx,yx),glm::vec2(xy,yy),glm::vec2(dx,dy)};return s;};
};

template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct VarAffine2x3 {
Fixed   xx;
Fixed   yx;
Fixed   xy;
Fixed   yy;
Fixed   dx;
Fixed   dy;
VarIndex   varIndexBase;
   ptype<13>::ty getPaint(){mod::paint::Affine s{glm::vec2(xx,yx),glm::vec2(xy,yy),glm::vec2(dx,dy)};
         ptype<13>::ty t;t.data=s;
         struct  {
            Fixed   xx;
            Fixed   yx;
            Fixed   xy;
            Fixed   yy;
            Fixed   dx;
            Fixed   dy;
         }*x;
         size_t i = varIndexBase.mapCount/(sizeof(Fixed)*6());
         x = new decltype(*x)[i];std::memcpy(x,varIndexBase.mapValues,varIndexBase.mapCount);
         t.vars.resize(i);
         for(size_t j=0;j<i;j++){
            t.vars[j]=x[i];
         };return t;};

VarAffine2x3<varValueBase> operator=(decltype(*this)& l){
   VarAffine2x3<varValueBase> r;
   r.xx=xx;   r.yx=yx;   r.xy=xy;   r.yy=yy;   r.dx=dx;   r.dy=dy;}
};


template < typename SCOLR>
colrf<varIndBase>* getPaintOffset(SCOLR& start){
   return (&start-sizeof(uint8)+start.paintOffset);
};
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,12>{//PaintTransform, 
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
colrLineOffTy<VarIndex> transformOffset; // Stores Index to value in VarValueBase
Affine2x3               transform;

};template<typename VarIndex> using colrff12=colrff<VarIndex,12> ; //PaintTransform:*/;
colrff<varValueBase,12> colrff<varIndexBase,12>::get(){colrff<varValueBase,12> g;
   g.transformOffset=this->transformOffset;
   g.transform=this->transform;
   return g ;}
 ptype<12>::ty colrff<varValueBase,12>::getPaint(){return this->transform.getPaint();}
ACQRES(colrff<varIndBase,12>){
   one(f.paintOffset);
   one(f.transformOffset);
   offone(f.transform,f.transformOffset);
}
USE_ACQRES(colrff<varIndBase,12>)
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,13>{//PaintVarTransform
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
Offset24 transformOffset; // Stores Index to value in VarValueBase
VarAffine2x3<VarIndex> transform;

};template<typename VarIndex> using colrff13=colrff<VarIndex,13> ; //PaintVarTransform:*/;
colrff<varValueBase,13> colrff<varIndexBase,13>::get(){colrff<varValueBase,13> g;
   g.transformOffset = this->transformOffset;
   g.transform = this->transform.get();
   return g ;}
 ptype<13>::ty colrff<varValueBase,13>::getPaint(){return this->transform.getPaint();}
ACQRES(colrff<varIndBase,13>){
   one(f.paintOffset);
   one(f.transformOffset);
   offone(f.transform,f.transformOffset);
};
USE_ACQRES(colrff<varIndBase,13>)


struct colrff<VarIndex,14>{//PaintTranslate, 
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
FWORD   dx;
FWORD   dy;

};template<typename VarIndex> using colrff14=colrff<VarIndex,14> ; //PaintTranslate:*/;
colrff<varValueBase,14> colrff<varIndexBase,14>::get(){colrff<varValueBase,14> g;
   g.dx=this->dx;g.dy=this->dy;
   return g ;}
 ptype<14>::ty colrff<varValueBase,14>::getPaint(){
   return glm::vec(this->dx,this->dy);  
}


template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
 struct colrff<VarIndex,15>{//PaintVarTranslate
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
FWORD   dx;
FWORD   dy;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff15=colrff<VarIndex,15> ; //PaintVarTranslate:*/;
colrff<varValueBase,15> colrff<varIndexBase,15>::get(){colrff<varValueBase,15> g;
   g.dx=this->dx;
   g.dy=this->dy;
   g.varIndexBase=this->varIndexBase.get();
   return g ;}
 ptype<15>::ty colrff<varValueBase,15>::getPaint(){
   ptype<15>::ty g;g.data = glm::vec(this->dx,this->dy);
   struct {
      FWORD   dx;
FWORD   dy;} *x;
   size_t s = this->varIndexBase.mapCount/(sizeof(FWORD)*2);
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s)
   for(size_t i=0;i<s;i++){g.vars[i]=glm::vec2(x[i].dx,x[i].dy)}
   return g; 
}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,16>{//PaintScale 
\\uint8   format;
PAINT_OFFSET <VarIndex>   paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;

};template<typename VarIndex> using colrff16=colrff<VarIndex,16> ; //PaintScale:*/;
colrff<varValueBase,16> colrff<varIndexBase,16>::get(){colrff<varValueBase,16> g{ this->scaleX, this->scaleY};return g ;}
 ptype<16>::ty colrff<varValueBase,16>::getPaint(){return glm::vec2(alphaval(this->scaleX),alphaval(this->scaleY));}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,17>{//PaintVarScale
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff17=colrff<VarIndex,17> ; //PaintVarScale:*/;

colrff<varValueBase,17> colrff<varIndexBase,17>::get(){colrff<varValueBase,17> 
   g{this->scaleX,this->scaleY,this->varIndexBase.get()};return g ;}
 ptype<17>::ty colrff<varValueBase,17>::getPaint(){
      ptype<17>::ty g;g.data =  glm::vec2(alphaval(this->scaleX),alphaval(this->scaleY));
      struct {
F2DOT14   scaleX;
F2DOT14   scaleY;
      }*x;
      size_t s = this->varIndexBase.mapCount/(sizeof(F2DOT14)*2);
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s)
   for(size_t i=0;i<s;i++){g.vars[i]=glm::vec2(x[i].dx,x[i].dy)}
   return g; 
}



template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrf18{//PaintScaleAroundCenter
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;

};//PaintScaleAroundCenter:*/;
colrff<varValueBase,18> colrff<varIndexBase,18>::get(){return colrff<varValueBase,17>{
   this->scaleX,this->scaleY,this->centerX,this->centerY};}
ptype<18>::ty colrff<varValueBase,18>::getPaint(){
   ptype<18>::ty g;g.d =  glm::vec2(alphaval(this->scaleX),alphaval(this->scaleY));g.center = glm::vec2(this->centerX,this->centerY);
   return g; 

 }
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
 struct colrff<VarIndex,19>{//PaintVarScaleAroundCente
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff19=colrff<VarIndex,19> ; //PaintVarScaleAroundCenter:*/;
colrff<varValueBase,19> colrff<varIndexBase,19>::get(){colrff<varValueBase,19> g{
         this->scaleX,   this->scaleY,   this->centerX,   this->centerY,   this->varIndexBase.get()};return g ;}
 ptype<19>::ty colrff<varValueBase,19>::getPaint(){
   ptype<19>::ty g;g.data.d =  glm::vec2(alphaval(this->scaleX),alphaval(this->scaleY));g.data.center = glm::vec2(this->centerX,this->centerY);
      struct {
F2DOT14   scaleX;
F2DOT14   scaleY;
FWORD   centerX;
FWORD   centerY;
      }*x;
      size_t s = this->varIndexBase.mapCount/((sizeof(F2DOT14)+sizeof(FWORD))*2);
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s)
   for(size_t i=0;i<s;i++){g.vars[i]={glm::vec2(x[i].dx,x[i].dy),glm::vec2(x[i].centerX,x[i].centerY)}}
   return g; 

 }


template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,20>{//PaintScaleUniform
\\uint8   format;
PAINT_OFFSET <VarIndex>   paintOffset;
F2DOT14   scale;

};template<typename VarIndex> using colrff20=colrff<VarIndex,20> ; //PaintScaleUniform:*/;
colrff<varValueBase,20> colrff<varIndexBase,20>::get(){colrff<varValueBase,20> g{this->scale};return g ;}
 ptype<20>::ty colrff<varValueBase,20>::getPaint(){float r=alphaval(this->scale);
   return glm::vec2(r,r);
}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,21>{//PaintVarScaleUniform
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   scale;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff21=colrff<VarIndex,21> ; //PaintVarScaleUniform:*/;
colrff<varValueBase,21> colrff<varIndexBase,21>::get(){colrff<varValueBase,21> g{this->scale,this->varIndexBase.get()};return g ;}
 ptype<21>::ty colrff<varValueBase,21>::getPaint(){
   ptype<21>::ty g;float r = alphaval(this->scale);g.d = glm::vec2(r,r);
    F2DOT14 *x;
      size_t s = this->varIndexBase.mapCount/(sizeof(F2DOT14));
   x=new F2DOT14[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s);
   for(size_t i=0;i<s;i++){g.vars[i]=glm::vec2(alphaval(x[i]),alphaval(x[i])) ;}
   return g; 
}


template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,22>{//PaintScaleUniformAroundCenter
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;


};template<typename VarIndex> using colrff22=colrff<VarIndex,22> ; //PaintScaleUniformAroundCenter:*/;
colrff<varValueBase,22> colrff<varIndexBase,22>::get(){colrff<varValueBase,22> g{this->scale,this->centerX,this->centerY};return g ;}
 ptype<22>::ty colrff<varValueBase,22>::getPaint(){
       ptype<22>::ty g; float r =alphaval(this->scale);g.d = glm::vec2(r,r);g.center=glm::vec2(this->centerX,this->centerY);return g;
  
}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,23>{//PaintVarScaleUniformAroundCenter
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
VarIndex varIndexBase;

} ;//PaintVarScaleUniformAroundCenter:*/;
template<typename VarIndex> using colrff23=colrff<VarIndex,23> ; //PaintRotate:*/;
colrff<varValueBase,23> colrff<varIndexBase,23>::get(){colrff<varValueBase,23> g{
   this->scale,this->centerX,this->centerY,this->varIndexBase.get()};return g ;}
 ptype<23>::ty colrff<varValueBase,23>::getPaint(){   
   ptype<23>::ty g;g.data.d = alphaval(this->scale);
   g.data.center=glm::vec2(this->centerX,this->centerY);
  struct{F2DOT14   scale;
FWORD   centerX;
FWORD   centerY;
} *x;
      size_t s = this->varIndexBase.mapCount/(sizeof(F2DOT14) + sizeof(FWORD)*2);
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s);
   for(size_t i=0;i<s;i++){g.vars[i].d=glm::vec2(alphaval(x[i].scale),alphaval(x[i].scale)) ;g.vars[i].center=glm::vec2(x[i].centerX,x[i].centerY) ;}
   return g; }





template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,24>{//PaintRotate
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   angle;


};template<typename VarIndex> using colrff24=colrff<VarIndex,24> ; //PaintRotate:*/;
colrff<varValueBase,24> colrff<varIndexBase,24>::get(){colrff<varValueBase,24> g{this->angle};return g ;}
 ptype<23>::ty colrff<varValueBase,24>::getPaint(){   return alphaval(this->angle);}


template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,25>{//PaintVarRotate
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   angle;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff25=colrff<VarIndex,25> ; //PaintVarRotate:*/;
colrff<varValueBase,25> colrff<varIndexBase,25>::get(){colrff<varValueBase,25> g{this->angle,this->varIndexBase.get()};return g ;}
 ptype<25>::ty colrff<varValueBase,25>::getPaint(){
   ptype<25>::ty g;g.data = alphaval(this->angle);
   F2DOT14 *x;
      size_t s = this->varIndexBase.mapCount/(sizeof(F2DOT14));
   x=new F2DOT14[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s);
   for(size_t i=0;i<s;i++){g.vars[i]=alphaval(x[i]);}
   return g; 
}




template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,26>{//PaintRotateAroundCenter
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;

};template<typename VarIndex> using colrff26=colrff<VarIndex,26> ; //PaintRotateAroundCenter:*/;
colrff<varValueBase,26> colrff<varIndexBase,26>::get(){colrff<varValueBase,26> g{
   this->angle,this->centerX,this->centerY,};return g ;}
 ptype<26>::ty colrff<varValueBase,26>::getPaint(){
   ptype<26>::ty g;g.d=alphaval(this->angle);g.center=glm::vec2(this->centerX,this->centerY);
   return g;
}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,27>{//PaintVarRotateAroundCenter
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff27=colrff<VarIndex,27> ; //PaintVarRotateAroundCenter:*/;
colrff<varValueBase,27> colrff<varIndexBase,27>::get(){colrff<varValueBase,27> g{
   this->angle,this->centerX,this->centerY,this->varIndexBase.get()};return g ;}
 ptype<27>::ty colrff<varValueBase,27>::getPaint(){
    ptype<27>::ty g;g.data.d=alphaval(this->angle);g.data.center=glm::vec2(this->centerX,this->centerY);
   
   struct{F2DOT14   angle;
FWORD   centerX;
FWORD   centerY;
} *x;
      size_t s = this->varIndexBase.mapCount/(sizeof(*x));
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s);
   for(size_t i=0;i<s;i++){g.vars[i].d=alphaval(x[i].angle);g.vars[i].center=glm::vec2(x[i].centerX,x[i].centerY);}
   return g;
}


struct colrff<VarIndex,28>{//PaintSkew
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;

};template<typename VarIndex> using colrff28=colrff<VarIndex,28> ; //PaintSkew:*/;
colrff<varValueBase,28> colrff<varIndexBase,28>::get(){colrff<varValueBase,28> g{
   this->xSkewAngle,this->ySkewAngle};return g ;}
 ptype<28>::ty colrff<varValueBase,28>::getPaint(){
   return glm::vec2(alphaval(this->xSkewAngle),alphaval(this->ySkewAngle));}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,29>{//PaintVarSkew
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff29=colrff<VarIndex,29> ; //PaintVarSkew:*/;
colrff<varValueBase,29> colrff<varIndexBase,29>::get(){colrff<varValueBase,29> g{
   this->xSkewAngle,this->ySkewAngle,this->varIndexBase.get()};return g ;}
 ptype<29>::ty colrff<varValueBase,29>::getPaint(){
   ptype<29>::ty g;g.data=glm::vec2(alphaval(this->xSkewAngle),alphaval(this->ySkewAngle));
   struct {
      F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
   }
size_t s = this->varIndexBase.mapCount/(sizeof(*x));
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s);
   for(size_t i=0;i<s;i++){g.vars[i]=glm::vec2(alphaval(x[i].xSkewAngle),alphaval(x[i].ySkewAngle)));}
   return g;
}


struct colrff<VarIndex,30>{//PaintSkewAroundCenter 
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;

};template<typename VarIndex> using colrff30=colrff<VarIndex,30> ; //PaintSkewAroundCenter:*/;
colrff<varValueBase,30> colrff<varIndexBase,30>::get(){colrff<varValueBase,30> g{
   this->xSkewAngle,this->ySkewAngle,this->centerX,this->centerY};return g ;}
 ptype<30>::ty colrff<varValueBase,30>::getPaint(){
   return {glm::vec2(alphaval(this->xSkewAngle),alphaval(this->ySkewAngle)),glm::vec2(this->centerX,this->centerY)};
}
template <typename VarIndex>// Uint32 or struct{uint16,uint8*}
struct colrff<VarIndex,31>{//PaintVarSkewAroundCenter 
\\uint8   format;
PAINT_OFFSET<VarIndex>  paintOffset;
F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
VarIndex   varIndexBase;

};template<typename VarIndex> using colrff31=colrff<VarIndex,31> ; //PaintVarSkewAroundCenter:*/;
colrff<varValueBase,31> colrff<varIndexBase,31>::get(){colrff<varValueBase,31> g{
   this->xSkewAngle,this->ySkewAngle,this->centerX,this->centerY,this->varIndexBase.get()};return g ;}
 ptype<31>::ty colrff<varValueBase,31>::getPaint(){
      ptype<31>::ty g;g.data={glm::vec2(alphaval(this->xSkewAngle),alphaval(this->ySkewAngle)),glm::vec2(this->centerX,this->centerY)};

struct {F2DOT14   xSkewAngle;
F2DOT14   ySkewAngle;
FWORD   centerX;
FWORD   centerY;
}*x;

size_t s = this->varIndexBase.mapCount/(sizeof(*x));
   x=new decltype(*x)[s];std::memcpy(x,this->varIndexBase.mapValues,this->varIndexBase.mapCount);g.vars.resize(s);
   for(size_t i=0;i<s;i++){g.vars[i]={glm::vec2(alphaval(x[i].xSkewAngle),alphaval(x[i].ySkewAngle)),glm::vec2(x[i].centerX,x[i].centerY)};}
   return g;
}


enum CompositeMode {
   COMPOSITE_CLEAR=0,
   COMPOSITE_SRC=1,
   COMPOSITE_DEST=2,
   COMPOSITE_SRC_OVER=3,
   COMPOSITE_DEST_OVER=4,
   COMPOSITE_SRC_IN=5,
   COMPOSITE_DEST_IN=6,
   COMPOSITE_SRC_OUT=7,
   COMPOSITE_DEST_OUT=8,
   COMPOSITE_SRC_ATOP=9,
   COMPOSITE_DEST_ATOP=10,
   COMPOSITE_XOR=11,
   COMPOSITE_PLUS=12,
   COMPOSITE_SCREEN=13,
   COMPOSITE_OVERLAY=14,
   COMPOSITE_DARKEN=15,
   COMPOSITE_LIGHTEN=16,
   COMPOSITE_COLOR_DODGE=17,
   COMPOSITE_COLOR_BURN=18,
   COMPOSITE_HARD_LIGHT=19,
   COMPOSITE_SOFT_LIGHT=20,
   COMPOSITE_DIFFERENCE=21,
   COMPOSITE_EXCLUSION=22,
   COMPOSITE_MULTIPLY=23,
   COMPOSITE_HSL_HUE=24,
   COMPOSITE_HSL_SATURATION=25,
   COMPOSITE_HSL_COLOR=26,
   COMPOSITE_HSL_LUMINOSITY=27
};
template <typename VarIndex>
struct colrff<VarIndex,32>{
\\uint8   format;
COND_IS_VARIND(Offset24,size_t) sourcePaintOffset;
uint8   compositeMode;
COND_IS_VARIND(Offset24,size_t) backdropPaintOffset;
};template<typename VarIndex> using colrff32=colrff<VarIndex,32> ; //PaintComposite:*/;
colrff<varValueBase,32> colrff<varIndexBase,32>::get(){colrff<varValueBase,32> g;
   g.sourcePaintOffset=this->sourcePaintOffset,
   g.compositeMode=this->compositeMode,
   g.backdropPaintOffset=this->backdropPaintOffset
   return g ;}
 ptype<32>::ty colrff<varValueBase,32>::getPaint(){ }

template <typename VarIndex,size_t... ss >
using _colrfu =pri::variant<colrff<ss,VarIndex>...>;

template <typename VarIndex >
using colrfu = _colrfu<VarIndex,1, 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32>
template <typename VarIndex>
struct colrf {
   uint8 format;
   colrfu<varIndex> f;
   
   template <size_t s>
   decltype(*this) operator=(colrff<VarIndex,s>& h ){pri::get<colrff<VarIndex,s>>(f) = h;return *this;};
};
colrf<varValueBase> colrf<varIndexBase>::get(){
   colrf<varValueBase> g;
   auto lam = [&]<size_t s>(){
      g.format = s; pri::get<colrff<varValueBase,s>>(g.f)=pri::get<colrff<varIndexBase,s>(this->f).get();
   }
   if(pri::Tcase<lam,1, 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32>
      (this->format)){
         return g;
      }

};

#define SWCASE(n) case n : {one(f.f##n);};

ACQRES(colrf<varIndBase>){
   one(f.format);
   one(pri::get(f.format,f.f));
}
USE_ACQRES(colrf<varIndBase>)
typedef struct {
   uint16   glyphID;
   uint16   paletteIndex;// CPAL table entry
}Layer;

typedef struct {
uint16   glyphID;
uint16   firstLayerIndex;
uint16   numLayers;
}BaseGlyph;
typedef struct {
uint16   glyphID;
Offset32   paintOffset;
}BaseGlyphPaintRecord;
 struct BaseGlyphList{
uint32   numBaseGlyphPaintRecords;
BaseGlyphPaintRecord*   baseGlyphPaintRecords;//[numBaseGlyphPaintRecords]
colrf<varIndBase>* paintTables;// TODO probably only in layerlist
};
ACQRES(BaseGlyphList){
one(f.numBaseGlyphPaintRecords);
arr(f.baseGlyphPaintRecords, f.numBaseGlyphPaintRecords);
int numPaintTables=0;
uint16* indPtTb = new uint16[f.numBaseGlyphPaintRecords]; 
for(int i=0;i<f.numBaseGlyphPaintRecords;i++){int j;
   for(j=0;j<i;j++){
      if(f.baseGlyphPaintRecords[j].paintOffset==f.baseGlyphPaintRecords[i].paintOffset){break;}
   };
   if(j<i){continue;};
   numPaintTables++;
};
if(!f.paintTables){f.paintTables=new colrf<varIndBase>[numPaintTables];}
for(int i=0;i<f.numBaseGlyphPaintRecords;i++){
   offone(f.paintTables[i],f.baseGlyphPaintRecords.paintOffset);
};
 };
USE_ACQRES(BaseGlyphList)

typedef struct {
uint32   numLayers;
Offset32*   paintOffsets;//[numLayers]
colrf<varIndBase>* paintTables;
}LayerList;
ACQRES(LayerList){
one(f.numLayers);
arr(f.paintOffsets, f.numLayers);
offmany(f.paintTables,f.paintOffset,f.numLayers);
};
USE_ACQRES(LayerList)

struct COLR0 {
// uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
// OffsetTables;
BaseGlyph* baseGlyphRecords;
Layer* layerRecords ;



   colorFT get(uint16 gid){
      colorFT r ;
      size_t firstLyr;size_t numLyr ;
      for(size_t s=0;s<numBaseGlyphRecords;s++){
         if(baseGlyphRecords[s].glyphID == gid){
            firstLyr= baseGlyphRecords[s].firstLayerIndex;
            numLyr= baseGlyphRecords[s].numLayers;break;
         };
      };
      r.values.resize(numLyr);
      r.numValues = numLyr;
      r.numLayers = 1;
      r.layers.resize(1);
      r.layers[0].numLayers=1;
      r.firstLayerIndex=0;

      std::vector<colrff<varValueBase,2>> ra;
      for(size_t n = firstLyr;n<firstLyr+numLyr;n++){
         colrff<varIndexBase,2> t;t.paletteIndex = layerRecords[n].paletteIndex; 
         ra.push_back(t.get());
      };
      size_t s=0;
      for( colrff<varValueBase,2>& it : r){
         pri::get<colrff<varValueBase,2>&>(r.values[s].f) = it;s++;
      };

   };
 
};
ACQRES(COLR0){
   one(f.numBaseGlyphRecords);
   one(f.baseGlyphRecordsOffset);
   one(f.layerRecordsOffset);
   one(f.numLayerRecords);
   offarr(f.baseGlyphRecords,f.baseGlyphRecordsOffset,f.numBaseGlyphRecords);
   offarr(f.layerRecords,f.layerRecordsOffset,f.numLayerRecords); 
}
USE_ACQRES(COLR0)

struct COLR1{
// uint16   version;
uint16   numBaseGlyphRecords;
Offset32   baseGlyphRecordsOffset;
Offset32   layerRecordsOffset;
uint16   numLayerRecords;
Offset32   baseGlyphListOffset;
Offset32   layerListOffset;
Offset32   clipListOffset;
Offset32   varIndexMapOffset;
Offset32   itemVariationStoreOffset;
// OffsetTables;
BaseGlyph* baseGlyphRecords;
Layer* layerRecords ;// [numLayerRecords]
BaseGlyphList baseGlyphList;
LayerList layerList;
ClipList clipList;
DeltaSetIndexMap deltaSetIndexMap;
ItemVariationStore itemVariationStore;
   #define CFXMACRO(x)  x(2) x(3) x(4) x(5) x(6) x(7) x(8) x(9)   x(12) x(13) x(14) x(15) x(16) x(17) x(18) x(19) x(20) x(21) x(22) x(23) x(24) x(25) x(26) x(27) x(28) x(29) x(30) x(31) 
         #define CFIXMACRO(x) x(1) x(10) x(11) x(32)

         #define COMMACRO(n) ,n

colorFT get( uint16 gid){
      dsim = &deltaSetIndexMap;
     colorFT r ;
      size_t firstLyr;size_t numLyr ;size_t firstOff;
      for(size_t s=0;s<baseGlyphList.numBaseGlyphPaintRecords;s++){
         if(baseGlyphList.baseGlyphPaintRecords[s].glyphID == gid){
            firstOff= baseGlyphList.baseGlyphPaintRecords[s].paintOffset;
            break;
         };
      };
      numLyr= baseGlyphRecords[s].numLayers;
      size_t baseGlSize = sizeof(uint32_t )+ baseGlyphList.numBaseGlyphPaintRecords * sizeof(BaseGlyphPaintRecord);
      for(firstLyr=0;firstLyr<layerList.numLayers;firstLyr++){
         if(firstOff + baseGlSize ==layerList.paintOffsets[firstLyr] ){break;}
      };

      
      size_t sizeLayers;
      size_t sizeValues;
   corlff<varIndBase,1> first= pri::get<corlff<varIndBase,1>(baseGlyphList.paintTables[firstLyr].f) ; 
   size_t firstLyrIndex = first.firstLayerIndex;
   size_t numLayers = first.numLayers;

   r.numValues=0;
   r.numLayers=0;
   
   colrf<varIndBase>& g;
   
      r.compositeMode =CompositeMode::COMPOSITE_SRC_OVER;

for(size_t i=0;i<numLayers;i++){

    g= baseGlyphList.paintTables[i+firstLyrIndex];
   if(g.format!=1){r.values.push_back(g.get())}
   else {
      colrff<varIndBase,1> x = pri::get<colrff<varIndBase,1>>(g.f).get();
      r.layers.push_back(x)}
};
   
};



};//COLR1
ACQRES(COLR1){
   one(f.numBaseGlyphRecords);
   one(f.baseGlyphRecordsOffset);
   one(f.layerRecordsOffset);
   one(f.numLayerRecords);
   one(f.baseGlyphListOffset);
   one(f.layerListOffset);
   one(f.clipListOffset);
   one(f.varIndexMapOffset);
   one(f.itemVariationStoreOffset);
   offarr(f.baseGlyphRecords,f.baseGlyphRecordsOffset,f.numBaseGlyphRecords);
   offarr(f.layerRecords,f.layerRecordsOffset,f.numLayerRecords);
   offarr(f.baseGlyphList,f.baseGlyphListOffset,);
   offone(f.layerList,f.layerListOffset);
   offone(f.clipList,f.clipListOffset);
   offone(f.deltaSetIndexMap,f.varIndexMapOffset;
   offone(f.itemVariationStore,f.itemVariationStoreOffset;
}
USE_ACQRES(COLR1)

typedef struct {
   uint16 version;
   union  {
   COLR0 c0;
   COLR1 c1;
} c;
   colorFT get(uint16 gid){
       switch(version){
      case 0 : {return c.c0.get(gid);};
      case 1 : (return c.c1.get(gid););
   };
   };
}COLR;
ACQRES(COLR){
   one(f.version);
   switch(f.version){
      case 0 : {one(f.c.c0);};
      case 1 : (one(f.c.c1););
   };
}
USE_ACQRES(COLR)
#endif