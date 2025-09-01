#include "vects.hpp"
#include "glm/geometric.hpp"
#include "math.h"
namespace pri{

mat4x4 ortho(float left,float right,float top,float bottom,float near,float far){
    mat4x4 result; result = result(1.0f);
    result[0][0] = 2.0f / (right - left);
    result[1][1] = 2.0f / (top - bottom);
    result[2][2] = -2.0f / (zFar - zNear);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(zFar + zNear) / (zFar - zNear);
    return result;
    };
mat4x4 perpective(float fovY, float aspect, float zNear, float zFar){
 mat4x4 result ; result = result(0.0f);
 float tanHalfFovY = tan(fovY / 2.0f);
    
    result[0][0] = 1.0f / (aspect * tanHalfFovY);
    result[1][1] = 1.0f / tanHalfFovY;
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    
    return result;
};
};