#pragma once
#include <initializer_list>
#include <memory>
#define SWIZZLE_ARR
#include "vects.hpp"
typedef    unsigned long long int    uint64;
typedef    unsigned int              uint32;
typedef    unsigned short int        uint16;
typedef    long long int             int64;
typedef    int                       int32;
typedef    short int                 int16;
typedef    unsigned long long int    lluint;
typedef    unsigned long int         luint;
typedef    unsigned int              uint;
typedef    unsigned short int        suint;
typedef    unsigned short short int  ssuint;    
typedef    long long int             llint;   
typedef    long int                  lint;  
typedef    short int                 sint;  
typedef    short short int           ssint;   
typedef    long double               double128;
typedef    double                    double64;
typedef    float                     float32;




using dvec2=arr<double,2> ;  
using dvec3=arr<double,3> ;  
using dvec4=arr<double,4> ;  //
using ldvec2=arr<long double,2> ;  
using ldvec3=arr<long double,3> ;  
using ldvec4=arr<long double,4> ;  //
using suvec2=arr<short unsigned int,2> ;
using suvec3=arr<short unsigned int,3> ;
using suvec4=arr<short unsigned int,4> ;
using sivec2=arr<short int,2> ;
using sivec3=arr<short int,3> ;
using sivec4=arr<short int,4> ;//
using luvec2=arr<long unsigned int,2> ;
using luvec3=arr<long unsigned int,3> ;
using luvec4=arr<long unsigned int,4> ;
using livec2=arr<long int,2> ;
using livec3=arr<long int,3> ;
using livec4=arr<long int,4> ;//
using lluvec2=arr<long long unsigned int,2> ;
using lluvec3=arr<long long unsigned int,3> ;
using lluvec4=arr<long long unsigned int,4> ;
using llivec2=arr<long long int,2> ;
using llivec3=arr<long long int,3> ;
using llivec4=arr<long long int,4> ;//
using dmat2x2=mat<double,2,2> ;
using dmat2x3=mat<double,2,3> ;
using dmat2x4=mat<double,2,4> ;
using dmat3x2=mat<double,3,2> ;
using dmat3x3=mat<double,3,3> ;
using dmat3x4=mat<double,3,4> ;
using dmat4x2=mat<double,4,2> ;
using dmat4x3=mat<double,4,3> ;
using dmat4x4=mat<double,4,4> ;
using sumat2x2=mat<short unsigned int,2,2> ;
using sumat2x3=mat<short unsigned int,2,3> ;
using sumat2x4=mat<short unsigned int,2,4> ;
using sumat3x2=mat<short unsigned int,3,2> ;
using sumat3x3=mat<short unsigned int,3,3> ;
using sumat3x4=mat<short unsigned int,3,4> ;
using sumat4x2=mat<short unsigned int,4,2> ;
using sumat4x3=mat<short unsigned int,4,3> ;
using sumat4x4=mat<short unsigned int,4,4> ;
using simat2x2=mat<short int,2,2> ;
using simat2x3=mat<short int,2,3> ;
using simat2x4=mat<short int,2,4> ;
using simat3x2=mat<short int,3,2> ;
using simat3x3=mat<short int,3,3> ;
using simat3x4=mat<short int,3,4> ;
using simat4x2=mat<short int,4,2> ;
using simat4x3=mat<short int,4,3> ;
using simat4x4=mat<short int,4,4> ;
using ldmat2x2=mat<long double,2,2> ;
using ldmat2x3=mat<long double,2,3> ;
using ldmat2x4=mat<long double,2,4> ;
using ldmat3x2=mat<long double,3,2> ;
using ldmat3x3=mat<long double,3,3> ;
using ldmat3x4=mat<long double,3,4> ;
using ldmat4x2=mat<long double,4,2> ;
using ldmat4x3=mat<long double,4,3> ;
using ldmat4x4=mat<long double,4,4> ;
using lumat2x2=mat<long unsigned int,2,2> ;
using lumat2x3=mat<long unsigned int,2,3> ;
using lumat2x4=mat<long unsigned int,2,4> ;
using lumat3x2=mat<long unsigned int,3,2> ;
using lumat3x3=mat<long unsigned int,3,3> ;
using lumat3x4=mat<long unsigned int,3,4> ;
using lumat4x2=mat<long unsigned int,4,2> ;
using lumat4x3=mat<long unsigned int,4,3> ;
using lumat4x4=mat<long unsigned int,4,4> ;
using limat2x2=mat<long int,2,2> ;
using limat2x3=mat<long int,2,3> ;
using limat2x4=mat<long int,2,4> ;
using limat3x2=mat<long int,3,2> ;
using limat3x3=mat<long int,3,3> ;
using limat3x4=mat<long int,3,4> ;
using limat4x2=mat<long int,4,2> ;
using limat4x3=mat<long int,4,3> ;
using limat4x4=mat<long int,4,4> ;
using llumat2x2=mat<long long unsigned int,2,2> ;
using llumat2x3=mat<long long unsigned int,2,3> ;
using llumat2x4=mat<long long unsigned int,2,4> ;
using llumat3x2=mat<long long unsigned int,3,2> ;
using llumat3x3=mat<long long unsigned int,3,3> ;
using llumat3x4=mat<long long unsigned int,3,4> ;
using llumat4x2=mat<long long unsigned int,4,2> ;
using llumat4x3=mat<long long unsigned int,4,3> ;
using llumat4x4=mat<long long unsigned int,4,4> ;
using llimat2x2=mat<long long int,2,2> ;
using llimat2x3=mat<long long int,2,3> ;
using llimat2x4=mat<long long int,2,4> ;
using llimat3x2=mat<long long int,3,2> ;
using llimat3x3=mat<long long int,3,3> ;
using llimat3x4=mat<long long int,3,4> ;
using llimat4x2=mat<long long int,4,2> ;
using llimat4x3=mat<long long int,4,3> ;
using llimat4x4=mat<long long int,4,4> ;


