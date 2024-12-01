#version 450
in uint n ; // Line strip
in vec2 icoCoord; 
out vec2 icofragCoord;
out vec2 

#ifdef EVENT 
// Square    
vec2 pinico(){
    
}; 
#endif
#ifdef RES
// circle
vec2 pinico( ){ 
    
}; 
#endif 
#ifdef exec
// triangle
vec4 pinico(){
   
}; 
#endif
#ifdef 
#ifdef FUNC
//cube
vec4 pinico(){

};
#endif
#ifdef ALL
vec4 pinico(uint which)
#endif
void main() {
    
    gl_Position = vec4(icoCoord, 0.0, 1.0); // Directly output NDC
    icofragCoord = icoCoord;                  // Pass NDC coordinates to fragment shader
}