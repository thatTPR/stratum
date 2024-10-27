#include "sys.hpp"
    class field ;
    class Field_2d : field {
        glm::fvec2 x ;
        glm::fvec2 y ;
        glm::angle phi ;
    }
    
    class Field_3d : field {
        glm::fvec3 x ;
        glm::fvec3 y ;
        glm::angle phi ;
        glm::angle theta ;
    };
    class Field_Sphere_3d : field{
        glm::fvec3 x ;
        
    };
    class Field_Sphere_2d : field {
        glm::vec<float,2,glm::defaultp> x ; 
    };
    

// TODO allign correctly
    class physics {
        bool gravity_override ;
        float gravity ;
        float air_current ;
        float magnetic;  // Unlike gravity defines a gradient throughout the field

    };
    
    template <DIM T>
    class physicsField {
        glm::vec3 pos ;
        glm::vec3    
        float gradient ; 
        physics properties ; 
    };
    
    class distorsion_3d {
        glm::fvec3 x ;
        glm::fvec3 y ;
        glm::fvec2 orientation ;
    };
    class distortion_2d {

    };

    class physics_constraint {
        
        glm::bvec3 xyz_pos_lock ;
        glm::bvec3 xyx_rot_lock ; 
    };
    class physical_properties {
        public:
        
        float gravitational_mass  ;
        float inertial_mass ;
        // Normalised between 0 and 1 : with 1 meaning perfect elasticity and 0 meaning complete absorbtion ( no moving ⌈)
        bool collision_enabled = true ;
        unsigned float collision_dampening ; // Higher value means higher elasticity value above 1 means multiplied 
        
        float friction ;
        float refraction ; 
        physical_properties(float _grav_mass, float _inert_mass , bool _collision_enabled , unsigned float _collision_dampening ,float _friction , float _refraction ): grav_mass(_grav_mass),inert_mass(_inert_mass),collision_enabled(_collision_enabled),collision_dampening(_collision_dampening) ,friction(_friction) ,refraction(_refraction){};
        physical_properties();
    };