#include "../glm.hpp"

    const rgb BLACK(0, 0, 0);
    const rgb WHITE(255, 255, 255);
    const rgb RED(255, 0, 0);
    const rgb GREEN(0, 255, 0);
    const rgb BLUE(0, 0, 255);
    const rgb YELLOW(255, 255, 0);
    const rgb CYAN(0, 255, 255);
    const rgb MAGENTA(255, 0, 255);
    const rgb ORANGE(255, 165, 0);  
    const rgb PURPLE(128, 0, 128); 
    const rgb BROWN(139, 69, 19); 
    const rgb PINK(255, 192, 203);  
    const rgb GRAY(128, 128, 128);
    const rgb LIME(0, 255, 0);      
    const rgb TEAL(0, 128, 128);    
    const rgb INDIGO(75, 0, 130);   
    const rgb GOLD(255, 215, 0);    


    template <uint length ,  typename T , glm::qualifier Q>
    class image {
        uint x ; 
        uint y  ; 
        std::mat<glm::vec<length,T ,Q> >  content ;  
        
        image(uint _x , uint _y) : x(_x) , y(_y){
            
        }
    };

    template <uint length , typename T , glm::prectision prec >
    class dyn_image : image<length, T , prec  > {

        virtual std::array<>
    };
    
   
    
    template<colorType ct, size_t x ,size_t y>
    using image = std::array<std::array<ct,x> ,y>;
    template <colorType ct, size_t x , size_t y >
    using rgba_static_arr = image<ct,x,y>;
    template <size_t frames , colorType ct, size_t x , size_t y>
    using rgba_dyn_arr = std::array<image<ct,x,y>,frames> ;
    template <colorType ct, size_t x , size_t y>
    using rgb_static_arr =  image<ct,x,y> ;
    template <colorType ct,size_t frames, size_t x , size_t y>
    using rgb_dyn_arr = std::array<image<ct,x,y>,frames> ;
    

    typedef std::vector<std::vector<rgba>>               rgba_static ; 
    typedef std::vector<std::vector<std::array<rgba>>>   rgba_dyn ;
    
    typedef std::vector<std::vector<rgb>>                rgb_static ; 
    typedef std::vector<std::vector<std::vector<rgb>>>   rgb_dyn ;
    
    union rgba_either {
        rgba_static_image static_img,
        rgba_dyn_image dyn_img
    };
