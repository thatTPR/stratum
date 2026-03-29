#include <StmModel.hpp>
#include <cstddef>


// Scope is entities , triggers, models and building structures

class StmWorld { 

// 
    // Tables
//    plnt,
//    model
//    
    
   
    struct plnt {
        uint16_t size;
        size_t nameSize;
        char* name ;
        struct {
            uint32_t bound_size ; // Bounding box size in meters; Should be a power of 2
            uint32_t 
        } manifold;
    };
};