using bvec2=arr<bool,2> ; 
using bvec3=arr<bool,3> ;
using bvec4=arr<bool,4> ;
using uvec2=arr<unsigned int,2> ;
using uvec3=arr<unsigned int,3> ;
using uvec4=arr<unsigned int,4> ;
using ivec2=arr<int,2> ;
using ivec3=arr<int,3> ;
using ivec4=arr<int,4> ;//
using vec2=arr<float,2> ;
using vec3=arr<float,3> ;
using vec4=arr<float,4> ;//
using bmat2x2=mat<bool,2,2> ;
using bmat2x3=mat<bool,2,3> ;
using bmat2x4=mat<bool,2,4> ;
using bmat3x2=mat<bool,3,2> ;
using bmat3x3=mat<bool,3,3> ;
using bmat3x4=mat<bool,3,4> ;
using bmat4x2=mat<bool,4,2> ;
using bmat4x3=mat<bool,4,3> ;
using bmat4x4=mat<bool,4,4> ;
using umat2x2=mat<unsigned int,2,2> ;
using umat2x3=mat<unsigned int,2,3> ;
using umat2x4=mat<unsigned int,2,4> ;
using umat3x2=mat<unsigned int,3,2> ;
using umat3x3=mat<unsigned int,3,3> ;
using umat3x4=mat<unsigned int,3,4> ;
using umat4x2=mat<unsigned int,4,2> ;
using umat4x3=mat<unsigned int,4,3> ;
using umat4x4=mat<unsigned int,4,4> ;
using imat2x2=mat<int,2,2> ;
using imat2x3=mat<int,2,3> ;
using imat2x4=mat<int,2,4> ;
using imat3x2=mat<int,3,2> ;
using imat3x3=mat<int,3,3> ;
using imat3x4=mat<int,3,4> ;
using imat4x2=mat<int,4,2> ;
using imat4x3=mat<int,4,3> ;
using imat4x4=mat<int,4,4> ;
using mat2x2=mat<float,2,2> ;
using mat2x3=mat<float,2,3> ;
using mat2x4=mat<float,2,4> ;
using mat3x2=mat<float,3,2> ;
using mat3x3=mat<float,3,3> ;
using mat3x4=mat<float,3,4> ;
using mat4x2=mat<float,4,2> ;
using mat4x3=mat<float,4,3> ;
using mat4x4=mat<float,4,4> ;//

