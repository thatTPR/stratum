
// TOOD not ready
class compl {
    // I J K rules;
    // Unit first eg: I3 + 4; or 4 + I3.5 ;

    template <typename inte>
    compl operator*(compl& lhs, inte& rhs );
    

    compl operator+(compl& lhs , inte& rhs);
    compl operator-(compl& lhs, inte& rhs);
    compl operator/(compl& lhs, inte& rhs);

};

class variable {
    size_t order ;
    double val ;
    variable(size_t t) : order(t);
};

 const variable x(1) ;
 const variable y(2) ;
 const variable z(3) ;
 const variable w(4) ;
 const variable v(5) ;
 const variable u(6) ;


 const variable e(0) ;
 const variable pi(0,3.1415926358979) ;
class limit ;
class zero : limit;
class inf : limit ; 
class minf : limit ;

class exprvec {
    enum ops {
        plus,
        minus,
        div,
        mul,
        fun
    };
    typedef union {
        double constant;
        variable var; 
        ops operation;
        func func;
        exprvec expr ;
    } member;
    
    std::vector<member> vec ;
    exprvec(double constant, ops op){vec.push_back(constant); vec.push_back(op); };
    exprvec(ops op , double cons1 , double cons2){vec.push_back(constant); vec.push_back(op); };
};


class func {
    public:
    typedef double (*fp)(double,double) ;
    fp func; 
    typedef union  {
        double constant ;
        variable var; 
    }args;
    args ar[2];
    bool cons[2];
    double operator()(double _x , double _y){
        return this->func( _x,_y  ); 
    };
    func operator()(variable var1, variable var2){
        this->ar[0]=var1;
        this->ar[1]=var2;
        this->cons[0] = false; this->cons[1] = false; 
        return func ;
    };
    func operator()(double c , variable var){
        this->ar = {c,var};
        this->cons = {true,false }; 
        return func ;
    };
    func operator()( variable var,double c){
        this->ar = {var,c};
        this->cons = {false,true };
        return func;  
    };

    auto operator!(func& f){
        if(cons[0] && cons[1]){
            return func(ar[0],ar[1]);
        }
        else return *this ;
    };
    func(fp fu ) : func(fu) ;
};
#include <math.h>
func logf(&log);
func pow(&pow);

double lnef(double x, double y){return ln(x);}
func lnf(&lnef);


class expr {
    exprvec vec(0,exprvec::ops::plus) ;

    
    expr& operator+=(exprvec::ops op){this->exprvec.push(op) ;}
    expr& operator+=(double constant){this->exprvec.push(constant) ;}
    expr& operator+=(variable var){this->exprvec.push(var) ;}
    
    
    expr operator+(expr& s, double c ){s+= exprvec::ops::plus; s+=c;  };
    expr operator-(expr& s, double c ){s+= exprvec::ops::minus; s+=c;  };
    expr operator/(expr& s, double c ){s+= exprvec::ops::div; s+=c;  };
    expr operator*(expr& s, double c ){s+= exprvec::ops::mul; s+=c;  };
    
    
    expr operator+(expr& s, variable c ){s+= exprvec::ops::plus; s+=c;  };
    expr operator-(expr& s, variable c ){s+= exprvec::ops::minus; s+=c;  };
    expr operator/(expr& s, variable c ){s+= exprvec::ops::div; s+=c;  };
    expr operator*(expr& s, variable c ){s+= exprvec::ops::mul; s+=c;  };

    
    expr operator+(expr& s, func c ){s+= exprvec::ops::plus; s+=c;  };
    expr operator-(expr& s, func c ){s+= exprvec::ops::minus; s+=c;  };
    expr operator/(expr& s, func c ){s+= exprvec::ops::div; s+=c;  };
    expr operator*(expr& s, func c ){s+= exprvec::ops::mul; s+=c;  };
    
    exprvec operator=(expr& e){
        exprvec s = e.vec; return s;
    };
    expr operator()(expr& e){exprvec  s = e ; return s;};
    


    void derive(size_t order){ // Pass system
        // (A + B)` = A` + B` 
        
        // c*x` = c
        // c*x^n = c*n*x^(n-1) ;
        // log(a,x) = 1/(x*ln(a)) ;
        // ln(f(x)) = f(x)` /f(x) ;
        // loc(x,a) = 1/(a)

    };
    void integral(size_t order,double x0 , double x1 );
    void integral(size_t order,double x0 , double y0, double x1,double y1 );
    void integral(size_t order,double x0, double y0 , double z0, double x1, double y1 , double z1);
    void integral(size_t order,double x0, double y0 , double z0, double w0, double x1, double y1 , double z1,double w1);

    void integral(glm::dvec2 _0 , glm::dvec2 _1){this->integral(_0.x,_0.y,_1.x,_1.y);};
    void integral(glm::dvec3 _0 , glm::dvec3 _1){this->integral(_0.x,_0.y,_0.z,_1.x,_1.y,_1.z);};
    void integral(glm::dvec4 _0 , glm::dvec4 _1){this->integral(_0.x,_0.y,_0.z,_0.w,_1.x,_1.y,_1.z,_1.w);};
};