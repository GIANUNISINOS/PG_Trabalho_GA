#version 410

in vec2 TexCoord;

uniform sampler2D sprite_OBJ;
uniform float offsetX;
uniform float offsetY;

out vec4 frag_color;

void main() {
    vec4 texel0 = texture(sprite_OBJ,vec2(TexCoord.x + offsetX,-(TexCoord.y + offsetY)));
    frag_color = texel0;
}