template <typename t,size_t r> bool[r] operator<(arr<t,r>& lhs, arr<t,r>& rhs){bool s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]<rhs[i]);};return s;};
template <typename t,size_t r> bool[r] operator>(arr<t,r>& lhs, arr<t,r>& rhs){bool s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]>rhs[i]);};return s;};
template <typename t,size_t r> bool[r] operator<=(arr<t,r>& lhs, arr<t,r>& rhs){bool s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]<=rhs[i]);};return s;};
template <typename t,size_t r> bool[r] operator>=(arr<t,r>& lhs, arr<t,r>& rhs){bool s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]>=rhs[i]);};return s;};
template <typename t,size_t r> bool[r] operator==(arr<t,r>& lhs, arr<t,r>& rhs){bool s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]==rhs[i]);};return s;};
template <typename t,size_t r> bool[r] operator!=(arr<t,r>& lhs, arr<t,r>& rhs){bool s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]!=rhs[i]);};return s;};
template <typename t,size_t r> arr<t,r> operator+(arr<t,r>& lhs, arr<t,r>& rhs){t s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]+rhs[i]);};return s;};
template <typename t,size_t r> arr<t,r> operator-(arr<t,r>& lhs, arr<t,r>& rhs){t s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]-rhs[i]);};return s;};
template <typename t,size_t r> arr<t,r> operator/(arr<t,r>& lhs, arr<t,r>& rhs){t s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]/rhs[i]);};return s;};
template <typename t,size_t r> arr<t,r> operator*(arr<t,r>& lhs, arr<t,r>& rhs){t s[r]; for(int i = 0; i<r;i++){s[i] = (lhs[i]*rhs[i]);};return s;};
template <typename t,size_t r> arr<t,r> operator()(arr<t,r>& lhs,t val){t s[r]; for(int i = 0; i<r;i++){s[i] =val;};return s;};


template <typename t,size_t r,size_t rs>
arr<t,r> vcon(std::initializer_list<t> val ) {t lhs[r] ; int j=0;for(t i : val){lhs[j]=i;j++;};return lhs ;};
template <typename t, size_t r , size_t rs >
arr<t,r> vcon( t val[rs] ){ t lhs[r] ; for(int i =0 ; i <r ; i++){lhs[i]=val[i];};return lhs;};
template <typename t, size_t r , size_t rs >
arr<t,r> vcon(t v, t val[rs] ){t lhs[r];lhs[0]=v; for(int i =1 ; i <r ; i++){lhs[i]=val[i-1];}; return lhs;};
template <typename t, size_t r , size_t rs  >
arr<t,r> vcon(t v, t vs,t val[rs] ){t lhs[r];lhs[0]=v;lhs[1]=vs; for(int i =2 ; i <r ; i++){lhs[i]=val[i-2];}; return lhs;};
template <typename t, size_t r , size_t rs ,size_t rv >
arr<t,r> vcon(t vs[rs],t val[rv] ){t lhs[r];for(int i=0;i<rs;i++){lhs[i]=vs[i];}; for(int i =rs ; i <r ; i++){lhs[i]=val[i-rs];}; return lhs;};
template <typename t, size_t r , size_t rs  >
arr<t,r> vcon(t vs[rs],t val ){t lhs[r];for(int i=0;i<rs;i++){lhs[i]=vs[i];}; lhs[rs]=val;};
template <typename t, size_t r , size_t rs  >
arr<t,r> vcon(t vs[rs],t val , t vals){t lhs[r];for(int i=0;i<rs;i++){lhs[i]=vs[i];}; lhs[rs]=val;lhs[rs+1]=vals; return lhs;};

