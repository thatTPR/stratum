#include <fstream>
#include <petri/vecs.hpp>
#include <petri/vects.hpp>

class acqres {
    // strct s ;
    vect<ivec4> ranges ;
    vect<ivec2> type_indices ;
    virtual void read();
    virtual void feed(ivec4 range){

    };

};