#include "svg.hpp"
#define SVGTAGS     aTag,animateTag,animateMotionTag,animateTransformTag,circleTag,clipPathTag,defsTag,descTag,ellipseTag,feBlendTag,feColorMatrixTag,feComponentTransferTag,feCompositeTag,feConvolveMatrixTag,feDiffuseLightingTag,feDisplacementMapTag,feDistantLightTag,feDropShadowTag,feFloodTag,feFuncATag,feFuncBTag,feFuncGTag,feFuncRTag,feGaussianBlurTag,feImageTag,feMergeTag,feMergeNodeTag,feMorphologyTag,feOffsetTag,fePointLightTag,feSpecularLightingTag,feSpotLightTag,feTileTag,feTurbulenceTag,filterTag,foreignObjectTag,gTag,imageTag,lineTag,linearGradientTag,markerTag,maskTag,metadataTag,mpathTag,pathTag,patternTag,polygonTag,polylineTag,radialGradientTag,rectTag,scriptTag,setTag,stopTag,styleTag,svgTag,switchTag,symbolTag,textTag,textPathTag,titleTag,tspanTag,useTag,viewTag

#include <iostream>
std::string toStr(uint32_t s) {
    std::string str=(char)s>>(3*8); str+= (char)(s>>(2*8) &0xFF) ;str+= (char)(s>>8 & 0xFF) ;str+= (char)s & 0xFF;
    return str;
};
template <typename T,typename... Ts>
void printTags(){
    std::cout<<toStr(T::tag) << " " << t::tag;
    if constexpr (sizeof...(Ts)>0){printTags<Ts...>();}
};
int main(){
    printTags(SVGTAGS) ;
};