template <typename t,size_t rs>
arr<t,2> vec2(std::initializer_list<T> r) { return vcon<t,2,rs>(val);};
template <typename t,size_t rs>
arr<t,2> vec2(t val[rs]) { return vcon<t,2,rs>( val);};
template <typename t,size_t rs>
arr<t,2> vec2(t v,t val[rs]) { return vcon<t,2,rs>(v, val);};
template <typename t,size_t rs>
arr<t,2> vec2(t v, t vs,t val[rs]) { return vcon<t,2,rs>(v,vs, val);};
template <typename t,size_t rs,size_t rv>
arr<t,2> vec2(t vs[rs],t val[rv]) { return vcon<t,2,rs,rv>(vs,val);};
template <typename t,size_t rs>
arr<t,2> vec2(t vs[rs],t val) { return vcon<t,2,rs>(vs,val);};
template <typename t,size_t rs>
arr<t,2> vec2(t vs[rs],t val), tvals { return vcon<t,2,rs>(vs,val,vals);};


template <typename t,size_t rs>
arr<t,2> vec2(std::initializer_list<T> r) { return vcon<t,3,rs>( val);};
template <typename t,size_t rs>
arr<t,3> vec3(t val[rs]) { return vcon<t,3,rs>( val);};
template <typename t,size_t rs>
arr<t,3> vec3(t v,t val[rs]) { return vcon<t,3,rs>(v, val);};
template <typename t,size_t rs>
arr<t,3> vec3(t v, t vs,t val[rs]) { return vcon<t,3,rs>(v,vs, val);};
template <typename t,size_t rs,size_t rv>
arr<t,3> vec3(t vs[rs],t val[rv]) { return vcon<t,3,rs,rv>(vs,val);};
template <typename t,size_t rs>
arr<t,3> vec3(t vs[rs],t val) { return vcon<t,3,rs>(vs,val);};
template <typename t,size_t rs>
arr<t,3> vec3(t vs[rs],t val), tvals { return vcon<t,3,rs>(vs,val,vals);};

template <typename t,size_t rs>
arr<t,2> vec4(std::initializer_list<T> r) { return vcon<t,4,rs>(val);};
template <typename t,size_t rs>
arr<t,4> vec4(t val[rs]) { return vcon<t,4,rs>( val);};
template <typename t,size_t rs>
arr<t,4> vec4(t v,t val[rs]) { return vcon<t,4,rs>(v, val);};
template <typename t,size_t rs>
arr<t,4> vec4(t v, t vs,t val[rs]) { return vcon<t,4,rs>(v,vs, val);};
template <typename t,size_t rs,size_t rv>
arr<t,4> vec4(t vs[rs],t val[rv]) { return vcon<t,4,rs,rv>(vs,val);};
template <typename t,size_t rs>
arr<t,2> vec4(t vs[rs],t val) { return vcon<t,4,rs>(vs,val);};
template <typename t,size_t rs>
arr<t,2> vec4(t vs[rs],t val), tvals { return vcon<t,4,rs>(vs,val,vals);};


template <typename t,size_t r,size_t c> bool[r][c]  operator<( arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){bool s[r][c]; for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]< rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c> bool[r][c]  operator>( arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){bool s[r][c]; for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]> rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c> bool[r][c]  operator<=(arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){bool s[r][c]; for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]<=rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c> bool[r][c]  operator>=(arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){bool s[r][c]; for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]>=rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c> bool[r][c]  operator==(arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){bool s[r][c]; for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]==rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c> bool[r][c]  operator!=(arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){bool s[r][c]; for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]!=rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c>     arr<t,r>[c] operator+( arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){t s[r][c];    for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]+ rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c>     arr<t,r>[c] operator-( arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){t s[r][c];    for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]- rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c>     arr<t,r>[c] operator/( arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){t s[r][c];    for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]/ rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c>     arr<t,r>[c] operator*( arr<t,r>[c]& lhs, arr<t,r>[c]& rhs){t s[r][c];    for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = (lhs[i][j]* rhs[i][j]);};};return s;};
template <typename t,size_t r,size_t c>     arr<t,r>[c] operator()( arr<t,r>[c]& lhs, t val){t s[r][c];    for(int i = 0; i<r;i++){for(int j=0;j<c;j++){ s[i][j] = val*(i==j);};};return s;};


