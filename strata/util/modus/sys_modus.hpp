#include "../sys_obj.hpp"


namespace sys_m {
    class surface {
        std::array<>

        surface getSurfaceForObject(glm::vec2 point , float radius){

        };
    };

    class texture_brush {
        float outer_r ;
        float inner_r ;
        virtual void stroke(float length , float speed , surface ){

        };
        virtual void apply()
    };
};