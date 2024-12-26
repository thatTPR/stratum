#include <impl.hpp>
#include <android/input.h>
namespace impl_android{
    struct MOUSE : impl::MOUSE {
        glm::vec2 Pos(){};
        
    };
    struct TOUCH : impl::TOUCH {
        handle(){

        };
    };
    class SYS : impl::SYS {

        
    };
};