/*
x
y 
z
w

xy
xz
xw

yx
yz
yw


zx
zw
zy

wx 
wy 
wz

xyz
xzy
xwy
xyw
xzw
xwz

zxw
zxy
zwy
zyx
zxw
zwx
*/
typedef size_t swit;
template <swit sit>
class swizzle {
     public:
    swit s = sit; 
    swizzle(){this->s = sit;};
    swit&  operator=(swizzle<sit> s){return s.sit;};
};
swizzle<0> x ; 
swizzle<1> y ; 
swizzle<2> z ; 
swizzle<3> w ; 
template <swit s, swit xt=0,swit yt=0,swit zt=0,swit wt=0>
struct swizzle_arr{
    swit x=xt;
    swit y=yt;
    swit z=zt;
    swit w=wt;
    swit si = s;
    // swit y=yt;
    // swit z=zt;
    // swit w=wt;
    
};
typedef size_t swit;
template <swit sit>
class swizzle {
     public:
    swit s = sit; 
    swizzle(){this->s = sit;};

   swit& operator=(swizzle<sit> s){return s.s;};
    
};
template <swit s, swit xt=0,swit yt=0,swit zt=0,swit wt=0>
struct swizzle_arr{
    swit x=xt;
    swit y=yt;
    swit z=zt;
    swit w=wt;
    swit si = s;
    // swit y=yt;
    // swit z=zt;
    // swit w=wt;
    
};
swizzle<0> x ; 
swizzle<1> y ; 
swizzle<2> z ; 
swizzle<3> w ; 
template <swit as,swit bs>
swizzle_arr<2> operator*(swizzle<bs> a, swizzle<bs> b){
    swizzle_arr<2> n ;
    n.x=a.s;n.y=b.s;
    return n;
};

template<swit bs>
swizzle_arr<3> operator*(swizzle_arr<2> a,swizzle<bs> b)
{
    swizzle_arr<3> n ;
    n.x=a.x;n.y=a.y;n.z=b; return n;
};
template<swit bs>
swizzle_arr<3> operator*(swizzle<bs> b,swizzle_arr<2> a)
{
    swizzle_arr<3> n ;
    n.x=b;n.y=a.x;n.z=b.y; return n;
};
template<swit bs>
swizzle_arr<4> operator*(swizzle_arr<3> a,swizzle<bs> b)
{
    swizzle_arr<4> n ;
    n.x=a.x;n.y=a.y;n.z=a.z;n.w=b;  return n;
};
template<swit bs>
swizzle_arr<4> operator*(swizzle<bs> b,swizzle_arr<3> a)
{
    swizzle_arr<4> n ;
    n.x=b;n.y=a.x;n.z=a.y;n.w=a.z ;
    return n;
};
template<swit bs>
swizzle_arr<4> operator*(swizzle_arr<2> a,swizzle_arr<2> b)
{
    swizzle_arr<4> n ;
    n.x=a.x;n.y=a.y;n.z=b.x;n.w=b.y;  return n;
};
template <typename T, swit r>
arr<T,1> operator<<(swizzle<r> s ){
    arr<T,1> res;res[0]=s.s;
};
template <typename T, swit r>
arr<T,2> operator<<(arr<T,r> h,swizzle_arr<2> s){
    arr<T,2> res;res[0]=h[s.x];res[1]=h[s.y];return res;
};
template <typename T, swit r>
arr<T,3> operator<<(arr<T,r> h,swizzle_arr<3> s){
    arr<T,3> res;res[0]=h[s.x];res[1]=h[s.y];res[2]=h[s.z];return res;
};
template <typename T, swit r>
arr<T,4> operator<<(arr<T,r> h,swizzle_arr<4> s){
    arr<T,4> res;
    res[0]=h[s.x];res[1]=h[s.y];res[2]=h[s.z];res[3]=h[s.w];return res;
};