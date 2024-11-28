#version 450

layout(location = 0) in vec2 icoPos; // Full-screen quad vertices (-1 to 1)
layout(location = 1) in float textSize;
out vec2 icofragCoord; // Pass normalized coordinates to the fragment shader

void main() {
    gl_Position = vec4(icoPos, 0.0, 1.0); // Directly output NDC
    icofragCoord = inPosition;                  // Pass NDC coordinates to fragment shader
}