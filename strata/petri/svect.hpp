#include "vects.hpp"
template <typename T,size_t dim>
class svect : public vect<T> {
    using x = this[0]; 
    using y = this[1]; 
    using z = this[2];
    using w = this[3];
    
    svect(T a, T b ){
        this=new svect<2>;
        this[0]=a;
        this[1]=b;
    };
    svect(T a ){this=new svect<1>;this[0]=a;    };
    namespace fours{
    svect(T a, T b , T c, T d){
        this=new svect<4>;
        this[0]=a;
        this[1]=b;
        this[2]=c;
        this[3]=d;
    };

    svect<4> xyzw(){return svect(x,y,z,w); };
    svect<4> xywz(){return svect(x,y,w,z); };
    svect<4> xwzy(){return svect(x,w,z,y); };
    svect<4> xwyz(){return svect(x,w,y,z); };
    svect<4> xzyw(){return svect(x,z,y,w); };
    svect<4> xzwy(){return svect(x,z,w,y); };
    svect<4> yzwx(){return svect(y,z,w,x); };
    svect<4> yzxw(){return svect(y,z,x,w); };
    svect<4> ywzx(){return svect(y,w,z,x); };
    svect<4> ywxz(){return svect(y,w,x,z); };
    svect<4> yxzw(){return svect(y,x,z,w); };
    svect<4> yxwz(){return svect(y,x,w,z); };
    svect<4> zxwy(){return svect(z,x,w,y); };
    svect<4> zxyw(){return svect(z,x,y,w); };
    svect<4> zyxw(){return svect(z,y,x,w); };
    svect<4> zywx(){return svect(z,y,w,x); };
    svect<4> zwxy(){return svect(z,w,x,y); };
    svect<4> zwyz(){return svect(z,w,y,z); };
    svect<4> wxyz(){return svect(w,x,y,z); };
    svect<4> wxzy(){return svect(w,x,z,y); };
    svect<4> wyzx(){return svect(w,y,z,x); };
    svect<4> wyxz(){return svect(w,y,x,z); };
    svect<4> wzxy(){return svect(w,z,x,y); };
    svect<4> wzyx(){return svect(w,z,y,x); };
    }   ;
    using x= std::enable_if<dim>=4,fours>::type; 
    using x::;
namespace threes {


    svect(T a, T b, T c ){
        this=new svect<3>;
        this[0]=a;
        this[1]=b;
        this[2]=c;
    };
    svect<3> xyz(){return svect(x,y,z); };
    svect<3> xyw(){return svect(x,y,w); };
    svect<3> xzy(){return svect(x,z,y); };
    svect<3> xzw(){return svect(x,z,w); };
    svect<3> xwy(){return svect(x,w,y); };
    svect<3> xwz(){return svect(x,w,z); };
    svect<3> yzx(){return svect(y,z,x); };
    svect<3> yzw(){return svect(y,z,w); };
    svect<3> ywz(){return svect(y,w,z); };
    svect<3> ywx(){return svect(y,w,x); };
    svect<3> yxz(){return svect(y,x,z); };
    svect<3> yxw(){return svect(y,x,w); };
    svect<3> zxy(){return svect(z,x,y); };
    svect<3> zxw(){return svect(z,x,w); };
    svect<3> zyx(){return svect(z,y,x); };
    svect<3> zyw(){return svect(z,y,w); };
    svect<3> zwx(){return svect(z,w,x); };
    svect<3> zwy(){return svect(z,w,y); };
    svect<3> wxz(){return svect(w,x,z); };
    svect<3> wxy(){return svect(w,x,y); };
    svect<3> wzx(){return svect(w,z,x); };
    svect<3> wzy(){return svect(w,z,y); };
    svect<3> wyx(){return svect(w,y,x); }; 
    svect<3> wyz(){return svect(w,y,z); };
};
    using y=std::enable_if<dim>=3 , threes >::type;
    using y:: ;
    namespace twos {

    svect<2> xy(){return svect<2>(x,y) ;};
    svect<2> xz(){return svect<2>(x,z) ;};
    svect<2> xw(){return svect<2>(x,w) ;};
    svect<2> yx(){return svect<2>(y,x) ;};
    svect<2> yz(){return svect<2>(y,z) ;};
    svect<2> yw(){return svect<2>(y,w) ;};
    svect<2> zx(){return svect<2>(z,x) ;};
    svect<2> zy(){return svect<2>(z,y) ;};
    svect<2> zw(){return svect<2>(z,w) ;};
    svect<2> wx(){return svect<2>(w,x)  ;}; 
    svect<2> wy(){return svect<2>(w,y)  ;}; 
    svect<2> wz(){return svect<2>(w,z)  ;}; 
    };
    using z=std::enable_if<dim>=1 , twos >::type;
    using z:: ;
    
    
};