#version 410

layout (location = 0) in vec2 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 matrix_OBJ;
uniform mat4 proj;
uniform float layer_z;

void main() {
    gl_Position = proj * vec4(aPos,layer_z,1.0);
    TexCoord = aTexCoord;
}